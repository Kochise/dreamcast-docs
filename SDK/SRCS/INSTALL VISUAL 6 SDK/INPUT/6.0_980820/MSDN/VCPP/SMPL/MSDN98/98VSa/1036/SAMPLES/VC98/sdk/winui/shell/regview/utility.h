/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          Utility.h
   
   Description:   Utility definitions.

**************************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

/**************************************************************************
   #include statements
**************************************************************************/

#include <windows.h>
#include <shlobj.h>
#include <Regstr.h>

#ifdef _cplusplus
extern "C" {
#endif   //_cplusplus

/**************************************************************************
   global variables
**************************************************************************/

extern int  g_nColumn1;
extern int  g_nColumn2;
extern BOOL g_bViewKeys;
extern BOOL g_bShowIDW;

/**************************************************************************
   function prototypes
**************************************************************************/

//registry utility functions
DWORD GetKeyName(HKEY, LPCTSTR, DWORD, LPTSTR, DWORD);
BOOL GetValueName(HKEY, LPCTSTR, DWORD, LPTSTR, DWORD);
DWORD GetRootKeyText(HKEY, LPTSTR, DWORD);
BOOL RootKeyExists(HKEY);

//utility functions
BOOL SaveGlobalSettings(void);
BOOL GetGlobalSettings(void);
int CALLBACK CompareItems(LPARAM, LPARAM, LPARAM);
VOID CreateImageLists(VOID);
VOID DestroyImageLists(VOID);
int WideCharToLocal(LPTSTR, LPWSTR, DWORD);
int LocalToWideChar(LPWSTR, LPTSTR, DWORD);

#ifdef _cplusplus
}
#endif   //_cplusplus

#define ARRAYSIZE(a)    (sizeof(a)/sizeof(a[0]))

#endif   //UTILITY_H