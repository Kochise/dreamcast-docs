/*+==========================================================================
  File:      APTSERVE.H

  Summary:   Include file for the APTSERVE code sample application.
             In addition to class definitions, this APTSERVE.H file
             contains definitions of the application's menu, string,
             and other resource IDs.

             For a comprehensive tutorial code tour of APTSERVE's
             contents and offerings see the tutoorial APTSERVE.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the APTSERVE source code.

  Classes:   CMainWindow

  Functions: WinMain

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

#if !defined(APTSERVE_H)
#define APTSERVE_H

#ifdef __cplusplus

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

  // Methods for registering and unregistering this server.
  BOOL RegisterServer(void);
  BOOL UnregisterServer(void);

  // For message box dialogs.
  CMsgBox*  m_pMsgBox;
  CSendLog* m_pMsgLog;

protected:
  LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
  LRESULT DoMenu(WPARAM wParam, LPARAM lParam);
};

#endif // __cplusplus

// Window Class String Macros.
#define MAIN_WINDOW_TITLE_STR       "APTSERVE: Tutorial Code Sample"
#define MAIN_WINDOW_CLASS_NAME_STR  "APTSERVEWindow"
#define MAIN_WINDOW_CLASS_MENU_STR  "APTSERVEMenu"
#define CLIENT_WINDOW_TITLE         "APTCLIEN: Tutorial Code Sample"

// File Menu Command Identifiers.
#define IDM_FILE_EXIT               1000

// Log Menu Command Identifiers.
#define IDM_LOG_LOGCLEAR            1890
#define IDM_LOG_COPYCLIP            1891

// Help Menu Command Identifiers.
#define IDM_HELP_ABOUT              1905

// Error-related String Identifiers.
#define IDS_COMINITFAILED           2000
#define IDS_APPINITFAILED           2001
#define IDS_OUTOFMEMORY             2002
#define IDS_NOHELPFILE              2003
#define IDS_NOUNICODE               2004
#define IDS_NOSERVER                2005

#define IDS_ASSERT_FAIL             2200

// Notice-related String Identifiers.
#define IDS_NOTIMPLEMENTED          2301

// Log Message String Identifiers.
#define IDS_LOGTO_CLIENT            2400
#define IDS_LOGTO_SERVER            2401

#endif  // APTSERVE_H
