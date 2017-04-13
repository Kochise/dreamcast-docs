/*+==========================================================================
  File:      DLLUSER.CPP

  Summary:   Based largely on the EXESKEL.EXE application code, this
             module is meant to implicitly link to the DLLSKEL.DLL
             and illustrate the use (by this DLLUSER app) of the two
             exported calls from that DLL: DllHelloBox and DllAboutBox.
             To this end, DLLUSER provides a Test menu with two menu
             selections that exercise each of those calls.

             Since it is only a slight augmentation over the EXESKEL code
             sample, DLLUSER in turn can be considered as another
             application skeleton in a graduated sequence of skeletal
             evolution.  Each capable of serving as a point of departure
             in building more sophisticated applications.

             For a comprehensive tutorial code tour of DLLUSER's
             contents and offerings see the tutorial DLLUSER.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the DLLUSER source code.
             For more details on the DLLSKEL.DLL that DLLUSER works with
             see the DLLSKEL.HTM file in the main tutorial directory.

  Classes:   CMainWindow

  Functions: InitApplication, WinMain

  Origin:    8-3-95: atrent - Editor-inheritance from the EXESKEL source.

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
  We include OLE2.H because we will be calling the COM
    Library's CoInitialize and CoUnInitialize calls.
  We include COMMDLG.H because we will be using the Open File and
    potentially other Common dialogs.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include DLLUSER.H because it has class and resource definitions
    specific to this DLLUSER application.
  We include DLLSKEL.H because we will be showcasing the use of service
    functions provided by DLLSKEL.DLL.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <commdlg.h>
#include <apputil.h>
#include "dlluser.h"
#include "dllskel.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::CMainWindow

  Summary:  CMainWindow Constructor.

  Args:     .

  Modifies: .

  Returns:  .
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CMainWindow::CMainWindow()
{
  // Ensure these member variable strings are null strings.
  m_szFileName[0] = 0;
  m_szFileTitle[0] = 0;

  // Fill in the Common Dialog's OPENFILENAME structure.
  m_ofnFile.lStructSize = sizeof(OPENFILENAME);
  m_ofnFile.hwndOwner = m_hWnd;
  m_ofnFile.hInstance = m_hInst;
  m_ofnFile.lpstrFilter = TEXT(OFN_DEFAULTFILES_STR);
  m_ofnFile.lpstrCustomFilter = NULL;
  m_ofnFile.nMaxCustFilter = 0;
  m_ofnFile.nFilterIndex = 1;
  m_ofnFile.lpstrFile = m_szFileName;
  m_ofnFile.nMaxFile = MAX_PATH;
  m_ofnFile.lpstrInitialDir = TEXT(".");
  m_ofnFile.lpstrFileTitle = m_szFileTitle;
  m_ofnFile.nMaxFileTitle = MAX_PATH;
  m_ofnFile.lpstrTitle = TEXT(OFN_DEFAULTTITLE_STR);
  m_ofnFile.lpstrDefExt = NULL;
  m_ofnFile.Flags = OFN_HIDEREADONLY;

  // Null the Message object pointer.
  m_pMsgBox = NULL;
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
  // after a close of the window. Prior to exiting the main message loop
  // we delete the CMsgBox object that was made in Initinstance.
  DELETE_POINTER(m_pMsgBox);

  // We post a WM_QUIT message to cause an exit of the main thread's
  // message loop and an exit of this instance of the application.
  PostQuitMessage(0);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::InitInstance

  Summary:  Instantiates an instance of the main application window.
            This method must be called only once, immediately after
            window class construction.  We take care to delete 'this'
            CMainWindow if we must return the error condition FALSE.

  Args:     HINSTANCE hInstance,
              Handle of the application instance.
            int nCmdShow)
              Command to pass to ShowWindow.

  Modifies: m_szHelpFile, m_pMsgBox.

  Returns:  BOOL.
              TRUE if succeeded.
              FALSE if failed.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CMainWindow::InitInstance(
       HINSTANCE hInstance,
       int nCmdShow)
{
  BOOL bResult = FALSE;

  // Create the Message Box object.
  m_pMsgBox = new CMsgBox;
  HWND hWnd;

  if (NULL != m_pMsgBox)
  {
    // Note, the Create method sets the m_hWnd member so we don't
    //   need to set it explicitly here first.

    // Here is the create of this window.  Size the window reasonably.
    //   Create sets both m_hInst and m_hWnd.
    hWnd = Create(
             TEXT(MAIN_WINDOW_CLASS_NAME_STR),
             TEXT(MAIN_WINDOW_TITLE_STR),
             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
               | WS_MAXIMIZEBOX | WS_THICKFRAME,
             CW_USEDEFAULT,
             CW_USEDEFAULT,
             ::GetSystemMetrics(SM_CXSCREEN)*2/5,
             ::GetSystemMetrics(SM_CYSCREEN)*2/5,
             NULL,
             NULL,
             hInstance);
    if (hWnd)
    {
      // Ensure the new window is shown on screen and its content is painted.
      ::ShowWindow(m_hWnd, nCmdShow);
      ::UpdateWindow(m_hWnd);

      // Build a path to where the help file should be (it should be in
      // the same directory as the .EXE but with the .HTM extension.
      MakeFamilyPath(hInstance, m_szHelpFile, TEXT(HELP_FILE_EXT));

      // Init the Message Box object and signal we succeeded initializing
      // the application.
      if (m_pMsgBox->Init(m_hInst, m_hWnd))
        bResult = TRUE;
    }
  }

  if (!bResult)
  {
    DELETE_POINTER(m_pMsgBox);
  }

  return (bResult);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::DoMenu

  Summary:  Dispatch and handle the main menu commands.

  Args:     WPARAM wParam,
              First message parameter (word sized).
            LPARAM lParam)
              Second message parameter (long sized).

  Modifies: m_ofnFile, ...

  Returns:  LRESULT
              Standard Windows WindowProc return value.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CMainWindow::DoMenu(
          WPARAM wParam,
          LPARAM lParam)
{
  LRESULT lResult = FALSE;

  switch (LOWORD(wParam))
  {
    case IDM_FILE_EXIT:
      // The user commands us to exit this application so we tell the
      // Main window to close itself.
      ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
      break;

    case IDM_TEST_DLLHELLO:
      // Call the DLLSKEL DLL to say hello from it.
      ::DllHelloBox(m_hWnd);
      break;

    case IDM_TEST_DLLABOUT:
      // Call the DLLSKEL DLL to show the DLL's About Box.
      ::DllAboutBox(m_hWnd);
      break;

    // Handle Help Menu Commands.
    case IDM_HELP_CONTENTS:
      // We have some stubbed support here for bringing up the online
      // Help for this application.
      ReadHelp(m_hWnd, m_szHelpFile);
      break;

    case IDM_HELP_TUTORIAL:
      // Call the APPUTIL utility function, ReadTutorial, to Browse the HTML
      // tutorial narrative file associated with this tutorial code sample.
      ReadTutorial(m_hInst, m_hWnd, TEXT(HTML_FILE_EXT));
      break;

    case IDM_HELP_TUTDLL:
      // Call the APPUTIL utility function, ReadTutorial, to Browse the HTML
      // tutorial narrative file associated with the DLL server.
      ReadTutorial(m_hInst, m_hWnd, TEXT(DLL_TUTFILE_STR));
      break;

    case IDM_HELP_READSOURCE:
      // Call the APPUTIL utility function ReadSource to allow the
      // user to open and read any of the source files of DLLUSER.
      ReadSource(m_hWnd, &m_ofnFile);
      break;

    case IDM_HELP_ABOUT:
      {
        CAboutBox dlgAboutBox;

        // Show the standard About Box dialog for this EXE by telling the
        // dialog C++ object to show itself by invoking its ShowDialog
        // method.  Pass it this EXE instance and the parent window handle.
        // Use a dialog resource ID for the dialog template stored in
        // this EXE module's resources.
        dlgAboutBox.ShowDialog(
          m_hInst,
          MAKEINTRESOURCE(IDM_HELP_ABOUT),
          m_hWnd);
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
      {
        // Setup for painting text in this window.
        HDC hdc = GetDC(m_hWnd);
        ::GetTextMetrics(hdc, &m_tm);
        ::ReleaseDC(m_hWnd, hdc);
      }
      break;

    case WM_MEASUREITEM:
      // Get setup for painting text in this window.
      {
        LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam;
        lpmis->itemHeight = m_tm.tmHeight + m_tm.tmExternalLeading;
        lpmis->itemWidth = m_wWidth;
        lResult = TRUE;
      }

    case WM_SIZE:
      // Handle a resize of this window.
      m_wWidth = LOWORD(lParam);
      m_wHeight = HIWORD(lParam);
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
  Function: InitApplication

  Summary:  Initializes the application and registers its main window
            class. InitApplication is called only once (in WinMain).

  Args:     HINSTANCE hInstance)
              Handle to the first instance of the application.

  Returns:  BOOL.
              TRUE if success.
              FALSE if fail.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
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
extern "C" int PASCAL WinMain(
                        HINSTANCE hInstance,
                        HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine,
                        int nCmdShow)
{
  CMainWindow* pWin;
  MSG msg;
  HACCEL hAccel;
  int iRun = FALSE;

  // If we were compiled for UNICODE and the platform seems OK with this
  // then proceed.  Else we error and exit the app.
  if (UnicodeOk())
  {
    // Call to initialize the COM Library.  Use the SUCCEEDED macro
    // to detect success.  If fail then exit app with error message.
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
          // Now we initialize an instance of the new CMainWindow.
          // This includes creating the main window.
          if (pWin->InitInstance(hInstance, nCmdShow))
          {
            // Load the keyboard accelerators from the resources.
            hAccel = LoadAccelerators(hInstance, TEXT("AppAccel"));
            if (NULL != hAccel)
            {
              // Signal App Initialization is successfully done.
              iRun = TRUE;
            }
          }
        }
      }

      if (iRun)
      {
        // If we initialized the app instance properly then we are still
        // go for running.  We then start up the main message pump for
        // the application.
        while (GetMessage(&msg, NULL, 0, 0))
        {
          if (!TranslateAccelerator(
                 pWin->GetHwnd(),
                 hAccel,
                 &msg))
          {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
          }
        }

        // We'll pass to Windows the reason why we exited the message loop.
        iRun = msg.wParam;
      }
      else
      {
        // We failed to initialize the application. Put up error message
        // box saying that application couldn't be initialized.  Parent
        // window is desktop (ie, NULL). Exit the failed application
        // (ie, by returning FALSE to WinMain).
        ErrorBox(hInstance, NULL, IDS_APPINITFAILED);

        // Delete the CMainWindow object.
        DELETE_POINTER(pWin);
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
          IDS_UNICODEFAIL,
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
