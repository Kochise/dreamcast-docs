/*
 *	reitp.c
 *	
 *	Purpose:
 *		Test program for RichEdit.  Excercises main RichEdit
 *		functionality while providing a good replacement for notepad.
 *	
 *	Owner:
 *
 *  Copyright (c) 1997 Microsoft Coporation
 */

#include "preinc.h"

#include <windows.h>
#include <windowsx.h>

#include <commdlg.h>
#include <cderr.h>
#include <ctype.h>
#include <stdio.h>
#include <tchar.h>

// for the benefit of the outside world,
// richedit.h uses cpMax instead of cpMost
// I highly prefer cpMost
#ifdef cpMax
#error "cpMax hack won't work"
#endif	// cpMax
#define cpMax cpMost
#include <richedit.h>
#undef cpMax

#include "olestd.h"
#include "reguid.h"
#include "dbugit.h"
#include <richole.h>

#include "reitp.h"
#include "reitp.rh"
#include "frmtbar.h"
#include <oledlg.h>


ASSERTDATA


#define SUNKENRICHEDIT

// define to use LiFormatRange() directly instead of via blitting
//#define NOBLIT

// used to make life simpler while testing, should not normally be defined
//#define NO_SAVE_PROMPT


struct _itpcall;

typedef struct _pp
{
	BOOL fDone;
	HWND hwndDlg;
	REDOC *predoc;
	LONG cchText;
	LONG dxPage;
	LONG dyPage;
	RECT rc;
	FORMATRANGE fr;
#ifndef NOBLIT
	HBITMAP hbmp;
	HBITMAP hbmpOld;
	INT dxBmp;
	INT dyBmp;
#endif	// !NOBLIT
	INT ipage;
	INT cpage;
	INT cpageMost;
	LONG *rgcpPages;
} PRINTPREVIEW;

// number of pages to allocate at once in PRINTPREVIEW.rgcpPages
#define cpageChunk 4

#define szFmtPrintPreview TEXT("Print Preview - Page %d")

typedef struct _assensz
{
	WORD wNotification;
	LPCSTR szDescription;
} ASSENSZ;

// added to the client rect to get the RichEdit size
#ifdef SUNKENRICHEDIT
#define dxRESize -GetSystemMetrics(SM_CXBORDER)
#define dyRESize -GetSystemMetrics(SM_CYBORDER)
#else	// SUNKENRICHEDIT
#define dxRESize 0
#define dyRESize 0
#endif	// SUNKENRICHEDIT, else

// Control ID for the format bar
#define	FBR_FormatBar	217

#define HinstFromHwnd(_hwnd) ((HINSTANCE) GetWindowLong(_hwnd, GWL_HINSTANCE))

#define uiMFDisabled MF_DISABLED | MF_GRAYED
#define uiMFEnabled MF_ENABLED

// Maximum text to be corrected under PenWin
#define cchMaxCorrectText		4096

#define szClosedName szAppName

static TCHAR szAppName[] = TEXT("REITP");
static const TCHAR szClassRE[] = TEXT(RICHEDIT_CLASS);

static const TCHAR szFmtTitle[] = TEXT("REITP - %s");
static const TCHAR szUntitled[] = TEXT("[Untitled]");
static const TCHAR szRTFSig[] = TEXT("{\\rtf");
#define cchRTFSig 5
static TCHAR szRegKey[] = TEXT("software\\microsoft\\reitp");
static TCHAR szRegValue[] = TEXT("placement");
static const POINT ptMinTrackSize = {300, 90};
// Make sure that these strings match the order of SF_*
static TCHAR szFilterLoad[] = TEXT("Text and Rich Text\0*.TXT;*.RTF\0Text Files (*.TXT)\0*.TXT\0Rich Text Format (*.RTF)\0*.RTF\0All Files\0*.*\0\0");
static TCHAR szFilterSave[] = TEXT("Text Files (*.TXT)\0*.TXT\0Rich Text Format (*.RTF)\0*.RTF\0RTF w/o Objects (*.RTF)\0*.RTF\0Textized\0*.TXT\0\0");

static HMODULE hmod = 0;		// Flag for FreeLibrary()
HWND hwndMain = 0;
static HMENU hmenuLoaded = 0;
HMENU hmenuFull = 0;
static PRINTDLG pdDef = {0};
static BOOL fPrint = fFalse;
static BOOL fWysiwygDefault = fFalse;
static BOOL fWrapDefault = fTrue;
static UINT msgFindReplace = 0;
static HWND hwndFR = 0;					// find/replace dialog
HINSTANCE hinst = 0;

static LONG cchTextMost = 0;
static CLIPFORMAT cfTxtObj = 0;
static BOOL fErrSpace = fFalse;




static CHARFORMAT cfDefault =
{
	sizeof(CHARFORMAT),
	CFM_EFFECTS | CFM_PROTECTED | CFM_SIZE | CFM_OFFSET | CFM_COLOR | CFM_CHARSET | CFM_FACE,
	CFE_AUTOCOLOR,		// effects
	200,				// height, 200 twips == 10 points
	0,					// offset
	0,					// color (not used since CFE_AUTOCOLOR is specified)
	ANSI_CHARSET,
	FF_ROMAN,			// pitch and family
	"Arial"				// face name
};

static ASSENSZ rgassenszErrors[] =
{
	{EN_ERRSPACE, "Out of memory. Exit some other applications and try again."},
	{EN_MAXTEXT, "The maximum text length has been reached."},
	{0, NULL}
};

/*
 *	ITPOLEINPLACEFRAME
 *	
 *	Purpose:
 *		Frame window support for in place editing
 */
typedef struct _itpoleinplaceframe
{
	IOleInPlaceFrameVtbl * lpVtbl;		// Virtual table
	ULONG cRef;						// Reference count
	REDOC * predoc;					// Document
	LPOLEINPLACEACTIVEOBJECT pipaobj;		// Current active object
}
ITPOLEINPLACEFRAME;

#define PipframeFromPunk(_p) ((ITPOLEINPLACEFRAME *) (_p))

// Functions for ITP in place frame
ITPOLEINPLACEFRAME * ITPOLEINPLACEFRAME_New(REDOC * predoc);
STDMETHODIMP ITPOLEINPLACEFRAME_QueryInterface(LPUNKNOWN punk, REFIID riid,
											   LPUNKNOWN * ppvObj);
STDMETHODIMP_(ULONG) ITPOLEINPLACEFRAME_AddRef(LPUNKNOWN punk);
STDMETHODIMP_(ULONG) ITPOLEINPLACEFRAME_Release(LPUNKNOWN punk);
STDMETHODIMP ITPOLEINPLACEFRAME_GetWindow(ITPOLEINPLACEFRAME * pipframe,
										  HWND * phwnd);
STDMETHODIMP ITPOLEINPLACEFRAME_ContextSensitiveHelp(ITPOLEINPLACEFRAME *pipframe,
													 BOOL fEnterMode);
STDMETHODIMP ITPOLEINPLACEFRAME_GetBorder(ITPOLEINPLACEFRAME * pipframe,
										  LPRECT prcBorder);
STDMETHODIMP ITPOLEINPLACEFRAME_RequestBorderSpace(ITPOLEINPLACEFRAME * pipframe,
												   LPCBORDERWIDTHS pbw);
STDMETHODIMP ITPOLEINPLACEFRAME_SetBorderSpace(ITPOLEINPLACEFRAME * pipframe,
											   LPCBORDERWIDTHS pbw);
STDMETHODIMP ITPOLEINPLACEFRAME_SetActiveObject(ITPOLEINPLACEFRAME * pipframe,
											    LPOLEINPLACEACTIVEOBJECT pipaobj,
											    LPCSTR szObjName); 
STDMETHODIMP ITPOLEINPLACEFRAME_InsertMenus(ITPOLEINPLACEFRAME * pipframe,
										    HMENU hmenuShared, 
										    LPOLEMENUGROUPWIDTHS pmgw);
STDMETHODIMP ITPOLEINPLACEFRAME_SetMenu(ITPOLEINPLACEFRAME * pipframe, 
									    HMENU hmenuShared, HOLEMENU holemenu, 
									    HWND hwndActiveObject);
STDMETHODIMP ITPOLEINPLACEFRAME_RemoveMenus(ITPOLEINPLACEFRAME * pipframe, 
										    HMENU hmenuShared);
STDMETHODIMP ITPOLEINPLACEFRAME_SetStatusText(ITPOLEINPLACEFRAME * pipframe, 
											  LPCSTR szStatusText);    
STDMETHODIMP ITPOLEINPLACEFRAME_EnableModeless(ITPOLEINPLACEFRAME * pipframe, 
											   BOOL fEnable);
STDMETHODIMP ITPOLEINPLACEFRAME_TranslateAccelerator(ITPOLEINPLACEFRAME *pipframe,
													 LPMSG pmsg, WORD wID);

// Virtual table for ole in place frame interface
IOleInPlaceFrameVtbl ITPOLEINPLACEFRAME_Vtbl =
{
	(LPVOID) ITPOLEINPLACEFRAME_QueryInterface,
	(LPVOID) ITPOLEINPLACEFRAME_AddRef,
	(LPVOID) ITPOLEINPLACEFRAME_Release,
	(LPVOID) ITPOLEINPLACEFRAME_GetWindow,
	(LPVOID) ITPOLEINPLACEFRAME_ContextSensitiveHelp,
	(LPVOID) ITPOLEINPLACEFRAME_GetBorder,
	(LPVOID) ITPOLEINPLACEFRAME_RequestBorderSpace,
	(LPVOID) ITPOLEINPLACEFRAME_SetBorderSpace,
	(LPVOID) ITPOLEINPLACEFRAME_SetActiveObject,
	(LPVOID) ITPOLEINPLACEFRAME_InsertMenus,
	(LPVOID) ITPOLEINPLACEFRAME_SetMenu,
	(LPVOID) ITPOLEINPLACEFRAME_RemoveMenus,
	(LPVOID) ITPOLEINPLACEFRAME_SetStatusText,
	(LPVOID) ITPOLEINPLACEFRAME_EnableModeless,
	(LPVOID) ITPOLEINPLACEFRAME_TranslateAccelerator
};


/*
 *	ITPCALL
 *	
 *	Purpose:
 *		Callbacks from the Rich Edit OLE support
 */

typedef struct _itpcall
{
	IRichEditOleCallbackVtbl * lpVtbl;	// Virtual table
	ULONG cRef;						    // Reference count
	REDOC * predoc;						// Document
	ITPOLEINPLACEFRAME * pipframe;		// In place frame object
}
ITPCALL;


#define PitpcallFromPunk(_p) ((ITPCALL *) (_p))

// Functions for ITP callbacks
ITPCALL * ITPCALL_New(REDOC * predoc);
STDMETHODIMP ITPCALL_QueryInterface(LPUNKNOWN punk, REFIID riid,
								    LPUNKNOWN * ppvObj);
STDMETHODIMP_(ULONG) ITPCALL_AddRef(LPUNKNOWN punk);
STDMETHODIMP_(ULONG) ITPCALL_Release(LPUNKNOWN punk);
STDMETHODIMP ITPCALL_GetNewStorage(ITPCALL * pitpcall, LPSTORAGE FAR * ppstg);
STDMETHODIMP ITPCALL_GetInPlaceContext(ITPCALL * pitpcall, 
									   LPOLEINPLACEFRAME FAR * ppipframe,
									   LPOLEINPLACEUIWINDOW FAR* ppipuiDoc,
									   LPOLEINPLACEFRAMEINFO pipfinfo);
STDMETHODIMP ITPCALL_ShowContainerUI(ITPCALL * pitpcall, BOOL fShow);
STDMETHODIMP ITPCALL_QueryInsertObject(ITPCALL * pitpcall, LPCLSID pclsid,
				LPSTORAGE pstg, LONG cp);
STDMETHODIMP ITPCALL_DeleteObject(ITPCALL * pitpcall, LPOLEOBJECT poleobj);
STDMETHODIMP ITPCALL_QueryAcceptData(ITPCALL * pitpcall, LPDATAOBJECT pdataobj,
				CLIPFORMAT *pcfFormat, DWORD reco, BOOL fReally,
				HGLOBAL hMetaPict);
STDMETHODIMP ITPCALL_ContextSensitiveHelp(ITPCALL * pitpcall, BOOL fEnterMode);
STDMETHODIMP ITPCALL_GetClipboardData(ITPCALL *pitpcall, CHARRANGE *pchrg,
				DWORD reco, LPDATAOBJECT *ppdataobj);
STDMETHODIMP ITPCALL_GetDragDropEffect(ITPCALL *pitpcall, BOOL fDrag,
				DWORD grfKeyState, LPDWORD pdwEffect);
STDMETHODIMP ITPCALL_GetContextMenu(ITPCALL *pitpcall, WORD seltype,
				LPOLEOBJECT poleobj, CHARRANGE * pchrg, HMENU * phmenu);

// Virtual table for ITP callbacks
IRichEditOleCallbackVtbl ITPCALL_Vtbl =
{
	(LPVOID) ITPCALL_QueryInterface,
	(LPVOID) ITPCALL_AddRef,
	(LPVOID) ITPCALL_Release,
	(LPVOID) ITPCALL_GetNewStorage,
	(LPVOID) ITPCALL_GetInPlaceContext,
	(LPVOID) ITPCALL_ShowContainerUI,
	(LPVOID) ITPCALL_QueryInsertObject,
	(LPVOID) ITPCALL_DeleteObject,
	(LPVOID) ITPCALL_QueryAcceptData,
	(LPVOID) ITPCALL_ContextSensitiveHelp,
	(LPVOID) ITPCALL_GetClipboardData,
	(LPVOID) ITPCALL_GetDragDropEffect,
	(LPVOID) ITPCALL_GetContextMenu
};


LOCAL VOID ParseArguments(LPSTR *pszDoc, LPCSTR szCmdLine);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
LOCAL LRESULT HandleCreate(REDOC *predoc, LPCSTR szCmdLine);
LOCAL VOID ResizeRedoc(REDOC *predoc, RECT rc);
LOCAL VOID SetupMenu(REDOC *predoc, int iMenu, HMENU hmenu);
LOCAL LRESULT HandleCommand(REDOC *predoc, HWND hwnd, WPARAM wparam,
								LPARAM lparam);
LOCAL BOOL ToggleCheck(REDOC *predoc, UINT uiMenuid);
LOCAL BOOL QueryCheck(REDOC *predoc, UINT uiMenuid);
LOCAL LRESULT NewREDoc(REDOC *predoc, BOOL fPrompt, BOOL fUpdateUI);
LOCAL LONG CheckSave(REDOC *predoc);
LOCAL INT CheckRevert(REDOC *predoc);
LOCAL LRESULT CloseREDoc(REDOC *predoc, BOOL fPrompt, BOOL fUpdateUI);
DWORD CALLBACK MyRead(DWORD dwCookie, LPBYTE pbBuffer, LONG cb, LONG *pcb);
LOCAL LRESULT OpenREDoc(REDOC *predoc, BOOL fInsert);
LOCAL LRESULT RevertREDoc(REDOC *predoc);
LOCAL DWORD ReadREDoc(REDOC *predoc, LPCSTR szFile, LPCSTR szTitle,
						DWORD dwFormat, BOOL fInsert);
DWORD CALLBACK MyWrite(DWORD dwCookie, LPBYTE pbBuffer, LONG cb, LONG *pcb);
LOCAL LRESULT SaveREDoc(REDOC *predoc);
LOCAL LRESULT SaveREDocAs(REDOC *predoc, BOOL fSelect);
LOCAL LRESULT InsertObject(REDOC *predoc);
LOCAL VOID SelectCharFormat(REDOC *predoc);
LOCAL VOID SaveWindowPos(HWND hwnd);
LOCAL BOOL FRestoreWindowPos(WINDOWPLACEMENT *pwndpl);
LOCAL VOID SetAlignment(REDOC *predoc, WORD wAlignment);
LOCAL VOID IndentFirst(REDOC *predoc, BOOL fIndent);
LOCAL VOID ProtectSelection(REDOC *predoc);
LOCAL VOID SetWordWrap(REDOC *predoc, BOOL fWysiwyg, BOOL fWrap);
LOCAL VOID SetupWordWrapMenu(REDOC *predoc);
LOCAL VOID SetOffset(REDOC *predoc, BOOL fSuperscript);
LRESULT CALLBACK PPDlgProc(HWND hdlg, UINT msg, WPARAM wparam, LPARAM lparam);
LOCAL BOOL FPPInit(PRINTPREVIEW *ppp);
LOCAL VOID PPInitDialogSize(PRINTPREVIEW *ppp);
LOCAL VOID PPChangePage(PRINTPREVIEW *ppp, BOOL fPrev);
LOCAL VOID PPPaint(PRINTPREVIEW *ppp);
VOID DoVerb(REDOC * predoc, INT ioleverb);
LOCAL VOID FindReplace(REDOC *predoc, BOOL fReplace);
LOCAL VOID ProcessFindReplace(REDOC *predoc, FINDREPLACE *pfr);
LOCAL BOOL FEnablePaste(VOID);
LOCAL VOID UpdateFormatBar(REDOC *predoc);
LOCAL VOID ShowMargins(REDOC *predoc);


int PASCAL
WinMain(HINSTANCE hinstCurr, HINSTANCE hinstPrev, LPSTR szCmdLine, int nCmdShow)
{
	SCODE sc;
	MSG msg;
	WNDCLASS wndclass;
	WINDOWPLACEMENT wndpl;
	TCHAR *szDoc = NULL;
	REDOC *predoc = NULL;
	HACCEL hAccels;
#ifndef NO_OLE
	LPOLEINPLACEACTIVEOBJECT pipaobj;
#endif	// NO_OLE

    LoadLibrary("RichEd32.Dll"); // Load the RichEdit DLL to activate the
				 // RichEdit classes

    wndclass.style         = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc   = WndProc;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = sizeof(REDOC *);
    wndclass.hInstance     = hinstCurr;
    wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH) (COLOR_BACKGROUND + 1);
    wndclass.hIcon	       = LoadIcon(hinstCurr, TEXT("IconApp"));
    wndclass.lpszMenuName  = NULL;
    wndclass.lpszClassName = szAppName;

	RegisterClass(&wndclass);
	hinst = hinstCurr;

#ifdef TEST_OLE_INITIALIZE
	OleInitialize(NULL);
	OleUninitialize();
	OleInitialize(NULL);
	OleUninitialize();
#endif	// TEST_OLE_INITIALIZE

	OleInitialize(NULL);
	sc = OleInitialize(NULL);
	if (FAILED(sc))
	{
		TraceError("OleInitialize failed", sc);
		goto done;				// If OLE can't be initialized abort.
	}
	// OleStdInitialize();

	// Initialize the format bar class
	if(!FInitFormatBarClass(hinst))
	{						
		MessageBoxA(NULL, "Unable to register format bar", NULL,
					MB_ICONSTOP | MB_OK);
		goto done;
	}

	hmenuLoaded = LoadMenu(hinstCurr, TEXT("LoadedMenu"));
	hmenuFull = LoadMenu(hinstCurr, TEXT("FullMenu"));

	msgFindReplace = RegisterWindowMessage(TEXT("commdlg_FindReplace"));

	cfTxtObj = RegisterClipboardFormat(TEXT(CF_RETEXTOBJ));

	ParseArguments(&szDoc, szCmdLine);

	if(fPrint && !szDoc)
		goto done;

	hwndMain = CreateWindow(szAppName, szAppName,
            WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 
            0, 0, 750, 500, NULL, NULL, hinstCurr, szDoc);
	if(!hwndMain)
	{
		MessageBoxA(NULL, "Unable to create main window", NULL, MB_ICONSTOP | MB_OK);
		goto done;
	}
	SideAssert(predoc = (REDOC *) GetWindowLong(hwndMain, 0));

	if(!fPrint)
	{
		if(FRestoreWindowPos(&wndpl))
			SetWindowPlacement(hwndMain, &wndpl);
		ShowWindow(hwndMain, nCmdShow);
	}

	hAccels = LoadAccelerators(hinstCurr, "WARPKEYS");
	Assert(hAccels);
	while(GetMessage(&msg, NULL, 0, 0))
	{
# ifndef NO_OLE
		// Translate accelerators for possible in place objects
		if(predoc->pitpcall && (pipaobj = predoc->pitpcall->pipframe->pipaobj))
			pipaobj->lpVtbl->TranslateAccelerator(pipaobj, &msg);
# endif	// NO_OLE

		if(predoc->hwndRE && TranslateAccelerator(hwndMain, hAccels, &msg))
			continue;

		if(!hwndFR || !IsDialogMessage(hwndFR, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}



done:
	if(szDoc)
		GlobalFreePtr(szDoc);
	if(hwndMain)
		DestroyWindow(hwndMain);
	if(hmenuLoaded)
		DestroyMenu(hmenuLoaded);
	if(hmenuFull)
		DestroyMenu(hmenuFull);

	// OleStdUninitialize();

	return msg.wParam;
}


LOCAL VOID ParseArguments(LPSTR *pszDoc, LPCSTR szCmdLine)
{
	const TCHAR *pch;

	*pszDoc = NULL;
	pch = szCmdLine - 1;
	while(pch)
	{
		pch++;
		if(*pch == TEXT('/') || *pch == '-')
		{
			pch++;
			switch(*pch)
			{
			case TEXT('p'):
			case TEXT('P'):
				fPrint = fTrue;
				break;

			case TEXT('w'):
			case TEXT('W'):
				pch++;
				if(*pch == 'p' || *pch == 'P')
				{
					pch++;
					fWrapDefault = fTrue;
					fWysiwygDefault = fTrue;
				}
				else if(*pch == 'n' || *pch == 'N')
				{
					pch++;
					fWrapDefault = fFalse;
					fWysiwygDefault = fFalse;
				}
				else
				{
					fWrapDefault = fTrue;
					fWysiwygDefault = fFalse;
				}
				break;

			default:
				if(*pch >= TEXT('0') && *pch <= TEXT('9') && !cchTextMost)
				{
					while(*pch >= TEXT('0') && *pch <= TEXT('9'))
					{
						cchTextMost *= 10;
						cchTextMost += *pch++ - TEXT('0');
					}
				}
				break;
			}
		}
		else if(!*pszDoc)
		{
			while(*pch == TEXT(' '))
				pch++;
			if(*pch)
			{
				INT cch;
				const TCHAR *pchT;

				pchT = _tcschr(pch, TEXT(' '));
				if(pchT)
					cch = pchT - pch;
				else
					cch = lstrlen(pch);
				*pszDoc = GlobalAllocPtr(GHND, cch + 1);
				if(!*pszDoc)
					break;
				lstrcpyn(*pszDoc, (LPCSTR) pch, cch + 1);
				(*pszDoc)[cch] = '\0';
			}
		}
		pch = _tcschr(pch, TEXT(' '));
	}
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	REDOC *predoc = (REDOC *) GetWindowLong(hwnd, 0);
#ifndef NO_OLE
	LPOLEINPLACEACTIVEOBJECT pipaobj;
#endif	// !NO_OLE

    switch(msg)
    {
	case WM_NCCREATE:
		predoc = (REDOC *) GlobalAllocPtr(GHND, sizeof(REDOC));
		if(!predoc)
			return 0;
		SetWindowLong(hwnd, 0, (LONG) predoc);
		predoc->hwndParent = hwnd;
#ifndef MAC				
		predoc->pd.lStructSize = sizeof(PRINTDLG);
		predoc->pd.hwndOwner = hwnd;
		predoc->pd.Flags = PD_RETURNDEFAULT;

		if(!PrintDlg(&predoc->pd) && CommDlgExtendedError())
			memset(&predoc->pd, 0, sizeof(PRINTDLG));
#endif		
		break;

	case WM_NCDESTROY:
		if(predoc)
		{
			if(predoc->pfr)
				GlobalFreePtr(predoc->pfr);
			GlobalFreePtr(predoc);
			predoc = NULL;
			SetWindowLong(hwnd, 0, 0);
		}
		break;

	case WM_CREATE:
		hwndMain = hwnd;	// a bit of a cheat...

		return HandleCreate(predoc,
				(LPCSTR) ((CREATESTRUCT *) lparam)->lpCreateParams);
    case WM_DESTROY:
		PostQuitMessage(0);
        return 0l;

	case WM_ACTIVATEAPP:
#ifndef NO_OLE
		// Notify in place active object of frame activation
		if(predoc->pitpcall && (pipaobj = predoc->pitpcall->pipframe->pipaobj))
		{
			TraceTag(tagInPlace, "OnFrameWindowActivate(%d)", !!wparam);
			pipaobj->lpVtbl->OnFrameWindowActivate(pipaobj, !!wparam);
		}
#endif	// !NO_OLE
		break;

	case WM_INITMENU:
		if(predoc->hwndRE)
			predoc->fUpdateEditMenu = TRUE;
		break;

	case WM_INITMENUPOPUP:
		if(predoc->hwndRE)
			SetupMenu(predoc, (int) lparam, (HMENU) wparam);
		return 0;

	case WM_GETMINMAXINFO:
		((MINMAXINFO *) lparam)->ptMinTrackSize = ptMinTrackSize;
		return 0;

	case WM_COMMAND:
		return HandleCommand(predoc, hwnd, wparam, lparam);

	case WM_CLOSE:
		if(predoc && predoc->hwndRE && CloseREDoc(predoc, fTrue, fFalse) < 0)
			return 0;
		if(!fPrint)
			SaveWindowPos(hwnd);
		DestroyWindow(hwnd);
		return 0;

	case WM_ACTIVATE:
		if(predoc->hwndRE && LOWORD(wparam))
		{
			SetFocus(predoc->hwndRE);
			return 0;
		}
		break;

	case WM_SIZE:
		if(predoc->hwndFormatBar)
			SendMessage(predoc->hwndFormatBar, WM_SIZE, 0, 0);
		if(predoc->hwndRE)
		{
			RECT rc;

			GetClientRect(hwnd, &rc);
			ResizeRedoc(predoc, rc);
#ifdef DEBUG
			SendMessage(predoc->hwndRE, EM_REQUESTRESIZE, 0, 0);
#endif	// DEBUG
		}
		break;


	case WM_NOTIFY:
		switch(((NMHDR *) lparam)->code)
		{
		case EN_SELCHANGE:
			if(predoc->hwndFormatBar)
				UpdateFormatBar(predoc);
			return 0;

		case EN_PROTECTED:
		{
			ENPROTECTED *penprotected = (ENPROTECTED *) lparam;

			// allow change of protected attribute
			if(penprotected->msg == EM_SETCHARFORMAT &&
				((CHARFORMAT *) penprotected->lParam)->dwMask & CFM_PROTECTED)
			{
				return 0;
			}
		}
			MessageBeep(0);
			return 1;

		case EN_CORRECTTEXT:
		{
			ENCORRECTTEXT *pct = (ENCORRECTTEXT *) lparam;

			if(pct->chrg.cpMost - pct->chrg.cpMin > cchMaxCorrectText)
			{
				MessageBox(hwndMain,
							"You are trying to correct too much text. "
							"Decrease the size of your selection.",
							"REITP: Correct Text", MB_OK);
				return 0;
			}
		}
		return 1;

#ifndef NO_OLE
		case EN_DROPFILES:
# ifdef DEBUG
			if(!QueryCheck(predoc, IDM_IGNOREDROPS))
				return fFalse;
			TraceTag(tagGeneral, "Ignoring drop of %d file(s) at position %d",
				DragQueryFile(((ENDROPFILES *) lparam)->hDrop, (UINT) -1,
					NULL, 0),
				((ENDROPFILES *) lparam)->cp);
			// ignore file drops
			return fTrue;
# else	// DEBUG
			return ((ENDROPFILES *) lparam)->fProtected;
# endif	// DEBUG, else
#endif	// !NO_OLE


#ifdef DEBUG
		case EN_MSGFILTER:
		{
			MSGFILTER *	pmsgfilter = (MSGFILTER *) lparam;

			// eat left button downs and 'e's
			return (pmsgfilter->msg == WM_LBUTTONDOWN) ||
						((pmsgfilter->msg == WM_CHAR) &&
							(pmsgfilter->wParam == 'e'));
		}

		case EN_REQUESTRESIZE:
			ResizeRedoc(predoc, ((REQRESIZE *) lparam)->rc);
			return 0;
#endif	// DEBUG
		}
		break;

	default:
		if(msg != msgFindReplace)
			break;

		if(((FINDREPLACE *) lparam)->Flags & FR_DIALOGTERM)
		{
			hwndFR = 0;
			SendMessage(predoc->hwndRE, EM_HIDESELECTION, fTrue, fTrue);
			return 0;
		}
		ProcessFindReplace(predoc, (FINDREPLACE *) lparam);
		return 0;
    }

	return DefWindowProc(hwnd, msg, wparam, lparam);
}


LOCAL LRESULT HandleCreate(REDOC *predoc, LPCSTR szFile)
{
	DWORD dwError;

	if(!szFile || !*szFile)
		goto no_file;

	if((dwError = ReadREDoc(predoc, szFile, NULL, 0, FALSE)))
	{
		TCHAR szErr[300];

		wsprintf(szErr, TEXT("Error opening %s [%ld]"), szFile, dwError);
		MessageBoxA(hwndMain, szErr, NULL, MB_OK);
		goto no_file;
	}

	if(fPrint)
	{
		PrintREDoc(predoc);
		PostQuitMessage(0);
	}
	else
	{
		TCHAR szT[256];

		wsprintf(szT, szFmtTitle, predoc->szTitle);
		SetWindowText(predoc->hwndParent, szT);

		SetMenu(hwndMain, hmenuFull);
		SetupWordWrapMenu(predoc);
		DrawMenuBar(hwndMain);
	}

#ifdef TIME_OPEN
	PostMessage(hwndMain, WM_CLOSE, 0, 0);
#endif	// TIME_OPEN

	return 0;

no_file:
	if(NewREDoc(predoc, fFalse, fTrue) < 0)
	{
		SetMenu(hwndMain, hmenuLoaded);
	}
	else
	{
		SetMenu(hwndMain, hmenuFull);
		SetupWordWrapMenu(predoc);
	}
	DrawMenuBar(hwndMain);

	return 0;
}


LOCAL VOID ResizeRedoc(REDOC *predoc, RECT rc)
{
	RECT rcParent;
#ifndef NO_OLE
	LPOLEINPLACEACTIVEOBJECT pipaobj = NULL;
#endif	// NO_OLE

	GetClientRect(predoc->hwndParent, &rcParent);
	InflateRect(&rcParent, dxRESize, dyRESize);

	// If we have a format bar, take it into account
	if(predoc->hwndFormatBar)
	{
		RECT rcFmtBar;

		GetClientRect(predoc->hwndFormatBar, &rcFmtBar);
		rcParent.top += rcFmtBar.bottom;
	}
	rc.top = max(rcParent.top, rc.top);
	rc.left = max(rcParent.left, rc.left);
	rc.right = min(rcParent.right, rc.right);
	rc.bottom = max(rc.bottom, rc.top + ptMinTrackSize.y);
	rc.bottom = min(rcParent.bottom, rc.bottom);

	MoveWindow(predoc->hwndRE, rc.left, rc.top, rc.right - rc.left,
		rc.bottom - rc.top, fTrue);

	if(GetMenuState(hmenuFull, IDM_SHOWMARGINS, MF_BYCOMMAND) & MF_CHECKED)
	{
		rc.bottom -= rc.top;
		rc.right -= rc.left;

		rc.top = 20;
		rc.bottom -= 30;
		if(rc.bottom < rc.top)
			rc.bottom = rc.top;
		rc.left = 30;
		rc.right -= 30;
		if(rc.right < rc.left)
			rc.right = rc.left;
		SendMessage(predoc->hwndRE, EM_SETRECT, 0, (LPARAM) &rc);
	}

	// Notify in place active object of resize
	//
	// NOTE : Do not change the following line so that it uses an &&
	// operation, this causes the Mac to lock up since the compiler
	// apparently checks the second half of an AND regardless of the
	// initial half's value.

#ifndef NO_OLE
	if(predoc->pitpcall && (pipaobj = predoc->pitpcall->pipframe->pipaobj))
	{
		TraceTag(tagInPlace, "ResizeBorder");
		GetClientRect(hwndMain, &rc);
# ifdef MAC
		pipaobj->lpVtbl->ResizeBorder(pipaobj, (RectPtr) &rc,
		  (LPOLEINPLACEUIWINDOW) predoc->pitpcall->pipframe, TRUE);
		// Throw out the mem
# else	// MAC
		pipaobj->lpVtbl->ResizeBorder(pipaobj, &rc, 
	 	  (LPOLEINPLACEUIWINDOW) predoc->pitpcall->pipframe, TRUE);
# endif	// MAC, else
	}
#endif 	// !NO_OLE		
}


LOCAL VOID SetupMenu(REDOC *predoc, int iMenu, HMENU hmenu)
{
	DWORD dw;
	LPOLEOBJECT poleobj = NULL;

	switch(iMenu)
	{
	case 0:		// file
		if(!predoc->szFile[0])
			dw = 0;
		else
			dw = (DWORD) SendMessage(predoc->hwndRE, EM_GETMODIFY, 0, 0);
		EnableMenuItem(hmenu, IDM_REVERT, dw ? uiMFEnabled : uiMFDisabled);
		EnableMenuItem(hmenu, IDM_SAVE, predoc->fReadOnly
											? uiMFDisabled : uiMFEnabled);
		break;

	case 1:		// edit
	
		dw = uiMFDisabled;
		// see if something can be pasted
		// let RichEdit figure out if it's read-only
		if(SendMessage(predoc->hwndRE, EM_CANPASTE, 0, 0))
			dw = uiMFEnabled;
		EnableMenuItem(hmenu, IDM_PASTE, (UINT) dw);

		dw = 0;
		if(!predoc->fReadOnly)
			dw = (DWORD) SendMessage(predoc->hwndRE, EM_CANUNDO, 0, 0);
		EnableMenuItem(hmenu, IDM_UNDO, dw ? uiMFEnabled : uiMFDisabled);

//$ REVIEW: use EN_SELCHANGE?
		dw = (DWORD) SendMessage(predoc->hwndRE, EM_SELECTIONTYPE, 0, 0);
		EnableMenuItem(hmenu, IDM_COPY, dw ? uiMFEnabled : uiMFDisabled);
#ifdef DEBUG
		if(predoc->fReadOnly && !QueryCheck(predoc, IDM_ENABLECUTREADONLY))
			dw = 0;
		EnableMenuItem(hmenu, IDM_CUT, dw ? uiMFEnabled : uiMFDisabled);
		if(predoc->fReadOnly)
			dw = 0;
#else	// DEBUG
		if(predoc->fReadOnly)
			dw = 0;
		EnableMenuItem(hmenu, IDM_CUT, dw ? uiMFEnabled : uiMFDisabled);
#endif	// DEBUG, else
		EnableMenuItem(hmenu, IDM_DELETE, dw ? uiMFEnabled : uiMFDisabled);

		EnableMenuItem(hmenu, IDM_INSOBJ, predoc->fReadOnly
											? uiMFDisabled : uiMFEnabled);
		EnableMenuItem(hmenu, IDM_REPLACE, predoc->fReadOnly ?
												uiMFDisabled : uiMFEnabled);


		// That's all we need to do
		if(!predoc->fUpdateEditMenu)
			break;

#ifndef NO_OLE
		// Find out if we have a single object to deal with
		if(!(dw ^ SEL_OBJECT))
		{
			REOBJECT reobj = { 0 };

			reobj.cbStruct = sizeof(REOBJECT);
			reobj.cp = REO_CP_SELECTION;

			if(!predoc->preole->lpVtbl->GetObject(predoc->preole,
													REO_IOB_USE_CP, &reobj,
													REO_GETOBJ_POLEOBJ))
			{
				poleobj = reobj.poleobj;
			}
		}
		// Ask OLE to build the menu for us

# ifdef MAC
//$ FUTURE MAC
		dw = IDM_OBJECTCONVERT;
#  ifdef NEVER
		macMenu1 = CheckoutMenu(hmenu, 2);
		if(!macMenu1)
			DebugStr("\pCheckoutMenu(macMenu1) failed");
		macMenu2 = CheckoutMenu(predoc->hmenuVerbs, 2);
		if(!macMenu2)
			DebugStr("\pCheckoutMenu(macMenu2) failed");

		if(!OleUIAddVerbMenu(poleobj,
						NULL,			// Ask OLE to look up the name for us
						macMenu1, predoc->hmenuVerbs, ipos_Object,
						TRUE, (short *) &dw))
		{
				DebugStr("\pOleUIAddVerbMenu failed!");
		}
		CheckinMenu(hmenu, 2);
		CheckinMenu(predoc->hmenuVerbs, 2);
#  endif	// NEVER
# else	// MAC
		OleUIAddVerbMenu(poleobj,
						NULL,			// Ask OLE to look up the name for us
						hmenu, ipos_Object, IDM_OBJECTMIN, 
						0, TRUE, IDM_OBJECTCONVERT, &predoc->hmenuVerbs);
# endif	// MAC, else

		if(poleobj)
			poleobj->lpVtbl->Release(poleobj);
#endif 	// !NO_OLE
	// We don't have to do all this hard work again unless the user leaves the
	// menu
		predoc->fUpdateEditMenu = FALSE;
		break;

	case 2:		// format
	{
		BOOL fReadOnly = !!predoc->fReadOnly;
		UINT uiSuperscript = MF_UNCHECKED;
		UINT uiSubscript = MF_UNCHECKED;
		UINT uiProtected = MF_UNCHECKED;
		UINT uiLeft = MF_UNCHECKED;
		UINT uiCenter = MF_UNCHECKED;
		UINT uiRight = MF_UNCHECKED;
		UINT uiFirstIndent = MF_UNCHECKED;
		UINT uiFirstOutdent = MF_UNCHECKED;
		CHARFORMAT cf;
		PARAFORMAT pf;

		cf.cbSize = sizeof(CHARFORMAT);
		pf.cbSize = sizeof(PARAFORMAT);

		SendMessage(predoc->hwndRE, EM_GETCHARFORMAT, fTrue, (LPARAM) &cf);
		if(cf.yOffset > 0)
			uiSuperscript = MF_CHECKED;
		else if(cf.yOffset < 0)
			uiSubscript = MF_CHECKED;
		if(cf.dwEffects & CFE_PROTECTED)
			uiProtected = MF_CHECKED;

		SendMessage(predoc->hwndRE, EM_GETPARAFORMAT, 0, (LPARAM) &pf);
		if(!pf.wAlignment || pf.wAlignment == PFA_LEFT)
			uiLeft = MF_CHECKED;
		else if(pf.wAlignment == PFA_CENTER)
			uiCenter = MF_CHECKED;
		else
			uiRight = MF_CHECKED;
		if(pf.dxOffset < 0)
			uiFirstIndent = MF_CHECKED;
		else if(pf.dxOffset > 0)
			uiFirstOutdent = MF_CHECKED;

		CheckMenuItem(hmenu, IDM_SUPERSCRIPT, uiSuperscript);
		CheckMenuItem(hmenu, IDM_SUBSCRIPT, uiSubscript);
		CheckMenuItem(hmenu, IDM_PROTECTED, uiProtected);
		CheckMenuItem(hmenu, IDM_ALIGNLEFT, uiLeft);
		CheckMenuItem(hmenu, IDM_ALIGNCENTER, uiCenter);
		CheckMenuItem(hmenu, IDM_ALIGNRIGHT, uiRight);
		CheckMenuItem(hmenu, IDM_INDENTFIRST, uiFirstIndent);
		CheckMenuItem(hmenu, IDM_OUTDENTFIRST, uiFirstOutdent);

		EnableMenuItem(hmenu, IDM_CHARFORMAT, fReadOnly
												? uiMFDisabled : uiMFEnabled);
		EnableMenuItem(hmenu, IDM_SUPERSCRIPT, fReadOnly
												? uiMFDisabled : uiMFEnabled);
		EnableMenuItem(hmenu, IDM_SUBSCRIPT, fReadOnly
												? uiMFDisabled : uiMFEnabled);
		EnableMenuItem(hmenu, IDM_ALIGNLEFT, fReadOnly
												? uiMFDisabled : uiMFEnabled);
		EnableMenuItem(hmenu, IDM_ALIGNCENTER, fReadOnly
												? uiMFDisabled : uiMFEnabled);
		EnableMenuItem(hmenu, IDM_ALIGNRIGHT, fReadOnly
												? uiMFDisabled : uiMFEnabled);
		EnableMenuItem(hmenu, IDM_INDENTFIRST, fReadOnly
												? uiMFDisabled : uiMFEnabled);
		EnableMenuItem(hmenu, IDM_OUTDENTFIRST, fReadOnly
												? uiMFDisabled : uiMFEnabled);
	}
		break;

	case 3:		// options
	{
		const DWORD eco = SendMessage(predoc->hwndRE, EM_GETOPTIONS, 0, 0);
		UINT uiSelBar = MF_UNCHECKED;
		UINT uiAutoWordSel = MF_UNCHECKED;
#ifdef DEBUG
		UINT uiReadOnly = MF_UNCHECKED;
		UINT uiAutoHScroll = MF_UNCHECKED;
		UINT uiAutoVScroll = MF_UNCHECKED;
		UINT uiAutoHideSel = MF_UNCHECKED;
#endif	// DEBUG

		if(eco & ECO_SELECTIONBAR)
			uiSelBar = MF_CHECKED;
		if(eco & ECO_AUTOWORDSELECTION)
			uiAutoWordSel = MF_CHECKED;
#ifdef DEBUG
		if(eco & ECO_READONLY)
			uiReadOnly = MF_CHECKED;
		if(eco & ECO_AUTOHSCROLL)
			uiAutoHScroll = MF_CHECKED;
		if(eco & ECO_AUTOVSCROLL)
			uiAutoVScroll = MF_CHECKED;
		if(!(eco & ECO_NOHIDESEL))
			uiAutoHideSel = MF_CHECKED;
#endif	// DEBUG

		CheckMenuItem(hmenu, IDM_SELBAR, uiSelBar);
		CheckMenuItem(hmenu, IDM_AUTOWORDSEL, uiAutoWordSel);
#ifdef DEBUG
		CheckMenuItem(hmenu, IDM_READONLY, uiReadOnly);
		CheckMenuItem(hmenu, IDM_AUTOHSCROLL, uiAutoHScroll);
		CheckMenuItem(hmenu, IDM_AUTOVSCROLL, uiAutoVScroll);
		CheckMenuItem(hmenu, IDM_AUTOHIDESEL, uiAutoHideSel);
#endif	// DEBUG
	}
		break;

	}
}


LOCAL LRESULT HandleCommand(REDOC *predoc, HWND hwnd, WPARAM wparam,
								LPARAM lparam)
{
	LRESULT lres = 0;
	INT		nID;

	if(GET_WM_COMMAND_HWND(wparam, lparam) == predoc->hwndRE && predoc->hwndRE)
	{
		WORD wNotification = GET_WM_COMMAND_CMD(wparam, lparam);
		ASSENSZ *passensz;

		switch(wNotification)
		{
		case EN_CHANGE:
			if(predoc->hwndFormatBar)
				UpdateFormatBar(predoc);
			break;

		case EN_ERRSPACE:
			if(fErrSpace)
				break;
			fErrSpace = fTrue;
			// fall through to default

		default:
			for(passensz = rgassenszErrors; passensz->szDescription; passensz++)
			{
				if(passensz->wNotification == wNotification)
				{
					MessageBeep(0);
					MessageBoxA(hwndMain, passensz->szDescription, NULL,
						MB_ICONSTOP | MB_OK);
					return 0;
				}
			}
			break;
		}
		return 0;
	}

	fErrSpace = fFalse;

	nID = GET_WM_COMMAND_ID(wparam, lparam);
	switch(nID)
	{
#ifdef DEBUG
	case IDM_CLSDBG:
		ClearDebugScreen();
		break;

	case IDM_TRACEDLG:
		DoTagsDialog();
		break;
#endif	// DEBUG

	case IDM_NEW:
		lres = NewREDoc(predoc, fTrue, fTrue);
#ifdef DEBUG
		if(predoc->hwndRE)
			SendMessage(predoc->hwndRE, EM_REQUESTRESIZE, 0, 0);
#endif	// DEBUG
		break;

	case IDM_OPEN:
		lres = OpenREDoc(predoc, FALSE);
		break;

	case IDM_REVERT:
		lres = RevertREDoc(predoc);
		break;

	case IDM_PRINT:
		PrintREDoc(predoc);
		break;

	case IDM_PRINTPREVIEW:
		DialogBoxParam(HinstFromHwnd(hwndMain), TEXT("PRINTPREVIEW"), hwndMain,
			(DLGPROC) PPDlgProc, (LPARAM) predoc);
		break;

	case IDM_PRINTSETUP:
		predoc->pd.lStructSize = sizeof(PRINTDLG);
		predoc->pd.Flags = PD_PRINTSETUP;
		if(PrintDlg(&predoc->pd) && predoc->fWysiwyg)
		{
			// illegal values to force SetWordWrap() to do something
			predoc->fWrap = fFalse;
			predoc->fWysiwyg = fTrue;
			SetWordWrap(predoc, fTrue, fTrue);
		}
		break;

	case IDM_EXIT:
		PostMessage(hwndMain, WM_CLOSE, 0, 0);
		return 0;

	case IDM_CLOSE:
		return CloseREDoc(predoc, fTrue, fTrue);

	case IDM_SAVE:
		lres = SaveREDoc(predoc);
		break;

	case IDM_SAVEAS:
		lres = SaveREDocAs(predoc, FALSE);
		break;

	case IDM_UNDO:
		lres = SendMessage(predoc->hwndRE, EM_UNDO, 0, 0);
		break;

	case IDM_CUT:
		lres = SendMessage(predoc->hwndRE, WM_CUT, 0, 0);
		break;

	case IDM_COPY:
		lres = SendMessage(predoc->hwndRE, WM_COPY, 0, 0);
		break;

	case IDM_PASTE:
		lres = SendMessage(predoc->hwndRE, WM_PASTE, 0, 0);
		break;

	case IDM_PASTESPECIAL:
		NYI("Paste special");
		break;

	case IDM_DELETE:
		lres = SendMessage(predoc->hwndRE, WM_KEYDOWN,
				(WPARAM) VK_DELETE, 0);
		break;

	case IDM_SELECTALL:
		lres = SendMessage(predoc->hwndRE, EM_SETSEL, 0, (LPARAM) -1);
		break;

	case IDM_FIND:
		FindReplace(predoc, fFalse);
		break;

	case IDM_REPLACE:
		FindReplace(predoc, fTrue);
		break;

	case IDM_OBJECT:
		NYI("Object");
		break;

	case IDM_OBJECTCONVERT:
		NYI("Object Convert");
		break;

	case IDM_INSOBJ:
		return InsertObject(predoc);

	case IDM_INSFILE:
		lres = OpenREDoc(predoc, TRUE);
		break;

	case IDM_SAVESEL:
		lres = SaveREDocAs(predoc, TRUE);
		break;

	case IDM_CHARFORMAT:
		SelectCharFormat(predoc);
		break;

	case IDM_APPLYTOWORD:
		predoc->scf = SCF_SELECTION;
		if(ToggleCheck(predoc, IDM_APPLYTOWORD))
			predoc->scf |= SCF_WORD;
		break;

	case IDM_SUPERSCRIPT:
		SetOffset(predoc, fTrue);
		break;

	case IDM_SUBSCRIPT:
		SetOffset(predoc, fFalse);
		break;

	case IDM_ALIGNLEFT:
		SetAlignment(predoc, PFA_LEFT);
		break;

	case IDM_ALIGNCENTER:
		SetAlignment(predoc, PFA_CENTER);
		break;

	case IDM_ALIGNRIGHT:
		SetAlignment(predoc, PFA_RIGHT);
		break;

	case IDM_INDENTFIRST:
		IndentFirst(predoc, fTrue);
		break;

	case IDM_OUTDENTFIRST:
		IndentFirst(predoc, fFalse);
		break;

	case IDM_MARGINS:
		NYI("set margins");
		break;

	case IDM_TABS:
		NYI("set tabs");
		break;

	case IDM_PROTECTED:
		ProtectSelection(predoc);
		break;

	case IDM_NOWRAP:
		SetWordWrap(predoc, fFalse, fFalse);
		break;

	case IDM_WRAP:
		SetWordWrap(predoc, fFalse, fTrue);
		break;

	case IDM_WYSIWYG:
		SetWordWrap(predoc, fTrue, fTrue);
		break;

	case IDM_SELBAR:
		SendMessage(predoc->hwndRE, EM_SETOPTIONS, ECOOP_XOR, ECO_SELECTIONBAR);
		ToggleCheck(predoc, IDM_SELBAR);
		break;

	case IDM_AUTOWORDSEL:
		SendMessage(predoc->hwndRE, EM_SETOPTIONS, ECOOP_XOR, ECO_AUTOWORDSELECTION);
		ToggleCheck(predoc, IDM_AUTOWORDSEL);
		break;

	case IDM_SHOWMARGINS:
		ShowMargins(predoc);
		break;

#ifdef DEBUG
	case IDM_READONLY:
		SendMessage(predoc->hwndRE, EM_SETOPTIONS, ECOOP_XOR, ECO_READONLY);
		predoc->fReadOnly = !!ToggleCheck(predoc, IDM_READONLY);
		EnableWindow(predoc->hwndFormatBar, !predoc->fReadOnly);
		break;

	case IDM_AUTOHSCROLL:
		SendMessage(predoc->hwndRE, EM_SETOPTIONS, ECOOP_XOR, ECO_AUTOHSCROLL);
		ToggleCheck(predoc, IDM_AUTOHSCROLL);
		break;

	case IDM_AUTOVSCROLL:
		SendMessage(predoc->hwndRE, EM_SETOPTIONS, ECOOP_XOR, ECO_AUTOVSCROLL);
		ToggleCheck(predoc, IDM_AUTOVSCROLL);
		break;

	case IDM_AUTOHIDESEL:
		SendMessage(predoc->hwndRE, EM_SETOPTIONS, ECOOP_XOR, ECO_NOHIDESEL);
		ToggleCheck(predoc, IDM_AUTOHIDESEL);
		break;
#endif	// DEBUG

	case IDM_GOTOCURSOR:
		{
			CHARRANGE cr;
			POINT pt;

			GetCursorPos(&pt);
			ScreenToClient(predoc->hwndRE, &pt);
			cr.cpMin = SendMessage(predoc->hwndRE, EM_CHARFROMPOS, 0,
									(LPARAM) &pt);
			cr.cpMost = cr.cpMin;
			SendMessage(predoc->hwndRE, EM_EXSETSEL, 0, (LPARAM) &cr);
		}
		break;

	case IDM_MOVECURSOR:
		{
			CHARRANGE cr;
			POINT pt;

			SendMessage(predoc->hwndRE, EM_EXGETSEL, 0, (LPARAM) &cr);
			SendMessage(predoc->hwndRE, EM_POSFROMCHAR, (WPARAM) &pt, cr.cpMin);
			ClientToScreen(predoc->hwndRE, &pt);
			SetCursorPos(pt.x, pt.y);
		}
		break;

	case TBI_IncreaseIndent:
	case TBI_DecreaseIndent:
		if(predoc->fReadOnly)
		{
			MessageBeep(0);
		}
		else
		{
			PARAFORMAT pf;

			pf.cbSize = sizeof(PARAFORMAT);

			if(GetFocus() == predoc->hwndFormatBar)
				SetFocus(predoc->hwndRE);
			pf.dwMask = PFM_OFFSETINDENT;
			pf.dxStartIndent = (nID == TBI_IncreaseIndent)
									? cxBulletIndent
									: -cxBulletIndent;
			if(!SendMessage(predoc->hwndRE, EM_SETPARAFORMAT, FALSE,
								(LPARAM) &pf))
			{
				MessageBeep(0);
			}
		}
		break;

	case TBI_Name:
	case TBI_Size:
	case TBI_Bold:
	case TBI_Italic:
	case TBI_Underline:
	case TBI_Color:
		{
			CHARFORMAT cf;

			cf.cbSize = sizeof(CHARFORMAT);
			if(GetFocus() == predoc->hwndFormatBar)
				SetFocus(predoc->hwndRE);
			SendMessage(predoc->hwndFormatBar, EM_GETCHARFORMAT, 0,
						(LPARAM) &cf);
			SendMessage(predoc->hwndRE, EM_SETCHARFORMAT, predoc->scf,
							(LPARAM) &cf);
		}
		break;

	case TBI_AccelBold:
	case TBI_AccelItalic:
	case TBI_AccelUnderline:
		{
			CHARFORMAT cf;
			DWORD dwEffects;

			cf.cbSize = sizeof(CHARFORMAT);
			SendMessage(predoc->hwndFormatBar, EM_GETCHARFORMAT, 0,
						(LPARAM) &cf);
			switch (nID)
			{
			case TBI_AccelBold:
				dwEffects = CFE_BOLD;
				break;
			case TBI_AccelItalic:
				dwEffects = CFE_ITALIC;
				break;
			case TBI_AccelUnderline:
				dwEffects = CFE_UNDERLINE;
				break;
			}

			cf.dwMask |= dwEffects;
			cf.dwEffects ^= dwEffects;

			if(GetFocus() == predoc->hwndFormatBar)
				SetFocus(predoc->hwndRE);
			SendMessage(predoc->hwndFormatBar, EM_SETCHARFORMAT, predoc->scf,
							(LPARAM) &cf);
			SendMessage(predoc->hwndRE, EM_SETCHARFORMAT, predoc->scf,
							(LPARAM) &cf);
		}
		break;

	case TBI_Bullet:
	case TBI_Left:
	case TBI_Center:
	case TBI_Right:
		{
			PARAFORMAT pf;

			pf.cbSize = sizeof(PARAFORMAT);

			if(GetFocus() == predoc->hwndFormatBar)
				SetFocus(predoc->hwndRE);
			SendMessage(predoc->hwndFormatBar, EM_GETPARAFORMAT, 0,
						(LPARAM) &pf);
			SendMessage(predoc->hwndRE, EM_SETPARAFORMAT, FALSE, (LPARAM) &pf);
		}
		break;


#ifdef DEBUG
	case IDM_DBGPED:
		SendMessage(predoc->hwndRE, EM_DBGPED, 0, 0);
		break;

	case IDM_GETTEXT:
		return GetText(predoc);

	case IDM_IGNORELEFTCLICK:
		IgnoreLeftClick(predoc);
		break;

	case IDM_EATES:
		EatEs(predoc);
		break;

	case IDM_BOTTOMLESS:
		Bottomless(predoc);
		break;

	case IDM_IGNOREDROPS:
	case IDM_TEXTONLY:
	case IDM_REFUSEGRAPH:
	case IDM_PPMETA:
	case IDM_ENABLECUTREADONLY:
	case IDM_ENABLEPASTEREADONLY:
	case IDM_ENABLEDRAGREADONLY:
	case IDM_SWAPDRAGEFFECT:
		ToggleCheck(predoc, nID);
		break;

	case IDM_HIDE:
		ShowWindow(predoc->hwndRE, ToggleCheck(predoc, IDM_HIDE) ? SW_HIDE : SW_SHOW);
		break;		

	case IDM_PASTEPLAINTEXT:
		lres = SendMessage(predoc->hwndRE, EM_PASTESPECIAL, CF_TEXT, 0);
		break;

	case IDM_PASTETXTOBJ:
		lres = SendMessage(predoc->hwndRE, EM_PASTESPECIAL, cfTxtObj, 0);
		break;

	case IDM_PASTERTFASTEXT:
		lres = SendMessage(predoc->hwndRE, EM_PASTESPECIAL, cfRTFAsText, 0);
		break;

	case IDM_BIGLIMIT:
		SetLimit(predoc);
		break;

	case IDM_FILLERUP:
		FillerUp(predoc);
		break;
#endif	// DEBUG

	default:
		// Pass through OLE verbs
		if(nID >= IDM_OBJECTMIN)
		{
			DoVerb(predoc, nID - IDM_OBJECTMIN);
		}
		return DefWindowProc(hwnd, WM_COMMAND, wparam, lparam);
	}

	return lres;
}


VOID DoVerb(REDOC * predoc, INT ioleverb)
{
	REOBJECT reobj = { 0 };
	POINT pt;
	RECT rc = { 0 };

	reobj.cbStruct = sizeof(REOBJECT);
	if(predoc->preole->lpVtbl->GetObject(predoc->preole, REO_IOB_SELECTION,
											&reobj,
											REO_GETOBJ_POLESITE |
											REO_GETOBJ_POLEOBJ))
	{
		AssertSz(FALSE, "DoVerb without object");
	}

	SendMessage(predoc->hwndRE, EM_POSFROMCHAR, (WPARAM) &pt, reobj.cp);

	XformSizeInHimetricToPixels(NULL, &reobj.sizel, &reobj.sizel);
	rc.right = (INT) reobj.sizel.cx;
	rc.bottom = (INT) reobj.sizel.cy;
	OffsetRect(&rc, pt.x, pt.y);

	reobj.poleobj->lpVtbl->DoVerb(reobj.poleobj, ioleverb, NULL,
									reobj.polesite, 0, predoc->hwndRE, &rc);
	reobj.poleobj->lpVtbl->Release(reobj.poleobj);
	reobj.polesite->lpVtbl->Release(reobj.polesite);

}


#ifdef DEBUG

LOCAL VOID IgnoreLeftClick(REDOC *predoc)
{
	HMENU hmenu = GetMenu(hwndMain);
	UINT uiMenuFlags;
	DWORD dwMask;

	Assert(predoc->hwndRE);

	dwMask = SendMessage(predoc->hwndRE, EM_GETEVENTMASK, 0, 0);
	uiMenuFlags = GetMenuState(hmenu, IDM_IGNORELEFTCLICK, MF_BYCOMMAND);
	if(uiMenuFlags & MF_CHECKED)
		dwMask &= ~ENM_MOUSEEVENTS;
	else
		dwMask |= ENM_MOUSEEVENTS;
	uiMenuFlags ^= MF_CHECKED;
	CheckMenuItem(hmenu, IDM_IGNORELEFTCLICK, MF_BYCOMMAND |
		(uiMenuFlags & MF_CHECKED));
	SendMessage(predoc->hwndRE, EM_SETEVENTMASK, 0, dwMask);
}


LOCAL VOID EatEs(REDOC *predoc)
{
	HMENU hmenu = GetMenu(hwndMain);
	UINT uiMenuFlags;
	DWORD dwMask;

	Assert(predoc->hwndRE);

	dwMask = SendMessage(predoc->hwndRE, EM_GETEVENTMASK, 0, 0);
	uiMenuFlags = GetMenuState(hmenu, IDM_EATES, MF_BYCOMMAND);
	if(uiMenuFlags & MF_CHECKED)
		dwMask &= ~ENM_KEYEVENTS;
	else
		dwMask |= ENM_KEYEVENTS;
	uiMenuFlags ^= MF_CHECKED;
	CheckMenuItem(hmenu, IDM_EATES, MF_BYCOMMAND | (uiMenuFlags & MF_CHECKED));
	SendMessage(predoc->hwndRE, EM_SETEVENTMASK, 0, dwMask);
}


LOCAL VOID Bottomless(REDOC *predoc)
{
	HMENU hmenu = GetMenu(hwndMain);
	UINT uiMenuFlags;
	DWORD dwMask;

	Assert(predoc->hwndRE);

	dwMask = SendMessage(predoc->hwndRE, EM_GETEVENTMASK, 0, 0);
	uiMenuFlags = GetMenuState(hmenu, IDM_BOTTOMLESS, MF_BYCOMMAND);
	if(uiMenuFlags & MF_CHECKED)
		dwMask &= ~ENM_REQUESTRESIZE;
	else
		dwMask |= ENM_REQUESTRESIZE;
	uiMenuFlags ^= MF_CHECKED;
	CheckMenuItem(hmenu, IDM_BOTTOMLESS,
		MF_BYCOMMAND | (uiMenuFlags & MF_CHECKED));
	SendMessage(predoc->hwndRE, EM_SETEVENTMASK, 0, dwMask);
	if(dwMask & ENM_REQUESTRESIZE)
	{
		SendMessage(predoc->hwndRE, EM_REQUESTRESIZE, 0, 0);
	}
	else
	{
		RECT rc;

		GetClientRect(predoc->hwndParent, &rc);
		ResizeRedoc(predoc, rc);
	}
}

#endif	// DEBUG


LOCAL BOOL ToggleCheck(REDOC *predoc, UINT uiMenuid)
{
	HMENU hmenu = GetMenu(hwndMain);
	UINT uiMenuFlags;

	Assert(predoc->hwndRE);

	uiMenuFlags = GetMenuState(hmenu, uiMenuid, MF_BYCOMMAND);
	uiMenuFlags ^= MF_CHECKED;
	CheckMenuItem(hmenu, uiMenuid, MF_BYCOMMAND | (uiMenuFlags & MF_CHECKED));

	return !!(uiMenuFlags & MF_CHECKED);
}


LOCAL BOOL QueryCheck(REDOC *predoc, UINT uiMenuid)
{
	HMENU hmenu = GetMenu(hwndMain);
	UINT uiMenuFlags;

	Assert(predoc->hwndRE);
	if(!hmenu)
		return fFalse;

	uiMenuFlags = GetMenuState(hmenu, uiMenuid, MF_BYCOMMAND);

	return !!(uiMenuFlags & MF_CHECKED);
}


LOCAL LRESULT NewREDoc(REDOC *predoc, BOOL fPrompt, BOOL fUpdateUI)
{
	RECT rc;
	DWORD dwStyle;
	if(predoc->hwndRE)
	{
		PARAFORMAT pf = {0};

		pf.cbSize = sizeof(PARAFORMAT);

		if(fPrompt && CheckSave(predoc) < 0)
			return -1;
		predoc->szFile[0] = TEXT('\0');
		lstrcpy(predoc->szTitle, szUntitled);
		SetWindowText(predoc->hwndRE, TEXT(""));
		pf.wAlignment = PFA_LEFT;
		pf.cTabCount = 1;
		pf.rgxTabs[0] = lDefaultTab;
		pf.dwMask = PFM_STARTINDENT | PFM_RIGHTINDENT | PFM_OFFSET |
						PFM_ALIGNMENT | PFM_TABSTOPS | PFM_NUMBERING;
		SendMessage(predoc->hwndRE, EM_SETPARAFORMAT, 0, (LPARAM) &pf);
		SendMessage(predoc->hwndRE, EM_SETCHARFORMAT, 0,
						(LPARAM) (LPVOID) &cfDefault);
		goto done;
	}
	else
	{
		predoc->szFile[0] = TEXT('\0');
		lstrcpy(predoc->szTitle, szUntitled);
	}
	GetClientRect(predoc->hwndParent, &rc);
	InflateRect(&rc, dxRESize, dyRESize);

	// Create and display the format bar
	if(predoc->hwndFormatBar = HwndCreateFormatBar(predoc->hwndParent,
							FBR_FormatBar, NULL))
	{
		RECT rcFormatBar;

		ShowWindow(predoc->hwndFormatBar, SW_SHOW);
		GetClientRect(predoc->hwndFormatBar, &rcFormatBar);
		rc.top += rcFormatBar.bottom;
	}

#ifdef SUNKENRICHEDIT
	dwStyle = 
				ES_AUTOHSCROLL |
				ES_AUTOVSCROLL |
//				ES_DISABLENOSCROLL |
				ES_MULTILINE |
//				ES_NOHIDESEL |
				ES_SAVESEL |
				ES_SELECTIONBAR |
				ES_SUNKEN |
//				WS_BORDER |
				WS_CHILD |
				WS_CLIPCHILDREN |
				WS_HSCROLL |
				WS_VISIBLE |
				WS_VSCROLL |
				0;		// zero gets or'd with above
	predoc->hwndRE = CreateWindow(szClassRE, TEXT(""),
				dwStyle,
				rc.left, rc.top,
				rc.right - rc.left,	rc.bottom - rc.top, predoc->hwndParent,
				NULL, HinstFromHwnd(predoc->hwndParent), NULL);

#else	// SUNKENRICHEDIT
				ES_AUTOHSCROLL |
				ES_AUTOVSCROLL |
//				ES_DISABLENOSCROLL |
				ES_MULTILINE |
//				ES_NOHIDESEL |
				ES_SAVESEL |
				ES_SELECTIONBAR |
//				ES_SUNKEN |
//				WS_BORDER |
				WS_CHILD |
				WS_CLIPCHILDREN |
				WS_HSCROLL |
				WS_VISIBLE |
				WS_VSCROLL |
				0;		// zero gets or'd with above
	predoc->hwndRE = CreateWindow(szClassRE, TEXT(""),
				dwStyle,
				rc.left, rc.top,
				rc.right - rc.left,	rc.bottom - rc.top, predoc->hwndParent,
				NULL, HinstFromHwnd(predoc->hwndParent), NULL);
#endif	// SUNKENRICHEDIT, else
	if(!predoc->hwndRE)
	{
		MessageBoxA(hwndMain, "Unable to create a new document", NULL, MB_ICONSTOP | MB_OK);
		return -1;
	}
	if(cchTextMost)
		SendMessage(predoc->hwndRE, EM_EXLIMITTEXT, 0, cchTextMost);
#ifndef NO_OLE
	DragAcceptFiles(predoc->hwndRE, TRUE);
#endif	// !NO_OLE


	// request EN_SELCHANGE, EN_CHANGE, EN_PROTECTED, and EN_DROPFILES
	SendMessage(predoc->hwndRE, EM_SETEVENTMASK, 0,
		ENM_SELCHANGE | ENM_CHANGE | ENM_PROTECTED | EN_DROPFILES |
		ENM_CORRECTTEXT);

	SetFocus(predoc->hwndRE);

	predoc->scf = SCF_SELECTION;
	if(GetMenu(hwndMain) && QueryCheck(predoc, IDM_APPLYTOWORD))
		predoc->scf |= SCF_WORD;

#ifndef NO_OLE
	if(!SendMessage(predoc->hwndRE, EM_GETOLEINTERFACE, 0, (LPARAM) &predoc->preole))
	{
		MessageBoxA(hwndMain, "No OLE interface!", NULL, MB_OK);
		DestroyWindow(predoc->hwndRE);
		predoc->hwndRE = 0;
		return -1;
	}

	if(!(predoc->pstg = OleStdCreateRootStorage(NULL, STGM_SHARE_EXCLUSIVE)))
	{
		MessageBoxA(hwndMain, "No Storage!", NULL, MB_OK);
		DestroyWindow(predoc->hwndRE);
		predoc->hwndRE = 0;
		return -1;
	}

	if(!(predoc->pitpcall = ITPCALL_New(predoc)))
	{
		MessageBoxA(hwndMain, "No callback object!", NULL, MB_OK);
		DestroyWindow(predoc->hwndRE);
		predoc->hwndRE = 0;
		return -1;
	}
	SendMessage(predoc->hwndRE, EM_SETOLECALLBACK, 0, (LPARAM) predoc->pitpcall);
#endif	// !NO_OLE

done:
	if(fUpdateUI)
	{
		TCHAR szT[64];

		wsprintf(szT, szFmtTitle, predoc->szTitle);
		SetWindowText(predoc->hwndParent, szT);
		SetMenu(hwndMain, hmenuFull);
		DrawMenuBar(hwndMain);
	}

	predoc->fReadOnly = fFalse;
	EnableWindow(predoc->hwndFormatBar, TRUE);

	// illegal values to force SetWordWrap() to do something
	predoc->fWrap = fFalse;
	predoc->fWysiwyg = fTrue;
	SetWordWrap(predoc, fWysiwygDefault, fWrapDefault);
	// if we don't have a default font, use the windows variable width font
	// otherwise, use the default font
	if(cfDefault.dwMask == 0)
	{
		SendMessage(predoc->hwndRE, WM_SETFONT,
						(WPARAM) GetStockObject(ANSI_VAR_FONT), 0);
		SendMessage(predoc->hwndRE, EM_GETCHARFORMAT, FALSE,
						(LPARAM) (LPVOID) &cfDefault);
	}
	else
	{
		SendMessage(predoc->hwndRE, EM_SETCHARFORMAT, 0,
						(LPARAM) (LPVOID) &cfDefault);
	}
	SendMessage(predoc->hwndRE, EM_SETMODIFY, (WPARAM) fFalse, 0);
	SendMessage(predoc->hwndRE, EM_SETREADONLY, (WPARAM) fFalse, 0);
	UpdateFormatBar(predoc);

	return 0;
}


LOCAL LONG CheckSave(REDOC *predoc)
{
	int iMbid;
	TCHAR szT[128];

#ifdef NO_SAVE_PROMPT
	return 0;
#endif	// NO_SAVE_PROMPT

	if(!SendMessage(predoc->hwndRE, EM_GETMODIFY, 0, 0))
		return 0;

	wsprintf(szT, TEXT("Save changes to %s?"), predoc->szTitle);
	iMbid = MessageBox(hwndMain, szT, szAppName, MB_APPLMODAL |
			MB_ICONQUESTION | MB_YESNOCANCEL);
	switch(iMbid)
	{
	case IDYES:
		if(SaveREDoc(predoc) < 0)
			return -1;
		break;

	case IDCANCEL:
		return -1;
	}
	return 0;
}


// returns 0 if no changes have been made
// returns > 0 if revert should continue
// returns < 0 if revert should be aborted
LOCAL INT CheckRevert(REDOC *predoc)
{
	int iMbid;
	TCHAR szT[128];

	if(!SendMessage(predoc->hwndRE, EM_GETMODIFY, 0, 0))
		return 0;

#ifdef NO_SAVE_PROMPT
	return 1;
#endif	// NO_SAVE_PROMPT

	wsprintf(szT, TEXT("Revert %s to last saved changes?"), predoc->szTitle);
	iMbid = MessageBox(hwndMain, szT, szAppName, MB_APPLMODAL |
			MB_ICONQUESTION | MB_YESNO);

	return iMbid == IDYES ? 1 : -1;
}


LOCAL LRESULT CloseREDoc(REDOC *predoc, BOOL fPrompt, BOOL fUpdateUI)
{
	if(fPrompt && CheckSave(predoc) < 0)
		return -1;

	if(predoc->hdcTarget)
	{
		DeleteDC(predoc->hdcTarget);
		predoc->hdcTarget = 0;
	}
#ifndef NO_OLE
	// Deactivate any existing in place object
	//$ FUTURE: This might be some generic I'm gonna close you call
	predoc->preole->lpVtbl->InPlaceDeactivate(predoc->preole);
	ITPCALL_Release((LPUNKNOWN) predoc->pitpcall);
	predoc->pitpcall = NULL;
	predoc->pstg->lpVtbl->Release(predoc->pstg);
	predoc->pstg = NULL;
	predoc->preole->lpVtbl->Release(predoc->preole);
	predoc->preole = NULL;
	predoc->cItem = 0;
#endif	// !NO_OLE
	DestroyWindow(predoc->hwndRE);
	DestroyWindow(predoc->hwndFormatBar);

	predoc->hwndRE = 0;
	predoc->szFile[0] = TEXT('\0');
	lstrcpy(predoc->szTitle, szUntitled);
	predoc->dwFormat = SF_TEXT;
	predoc->fReadOnly = fFalse;
	EnableWindow(predoc->hwndFormatBar, TRUE);
#ifdef DEBUG
	CheckMenuItem(hmenuFull, IDM_IGNORELEFTCLICK, MF_BYCOMMAND | MF_UNCHECKED);
	CheckMenuItem(hmenuFull, IDM_EATES, MF_BYCOMMAND | MF_UNCHECKED);
	CheckMenuItem(hmenuFull, IDM_IGNOREDROPS, MF_BYCOMMAND | MF_UNCHECKED);
	CheckMenuItem(hmenuFull, IDM_BOTTOMLESS, MF_BYCOMMAND | MF_UNCHECKED);
	CheckMenuItem(hmenuFull, IDM_TEXTONLY, MF_BYCOMMAND | MF_UNCHECKED);

	if(hwndGT)
	{
		DestroyWindow(hwndGT);
		hwndGT = 0;
	}
#endif	// DEBUG

	if(fUpdateUI)
	{
		SetWindowText(predoc->hwndParent, szClosedName);
		SetMenu(hwndMain, hmenuLoaded);
		DrawMenuBar(hwndMain);
	}

	return 1;
}


DWORD CALLBACK MyRead(DWORD dwCookie, LPBYTE pbBuffer, LONG cb, LONG *pcb)
{
	HFILE	hf = (HFILE) dwCookie;

	if(hf == HFILE_ERROR)
		return (DWORD) E_FAIL;
	*pcb = _lread(hf, pbBuffer, cb);
	return (DWORD) (*pcb >= 0 ? NOERROR : (*pcb = 0, E_FAIL));
}


// This function gives the Mac version the ability to open and print
// files via Apple Events.
LRESULT DoOpen(predoc, szT, szTitle, fInsert)
REDOC *predoc;
LPSTR szT, szTitle;
BOOL fInsert;
{
	DWORD dwError;

	if((dwError = ReadREDoc(predoc, szT, szTitle, 0, fInsert)))
		goto err;
	wsprintf(szT, szFmtTitle, szTitle);
	SetWindowText(predoc->hwndParent, szT);

	EnableWindow(predoc->hwndFormatBar, !predoc->fReadOnly);
	SendMessage(predoc->hwndRE, EM_SETREADONLY, (WPARAM) predoc->fReadOnly, 0);
	SetMenu(hwndMain, hmenuFull);

	SetupWordWrapMenu(predoc);
	DrawMenuBar(hwndMain);
	return 0;

err:
	wsprintf(szT, TEXT("Error opening document. [%ld]"), dwError);
	MessageBox(hwndMain, szT, NULL, MB_OK);
	return -1;
}


LOCAL LRESULT OpenREDoc(REDOC *predoc, BOOL fInsert)
{
	DWORD dwError;
	OPENFILENAME ofn;
	TCHAR szTitle[64];
	TCHAR szT[256];

	if(predoc->hwndRE && !fInsert && CheckSave(predoc) < 0)
		return -1;

	if(fInsert && predoc->fReadOnly)
		return -1;

	ofn.lStructSize			= sizeof(ofn);
	ofn.hInstance			= 0;
	ofn.lpstrFilter			= szFilterLoad;
	ofn.lpstrCustomFilter	= NULL;
	ofn.nMaxCustFilter		= 0;
	ofn.nFilterIndex		= 0;
	ofn.lpstrFileTitle		= szTitle;
	ofn.nMaxFileTitle		= sizeof(szTitle);
	ofn.lpstrInitialDir		= NULL;
	ofn.lpstrTitle			= fInsert ? "Insert from File" : NULL;
	ofn.nFileOffset			= 0;
	ofn.nFileExtension		= 0;
	ofn.lpstrDefExt			= NULL;
	ofn.lCustData			= 0L;
	ofn.lpfnHook			= NULL;
	ofn.lpTemplateName		= NULL;
	ofn.hwndOwner			= hwndMain;
	ofn.lpstrFile			= szT;
	ofn.nMaxFile			= sizeof(szT);
	ofn.Flags				= OFN_FILEMUSTEXIST;

	szTitle[0] = TEXT('\0');
	szT[0] = TEXT('\0');

	// Query user for filename for input
    if(!GetOpenFileName(&ofn))
	{
		if((dwError = CommDlgExtendedError()) != 0)
		{
			wsprintf(szT, TEXT("Error opening document. [%ld]"), dwError);
			MessageBox(hwndMain, szT, NULL, MB_OK);
			return -1;
		}
		return 0;
	}
	predoc->fReadOnly = (ofn.Flags & OFN_READONLY) ? fTrue : fFalse;
	EnableWindow(predoc->hwndFormatBar, !predoc->fReadOnly);
	return(DoOpen(predoc, szT, szTitle, fInsert));	
}


LOCAL LRESULT RevertREDoc(REDOC *predoc)
{
	DWORD dwError;
	TCHAR szT[256];

	if(CheckRevert(predoc) <= 0)
		return 0;

	lstrcpy(szT, predoc->szFile);
	dwError = ReadREDoc(predoc, szT, NULL, predoc->dwFormat, FALSE);
	if(!dwError)
		return 0;

	wsprintf(szT, TEXT("Error reading document. [%ld]"), dwError);
	MessageBox(hwndMain, szT, NULL, MB_OK);

	return -1;
}


LOCAL DWORD ReadREDoc(REDOC *predoc, LPCSTR szFile, LPCSTR szTitle,
				DWORD dwFormat, BOOL fInsert)
{
	LONG cch;
	HCURSOR hcur;
	EDITSTREAM es;
	TCHAR szType[cchRTFSig + 1];

 	hcur = SetCursor(LoadCursor(NULL, IDC_WAIT));

	es.dwCookie = (DWORD) _lopen(szFile, OF_READ);
	if(es.dwCookie == (DWORD) HFILE_ERROR)
	{
		return GetLastError();
	}

	if(!fInsert)
	{
		// save read-only flag across NewREDoc()
		const BOOL fReadOnlySave = predoc->fReadOnly;

		if(NewREDoc(predoc, fFalse, fFalse) < 0)
		{
			_lclose((HFILE) es.dwCookie);
			return (DWORD) -1;
		}
		predoc->fReadOnly = fReadOnlySave;
	}
	if(dwFormat == 0)	// unknown format, figure out what it is
	{
		UINT cb = cchRTFSig * sizeof(TCHAR);

		cb = _lread((HFILE) es.dwCookie, szType, cb);
		szType[cb / sizeof(TCHAR)] = TEXT('\0');
		if(cb == cchRTFSig * sizeof(TCHAR))
			dwFormat = lstrcmpi(szRTFSig, szType) ? SF_TEXT : SF_RTF;
		else
			dwFormat = SF_TEXT;		// not big enough to be RTF, assume text

		// move back to the beginning of the file
		_llseek((HFILE) es.dwCookie, 0, 0);
	}

	SendMessage(predoc->hwndRE, WM_SETREDRAW, (WPARAM) fFalse, 0);

	es.dwError = 0;
	es.pfnCallback = MyRead;

	cch = SendMessage(predoc->hwndRE, EM_STREAMIN,
			(WPARAM) (fInsert ? dwFormat | SFF_SELECTION : dwFormat),
			(LPARAM) &es);
	_lclose((HFILE) es.dwCookie);
#ifdef DEBUG
	if(predoc->hwndRE)
		SendMessage(predoc->hwndRE, EM_REQUESTRESIZE, 0, 0);
#endif	// DEBUG

	SendMessage(predoc->hwndRE, EM_SETMODIFY, (WPARAM) fFalse, 0);

	predoc->dwFormat = dwFormat;
	lstrcpy(predoc->szFile, szFile);
	if(szTitle)
		lstrcpy(predoc->szTitle, szTitle);
	else
		GetFileTitle(szFile, predoc->szTitle, sizeof(predoc->szTitle));

	SendMessage(predoc->hwndRE, WM_SETREDRAW, (WPARAM) fTrue, 0);
	InvalidateRect(predoc->hwndRE, NULL, fTrue);
	UpdateWindow(predoc->hwndRE);

	SetCursor(hcur);

	UpdateFormatBar(predoc);
	return 0;
}


DWORD CALLBACK MyWrite(DWORD dwCookie, LPBYTE pbBuffer, LONG cb, LONG *pcb)
{
	HFILE	hf = (HFILE) dwCookie;

	if(hf == HFILE_ERROR)
		return (DWORD) E_FAIL;

	*pcb = _lwrite(hf, pbBuffer, cb);
	return (DWORD) (*pcb == cb ? NOERROR : E_FAIL);
}


LOCAL LRESULT SaveREDoc(REDOC *predoc)
{
	HCURSOR hcur;
	LONG cch;
	DWORD dwError;
	EDITSTREAM es;

	if(!predoc->szFile[0])
		return SaveREDocAs(predoc, FALSE);

	hcur = SetCursor(LoadCursor(NULL, IDC_WAIT));

	es.dwCookie = _lcreat(predoc->szFile, 0);
	if(es.dwCookie == (DWORD) HFILE_ERROR)
	{
		dwError = GetLastError();
		goto err;
	}
	es.dwError = 0;
	es.pfnCallback = MyWrite;
	cch = SendMessage(predoc->hwndRE, EM_STREAMOUT,	(WPARAM) predoc->dwFormat,
			(LPARAM) &es);
	_lclose((HFILE) es.dwCookie);

	SendMessage(predoc->hwndRE, EM_SETMODIFY, (WPARAM) fFalse, 0);
	SendMessage(predoc->hwndRE, EM_SETREADONLY, (WPARAM) fFalse, 0);
	predoc->fReadOnly = fFalse;
	EnableWindow(predoc->hwndFormatBar, TRUE);

	SetCursor(hcur);

	return 0;

err:
	{
		TCHAR szT[64];

		wsprintf(szT, TEXT("Error saving document. [%ld]"), dwError);
		MessageBox(hwndMain, szT, NULL, MB_OK);
	}

	return -1;
}


LOCAL LRESULT SaveREDocAs(REDOC *predoc, BOOL fSelect)
{
	HCURSOR hcur;
	LONG cch;
	DWORD dwError;
	EDITSTREAM es;
	OPENFILENAME ofn;
	TCHAR szTitle[64];
	TCHAR szT[256];

	ofn.lStructSize			= sizeof(ofn);
	ofn.hInstance			= 0;
	ofn.lpstrFilter			= szFilterSave;
	ofn.lpstrCustomFilter	= NULL;
	ofn.nMaxCustFilter		= 0;
	ofn.nFilterIndex		= 0;
	ofn.lpstrFileTitle		= szTitle;
	ofn.nMaxFileTitle		= sizeof(szTitle);
	ofn.lpstrInitialDir		= NULL;
	ofn.lpstrTitle			= fSelect ? "Save Selection As": NULL;
	ofn.nFileOffset			= 0;
	ofn.nFileExtension		= 0;
 	ofn.lpstrDefExt			= NULL;
	ofn.lCustData			= 0L;
	ofn.lpfnHook			= NULL;
	ofn.lpTemplateName		= NULL;
	ofn.hwndOwner			= hwndMain;
	ofn.lpstrFile			= szT;
	ofn.nMaxFile			= sizeof(szT);
	ofn.Flags				= OFN_CREATEPROMPT | OFN_HIDEREADONLY |
								OFN_OVERWRITEPROMPT;

	szT[0] = TEXT('\0');
	szTitle[0] = TEXT('\0');
	// Query user for filename for input
    if(!GetSaveFileName(&ofn))
	{
		if((dwError = CommDlgExtendedError()) != 0)
			goto err;
		return -1;
	}

	hcur = SetCursor(LoadCursor(NULL, IDC_WAIT));

	es.dwCookie = _lcreat(szT, 0);
	if(es.dwCookie == (DWORD) HFILE_ERROR)
	{
		dwError = GetLastError();
		goto err;
	}
	es.dwError = 0;
	es.pfnCallback = MyWrite;
	cch = SendMessage(predoc->hwndRE, EM_STREAMOUT,
		(WPARAM) (fSelect ? ofn.nFilterIndex | SFF_SELECTION
						  : ofn.nFilterIndex),
		(LPARAM) &es);
	_lclose((HFILE) es.dwCookie);

	// Don't mark the doc as clean, nor remember format if only selection
	if(fSelect)
		goto Quit;

	SendMessage(predoc->hwndRE, EM_SETMODIFY, (WPARAM) fFalse, 0);

	predoc->dwFormat = (DWORD) ofn.nFilterIndex;
	predoc->fReadOnly = fFalse;
	EnableWindow(predoc->hwndFormatBar, TRUE);

	lstrcpy(predoc->szFile, szT);
	lstrcpy(predoc->szTitle, szTitle);

	wsprintf(szT, szFmtTitle, szTitle);
	SetWindowText(predoc->hwndParent, szT);

	SendMessage(predoc->hwndRE, EM_SETMODIFY, (WPARAM) fFalse, 0);
	SendMessage(predoc->hwndRE, EM_SETREADONLY, (WPARAM) fFalse, 0);

Quit:
	SetCursor(hcur);

	return 0;

err:
	wsprintf(szT, TEXT("Error saving document. [%ld]"), dwError);
	MessageBox(hwndMain, szT, NULL, MB_OK);

	return -1;
}


LOCAL LRESULT InsertObject(REDOC *predoc)
{
#ifdef NO_OLE
	MessageBox(NULL, "Not yet implemented", NULL, MB_OK);
	return 0;
#else	// NO_OLE
	const LPRICHEDITOLE preole = predoc->preole;
	LPOLECLIENTSITE polesite = NULL;
	LPSTORAGE pstgItem = NULL;
	OLEUIINSERTOBJECT ouio = { 0 };
	REOBJECT reobj = { 0 };
	LPOLEOBJECT poleobj = NULL;
	CHAR szFileA[OLEUI_CCHPATHMAX];
	WCHAR szItemW[OLEUI_CCHPATHMAX];
	DWORD dwRet;
	RECT rect;

	if(!preole)
		return 0;

	if(preole->lpVtbl->SetHostNames(preole, "REITP", predoc->szTitle))
	{
		MessageBoxA(hwndMain, "Can't set host name", NULL, MB_OK);
		goto error;
	}

	if(preole->lpVtbl->GetClientSite(preole, (LPOLECLIENTSITE FAR *) &polesite))
	{
		MessageBoxA(hwndMain, "No client site!", NULL, MB_OK);
		goto error;
	}

	wsprintfW(szItemW, L"REOBJ%ld", ++predoc->cItem);
	if(!(pstgItem = OleStdCreateChildStorage(predoc->pstg, szItemW)))
	{
		MessageBoxW(hwndMain, szItemW, L"No item storage!", MB_OK);
		goto error;
	}

	szFileA[0] = '\0';
	ouio.cbStruct = sizeof(ouio);
	ouio.dwFlags = IOF_SHOWHELP | IOF_CREATENEWOBJECT | IOF_CREATEFILEOBJECT |
				   IOF_CREATELINKOBJECT | IOF_SELECTCREATENEW;
//				   IOF_VERIFYSERVERSEXIST;
# ifdef MAC	// Mac version doesn't have the same members
	ouio.pszFile = szFileA;
# else	// MAC
	ouio.hWndOwner = hwndMain;
	ouio.lpszFile = szFileA;
# endif	// MAC, else
	ouio.lpszCaption = "Insert Object (REITP)";
	ouio.cchFile = OLEUI_CCHPATHMAX;
	ouio.iid = IID_IOleObject;
	ouio.oleRender = OLERENDER_DRAW;
	ouio.lpIOleClientSite = polesite;
	ouio.lpIStorage = pstgItem;
	ouio.ppvObj = (LPVOID FAR *) &poleobj;
	ouio.clsid = CLSID_NULL;

	if((dwRet = OleUIInsertObject(&ouio)) != OLEUI_SUCCESS)
	{
		if(dwRet == OLEUI_CANCEL)
			goto error;
		if(dwRet == OLEUI_IOERR_SCODEHASERROR)
			wsprintfA(szFileA, "OleUIInsertObject scode is %lx", ouio.sc);
		else
			wsprintfA(szFileA, "OleUIInsertObject returned %ld", dwRet);
		MessageBoxA(hwndMain, szFileA, NULL, MB_OK);
		goto error;
	}

	AssertSz(ouio.sc == S_OK, "Object wasn't created properly");

	reobj.cbStruct = sizeof(REOBJECT);
	reobj.clsid = ouio.clsid;
	reobj.cp = REO_CP_SELECTION;
	reobj.poleobj = poleobj;
	reobj.pstg = pstgItem;
	reobj.polesite = polesite;
	reobj.dvaspect = DVASPECT_CONTENT;
	reobj.dwFlags = REO_RESIZABLE;
	reobj.dwUser = 0;

	if(ouio.dwFlags & IOF_SELECTCREATENEW)
		reobj.dwFlags |= REO_BLANK;

	//$ Raid 101: RichEdit doesn't setup advises if reobj.clsid == CLSID_NULL
	// Try our darnest to get a CLSID

	if(IsEqualCLSID(&reobj.clsid, &CLSID_NULL) &&
		HrGetClassFileA(szFileA, &reobj.clsid))
	{
		MessageBoxA(hwndMain, "No CLSID, but forging on", "Insert Object",
					MB_OK);
	}


	// Do we want an iconized version ?
	if(ouio.dwFlags & IOF_CHECKDISPLAYASICON)
	{
	BOOL		fUpdate;				// Can't pass in NULL instead of &this

		// OLE call will update dvaspect on success
# ifdef MAC
		// NOTE : There presently is no Mac equivalent of the <.hMetaPict>
		// member of the tagOleUIInsertObject structure. This is certainly
		// a problem. For now just pass in NULL since the Mac routines will
		// not try to use this member.
		DebugStr("\pBefore OleStdSwitchDisplayAspect() call");
		if(OleStdSwitchDisplayAspect(poleobj, &reobj.dvaspect, 
									  DVASPECT_ICON, (Handle) NULL, 
									  TRUE, FALSE, NULL, &fUpdate))
# else	// MAC
		if(OleStdSwitchDisplayAspect(poleobj, &reobj.dvaspect, 
									  DVASPECT_ICON, ouio.hMetaPict, 
									  TRUE, FALSE, NULL, &fUpdate))
# endif	// MAC, else
		{
			// How much do we care about reporting errors?  Alot!! {Mac will have more}
			MessageBoxA(hwndMain, "Object couldn't be displayed as an icon.",
						"Insert Object", MB_OK);
		}
		AssertSz(!fUpdate, "We gave it an hMetaPict, should not need updating");
	}

	// Put the thing in the edit control
	if(preole->lpVtbl->InsertObject(preole, &reobj))
	{
		MessageBoxA(hwndMain, "Object couldn't be inserted",
					"Insert object", MB_OK);
		goto error;
	}

	// Do show verb only on new objects
	if(ouio.dwFlags & IOF_SELECTCREATENEW)
	{
		rect.top = rect.left = 0;
		rect.bottom = rect.right = 50;
		dwRet = (ULONG) poleobj->lpVtbl->DoVerb(poleobj, OLEIVERB_SHOW, NULL,
											polesite, 0, hwndMain, 
											(LPCRECT) &rect);
	}

error:
# ifndef MAC
	if(ouio.hMetaPict)
		OleUIMetafilePictIconFree(ouio.hMetaPict);
# endif	// !MAC
	if(polesite)
		polesite->lpVtbl->Release(polesite);
	if(pstgItem)
		pstgItem->lpVtbl->Release(pstgItem);
	if(poleobj)
		poleobj->lpVtbl->Release(poleobj);

	return 0;
#endif	// NO_OLE, else
}


#ifdef DEBUG

LOCAL LRESULT GetText(REDOC *predoc)
{
	HWND hwndEdit;
	LONG cch;
	TCHAR *pch;

	if(!hwndGT)
	{
		hwndGT = CreateDialog(HinstFromHwnd(hwndMain), TEXT("GETTEXT"),
					hwndMain, (DLGPROC) GTDlgProc);
		if(!hwndGT)
		{
			MessageBoxA(hwndMain, "Unable to create dialog", NULL, MB_ICONSTOP | MB_OK);
			return 0;
		}
	}
	hwndEdit = GetDlgItem(hwndGT, GTCTRL);
	cch = SendMessage(predoc->hwndRE, WM_GETTEXTLENGTH, 0, 0);
# ifdef WIN16
	if(cch > 65000)
	{
		MessageBoxA(hwndMain, "Text too big, truncating", NULL,
			MB_ICONSTOP | MB_OK);
		cch = 65000;
	}
# endif	// WIN16
	pch = GlobalAllocPtr(GHND, cch + 1);
	if(!pch)
	{
		MessageBoxA(hwndMain, "Not enough memory to hold text", NULL,
			MB_ICONSTOP | MB_OK);
		return 0;
	}
	GetWindowText(predoc->hwndRE, pch, (int) cch + 1);
	*pch = toupper(*pch);
	SetWindowText(hwndEdit, pch);
	GlobalFreePtr(pch);

	return 0;
}


LRESULT CALLBACK GTDlgProc(HWND hdlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch(msg)
	{
	case WM_INITDIALOG:
		return 1;

	case WM_SIZE:
		MoveWindow(GetDlgItem(hdlg, GTCTRL), 5, 5, LOWORD(lparam)-10,
				   HIWORD(lparam)-10, TRUE);
		return 0;

	case WM_CLOSE:
		EndDialog(hdlg, 0);
		hwndGT = NULL;
		return 1;
	}

	return 0;
}


LOCAL VOID ClearDebugScreen(void)
{
	HFILE hf;

	hf = _lopen("COM1", OF_WRITE);
	if(hf)
	{
		_lwrite(hf, "\x1B[H\x1B[J", 6);
		_lclose(hf);
	}
}

#endif	// DEBUG


LOCAL VOID SelectCharFormat(REDOC *predoc)
{
	LOGFONT lf;
	CHOOSEFONT csf = {0};
	CHARFORMAT cf;
	LONG yPerInch;
	HDC hdc;

	cf.cbSize = sizeof(CHARFORMAT);

	hdc = GetDC(hwndMain);
	yPerInch = GetDeviceCaps(hdc, LOGPIXELSY);
	ReleaseDC(hwndMain, hdc);

	(void) SendMessage(predoc->hwndRE, EM_GETCHARFORMAT, (WPARAM) fTrue,
			(LPARAM) &cf);

	csf.lStructSize = sizeof(csf);
	csf.hwndOwner = hwndMain;
	csf.hDC = 0;
	csf.lpLogFont = &lf;
	csf.Flags = CF_EFFECTS | CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT |
				CF_LIMITSIZE;
	csf.nSizeMin = 1;
	csf.nSizeMax = yHeightCharPtsMost;
	csf.rgbColors = cf.crTextColor;
	csf.lpszStyle = NULL;
	csf.nFontType = REGULAR_FONTTYPE | SCREEN_FONTTYPE;
	lf.lfHeight = -(INT) ((cf.yHeight * yPerInch) / 1440);
	lf.lfWidth = 0;
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = (cf.dwEffects & CFE_BOLD) ? FW_BOLD : FW_NORMAL;
	lf.lfItalic = (cf.dwEffects & CFE_ITALIC) ? fTrue : fFalse;
	lf.lfUnderline = (cf.dwEffects & CFE_UNDERLINE) ? fTrue : fFalse;
	lf.lfStrikeOut = (cf.dwEffects & CFE_STRIKEOUT) ? fTrue : fFalse;
	lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	lf.lfQuality = DRAFT_QUALITY;
	lf.lfCharSet = cf.bCharSet;
	lf.lfPitchAndFamily = cf.bPitchAndFamily;
	_tcscpy(lf.lfFaceName, cf.szFaceName);

	if(!ChooseFont(&csf))
		return;

	cf.cbSize = sizeof(CHARFORMAT);

	// don't change read-only bit
	cf.dwMask = CFM_SIZE | CFM_EFFECTS | CFM_COLOR | CFM_FACE | CFM_CHARSET;
	cf.yHeight = (LONG) csf.iPointSize * 2;
	cf.dwEffects = CFM_EFFECTS;
	if(lf.lfWeight < FW_BOLD)
		cf.dwEffects &= ~CFE_BOLD;
	if(!lf.lfItalic)
		cf.dwEffects &= ~CFE_ITALIC;
	if(!lf.lfUnderline)
		cf.dwEffects &= ~CFE_UNDERLINE;
	if(!lf.lfStrikeOut)
		cf.dwEffects &= ~CFE_STRIKEOUT;
	cf.crTextColor = csf.rgbColors;
	cf.bCharSet = lf.lfCharSet;
	cf.bPitchAndFamily = lf.lfPitchAndFamily;
	_tcscpy(cf.szFaceName, lf.lfFaceName);

	if(!SendMessage(predoc->hwndRE, EM_SETCHARFORMAT, predoc->scf,
		(LPARAM) &cf))
	{
		MessageBoxA(hwndMain, "Error setting character format", NULL,
			MB_ICONSTOP | MB_OK);
	}
}


LOCAL VOID SaveWindowPos(HWND hwnd)
{
	WINDOWPLACEMENT	wndpl;
	HKEY hkey;

    wndpl.length = sizeof(wndpl);
    GetWindowPlacement(hwnd, &wndpl);
    if(RegCreateKeyEx(HKEY_CURRENT_USER, szRegKey, 0, szAppName, 0,
		KEY_ALL_ACCESS, NULL, &hkey, NULL) == ERROR_SUCCESS)
    {
        RegSetValueEx(hkey, szRegValue, 0, REG_BINARY, (LPBYTE) &wndpl,
			sizeof(wndpl));
        RegCloseKey(hkey);
    }
}


LOCAL BOOL FRestoreWindowPos(WINDOWPLACEMENT *pwndpl)
{
	BOOL fReturn = fFalse;
	DWORD cb;
	HKEY hkey = 0;

    if(RegOpenKeyEx(HKEY_CURRENT_USER, szRegKey, 0, KEY_READ, &hkey)
		== ERROR_SUCCESS)
	{
		cb = sizeof(*pwndpl);
		if(RegQueryValueEx(hkey, szRegValue, 0, 0, (LPBYTE) pwndpl,
			&cb) == ERROR_SUCCESS)
		{
			fReturn = (cb == sizeof(*pwndpl));
		}
		RegCloseKey(hkey);
	}

	return fReturn;
}


LOCAL VOID SetAlignment(REDOC *predoc, WORD wAlignment)
{
	PARAFORMAT pf;

	pf.cbSize = sizeof(PARAFORMAT);

	SendMessage(predoc->hwndRE, EM_GETPARAFORMAT, 0, (LPARAM) &pf);

	if(!(pf.dwMask & PFM_ALIGNMENT) || pf.wAlignment != wAlignment)
	{
		pf.dwMask = PFM_ALIGNMENT;		// only change the alignment
		pf.wAlignment = wAlignment;
		SendMessage(predoc->hwndRE, EM_SETPARAFORMAT, 0, (LPARAM) &pf);
	}
}


LOCAL VOID IndentFirst(REDOC *predoc, BOOL fIndent)
{
	PARAFORMAT pf;

	pf.cbSize = sizeof(PARAFORMAT);

	SendMessage(predoc->hwndRE, EM_GETPARAFORMAT, 0, (LPARAM) &pf);

	pf.dwMask = PFM_OFFSET | PFM_OFFSETINDENT;
	if(fIndent)
	{
		if(pf.dxOffset < 0)
		{
			pf.dxStartIndent = pf.dxOffset;
			pf.dxOffset = 0;
		}
		else
		{
			pf.dxOffset = pf.dxOffset ? -pf.dxOffset : -lDefaultTab;
			pf.dxStartIndent = -pf.dxOffset;
		}
	}
	else
	{
		if(pf.dxOffset < 0)
		{
			pf.dxStartIndent = pf.dxOffset;
			pf.dxOffset = -pf.dxOffset;
		}
		else
		{
			pf.dxStartIndent = 0;
			pf.dxOffset = pf.dxOffset ? 0 : lDefaultTab;
		}
	}

	SendMessage(predoc->hwndRE, EM_SETPARAFORMAT, 0, (LPARAM) &pf);
}


LOCAL VOID ProtectSelection(REDOC *predoc)
{
	CHARFORMAT cf;

	cf.cbSize = sizeof(CHARFORMAT);

	(void) SendMessage(predoc->hwndRE, EM_GETCHARFORMAT, fTrue, (LPARAM) &cf);
	cf.dwMask = CFM_PROTECTED;
	cf.dwEffects = cf.dwEffects ^ CFE_PROTECTED;
	(void) SendMessage(predoc->hwndRE, EM_SETCHARFORMAT, predoc->scf,
						(LPARAM) &cf);
}


LOCAL VOID SetWordWrap(REDOC *predoc, BOOL fWysiwyg, BOOL fWrap)
{
	HCURSOR hcur;
	HDC hdcDel = predoc->hdcTarget;
	LONG xWidth;

	if(!fWysiwyg == !predoc->fWysiwyg && !fWrap == !predoc->fWrap)
		return;

	hcur = SetCursor(LoadCursor(NULL, IDC_WAIT));

	if(fWysiwyg)
	{
		POINT pt;
		LPDEVMODE pDevMode;
		LPDEVNAMES pDevNames;

		if(predoc->pd.lStructSize != sizeof(PRINTDLG))
			goto done;	// error occured getting default printer

		pDevMode = (LPDEVMODE) GlobalLock(predoc->pd.hDevMode);
		pDevNames = (LPDEVNAMES) GlobalLock(predoc->pd.hDevNames);
		predoc->hdcTarget = CreateIC((LPTSTR) pDevNames +
										pDevNames->wDriverOffset,
								(LPTSTR) pDevNames + pDevNames->wDeviceOffset,
								(LPTSTR) pDevNames + pDevNames->wOutputOffset,
								pDevMode);
		GlobalUnlock(predoc->pd.hDevNames);
		GlobalUnlock(predoc->pd.hDevMode);
		if(!predoc->hdcTarget)
			goto done;
		SetMapMode(predoc->hdcTarget, MM_TEXT);
		if(Escape(predoc->hdcTarget, GETPHYSPAGESIZE, 0, NULL, &pt) > 0)
		{
			const LONG xPerInch = GetDeviceCaps(predoc->hdcTarget, LOGPIXELSX);

			xWidth = (pt.x * 1440l) / xPerInch;
			// leave 1.25" (1800 twips) margins if that will leave >= 1"
			if(xWidth >= 1800 + 1440 + 1800)
				xWidth -= 1800 + 1800;
		}
		else
		{
			const LONG xPerInch = GetDeviceCaps(predoc->hdcTarget, LOGPIXELSX);

			xWidth = (GetDeviceCaps(predoc->hdcTarget, HORZRES) * 1440l) /
						xPerInch;
		}
	}
	else
	{
		predoc->hdcTarget = 0;
		xWidth = (LONG) !fWrap;
	}
	predoc->fWysiwyg = fWysiwyg;
	predoc->fWrap = fWrap;

	SetupWordWrapMenu(predoc);

	SendMessage(predoc->hwndRE, EM_SETTARGETDEVICE,
			(WPARAM) predoc->hdcTarget, (LPARAM) xWidth);
	if(hdcDel)
		DeleteDC(hdcDel);

done:
	SetCursor(hcur);
}


LOCAL VOID SetupWordWrapMenu(REDOC *predoc)
{
	HMENU hmenu = GetMenu(hwndMain);

	CheckMenuItem(hmenu, IDM_NOWRAP,
		(!predoc->fWysiwyg && !predoc->fWrap) ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hmenu, IDM_WRAP,
		(!predoc->fWysiwyg && predoc->fWrap) ? MF_CHECKED : MF_UNCHECKED);
	CheckMenuItem(hmenu, IDM_WYSIWYG,
		predoc->fWysiwyg ? MF_CHECKED :	MF_UNCHECKED);
}


LOCAL VOID SetOffset(REDOC *predoc, BOOL fSuperscript)
{
	CHARFORMAT cf;

	cf.cbSize = sizeof(CHARFORMAT);

	SendMessage(predoc->hwndRE, EM_GETCHARFORMAT, fTrue, (LPARAM) &cf);

	cf.dwMask = CFM_OFFSET;			// only change the yOffset
	if(fSuperscript)
	{
		if(cf.yOffset > 0)
			cf.yOffset = 0;
		else
			cf.yOffset = 50;
	}
	else
	{
		if(cf.yOffset < 0)
			cf.yOffset = 0;
		else
			cf.yOffset = -50;
	}

	SendMessage(predoc->hwndRE, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM) &cf);
}


VOID PrintREDoc(REDOC *predoc)
{
	LONG cchText;
	HCURSOR hcur;
	POINT pt;
	DOCINFO di;
	FORMATRANGE fr;
	RECT rc;

	cchText = SendMessage(predoc->hwndRE, WM_GETTEXTLENGTH, 0, 0);

	predoc->pd.nFromPage = 0;
	predoc->pd.nToPage = 0;
	predoc->pd.nMinPage = 0;
	predoc->pd.nMaxPage = 0;
	predoc->pd.nCopies = 1;
	predoc->pd.Flags = 
			PD_NOPAGENUMS | PD_NOSELECTION |
			PD_USEDEVMODECOPIES | PD_COLLATE | PD_RETURNDC;

	if(!PrintDlg(&predoc->pd))
		return;

	hcur = SetCursor(LoadCursor(NULL, IDC_WAIT));

	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = predoc->szTitle;
	di.lpszOutput = NULL;

	fr.hdc = predoc->pd.hDC;
	fr.hdcTarget = 0;

	if(Escape(fr.hdc, GETPHYSPAGESIZE, 0, NULL, &pt) > 0)
	{
		const LONG xPerInch = GetDeviceCaps(fr.hdc, LOGPIXELSX);
		const LONG yPerInch = GetDeviceCaps(fr.hdc, LOGPIXELSY);

		rc.left = rc.top = 0;
		fr.rcPage.left = fr.rcPage.top = 0;
		rc.right = (INT) ((pt.x * 1440l) / xPerInch);
		fr.rcPage.right = rc.right;
		// leave 1.25" (1800 twips) margins if that will leave >= 1"
		if(rc.right >= 1800 + 1440 + 1800)
			rc.right -= (rc.left = 1800);
		rc.bottom = (INT) ((pt.y * 1440l) / yPerInch);
		fr.rcPage.bottom = rc.bottom;
		// leave 1" (1440 twips) margins if that will leave >= 1"
		if(rc.bottom >= 1440 + 1440 + 1440)
			rc.bottom -= (rc.top = 1440);
	}
	else
	{
		const LONG xPerInch = GetDeviceCaps(fr.hdc, LOGPIXELSX);
		const LONG yPerInch = GetDeviceCaps(fr.hdc, LOGPIXELSY);

		rc.left = rc.top = 0;
		rc.right = (INT) ((GetDeviceCaps(fr.hdc, HORZRES) * 1440l) /
								xPerInch);
		rc.bottom = (INT) ((GetDeviceCaps(fr.hdc, VERTRES) * 1440l) /
								yPerInch);
		fr.rcPage = rc;
	}

	if(StartDoc(fr.hdc, &di) <= 0)
		goto err;

	// tell RichEdit not to erase before rendering text
	SetBkMode(fr.hdc, TRANSPARENT);

	fr.chrg.cpMin = 0;
	fr.chrg.cpMost = cchText;
	do
	{
		if(StartPage(fr.hdc) <= 0)
			goto abort;
		fr.rc = rc;
		fr.chrg.cpMin = SendMessage(predoc->hwndRE, EM_FORMATRANGE,
							(WPARAM) fTrue, (LPARAM) &fr);
		if(EndPage(fr.hdc) <= 0)
			goto abort;
	} while(fr.chrg.cpMin > 0 && fr.chrg.cpMin < fr.chrg.cpMost);

	if(fr.chrg.cpMin >= 0 && EndDoc(fr.hdc) > 0)
	{
		fr.chrg.cpMin = fr.chrg.cpMost = cchText;
		// free up RichEdit's format range info
		SendMessage(predoc->hwndRE, EM_FORMATRANGE, 0, 0);
		(void) SetCursor(hcur);
		return;
	}

abort:
	(void) AbortDoc(fr.hdc);

err:
	fr.chrg.cpMin = fr.chrg.cpMost = cchText;
	// free up RichEdit's format range info
	SendMessage(predoc->hwndRE, EM_FORMATRANGE, 0, 0);
	(void) SetCursor(hcur);
	MessageBoxA(hwndMain, "An error occurred while printing", NULL,
		MB_ICONSTOP | MB_OK);
}


LRESULT CALLBACK PPDlgProc(HWND hdlg, UINT msg, WPARAM wparam, LPARAM lparam)
{
	PRINTPREVIEW * ppp = (PRINTPREVIEW *) GetWindowLong(hdlg, DWL_USER);

	switch(msg)
	{
	case WM_INITDIALOG:
		// hide the button we use to tell us where the top left is
		ShowWindow(GetDlgItem(hdlg, PSB_TopLeft), SW_HIDE);

		ppp = (PRINTPREVIEW *) GlobalAllocPtr(GHND, sizeof(PRINTPREVIEW));
		SetWindowLong(hdlg, DWL_USER, (LONG) ppp);
		if(!ppp)
		{
			MessageBoxA(hwndMain,
				"Not enough memory for Print Preview window.",
				NULL, MB_ICONSTOP | MB_OK);
			EndDialog(hdlg, 0);
			return 0;
		}
		ppp->hwndDlg = hdlg;
		ppp->predoc = (REDOC *) lparam;
		AssertSz(ppp->predoc, "print preview: no redoc");
		ppp->cchText = -1;
		ppp->ipage = -1;
		PPChangePage(ppp, fFalse);
		if(ppp->ipage < 0)
		{
			ppp->fDone = fTrue;		// prevent any movement
			// bail
			PostMessage(hdlg, WM_CLOSE, 0, 0);
			return 0;
		}
		return 1;

	case WM_PAINT:
		PPPaint(ppp);
		break;

	case WM_SIZE:
		// cause complete redraw
		InvalidateRect(hdlg, NULL, fTrue);
		break;

#if defined(DEBUG) && defined(CLIPMETA)
	case WM_LBUTTONDBLCLK:
		if(ppp->hmf)
		{
			HMETAFILE hmf = 0;
			HANDLE hMfp = 0;
			METAFILEPICT *pmfp;

			if(!OpenClipboard(hwndMain))
				break;
			EmptyClipboard();
			hmf = CopyMetaFile(ppp->hmf, NULL);
			if(!hmf)
			{
				MessageBeep(0);
				break;
			}
			hMfp = GlobalAlloc(GHND | GMEM_DDESHARE, sizeof(METAFILEPICT));
			if(!hMfp)
				goto err;
			pmfp = (METAFILEPICT *) GlobalLock(hMfp);
			pmfp->mm = MM_ANISOTROPIC;
			pmfp->xExt = (INT) ppp->dxPage;
			pmfp->yExt = (INT) ppp->dyPage;
			pmfp->hMF = hmf;
			GlobalUnlock(hMfp);
			SetClipboardData(CF_METAFILEPICT, hMfp);
			CloseClipboard();
			TraceTag(tagNull, "clipped");
			break;
err:
			if(hmf)
				DeleteMetaFile(hmf);
			if(hMfp)
				GlobalFree(hMfp);
			CloseClipboard();
		}
		break;
#endif	// DEBUG && CLIPMETA

	case WM_COMMAND:
		switch(GET_WM_COMMAND_ID(wparam, lparam))
		{
		case PSB_NextPage:
			PPChangePage(ppp, fFalse);
			break;
		case PSB_PrevPage:
			PPChangePage(ppp, fTrue);
			break;
		case PSB_Close:
			PostMessage(hdlg, WM_CLOSE, 0, 0);
			break;
		}
		break;

	case WM_CLOSE:
		if(ppp)
		{
			// free up RichEdit's format range info
			SendMessage(ppp->predoc->hwndRE, EM_FORMATRANGE, 0, 0);
#ifdef DEBUG
			if(ppp->hmf)
				DeleteMetaFile(ppp->hmf);
#endif	// DEBUG
			if(ppp->fr.hdc)
			{
#ifndef NOBLIT
				SelectObject(ppp->fr.hdc, ppp->hbmpOld);
#endif	// !NOBLIT
				DeleteDC(ppp->fr.hdc);
			}
#ifndef NOBLIT
			if(ppp->hbmp)
				DeleteObject(ppp->hbmp);
#endif	// !NOBLIT
			if(ppp->fr.hdcTarget)
				DeleteDC(ppp->fr.hdcTarget);
			GlobalFreePtr(ppp);
		}
		SetWindowLong(hdlg, DWL_USER, 0);
		EndDialog(hdlg, 0);
		return 1;
	}

	return 0;
}


LOCAL BOOL FPPInit(PRINTPREVIEW *ppp)
{
	LPDEVMODE pDevMode;
	LPDEVNAMES pDevNames;
	POINT pt;

#ifndef NOBLIT
	ppp->hbmp = ppp->hbmpOld = 0;
#endif	// !NOBLIT
	ppp->fr.hdc = 0;
	ppp->cchText = SendMessage(ppp->predoc->hwndRE, WM_GETTEXTLENGTH, 0, 0);

	if(ppp->predoc->pd.lStructSize != sizeof(PRINTDLG))
	{
		MessageBoxA(hwndMain, "No printer selected.", NULL,
			MB_ICONSTOP | MB_OK);
		return fFalse;
	}

	ppp->cpage = 0;
	ppp->ipage = -1;	// first increment will display page 0
	ppp->cpageMost = cpageChunk;
	ppp->rgcpPages = (LONG *) GlobalAllocPtr(GHND, cpageChunk * sizeof(LONG));
	if(!ppp->rgcpPages)
		ppp->cpageMost = 0;

	pDevMode = (LPDEVMODE) GlobalLock(ppp->predoc->pd.hDevMode);
	pDevNames = (LPDEVNAMES) GlobalLock(ppp->predoc->pd.hDevNames);
	ppp->fr.hdcTarget = CreateIC((LPTSTR) pDevNames + pDevNames->wDriverOffset,
								(LPTSTR) pDevNames + pDevNames->wDeviceOffset,
								(LPTSTR) pDevNames + pDevNames->wOutputOffset,
								pDevMode);
	GlobalUnlock(ppp->predoc->pd.hDevNames);
	GlobalUnlock(ppp->predoc->pd.hDevMode);
	if(!ppp->fr.hdcTarget)
		goto err;

	// does this matter?
	SetMapMode(ppp->fr.hdcTarget, MM_TEXT);

	if(Escape(ppp->fr.hdcTarget, GETPHYSPAGESIZE, 0, NULL, &pt) > 0)
	{
		const LONG xPerInch = GetDeviceCaps(ppp->fr.hdcTarget, LOGPIXELSX);
		const LONG yPerInch = GetDeviceCaps(ppp->fr.hdcTarget, LOGPIXELSY);

		ppp->rc.left = ppp->rc.top = 0;
		ppp->dxPage = (pt.x * 1440l) / xPerInch;
		ppp->rc.right = (INT) ppp->dxPage;
		ppp->fr.rcPage.left = 0;
		ppp->fr.rcPage.right = ppp->rc.right;
		// leave 1.25" (1800 twips) margins if that will leave >= 1"
		if(ppp->rc.right >= 1800 + 1440 + 1800)
			ppp->rc.right -= (ppp->rc.left = 1800);
		ppp->dyPage = (pt.y * 1440l) / yPerInch;
		ppp->rc.bottom = (INT) ppp->dyPage;
		ppp->fr.rcPage.top = 0;
		ppp->fr.rcPage.bottom = ppp->rc.bottom;
		// leave 1" (1440 twips) margins if that will leave >= 1"
		if(ppp->rc.bottom >= 1440 + 1440 + 1440)
			ppp->rc.bottom -= (ppp->rc.top = 1440);
	}
	else
	{
		const LONG xPerInch = GetDeviceCaps(ppp->fr.hdcTarget, LOGPIXELSX);
		const LONG yPerInch = GetDeviceCaps(ppp->fr.hdcTarget, LOGPIXELSY);
		const LONG dxRes = GetDeviceCaps(ppp->fr.hdcTarget, HORZRES);
		const LONG dyRes = GetDeviceCaps(ppp->fr.hdcTarget, VERTRES);

		ppp->rc.left = ppp->rc.top = 0;
		ppp->dxPage = (dxRes * 1440l) / xPerInch;
		ppp->rc.right = (INT) ppp->dxPage;
		ppp->dyPage = (dyRes * 1440l) / yPerInch;
		ppp->rc.bottom = (INT) ppp->dyPage;
		ppp->fr.rcPage = ppp->rc;
	}

	PPInitDialogSize(ppp);

#ifdef DEBUG
	if(!QueryCheck(ppp->predoc, IDM_PPMETA))
#endif	// DEBUG
	{
		HDC hdcT;
#ifdef NOBLIT

		hdcT = GetDC(ppp->hwndDlg);
		ppp->fr.hdc = CreateCompatibleDC(hdcT);
		ReleaseDC(ppp->hwndDlg, hdcT);
		if(!ppp->fr.hdc)
			goto err;
#else	// NOBLIT
		LONG xPerInch;
		LONG yPerInch;

		hdcT = GetDC(ppp->hwndDlg);
		SaveDC(hdcT);
		SetMapMode(hdcT, MM_TEXT);
		xPerInch = GetDeviceCaps(hdcT, LOGPIXELSX);
		yPerInch = GetDeviceCaps(hdcT, LOGPIXELSY);
		ppp->dxBmp = (INT) ((ppp->dxPage * xPerInch) / 1440l);
		ppp->dyBmp = (INT) ((ppp->dyPage * yPerInch) / 1440l);
		ppp->fr.hdc = CreateCompatibleDC(hdcT);
		ppp->hbmp = CreateCompatibleBitmap(hdcT, ppp->dxBmp, ppp->dyBmp);
		RestoreDC(hdcT, -1);
		ReleaseDC(ppp->hwndDlg, hdcT);
		if(!ppp->fr.hdc)
		{
			if(ppp->hbmp)
				DeleteObject(ppp->hbmp);
			ppp->hbmp = 0;
			goto err;
		}
		if(!ppp->hbmp)
			goto err;
		ppp->hbmpOld = SelectObject(ppp->fr.hdc, ppp->hbmp);
#endif	// NOBLIT, else
		SetMapMode(ppp->fr.hdc, MM_TEXT);
	}

	ppp->fr.chrg.cpMin = 0;
	ppp->fr.chrg.cpMost = ppp->cchText;

	return fTrue;

err:
	if(ppp->fr.hdcTarget)
	{
		DeleteDC(ppp->fr.hdcTarget);
		ppp->fr.hdcTarget = 0;
	}
	if(ppp->fr.hdc)
	{
		DeleteDC(ppp->fr.hdc);
		ppp->fr.hdc = 0;
	}
#ifndef NOBLIT
	Assert(!ppp->hbmp);
	Assert(!ppp->hbmpOld);
#endif	// !NOBLIT

	MessageBoxA(hwndMain,
		"An error occurred while processing the print preview",
		NULL, MB_ICONSTOP | MB_OK);

	return fFalse;
}


LOCAL VOID PPInitDialogSize(PRINTPREVIEW *ppp)
{
	LONG dx;
	LONG dy;
	LONG numer;
	LONG denom;
	RECT rc;

	dx = GetSystemMetrics(SM_CXFULLSCREEN) - 2 * GetSystemMetrics(SM_CXBORDER);
	dy = GetSystemMetrics(SM_CYFULLSCREEN) - 2 * GetSystemMetrics(SM_CYBORDER);

	// select initial scale
	if(dy * ppp->dxPage > dx * ppp->dyPage)
	{
		numer = dx;
		denom = ppp->dxPage;
	}
	else
	{
		numer = dy;
		denom = ppp->dyPage;
	}
	rc.top = 0;
	rc.left = 0;
	rc.bottom = (INT) ((numer * ppp->dyPage) / denom);
	rc.right = (INT) ((numer * ppp->dxPage) / denom);

	rc.right += 2 * GetSystemMetrics(SM_CXFRAME);
	rc.bottom += GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYFRAME);

	MoveWindow(ppp->hwndDlg, rc.left, rc.top, rc.right, rc.bottom, fTrue);
	ShowWindow(ppp->hwndDlg, SW_SHOW);
}


LOCAL VOID PPChangePage(PRINTPREVIEW *ppp, BOOL fPrev)
{
	HCURSOR hcur;
	TCHAR szCaption[40];

	if(ppp->cchText < 0 && !FPPInit(ppp))
		return;

	if(fPrev)
	{
		// no page before page zero or no page array so we can't go back
		if(ppp->ipage <= 0 || !ppp->rgcpPages)
		{
			MessageBeep(0);
			return;
		}
		Assert(ppp->ipage - 1 < ppp->cpage);
		// backup a page
		ppp->fr.chrg.cpMin = ppp->rgcpPages[ppp->ipage - 1];
	}
	else if(ppp->ipage + 1 >= ppp->cpage)
	{
		if(ppp->fDone)
		{
			MessageBeep(0);
			return;
		}
		if(!ppp->rgcpPages)
			goto doit;
		if(ppp->ipage + 1 >= ppp->cpageMost)
		{
			LONG *pcp;

			pcp = (LONG *) GlobalReAllocPtr(ppp->rgcpPages,
					(ppp->cpageMost + cpageChunk) * sizeof(LONG), GHND);
			if(!pcp)
			{
				GlobalFreePtr(ppp->rgcpPages);
				ppp->rgcpPages = NULL;
				ppp->cpage = ppp->cpageMost = 0;
				goto doit;
			}
			ppp->rgcpPages = pcp;
			ppp->cpageMost += cpageChunk;
		}
		ppp->cpage++;
		ppp->rgcpPages[ppp->ipage + 1] = ppp->fr.chrg.cpMin;
	}

doit:
	hcur = SetCursor(LoadCursor(NULL, IDC_WAIT));

#ifndef NOBLIT
	if(ppp->fr.hdc)
	{
		RECT rc;

		rc.top = rc.left = 0;
		rc.bottom = ppp->dyBmp;
		rc.right = ppp->dxBmp;
		// erase the background
		SetBkColor(ppp->fr.hdc, GetSysColor(COLOR_WINDOW));
		ExtTextOut(ppp->fr.hdc, 0, 0, ETO_OPAQUE, &rc, "", 0, NULL);
		// tell RichEdit not to bother erasing the background
		SetBkMode(ppp->fr.hdc, TRANSPARENT);
	}
#endif	// !NOBLIT

#ifdef DEBUG
	if(ppp->hmf)
	{
		// delete any metafile left around from the last page
		DeleteMetaFile(ppp->hmf);
		ppp->hmf = NULL;
	}
	if(QueryCheck(ppp->predoc, IDM_PPMETA))
	{
		AssertSz(!ppp->fr.hdc, "How'd that get there?");
		ppp->fr.hdc = CreateMetaFile(NULL);
		if(!ppp->fr.hdc)
			goto err;
		TraceTag(tagEnumMF, "Window Ext = %d, %d", ppp->dxPage, ppp->dyPage);
	}
#endif	// DEBUG

	ppp->fr.rc = ppp->rc;
	ppp->fr.chrg.cpMin = SendMessage(ppp->predoc->hwndRE, EM_FORMATRANGE,
							(WPARAM) fTrue, (LPARAM) &ppp->fr);

	if(!fPrev && ppp->fr.chrg.cpMin >= ppp->fr.chrg.cpMost)
	{
		// free up RichEdit's format range info
		ppp->fr.chrg.cpMin = ppp->fr.chrg.cpMost = ppp->cchText;
		SendMessage(ppp->predoc->hwndRE, EM_FORMATRANGE, 0, 0);
		// setup for a prev
		ppp->fr.chrg.cpMost = ppp->cchText;
		// done with all pages, ppp->cpage is the max # of pages
		ppp->fDone = fTrue;
	}

#ifdef DEBUG
	if(QueryCheck(ppp->predoc, IDM_PPMETA))
	{
		//$ REVIEW: what happens to ppp->fr.hdc if this fails?
		ppp->hmf = CloseMetaFile(ppp->fr.hdc);
		ppp->fr.hdc = 0;
		if(!ppp->hmf)
			goto err;
	}
#endif	// DEBUG

	// update the current page number
	ppp->ipage += fPrev ? -1 : 1;

	EnableWindow(GetDlgItem(ppp->hwndDlg, PSB_PrevPage), ppp->ipage > 0);
	EnableWindow(GetDlgItem(ppp->hwndDlg, PSB_NextPage),
		!ppp->fDone || ppp->ipage + 1 < ppp->cpage);

	wsprintf(szCaption, szFmtPrintPreview, ppp->ipage + 1);
	SetWindowText(ppp->hwndDlg, szCaption);

	// cause redraw
	InvalidateRect(ppp->hwndDlg, NULL, fTrue);

	(void) SetCursor(hcur);

	return;

#ifdef DEBUG
err:
	ppp->fDone = fTrue;

	// free up RichEdit's format range info
	ppp->fr.chrg.cpMin = ppp->fr.chrg.cpMost = ppp->cchText;
	SendMessage(ppp->predoc->hwndRE, EM_FORMATRANGE, 0, 0);
	// setup for a prev
	ppp->fr.chrg.cpMost = ppp->cchText;
	(void) SetCursor(hcur);
	MessageBoxA(hwndMain,
		"An error occurred while processing the print preview",
		NULL, MB_ICONSTOP | MB_OK);
#endif	// DEBUG
}


LOCAL VOID PPPaint(PRINTPREVIEW *ppp)
{
	HDC hdc;
	RECT rc;
	RECT rcClient;
	PAINTSTRUCT ps;

	// if we're iconic, don't bother
	if(IsIconic(ppp->hwndDlg))
		return;

	hdc = BeginPaint(ppp->hwndDlg, &ps);
	SaveDC(hdc);
	GetClientRect(ppp->hwndDlg, &rcClient);
	GetWindowRect(GetDlgItem(ppp->hwndDlg, PSB_TopLeft), &rc);
	MapWindowPoints(GetDesktopWindow(), ppp->hwndDlg, (LPPOINT) &rc, 2);
	rc.bottom = rc.top + GetSystemMetrics(SM_CYBORDER);
	rc.right = rcClient.right;
	SetBkColor(hdc, GetSysColor(COLOR_WINDOWFRAME));
	ExtTextOut(hdc, rc.left, rc.top, ETO_OPAQUE, &rc, "", 0, NULL);
	rc.top = rc.bottom;
	rc.bottom = rcClient.bottom;
#ifdef DEBUG
	if(ppp->hmf)
	{
		// erase the background
		SetBkColor(hdc, GetSysColor(COLOR_WINDOW));
		ExtTextOut(hdc, rc.left, rc.top, ETO_OPAQUE, &rc, "", 0, NULL);
		// make the window the same logical size as the page
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetViewportOrgEx(hdc, rc.left, rc.top, NULL);
		TraceTag(tagEnumMF, "Viewport Org = %d, %d", rc.left, rc.top);
		SetViewportExtEx(hdc, rc.right - rc.left, rc.bottom - rc.top, NULL);
		TraceTag(tagEnumMF, "Viewport Ext = %d, %d", rc.right - rc.left, rc.bottom - rc.top);
		if(FFromTag(tagEnumMF))
			EnumMetaFile(hdc, ppp->hmf, MFEnumCallback, 0);
		PlayMetaFile(hdc, ppp->hmf);
	}
	else
#endif	// DEBUG
	if(ppp->ipage >= 0)
	{
#ifdef NOBLIT
		HDC hdcSave = ppp->fr.hdc;
		LONG xPerInch = GetDeviceCaps(hdc, LOGPIXELSX);
		LONG yPerInch = GetDeviceCaps(hdc, LOGPIXELSY);

		// make the window the same logical size as the page
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, (ppp->dxPage * xPerInch) / 1440,
			(ppp->dyPage * yPerInch) / 1440, NULL);
		SetViewportExtEx(hdc, rc.right - rc.left, rc.bottom - rc.top, NULL);

		// erase the background
		SetBkColor(hdc, GetSysColor(COLOR_WINDOW));
		ExtTextOut(hdc, rc.left, rc.top, ETO_OPAQUE, &rc, "", 0, NULL);

		// tell RichEdit not to bother erasing the background
		SetBkMode(hdc, TRANSPARENT);

		ppp->fr.hdc = hdc;
		ppp->fr.rc = ppp->rc;
		ppp->fr.chrg.cpMin = ppp->rgcpPages[ppp->ipage];
		ppp->fr.chrg.cpMin = SendMessage(ppp->predoc->hwndRE, EM_FORMATRANGE,
								(WPARAM) fTrue, (LPARAM) &ppp->fr);
		ppp->fr.hdc = hdcSave;
#else	// NOBLIT
		// convert RECT to x,y,dx,dy
		rc.right -= rc.left;
		rc.bottom -= rc.top;

		StretchBlt(hdc, rc.left, rc.top, rc.right, rc.bottom,
			ppp->fr.hdc, 0, 0, ppp->dxBmp, ppp->dyBmp, SRCCOPY);
#endif	// NOBLIT, else
	}
	RestoreDC(hdc, -1);
	EndPaint(ppp->hwndDlg, &ps);
}

#ifdef DEBUG

int CALLBACK MFEnumCallback(HDC hdc, HANDLETABLE *lpHTable, METARECORD *pmfr,
				int nObj, LPARAM lparam)
{
	switch(pmfr->rdFunction)
	{
	case META_SETWINDOWORG:
		TraceTag(tagEnumMF, "SetWindowOrg(): %d, %d", (INT) (SHORT) pmfr->rdParm[1], (INT) (SHORT) pmfr->rdParm[0]);
		break;

	case META_SETVIEWPORTORG:
		TraceTag(tagEnumMF, "SetViewportOrg(): %d, %d", (INT) (SHORT) pmfr->rdParm[1], (INT) (SHORT) pmfr->rdParm[0]);
		break;

	case META_OFFSETWINDOWORG:
		TraceTag(tagEnumMF, "OffsetWindowOrg(): %d, %d", (INT) (SHORT) pmfr->rdParm[1], (INT) (SHORT) pmfr->rdParm[0]);
		break;

	case META_OFFSETVIEWPORTORG:
		TraceTag(tagEnumMF, "OffsetViewportOrg(): %d, %d", (INT) (SHORT) pmfr->rdParm[1], (INT) (SHORT) pmfr->rdParm[0]);
		break;

	case META_SETWINDOWEXT:
		TraceTag(tagEnumMF, "SetWindowExt(): %d, %d", (INT) (SHORT) pmfr->rdParm[1], (INT) (SHORT) pmfr->rdParm[0]);
		break;

	case META_SETVIEWPORTEXT:
		TraceTag(tagEnumMF, "SetViewportExt(): %d, %d", (INT) (SHORT) pmfr->rdParm[1], (INT) (SHORT) pmfr->rdParm[0]);
		break;

	case META_SCALEWINDOWEXT:
		TraceTag(tagEnumMF, "ScaleWindowExt(): %d, %d, %d, %d", (INT) (SHORT) pmfr->rdParm[3], (INT) (SHORT) pmfr->rdParm[2], (INT) (SHORT) pmfr->rdParm[1], (INT) (SHORT) pmfr->rdParm[0]);
		break;

	case META_SCALEVIEWPORTEXT:
		TraceTag(tagEnumMF, "ScaleViewportExt(): %d, %d, %d, %d", (INT) (SHORT) pmfr->rdParm[3], (INT) (SHORT) pmfr->rdParm[2], (INT) (SHORT) pmfr->rdParm[1], (INT) (SHORT) pmfr->rdParm[0]);
		break;

	case META_SAVEDC:
		TraceTag(tagEnumMF, "SaveDC()");
		break;

	case META_RESTOREDC:
		TraceTag(tagEnumMF, "RestoreDC()");
		break;

	case META_SELECTPALETTE:
		TraceTag(tagEnumMF, "Select Palette");
		break;

	case META_SETMAPMODE:
		TraceTag(tagEnumMF, "SetMapMode(): %d", (INT) (SHORT) pmfr->rdParm[0]);
		break;

	case META_EXTTEXTOUT:
		TraceTag(tagEnumMF, "ExtTextOut(): %d, %d", (INT) (SHORT) pmfr->rdParm[1], (INT) (SHORT) pmfr->rdParm[0]);
		break;

	case META_TEXTOUT:
		TraceTag(tagEnumMF, "TextOut(): %d, %d", (INT) (SHORT) pmfr->rdParm[3], (INT) (SHORT) pmfr->rdParm[2]);
		break;

	case META_LINETO:
		TraceTag(tagEnumMF, "LineTo(): %d, %d", (INT) (SHORT) pmfr->rdParm[1], (INT) (SHORT) pmfr->rdParm[0]);
		break;

	case META_RECTANGLE:
		TraceTag(tagEnumMF, "Rectangle(): %d, %d, %d, %d", (INT) (SHORT) pmfr->rdParm[3], (INT) (SHORT) pmfr->rdParm[2], (INT) (SHORT) pmfr->rdParm[1], (INT) (SHORT) pmfr->rdParm[0]);
		break;
	}

	return fTrue;
}

#endif	// DEBUG


/*
 *	I T P C A L L   I m p l e m e n t a t i o n
 */


/* 
 *	ITPCALL_New
 *
 *	Purpose:
 *		Creates a new ITPCALL.
 *
 *	Arguments:
 *		REDOC *		Pointer to the document information.
 *
 *	Returns:
 *		ITPCALL *	The newly created ITPCALL.
 */
ITPCALL * ITPCALL_New(REDOC * predoc)
{
#ifndef NO_OLE
	ITPCALL * pitpcall;

	if(!(pitpcall = (ITPCALL *) GlobalAllocPtr(GHND, sizeof(ITPCALL))))
		goto Error;
	pitpcall->lpVtbl = &ITPCALL_Vtbl;
	pitpcall->cRef = 1;					// Start with one reference
	pitpcall->predoc = predoc;
	if(!(pitpcall->pipframe = ITPOLEINPLACEFRAME_New(predoc)))
		GlobalFreePtr(pitpcall);
	else
		return pitpcall;
Error:
#endif	// !NO_OLE

	return NULL;
}


/*
 *	ITPCALL_QueryInterface
 *
 *	Purpose:
 *		Returns a pointer to the specified site.
 *
 *	Arguments:
 *		LPUNKNOWN *		Object from which we want an interface.
 *		REFIID			Interface we want.
 *		LPUNKNOWN *		Interface we return.
 *
 *	Returns:
 *		HRESULT		 Error status.
 */
STDMETHODIMP ITPCALL_QueryInterface(LPUNKNOWN punk, REFIID riid, 
								   LPUNKNOWN * ppvObj)
{
	SCODE sc = S_OK;

	if(IsEqualIID(riid, &IID_IUnknown))
		ITPCALL_AddRef(*ppvObj = punk);
	else if(IsEqualIID(riid, &IID_IRichEditOleCallback))
		ITPCALL_AddRef(*ppvObj = punk);
	else
		sc = E_NOINTERFACE, *ppvObj = NULL;

	return sc;
}


/*
 *	ITPCALL_AddRef
 *
 *	Purpose:
 *		Increments reference count on the specified site.
 *
 *	Arguments:
 *		LPUNKNOWN *		Object whose count we want to increment.
 *
 *	Returns:
 *		ULONG			New value of reference count.
 */
STDMETHODIMP_(ULONG) ITPCALL_AddRef(LPUNKNOWN punk)
{
	return ++PitpcallFromPunk(punk)->cRef;
}


/*
 *	ITPCALL_Release
 *
 *	Purpose:
 *		Decrements reference count on the specified site.  If count is
 *		decremented to zero, the object is freed.
 *
 *	Arguments:
 *		LPUNKNOWN *		Object whose count we want to decrement.
 *
 *	Returns:
 *		ULONG			New value of reference count.
 */
STDMETHODIMP_(ULONG) ITPCALL_Release(LPUNKNOWN punk)
{
#ifndef NO_OLE
	ITPCALL * pitpcall = PitpcallFromPunk(punk);
	ULONG cRef = --pitpcall->cRef;

	if(!cRef)
	{
		// Free stuff we own
		if(pitpcall->pipframe)
		{
			pitpcall->pipframe->lpVtbl->Release((LPOLEINPLACEFRAME) 
												 pitpcall->pipframe);
		}

		// Free memory allocated for us
		GlobalFreePtr(pitpcall);
		TraceTag(tagITPCALL, "ITPCALL_Release: freeing the itpcall");
	}

	AssertSz(cRef >= 0, "ITPCALL_Release: negative cRef");
	return cRef;
#endif	// !NO_OLE

	return (ULONG) NULL;
}


/*
 *	ITPCALL_GetNewStorage
 *
 *	Purpose:
 *		Gets storage for a new object.
 *
 *	Arguments:
 *		ITPCALL *			Callback object.
 *		LPSTORAGE FAR *		Where to return storage.
 *
 *	Returns:
 *		HRESULT				Error status.
 */
STDMETHODIMP ITPCALL_GetNewStorage(ITPCALL * pitpcall, LPSTORAGE FAR * ppstg)
{
	SCODE sc = S_OK;
	WCHAR szItemW[OLEUI_CCHPATHMAX];

	wsprintfW(szItemW, L"REOBJ%ld", ++pitpcall->predoc->cItem);
	if(!(*ppstg = OleStdCreateChildStorage(pitpcall->predoc->pstg, szItemW)))
	{
		MessageBoxW(hwndMain, szItemW, L"No item storage!", MB_OK);
		sc = E_FAIL;
	}

	return sc;
}


/*
 *	ITPCALL_GetInPlaceContext
 *
 *	Purpose:
 *		Gets context information for an in place object.
 *
 *	Arguments:
 *		ITPCALL *				Callback object.
 *		LPOLEINPLACEFRAME *		Frame window object.
 *		LPOLEINPLACEUIWINDOW *	Document window object.
 *		LPOLEINPLACEFRAMEINFO	Frame window information.
 *
 *	Returns:
 *		HRESULT					Error status.
 */
STDMETHODIMP ITPCALL_GetInPlaceContext(ITPCALL * pitpcall, 
									   LPOLEINPLACEFRAME FAR * ppipframe,
									   LPOLEINPLACEUIWINDOW FAR* ppipuiDoc,
									   LPOLEINPLACEFRAMEINFO pipfinfo)
{
#ifndef NO_OLE
	// Return window pointers
	*ppipframe = (LPOLEINPLACEFRAME) pitpcall->pipframe;
	(VOID) (*ppipframe)->lpVtbl->AddRef(*ppipframe);
	*ppipuiDoc = NULL;

	// Fill in frame window information
	pipfinfo->cb = sizeof(OLEINPLACEFRAMEINFO);
	pipfinfo->fMDIApp = FALSE;
	pipfinfo->hwndFrame = pitpcall->predoc->hwndParent;
	pipfinfo->haccel = (long) NULL;
	pipfinfo->cAccelEntries = 0;
#endif	// !NO_OLE

	return S_OK;
}


/*
 *	ITPCALL_ShowContainerUI
 *
 *	Purpose:
 *		Displays or hides REITP's container UI.
 *
 *	Arguments:
 *		ITPCALL *		Callback object.
 *		BOOL			
 *
 *	Returns:
 *		HRESULT			Error status.
 */
STDMETHODIMP ITPCALL_ShowContainerUI(ITPCALL * pitpcall, BOOL fShow)
{
	TraceTag(tagITPCALL, "ITPCALL_ShowContainerUI(%d)", fShow);

	// If we're displaying our UI, show our menus
	if(fShow)
		ITPOLEINPLACEFRAME_SetMenu(pitpcall->pipframe, NULL, NULL, NULL);

	return S_OK;
}


STDMETHODIMP ITPCALL_QueryInsertObject(ITPCALL * pitpcall, LPCLSID pclsid,
				LPSTORAGE pstg, LONG cp)
{
#if !defined(NO_OLE) && defined(DEBUG)
	LPTSTR szProgID;

	if(HrProgIDFromCLSIDA(pclsid, &szProgID))
	{
		TraceTag(tagITPCALL, "QueryInsertObject(): unknown class id");
	}
	else
	{
		SCODE sc = S_OK;

		TraceTag(tagITPCALL, "QueryInsertObject(): %s object", szProgID);
		if(QueryCheck(pitpcall->predoc, IDM_REFUSEGRAPH) &&
			!lstrcmpi(szProgID, "MSGraph"))
		{
			TraceTag(tagITPCALL, "Refusing object");
			sc = S_FALSE;
		}
		OleStdFreeString((LPSTR) szProgID, NULL);
		return sc;
	}
#endif	// !NO_OLE && DEBUG

	return NOERROR;
}


STDMETHODIMP ITPCALL_DeleteObject(ITPCALL * pitpcall, LPOLEOBJECT poleobj)
{
	TraceTag(tagITPCALL, "DeleteObject()");
	return NOERROR;
}


STDMETHODIMP ITPCALL_QueryAcceptData(ITPCALL * pitpcall, LPDATAOBJECT pdataobj,
				CLIPFORMAT *pcfFormat, DWORD reco, BOOL fReally,
				HGLOBAL hMetaPict)
{
#if !defined(NO_OLE) && defined(DEBUG)
	TraceTag(tagITPCALL, "QueryAcceptData(%s) for %s", fReally ? "really" : "test", (reco == RECO_DROP ? "drop" : (reco == RECO_PASTE ? "paste" : "unknown op")));
	if(pitpcall->predoc->fReadOnly)
	{
		BOOL fDoIt = fFalse;
		HRESULT hr;

		switch(reco)
		{
		case RECO_DROP:
			fDoIt = QueryCheck(pitpcall->predoc, IDM_ENABLEDRAGREADONLY);
			break;

		case RECO_PASTE:
			fDoIt = QueryCheck(pitpcall->predoc, IDM_ENABLEPASTEREADONLY);
			break;

		default:
			TraceTag(tagNull, "QAD: invalid RECO %lx", reco);
			AssertSz(fFalse, "QAD: invalid RECO");
			break;
		}
		if(fDoIt)
		{
			if(fReally)
			{
				LPRICHEDITOLE const preole = pitpcall->predoc->preole;

				// import that sucker

				hr = preole->lpVtbl->ImportDataObject(preole, pdataobj,
														*pcfFormat, hMetaPict);
				TraceError("IRichEditOle::ImportDataObject", hr);
				if(SUCCEEDED(hr))
					hr = S_FALSE;	// we did it ourselves
			}
			else
			{
				// return that we'll import it ourselves
				hr = S_FALSE;
			}
		}
		else
		{
			hr = E_FAIL;
		}
		TraceError("IPCALL_QueryAcceptData", hr);
		return hr;
	}
	if(QueryCheck(pitpcall->predoc, IDM_TEXTONLY))
	{
		TraceTag(tagITPCALL, "QueryAcceptData(): asking for text only");
		*pcfFormat = CF_TEXT;		// accept only text
	}
	else
	{
		TraceTag(tagITPCALL, "QueryAcceptData(): delegating back to RichEdit");
	}
#endif	// !NO_OLE && DEBUG

	return NOERROR;
}


STDMETHODIMP ITPCALL_ContextSensitiveHelp(ITPCALL * pitpcall, BOOL fEnterMode)
{
	return NOERROR;
}


STDMETHODIMP ITPCALL_GetClipboardData(ITPCALL *pitpcall, CHARRANGE *pchrg,
					DWORD reco, LPDATAOBJECT *ppdataobj)
{
#if !defined(NO_OLE) && defined(DEBUG)
	TraceTag(tagITPCALL, "GetClipboardData(%d-%d) for %s", pchrg->cpMin, pchrg->cpMost, reco == RECO_COPY ? "copy" : (reco == RECO_CUT ? "cut" : (reco == RECO_DRAG ? "drag" : "unknown op")));

	if(pitpcall->predoc->fReadOnly)
	{
		BOOL fDoIt = fFalse;

		switch(reco)
		{
		case RECO_COPY:
			// prevent assert in default case
			break;

		case RECO_CUT:
			fDoIt = QueryCheck(pitpcall->predoc, IDM_ENABLECUTREADONLY);
			break;

		case RECO_DRAG:
			fDoIt = QueryCheck(pitpcall->predoc, IDM_ENABLEDRAGREADONLY);
			break;

		default:
			TraceTag(tagNull, "GCD: invalid RECO %lx", reco);
			AssertSz(fFalse, "GCD: invalid RECO");
			break;
		}
		if(fDoIt)
		{
			LPRICHEDITOLE const preole = pitpcall->predoc->preole;
			HRESULT hr;

			// delegate to IRichEditOle::GetClipboardData()

			*ppdataobj = NULL;
			hr = preole->lpVtbl->GetClipboardData(preole, pchrg, reco,
													ppdataobj);
			TraceError("IRichEditOle::GetClipboardData", hr);
			if(SUCCEEDED(hr) && *ppdataobj)
				hr = S_FALSE;	// we did it ourselves
			TraceError("IPCALL_GetClipboardData", hr);
			return hr;
		}
		// go return E_NOTIMPL & let RichEdit deal with it itself
	}
#endif	// !NO_OLE && DEBUG

	// *ppdataobj isn't used if E_NOTIMPL is returned
	// so we don't need to set it

	// tell RichEdit to do it itself
	TraceTag(tagITPCALL, "GetClipboardData(): delegating back to RichEdit");
	return E_NOTIMPL;
}


STDMETHODIMP ITPCALL_GetDragDropEffect(ITPCALL *pitpcall, BOOL fDrag,
				DWORD grfKeyState, LPDWORD pdwEffect)
{
	TraceTag(tagITPCALL, "GetDragDropEffect(%s)", fDrag ? "drag" : "drop");

#ifdef DEBUG
	if(QueryCheck(pitpcall->predoc, IDM_SWAPDRAGEFFECT))
	{
		DWORD dwT;

		// strip off move, copy, and link
		dwT = *pdwEffect &
				~(DWORD) (DROPEFFECT_MOVE | DROPEFFECT_COPY | DROPEFFECT_LINK);

		if(!pitpcall->predoc->fReadOnly ||
			QueryCheck(pitpcall->predoc, IDM_ENABLEDRAGREADONLY))
		{
			if(fDrag)
				dwT = DROPEFFECT_MOVE | DROPEFFECT_COPY;
			else if(grfKeyState & MK_CONTROL)
				dwT = DROPEFFECT_MOVE;
			else
				dwT = DROPEFFECT_COPY;
		}

		*pdwEffect = dwT;

		return NOERROR;
	}
#endif	// DEBUG

	// delegate back to RichEdit
	return E_NOTIMPL;
}


STDMETHODIMP ITPCALL_GetContextMenu(ITPCALL *pitpcall, WORD seltype,
				LPOLEOBJECT poleobj, CHARRANGE * pchrg, HMENU * phmenu)
{
	HMENU hmenu;
	HMENU hmenuParent = NULL;
	HMENU hmenuVerbs = NULL;
	UINT uiT;

	TraceTag(tagITPCALL, "GetContextMenu");

	hmenuParent = CreatePopupMenu();
	if(!hmenuParent)
		goto Cleanup;

	// Put the verbs on the menu
	if(poleobj)
	{
		OleUIAddVerbMenu(poleobj, NULL, hmenuParent, 0, IDM_OBJECTMIN, 
						0, TRUE, IDM_OBJECTCONVERT, &hmenuVerbs);
	}

	// Determine which menu to pass back to RichEdit
	*phmenu = hmenu = hmenuVerbs ? hmenuVerbs : hmenuParent;

	if(poleobj)
		AppendMenu(hmenu, MF_SEPARATOR, 0, NULL);

	// Add the cut, copy, paste verbs
	
	uiT = MF_STRING | MF_BYCOMMAND;
	uiT |= pchrg->cpMin == pchrg->cpMost ? uiMFDisabled : uiMFEnabled;
	AppendMenu(hmenu, uiT, IDM_CUT, "Cut");
	AppendMenu(hmenu, uiT, IDM_COPY, "Copy");


	uiT = MF_STRING | MF_BYCOMMAND;
	uiT |= SendMessage(pitpcall->predoc->hwndRE, EM_CANPASTE, 0, 0)
				? uiMFEnabled : uiMFDisabled;
	AppendMenu(hmenu, uiT, IDM_PASTE, "Paste");

Cleanup:
	if(hmenu == hmenuVerbs && hmenuParent)
		DestroyMenu(hmenuParent);
	else if(hmenu == hmenuParent && hmenuVerbs)
		DestroyMenu(hmenuVerbs);
	
	return S_OK;
}


/*
 *	I T P O L E I N P L A C E F R A M E  I m p l e m e n t a t i o n
 */


/* 
 *	ITPOLEINPLACEFRAME_New
 *
 *	Purpose:
 *		Creates a new ITPOLEINPLACEFRAME.
 *
 *	Arguments:
 *		REDOC *					Pointer to the document information.
 *
 *	Returns:
 *		ITPOLEINPLACEFRAME *	The newly created ITPOLEINPLACEFRAME.
 */
ITPOLEINPLACEFRAME * ITPOLEINPLACEFRAME_New(REDOC * predoc)
{
#ifndef NO_OLE
	ITPOLEINPLACEFRAME * pipframe;

	if(!(pipframe = (ITPOLEINPLACEFRAME *) GlobalAllocPtr(GHND, sizeof(ITPOLEINPLACEFRAME))))
		return NULL;
	pipframe->lpVtbl = &ITPOLEINPLACEFRAME_Vtbl;
	pipframe->cRef = 1;					// Start with one reference
	pipframe->predoc = predoc;
	return pipframe;
#endif	// !NO_OLE

	return NULL;
}


/*
 *	ITPOLEINPLACEFRAME_QueryInterface
 *
 *	Purpose:
 *		Returns a pointer to the specified site.
 *
 *	Arguments:
 *		LPUNKNOWN *		Object from which we want an interface.
 *		REFIID			Interface we want.
 *		LPUNKNOWN *		Interface we return.
 *
 *	Returns:
 *		HRESULT			Error status.
 */
STDMETHODIMP ITPOLEINPLACEFRAME_QueryInterface(LPUNKNOWN punk, REFIID riid, 
								   LPUNKNOWN * ppvObj)
{
	SCODE sc = S_OK;

	if(IsEqualIID(riid, &IID_IUnknown) ||
		IsEqualIID(riid, &IID_IOleWindow) ||
		IsEqualIID(riid, &IID_IOleInPlaceUIWindow) ||
		IsEqualIID(riid, &IID_IOleInPlaceFrame))
	{
		ITPOLEINPLACEFRAME_AddRef(*ppvObj = punk);
	}
	else
	{
		sc = E_NOINTERFACE, *ppvObj = NULL;
	}

	return sc;
}


/*
 *	ITPOLEINPLACEFRAME_AddRef
 *
 *	Purpose:
 *		Increments reference count on the specified site.
 *
 *	Arguments:
 *		LPUNKNOWN *		Object whose count we want to increment.
 *
 *	Returns:
 *		ULONG			New value of reference count.
 */
STDMETHODIMP_(ULONG) ITPOLEINPLACEFRAME_AddRef(LPUNKNOWN punk)
{
	return ++PipframeFromPunk(punk)->cRef;
}


/*
 *	ITPOLEINPLACEFRAME_Release
 *
 *	Purpose:
 *		Decrements reference count on the specified site.  If count is
 *		decremented to zero, the object is freed.
 *
 *	Arguments:
 *		LPUNKNOWN *		Object whose count we want to decrement.
 *
 *	Returns:
 *		ULONG			New value of reference count.
 */
STDMETHODIMP_(ULONG) ITPOLEINPLACEFRAME_Release(LPUNKNOWN punk)
{
	ITPOLEINPLACEFRAME * pipframe = PipframeFromPunk(punk);
	ULONG cRef = --pipframe->cRef;

	if(!cRef)
	{
		// Free memory allocated for us
		GlobalFreePtr(pipframe);
		TraceTag(tagInPlace, "ITPOLEINPLACEFRAME_Release: freeing the ipframe");
	}

	AssertSz(cRef >= 0, "ITPOLEINPLACEFRAME_Release: negative cRef");

	return cRef;
}


/*
 *	ITPOLEINPLACEFRAME_GetWindow
 *
 *	Purpose:
 *		Return the window handle of the app-level window for in place use.
 *
 *	Arguments:
 *		ITPOLEINPLACESITE *	Client site.
 *
 *	Returns:
 *		HRESULT				Error status.
 */
STDMETHODIMP ITPOLEINPLACEFRAME_GetWindow(ITPOLEINPLACEFRAME * pipframe,
										  HWND * phwnd)
{
	TraceTag(tagInPlace, "ITPOLEINPLACEFRAME_GetWindow: NYI");

	return E_NOTIMPL;
}


/*
 *	ITPOLEINPLACEFRAME_ContextSensitiveHelp
 *
 *	Purpose:
 *		Notifies the frame that the object has entered Context Help mode.
 *
 *	Arguments:
 *		ITPOLEINPLACESITE *	Client site.
 *
 *	Returns:
 *		HRESULT				Error status.
 */
STDMETHODIMP ITPOLEINPLACEFRAME_ContextSensitiveHelp(ITPOLEINPLACEFRAME *pipframe,
													 BOOL fEnterMode)
{
	TraceTag(tagInPlace, "ITPOLEINPLACEFRAME_ContextSensitiveHelp: NYI");
	TraceError("ITPOLEINPLACEFRAME_ContextSensitiveHelp()", E_NOTIMPL);

	return E_NOTIMPL;
}


/*
 *	ITPOLEINPLACEFRAME_GetBorder
 *
 *	Purpose:
 *		Returns a RECT structure in which the object can put toolbars and 
 *		similar controls while an object is active in place.
 *
 *	Arguments:
 *		ITPOLEINPLACESITE *	Client site.
 *
 *	Returns:
 *		HRESULT				Error status.
 */
STDMETHODIMP ITPOLEINPLACEFRAME_GetBorder(ITPOLEINPLACEFRAME * pipframe,
										  LPRECT prcBorder)
{
	TraceTag(tagInPlace, "ITPOLEINPLACEFRAME_GetBorder: NYI");
	TraceError("ITPOLEINPLACEFRAME_GetBorder()", E_NOTIMPL);

	return E_NOTIMPL;
}


/*
 *	ITPOLEINPLACEFRAME_RequestBorderSpace
 *
 *	Purpose:
 *		Determines whether tools can be installed around the objects 
 *		window frame while the object is active in place.
 *
 *	Arguments:
 *		ITPOLEINPLACESITE *	Client site.
 *
 *	Returns:
 *		HRESULT				Error status.
 */
STDMETHODIMP ITPOLEINPLACEFRAME_RequestBorderSpace(ITPOLEINPLACEFRAME * pipframe,
												   LPCBORDERWIDTHS pbw)
{
	TraceTag(tagInPlace, "ITPOLEINPLACEFRAME_RequestBorderSpace: NYI");
	TraceError("ITPOLEINPLACEFRAME_RequestBorderSpace()", E_NOTIMPL);

	return E_NOTIMPL;
}


/*
 *	ITPOLEINPLACEFRAME_SetBorderSpace
 *
 *	Purpose:
 *		Allocates space for the border requested in the call to the 
 *		RequestBorderSpace member function.
 *
 *	Arguments:
 *		ITPOLEINPLACESITE *	Client site.
 *
 *	Returns:
 *		HRESULT				Error status.
 */
STDMETHODIMP ITPOLEINPLACEFRAME_SetBorderSpace(ITPOLEINPLACEFRAME * pipframe,
											   LPCBORDERWIDTHS pbw)
{
	//$ FUTURE: If NULL, then put our tools back
	TraceTag(tagInPlace, "ITPOLEINPLACEFRAME_SetBorderSpace: NYI");
	TraceError("ITPOLEINPLACEFRAME_SetBorderSpace()", E_NOTIMPL);

	return E_NOTIMPL;
}


/*
 *	ITPOLEINPLACEFRAME_SetActiveObject
 *
 *	Purpose:
 *		Called by the object to provide the frame window a direct channel 
 *		of communication with the active in-place object.
 *
 *	Arguments:
 *		ITPOLEINPLACESITE *	Client site.
 *
 *	Returns:
 *		HRESULT				Error status.
 */
STDMETHODIMP ITPOLEINPLACEFRAME_SetActiveObject(ITPOLEINPLACEFRAME * pipframe,
											    LPOLEINPLACEACTIVEOBJECT pipaobj,
											    LPCSTR szObjName)
{
#ifndef NO_OLE
	// Free any existing active object
	if(pipframe->pipaobj)
		pipframe->pipaobj->lpVtbl->Release(pipframe->pipaobj);

	// If we're given an object, AddRef it; update our remembered ipaobj
	if(pipaobj)
		pipaobj->lpVtbl->AddRef(pipaobj);
	pipframe->pipaobj = pipaobj;

	TraceTag(tagInPlace, "ITPOLEINPLACEFRAME_SetActiveObject: %s", szObjName ? szObjName : "NULL");
#endif	// !NO_OLE

	return S_OK;
}


/*
 *	ITPOLEINPLACEFRAME_InsertMenus
 *
 *	Purpose:
 *		Called by the object server to allow the container to insert 
 *		its menu groups in the composite menu that will be used during
 *		the in-place session.
 *
 *	Arguments:
 *		ITPOLEINPLACESITE *	Client site.
 *
 *	Returns:
 *		HRESULT				Error status.
 */
STDMETHODIMP ITPOLEINPLACEFRAME_InsertMenus(ITPOLEINPLACEFRAME * pipframe,
										    HMENU hmenuShared, 
										    LPOLEMENUGROUPWIDTHS pmgw)
{
	//$ FUTURE: Do something interesting here
	// Don't actually put any menus on right now
	pmgw->width[0] = pmgw->width[2] = pmgw->width[4] = 0;
	TraceTag(tagInPlace, "ITPOLEINPLACEFRAME_InsertMenus: S_OK");

	return S_OK;
}


/*
 *	ITPOLEINPLACEFRAME_SetMenu
 *
 *	Purpose:
 *		Installs the composite menu into the window frame containing
 *		the object that is being activated in place.
 *
 *	Arguments:
 *		ITPOLEINPLACESITE *	Client site.
 *
 *	Returns:
 *		HRESULT				Error status.
 */
STDMETHODIMP ITPOLEINPLACEFRAME_SetMenu(ITPOLEINPLACEFRAME * pipframe, 
									    HMENU hmenuShared, HOLEMENU holemenu, 
									    HWND hwndActiveObject)
{
#ifndef NO_OLE
	HWND hwnd = pipframe->predoc->hwndParent;

	TraceTag(tagInPlace, "ITPOLEINPLACEFRAME_SetMenu: hMenuShared=%08lx holemenu=%08lx", (DWORD) (LPVOID) hmenuShared, (DWORD) (LPVOID) holemenu);

	// Did OLE give us a menu, or leave us to ourselves?
	if(hmenuShared && holemenu)
	{
		// Put the merged menu OLE gave us on our menu bar
		SetMenu(hwnd, hmenuShared);
	}
	else
	{
		// Put our regular menu on the menu bar
		SetMenu(hwnd, hmenuFull);
		SetupWordWrapMenu(pipframe->predoc);
	}
	DrawMenuBar(hwnd);
# ifdef MAC
	DebugStr("\pTry calling OleSetMenuDescriptor()");
# else	// MAC
	// Pass the menu descriptor to OLE
	return OleSetMenuDescriptor(holemenu, pipframe->predoc->hwndParent, 
								hwndActiveObject, (LPOLEINPLACEFRAME) pipframe,
								pipframe->pipaobj);
# endif	// MAC, else
#endif	// !NO_OLE

	return S_OK;
}


/*
 *	ITPOLEINPLACEFRAME_RemoveMenus
 *
 *	Purpose:
 *		Called by the object server to give the container a chance to 
 *		remove its menu elements from the in-place composite menu.
 *
 *	Arguments:
 *		ITPOLEINPLACESITE *	Client site.
 *
 *	Returns:
 *		HRESULT				Error status.
 */
STDMETHODIMP ITPOLEINPLACEFRAME_RemoveMenus(ITPOLEINPLACEFRAME * pipframe, 
										    HMENU hmenuShared)
{
	// We didn't put any menus on!
	TraceTag(tagInPlace, "ITPOLEINPLACEFRAME_RemoveMenus: S_OK");

	return S_OK;
}


/*
 *	ITPOLEINPLACEFRAME_SetStatusText
 *
 *	Purpose:
 *		Sets and displays status text about the in-place object in the
 *		containers frame window status line.
 *
 *	Arguments:
 *		ITPOLEINPLACESITE *	Client site.
 *
 *	Returns:
 *		HRESULT				Error status.
 */
STDMETHODIMP ITPOLEINPLACEFRAME_SetStatusText(ITPOLEINPLACEFRAME * pipframe, 
											  LPCSTR szStatusText)
{
	TraceTag(tagInPlace, "ITPOLEINPLACEFRAME_SetStatusText: NYI");
	TraceError("ITPOLEINPLACEFRAME_SetStatusText()", E_NOTIMPL);

	return E_NOTIMPL;
}


/*
 *	ITPOLEINPLACEFRAME_EnableModeless
 *
 *	Purpose:
 *		Enables or disables modeless dialogs of the frame.
 *
 *	Arguments:
 *		ITPOLEINPLACESITE *	Client site.
 *
 *	Returns:
 *		HRESULT				Error status.
 */
STDMETHODIMP ITPOLEINPLACEFRAME_EnableModeless(ITPOLEINPLACEFRAME * pipframe, 
											   BOOL fEnable)
{
	TraceTag(tagInPlace, "ITPOLEINPLACEFRAME_EnableModeless: NYI");
	TraceError("ITPOLEINPLACEFRAME_EnableModeless()", E_NOTIMPL);

	return E_NOTIMPL;
}


/*
 *	ITPOLEINPLACEFRAME_TranslateAccelerator
 *
 *	Purpose:
 *		Translates keystrokes intended for the container frame while
 *		an object is active in place.
 *
 *	Arguments:
 *		ITPOLEINPLACESITE *	Client site.
 *
 *	Returns:
 *		HRESULT				Error status.
 */
STDMETHODIMP ITPOLEINPLACEFRAME_TranslateAccelerator(ITPOLEINPLACEFRAME *pipframe,
													 LPMSG pmsg, WORD wID)
{
	// REITP doesn't have any accelerators!
	return S_FALSE;
}


LOCAL VOID FindReplace(REDOC *predoc, BOOL fReplace)
{
	FINDREPLACE *pfr;

	if(hwndFR)
		return;

	if(!(pfr = predoc->pfr))
	{
		pfr = predoc->pfr = (FINDREPLACE * ) GlobalAllocPtr(GHND,
								sizeof(FINDREPLACE) + 2 * 80 * sizeof(TCHAR));
		if(!predoc->pfr)
			return;
	}
	else
	{
		memset(pfr, 0, sizeof(FINDREPLACE));
	}

	SendMessage(predoc->hwndRE, EM_HIDESELECTION, fFalse, fTrue);

	pfr->lStructSize = sizeof(FINDREPLACE);
	pfr->hwndOwner = predoc->hwndParent;
	pfr->Flags = FR_HIDEUPDOWN;
	pfr->lpstrFindWhat = (LPSTR) (((BYTE *) pfr) + sizeof(FINDREPLACE));
	pfr->lpstrReplaceWith = pfr->lpstrFindWhat + 80;
	pfr->wFindWhatLen = 80 * sizeof(TCHAR);
	pfr->wReplaceWithLen = 80 * sizeof(TCHAR);

	hwndFR = fReplace ? ReplaceText(pfr) : FindText(pfr);
}


LOCAL VOID ProcessFindReplace(REDOC *predoc, FINDREPLACE *pfr)
{
	HCURSOR hcur;
	LONG cszReplaced = 0;
	LONG cpMatch;
	CHARRANGE chrgSave;
	FINDTEXTEX ft;

	SendMessage(predoc->hwndRE, EM_EXGETSEL, 0, (LPARAM) &chrgSave);
	ft.chrg.cpMost = -1;	// search through end of the text
	ft.chrg.cpMin = chrgSave.cpMin;
	if(!(pfr->Flags & (FR_REPLACE | FR_REPLACEALL)))
		ft.chrg.cpMin = chrgSave.cpMost;
	ft.lpstrText = pfr->lpstrFindWhat;

	if(pfr->Flags & FR_REPLACEALL)
	{
		hcur = SetCursor(LoadCursor(NULL, IDC_WAIT));
		SendMessage(predoc->hwndRE, EM_HIDESELECTION, fTrue, fFalse);
	}

next:
	cpMatch = SendMessage(predoc->hwndRE, EM_FINDTEXTEX,
		(WPARAM) (pfr->Flags),
		(LPARAM) &ft);
	if(cpMatch < 0)
	{
		if(cszReplaced == 0)
		{
			MessageBoxA(hwndFR,
				"The search text is not found.", szAppName, MB_OK);
		}
		else
		{
			char rgch[80];

			wsprintfA(rgch, "Replaced %ld occurances.", cszReplaced);
			MessageBoxA(hwndFR, rgch, szAppName, MB_OK);
		}
		SetFocus(hwndFR);
		goto done;
	}
//	ft.chrg.cpMin = cpMatch;
//	ft.chrg.cpMost = cpMatch + lstrlen(ft.lpstrText);
	ft.chrg.cpMin = ft.chrgText.cpMin;
	ft.chrg.cpMost = ft.chrgText.cpMost;
	SendMessage(predoc->hwndRE, EM_EXSETSEL, 0, (LPARAM) &ft.chrg);
	if(((pfr->Flags & FR_REPLACE) && cszReplaced == 0) ||
		(pfr->Flags & FR_REPLACEALL))
	{
		SendMessage(predoc->hwndRE, EM_REPLACESEL, 0,
			(LPARAM) pfr->lpstrReplaceWith);
		ft.chrg.cpMin = cpMatch + lstrlen(pfr->lpstrReplaceWith);
		ft.chrg.cpMost = -1;	// search through end of the text
		cszReplaced++;
		goto next;
	}

done:
	if(pfr->Flags & FR_REPLACEALL)
	{
		SetCursor(hcur);

		SendMessage(predoc->hwndRE, EM_HIDESELECTION, fFalse, fFalse);
	}
}


VOID UpdateFormatBar(REDOC * predoc)
{
	CHARFORMAT cf;
	PARAFORMAT pf;

	cf.cbSize = sizeof(CHARFORMAT);
	pf.cbSize = sizeof(PARAFORMAT);

	SendMessage(predoc->hwndRE, EM_GETCHARFORMAT, TRUE, (LPARAM) &cf);
	SendMessage(predoc->hwndFormatBar, EM_SETCHARFORMAT, 0, (LPARAM) &cf);
	SendMessage(predoc->hwndRE, EM_GETPARAFORMAT, FALSE, (LPARAM) &pf);
	SendMessage(predoc->hwndFormatBar, EM_SETPARAFORMAT, 0, (LPARAM) &pf);
}



LOCAL VOID ShowMargins(REDOC *predoc)
{
	if(ToggleCheck(predoc, IDM_SHOWMARGINS))
	{
		RECT rc;

		GetClientRect(predoc->hwndParent, &rc);
		ResizeRedoc(predoc, rc);
	}
	else
	{
		SendMessage(predoc->hwndRE, EM_SETRECT, 0, 0);
	}
}


# ifdef DEBUG

LOCAL VOID SetLimit(REDOC *predoc)
{
	LONG cchLimit = 32767;

	if(ToggleCheck(predoc, IDM_BIGLIMIT))
		cchLimit = 1024 * (LONG) 1024 - 1;

	SendMessage(predoc->hwndRE, EM_EXLIMITTEXT, 0, cchLimit);
}


static TCHAR szText[] = "Once upon a time there was an edit control.  "
	"This was a happy edit control until some mean evil tester "
	"(who shall remain nameless) came along and started beating on "
	"the poor little helpless edit control.  The edit control bravely "
	"faced it's unprovoked attacker, but an edit control can only take "
	"so much.  One day when it was being ferociously tortured it thought "
	"to itself \"What have I ever done to this poor homely creature to "
	"deserve this type of punishment?\".  It stirred up it's self esteem "
	"and stood up and said to the nasty creature \"I am an edit control, "
	"hear me roar!  I deserve to be treated with dignity and respect!\".  "
	"The evil little tester was taken aback by the edit control's sudden "
	"show of courage, but being the spawn of hell, he dismissed the edit "
	"control's declaration and continued his ghastly attacks.  The edit "
	"control decided that nothing would ever reform this hideous beast "
	"imparting terror upon it so he decided to do something about it.  "
	"The next day when the heathen was preparing to nuke the edit control "
	"the edit control jumped out at the beast and ripped it's heart out.  "
	"The tester stood shocked for a millisecond and then dropped over dead.  "
	"The end.\r\n\r\n";

LOCAL VOID FillerUp(REDOC *predoc)
{
	const LONG cch = lstrlen(szText);
	LONG cchAdded;
	LONG cchText;
	DWORD dwTicks;

	SetWindowText(predoc->hwndRE, TEXT(""));
	cchText = 0;

	(void) GetAsyncKeyState(VK_ESCAPE);	// reset key state
	dwTicks = GetTickCount();
	do
	{
		LONG cchT;

		SendMessage(predoc->hwndRE, EM_REPLACESEL, 0, (LPARAM) (LPSTR) szText);
		cchT = SendMessage(predoc->hwndRE, WM_GETTEXTLENGTH, 0, 0);
		cchAdded = cchT - cchText;
		if(cchText % 8192 > cchT % 8192)
		{
			const DWORD dwT = GetTickCount();

			TraceTag(tagGeneral, "%ld characters, %ld ticks", cchT, dwT - dwTicks);
			dwTicks = dwT;
		}
		cchText = cchT;
		if(GetAsyncKeyState(VK_ESCAPE) & 0x8001)
		{
			TraceTag(tagGeneral, "stopping for escape");
			break;
		}
	} while(cchAdded > 0 && !fErrSpace);

	TraceTag(tagGeneral, "Stopped at %ld character", cchText);
}

#endif	// DEBUG
