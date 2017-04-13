/*++

Copyright 1996 - 1997 Microsoft Corporation

Module Name:

    disptrus.c

Abstract:

    This sample enumerates the trusted domains on the target machine, and
    displays them on stdout.  This list matches (minus sorting) the list of
    domains presents by the WinNT Dacl editor.  For practical applications,
    replace the AddTrustToList() function with linked-list management code
    and then use the resultant list later on in the application.

    The optional target machine is specified as argv[1], eg, lsatrust \\winbase

    For a WinNT workstation which is not a member of a domain, the only
    relevant trusted domain is the account domain of the machine.  We detect
    a non-member workstation by checking if the primary domain Sid is NULL.

    For a WinNT workstation which is a member of a domain, the relevant trusted
    domain is the account domain, the primary domain, and the trusted domain(s)
    of the primary domain.

    For a WinNT Domain controller, the account domain and the trusted domains.

Author:

    Scott Field (sfield) 16-Mar-96

--*/

#include <windows.h>
#include <lm.h>
#include "ntsecapi.h" // \mstools\samples\win32\winnt\security\include\ntsecapi.h

#include <stdio.h>

BOOL
BuildTrustList(
    LPWSTR Target
    );

BOOL
IsDomainController(
    LPWSTR Server,
    LPBOOL bDomainController
    );

BOOL
EnumTrustedDomains(
    LSA_HANDLE PolicyHandle
    );

BOOL
AddTrustToList(
    PLSA_UNICODE_STRING UnicodeString
    );

//
// helper functions
//

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

void
DisplayWinError(
    LPSTR szAPI,        // pointer to Ansi function name
    DWORD dwLastError   // DWORD WinError
    );

#define RTN_OK 0
#define RTN_ERROR 13

//
// if you have the ddk, include ntstatus.h
//
#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS                  ((NTSTATUS)0x00000000L)
#define STATUS_MORE_ENTRIES             ((NTSTATUS)0x00000105L)
#define STATUS_NO_MORE_ENTRIES          ((NTSTATUS)0x8000001AL)
#endif


#define ELEMENT_COUNT 64    // number of array elements to allocate

LPWSTR *g_TrustList;        // array of trust elements
DWORD g_TrustCount;         // number of elements in g_TrustList

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
    LPWSTR TargetComputer;
    DWORD i;

    g_TrustCount = 0;
    g_TrustList = (LPWSTR *)HeapAlloc(
        GetProcessHeap(), HEAP_ZERO_MEMORY,
        ELEMENT_COUNT * sizeof(LPWSTR)
        );

    if(g_TrustList == NULL) {
        printf("HeapAlloc error!\n");
        return RTN_ERROR;
    }

    //
    // if a target computer was specified, get it
    //
    if(argc == 2)
        TargetComputer = argv[1];
    else
        TargetComputer = NULL; // default to local machine

    //
    // build the trust list, and display it if successful
    //
    if(!BuildTrustList(TargetComputer)) {
        DisplayWinError("BuildTrustList", GetLastError());
    } else {

        //
        // display trust list
        //
        for(i = 0 ; i < g_TrustCount ; i++)
            printf("%ls\n", g_TrustList[i]);
    }

    //
    // free trust list
    //
    for(i = 0 ; i < g_TrustCount ; i++) {
        if(g_TrustList[i] != NULL)
            HeapFree(GetProcessHeap(), 0, g_TrustList[i]);
    }

    HeapFree(GetProcessHeap(), 0, g_TrustList);

    return RTN_OK;
}

BOOL
BuildTrustList(
    LPWSTR Target
    )
{
    LSA_HANDLE PolicyHandle;
    NTSTATUS Status;

    PPOLICY_ACCOUNT_DOMAIN_INFO AccountDomain;
    BOOL bDC;
    NET_API_STATUS nas = NERR_Success; // assume success

    BOOL bSuccess = FALSE; // assume this function will fail

    //
    // open the policy on the specified machine
    //
    Status = OpenPolicy(
                Target,
                POLICY_VIEW_LOCAL_INFORMATION,
                &PolicyHandle
                );

    if(Status != STATUS_SUCCESS) {
        SetLastError( LsaNtStatusToWinError(Status) );
        return FALSE;
    }

    //
    // obtain the AccountDomain, which is common to all three cases
    //
    Status = LsaQueryInformationPolicy(
                PolicyHandle,
                PolicyAccountDomainInformation,
                &AccountDomain
                );

    if(Status != STATUS_SUCCESS)
        goto cleanup;

    //
    // Note: AccountDomain->DomainSid will contain binary Sid
    //
    AddTrustToList(&AccountDomain->DomainName);

    //
    // free memory allocated for account domain
    //
    LsaFreeMemory(AccountDomain);

    //
    // find out if the target machine is a domain controller
    //
    if(!IsDomainController(Target, &bDC)) {
        ////
        goto cleanup;
    }

    if(!bDC) {
        PPOLICY_PRIMARY_DOMAIN_INFO PrimaryDomain;
        LPWSTR szPrimaryDomainName = NULL;
        LPWSTR DomainController = NULL;

        //
        // get the primary domain
        //
        Status = LsaQueryInformationPolicy(
                PolicyHandle,
                PolicyPrimaryDomainInformation,
                &PrimaryDomain
                );

        if(Status != STATUS_SUCCESS)
            goto cleanup;

        //
        // if the primary domain Sid is NULL, we are a non-member, and
        // our work is done.
        //
        if(PrimaryDomain->Sid == NULL) {
            LsaFreeMemory(PrimaryDomain);
            bSuccess = TRUE;
            goto cleanup;
        }

        AddTrustToList(&PrimaryDomain->Name);

        //
        // build a copy of what we just added.  This is necessary in order
        // to lookup the domain controller for the specified domain.
        // the Domain name must be NULL terminated for NetGetDCName(),
        // and the LSA_UNICODE_STRING buffer is not necessarilly NULL
        // terminated.  Note that in a practical implementation, we
        // could just extract the element we added, since it ends up
        // NULL terminated.
        //

        szPrimaryDomainName = (LPWSTR)HeapAlloc(
            GetProcessHeap(), 0,
            PrimaryDomain->Name.Length + sizeof(WCHAR) // existing length + NULL
            );

        if(szPrimaryDomainName != NULL) {
            //
            // copy the existing buffer to the new storage, appending a NULL
            //
            lstrcpynW(
                szPrimaryDomainName,
                PrimaryDomain->Name.Buffer,
                (PrimaryDomain->Name.Length / sizeof(WCHAR)) + 1
                );
        }

        LsaFreeMemory(PrimaryDomain);

        if(szPrimaryDomainName == NULL) goto cleanup;

        //
        // get the primary domain controller computer name
        //
        nas = NetGetDCName(
            NULL,
            szPrimaryDomainName,
            (LPBYTE *)&DomainController
            );

        HeapFree(GetProcessHeap(), 0, szPrimaryDomainName);

        if(nas != NERR_Success)
            goto cleanup;

        //
        // close the policy handle, because we don't need it anymore
        // for the workstation case, as we open a handle to a DC
        // policy below
        //
        LsaClose(PolicyHandle);
        PolicyHandle = INVALID_HANDLE_VALUE; // invalidate handle value

        //
        // open the policy on the domain controller
        //
        Status = OpenPolicy(
                    DomainController,
                    POLICY_VIEW_LOCAL_INFORMATION,
                    &PolicyHandle
                    );

        //
        // free the domaincontroller buffer
        //
        NetApiBufferFree(DomainController);

        if(Status != STATUS_SUCCESS)
            goto cleanup;
    }

    //
    // build additional trusted domain(s) list and indicate if successful
    //
    bSuccess = EnumTrustedDomains(PolicyHandle);

cleanup:

    //
    // close the policy handle
    //
    if(PolicyHandle != INVALID_HANDLE_VALUE)
        LsaClose(PolicyHandle);

    if(!bSuccess) {
        if(Status != STATUS_SUCCESS)
            SetLastError( LsaNtStatusToWinError(Status) );
        else if(nas != NERR_Success)
            SetLastError( nas );
    }

    return bSuccess;
}

BOOL
EnumTrustedDomains(
    LSA_HANDLE PolicyHandle
    )
{
    LSA_ENUMERATION_HANDLE lsaEnumHandle=0; // start an enum
    PLSA_TRUST_INFORMATION TrustInfo;
    ULONG ulReturned;               // number of items returned
    ULONG ulCounter;                // counter for items returned
    NTSTATUS Status;

    do {
        Status = LsaEnumerateTrustedDomains(
                        PolicyHandle,   // open policy handle
                        &lsaEnumHandle, // enumeration tracker
                        &TrustInfo,     // buffer to receive data
                        32000,          // recommended buffer size
                        &ulReturned     // number of items returned
                        );
        //
        // get out if an error occurred
        //
        if( (Status != STATUS_SUCCESS) &&
            (Status != STATUS_MORE_ENTRIES) &&
            (Status != STATUS_NO_MORE_ENTRIES)
            ) {
            SetLastError( LsaNtStatusToWinError(Status) );
            return FALSE;
        }

        //
        // Display results
        // Note: Sids are in TrustInfo[ulCounter].Sid
        //
        for(ulCounter = 0 ; ulCounter < ulReturned ; ulCounter++)
            AddTrustToList(&TrustInfo[ulCounter].Name);

        //
        // free the buffer
        //
        LsaFreeMemory(TrustInfo);

    } while (Status != STATUS_NO_MORE_ENTRIES);

    return TRUE;
}

BOOL
IsDomainController(
    LPWSTR Server,
    LPBOOL bDomainController
    )
{
    PSERVER_INFO_101 si101;
    NET_API_STATUS nas;

    nas = NetServerGetInfo(
        Server,
        101,    // info-level
        (LPBYTE *)&si101
        );

    if(nas != NERR_Success) {
        SetLastError(nas);
        return FALSE;
    }

    if( (si101->sv101_type & SV_TYPE_DOMAIN_CTRL) ||
        (si101->sv101_type & SV_TYPE_DOMAIN_BAKCTRL) ) {
        //
        // we are dealing with a DC
        //
        *bDomainController = TRUE;
    } else {
        *bDomainController = FALSE;
    }

    NetApiBufferFree(si101);

    return TRUE;
}

BOOL
AddTrustToList(
    PLSA_UNICODE_STRING UnicodeString
    )
{
    if(g_TrustCount >= ELEMENT_COUNT) return FALSE;

    //
    // allocate storage for array element
    //
    g_TrustList[g_TrustCount] = (LPWSTR)HeapAlloc(
        GetProcessHeap(), 0,
        UnicodeString->Length + sizeof(WCHAR) // existing length + NULL
        );

    if(g_TrustList[g_TrustCount] == NULL) return FALSE;

    //
    // copy the existing buffer to the new storage, appending a NULL
    //
    lstrcpynW(
        g_TrustList[g_TrustCount],
        UnicodeString->Buffer,
        (UnicodeString->Length / sizeof(WCHAR)) + 1
        );

    g_TrustCount++; // increment the trust count

    return TRUE;
}

void
InitLsaString(
    PLSA_UNICODE_STRING LsaString,
    LPWSTR String
    )
{
    DWORD StringLength;

    if (String == NULL) {
        LsaString->Buffer = NULL;
        LsaString->Length = 0;
        LsaString->MaximumLength = 0;

        return;
    }

    StringLength = lstrlenW(String);
    LsaString->Buffer = String;
    LsaString->Length = (USHORT) StringLength * sizeof(WCHAR);
    LsaString->MaximumLength = (USHORT) (StringLength + 1) * sizeof(WCHAR);
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

void
DisplayWinError(
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

