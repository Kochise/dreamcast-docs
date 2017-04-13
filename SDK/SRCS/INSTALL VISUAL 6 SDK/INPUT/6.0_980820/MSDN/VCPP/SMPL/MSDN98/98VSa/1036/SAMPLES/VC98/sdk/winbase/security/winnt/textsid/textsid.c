/*++

Copyright 1996 - 1997 Microsoft Corporation

Module Name:

    textsid.c

Abstract:

    This module illustrates how to obtain the textual representation
    of a binary Sid.  This is useful in scenarios where it is not appropriate
    to obtain the name associated with the Sid, or, when the network is not
    available to obtain such information.  The Windows NT event viewer
    utility displays Sids in textual form when the username cannot be
    looked up.  Furthermore, lookup of local user profiles is facilitated
    through conversion of the user Sid to textual form.

    This sample obtains the Sid of the current user and then displays the
    Sid in textual notation.

    A standardized shorthand notation for SIDs makes it simpler to
    visualize their components:

    S-R-I-S-S...

    In the notation shown above,

    S identifies the series of digits as an SID,
    R is the revision level,
    I is the identifier-authority value,
    S is subauthority value(s).

    An SID could be written in this notation as follows:
    S-1-5-32-544

    In this example,
    the SID has a revision level of 1,
    an identifier-authority value of 5,
    first subauthority value of 32,
    second subauthority value of 544.
    (Note that the above Sid represents the local Administrators group)

    The GetTextualSid() function will convert a binary Sid to a textual
    string.

    The resulting string will take one of two forms.  If the
    IdentifierAuthority value is not greater than 2^32, then the SID
    will be in the form:

    S-1-5-21-2127521184-1604012920-1887927527-19009
      ^ ^ ^^ ^^^^^^^^^^ ^^^^^^^^^^ ^^^^^^^^^^ ^^^^^
      | | |      |          |          |        |
      +-+-+------+----------+----------+--------+--- Decimal

    Otherwise it will take the form:

    S-1-0x206C277C6666-21-2127521184-1604012920-1887927527-19009
      ^ ^^^^^^^^^^^^^^ ^^ ^^^^^^^^^^ ^^^^^^^^^^ ^^^^^^^^^^ ^^^^^
      |       |        |      |          |          |        |
      |   Hexidecimal  |      |          |          |        |
      +----------------+------+----------+----------+--------+--- Decimal

    If the function succeeds, the return value is TRUE.
    If the function fails, the return value is FALSE.  To get extended
        error information, call the Win32 API GetLastError().

Author:

    Scott Field (sfield)    13-Apr-96

Revision History:

    Scott Field (sfield)    11-Jul-95
    Unicode enabled

    Scott Field (sfield)    15-May-95
--*/

#define RTN_OK 0
#define RTN_ERROR 13

#include <windows.h>
#include <stdio.h>

BOOL
GetTextualSid(
    PSID pSid,          // binary Sid
    LPTSTR TextualSID,  // buffer for Textual representaion of Sid
    LPDWORD cchSidSize  // required/provided TextualSid buffersize
    );

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
#define MY_BUFSIZE 256 // all allocations should be dynamic
    HANDLE hToken;
    BYTE buf[MY_BUFSIZE];
    PTOKEN_USER ptgUser = (PTOKEN_USER)buf;
    DWORD cbBuffer=MY_BUFSIZE;

    TCHAR szTextualSid[MY_BUFSIZE];
    DWORD cchSid=MY_BUFSIZE;

    BOOL bSuccess;

    //
    // obtain current process token
    //
    if(!OpenProcessToken(
                GetCurrentProcess(), // target current process
                TOKEN_QUERY,         // TOKEN_QUERY access
                &hToken              // resultant hToken
                ))
    {
        DisplayWinError("OpenProcessToken", GetLastError());
        return RTN_ERROR;
    }

    //
    // obtain user identified by current process' access token
    //
    bSuccess = GetTokenInformation(
                hToken,    // identifies access token
                TokenUser, // TokenUser info type
                ptgUser,   // retrieved info buffer
                cbBuffer,  // size of buffer passed-in
                &cbBuffer  // required buffer size
                );

    // close token handle.  do this even if error above
    CloseHandle(hToken);

    if(!bSuccess) {
        DisplayWinError("GetTokenInformation", GetLastError());
        return RTN_ERROR;
    }

    //
    // obtain the textual representaion of the Sid
    //
    if(!GetTextualSid(
                ptgUser->User.Sid, // user binary Sid
                szTextualSid,      // buffer for TextualSid
                &cchSid            // size/required buffer
                )) {
        DisplayWinError("GetTextualSid", GetLastError());
        return RTN_ERROR;
    }

    // display the TextualSid representation
    printf("%s\n", szTextualSid);

    return RTN_OK;
}

BOOL
GetTextualSid(
    PSID pSid,          // binary Sid
    LPTSTR TextualSid,  // buffer for Textual representaion of Sid
    LPDWORD cchSidSize  // required/provided TextualSid buffersize
    )
{
    PSID_IDENTIFIER_AUTHORITY psia;
    DWORD dwSubAuthorities;
    DWORD dwCounter;
    DWORD cchSidCopy;

    //
    // test if Sid passed in is valid
    //
    if(!IsValidSid(pSid)) return FALSE;

    // obtain SidIdentifierAuthority
    psia = GetSidIdentifierAuthority(pSid);

    // obtain sidsubauthority count
    dwSubAuthorities = *GetSidSubAuthorityCount(pSid);

    //
    // compute approximate buffer length
    // S-SID_REVISION- + identifierauthority- + subauthorities- + NULL
    //
    cchSidCopy = (15 + 12 + (12 * dwSubAuthorities) + 1) * sizeof(TCHAR);

    //
    // check provided buffer length.
    // If not large enough, indicate proper size and setlasterror
    //
    if(*cchSidSize < cchSidCopy) {
        *cchSidSize = cchSidCopy;
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        return FALSE;
    }

    //
    // prepare S-SID_REVISION-
    //
    cchSidCopy = wsprintf(TextualSid, TEXT("S-%lu-"), SID_REVISION );

    //
    // prepare SidIdentifierAuthority
    //
    if ( (psia->Value[0] != 0) || (psia->Value[1] != 0) ) {
        cchSidCopy += wsprintf(TextualSid + cchSidCopy,
                    TEXT("0x%02hx%02hx%02hx%02hx%02hx%02hx"),
                    (USHORT)psia->Value[0],
                    (USHORT)psia->Value[1],
                    (USHORT)psia->Value[2],
                    (USHORT)psia->Value[3],
                    (USHORT)psia->Value[4],
                    (USHORT)psia->Value[5]);
    } else {
        cchSidCopy += wsprintf(TextualSid + cchSidCopy,
                    TEXT("%lu"),
                    (ULONG)(psia->Value[5]      )   +
                    (ULONG)(psia->Value[4] <<  8)   +
                    (ULONG)(psia->Value[3] << 16)   +
                    (ULONG)(psia->Value[2] << 24)   );
    }

    //
    // loop through SidSubAuthorities
    //
    for(dwCounter = 0 ; dwCounter < dwSubAuthorities ; dwCounter++) {
        cchSidCopy += wsprintf(TextualSid + cchSidCopy, TEXT("-%lu"),
                    *GetSidSubAuthority(pSid, dwCounter) );
    }

    //
    // tell the caller how many chars we provided, not including NULL
    //
    *cchSidSize = cchSidCopy;

    return TRUE;
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
