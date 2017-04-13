/*++

Copyright 1996 - 1997 Microsoft Corporation

Module Name:

    server.c

Abstract:

    This sample illustrates the new DuplicateTokenEx() API for Windows NT 4.0.
    This portion of the sample illustrates how to implement a remote cmd
    server which launches cmd.exe in the security context of the client that
    connected to the server.

    When a client connects to the named-pipe, the server process impersonates
    the client and then saves a copy of the impersonation token.  This token
    is then duplicated via DuplicateTokenEx() to a primary level access token.
    The primary level token is then supplied to CreateProcessAsUser(), which
    launches a process in the security context of the client.  All threads in
    the new process inherit the security context of the client.  All processes
    created by the new process inherit the security context of the client.  The
    input and output of the new process will be redirected to the client over
    the named-pipes, which provides a means of interactively executing commands
    remotely in a secure manner.

    In order to allow processes to run in a different security context than
    the server process, it is necessary to adjust the security on the
    windowstation and desktop objects associated with the server process.
    This is required to allow for proper console initialization.

    For simplicity, this sample applies a Null Dacl to the windowstation and
    desktop objects, which is generally not appropriate in a production
    environment.  The best approach to selectively secure the windowstation and
    desktop objects is to extract the Logon Sid from the access token returned
    by DuplicateTokenEx().  The Logon Sid can be extracted with
    GetTokenInformation() and then added to an access allowed ace which is
    supplied in a Dacl which contains the existing access allowed aces in
    addition to the new access allowed ace.

    Some additional considerations with this sample follow:

    * The account which the server process runs in needs the following two
      privileges granted, to allow for the call to CreateProcessAsUser() to
      succeed:

      SeAssignPrimaryTokenPrivilege (Replace a process level token)
      SeIncreateQuotaPrivilege (Increase quotas)

    * The security on the initial server side named-pipe allows for Everyone
      to connect.  This may present security problems in the event that the
      server's file system has not be secured appropriately.  In a production
      environment, it may be appropriate to apply a more restrictive Dacl on
      the initial named-pipe.

    * This sample only allows one client to be connected at a time.

    * Any child processes started by the launched process will not be terminated
      when the initial child process exits.


Author:

    Scott Field (sfield)    02-Apr-96

--*/

#include <windows.h>
#include <stdio.h>

BOOL
BuildNamedPipeAcl(
    PACL pAcl,
    PDWORD cbAclSize
    );

BOOL
SetupNamedPipes(
    PSECURITY_ATTRIBUTES saInbound,
    PSECURITY_ATTRIBUTES saOutbound,
    PHANDLE hFileIn,
    PHANDLE hFileOut
    );

BOOL
SetWinstaDesktopSecurity(
    void
    );

void
DisplayLastError(
    LPSTR szAPI // pointer to Ansi function name
    );

//
// this defines the commandline that the server will execute in the security
// context of the client.  The /Q switch tells cmd.exe not to echo the
// entered commands back to the client.
//
#define COMMANDLINE     TEXT("cmd.exe /Q")

#define INBOUND_PIPE    TEXT("\\\\.\\pipe\\rcmd_in")
#define OUTBOUND_PIPE   TEXT("\\\\.\\pipe\\rcmd_out")

#define RTN_OK 0
#define RTN_ERROR 13

int
__cdecl
main(
    void
    )
{
    HANDLE hPipeInbound;
    HANDLE hPipeOutbound;

    SECURITY_ATTRIBUTES saInbound;
    SECURITY_DESCRIPTOR sd;

    BYTE AclBuf[ 64 ];
    DWORD cbAclSize = 64;
    PACL pAcl = (PACL)AclBuf;

    SECURITY_ATTRIBUTES saOutbound;

    HANDLE hImpersonationToken;
    HANDLE hPrimaryToken;

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    //
    // suppress errors regarding startup directory, etc
    //
    SetErrorMode(SEM_FAILCRITICALERRORS);

    //
    // build security attributes for named-pipes
    //
    // the inbound pipe will grant Everyone the ability to connect,
    // and the server process full control over the pipe.  This way,
    // only the server process has the ability to update security
    // on the resource; clients can only connect.
    //
    // the outbound pipe will be built after the server impersonates
    // the client, and will inherit the default security of the client
    // as a result.  This allows only the same user that connected to
    // the inbound pipe to connect to the outbound pipe
    //

    if(!BuildNamedPipeAcl(pAcl, &cbAclSize)) {
        DisplayLastError("BuildNamedPipeAcl");
        return RTN_ERROR;
    }

    if(!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION)) {
        DisplayLastError("InitializeSecurityDescriptor");
        return RTN_ERROR;
    }

    if(!SetSecurityDescriptorDacl(&sd, TRUE, pAcl, FALSE)) {
        DisplayLastError("SetSecurityDescriptorDacl");
        return RTN_ERROR;
    }

    saInbound.nLength = sizeof(SECURITY_ATTRIBUTES);
    saInbound.lpSecurityDescriptor = &sd;
    saInbound.bInheritHandle = TRUE;

    saOutbound.nLength = sizeof(SECURITY_ATTRIBUTES);
    saOutbound.lpSecurityDescriptor = NULL; // default Dacl of caller
    saOutbound.bInheritHandle = TRUE;

    //
    // modify security on windowstation and desktop to allow for correct
    // process and console initialization by arbitrary clients
    //
    if(!SetWinstaDesktopSecurity()) {
        DisplayLastError("SetWinstaDesktopSecurity");
        return RTN_ERROR;
    }

    while(1) {

    hPipeInbound = INVALID_HANDLE_VALUE;
    hPipeOutbound = INVALID_HANDLE_VALUE;
    hImpersonationToken = INVALID_HANDLE_VALUE;
    hPrimaryToken = INVALID_HANDLE_VALUE;
    pi.hProcess = INVALID_HANDLE_VALUE;
    pi.hThread = INVALID_HANDLE_VALUE;

    if(!SetupNamedPipes(
        &saInbound,
        &saOutbound,
        &hPipeInbound,
        &hPipeOutbound
        )) {

        //
        // just bail out on failure for now
        //
        DisplayLastError("SetupNamedPipes");
        break;
    }

    //
    // obtain the impersonation token from the current thread
    //
    if(!OpenThreadToken(
        GetCurrentThread(),
        TOKEN_DUPLICATE,
        TRUE,
        &hImpersonationToken
        )) {
        DisplayLastError("OpenThreadToken");
        goto cleanup;
    }

    //
    // duplicate the impersonation token to primary
    // since we are impersonating the client, the token will get the
    // default Dacl of the client
    //
    if(!DuplicateTokenEx(
        hImpersonationToken,
        TOKEN_IMPERSONATE | TOKEN_READ |
        TOKEN_ASSIGN_PRIMARY | TOKEN_DUPLICATE,
        NULL,
        SecurityImpersonation,
        TokenPrimary,
        &hPrimaryToken
        )) {
        DisplayLastError("DuplicateTokenEx");
        goto cleanup;
    }

    RevertToSelf();
    CloseHandle(hImpersonationToken);
    hImpersonationToken = INVALID_HANDLE_VALUE;

    //
    // setup STARTUPINFO structure
    //
    si.cb = sizeof(STARTUPINFO);
    si.lpReserved = NULL;
    si.lpDesktop = NULL;
    si.lpTitle = NULL;
    si.cbReserved2 = 0;
    si.lpReserved2 = NULL;
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = hPipeOutbound;
    si.hStdError = hPipeOutbound;
    si.hStdInput = hPipeInbound;

    //
    // create a process running as the user
    //

    if(!CreateProcessAsUser(
        hPrimaryToken,
        NULL,
        COMMANDLINE, // commandline to execute
        NULL,   // process sa
        NULL,   // thread sa
        TRUE,   // inherit handles?
        0,      // process creation flags (inherit existing console)
        NULL,   // environment
        NULL,   // current directory
        &si,    // startupinfo
        &pi     // processinfo
        )) {
        DisplayLastError("CreateProcessAsUser");
        goto cleanup;
    }

cleanup:

    if(hImpersonationToken != INVALID_HANDLE_VALUE) {
        RevertToSelf();
        CloseHandle(hImpersonationToken);
    }

    if(hPrimaryToken != INVALID_HANDLE_VALUE) {
        CloseHandle(hPrimaryToken);
    }

    if(pi.hThread != INVALID_HANDLE_VALUE) {
        CloseHandle(pi.hThread);
    }

    if(pi.hProcess != INVALID_HANDLE_VALUE) {
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);

        //
        // TODO kill any child by enumerating process tokens in the system
        // by looking at the tokenID
        //
    }

    if(hPipeInbound != INVALID_HANDLE_VALUE) {
        DisconnectNamedPipe(hPipeInbound);
        CloseHandle(hPipeInbound);
    }

    if(hPipeOutbound != INVALID_HANDLE_VALUE) {
        DisconnectNamedPipe(hPipeOutbound);
        CloseHandle(hPipeOutbound);
    }

    } // while

    return RTN_OK;
}

/***
 If the function succeeds, the return value is TRUE.  The parameters
 hFileIn and hFileOut will point to the Inbound and Outbound named-pipe
 handles.  The current thread will be impersonating the client.

 If the function fails, the return value is FALSE.  The current thread will
 not be impersonating the client.
***/
BOOL
SetupNamedPipes(
    PSECURITY_ATTRIBUTES saInbound, // security attributes for Inbound pipe
    PSECURITY_ATTRIBUTES saOutbound,// security attributes for Outbound pipe
    PHANDLE hFileIn,                // resultant Inbound pipe handle on success
    PHANDLE hFileOut                // resultant Outbound pipe handle on success
    )
{
    HANDLE hPipeInbound = INVALID_HANDLE_VALUE;
    HANDLE hPipeOutbound = INVALID_HANDLE_VALUE;

    BOOL bSuccess = FALSE; // assume this function fails

    //
    // create Inbound named-pipe
    //
    hPipeInbound = CreateNamedPipe(
        INBOUND_PIPE,
        PIPE_ACCESS_INBOUND,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1, // number of instances
        4096,
        4096,
        NMPWAIT_USE_DEFAULT_WAIT,
        saInbound
        );

    if(hPipeInbound == INVALID_HANDLE_VALUE) {
        DisplayLastError("CreateNamedPipe");
        return FALSE;
    }

    printf("Waiting for connection... ");

    //
    // wait for somebody to connect to the Inbound named pipe
    //
    ConnectNamedPipe(hPipeInbound, NULL);

    //
    // impersonate the client
    //
    if(!ImpersonateNamedPipeClient(hPipeInbound)) {
        DisplayLastError("ImpersonateNamedPipeClient");
        goto cleanup;
    }

    //
    // create Outbound named-pipe
    // the security on this named-pipe will be inherited from the default Dacl
    // of the client that just connected, because this pipe instance is
    // created in that users security context.  This prevents other users
    // from connecting to the Outbound pipe.
    //
    hPipeOutbound = CreateNamedPipe(
        OUTBOUND_PIPE,
        PIPE_ACCESS_OUTBOUND,
        PIPE_TYPE_MESSAGE | PIPE_WAIT,
        1, // number of instances
        4096,
        4096,
        NMPWAIT_USE_DEFAULT_WAIT,
        saOutbound
        );

    if(hPipeOutbound == INVALID_HANDLE_VALUE) {
        DisplayLastError("CreateNamedPipe");
        goto cleanup;
    }

    //
    // wait for the client to connect to the Outbound named pipe
    //
    ConnectNamedPipe(hPipeOutbound, NULL);

    printf("Client connected!\n");

    *hFileIn = hPipeInbound;
    *hFileOut = hPipeOutbound;

    bSuccess = TRUE;

cleanup:

    if(!bSuccess) {
        RevertToSelf();

        if(hPipeInbound != INVALID_HANDLE_VALUE)
            CloseHandle(hPipeInbound);
        if(hPipeOutbound != INVALID_HANDLE_VALUE)
            CloseHandle(hPipeOutbound);
    }

    return bSuccess;
}

/**
This function builds a Dacl which grants the creator of the objects
FILE_ALL_ACCESS and Everyone FILE_GENERIC_READ and FILE_GENERIC_WRITE
access to the object.

This Dacl allows for higher security than a NULL Dacl, which is common for
named-pipes, as this only grants the creator/owner write access to the
security descriptor, and grants Everyone the ability to "use" the named-pipe.
This scenario prevents a malevolent user from disrupting service by preventing
arbitrary access manipulation.
**/
BOOL
BuildNamedPipeAcl(
    PACL pAcl,
    PDWORD cbAclSize
    )
{
    DWORD dwAclSize;

    SID_IDENTIFIER_AUTHORITY siaWorld = SECURITY_WORLD_SID_AUTHORITY;
    SID_IDENTIFIER_AUTHORITY siaCreator = SECURITY_CREATOR_SID_AUTHORITY;

    BYTE BufEveryoneSid[32];
    BYTE BufOwnerSid[32];

    PSID pEveryoneSid = (PSID)BufEveryoneSid;
    PSID pOwnerSid = (PSID)BufOwnerSid;

    //
    // compute size of acl
    //
    dwAclSize = sizeof(ACL) +
        2 * ( sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) ) +
        GetSidLengthRequired( 1 ) + // well-known Everyone Sid
        GetSidLengthRequired( 1 ) ; // well-known Creator Owner Sid

    if(*cbAclSize < dwAclSize) {
        *cbAclSize = dwAclSize;
        return FALSE;
    }

    *cbAclSize = dwAclSize;

    //
    // intialize well known sids
    //

    if(!InitializeSid(pEveryoneSid, &siaWorld, 1)) return FALSE;
    *GetSidSubAuthority(pEveryoneSid, 0) = SECURITY_WORLD_RID;

    if(!InitializeSid(pOwnerSid, &siaCreator, 1)) return FALSE;
    *GetSidSubAuthority(pOwnerSid, 0) = SECURITY_CREATOR_OWNER_RID;

    if(!InitializeAcl(pAcl, dwAclSize, ACL_REVISION))
        return FALSE;

    //
    //
    if(!AddAccessAllowedAce(
        pAcl,
        ACL_REVISION,
        FILE_GENERIC_READ | FILE_GENERIC_WRITE,
        pEveryoneSid
        ))
        return FALSE;

    //
    //
    return AddAccessAllowedAce(
        pAcl,
        ACL_REVISION,
        FILE_ALL_ACCESS,
        pOwnerSid
        );
}

/**
This function adjusts the security on the current windowstation and desktop,
to allow arbitrary client to have access to the windowstation and desktop.
This is necessary to allow for correct process and console initialization.

Note that in a secure environment, it would be appropriate to create
a specific desktop and launch the process spawned by the client on that
desktop, rather than opening up the current desktop to the client.

This function simply applies a NULL Dacl to the current windowstation and
desktop in order to reduce the size of this sample.  Applying NULL Dacls
to objects is generally not a wise idea.

TODO revist this function later to better address security on the windowstation
and desktop.
**/
BOOL
SetWinstaDesktopSecurity(
    void
    )
{
    HWINSTA hWinsta;
    HDESK hDesk;

    SECURITY_INFORMATION si = DACL_SECURITY_INFORMATION;
    SECURITY_DESCRIPTOR sd;

    hWinsta = GetProcessWindowStation();
    if(hWinsta == NULL) return FALSE;

    hDesk = GetThreadDesktop(GetCurrentThreadId());
    if(hDesk == NULL) return FALSE;

    InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
    SetSecurityDescriptorDacl(&sd, TRUE, (PACL)NULL, FALSE);

    if(!SetUserObjectSecurity(hWinsta, &si, &sd)) return FALSE;

    return SetUserObjectSecurity(hDesk, &si, &sd);
}

void
DisplayLastError(
    LPSTR szAPI // pointer to Ansi function name
    )
{
    LPSTR MessageBuffer;
    DWORD dwBufferLength;

    //
    // TODO get this fprintf out of here!
    //
    fprintf(stderr,"%s error!\n", szAPI);

    if(dwBufferLength=FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR) &MessageBuffer,
            0,
            NULL
            ))
    {
        DWORD dwBytesWritten; // unused

        //
        // Output message string on stderr
        //
        WriteFile(
                GetStdHandle(STD_ERROR_HANDLE),
                MessageBuffer,
                dwBufferLength,
                &dwBytesWritten,
                NULL
                );

        //
        // free the buffer allocated by the system
        //
        LocalFree(MessageBuffer);
    }
}
