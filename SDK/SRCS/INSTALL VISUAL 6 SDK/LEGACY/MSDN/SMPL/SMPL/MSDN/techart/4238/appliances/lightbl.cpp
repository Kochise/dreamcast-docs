// lightbl.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\impiunk.h"
#include "Appliances.h"
#include "..\include\appliancesid.h"
#include "..\include\ibitmap.h"
#include "..\include\idrawing.h"
#include "..\include\ioutlet.h"
#include "..\include\inotify.h"
#include "..\include\inotifysrc.h"
#include "resource.h"
#include "lightbl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLightBulb

IMPLEMENT_DYNCREATE(CLightBulb, CCmdTarget)

CLightBulb::CLightBulb()
{
	TRACE("CLightBulb::CLightBulb()\n");
	m_punkBitmap = NULL;
    m_pIBitmap = NULL;
    m_bIsOn = FALSE; // off
    m_punkNotifyList = NULL;
    m_pINotifySrc = NULL;

	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CLightBulb::~CLightBulb()
{
	TRACE("CLightBulb::~CLightBulb()\n");
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void CLightBulb::OnFinalRelease()
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


BEGIN_MESSAGE_MAP(CLightBulb, CCmdTarget)
	//{{AFX_MSG_MAP(CLightBulb)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLightBulb, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CLightBulb)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Add class factory support
IMPLEMENT_OLECREATE(CLightBulb, "LightBulb", 0x3a015b30, 0x41fc, 0x11ce, 0x9e, 0xe5, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf)

BEGIN_INTERFACE_MAP(CLightBulb, CCmdTarget)
    INTERFACE_PART(CLightBulb, IID_IOutlet, Outlet)
    INTERFACE_AGGREGATE(CLightBulb, m_punkBitmap)
    INTERFACE_AGGREGATE(CLightBulb, m_punkNotifyList)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////
// IOutlet

// IUnknown for IOutlet
    IMPLEMENT_IUNKNOWN(CLightBulb, Outlet)

// IOutlet methods
STDMETHODIMP CLightBulb::XOutlet::On()
{
    METHOD_PROLOGUE(CLightBulb, Outlet);
    pThis->SetState(TRUE);
    return NOERROR;
}

STDMETHODIMP CLightBulb::XOutlet::Off()
{
    METHOD_PROLOGUE(CLightBulb, Outlet);
    pThis->SetState(FALSE);
    return NOERROR;
}

STDMETHODIMP CLightBulb::XOutlet::GetState(BOOL* pState)
{
    METHOD_PROLOGUE(CLightBulb, Outlet);
    if (!pState) return E_INVALIDARG;
    *pState = pThis->m_bIsOn;
    return NOERROR;
}

BOOL CLightBulb::OnCreateAggregates()
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

    if (m_pIBitmap->LoadResource(IDR_DIB_LIGHTBULB) != S_OK) {
        TRACE("Failed to load bitmap resource\n");
    }

    // Set the the initial brightness level so we will get the
    // correct image clipping
    SetState(FALSE);

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

///////////////////////////////////////////////////////////////////////////////
// Helpers

void CLightBulb::SetState(BOOL bState)
{
    m_bIsOn = bState;

    // Adjust the image clipping region so we show the 
    // correct image
    CRect rcClip;
    m_pIBitmap->GetRect(&rcClip);
    int w = (rcClip.right - rcClip.left + 1) / 2;
    if (m_bIsOn) {
        rcClip.left += w;
    }
    rcClip.right = rcClip.left + w;
    m_pIBitmap->SetClipRect(&rcClip);    

    // Send change notification
    if (m_pINotifySrc) {
        m_pINotifySrc->NotifyAll();
    }
}
