
#include "stdafx.h"
#include "COMBASE.h"
//#include "appliances.h"
#include "..\include\idrawing.h"
#include "..\include\iapplianceui.h"
#include "resource.h"
#include "CTelevision.h"
#include "tvdlg.h"

//
// Constructor
//
CTelevision::CTelevision(IUnknown* pUnk, HRESULT* phr)
	: CUnknown(pUnk, phr) 
{
    m_pPal = NULL;
    m_bIsOn = FALSE;

    // Load the image
    m_dibImage.Load(IDR_DIB_TV);
}

//
// Destructor
//
CTelevision::~CTelevision() 
{
}

//
// CreateInstance is called by CClassFactory
//
CUnknown* CTelevision::CreateInstance(IUnknown* pUnk, HRESULT* phr)
{
	CTelevision* pNewObject = new CTelevision(pUnk, phr) ;
	if (pNewObject == NULL)
		*phr = E_OUTOFMEMORY ;

	return pNewObject ;
}


// Overload To support IDrawing and IApplianceUI
HRESULT __stdcall CTelevision::NonDelegatingQueryInterface(REFIID riid, void** ppv)
{
	if (riid == IID_IApplianceUI)
	{
		return GetInterface((IApplianceUI*)this, ppv) ;
	}
	else if  (riid == IID_IDrawing)
	{
		return GetInterface((IDrawing*)this, ppv) ;
	}
	else
	{
		return CUnknown::NonDelegatingQueryInterface(riid, ppv) ;
	}
}

//
//
// IDrawing methods
//
//

//
// Draw
//
STDMETHODIMP CTelevision::Draw(CDC* pDC, int x, int y)
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
    m_dibImage.CopyBits(		&dsBuffer,
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
STDMETHODIMP CTelevision::SetPalette(CPalette* pPal)
{
    if (!pPal) return E_INVALIDARG;

    m_pPal = pPal;

    // Reload the image and map it to the new palette
    m_dibImage.Load(IDR_DIB_TV);
    m_dibImage.MapColorsToPalette(m_pPal);

    return NOERROR;
}

//
// GetRect
//
STDMETHODIMP CTelevision::GetRect(CRect* pRect)
{
    if (!pRect) return E_INVALIDARG;

    m_dibImage.GetRect(pRect);

    return NOERROR;
}

//
//
// IApplianceUI methods
//
//

STDMETHODIMP CTelevision::ShowControl(CWnd* pParent)
{
    CTelevisionDlg* pDlg = new CTelevisionDlg;
    pDlg->m_pTV = this;
    pDlg->Create(pParent);
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
    return TRUE;
}
