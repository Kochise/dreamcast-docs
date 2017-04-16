// StopLiteCtl.cpp : Implementation of the CStopLiteCtrl OLE control class.

#include "stdafx.h"
#include "StopLite.h"
#include "StopLiteCtl.h"
#include "StopLitePpg.h"

#include "helpers.h"
#include <objsafe.h>

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
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CStopLiteCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CStopLiteCtrl)
	DISP_PROPERTY_EX(CStopLiteCtrl, "Color", GetColor, SetColor, VT_I2)
	DISP_FUNCTION(CStopLiteCtrl, "Next", Next, VT_EMPTY, VTS_NONE)
	DISP_DEFVALUE(CStopLiteCtrl, "Color")
	DISP_STOCKFUNC_REFRESH()
	DISP_STOCKPROP_BACKCOLOR()
	DISP_STOCKPROP_FORECOLOR()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CStopLiteCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CStopLiteCtrl, COleControl)
	//{{AFX_EVENT_MAP(CStopLiteCtrl)
	EVENT_CUSTOM("Stop", FireStop, VTS_NONE)
	EVENT_CUSTOM("Caution", FireCaution, VTS_NONE)
	EVENT_CUSTOM("Go", FireGo, VTS_NONE)
	EVENT_CUSTOM("Testing", FireTesting, VTS_NONE)
	EVENT_CUSTOM("Off", FireOff, VTS_NONE)
	EVENT_STOCK_CLICK()
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
		{ 0x20048bb1, 0xdb68, 0x11cf, { 0x9c, 0xaf, 0, 0xaa, 0, 0x6c, 0xb4, 0x25 } };
const IID BASED_CODE IID_DStopLiteEvents =
		{ 0x20048bb2, 0xdb68, 0x11cf, { 0x9c, 0xaf, 0, 0xaa, 0, 0x6c, 0xb4, 0x25 } };


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


	if (bRegister) {
		BOOL retval = AfxOleRegisterControlClass(
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

		// mark as safe for scripting--failure OK
		HRESULT hr = CreateComponentCategory(CATID_SafeForScripting, 
			L"Controls that are safely scriptable");

		if (SUCCEEDED(hr))
			// only register if category exists
			RegisterCLSIDInCategory(m_clsid, CATID_SafeForScripting);
			// don't care if this call fails

		// mark as safe for data initialization
		hr = CreateComponentCategory(CATID_SafeForInitializing, 
			L"Controls safely initializable from persistent data");

		if (SUCCEEDED(hr))
			// only register if category exists
			RegisterCLSIDInCategory(m_clsid, CATID_SafeForInitializing);
			// don't care if this call fails

		return retval;
	}
	else
		// since unregistering the class automatically eliminates 
		// the category registration and since we don't want to 
		// remove the categories, we don't need to do anything special

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
	// 1. erase background using container's background color
	CBrush brAmbientBack(TranslateColor(AmbientBackColor()));
	pdc->FillRect(rcBounds, &brAmbientBack);
	
	// 2. draw bezel using control's stock properties 
	//	BackColor and ForeColor
		// calculate size based on 40% of height
	CRect rcBezel(rcBounds);
	int nHeight = rcBounds.Height();
	int nWidth = rcBounds.Width();
	int nBezelWidth = nHeight * 40 / 100;
	if (nBezelWidth > nWidth) 
		nBezelWidth = nWidth;	// not more then width!
	int nDeflateBezel = (nWidth - nBezelWidth) / 2;
	rcBezel.DeflateRect(nDeflateBezel, 0);
		// create and select brush and pen
	CBrush brBack(TranslateColor(GetBackColor()));
	CBrush * pbrOld = pdc->SelectObject(&brBack);
	CPen pnFore(PS_SOLID, 2, TranslateColor(GetForeColor()));
	CPen * ppnOld = pdc->SelectObject(&pnFore);
		// draw
	pdc->Rectangle(rcBezel);
		// select old brush, but not old pen
	pdc->SelectObject(pbrOld);

	// 3. draw lights using stock ForeColor, already selected
		// translate enum code to bits for red, green, yellow
	int nLights = TranslateLights();
		// percentages are percentage of height
		// draw red light on top, 6% down, 27% diameter
	DrawLight(pdc, rcBounds, 6, 27, 
		(nLights & SLBIT_RED) ? SLCOLOR_RED : SLCOLOR_OFF);
		// yellow light in middle, 37% down, 27% diameter
	DrawLight(pdc, rcBounds, 37, 27, 
		(nLights & SLBIT_YELLOW) ? SLCOLOR_YELLOW : SLCOLOR_OFF);
		// green light on bottom, 68% down, 27% diameter
	DrawLight(pdc, rcBounds, 68, 27,
		(nLights & SLBIT_GREEN) ? SLCOLOR_GREEN : SLCOLOR_OFF);
	pdc->SelectObject(ppnOld);
}


/////////////////////////////////////////////////////////////////////////////
// CStopLiteCtrl::DoPropExchange - Persistence support

void CStopLiteCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
	PX_Short(pPX, "Color", m_color, SL_TEST); 
					// default to test state (all on)

					// check for load of bad value, fix
	if (pPX->IsLoading()) {
		if (m_color < SL_NONE || m_color > SL_TEST)  {
			m_color = SL_TEST;
		}
	}
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

void CStopLiteCtrl::DrawLight(
// draws an individual light centered in the control at
//	vertical position specified
		CDC* pdc,				// DC in which to draw
		const CRect& rcBounds,	// control's rectangle
		int nPercentDown,		// top position as % of height
		int nPercentDiameter,	// diameter as % of height
		COLORREF crColor		// color to fill light	
	)
{

	// calculate diameter in drawing units
	int nHeight = rcBounds.Height();
	int nWidth = rcBounds.Width();
	int nDiameter = nHeight * nPercentDiameter / 100;
	if (nDiameter > nWidth) 
		nDiameter = nWidth;	// but not greater than width!

	// create light's bounding rect
	int nLeftEdge = (rcBounds.left + rcBounds.right - nDiameter) / 2;
	int nTopEdge = rcBounds.top + nHeight * nPercentDown / 100;
	CRect rcLight(	nLeftEdge,
					nTopEdge,
					nLeftEdge + nDiameter,
					nTopEdge + nDiameter);
	// make absolutely sure we're within bounds--
	// distort circle if necessary!
	rcLight.IntersectRect(rcLight, rcBounds);

	// create brush, draw, select old brush
	CBrush brColor(crColor);
	CBrush * brOld = pdc->SelectObject(&brColor);
	pdc->Ellipse(rcLight);
	pdc->SelectObject(brOld);

}

int CStopLiteCtrl::TranslateLights()
// sets appropriate bits for stoplight state
{
	int nLights = SLBIT_RED;	// safe default
	switch (m_color) {
	case SL_NONE: nLights = 0;
		break;
	case SL_RED: nLights = SLBIT_RED;
		break;
	case SL_GREEN: nLights = SLBIT_GREEN;
		break;
	case SL_YELLOW: nLights = SLBIT_YELLOW;
		break;
	case SL_TEST: nLights = SLBIT_RED | SLBIT_YELLOW | SLBIT_GREEN;
		break;
	}
	return nLights;
}

void CStopLiteCtrl::Next() 
// changes stoplight to next state, redraws
{
	if (m_color >= SL_LAST || m_color < SL_FIRST)  {
		m_color = SL_FIRST;
	}
	else m_color++;
	InvalidateControl();
	FireRightEvent();
	SetModifiedFlag();
}

short CStopLiteCtrl::GetColor() 
{
	return m_color;
}

void CStopLiteCtrl::SetColor(short nNewValue)
// set color, redraw; throw error if parameter bad
{
	if (nNewValue >= SL_NONE && nNewValue <= SL_TEST)  {
		m_color = nNewValue;
		InvalidateControl();
		FireRightEvent();
		SetModifiedFlag();
	}
	else {
		ThrowError(CTL_E_ILLEGALFUNCTIONCALL, 
			"Color parameter out of range");
	}
}

void CStopLiteCtrl::FireRightEvent()
// called whenever the stoplight state changes to fire the
//	appropriate event--must call AFTER m_color set to new value!
// Use the source browser to make sure you call each time 
//	m_color changed!
{
	switch (m_color) {
		case SL_RED: FireStop();
			break;
		case SL_YELLOW: FireCaution();
			break;
		case SL_GREEN: FireGo();
			break;
		case SL_NONE: FireOff();
			break;
		case SL_TEST: FireTesting();
			break;
	}
}


void CStopLiteCtrl::OnAmbientPropertyChange(DISPID dispid) 
{
	// Repaint if ambient background changed or if several changed
	if (dispid == DISPID_AMBIENT_BACKCOLOR ||
		dispid == DISPID_UNKNOWN) 
	{
		InvalidateControl();
	}

	// pass on to base class
	COleControl::OnAmbientPropertyChange(dispid);
}

void CStopLiteCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
// call Next method on left click, allow Click stock event to be fired
{
	Next();
	
	COleControl::OnLButtonDown(nFlags, point);
}
