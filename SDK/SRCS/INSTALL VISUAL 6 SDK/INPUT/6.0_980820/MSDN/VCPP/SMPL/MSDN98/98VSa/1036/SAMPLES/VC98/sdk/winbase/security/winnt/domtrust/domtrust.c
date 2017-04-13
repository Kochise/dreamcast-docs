/*++

Copyright 1996 - 1997 Microsoft Corporation

Module Name:

    domtrust.c

Abstract:

    This sample illustrates how to manage Windows NT trusted domains at the
    domain controller level.

    The first command line argument indicates the name of the new or existing
    trusted domain to create or modify.

    The second command line argument indicates the new password for the
    trusted domain specified in the first argument.

    The optional third argument indicates the domain name that is the target
    of the trusted domain update operation. If this argument is not specified,
    the update will occur on the local domain. Note that this sample will not
    allow a trusted domain update to occur on a non-domain controller.

    This sample works correctly compiled ANSI or Unicode. Note that LAN
    Manager NetXxx API are Unicode only, and Windows NT LSA API are Unicode
    only.

Author:

    Scott Field (sfield)    05-Feb-96

--*/

#ifndef UNICODE
#define UNICODE
#define _UNICODE
#endif

#include <windows.h>
#include <lm.h>         // for NetXxx API

#include "ntsecapi.h"   // \mstools\samples\win32\winnt\security\include\ntsecapi.h

#include <stdio.h>

void
InitLsaString(
    PLSA_UNICODE_STRING LsaString,
    LPWSTR String
    );

NTSTATUS
OpenPolicy(
    LPWSTR ServerName,
    DWORD DesiredAccess,
    PLSA_HANDLE PolicyHandle
    );

BOOL
GetDomainSid(
    LPWSTR DomainName,  // domain name to acquire Sid of
    PSID *pDomainSid    // points to allocated Sid on success
    );

NTSTATUS
SetTrustedDomainInfo(
    LSA_HANDLE PolicyHandle,
    PSID DomainSid,             // Sid of domain to manipulate
    LPWSTR TrustedDomainName,   // trusted domain name to add/update
    LPWSTR Password             // new trust password for trusted domain
    );

BOOL
VerifyTrustRelationship(
    LPWSTR TargetDomainName,        // domain name to verify trust at
    LPWSTR TrustAccountToVerify,    // trusted domain name to verify
    LPWSTR Password,                // password associated with trust
    LPBOOL bTrustVerified           // indicates if trust was verified
    );

void
DisplayNtStatus(
    LPSTR szAPI,    // ANSI string containing API name
    NTSTATUS Status
    );

void
DisplayError(
    LPSTR szAPI,    // pointer to failed API name
    DWORD dwLastError
    );

#define RTN_OK 0
#define RTN_USAGE 1
#define RTN_ERROR 13

//
// if you have the DDK, include Ntstatus.h
//
#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS                  ((NTSTATUS)0x00000000L)
#define STATUS_OBJECT_NAME_NOT_FOUND    ((NTSTATUS)0xC0000034L)
#define STATUS_INVALID_SID              ((NTSTATUS)0xC0000078L)
#endif

//
// Unicode entry point and argv
//

int
__cdecl
wmain(
    int argc,
    wchar_t *argv[]
    )
{
    BOOL bAllocTargetDomain;    // did you allocate memory for target?
    LSA_HANDLE PolicyHandle;
    LPWSTR TargetDomainName;    // target domain of policy update
    LPWSTR DomainController;    // computer name where policy update
    PSID DomainSid; // allocated Sid representing domain to trust
    LPWSTR TrustedDomainName;
    LPWSTR Password;
    BOOL bTrustVerified;
    NET_API_STATUS nas;
    NTSTATUS Status;

    if(argc < 3) {
        fprintf(stderr,
            "Usage: %ls <NewTrustedDomain> <Password> [TargetDomain]\n",
            argv[0]);
        return RTN_USAGE;
    }

    TrustedDomainName = argv[1];    // existing or new TrustedDomain
    Password = argv[2];             // new password for TrustedDomain

    //
    // if a TargetDomain was specified, point to that.
    // if not, set TargetDomain to the current domain if a DC.
    //
    if(argc == 4 && *argv[3] != L'\0') {
        TargetDomainName = argv[3]; // domain to update trust at
        bAllocTargetDomain = FALSE; // no memory allocated
    }
    else {
        PSERVER_INFO_101 si101;
        DWORD Type;
        PUSER_MODALS_INFO_2 umi2;

        //
        // ensure that the local computer is a DC. This operation is only
        // appropriate against a domain controller.
        //
        nas = NetServerGetInfo(NULL, 101, (LPBYTE *)&si101);
        if(nas != NERR_Success) {
            DisplayError("NetServerGetInfo", nas);
            return RTN_ERROR;
        }

        Type = si101->sv101_type;
        NetApiBufferFree(si101);

        if( !(Type & SV_TYPE_DOMAIN_CTRL) &&
            !(Type & SV_TYPE_DOMAIN_BAKCTRL) ) {
            printf("Error:  Specify a TargetDomain; this operation"
                    " is only valid against a domain.\n");
            return RTN_ERROR;
        }

        //
        // obtain the local computer's domain name
        //
        nas = NetUserModalsGet(NULL, 2, (LPBYTE *)&umi2);

        if(nas != NERR_Success) {
            DisplayError("NetUserModalsGet", nas);
            return RTN_ERROR;
        }

        //
        // copy the domain name to new storage
        //
        TargetDomainName = (LPWSTR)HeapAlloc(GetProcessHeap(), 0,
            (lstrlenW(umi2->usrmod2_domain_name) + 1) * sizeof(WCHAR));

        if(TargetDomainName != NULL) {
            lstrcpyW(TargetDomainName, umi2->usrmod2_domain_name);
            bAllocTargetDomain = TRUE; // we allocated memory
        }

        NetApiBufferFree(umi2); // free memory allocated by NetXxx

        //
        // if an error occurred allocating memory, exit
        //
        if(TargetDomainName == NULL) {
            DisplayError("HeapAlloc", 0);
            return RTN_ERROR;
        }
    }

    //
    // do not allow a Domain to trust itself
    //
    if(lstrcmpiW(TargetDomainName, TrustedDomainName) == 0) {
        fprintf(stderr,"Error:  Domain %ls cannot trust itself.\n",
            TargetDomainName);

        return RTN_ERROR;
    }

    //
    // ensure Password and TrustedDomainName are the correct length
    //
    if(lstrlenW(Password) > LM20_PWLEN)
        Password[LM20_PWLEN] = L'\0'; // truncate

    if(lstrlenW(TrustedDomainName) > MAX_COMPUTERNAME_LENGTH)
        TrustedDomainName[MAX_COMPUTERNAME_LENGTH] = L'\0'; // truncate

    //
    // obtain the primary DC computer name from the specified
    // TargetDomainName
    //
    nas = NetGetDCName(
        NULL, TargetDomainName, (LPBYTE *)&DomainController);

    if(nas != NERR_Success) {
        DisplayError("NetGetDCName", nas);
        return RTN_ERROR;
    }

    //
    // verify the trust relationship
    //
    if(!VerifyTrustRelationship(
        TrustedDomainName,
        TargetDomainName,   // trust account to verify
        Password,
        &bTrustVerified
        )) {
        //
        // an error occurred during trust relationship verification
        //
        DisplayError("VerifyTrustRelationship", GetLastError());
    }
    else {
        //
        // inform the user if the trust was not verified
        //
        if(!bTrustVerified) {
            DWORD dwTrustVerifyFailReason = GetLastError();

            //
            // You could exit here, but this is optional. Reasons for
            // trust verification failure could be non-existent
            // "permitted to trust" on the verified domain (rc=1317),
            // wrong password (rc=1326), etc
            //
            printf("Warning:  ");

            switch(dwTrustVerifyFailReason) {
                case ERROR_NO_SUCH_USER:
                    printf("%ls not permitted-to-trust on %ls\n",
                        TargetDomainName, TrustedDomainName);
                    break;

                case ERROR_LOGON_FAILURE:
                    printf("Trust %ls has incorrect password on %ls\n",
                        TrustedDomainName, TargetDomainName);
                    break;

                default:
                    DisplayError("Trust was not verified.  Non-fatal",
                        dwTrustVerifyFailReason);
            } // switch
        }
    }

    //
    // fetch the DomainSid of the domain to trust
    //
    if(!GetDomainSid(TrustedDomainName, &DomainSid)) {
        DisplayError("GetDomainSid", GetLastError());
        return RTN_ERROR;
    }

    //
    // open the policy on the target domain
    //
    Status = OpenPolicy(
                DomainController,
                POLICY_CREATE_SECRET |  // for password set operation
                POLICY_TRUST_ADMIN,     // for trust creation
                &PolicyHandle
                );

    if(Status != STATUS_SUCCESS) {
        DisplayNtStatus("OpenPolicy", Status);
        return RTN_ERROR;
    }

    //
    // Update TrustedDomainInfo to reflect the specified trust.
    //
    Status = SetTrustedDomainInfo(
        PolicyHandle,
        DomainSid,
        TrustedDomainName,
        Password
        );

    if(Status != STATUS_SUCCESS) {
        DisplayNtStatus("SetTrustedDomainInfo", Status);
        return RTN_ERROR;
    }

    //
    // if you allocated memory for TargetDomainName, free it
    //
    if(bAllocTargetDomain)
        HeapFree(GetProcessHeap(), 0, TargetDomainName);

    //
    // free the Sid which was allocated for the TrustedDomain Sid
    //
    FreeSid(DomainSid);

    //
    // close the policy handle
    //
    LsaClose(PolicyHandle);

    if(DomainController != NULL)
        NetApiBufferFree(DomainController);

    return RTN_OK;
}

void
InitLsaString(
    PLSA_UNICODE_STRING LsaString,
    LPWSTR String
    )
{
    DWORD StringLength;

    if(String == NULL) {
        LsaString->Buffer = NULL;
        LsaString->Length = 0;
        LsaString->MaximumLength = 0;

        return;
    }

    StringLength = lstrlenW(String);
    LsaString->Buffer = String;
    LsaString->Length = (USHORT) StringLength * sizeof(WCHAR);
    LsaString->MaximumLength = (USHORT) (StringLength + 1) *
        sizeof(WCHAR);
}

NTSTATUS
OpenPolicy(
    LPWSTR ServerName,
    DWORD DesiredAccess,
    PLSA_HANDLE PolicyHandle
    )
{
    LSA_OBJECT_ATTRIBUTES ObjectAttributes;
    LSA_UNICODE_STRING ServerString;
    PLSA_UNICODE_STRING Server;

    //
    // Always initialize the object attributes to all zeroes
    //
    ZeroMemory(&ObjectAttributes, sizeof(ObjectAttributes));

    if(ServerName != NULL) {
        //
        // Make a LSA_UNICODE_STRING out of the LPWSTR passed in
        //
        InitLsaString(&ServerString, ServerName);

        Server = &ServerString;
    } else {
        Server = NULL;
    }

    //
    // Attempt to open the policy
    //
    return LsaOpenPolicy(
                Server,
                &ObjectAttributes,
                DesiredAccess,
                PolicyHandle
                );
}

/*++
 This function retrieves the Sid representing the specified DomainName.

 If the function succeeds, the return value is TRUE and pDomainSid will
 point to the Sid representing the specified DomainName. The caller
 should free the memory associated with this Sid with the Win32 API
 FreeSid() when the Sid is no longer needed.

 If the function fails, the return value is FALSE, and pDomainSid will
 be set to NULL.

--*/

BOOL
GetDomainSid(
    LPWSTR DomainName,  // domain name to acquire Sid of
    PSID *pDomainSid    // points to allocated Sid on success
    )
{
    NET_API_STATUS nas;
    LPWSTR DomainController;
    PUSER_MODALS_INFO_2 umi2 = NULL;
    DWORD dwSidSize;
    BOOL bSuccess = FALSE; // assume this function will fail

    *pDomainSid = NULL; // invalidate pointer

    //
    // obtain the PDC computer name of the supplied domain name
    //
    nas = NetGetDCName(NULL, DomainName, (LPBYTE *)&DomainController);
    if(nas != NERR_Success) {
        SetLastError(nas);
        return FALSE;
    }

    __try {

    //
    // obtain the domain Sid from the PDC
    // NOTE: this may fail if the credentials of the caller are not
    // recognized or valid on the target computer. In this case, it
    // is necessary to first establish a connection via NetUseAdd()
    // at info-level 2 to the remote IPC$, specifying EMPTY
    // credentials.
    //
    nas = NetUserModalsGet(DomainController, 2, (LPBYTE *)&umi2);
    if(nas != NERR_Success) __leave;

    //
    // if the Sid is valid, obtain the size of the Sid
    //
    if(!IsValidSid(umi2->usrmod2_domain_id)) __leave;
    dwSidSize = GetLengthSid(umi2->usrmod2_domain_id);

    //
    // allocate storage and copy the Sid
    //
    *pDomainSid = (PSID)HeapAlloc(GetProcessHeap(), 0, dwSidSize);
    if(*pDomainSid == NULL) __leave;

    if(!CopySid(dwSidSize, *pDomainSid, umi2->usrmod2_domain_id))
        __leave;

    bSuccess = TRUE; // indicate success

    } // try
    __finally {

    //
    // free allocated memory
    //
    NetApiBufferFree(DomainController);

    if(umi2 != NULL)
        NetApiBufferFree(umi2);

    if(!bSuccess) {
        //
        // if the function failed, free memory and indicate result code
        //

        if(*pDomainSid != NULL) {
            FreeSid(*pDomainSid);
            *pDomainSid = NULL;
        }

        if(nas != NERR_Success) {
            SetLastError(nas);
        }
    }

    }
    return bSuccess;
}

/*++
 This function manipulates the trust associated with the supplied
 DomainSid.

 If the domain trust does not exist, it is created with the
 specified password. In this case, the supplied PolicyHandle must
 have been opened with POLICY_TRUST_ADMIN and POLICY_CREATE_SECRET
 access to the policy object.

 If the domain trust exists, the password is updated with the
 password specified by the Password parameter. The trust OldPassword
 is set to the previous password.

 If DomainName and Password are NULL, the trusted domain specified by
 DomainSid is deleted.

--*/

NTSTATUS
SetTrustedDomainInfo(
    LSA_HANDLE PolicyHandle,
    PSID DomainSid,             // Sid of domain to manipulate
    LPWSTR TrustedDomainName,   // trusted domain name to add/update
    LPWSTR Password             // new trust password for trusted domain
    )
{
    PTRUSTED_PASSWORD_INFO tpi;
//    PTRUSTED_DOMAIN_NAME_INFO tdni;
    LSA_UNICODE_STRING LsaPassword;
    TRUSTED_PASSWORD_INFO Newtpi;
    BOOL bTrustExists = TRUE; // assume trust exists
    NTSTATUS Status;

    //
    // Make sure you were passed a valid Sid
    //
    if(DomainSid == NULL || !IsValidSid(DomainSid))
        return STATUS_INVALID_SID;

    //
    // if TristedDomainName and Password is NULL (or emptry strings),
    // delete the specified trust
    //
    if( (TrustedDomainName == NULL || *TrustedDomainName == L'\0') &&
        (Password == NULL || *Password == L'\0') ) {
        return LsaDeleteTrustedDomain(PolicyHandle, DomainSid);
    }

    //
    // query the current password, which is used to update the
    // OldPassword. If the trust doesn't exist, indicate this so that the
    // trust will be created.
    //
    Status = LsaQueryTrustedDomainInfo(
        PolicyHandle,
        DomainSid,
        TrustedPasswordInformation,
        &tpi);

    if(Status != STATUS_SUCCESS) {
        if(Status == STATUS_OBJECT_NAME_NOT_FOUND) {
            bTrustExists = FALSE; // indicate trust does not exist
        }
        else {
            DisplayNtStatus("LsaQueryTrustedDomainInfo", Status);
            return Status;
        }
    }

    InitLsaString(&LsaPassword, Password);

    //
    // set the new password to the supplied password
    //
    Newtpi.Password = LsaPassword;

    if(bTrustExists) {
        //
        // if the trust already existed, set OldPassword to the
        // current password...
        //
        Newtpi.OldPassword = tpi->Password;
    }
    else {
        LSA_UNICODE_STRING LsaDomainName;
        DWORD cchDomainName; // number of chars in TrustedDomainName

        //
        // if the trust did not exist, set OldPassword to the
        // supplied password...
        //
        Newtpi.OldPassword = LsaPassword;

        InitLsaString(&LsaDomainName, TrustedDomainName);

        //
        // ...convert TrustedDomainName to uppercase...
        //
        cchDomainName = LsaDomainName.Length / sizeof(WCHAR);
        while(cchDomainName--) {
            LsaDomainName.Buffer[cchDomainName] =
             towupper(LsaDomainName.Buffer[cchDomainName]);
        }

        //
        // ...create the trusted domain object
        //
        Status = LsaSetTrustedDomainInformation(
            PolicyHandle,
            DomainSid,
            TrustedDomainNameInformation,
            &LsaDomainName
            );

        if(Status != STATUS_SUCCESS) return Status;
    }

    //
    // update TrustedPasswordInformation for the specified trust
    //
    Status = LsaSetTrustedDomainInformation(
        PolicyHandle,
        DomainSid,
        TrustedPasswordInformation,
        &Newtpi
        );

    //
    // if a trust already existed, free the memory associated with
    // the retrieved information
    //
    if(bTrustExists) LsaFreeMemory(tpi);

    return Status;
}

/*++

 This function verifies that the "permitted to trust" side of the
 trust relationship has been established and that the specified
 password matches the "permitted to trust" password.

 If the function fails, the return value is FALSE, and bTrustVerified
 is undefined.

 If the function succeeds, the trust verification succeeded, and
 bTrustVerified is set to the result of the verification.

 If bTrustVerified is TRUE, the trust relationship is verfied.

 If bTrustVerified is FALSE, the trust was not verified.  Call
 GetLastError() to get extended error information.

 ERROR_NO_SUCH_USER indicates that the "permitted to trust"
 UF_INTERDOMAIN_TRUST_ACCOUNT does not exist on the specified domain.

 ERROR_LOGON_FAILURE indicates that the supplied password does
 not match the password in the "permitted to trust"
 UF_INTERDOMAIN_TRUST_ACCOUNT.

 NOTE: if a connection exists to the domain controller of the
 TargetDomainName prior to calling this function, this function will
 fail due to a credential conflict (WinError == 1219).

--*/

BOOL
VerifyTrustRelationship(
    LPWSTR TargetDomainName,        // domain name to verify trust at
    LPWSTR TrustAccountToVerify,    // trusted domain name to verify
    LPWSTR Password,                // password associated with trust
    LPBOOL bTrustVerified           // indicates if trust was verified
    )
{
    NET_API_STATUS nas;
    USE_INFO_2 ui2;
    LPWSTR DomainController;
    LPWSTR szIpc = L"\\IPC$";
    LPWSTR RemoteResource = NULL;
    LPWSTR UserName = NULL;
    BOOL bSuccess = FALSE; // assume this function will fail

    //
    // fetch the computer name of the domain you try to connect to
    //
    nas = NetGetDCName(
        NULL, TargetDomainName, (LPBYTE *)&DomainController);
    if(nas != NERR_Success) {
        SetLastError(nas);
        return FALSE;
    }

    __try {

    //
    // build the \\<DCName>\ipc$ as the remote resource
    //
    RemoteResource = (LPWSTR)HeapAlloc(GetProcessHeap(), 0,
        (lstrlenW(DomainController) + lstrlenW(szIpc) + 1 ) *
            sizeof(WCHAR)
        );

    if(RemoteResource == NULL) __leave;

    if(lstrcpyW(RemoteResource, DomainController) == NULL) __leave;
    if(lstrcatW(RemoteResource, szIpc) == NULL) __leave;

    //
    // build the user name as <TrustAccountToVerify>$
    //
    UserName = (LPWSTR)HeapAlloc(GetProcessHeap(), 0,
        (lstrlenW(TrustAccountToVerify) + 1 + 1) * sizeof(WCHAR)
        );

    if(UserName == NULL) __leave;

    if(lstrcpyW(UserName, TrustAccountToVerify) == NULL) __leave;
    if(lstrcatW(UserName, L"$") == NULL) __leave;

    ZeroMemory(&ui2, sizeof(ui2));

    ui2.ui2_local = NULL;
    ui2.ui2_remote = RemoteResource;
    ui2.ui2_asg_type = USE_IPC;
    ui2.ui2_password = Password;
    ui2.ui2_username = UserName;
    ui2.ui2_domainname = TargetDomainName;

    //
    // Attempt to establish a connection to the target domain.
    // If the result is ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT,
    // this illustrates the supplied Password matches an existing
    // trust account because the credentials were validated but
    // a logon is not allowed for this account type.
    //
    nas = NetUseAdd(NULL, 2, (LPBYTE)&ui2, NULL);

    if(nas == ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT) {
        *bTrustVerified = TRUE;     // indicate trust verified
    }
    else {
        *bTrustVerified = FALSE;    // indicate trust not verified

        //
        // if the connection succeeded, the UF_INTERDOMAIN_TRUST_ACCOUNT
        // does not exist, because the supplied credentials aren't
        // recognized by the remote (default credentials are applied).
        // Delete the connection and indicate the "permitted to trust"
        // account is non-existent.
        //
        if(nas == NERR_Success) {
            NetUseDel(NULL, RemoteResource, 0);
            nas = ERROR_NO_SUCH_USER;
        }
    }

    bSuccess = TRUE; // indicate this function succeeded

    } // try
    __finally {

    //
    // free allocated memory
    //
    NetApiBufferFree(DomainController);

    if(RemoteResource != NULL) {
        HeapFree(GetProcessHeap(), 0, RemoteResource);
    }

    if(UserName != NULL) {
        HeapFree(GetProcessHeap(), 0, UserName);
    }

    //
    // if you succeeded, but trust could not be verified, indicate why
    //
    if(bSuccess == TRUE && *bTrustVerified == FALSE) {
        SetLastError(nas);
    }

    }

    return bSuccess;
}

void
DisplayNtStatus(
    LPSTR szAPI,    // ANSI string containing API name
    NTSTATUS Status
    )
{
    //
    // convert the NTSTATUS to Winerror and display the result
    //
    DisplayError(szAPI, LsaNtStatusToWinError(Status));
}


void
DisplayError(
    LPSTR szAPI,    // pointer to failed API name
    DWORD dwLastError
    )
{
    HMODULE hModule = NULL;
    LPSTR MessageBuffer;
    DWORD dwBufferLength;

    fprintf(stderr,"%s error! (rc=%lu)\n", szAPI, dwLastError);

    if(dwLastError >= NERR_BASE && dwLastError <= MAX_NERR) {
        hModule = LoadLibraryEx(
            TEXT("netmsg.dll"),
            NULL,
            LOAD_LIBRARY_AS_DATAFILE
            );
    }

    if(dwBufferLength=FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_IGNORE_INSERTS |
        FORMAT_MESSAGE_FROM_SYSTEM |
        ((hModule != NULL) ? FORMAT_MESSAGE_FROM_HMODULE : 0),
        hModule, // module to get message from
        dwLastError,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // default language
        (LPSTR) &MessageBuffer,
        0,
        NULL
        ))
    {
        DWORD dwBytesWritten;

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

    if(hModule != NULL)
        FreeLibrary(hModule);
}

