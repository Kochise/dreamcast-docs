// bitmapob.cpp : implementation file
//

#include "stdafx.h"
#include "appliances.h"
#include "..\include\impiunk.h"
#include "..\include\ibitmap.h"
#include "..\include\idrawing.h"
#include "bitmapob.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapObject

IMPLEMENT_DYNCREATE(CBitmapObject, CCmdTarget)

CBitmapObject::CBitmapObject()
{
	m_pPal = NULL;
    m_wResID = 0;
	
	EnableAutomation();

    // Make this object aggregatable
    EnableAggregation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CBitmapObject::~CBitmapObject()
{
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void CBitmapObject::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CBitmapObject, CCmdTarget)
	//{{AFX_MSG_MAP(CBitmapObject)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CBitmapObject, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CBitmapObject)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CBitmapObject, "BitmapObject", 0xe6a59af2, 0x532e, 0x11ce, 0x9e, 0xf1, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf)

BEGIN_INTERFACE_MAP(CBitmapObject, CCmdTarget)
    INTERFACE_PART(CBitmapObject, IID_IBitmap, Bitmap)
    INTERFACE_PART(CBitmapObject, IID_IDrawing, Drawing)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////
// IBitmap interface

// IUnknown for IBitmap
    IMPLEMENT_IUNKNOWN(CBitmapObject, Bitmap)

// IBitmap methods
STDMETHODIMP CBitmapObject::XBitmap::LoadResource(WORD wResID)
{
    METHOD_PROLOGUE(CBitmapObject, Bitmap);
    if (!pThis->m_dibImage.Load(wResID)) {
        TRACE("Failed to load DIB resource\n");
        return E_INVALIDARG;
    }

    // Save the resource id for later
    pThis->m_wResID = wResID;

    return NOERROR;
}

/////////////////////////////////////////////////////////
// IDrawing interface

// IUnknown for IDrawing
    IMPLEMENT_IUNKNOWN(CBitmapObject, Drawing)

// IDrawing methods
STDMETHODIMP CBitmapObject::XDrawing::Draw(CDC* pDC, int x, int y)
{
    METHOD_PROLOGUE(CBitmapObject, Drawing);

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

STDMETHODIMP CBitmapObject::XDrawing::SetPalette(CPalette* pPal)
{
    METHOD_PROLOGUE(CBitmapObject, Drawing);

    if (!pPal) return E_INVALIDARG;

    pThis->m_pPal = pPal;

    // Reload the image and map it to the new palette
    if (pThis->m_wResID) {
        if (pThis->m_dibImage.Load(pThis->m_wResID)) {
            pThis->m_dibImage.MapColorsToPalette(pThis->m_pPal);
        }
    }

    return NOERROR;
}

STDMETHODIMP CBitmapObject::XDrawing::GetRect(CRect* pRect)
{
    METHOD_PROLOGUE(CBitmapObject, Drawing);

    if (!pRect) return E_INVALIDARG;

    pThis->m_dibImage.GetRect(pRect);

    return NOERROR;
}

