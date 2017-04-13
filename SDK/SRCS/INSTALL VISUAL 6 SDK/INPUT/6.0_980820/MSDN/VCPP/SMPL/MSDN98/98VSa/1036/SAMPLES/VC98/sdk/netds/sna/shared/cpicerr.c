/*****************************************************************************
 *
 *  MODULE NAME: CPICERR.C
 *
 *  COPYRIGHTS:
 *             This module contains code made available by IBM
 *             Corporation on an AS IS basis.  Any one receiving the
 *             module is considered to be licensed under IBM copyrights
 *             to use the IBM-provided source code in any way he or she
 *             deems fit, including copying it, compiling it, modifying
 *             it, and redistributing it, with or without
 *             modifications.  No license under any IBM patents or
 *             patent applications is to be implied from this copyright
 *             license.
 *
 *             A user of the module should understand that IBM cannot
 *             provide technical support for the module and will not be
 *             responsible for any consequences of use of the program.
 *
 *             Any notices, including this one, are not to be removed
 *             from the module without the prior written consent of
 *             IBM.
 *
 *  AUTHOR:    Peter J. Schwaller
 *             VNET:     PJS at RALVM6           Tie Line: 444-4376
 *             Internet: pjs@ralvm6.vnet.ibm.com     (919) 254-4376
 *
 *             John Q. Walker
 *             VNET:     JOHNQ at RALVM6         Tie Line: 444-4414
 *             Internet: johnq@ralvm6.vnet.ibm.com   (919) 254-4414
 *
 *  FUNCTION:  Contains procedures to be called for handling
 *             unexpected CPI-C return codes.
 *             Contains procedures to be called for handling the
 *             CPI-C error information cpicerr.
 *
 *  AVAILABILITY:
 *             These sample programs and source are also available on
 *             CompuServe through the APPC Information Exchange.  To get
 *             to the APPC forum just type 'GO APPC' from any CompuServe
 *             prompt.  The samples are available in the Sample Programs
 *             library section.  Just search on the keyword CPICPGMS to
 *             find all the samples in this series.
 *
 *             Updates for the sample programs and support for many more
 *             CPI-C platforms will also be made available on CompuServe.
 *
 *  RELATED FILES:
 *             CPICERR.H
 *
 *  CHANGE HISTORY:
 *  Date       Description
 *  08/05/92   Version 2.31 of APING, ATELL and AREXEC released to CompuServe.
 *             This version was also distributed at the APPC/APPN Platform
 *             Developer's Conference held in Raleigh, NC.
 *  08/13/92   Changed all printf and fprintf calls to use a write_*() call.
 *             Changed cpicerr_handle_rc() to a macro referencing a new call,
 *             cpicerr_handle_rc_extended().  The macro adds the current
 *             source file and line number to improve source code debugging.
 *  08/15/92   Changed cpicerr_exchange_version() to receive 128 bytes
 *             instead of 3 bytes.  This change was also made to the
 *             NS/DOS ship code.
 *  08/18/92   Removed extra newline in cpicerr_show_rc().
 *  09/02/92   Fixed bug in cpicerr_log_cpicerr() when the log_file_path
 *             was a zero length string.
 *  11/15/92   Changed reply structure to include 2 byte indicator.
 *  11/17/92   Added send/receipt of operating system string.
 *             Added cpicerr_exchange_version_plus() to return the string.
 *
 *****************************************************************************/

/*****************************************************************************
 *
 * OVERVIEW OF CPICERR CALLS
 *
 * cpicerr_new()                      Creates a CPICERR object.
 *                                    This must be done before any other
 *                                    cpicerr calls can be used.
 *
 * These calls set values in the cpicerr object structure and affect how
 * cpicerr_handle_rc reacts to errors.
 *
 * cpicerr_set_conv_id()              Used to extract conversation state info
 * cpicerr_set_exit_level()           Level of error on which to exit
 * cpicerr_set_log_file_name()        What filename to use for logging
 * cpicerr_set_log_file_path()        Where the filename is
 * cpicerr_set_log_level()            Level of error on which to log errors
 * cpicerr_set_major_version()        8 bit int - see cpicerr_exchange_version
 * cpicerr_set_minor_version()        8 bit int - see cpicerr_exchange_version
 * cpicerr_set_program_name()         String - Output as part of log info
 * cpicerr_set_program_info()         String - Output as part of log info
 * cpicerr_set_show_level()           Level of error on which to show errors
 *
 * cpicerr_handle_rc()                Should be called by the program for all
 *                                    UNEXPECTED return codes.
 *                                    Functions performed are:
 *                                       Classification of the return code
 *                                       Showing partial info to end user
 *                                       Logging complete info to disk
 *                                    This is a macro that actually expands
 *                                    to cpicerr_handle_rc_extended().
 *
 * cpicerr_exchange_version()         Exchanges version numbers with the
 *                                    partner.  Very useful when supporting
 *                                    multiple versions of a program.
 *
 * cpicerr_destroy()                  Destroys the CPICERR  object.
 *
 *
 * cpicerr_classify_rc()              These are internal calls used by
 * cpicerr_show_rc()                  other cpicerr_handle_rc.
 * cpicerr_log_rc()
 * cpicerr_log_cpicerr()
 * cpicerr_get_message()
 * cpicerr_set_rc_info()
 * cpicerr_show_product_info()
 *
 *****************************************************************************/
#if defined(WIN32) || defined(WINDOWS)                                /*WIN32*/
#include <windows.h>                                                  /*WIN32*/
#define GET_OS2_SENSE_DATA                                            /*WIN32*/
#endif                                                                /*WIN32*/

#include "wincpic.h"

#ifdef GET_OS2_SENSE_DATA
#include <winappc.h>
#endif

/* Set up constant declarations */
#include "cpicdefs.h"

/* Collection of routines with special ported version for each platform */
#include "cpicport.h"

#include <stdio.h>                          /* C library includes            */
#include <stdlib.h>
#include <string.h>

#include <time.h>

#include "cpicerrs.h"                       /* CPI-C error handling vars.    */

/*
 * Each of the following is a list of messages, which are actually defined
 * in this file below.  The messages are grouped together.  For example,
 * all of the return code messages are in the cpicerr_return_codes list.
 */
extern CPICERR_MESSAGE cpicerr_verbs_short[];
extern CPICERR_MESSAGE cpicerr_verbs_long[];
extern CPICERR_MESSAGE cpicerr_return_codes[];
extern CPICERR_MESSAGE cpicerr_rc_classes[];
extern CPICERR_MESSAGE cpicerr_states_conv[];
extern CPICERR_MESSAGE cpicerr_conv_types[];
extern CPICERR_MESSAGE cpicerr_sync_levels[];

/*****************************************************************************
 * Function prototypes for internal routines.  In general, these should
 * not be called directly by an application program.
 *****************************************************************************/
void   cpicerr_classify_rc(      CM_RETURN_CODE       conv_rc,
                                 CPIC_RC_HANDLING *   classification);
void   cpicerr_show_rc(          CPICERR *            cpicerr);
void   cpicerr_log_rc(           CPICERR *            cpicerr,
                                 FILE *               log_file);
int    cpicerr_log_cpicerr(      CPICERR *            cpicerr,
                                 char *               file_name,
                                 int                  file_line);
char * cpicerr_get_message(      CPICERR_MESSAGE_TYPE message_type,
                                 CM_INT32             index);
void   cpicerr_set_rc_info(      CPICERR *            cpicerr,
                                 CPIC_VERB_INDEX      verb_index,
                                 CM_RETURN_CODE       conv_rc);
void   cpicerr_show_product_info(CPICERR *            cpicerr);

/*****************************************************************************
 * The following function prototypes and macros are used only by the
 * OS/2 specific code used to obtain the sense data after an
 * allocation failure.  They are not necessary, if GET_OS2_SENSE_DATA
 * has not been externally defined (with the -D compile flag).
 *****************************************************************************/
#ifdef GET_OS2_SENSE_DATA
int    cpicerr_os2_appc_allocate(CPICERR *            cpicerr);

int
parse_destination(char * in_string,
                  char * plu_alias,
                  char * fqplu_name);




/* Macro BLANK_STRING sets string to all blanks */
#define BLANK_STRING(str)  memset(str,(int)' ',sizeof(str))

#undef CLEAR_VCB
/* Macro CLEAR_VCB sets the APPC verb control block to zeros */
#define CLEAR_VCB(vcb)     memset((char *)&vcb,(int)'\0',sizeof(vcb))

/* convert a string to uppercase, up to length specified */
#define TOUPPER_STRING(str,length) \
                           {int i; for (i=0;i < length;i ++) \
                           {str[i] = (char)toupper(str[i]);}}

/* convert an ASCII blank padded string to an ASCIIZ string without pads */
#define SNA2STRING(outstr, instr, max_length) \
                   {int i; for (i=0;i < max_length && instr[i] != ' ';i ++) \
                   {outstr[i] = instr[i];} outstr[i] = '\0';}

#endif


/*
 * The error REPLY routines below are experimental and may change
 * at any time!
 */

void
cpicerr_show_reply(CPICERR_REPLY * reply)
{
    unsigned short length;
    unsigned short offset;
    unsigned short indicator;
    int            rc = 0;

    if (reply->length >= CPICERR_REPLY_MIN_LENGTH) {
        write_error(
            "\nAn application error was detected by the partner:\n");
        indicator =
          convert_short_from_network(
              *((unsigned short*)&reply->buffer[CPICERR_REPLY_INDICATOR]));
        if (indicator == CPICERR_REPLY_INDICATOR_VALUE) {
            write_error("Response:              %d\n",
                        (int)reply->buffer[CPICERR_REPLY_RESPONSE]);
            write_error("Message Category:      %u\n",
              convert_short_from_network(
                  *((unsigned short*)&reply->buffer[CPICERR_REPLY_CATEGORY])));
            write_error("Primary Code:          %ld\n",
              convert_long_from_network(
                  *((unsigned long *)&reply->buffer[CPICERR_REPLY_PRIMARY])));
            write_error("Secondary Code:        %ld\n",
              convert_long_from_network(
                 *((unsigned long *)&reply->buffer[CPICERR_REPLY_SECONDARY])));


            if (reply->length >=
                (unsigned int)(CPICERR_REPLY_MIN_LENGTH + 2)) {
                length = convert_short_from_network(
                *((unsigned short *)
                               &reply->buffer[CPICERR_REPLY_PRIMARY_LENGTH]));

                if (reply->length >=
                    (unsigned int)(CPICERR_REPLY_PRIMARY_TEXT+length)) {
                    reply->buffer[length + CPICERR_REPLY_PRIMARY_TEXT - 1] =
                                                                          '\0';
                    write_error("%s\n",
                                &reply->buffer[CPICERR_REPLY_PRIMARY_TEXT]);
                    offset = CPICERR_REPLY_PRIMARY_TEXT + length;
                    if (reply->length >= 2+offset) {
                        length = convert_short_from_network(
                                  *((unsigned short *)&reply->buffer[offset]));
                        if (reply->length >= (offset+ 2 +length)) {
                            reply->buffer[length + offset + 2] = '\0';
                            write_error("%s\n", &reply->buffer[offset+2]);
                        }
                        else {
                            rc = 1;
                        }
                    }
                    else {
                        rc = 1;
                    }
                }
                else {
                    rc = 1;
                }
            }
            else {
                write_error("No text strings were sent.\n");
            }
        }
        else {
            write_error("Record received was not a reply structure.\n");
        }

    }
    else {
        rc = 1;
    }
    if (rc) {
        write_error("Reply length error in cpicerr_show_reply().\n");
    }
}


CPICERR_REPLY *
cpicerr_create_reply(unsigned int primary_message_buffer_size,
                     unsigned int secondary_message_buffer_size)
{
    CPICERR_REPLY * reply;

    reply = calloc(1, sizeof(CPICERR_REPLY));
    if (reply == NULL) {
        return NULL;
    }

    reply->buffer_length = CPICERR_REPLY_MIN_LENGTH+
                           primary_message_buffer_size+1 +
                           secondary_message_buffer_size+1 +
                           4;          /* two length fields */
    reply->buffer = calloc(reply->buffer_length, 1);
    if (reply == NULL) {
        return NULL;
    }

    return reply;
}

void
cpicerr_destroy_reply(CPICERR_REPLY * reply)
{
    /*
     * Make sure we don't free any NULL pointers!
     */
    if (reply != NULL) {
        if (reply->buffer != NULL) {
            free(reply->buffer);
        }
        free(reply);
    }
}



/*
 * Requires that cpicerr_set_conv_id() has been called.
 */
int    cpicerr_recv_appl_error(CPICERR *  cpicerr,
                               CPICERR_REPLY * reply)
{
    CM_RETURN_CODE cm_rc;
    CM_INT32  rts_received;
    CM_INT32  max_receive_len;
    CM_INT32  what_received;
    CM_INT32  received_len;
    CM_INT32  status_received;

    max_receive_len = reply->buffer_length;

    cmrcv (cpicerr->conversation_id,
           reply->buffer,
           &max_receive_len,
           &what_received,
           &received_len,
           &status_received,
           &rts_received,
           &cm_rc);

    reply->length = (unsigned int)received_len;

    return reply->buffer[0];
}


void
cpicerr_set_error_reply(CPICERR_REPLY * reply,
                        REPLY_RESPONSE  response,
                        unsigned int    message_category,
                        unsigned long   primary_code,
                        char *          primary_message_text,
                        unsigned long   secondary_code,
                        char *          secondary_message_text)
{
    unsigned int length = 0;
    unsigned short string_length;

    /*
     * Check and see that there is at least enough space in the reply_buffer
     * to sent the required fields.  If there is not enough space, return
     * 0 (zero) to the caller, indicating that no bytes were copied into
     * the reply_buffer.
     */
    if (reply->buffer_length < CPICERR_REPLY_MIN_LENGTH) {
        reply->length = 0;
        return/* 0 */;
    }

    *((unsigned short *)&reply->buffer[CPICERR_REPLY_INDICATOR]) =
                       convert_short_to_network(CPICERR_REPLY_INDICATOR_VALUE);
    reply->buffer[CPICERR_REPLY_RESPONSE] = (char)response;
    reply->buffer[CPICERR_REPLY_RESERVED] = 0; /* set reserved byte to zero  */
    *((unsigned short *)&reply->buffer[CPICERR_REPLY_CATEGORY]) =
                            convert_short_to_network(message_category);
    *((unsigned long *)&reply->buffer[CPICERR_REPLY_PRIMARY]) =
                            convert_long_to_network(primary_code);
    *((unsigned long *)&reply->buffer[CPICERR_REPLY_SECONDARY]) =
                            convert_long_to_network(secondary_code);
    length = CPICERR_REPLY_MIN_LENGTH;


    /* check length of buffer!!! */

    /*
     * Copy the length and text of the primary message.
     */
    string_length = strlen(primary_message_text) + 1;
    *((unsigned short *)&reply->buffer[CPICERR_REPLY_PRIMARY_LENGTH]) =
                  convert_short_to_network(string_length);
    memcpy(&reply->buffer[CPICERR_REPLY_PRIMARY_TEXT],
           primary_message_text,
           string_length);
    convert_to_ascii(&reply->buffer[CPICERR_REPLY_PRIMARY_TEXT],
                     string_length);

    length += 2 + string_length;

    /*
     * Copy the length and text of the secondary message.
     */
    string_length = strlen(secondary_message_text) + 1;
    *((unsigned short *)&reply->buffer[length]) =
              convert_short_to_network(string_length);
    memcpy(&reply->buffer[length+2],
           secondary_message_text,
           string_length);
    convert_to_ascii(&reply->buffer[length+2],
                     string_length);

    length += 2 + string_length;

    reply->length = length;

    return /* length */;
}




/*
 * Requires that cpicerr_set_conv_id() has been called.
 */

int
cpicerr_send_appl_error( CPICERR *       cpicerr,
                         NEXT_STATE      next_state,
                         CPICERR_REPLY * reply)
{
    CM_RETURN_CODE  cm_rc;
    CM_INT32        length;
    CM_INT32        rts_received;
    CM_SEND_TYPE    send_type;

    cmserr(cpicerr->conversation_id,
           &rts_received,
           &cm_rc);


    switch (next_state) {
        case NEXT_DEALLOCATE:
        case NEXT_DEALLOCATE_AND_EXIT:
            send_type = CM_SEND_AND_DEALLOCATE;
            {
            CM_INT32 deallocate_type = CM_DEALLOCATE_FLUSH;
            cmsdt(cpicerr->conversation_id,
                  &deallocate_type,
                  &cm_rc);
            }
            break;
        case NEXT_SEND:
            send_type = CM_SEND_AND_FLUSH;
            break;
        case NEXT_RECEIVE:
            send_type = CM_SEND_AND_PREP_TO_RECEIVE;
            {
            CM_PREPARE_TO_RECEIVE_TYPE ptr_type;
            ptr_type = CM_PREP_TO_RECEIVE_FLUSH;
            cmsptr (cpicerr->conversation_id,
                    &ptr_type,
                    &cm_rc);
            }
            break;
    }

    cmsst (cpicerr->conversation_id,
           &send_type,
           &cm_rc);
#if 1
    if (cm_rc != CM_OK) {
        printf("Ouch!!!!!!!!\n");
    }
    else {
    }
#endif

    length = reply->length;

    cmsend (cpicerr->conversation_id,
            reply->buffer,
            &length,
            &rts_received,
            &cm_rc);

    if (next_state == NEXT_DEALLOCATE_AND_EXIT) {
        exit(EXIT_FAILURE);
    }

#if 1
    printf("didn't exit\n");
#endif

	return	0;

}



/*****************************************************************************
 *
 *  cpicerr_new()
 *
 *  Usage:
 *  This function creates a CPICERR object which should be used on all
 *  subsequent calls to cpicerr.  If an error occurs and a valid object
 *  cannot be created, NULL will be returned.
 *
 *****************************************************************************/
CPICERR *
cpicerr_new(void)
{
    CPICERR *  cpicerr;

    /*-----------------------------------------------------------------------*
     * Allocate a block for the CPICERR structure.  calloc() will initialize
     * all bytes to 0.
     *-----------------------------------------------------------------------*/
    cpicerr = (CPICERR *) calloc(1, sizeof(*cpicerr));
    if (cpicerr == NULL) {
        return NULL;
    }


    /*-----------------------------------------------------------------------*
     * Save the time of program initialization.
     *-----------------------------------------------------------------------*/
    cpicerr->program_start_time = time(NULL);

    /*-----------------------------------------------------------------------*
     * Indicate that the conversation id field has not been set.
     *-----------------------------------------------------------------------*/
    cpicerr->conv_id_set = FALSE;


    /*-----------------------------------------------------------------------*
     * Initialize version levels.  0 indicates they have not been set.
     *-----------------------------------------------------------------------*/
    cpicerr->major_version = 0;
    cpicerr->minor_version = 0;

    /*-----------------------------------------------------------------------*
     * Initialize to always exit after an error occurs.
     *-----------------------------------------------------------------------*/
    cpicerr->exit_level = ALL_ERRORS;

    /*-----------------------------------------------------------------------*
     * Initialize to always show errors.
     *-----------------------------------------------------------------------*/
    cpicerr->show_level = ALL_ERRORS;

    /*-----------------------------------------------------------------------*
     * Initialize to always log errors.
     *-----------------------------------------------------------------------*/
    cpicerr->log_level = ALL_ERRORS;

    /*-----------------------------------------------------------------------*
     * Indicate that cpicerr should process all ERROR_RECEIVED return codes
     * (indicating our partner issued Send_Error())
     *-----------------------------------------------------------------------*/
    cpicerr->handle_error = TRUE;

    /*-----------------------------------------------------------------------*
     * Initialize strings to NULL in case 0 != NULL
     *-----------------------------------------------------------------------*/
    cpicerr->program_name  = NULL;
    cpicerr->program_info  = NULL;
    cpicerr->log_file_name = NULL;
    cpicerr->log_file_path = NULL;


    /*-----------------------------------------------------------------------*
     * Set the conversation characteristics to invalid values.  If this
     * isn't done, we could display seemingly valid values for these
     * parameters even though they were never set properly.
     *-----------------------------------------------------------------------*/
    cpicerr->conversation_type  = MAX_MESSAGE;
    cpicerr->conversation_state = MAX_MESSAGE;
    cpicerr->sync_level         = MAX_MESSAGE;

    return cpicerr;
}

/*****************************************************************************
 *
 *  cpicerr_set_conv_id
 *
 *  Usage:
 *  This call should be used just before the cmallc call (for clients),
 *  or just after the cmaccp call (for servers).
 *
 *  This routine will save the conversation id, as well as partner information
 *  and conversation status which can be extracted from CPI-C.
 *
 *  This information is often helpful for debugging and in many cases cannot
 *  be obtained after an error occurs, since you no longer have a valid
 *  conversation id after the conversation has been deallocated.
 *
 *  Returns 0 if everything was processed successfully.
 *  Returns 1 if an error occurred.  In general, the only reason for an
 *     error to occur is if one of the passed parameters is invalid.  Since
 *     this is just storing information in the footprint, we will not
 *     attempt to do sophisticated error processing in this procedure.
 *
 *****************************************************************************/
int
cpicerr_set_conv_id(CPICERR *       cpicerr,
                    unsigned char * conversation_id)
{
    CM_RETURN_CODE        conv_rc;          /* Return code from CPI-C call   */
    int                   rc;               /* return value for function     */


    if (cpicerr != (CPICERR *)NULL) {
        /*-------------------------------------------------------------------*
         * Save the conversation ID.
         * This can often be used in conjunction with error logs or trace
         * utilities.
         *-------------------------------------------------------------------*/
        memcpy(cpicerr->conversation_id,
               conversation_id,
               sizeof(cpicerr->conversation_id));

        /*
         * Extract the conversation type.
         */
        cmect(conversation_id,              /* Current conversation ID       */
              &cpicerr->conversation_type,  /* Returned conversation type    */
              &conv_rc);                    /* Put the return code here      */
        if (conv_rc != CM_OK) {
            /*
             * Set the conversation type to an invalid value and set
             * the return code to indicate an error.
             */
            cpicerr->conversation_type = MAX_MESSAGE;
            rc = 1;
        }

        /*
         * Extract the mode name used for this conversation.
         */
        cmemn(conversation_id,              /* Current conversation ID       */
              cpicerr->mode_name,           /* Returned mode name            */
              &(cpicerr->mode_name_length), /* Returned mode name length     */
              &conv_rc);                    /* Put the return code here      */
        if (conv_rc != CM_OK) {
            /*
             * Make sure the mode name is reset to uninitialized and
             * set the return code to indicate an error.
             */
            cpicerr->mode_name_length = 0;
            rc = 1;
        }
        /* make sure we place the null terminator at the end of the string   */
        cpicerr->mode_name[(int)cpicerr->mode_name_length] = '\0';

        /*-------------------------------------------------------------------*
         * Extract the partner's LU name.
         *-------------------------------------------------------------------*/
        cmepln(conversation_id,             /* Current conversation ID       */
               cpicerr->partner_LU_name,    /* Returned partner LU           */
               &(cpicerr->partner_LU_name_length),/* Partner LU name length  */
               &conv_rc);                   /* Put the return code here      */
        if (conv_rc != CM_OK) {
            /*
             * Make sure the partner LU name is reset to uninitialized and
             * set the return code to indicate an error.
             */
            cpicerr->partner_LU_name_length = 0;
            rc = 1;
        }
        /* make sure we place the null terminator at the end of the string   */
        cpicerr->partner_LU_name[(int)cpicerr->partner_LU_name_length] = '\0';

        /*-------------------------------------------------------------------*
         * Extract the conversation sync level.
         *-------------------------------------------------------------------*/
        cmesl(conversation_id,              /* Current conversation ID       */
              &cpicerr->sync_level,         /* Returned sync level           */
              &conv_rc);                    /* Put the return code here      */
        if (conv_rc != CM_OK) {
            /*
             * Set the sync level to an invalid value and set
             * the return code to indicate an error.
             */
            cpicerr->sync_level = MAX_MESSAGE;
            rc = 1;
        }

        rc = 0;
    } else {
        rc = 1;
    }
    return rc;
}

/*****************************************************************************
 *
 *  cpicerr_set_exit_level
 *
 *  Usage:
 *  Specify the CPI-C error classification as the exit level.
 *  When cpicerr_handle_rc() is called, the return code will be classified.
 *  If the classification is above the exit level, the program will be
 *  terminated (after conversation cleanup).
 *
 *  A value of ALL_ERRORS can be used to force an exit on any call to
 *  cpicerr_handle_rc().  This is the DEFAULT value.
 *
 *  A value of NO_ERRORS can be used to indicate that cpicerr should never
 *  cause an exit.  Your application should handle all exit termination.
 *  This is especially useful when using more than one conversation.
 *
 *  Also see:
 *      cpicerr_set_log_level
 *      cpicerr_set_show_level
 *****************************************************************************/
int
cpicerr_set_exit_level(CPICERR *        cpicerr,
                       CPIC_RC_HANDLING exit_level)
{
    cpicerr->exit_level = exit_level;
    return 0;
}

/*****************************************************************************
 *
 *  cpicerr_set_log_file_name
 *
 *  Usage:
 *  Sets the name of the log file to be used in cpicerr_handle_rc() to
 *  log complete error information.  No attempt is made to verify that
 *  the log_file_name specified is a valid filename or whether the file
 *  can be opened.  If the log_file_name cannot be opened when logging
 *  needs to be done, all log output will be sent to stderr instead.
 *
 *  For environments that support directory structures, you should specify
 *  the filename on cpicerr_set_log_file_name and the directory on
 *  cpicerr_set_log_file_path.  This allows your program to be isolated
 *  from changes in environments that only support a single level
 *  of directory (for example, VM).
 *
 *  Also see:
 *      cpicerr_set_log_file_path
 *      cpicerr_log_cpicerr (internal)
 *****************************************************************************/
int
cpicerr_set_log_file_name(CPICERR * cpicerr,
                          char *    log_file_name)
{
    /*-----------------------------------------------------------------------*
     * Initialize the name of the log file.
     *-----------------------------------------------------------------------*/
    cpicerr->log_file_name = (char *) malloc(strlen(log_file_name)+1);
    if (cpicerr->log_file_name != NULL) {
        strcpy(cpicerr->log_file_name, log_file_name);
        return 0;
    } else {
        return 1;
    }

}

/*****************************************************************************
 *
 *  cpicerr_set_log_file_path
 *
 *  Usage:
 *  Specifies the path qualifier for the log file name specified in the
 *  cpicerr_set_log_file_name call.  If cpicerr_set_log_file_path is used
 *  without setting the log file name, no error logging will occur.
 *
 *  If you specify a string whose first character is a $, the rest of the
 *  string will be looked for as an environment variable.  For example,
 *  in OS/2, you put the following in your CONFIG.SYS:
 *  SET LOGPATH=d:\logfiles
 *
 *  then specify $LOGPATH as a parameter on cpicerr_set_log_file_path.
 *
 *****************************************************************************/
int
cpicerr_set_log_file_path(CPICERR * cpicerr,
                          char *    log_file_path)
{
    char * path;
    int    rc;

    /*-----------------------------------------------------------------------*
     * Initialize the name of the log file.
     * If the first character is a dollar sign ('$'), then try to extract
     * the log file path from the environment.  If not, use the path
     * as specified.
     *-----------------------------------------------------------------------*/
    if (log_file_path[0] == '$') {
        path = getenv(&log_file_path[1]);
    } else {
        path = log_file_path;
    }

    /*-----------------------------------------------------------------------*
     * Check that we have a valid log file path string, allocate memory for
     * the string and copy it into the cpicerr structure.
     *-----------------------------------------------------------------------*/
    if (path != NULL) {
        cpicerr->log_file_path = (char *) malloc(strlen(path)+1);
        if (cpicerr->log_file_path != NULL) {
            strcpy(cpicerr->log_file_path, path);
            rc = 0;
        } else {
            rc = 1;
        }
    }
    else {
        rc = 1;
    }
    return rc;

}

/*****************************************************************************
 *
 *  cpicerr_set_log_level
 *
 *  Usage:
 *  Specify the CPI-C error classification as the log level.
 *  When cpicerr_handle_rc() is called, the return code will be classified.
 *  If the classification is above the log level, the return code and
 *  conversation information will be logged to the log file specified
 *  with the cpicerr_set_log_file_name and cpicerr_set_log_file_path.
 *
 *  A value of ALL_ERRORS can be used to force logging on any call to
 *  cpicerr_handle_rc().  This is the DEFAULT value.  This is especially
 *  useful when used on servers.
 *
 *  A value of NO_ERRORS can be used to indicate that cpicerr should never
 *  cause an error log.  Your application should handle all error logging.
 *
 *  Also see:
 *      cpicerr_set_log_file_name
 *      cpicerr_set_log_file_path
 *      cpicerr_log_cpicerr (internal)
 *      cpicerr_set_exit_level
 *      cpicerr_set_show_level
 *****************************************************************************/
int
cpicerr_set_log_level(CPICERR *        cpicerr,
                      CPIC_RC_HANDLING log_level)
{
    cpicerr->log_level = log_level;
    return 0;
}

/*****************************************************************************
 *
 *  cpicerr_set_major_version
 *
 *  Usage:
 *  Sets the major version number for the application.
 *  The version number can be 0-255.
 *
 *  The version number is used on error logging and by the
 *  cpicerr_exchange_version() call.
 *
 *  Also see:
 *      cpicerr_set_minor_version
 *****************************************************************************/
int
cpicerr_set_major_version(CPICERR *     cpicerr,
                          unsigned char major_version)
{
    cpicerr->major_version = major_version;
    return 0;
}

/*****************************************************************************
 *
 *  cpicerr_set_minor_version
 *
 *  Usage:
 *  Sets the minor version number for the application.
 *  The version number can be 0-255.
 *
 *  The version number is used on error logging and by the
 *  cpicerr_exchange_version() call.
 *
 *  Also see:
 *      cpicerr_set_major_version
 *****************************************************************************/
int
cpicerr_set_minor_version(CPICERR *     cpicerr,
                          unsigned char minor_version)
{
    cpicerr->minor_version = minor_version;
    return 0;
}


/*****************************************************************************
 *
 *  cpicerr_set_program_info
 *
 *  Usage:
 *  Sets a program information string that is included in the log information.
 *****************************************************************************/
int
cpicerr_set_program_info( CPICERR * cpicerr,
                          char * program_info)
{
    int rc;

    /*-----------------------------------------------------------------------*
     * Save the application's program information string
     *-----------------------------------------------------------------------*/
    cpicerr->program_info = (char *) malloc(strlen(program_info)+1);
    if (cpicerr->program_info != NULL) {
        strcpy(cpicerr->program_info, program_info);
        rc = 0;
    } else {
        rc = 1;
    }
    return rc;
}


/*****************************************************************************
 *
 *  cpicerr_set_program_name
 *
 *  Usage:
 *  Sets a program name string that is included in the log information.
 *****************************************************************************/
int
cpicerr_set_program_name(CPICERR * cpicerr,
                         char * program_name)
{
    int rc;
    /*-----------------------------------------------------------------------*
     * Save the local program name.
     *-----------------------------------------------------------------------*/
    cpicerr->program_name = (char *) malloc(strlen(program_name)+1);
    if (cpicerr->program_name != NULL) {
        strcpy(cpicerr->program_name, program_name);
        rc = 0;
    } else {
        rc = 1;
    }
    return rc;
}


/*****************************************************************************
 *
 *  cpicerr_set_show_level
 *
 *  Usage:
 *  Specify the CPI-C error classification as the show level.
 *  When cpicerr_handle_rc() is called, the return code will be classified.
 *  If the classification is above the show level, the return code and
 *  some conversation information will be shown to the user.
 *
 *  A value of ALL_ERRORS can be used to force showing of all calls to
 *  cpicerr_handle_rc().  This is the DEFAULT value.
 *
 *  A value of NO_ERRORS can be used to indicate that cpicerr should never
 *  cause an error to be shown to the user.
 *
 *  Also see:
 *      cpicerr_set_exit_level
 *      cpicerr_set_log_level
 *****************************************************************************/
int
cpicerr_set_show_level(CPICERR *        cpicerr,
                       CPIC_RC_HANDLING show_level)
{
    cpicerr->show_level = show_level;
    return 0;
}


/******************************************************************************
 *
 *  cpicerr_handle_rc_extended
 *
 *  Note:
 *  applications should use the cpicerr_handle_rc() macro.
 *
 *  Usage:
 *  This function should be called to handle any unexpected CPI-C return
 *  codes.  The exact function of this routine depends upon the settings
 *  that have been made to the CPICERR object.
 *
 *  Functions include:
 *      Determining the current conversation state
 *      Classifying the return code (CPIC_RC_HANDLING enum)
 *      Showing return code info to the user
 *      Logging the return code and conversation info to disk
 *      Deallocate the conversation and exit
 *
 *  Also see:
 *      cpicerr_set_exit_level
 *      cpicerr_set_log_level
 *      cpicerr_set_show_level
 *
 *****************************************************************************/
CPIC_RC_HANDLING
cpicerr_handle_rc_extended(CPICERR *       cpicerr,
                           CPIC_VERB_INDEX verb_index,
                           CM_RETURN_CODE  conv_rc,
                           char *          file_name,
                           int             file_line)

{
   /* Displays the CPI-C return code and the verb name. */

    CM_RETURN_CODE   cm_rc;                 /* Return code from CPI-C call   */
    CPIC_RC_HANDLING classification;        /* Returned RC classification    */
    char *           string;                /* temp var for output strings   */
    CM_CONVERSATION_STATE conversation_state; /* Current conv. state         */

    /*-----------------------------------------------------------------------*
     * Extract the current conversation state.
     * This will not be useful if the conversation has failed or a deallocate
     * return code has been received.  The conversation state is most useful
     * when a state check has occurred.
     *-----------------------------------------------------------------------*/
#ifndef ECS_NOT_SUPPORTED
     cmecs(cpicerr->conversation_id,
           &conversation_state,
           &cm_rc);
     if (cm_rc == CM_OK) {
         cpicerr->conversation_state = conversation_state;
     }
     else {
         cpicerr->conversation_state = CMECS_NOT_SUPPORTED;
     }
#else
     cpicerr->conversation_state = CMECS_NOT_SUPPORTED;
#endif

    /*-----------------------------------------------------------------------*
     * Store the error information in the cpicerr structure
     *-----------------------------------------------------------------------*/
     cpicerr_set_rc_info(cpicerr, verb_index, conv_rc);

    /*-----------------------------------------------------------------------*
     * Get the classification for this return code.
     *-----------------------------------------------------------------------*/
    cpicerr_classify_rc(conv_rc, &classification);


    if (classification == ERROR_RECEIVED && cpicerr->handle_error == TRUE) {
        CPICERR_REPLY * reply;
        reply = cpicerr_create_reply(1000,1000);
        cpicerr_recv_appl_error(cpicerr, reply);
        cpicerr_show_reply(reply);
        if (classification >= cpicerr->exit_level) {
            CM_INT32 deallocate_type;
            /*
             * Exit the application, rather than returning to the caller.
             */
            deallocate_type = CM_DEALLOCATE_ABEND;

            cmsdt(cpicerr -> conversation_id,
                  &deallocate_type,
                  &cm_rc);

            cmdeal(cpicerr -> conversation_id,
                   &cm_rc);

            do_exit(EXIT_FAILURE);
        }
        return classification;
    }


    /*-----------------------------------------------------------------------*
     * Show the CPI-C verb and return code.
     *-----------------------------------------------------------------------*/
    if (classification >= cpicerr->show_level) {
        cpicerr_show_rc(cpicerr);
    }


    /*-----------------------------------------------------------------------*
     * Show the classification for this return code.
     *-----------------------------------------------------------------------*/
    if (classification >= cpicerr->show_level) {
        string = cpicerr_get_message(CPIC_RC_CLASSES, classification);
        write_error("       return code class: %s\n", string);
        /*-------------------------------------------------------------------*
         * Show product specific information associated with this error.
         *-------------------------------------------------------------------*/
        cpicerr_show_product_info(cpicerr);
    }


    /*-----------------------------------------------------------------------*
     * Log this error, along with the infomation in its cpicerr.
     *-----------------------------------------------------------------------*/
    if (classification >= cpicerr->log_level) {
        cpicerr_log_cpicerr(cpicerr, file_name, file_line);
    }


    if (classification >= cpicerr->exit_level) {
        CM_INT32 deallocate_type;
        /*-------------------------------------------------------------------*
         * Exit the application, rather than returning to the caller.
         *-------------------------------------------------------------------*/
        deallocate_type = CM_DEALLOCATE_ABEND;

        cmsdt(cpicerr -> conversation_id,
              &deallocate_type,
              &cm_rc);

        cmdeal(cpicerr -> conversation_id,
               &cm_rc);

        do_exit(EXIT_FAILURE);              /* Set a failure return code     */
    }
    return classification;
}

/******************************************************************************
 *
 *  cpicerr_exchange_version
 *
 *  Usage:
 *  Calls cpicerr_exchange_version_plus()
 *
 *****************************************************************************/
int
cpicerr_exchange_version(CPICERR *       cpicerr,
                         unsigned char * cm_conv_id,
                         CM_INT32        conv_state,
                         unsigned char * partner_major_version,
                         unsigned char * partner_minor_version)
{
    return cpicerr_exchange_version_plus(cpicerr,
                                         cm_conv_id,
                                         conv_state,
                                         partner_major_version,
                                         partner_minor_version,
                                         NULL,
                                         0);




}

/******************************************************************************
 *
 *  cpicerr_exchange_version_plus
 *
 *  Usage:
 *  Send our two version number bytes to the partner and receive our
 *  partner's two version numbers.  The input parameter conv_state
 *  determines whether our version numbers are sent first, or whether
 *  we receive the partner's numbers first.
 *
 *  Also will return the remote operating system string, if sent.
 *
 *****************************************************************************/
int
cpicerr_exchange_version_plus(CPICERR *       cpicerr,
                              unsigned char * cm_conv_id,
                              CM_INT32        conv_state,
                              unsigned char * partner_major_version,
                              unsigned char * partner_minor_version,
                              unsigned char * opsys_string,
                              unsigned int    opsys_string_length)
{
    CM_SEND_TYPE send_type;                 /* CPI-C send type               */
    CM_PREPARE_TO_RECEIVE_TYPE prep_to_receive; /* CPI-C prepare to receive  */
    CM_INT32    cm_rc;                      /* CPI-C return code             */
    CM_INT32    length;                     /* generic length variable       */
    CM_INT32    rts_received;               /* request to send received      */
    CM_INT32    max_receive_len;            /* Max receive length on CMRCV   */
    CM_INT32    what_received;              /* What received parm from CMRCV */
    CM_INT32    received_len;               /* Amount of data rcvd on CMRCV  */
    CM_INT32    status_received;            /* Status from CMRCV             */
    unsigned char buffer[EXCHANGE_BUFFER_SIZE]; /* data buffer               */

    *partner_major_version = 0;
    *partner_minor_version = 0;

    prep_to_receive = CM_PREP_TO_RECEIVE_FLUSH;
    cmsptr(cm_conv_id,                      /* Set prepare to receive type   */
           &prep_to_receive,
           &cm_rc);
    /* The only expected return code is CM_OK */
    if (cm_rc != CM_OK) return cpicerr_handle_rc(cpicerr, MSG_CMSPTR, cm_rc);

    send_type = CM_BUFFER_DATA;
    cmsst(cm_conv_id,                       /* Set send type                 */
          &send_type,
          &cm_rc);
    if (cm_rc != CM_OK) return cpicerr_handle_rc(cpicerr, MSG_CMSST, cm_rc);


    switch (conv_state) {
    case CM_SEND_STATE:
        buffer[0] = CPICERR_EXCHANGE_VERSION;
        buffer[1] = cpicerr->major_version;
        buffer[2] = cpicerr->minor_version;
        length = 3;
        cmsend(cm_conv_id,
               buffer,
               &length,
               &rts_received,
               &cm_rc);
        /* The only expected return code is CM_OK */
        if (cm_rc != CM_OK)
            return cpicerr_handle_rc(cpicerr, MSG_CMSEND, cm_rc);
        /* this falls through to the receive code!!! */
    case CM_RECEIVE_STATE:
        max_receive_len = sizeof(buffer);
        cmrcv (cm_conv_id,
               buffer,
               &max_receive_len,
               &what_received,
               &received_len,
               &status_received,
               &rts_received,
               &cm_rc);
        if (cm_rc == CM_OK) {
            if (what_received != CM_NO_DATA_RECEIVED) {
                if (received_len > 2 && buffer[0]==CPICERR_EXCHANGE_VERSION) {
                    *partner_major_version = buffer[1];
                    *partner_minor_version = buffer[2];
                }
                if (opsys_string != NULL && opsys_string_length > 1) {
                    if (received_len > 4 &&
                        buffer[3]==CPICERR_EXCHANGE_OPSYS_STRING) {
                        if (received_len < sizeof(buffer)) {
                            buffer[received_len] = '\0';
                        }
                        else {
                            buffer[sizeof(buffer)] = '\0';
                        }
                        {
                        unsigned int string_length;

                        string_length = strlen(&buffer[4]);
                        convert_from_ascii(&buffer[4], string_length);

                        memcpy(opsys_string,
                               &buffer[4],
                               min(string_length, opsys_string_length-1));

                        opsys_string[min(string_length, opsys_string_length-1)]
                                                                        = '\0';

                        }

                    }
                    else {
                        opsys_string[0] = '\0';
                    }
                }
                else {
                }

            }
            switch (status_received) {
            case CM_CONFIRM_RECEIVED:
                cmcfmd(cm_conv_id,
                       &cm_rc);
                if (cm_rc != CM_OK)
                    return cpicerr_handle_rc(cpicerr, MSG_CMCFMD, cm_rc);
                break;
            case CM_SEND_RECEIVED:
                /* This is good, we don't have to do anything. */
                break;
            default:
                ;
                /* should do a reply_error here */

            }
        } else {
            return cpicerr_handle_rc(cpicerr, MSG_CMRCV, cm_rc);
        }
        break;
    default:
        /* do a reply error here */
        return UNRECOVERABLE;
    }

    if ((conv_state == CM_RECEIVE_STATE) &&
         (status_received == CM_SEND_RECEIVED)) {

        char *       local_opsys_string;
        unsigned int local_opsys_string_length;

        buffer[0] = CPICERR_EXCHANGE_VERSION;
        buffer[1] = cpicerr->major_version;
        buffer[2] = cpicerr->minor_version;
        local_opsys_string = OPSYS_STRING;
        local_opsys_string_length = strlen(local_opsys_string);
        if ((local_opsys_string_length + 1+ 3 +1) < sizeof(buffer)) {
            buffer[3] = CPICERR_EXCHANGE_OPSYS_STRING;
            memcpy(&buffer[4],
                   local_opsys_string,
                   local_opsys_string_length);
            convert_to_ascii(&buffer[4], local_opsys_string_length);
            buffer[4+local_opsys_string_length] ='\0';
            length = 4 + local_opsys_string_length + 1;
        }
        else {


            length = 3;
        }

        cmsend(cm_conv_id,
               buffer,
               &length,
               &rts_received,
               &cm_rc);
        /* The only expected return code is CM_OK */

        if (cm_rc != CM_OK)
            return cpicerr_handle_rc(cpicerr, MSG_CMSEND, cm_rc);

        cmptr(cm_conv_id,
              &cm_rc);
        if (cm_rc != CM_OK)
            return cpicerr_handle_rc(cpicerr, MSG_CMPTR, cm_rc);
    }
    return RC_OK;
}

/*****************************************************************************
 *
 *  cpicerr_destroy()
 *
 *  Destroys a CPICERR structure created with cpicerr_new().
 *  All memory assocated with the input CPICERR pointer is freed.
 *
 *****************************************************************************/
void
cpicerr_destroy(CPICERR * cpicerr)
{
    /*
     * Make sure we don't free() a NULL pointer!!!
     */
    if (cpicerr != NULL) {
        if (cpicerr->program_name != NULL) {
            free(cpicerr->program_name);
        }

        if (cpicerr->program_info != NULL) {
            free(cpicerr->program_info);
        }

        if (cpicerr->log_file_name != NULL) {
            free(cpicerr->log_file_name);
        }

        if (cpicerr->log_file_path != NULL) {
            free(cpicerr->log_file_path);
        }

        free(cpicerr);
    }
    return;
}



/*****************************************************************************
 *
 *  cpicerr_set_rc_info
 *
 *  Internal call which makes it easier to store return code information
 *  in the CPICERR structure.  Called from cpicerr_handle_rc().
 *
 *****************************************************************************/
void
cpicerr_set_rc_info(CPICERR *       cpicerr,
                    CPIC_VERB_INDEX verb_index,
                    CM_RETURN_CODE  conv_rc)
/* Store the verb return code information into the cpicerr structure */
{
    cpicerr->verb_index = verb_index;
    cpicerr->conv_rc =    conv_rc;
}

/*****************************************************************************
 *
 *  cpicerr_show_rc
 *
 *  Internal call which will display information about the unexpected
 *  return code encountered.  Called from cpicerr_handle_rc().
 *
 *****************************************************************************/
void
cpicerr_show_rc(CPICERR * cpicerr)
{
    write_error("\n  Unexpected CPI-C return code encountered...\n");

    /*-----------------------------------------------------------------------*
     * Find the CPI-C verb's name, and show it.
     *-----------------------------------------------------------------------*/
    write_error( "         CPI-C verb name: %s, %s\n",
            cpicerr_get_message(CPIC_VERBS_SHORT,
                                (CM_INT32)cpicerr->verb_index),
            cpicerr_get_message(CPIC_VERBS_LONG,
                                (CM_INT32)cpicerr->verb_index));

    /*-----------------------------------------------------------------------*
     * Find the CPI-C return code's name, and show it.
     *-----------------------------------------------------------------------*/
    write_error( "       CPI-C return code: %lu, %s\n",
            cpicerr->conv_rc,
            cpicerr_get_message(CPIC_RETURN_CODES, cpicerr->conv_rc));

    return;
}

/*****************************************************************************
 *
 *  cpicerr_log_rc
 *
 *  Internal call which will log information about the unexpected
 *  return code encountered.  Called from cpicerr_handle_rc().
 *
 *****************************************************************************/
void
cpicerr_log_rc(CPICERR * cpicerr,
               FILE *    log_file)
{
    write_log(log_file, "  Unexpected CPI-C return code encountered...\n");

    /*-----------------------------------------------------------------------*
     * Find the CPI-C verb's name, and show it.
     *-----------------------------------------------------------------------*/
    write_log(log_file,
              "         CPI-C verb name: %s, %s\n",
              cpicerr_get_message(CPIC_VERBS_SHORT,
                                  (CM_INT32)cpicerr->verb_index),
              cpicerr_get_message(CPIC_VERBS_LONG,
                                  (CM_INT32)cpicerr->verb_index));

    /*-----------------------------------------------------------------------*
     * Find the CPI-C return code's name, and show it.
     *-----------------------------------------------------------------------*/
    write_log(log_file,
              "       CPI-C return code: %lu, %s\n",
              cpicerr->conv_rc,
              cpicerr_get_message(CPIC_RETURN_CODES, cpicerr->conv_rc));

    return;
}


/*****************************************************************************
 *
 *  cpicerr_classify_rc
 *
 *  Internal call which takes a CPI-C return code and classifies it
 *  into one of the categories that we have defined.
 *  Called from cpicerr_handle_rc().
 *
 *****************************************************************************/
void
cpicerr_classify_rc (CM_RETURN_CODE conv_rc,
                     CPIC_RC_HANDLING * classification)
{
    switch (conv_rc) {

        case CM_ALLOCATE_FAILURE_NO_RETRY:
            /* configuration defect or protocol defect, local or partner */
        case CM_TP_NOT_AVAILABLE_NO_RETRY:
            /* partner program could not be sucessfully started */
        case CM_RESOURCE_FAILURE_NO_RETRY:
            /* communication failure or protocol defect, local or partner */

        case CM_DEALLOCATED_ABEND:
            /* unrecoverable error in the partner TP */
        case CM_DEALLOCATED_ABEND_SVC:
            /* unrecoverable error in the partner TP */
        case CM_DEALLOCATED_ABEND_TIMER:
            /* unrecoverable error in the partner TP */

        case CM_CONVERSATION_TYPE_MISMATCH:
        case CM_PIP_NOT_SPECIFIED_CORRECTLY:

            /* configuration defect or mismatch with the partner */

        case CM_OK:
            /* application design defect, local or partner program */
        case CM_DEALLOCATED_NORMAL:
            /* TP design defect, local or partner program */
        case CM_PARAMETER_ERROR:
            /* local program design or coding defect */
        case CM_PROGRAM_PARAMETER_CHECK:
            /* local program design or coding defect */
        case CM_PROGRAM_STATE_CHECK:
            /* local program design or coding defect */
            *classification = UNRECOVERABLE;
            break;

        case CM_ALLOCATE_FAILURE_RETRY:
            /* configuration defect or route temporarily down */
        case CM_TP_NOT_AVAILABLE_RETRY:
            /* congestion at the partner operating system */
        case CM_RESOURCE_FAILURE_RETRY:
            /* route temporarily down */
            *classification = RETRY_CONV;
            break;

        case CM_UNSUCCESSFUL:
            /* verb could not be completed now */
            *classification = RETRY_VERB;
            break;

        case CM_PROGRAM_ERROR_NO_TRUNC:
        case CM_SVC_ERROR_NO_TRUNC:
            /* partner failed while building a record to send */
        case CM_PROGRAM_ERROR_PURGING:
        case CM_SVC_ERROR_PURGING:
            /* partner failed while processing a received record */
        case CM_PROGRAM_ERROR_TRUNC:
        case CM_SVC_ERROR_TRUNC:
            /* partner failed after partially sending a record */
            *classification = ERROR_RECEIVED;
            break;

        case CM_PRODUCT_SPECIFIC_ERROR:
            /********************************/
            /* Examine each of these.       */
            /* In some cases, you may want  */
            /* to return CONTINUE.          */
            /********************************/
            *classification = UNRECOVERABLE;
            break;

        case CM_SECURITY_NOT_VALID:
            *classification = SECURITY_NOT_VALID;
            break;

        default:
            *classification = UNRECOVERABLE;
            break;
    }
    return;
}




/*****************************************************************************
 *
 *  cpicerr_log_cpicerr()
 *
 *  Internal call which logs complete conversation and error information
 *  to a log file.  Called by cpicerr_handle_rc().
 *
 *****************************************************************************/
int
cpicerr_log_cpicerr(CPICERR * cpicerr,
                    char *    file_name,
                    int       file_line)
{
    int      rc;                            /* return value                  */
    FILE *   log_file;                      /* log file handle               */
    unsigned count;                         /* used to extract text strings  */
    char     filepath[256];                 /* actual file path for logging  */
    char     last_char;

    if (cpicerr != (CPICERR *)NULL) {

        /*-------------------------------------------------------------------*
         * Save the time of the call to this procedure.
         *-------------------------------------------------------------------*/
        cpicerr->program_error_time = time(NULL);

        filepath[0] = '\0';
        if (cpicerr->log_file_path != NULL &&
            cpicerr->log_file_path[0] != '\0') {
            strcpy(filepath, cpicerr->log_file_path);
            last_char =
                    cpicerr->log_file_path[strlen(cpicerr->log_file_path)-1];
            if (!(last_char == '\\' || last_char == '/')) {
                strcat(filepath, "/");
            }
        }
        if (cpicerr->log_file_name != NULL) {
            strcat(filepath, cpicerr->log_file_name);
        }

        if ((strlen(filepath) == 0) ||
                               ((log_file = fopen(filepath, "a")) == NULL  )) {
            log_file = stderr;
        }

        write_log(log_file,
                  "------------------------------------------------------\n");

        if (cpicerr->program_name != NULL) {
            write_log(log_file, "  CPI-C error in program: \"%s\"",
                                                     cpicerr->program_name);
        }

        if (cpicerr->program_info != NULL) {
            write_log(log_file, ", %s\n", cpicerr->program_info);
        }

        if (cpicerr->major_version != 0 || cpicerr->minor_version != 0) {
            write_log(log_file, "         Program version: %u.%u\n",
                                       (unsigned int)cpicerr->major_version,
                                       (unsigned int)cpicerr->minor_version);
        }

        cpicerr_log_rc(cpicerr, log_file);

        if (cpicerr->partner_LU_name[0] != '\0') {
            cpicerr->partner_LU_name[(int)cpicerr->partner_LU_name_length]
                                                                       = '\0';
        }
        if (cpicerr->mode_name[0] != '\0') {
            cpicerr->mode_name[(int)cpicerr->mode_name_length] = '\0';
        }
        write_log(log_file, "         Partner LU name: %s\n",
                                                     cpicerr->partner_LU_name);
        write_log(log_file, "               Mode name: %s\n",
                                                     cpicerr->mode_name);

        write_log(log_file, "   CPI-C conversation ID: ");

        for (count = 0; count<sizeof(cpicerr->conversation_id); count++ ) {
            write_log(log_file, "%02X",
                               (unsigned int)cpicerr->conversation_id[count]);
        }
        write_log(log_file, "\n");

        write_log(log_file, "CPI-C conversation state: %lu, %s\n",
           cpicerr->conversation_state,
           cpicerr_get_message(CPIC_STATES_CONV, cpicerr->conversation_state));

        write_log(log_file, " CPI-C conversation type: %lu, %s\n",
           cpicerr->conversation_type,
           cpicerr_get_message( CPIC_CONV_TYPES, cpicerr->conversation_type));

        write_log(log_file, " Conversation sync level: %lu, %s\n",
                cpicerr->sync_level,
                cpicerr_get_message( CPIC_SYNC_LEVELS, cpicerr->sync_level));




        write_log(log_file, "      Program start time: %s",
                                        ctime(&(cpicerr->program_start_time)));
        write_log(log_file, "      Program error time: %s",
                                        ctime(&(cpicerr->program_error_time)));
        write_log(log_file, " Called from source file: %s\n", file_name);
        write_log(log_file, "                 at line: %d\n", file_line);

        fclose(log_file);

        rc = 0;
    } else {
        rc = 1;
    }

    return rc;
}




CPICERR_MESSAGE cpicerr_verbs_short[] = {
    MSG_CMACCP,         "CMACCP",
    MSG_CMALLC,         "CMALLC",
    MSG_CMCFM,          "CMCFM",
    MSG_CMCFMD,         "CMCFMD",
    MSG_CMDEAL,         "CMDEAL",
    MSG_CMECS,          "CMECS",
    MSG_CMECT,          "CMECT",
    MSG_CMEMN,          "CMEMN",
    MSG_CMEPLN,         "CMEPLN",
    MSG_CMESL,          "CMESL",
    MSG_CMFLUS,         "CMFLUS",
    MSG_CMINIT,         "CMINIT",
    MSG_CMPTR,          "CMPTR",
    MSG_CMRCV,          "CMRCV",
    MSG_CMRTS,          "CMRTS",
    MSG_CMSCT,          "CMSCT",
    MSG_CMSDT,          "CMSDT",
    MSG_CMSED,          "CMSED",
    MSG_CMSEND,         "CMSEND",
    MSG_CMSERR,         "CMSERR",
    MSG_CMSF,           "CMSF",
    MSG_CMSLD,          "CMSLD",
    MSG_CMSMN,          "CMSMN",
    MSG_CMSPLN,         "CMSPLN",
    MSG_CMSPTR,         "CMSPTR",
    MSG_CMSRC,          "CMSRC",
    MSG_CMSRT,          "CMSRT",
    MSG_CMSSL,          "CMSSL",
    MSG_CMSST,          "CMSST",
    MSG_CMSTPN,         "CMSTPN",
    MSG_CMTRTS,         "CMTRTS",
    MSG_XCSCSU,         "XCSCSU",
    MSG_XCSCSP,         "XCSCSP",
    MSG_XCSCST,         "XCSCST",
    MSG_XCECST,         "XCECST",
    MSG_XCECSU,         "XCECSU",
    MSG_XCMSSI,         "XCMSSI",
    MSG_XCMESI,         "XCMESI",
    MSG_XCMDSI,         "XCMDSI",
    MAX_MESSAGE,        "ERROR "
};

CPICERR_MESSAGE cpicerr_verbs_long[] = {
    MSG_CMACCP,         "Accept_Conversation",
    MSG_CMALLC,         "Allocate",
    MSG_CMCFM,          "Confirm",
    MSG_CMCFMD,         "Confirmed",
    MSG_CMDEAL,         "Deallocate",
    MSG_CMECS,          "Extract_Conversation_State",
    MSG_CMECT,          "Extract_Conversation_Type",
    MSG_CMEMN,          "Extract_Mode_Name",
    MSG_CMEPLN,         "Extract_Partner_LU_Name",
    MSG_CMESL,          "Extract_Sync_Level",
    MSG_CMFLUS,         "Flush",
    MSG_CMINIT,         "Initialize_Conversation",
    MSG_CMPTR,          "Prepare_To_Receive",
    MSG_CMRCV,          "Receive",
    MSG_CMRTS,          "Request_To_Send",
    MSG_CMSCT,          "Set_Conversation_Type",
    MSG_CMSDT,          "Set_Deallocate_Type",
    MSG_CMSED,          "Set_Error_Direction",
    MSG_CMSEND,         "Send_Data",
    MSG_CMSERR,         "Send_Error",
    MSG_CMSF,           "Set_Fill",
    MSG_CMSLD,          "Set_Log_Data",
    MSG_CMSMN,          "Set_Mode_Name",
    MSG_CMSPLN,         "Set_Partner_LU_Name",
    MSG_CMSPTR,         "Set_Prepare_To_Receive_Type",
    MSG_CMSRC,          "Set_Return_Control",
    MSG_CMSRT,          "Set_Receive_Type",
    MSG_CMSSL,          "Set_Sync_Level",
    MSG_CMSST,          "Set_Send_Type",
    MSG_CMSTPN,         "Set_TP_Name",
    MSG_CMTRTS,         "Test_Request_To_Send_Received",
    MSG_XCSCSU,         "Set Conversation Security Userid",
    MSG_XCSCSP,         "Set Conversation Security Password",
    MSG_XCSCST,         "Set Conversation Security Type",
    MSG_XCECST,         "Extract_Conversation_Security_Type",
    MSG_XCECSU,         "Extract_Conversation_Security_Userid",
    MSG_XCMSSI,         "Set_CPIC_Side_Information",
    MSG_XCMESI,         "Extract_CPIC_Side_Information",
    MSG_XCMDSI,         "Delete_CPIC_Side_Information",
    MAX_MESSAGE,        "Invalid verb name"
};

CPICERR_MESSAGE cpicerr_return_codes[] = {
    CM_OK,                          "CM_OK",
    CM_ALLOCATE_FAILURE_NO_RETRY,   "CM_ALLOCATE_FAILURE_NO_RETRY",
    CM_ALLOCATE_FAILURE_RETRY,      "CM_ALLOCATE_FAILURE_RETRY",
    CM_CONVERSATION_TYPE_MISMATCH,  "CM_CONVERSATION_TYPE_MISMATCH",
    CM_PIP_NOT_SPECIFIED_CORRECTLY, "CM_PIP_NOT_SPECIFIED_CORRECTLY",
    CM_SECURITY_NOT_VALID,          "CM_SECURITY_NOT_VALID",
    CM_TP_NOT_AVAILABLE_NO_RETRY,   "CM_TP_NOT_AVAILABLE_NO_RETRY",
    CM_TP_NOT_AVAILABLE_RETRY,      "CM_TP_NOT_AVAILABLE_RETRY",
    CM_DEALLOCATED_ABEND,           "CM_DEALLOCATED_ABEND",
    CM_DEALLOCATED_NORMAL,          "CM_DEALLOCATED_NORMAL",
    CM_PARAMETER_ERROR,             "CM_PARAMETER_ERROR",
    CM_PRODUCT_SPECIFIC_ERROR,      "CM_PRODUCT_SPECIFIC_ERROR",
    CM_PROGRAM_ERROR_NO_TRUNC,      "CM_PROGRAM_ERROR_NO_TRUNC",
    CM_PROGRAM_ERROR_PURGING,       "CM_PROGRAM_ERROR_PURGING",
    CM_PROGRAM_ERROR_TRUNC,         "CM_PROGRAM_ERROR_TRUNC",
    CM_PROGRAM_PARAMETER_CHECK,     "CM_PROGRAM_PARAMETER_CHECK",
    CM_PROGRAM_STATE_CHECK,         "CM_PROGRAM_STATE_CHECK",
    CM_RESOURCE_FAILURE_NO_RETRY,   "CM_RESOURCE_FAILURE_NO_RETRY",
    CM_RESOURCE_FAILURE_RETRY,      "CM_RESOURCE_FAILURE_RETRY",
    CM_UNSUCCESSFUL,                "CM_UNSUCCESSFUL",
    CM_DEALLOCATED_ABEND_SVC,       "CM_DEALLOCATED_ABEND_SVC",
    CM_DEALLOCATED_ABEND_TIMER,     "CM_DEALLOCATED_ABEND_TIMER",
    CM_SVC_ERROR_NO_TRUNC,          "CM_SVC_ERROR_NO_TRUNC",
    CM_SVC_ERROR_PURGING,           "CM_SVC_ERROR_PURGING",
    CM_SVC_ERROR_TRUNC,             "CM_SVC_ERROR_TRUNC",
    MAX_MESSAGE,                    "Invalid Return Code Value"
};

CPICERR_MESSAGE cpicerr_rc_classes[] = {
    BACKOUT_RECEIVED,   "BACKOUT_RECEIVED",
    CONTINUE,           "CONTINUE",
    ERROR_RECEIVED,     "ERROR_RECEIVED",
    SECURITY_NOT_VALID, "SECURITY_NOT_VALID",
    RETRY_CONV,         "RETRY_CONVERSATION",
    RETRY_CONV_BO,      "RETRY_CONVERSATION_BACKOUT",
    RETRY_VERB,         "RETRY_LAST_VERB",
    UNRECOVERABLE,      "UNRECOVERABLE",
    UNRECOVERABLE_BO,   "UNRECOVERABLE_BACKOUT",
    MAX_MESSAGE,        "Invalid Return Code Class"
};

CPICERR_MESSAGE cpicerr_states_conv[] = {
    CM_INITIALIZE_STATE,            "Initialize state",
    CM_SEND_STATE,                  "Send state",
    CM_RECEIVE_STATE,               "Receive state",
    CM_SEND_PENDING_STATE,          "Send pending state",
    CM_CONFIRM_STATE,               "Confirm state",
    CM_CONFIRM_SEND_STATE,          "Confirm send state",
    CM_CONFIRM_DEALLOCATE_STATE,    "Confirm deallocate state",
    CMECS_NOT_SUPPORTED,            "CMECS not supported",
    MAX_MESSAGE,                    "Invalid Conversation State value"
};

CPICERR_MESSAGE cpicerr_sync_levels[] = {
    CM_NONE,            "None",
    CM_CONFIRM,         "Confirm",
    MAX_MESSAGE,        "Invalid Sync Level value"
};

CPICERR_MESSAGE cpicerr_conv_types[] = {
    CM_BASIC_CONVERSATION , "Basic",
    CM_MAPPED_CONVERSATION, "Mapped",
    MAX_MESSAGE,            "Invalid conversation type value"
};

CPICERR_MESSAGE_LIST message_list[] = {
    CPIC_SYNC_LEVELS,   cpicerr_sync_levels,
    CPIC_CONV_TYPES,    cpicerr_conv_types,
    CPIC_STATES_CONV,   cpicerr_states_conv,
    CPIC_RC_CLASSES,    cpicerr_rc_classes,
    CPIC_RETURN_CODES,  cpicerr_return_codes,
    CPIC_VERBS_SHORT,   cpicerr_verbs_short,
    CPIC_VERBS_LONG,    cpicerr_verbs_long,
    MAX_MESSAGE,        NULL
};

/*****************************************************************************
 *
 *  cpicerr_get_message()
 *
 *  Loop through the message arrays looking for the message type and
 *  message index.  Return a pointer to the appropriate string.
 *
 *  This procedure will never return NULL, thus is safe to use in
 *  printf() type calls.
 *
 *****************************************************************************/
char *
cpicerr_get_message(CPICERR_MESSAGE_TYPE message_type, CM_INT32 index)
{
    unsigned int count;                     /* counter through the array     */

    CPICERR_MESSAGE * messages;

    for (count = 0; message_list[count].type < MAX_MESSAGE ; count++ ) {
        if (message_list[count].type == message_type) break;
    }

    if ( (messages = message_list[count].list) == NULL ) {
        return "Message list not found.";
    }

    for (count = 0; messages[count].index < MAX_MESSAGE; count++) {
       if (messages[count].index == index) break;
    }
    return messages[count].message;
}



/*****************************************************************************
 *
 *  cpicerr_show_product_info
 *
 *****************************************************************************/
void
cpicerr_show_product_info(CPICERR * cpicerr)
{
    if (cpicerr->conv_rc == CM_ALLOCATE_FAILURE_NO_RETRY ||
        cpicerr->conv_rc == CM_ALLOCATE_FAILURE_RETRY ) {
#if defined(GET_OS2_SENSE_DATA)
#if defined(FAPI)
        if (get_machine_mode()) {
#endif
             write_error(
             "\n  Retrying Allocate to extract OS/2 sense data:\n");
            cpicerr_os2_appc_allocate(cpicerr);
#if defined(FAPI)
        }
#endif
#endif

    }
}

#ifdef GET_OS2_SENSE_DATA

cpicerr_os2_appc_allocate(CPICERR * cpicerr)
/*
 * This procedure retries the allocate that failed in CPI-C.  We are not
 * retrying the allocate to establish the connection, but to get more
 * error information about why the first allocate failed.
 *
 * The OS/2 APPC api is used to extract the sense data, which provides
 * a more specify reason for an allocation failure.
 */
{
   TP_STARTED tp_started;                    /* Declare a verb control block */
   TP_STARTED *ptr_tp_started = (TP_STARTED *)&tp_started;
   int    length;                            /* length of lu_alias           */
   char   plu_alias[8+1];
   char   fqplu_name[17+1];

   ALLOCATE allocate;                        /* Declare a verb control block */
   ALLOCATE *ptr_allocate = (ALLOCATE *)&allocate;

   TP_ENDED tp_ended;                        /* Declare a verb control block */
   TP_ENDED *ptr_tp_ended = (TP_ENDED *)&tp_ended;


   CLEAR_VCB(tp_started);                    /* Zero the verb control block  */
   tp_started.opcode = AP_TP_STARTED;        /* APPC verb - TP_STARTED       */

   memset( tp_started.lu_alias, (int)'\0', sizeof(tp_started.lu_alias));

   BLANK_STRING(tp_started.tp_name);         /* Set 64-byte string to blanks */
   ascii_to_ebcdic_field(tp_started.tp_name,
                         sizeof(tp_started.tp_name));

   APPC ((ULONG) (TP_STARTED far *)ptr_tp_started); /* Issue the verb        */

   if (tp_started.primary_rc == AP_OK) {
       CLEAR_VCB(allocate);                  /* Zero the vcb                 */
       allocate.opcode = AP_B_ALLOCATE;      /* Verb - ALLOCATE              */
       allocate.opext = AP_MAPPED;           /* Basic Conversation type      */

                                             /* Set the TP_ID */
       memcpy (allocate.tp_id, tp_started.tp_id, sizeof(allocate.tp_id));
       allocate.sync_level = AP_CONFIRM;     /* Sync level-confirm           */
       allocate.rtn_ctl = AP_WHEN_SESSION_FREE;/* avoid deadlock             */
       allocate.security = AP_NONE;          /* Set security type            */

       if (!parse_destination(cpicerr->partner_LU_name,
                              plu_alias,
                              fqplu_name)) {
          if ((length = strlen(plu_alias)) != 0) {
             BLANK_STRING(allocate.plu_alias);
             memcpy ( allocate.plu_alias,
                      plu_alias,
                      min(length, sizeof(allocate.plu_alias)));
                                             /* Set PLU_ALIAS                */
          } else {
             memset (allocate.plu_alias,(int)'\0',sizeof(allocate.plu_alias));
             BLANK_STRING(allocate.fqplu_name);  /* Set FQ PLU NAME          */
             memcpy ( allocate.fqplu_name,
                      fqplu_name,
                      min(strlen(fqplu_name), sizeof(allocate.fqplu_name)));
             TOUPPER_STRING(allocate.fqplu_name, 17);
             ascii_to_ebcdic_field(allocate.fqplu_name,
                                   sizeof(allocate.fqplu_name));
          }


       } else {
          BLANK_STRING(allocate.plu_alias);
          memcpy ( allocate.plu_alias,
                   "UNKNOWN",
                   7);
       }


       BLANK_STRING(allocate.tp_name);       /* Set 64-byte string to blanks */
       ascii_to_ebcdic_field(allocate.tp_name,
                             sizeof(allocate.tp_name));

       BLANK_STRING(allocate.mode_name);     /* Set 8-byte string to blanks  */
          memcpy ( allocate.mode_name,
                   cpicerr->mode_name,
                   min(strlen(cpicerr->mode_name),
                       sizeof(allocate.mode_name)));
          TOUPPER_STRING(allocate.mode_name, 8);
       ascii_to_ebcdic_field(allocate.mode_name,
                             sizeof(allocate.mode_name));

       APPC((ULONG) (ALLOCATE far *) ptr_allocate);  /* Issue the verb       */

       if (allocate.primary_rc != AP_OK) {
        write_error(
        "\t OS/2 Sense Data: %08lX\n", SWAP4(allocate.sense_data));

       }

   } else {                                  /* Save the returned tp_id      */
       return (tp_started.primary_rc);
   }
   CLEAR_VCB(tp_ended);                      /* Zero the verb control block  */
   tp_ended.opcode = AP_TP_ENDED;            /* Set the verb opcode          */
                                             /* Set the tp_id  */
   memcpy (tp_ended.tp_id, tp_started.tp_id, sizeof(tp_ended.tp_id));
   tp_ended.type = AP_SOFT;                  /* type: AP_HARD or AP_SOFT     */

   APPC((ULONG) (TP_ENDED far *) ptr_tp_ended); /* Issue the verb.           */
}



int
parse_destination(char * in_string,
                  char * plu_alias,
                  char * fqplu_name)
/*
 * This procedure is used by cpicerr_os2_appc_allocate verb
 */
{
   if (strchr(in_string, '.') != NULL) {
      if (in_string[0] == '.') {
          in_string++;
      }
      strcpy(fqplu_name, in_string);
      plu_alias[0] = '\0';
   } else {
      strcpy(plu_alias, in_string);
      fqplu_name[0] = '\0';
   }
   return 0;

}

#endif

