// televisi.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\impiunk.h"
#include "appliances.h"
#include "..\include\appliancesid.h"
#include "..\include\iapplianceui.h"
#include "..\include\ibitmap.h"
#include "..\include\inotify.h"
#include "..\include\inotifysrc.h"
#include "resource.h"
#include "televisi.h"
#include "tvdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTelevision

IMPLEMENT_DYNCREATE(CTelevision, CCmdTarget)

CTelevision::CTelevision()
{
	TRACE("CTelevision::CTelevision()\n");
	m_punkBitmap = NULL;
    m_pIBitmap = NULL;
    m_bIsOn = FALSE;
    m_punkNotifyList = NULL;
    m_pINotifySrc = NULL;

	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CTelevision::~CTelevision()
{
	TRACE("CTelevision::~CTelevision()\n");
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void CTelevision::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	// Release the aggregated object interfaces
    // We add a ref count to our own counter here to
    // prevent our destructor from being called again.
    m_dwRef++;

    // We then add one ref count for each cached interface pointer
    // we created for our aggregated objects.

    ASSERT(m_pINotifySrc);
    m_dwRef++;
    m_pINotifySrc->Release();

    ASSERT(m_punkNotifyList);
    m_punkNotifyList->Release();

    ASSERT(m_pIBitmap);
    m_dwRef++;
    m_pIBitmap->Release();

    ASSERT(m_punkBitmap);
    m_punkBitmap->Release();

	delete this;
}


BEGIN_MESSAGE_MAP(CTelevision, CCmdTarget)
	//{{AFX_MSG_MAP(CTelevision)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTelevision, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CTelevision)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CTelevision, "Television", 0x44434a22, 0x4374, 0x11ce, 0x9e, 0xe8, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf)

BEGIN_INTERFACE_MAP(CTelevision, CCmdTarget)
    INTERFACE_PART(CTelevision, IID_IApplianceUI, ApplianceUI)
    INTERFACE_AGGREGATE(CTelevision, m_punkNotifyList)
    INTERFACE_AGGREGATE(CTelevision, m_punkBitmap)
END_INTERFACE_MAP()

// IUnknown for IApplianceUI
    IMPLEMENT_IUNKNOWN(CTelevision, ApplianceUI)

// IApplianceUI methods
STDMETHODIMP CTelevision::XApplianceUI::ShowControl(HWND hwndParent)
{
    METHOD_PROLOGUE(CTelevision, ApplianceUI);
    CWnd wndParent;
    wndParent.Attach(hwndParent);
    CTelevisionDlg* pDlg = new CTelevisionDlg;
    pDlg->m_pTV = pThis;
    pDlg->Create(&wndParent);
    return NOERROR;
}

/////////////////////////////////////////////////////////////////
// Direct object control functions 

BOOL CTelevision::Power(BOOL b)
{
    if (b == m_bIsOn) return TRUE;

    if (b) {
        AfxMessageBox("Sorry, the TV is broken.");
        return FALSE;
    }

    // Save the new state
    m_bIsOn = b;

    // Send change notification
    if (m_pINotifySrc) {
        m_pINotifySrc->NotifyAll();
    }

    return TRUE;
}

BOOL CTelevision::OnCreateAggregates()
{
    // Create the bitmap object we want to aggregate
    HRESULT hr = ::CoCreateInstance(CLSID_BitmapObject,
                            GetControllingUnknown(),
                            CLSCTX_INPROC_SERVER,
                            IID_IUnknown,
                            (LPVOID*)&m_punkBitmap);
    if (FAILED(hr)) {
        TRACE("Failed to create object. SCODE: %8.8lXH (%lu)\n",
              GetScode(hr),
              GetScode(hr) & 0x0000FFFF);
        m_punkBitmap = NULL;
        return FALSE;
    }
    ASSERT(m_punkBitmap);

    // get a cached pointer to the IBitmap interface
    if (m_punkBitmap->QueryInterface(IID_IBitmap, (LPVOID*)&m_pIBitmap) != S_OK) {
        TRACE("IBitmap not supported\n");
        return FALSE;
    }

    m_dwRef--;
    ASSERT(m_dwRef > 0);

    if (m_pIBitmap->LoadResource(IDR_DIB_TV) != S_OK) {
        TRACE("Failed to load bitmap resource\n");
    }

    // Set the the initial brightness level so we will get the
    // correct image clipping
    Power(0);

    // Create the notify list object we want to aggregate
    hr = ::CoCreateInstance(CLSID_NotifyListObject,
                                    GetControllingUnknown(),
                                    CLSCTX_INPROC_SERVER,
                                    IID_IUnknown,
                                    (LPVOID*)&m_punkNotifyList);
    if (FAILED(hr)) {
        TRACE("Failed to create object. SCODE: %8.8lXH (%lu)\n",
              GetScode(hr),
              GetScode(hr) & 0x0000FFFF);
        m_punkNotifyList = NULL;
        return FALSE;
    }
    ASSERT(m_punkNotifyList);

    // get a pointer to the object's INotifySrc interface
    if (m_punkNotifyList->QueryInterface(IID_INotifySrc, (LPVOID*)&m_pINotifySrc) != S_OK) {
        TRACE("INotifySrc not supported");
        return FALSE;
    }
    ASSERT(m_pINotifySrc);
    m_dwRef--;
    ASSERT(m_dwRef > 0);

    return TRUE;
}
