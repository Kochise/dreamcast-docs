/*****************************************************************************
 *
 *  MODULE NAME : AREXEC.C
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
 *  FUNCTION:  Execute a command on a remote workstation and display the
 *             output from the command (both stdout and stderr) on the
 *             requesting workstation.
 *
 *  Usage:
 *      AREXEC destination command
 *
 *    Destination may be either a partner LU alias (up to eight
 *    characters) or a fully qualified LU name (3-17 characters separated
 *    by a period)
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
 *             See AREXEC.DOC for usage instructions.
 *
 *  CHANGE HISTORY:
 *  Date       Description
 *  06/15/92   NS/DOS accepts version 2.02 into system test.
 *  08/05/92   Version 2.31 released to CompuServe
 *             This version was also distributed at the APPC/APPN Platform
 *             Developer's Conference held in Raleigh, NC.
 *  08/13/92   Changed all printf and fprintf calls to use a write_*() call.
 *  08/17/92   Made security handling code conditionally compiled.
 *  08/23/92   Removed call to cpicinit_default_destination().
 *  08/24/92   Version 2.32 released to CompuServe.
 *  09/22/92   Version 2.33 released to CompuServe.
 *  11/17/92   Added support for printing remote operating system name.
 *             Version 2.34 released to CompuServe
 *  01/07/93   Version 2.35
 *             Fixed a number of problems when compiling with IBM C Set/2
 *                password input was displayed
 *                timer resolution was 1 second
 *
 *****************************************************************************/

/*****************************************************************************
 * OVERVIEW of AREXEC CPI-C Flows
 *
 *   Client (AREXEC)                     Server (AREXECD)
 *   --------------                      ---------------
 * Set up conversation
 *   Allocate       -------------------> Accept Conversation
 * Exchange Version Numbers
 *   Send Data      -------------------> Receive
 *   Receive        <------------------- Send Data
 * Send the Command
 *   Send Data      -------------------> Receive
 * Receive the Output
 * -->                                           <--
 * | Receive        <------------------- Send Data |     LOOP
 * ---                                           ---
 * Command is finished
 * Receive          <------------------- Deallocate(FLUSH)
 *****************************************************************************/

#if defined(WINDOWS)||defined(WIN32)
#include <windows.h>
#endif
#include "wincpic.h"

/* standard C include files */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Set up constant declarations */
#include "cpicdefs.h"

/* Collection of routines with special ported version for each platform */
#include "cpicport.h"

/* CPI-C error handling routines */
/* This file is supplied with AREXEC */
#include "cpicerrs.h"

/* Argument processing procedure */
/* This file is supplied with AREXEC */
#include "getopt.h"

/* CPI-C initialization routines */
/* This file is supplied with AREXEC */
#include "cpicinit.h"

#define  MAX_COMMAND_LENGTH   500

/* CPI-C error handling info */
CPICERR * cpicerr;

/* These are the defaults to be used if the user does not provide arguments  */
/* to override these values.                                                 */
#define  DEFAULT_TP_NAME   "AREXECD"
#define  DEFAULT_MODE_NAME "#INTER"
#define  DEFAULT_SYM_DEST  "AREXECD"

/* Define these here so we can make changes throughout the code. */
/*
 * The PROGRAM_INFO string should be kept in sync with the
 * MAJOR_VERSION and MINOR_VERSION constants.  Although the
 * cpicerr_exchange_version() call will support values up to 255,
 * values for MINOR_VERSION should be from 00-99 to maintain the
 * two character format in the version string.
 */
#define  PROGRAM_NAME      "AREXEC"
#define  PROGRAM_INFO      "version 2.35"
#define  MAJOR_VERSION     (2)
#define  MINOR_VERSION     (35)
#define  LOG_FILE_NAME     "arexec.err"
#define  LOG_FILE_PATH     "$LOGPATH"

/* local structure definition */
typedef struct command_info {
    char        buffer[MAX_COMMAND_LENGTH];
    CM_INT32    buffer_length;
} COMMAND_INFO;

/* local function prototypes */
void process_arguments(int argc,
                       char *argv[],
                       CPICINIT * cpicinit,
                       COMMAND_INFO * command_info);

/*
 * Message displayed with show_info() when APING is started.
 */
char * intro[] = {
    PROGRAM_NAME " " PROGRAM_INFO " - Execute a remote command.",
    "  by Peter J. Schwaller (pjs@ralvm6.vnet.ibm.com)",
    NULL
    };

/*
 * Message displayed with show_info() when AREXEC is started.
 */
char * usage[] = {
    "",
    "Usage:",
    "AREXEC [flags] destination command",
    "Flags:",
    "  destination",
    "\tmay be either a symbolic destination name or a partner LU name",
    "  command",
    "\tcommand string to be executed on the remote machine",
    "  -m mode_name",
    "\tMode name (default: " DEFAULT_MODE_NAME ")",
    "  -t tp_name",
#if defined(SUPPORTS_SETTING_SECURITY)
    "\tthe TP to use on the allocate (default: " DEFAULT_TP_NAME ")",
    "  -u userid",
    "  -p password",
    "\tSecurity parameters.  If a userid is specified without a password,",
    "\tyou will be prompted for the password.",
    "  -n",
    "\tDo not use any security (SECURITY=NONE).",
#endif
    NULL
    };


void _cdecl
main( int argc, char *argv[])
{
    /* Variables used for CPI-C calls */
    unsigned char cm_conv_id[8];            /* CPI-C conversation ID         */
    CM_INT32     cm_rc;                     /* CPI-C return code             */
    CM_INT32     rts_received;              /* request to send received      */
    CM_INT32     max_receive_len;           /* Max receive length on CMRCV   */
    CM_INT32     what_received;             /* What received parm from CMRCV */
    CM_INT32     received_len;              /* Amount of data rcvd on CMRCV  */
    CM_INT32     status_received;           /* Status from CMRCV             */

    /* Destination information */
    CPICINIT *   cpicinit;

    char         partner_major_version;
    char         partner_minor_version;
    char         opsys_string[64];

#if defined(WINDOWS) || defined(WIN32)
    unsigned short WinCPICVersion = 0x0001;
    WCPICDATA CPICData;
#endif

    COMMAND_INFO command_info;

    /*
     * Make sure all output is seen as soon as possible.
     */
    setbuf(stdout, NULL);

    show_info(intro);                       /* Show program information      */

#if (defined(WIN32) || defined(WINDOWS))                              /*WIN32*/
       /****************************************************************WIN32*/
       /* Initialisation for WinCPIC                                   *WIN32*/
       /****************************************************************WIN32*/
    if (WinCPICStartup(WinCPICVersion,&CPICData))                     /*WIN32*/
    {                                                                 /*WIN32*/
       return;                                                        /*WIN32*/
    }                                                                 /*WIN32*/
#endif                                                                /*WIN32*/

    /*
     * Create a new CPICINIT structure and initialize values.
     * The procedures are in CPICINIT.C
     */
    cpicinit = cpicinit_new();
    cpicinit_default_tp_name(cpicinit, DEFAULT_TP_NAME);
    cpicinit_default_mode_name(cpicinit, DEFAULT_MODE_NAME);
    cpicinit_default_sym_dest_name(cpicinit, DEFAULT_SYM_DEST);


    /*
     * Process all of the command line arguments.  All of the conversation
     * setup arguments are stored in the cpicinit object.  The command
     * to be sent is returned in the buffer variable within command_info.
     */
    process_arguments(argc, argv, cpicinit, &command_info);

    if (cpicinit_query_password_needed(cpicinit)) {
        /* get a password from the user */
        cpicinit_get_password(cpicinit);
    }

    /*
     * Initialize the CPICERR structure.  This is done before the CMINIT
     * call so that we can use CPICERR for help with errors on CMINIT.
     * The procedure is in CPICERR.C
     */
    cpicerr = cpicerr_new();
    cpicerr_set_program_name(cpicerr, PROGRAM_NAME);
    cpicerr_set_program_info(cpicerr, PROGRAM_INFO);
    cpicerr_set_major_version(cpicerr, MAJOR_VERSION);
    cpicerr_set_minor_version(cpicerr, MINOR_VERSION);
    cpicerr_set_log_file_name(cpicerr, LOG_FILE_NAME);
    cpicerr_set_log_file_path(cpicerr, LOG_FILE_PATH);

    cpicinit_setup_conversation(cpicinit, cm_conv_id, cpicerr);

    {
    CM_SYNC_LEVEL sync_level = CM_CONFIRM;
    cmssl(cm_conv_id,                        /* Set sync level               */
          &sync_level,
          &cm_rc);
    }

    cmallc(cm_conv_id,                       /* Allocate the conversation    */
           &cm_rc);
    if (cm_rc != CM_OK) cpicerr_handle_rc(cpicerr, MSG_CMALLC, cm_rc);

    cpicerr_exchange_version_plus(cpicerr,
                                  cm_conv_id,
                                  CM_SEND_STATE,
                                  &partner_major_version,
                                  &partner_minor_version,
                                  opsys_string,
                                  sizeof(opsys_string));
    /*
     * Display the operating system string returned in the exchange.
     * The string length will be 0 if the operating system string
     * wasn't available.
     */

    if (strlen(opsys_string) != 0) {
        write_output("\nConnected to a partner running on: %s\n",
                     opsys_string);
    }

    convert_to_ascii(command_info.buffer, command_info.buffer_length);
    cmsend(cm_conv_id,                     /* Send Data                      */
           (unsigned char *)command_info.buffer, /* data pointer             */
           &command_info.buffer_length,    /* length of data sent            */
           &rts_received,                  /* request to send indicator      */
           &cm_rc);
    if (cm_rc != CM_OK) cpicerr_handle_rc(cpicerr, MSG_CMSEND, cm_rc);

    max_receive_len = sizeof(command_info.buffer);
    do {
        cmrcv(cm_conv_id,                   /* Receive Data                  */
              (unsigned char *)command_info.buffer, /* Data Pointer          */
              &max_receive_len,             /* Size of Data Buffer           */
              &what_received,               /* returned - what received      */
              &received_len,                /* returned - length of data     */
              &status_received,             /* returned - status received    */
              &rts_received,                /* returned - request to send    */
              &cm_rc);

       if (what_received != CM_NO_DATA_RECEIVED &&
            (cm_rc == CM_OK || cm_rc == CM_DEALLOCATED_NORMAL)) {
                                            /* Write the received data       */
            convert_from_ascii(command_info.buffer, received_len);
            fwrite(command_info.buffer, 1, (unsigned int)received_len, stdout);
       }

    } while ( !cm_rc );

    if (cm_rc != CM_DEALLOCATED_NORMAL) {
        cpicerr_handle_rc(cpicerr, MSG_CMRCV, cm_rc);
    }

    /* destroy the object we created with cpicinit_new() */
    cpicinit_destroy(cpicinit);

    /* destroy the object we created with cpicerr_new() */
    cpicerr_destroy(cpicerr);

    exit(EXIT_SUCCESS);
}


void
process_arguments(int argc,
                  char *argv[],
                  CPICINIT * cpicinit,
                  COMMAND_INFO * command_info)
{
    int         set_destination = 0;
    int         c;                          /* flag specifed, used w/getopt  */

    command_info -> buffer_length = 0;
    command_info -> buffer[0] = '\0';

    while (optind != argc) {
        c = getopt(argc, argv, "?t:m:u:p:T:M:U:P:Nn");
        switch (c) {
        case EOF:
            if (set_destination == 0) {
                set_destination = 1;
                optarg = argv[optind];
                if (optarg[0] == '?') {
                   show_info(usage);
                   exit(EXIT_FAILURE);
                }
                optind++;
                cpicinit_set_destination(cpicinit, optarg);
            } else {
                command_info -> buffer[0] = '\0';
                for ( ; optind<argc ; optind++ ) {
                    command_info -> buffer_length += strlen(argv[optind])+1;
                    if (command_info->buffer_length < MAX_COMMAND_LENGTH) {
                        strcat(command_info->buffer, argv[optind]);
                        strcat(command_info->buffer, " ");
                    } else {
                        write_error(
                                "Command length exceeds max allowed (%d).\n",
                                MAX_COMMAND_LENGTH-1);
                        write_error(
                                "No command will be sent.\n");
                        exit(EXIT_FAILURE);
                    }
                }
            }
            break;
        case 'M':
        case 'm':
            cpicinit_set_mode_name(cpicinit, optarg);
            break;
        case 'T':
        case 't':
            cpicinit_set_tp_name(cpicinit,optarg);
            break;
#if defined(SUPPORTS_SETTING_SECURITY)
        case 'U':
        case 'u':
            cpicinit_set_userid(cpicinit, optarg);
            break;
        case 'P':
        case 'p':
            cpicinit_set_password(cpicinit, optarg);
            break;
        case 'N':
        case 'n':
            cpicinit_set_security_type(cpicinit, CM_SECURITY_NONE);
            break;
#endif
        case '?':
            show_info(usage);
            exit(EXIT_FAILURE);
            break;
        default:
            write_output("Invalid flag.  Use AREXEC -? for usage\n");
            exit(EXIT_FAILURE);
        }
    }
    if (!(set_destination && command_info->buffer_length)) {
        write_error(
                "You must specify at least a destination and a command.\n");
        show_info(usage);
        exit(EXIT_FAILURE);
    }
}
