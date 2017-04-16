// callbctl.cpp : Implementation of the CCallBackCtrl OLE control class.

#include "stdafx.h"
#include "cback.h"
#include "callbctl.h"
#include "callbppg.h"
#include "memory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CCallBackCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CCallBackCtrl, COleControl)
	//{{AFX_MSG_MAP(CCallBackCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CCallBackCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CCallBackCtrl)
	DISP_FUNCTION(CCallBackCtrl, "WatchMsg", WatchMsg, VT_I2, VTS_I2)
	DISP_FUNCTION(CCallBackCtrl, "PtrValL", PtrValL, VT_I4, VTS_HANDLE)
	DISP_FUNCTION(CCallBackCtrl, "PtrValI", PtrValI, VT_I2, VTS_HANDLE)
	DISP_STOCKPROP_HWND()
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CCallBackCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CCallBackCtrl, COleControl)
	//{{AFX_EVENT_MAP(CCallBackCtrl)
	EVENT_CUSTOM("Callback", FireCallback, VTS_I2  VTS_I4  VTS_I4)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CCallBackCtrl, 1)
	PROPPAGEID(CCallBackPropPage::guid)
END_PROPPAGEIDS(CCallBackCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CCallBackCtrl, "MSJ.Callback.Control",
	0x3d76aaa0, 0x17aa, 0x11cf, 0xa0, 0x18, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CCallBackCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DCallBack =
		{ 0x3d76aaa1, 0x17aa, 0x11cf, { 0xa0, 0x18, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };
const IID BASED_CODE IID_DCallBackEvents =
		{ 0x3d76aaa2, 0x17aa, 0x11cf, { 0xa0, 0x18, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwCallBackOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CCallBackCtrl, IDS_CALLBACK, _dwCallBackOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CCallBackCtrl::CCallBackCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CCallBackCtrl

BOOL CCallBackCtrl::CCallBackCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_CALLBACK,
			IDB_CALLBACK,
			TRUE,                       //  Insertable
			_dwCallBackOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CCallBackCtrl::CCallBackCtrl - Constructor

CCallBackCtrl::CCallBackCtrl()
{
	InitializeIIDs(&IID_DCallBack, &IID_DCallBackEvents);
}


/////////////////////////////////////////////////////////////////////////////
// CCallBackCtrl::~CCallBackCtrl - Destructor

CCallBackCtrl::~CCallBackCtrl()
{
}


/////////////////////////////////////////////////////////////////////////////
// CCallBackCtrl::OnDraw - Drawing function

void CCallBackCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{

    // Always hide the window - we need a handle, but not a displayed
    // window.

    if (m_hWnd != NULL)
		::ShowWindow(m_hWnd, SW_HIDE);

	pdc->Rectangle(rcBounds);
}


/////////////////////////////////////////////////////////////////////////////
// CCallBackCtrl::DoPropExchange - Persistence support

void CCallBackCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);
}


/////////////////////////////////////////////////////////////////////////////
// CCallBackCtrl::OnResetState - Reset control to default state

void CCallBackCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}


/////////////////////////////////////////////////////////////////////////////
// CCallBackCtrl::AboutBox - Display an "About" box to the user

void CCallBackCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_CALLBACK);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CCallBackCtrl message handlers

short CCallBackCtrl::WatchMsg(short msg) 
{
    // Control method - the user can add a message for the control
    // to watch for.

    m_msglist.Add(msg);

	return msg;
}

// When we get a registered message, call FireCallback(msg, wParam, lParam)

LRESULT CCallBackCtrl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	for (int m=0; m < m_msglist.GetSize(); m++)
	{
		if (m_msglist[m] == message)
			FireCallback(message, wParam, lParam);
	}

	return COleControl::WindowProc(message, wParam, lParam);
}

// Special bonus for people who actually read these code samples!
// The following functions take a long int pointer value and return
// the long integer or short integer it points to. These can be
// useful depending on the information the Callback function sends
// back to wParam and lParam.

long CCallBackCtrl::PtrValL(OLE_HANDLE lpPtr) 
{
	return *((LPLONG) lpPtr);
}

short CCallBackCtrl::PtrValI(OLE_HANDLE lpPtr) 
{
	return *((LPINT) lpPtr);
}
