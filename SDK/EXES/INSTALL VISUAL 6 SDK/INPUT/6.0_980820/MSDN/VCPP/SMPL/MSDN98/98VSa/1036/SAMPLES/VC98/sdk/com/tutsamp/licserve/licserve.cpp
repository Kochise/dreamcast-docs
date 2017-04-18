/*+==========================================================================
  File:      LICSERVE.CPP

  Summary:   Implementation file for a DLL COM Component server providing
             the licensed COM component COLicCruiseCar. This server
             supports self registration and unregistration.  A special
             Utility COM Component is also provided: COLicCarSample.
             Exposing an ISample interface it supports utility operations
             on the DLL server itself (eg, the server can be given a
             pointer to the Client's trace Logging facility and can be
             told to show the server's Aboutbox dialog).

             For a comprehensive tutorial code tour of LICSERVE's contents
             and offerings see the tutorial LICSERVE.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the LICSERVE source code.

  Classes:   none.

  Functions: DllMain, DllGetClassObject, DllCanUnloadNow, DllRegisterServer,
             DllUnregisterServer.

  Origin:    10-5-95: atrent - Editor-inheritance from DLLSERVE.CPP in
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
  We include INITGUID.H only once (here) in the entire DLL because we
    will be defining GUIDs and want them as constants in the data segment.
  We include OLECTL.H because we will using IClassFactory2.
  We include APPUTIL.H because we will be building this DLL using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include ICARS.H and CARGUIDS.H for the common car-related Interface
    class, GUID, and CLSID specifications.
  We include LICSERVE.H because it has the main declerations of all the
    car related interfaces and their GUIDs.  It also has the _DLLEXPORT_
    controlled import and export specifications.
  We include SERVER.H because it has the necessary internal class and
    resource definitions for this DLL.
  We include FACTORY.H because it has the necessary internal class factory
    declarations for this DLL component server.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <initguid.h>
#include <olectl.h>
#include <apputil.h>
#include <icars.h>
#include <carguids.h>
#define _DLLEXPORT_
#include "licserve.h"
#include "server.h"
#include "factory.h"


// Global variable definitions. Some Initialized in DllMain() below.

// We encapsulate the control of this COM server (eg, lock and object
// counting) in a server control C++ object.  Here is it's pointer.
CServer* g_pServer = NULL;

// Here is a pointer for use by the global Trace Message logging macros.
// Set by the ISample::Init function call from an outside EXE client.
CMsgLog* g_pMsgLog = NULL;


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
      bResult = FALSE;
      if (UnicodeOk())
      {
        // Instantiate the CServer utility class.
        g_pServer = new CServer;
        if (NULL != g_pServer)
        {
          // Remember the DLL Instance handle.
          g_pServer->m_hDllInst = hDllInst;

          // Create a MsgBox object.
          g_pServer->m_pMsgBox = new CMsgBox;
          if (NULL != g_pServer->m_pMsgBox)
          {
            // Check for valid Machine License.
            g_pServer->CheckLicense();
            bResult = TRUE;
          }
        }
      }
      break;

    case DLL_PROCESS_DETACH:
      // The DLL is being unloaded by a given process.  Do any
      // per-process clean up here, such as undoing what was done in
      // DLL_PROCESS_ATTACH.  The return value is ignored.
      DELETE_POINTER(g_pServer->m_pMsgBox);
      DELETE_POINTER(g_pServer);
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


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DllGetClassObject

  Summary:  The standard exported function that the COM service library
            uses to obtain an object class of the class factory for a
            specified component provided by this server DLL.

  Args:     REFCLSID rclsid,
              [in] The CLSID of the requested Component.
            REFIID riid,
              [in] GUID of the requested interface on the Class Factory.
            PPVOID ppv)
              [out] Address of the caller's pointer variable that will
              receive the requested interface pointer.

  Returns:  HRESULT
              E_FAIL if requested component isn't supported.
              E_OUTOFMEMORY if out of memory.
              Error code out of the QueryInterface.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
STDAPI DllGetClassObject(
         REFCLSID rclsid,
         REFIID riid,
         PPVOID ppv)
{
  HRESULT hr = CLASS_E_CLASSNOTAVAILABLE;
  IUnknown* pCob = NULL;

  if (CLSID_LicCruiseCar == rclsid)
  {
    LOG("P: DllGetClassObject: Requesting CFLicCruiseCar.");
    hr = E_OUTOFMEMORY;
    pCob = new CFLicCruiseCar(NULL, g_pServer);
  }
  else if (CLSID_LicCarSample == rclsid)
  {
    LOG("P: DllGetClassObject: Requesting CFLicCarSample.");
    hr = E_OUTOFMEMORY;
    pCob = new CFLicCarSample(NULL, g_pServer);
  }

  if (NULL != pCob)
  {
    g_pServer->ObjectsUp();
    hr = pCob->QueryInterface(riid, ppv);
    if (FAILED(hr))
    {
      g_pServer->ObjectsDown();
      DELETE_POINTER(pCob);
    }
  }

  return hr;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DllCanUnloadNow

  Summary:  The standard exported function that the COM service library
            uses to determine if this server DLL can be unloaded.

  Args:     void.

  Returns:  HRESULT
              S_OK if this DLL server can be unloaded.
              S_FALSE if this DLL can not be unloaded.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
STDAPI DllCanUnloadNow(void)
{
  HRESULT hr;

  LOGF2("P: DllCanUnloadNow. cObjects=%i, cLocks=%i.", g_pServer->m_cObjects, g_pServer->m_cLocks);

  // We return S_OK of there are no longer any living objects AND
  // there are no outstanding client locks on this server.
  hr = (0L==g_pServer->m_cObjects && 0L==g_pServer->m_cLocks) ? S_OK : S_FALSE;

  return hr;
}


/*F+F++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: SetRegKeyValue

  Summary:  Internal utility function to set a Key, Subkey, and value
            in the system Registry under HKEY_CLASSES_ROOT.

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

  if (ERROR_SUCCESS == ec)
  {
    if (NULL != pszValue)
    {
      ec = RegSetValueEx(
             hKey,
             NULL,
             0,
             REG_SZ,
             (BYTE *)pszValue,
             (lstrlen(pszValue)+1)*sizeof(TCHAR));
    }
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
  TCHAR    szCLSID[GUID_SIZE+32];
  TCHAR    szModulePath[MAX_PATH];

  // Obtain the path to this module's executable file for later use.
  GetModuleFileName(
    g_pServer->m_hDllInst,
    szModulePath,
    sizeof(szModulePath) / sizeof(TCHAR));

  /*-------------------------------------------------------------------------
    Create registry entries for the LicCruiseCar Component.
  -------------------------------------------------------------------------*/
  // Create some base key strings.
  StringFromGUID2(CLSID_LicCruiseCar, szID, GUID_SIZE);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  // Create ProgID keys.
  SetRegKeyValue(
    TEXT("CTS.LicCruiseCar.1"),
    NULL,
    TEXT("LicCruiseCar Component - LICSERVE Code Sample"));
  SetRegKeyValue(
    TEXT("CTS.LicCruiseCar.1"),
    TEXT("CLSID"),
    szID);

  // Create VersionIndependentProgID keys.
  SetRegKeyValue(
    TEXT("CTS.LicCruiseCar"),
    NULL,
    TEXT("LicCruiseCar Component - LICSERVE Code Sample"));
  SetRegKeyValue(
    TEXT("CTS.LicCruiseCar"),
    TEXT("CurVer"),
    TEXT("CTS.LicCruiseCar.1"));
  SetRegKeyValue(
    TEXT("CTS.LicCruiseCar"),
    TEXT("CLSID"),
    szID);

  // Create entries under CLSID.
  SetRegKeyValue(
    szCLSID,
    NULL,
    TEXT("LicCruiseCar Component - LICSERVE Code Sample"));
  SetRegKeyValue(
    szCLSID,
    TEXT("ProgID"),
    TEXT("CTS.LicCruiseCar.1"));
  SetRegKeyValue(
    szCLSID,
    TEXT("VersionIndependentProgID"),
    TEXT("CTS.LicCruiseCar"));
  SetRegKeyValue(
    szCLSID,
    TEXT("NotInsertable"),
    NULL);
  SetRegKeyValue(
    szCLSID,
    TEXT("InprocServer32"),
    szModulePath);

  /*-------------------------------------------------------------------------
    Create registry entries for the LicCarSample Component.
  -------------------------------------------------------------------------*/
  // Create some base key strings.
  StringFromGUID2(CLSID_LicCarSample, szID, GUID_SIZE);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  // Create ProgID keys.
  SetRegKeyValue(
    TEXT("CTS.LicCarSample.1"),
    NULL,
    TEXT("LicCarSample Component - LICSERVE Code Sample"));
  SetRegKeyValue(
    TEXT("CTS.LicCarSample.1"),
    TEXT("CLSID"),
    szID);

  // Create VersionIndependentProgID keys.
  SetRegKeyValue(
    TEXT("CTS.LicCarSample"),
    NULL,
    TEXT("LicCarSample Component - LICSERVE Code Sample"));
  SetRegKeyValue(
    TEXT("CTS.LicCarSample"),
    TEXT("CurVer"),
    TEXT("CTS.LicCarSample.1"));
  SetRegKeyValue(
    TEXT("CTS.LicCarSample"),
    TEXT("CLSID"),
    szID);

  // Create entries under CLSID.
  SetRegKeyValue(
    szCLSID,
    NULL,
    TEXT("LicCarSample Component - LICSERVE Code Sample"));
  SetRegKeyValue(
    szCLSID,
    TEXT("ProgID"),
    TEXT("CTS.LicCarSample.1"));
  SetRegKeyValue(
    szCLSID,
    TEXT("VersionIndependentProgID"),
    TEXT("CTS.LicCarSample"));
  SetRegKeyValue(
    szCLSID,
    TEXT("NotInsertable"),
    NULL);
  SetRegKeyValue(
    szCLSID,
    TEXT("InprocServer32"),
    szModulePath);

  return hr;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: DllUnregisterServer

  Summary:  The standard exported function that can be called to command
            this DLL server to unregister itself from the system Registry
            (under main key: HKEY_CLASSES_ROOT).

  Args:     void.

  Returns:  HRESULT
              NOERROR
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
STDAPI DllUnregisterServer(void)
{
  HRESULT  hr = NOERROR;
  TCHAR    szID[GUID_SIZE+1];
  TCHAR    szCLSID[GUID_SIZE+32];
  TCHAR    szTemp[MAX_PATH+GUID_SIZE];

  /*-------------------------------------------------------------------------
    Delete registry entries for the LicCruiseCar Component.
  -------------------------------------------------------------------------*/
  //Create some base key strings.
  StringFromGUID2(CLSID_LicCruiseCar, szID, GUID_SIZE);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.LicCruiseCar\\CurVer"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.LicCruiseCar\\CLSID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.LicCruiseCar"));

  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.LicCruiseCar.1\\CLSID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.LicCruiseCar.1"));

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("ProgID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("VersionIndependentProgID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("NotInsertable"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("InprocServer32"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  RegDeleteKey(HKEY_CLASSES_ROOT, szCLSID);

  /*-------------------------------------------------------------------------
    Delete registry entries for the LicCarSample Component.
  -------------------------------------------------------------------------*/
  //Create some base key strings.
  StringFromGUID2(CLSID_LicCarSample, szID, GUID_SIZE);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.LicCarSample\\CurVer"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.LicCarSample\\CLSID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.LicCarSample"));

  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.LicCarSample.1\\CLSID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.LicCarSample.1"));

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("ProgID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("VersionIndependentProgID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("NotInsertable"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("InprocServer32"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  RegDeleteKey(HKEY_CLASSES_ROOT, szCLSID);

  return hr;
}
