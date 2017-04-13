
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//+---------------------------------------------------------------------------
//
//  File:       protos.h
//
//  Contents:
//
//  Classes:
//
//  Functions:
//
//----------------------------------------------------------------------------

#ifndef __PROTOS_H__
#define __PROTOS_H__




//
// Service Controller interaction:
//

BOOL
NotifyServiceController(
            VOID);

BOOL
UpdateServiceStatus(DWORD   Status);

void
FailServiceStart(
    DWORD           Win32Code,
    DWORD           PrivateCode);


//
// Event Logging Support
//

BOOL
InitializeEvents(void);

DWORD
ReportServiceEvent(
    IN WORD EventType,
    IN DWORD EventId,
    IN DWORD SizeOfRawData,
    IN PVOID RawData,
    IN DWORD NumberOfStrings,
    ...
    );


//
// Command dispatcher
//

Pop3Disposition
Pop3Dispatch(
    PVOID       pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen
    );

PVOID
CreatePop3Context(void);

//
// Parameter support:
//

BOOL
ReadParameters(VOID);



//
// Service Support
//

void
WINAPI
Pop3SrvMain(
    DWORD       argc,
    LPTSTR      argv[]);

//
// Worker thread initialization routine.
//

HANDLE
InitializeThreads (
    VOID
    );

//
// Connection management routines.
//

BOOL
AcceptClients (
    HANDLE hCompletionPort
    );

VOID
CloseClient (
    PCLIENT_CONTEXT lpClientContext,
    BOOL bGraceful
    );

#endif
