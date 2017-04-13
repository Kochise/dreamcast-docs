/*+==========================================================================
  File:      APTSERVE.CPP

  Summary:   Based largely on the LOCSERVE.EXE source code, this module
             implements the main framework for a Win32 .EXE application.
             This application is meant to run hidden as a local multiple
             Apartment COM server that offers the Car, UtilityCar, and
             CruiseCar components.  Though this local server offers a
             simple main window and menu system these are not seen during
             normal operation.  This server can be run stand-alone for
             debugging purposes by explicitly using the -embedding command
             line switch and invoking APTSERVE prior to the client.

             This local server supports self-registration and this program
             recognizes the -RegServer and -UnregServer command line
             switches and has the appropriate functions (RegisterServer
             and UnregisterServer) to register this local server in the
             system Registry.

             For a comprehensive tutorial code tour of APTSERVE's
             contents and offerings see the tutorial APTSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the APTSERVE source code.
             For more details on the APTCLIEN.EXE that APTSERVE works with
             see the APTCLIEN.HTM file in the main tutorial directory.

  Classes:   CMainWindow

  Functions: InitApplication, WinMain

  Origin:    3-20-96: atrent - Editor-inheritance from the LOCSERVE source.

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

/*--------------------------------------------------------------------------
  We include WINDOWS.H for all Win32 applications.
  We include OLE2.H because we will make calls to the COM/OLE libraries.
  We include INITGUID.H only once (here) in the entire app because we
    will be defining GUIDs and want them as constants in the data segment.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include MICARS.H and CARGUIDS.H for the common car-related Interface
    class, GUID, and CLSID specifications.
  We include APTSERVE.H because it has class and resource definitions
    specific to this APTSERVE application.
  We include SERVER.H because it has internal class declarations for
    the server's control object.
  We include FACTORY.H because it has the necessary internal class factory
    declarations for this component server.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <initguid.h>
#include <apputil.h>
#include <micars.h>
#include <carguids.h>
#include "aptserve.h"
#include "server.h"
#include "factory.h"


// We encapsulate the control of this COM server (eg, lock and object
// counting) in a server control C++ object.  Here is it's pointer.
CServer*  g_pServer = NULL;

// Here is a pointer for use by the global Trace Message logging macros.
CSendLog* g_pMsgLog = NULL;


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::CMainWindow

  Summary:  CMainWindow Constructor.

  Args:     .

  Modifies: m_pMsgBox.

  Returns:  .
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CMainWindow::CMainWindow()
{
  // Null the Message object pointers.
  m_pMsgBox = NULL;
  m_pMsgLog = NULL;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::~CMainWindow

  Summary:  CMainWindow Destructor.  Destruction of the main window
            indicates that the application should quit and thus the
            PostQuitMessage API is called.

  Args:     .

  Modifies: .

  Returns:  .
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CMainWindow::~CMainWindow()
{
  // CMainWindow is derived from CVirWindow which traps the WM_DESTROY
  // message and causes a delete of CMainWindow which in turn causes this
  // destructor to run. The WM_DESTROY results when the window is destoyed
  // after a close of the window. Prior to exiting the main message loop:

  // Close down the factories (ie, Revoke and release the Class Factories).
  if (NULL != g_pServer)
    g_pServer->CloseFactories();

  LOGF1("L<%X>: Exiting APTSERVE local server application.",TID);

  // We delete the CMsgBox and CMsgLog objects that were made in
  // Initinstance and the server control object, CServer.
  DELETE_POINTER(g_pServer);
  DELETE_POINTER(m_pMsgBox);
  DELETE_POINTER(m_pMsgLog);

  // We then post a WM_QUIT message to cause an exit of the main thread's
  // message loop and an exit of this instance of the application.
  PostQuitMessage(0);
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


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::RegisterServer

  Summary:  Member function used by this server to register itself in the
            system registry.

  Args:     void.

  Returns:  BOOL
              TRUE
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CMainWindow::RegisterServer(void)
{
  BOOL  bOk = TRUE;
  TCHAR szID[GUID_SIZE+1];
  TCHAR szCLSID[GUID_SIZE+32];
  TCHAR szModulePath[MAX_PATH];

  // Obtain the path to this module's executable file for later use.
  GetModuleFileName(
    g_pServer->m_hInstServer,
    szModulePath,
    sizeof(szModulePath)/sizeof(TCHAR));

  /*-------------------------------------------------------------------------
    Create registry entries for the AptCar Component.
  -------------------------------------------------------------------------*/
  // Create some base key strings.
  StringFromGUID2(CLSID_AptCar, szID, GUID_SIZE);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  // Create ProgID keys.
  SetRegKeyValue(
    TEXT("CTS.AptCar.1"),
    NULL,
    TEXT("AptCar Component - APTSERVE Code Sample"));
  SetRegKeyValue(
    TEXT("CTS.AptCar.1"),
    TEXT("CLSID"),
    szID);

  // Create VersionIndependentProgID keys.
  SetRegKeyValue(
    TEXT("CTS.AptCar"),
    NULL,
    TEXT("AptCar Component - APTSERVE Code Sample"));
  SetRegKeyValue(
    TEXT("CTS.AptCar"),
    TEXT("CurVer"),
    TEXT("CTS.AptCar.1"));
  SetRegKeyValue(
    TEXT("CTS.AptCar"),
    TEXT("CLSID"),
    szID);

  // Create entries under CLSID.
  SetRegKeyValue(
    szCLSID,
    NULL,
    TEXT("AptCar Component - APTSERVE Code Sample"));
  SetRegKeyValue(
    szCLSID,
    TEXT("ProgID"),
    TEXT("CTS.AptCar.1"));
  SetRegKeyValue(
    szCLSID,
    TEXT("VersionIndependentProgID"),
    TEXT("CTS.AptCar"));
  SetRegKeyValue(
    szCLSID,
    TEXT("NotInsertable"),
    NULL);
  SetRegKeyValue(
    szCLSID,
    TEXT("LocalServer32"),
    szModulePath);

  /*-------------------------------------------------------------------------
    Create registry entries for the AptUtilityCar Component.
  -------------------------------------------------------------------------*/
  // Create some base key strings.
  StringFromGUID2(CLSID_AptUtilityCar, szID, GUID_SIZE);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  // Create ProgID keys.
  SetRegKeyValue(
    TEXT("CTS.AptUtilityCar.1"),
    NULL,
    TEXT("AptUtilityCar Component - APTSERVE Code Sample"));
  SetRegKeyValue(
    TEXT("CTS.AptUtilityCar.1"),
    TEXT("CLSID"),
    szID);

  // Create VersionIndependentProgID keys.
  SetRegKeyValue(
    TEXT("CTS.AptUtilityCar"),
    NULL,
    TEXT("AptUtilityCar Component - APTSERVE Code Sample"));
  SetRegKeyValue(
    TEXT("CTS.AptUtilityCar"),
    TEXT("CurVer"),
    TEXT("CTS.AptUtilityCar.1"));
  SetRegKeyValue(
    TEXT("CTS.AptUtilityCar"),
    TEXT("CLSID"),
    szID);

  // Create entries under CLSID.
  SetRegKeyValue(
    szCLSID,
    NULL,
    TEXT("AptUtilityCar Component - APTSERVE Code Sample"));
  SetRegKeyValue(
    szCLSID,
    TEXT("ProgID"),
    TEXT("CTS.AptUtilityCar.1"));
  SetRegKeyValue(
    szCLSID,
    TEXT("VersionIndependentProgID"),
    TEXT("CTS.AptUtilityCar"));
  SetRegKeyValue(
    szCLSID,
    TEXT("NotInsertable"),
    NULL);
  SetRegKeyValue(
    szCLSID,
    TEXT("LocalServer32"),
    szModulePath);

  /*-------------------------------------------------------------------------
    Create registry entries for the AptCruiseCar Component.
  -------------------------------------------------------------------------*/
  // Create some base key strings.
  StringFromGUID2(CLSID_AptCruiseCar, szID, GUID_SIZE);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  // Create ProgID keys.
  SetRegKeyValue(
    TEXT("CTS.AptCruiseCar.1"),
    NULL,
    TEXT("AptCruiseCar Component - APTSERVE Code Sample"));
  SetRegKeyValue(
    TEXT("CTS.AptCruiseCar.1"),
    TEXT("CLSID"),
    szID);

  // Create VersionIndependentProgID keys.
  SetRegKeyValue(
    TEXT("CTS.AptCruiseCar"),
    NULL,
    TEXT("AptCruiseCar Component - APTSERVE Code Sample"));
  SetRegKeyValue(
    TEXT("CTS.AptCruiseCar"),
    TEXT("CurVer"),
    TEXT("CTS.AptCruiseCar.1"));
  SetRegKeyValue(
    TEXT("CTS.AptCruiseCar"),
    TEXT("CLSID"),
    szID);

  // Create entries under CLSID.
  SetRegKeyValue(
    szCLSID,
    NULL,
    TEXT("AptCruiseCar Component - APTSERVE Code Sample"));
  SetRegKeyValue(
    szCLSID,
    TEXT("ProgID"),
    TEXT("CTS.AptCruiseCar.1"));
  SetRegKeyValue(
    szCLSID,
    TEXT("VersionIndependentProgID"),
    TEXT("CTS.AptCruiseCar"));
  SetRegKeyValue(
    szCLSID,
    TEXT("NotInsertable"),
    NULL);
  SetRegKeyValue(
    szCLSID,
    TEXT("LocalServer32"),
    szModulePath);

  return bOk;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::UnregisterServer

  Summary:  Member function used by this server to unregister itself from
            the system Registry.

  Args:     void.

  Returns:  BOOL
              TRUE
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CMainWindow::UnregisterServer(void)
{
  BOOL  bOk = TRUE;
  TCHAR szID[GUID_SIZE+1];
  TCHAR szCLSID[GUID_SIZE+32];
  TCHAR szTemp[MAX_PATH+GUID_SIZE];

  /*-------------------------------------------------------------------------
    Delete registry entries for the AptCar Component.
  -------------------------------------------------------------------------*/
  //Create some base key strings.
  StringFromGUID2(CLSID_AptCar, szID, GUID_SIZE);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptCar\\CurVer"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptCar\\CLSID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptCar"));

  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptCar.1\\CLSID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptCar.1"));

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("ProgID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("VersionIndependentProgID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("NotInsertable"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("LocalServer32"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  RegDeleteKey(HKEY_CLASSES_ROOT, szCLSID);

  /*-------------------------------------------------------------------------
    Delete registry entries for the AptUtilityCar Component.
  -------------------------------------------------------------------------*/
  //Create some base key strings.
  StringFromGUID2(CLSID_AptUtilityCar, szID, GUID_SIZE);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptUtilityCar\\CurVer"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptUtilityCar\\CLSID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptUtilityCar"));

  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptUtilityCar.1\\CLSID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptUtilityCar.1"));

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("ProgID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("VersionIndependentProgID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("NotInsertable"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("LocalServer32"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  RegDeleteKey(HKEY_CLASSES_ROOT, szCLSID);

  /*-------------------------------------------------------------------------
    Delete registry entries for the AptCruiseCar Component.
  -------------------------------------------------------------------------*/
  //Create some base key strings.
  StringFromGUID2(CLSID_AptCruiseCar, szID, GUID_SIZE);
  lstrcpy(szCLSID, TEXT("CLSID\\"));
  lstrcat(szCLSID, szID);

  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptCruiseCar\\CurVer"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptCruiseCar\\CLSID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptCruiseCar"));

  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptCruiseCar.1\\CLSID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, TEXT("CTS.AptCruiseCar.1"));

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("ProgID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("VersionIndependentProgID"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("NotInsertable"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  wsprintf(szTemp, TEXT("%s\\%s"), szCLSID, TEXT("LocalServer32"));
  RegDeleteKey(HKEY_CLASSES_ROOT, szTemp);

  RegDeleteKey(HKEY_CLASSES_ROOT, szCLSID);

  return bOk;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::DoMenu

  Summary:  Dispatch and handle the main menu commands.

  Args:     WPARAM wParam,
              First message parameter (word sized).
            LPARAM lParam)
              Second message parameter (long sized).

  Modifies: ...

  Returns:  LRESULT
              Standard Windows WindowProc return value.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CMainWindow::DoMenu(
          WPARAM wParam,
          LPARAM lParam)
{
  LRESULT lResult = FALSE;
  HMENU hMenu  = ::GetMenu(m_hWnd);

  switch (LOWORD(wParam))
  {
    //----------------------------------------------------------------------
    // Handle File Menu Commands.
    //----------------------------------------------------------------------
    case IDM_FILE_EXIT:
      // The user commands us to exit this application so we tell the
      // Main window to close itself.
      ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
      break;

    //----------------------------------------------------------------------
    // Handle Log Menu Commands.
    //----------------------------------------------------------------------
    case IDM_LOG_LOGCLEAR:
      // Clear the message log.
      g_pMsgLog->Clear();
      // Use macro to log messages.
      LOGID(IDS_LOGTO_SERVER);
      break;
    case IDM_LOG_COPYCLIP:
      // Copy trace message log to clipboard.
      g_pMsgLog->Copy();
      break;

    //----------------------------------------------------------------------
    // Handle Help Menu Commands.
    //----------------------------------------------------------------------
    case IDM_HELP_ABOUT:
      {
        CAboutBox dlgAboutBox;
        HWND hWnd = FindWindow(NULL, TEXT(CLIENT_WINDOW_TITLE));
        if (NULL == hWnd)
          hWnd = m_hWnd;

        LOGF1("L<%X>: === Help Menu: About APTSERVE.",TID);
        // Show the standard About Box dialog for this EXE by telling the
        // dialog C++ object to show itself by invoking its ShowDialog
        // method.  Pass it this EXE instance and the parent window handle.
        // Use a dialog resource ID for the dialog template stored in
        // this EXE module's resources.
        dlgAboutBox.ShowDialog(
          m_hInst,
          MAKEINTRESOURCE(IDM_HELP_ABOUT),
          hWnd);
      }
      break;

    default:
      // Defer all messages NOT handled here to the Default Window Proc.
      lResult = ::DefWindowProc(m_hWnd, WM_COMMAND, wParam, lParam);
      break;
  }

  return(lResult);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::InitInstance

  Summary:  Instantiates an instance of the main application window.
            This method must be called only once, immediately after
            window class construction.  We take care to delete 'this'
            CMainWindow if we must return the error condition FALSE.

  Args:     HINSTANCE hInstance,
              Handle of the application instance.
            int nShow)
              Command to pass to ShowWindow.

  Modifies: m_pMsgBox, m_pMsgLog.

  Returns:  BOOL.
              TRUE if succeeded.
              FALSE if failed.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CMainWindow::InitInstance(
       HINSTANCE hInstance,
       int nShow)
{
  BOOL bOk = FALSE;
  HWND hWnd;

  // Create the Message Box object.
  m_pMsgBox = new CMsgBox;
  m_pMsgLog = new CSendLog;

  if (NULL != m_pMsgBox && NULL != m_pMsgLog)
  {
    // Note, the Create method sets the m_hWnd member so we don't
    // need to set it explicitly here first.

    // Here is the create of this window.  Size the window reasonably.
    // Create sets both m_hInst and m_hWnd.
    hWnd = Create(
             TEXT(MAIN_WINDOW_CLASS_NAME_STR),
             TEXT(MAIN_WINDOW_TITLE_STR),
             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
               | WS_MAXIMIZEBOX | WS_THICKFRAME,
             CW_USEDEFAULT,
             CW_USEDEFAULT,
             ::GetSystemMetrics(SM_CXSCREEN)*3/5,
             ::GetSystemMetrics(SM_CYSCREEN)*3/5,
             NULL,
             NULL,
             hInstance);
    if (hWnd)
    {
      // Assign the server's copy of the main window handle.
      g_pServer->m_hWndServer = m_hWnd;

      // Init the Message Box object.
      if (m_pMsgBox->Init(m_hInst, m_hWnd))
      {
        bOk = TRUE;
        // If the Client's Main window is found then set up logging to it.
        hWnd = FindWindow(NULL, TEXT(CLIENT_WINDOW_TITLE));
        if (NULL != hWnd)
        {
          // Tell the CSendLog object that we are logging to client.
          m_pMsgLog->LogToServer(FALSE);
          // Assign the global MsgLog pointer.
          g_pMsgLog = m_pMsgLog;
          m_pMsgLog->SetClient(m_hInst, m_hWnd, hWnd);
          LOGID(IDS_LOGTO_CLIENT);
        }
        else
        {
          // If the client window can't be found then create and show the
          // log display in this local server.

          // Indicate we are logging to our own server log facility.
          m_pMsgLog->LogToServer(TRUE);

          // Ensure the new window is shown on screen and its content
          // is painted.
          ::ShowWindow(m_hWnd, nShow);
          ::UpdateWindow(m_hWnd);

          // Create the Trace Message Log ListBox as a child window that
          // fits the client area of the Main Window (the TRUE 3rd argument
          // specifies such an inside child). If you want the Trace Message
          // Log in a separate (but owned) window, then pass a FALSE
          // instead for the 3rd argument.
          if (m_pMsgLog->CreateServerLog(m_hInst, m_hWnd, TRUE))
          {
            // Assign the global MsgLog pointer.
            g_pMsgLog = m_pMsgLog;
            // Use macro to log an initial start messsage.
            LOGID(IDS_LOGTO_SERVER);
          }
          else
            bOk = FALSE;
        }
      }
    }
  }

  if (!bOk)
  {
    DELETE_POINTER(m_pMsgBox);
    DELETE_POINTER(m_pMsgLog);
  }

  return (bOk);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::WindowProc

  Summary:  Main window procedure for this window object.  See CVirWindow
            in the APPUTIL library (APPUTIL.CPP) for details on how this
            method gets called by the global WindowProc.

  Args:     UINT uMsg,
              Windows message that is "sent" to this window.
            WPARAM wParam,
              First message parameter (word sized).
            LPARAM lParam)
              Second message parameter (long sized).

  Modifies: ...

  Returns:  LRESULT
              Standard Windows WindowProc return value.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CMainWindow::WindowProc(
          UINT uMsg,
          WPARAM wParam,
          LPARAM lParam)
{
  LRESULT lResult = FALSE;

  switch (uMsg)
  {
    case WM_CREATE:
      break;

    case WM_COMMAND:
      // Dispatch and handle any Menu command messages received.
      lResult = DoMenu(wParam, lParam);
      break;

    case WM_CLOSE:
      // The user selected Close on the main window's System menu
      // or Exit on the File menu.
    case WM_QUIT:
      // If the app is being quit then close any associated help windows.
    default:
      // Defer all messages NOT handled here to the Default Window Proc.
      lResult = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
      break;
  }

  return(lResult);
}


/*F+F++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: UnicodeOk

  Summary:  Checks if the platform will handle unicode versions of
            Win32 API calls.

  Args:     void

  Modifies: .

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


/*F+F++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: InitApplication

  Summary:  Initializes the application and registers its main window class.

  Args:     HINSTANCE hInstance)
              Handle to the first instance of the application.

  Modifies: .

  Returns:  BOOL.
              TRUE if success.
              FALSE if fail.
------------------------------------------------------------------------F-F*/
BOOL InitApplication(
       HINSTANCE hInstance)
{
  BOOL bOk;
  // The window class for all instances of the main frame window.
  WNDCLASSEX wcf;

  // Assign the appropriate values for this main frame window class.
  wcf.cbSize        = sizeof(WNDCLASSEX);
  wcf.cbClsExtra    = 0;            // No per-class extra data.
  wcf.cbWndExtra    = 0;            // No per-window extra data.
  wcf.hInstance     = hInstance;    // Application module instance.
  wcf.lpfnWndProc   = &WindowProc;  // Global Window Procedure (defined in
                                    // APPUTIL for all CVirWindows).
  wcf.hCursor       = LoadCursor(NULL, IDC_ARROW); // Load app cursor.
  wcf.hIcon         = (HICON) LoadIcon(            // Load app icon.
                                hInstance,
                                TEXT("AppIcon"));
  wcf.hIconSm       = (HICON) LoadImage(           // Load small icon.
                                hInstance,
                                TEXT("AppIcon"),
                                IMAGE_ICON,
                                16, 16,
                                0);
  wcf.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);  // Default backgnd color.
  wcf.style         = CS_HREDRAW | CS_VREDRAW;     // Class style(s).
  wcf.lpszClassName = TEXT(MAIN_WINDOW_CLASS_NAME_STR); // Class name.
  wcf.lpszMenuName  = TEXT(MAIN_WINDOW_CLASS_MENU_STR); // Menu name.

  // Register the window class and return FALSE if unsuccesful.
  bOk = RegisterClassEx(&wcf);

  return (bOk);
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: WinMain

  Summary:  The Windows main entry point function for this application.
            Initializes the application, the COM Libraries, and starts
            the main application message loop.

  Args:     HINSTANCE hInstance,
              Instance handle; a new one for each invocation of this app.
            HINSTANCE hPrevInstance,
              Instance handle of the previous instance. NULL in Win32.
            LPSTR lpCmdLine,
              Windows passes a pointer to the application's
              invocation command line.
            int nCmdShow)
              Bits telling the show state of the application.

  Returns:  int
              msg.wParam (upon exit of message loop).
              FALSE if this instance couldn't initialize and run.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern "C" int WINAPI WinMain(
                        HINSTANCE hInstance,
                        HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine,
                        int nCmdShow)
{
  CMainWindow* pWin = NULL;
  int iRun = TRUE;
  MSG msg;

  // If we were compiled for UNICODE and the platform seems OK with this
  // then proceed.  Else we error and exit the app.
  if (UnicodeOk())
  {
    // Call to initialize the COM Library.  Use the SUCCEEDED macro
    // to detect success.  If fail then exit app with error message.
    // The default apartment model is assumed and used.
    if (SUCCEEDED(CoInitialize(NULL)))
    {
      // If we succeeded in initializing the COM Library we proceed to
      // initialize the application.  If we can't init the application
      // then we signal shut down with an error message exit.
      iRun = InitApplication(hInstance);
      if (iRun)
      {
        // Assume we'll set iRun to TRUE when initialization is done.
        iRun = FALSE;

        // We are still go for running so we try to create a nifty new
        // CMainWindow object for this app instance.
        pWin = new CMainWindow;
        if (NULL != pWin)
        {
          // Setup the server control object.
          g_pServer = new CServer;
          if (NULL != g_pServer)
          {
            // Assign the server's instance handle.
            g_pServer->m_hInstServer = hInstance;

            // Check command line for switches to register or unregister
            // this server's managed components.   iRun will be set to 2
            // to signal an immediate and quiet exit of this application
            // if such registration or unregistration is requested.
            if (0 == lstrcmpiA(lpCmdLine, "-RegServer")
                || 0 == lstrcmpiA(lpCmdLine, "/RegServer"))
            {
              if (pWin->RegisterServer())
                iRun = 2;
            }
            else if (0 == lstrcmpiA(lpCmdLine, "-UnregServer")
                     || 0 == lstrcmpiA(lpCmdLine, "/UnregServer"))
            {
              if (pWin->UnregisterServer())
                iRun = 2;
            }

            if (FALSE == iRun)
            {
              // If we did not process a command line switch that
              // requires immediate exit, then initialize an instance of
              // the new CMainWindow. This entails creating the main window.
              if (pWin->InitInstance(hInstance, nCmdShow))
              {
                LOGF2("L<%X>: CmdLine Switches= %s",TID,lpCmdLine);
                // Create and register the Class Factories.  But only do so
                // if this application has been launched by COM as indicated
                // by the -Embedding command line switch.
                if (0 == lstrcmpiA(lpCmdLine, "-Embedding")
                    || 0 == lstrcmpiA(lpCmdLine, "/Embedding"))
                  iRun = g_pServer->OpenFactories();
              }
            }
          }
        }
      }

      switch (iRun)
      {
        case TRUE:
          {
            // If we initialized the app instance properly then we are still
            // go for running.  We then start up the main message pump for
            // the application.  The application will normally live hidden
            // as a local server.
            while (GetMessage(&msg, NULL, 0, 0))
            {
              TranslateMessage(&msg);
              DispatchMessage(&msg);
            }

            // We'll pass to the OS the reason why we exited the message
            // loop.
            iRun = msg.wParam;
          }
          break;

        case FALSE:
          // We failed to initialize the application--issue an error
          // messagebox.  Can't initialize or can't run stand-alone.
          ErrorBox(hInstance, NULL, IDS_APPINITFAILED);

          // Delete the CMainWindow object.
          DELETE_POINTER(pWin);

          // Pass the OS an error code of 1.
          iRun = 1;
          break;

        default:
          // Pass the OS an error code of 0.
          iRun = 0;
          break;
      }

      // We're exiting this app (either normally or by init failure) so
      // shut down the COM Library.
      CoUninitialize();
    }
    else
    {
      // We failed to Initialize the COM Library. Put up error message box
      // saying that COM Library couldn't be initialized.  Parent window
      // is desktop (ie, NULL). Exit the failed application (ie, by
      // returning FALSE to WinMain).
      ErrorBox(hInstance, NULL, IDS_COMINITFAILED);
    }
  }
  else
  {
    // If we were compiled for UNICODE but the platform has problems with
    // this then indicate an error and exit the app immediately.
    CHAR szMsg[MAX_STRING_LENGTH];

    if (LoadStringA(
          hInstance,
          IDS_NOUNICODE,
          szMsg,
          MAX_STRING_LENGTH))
    {
      MessageBoxA(
        NULL,
        szMsg,
        ERROR_TITLE_STR,
        MB_OK | MB_ICONEXCLAMATION);
    }
  }

  return iRun;
}
