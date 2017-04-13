
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/* ttfonts.h - header file
*/

/* function prototypes, window procedures first. */
LRESULT CALLBACK MainWndProc    (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ToolBarWndProc (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK AllFontsWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK LogFontWndProc (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK FontDataWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK DisplayWndProc (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About (HWND, UINT, WPARAM, LPARAM);



/* the initialization routines for the different modules. */
int initDlg(HWND);
int initDisplay(HWND);
int initTB(HWND);
int initAllFont(HWND);

/* misc. routine to show data flow to the user. */
VOID flyWinWin(HWND, HWND, HWND, int);


HDC      GetPrinterDC (VOID);

/* the height of the toolbar in pels. */
#define TOOLBARHEIGHT 30

/* for the initial positioning of the three child windows. */
#define CHILDLEFT(x) (GetSystemMetrics (SM_CXFULLSCREEN) * x/3 + 5)
#define CHILDTOP     TOOLBARHEIGHT*6/5

/* the default size of some of the dialogs. */
#define DLGWIDTH   110
#define DLGHEIGHT  160



/* menu IDs */
#define  IDM_CASCADE        1001
#define  IDM_TILE           1002
#define  IDM_ARRANGE        1003
#define  IDM_HELP           2001
#define  IDM_ABOUT          2002

#define  IDM_FLYWINWIN      2000
#define  IDM_GRID           2001

#define  IDM_GETOBJECT               3000
#define  IDM_CHOOSEFONT              3001
#define  IDM_ANSI_FIXED_FONT         3002
#define  IDM_ANSI_VAR_FONT           3003
#define  IDM_DEVICE_DEFAULT_FONT     3004
#define  IDM_OEM_FIXED_FONT          3005
#define  IDM_SYSTEM_FIXED_FONT       3006
#define  IDM_SYSTEM_FONT             3007


/* dialog IDs from the LOGFONT dialog. */
#define  DID_X              101
#define  DIDHEIGHT          201
#define  DIDWIDTH           202
#define  DIDESCAPE          203
#define  DIDORIENT          204
#define  DIDWEIGHT          205
#define  DIDITALIC          206
#define  DIDUNDERL          207
#define  DIDSTRIKE          208
#define  DIDCHARSE          209
#define  DIDOUTPRE          210
#define  DIDCLIPPR          211
#define  DIDQUALIT          212
#define  DIDPITCHA          213
#define  DIDFACENA          214

/* dialog ID from the TEXTMETRIC dialog. */
#define DID_LISTBOX         500

/* dialog ID from the FontData dialog. */
#define DID_DWTABLE         200
#define DID_DWOFFSET        201
#define DID_CBDATA          203
#define DID_DOIT            300




/* button window IDs from toolbar. */
#define TBID_ENUM     57
#define TBID_CREATE   58
#define TBID_GETTM    59
#define TBID_PRINT    60
#define TBID_GETFONTDATA 61
#define IDM_PRINT     70




/* user defined wm_command to send to main window */
#define IDU_NOPRINTER 71


/* USER messages used between windows. */
#define  WMU_HFONTTODEMO      WM_USER+0x1000
#define  WMU_LFTODEMO         WM_USER+0x1001
#define  WMU_DEMOTOLF         WM_USER+0x1002
#define  WMU_DEMOTOTM         WM_USER+0x1003
#define  WMU_DEMOTOOLTM       WM_USER+0x1004
#define  WMU_DEMOGETDC        WM_USER+0x1005
#define  WMU_DEMORELEASEDC    WM_USER+0x1006
#define  WMU_GETFONTDATA      WM_USER+0x1007
#define  WMU_PREPAREALLGLYPHS WM_USER+0x1008


#define  WMU_NEWFONT          WM_USER+0x1100
#define  WMU_NEWMODEHELLO     WM_USER+0x1101
#define  WMU_NEWMODETMRANGE   WM_USER+0x1102
#define  WMU_NEWMODEALL       WM_USER+0x1103
#define  WMU_NEWMODE_NEWSEG   WM_USER+0x1104
#define  WMU_PRINT            WM_USER+0x1110

/* user defined create messsage, sent to window once CreateWindow() returns */
#define WMU_CREATE          WM_USER+0x1000




/* define strings and flags for use in warning message boxes */
#define MBERRORFLAGS     MB_OK | MB_ICONHAND


/* define string table IDs */
#define IDS_MBERROR       32
#define IDS_INITSTRING    33
#define IDS_ALLOCFAILED   34
#define IDS_RESETDISPLAY  35
#define IDS_NOCMAPTABLE   36
#define IDS_CBDATATOOBIG  37
#define IDS_NOTABLE       38
#define IDS_FORMATNOT4    39
#define IDS_FONTDATAERR   40
#define IDS_ENUMPRINTERR  41


extern TCHAR szMBERROR      [MAX_PATH];
extern TCHAR szInitString   [MAX_PATH];
extern TCHAR szAllocFailed  [MAX_PATH];
extern TCHAR szResetDisplay [MAX_PATH];
extern TCHAR szNoCMAPTable  [MAX_PATH];
extern TCHAR szCBDataTooBig [MAX_PATH];
extern TCHAR szNoTable      [MAX_PATH];
extern TCHAR szFormatNot4   [MAX_PATH];
extern TCHAR szFontDataErr  [MAX_PATH];
extern TCHAR szEnumPrinterR [MAX_PATH];




/* Global variables. */
HANDLE hInst;
HWND   hwndMain, hwndDisplay;
HWND   hwndTB, hwndDlgLF, hwndDlgTM, hwndDlgOLTM, hwndDlgFD;
HWND   hwndDisplayFonts, hwndPrinterFonts;
HWND   hwndClient;

/* the display window works in one of 3 modes
 *  this is shown to the user by a check mark in the 'Display' menu
 *  it is stored internally in the following variable
 *  (contains the checked menu ID)
 */
int gDisplaymode;
#define  IDM_MODEHELLO          101
#define  IDM_MODETMRANGE        102
#define  IDM_MODEALL            103
