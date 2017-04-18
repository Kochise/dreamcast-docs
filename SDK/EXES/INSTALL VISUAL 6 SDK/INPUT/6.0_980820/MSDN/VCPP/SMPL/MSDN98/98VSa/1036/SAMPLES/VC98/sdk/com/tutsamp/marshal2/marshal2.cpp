/*+==========================================================================
  File:      MARSHAL2.CPP

  Summary:   Main implementation file for MARSHAL2.DLL, a COM marshaling
             server for the ICar, IUtility, and ICruise interfaces. This
             module provides the main Win32 DLL framework including
             explicit definitions for the DllMain, DllRegisterServer, and
             DllUnregisterServer exported functions.

             For a comprehensive tutorial code tour of MARSHAL2's contents
             and offerings see the tutorial MARSHAL2.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the MARSHAL2 source code.

  Classes:   none.

  Functions: DllMain, DllRegisterServer, DllUnregisterServer.

  Origin:    5-5-97: atrent - Editor-inheritance from DLLSERVE.CPP in
               the DLLSERVE Tutorial Code Sample.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

/*---------------------------------------------------------------------------
  We include WINDOWS.H for all Win32 applications.
  We include OLE2.H because we will be calling the COM/OLE Libraries.
  We include APPUTIL.H because we will be building this DLL using
    the convenient Virtual Window and Dialog classes and other
  We include MICARS.H for the interface declarations that were produced
    by the MIDL comilation.  In particular this module needs the
    interface IID declarations.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include "micars.h"


// Global save variable for this module's instance handle.
HINSTANCE g_hDllInst = NULL;


/*F+F++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: UnicodeOk

  Summary:  Checks if the platform will handle unicode versions of
            Win32 string API calls.

  Args:     void

  Returns:  BOOL
              TRUE if unicode support; FALSE if not.
------------------------------------------------------------------------F-F*/
BOOL UnicodeOk(void)
{
  BOOL bOk = TRUE;
  TCHAR szUserName[MAX_STRING_LENGTH];
  DWORD dwSize = MAX_STRING_LENGTH;

  if (!GetUserName(szUserName, &dwSize))
    bOk = ERROR_CALL_NOT_IMPLEMENTED == GetLastError() ? FALSE : TRUE;

  return bOk;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DllMain

  Summary:  Like WinMain is for an EXE application, this DllMain function
            is the main entry point for this DLL.  It is called when the
            DLL is loaded by a process, and when new threads are created
            by a process that has already loaded this DLL.  DllMain is also
            called when threads of a process that has loaded the DLL exit
            cleanly and when the process itself unloads the DLL.

            If you want to use C runtime libraries, keep this function
            named "DllMain" and you won't have to do anything special to
            initialize the runtime libraries.

            When fdwReason == DLL_PROCESS_ATTACH, the return value is used
            to determine if the DLL should remain loaded, or should be
            immediately unloaded depending upon whether the DLL could be
            initialized properly.  For all other values of fdwReason,
            the return value is ignored.

  Args:     HINSTANCE hDLLInst,
              Instance handle of the DLL.
            DWORD fdwReason,
              Process attach/detach or thread attach/detach.
              Reason for calling.
            LPVOID lpvReserved)
              Reserved and not used.

  Returns:  BOOL,
              Return value is used only when fdwReason == DLL_PROCESS_ATTACH.
              TRUE  -  Used to signify that the DLL should remain loaded.
              FALSE -  Used to signify that the DLL should be
                immediately unloaded.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
BOOL WINAPI DllMain(
              HINSTANCE hDllInst,
              DWORD fdwReason,
              LPVOID lpvReserved)
{
  BOOL bResult = TRUE;

  // Dispatch this main call based on the reason it was called.
  switch (fdwReason)
  {
    case DLL_PROCESS_ATTACH:
      // The DLL is being loaded for the first time by a given process.
      // Perform per-process initialization here.  If the initialization
      // is successful, return TRUE; if unsuccessful, return FALSE.
      g_hDllInst = hDllInst;
      bResult = UnicodeOk();
      break;

    case DLL_PROCESS_DETACH:
      // The DLL is being unloaded by a given process.  Do any
      // per-process clean up here, such as undoing what was done in
      // DLL_PROCESS_ATTACH.  The return value is ignored.
      break;

    case DLL_THREAD_ATTACH:
      // A thread is being created in a process that has already loaded
      // this DLL.  Perform any per-thread initialization here.  The
      // return value is ignored.
      break;

    case DLL_THREAD_DETACH:
      // A thread is exiting cleanly in a process that has already
      // loaded this DLL.  Perform any per-thread clean up here.  The
      // return value is ignored.
      break;

    default:
      break;
  }

  return (bResult);
}


/*F+F++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: SetRegKeyValue

  Summary:  Internal utility function to set a Key, Subkey, and value
            in the system Registry.

  Args:     LPTSTR pszKey,
            LPTSTR pszSubkey,
            LPTSTR pszValue)

  Returns:  BOOL
              TRUE if success; FALSE if not.
------------------------------------------------------------------------F-F*/
BOOL SetRegKeyValue(
       LPTSTR pszKey,
       LPTSTR pszSubkey,
       LPTSTR pszValue)
{
  BOOL bOk = FALSE;
  LONG ec;
  HKEY hKey;
  TCHAR szKey[MAX_STRING_LENGTH];

  lstrcpy(szKey, pszKey);

  if (NULL != pszSubkey)
  {
    lstrcat(szKey, TEXT("\\"));
    lstrcat(szKey, pszSubkey);
  }

  ec = RegCreateKeyEx(
         HKEY_CLASSES_ROOT,
         szKey,
         0,
         NULL,
         REG_OPTION_NON_VOLATILE,
         KEY_ALL_ACCESS,
         NULL,
         &hKey,
         NULL);

  if (NULL != pszValue && ERROR_SUCCESS == ec)
  {
    ec = RegSetValueEx(
           hKey,
           NULL,
           0,
           REG_SZ,
           (BYTE *)pszValue,
           (lstrlen(pszValue)+1)*sizeof(TCHAR));
    if (ERROR_SUCCESS == ec)
      bOk = TRUE;
    RegCloseKey(hKey);
  }

  return bOk;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DllRegisterServer

  Summary:  The standard exported function that can be called to command
            this DLL server to register itself in the system registry.

  Args:     void.

  Returns:  HRESULT
              NOERROR
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
STDAPI DllRegisterServer(void)
{
  HRESULT  hr = NOERROR;
  TCHAR    szID[GUID_SIZE+1];
  TCHAR    szIFace[GUID_SIZE+32];
  TCHAR    szCLSID[GUID_SIZE+32];
  TCHAR    szModulePath[MAX_PATH];

  // Obtain the path to this module's executable file for later use.
  GetModuleFileName(
    g_hDllInst,
    szModulePath,
    sizeof(szModulePath)/sizeof(TCHAR));

  /*-------------------------------------------------------------------------
    Create registry entries for the ICar Interface.
  -------------------------------------------------------------------------*/
  // Create some base key strings.
  StringFromGUID2(IID_ICar, szID, GUID_SIZE);
  lstrcpy(szIFace, TEXT("Interface\\"));
  lstrcat(szIFace, szID);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  // Create the HKEY_CLASSES_ROOT\Interface entries.
  SetRegKeyValue(
    szIFace,
    NULL,
    TEXT("ICar"));
  SetRegKeyValue(
    szIFace,
    TEXT("ProxyStubClsid32"),
    szID);
  SetRegKeyValue(
    szIFace,
    TEXT("NumMethods"),
    TEXT("7"));

  // Create the HKEY_CLASSES_ROOT\CLSID entries.
  SetRegKeyValue(
    szCLSID,
    NULL,
    TEXT("ICar Proxy/Stub Factory"));
  SetRegKeyValue(
    szCLSID,
    TEXT("InprocServer32"),
    szModulePath);

  /*-------------------------------------------------------------------------
    Create registry entries for the IUtility Interface.
  -------------------------------------------------------------------------*/
  // Create some base key strings.
  StringFromGUID2(IID_IUtility, szID, GUID_SIZE);
  lstrcpy(szIFace, TEXT("Interface\\"));
  lstrcat(szIFace, szID);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  // Create the HKEY_CLASSES_ROOT\Interface entries.
  SetRegKeyValue(
    szIFace,
    NULL,
    TEXT("IUtility"));
  SetRegKeyValue(
    szIFace,
    TEXT("ProxyStubClsid32"),
    szID);
  SetRegKeyValue(
    szIFace,
    TEXT("NumMethods"),
    TEXT("5"));

  // Create the HKEY_CLASSES_ROOT\CLSID entries.
  SetRegKeyValue(
    szCLSID,
    NULL,
    TEXT("IUtility Proxy/Stub Factory"));
  SetRegKeyValue(
    szCLSID,
    TEXT("InprocServer32"),
    szModulePath);

  /*-------------------------------------------------------------------------
    Create registry entries for the ICruise Interface.
  -------------------------------------------------------------------------*/
  // Create some base key strings.
  StringFromGUID2(IID_ICruise, szID, GUID_SIZE);
  lstrcpy(szIFace, TEXT("Interface\\"));
  lstrcat(szIFace, szID);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  // Create the HKEY_CLASSES_ROOT\Interface entries.
  SetRegKeyValue(
    szIFace,
    NULL,
    TEXT("ICruise"));
  SetRegKeyValue(
    szIFace,
    TEXT("ProxyStubClsid32"),
    szID);
  SetRegKeyValue(
    szIFace,
    TEXT("NumMethods"),
    TEXT("5"));

  // Create the HKEY_CLASSES_ROOT\CLSID entries.
  SetRegKeyValue(
    szCLSID,
    NULL,
    TEXT("ICruise Proxy/Stub Factory"));
  SetRegKeyValue(
    szCLSID,
    TEXT("InprocServer32"),
    szModulePath);

  return hr;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DllUnregisterServer

  Summary:  The standard exported function that can be called to command
            this DLL server to unregister itself from the system Registry.

  Args:     void.

  Returns:  HRESULT
              NOERROR
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
STDAPI DllUnregisterServer(void)
{
  HRESULT  hr = NOERROR;
  TCHAR    szID[GUID_SIZE+1];
  TCHAR    szIFace[GUID_SIZE+32];
  TCHAR    szCLSID[GUID_SIZE+32];
  TCHAR    szTemp[MAX_PATH+GUID_SIZE];

  /*-------------------------------------------------------------------------
    Delete registry entries for the ICar Interface.
  -------------------------------------------------------------------------*/
  //Create some base key strings.
  StringFromGUID2(IID_ICar, szID, GUID_SIZE);
  lstrcpy(szIFace, TEXT("Interface\\"));
  lstrcat(szIFace, szID);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  lstrcpy(szTemp, szCLSID);
  lstrcat(szTemp, TEXT("\\InprocServer32"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  lstrcpy(szTemp, szIFace);
  lstrcat(szTemp, TEXT("\\ProxyStubClsid32"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  lstrcpy(szTemp, szIFace);
  lstrcat(szTemp, TEXT("\\NumMethods"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  RegDeleteKey(HKEY_CLASSES_ROOT, szCLSID);
  RegDeleteKey(HKEY_CLASSES_ROOT, szIFace);

  /*-------------------------------------------------------------------------
    Delete registry entries for the IUtility Interface.
  -------------------------------------------------------------------------*/
  //Create some base key strings.
  StringFromGUID2(IID_IUtility, szID, GUID_SIZE);
  lstrcpy(szIFace, TEXT("Interface\\"));
  lstrcat(szIFace, szID);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  lstrcpy(szTemp, szCLSID);
  lstrcat(szTemp, TEXT("\\InprocServer32"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  lstrcpy(szTemp, szIFace);
  lstrcat(szTemp, TEXT("\\ProxyStubClsid32"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  lstrcpy(szTemp, szIFace);
  lstrcat(szTemp, TEXT("\\NumMethods"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  RegDeleteKey(HKEY_CLASSES_ROOT, szCLSID);
  RegDeleteKey(HKEY_CLASSES_ROOT, szIFace);

  /*-------------------------------------------------------------------------
    Delete registry entries for the ICruise Interface.
  -------------------------------------------------------------------------*/
  //Create some base key strings.
  StringFromGUID2(IID_ICruise, szID, GUID_SIZE);
  lstrcpy(szIFace, TEXT("Interface\\"));
  lstrcat(szIFace, szID);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  lstrcpy(szTemp, szCLSID);
  lstrcat(szTemp, TEXT("\\InprocServer32"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  lstrcpy(szTemp, szIFace);
  lstrcat(szTemp, TEXT("\\ProxyStubClsid32"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  lstrcpy(szTemp, szIFace);
  lstrcat(szTemp, TEXT("\\NumMethods"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  RegDeleteKey(HKEY_CLASSES_ROOT, szCLSID);
  RegDeleteKey(HKEY_CLASSES_ROOT, szIFace);

  return hr;
}
