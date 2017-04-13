/*++

Copyright (c) 1995-1997  Microsoft Corporation

Module Name:

    init.c

Abstract:

    This is the initialization module for the pfmon program.

Author:

    Mark Lucovsky (markl) 26-Jan-1995

Revision History:

--*/

#include "pfmonp.h"

BOOL
InitializePfmon( VOID )
{
    LPTSTR CommandLine;
    BOOL fShowUsage;
    DWORD Pid = 0;

    fShowUsage = FALSE;
    CommandLine = GetCommandLine();
    while (*CommandLine > ' ') {
        CommandLine += 1;
    }
    while (TRUE) {
        while (*CommandLine <= ' ') {
            if (*CommandLine == '\0') {
                break;
            } else {
                CommandLine += 1;
            }
        }

        if (!strnicmp( CommandLine, "/v", 2 ) || !strnicmp( CommandLine, "-v", 2 )) {
            CommandLine += 2;
            fVerbose = TRUE;
        } else if (!strnicmp( CommandLine, "/?", 2 ) || !strnicmp( CommandLine, "-?", 2 )) {
            CommandLine += 2;
            fShowUsage = TRUE;
            goto showusage;
        } else if (!strnicmp( CommandLine, "/c", 2 ) || !strnicmp( CommandLine, "-c", 2 )) {
            CommandLine += 2;
            fCodeOnly = TRUE;
        } else if (!strnicmp( CommandLine, "/h", 2 ) || !strnicmp( CommandLine, "-h", 2 )) {
            CommandLine += 2;
            fHardOnly = TRUE;
        } else if (!strnicmp( CommandLine, "/n", 2 ) || !strnicmp( CommandLine, "-n", 2 )) {
            CommandLine += 2;
            LogFile = fopen("pfmon.log","wt");
            fLogOnly = TRUE;
        } else if (!strnicmp( CommandLine, "/l", 2 ) || !strnicmp( CommandLine, "-l", 2 )) {
            CommandLine += 2;
            LogFile = fopen("pfmon.log","wt");
        } else if (!strnicmp( CommandLine, "/p", 2 ) || !strnicmp( CommandLine, "-p", 2 )) {
            CommandLine += 2;
            while (*CommandLine <= ' ') {
                if (*CommandLine == '\0') {
                    break;
                } else {
                    ++CommandLine;
                }
            }
            Pid = atoi(CommandLine);
            CommandLine = strchr(CommandLine,' ');
            if (CommandLine==NULL) {
                break;
            }
        } else if (!strnicmp( CommandLine, "/d", 2 ) || !strnicmp( CommandLine, "-d", 2 )) {
            CommandLine += 2;
            fDatabase = TRUE;
        } else {
            break;
        }
    }
showusage:
    if ( fShowUsage ) {
        fprintf(stdout,"Usage: PFMON [switches] application-command-line\n");
        fprintf(stdout,"             [-?] display this message\n");
        fprintf(stdout,"             [-n] don't display running faults, just log to pfmon.log\n");
        fprintf(stdout,"             [-l] log faults to pfmon.log\n");
        fprintf(stdout,"             [-c] only show code faults\n");
        fprintf(stdout,"             [-h] only show hard faults\n");
        fprintf(stdout,"             [-p pid] attach to existing process\n");
        fprintf(stdout,"             [-d] Database format (tab delimited)\n");
        fprintf(stdout,"                  format: pagefault number, Page Fault type (Hard or Soft),\n");
        fprintf(stdout,"                  Program Counter's Module, Symbol for PC, Decimal value of PC,\n");
        fprintf(stdout,"                  Decimal value of PC, Module of the virtual address accessed,\n");
        fprintf(stdout,"                  Symbol for VA, value of VA\n");
        return FALSE;
        };

    InitializeListHead( &ProcessListHead );
    InitializeListHead( &ModuleListHead );
    SetSymbolSearchPath();

    PfmonModuleHandle = GetModuleHandle( NULL );

    if (Pid != 0) {
        return(AttachApplicationForDebug(Pid));
    } else {
        return (LoadApplicationForDebug( CommandLine ));
    }

    return TRUE;
}

BOOL
LoadApplicationForDebug(
    LPSTR CommandLine
    )
{
    STARTUPINFO StartupInfo;
    PROCESS_INFORMATION ProcessInformation;

    ZeroMemory( &StartupInfo, sizeof( StartupInfo ) );
    StartupInfo.cb = sizeof(StartupInfo);

    if (!CreateProcess( NULL,
                        CommandLine,
                        NULL,
                        NULL,
                        FALSE,                          // No handles to inherit
                        DEBUG_PROCESS,
                        NULL,
                        NULL,
                        &StartupInfo,
                        &ProcessInformation)) {
        DeclareError( PFMON_CANT_DEBUG_PROGRAM,
                      GetLastError(),
                      CommandLine
                    );
        return FALSE;
    } else {
        hProcess = ProcessInformation.hProcess;
        SymInitialize(hProcess,NULL,FALSE);

        return InitializeProcessForWsWatch(hProcess);
    }
}

BOOL
AttachApplicationForDebug(
    DWORD Pid
    )
{

    if (!DebugActiveProcess(Pid)) {
        DeclareError( PFMON_CANT_DEBUG_ACTIVE_PROGRAM,
                      GetLastError(),
                      Pid );
        return FALSE;
    } else {
        hProcess = OpenProcess(PROCESS_VM_READ
                               | PROCESS_QUERY_INFORMATION
                               | PROCESS_SET_INFORMATION,
                               FALSE,
                               Pid);
        SymInitialize(hProcess,NULL,FALSE);

        return InitializeProcessForWsWatch(hProcess);
    }
}
