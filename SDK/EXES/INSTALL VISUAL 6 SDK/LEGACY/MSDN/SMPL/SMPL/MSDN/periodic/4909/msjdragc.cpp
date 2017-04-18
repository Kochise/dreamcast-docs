// MSJDragCtl.cpp : Implementation of the CMSJDragCtrl OLE control class.

#include "stdafx.h"
#include "msjdrag.h"
#include "VBFrWnd.h"
#include "MSJDragCtl.h"
#include "MSJDragPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMSJDragCtrl, COleControl)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMSJDragCtrl, COleControl)
	//{{AFX_MSG_MAP(CMSJDragCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMSJDragCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CMSJDragCtrl)
	DISP_PROPERTY_EX(CMSJDragCtrl, "ParentWnd", GetParentWnd, SetParentWnd, VT_HANDLE)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMSJDragCtrl, COleControl)
	//{{AFX_EVENT_MAP(CMSJDragCtrl)
	EVENT_CUSTOM("FileDrop", FireFileDrop, VTS_HANDLE  VTS_BSTR)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMSJDragCtrl, 1)
	PROPPAGEID(CMSJDragPropPage::guid)
END_PROPPAGEIDS(CMSJDragCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMSJDragCtrl, "MSJDRAG.MSJDragCtrl.1",
	0xab688443, 0x632f, 0x11cf, 0xa0, 0x18, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMSJDragCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMSJDrag =
		{ 0xab688441, 0x632f, 0x11cf, { 0xa0, 0x18, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DMSJDragEvents =
		{ 0xab688442, 0x632f, 0x11cf, { 0xa0, 0x18, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwMSJDragOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMSJDragCtrl, IDS_MSJDRAG, _dwMSJDragOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMSJDragCtrl::CMSJDragCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMSJDragCtrl

BOOL CMSJDragCtrl::CMSJDragCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MSJDRAG,
			IDB_MSJDRAG,
			FALSE,                      //  Not insertable
			_dwMSJDragOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CMSJDragCtrl::CMSJDragCtrl - Constructor

CMSJDragCtrl::CMSJDragCtrl()
{
	InitializeIIDs(&IID_DMSJDrag, &IID_DMSJDragEvents);

	// TODO: Initialize your control's instance data here.
	m_parentwnd = NULL;
	}


/////////////////////////////////////////////////////////////////////////////
// CMSJDragCtrl::~CMSJDragCtrl - Destructor

CMSJDragCtrl::~CMSJDragCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CMSJDragCtrl::OnDraw - Drawing function

void CMSJDragCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);

	if (m_hWnd)
		ShowWindow(FALSE);
}


/////////////////////////////////////////////////////////////////////////////
// CMSJDragCtrl::DoPropExchange - Persistence support

void CMSJDragCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CMSJDragCtrl::OnResetState - Reset control to default state

void CMSJDragCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CMSJDragCtrl message handlers

OLE_HANDLE CMSJDragCtrl::GetParentWnd() 
{
	// TODO: Add your property handler here

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////

void CMSJDragCtrl::SetParentWnd(OLE_HANDLE nNewValue) 
{
	// TODO: Add your property handler here

	SetModifiedFlag();
}

/////////////////////////////////////////////////////////////////////////////

HWND CMSJDragCtrl::GetContainerHWnd()
{
	LPOLEWINDOW       lpOleWnd;
	HWND              docWnd = NULL;
	HRESULT           hRes;

	// If the control exists with an hWnd, this call will use its
	// IOleInPlaceSite pointer to retrieve the container's IOleWindow.
	// From there, IOleWindow can be queried to retrieve the container's
	// hWnd.

	if (m_pInPlaceSite) // Should always be ok
	{
		hRes = m_pInPlaceSite->QueryInterface(IID_IOleWindow, (LPVOID *) &lpOleWnd);

		if (SUCCEEDED(hRes))
		{
			hRes = lpOleWnd->GetWindow(&docWnd);

			if (SUCCEEDED(hRes))
			{
				lpOleWnd->Release();
			}
		}
	}

	return docWnd;
}

/////////////////////////////////////////////////////////////////////////////

int CMSJDragCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	HWND hw;

	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Call our control's added procedure to get its
	// container window through its OLE interfaces.

	hw = GetContainerHWnd();

	// Tell the container to accept dragged files.

	::DragAcceptFiles(hw, TRUE);

	// Initialize the m_framewnd object with the real frame
	// window we just retrieved.

	m_framewnd.SubclassWindow(hw);

	// Initialize the frame window's pointer back to this
	// control object. This allows the framewnd class to
	// fire off an event through this control class.

	m_framewnd.m_ctrlwnd = this;
	
	return 0;
}
