/*++

Copyright 1996 - 1997 Microsoft Corporation

Module Name:

    nullsess.c

Abstract:

    This module illustrates how to use a Null session to overcome access
    problems during network related query operations.

    One example of the scenario this approach addresses is as follows:

    User logs onto workstation A as the local administrator.

    Administrator tries to query user information using the NetUserGetInfo()
    API call on server B.  This call fails with ERROR_ACCESS_DENIED.

    The reason this problem occurs is that the administrator password on
    workstation A does not match the administrator password on server B.

    During the network query operation, the default behavior is to establish
    a connection to the remote server using the credentials of the logged-in
    user.  In some scenarios, this behavior is not appropriate, and the
    solution is to establish a connection using either known credentials,
    or the Null credentials.  Null credentials are suitable for most query
    operations against a remote machine.  However, if administrator
    related actions are necessary, it is necessary to supply credentials
    which have administrative privilege on the remote machine.  Valid
    credentials consist of a username, password, and optional domain name.

    Establishing a connection in this manner requires that no existing
    connections exist to the remote machine tied to the current logon
    session.

    Note: Null sessions are those where the user credentials passed in the
    session setup SMB are null.  This sample only implements a function to
    establish a Null session, rather than a session with specific credentials.

    Processes and Services running in the Local System account security context
    have Null credentials by default, so establishing Null sessions in this
    scenario is not required.

    Applications that run only on Windows NT 4.0 and above can use
    WNetAddConnection2() rather than NetUseAdd() to establish a Null session.

Author:

    Scott Field (sfield)    13-Jun-96

--*/

#include <windows.h>
#include <lm.h>

#include <stdio.h>

BOOL
EstablishNullSession(
    LPCWSTR Server,
    BOOL bEstablish
    );

#define RTN_OK 0
#define RTN_USAGE 1
#define RTN_ERROR 13

int
__cdecl
wmain(
    int argc,
    wchar_t *argv[]
    )
{

    if(argc != 2) {
        printf("Usage: %ls <\\\\Server>\n", argv[0]);
        return RTN_USAGE;
    }

    //
    // try network operation here.  If this fails with an access denied
    // error message, retry the operation using a Null session.
    //

    //
    // establish a session to the target machine with Null credentials
    //

    if(EstablishNullSession( argv[1], TRUE )) {

        //
        // retry network related operation here.
        //

        //
        // break the existing connection we made
        //

        EstablishNullSession( argv[1], FALSE );
    } else {

        //
        // error occurred establishing Null session
        //

        printf("Error establishing Null session! (rc=%lu)\n", GetLastError());
        return RTN_ERROR;
    }

    return RTN_OK;
}

BOOL
EstablishNullSession(
    LPCWSTR Server,
    BOOL bEstablish
    )
{
    LPCWSTR szIpc = L"\\IPC$";
    WCHAR RemoteResource[UNCLEN + 5 + 1]; // UNC len + \IPC$ + NULL
    DWORD cchServer;

    NET_API_STATUS nas;

    //
    // do not allow NULL or empty server name
    //

    if(Server == NULL || *Server == L'\0') {
        SetLastError(ERROR_INVALID_COMPUTERNAME);
        return FALSE;
    }

    cchServer = lstrlenW( Server );

    if(Server[0] != L'\\' && Server[1] != L'\\') {

        //
        // prepend slashes and NULL terminate
        //

        RemoteResource[0] = L'\\';
        RemoteResource[1] = L'\\';
        RemoteResource[2] = L'\0';
    }
    else {
        cchServer -= 2; // drop slashes from count

        RemoteResource[0] = L'\0';
    }

    if(cchServer > CNLEN) {
        SetLastError(ERROR_INVALID_COMPUTERNAME);
        return FALSE;
    }

    if(lstrcatW(RemoteResource, Server) == NULL) return FALSE;
    if(lstrcatW(RemoteResource, szIpc) == NULL) return FALSE;

    //
    // disconnect or connect to the resource, based on bEstablish
    //

    if(bEstablish) {
        USE_INFO_2 ui2;

        ZeroMemory(&ui2, sizeof(ui2));

        ui2.ui2_local = NULL;
        ui2.ui2_remote = (LPTSTR) RemoteResource;
        ui2.ui2_asg_type = USE_IPC;
        ui2.ui2_password = ui2.ui2_username = ui2.ui2_domainname = (LPTSTR) L"";

        nas = NetUseAdd(NULL, 2, (LPBYTE)&ui2, NULL);
    }
    else {
        nas = NetUseDel(NULL, (LPTSTR) RemoteResource, 0);
    }

    if( nas == NERR_Success ) return TRUE; // indicate success

    SetLastError( nas );

    return FALSE;
}
