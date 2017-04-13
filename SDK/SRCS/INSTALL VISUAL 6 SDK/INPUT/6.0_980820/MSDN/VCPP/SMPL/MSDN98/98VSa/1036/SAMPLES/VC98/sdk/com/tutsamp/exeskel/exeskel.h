/*+==========================================================================
  File:      EXESKEL.H

  Summary:   Include file for the EXESKEL skeleton code sample application.
             In addition to a main window class definition, this EXESKEL.H
             file contains definitions of the application's menu, string,
             and other resource IDs.

             For a comprehensive tutorial code tour of EXESKEL's
             contents and offerings see the tutorial EXESKEL.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the EXESKEL source code.

  Classes:   CMainWindow

  Functions: WinMain

  Origin:    7-27-95: atrent - Created based on DFVIEW by stevebl.

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

#if !defined(EXESKEL_H)
#define EXESKEL_H

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
#define MAIN_WINDOW_TITLE_STR       "EXESKEL: Tutorial Code Sample"
#define MAIN_WINDOW_CLASS_NAME_STR  "EXESKELWindow"
#define MAIN_WINDOW_CLASS_MENU_STR  "EXESKELMenu"

// OpenFile-related String Macros.
#define OFN_DEFAULTFILES_STR "All Files (*.*)\0*.*\0"
#define OFN_DEFAULTTITLE_STR "Open File"

// File Menu Command Identifiers.
#define IDM_FILE_EXIT               1000

// Help Menu Command Identifiers.
#define IDM_HELP_CONTENTS           1900
#define IDM_HELP_TUTORIAL           1901
#define IDM_HELP_READSOURCE         1902
#define IDM_HELP_ABOUT              1903

// Error-related String Identifiers.
#define IDS_COMINITFAILED           2000
#define IDS_APPINITFAILED           2001
#define IDS_OUTOFMEMORY             2002
#define IDS_UNICODEFAIL             2003

#define IDS_ASSERT_FAIL             2200

// Notice-related String Identifiers.
#define IDS_NOTIMPLEMENTED          2301

#endif
