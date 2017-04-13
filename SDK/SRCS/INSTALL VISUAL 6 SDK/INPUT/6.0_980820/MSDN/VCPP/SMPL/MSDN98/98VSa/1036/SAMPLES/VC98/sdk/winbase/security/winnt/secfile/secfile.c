//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1995 - 1997 Microsoft Corporation.	All Rights Reserved.
//
// COMMENTS:
//  All buffers allocated in this sample come from HeapAlloc.  If
//  HeapAlloc fails, the PERR macro is not used because HeapAlloc does
//  not call SetLastError().
//

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>


//
//  Constants and Macros
//
#define USER_ACCESS		GENERIC_ALL
#define WORLD_ACCESS	GENERIC_READ
#define FILENAME		"testfile.txt"

#define PERR(s) fprintf(stderr, "%s(%d) %s : Error %d\n%s\n", \
		    __FILE__, __LINE__, (s), GetLastError(), \
		    GetLastErrorText())

//
//  Prototypes
//
PSID GetUserSid(void);
PSID CreateWorldSid(void);
LPSTR GetLastErrorText(void);


//
//  FUNCTION: main
//
//  PURPOSE: Driving routine for this sample.
//
//  PARAMETERS:
//	none
//
//  RETURN VALUE:
//	none
//
//  COMMENTS:
//
void main()
{
    PSID psidUser, psidEveryone;
    PACL pAcl;
    SECURITY_DESCRIPTOR sd;
    SECURITY_ATTRIBUTES sa;
    BOOL bRes;
    HANDLE hFile;
    DWORD dwBytesWritten, cbMsg, cbAcl;
    char szMsg[] = "Protected data\n";


    // Get the SIDs we'll need for the DACL
    //
    psidUser = GetUserSid();
    psidEveryone = CreateWorldSid();


    // Allocate space for the ACL
	//	For information about computing the size of the ACL, see
	//	the Win32 SDK reference entry for InitializeAcl()
    //
    cbAcl = GetLengthSid (psidUser) + GetLengthSid (psidEveryone) +
	    sizeof(ACL) + (2 * (sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD)));

    pAcl = (PACL) HeapAlloc(GetProcessHeap(), 0, cbAcl);
    if (NULL == pAcl) {
		fprintf(stderr, "HeapAlloc failed.\n");
		ExitProcess(EXIT_FAILURE);
    }


    bRes = InitializeAcl(pAcl,
		    cbAcl,
		    ACL_REVISION);
    if (FALSE == bRes) {
		PERR("InitializeAcl");
		ExitProcess(EXIT_FAILURE);
    }

    // Add Aces for User and World
    //
    bRes = AddAccessAllowedAce(pAcl,
		    ACL_REVISION,
		    USER_ACCESS,
		    psidUser);
    if (FALSE == bRes) {
		PERR("AddAccessAllowedAce");
		ExitProcess(EXIT_FAILURE);
    }

    bRes = AddAccessAllowedAce(pAcl,
		    ACL_REVISION,
		    WORLD_ACCESS,
		    psidEveryone);
    if (FALSE == bRes) {
		PERR("AddAccessAllowedAce");
		ExitProcess(EXIT_FAILURE);
    }

    // Put together the security descriptor
    //
    bRes = InitializeSecurityDescriptor(&sd,
			SECURITY_DESCRIPTOR_REVISION);
    if (FALSE == bRes) {
		PERR("InitializeSecurityDescriptor");
		ExitProcess(EXIT_FAILURE);
    }

    bRes = SetSecurityDescriptorDacl(&sd,
			TRUE,
			pAcl,
			FALSE);
    if (FALSE == bRes) {
		PERR("SetSecurityDescriptorDacl");
		ExitProcess(EXIT_FAILURE);
    }

    // Add the security descriptor to the sa structure
    //
    sa.nLength = sizeof(sa);
    sa.lpSecurityDescriptor = &sd;
    sa.bInheritHandle = FALSE;

    // Generate the file using the security attributes that
    // we've assembled
    //
    hFile = CreateFile(FILENAME,
		       GENERIC_READ |
		       GENERIC_WRITE,
		       0,
		       &sa,
		       CREATE_ALWAYS,
		       FILE_ATTRIBUTE_NORMAL,
		       NULL);
    if (INVALID_HANDLE_VALUE == hFile) {
		PERR("CreateFile");
		ExitProcess(EXIT_FAILURE);
    }

    cbMsg = lstrlen(szMsg);

    bRes = WriteFile(hFile,
		     szMsg,
		     cbMsg,
		     &dwBytesWritten,
		     NULL);
    if (FALSE == bRes) {
		PERR("WriteFile");
		ExitProcess(EXIT_FAILURE);
    }

    if (!CloseHandle(hFile)) {
		PERR("CloseHandle");
		ExitProcess(EXIT_FAILURE);
    }

    // Clean up
    //
    HeapFree(GetProcessHeap(), 0, pAcl);
    HeapFree(GetProcessHeap(), 0, psidUser);
    HeapFree(GetProcessHeap(), 0, psidEveryone);


    printf ("Created %s with special access.\n", FILENAME);

    ExitProcess(EXIT_SUCCESS);
}


//
//  FUNCTION: GetUserSid
//
//  PURPOSE: Obtains a pointer to the SID for the current user
//
//  PARAMETERS:
//	none
//
//  RETURN VALUE:
//	Pointer to the SID
//
//  COMMENTS:
//	The SID buffer returned by this function is allocated with
//	HeapAlloc and should be freed with HeapFree.
//
PSID GetUserSid()
{
    HANDLE hToken;
    BOOL bRes;
    DWORD cbBuffer, cbRequired;
    PTOKEN_USER pUserInfo;
    PSID pUserSid;

    // The User's SID can be obtained from the process token
    //
    bRes = OpenProcessToken(GetCurrentProcess(),
			    TOKEN_QUERY,
			    &hToken);
    if (FALSE == bRes) {
		PERR("OpenProcessToken");
		ExitProcess(EXIT_FAILURE);
    }

    // Set buffer size to 0 for first call to determine
    // the size of buffer we need.
    //
    cbBuffer = 0;
    bRes = GetTokenInformation(hToken,
			TokenUser,
			NULL,
			cbBuffer,
			&cbRequired);

    if (GetLastError() != ERROR_INSUFFICIENT_BUFFER) {
		PERR("GetTokenInformation");
		ExitProcess(EXIT_FAILURE);
    }

    // Allocate a buffer for our token user data
    //
    cbBuffer = cbRequired;
    pUserInfo = (PTOKEN_USER) HeapAlloc(GetProcessHeap(), 0, cbBuffer);
    if (NULL == pUserInfo) {
		fprintf(stderr, "HeapAlloc failed.\n");
		ExitProcess(EXIT_FAILURE);
    }

    // Make the "real" call
    //
    bRes = GetTokenInformation(hToken,
			TokenUser,
			pUserInfo,
			cbBuffer,
			&cbRequired);
    if (FALSE == bRes) {
		PERR("GetTokenInformation");
		ExitProcess(EXIT_FAILURE);
    }

    // Make another copy of the SID for the return value
    //
    cbBuffer = GetLengthSid(pUserInfo->User.Sid);

    pUserSid = (PSID) HeapAlloc(GetProcessHeap(), 0, cbBuffer);
    if (NULL == pUserSid) {
		fprintf(stderr, "HeapAlloc failed.\n");
		ExitProcess(EXIT_FAILURE);
    }

    bRes = CopySid(cbBuffer, pUserSid, pUserInfo->User.Sid);
    if (FALSE == bRes) {
		PERR("CopySid");
		ExitProcess(EXIT_FAILURE);
    }

    bRes = HeapFree(GetProcessHeap(), 0, pUserInfo);
    if (FALSE == bRes) {
		fprintf(stderr, "HeapFree failed.\n");
		ExitProcess(EXIT_FAILURE);
    }

    return pUserSid;
}


//
//  FUNCTION: CreateWorldSid
//
//  PURPOSE: Creates a SID that represents "Everyone"
//
//  PARAMETERS:
//	none
//
//  RETURN VALUE:
//	A pointer to the SID.
//
//  COMMENTS:
//	The SID buffer returned by this function is allocated with
//	HeapAlloc and should be freed with HeapFree.  I made a copy
//	of the SID on the heap so that when the calling code is done
//	with the SID it can use HeapFree().  This is consistent with
//	other parts of this sample.
//
//	The SID Authority and RID used here are defined in winnt.h.
//
PSID CreateWorldSid()
{
    SID_IDENTIFIER_AUTHORITY authWorld = SECURITY_WORLD_SID_AUTHORITY;
    PSID pSid, psidWorld;
    BOOL bRes;
    DWORD cbSid;

    bRes = AllocateAndInitializeSid(&authWorld,
		    1,
		    SECURITY_WORLD_RID,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    &psidWorld);
    if (FALSE == bRes) {
		PERR("AllocateAndInitializeSid");
		ExitProcess(EXIT_FAILURE);
    }

    // Make a copy of the SID using a HeapAlloc'd block for return
    //
    cbSid = GetLengthSid(psidWorld);

    pSid = (PSID) HeapAlloc(GetProcessHeap(), 0, cbSid);
    if (NULL == pSid) {
		fprintf(stderr, "HeapAlloc failed.\n");
		ExitProcess(EXIT_FAILURE);
    }

    bRes = CopySid(cbSid, pSid, psidWorld);
    if (FALSE == bRes) {
		PERR("CopySid");
		ExitProcess(EXIT_FAILURE);
    }

    FreeSid(psidWorld);

    return pSid;
}


//
//  FUNCTION: GetLastErrorText
//
//  PURPOSE: Retrieves the text associated with the last system error.
//
//  PARAMETERS:
//	none
//
//  RETURN VALUE:
//	A pointer to the error text.
//
//  COMMENTS:
//	The contents of the returned buffer will only be valid until
//	the next call to this routine.
//
LPSTR GetLastErrorText()
{
#define MAX_MSG_SIZE 256

    static char szMsgBuf[MAX_MSG_SIZE];
    DWORD dwError, dwRes;

    dwError = GetLastError ();

    dwRes = FormatMessage (
				FORMAT_MESSAGE_FROM_SYSTEM,
                NULL,
                dwError,
                MAKELANGID (LANG_ENGLISH, SUBLANG_ENGLISH_US),
				szMsgBuf,
				MAX_MSG_SIZE,
				NULL);
    if (0 == dwRes) {
		fprintf(stderr, "FormatMessage failed with %d\n", GetLastError());
		ExitProcess(EXIT_FAILURE);
    }

    return szMsgBuf;
}
