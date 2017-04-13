//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright  1994-1996  Microsoft Corporation.  All Rights Reserved.
//
//      PROGRAM: FVINIT.CPP             
//
//      PURPOSE:  All initialization functions and some miscellany for the CFileViewer implementation.
//
//      PLATFORMS:      Windows 95
//
//      FUNCTIONS:      
//   
//
//      SPECIAL INSTRUCTIONS: N/A
//
#include "fileview.h"

//
//   FUNCTION: CFileViewer::Init        
//
//   PURPOSE: Performs any intiailization of a CFileViewer that's prone to
//  failure that we also use internally before exposing the object
//  outside.  
//
//   RETURN VALUE:
//   HRESULT         NOERROR if successful, error code otherwise.
//
HRESULT CFileViewer::Init(void)
    {
    LPUNKNOWN       pIUnknown=(LPUNKNOWN)this;
    WNDCLASS        wc;
    HRESULT         hr;
    HDC             hDC;

    //Default error code
    hr=ResultFromScode(E_OUTOFMEMORY);

    // Make pIUnknown point to outer unknown if we get one.
    // The interfaces allocated below are always given an IUnknown
    // to which they delegate at all times.  This will be either
    // the CFileViewer object's IUnknown itself or the outer
    // unknown if this object is aggregated.  The interfaces
    // need not know which case is being used.
    if (NULL!=m_pUnkOuter)
	pIUnknown=m_pUnkOuter;

    //Allocate contained interfaces.
    m_pIPersistFile=new CImpIPersistFile(this, pIUnknown);

    if (NULL==m_pIPersistFile)
	return hr;

    m_pIFileViewer=new CImpIFileViewer(this, pIUnknown);

    if (NULL==m_pIFileViewer)
	return hr;

    m_pST=new CStringTable(m_hInst);

    if (NULL==m_pST)
	return hr;

    // Go load the strings we need in CFileViewer::String.  
    if (!m_pST->FInit(IDS_MIN, IDS_MAX, CCHSTRINGMAX))
	return hr;

    //Register window classes that we'll need to display the file
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = FileViewerFrameProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = CBWNDEXTRAFRAME;
    wc.hInstance     = m_hInst;
    wc.hIcon         = LoadIcon(m_hInst, "Icon");
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE+1);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
    wc.lpszClassName = String(IDS_CLASSFRAME);

    if (!RegisterClass(&wc))
	return hr;

    // MODIFY:  This is the viewport window that does the work
    // of displaying the data.  Modify it to your needs.
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = ViewportWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = CBWNDEXTRAVIEWPORT;
    wc.hInstance     = m_hInst;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
    wc.lpszClassName = String(IDS_CLASSVIEWPORT);

    if (!RegisterClass(&wc))
	return hr;

    m_fClassReg=TRUE;

    // Create a default fixed pitch font for the Viewport.  We
    // use Courier New here instead of say, SYSTEM_FIXED_FONT
    // because we want the font sizing buttons to work normally
     // when this window appears, and the system fonts do not
     // scale, but Courier New does.  Default is 10 point calculated
     // from 10*PIXELSPERINCH/72.
    hDC=GetDC(NULL);
    m_cyPPI=GetDeviceCaps(hDC, LOGPIXELSY);
    ReleaseDC(NULL, hDC);

    m_hFont=CreateFont(MulDiv(-10, m_cyPPI, 72)
	, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE
	, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS
	, DEFAULT_QUALITY, FIXED_PITCH | FF_MODERN, "Courier New");

    return NOERROR;
    }
//
//   FUNCTION: CFileViewer::FInitFrameControls  
//
//   PURPOSE:  Creates and initializes the toolbar and status bar for the frame window.
//
//   PARAMETERS: 
//
//   RETURN VALUE:
//  BOOL            TRUE if the function worked, FALSE otherwise.
//
BOOL CFileViewer::FInitFrameControls(void)
    {
    BOOL        fRet;
    RECT        rc;
    TBBUTTON    rgtb[CTBBUTTONS];

     // Initialize the toolbar button array.  This uses the TOOLS.BMP
     // resource which has three buttons and one separator.  The
     // buttons are tied to File/Open As and Increase/Decrease Font
     // size.
    rgtb[0].iBitmap=IDBT_OPENAS;
    rgtb[0].idCommand=IDM_FILEOPENAS;
    rgtb[0].fsState=TBSTATE_ENABLED;
    rgtb[0].fsStyle=TBSTYLE_BUTTON;
    rgtb[0].dwData=0L;
    rgtb[0].iString=0;

    rgtb[1].iBitmap=0;
    rgtb[1].idCommand=0;
    rgtb[1].fsState=TBSTATE_ENABLED;
    rgtb[1].fsStyle=TBSTYLE_SEP;
    rgtb[1].dwData=0L;
    rgtb[1].iString=0;

    rgtb[2].iBitmap=IDBT_FONTSIZEINCREASE;
    rgtb[2].idCommand=IDM_VIEWFONTINCREASE;
    rgtb[2].fsState=TBSTATE_ENABLED;
    rgtb[2].fsStyle=TBSTYLE_BUTTON;
    rgtb[2].dwData=0L;
    rgtb[2].iString=0;

    rgtb[3].iBitmap=IDBT_FONTSIZEDECREASE;
    rgtb[3].idCommand=IDM_VIEWFONTDECREASE;
    rgtb[3].fsState=TBSTATE_ENABLED;
    rgtb[3].fsStyle=TBSTYLE_BUTTON;
    rgtb[3].dwData=0L;
    rgtb[3].iString=0;

     // BUGBUG:  Open as button:  call SHGetIconOfFile to retrieve
     // the image, then overwrite it in the toolbar bitmap we send
     // to CreateToolbarEx.  If SHGetIconOfFile fails, then just
     // use the one in the toolbar bitmap already.
     //
    m_hWndToolbar=CreateToolbarEx(m_hWnd, TBSTYLE_TOOLTIPS
	| WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS, ID_TOOLBAR
	, CTBBITMAPS, m_hInst, IDB_TOOLS, rgtb, CTBBUTTONS
	, 0, 0, 0, 0, sizeof(TBBUTTON));

    if (NULL==m_hWndToolbar)
	{
	ODS("CFileViewer::FInitFrameTools failed to create toolbar");
	return FALSE;
	}

     // Remember the height for resizing this and the viewport.
     // Use window rectangles for toolbars.
    GetWindowRect(m_hWndToolbar, &rc);
    m_cyTools=rc.bottom-rc.top;

     // Status line
    m_hWndStatus=CreateStatusWindow(WS_CHILD | WS_VISIBLE
	, String(IDS_MSGREADY), m_hWnd, ID_STATUSBAR);

    if (NULL==m_hWndStatus)
	{
	ODS("CFileViewer::FInitFrameTools failed to create status bar");
	return FALSE;
	}

     // Remember the height for resizing this and the viewport.
     // Use client rectangle for status lines.
    GetClientRect(m_hWndStatus, &rc);
    m_cyStatus=rc.bottom-rc.top;

     // Create a status bar helper and tell it what messages
     // to use.  This object will be called from WM_MENUSELECT
     // in FileViewerFrameProc in FVPROC.CPP.
    m_pSH=new CStatusHelper(m_hWndStatus, m_hInst);

    if (NULL==m_pSH)
	return FALSE;

    fRet=m_pSH->MessageMap(m_hWnd, IDR_STATMESSAGEMAP, IDS_STATUSMSGMIN
	, IDS_STATUSMSGMAX, CCHSTATUSMSGMAX, ID_MENUFILE, ID_MENUHELP
	, ID_MSGREADY, ID_MSGEMPTY, ID_MENUSYS);

    return fRet;
    }

//
//   FUNCTION:  CFileViewer::String
//
//   PURPOSE:    string lookup function for access to stringtable. 
//
LPSTR CFileViewer::String(UINT uID)
    {
    return (*m_pST)[uID];
    }

//
//   FUNCTION:  CFileViewer::MemAlloc
//
//   PURPOSE:Central allocation function using IMalloc.   
//
LPVOID CFileViewer::MemAlloc(ULONG cb)
    {
    LPMALLOC    pIMalloc;
    LPVOID      pv;
    HRESULT     hr;

    if (FAILED(hr = CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
	{
	ODSu("CFileViewer::MemAlloc CoGetMalloc failed %ld", hr);

	if (hr == CO_E_NOTINITIALIZED)
	    {
	    if ((FAILED(hr=CoInitialize(NULL))) ||
			FAILED(hr=CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
		{
		ODSu("CFileViewer::MemAlloc CoInitialize/CoGetMalloc failed %x", hr);
		return NULL;
		}

	    }
	else
	    return NULL;
	}

    pv=pIMalloc->Alloc(cb);
    pIMalloc->Release();
    return pv;
    }
//
//   FUNCTION:CFileViewer::MemFree      
//
//   PURPOSE:  Central free function using IMalloc. 
//
void CFileViewer::MemFree(LPVOID pv)
    {
    LPMALLOC    pIMalloc;

    if (NULL==pv)
	{
	ODS("CFileViewer::MemFree passed NULL pointer");
	return;
	}

    if (FAILED(CoGetMalloc(MEMCTX_SHARED, &pIMalloc)))
	{
	ODS("CFileViewer::MemFree CoGetMalloc failed");
	return;
	}

    pIMalloc->Free(pv);
    pIMalloc->Release();
    return;
    }
//
//   FUNCTION: CFileViewer::QueryInterface      
//
STDMETHODIMP CFileViewer::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

     //The only calls for IUnknown are either in a nonaggregated
     // case or when created in an aggregation, so in either case
     // always return our IUnknown for IID_IUnknown.
    if (IsEqualIID(riid, IID_IUnknown))
	*ppv=(LPVOID)this;

    //IPersist is base of IPersistFile
    if (IsEqualIID(riid, IID_IPersist)
	|| IsEqualIID(riid, IID_IPersistFile))
	*ppv=(LPVOID)m_pIPersistFile;

    if (IsEqualIID(riid, IID_IFileViewer))
	*ppv=(LPVOID)m_pIFileViewer;

    //AddRef any interface we'll return.
    if (NULL!=*ppv)
	{
	((LPUNKNOWN)*ppv)->AddRef();
	return NOERROR;
	}

    return ResultFromScode(E_NOINTERFACE);
    }

//
//   FUNCTION:  CFileViewer::AddRef
//
STDMETHODIMP_(ULONG) CFileViewer::AddRef(void)
    {
    return ++m_cRef;
    }

//
//   FUNCTION: CFileViewer::Release
//
STDMETHODIMP_(ULONG) CFileViewer::Release(void)
    {
    ULONG       cRefT;

    cRefT=--m_cRef;

    ODSu("CFileViewer::Release Count=%d", cRefT);

    if (0L==m_cRef)
	{
	 // Tell the server that an object is going away
	 // so it can shut down if appropriate.  (See FILEVIEW.CPP
	 // for the ObjectDestroyed function).
	if (NULL!=m_pfnDestroy)
	    (*m_pfnDestroy)();

	delete this;
	}

    return cRefT;
    }
