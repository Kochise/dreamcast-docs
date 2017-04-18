
#include "stdafx.h"
#include "combase.h"
#include "..\include\idrawing.h"
#include "..\include\ioutlet.h"
#include "resource.h"
#include "CLightBulb.h"

//
// Constructor
//
CLightBulb::CLightBulb(IUnknown* pUnk, HRESULT* phr)
	: CUnknown(pUnk, phr) 
{
    m_pPal = NULL;
    m_bIsOn = FALSE; // off

    // Load the image
    m_dibImageOn.Load(IDR_DIB_LIGHTBULB_ON);
    m_dibImageOff.Load(IDR_DIB_LIGHTBULB_OFF);
}

//
// Destructor
//
CLightBulb::~CLightBulb()
{
}

//
// CreateInstance is called by CClassFactory
//
CUnknown* CLightBulb::CreateInstance(IUnknown* pUnk, HRESULT* phr)
{
	CLightBulb* pNewObject = new CLightBulb(pUnk, phr) ;
	if (pNewObject == NULL)
		*phr = E_OUTOFMEMORY ;

	return pNewObject ;
}

// Overload To support IDrawing and IOutlet
HRESULT CLightBulb::NonDelegatingQueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IOutlet)
	{
		return GetInterface((IOutlet*)this, ppv) ;
	}
	else if (riid == IID_IDrawing)
	{
		return GetInterface((IDrawing*)this, ppv) ;
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
HRESULT CLightBulb::Draw(CDC* pDC, int x, int y)
{
    // Get a copy of the background the same size as the image
    CDIB* pDIB = m_bIsOn ? &m_dibImageOn : &m_dibImageOff;
    
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
HRESULT CLightBulb::SetPalette(CPalette* pPal)
{
    if (!pPal) return E_INVALIDARG;

    m_pPal = pPal;

    // Reload the image and map it to the new palette
    m_dibImageOn.Load(IDR_DIB_LIGHTBULB_ON);
    m_dibImageOn.MapColorsToPalette(m_pPal);
    m_dibImageOff.Load(IDR_DIB_LIGHTBULB_OFF);
    m_dibImageOff.MapColorsToPalette(m_pPal);

    return NOERROR;
}

//
// GetRect
//
HRESULT CLightBulb::GetRect(CRect* pRect)
{
    if (!pRect) return E_INVALIDARG;

    CDIB* pDIB = m_bIsOn ? &m_dibImageOn : &m_dibImageOff;
    pDIB->GetRect(pRect);

    return NOERROR;
}

//
//
// IOutlet Interface Implementation
//
//
HRESULT CLightBulb::On()
{
    m_bIsOn = TRUE;
    return NOERROR;
}

HRESULT CLightBulb::Off()
{
    m_bIsOn = FALSE;
    return NOERROR;
}

HRESULT CLightBulb::GetState(BOOL* pState)
{
    if (!pState) return E_INVALIDARG;
    *pState = m_bIsOn;
    return NOERROR;
}



