// standard.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\impiunk.h"
#include "appliances.h"
#include "..\include\appliancesid.h"
#include "..\include\ibitmap.h"
#include "..\include\ioutlet.h"
#include "..\include\ilight.h"
#include "..\include\inotify.h"
#include "..\include\inotifysrc.h"
#include "resource.h"
#include "standard.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStandardLamp

IMPLEMENT_DYNCREATE(CStandardLamp, CCmdTarget)

CStandardLamp::CStandardLamp()
{
	TRACE("CStandardLamp::CStandardLamp()\n");
    m_bLevel = 0; // off
	m_punkBitmap = NULL;
    m_pIBitmap = NULL;

	EnableAutomation();
    m_punkNotifyList = NULL;
    m_pINotifySrc = NULL;
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CStandardLamp::~CStandardLamp()
{
	TRACE("CStandardLamp::~CStandardLamp()\n");

	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void CStandardLamp::OnFinalRelease()
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


BEGIN_MESSAGE_MAP(CStandardLamp, CCmdTarget)
	//{{AFX_MSG_MAP(CStandardLamp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CStandardLamp, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CStandardLamp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CStandardLamp, "StandardLamp", 0x44434a24, 0x4374, 0x11ce, 0x9e, 0xe8, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf)

BEGIN_INTERFACE_MAP(CStandardLamp, CCmdTarget)
    INTERFACE_PART(CStandardLamp, IID_IOutlet, Outlet)
    INTERFACE_PART(CStandardLamp, IID_ILight, Light)
    INTERFACE_AGGREGATE(CStandardLamp, m_punkNotifyList)
    INTERFACE_AGGREGATE(CStandardLamp, m_punkBitmap)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////
// IOutlet interface

// IUnknown for IOutlet
    IMPLEMENT_IUNKNOWN(CStandardLamp, Outlet)

// IOutlet methods
STDMETHODIMP CStandardLamp::XOutlet::On()
{
    METHOD_PROLOGUE(CStandardLamp, Outlet);
    pThis->SetLevel(255);
    return NOERROR;
}

STDMETHODIMP CStandardLamp::XOutlet::Off()
{
    METHOD_PROLOGUE(CStandardLamp, Outlet);
    pThis->SetLevel(0);
    return NOERROR;
}

STDMETHODIMP CStandardLamp::XOutlet::GetState(BOOL* pState)
{
    METHOD_PROLOGUE(CStandardLamp, Outlet);
    if (!pState) return E_INVALIDARG;
    *pState = (pThis->m_bLevel > 0) ? TRUE : FALSE;
    return NOERROR;
}

/////////////////////////////////////////////////////////
// ILight interface

// IUnknown for ILight
    IMPLEMENT_IUNKNOWN(CStandardLamp, Light)

// ILight methods
STDMETHODIMP CStandardLamp::XLight::SetBrightness(BYTE bLevel)
{
    METHOD_PROLOGUE(CStandardLamp, Light);
    pThis->SetLevel(bLevel);
    return NOERROR;
}

STDMETHODIMP CStandardLamp::XLight::GetBrightness(BYTE* pLevel)
{
    METHOD_PROLOGUE(CStandardLamp, Light);
    if (!pLevel) return E_INVALIDARG;
    *pLevel = pThis->m_bLevel;
    return NOERROR;
}

////////////////////////////////////////////////////////////////////////////
// 4:Aggregation

BOOL CStandardLamp::OnCreateAggregates()
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

    if (m_pIBitmap->LoadResource(IDR_DIB_STDLAMP) != S_OK) {
        TRACE("Failed to load bitmap resource\n");
    }

    // Set the the initial brightness level so we will get the
    // correct image clipping
    SetLevel(0);

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

void CStandardLamp::SetLevel(BYTE bLevel)
{
    ASSERT((bLevel >= 0) && (bLevel <= 255));
    m_bLevel = bLevel;

    // Adjust the image clipping region so we show the 
    // correct image
    CRect rcClip;
    m_pIBitmap->GetRect(&rcClip);
    int w = (rcClip.right - rcClip.left + 1) / 3;
    if (m_bLevel > 170) {
        rcClip.left += w * 2;
    } else if (m_bLevel > 85) {
        rcClip.left += w;
    }
    rcClip.right = rcClip.left + w;
    m_pIBitmap->SetClipRect(&rcClip);    

    // Send change notification
    if (m_pINotifySrc) {
        m_pINotifySrc->NotifyAll();
    }
}
