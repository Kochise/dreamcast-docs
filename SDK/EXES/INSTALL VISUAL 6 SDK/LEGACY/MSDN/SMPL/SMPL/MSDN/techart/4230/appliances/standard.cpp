// standard.cpp : implementation file
//

#include "stdafx.h"
#include "impiunk.h"
#include "appliances.h"
#include "..\include\idrawing.h"
#include "..\include\ioutlet.h"
#include "..\include\ilight.h"
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
    m_pPal = NULL;
    m_bLevel = 0; // off

    // Load the images
    m_dibImageOff.Load(IDR_DIB_STDLAMP_OFF);
    m_dibImageDim.Load(IDR_DIB_STDLAMP_DIM);
    m_dibImageBright.Load(IDR_DIB_STDLAMP_BRIGHT);

	EnableAutomation();
	
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
    INTERFACE_PART(CStandardLamp, IID_IDrawing, Drawing)
    INTERFACE_PART(CStandardLamp, IID_IOutlet, Outlet)
    INTERFACE_PART(CStandardLamp, IID_ILight, Light)
END_INTERFACE_MAP()

//////////////////////////////////////////////////////////////////////////////
// IDrawing interface

// IUnknown for IDrawing
    IMPLEMENT_IUNKNOWN(CStandardLamp, Drawing)

// IDrawing methods
STDMETHODIMP CStandardLamp::XDrawing::Draw(CDC* pDC, int x, int y)
{
    METHOD_PROLOGUE(CStandardLamp, Drawing);

    // See which image to use
    CDIB* pDIB;
    if (pThis->m_bLevel > 127) {
        pDIB = &pThis->m_dibImageBright;
    } else if (pThis->m_bLevel > 0) {
        pDIB = &pThis->m_dibImageDim;
    } else {
        pDIB = &pThis->m_dibImageOff;
    }

    // Get a copy of the background the same size as the image
    int w = pDIB->GetWidth();
    int h = pDIB->GetHeight();
    CDIBSurface dsBuffer;
    dsBuffer.Create(w, h, pThis->m_pPal);
    CDC* pDCBuf = dsBuffer.GetDC();
    CPalette* pOldPal = NULL;
    if (pThis->m_pPal) {
        pDCBuf->SelectPalette(pThis->m_pPal, FALSE);
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

STDMETHODIMP CStandardLamp::XDrawing::SetPalette(CPalette* pPal)
{
    METHOD_PROLOGUE(CStandardLamp, Drawing);

    if (!pPal) return E_INVALIDARG;

    pThis->m_pPal = pPal;

    // Reload the images and map them to the new palette
    pThis->m_dibImageBright.Load(IDR_DIB_STDLAMP_BRIGHT);
    pThis->m_dibImageDim.Load(IDR_DIB_STDLAMP_DIM);
    pThis->m_dibImageOff.Load(IDR_DIB_STDLAMP_OFF);
    pThis->m_dibImageBright.MapColorsToPalette(pThis->m_pPal);
    pThis->m_dibImageDim.MapColorsToPalette(pThis->m_pPal);
    pThis->m_dibImageOff.MapColorsToPalette(pThis->m_pPal);

    return NOERROR;
}

STDMETHODIMP CStandardLamp::XDrawing::GetRect(CRect* pRect)
{
    METHOD_PROLOGUE(CStandardLamp, Drawing);

    if (!pRect) return E_INVALIDARG;

    // See which image to use
    CDIB* pDIB;
    if (pThis->m_bLevel > 127) {
        pDIB = &pThis->m_dibImageBright;
    } else if (pThis->m_bLevel > 0) {
        pDIB = &pThis->m_dibImageDim;
    } else {
        pDIB = &pThis->m_dibImageOff;
    }
    pDIB->GetRect(pRect);

    return NOERROR;
}

/////////////////////////////////////////////////////////
// IOutlet interface

// IUnknown for IOutlet
    IMPLEMENT_IUNKNOWN(CStandardLamp, Outlet)

// IOutlet methods
STDMETHODIMP CStandardLamp::XOutlet::On()
{
    METHOD_PROLOGUE(CStandardLamp, Outlet);
    pThis->m_bLevel = 255;
    return NOERROR;
}

STDMETHODIMP CStandardLamp::XOutlet::Off()
{
    METHOD_PROLOGUE(CStandardLamp, Outlet);
    pThis->m_bLevel = 0;
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
    pThis->m_bLevel = bLevel;
    return NOERROR;
}

STDMETHODIMP CStandardLamp::XLight::GetBrightness(BYTE* pLevel)
{
    METHOD_PROLOGUE(CStandardLamp, Light);
    if (!pLevel) return E_INVALIDARG;
    *pLevel = pThis->m_bLevel;
    return NOERROR;
}
