/*++

Copyright 1996 - 1997 Microsoft Corporation

Module Name:

    ginastub.c

Abstract:

    This sample illustrates a pass-thru "stub" gina which can be used
    in some cases to simplify gina development.

    A common use for a gina is to implement code which requires the
    credentials of the user logging onto the workstation.  The credentials
    may be required for syncronization with foreign account databases
    or custom authentication activities.

    In this example case, it is possible to implement a simple gina
    stub layer which simply passes control for the required functions
    to the previously installed gina, and captures the interesting
    parameters from that gina.  In this scenario, the existing functionality
    in the existent gina is retained.  In addition, the development time
    is reduced drastically, as existing functionality does not need to
    be duplicated.

    When dealing with credentials, take steps to maintain the security
    of the credentials.  For instance, if transporting credentials over
    a network, be sure to encrypt the credentials.

Author:

    Scott Field (sfield)    18-Jul-96

--*/

#include <windows.h>
#include <stdio.h>
#include <winwlx.h>

#include "ginastub.h"

//
// Location of the real msgina.
//

#define REALGINA_PATH   TEXT("MSGINA.DLL")


//
// winlogon function dispatch table
//

PWLX_DISPATCH_VERSION_1_0 g_pWinlogon;

//
// Functions pointers to the real msgina which we will call.
//

PGWLXNEGOTIATE GWlxNegotiate;
PGWLXINITIALIZE GWlxInitialize;
PGWLXDISPLAYSASNOTICE GWlxDisplaySASNotice;
PGWLXLOGGEDOUTSAS GWlxLoggedOutSAS;
PGWLXACTIVATEUSERSHELL GWlxActivateUserShell;
PGWLXLOGGEDONSAS GWlxLoggedOnSAS;
PGWLXDISPLAYLOCKEDNOTICE GWlxDisplayLockedNotice;
PGWLXWKSTALOCKEDSAS GWlxWkstaLockedSAS;
PGWLXISLOCKOK GWlxIsLockOk;
PGWLXISLOGOFFOK GWlxIsLogoffOk;
PGWLXLOGOFF GWlxLogoff;
PGWLXSHUTDOWN GWlxShutdown;

//
// NEW for version 1.1
//

PGWLXSTARTAPPLICATION GWlxStartApplication;
PGWLXSCREENSAVERNOTIFY GWlxScreenSaverNotify;

//
// hook into the real GINA.
//

BOOL
MyInitialize( void )
{
    HINSTANCE hDll;

    //
    // Load MSGINA.DLL.
    //
    if( !(hDll = LoadLibrary( REALGINA_PATH )) ) {
        return FALSE;
    }

    //
    // Get pointers to all of the WLX functions in the real MSGINA.
    //
    GWlxNegotiate = (PGWLXNEGOTIATE)GetProcAddress( hDll, "WlxNegotiate" );
    if( !GWlxNegotiate ) {
        return FALSE;
    }

    GWlxInitialize = (PGWLXINITIALIZE)GetProcAddress( hDll, "WlxInitialize" );
    if( !GWlxInitialize ) {
        return FALSE;
    }

    GWlxDisplaySASNotice =
        (PGWLXDISPLAYSASNOTICE)GetProcAddress( hDll, "WlxDisplaySASNotice" );
    if( !GWlxDisplaySASNotice ) {
        return FALSE;
    }

    GWlxLoggedOutSAS =
        (PGWLXLOGGEDOUTSAS)GetProcAddress( hDll, "WlxLoggedOutSAS" );
    if( !GWlxLoggedOutSAS ) {
        return FALSE;
    }

    GWlxActivateUserShell =
        (PGWLXACTIVATEUSERSHELL)GetProcAddress( hDll, "WlxActivateUserShell" );
    if( !GWlxActivateUserShell ) {
        return FALSE;
    }

    GWlxLoggedOnSAS =
        (PGWLXLOGGEDONSAS)GetProcAddress( hDll, "WlxLoggedOnSAS" );
    if( !GWlxLoggedOnSAS ) {
        return FALSE;
    }

    GWlxDisplayLockedNotice =
        (PGWLXDISPLAYLOCKEDNOTICE)GetProcAddress(
                                        hDll,
                                        "WlxDisplayLockedNotice" );
    if( !GWlxDisplayLockedNotice ) {
        return FALSE;
    }

    GWlxIsLockOk = (PGWLXISLOCKOK)GetProcAddress( hDll, "WlxIsLockOk" );
    if( !GWlxIsLockOk ) {
        return FALSE;
    }

    GWlxWkstaLockedSAS =
        (PGWLXWKSTALOCKEDSAS)GetProcAddress( hDll, "WlxWkstaLockedSAS" );
    if( !GWlxWkstaLockedSAS ) {
        return FALSE;
    }

    GWlxIsLogoffOk = (PGWLXISLOGOFFOK)GetProcAddress( hDll, "WlxIsLogoffOk" );
    if( !GWlxIsLogoffOk ) {
        return FALSE;
    }

    GWlxLogoff = (PGWLXLOGOFF)GetProcAddress( hDll, "WlxLogoff" );
    if( !GWlxLogoff ) {
        return FALSE;
    }

    GWlxShutdown = (PGWLXSHUTDOWN)GetProcAddress( hDll, "WlxShutdown" );
    if( !GWlxShutdown ) {
        return FALSE;
    }

    //
    // we don't check for failure here because these don't exist for
    // gina's implemented prior to Windows NT 4.0
    //

    GWlxStartApplication = (PGWLXSTARTAPPLICATION) GetProcAddress( hDll, "WlxStartApplication" );
    GWlxScreenSaverNotify = (PGWLXSCREENSAVERNOTIFY) GetProcAddress( hDll, "WlxScreenSaverNotify" );

    //
    // Everything loaded ok.  Return success.
    //
    return TRUE;
}


BOOL
WINAPI
WlxNegotiate(
    DWORD       dwWinlogonVersion,
    DWORD       *pdwDllVersion)
{
    if( !MyInitialize() )
        return FALSE;

    return GWlxNegotiate( dwWinlogonVersion, pdwDllVersion );
}


BOOL
WINAPI
WlxInitialize(
    LPWSTR      lpWinsta,
    HANDLE      hWlx,
    PVOID       pvReserved,
    PVOID       pWinlogonFunctions,
    PVOID       *pWlxContext)
{
    return GWlxInitialize(
                lpWinsta,
                hWlx,
                pvReserved,
                pWinlogonFunctions,
                pWlxContext
                );
}


VOID
WINAPI
WlxDisplaySASNotice(
    PVOID   pWlxContext)
{
    GWlxDisplaySASNotice( pWlxContext );
}


int
WINAPI
WlxLoggedOutSAS(
    PVOID           pWlxContext,
    DWORD           dwSasType,
    PLUID           pAuthenticationId,
    PSID            pLogonSid,
    PDWORD          pdwOptions,
    PHANDLE         phToken,
    PWLX_MPR_NOTIFY_INFO    pMprNotifyInfo,
    PVOID           *pProfile)
{
    int iRet;

    iRet = GWlxLoggedOutSAS(
                pWlxContext,
                dwSasType,
                pAuthenticationId,
                pLogonSid,
                pdwOptions,
                phToken,
                pMprNotifyInfo,
                pProfile
                );

    if(iRet == WLX_SAS_ACTION_LOGON) {
        //
        // copy pMprNotifyInfo and pLogonSid for later use
        //

        // pMprNotifyInfo->pszUserName
        // pMprNotifyInfo->pszDomain
        // pMprNotifyInfo->pszPassword
        // pMprNotifyInfo->pszOldPassword

    }

    return iRet;
}


BOOL
WINAPI
WlxActivateUserShell(
    PVOID           pWlxContext,
    PWSTR           pszDesktopName,
    PWSTR           pszMprLogonScript,
    PVOID           pEnvironment)
{
    return GWlxActivateUserShell(
                pWlxContext,
                pszDesktopName,
                pszMprLogonScript,
                pEnvironment
                );
}


int
WINAPI
WlxLoggedOnSAS(
    PVOID           pWlxContext,
    DWORD           dwSasType,
    PVOID           pReserved)
{
    return GWlxLoggedOnSAS( pWlxContext, dwSasType, pReserved );
}

VOID
WINAPI
WlxDisplayLockedNotice(
    PVOID           pWlxContext )
{
    GWlxDisplayLockedNotice( pWlxContext );
}


BOOL
WINAPI
WlxIsLockOk(
    PVOID           pWlxContext)
{
    return GWlxIsLockOk( pWlxContext );
}


int
WINAPI
WlxWkstaLockedSAS(
    PVOID           pWlxContext,
    DWORD           dwSasType )
{
    return GWlxWkstaLockedSAS( pWlxContext, dwSasType );
}

BOOL
WINAPI
WlxIsLogoffOk(
    PVOID pWlxContext
    )
{
    BOOL bSuccess;

    bSuccess = GWlxIsLogoffOk( pWlxContext );

    if(bSuccess) {

        //
        // if it's ok to logoff, finish with the stored credentials
        // and scrub the buffers
        //

    }

    return bSuccess;
}


VOID
WINAPI
WlxLogoff(
    PVOID pWlxContext
    )
{
    GWlxLogoff( pWlxContext );
}


VOID
WINAPI
WlxShutdown(
    PVOID pWlxContext,
    DWORD ShutdownType
    )
{
    GWlxShutdown( pWlxContext, ShutdownType );
}


//
// NEW for version 1.1
//

BOOL
WINAPI
WlxScreenSaverNotify(
    PVOID                   pWlxContext,
    BOOL *                  pSecure
    )
{
    if(GWlxScreenSaverNotify != NULL)
        return GWlxScreenSaverNotify( pWlxContext, pSecure );

    //
    // if not exported, return something intelligent
    //

    *pSecure = TRUE;

    return TRUE;
}

BOOL
WINAPI
WlxStartApplication(
    PVOID                   pWlxContext,
    PWSTR                   pszDesktopName,
    PVOID                   pEnvironment,
    PWSTR                   pszCmdLine
    )
{
    if(GWlxStartApplication != NULL)
        return GWlxStartApplication(
            pWlxContext,
            pszDesktopName,
            pEnvironment,
            pszCmdLine
            );

    //
    // if not exported, return something intelligent
    //

}

