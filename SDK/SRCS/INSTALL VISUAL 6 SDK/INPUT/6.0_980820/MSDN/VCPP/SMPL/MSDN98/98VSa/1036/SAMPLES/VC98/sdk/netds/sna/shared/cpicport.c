/*****************************************************************************
 *
 *  MODULE NAME: CPICPORT.C
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
 *  FUNCTION:  Contains procedures to that may have to be rewritten for
 *             different environments.
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
 *             CPICPORT.H
 *
 *  PORTABILITY NOTES:
 *             This file is the home of all operating system specific
 *             functions.  The following is a summary of the routines
 *             in this file and where they are used:
 *
 *             write_output()
 *                 displays a text string to normal output
 *
 *             write_error()
 *                 displays error text to error output
 *
 *             write_log()
 *                 logs text to an opened log file
 *                 if the log file was not open, will display to error output
 *
 *             display_message()
 *                 Delivers a text message.
 *                 Used by ATELLD.C.
 *
 *             get_time()
 *                 Returns time in milliseconds.
 *                 Used by APING.C.
 *
 *             alloc_cpic_buffer()
 *                 Allocates the best memory buffer for CPI-C performance.
 *                 Used by APING.C and APINGD.C.
 *
 *             show_info()
 *                 Displays an array of text strings.
 *                 Used by all files with a main() function.
 *
 *             get_machine_mode()
 *                 For family API applications; determines whether we
 *                 are running under OS/2 or DOS.
 *
 *             get_password()
 *                 Used to request that the user enter a password.
 *                 If possible, the password will not display while the
 *                 user types it.
 *                 Used by CPICINIT.C
 *
 *             execute_and_send_output()
 *                 Execute the specified command and send the output back
 *                 to the client side.
 *                 This routine is called by AREXECD.C.
 *
 *             do_exit()
 *                 Exit properly for the environment.  This is usually
 *                 necessary for GUI environments.
 *
 *             free_cpic_buffer()
 *                 Frees the memory allocated by alloc_cpic_buffer().
 *                 Used by MPINGD.C.
 *
 *  CHANGE HISTORY:
 *  Date       Description
 *  08/05/92   Version 2.31 of APING, ATELL and AREXEC released to CompuServe.
 *             This version was also distributed at the APPC/APPN Platform
 *             Developer's Conference held in Raleigh, NC.
 *  08/13/92   Added the write_*() calls.
 *             Changed all printf and fprintf calls to use a write_*() call.
 *  08/19/92   Added workaround for problem with system() returning non-null
 *             even when command succeeded.  The fix is in DOS and FAPI
 *             versions of execute_and_send_output().
 *  08/20/92   Fixed alloc_cpic_buffer() so it will use a shared buffer
 *             under OS/2 2.0.
 *  08/23/92   Fixed extra rc definition for AS/400 definition of the
 *             execute_and_send_output() routine.
 *  08/24/92   Version 2.32 released to CompuServe.
 *  08/25/92   Changed DOS and AIX execute_and_send_output() to use the
 *             tempnam() function instead of the tmpnam() function.  This
 *             results in tempfiles being written to the TMP directory.
 *  09/22/92   Version 2.33 released to CompuServe.
 *  01/07/93   Added OS2_20 to list of conditional compile directives in
 *             the following routines:
 *               get_time
 *               get_password
 *               set_echo
 *               execute_and_send_output
 *  11/11/94   Wrote free_cpic_buffer()
 *
 *****************************************************************************/

#if defined(WIN32) || defined(WINDOWS)
#include <windows.h>
#endif

#include "wincpic.h"

#include "cpicerrs.h"

/* Set up constant declarations */
#include "cpicdefs.h"

#include "cpicport.h"


/* standard C include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

extern char ebcdic_to_ascii_table[];
extern char ascii_to_ebcdic_table[];



void write_error(char *fmt, ...)
{
    /*=========================================================================
     *
     *=======================================================================*/

    va_list args;

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}


void write_output(char *fmt, ...)
{
    /*=========================================================================
     *
     *=======================================================================*/

    va_list args;

    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
}

void write_log(FILE * file, char *fmt, ...)
{
    /*=========================================================================
     *
     *=======================================================================*/

    va_list args;

    va_start(args, fmt);
    if (file == NULL) {
        write_error(fmt, args);
    } else {
        vfprintf(file, fmt, args);
    }
    va_end(args);
}

/*
 * display_message()
 *       delivers a text message
 *       used by ATELLD.C
 *
 *    default
 *       Uses C library functions to print the message.
 */
void
display_message(char * origin, char * dest_userid, char * message)
{

    char timestamp[TIMELENGTH];
    struct tm * newtime;
    time_t ltime;

    time(&ltime);
    newtime = localtime(&ltime);
    strcpy(timestamp, asctime(newtime));

    /* eliminate new line character for display */
    timestamp[strlen(timestamp)-1] = '\0';

    write_output("\n\n  msg from %s ", origin);
    if (dest_userid[0] != '\0') {
        write_output("to user %s ", dest_userid);
    }
    write_output("on %s:", timestamp);
    write_output("\n\n     %s\n\n",message);
}



/*
 * get_time()
 *       returns time in milliseconds
 *       used by APING.C
 *
 */
unsigned long
get_time(void)
{

    return GetTickCount();

}


/*
 * alloc_cpic_buffer()
 */

char CM_PTR
alloc_cpic_buffer (unsigned int size)
{
   return malloc(size);
}

/*
 * freec_cpic_buffer()
 */

void
free_cpic_buffer( void *memblock )
{
	free( memblock );
}


/*
 * show_info()
 *
 *       This procedure displays a block of text information on the the
 *       screen.  The input argument is an array of strings to be output,
 *       one string per line.  A NULL array element indicates the end of
 *       the strings.
 *
 *    default
 *       print out all of the text strings in the array using the cpicport
 *       write_output() call.
 */
void
show_info(char * * text)
{
    int i;

    for ( i = 0; text[i] != NULL; i++ ) {
        write_output("%s\n", text[i]);
    }
    return;
}

/*
 * get_password()
 *
 *    Gets a password from the user.  Where possible, this routine should
 *    disable echoing of keystrokes for security reasons.
 *
 *    Returns
 *       0 - password was successfully input
 *       1 - password variable was not updated successfully
 */
int
get_password(char * password, int max_length)
{
    int rc;
    int length;

    /* There is no portable way to disable echoing of input keystrokes.      */
    /* If a platform does support turning off echo, this section should be   */
    /* rewritten and ifdef'ed.                                               */

    if (NULL != fgets(password, max_length+1, stdin)) {
        length = strlen(password);
        if (length > 0 && length < max_length) {
            if (password[length-1] == '\n') { /* remove the trailing         */
                password[length-1] = '\0';    /* newline if it exists        */
            }
            rc = 0;
        } else {
            rc = 1;
        }

    } else {
        rc = 1;
    }

    return rc;
}

/*
 * do_exit()
 *
 * Exit properly for the environment we're running in.
 */
void
do_exit(int rc)
{
#ifdef EXITTHREAD
    ExitThread(rc);
#else
    WinCPICCleanup();
    exit(rc);
#endif
}

/*
 * The ASCII<-->EBCDIC character set translation routines are implemented
 * below.  These procedures should never be called directly, but should
 * be accessed through the convert_to_ascii() and convert_from_ascii()
 * macros.  This frees the application program from knowing whether
 * it is being coded on an ASCII or EBCDIC computer (this must be
 * determined in the macro definition in CPICPORT.H).
 */

void   ascii_to_ebcdic_field  (unsigned char * ascii_field,
                               unsigned int field_size)
{
    unsigned int i;

    for (i = 0;
         i < field_size;
         ascii_field[i] = ascii_to_ebcdic_table[(unsigned)ascii_field[i]],i++);
}

void  ascii_to_ebcdic_string (unsigned char * ascii_string)
{
    ascii_to_ebcdic_field(ascii_string, strlen((char*)ascii_string));
}

void   ebcdic_to_ascii_field  (unsigned char * ebcdic_field,
                               unsigned int field_size)
{
    unsigned int i;

    for (i = 0;
         i < field_size;
         ebcdic_field[i] =
                         ebcdic_to_ascii_table[(unsigned)ebcdic_field[i]],i++);
}

void  ebcdic_to_ascii_string (unsigned char * ebcdic_string)
{
    ebcdic_to_ascii_field(ebcdic_string, strlen((char*)ebcdic_string));
}



/* ASCII to EBCDIC translate table (only UGL character set) */

char ascii_to_ebcdic_table[] = {
"\x00\x01\x02\x03\x37\x2D\x2E\x2F\x16\x05\x15\x0B\x0C\x0D\x0E\x0F"  /* 00-0F */
"\x10\x11\x12\x13\x3C\x3D\x32\x26\x18\x19\x3F\x27\x22\x1D\x35\x1F"  /* 10-1F */
"\x40\x5A\x7F\x7B\x5B\x6C\x50\x7D\x4D\x5D\x5C\x4E\x6B\x60\x4B\x61"  /* 20-2F */
"\xF0\xF1\xF2\xF3\xF4\xF5\xF6\xF7\xF8\xF9\x7A\x5E\x4C\x7E\x6E\x6F"  /* 30-3F */
"\x7C\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xD1\xD2\xD3\xD4\xD5\xD6"  /* 40-4F */
"\xD7\xD8\xD9\xE2\xE3\xE4\xE5\xE6\xE7\xE8\xE9\xAD\xE0\xBD\x5F\x6D"  /* 50-5F */
"\x79\x81\x82\x83\x84\x85\x86\x87\x88\x89\x91\x92\x93\x94\x95\x96"  /* 60-6F */
"\x97\x98\x99\xA2\xA3\xA4\xA5\xA6\xA7\xA8\xA9\xC0\x4F\xD0\xA1\x07"  /* 70-7F */
"\x43\x20\x21\x1C\x23\xEB\x24\x9B\x71\x28\x38\x49\x90\xBA\xEC\xDF"  /* 80-8F */
"\x45\x29\x2A\x9D\x72\x2B\x8A\x9A\x67\x56\x64\x4A\x53\x68\x59\x46"  /* 90-9F */
"\xEA\xDA\x2C\xDE\x8B\x55\x41\xFE\x58\x51\x52\x48\x69\xDB\x8E\x8D"  /* A0-AF */
"\x73\x74\x75\xFA\x15\xB0\xB1\xB3\xB4\xB5\x6A\xB7\xB8\xB9\xCC\xBC"  /* B0-BF */
"\xAB\x3E\x3B\x0A\xBF\x8F\x3A\x14\xA0\x17\xCB\xCA\x1A\x1B\x9C\x04"  /* C0-CF */
"\x34\xEF\x1E\x06\x08\x09\x77\x70\xBE\xBB\xAC\x54\x63\x65\x66\x62"  /* D0-DF */
"\x30\x42\x47\x57\xEE\x33\xB6\xE1\xCD\xED\x36\x44\xCE\xCF\x31\xAA"  /* E0-EF */
"\xFC\x9E\xAE\x8C\xDD\xDC\x39\xFB\x80\xAF\xFD\x78\x76\xB2\x9F\xFF"  /* F0-FF */
};

/* EBCDIC to ASCII translate table (only UGL character set) */

char ebcdic_to_ascii_table[] = {
"\x00\x01\x02\x03\xCF\x09\xD3\x7F\xD4\xD5\xC3\x0B\x0C\x0D\x0E\x0F"  /* 00-0F */
"\x10\x11\x12\x13\xC7\x0A\x08\xC9\x18\x19\xCC\xCD\x83\x1D\xD2\x1F"  /* 10-1F */
"\x81\x82\x1C\x84\x86\x0A\x17\x1B\x89\x91\x92\x95\xA2\x05\x06\x07"  /* 20-2F */
"\xE0\xEE\x16\xE5\xD0\x1E\xEA\x04\x8A\xF6\xC6\xC2\x14\x15\xC1\x1A"  /* 30-3F */
"\x20\xA6\xE1\x80\xEB\x90\x9F\xE2\xAB\x8B\x9B\x2E\x3C\x28\x2B\x7C"  /* 40-4F */
"\x26\xA9\xAA\x9C\xDB\xA5\x99\xE3\xA8\x9E\x21\x24\x2A\x29\x3B\x5E"  /* 50-5F */
"\x2D\x2F\xDF\xDC\x9A\xDD\xDE\x98\x9D\xAC\xBA\x2C\x25\x5F\x3E\x3F"  /* 60-6F */
"\xD7\x88\x94\xB0\xB1\xB2\xFC\xD6\xFB\x60\x3A\x23\x40\x27\x3D\x22"  /* 70-7F */
"\xF8\x61\x62\x63\x64\x65\x66\x67\x68\x69\x96\xA4\xF3\xAF\xAE\xC5"  /* 80-8F */
"\x8C\x6A\x6B\x6C\x6D\x6E\x6F\x70\x71\x72\x97\x87\xCE\x93\xF1\xFE"  /* 90-9F */
"\xC8\x7E\x73\x74\x75\x76\x77\x78\x79\x7A\xEF\xC0\xDA\x5B\xF2\xF9"  /* A0-AF */
"\xB5\xB6\xFD\xB7\xB8\xB9\xE6\xBB\xBC\xBD\x8D\xD9\xBF\x5D\xD8\xC4"  /* B0-BF */
"\x7B\x41\x42\x43\x44\x45\x46\x47\x48\x49\xCB\xCA\xBE\xE8\xEC\xED"  /* C0-CF */
"\x7D\x4A\x4B\x4C\x4D\x4E\x4F\x50\x51\x52\xA1\xAD\xF5\xF4\xA3\x8F"  /* D0-DF */
"\x5C\xE7\x53\x54\x55\x56\x57\x58\x59\x5A\xA0\x85\x8E\xE9\xE4\xD1"  /* E0-EF */
"\x30\x31\x32\x33\x34\x35\x36\x37\x38\x39\xB3\xF7\xF0\xFA\xA7\xFF"  /* F0-FF */
};

void
execute_and_send_output(char * command,
                        unsigned char * cm_conv_id,
                        struct error_handler_cpicerr * cpicerr)
{

   DWORD lasterror = 0;
   HANDLE hWritePipe = NULL;
   HANDLE hReadPipe = NULL;
   SECURITY_ATTRIBUTES SecAttrib = {0};
   STARTUPINFO StartInfo = {0};
   PROCESS_INFORMATION ProcInfo = {0};
   unsigned char * buffer=NULL;
   DWORD BufferSize=10000;
   DWORD BytesRead=0;
   DWORD BytesInPipe=0;
   DWORD WaitState=0;
   BOOL ProcessDead=FALSE;
   CM_INT32 rts_received;
   CM_INT32 cm_rc;
   char NewCommand[255] = {0};

   strcpy(NewCommand,"cmd /c ");
   strcat(NewCommand,command);

   buffer=malloc(BufferSize+2);

   SecAttrib.nLength = sizeof(SECURITY_ATTRIBUTES);
   SecAttrib.lpSecurityDescriptor = NULL;
   SecAttrib.bInheritHandle = TRUE;

   /**************************************************************************/
   /* Create named pipe and get handle to read end of the pipe.              */
   /**************************************************************************/
   if ((hReadPipe = CreateNamedPipe("\\\\.\\pipe\\arexecpipe",
               PIPE_ACCESS_INBOUND, PIPE_TYPE_BYTE, 1, BufferSize,
               BufferSize, 1000,&SecAttrib)) == INVALID_HANDLE_VALUE)
   {
      lasterror = GetLastError();
      printf("CreateNamedPipe returned %d",lasterror);
      return;
   }

   /**************************************************************************/
   /* Open a handle to the write end of the pipe, NB must be inheritable     */
   /**************************************************************************/
   if ((hWritePipe = CreateFile("\\\\.\\pipe\\arexecpipe",GENERIC_WRITE, 0,
                &SecAttrib, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL))
        == INVALID_HANDLE_VALUE)
   {
      lasterror = GetLastError();
      printf("CreateFile returned %d",lasterror);
      return;
   }

   /**************************************************************************/
   /* Now create the process, with its stdout and stderr pipes attatched to  */
   /* the write end of the named pipe.                                       */
   /**************************************************************************/
   StartInfo.cb = sizeof(STARTUPINFO);
   StartInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
   StartInfo.wShowWindow = SW_HIDE;
   StartInfo.hStdInput = NULL;
   StartInfo.hStdOutput = hWritePipe;
   StartInfo.hStdError = hWritePipe;
   ProcessDead = FALSE;

   if (!CreateProcess(NULL,NewCommand, NULL, NULL, TRUE, 0, NULL, NULL,
                      &StartInfo, &ProcInfo))
   {
      lasterror=GetLastError();
      printf("CreateProcess returned %d\n",lasterror);
      return;
   }

   /**************************************************************************/
   /* Loop whilst the process is still running                               */
   /**************************************************************************/
   while (!ProcessDead)
   {
      /***********************************************************************/
      /* Check the process handle to see if it is dead yet.                  */
      /***********************************************************************/
      WaitState = WaitForSingleObject(ProcInfo.hProcess,1);
      if (WaitState != WAIT_TIMEOUT)
      {
         ProcessDead = TRUE;
      }

      /***********************************************************************/
      /* Peek in the named pipe for some data, don't just do a ReadFile as   */
      /* we may never get any more data!                                     */
      /* If there is some then read it out of the pipe and send it.          */
      /***********************************************************************/
      if (!PeekNamedPipe(hReadPipe, NULL, 0, NULL, &BytesInPipe, NULL))
      {
         lasterror=GetLastError();
         printf("PeekNamePipe returned %d\n",lasterror);
         return;
      }
      if (BytesInPipe != 0)
      {
         memset(buffer,'\0',BufferSize+1);
         if (!ReadFile(hReadPipe, buffer, BufferSize, &BytesRead, NULL))
         {
            lasterror=GetLastError();
            printf("ReadFile returned %d\n",lasterror);
            return;
         }
         cmsend(cm_conv_id,(unsigned char *) buffer,(CM_INT32 *)&BytesRead,
                &rts_received,&cm_rc);
         if (cm_rc) cpicerr_handle_rc(cpicerr, MSG_CMSEND, cm_rc);
      }
   }
   do
   {
      /***********************************************************************/
      /* The process is now dead, but there could still be some data in the  */
      /* pipe, so we do a peek/read loop until the number of bytes left is 0 */
      /***********************************************************************/
      if (!PeekNamedPipe(hReadPipe, NULL, 0, NULL, &BytesInPipe, NULL))
      {
         lasterror=GetLastError();
         printf("PeekNamePipe returned %d\n",lasterror);
         return;
      }
      if (BytesInPipe != 0)
      {
         memset(buffer,'\0',BufferSize+1);
         if (!ReadFile(hReadPipe, buffer, BufferSize, &BytesRead, NULL))
         {
            lasterror=GetLastError();
            printf("ReadFile returned %d\n",lasterror);
            return;
         }
         cmsend(cm_conv_id,(unsigned char *) buffer,(CM_INT32 *)&BytesRead,
                &rts_received,&cm_rc);
         if (cm_rc) cpicerr_handle_rc(cpicerr, MSG_CMSEND, cm_rc);
      }
   } while (BytesInPipe != 0);

   CloseHandle(hReadPipe);
   CloseHandle(hWritePipe);

   return;

}
