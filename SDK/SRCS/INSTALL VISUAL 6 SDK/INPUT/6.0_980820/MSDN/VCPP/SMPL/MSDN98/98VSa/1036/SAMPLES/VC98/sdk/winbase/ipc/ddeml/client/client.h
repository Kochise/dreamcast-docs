
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

#include <windows.h>
#include <ddeml.h>
#include <tchar.h>

#define WINDOWMENU  3   /* position of window menu               */

/* resource ID's */
#define IDCLIENT  1
#define IDCONV    2
#define IDLIST    3


/* menu ID's */

#define IDM_EDITPASTE           2004

#define IDM_CONNECT             3000    // enabled always
#define IDM_RECONNECT           3001    // enabled if list selected
#define IDM_DISCONNECT          3002    // enabled if conversation selected
#define IDM_TRANSACT            3003    // enabled if conversation selected
#define IDM_ABANDON             3004    // enabled if transaction selected
#define IDM_ABANDONALL          3005    // enabled if conv. selected &&
                                        // and any transaction windows exist

#define IDM_BLOCKCURRENT        3010    // enabled if conv. sel.  chkd if conv. blocked
#define IDM_ENABLECURRENT       3011    // enabled if conv. sel.  chkd if not blocked
#define IDM_ENABLEONECURRENT    3012    // enabled if conv. sel.

#define IDM_BLOCKALLCBS         3013    // enabled if any convs.
#define IDM_ENABLEALLCBS        3014    // enabled if any convs.
#define IDM_ENABLEONECB         3015    // enabled if any convs.

#define IDM_BLOCKNEXTCB         3016    // enabled always, chkd if set.
#define IDM_TERMNEXTCB          3017    // enabled if any convs.  chked if set.

#define IDM_TIMEOUT             3021
#define IDM_DELAY               3022
#define IDM_CONTEXT             3023
#define IDM_AUTORECONNECT       3024

#define IDM_WINDOWTILE          4001
#define IDM_WINDOWCASCADE       4002
#define IDM_WINDOWCLOSEALL      4003
#define IDM_WINDOWICONS         4004

#define IDM_XACTTILE            4005
#define IDM_XACTCASCADE         4006
#define IDM_XACTCLOSEALL        4007

#define IDM_WINDOWCHILD         4100

#define IDM_HELP                5001
#define IDM_HELPABOUT           5002


#define DEFTIMEOUT              1000

#include "dialog.h"

// predefined format list item

typedef struct {
    DWORD fmt;
    PTSTR sz;
} FORMATINFO;
#define CFORMATS 3

// conversation (MDI child) window information
typedef struct {
    HWND hwndXaction;       // last xaction window with focus, 0 if none.
    BOOL fList;
    HCONV hConv;
    HSZ hszTopic;
    HSZ hszApp;
    INT x;          // next child coord.
    INT y;
    CONVINFO ci; // most recent status info.
} MYCONVINFO;       // parameters to AddConv() in reverse order.
#define CHILDCBWNDEXTRA     sizeof(HWND)
#define UM_GETNEXTCHILDX    (WM_USER + 200)
#define UM_GETNEXTCHILDY    (WM_USER + 201)
#define UM_DISCONNECTED     (WM_USER + 202)

// transaction processing structure - this structure is associated with
// infoctrl control windows.  A handle to this structure is placed into
// the first window word of the control.
typedef struct {    // used to passinfo to/from TransactionDlgProc and
    DWORD ret;      // TextEntryDlgProc.
    DWORD Result;
    DWORD ulTimeout;
    DWORD wType;
    HCONV hConv;
    HDDEDATA hDdeData;
    DWORD wFmt;
    HSZ hszItem;
    DWORD fsOptions;
} XACT;

typedef struct {
    HDDEDATA hData;
    HSZ hszItem;
    DWORD wFmt;
} OWNED;

// transaction option flags - for fsOptions field and DefOptions global.

#define XOPT_NODATA             0x0001
#define XOPT_ACKREQ             0x0002
#define XOPT_DISABLEFIRST       0x0004
#define XOPT_ABANDONAFTERSTART  0x0008
#define XOPT_BLOCKRESULT        0x0010
#define XOPT_ASYNC              0x0020
#define XOPT_COMPLETED          0x8000      // used internally only.

/* strings */
#define IDS_ILLFNM              1
#define IDS_ADDEXT              2
#define IDS_CLOSESAVE       3
#define IDS_HELPNOTAVAIL    4
#define IDS_CLIENTTITLE     5
#define IDS_APPNAME             6
#define IDS_DDEMLERR        7
#define IDS_BADLENGTH       8

/* attribute flags for DlgDirList */
#define ATTR_DIRS       0xC010          /* find drives and directories */
#define ATTR_FILES      0x0000          /* find ordinary files         */
#define PROP_FILENAME   szPropertyName  /* name of property for dialog */
#define MAX_OWNED   20

/*
 *  GLOBALS
 */
extern CONVCONTEXT CCFilter;
extern DWORD idInst;
extern HANDLE hInst;            /* application instance handle            */
extern HANDLE hAccel;           /* resource handle of accelerators        */
extern HWND hwndFrame;          /* main window handle                     */
extern HWND hwndMDIClient;      /* handle of MDI Client window            */
extern HWND hwndActive;         /* handle of current active MDI child     */
extern HWND hwndActiveEdit;     /* handle of edit control in active child */
extern LONG styleDefault;       /* default child creation state           */
extern DWORD SyncTimeout;
extern LONG DefTimeout;
extern DWORD wDelay;
extern BOOL fEnableCBs;
extern BOOL fEnableOneCB;
extern BOOL fBlockNextCB;
extern BOOL fTermNextCB;
extern BOOL fAutoReconnect;
extern HDDEDATA hDataOwned;
extern DWORD fmtLink;        // registered LINK clipboard fmt
extern DWORD DefOptions;
extern TCHAR szChild[];          /* class of child                         */
extern TCHAR szList[];           /* class of child                         */
extern TCHAR szSearch[];         /* search string                          */
extern TCHAR *szDriver;          /* name of printer driver                 */
extern TCHAR szPropertyName[];   /* filename property for dialog box       */
extern INT iPrinter;            /* level of printing capability           */
extern BOOL fCase;              /* searches case sensitive                */
extern DWORD cFonts;            /* number of fonts enumerated             */
extern FORMATINFO aFormats[];
extern OWNED aOwned[MAX_OWNED];
extern DWORD cOwned;
extern FARPROC lpMsgFilterProc;
extern HSZ hszHuge;
extern HHOOK ghhk;


// MACROS

#ifdef NODEBUG
#define MyAlloc(cb)     (PTSTR)LocalAlloc(LPTR, (cb))
#define MyFree(p)       (LocalUnlock((HANDLE)(p)), LocalFree((HANDLE)(p)))
#else   // DEBUG

#define MyAlloc(cb)     DbgAlloc((DWORD)cb)
#define MyFree(p)       DbgFree((PTSTR)p)
#endif //NODEBUG


/*  externally declared functions
 */

// client.c

BOOL  APIENTRY InitializeApplication(VOID);
BOOL  APIENTRY InitializeInstance(DWORD);
INT FAR cdecl MPError(DWORD,DWORD, ...);
LONG  APIENTRY FrameWndProc(HWND, UINT, WPARAM, LPARAM);
LONG  APIENTRY MDIChildWndProc(HWND, UINT, WPARAM, LPARAM);
HCONV CreateConv(HSZ hszApp, HSZ hszTopic, BOOL fList);
HWND  APIENTRY AddConv(HSZ hszApp, HSZ hszTopic, HCONV hConv, BOOL fList);
PTSTR GetConvListText(HCONVLIST hConvList);
PTSTR GetConvInfoText(HCONV hConv, CONVINFO *pci);
PTSTR GetConvTitleText(HCONV hConv, HSZ hszApp, HSZ hszTopic, BOOL fList);
PTSTR Status2String(DWORD status);
PTSTR State2String(DWORD state);
PTSTR Error2String(DWORD error);
PTSTR Type2String(DWORD wType, DWORD fsOptions);
PTSTR GetHSZName(HSZ hsz);
LRESULT CALLBACK MyMsgFilterProc(int nCode, WPARAM wParam, LPARAM lParam);

// dialog.c


INT FAR DoDialog(LPTSTR lpTemplateName, DLGPROC lpDlgProc, LONG param,
        BOOL fRememberFocus);
BOOL  APIENTRY AboutDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL  APIENTRY ConnectDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL  APIENTRY TransactDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL  APIENTRY AdvOptsDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL  APIENTRY TextEntryDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL  APIENTRY ViewHandleDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL  APIENTRY TimeoutDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL  APIENTRY DelayDlgProc(HWND, UINT, WPARAM, LPARAM);
BOOL  APIENTRY ContextDlgProc(HWND, UINT, WPARAM, LPARAM);
VOID Delay(DWORD delay);

// dde.c


BOOL ProcessTransaction(XACT *pxact);
VOID CompleteTransaction(HWND hwndInfoCtr, XACT *pxact);
HDDEDATA CALLBACK DdeCallback(UINT wType, UINT wFmt, HCONV hConv, HSZ hsz1,
        HSZ hsz2, HDDEDATA hData, DWORD lData1, DWORD lData2);
HWND MDIChildFromhConv(HCONV hConv);
HWND FindAdviseChild(HWND hwndMDI, HSZ hszItem, DWORD wFmt);
HWND FindListWindow(HCONVLIST hConvList);
PTSTR GetTextData(HDDEDATA hData);
PTSTR GetFormatData(HDDEDATA hData);
INT MyGetClipboardFormatName(DWORD fmt, LPTSTR lpstr, INT cbMax);
PTSTR GetFormatName(DWORD wFmt);
BOOL MyDisconnect(HCONV hConv);

// mem.c


PTSTR DbgAlloc(DWORD cb);
PTSTR DbgFree(PTSTR p);
