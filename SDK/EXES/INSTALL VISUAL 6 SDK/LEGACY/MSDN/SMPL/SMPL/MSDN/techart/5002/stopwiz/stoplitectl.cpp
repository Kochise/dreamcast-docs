// StopLiteCtl.cpp : Implementation of the CStopLiteCtrl OLE control class.

#include "stdafx.h"
#include "StopLite.h"
#include "StopLiteCtl.h"
#include "StopLitePpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CStopLiteCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CStopLiteCtrl, COleControl)
	//{{AFX_MSG_MAP(CStopLiteCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CStopLiteCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CStopLiteCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CStopLiteCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CStopLiteCtrl, COleControl)
	//{{AFX_EVENT_MAP(CStopLiteCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CStopLiteCtrl, 1)
	PROPPAGEID(CStopLitePropPage::guid)
END_PROPPAGEIDS(CStopLiteCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CStopLiteCtrl, "STOPLITE.StopLiteCtrl.1",
	0x20048bb3, 0xdb68, 0x11cf, 0x9c, 0xaf, 0, 0xaa, 0, 0x6c, 0xb4, 0x25)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CStopLiteCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DStopLite =
		{ 0xab9422e1, 0xec0f, 0x11cf, { 0x9c, 0xc6, 0, 0xaa, 0, 0x6c, 0xb4, 0x25 } };
const IID BASED_CODE IID_DStopLiteEvents =
		{ 0xab9422e2, 0xec0f, 0x11cf, { 0x9c, 0xc6, 0, 0xaa, 0, 0x6c, 0xb4, 0x25 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwStopLiteOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CStopLiteCtrl, IDS_STOPLITE, _dwStopLiteOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CStopLiteCtrl::CStopLiteCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CStopLiteCtrl

BOOL CStopLiteCtrl::CStopLiteCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_STOPLITE,
			IDB_STOPLITE,
			afxRegApartmentThreading,
			_dwStopLiteOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CStopLiteCtrl::CStopLiteCtrl - Constructor

CStopLiteCtrl::CStopLiteCtrl()
{
	InitializeIIDs(&IID_DStopLite, &IID_DStopLiteEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CStopLiteCtrl::~CStopLiteCtrl - Destructor

CStopLiteCtrl::~CStopLiteCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CStopLiteCtrl::OnDraw - Drawing function

void CStopLiteCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// TODO: Replace the following code with your own drawing code.
	pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
	pdc->Ellipse(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CStopLiteCtrl::DoPropExchange - Persistence support

void CStopLiteCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CStopLiteCtrl::OnResetState - Reset control to default state

void CStopLiteCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CStopLiteCtrl::AboutBox - Display an "About" box to the user

void CStopLiteCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_STOPLITE);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CStopLiteCtrl message handlers
