/*+==========================================================================
  File:      LICCLIEN.H

  Summary:   Include file for the LICCLIEN code sample application.
             In addition to class definitions, this LICCLIEN.H file
             contains definitions of the application's menu, string,
             and other resource IDs.

             Based largely on the DLLCLIEN.EXE source code, this include
             file has resource IDs for the set of new menus for exercising
             the several COM components manipulated in this COM Client.
             Of special interest are the new menus for exercising the
             licensed COM components housed in the partner LICSERVE server.

             For a comprehensive tutorial code tour of LICCLIEN's
             contents and offerings see the tutorial LICCLIEN.HTM file.
             For more specific technical details on the internal workings
             see the comments dispersed throughout the LICCLIEN source code.

  Classes:   CMainWindow

  Functions: WinMain

  Origin:    10-5-95: atrent - Editor-inheritance from the DLLCLIEN source.

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

#if !defined(LICCLIEN_H)
#define LICCLIEN_H

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

  // A method for getting an interface on a COM object.
  BOOL GetInterface(IUnknown* pObj, REFIID riid, PPVOID ppv);

  TCHAR m_szFileName[MAX_PATH];
  CMsgBox*  m_pMsgBox;
  CMsgLog*  m_pMsgLog;
  BSTR      m_bstrLicKey;

  // Some member variables to store pointers to Car-like COM Objects.
  // We save pointers to each COM objects controlling IUnknown.
  IUnknown* m_pCar;
  IUnknown* m_pUtilityCar;
  IUnknown* m_pLicCruiseCar;
  IUnknown* m_pUtilityCruiseCar;

  // Some cached pointers to the the Car Sample utility objects.
  ISample*  m_pLicCarSample;
  ISample*  m_pDllCarSample;

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
#define MAIN_WINDOW_TITLE_STR       "LICCLIEN: Tutorial Code Sample"
#define MAIN_WINDOW_CLASS_NAME_STR  "LICCLIENWindow"
#define MAIN_WINDOW_CLASS_MENU_STR  "LICCLIENMenu"

// File Name String Macros.
#define LICSERVE_TUTFILE_STR        "licserve.htm"
#define DLLSERVE_TUTFILE_STR        "dllserve.htm"

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

// LicCruiseCar Menu Command Identifiers.
#define IDM_CCAR_CREATE             1300
#define IDM_CCAR_RELEASE            1301
#define IDM_CCAR_SHIFT              1302
#define IDM_CCAR_CLUTCH             1303
#define IDM_CCAR_SPEED              1304
#define IDM_CCAR_STEER              1305
#define IDM_CCAR_ENGAGE             1306
#define IDM_CCAR_ADJUST             1307

// UtilityCruiseCar Menu Command Identifiers.
#define IDM_UCRU_GETLICKEY          1400
#define IDM_UCRU_CLEARLICKEY        1401
#define IDM_UCRU_CREATE             1402
#define IDM_UCRU_RELEASE            1403
#define IDM_UCRU_SHIFT              1404
#define IDM_UCRU_CLUTCH             1405
#define IDM_UCRU_SPEED              1406
#define IDM_UCRU_STEER              1407
#define IDM_UCRU_ENGAGE             1408
#define IDM_UCRU_ADJUST             1409
#define IDM_UCRU_OFFROAD            1410
#define IDM_UCRU_WINCH              1411

// Log Menu Command Identifiers.
#define IDM_LOG_LOGCLEAR            1890
#define IDM_LOG_LICSERVER           1891
#define IDM_LOG_DLLSERVER           1892
#define IDM_LOG_LOGGING             1893
#define IDM_LOG_COPYCLIP            1894

// Help Menu Command Identifiers.
#define IDM_HELP_CONTENTS           1900
#define IDM_HELP_TUTORIAL           1901
#define IDM_HELP_TUTLICSERVER       1902
#define IDM_HELP_TUTDLLSERVER       1903
#define IDM_HELP_READSOURCE         1904
#define IDM_HELP_ABOUT              1905
#define IDM_HELP_ABOUTLICSERVER     1906
#define IDM_HELP_ABOUTDLLSERVER     1907

// Error-related String Identifiers.
#define IDS_COMINITFAILED           2000
#define IDS_APPINITFAILED           2001
#define IDS_OUTOFMEMORY             2002
#define IDS_NOUNICODE               2003
#define IDS_NODLLSERVER             2004
#define IDS_NOLICSERVER             2005
#define IDS_NOLICENSE               2006
#define IDS_NORUNLICENSE            2007

#define IDS_ASSERT_FAIL             2200

// Notice-related String Identifiers.
#define IDS_NOTIMPLEMENTED          2301

// Log Message String Identifiers.
#define IDS_START_MESSAGE_LOG       2400

#endif
