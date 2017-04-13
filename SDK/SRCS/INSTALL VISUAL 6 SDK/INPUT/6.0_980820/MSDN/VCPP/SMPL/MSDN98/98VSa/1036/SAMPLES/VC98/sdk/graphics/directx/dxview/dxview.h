/****************************************************************************

    Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.

    DirectX Device Viewer - Common header file

****************************************************************************/

#include <windows.h>
#ifndef RC_INVOKED
#include <windowsx.h>
#include <mmsystem.h>
#include <commctrl.h>
#include <tchar.h>

#include <ddraw.h>
//#include <mmreg.h>
#include <dsound.h>
#include <dplay.h>
#include <dplobby.h>
#include <d3d.h>
#include <dinput.h>
#endif

//================================================================
// Defines
//================================================================

// Window Width and Height
#define DXView_WIDTH       700
#define DXView_HEIGHT      400

#define DEF_TAB_SIZE        3

// Child controls
#define IDC_LV          0x2000
#define IDC_TV          0x2003

// Imagelist first and last icons
#define IDI_FIRSTIMAGE  IDI_DIRECTX
#define IDI_LASTIMAGE   IDI_CAPSOPEN

#define IDC_SPLIT                       100

#define IDD_ABORTPRINTDLG               1001

#define IDM_EXIT                        40001
#define IDM_ABOUT                       40002
#define IDM_VIEWAVAIL                   40003
#define IDM_VIEWALL                     40004
#define IDM_PRINT                       40005
#define IDM_PRINTALL                    40006
#define IDM_PRINTTOFILE                 40007

#define IDI_DIRECTX                     100
#define IDI_CAPS                        101
#define IDI_CAPSOPEN                    102

#define IDS_PRINT_WARNING               1
#define IDS_PRINT_NEEDSELECT            2
#define IDS_PRINT_NOROOT                3

#define TIMER_PERIOD					500
//================================================================
// Typedefs
//================================================================

typedef struct 
{
    HDC         hdcPrint;       // In:      Printer DC
    HWND        hTreeWnd;       // In:      tree window
    HTREEITEM   hCurrTree;      // In:      current tree item handle
    DWORD       dwCharWidth;    // In:      average char width
    DWORD       dwLineHeight;   // In:      max line height
    DWORD       dwCurrLine;     // In/Out:  curr line position on page
    DWORD       dwCharsPerLine; // In:      maximum chars per line (based on avg. char width)
    DWORD       dwLinesPerPage; // In:      maximum lines per page
    DWORD       dwCurrIndent;   // In:      Current tab setting
    BOOL        fStartPage;     // In/Out:  need to a start new page ?!?
} PRINTCBINFO;

typedef void (*SELCALLBACK)(LPARAM lParam1, LPARAM lParam2);
typedef BOOL (*PRINTCALLBACK)(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo);

typedef struct
{
    SELCALLBACK     Callback;
    LPARAM          lParam1;
    LPARAM          lParam2;
    PRINTCALLBACK   printCallback;
} NODEINFO;

typedef struct
{
    char *  szName;         // name of cap
    DWORD   dwOffset;       // offset to cap
    DWORD   dwFlag;         // bit flag for cal
} CAPDEF;

typedef struct
{
    char *szName;         // name of cap
    SELCALLBACK     Callback;
    LPARAM          lParam2;
    PRINTCALLBACK   printCallback;
} CAPDEFS;

typedef struct
{
    D3DDEVICEDESC d3dDeviceDesc;
    GUID* device;       // DirectDraw device (can be NULL)
    GUID  driver;       // Direct3D driver
} CAP3DDEVICEDESC;

typedef struct
{
	GUID	guidInstance;
	DWORD	dwRefresh;
} LV_INSTANCEGUIDSTRUCT, * LPLV_INSTANCEGUIDSTRUCT;

typedef struct LOCALAPP
{
	struct LOCALAPP *	lpNext;
	GUID				guidApplication;
    char				szAppNameA[1];
} LOCALAPP, *LPLOCALAPP;

typedef struct
{
	HWND			hwndLV;
	LPLOCALAPP 	*	lp;
} ENUMLOCALAPPSTRUCT, *LPENUMLOCALAPPSTRUCT;


//================================================================
// Function prototypes
//================================================================

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

BOOL InitInstance(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow, int iWidth, int iHeight);

//================================================================
// DXView treeview/listview helper functions
//================================================================

BOOL DXView_OnCreate(HWND hwnd);
void DXView_OnCommand(HWND hwnd, WPARAM wParam);
void DXView_OnSize(HWND hwnd);
void DXView_OnTreeSelect(HWND hwndTV, NM_TREEVIEW *ptv);
void DXView_OnListViewDblClick(HWND hwndLV, NM_LISTVIEW *plv);
void DXView_Cleanup(void);
void DXView_FillTree(HWND hwndTV);
BOOL DXView_InitImageList(void);
BOOL DXView_OnPrint (HWND hWindow, HWND hTreeView, BOOL fPrintAll);
BOOL DXView_OnFile (HWND hWindow, HWND hTreeWnd,BOOL fPrintAll);
void LVAddColumn(HWND hwndLV, int i, char *name, int width);
int  LVAddText(HWND hwndLV, int col, const char *sz, ...);
void LVDeleteAllItems(HWND hwndLV);
HTREEITEM TVAddNode(HTREEITEM hParent, char *szText, 
                    BOOL fKids, int iImage, 
                    SELCALLBACK Callback, 
                    LPARAM lParam1, LPARAM lParam2,
                    PRINTCALLBACK printCallback);
void AddCapsToTV(HTREEITEM hParent, CAPDEFS *pcds, LPARAM lParam1);
void AddColsToLV(void);
void AddCapsToLV(CAPDEF *pcd, LPVOID pv);
void AddMoreCapsToLV(CAPDEF *pcd, LPVOID pv);
BOOL PrintCapsToDC(CAPDEF *pcd, LPVOID pv, PRINTCBINFO * lpInfo);

// Caps add to ListView callbacks
void DDAddCaps(LPARAM lParam1, LPARAM lParam2);
void DSAddCaps(LPARAM lParam1, LPARAM lParam2);
void DSCAddCaps(LPARAM lParam1, LPARAM lParam2);
void DPAddCaps(LPARAM lParam1, LPARAM lParam2);
void DPAddLocalApps(LPARAM lParam1, LPARAM lParam2);
void D3AddCaps(LPARAM lParam1, LPARAM lParam2);
void D3AddLineCaps(LPARAM lParam1, LPARAM lParam2);
void D3AddTexF(LPARAM lParam1, LPARAM lParam2);
void DDAddVideoModes(LPARAM lParam1, LPARAM lParam2);
void DPAddSessions(LPARAM lParam1, LPARAM lParam2);
void DDFourCCFormat(LPARAM lParam1, LPARAM lParam2);

// Caps Print Callbacks
BOOL DDPrintCaps (LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo);
BOOL DSPrintCaps(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo);
BOOL DSCPrintCaps(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo);
BOOL DPPrintCaps(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo);
BOOL DPPrintLocalApps(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo);
BOOL D3PrintCaps(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo);
BOOL DDPrintVideoModes(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo);
BOOL DPPrintSessions(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo);
BOOL DDPrintFourCCFormat(LPARAM lParam1, LPARAM lParam2, PRINTCBINFO * lpInfo);

// Printer Helper functions
BOOL PrintStartPage (PRINTCBINFO * pci);
BOOL PrintEndPage (PRINTCBINFO * pci);
BOOL PrintLine (int x, int y, LPCTSTR lpszBuff, DWORD cchBuff, PRINTCBINFO * pci);
BOOL PrintNextLine (PRINTCBINFO * pci);

//DirectPlay helper functions
HRESULT EnumSessions( LPDIRECTPLAY3A lpDP3A );
void RemoveStaleSessions();
void ResetListViewRefresh( HWND hwndLV );

// DirectInput helper functions
void DI_FillTree(void);

void FreeLocalAppList();
void GetAppName(LPSTR szNameBuffer, LPCGUID lpguidApplication, DWORD dwBufferSize);

#ifdef DX_3D
HRESULT CALLBACK D3EnumCallback(
            LPGUID pid,
            LPSTR lpDriverDesc,
            LPSTR lpDriverName, 
            LPD3DDEVICEDESC lpD3DDeviceDesc1, 
            LPD3DDEVICEDESC lpD3DDeviceDesc2, 
            LPVOID lpContext);
#endif

//================================================================
// DXView external variables
//================================================================

extern HINSTANCE    g_hInstance;
extern HWND         g_hwndLV;        // List view
extern HWND         g_hwndTV;        // Tree view
