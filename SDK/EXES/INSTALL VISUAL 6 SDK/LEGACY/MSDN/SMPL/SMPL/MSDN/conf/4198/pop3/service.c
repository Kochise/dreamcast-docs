//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992 - 1993.
//
//  File:       service.c
//
//  Contents:
//
//  Classes:
//
//  Functions:
//
//  History:    12-12-94   RichardW   Created
//
//----------------------------------------------------------------------------

#include "pop3srvp.h"
#pragma hdrstop

SERVICE_STATUS_HANDLE   hService = 0;
WCHAR                   wszServiceName[] = APPLICATION_NAME;
SERVICE_STATUS          ServiceStatus;

extern  BOOLEAN fService;
extern  BOOLEAN fTestMode;

SOCKET sListener;
HANDLE  hCompletionPort;
WSADATA WsaData;
BOOL bServiceTerminating = FALSE;

//+---------------------------------------------------------------------------
//
//  Function:   ServiceControlHandler
//
//  Synopsis:   Handles requests from the service controller.
//
//  Arguments:  [fdwControl] -- Request code
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
VOID
WINAPI
ServiceControlHandler(
    DWORD           fdwControl)
{
    switch (fdwControl)
    {
        case SERVICE_CONTROL_STOP:

            UpdateServiceStatus(SERVICE_STOP_PENDING);

            //
            // Remember that the service is terminating.
            //

            bServiceTerminating = TRUE;

            //
            // Close the completion port and the listening socket.
            // These actions will cause the other threads to exit.
            //

            closesocket( sListener );
            CloseHandle( hCompletionPort );

            UpdateServiceStatus(SERVICE_STOPPED);
            return;

        case SERVICE_CONTROL_INTERROGATE:
            UpdateServiceStatus(ServiceStatus.dwCurrentState);
            return;

        default:
            return;
    }

}

//+---------------------------------------------------------------------------
//
//  Function:   NotifyServiceController
//
//  Synopsis:   Notifies the service controller of our control entry point,
//              and tells it that we're trying to start up.
//
//  Arguments:  (none)
//
//  Algorithm:
//
//  History:    1-11-95   RichardW   Created
//
//  Notes:
//
//----------------------------------------------------------------------------
BOOL
NotifyServiceController(
            VOID)
{
    if (!fService)
    {
        return(TRUE);
    }
    ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    ServiceStatus.dwWin32ExitCode = 0;
    ServiceStatus.dwServiceSpecificExitCode = 0;
    ServiceStatus.dwCheckPoint = 0;
    ServiceStatus.dwWaitHint = 0;

    hService = RegisterServiceCtrlHandler(wszServiceName, ServiceControlHandler);

    if (hService)
    {
        UpdateServiceStatus(SERVICE_START_PENDING);
        return(TRUE);
    }
    else
        return(FALSE);

}

BOOL
UpdateServiceStatus(DWORD   Status)
{
    if (hService)
    {
        ServiceStatus.dwCurrentState = Status;
        if ((Status == SERVICE_START_PENDING) || (Status == SERVICE_STOP_PENDING))
        {
            ServiceStatus.dwCheckPoint ++;
            ServiceStatus.dwWaitHint = 5000;    // 5 sec.
        }
        else
        {
            ServiceStatus.dwCheckPoint = 0;
            ServiceStatus.dwWaitHint = 0;
        }

        return(SetServiceStatus(hService, &ServiceStatus));
    }

    return(FALSE);
}

void
FailServiceStart(
    DWORD           Win32Code,
    DWORD           PrivateCode)
{
    ServiceStatus.dwWin32ExitCode = Win32Code;
    ServiceStatus.dwServiceSpecificExitCode = PrivateCode;
    UpdateServiceStatus(SERVICE_STOPPED);

}

void
WINAPI
Pop3SrvMain(
    DWORD       argc,
    LPTSTR      argv[])
{
    int error;

    if (!NotifyServiceController())
    {
        DebugLog((DEB_ERROR, "Could not contact service controller\n"));
        return;
    }

    if (!InitializeEvents())
    {
        DebugLog((DEB_ERROR, "Could not initialize events\n"));
        FailServiceStart(GetLastError(), 0);
        return;
    }

    UpdateServiceStatus(SERVICE_START_PENDING);

    if (!ReadParameters())
    {
        DebugLog((DEB_ERROR, "Could not read parameters!\n"));
        FailServiceStart(GetLastError(), 0);
        return;
    }

    UpdateServiceStatus(SERVICE_START_PENDING);


    ReportServiceEvent(
        EVENTLOG_INFORMATION_TYPE,
        POP3EVENT_SERVICE_STARTED,
        0, NULL, 0);


    if (fTestMode)
    {
        TestLoop();
    }
    else
    {

        error = WSAStartup( 0x0101, &WsaData );
        if ( error == SOCKET_ERROR ) {
            printf( "WSAStartup failed.\n" );
        }

        UpdateServiceStatus(SERVICE_START_PENDING);

        //
        // Initialize the POP3SRV worker threads.
        //

        hCompletionPort = InitializeThreads( );
        if ( hCompletionPort == NULL ) {
            printf( "it failed.\n" );
        }

        UpdateServiceStatus(SERVICE_RUNNING);

        //
        // Start accepting and processing clients.
        //

        AcceptClients( hCompletionPort );
    }
}
