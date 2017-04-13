/*****************************************************************************
 *
 *  MODULE NAME: CPICERRS.H
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
 *             Use CPICERR.C
 *
 *  CHANGE HISTORY:
 *  Date       Description
 *  08/05/92   Version 2.31 of APING, ATELL and AREXEC released to CompuServe.
 *             This version was also distributed at the APPC/APPN Platform
 *             Developer's Conference held in Raleigh, NC.
 *  08/13/92   Changed cpicerr_handle_rc() to a macro referencing
 *             cpicerr_handle_rc_extended().  The macro adds the current
 *             source file and line number to improve source code debugging.
 *  11/04/92   Changed version from char to unsigned char.
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
 * cpicerr_set_log_file_name()        What filename to use for logging
 * cpicerr_set_log_file_path()        Where the filename is
 * cpicerr_set_program_name()         String - Output as part of log info
 * cpicerr_set_program_info()         String - Output as part of log info
 * cpicerr_set_major_version()        8 bit int - see cpicerr_exchange_version
 * cpicerr_set_minor_version()        8 bit int - see cpicerr_exchange_version
 * cpicerr_set_conv_id()              Used to extract conversation state info
 * cpicerr_set_exit_level()           Level of error on which to exit
 * cpicerr_set_show_level()           Level of error on which to show errors
 * cpicerr_set_log_level()            Level of error on which to log errors
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
 * cpicerr_destroy()                  Destroys the CPICERR  object.
 *
 *
 * cpicerr_classify_rc()              These are internal calls used by
 * cpicerr_show_rc()                  other cpicerr_handle_rc.
 * cpicerr_log_cpicerr()
 * cpicerr_get_message()
 * cpicerr_set_rc_info()
 * cpicerr_show_product_info()
 *
 *****************************************************************************/

#ifndef INCL_CPICERR
#define INCL_CPICERR


/*
 * Include the C standard I/O library for the FILE structure definition.
 */
#include <stdio.h>

/*
 * Collection of routines with special ported version for each platform
 * The only thing that is used from CPICDEFS.H is the correct setting
 * of the SHORT_IDENTIFIERS identifier.
 */
#include "cpicdefs.h"

#if defined(SHORT_IDENTIFIERS)
/*
 * The C/370 compiler requires that identifier be unique in the 1st 8 chars.
 * If any new functions are added to this file, they should also be added to
 * this list, with a unique mapping.
 */
#    define  cpicerr_build_reply_image      cebri
#    define  cpicerr_conv_types             ceconv_type
#    define  cpicerr_classify_rc            cecr
#    define  cpicerr_create_reply           cecrep
#    define  cpicerr_destroy                cedestroy
#    define  cpicerr_destroy_reply          cedr
#    define  cpicerr_extract_reply_image    ceeri
#    define  cpicerr_exchange_version       ceev
#    define  cpicerr_exchange_version_plus  ceevp
#    define  cpicerr_get_message            cegm
#    define  cpicerr_handle_rc_extended     cehre
#    define  cpicerr_log_cpicerr            celf
#    define  cpicerr_set_major_version      cemajor
#    define  cpicerr_set_minor_version      ceminor
#    define  cpicerr_new                    cenew
#    define  cpicerr_recv_appl_error        cerae
#    define  cpicerr_return_codes           cerc
#    define  cpicerr_rc_classes             cercclass
#    define  cpicerr_send_appl_error        cesae
#    define  cpicerr_set_conv_id            cesci
#    define  cpicerr_set_error_reply        ceser
#    define  cpicerr_set_rc_info            cesetr
#    define  cpicerr_set_log_file_name      ceslfn
#    define  cpicerr_set_log_file_path      ceslfp
#    define  cpicerr_set_log_level          cesll
#    define  cpicerr_set_program_info       cespi
#    define  cpicerr_set_program_name       cespn
#    define  cpicerr_show_product_info      cespri
#    define  cpicerr_show_rc                cesr
#    define  cpicerr_show_reply             cesrep
#    define  cpicerr_set_show_level         cessl
#    define  cpicerr_states_conv            cestate
#    define  cpicerr_set_exit_level         cesxl
#    define  cpicerr_sync_levels            cesync
#    define  cpicerr_verbs_long             cvlong
#    define  cpicerr_verbs_short            cvshort
#endif

/* Needed for the time_t structure used within the CPICINIT structure */
#include <time.h>

/*
 * Specify the maximum sizes for a variety of CPI-C fields.
 * The +1 is added to allow room for the C null terminator for strings.
 */
#define  MAX_LU_ALIAS      (8+1)
#define  MAX_PLU_ALIAS     (8+1)
#define  MAX_TP_NAME       (64+1)
#define  MAX_SYM_DEST_NAME (8+1)
#define  MAX_FQPLU_NAME    (17+1)
#define  MAX_DESTINATION   (17+1)
#define  MAX_MODE_NAME     (8+1)
#define  MAX_USERID        (8+1)
#define  MAX_PASSWORD      (8+1)



#define  MAX_MESSAGE_TEXT_LENGTH    (2048)


/*****************************************************************************
 * These values are used to break the CPI-C return codes down into classes.
 * They are organized from errors that can be ignored, to fatal errors
 * which cannot be recovered from.
 *
 * The values ALL_ERRORS and NO_ERRORS are used as extremes for the
 * cpicerr_set_exit_level() and cpicerr_set_show_level() calls, and are
 * not actual classification values.
 *****************************************************************************/
typedef enum {
    RC_OK = 0,
    ALL_ERRORS,
    CONTINUE          ,
    RETRY_VERB        ,
    SECURITY_NOT_VALID,
    ERROR_RECEIVED    ,
    RETRY_CONV        ,
    RETRY_CONV_BO     ,
    BACKOUT_RECEIVED  ,
    UNRECOVERABLE     ,
    UNRECOVERABLE_BO  ,
    NO_ERRORS
} CPIC_RC_HANDLING;

/*
 * Since CPI-C does not provide actual values that correspond to each CPI-C
 * call, we have to invent our own so that we can put the call names into
 * our message lists.
 */
typedef enum {
    MSG_CMACCP,
    MSG_CMALLC,
    MSG_CMCFM ,
    MSG_CMCFMD,
    MSG_CMDEAL,
    MSG_CMECS ,
    MSG_CMECT ,
    MSG_CMEMN ,
    MSG_CMEPLN,
    MSG_CMESL ,
    MSG_CMFLUS,
    MSG_CMINIT,
    MSG_CMPTR ,
    MSG_CMRCV ,
    MSG_CMRTS ,
    MSG_CMSCT ,
    MSG_CMSDT ,
    MSG_CMSED ,
    MSG_CMSEND,
    MSG_CMSERR,
    MSG_CMSF  ,
    MSG_CMSLD ,
    MSG_CMSMN ,
    MSG_CMSPLN,
    MSG_CMSPTR,
    MSG_CMSRC ,
    MSG_CMSRT ,
    MSG_CMSSL ,
    MSG_CMSST ,
    MSG_CMSTPN,
    MSG_CMTRTS,
    MSG_XCSCSU,
    MSG_XCSCST,
    MSG_XCSCSP,
    MSG_XCECST,
    MSG_XCECSU,
    MSG_XCMSSI,
    MSG_XCMESI,
    MSG_XCMDSI
} CPIC_VERB_INDEX;


/*****************************************************************************
 *
 * CPICERR_REPLY
 *
 * This structure is a reusable reply format.  This can be used either
 * as part of a data reply, or as an error reply after a send_error()
 * call.  See CPICERR.C for complete details of how this structure
 * is formatted on a CPI-C conversation.
 *****************************************************************************/

typedef enum next_state {
    NEXT_SEND,
    NEXT_RECEIVE,
    NEXT_DEALLOCATE,
    NEXT_DEALLOCATE_AND_EXIT
} NEXT_STATE;

typedef enum reply_response {
    REPLY_POSITIVE_COMPLETE     = 1,
    REPLY_POSITIVE_INTERMEDIATE = 2,
    REPLY_NEGATIVE_TRANSIENT    = 3,
    REPLY_NEGATIVE_PERMANENT    = 4
} REPLY_RESPONSE;

typedef struct cpicerr_reply {
    unsigned short      length;
    unsigned short      buffer_length;
    char *              buffer;
} CPICERR_REPLY;

/*
 * The format of the reply buffer is:
 * Offset   Length   Field
 * ------   ------   -----
 *    0        2     Reply Indicator (0xFF01)
 *    2        1     response
 *    3        1     reserved (must be 0)
 *    4        2     message category
 *    6        4     primary code
 *   10        4     secondary code
 * The following two fields are optional:
 *   12        2     primary message length
 *   14        x     primary message text
 * The following two fields are optional and should follow the primary message:
 *  14+x       2     secondary message length
 *  16+x       y     secondary message text
 */


#define CPICERR_REPLY_INDICATOR_VALUE   (0xFF01)
#define CPICERR_REPLY_MIN_LENGTH        (14)

/* offsets into the reply buffer for each field */
#define CPICERR_REPLY_INDICATOR         (0)
#define CPICERR_REPLY_RESPONSE          (2)
#define CPICERR_REPLY_RESERVED          (3)
#define CPICERR_REPLY_CATEGORY          (4)
#define CPICERR_REPLY_PRIMARY           (6)
#define CPICERR_REPLY_SECONDARY        (10)
#define CPICERR_REPLY_PRIMARY_LENGTH   (14)
#define CPICERR_REPLY_PRIMARY_TEXT     (16)

/*****************************************************************************
 *
 * CPICERR
 *
 * This structure contains all of the information necessary to for all
 * cpicerr calls.  All of the fields which need to be changed by the
 * application program should be modified through the cpicerr_set...()
 * calls.  The application program should never have to access the
 * cpicerr structure directly.
 *
 * When an unexpected return code occurs, this structure is used to
 * determine what error processing should occur, including:
 *   display of minimal error information
 *   logging of complete error information
 *     where to log the data
 *
 * If a field is added to this structure, be sure to add the correct
 * initialization values for the field in the cpicerr_new() function.
 *****************************************************************************/

typedef struct error_handler_cpicerr {
    char *        program_name;             /* program's name                */
    char *        program_info;             /* program information           */
    CPIC_VERB_INDEX verb_index;             /* index of the failing verb     */
    CM_RETURN_CODE conv_rc;                 /* return code from CPI-C        */
    CM_CONVERSATION_STATE conversation_state;
    CM_CONVERSATION_TYPE  conversation_type;
    CM_SYNC_LEVEL         sync_level;
    char *        log_file_path;            /* path for the log file         */
    char *        log_file_name;            /* where to log errors           */
    unsigned char conversation_id[8];       /* CPI-C Conversation ID         */
    int           conv_id_set;              /* Was conv_id set?              */
    CM_INT32      mode_name_length;         /* mode_name length              */
    CM_INT32      partner_LU_name_length;   /* partner_LU_name length        */
    unsigned char mode_name[MAX_MODE_NAME]; /* mode_name                     */
    unsigned char partner_LU_name[MAX_FQPLU_NAME]; /* partner_LU_name        */
    CPIC_RC_HANDLING exit_level;            /* should we exit on an error?   */
    CPIC_RC_HANDLING show_level;            /* should we show errors?        */
    CPIC_RC_HANDLING log_level;             /* should we log errors?         */
    unsigned char major_version;            /* Major version number          */
    unsigned char minor_version;            /* Minor version number          */
    time_t        program_start_time;       /* time of cpicerr init          */
    time_t        program_error_time;       /* time of error report          */
    int           handle_error;             /* should cpicerr process all    */
                                            /* ERROR_RECEIVED ret codes?     */
} CPICERR;


/*****************************************************************************
 * The following are the structures and constants used for handling all of
 * message strings in CPICERR.
 *****************************************************************************/

/*
 * The cpicerr_message structure contains an index and the text message
 * associated with that index.  In most cases, the index will be an actual
 * CPI-C return value.  For example,
 * index = CM_SEND_STATE, message = "Send state"
 */
typedef struct cpicerr_message {
    CM_INT32   index;
    char *     message;
} CPICERR_MESSAGE;


/*
 * This enum gives each list a label and a value to make it easier to
 * process all of the lists.
 */
typedef enum cpicerr_message_type {
    CPIC_SYNC_LEVELS  = 1,
    CPIC_CONV_TYPES   = 2,
    CPIC_STATES_CONV  = 3,
    CPIC_RC_CLASSES   = 4,
    CPIC_RETURN_CODES = 5,
    CPIC_VERBS_SHORT  = 6,
    CPIC_VERBS_LONG   = 7
} CPICERR_MESSAGE_TYPE;

/*
 * The CPICERR_MESSAGE_LIST structure is what actually ties a
 * CPICERR_MESSAGE_TYPE value to the CPICERR_MESSAGE list that it relates
 * to.  A table is defined in CPICERR.C that allows the cpicerr_get_message
 * routine to correlate a message label to its corresponding message list.
 */
typedef struct cpicerr_message_list {
    CPICERR_MESSAGE_TYPE type;
    CPICERR_MESSAGE *    list;
} CPICERR_MESSAGE_LIST;

/*
 * The following value is used to mark the end of CPICERR_MESSAGE lists.
 */
#define  MAX_MESSAGE       32767


/*
 * Set the size of the buffer used by the cpicerr_exchange_version() call.
 */
#define  EXCHANGE_BUFFER_SIZE    128


/*
 * If these CPI-C calls are not supported, these values will be returned
 * instead of a valid CPI-C values.  In the message tables, the values
 * below will result in a message of "XXX not supported".  This allows
 * us to differentiate between a call not being available on a platform,
 * and an unrecognized value returned on a call.
 */
#define CMECS_NOT_SUPPORTED              (CM_CONVERSATION_STATE) 99



/*
 * Used by the cpicerr_exchange_version() routine.  Future flows may
 * be prefaced with new "command values" taken from this list.
 */
typedef enum cpicerr_command {
    CPICERR_EXCHANGE_VERSION = 1,
    CPICERR_EXCHANGE_OPSYS_STRING = 2
} CPICERR_COMMAND;


/*****************************************************************************
 * Function prototypes for routines that can be called via an application
 * program.  See CPICERR.C for a full description of each function and
 * how to use it.
 *****************************************************************************/
CPICERR *
       cpicerr_new(void);

void   cpicerr_show_reply(       CPICERR_REPLY * reply);
CPICERR_REPLY *
       cpicerr_create_reply(     unsigned int primary_message_buffer_size,
                                 unsigned int secondary_message_buffer_size);
void   cpicerr_destroy_reply(    CPICERR_REPLY * reply);
unsigned int
       cpicerr_build_reply_image(CPICERR_REPLY * reply,
                                 char *          reply_buffer,
                                 unsigned int    reply_buffer_length);
unsigned int
       cpicerr_extract_reply_image(CPICERR_REPLY * reply,
                                 char *          reply_buffer,
                                 unsigned int    reply_buffer_length);
void   cpicerr_set_error_reply(  CPICERR_REPLY * reply,
                                 REPLY_RESPONSE  response,
                                 unsigned int    message_category,
                                 unsigned long   primary_code,
                                 char *          primary_message_text,
                                 unsigned long   secondary_code,
                                 char *          secondary_message_text);
int    cpicerr_recv_appl_error(  CPICERR *  cpicerr,
                                 CPICERR_REPLY * reply);
int    cpicerr_send_appl_error(  CPICERR *  cpicerr,
                                 NEXT_STATE next_state,
                                 CPICERR_REPLY * reply);
int    cpicerr_set_program_name( CPICERR *            cpicerr,
                                 char *               program_name);
int    cpicerr_set_program_info( CPICERR *            cpicerr,
                                 char *               program_info);
int    cpicerr_set_major_version(CPICERR *            cpicerr,
                                 unsigned char        major_version);
int    cpicerr_set_minor_version(CPICERR *            cpicerr,
                                 unsigned char        minor_version);
int    cpicerr_set_conv_id(      CPICERR *            cpicerr,
                                 unsigned char *      cm_conv_id);
int    cpicerr_set_log_file_name(CPICERR *            cpicerr,
                                 char *               log_file_name);
int    cpicerr_set_log_file_path(CPICERR *            cpicerr,
                                 char *               log_file_path);
int    cpicerr_set_exit_level(   CPICERR *            cpicerr,
                                 CPIC_RC_HANDLING     exit_level);
int    cpicerr_set_show_level(   CPICERR *            cpicerr,
                                 CPIC_RC_HANDLING     show_level);
int    cpicerr_set_log_level(    CPICERR *            cpicerr,
                                 CPIC_RC_HANDLING     log_level);
CPIC_RC_HANDLING
cpicerr_handle_rc_extended(      CPICERR *            cpicerr,
                                 CPIC_VERB_INDEX      verb_index,
                                 CM_RETURN_CODE       conv_rc,
                                 char *               file_name,
                                 int                  file_line);
/*
 * Provide an alternative interface for handling unexpected CPI-C
 * return codes.  This macro saves the programming from having
 * to type the __FILE__ and __LINE__ macros for each call.
 */
#define cpicerr_handle_rc(x,y,z)                    \
        cpicerr_handle_rc_extended(x,y,z, __FILE__, __LINE__)

int    cpicerr_exchange_version( CPICERR *            cpicerr,
                                 unsigned char *      cm_conv_id,
                                 CM_INT32             conv_state,
                                 unsigned char *      partner_major_version,
                                 unsigned char *      partner_minor_version);
int    cpicerr_exchange_version_plus(
                                 CPICERR *            cpicerr,
                                 unsigned char *      cm_conv_id,
                                 CM_INT32             conv_state,
                                 unsigned char *      partner_major_version,
                                 unsigned char *      partner_minor_version,
                                 unsigned char *      opsys_string,
                                 unsigned int         opsys_string_length);
void   cpicerr_destroy(          CPICERR *            cpicerr);



#endif
