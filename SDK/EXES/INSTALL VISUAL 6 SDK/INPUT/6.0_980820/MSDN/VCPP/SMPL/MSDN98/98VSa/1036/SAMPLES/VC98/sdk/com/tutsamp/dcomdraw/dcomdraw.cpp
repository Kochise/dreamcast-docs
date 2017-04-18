/*+==========================================================================
  File:      DCOMDRAW.CPP

  Summary:   This client loads and accesses the Connectable SharePaper
             component provided in a separate out-of-process COM Server
             (DCDSERVE built in the sibling DCDSERVE directory). Thus to
             run DCOMDRAW you must build DCDSERVE first. This client
             application is meant to exercise the DCDSERVE out-of-process
             server and to illustrate the use of a shared single COPaper
             COM object in a remote server. Distributed COM (DCOM) is
             used. The shared COPaper object can store its drawing data in
             the structured storage of a single compound file.

             The COPaper object maintains logic and data to represent a
             white sheet of free-form drawing paper. The behavior is much
             like other C++ scribble code samples except that the
             DCOMDRAW/DCDSERVE pair are implemented using custom COM
             objects, interfaces, and standard COM services. The client
             mouse activity is used to draw ink lines on the paper
             surface. The COPaper object keeps a memory array of the Ink
             data but performs no GUI display. This DCOMDRAW (largely
             within the CGuiPaper object) manages the display of the
             current drawing data.

             There is no GUI behavior in the server--it is all in this
             client.  This client instantiates one instance of the
             server's COPaper COM object and then allows the user to
             use the mouse to draw lines in the client area of the
             main window. If other clients are run they access the same
             shared drawing even if the server requested is on a remote
             machine. DCDSERVE registers its COPaper component so that
             there is one shared drawing per machine.

             For a comprehensive tutorial code tour of DCOMDRAW's contents
             and offerings see the tutorial DCOMDRAW.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the DCOMDRAW source code.
             For more details on the DCDSERVE.DLL that DCOMDRAW works with
             see the DCDSERVE.HTM file in the main tutorial directory.

  Classes:   CMainWindow.

  Functions: InitApplication, WinMain

  Origin:    8-23-97: atrent - Editor-inheritance from the CONCLIEN source.
               [Revised]

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
  We include OLE2.H because we will be calling the COM/OLE Libraries.
  We include OLECTL.H because it has definitions for connectable objects.
  We include INITGUID.H only once (here) in the entire app because we
    will be defining GUIDs and want them as constants in the data segment.
  We include COMMDLG.H because we will be using the Open File
    and potentially other Common dialogs.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include PAPINT.H and PAPGUIDS.H for the common paper-related Interface
    class, GUID, and CLSID specifications.
  We include GUIPAPER.H because it has the C++ class used for GUI display
    of the drawing paper.
  We include DCOMDRAW.H because it has class and resource definitions
    specific to this DCOMDRAW application.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <initguid.h>
#include <commdlg.h>
#include <apputil.h>
#include <papint.h>
#include <papguids.h>
#include "guipaper.h"
#include "dcomdraw.h"


// Here is a structure for storing the remote server info.
COSERVERINFO g_ServerInfo;
// Storage for the user entered remote machine name.
TCHAR g_szMachineName[MAX_PATH] = TEXT("");
OLECHAR g_wszMachineName[MAX_PATH];


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::CMainWindow

  Summary:  CMainWindow Constructor.

  Args:     .

  Returns:  .
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CMainWindow::CMainWindow()
{
  // Ensure these member variable strings are null strings.
  m_szFileName[0] = 0;

  // Fill in the Open File Name Common Dialog's OPENFILENAME structure.
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

  m_pMsgBox  = NULL;
  m_pGuiPaper = NULL;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::~CMainWindow

  Summary:  CMainWindow Destructor.  Destruction of the main window
            indicates that the application should quit and thus the
            PostQuitMessage API is called.

  Args:     .

  Returns:  .
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CMainWindow::~CMainWindow()
{
  // CMainWindow is derived from CVirWindow which traps the WM_DESTROY
  // message and causes a delete of CMainWindow which in turn causes this
  // destructor to run. The WM_DESTROY results when the window is destoyed
  // after a close of the window. Prior to exiting the main message loop:

  // We delete the CGuiPaper and CMsgBox objects that were made in
  // Initinstance.
  DELETE_POINTER(m_pGuiPaper);
  DELETE_POINTER(m_pMsgBox);

  // We then post a WM_QUIT message to cause an exit of the main
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
            LPSTR pszCmdLine,
              Pointer to the application's invocation command line.
            int nCmdShow)
              Command to pass to ShowWindow.

  Modifies: m_szHelpFile, m_pMsgBox.

  Returns:  BOOL.
              TRUE if succeeded.
              FALSE if failed.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CMainWindow::InitInstance(
       HINSTANCE hInstance,
       LPSTR pszCmdLine,
       int nCmdShow)
{
  BOOL bOk = FALSE;
  HWND hWnd = NULL;
  HRESULT hr = E_FAIL;

  // Create the Message Box and Message Log objects.
  m_pMsgBox = new CMsgBox;

  // Create the CGuiPaper C++ object.
  m_pGuiPaper = new CGuiPaper;

  if (NULL != m_pMsgBox && NULL != m_pGuiPaper)
  {
    // Note, the Create method sets the m_hWnd member so we don't
    // need to set it explicitly here first. Here is the create of this
    // window.  Size the window reasonably. Create sets both m_hInst and
    // m_hWnd. This creates the main client window.
    hWnd = Create(
             TEXT(MAIN_WINDOW_CLASS_NAME_STR),
             TEXT(MAIN_APP_NAME_STR),
             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
               | WS_MAXIMIZEBOX | WS_THICKFRAME,
             CW_USEDEFAULT,
             CW_USEDEFAULT,
             ::GetSystemMetrics(SM_CXSCREEN)*2/5,
             ::GetSystemMetrics(SM_CYSCREEN)*2/5,
             NULL,
             NULL,
             hInstance);
    if (NULL != hWnd)
    {
      // Init the new GuiPaper.
      bOk = m_pGuiPaper->Init(m_hInst, m_hWnd);
      if (bOk)
      {
        // Ensure the new window is shown on screen and content
        // is painted.
        ::ShowWindow(m_hWnd, nCmdShow);
        ::UpdateWindow(m_hWnd);

        // Build a path to where the help file should be (it should be in
        // the same directory as the .EXE but with the .HTM extension).
        MakeFamilyPath(hInstance, m_szHelpFile, TEXT(HELP_FILE_EXT));

        // Init the Message Box object.
        bOk = m_pMsgBox->Init(m_hInst, m_hWnd);

        // Connect the new Paper Sink in this client to receive event
        // calls from a COPaper source in the server.
        hr = m_pGuiPaper->ConnectPaperSink();
        if (SUCCEEDED(hr))
        {
          // Lock the paper object for drawing by this client. Can't draw
          // with mouse until doing this. Set the proper checkmark
          // indicator on the menu selections as well.
          hr = m_pGuiPaper->Lock(TRUE);
          if (SUCCEEDED(hr))
          {
            // Try to load drawing data from local COPaper's compound file.
            hr = m_pGuiPaper->Load();
          }
          else
          {
            // Shared drawing already loaded by another client.
            // Paint this client's window with the shared drawing.
            hr = m_pGuiPaper->PaintWin();
          }
        }
      }
    }
  }

  bOk = SUCCEEDED(hr);

  if (!bOk)
  {
    DELETE_POINTER(m_pMsgBox);
    DELETE_POINTER(m_pGuiPaper);
  }

  return (bOk);
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
  HRESULT hr;

  switch (LOWORD(wParam))
  {
    //----------------------------------------------------------------------
    // Handle File Menu Commands.
    //----------------------------------------------------------------------
    case IDM_FILE_LOADREMOTE:
      // Ask the user for the name of the machine where the remote
      // DCDSERVE server is.
      hr = m_pGuiPaper->LoadRemote();
      if (FAILED(hr))
        Beep(2000, 200);
      break;
    case IDM_FILE_LOADLOCAL:
      // Ask COPaper to load the drawing from the local DCDSERVE server.
      hr = m_pGuiPaper->LoadLocal();
      if (FAILED(hr))
        Beep(2000, 200);
      break;
    case IDM_FILE_SAVE:
      // Ask COPaper to save the current shared drawing.
      hr = E_FAIL;
      if (m_pGuiPaper->Master())
        hr = m_pGuiPaper->Save();
      if (FAILED(hr))
        Beep(2000, 200);
      break;
    case IDM_FILE_EXIT:
      // The user commands us to exit this application so we tell the
      // Main window to close itself.
      ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
      break;

    //----------------------------------------------------------------------
    // Handle Draw Menu Choice Commands.
    //----------------------------------------------------------------------
    case IDM_DRAW_MASTER:
      // Lock the paper object for drawing by this client. Can't draw
      // with mouse until doing this. This makes this client the master
      // client that currently owns the drawing. Drawing activity in the
      // master is echoed to any other connected slave clients.
      hr = E_FAIL;
      if (!m_pGuiPaper->Master())
        hr = m_pGuiPaper->Lock(TRUE);
      if (FAILED(hr))
        Beep(2000, 200);
      break;
    case IDM_DRAW_SLAVE:
      // Unlock the paper object for drawing by this client. This
      // makes this client a slave to a separate other master client.
      hr = E_FAIL;
      if (m_pGuiPaper->Master())
        hr = m_pGuiPaper->Lock(FALSE);
      if (FAILED(hr))
        Beep(2000, 200);
      break;
    case IDM_DRAW_REDRAW:
      // Ask Paper object to redraw its current content.
      m_pGuiPaper->ClearWin();
      m_pGuiPaper->PaintWin();
      break;
    case IDM_DRAW_ERASE:
      // Ask Paper object to erase its current content and if it can
      // Clear drawing display window.
      hr = E_FAIL;
      if (m_pGuiPaper->Master())
        hr = m_pGuiPaper->Erase();
      if (FAILED(hr))
        Beep(2000, 200);
      break;

    //----------------------------------------------------------------------
    // Handle Pen Menu Commands.
    //----------------------------------------------------------------------
    case IDM_PEN_COLOR:
      // Select Ink drawing color using ChooseColor common dialog.
      hr = E_FAIL;
      if (m_pGuiPaper->Master())
      {
        COLORREF crNewColor = m_pGuiPaper->PickColor();
        hr = m_pGuiPaper->InkColor(crNewColor);
      }
      if (FAILED(hr))
        Beep(2000, 200);
      break;
    case IDM_PEN_THIN:
      // Select thin Ink width. Set menu check indicator.
      hr = E_FAIL;
      if (m_pGuiPaper->Master())
        hr = m_pGuiPaper->InkWidth(INK_THIN);
      if (FAILED(hr))
        Beep(2000, 200);
      break;
    case IDM_PEN_MEDIUM:
      // Select medium Ink width. Set menu check indicator.
      hr = E_FAIL;
      if (m_pGuiPaper->Master())
        hr = m_pGuiPaper->InkWidth(INK_MEDIUM);
      if (FAILED(hr))
        Beep(2000, 200);
      break;
    case IDM_PEN_THICK:
      // Select thick Ink width. Set menu check indicator.
      hr = E_FAIL;
      if (m_pGuiPaper->Master())
        hr = m_pGuiPaper->InkWidth(INK_THICK);
      if (FAILED(hr))
        Beep(2000, 200);
      break;

    //----------------------------------------------------------------------
    // Handle Help Menu Commands.
    //----------------------------------------------------------------------
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
    case IDM_HELP_TUTSERVER:
      // Call the APPUTIL utility function, ReadTutorial, to Browse the HTML
      // tutorial narrative file associated with the DCDSERVE COM server.
      ReadTutorial(m_hInst, m_hWnd, TEXT(SERVER_TUTFILE_STR));
      break;
    case IDM_HELP_TUTMARSH:
      // Call the APPUTIL utility function, ReadTutorial, to Browse the HTML
      // tutorial narrative file associated with the DCDMARSH COM server.
      ReadTutorial(m_hInst, m_hWnd, TEXT(MARSHAL_TUTFILE_STR));
      break;
    case IDM_HELP_READSOURCE:
      // Call the APPUTIL utility function ReadSource to allow the
      // user to open and read any of the source files of DCOMDRAW.
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
  Method:   CDlgLoadRemote::DialogProc

  Summary:  Dialog proc for the Remote Load dialog box.  This DialogProc
            method definition overrides the same-named pure virtual
            function in abstract base class CVirDialog thus giving unique
            message dispatching behavior to this derivation of CVirDialog.
            The remaining behavior of CDlgRemoteInfo is inherited from
            CVirDialog and is common to all CVirDialogs.

  Args:     HWND hWndDlg,
              Handle to the dialog.
            UINT uMsg,
              Windows message to dialog.
            WPARAM wParam,
              First message parameter (word sized).
            LPARAM lParam)
              Second message parameter (long sized).

  Returns:  BOOL.  TRUE if message was handled; FALSE otherwise.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CDlgLoadRemote::DialogProc(
       HWND hWndDlg,
       UINT uMsg,
       WPARAM wParam,
       LPARAM lParam)
{
  BOOL bResult = TRUE;
  HWND hCtrl = GetDlgItem(hWndDlg, IDC_EDIT_MACHINE);

  switch (uMsg)
  {
    case WM_INITDIALOG:
      SetDlgItemText(hWndDlg, IDC_EDIT_MACHINE, g_szMachineName);
      SetFocus(hCtrl);
      bResult = FALSE;
      break;

    case WM_COMMAND:
      {
        WORD wCmd = LOWORD(wParam);

        if (wCmd == IDOK)
        {
          // Obtain the machine name from the edit control.
          GetDlgItemText(hWndDlg, IDC_EDIT_MACHINE, g_szMachineName, MAX_PATH);
#if !defined(UNICODE)
          // Convert to WideChar Unicode if we are NOT compiled for Unicode.
          AnsiToUc(g_szMachineName, g_wszMachineName, 0);
#endif
          ::EndDialog(hWndDlg, IDOK);
        }
        else if (wCmd == IDCANCEL)
          ::EndDialog(hWndDlg, IDCANCEL);
      }
      break;

    default:
      bResult = FALSE;
      break;
  }

  return(bResult);
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

    case WM_ACTIVATE:
      // If we were newly activated by a mouse click then don't just sit
      // there--re-paint. This is needed when another window was topped
      // over part of DCOMDRAW and the user then topped DCOMDRAW using
      // a mouse click on the visible part of DCOMDRAW. In any case let
      // the windows default WindowProc handle this message to set
      // keyboard focus to the newly active window.
      if (WA_CLICKACTIVE == LOWORD(wParam))
        m_pGuiPaper->PaintWin();
      lResult = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
      break;

    case WM_MEASUREITEM:
      // Get setup for painting text in this window. For later evolution.
      {
        LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam;
        lpmis->itemHeight = m_tm.tmHeight + m_tm.tmExternalLeading;
        lpmis->itemWidth = m_lWidth;
        lResult = TRUE;
      }

    case WM_SIZE:
      // Handle a resize of this window.
      if (m_pGuiPaper->Master())
      {
        m_lWidth = LOWORD(lParam);
        m_lHeight = HIWORD(lParam);
        // Inform CGuiPaper of the change.
        m_pGuiPaper->Resize(m_lWidth, m_lHeight);
      }
      break;

    case WM_PAINT:
      // If something major happened repaint the whole window.
      {
        PAINTSTRUCT ps;

        if(BeginPaint(m_hWnd, &ps))
        {
          m_pGuiPaper->PaintWin();
          EndPaint(m_hWnd, &ps);
        }
      }
      break;

    case WM_LBUTTONDOWN:
      // Start sequence of ink drawing to the paper.
      if (m_pGuiPaper->Master())
        m_pGuiPaper->InkStart(LOWORD(lParam), HIWORD(lParam));
      break;

    case WM_MOUSEMOVE:
      // Draw inking sequence data.
      if (m_pGuiPaper->Master())
        m_pGuiPaper->InkDraw(LOWORD(lParam), HIWORD(lParam));
      break;

    case WM_LBUTTONUP:
      // Stop an ink drawing sequence.
      if (m_pGuiPaper->Master())
        m_pGuiPaper->InkStop(LOWORD(lParam), HIWORD(lParam));
      break;

    case WM_COMMAND:
      // Dispatch and handle any Menu command messages received.
      lResult = DoMenu(wParam, lParam);
      break;

    case WM_CHAR:
      if (wParam == 0x1b)
      {
        // Exit this app if user hits ESC key.
        ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
      }
      break;

    case WM_CLOSE:
      // The user selected Close on the main window's System menu
      // or Exit on the File menu.
      // If there is ink data that has not been saved then ask user
      // if it should be saved. If user cancels then cancel the exit.
      if (IDCANCEL == m_pGuiPaper->AskSave())
        break;
    case WM_QUIT:
      // If the app is being quit then close any associated help windows.
    default:
      // Defer all messages NOT handled above to the Default Window Proc.
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
  wcf.hCursor       = NULL;                        // Load app cursor.
  wcf.hIcon         = (HICON) LoadIcon(            // Load app icon.
                                hInstance,
                                TEXT("AppIcon"));
  wcf.hIconSm       = (HICON) LoadImage(           // Load small icon.
                                hInstance,
                                TEXT("AppIcon"),
                                IMAGE_ICON,
                                16, 16,
                                0);
  wcf.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); // Backgnd color.
  wcf.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Class style(s).
  wcf.lpszClassName = TEXT(MAIN_WINDOW_CLASS_NAME_STR);   // Class name.
  wcf.lpszMenuName  = TEXT(MAIN_WINDOW_CLASS_MENU_STR);   // Menu name.

  // Register the window class and return FALSE if unsuccesful.
  bOk = RegisterClassEx(&wcf);

  // Zero the g_ServerInfo structure.
  memset(&g_ServerInfo, 0, sizeof(COSERVERINFO));

  // Init the remote machine name.
  g_wszMachineName[0] = 0;
#ifdef UNICODE
  g_ServerInfo.pwszName = &g_szMachineName[0];
#else
  g_ServerInfo.pwszName = &g_wszMachineName[0];
#endif

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
            LPSTR pszCmdLine,
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
                        LPSTR pszCmdLine,
                        int nCmdShow)
{
  CMainWindow* pWin = NULL;
  MSG msg;
  HACCEL hAccel;
  HRESULT hr;
  int iRun = FALSE;

  // If we were compiled for UNICODE and the platform seems OK with this
  // then proceed.  Else we error and exit the app.
  if (UnicodeOk())
  {
    // Call to initialize the COM Library.  Use the SUCCEEDED macro
    // to detect success.  If fail then exit app with error message.
    // Tell COM that this client process will use the Single Threaded
    // Apartment model.
    if (SUCCEEDED(CoInitialize(NULL)))
    {
      // Ensure that DCOM (Distributed COM) is installed.
      if (DComOk())
      {
        // Initialize for Client process security. Allow COPaper to
        // call back into the client (ie, the client can impersonate
        // the server identity).
        hr = CoInitializeSecurity(
               NULL,                        //Points to security descriptor
               -1,                          //Count of entries in asAuthSvc
               NULL,                        //Array of names to register
               NULL,                        //Reserved for future use
               RPC_C_AUTHN_LEVEL_NONE,      //Default authentication level
                                            // for proxies
               RPC_C_IMP_LEVEL_IMPERSONATE, //Default impersonation level
                                            // for proxies
               NULL,                        //Reserved; must be set to NULL
               EOAC_NONE,                   //Additional client or
                                            // server-side capabilities
               NULL);                       //Reserved for future use
        if (SUCCEEDED(hr))
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
              if (pWin->InitInstance(hInstance, pszCmdLine, nCmdShow))
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
        }

        if (iRun)
        {
          // If we initialized the app instance properly then we are still
          // go for running.  We then start up the main message pump for
          // the application.
          while (GetMessage(&msg, NULL, 0, 0))
          {
            if (!TranslateAccelerator(pWin->GetHwnd(), hAccel, &msg))
            {
              TranslateMessage(&msg);
              DispatchMessage(&msg);
            }
          }

          // We also ask COM to unload any unused COM Servers, including our
          // friend, DCDSERVE.
          CoFreeUnusedLibraries();

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
        // If DCOM isn't installed then indicate an error
        // and exit the app immediately.
        ErrorBox(hInstance, NULL, IDS_NODCOM);
      }
    }
    else
    {
      // We failed to Initialize the COM Library. Put up error message
      // box saying that COM Library couldn't be initialized.  Parent
      // window is desktop (ie, NULL). Exit the failed application
      // (ie, by returning FALSE to WinMain).
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
