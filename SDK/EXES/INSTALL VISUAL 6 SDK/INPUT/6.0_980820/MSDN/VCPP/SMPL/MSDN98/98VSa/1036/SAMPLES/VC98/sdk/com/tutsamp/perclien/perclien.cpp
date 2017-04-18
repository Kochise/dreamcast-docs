/*+==========================================================================
  File:      PERCLIEN.CPP

  Summary:   Main implementation for the PERCLIEN client application. This
             client loads and accesses the connectable COPageList COM
             object housed in a separate in-process COM Server (PERSERVE
             built in the sibling PERSERVE directory). The COPageList COM
             object is persistent and manages the page list data.

             Using the data in COPageList, PERCLIEN displays the page list
             and allows the user to create, open, and edit various page
             types kept in the list. The page editing is done in separate
             child windows. Each page type has data that is managed by
             appropriate COM servers. The PERTEXT server houses COTextPage
             COM objects. The PERDRAW server houses CODrawPage COM
             objects. The COPageList, COTextPage, and CODrawPage objects
             each use a different kind of COM object persistence.
             COPageList exposes IPersistStream for its persistence
             features. COTextPage exposes IPersistStreamInit. CODrawPage
             exposes IPersistStorage.

             All of the data content in the page list, text pages, and
             draw pages is stored in one compound file managed by this
             PERCLIEN client. Files of this type have the .PAG extension.

             To run PERCLIEN you must build the PERSERVE, PERTEXT, and
             PERDRAW samples first.

             For a comprehensive tutorial code tour of PERCLIEN's contents
             and offerings see the tutorial PERCLIEN.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the PERCLIEN source code.
             For more details on the PERSERVE.DLL that PERCLIEN works with
             see the PERSERVE.HTM file in the main tutorial directory.
             For more details on the PERTEXT.DLL that PERCLIEN works with
             see the PERTEXT.HTM file in the main tutorial directory.
             For more details on the PERDRAW.DLL that PERCLIEN works with
             see the PERDRAW.HTM file in the main tutorial directory.

  Classes:   CMainWindow.

  Functions: InitApplication, WinMain

  Origin:    5-24-96: atrent - Editor-inheritance from the STOCLIEN source.

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
  We include IPAGES.H and PAGEGUID.H for the common page-related Interface
    class, GUID, and CLSID specifications.
  We include RESDEF.H because it has the resource definitions specific
    to this application.
  We include PAGEFILE.H because it has the C++ class used for compound file
    storage of page list data.
  We include LISTWIN.H because CGuiList creates and uses a CListWin to
    encapsulate the standard listbox control window.
  We include GUILIST.H because it has the C++ class used for GUI display
    of the page list.
  We include PERCLIEN.H because it has the CMainWindow class definition.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <initguid.h>
#include <commdlg.h>
#include <apputil.h>
#include <ipages.h>
#include <pageguid.h>
#include "resdef.h"
#include "pagefile.h"
#include "listwin.h"
#include "guilist.h"
#include "perclien.h"


// Work storage for the user-entered page title.
TCHAR g_szPageTitle[PAGE_TITLE_SIZE] = TEXT(PAGE_UNTITLED_STR);


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

  m_pGuiList = NULL;
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

  // We delete the CGuiList object that was made in InitInstance.
  DELETE_POINTER(m_pGuiList);

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

  Modifies: m_szHelpFile

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

  // Create the CGuiList C++ object.
  m_pGuiList = new CGuiList;

  if (NULL != m_pGuiList)
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
             ::GetSystemMetrics(SM_CXSCREEN)*1/3,
             ::GetSystemMetrics(SM_CYSCREEN)*1/3,
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

        if (NULL != pszCmdLine)
        {
          // Convert from Ansi to Unicode.
          AnsiToUc(pszCmdLine, wszUc, MAX_PATH);
          // Init the new GuiList.
          bOk = m_pGuiList->Init(m_hInst, m_hWnd, wszUc);
        }
        else
          bOk = m_pGuiList->Init(m_hInst, m_hWnd, NULL);
      }
#else
      // Init the new GuiList.
      bOk = m_pGuiList->Init(m_hInst, m_hWnd, pszCmdLine);
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

        // Try to open the page list compound file and populate the
        // main page list. Open either the default PERCLIEN.PAG
        // or the one specified on the invocation command line.
        // Load will create/load the default PERCLIEN.PAG if no specified
        // .PAG file is found.
        hr = m_pGuiList->Load();
        if (SUCCEEDED(hr))
        {
          // If the COPageList COM object was created and reconstituted
          // by loading the .PAG file then show its Page List.
          hr = m_pGuiList->Show(0);
        }
        bOk = SUCCEEDED(hr);
        if (!bOk)
          HrMsgId(m_hInst, m_hWnd, IDS_NOSERVER, hr);
      }
    }
  }

  if (!bOk)
  {
    DELETE_POINTER(m_pGuiList);
  }

  return (bOk);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::DoCommand

  Summary:  Dispatch and handle the main menu commands.

  Args:     WPARAM wParam,
              First message parameter.
            LPARAM lParam)
              Second message parameter.

  Modifies: m_ofnFile, ...

  Returns:  LRESULT
              Standard Windows WindowProc return value.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CMainWindow::DoCommand(
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
    case IDM_FILE_NEW:
      // Create an empty compound file; ask CGuiList to save itself to it.
      m_pGuiList->New();
      break;
    case IDM_FILE_OPEN:
      // Open existing compound file; ask CGuiList to load itself from it.
      m_pGuiList->Open();
      break;
    case IDM_FILE_SAVE:
      // Ask all pages to save to current compound file.
      m_pGuiList->Save();
      break;
    case IDM_FILE_SAVEAS:
      // Create new compound file and ask all pages to save to it.
      m_pGuiList->SaveAs();
      break;
    case IDM_FILE_EXIT:
      // The user commands us to exit this application so we tell the
      // Main window to close itself.
      ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
      break;

    //----------------------------------------------------------------------
    // Handle Page Menu Commands.
    //----------------------------------------------------------------------
    case IDM_PAGE_OPEN:
      // Open the selected page in the list.
      m_pGuiList->PageOpen();
      break;
    case IDM_PAGE_TITLE:
      // Edit a new title for the selected page in the list.
      m_pGuiList->PageTitle();
      break;
    case IDM_PAGE_NEWTEXT:
      // Create new Text page.
      m_pGuiList->PageAdd(PAGETYPE_TEXT);
      break;
    case IDM_PAGE_NEWDRAW:
      // Create new Drawing page.
      m_pGuiList->PageAdd(PAGETYPE_DRAWING);
      break;
    case IDM_PAGE_DELETE:
      // Delete the selected page in the list.
      m_pGuiList->PageDelete();
      break;

    //----------------------------------------------------------------------
    // Handle Help Menu Commands.
    //----------------------------------------------------------------------
    case IDM_HELP_CONTENTS:
      // We have some stubbed support here for bringing up the main online
      // Help for this application. Assumed to be in an .HTM file located
      // next to the .EXE file of the current executable.
      ReadHelp(m_hWnd, m_szHelpFile);
      break;
    case IDM_HELP_TUTORIAL:
      // Call the APPUTIL utility function, ReadTutorial, to Browse the HTML
      // tutorial narrative file associated with this tutorial code sample.
      ReadTutorial(m_hInst, m_hWnd, TEXT(HTML_FILE_EXT));
      break;
    case IDM_HELP_PERSERVE:
      // Call the APPUTIL utility function, ReadTutorial, to Browse the HTML
      // tutorial narrative file associated with the PERSERVE COM server.
      ReadTutorial(m_hInst, m_hWnd, TEXT(SERVER_PERSERVE_STR));
      break;
    case IDM_HELP_PERTEXT:
      // Call the APPUTIL utility function, ReadTutorial, to Browse the HTML
      // tutorial narrative file associated with the PERTEXT COM server.
      ReadTutorial(m_hInst, m_hWnd, TEXT(SERVER_PERTEXT_STR));
      break;
    case IDM_HELP_PERDRAW:
      // Call the APPUTIL utility function, ReadTutorial, to Browse the HTML
      // tutorial narrative file associated with the PERDRAW COM server.
      ReadTutorial(m_hInst, m_hWnd, TEXT(SERVER_PERDRAW_STR));
      break;
    case IDM_HELP_READSOURCE:
      // Call the APPUTIL utility function ReadSource to allow the
      // user to open and read any of the source files of PERCLIEN.
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

    //----------------------------------------------------------------------
    // Handle ListWin Commands (ie, from the child list box control).
    //----------------------------------------------------------------------
    case IDC_LISTWIN:
      switch (HIWORD(wParam))
      {
        case LBN_DBLCLK:
          // User Double Clicked. Open the selected page in the list.
          m_pGuiList->PageOpen();
          break;
        case LBN_SELCHANGE:
          // User changed the page selection.
          break;
        default:
          break;
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
  Method:   CDlgPageProps::DialogProc

  Summary:  Dialog proc for the Page Properties dialog box. This
            DialogProc method definition overrides the same-named pure
            virtual function in abstract base class CVirDialog thus giving
            unique message dispatching behavior to this derivation of
            CVirDialog. The remaining behavior of CDlgPageProps is
            inherited from CVirDialog and is common to all CVirDialogs.

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
BOOL CDlgPageProps::DialogProc(
       HWND hWndDlg,
       UINT uMsg,
       WPARAM wParam,
       LPARAM lParam)
{
  BOOL bResult = TRUE;
  HWND hCtrl = GetDlgItem(hWndDlg, IDC_EDIT_PGTITLE);

  switch (uMsg)
  {
    case WM_INITDIALOG:
      SetDlgItemText(hWndDlg, IDC_EDIT_PGTITLE, g_szPageTitle);
      SetFocus(hCtrl);
      bResult = FALSE;
      break;

    case WM_COMMAND:
      {
        WORD wCmd = LOWORD(wParam);

        if (wCmd == IDOK)
        {
          // Obtain the machine name from the edit control and store
          // it where other functions can get it.
          GetDlgItemText(
            hWndDlg,
            IDC_EDIT_PGTITLE,
            g_szPageTitle,
            PAGE_TITLE_SIZE);
          ::EndDialog(hWndDlg, TRUE);
        }
        else if (wCmd == IDCANCEL)
          ::EndDialog(hWndDlg, FALSE);
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
              First message parameter.
            LPARAM lParam)
              Second message parameter.

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

    case WM_SIZE:
      // Handle a resize of this window.
      m_wWidth = LOWORD(lParam);
      m_wHeight = HIWORD(lParam);
      // Inform CGuiList and CListWin of the change.
      m_pGuiList->Resize(m_wWidth, m_wHeight);
      break;

    case WM_COMMAND:
      // Dispatch and handle any Menu command messages received.
      lResult = DoCommand(wParam, lParam);
      break;

    case WM_USER_PAGECHANGED:
      // An open page was edit/changed.
      m_pGuiList->PageChanged(lParam);
      break;

    case WM_USER_PAGECLOSED:
      // A separate page edit window was closed.
      m_pGuiList->PageClosed(lParam);
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
      // If there is data that has not been saved then ask user
      // if it should be saved. If user cancels then cancel the exit.
      if (IDCANCEL == m_pGuiList->AskSave())
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
  wcf.style         = CS_HREDRAW | CS_VREDRAW;          // Class style(s).
  wcf.lpszClassName = TEXT(MAIN_WINDOW_CLASS_NAME_STR); // Class name.
  wcf.lpszMenuName  = TEXT(MAIN_WINDOW_CLASS_MENU_STR); // Menu name.
  // Register the window class and return FALSE if unsuccesful.
  bOk = RegisterClassEx(&wcf);

  if (bOk)
  {
    // Assign the appropriate values for the text page window class.
    wcf.lpszClassName = TEXT(TEXT_WINDOW_CLASS_NAME_STR); // Class name.
    wcf.lpszMenuName  = TEXT(TEXT_WINDOW_CLASS_MENU_STR); // Menu name.
    // Register the window class and return FALSE if unsuccesful.
    bOk = RegisterClassEx(&wcf);
  }

  if (bOk)
  {
    // Assign the appropriate values for the drawing page window class.
    wcf.hCursor       = LoadCursor(                  // Load pen cursor.
                          hInstance,
                          TEXT("PenCursor"));
    wcf.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH); // Backgnd color.
    wcf.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Class style(s).
    wcf.lpszClassName = TEXT(DRAW_WINDOW_CLASS_NAME_STR);   // Class name.
    wcf.lpszMenuName  = TEXT(DRAW_WINDOW_CLASS_MENU_STR);   // Menu name.
    // Register the window class and return FALSE if unsuccesful.
    bOk = RegisterClassEx(&wcf);
  }

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
          // This includes creating the main window.  Note: if
          // InitInstance fails then it would have already deleted
          // pWin so we wouldn't need to delete it here.
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
        // friend, PERSERVE.
        CoFreeUnusedLibraries();

        // We'll pass to Windows the reason why we exited the message loop.
        iRun = msg.wParam;
      }
      else
      {
        // We failed to Initialize the application. Put up error message
        // box saying that application couldn't be initialized.  Parent
        // window is desktop (ie, NULL).
        ErrorBox(hInstance, NULL, IDS_APPINITFAILED);
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
      // is desktop (ie, NULL).
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
