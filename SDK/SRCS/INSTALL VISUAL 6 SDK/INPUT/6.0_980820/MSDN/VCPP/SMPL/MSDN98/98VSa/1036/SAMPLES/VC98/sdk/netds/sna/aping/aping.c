/*****************************************************************************
 *
 *  MODULE NAME: APING.C
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
 *  FUNCTION:  Perform an echo test to a specified destination.
 *             APING can be used when you are first installing APPC on
 *             your computer to make sure you can connect to another
 *             computer in the network.  APING can also be used to
 *             get an estimate of the delay time or throughput to another
 *             computer in the network.
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
 *             See APING.DOC for detailed information.
 *
 *  PORTABILIITY NOTES:
 *             The APING client program is completely portable.  In fact,
 *             all of the source modules can be compiled without #define-ing
 *             any platform constant value.
 *
 *             To take advantage of a performance optimization on the
 *             OS/2 platform, the alloc_cpic_buffer() is used.  If the
 *             OS/2 platform is specified (#define of OS2, FAPI, or OS2_20)
 *             alloc_cpic_buffer() will return a shared memory buffer.
 *             If not, a buffer allocated with malloc() will be returned.
 *
 *             If you are porting to a platform that can take advantage
 *             of a specially allocated memory buffer, you should
 *             add this support to the alloc_cpic_buffer() routine in the
 *             CPICPORT.C file.
 *
 *             The get_time() routine is used to determine the current time,
 *             which is in turn used to calculate the elapsed time of the
 *             data transfer.  The get_time() routine is used to hide
 *             differences between operating system timer facilties that
 *             are available.  Since the C library routine to query the
 *             current time only returns the time in seconds, it is
 *             advantageous to return the current time in milliseconds
 *             if it is available.
 *
 *             If you are porting to a platform that support a timer
 *             with a resolution better than one second, you should
 *             modify the get_time() routine in the CPICPORT.C file.
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
 *  08/28/92   Changed message about invalid size parm to go to write_error().
 *  09/08/92   Added check for buffer==NULL.  Initialized block to zeros.
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
 * OVERVIEW of APING CPI-C Flows
 *
 *   Client (APING)                      Server (APINGD)
 *   --------------                      ---------------
 * Set up conversation
 *   Allocate       -------------------> Accept Conversation
 * Exchange Version Numbers
 *   Send Data      -------------------> Receive
 *   Receive        <------------------- Send Data
 * For number of iterations (i)
 *  For number of consecutive packets (c)
 *     Send Data    -------------------> Receive
 *  For number of consecutive packets (c)
 *     Receive      <------------------- Send Data
 * Shut down the conversation
 *   Deallocate (FLUSH)
 *****************************************************************************/

#if defined(WIN32) || defined(WINDOWS)                                 /*WIN32*/
#include <windows.h>                                                   /*WIN32*/
#endif                                                                 /*WIN32*/

#include "wincpic.h"

/* Set up constant declarations */
#include "cpicdefs.h"

/* Collection of routines with special ported version for each platform */
#include "cpicport.h"

/* standard C include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* CPI-C error handling routines */
/* This file is supplied with APING */
#include "cpicerrs.h"

/* CPI-C conversation startup routines */
/* This file is supplied with APING */
#include "cpicinit.h"

/* Argument processing procedure */
/* This file is supplied with APING */
#include "getopt.h"



/* CPI-C error handling info */
CPICERR * cpicerr;


/*
 * Max size of a data buffer.  This is the largest size buffer that can
 * be specified on a call to CPI-C.
 */
#define  MAX_SIZE (32763)

/* These are the defaults to be used if the user does not provide arguments  */
/* to override these values.                                                 */
#define  DEFAULT_TP_NAME   "APINGD"
#define  DEFAULT_MODE_NAME "#INTER"
#define  DEFAULT_SYM_DEST  "APINGD"

/* Define these here so we can make changes throughout the code. */
/*
 * The PROGRAM_INFO string should be kept in sync with the
 * MAJOR_VERSION and MINOR_VERSION constants.  Although the
 * cpicerr_exchange_version() call will support values up to 255,
 * values for MINOR_VERSION should be from 00-99 to maintain the
 * two character format in the version string.
 */
#define  PROGRAM_NAME      "APING"
#define  PROGRAM_INFO      "version 2.35"
#define  MAJOR_VERSION     (2)
#define  MINOR_VERSION     (35)
#define  LOG_FILE_NAME     "aping.err"
#define  LOG_FILE_PATH     "$LOGPATH"

/*
 * Define the first APING version to support one way data transfer.
 * (Version 2.02).  After we exchange version numbers, we can determine
 * whether or not our partner can handle one way data or not.
 */
#define  ONEWAY_MAJOR_VERSION    (2)
#define  ONEWAY_MINOR_VERSION    (2)



typedef struct flags {
    int    one_way_flag;                    /* Was one way data requested    */
                                            /* value of 2 means two way echo */
                                            /* value of 1 means one way      */
    unsigned long size;                     /* size of data sends            */
    unsigned long number_iterations;        /* times through the loop        */
    unsigned long number_concurrent;        /* sends by each side per loop   */
} FLAGS;

/* function prototypes for procedures in this file */
void     do_aping(int argc,
                  char *argv[]);
void     process_arguments(int argc,
                           char *argv[],
                           CPICINIT * cpicinit,
                           FLAGS * flags);



/*
 * Message displayed with show_info() when APING is started.
 */
char * intro[] = {
    PROGRAM_NAME " " PROGRAM_INFO " APPC echo test with timings.",
    "  by Peter J. Schwaller (pjs@ralvm6.vnet.ibm.com)",
    NULL
    };

/*
 * Message displayed with show_info() when usage information is requested or
 * after an invalid flag was specified.
 */
char * usage[] = {
    "",
    "APING [flags] destination",
    "  destination",
    "\tmay be either a symbolic destination name or a partner LU name",
    "  -m mode_name",
    "\tmode name (default: " DEFAULT_MODE_NAME ")",
    "  -t tp_name",
    "\tthe TP to start on the server (default: " DEFAULT_TP_NAME ")",
    "  -s N",
    "\tN is the size of the packet transmitted (default: 100 bytes)",
    "  -i N",
    "\tN is the number of iterations (default: 2)",
    "  -c N",
    "\tN is the number of consecutive packets sent by each side (default: 1)",
    "  -1",
    "\tOnly send data from client to server (No echo)",
#if defined(SUPPORTS_SETTING_SECURITY)
    "  -u userid",
    "  -p password",
    "\tSecurity parameters.  If a userid is specified without a password,",
    "\tyou will be prompted for the password.",
    "  -n",
    "\tDo not use any security (SECURITY=NONE).",
#endif
    "",
    "The minimum time, maximum time, and average time will be shown.",
    NULL
    };

void _cdecl
main(int argc, char *argv[])
{

    do_aping(argc, argv);

}


void
do_aping( int argc, char *argv[])
{
    /* Variables used for CPI-C calls */
    unsigned char cm_conv_id[8];            /* CPI-C conversation ID         */
    CM_INT32    cm_rc;                      /* CPI-C return code             */
    CM_INT32    length;                     /* generic length variable       */
    CM_INT32    rts_received;               /* request to send received      */
    CM_INT32    max_receive_len;            /* Max receive length on CMRCV   */
    CM_INT32    data_received;              /* Data received parm from CMRCV */
    CM_INT32    received_len;               /* Amount of data rcvd on CMRCV  */
    CM_INT32    status_received;            /* Status from CMRCV             */

    /* Data buffer for send and receive */
    unsigned char CM_PTR buffer;            /* CPIC data buffer              */

#ifdef WIN32                                                          /*WIN32*/
    unsigned short WinCPICVERSION = 0x0001;                           /*WIN32*/
    WCPICDATA CPICData;                                               /*WIN32*/
#endif                                                                /*WIN32*/

    /* Destination information */
    CPICINIT * cpicinit;

    unsigned long start_time = 0;           /* when a ping starts            */
    unsigned long end_time;                 /* when a ping ends              */
    unsigned long elapsed_time;             /* used for time calculations    */

    char          partner_major_version;
    char          partner_minor_version;
    char          opsys_string[64];


    unsigned long curr_iteration;           /* which iteration is active     */
    unsigned long curr_concurrent;          /* which send/recv is active     */
    unsigned long total_time = 0;           /* used to calculate averages    */

    unsigned long min_time = 0xFFFFFFFF;    /* used for min elapsed time     */
    unsigned long max_time = 0;             /* used for max elapsed time     */
                                            /* min and max are initialized   */
                                            /* to the extreme opposite values*/
                                            /* to avoid doing special        */
                                            /* processing the first time thru*/

    double data_rate;                       /* Variable used to calculate    */
                                            /* the data rate                 */

    FLAGS  flags;                           /* Command line flags            */

    flags.one_way_flag = 2;
    flags.size = 100;
    flags.number_iterations = 2;
    flags.number_concurrent = 1;

    /*
     * Make sure all output is seen as soon as possible.
     */
    setbuf(stdout, NULL);

    show_info(intro);                       /* Show program information      */

#if (defined(WIN32) || defined(WINDOWS))                              /*WIN32*/
       /****************************************************************WIN32*/
       /* Initialisation for WinCPIC                                   *WIN32*/
       /****************************************************************WIN32*/
    if (WinCPICStartup(WinCPICVERSION,&CPICData))                     /*WIN32*/
    {                                                                 /*WIN32*/
       return ;                                                    /*WIN32*/
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
     * setup arguments are stored in the cpicinit object.  The block size
     * and other loop parameters are set in the global variables.
     */
    process_arguments(argc, argv, cpicinit, &flags);


    if (cpicinit->set_destination == NOT_SET) {
        write_error( "\n\aYou must specify a destination.\n");
        show_info(usage);
        do_exit(EXIT_FAILURE);
    }

    if (cpicinit_query_password_needed(cpicinit)) {
        /* get a password from the user */
        cpicinit_get_password(cpicinit);
    }

    buffer = (unsigned char CM_PTR)alloc_cpic_buffer((unsigned int)flags.size);
                                            /* allocate an APPC buffer       */

    if (buffer == NULL) {
        write_error("Error allocating memory buffer.\nExiting...\n");
        do_exit(EXIT_FAILURE);
    }

    memset(buffer, 0, (unsigned int)flags.size);  /* Set block to zeros      */


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

    /*
     * Setup a CPI-C conversation.  This routine issues all of the
     * CPI-C calls from CMINIT() through just before you would
     * issue the CMALLC() call.  The conversation id is returned
     * for use by the program.
     */
    cpicinit_setup_conversation(cpicinit, cm_conv_id, cpicerr);

    /*
     * Fill in conversation information for CPI-C error reporting.
     */
    cpicerr_set_conv_id(cpicerr, cm_conv_id);

    {
    CM_SYNC_LEVEL sync_level = CM_CONFIRM;
    cmssl(cm_conv_id,                       /* Set sync level                */
          &sync_level,
          &cm_rc);
    /* The only expected return code is CM_OK */
    if (cm_rc != CM_OK) cpicerr_handle_rc(cpicerr, MSG_CMSSL, cm_rc);
    }

    {
    CM_PREPARE_TO_RECEIVE_TYPE prep_to_receive = CM_PREP_TO_RECEIVE_FLUSH;
    cmsptr(cm_conv_id,                      /* Set prepare to receive type   */
           &prep_to_receive,
           &cm_rc);
    /* The only expected return code is CM_OK */
    if (cm_rc != CM_OK) cpicerr_handle_rc(cpicerr, MSG_CMSPTR, cm_rc);
    }


    /*
     * Fill in conversation information for CPI-C error reporting.
     */
    cpicerr_set_conv_id(cpicerr, cm_conv_id);

    start_time = get_time();            /* let's time the allocate       */

    cmallc(cm_conv_id,
           &cm_rc);

    end_time = get_time();                  /* stop the timer                */

    /* The only expected return code is CM_OK */
    if (cm_rc != CM_OK) cpicerr_handle_rc(cpicerr, MSG_CMALLC, cm_rc);


                                            /* show the allocate time        */
    write_output("\nAllocate duration:                     %8lu ms\n",
                                                       end_time - start_time);

    start_time = get_time();

    cpicerr_exchange_version_plus(cpicerr,
                                  cm_conv_id,
                                  CM_SEND_STATE,
                                  &partner_major_version,
                                  &partner_minor_version,
                                  opsys_string,
                                  sizeof(opsys_string));

    end_time = get_time();                  /* stop the timer                */


    /*
     * Display the operating system string returned in the exchange.
     * The string length will be 0 if the operating system string
     * wasn't available.
     */

    if (strlen(opsys_string) != 0) {
        write_output("\nConnected to a partner running on: %s\n",
                     opsys_string);
    }


    /*
     * If the one_way_flag has been set, we have to make sure that our
     * partner is at the correct version to accept one way data.  If
     * the partner is not at the right level, we'll turn off the one
     * way flag and the partner will echo data (normal operating mode).
     *
     * Trying to use one way data with a partner that can't handle the
     * CONFIRM status indicator would result in an error on the partner
     * side.  On this side, we would see DEALLOCATE_ABEND.
     */
    if ((flags.one_way_flag == 1)  &&
        !(partner_major_version > ONEWAY_MAJOR_VERSION ||
        (partner_major_version == ONEWAY_MAJOR_VERSION &&
         partner_minor_version >= ONEWAY_MINOR_VERSION))) {
        write_output("\nOne way data transfer is not supported by partner.\n");
        write_output("Partner will echo data.\n");
        flags.one_way_flag = 2;
    }


                                            /* show the startup time         */
    write_output("\nProgram startup and Confirm duration:  %8lu ms\n\n",
                                                       end_time - start_time);


    write_output(
    "        Duration        Data Sent        Data Rate        Data Rate\n");
    write_output(
    "        (msec)          (bytes)          (KB/s)           (Mb/s)   \n");
    write_output(
    "        --------        ---------        ---------        ---------\n");

    /*
     * Set the amount of data we will send on each CMSEND() call.
     */
    length = flags.size;

    /*
     * Start current at zero so if a BREAK occurs, it will contain the number
     * of iterations completed.  We take a slight risk in assuming that
     * the curr_iteration++ operation is atomic.
     *
     * This loop encompasses both a send loop and a receive loop.  Both
     * the send a receive loop are executed the number of times specified
     * by the number_iterations variable (set by the -i argument).
     */
    for (curr_iteration = 0;
         curr_iteration<flags.number_iterations;
         curr_iteration++ ) {
        {
        CM_SEND_TYPE send_type = CM_BUFFER_DATA;
        cmsst(cm_conv_id,
              &send_type,
              &cm_rc);
        if (cm_rc != CM_OK) cpicerr_handle_rc(cpicerr, MSG_CMSST, cm_rc);
        }

        start_time = get_time();


        for (curr_concurrent = 1;           /* Start current at one so we    */
             curr_concurrent<flags.number_concurrent ;/* do one LESS send in */
             curr_concurrent++ ) {          /* loop than the specifed number */

            cmsend(cm_conv_id,
                   buffer,
                   &length,
                   &rts_received,
                   &cm_rc);


            /* The only expected return code is CM_OK */
            if (cm_rc != CM_OK) cpicerr_handle_rc(cpicerr, MSG_CMSEND, cm_rc);

        }

        /*
         * For the final send in the number of concurrent sends, set the send
         * type to do a send and a prepare to receive.  This will send both
         * the data and the send permission indicator to our partner all at
         * once.
         *
         * If the one_way_flag has been set, we will issue a Confirm along
         * with the Send_Data.  This will allow us to know when the partner
         * has actually received all the data so we can get an accurate
         * timing.
         *
         * On the partner side, if Send status is received, the partner will
         * know to echo the data.  If Confirm status is received, the partner
         * will know to issued Confirmed and then get ready to receive
         * more data, since the partner won't be echoing.
         */
        {
        CM_SEND_TYPE send_type;
        if (flags.one_way_flag != 1) {
            send_type = CM_SEND_AND_PREP_TO_RECEIVE;
        } else {
            send_type = CM_SEND_AND_CONFIRM;
        }
        cmsst(cm_conv_id,
              &send_type,
              &cm_rc);
        if (cm_rc != CM_OK) cpicerr_handle_rc(cpicerr, MSG_CMSST, cm_rc);
        }

        cmsend(cm_conv_id,
               buffer,
               &length,
               &rts_received,
               &cm_rc);
        /* The only expected return code is CM_OK */
        if (cm_rc != CM_OK) cpicerr_handle_rc(cpicerr, MSG_CMSEND, cm_rc);

        if (flags.one_way_flag != 1) {
            max_receive_len = flags.size;
            do {

                cmrcv (cm_conv_id,          /* Receive Data                  */
                       buffer,              /* Data Pointer                  */
                       &max_receive_len,    /* Size of Data Buffer           */
                       &data_received,      /* returned - data received      */
                       &received_len,       /* returned - length of data     */
                       &status_received,    /* returned - status received    */
                       &rts_received,       /* returned - request to send    */
                       &cm_rc);
                /* The only expected return code is CM_OK */
                if (cm_rc != CM_OK) {
                    cpicerr_handle_rc(cpicerr, MSG_CMRCV, cm_rc);
                }

                if (data_received != CM_NO_DATA_RECEIVED) {
                    curr_concurrent--;
                }

            } while ((status_received !=  CM_SEND_RECEIVED));
            /* Repeat the receive loop until SEND permission has been rcvd. */

            if (curr_concurrent != 0) {
                write_error(
                "ERROR.\n");
                write_error(
                    "Partner did not send the expected number of records.\n");
            }
        } else {
        }

        end_time = get_time();              /* stop timer                    */

        elapsed_time = end_time - start_time; /* calculate elapsed time      */

        write_output("%16ld", elapsed_time);
        write_output("%17lu", flags.size * flags.number_concurrent *
                              flags.one_way_flag);

        if (elapsed_time) {
            data_rate =                     /* in KBytes / 0.1 Sec           */
                              (double)
              ( ( (((double)flags.size * (double)flags.number_concurrent) /
                       (double)1024) *
                   (double)1 * (double)1000 * (double)flags.one_way_flag)
                           /    /* divided by */
                 ( (double)elapsed_time  / (double)10)  );

            data_rate = data_rate / (double)10;

            write_output("%17.1f", data_rate);
            write_output("%17.3f\n", (data_rate * (double)8) / (double)1000);
            {
            /* this code was for integer arithmetic */
            unsigned long data_rate;
            unsigned long modifier = 100000L;
            unsigned long bytes = flags.size * flags.number_concurrent
                                  * flags.one_way_flag;

            while ( bytes > (0xFFFFFFFF / modifier) && (modifier > 10)) {
                modifier = modifier / 10;
            } /* endwhile */

            data_rate = (unsigned long)
                           ((bytes * modifier))
                                    /
               (((unsigned long)elapsed_time * 1024L) / (100000L / modifier) );
            }


        } else {
            write_output("\n");             /* Make sure we move to next line*/
        }

        total_time += elapsed_time;         /* accumulate the elapsed time   */

        if (elapsed_time > max_time) {
            max_time = elapsed_time;        /* set the max time              */
        }
        if (elapsed_time < min_time) {
            min_time = elapsed_time;        /* set the min time              */
        }

    }

    {
    CM_DEALLOCATE_TYPE deallocate_type = CM_DEALLOCATE_FLUSH;
    cmsdt(cm_conv_id,
          &deallocate_type,
          &cm_rc);
    /* The only expected return code is CM_OK */
    if (cm_rc != CM_OK) cpicerr_handle_rc(cpicerr, MSG_CMSDT, cm_rc);
    }

    cmdeal(cm_conv_id,
           &cm_rc);
    /* The only expected return code is CM_OK */
    if (cm_rc != CM_OK) cpicerr_handle_rc(cpicerr, MSG_CMDEAL, cm_rc);

    /* destroy the object we created with cpicinit_new() */
    cpicinit_destroy(cpicinit);

    /* destroy the object we created with cpicerr_new() */
    cpicerr_destroy(cpicerr);

    /*
     * Print out the grand totals and max/min times.
     */
    {

        double data_rate;


        if (total_time > 10) {

            data_rate =                 /* in KBytes / 0.1 Sec           */
                              (double)
              ( ( (((double)flags.size * (double)flags.number_concurrent) /
                         (double)1024) *
                (double)curr_iteration * (double)1000 *
                (double)flags.one_way_flag)
                           /    /* divided by */
                 ( (double)total_time  / (double)10)  );

            data_rate = data_rate / 10;

            write_output("Totals:%9lu", total_time);
            write_output("%17lu", flags.size *
                                  flags.number_concurrent *
                                  curr_iteration *
                                  flags.one_way_flag);
            write_output("%17.1f", data_rate);
            write_output("%17.3f\n", (data_rate * (double)8) /
                                               (double)1000);
        } else {
            write_output("Totals:%9lu", total_time);
            write_output("%17lu\n", flags.size *
                                    flags.number_concurrent *
                                    curr_iteration *
                                    flags.one_way_flag);
        }
        if (curr_iteration > 0) {
            write_output(
            "\nDuration statistics:   Min = %lu   Ave = %lu   Max = %lu\n",
                                             min_time,
                                             total_time / curr_iteration,
                                             max_time);
        }

    }
    do_exit(EXIT_SUCCESS);

}

void
process_arguments(int argc,
                  char *argv[],
                  CPICINIT * cpicinit,
                  FLAGS * flags )
{
    int         c;                          /* flag specifed, used w/getopt  */

    /*
     * GETOPT is an easy way to parse command line arguments
     * Each parameter which can have a flag is passed in the third argument
     * to getopt.  Getopt returns the character of the flag on the command
     * line and sets optarg to point to the value associated with the flag.
     * optind is the index of the argument that getopt is currently processing.
     */
    while (optind != argc) {
        c = getopt(argc, argv, "?1c:t:m:i:s:u:p:C:T:M:I:S:U:P:nNqQ");
        switch (c) {
        case EOF:
            optarg = argv[optind];
            if (optarg[0] == '?') {
               show_info(usage);
               do_exit(EXIT_FAILURE);
            }
            optind++;
            if (cpicinit->set_destination == NOT_SET) {
                cpicinit_set_destination(cpicinit, optarg);
            } else {
                write_error("Only one destination may be specified.\n");
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
        case 'S':
        case 's':
            flags -> size = atol(optarg);

            if (flags->size > MAX_SIZE) {   /* check bounds                  */
                write_error("Size (-s) of %lu too large.\n", flags->size);
                write_error("Setting size to %lu\n", (unsigned long)MAX_SIZE);
                flags->size = MAX_SIZE;     /* reset to MAX                  */
            }
            break;
        case 'Q':
        case 'q':
            /* quiet processing is done in main() */
            break;
        case 'I':
        case 'i':
            flags->number_iterations = atol(optarg);
            break;
        case 'C':
        case 'c':
            flags->number_concurrent = atol(optarg);
            break;
        case '1':
            flags->one_way_flag = 1;
            break;
        case '?':
            show_info(usage);
            do_exit(EXIT_FAILURE);
            break;
        default:
            write_output("Invalid flag.  Use %s -? for usage\n", PROGRAM_NAME);
            do_exit(EXIT_FAILURE);
        }
    }
}


