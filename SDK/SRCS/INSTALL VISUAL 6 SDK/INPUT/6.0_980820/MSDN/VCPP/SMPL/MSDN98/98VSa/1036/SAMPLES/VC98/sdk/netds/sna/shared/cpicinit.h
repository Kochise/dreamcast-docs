/*****************************************************************************
 *
 *  MODULE NAME: CPICINIT.H
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
 *             CPICINIT.C
 *
 *  CHANGE HISTORY:
 *  Date       Description
 *  08/05/92   Version 2.31 of APING, ATELL and AREXEC released to CompuServe.
 *             This version was also distributed at the APPC/APPN Platform
 *             Developer's Conference held in Raleigh, NC.
 *  08/23/92   Removed cpicinit_default_destination() and associated
 *             processing.   After review, we decided that this call was
 *             extraneous and that cpicinit_default_sym_dest_name() was
 *             a better mechanism for a default destination.
 *  11/13/92   Changed most return values from TRUE/FALSE to CPICINIT_OK and
 *             other return codes.
 *
 *****************************************************************************/

/*****************************************************************************
 *
 * OVERVIEW OF CPICINIT CALLS
 *
 * cpicinit_new()                     Creates a CPICINIT object.
 *                                    This must be done before any other
 *                                    cpicinit calls can be used.
 *
 * cpicinit_default_tp_name()         These calls set the initial values
 * cpicinit_default_mode_name()       for CPICINIT parameters.  These should
 * cpicinit_default_sym_dest_name()   all be issued right after the CPICINIT
 *                                    object is created.
 *
 * cpicinit_set_tp_name()             These calls also set the values for
 * cpicinit_set_mode_name()           CPICINIT parameters.  These calls should
 * cpicinit_set_destination()         be used to set values from user input
 *                                    or profile values.
 *
 *   Security calls - only available where supported by CPI-C
 * cpicinit_set_userid                Sets the userid for the conversation.
 * cpicinit_set_password              Sets the password for the conversation.
 * cpicinit_query_password_needed     If a userid was set, then a password
 *                                    is required.
 * cpicinit_get_password              Let cpicinit prompt the user for a
 *                                    password.
 * cpicinit_set_security_type         Set the security type for this conv.
 *
 * cpicinit_setup_conversation()      Handles all CMINIT and set calls.
 *                                    Should be used by the calling program
 *                                    instead of CMINIT.  See description
 *                                    of the procedure for more details.
 *
 * cpicinit_destroy()                 Destroys the CPICINIT object.
 *
 * cpicinit_pln_valid()               These are internal calls used by
 * cpicinit_mode_valid()              cpicinit_setup_conversation.
 *
 *****************************************************************************/

#ifndef INCL_CPICINIT
#define INCL_CPICINIT

/*
 * Collection of routines with special ported version for each platform
 * The only thing that is used from CPICDEFS.H is the correct setting
 * of the SHORT_IDENTIFIERS identifier.
 */
#include "cpicdefs.h"

#if defined(SHORT_IDENTIFIERS)
/*
 * Some compilers require that identifiers be unique in the 1st 8 chars.
 * Any new functions should be added to this list.
 */
#define cpicinit_default_mode_name        cidmode
#define cpicinit_default_sym_dest_name    cidsdn
#define cpicinit_default_tp_name          cidtp
#define cpicinit_destroy                  cid
#define cpicinit_get_password             cigp
#define cpicinit_mode_valid               cimv
#define cpicinit_new                      cinew
#define cpicinit_pln_valid                cipv
#define cpicinit_query_password_needed    ciqpn
#define cpicinit_set_destination          cisdest
#define cpicinit_set_mode_name            cismode
#define cpicinit_set_password             cisp
#define cpicinit_set_tp_name              cistp
#define cpicinit_set_userid               cisu
#define cpicinit_setup_conversation       cisc
#endif

/*
 * A string of 8 blanks is a special symbolic destination name.  We define
 * this constant here rather than typing out 8 blanks within the code.
 */
#define  BLANK_SYM_DEST_NAME     "        "


/*
 * Return code values for most of the CPICINIT calls.
 */

#define CPICINIT_OK     (0)
#define CPICINIT_ERROR  (1)



/*
 * This structure contains all of the information necessary to for all
 * cpicinit calls.  The standard CPI-C destination and partner information
 * is stored.  These values can be changed by the program through the
 * use of cpicinit_default... and cpicinit_set... calls.
 */

typedef struct cpicinit {
    char          def_sym_dest_name[MAX_SYM_DEST_NAME];
                                            /* Default symbolic dest name    */
    char          tp_name[MAX_TP_NAME];     /* Transaction Program name      */
    int           set_tp_name;              /* Was tp name set?              */
    char          mode_name[MAX_MODE_NAME]; /* Mode name                     */
    int           set_mode_name;            /* Was mode name set?            */
    char          destination[MAX_FQPLU_NAME];
                                            /* Destination - may be either   */
                                            /* a sym dest name or a partner  */
                                            /* lu name                       */
    int           set_destination;          /* Was destination set?          */
    char          userid[MAX_USERID];       /* Userid                        */
    int           set_userid;               /* Was userid set?               */
    char          password[MAX_PASSWORD];   /* Password                      */
    int           set_password;             /* Was password set?             */
    int           show_error;               /* Should we show errors?        */
    unsigned long security_type;            /* Security type                 */
} CPICINIT;


/*
 * Some of the fields in the CPICINIT object indicate whether another
 * field has been set or not.  These fields will have one of the following
 * values.  defines have been used to make the code more readable and to
 * protect against the need to change these values in the future.
 */
#define  SET      1
#define  NOT_SET  0


/* function prototypes for this module */

/* create a new CPICINIT object */
CPICINIT * cpicinit_new(void);

/* Initialize defaults for CPICINIT values */
int cpicinit_default_tp_name(       CPICINIT *      cpicinit,
                                    char *          tp_name);
int cpicinit_default_mode_name(     CPICINIT *      cpicinit,
                                    char *          mode_name);
int cpicinit_default_sym_dest_name( CPICINIT *      cpicinit,
                                    char *          def_sym_dest_name);

/* Set new values, based on user input or profile values */
int cpicinit_set_tp_name(           CPICINIT *      cpicinit,
                                    char *          tp_name);
int cpicinit_set_mode_name(         CPICINIT *      cpicinit,
                                    char *          mode_name);
int cpicinit_set_destination(       CPICINIT *      cpicinit,
                                    char *          destination);
int cpicinit_set_userid(            CPICINIT *      cpicinit,
                                    char *          userid);
int cpicinit_set_password(          CPICINIT *      cpicinit,
                                    char *          password);
int cpicinit_query_password_needed( CPICINIT *      cpicinit);
void cpicinit_get_password(         CPICINIT *      cpicinit);
void cpicinit_set_security_type(    CPICINIT *      cpicinit,
                                    unsigned long   security_type);

/* This call will prepare the conversation id for the Allocate call */
int cpicinit_setup_conversation(    CPICINIT *      cpicinit,
                                    unsigned char * cm_conv_id,
                                    CPICERR *       cpicerr);

/* destroys the CPICINIT object created with cpicinit_new() */
void cpicinit_destroy(              CPICINIT *      cpicinit);

/* Internal routines */
int cpicinit_pln_valid(             unsigned char * cm_conv_id);
int cpicinit_mode_valid(            unsigned char * cm_conv_id);

#endif
