// lightbl.cpp : implementation file
//

#include "stdafx.h"
#include "Appliances.h"
#include "..\include\idrawing.h"
#include "lightbl.h"
#include "resource.h"

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

    // Load the image
    m_dibImage.Load(IDR_DIB_LIGHTBULB_ON);

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
    TRACE("CLightBulb::XDrawing::QueryInterface\n");
    return pThis->ExternalQueryInterface(&riid, ppVoid);
}

// IDrawing methods
STDMETHODIMP CLightBulb::XDrawing::Draw(CDC* pDC, int x, int y)
{
    METHOD_PROLOGUE(CLightBulb, Drawing);
    TRACE("CLightBulb::XDrawing::Draw");

    // Get a copy of the background the same size as the image
    int w = pThis->m_dibImage.GetWidth();
    int h = pThis->m_dibImage.GetHeight();
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
    BYTE* pPixel = (BYTE*) pThis->m_dibImage.GetPixelAddress(0, 0);
    ASSERT(pPixel);

    // Draw the image transparently to the buffer
    pThis->m_dibImage.CopyBits(&dsBuffer,
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
    TRACE("CLightBulb::XDrawing::SetPalette");

    if (!pPal) return E_INVALIDARG;

    pThis->m_pPal = pPal;

    // Reload the image and map it to the new palette
    pThis->m_dibImage.Load(IDR_DIB_LIGHTBULB_ON);
    pThis->m_dibImage.MapColorsToPalette(pThis->m_pPal);

    return NOERROR;
}
