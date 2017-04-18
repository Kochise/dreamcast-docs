//**********************************************************************
// File name: client.h
//
//    Header file for client application
//
//
// Copyright (c) 1994 Microsoft Corporation. All rights reserved.
//**********************************************************************


#define MAXBUFF 64

typedef  ILookup * LPLOOKUP;

// Global variables

HINSTANCE hInst;          // current instance

BOOL  fOleInitialized = FALSE;  // Are the OLE libraries initialized?                                                                      
BOOL  fConnected = FALSE;  // Are we connected to the Phone Book Server?

LPLOOKUP pLookup = NULL;
LPMALLOC pMalloc = NULL;


// Strings

TCHAR ptszNotFound[] = TEXT("Not Found");

TCHAR szAppName[] = TEXT("PHONEDIRCLIENT");   // The name of this application
TCHAR szTitle[]   = TEXT("Phone Dir Client"); // The title bar text
TCHAR ptszFindNum[] = TEXT("Find Number in Phone Directory");
TCHAR ptszEnter[] =  TEXT("Enter number to look up:");

// Forward Function Declarations
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK Find  (HWND, UINT, WPARAM, LPARAM);

typedef struct _FINDDLGINFO
{
	LPTSTR	ptszNameNum;
	UINT	uDlgType;
} FINDDLGINFO, *LPFINDDLGINFO;


