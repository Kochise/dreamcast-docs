// lightbl.cpp : implementation file
//

#include "stdafx.h"
#include "Appliances.h"
#include "..\include\idrawing.h"
#include "..\include\ioutlet.h"
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
    m_pPal = NULL;
    m_bIsOn = FALSE; // off

    // Load the image
    m_dibImageOn.Load(IDR_DIB_LIGHTBULB_ON);
    m_dibImageOff.Load(IDR_DIB_LIGHTBULB_OFF);

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
    INTERFACE_PART(CLightBulb, IID_IDrawing, Drawing)
    INTERFACE_PART(CLightBulb, IID_IOutlet, Outlet)
END_INTERFACE_MAP()

// IUnknown for IDrawing
STDMETHODIMP_(ULONG) CLightBulb::XDrawing::AddRef(void)
{
    METHOD_PROLOGUE(CLightBulb, Drawing);
    return pThis->ExternalAddRef();
}
 
STDMETHODIMP_(ULONG) CLightBulb::XDrawing::Release(void)
{
    METHOD_PROLOGUE(CLightBulb, Drawing);
    return pThis->ExternalRelease();
}

STDMETHODIMP CLightBulb::XDrawing::QueryInterface(REFIID riid, LPVOID* ppVoid)
{
    METHOD_PROLOGUE(CLightBulb, Drawing);
    return pThis->ExternalQueryInterface(&riid, ppVoid);
}

// IDrawing methods
STDMETHODIMP CLightBulb::XDrawing::Draw(CDC* pDC, int x, int y)
{
    METHOD_PROLOGUE(CLightBulb, Drawing);

    // Get a copy of the background the same size as the image
    CDIB* pDIB = pThis->m_bIsOn ? &pThis->m_dibImageOn : &pThis->m_dibImageOff;
    
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

STDMETHODIMP CLightBulb::XDrawing::SetPalette(CPalette* pPal)
{
    METHOD_PROLOGUE(CLightBulb, Drawing);

    if (!pPal) return E_INVALIDARG;

    pThis->m_pPal = pPal;

    // Reload the image and map it to the new palette
    pThis->m_dibImageOn.Load(IDR_DIB_LIGHTBULB_ON);
    pThis->m_dibImageOn.MapColorsToPalette(pThis->m_pPal);
    pThis->m_dibImageOff.Load(IDR_DIB_LIGHTBULB_OFF);
    pThis->m_dibImageOff.MapColorsToPalette(pThis->m_pPal);

    return NOERROR;
}

STDMETHODIMP CLightBulb::XDrawing::GetRect(CRect* pRect)
{
    METHOD_PROLOGUE(CLightBulb, Drawing);

    if (!pRect) return E_INVALIDARG;

    CDIB* pDIB = pThis->m_bIsOn ? &pThis->m_dibImageOn : &pThis->m_dibImageOff;
    pDIB->GetRect(pRect);

    return NOERROR;
}

/////////////////////////////////////////////////////////
// IOutlet

// IUnknown for IOutlet
STDMETHODIMP_(ULONG) CLightBulb::XOutlet::AddRef(void)
{
    METHOD_PROLOGUE(CLightBulb, Outlet);
    return pThis->ExternalAddRef();
}
 
STDMETHODIMP_(ULONG) CLightBulb::XOutlet::Release(void)
{
    METHOD_PROLOGUE(CLightBulb, Outlet);
    return pThis->ExternalRelease();
}

STDMETHODIMP CLightBulb::XOutlet::QueryInterface(REFIID riid, LPVOID* ppVoid)
{
    METHOD_PROLOGUE(CLightBulb, Outlet);
    return pThis->ExternalQueryInterface(&riid, ppVoid);
}

// IOutlet methods
STDMETHODIMP CLightBulb::XOutlet::On()
{
    METHOD_PROLOGUE(CLightBulb, Outlet);
    pThis->m_bIsOn = TRUE;
    return NOERROR;
}

STDMETHODIMP CLightBulb::XOutlet::Off()
{
    METHOD_PROLOGUE(CLightBulb, Outlet);
    pThis->m_bIsOn = FALSE;
    return NOERROR;
}

STDMETHODIMP CLightBulb::XOutlet::GetState(BOOL* pState)
{
    METHOD_PROLOGUE(CLightBulb, Outlet);
    if (!pState) return E_INVALIDARG;
    *pState = pThis->m_bIsOn;
    return NOERROR;
}

