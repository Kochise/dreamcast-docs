/*+==========================================================================
  File:      DLLCLIEN.H

  Summary:   Include file for the DLLCLIEN code sample application.
             In addition to class definitions, this DLLCLIEN.H file
             contains definitions of the application's menu, string,
             and other resource IDs.

             Based largely on the DLLUSER.EXE source code, this include
             file adds resource IDs for a set of new menus for exercising
             the several COM Components manipulated in this code sample
             as a COM Client of those components housed the the DLLSERVE
             server.

             For a comprehensive tutorial code tour of DLLCLIEN's
             contents and offerings see the tutorial DLLCLIEN.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the DLLCLIEN source code.

  Classes:   CMainWindow

  Functions: WinMain

  Origin:    9-20-95: atrent - Editor-inheritance from the DLLUSER source.

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

#if !defined(DLLCLIEN_H)
#define DLLCLIEN_H

#ifdef __cplusplus

extern CMsgLog* g_pMsgLog;

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
  CMsgBox*  m_pMsgBox;
  CMsgLog*  m_pMsgLog;

  // A method for getting an interface on a COM object.
  BOOL GetInterface(IUnknown* pObj, REFIID riid, PPVOID ppv);
  // Some member variables to store pointers to Car-like COM Objects.
  // We save pointers to each COM objects controlling IUnknown.
  IUnknown* m_pCar;
  IUnknown* m_pUtilityCar;
  IUnknown* m_pCruiseCar;
  IUnknown* m_pUtilityCruiseCar;
  ISample*  m_pCarSample;

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
#define MAIN_WINDOW_TITLE_STR       "DLLCLIEN: Tutorial Code Sample"
#define MAIN_WINDOW_CLASS_NAME_STR  "DLLCLIENWindow"
#define MAIN_WINDOW_CLASS_MENU_STR  "DLLCLIENMenu"

// File Name String Macros.
#define SERVER_TUTFILE_STR          "dllserve.htm"
#define REGISTER_TUTFILE_STR        "register.htm"

// OpenFile-related String Macros.
#define OFN_DEFAULTFILES_STR "All Files (*.*)\0*.*\0"
#define OFN_DEFAULTTITLE_STR "Open File"

// File Menu Command Identifiers.
#define IDM_FILE_EXIT               1000

// Car Menu Command Identifiers.
#define IDM_CAR_CREATE              1100
#define IDM_CAR_RELEASE             1101
#define IDM_CAR_SHIFT               1102
#define IDM_CAR_CLUTCH              1103
#define IDM_CAR_SPEED               1104
#define IDM_CAR_STEER               1105

// UtilityCar Menu Command Identifiers.
#define IDM_UCAR_CREATE             1200
#define IDM_UCAR_RELEASE            1201
#define IDM_UCAR_SHIFT              1202
#define IDM_UCAR_CLUTCH             1203
#define IDM_UCAR_SPEED              1204
#define IDM_UCAR_STEER              1205
#define IDM_UCAR_OFFROAD            1206
#define IDM_UCAR_WINCH              1207

// CruiseCar Menu Command Identifiers.
#define IDM_CCAR_CREATE             1300
#define IDM_CCAR_RELEASE            1301
#define IDM_CCAR_SHIFT              1302
#define IDM_CCAR_CLUTCH             1303
#define IDM_CCAR_SPEED              1304
#define IDM_CCAR_STEER              1305
#define IDM_CCAR_ENGAGE             1306
#define IDM_CCAR_ADJUST             1307

// UtilityCruiseCar Menu Command Identifiers.
#define IDM_UCRU_CREATE             1400
#define IDM_UCRU_RELEASE            1401
#define IDM_UCRU_SHIFT              1402
#define IDM_UCRU_CLUTCH             1403
#define IDM_UCRU_SPEED              1404
#define IDM_UCRU_STEER              1405
#define IDM_UCRU_ENGAGE             1406
#define IDM_UCRU_ADJUST             1407
#define IDM_UCRU_OFFROAD            1408
#define IDM_UCRU_WINCH              1409

// Log Menu Command Identifiers.
#define IDM_LOG_LOGCLEAR            1890
#define IDM_LOG_LOGGING             1891
#define IDM_LOG_COPYCLIP            1892

// Help Menu Command Identifiers.
#define IDM_HELP_CONTENTS           1900
#define IDM_HELP_TUTORIAL           1901
#define IDM_HELP_TUTSERVER          1902
#define IDM_HELP_TUTREGISTER        1903
#define IDM_HELP_READSOURCE         1904
#define IDM_HELP_ABOUT              1905
#define IDM_HELP_ABOUTSERVER        1906

// Error-related String Identifiers.
#define IDS_COMINITFAILED           2000
#define IDS_APPINITFAILED           2001
#define IDS_OUTOFMEMORY             2002
#define IDS_NOUNICODE               2003
#define IDS_NOSERVER                2004

#define IDS_ASSERT_FAIL             2200

// Notice-related String Identifiers.
#define IDS_NOTIMPLEMENTED          2301

// Log Message String Identifiers.
#define IDS_START_MESSAGE_LOG       2400

#endif
