/*+==========================================================================
  File:      STOCLIEN.CPP

  Summary:   This client loads and accesses the Connectable DllPaper
             component provided in a separate in-process COM Server
             (STOSERVE built in the sibling STOSERVE directory). Thus to
             run STOCLIEN you must build STOSERVE first. This client
             application is meant to exercise the STOSERVE in-process
             server and to illustrate the use of the compound file storage
             supported by both the CPapFile C++ object in STOCLIEN and the
             COPaper COM object in the STOSERVE server. Both client and
             server cooperate to use compound files to store drawing
             paper data.

             The COPaper object maintains logic and data to represent a
             white sheet of free-form drawing paper. The behavior is much
             like other C++ scribble code samples except that the
             STOCLIEN/STOSERVE pair are implemented using custom COM
             objects, interfaces, and standard COM services. The client
             mouse activity is used to draw ink lines on the paper
             surface. The COPaper object keeps a memory array of the Ink
             data but performs no GUI display. This STOCLIEN (largely
             within the CGuiPaper object) manages the display of the
             current drawing data.

             There is no GUI behavior in the server--it is all in this
             client.  This client instantiates one instance of the
             server's COPaper COM object and then allows the user to
             use the mouse to draw lines in the client area of the
             main window.

             For a comprehensive tutorial code tour of STOCLIEN's contents
             and offerings see the tutorial STOCLIEN.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the STOCLIEN source code.
             For more details on the STOSERVE.DLL that STOCLIEN works with
             see the STOSERVE.HTM file in the main tutorial directory.

  Classes:   CMainWindow.

  Functions: InitApplication, WinMain

  Origin:    6-10-96: atrent - Editor-inheritance from the CONCLIEN source.

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
  We include IPAPER.H and PAPGUIDS.H for the common paper-related Interface
    class, GUID, and CLSID specifications.
  We include PAPFILE.H because it has the C++ class used for compound file
    storage of drawing paper data.
  We include GUIPAPER.H because it has the C++ class used for GUI display
    of the drawing paper.
  We include STOCLIEN.H because it has class and resource definitions
    specific to this STOCLIEN application.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <initguid.h>
#include <commdlg.h>
#include <apputil.h>
#include <ipaper.h>
#include <papguids.h>
#include "papfile.h"
#include "guipaper.h"
#include "stoclien.h"


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
  m_szFileTitle[0] = 0;

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
    if (NULL != hWnd)
    {
      if (pszCmdLine[0] == 0)
        pszCmdLine = NULL;

#if defined(UNICODE)
      {
        WCHAR wszUc[MAX_PATH];

        if (pszCmdLine)
        {
          // Convert Ansi command line string to Unicode if we are
          // compiled for Unicode.
          AnsiToUc(pszCmdLine, wszUc, MAX_PATH);
          // Init the new GuiPaper.
          bOk = m_pGuiPaper->Init(m_hInst, m_hWnd, wszUc);
        }
        else
          bOk = m_pGuiPaper->Init(m_hInst, m_hWnd, NULL);
      }
#else
      // Init the new GuiPaper.
      bOk = m_pGuiPaper->Init(m_hInst, m_hWnd, pszCmdLine);
#endif

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

        // Lock the paper object for drawing by this client. Can't draw
        // with mouse until doing this. Set the proper checkmark
        // indicator on the menu selections as well.
        hr = m_pGuiPaper->DrawOn();
        if (SUCCEEDED(hr))
        {
          HMENU hMenu  = ::GetMenu(m_hWnd);

          ::CheckMenuItem(
              hMenu,
              IDM_DRAW_ON,
              MF_BYCOMMAND | MF_CHECKED);
          ::CheckMenuItem(
              hMenu,
              IDM_DRAW_OFF,
              MF_BYCOMMAND | MF_UNCHECKED);

          // Connect the new Paper Sink in this client to receive event
          // calls from a COPaper source in the server.
          hr = m_pGuiPaper->ConnectPaperSink();
          if (SUCCEEDED(hr))
          {
            ::CheckMenuItem(
                hMenu,
                IDM_SINK_ON,
                MF_BYCOMMAND | MF_CHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_SINK_OFF,
                MF_BYCOMMAND | MF_UNCHECKED);

            // Try to load the paper data compound file. Either the
            // default STOCLIEN.PAP or the one specified on the
            // invocation command line.
            m_pGuiPaper->Load();
          }
        }
      }
    }
  }

  if (!bOk)
  {
    DELETE_POINTER(m_pMsgBox);
    DELETE_POINTER(m_pGuiPaper);
  }

  bOk = SUCCEEDED(hr);

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
  HMENU hMenu  = ::GetMenu(m_hWnd);

  switch (LOWORD(wParam))
  {
    //----------------------------------------------------------------------
    // Handle File Menu Commands.
    //----------------------------------------------------------------------
    case IDM_FILE_OPEN:
      // Open existing compound file and ask COPaper to load itself from it.
      m_pGuiPaper->Open();
      break;
    case IDM_FILE_SAVE:
      // Open current compound file and ask COPaper to save itself to it.
      m_pGuiPaper->Save();
      break;
    case IDM_FILE_SAVEAS:
      // Create new compound file and ask COPaper to save itself to it.
      m_pGuiPaper->SaveAs();
      break;
    case IDM_FILE_EXIT:
      // The user commands us to exit this application so we tell the
      // Main window to close itself.
      ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
      break;

    //----------------------------------------------------------------------
    // Handle Draw Menu Choice Commands.
    //----------------------------------------------------------------------
    case IDM_DRAW_ON:
      // Lock the paper object for drawing by this client. Can't draw
      // with mouse until doing this. Set the proper checkmark indicator
      // on the menu selections as well.
      {
        HRESULT hr;
        HMENU hMenu  = ::GetMenu(m_hWnd);
        BOOL bDrawOn = ::GetMenuState(
                           hMenu,
                           IDM_DRAW_ON,
                           MF_BYCOMMAND) & MF_CHECKED;
        if (!bDrawOn)
        {
          hr = m_pGuiPaper->DrawOn();
          if (SUCCEEDED(hr))
          {
            ::CheckMenuItem(
                hMenu,
                IDM_DRAW_ON,
                MF_BYCOMMAND | MF_CHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_DRAW_OFF,
                MF_BYCOMMAND | MF_UNCHECKED);
            // Ask Paper object to redraw its current content.
            m_pGuiPaper->PaintWin();
          }
        }
      }
      break;
    case IDM_DRAW_OFF:
      // Unlock the paper object for drawing by this client. Set the
      // proper checkmark indicator on the menu selections as well.
      {
        HRESULT hr;
        HMENU hMenu  = ::GetMenu(m_hWnd);
        BOOL bDrawOff = ::GetMenuState(
                            hMenu,
                            IDM_DRAW_OFF,
                            MF_BYCOMMAND) & MF_CHECKED;
        if (!bDrawOff)
        {
          hr = m_pGuiPaper->DrawOff();
          if (SUCCEEDED(hr))
          {
            ::CheckMenuItem(
                hMenu,
                IDM_DRAW_ON,
                MF_BYCOMMAND | MF_UNCHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_DRAW_OFF,
                MF_BYCOMMAND | MF_CHECKED);
          }
        }
      }
      break;
    case IDM_DRAW_REDRAW:
      // Ask Paper object to redraw its current content.
      m_pGuiPaper->PaintWin();
      break;
    case IDM_DRAW_ERASE:
      // Ask Paper object to erase its current content and if it can
      // Clear drawing display window.
      m_pGuiPaper->Erase();
      break;

    //----------------------------------------------------------------------
    // Handle Pen Menu Commands.
    //----------------------------------------------------------------------
    case IDM_PEN_COLOR:
      // Select Ink drawing color using ChooseColor common dialog.
      {
        COLORREF crNewColor = m_pGuiPaper->PickColor();
        m_pGuiPaper->InkColor(crNewColor);
      }
      break;
    case IDM_PEN_THIN:
      // Select thin Ink width. Set menu check indicator.
      {
        HRESULT hr;
        HMENU hMenu  = ::GetMenu(m_hWnd);
        BOOL bOn = ::GetMenuState(
                       hMenu,
                       IDM_PEN_THIN,
                       MF_BYCOMMAND) & MF_CHECKED;
        if (!bOn)
        {
          hr = m_pGuiPaper->InkWidth(INK_THIN);
          if (SUCCEEDED(hr))
          {
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_THIN,
                MF_BYCOMMAND | MF_CHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_MEDIUM,
                MF_BYCOMMAND | MF_UNCHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_THICK,
                MF_BYCOMMAND | MF_UNCHECKED);
          }
        }
      }
      break;
    case IDM_PEN_MEDIUM:
      // Select medium Ink width. Set menu check indicator.
      {
        HRESULT hr;
        HMENU hMenu  = ::GetMenu(m_hWnd);
        BOOL bOn = ::GetMenuState(
                       hMenu,
                       IDM_PEN_MEDIUM,
                       MF_BYCOMMAND) & MF_CHECKED;
        if (!bOn)
        {
          hr = m_pGuiPaper->InkWidth(INK_MEDIUM);
          if (SUCCEEDED(hr))
          {
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_MEDIUM,
                MF_BYCOMMAND | MF_CHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_THICK,
                MF_BYCOMMAND | MF_UNCHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_THIN,
                MF_BYCOMMAND | MF_UNCHECKED);
          }
        }
      }
      break;
    case IDM_PEN_THICK:
      // Select thick Ink width. Set menu check indicator.
      {
        HRESULT hr;
        HMENU hMenu  = ::GetMenu(m_hWnd);
        BOOL bOn = ::GetMenuState(
                       hMenu,
                       IDM_PEN_THICK,
                       MF_BYCOMMAND) & MF_CHECKED;
        if (!bOn)
        {
          hr = m_pGuiPaper->InkWidth(INK_THICK);
          if (SUCCEEDED(hr))
          {
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_THICK,
                MF_BYCOMMAND | MF_CHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_MEDIUM,
                MF_BYCOMMAND | MF_UNCHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_THIN,
                MF_BYCOMMAND | MF_UNCHECKED);
          }
        }
      }
      break;

    //----------------------------------------------------------------------
    // Handle Sink Menu Commands.
    //----------------------------------------------------------------------
    case IDM_SINK_ON:
      // Connect the client's event Paper Sink to the COPaper event
      // source in the server. Set the proper checkmark indicator on
      // the menu selections as well.
      {
        HRESULT hr;
        HMENU hMenu  = ::GetMenu(m_hWnd);
        BOOL bConnected = ::GetMenuState(
                              hMenu,
                              IDM_SINK_ON,
                              MF_BYCOMMAND) & MF_CHECKED;
        if (!bConnected)
        {
          hr = m_pGuiPaper->ConnectPaperSink();
          if (SUCCEEDED(hr))
          {
            ::CheckMenuItem(
                hMenu,
                IDM_SINK_ON,
                MF_BYCOMMAND | MF_CHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_SINK_OFF,
                MF_BYCOMMAND | MF_UNCHECKED);
          }
        }
      }
      break;
    case IDM_SINK_OFF:
      // Disconnect the client's event Paper Sink from the COPaper
      // event source in the server. Set the proper checkmark indicator
      // on the menu selections as well.
      {
        HRESULT hr;
        HMENU hMenu  = ::GetMenu(m_hWnd);
        BOOL bDisConnected = ::GetMenuState(
                                hMenu,
                                IDM_SINK_OFF,
                                MF_BYCOMMAND) & MF_CHECKED;
        if (!bDisConnected)
        {
          hr = m_pGuiPaper->DisconnectPaperSink();
          if (SUCCEEDED(hr))
          {
            ::CheckMenuItem(
                hMenu,
                IDM_SINK_ON,
                MF_BYCOMMAND | MF_UNCHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_SINK_OFF,
                MF_BYCOMMAND | MF_CHECKED);
          }
        }
      }
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
      // tutorial narrative file associated with the STOSERVE COM server.
      ReadTutorial(m_hInst, m_hWnd, TEXT(SERVER_TUTFILE_STR));
      break;
    case IDM_HELP_READSOURCE:
      // Call the APPUTIL utility function ReadSource to allow the
      // user to open and read any of the source files of STOCLIEN.
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
      break;

    case WM_ACTIVATE:
      // If we were newly activated by a mouse click then don't just sit
      // there--re-paint. This is needed when another window was topped
      // over part of STOCLIEN and the user then topped STOCLIEN using
      // a mouse click on the visible part of STOCLIEN. In any case let
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
        lpmis->itemWidth = m_wWidth;
        lResult = TRUE;
      }

    case WM_SIZE:
      // Handle a resize of this window.
      m_wWidth = LOWORD(lParam);
      m_wHeight = HIWORD(lParam);
      // Inform CGuiPaper of the change.
      m_pGuiPaper->Resize(m_wWidth, m_wHeight);
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
      m_pGuiPaper->InkStart(LOWORD(lParam), HIWORD(lParam));
      break;

    case WM_MOUSEMOVE:
      // Draw inking sequence data.
      m_pGuiPaper->InkDraw(LOWORD(lParam), HIWORD(lParam));
      break;

    case WM_LBUTTONUP:
      // Stop an ink drawing sequence.
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
  wcf.hCursor       = LoadCursor(                  // Load app cursor.
                        hInstance,
                        TEXT("AppCursor"));
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
  int iRun = FALSE;

  // If we were compiled for UNICODE and the platform seems OK with this
  // then proceed.  Else we error and exit the app.
  if (UnicodeOk())
  {
    // Call to initialize the COM Library.  Use the SUCCEEDED macro
    // to detect success.  If fail then exit app with error message.
    // Tell COM that this client process and all subordinate threads
    // will live in an apartment threaded world.
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
        // friend, STOSERVE.
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
