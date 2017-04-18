
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1994-1996 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/*++

Module Name:

    kill.c

Abstract:

    This module implements a task killer application.

--*/

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"


#define MAX_TASKS           256

BOOL        ForceKill;
DWORD       pid;
CHAR        pname[MAX_PATH];
TASK_LIST   tlist[MAX_TASKS];


VOID GetCommandLineArgs(VOID);
VOID Usage(VOID);



int _cdecl
main(
    int argc,
    char *argv[]
    )
{
    DWORD             i;
    DWORD             numTasks;
    TASK_LIST_ENUM    te;
    int               rval = 0;
    char              tname[PROCESS_SIZE];
    LPSTR             p;
    DWORD             ThisPid;
    OSVERSIONINFO     verInfo = {0};
    LPGetTaskList     GetTaskList;
    LPEnableDebugPriv EnableDebugPriv;


    GetCommandLineArgs();

    if (pid == 0 && pname[0] == 0) {
        printf( "missing pid or task name\n"
                "type kill /? for help\n");
        return 1;
    }


    //
    // Determine what system we're on and do the right thing
    //
    verInfo.dwOSVersionInfoSize = sizeof (verInfo);
    GetVersionEx(&verInfo);

    switch (verInfo.dwPlatformId)
    {
    case VER_PLATFORM_WIN32_NT:
       GetTaskList     = GetTaskListNT;
       EnableDebugPriv = EnableDebugPrivNT;
       break;

    case VER_PLATFORM_WIN32_WINDOWS:
       GetTaskList = GetTaskList95;
       EnableDebugPriv = EnableDebugPriv95;
       break;

    default:
       printf ("tlist requires Windows NT or Windows 95\n");
       return 1;
    }


    //
    // Obtain the ability to manipulate other processes
    //
    EnableDebugPriv();

    if (pid) {
        tlist[0].dwProcessId = pid;
        if (KillProcess( tlist, TRUE )) {
            printf( "process #%d killed\n", pid );
            return 0;
        } else {
            printf( "process #%d could not be killed\n", pid );
            return 1;
        }
    }

    //
    // get the task list for the system
    //
    numTasks = GetTaskList( tlist, MAX_TASKS );

    //
    // enumerate all windows and try to get the window
    // titles for each task
    //
    te.tlist = tlist;
    te.numtasks = numTasks;
    GetWindowTitles( &te );

    ThisPid = GetCurrentProcessId();

    for (i=0; i<numTasks; i++) {
        //
        // this prevents the user from killing KILL.EXE and
        // it's parent cmd window too
        //
        if (ThisPid == tlist[i].dwProcessId) {
            continue;
        }
        if (MatchPattern( tlist[i].WindowTitle, "*KILL*" )) {
            continue;
        }

        tname[0] = 0;
        strcpy( tname, tlist[i].ProcessName );
        p = strchr( tname, '.' );
        if (p) {
            p[0] = '\0';
        }
        if (MatchPattern( tname, pname )) {
            tlist[i].flags = TRUE;
        } else if (MatchPattern( tlist[i].ProcessName, pname )) {
            tlist[i].flags = TRUE;
        } else if (MatchPattern( tlist[i].WindowTitle, pname )) {
            tlist[i].flags = TRUE;
        }
    }

    for (i=0; i<numTasks; i++) {
        if (tlist[i].flags) {
            if (KillProcess( &tlist[i], ForceKill )) {
                printf( "process #%d [%s] killed\n", tlist[i].dwProcessId, tlist[i].ProcessName );
            } else {
                printf( "process #%d [%s] could not be killed\n", tlist[i].dwProcessId, tlist[i].ProcessName );
                rval = 1;
            }
        }
    }

    return rval;
}

VOID
GetCommandLineArgs(
    VOID
    )
{
    char        *lpstrCmd;
    UCHAR       ch;
    char        *p = pname;


    pid = 0;
    *p = '\0';

    lpstrCmd = GetCommandLine();

    // skip over program name
    do 
    {
       ch = *lpstrCmd++;
    }
    while (!isspace(ch));

    //  skip over any white space following the program name
    while (isspace(ch)) 
    {
       ch = *lpstrCmd++;
    }


    // Follow this pattern strictly:
    //  KILL [options] <<pid> | <pattern>>\n\n" 
    //  where options is /f,
    //  and PID is a positive or negative decimal number, and
    //  pattern is a string of characters

    // Look for an option, which will be prefaced with '/'
    if (ch == '/')
    {
       ch = *lpstrCmd++;
  
       switch (ch) 
       {
       case 'F':     // found "kill /f" so far
       case 'f':
          ForceKill = TRUE;
          ch = *lpstrCmd++;
          break;

       case '?':    // found "kill /?"
          Usage();
          return;   // don't do anything after printing usage
          break;

       default:
          printf ("%c is an invalid switch\n", ch);  // invalid switch
          return;   
       }
    
       // eat whitepace after option switch
       while (isspace(ch)) 
       {
          ch = *lpstrCmd++;
       }
    }

    // In the 3 cases below, look for either a PID or a pattern 
    // a PID could be a positive or negative decimal integer

    // Look for a negative PID
    if (ch == '-')
    {
       ch = *lpstrCmd++;

       while (isdigit(ch)) 
       {
          pid = pid * 10 - ( ch - '0' );
          ch = *lpstrCmd++;
       }
       return; // found "kill -pid" or "kill /f -pid" so we're done
    }

    // Look for a postive PID
    if (isdigit(ch)) 
    {
       while (isdigit(ch)) 
       {
          pid = pid * 10 + ch - '0';
          ch = *lpstrCmd++;
       }
       return;  // found "kill pid" or "kill /f pid" so we're done
    }
 
    // Look for a pattern
    while (ch) 
    {
       *p++ = ch;
       ch = *lpstrCmd++;
    }
    *p = '\0';
    strupr(pname);

    return;  // found "kill pattern" or "kill /f pattern" so we're done
}
      


VOID
Usage(
    VOID
    )

/*++

Routine Description:

    Prints usage text for this tool.

Arguments:

    None.

Return Value:

    None.

--*/

{
    fprintf( stderr, "Microsoft (R) Windows (TM) KILL\n" );
    fprintf( stderr, "Copyright (C) 1994-1996 Microsoft Corp. All rights reserved\n\n" );
    fprintf( stderr, "usage: KILL [options] <<pid> | <pattern>>\n\n" );
    fprintf( stderr, "           [options]:\n" );
    fprintf( stderr, "               /?     This help\n\n" );
    fprintf( stderr, "               /f     Force process kill\n\n" );
    fprintf( stderr, "           <pid>\n" );
    fprintf( stderr, "              This is the process id for the task\n" );
    fprintf( stderr, "               to be killed.  Use TLIST to get a\n" );
    fprintf( stderr, "               valid pid\n\n" );
    fprintf( stderr, "           <pattern>\n" );
    fprintf( stderr, "              The pattern can be a complete task\n" );
    fprintf( stderr, "              name or a regular expression pattern\n" );
    fprintf( stderr, "              to use as a match.  Kill matches the\n" );
    fprintf( stderr, "              supplied pattern against the task names\n" );
    fprintf( stderr, "              and the window titles.\n" );
    ExitProcess(0);
}
