/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          RegView.cpp
   
   Description:   Contains DLLMain and standard OLE COM object creation stuff.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "ShlView.h"
#include "ClsFact.h"
#include "Utility.h"
#include <olectl.h>

/**************************************************************************
   GUID stuff
**************************************************************************/

//this part is only done once
//if you need to use the GUID in another file, just include Guid.h
#pragma data_seg(".text")
#define INITGUID
#include <initguid.h>
#include <shlguid.h>
#include "Guid.h"
#pragma data_seg()

/**************************************************************************
   private function prototypes
**************************************************************************/

extern "C" BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID);

/**************************************************************************
   global variables
**************************************************************************/

HINSTANCE   g_hInst;
UINT        g_DllRefCount;
int         g_nColumn1;
int         g_nColumn2;
BOOL        g_bViewKeys;
BOOL        g_bShowIDW;
HIMAGELIST  g_himlLarge;
HIMAGELIST  g_himlSmall;

/**************************************************************************

   DllMain

**************************************************************************/

extern "C" BOOL WINAPI DllMain(  HINSTANCE hInstance, 
                                 DWORD dwReason, 
                                 LPVOID lpReserved)
{
switch(dwReason)
   {
   case DLL_PROCESS_ATTACH:
      g_hInst = hInstance;

      GetGlobalSettings();

      //create the global image lists
      CreateImageLists();
      break;

   case DLL_PROCESS_DETACH:
      SaveGlobalSettings();

      //destroy the global image lists
      DestroyImageLists();
      break;
   }
   
return TRUE;
}                                 

/**************************************************************************

   DllCanUnloadNow

**************************************************************************/

STDAPI DllCanUnloadNow(void)
{
return (g_DllRefCount ? S_FALSE : S_OK);
}

/**************************************************************************

   DllGetClassObject

**************************************************************************/

STDAPI DllGetClassObject(  REFCLSID rclsid, 
                           REFIID riid, 
                           LPVOID *ppReturn)
{
*ppReturn = NULL;

//if we don't support this classid, return the proper error code
if(!IsEqualCLSID(rclsid, CLSID_RegViewNameSpace))
   return CLASS_E_CLASSNOTAVAILABLE;
   
//create a CClassFactory object and check it for validity
CClassFactory *pClassFactory = new CClassFactory();
if(NULL == pClassFactory)
   return E_OUTOFMEMORY;
   
//get the QueryInterface return for our return value
HRESULT hResult = pClassFactory->QueryInterface(riid, ppReturn);

//call Release to decement the ref count - creating the object set it to one 
//and QueryInterface incremented it - since its being used externally (not by 
//us), we only want the ref count to be 1
pClassFactory->Release();

//return the result from QueryInterface
return hResult;
}

/**************************************************************************

   DllRegisterServer

**************************************************************************/

typedef struct{
   HKEY  hRootKey;
   LPTSTR lpszSubKey;
   LPTSTR lpszValueName;
   LPTSTR lpszData;
}REGSTRUCT, *LPREGSTRUCT;

STDAPI DllRegisterServer(void)
{
int      i;
HKEY     hKey;
LRESULT  lResult;
DWORD    dwDisp;
TCHAR    szSubKey[MAX_PATH];
TCHAR    szCLSID[MAX_PATH];
TCHAR    szModule[MAX_PATH];
LPWSTR   pwsz;

//get the CLSID in string form
StringFromIID(CLSID_RegViewNameSpace, &pwsz);

if(pwsz)
   {
   WideCharToLocal(szCLSID, pwsz, ARRAYSIZE(szCLSID));

   //free the string
   LPMALLOC pMalloc;
   CoGetMalloc(1, &pMalloc);
   if(pMalloc)
      {
      pMalloc->Free(pwsz);
      pMalloc->Release();
      }
   }

//get this DLL's path and file name
GetModuleFileName(g_hInst, szModule, ARRAYSIZE(szModule));

//register the CLSID entries
REGSTRUCT ClsidEntries[] = {  HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s"),                  NULL,                   TEXT("Registry View"),
                              HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\InprocServer32"),  NULL,                   TEXT("%s"),
                              HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\InprocServer32"),  TEXT("ThreadingModel"), TEXT("Apartment"),
                              HKEY_CLASSES_ROOT,   TEXT("CLSID\\%s\\DefaultIcon"),     NULL,                   TEXT("%s,0"),
                              NULL,                NULL,                               NULL,                   NULL};

for(i = 0; ClsidEntries[i].hRootKey; i++)
   {
   //Create the sub key string.
   wsprintf(szSubKey, ClsidEntries[i].lpszSubKey, szCLSID);

   lResult = RegCreateKeyEx(  ClsidEntries[i].hRootKey,
                              szSubKey,
                              0,
                              NULL,
                              REG_OPTION_NON_VOLATILE,
                              KEY_WRITE,
                              NULL,
                              &hKey,
                              &dwDisp);
   
   if(NOERROR == lResult)
      {
      TCHAR szData[MAX_PATH];

      //if necessary, create the value string
      wsprintf(szData, ClsidEntries[i].lpszData, szModule);
   
      lResult = RegSetValueEx(   hKey,
                                 ClsidEntries[i].lpszValueName,
                                 0,
                                 REG_SZ,
                                 (LPBYTE)szData,
                                 lstrlen(szData) + 1);
      
      RegCloseKey(hKey);
      }
   else
      return SELFREG_E_CLASS;
   }

//Register the default flags for the folder.

wsprintf(   szSubKey, 
            TEXT("CLSID\\%s\\ShellFolder"), 
            szCLSID);

lResult = RegCreateKeyEx(  HKEY_CLASSES_ROOT,
                           szSubKey,
                           0,
                           NULL,
                           REG_OPTION_NON_VOLATILE,
                           KEY_WRITE,
                           NULL,
                           &hKey,
                           &dwDisp);

if(NOERROR == lResult)
   {
   DWORD dwData = SFGAO_FOLDER | SFGAO_HASSUBFOLDER;

   lResult = RegSetValueEx(   hKey,
                              TEXT("Attributes"),
                              0,
                              REG_BINARY,
                              (LPBYTE)&dwData,
                              sizeof(dwData));
   
   RegCloseKey(hKey);
   }
else
   return SELFREG_E_CLASS;

//Register the name space extension

/*
Create the sub key string. Change this from "...Desktop..." to 
"...MyComputer..." if desired.
*/
wsprintf(   szSubKey, 
            TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Desktop\\NameSpace\\%s"), 
            szCLSID);

lResult = RegCreateKeyEx(  HKEY_LOCAL_MACHINE,
                           szSubKey,
                           0,
                           NULL,
                           REG_OPTION_NON_VOLATILE,
                           KEY_WRITE,
                           NULL,
                           &hKey,
                           &dwDisp);

if(NOERROR == lResult)
   {
   TCHAR szData[MAX_PATH];

   //Create the value string.
   lstrcpy(szData, TEXT("Registry View"));

   lResult = RegSetValueEx(   hKey,
                              NULL,
                              0,
                              REG_SZ,
                              (LPBYTE)szData,
                              lstrlen(szData) + 1);
   
   RegCloseKey(hKey);
   }
else
   return SELFREG_E_CLASS;

//If running on NT, register the extension as approved.
OSVERSIONINFO  osvi;

osvi.dwOSVersionInfoSize = sizeof(osvi);
GetVersionEx(&osvi);

if(VER_PLATFORM_WIN32_NT == osvi.dwPlatformId)
   {
   lstrcpy( szSubKey, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"));

   lResult = RegCreateKeyEx(  HKEY_LOCAL_MACHINE,
                              szSubKey,
                              0,
                              NULL,
                              REG_OPTION_NON_VOLATILE,
                              KEY_WRITE,
                              NULL,
                              &hKey,
                              &dwDisp);

   if(NOERROR == lResult)
      {
      TCHAR szData[MAX_PATH];

      //Create the value string.
      lstrcpy(szData, TEXT("Registry View"));

      lResult = RegSetValueEx(   hKey,
                                 szCLSID,
                                 0,
                                 REG_SZ,
                                 (LPBYTE)szData,
                                 lstrlen(szData) + 1);
      
      RegCloseKey(hKey);
      }
   else
      return SELFREG_E_CLASS;
   }

return S_OK;
}

