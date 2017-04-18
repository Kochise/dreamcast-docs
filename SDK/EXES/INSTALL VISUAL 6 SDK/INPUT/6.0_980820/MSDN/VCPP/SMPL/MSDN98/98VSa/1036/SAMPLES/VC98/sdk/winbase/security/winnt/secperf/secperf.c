/*++

Module Name:

    secperf.c

Abstract:

    This sample illustrates how to regulate access to the performance data
    provided by the registry key HKEY_PERFORMANCE_DATA.

    The security on the following registry key dictates which users or groups
    can gain access to the performance data:

    HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Perflib

    This sample opens the registry key for WRITE_DAC access, which allows
    for a new Dacl to be applied to the registry key.

    A Dacl is then built, which grants the following users access:

    Administrators are granted full control to allow for future updates to the
    security on the key and to allow for querying performance data.

    Interactively logged on users, through the well-known Interactive Sid,
    are granted KEY_READ access, which allows for querying performance
    data.

    The new Dacl is then applied to the registry key using the
    RegSetKeySecurity() Win32 API.

    This sample relies on the import library advapi32.lib.

Author:

    Scott Field (sfield)    19-Feb-96

--*/

#include <windows.h>
#include <stdio.h>

#define RTN_OK 0
#define RTN_ERROR 13

void
DisplayWinError(
    LPSTR szAPI,    // pointer to Ansi function name
    DWORD dwError   // DWORD WinError
    );

int
__cdecl
main(
    void
    )
{
    SID_IDENTIFIER_AUTHORITY sia = SECURITY_NT_AUTHORITY;
    PSID pInteractiveSid = NULL;
    PSID pAdministratorsSid = NULL;
    SECURITY_DESCRIPTOR sd;
    PACL pDacl = NULL;
    DWORD dwAclSize;
    HKEY hKey;
    LONG lRetCode;
    BOOL bSuccess = FALSE; // assume this function fails

    //
    // open the performance key for WRITE_DAC access
    //
    lRetCode = RegOpenKeyEx(
        HKEY_LOCAL_MACHINE,
       TEXT("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib"),
        0,
        WRITE_DAC,
        &hKey
        );

    if(lRetCode != ERROR_SUCCESS) {
        DisplayWinError("RegOpenKeyEx", lRetCode);
        return RTN_ERROR;
    }

    //
    // prepare a Sid representing any Interactively logged-on user
    //
    if(!AllocateAndInitializeSid(
        &sia,
        1,
        SECURITY_INTERACTIVE_RID,
        0, 0, 0, 0, 0, 0, 0,
        &pInteractiveSid
        )) {
        DisplayWinError("AllocateAndInitializeSid", GetLastError());
        goto cleanup;
    }

    //
    // preprate a Sid representing the well-known admin group
    //
    if(!AllocateAndInitializeSid(
        &sia,
        2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &pAdministratorsSid
        )) {
        DisplayWinError("AllocateAndInitializeSid", GetLastError());
        goto cleanup;
    }

    //
    // compute size of new acl
    //
    dwAclSize = sizeof(ACL) +
        2 * ( sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) ) +
        GetLengthSid(pInteractiveSid) +
        GetLengthSid(pAdministratorsSid) ;

    //
    // allocate storage for Acl
    //
    pDacl = (PACL)HeapAlloc(GetProcessHeap(), 0, dwAclSize);
    if(pDacl == NULL) goto cleanup;

    if(!InitializeAcl(pDacl, dwAclSize, ACL_REVISION)) {
        DisplayWinError("InitializeAcl", GetLastError());
        goto cleanup;
    }

    //
    // grant the Interactive Sid KEY_READ access to the perf key
    //
    if(!AddAccessAllowedAce(
        pDacl,
        ACL_REVISION,
        KEY_READ,
        pInteractiveSid
        )) {
        DisplayWinError("AddAccessAllowedAce", GetLastError());
        goto cleanup;
    }

    //
    // grant the Administrators Sid KEY_ALL_ACCESS access to the perf key
    //
    if(!AddAccessAllowedAce(
        pDacl,
        ACL_REVISION,
        KEY_ALL_ACCESS,
        pAdministratorsSid
        )) {
        DisplayWinError("AddAccessAllowedAce", GetLastError());
        goto cleanup;
    }

    if(!InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION)) {
        DisplayWinError("InitializeSecurityDescriptor", GetLastError());
        goto cleanup;
    }

    if(!SetSecurityDescriptorDacl(&sd, TRUE, pDacl, FALSE)) {
        DisplayWinError("SetSecurityDescriptorDacl", GetLastError());
        goto cleanup;
    }

    //
    // apply the security descriptor to the registry key
    //
    lRetCode = RegSetKeySecurity(
        hKey,
        (SECURITY_INFORMATION)DACL_SECURITY_INFORMATION,
        &sd
        );

    if(lRetCode != ERROR_SUCCESS) {
        DisplayWinError("RegSetKeySecurity", lRetCode);
        goto cleanup;
    }

    bSuccess = TRUE; // indicate success

cleanup:

    RegCloseKey(hKey);
    RegCloseKey(HKEY_LOCAL_MACHINE);

    //
    // free allocated resources
    //
    if(pDacl != NULL)
        HeapFree(GetProcessHeap(), 0, pDacl);

    if(pInteractiveSid != NULL)
        FreeSid(pInteractiveSid);

    if(pAdministratorsSid != NULL)
        FreeSid(pAdministratorsSid);

    if(bSuccess) {
        printf("SUCCESS updating performance data security\n");
        return RTN_OK;
    } else {
        printf("ERROR updating performance data security\n");
        return RTN_ERROR;
    }
}

void
DisplayWinError(
    LPSTR szAPI,    // pointer to Ansi function name
    DWORD dwError   // DWORD WinError
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
            dwError,
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
