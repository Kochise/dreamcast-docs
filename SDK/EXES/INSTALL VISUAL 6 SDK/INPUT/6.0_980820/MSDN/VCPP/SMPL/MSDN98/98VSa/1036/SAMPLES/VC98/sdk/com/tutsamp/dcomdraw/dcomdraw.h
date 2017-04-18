/*+==========================================================================
  File:      DCOMDRAW.H

  Summary:   Include file for the DCOMDRAW code sample application. In
             addition to class definitions, this DCOMDRAW.H file contains
             definitions of the application's menu, string, and other
             resource IDs.

             For a comprehensive tutorial code tour of DCOMDRAW's contents
             and offerings see the tutorial DCOMDRAW.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the DCOMDRAW source code.

  Classes:   CMainWindow.

  Functions: WinMain.

  Origin:    8-23-97: atrent - Editor-inheritance from CONCLIEN source.

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

#if !defined(DCOMDRAW_H)
#define DCOMDRAW_H

#ifdef __cplusplus

extern COSERVERINFO g_ServerInfo;

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
    BOOL InitInstance(HINSTANCE hInst, LPSTR pszCmdLine, int nCmdShow);

    TCHAR m_szFileName[MAX_PATH];
    CMsgBox*   m_pMsgBox;
    CGuiPaper* m_pGuiPaper;

  protected:
    LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

  private:
    LRESULT DoMenu(WPARAM wParam, LPARAM lParam);

    LONG m_lWidth;
    LONG m_lHeight;
    TCHAR m_szFileTitle[MAX_PATH];
    TCHAR m_szHelpFile[MAX_PATH];
    TEXTMETRIC m_tm;
    OPENFILENAME m_ofnFile;
};


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CDlgLoadRemote

  Summary:  Class to encapsulate the Load Remote Dialog.

  Methods:  DialogProc
              Dialog procedure
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CDlgLoadRemote: public CVirDialog
{
public:
  BOOL DialogProc(
         HWND hWndDlg,
         UINT uMsg,
         WPARAM wParam,
         LPARAM lParam);
};

#endif // __cplusplus

// Window Class String Macros.
#define MAIN_APP_NAME_STR           "DCOMDRAW: "
#define MAIN_WINDOW_TITLE_STR       "DCOMDRAW: Shared Drawing"
#define MAIN_WINDOW_MASTER_STR      "DCOMDRAW: Shared Drawing [***TALK***]"
#define MAIN_WINDOW_SLAVE_STR       "DCOMDRAW: Shared Drawing [LISTEN]"
#define MAIN_WINDOW_CLASS_NAME_STR  "DCOMDRAWWindow"
#define MAIN_WINDOW_CLASS_MENU_STR  "DCOMDRAWMenu"

// File Name String Macros.
#define SERVER_TUTFILE_STR          "dcdserve.htm"
#define MARSHAL_TUTFILE_STR         "dcdmarsh.htm"

// OpenFile-related String Macros.
#define OFN_DEFAULTFILES_STR "All Files (*.*)\0*.*\0"
#define OFN_DEFAULTTITLE_STR "Open File"

// Error strings.
#define REMOTE_CREATE_ERR_STR       "Remote Object Creation"
#define LOCAL_CREATE_ERR_STR        "Local Object Creation"

// Some compile-time constants for ink thickness in pixels.
enum
{
  INK_THIN = 2,
  INK_MEDIUM = 10,
  INK_THICK = 20
};

// Bit constants for the pen cursor.
#define PENCUR_OFF    0
#define PENCUR_ON     1
#define PENCUR_THIN   2
#define PENCUR_MEDIUM 4
#define PENCUR_THICK  8


// File Menu Command Identifiers.
#define IDM_FILE_LOADREMOTE         1000
#define IDM_FILE_LOADLOCAL          1001
#define IDM_FILE_SAVE               1002
#define IDM_FILE_EXIT               1019

// Draw Menu Command Identifiers.
#define IDM_DRAW_MASTER             1100
#define IDM_DRAW_SLAVE              1101
#define IDM_DRAW_REDRAW             1102
#define IDM_DRAW_ERASE              1103

// PEN Menu Command Identifiers.
#define IDM_PEN_COLOR               1200
#define IDM_PEN_THIN                1201
#define IDM_PEN_MEDIUM              1202
#define IDM_PEN_THICK               1203

// Help Menu Command Identifiers.
#define IDM_HELP_CONTENTS           1900
#define IDM_HELP_TUTORIAL           1901
#define IDM_HELP_TUTSERVER          1902
#define IDM_HELP_TUTMARSH           1903
#define IDM_HELP_READSOURCE         1904
#define IDM_HELP_ABOUT              1905

// Error-related String Identifiers.
#define IDS_COMINITFAILED           2000
#define IDS_APPINITFAILED           2001
#define IDS_OUTOFMEMORY             2002
#define IDS_NOUNICODE               2003
#define IDS_NODCOM                  2004
#define IDS_NOSERVER                2005
#define IDS_NOTIMPLEMENTED          2006

#define IDS_ASSERT_FAIL             2200

// Notice-related String Identifiers.
#define IDS_DRAWING_CHANGED         2300
#define IDS_ASK_SAVE                2301

// Dialog IDs.
#define IDD_LOAD_REMOTE             2500
#define IDC_STATIC_MACHINE          2501
#define IDC_EDIT_MACHINE            2502

#endif
