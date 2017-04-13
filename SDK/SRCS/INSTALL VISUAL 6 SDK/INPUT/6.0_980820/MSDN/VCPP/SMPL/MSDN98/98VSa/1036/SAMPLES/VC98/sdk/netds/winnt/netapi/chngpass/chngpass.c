/*++

Copyright (c) 1995, 1996  Microsoft Corporation

Module Name:

    chngpass.c

Abstract:

    This sample changes the password for an arbitrary user on an arbitrary
    target machine.

    When targetting a domain controller for account update operations,
    be sure to target the primary domain controller for the domain.
    The account settings are replicated by the primary domain controller
    to each backup domain controller as appropriate.  The NetGetDCName()
    Lan Manager API call can be used to get the primary domain controller
    computer name from a domain name.


    Username is argv[1]
    new password is argv[2]
    optional target machine (or domain name) is argv[3]
    optional old password is argv[4].  This allows non-admin password
     changes.

    Note that admin or account operator privilege is required on the
    target machine unless argv[4] is present and represents the correct
    current password.

    NetUserSetInfo() at info-level 1003 is appropriate for administrative
    over-ride of an existing password.

    NetUserChangePassword() allows for an arbitrary user to over-ride
    an existing password providing that the current password is confirmed.

    Link with netapi32.lib

Author:

    Scott Field (sfield)    21-Dec-95

--*/

#include <windows.h>
#include <stdio.h>

#include <lm.h>

#define RTN_OK 0
#define RTN_USAGE 1
#define RTN_ERROR 13

void
DisplayErrorText(
    DWORD dwLastError
    );

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
    LPWSTR          wUserName;
    LPWSTR          wComputerName = NULL; // default to local machine
    LPWSTR          wOldPassword;
    LPWSTR          wNewPassword;
    USER_INFO_1003  pi1003;
    NET_API_STATUS  nas;

    if( argc < 3 ) {
        fprintf(stderr, "Usage: %ls <user> <new_password> "
                        "[\\\\machine | domain] [old_password]\n",
                        argv[0]);
        return RTN_USAGE;
    }

    //
    // process command line arguments
    //

    wUserName = argv[1];
    wNewPassword = argv[2];

    if( argc >= 4 && *argv[3] != L'\0' ) {

        //
        // obtain target machine name, if appropriate
        // always in Unicode, as that is what the API takes
        //

        if(argv[3][0] == L'\\' && argv[3][1] == L'\\') {

            //
            // target specified machine name
            //

            wComputerName = argv[3];
        }
        else {

            //
            // the user specified a domain name.  Lookup the PDC
            //

            nas = NetGetDCName(
                NULL,
                argv[3],
                (LPBYTE *)&wComputerName
                );

            if(nas != NERR_Success) {
                DisplayErrorText( nas );
                return RTN_ERROR;
            }
        }
    }

    if(argc == 5) {
        wOldPassword = argv[4];
    } else {
        wOldPassword = NULL;
    }

    if(wOldPassword == NULL) {

        //
        // administrative over-ride of existing password
        //

        pi1003.usri1003_password = wNewPassword;

        nas = NetUserSetInfo(
                wComputerName,  // computer name
                wUserName,      // username
                1003,           // info level
                (LPBYTE)&pi1003,     // new info
                NULL
                );
    } else {

        //
        // allows user to change their own password
        //

        nas = NetUserChangePassword(
                wComputerName,
                wUserName,
                wOldPassword,
                wNewPassword
                );
    }

    if(wComputerName != NULL && wComputerName != argv[3]) {

        //
        // a buffer was allocated for the PDC name, free it
        //

        NetApiBufferFree(wComputerName);
    }

    if(nas != NERR_Success) {
        DisplayErrorText( nas );
        return RTN_ERROR;
    }

    return RTN_OK;
}

void
DisplayErrorText(
    DWORD dwLastError
    )
{
    HMODULE hModule = NULL; // default to system source
    LPSTR MessageBuffer;
    DWORD dwBufferLength;
    DWORD dwFormatFlags;

    dwFormatFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER |
                    FORMAT_MESSAGE_IGNORE_INSERTS |
                    FORMAT_MESSAGE_FROM_SYSTEM ;

    //
    // if dwLastError is in the network range, load the message source
    //
    if(dwLastError >= NERR_BASE && dwLastError <= MAX_NERR) {
        hModule = LoadLibraryEx(
            TEXT("netmsg.dll"),
            NULL,
            LOAD_LIBRARY_AS_DATAFILE
            );

        if(hModule != NULL)
            dwFormatFlags |= FORMAT_MESSAGE_FROM_HMODULE;
    }

    //
    // call FormatMessage() to allow for message text to be acquired
    // from the system or the supplied module handle
    //
    if(dwBufferLength = FormatMessageA(
        dwFormatFlags,
        hModule, // module to get message from (NULL == system)
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

    //
    // if we loaded a message source, unload it
    //
    if(hModule != NULL)
        FreeLibrary(hModule);
}
