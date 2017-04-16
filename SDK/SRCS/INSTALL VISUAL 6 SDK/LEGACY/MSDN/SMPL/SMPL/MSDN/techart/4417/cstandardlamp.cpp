#include "stdafx.h"
#include "combase.h"
#include "..\include\appliancesid.h"
#include "..\include\idrawing.h"
#include "..\include\ioutlet.h"
#include "..\include\ilight.h"
#include "..\include\inotify.h"
#include "..\include\inotifysrc.h"
#include "resource.h"
#include "CStandardLamp.h"

//
// Constructor
//
CStandardLamp::CStandardLamp(IUnknown* pUnk, HRESULT* phr)
	: CUnknown(pUnk, phr) 
{
    m_pPal = NULL;
    m_bLevel = 0; // off

    // Load the images
    m_dibImageOff.Load(IDR_DIB_STDLAMP_OFF);
    m_dibImageDim.Load(IDR_DIB_STDLAMP_DIM);
    m_dibImageBright.Load(IDR_DIB_STDLAMP_BRIGHT);

    m_punkNotifyList = NULL;
    m_pINotifySrc = NULL;
}

//
// Destructor
//
CStandardLamp::~CStandardLamp()
{

	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	// Release the aggregated object interfaces
    // We add a ref count to our own counter here to
    // prevent our destructor from being called again.
    m_RefCount++;

    // We then add one ref count for each cached interface pointer
    // we created for our aggregated objects.

    ASSERT(m_pINotifySrc);
    m_RefCount++;

    m_pINotifySrc->Release();

    ASSERT(m_punkNotifyList);
    m_punkNotifyList->Release();
}

//
// CreateInstance is called by CClassFactory
//
CUnknown* CStandardLamp::CreateInstance(IUnknown* pUnk, HRESULT* phr)
{
	CStandardLamp* pNewObject = new CStandardLamp(pUnk, phr) ;
	if (pNewObject == NULL)
		*phr = E_OUTOFMEMORY ;

	return pNewObject ;
}

//
// OnInit
//
BOOL CStandardLamp::OnInit()
{
    // Create the objects we want to aggregate
    HRESULT hr = ::CoCreateInstance(CLSID_NotifyListObject,
                                    GetOwner(), 
                                    CLSCTX_INPROC_SERVER,
                                    IID_IUnknown,
                                    (void**)&m_punkNotifyList);
    if (FAILED(hr)) {
        TRACE("Failed to create object. SCODE: %8.8lXH (%lu)\n",
              GetScode(hr),
              GetScode(hr) & 0x0000FFFF);
        m_punkNotifyList = NULL;
        return FALSE;
    }
    ASSERT(m_punkNotifyList);

    // get a pointer to the object's INotifySrc interface
    // so we won't have to get this every time we want to use it
    if (m_punkNotifyList->QueryInterface(IID_INotifySrc, (void**)&m_pINotifySrc) != S_OK)
    {
        TRACE("INotifySrc not supported");
        return FALSE;
    }
    ASSERT(m_pINotifySrc);

    // When we got the INotifySrc pointer, this caused our main object
    // ref count to be incremented by one (because the notify src list
    // object is aggregated).  We don't want this extra ref count so
    // we manually remove it. (Yes I know this doesn't look very kosher)
    m_RefCount-- ;
    ASSERT(m_RefCount > 0);

    return TRUE;	
}


// Overload To support IDrawing, ILight, and IOutlet
// INotifySrc support via aggregation.
HRESULT __stdcall CStandardLamp::NonDelegatingQueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IOutlet)
		return GetInterface((IOutlet*)this, ppv) ;
	else if (riid == IID_IDrawing)
		return GetInterface((IDrawing*)this, ppv) ;
	else if (riid == IID_ILight)
		return GetInterface((ILight*)this, ppv) ;
	else if (riid == IID_INotifySrc)
	{
		TRACE("Aggregated Interface wanted.\r\n") ;
		return GetInterface((IUnknown*)m_pINotifySrc, ppv) ;
	}

	else
		return CUnknown::NonDelegatingQueryInterface(riid, ppv) ;
}

//
//
// IDrawing Interface Implementation
//
//

//
// Draw
//
HRESULT __stdcall CStandardLamp::Draw(CDC* pDC, int x, int y)
{
    // See which image to use
    CDIB* pDIB;
    if (m_bLevel > 127) {
        pDIB = &m_dibImageBright;
    } else if (m_bLevel > 0) {
        pDIB = &m_dibImageDim;
    } else {
        pDIB = &m_dibImageOff;
    }

    // Get a copy of the background the same size as the image
    int w = pDIB->GetWidth();
    int h = pDIB->GetHeight();
    CDIBSurface dsBuffer;
    dsBuffer.Create(w, h, m_pPal);
    CDC* pDCBuf = dsBuffer.GetDC();
    CPalette* pOldPal = NULL;
    if (m_pPal) {
        pDCBuf->SelectPalette(m_pPal, FALSE);
        pDCBuf->RealizePalette();
    }
    pDCBuf->BitBlt(0, 0,
                   w, h,
                   pDC,
                   x, y,
                   SRCCOPY);

    // Flush the GDI queue before we do a direct pixel operation
    ::GdiFlush();

    // Get the palette index of the top left pixel which defines
    // the image transparency color
    BYTE* pPixel = (BYTE*) pDIB->GetPixelAddress(0, 0);
    ASSERT(pPixel);

    // Draw the image transparently to the buffer
    pDIB->CopyBits(&dsBuffer,
                   0, 0,
                   w, h,
                   0, 0,
                   PALETTEINDEX(*pPixel));

    // Now copy the composite image back to the main DC
    pDC->BitBlt(x, y,
                w, h,
                pDCBuf,
                0, 0,
                SRCCOPY);

    // tidy up
    if (pOldPal) pDCBuf->SelectPalette(pOldPal, FALSE);


    return NOERROR;
}

//
// SetPalette
//
HRESULT __stdcall CStandardLamp::SetPalette(CPalette* pPal)
{
    if (!pPal) return E_INVALIDARG;

    m_pPal = pPal;

    // Reload the images and map them to the new palette
    m_dibImageBright.Load(IDR_DIB_STDLAMP_BRIGHT);
    m_dibImageDim.Load(IDR_DIB_STDLAMP_DIM);
    m_dibImageOff.Load(IDR_DIB_STDLAMP_OFF);
    m_dibImageBright.MapColorsToPalette(m_pPal);
    m_dibImageDim.MapColorsToPalette(m_pPal);
    m_dibImageOff.MapColorsToPalette(m_pPal);

    return NOERROR;
}

//
// GetRect
//
HRESULT __stdcall CStandardLamp::GetRect(CRect* pRect)
{
    if (!pRect) return E_INVALIDARG;

    // See which image to use
    CDIB* pDIB;
    if (m_bLevel > 127) {
        pDIB = &m_dibImageBright;
    } else if (m_bLevel > 0) {
        pDIB = &m_dibImageDim;
    } else {
        pDIB = &m_dibImageOff;
    }
    pDIB->GetRect(pRect);

    return NOERROR;
}


//
//
// IOutlet Interface Implementation
//
//

HRESULT __stdcall CStandardLamp::On()
{
    m_bLevel = 255;
    NotifyChange();
    return NOERROR;
}


HRESULT __stdcall CStandardLamp::Off()
{
    m_bLevel = 0;
    NotifyChange();
    return NOERROR;
}

HRESULT __stdcall CStandardLamp::GetState(BOOL* pState)
{
    if (!pState) return E_INVALIDARG;
    *pState = (m_bLevel > 0) ? TRUE : FALSE;
    return NOERROR;
}

//
//
// ILight interface Implementation
//
//

HRESULT __stdcall CStandardLamp::SetBrightness(BYTE bLevel)
{
    m_bLevel = bLevel;
    NotifyChange();
    return NOERROR;
}

HRESULT __stdcall CStandardLamp::GetBrightness(BYTE* pLevel)
{
    if (!pLevel) return E_INVALIDARG;
    *pLevel = m_bLevel;
    return NOERROR;
}

//
// Helper
//
void CStandardLamp::NotifyChange()
{
    ASSERT(m_pINotifySrc);
    m_pINotifySrc->NotifyAll();
}
