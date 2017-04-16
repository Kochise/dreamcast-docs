#include "stdafx.h"
#include "combase.h"
#include "..\include\idrawing.h"
#include "..\include\ibitmap.h"
#include "resource.h"
#include "CBitmapObject.h"

//
// Constructor
//

CBitmapObject::CBitmapObject(IUnknown* pUnk, HRESULT* phr)
	: CUnknown(pUnk, phr)
{
	m_pPal = NULL;
    m_wResID = 0;
}	 

//
// Destructor
//
CBitmapObject::~CBitmapObject()
{
}

//
// CreateInstance
//
CUnknown* CBitmapObject::CreateInstance(IUnknown* pUnk, HRESULT* phr)
{
	CBitmapObject* pNewObject = new CBitmapObject(pUnk, phr) ;
	if (pNewObject == NULL)
		*phr = E_OUTOFMEMORY ;

	return pNewObject ;
}

//
// Overload To support IDrawing and IBitmap
//
HRESULT __stdcall CBitmapObject::NonDelegatingQueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IBitmap)
		return GetInterface((IBitmap*)this, ppv) ;
	else if (riid == IID_IDrawing)
		return GetInterface((IDrawing*)this, ppv) ;
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
HRESULT __stdcall CBitmapObject::Draw(CDC* pDC, int x, int y)
{
    // Get a copy of the background the same size as the image
    int w = m_dibImage.GetWidth();
    int h = m_dibImage.GetHeight();
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
    BYTE* pPixel = (BYTE*) m_dibImage.GetPixelAddress(0, 0);
    ASSERT(pPixel);

    // Draw the image transparently to the buffer
    m_dibImage.CopyBits(&dsBuffer,
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
HRESULT __stdcall CBitmapObject::SetPalette(CPalette* pPal)
{
    if (!pPal) return E_INVALIDARG;

    m_pPal = pPal;

    // Reload the image and map it to the new palette
    if (m_wResID) {
        if (m_dibImage.Load(m_wResID)) {
            m_dibImage.MapColorsToPalette(m_pPal);
        }
    }

    return NOERROR;
}

//
// GetRect
//
HRESULT __stdcall CBitmapObject::GetRect(CRect* pRect)
{
    if (!pRect) return E_INVALIDARG;

    m_dibImage.GetRect(pRect);

    return NOERROR;
}

//
//
// IBitmap Interface Implementation
//
//
HRESULT __stdcall CBitmapObject::LoadResource(WORD wResID)
{
    if (!m_dibImage.Load(wResID)) {
        TRACE("Failed to load DIB resource\n");
        return E_INVALIDARG;
    }
    // Save the resource id for later
    m_wResID = wResID;

    return NOERROR;
} 
