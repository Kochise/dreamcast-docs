/*+==========================================================================
  File:      DLLUSER.H

  Summary:   Include file for the DLLUSER skeleton code sample application.
             In addition to class definitions, this DLLUSER.H file contains
             definitions of the application's menu, string, and other
             resource IDs.

             Based largely on the EXESKEL.EXE source code, this include
             file adds resource IDs for a new Test menu for exercising
             the exported function calls provided by DLLSKEL.DLL.

             For a comprehensive tutorial code tour of DLLUSER's
             contents and offerings see the tutorial DLLUSER.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the DLLUSER source code.

  Classes:   CMainWindow

  Functions: WinMain

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

#if !defined(DLLUSER_H)
#define DLLUSER_H

#if defined(__cplusplus)

/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CMainWindow

  Summary:  Class to encapsulate the application's main window, menu, and
            message dispatching behavior.

  Methods:  CMainWindow
              Constructor.
            InitInstance
              Creates a new instance of the main window.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CMainWindow: public CVirWindow
{
public:
  CMainWindow();
  ~CMainWindow();
  BOOL InitInstance(HINSTANCE, int);

  TCHAR m_szFileName[MAX_PATH];
  CMsgBox* m_pMsgBox;

protected:
  LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
  LRESULT DoMenu(WPARAM wParam, LPARAM lParam);

  WORD m_wWidth;
  WORD m_wHeight;
  TCHAR m_szHelpFile[MAX_PATH];
  TCHAR m_szFileTitle[MAX_PATH];
  TEXTMETRIC m_tm;
  OPENFILENAME m_ofnFile;
};

#endif // __cplusplus


// Window Class String Macros.
#define MAIN_WINDOW_TITLE_STR       "DLLUSER: Tutorial Code Sample"
#define MAIN_WINDOW_CLASS_NAME_STR  "DLLUSERWindow"
#define MAIN_WINDOW_CLASS_MENU_STR  "DLLUSERMenu"

// File Name String Macros.
#define DLL_TUTFILE_STR             "dllskel.htm"

// OpenFile-related String Macros.
#define OFN_DEFAULTFILES_STR "All Files (*.*)\0*.*\0"
#define OFN_DEFAULTTITLE_STR "Open File"

// File Menu Command Identifiers.
#define IDM_FILE_EXIT               1000

// Test Menu Command Identifiers.
#define IDM_TEST_DLLHELLO           1800
#define IDM_TEST_DLLABOUT           1801

// Help Menu Command Identifiers.
#define IDM_HELP_CONTENTS           1900
#define IDM_HELP_TUTORIAL           1901
#define IDM_HELP_TUTDLL             1902
#define IDM_HELP_READSOURCE         1903
#define IDM_HELP_ABOUT              1904

// Error-related String Identifiers.
#define IDS_COMINITFAILED           2000
#define IDS_APPINITFAILED           2001
#define IDS_OUTOFMEMORY             2002
#define IDS_UNICODEFAIL             2003

#define IDS_ASSERT_FAIL             2200

// Notice-related String Identifiers.
#define IDS_NOTIMPLEMENTED          2301

#endif
