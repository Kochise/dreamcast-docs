/*
 *  netwatch.h
 *  
 *  Purpose:
 *      main header file
 *  
 *  Owner:
 *      MikeSart
 */

// max size of strings in STRINGTABLE for LoadString
#define cchSzMax			64
#define cchTVSzMax			512
#define cchMsgMax			512
#define cchErrMax			1024

#define TIMERID				1

#define SCONST				static const

// Treeview types
#define TYPE_ERROR			((DWORD)-1)
#define TYPE_COMPUTER		0x0
#define TYPE_SHARE			0x1
#define TYPE_USER			0x2
#define TYPE_FILE			0x3
#define TYPE_MAX			0x4

// Bitmap Indexes
#define BMP_SHARE			0
#define BMP_COMPUTER		1
#define BMP_FILE			2
#define BMP_WRITE			3
#define BMP_READ			4
#define BMP_DENIED			5
#define BMP_BOB				6
#define BMP_USER			7
#define BMP_IPC				8
#define BMP_COMPUTERLIMITED	9

#define BMWIDTH				16
#define BMHEIGHT			16
#define RGBREPLACE			0x00FF0000 // solid blue

#define GlobalFreeNullPtr(_ptr) \
	if(_ptr) GlobalFreePtr(_ptr)

/*
 *  globules
 */
extern HINSTANCE	ghInst;
extern HMENU		ghMenu;
extern TCHAR		szAppName[];
extern DWORD		dwTimerInterval;
extern TCHAR		szNil[];
extern UINT			unMenuFlags[];

/*
 *  function prototypes
 */

// netwatch.c
LRESULT CALLBACK	NewTVProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK		SelectDlgProc(HWND, UINT, WPARAM, LPARAM);
VOID _cdecl			PropertyDlg(HWND hwnd, UINT rgIDSStart, DWORD dwrgBmp, ...);

// utils.c
HWND				InitNetWatchWnd(HWND hwnd);
VOID				DeInitNetWatchWnd(VOID);
VOID				BlitIcon(HDC hdc, LONG x, LONG y, int nBitmap);
HTREEITEM			hAddComputer(HWND hwnd, HWND hwndTV, LPTSTR szComputerName,
						HTREEITEM hItemLocation);
BOOL				FTreeView_GetString(HWND hwndTV, HTREEITEM hItem,
						TCHAR *szText, UINT cchTextMax);
VOID				ShowTitle(HWND hwnd, int nCmdShow);
VOID				PunchTimer(HWND hwndMain, BOOL fNewState);
VOID				RestoreWindowPosition(HWND hwnd, HWND hwndTV);
VOID				SaveWindowPosition(HWND hwnd, HWND hwndTV);
TCHAR				*szFromIDS1(UINT unID);
TCHAR				*GetSystemErrMessage(DWORD dwError);

// net.c
VOID				TreeView_FreeItemData(TV_ITEM *ptvItem);
UINT				RefreshDisplay(HWND hwnd, HWND hwndTV);
BOOL				HandleWM_VKEY(HWND hwnd, HWND hwndTV, WORD wAction);
VOID				AddErrorStringToTV(HWND hwndTV, HTREEITEM hParent, UINT ids,
						NET_API_STATUS nas);
VOID				HandleMenu(HWND hwnd, HWND hwndTV, HMENU hMenu);

/*
 *	DEBUG stuff
 */

#ifdef DEBUG

VOID _cdecl DbgPrint(LPCSTR lpFmt, ...);
UINT AssertSzFn(LPSTR szMsg, LPSTR szFile, INT nLine);
#define OutputDbgStr	DbgPrint
#define OutputDbgStrError(_szFunction, _sc) \
	if(_sc) \
		DbgPrint("%s returns sc=0x%08lx", _szFunction, _sc)
#define ASSERTDATA		static CHAR _szFile[] = __FILE__;
#define AssertSz(a,b)	((VOID)((a) || (AssertSzFn(b, _szFile, __LINE__))))
#define Assert(a)		((VOID)((a) || (AssertSzFn(NULL, _szFile, __LINE__))))
#define SideAssert(a)	((VOID)((a) || (AssertSzFn(NULL, _szFile, __LINE__))))

#else

VOID _cdecl IDbgPrint(LPCSTR lpFmt, ...);
#define OutputDbgStr		1 ? (VOID)0 : IDbgPrint
#define OutputDbgStrError	1 ? (VOID)0 : IDbgPrint
#define ASSERTDATA
#define AssertSz(a,b)
#define Assert(a)
#define SideAssert(a)		(a)

#endif
