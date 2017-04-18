///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      RASHOST.H
//
//  Description
//      This file defines all the data structures used in the files and the
//      appropiate constants.
//      In this file we also define the function prototypes for all the
//      methods used in the project files.
//
//  Author
//      Irving De la Cruz
//
//  Revision: 1.1
//
// Written for Microsoft Developer Support
// Copyright (c) 1995-1997 Microsoft Corporation. All rights reserved.
//
#ifndef _RASHOST_H
#define _RASHOST_H

#pragma warning (disable : 4100)
#pragma warning (disable : 4201)
#pragma warning (disable : 4237)
#pragma warning (disable : 4514)
#pragma warning (disable : 4702)
#pragma warning (disable : 4710)

#define STRICT
#include <WINDOWS.H>
#include <RASERROR.H>
extern "C"
{
	#include "RASSHOST.H"
};

// Constants
#define CLIENT_RESPONSE_TIMEOUT     15000

// Private data structures
typedef struct _WORK_THREAD_DATA
{
    HPORT  hPort;
    PBYTE  pSendBuf;
    DWORD  SendBufSize;
    PBYTE  pRecvBuf;
    DWORD  RecvBufSize;
    VOID  (WINAPI *pfnSecurityDialogEnd)(SECURITY_MESSAGE*);
} WORK_THREAD_DATA, *PWORK_THREAD_DATA;

typedef struct _RASHOST_DATA
{
    DWORD   dwSize;
    TCHAR   szUserName[64];
    TCHAR   szUserDomain[64];
    BYTE    Buffer[512];
} RASHOST_DATA, *PRASHOST_DATA;

// Function prototypes for dynamic bindings
typedef DWORD (WINAPI * RASSECURITYDIALOGSENDPROC)(HPORT, PBYTE, WORD);
typedef DWORD (WINAPI * RASSECURITYDIALOGRECEIVEPROC)(HPORT, PBYTE, PWORD, DWORD, HANDLE);

// Global variables
extern RASSECURITYDIALOGSENDPROC    gpfnSendProc;
extern RASSECURITYDIALOGRECEIVEPROC gpfnReceiveProc;

///////////////////////////////////////////////////////////////////////////////
// Function prototypes

// Data transmission functions
void WINAPI CallWorkerThread
                    (PWORK_THREAD_DATA          pCallData);

// User validation function
DWORD WINAPI ValidateCallingUser
                    (PRASHOST_DATA              pData,
                     BOOL *                     pfAccessGranted);

#endif  // _RASHOST_H

// End of file for RASHOST.H
