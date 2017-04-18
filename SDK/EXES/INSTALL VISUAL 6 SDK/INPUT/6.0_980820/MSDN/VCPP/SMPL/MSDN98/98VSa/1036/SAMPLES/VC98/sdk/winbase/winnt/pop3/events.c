
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
//  File:       events.c
//
//  Contents:
//
//  Classes:
//
//  Functions:
//
//----------------------------------------------------------------------------

#include "pop3srvp.h"
#pragma hdrstop

HANDLE  hEventLog = INVALID_HANDLE_VALUE;
DWORD   LoggingLevel = 1;
WCHAR   EventSourceName[] = TEXT("Pop3 Server");

#define MAX_EVENT_STRINGS 8

//+---------------------------------------------------------------------------
//
//  Function:   InitializeEvents
//
//  Synopsis:   Connects to event log service
//
//  Arguments:  (none)
//
//  History:    1-03-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
BOOL
InitializeEvents(void)
{
    hEventLog = RegisterEventSource(NULL, EventSourceName);
    if (hEventLog)
    {
        return(TRUE);
    }
    DebugLog((DEB_ERROR, "Could not open event log, error %d\n", GetLastError()));
    return(FALSE);
}


//+---------------------------------------------------------------------------
//
//  Function:   ReportServiceEvent
//
//  Synopsis:   Reports an event to the event log
//
//  Arguments:  [EventType]       -- EventType (ERROR, WARNING, etc.)
//              [EventId]         -- Event ID
//              [SizeOfRawData]   -- Size of raw data
//              [RawData]         -- Raw data
//              [NumberOfStrings] -- number of strings
//              ...               -- PWSTRs to string data
//
//  History:    1-03-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
DWORD
ReportServiceEvent(
    IN WORD EventType,
    IN DWORD EventId,
    IN DWORD SizeOfRawData,
    IN PVOID RawData,
    IN DWORD NumberOfStrings,
    ...
    )
{
    va_list arglist;
    ULONG i;
    PWSTR Strings[ MAX_EVENT_STRINGS ];
    DWORD rv;

    if (!hEventLog)
    {
        DebugLog((DEB_ERROR, "Cannot log event, no handle!\n"));
        return((DWORD)-1);
    }

    //
    // We're not supposed to be logging this, so nuke it
    //
    if ((LoggingLevel & (1 << EventType)) == 0)
    {
        return(0);
    }

    //
    // Look at the strings, if they were provided
    //
    va_start( arglist, NumberOfStrings );

    if (NumberOfStrings > MAX_EVENT_STRINGS) {
        NumberOfStrings = MAX_EVENT_STRINGS;
    }

    for (i=0; i<NumberOfStrings; i++) {
        Strings[ i ] = va_arg( arglist, PWSTR );
    }


    //
    // Report the event to the eventlog service
    //

    if (!ReportEvent(   hEventLog,
                        EventType,
                        0,            // event category
                        EventId,
                        NULL,
                        (WORD)NumberOfStrings,
                        SizeOfRawData,
                        Strings,
                        RawData) )
    {
        rv = GetLastError();
        DebugLog((DEB_ERROR,  "ReportEvent( %u ) failed - %u\n", EventId, GetLastError() ));

    }
    else
    {
        rv = ERROR_SUCCESS;
    }

    return rv;
}

BOOL
ShutdownEvents(void)
{
    return(DeregisterEventSource(hEventLog));
}
