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
    m_hPal = NULL;
    m_wResID = 0;
    m_rcClip = CRect(0,0,0,0);
	
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

    // Set the clip rect to be the entire image
    pThis->m_dibImage.GetRect(&pThis->m_rcClip);
    return NOERROR;
}

STDMETHODIMP CBitmapObject::XBitmap::GetRect(RECT* pRect)
{
    METHOD_PROLOGUE(CBitmapObject, Bitmap);
    if (!pRect) return E_INVALIDARG;
    pThis->m_dibImage.GetRect(pRect);
    return NOERROR;
}

STDMETHODIMP CBitmapObject::XBitmap::SetClipRect(RECT* pClipRect)
{
    METHOD_PROLOGUE(CBitmapObject, Bitmap);
    if (!pClipRect) return E_INVALIDARG;

    // make sure the requested clip rect is within the 
    // bounding rect of the image
    CRect rcImage;
    pThis->m_dibImage.GetRect(&rcImage);
    if ((pClipRect->left >= rcImage.left)
    &&  (pClipRect->top >= rcImage.top)
    &&  (pClipRect->right <= rcImage.right)
    &&  (pClipRect->bottom <= rcImage.bottom)) {
        pThis->m_rcClip = *pClipRect;
        return NOERROR;
    }
    return E_INVALIDARG;
}

STDMETHODIMP CBitmapObject::XBitmap::GetClipRect(RECT* pClipRect)
{
    METHOD_PROLOGUE(CBitmapObject, Bitmap);
    if (!pClipRect) return E_INVALIDARG;
    *pClipRect = pThis->m_rcClip;
    return NOERROR;
}

/////////////////////////////////////////////////////////
// IDrawing interface

// IUnknown for IDrawing
    IMPLEMENT_IUNKNOWN(CBitmapObject, Drawing)

// IDrawing methods
STDMETHODIMP CBitmapObject::XDrawing::Draw(HDC hDC, int x, int y)
{
    METHOD_PROLOGUE(CBitmapObject, Drawing);

    // Get a copy of the background the same size as the image
    int w = pThis->m_rcClip.Width();
    int h = pThis->m_rcClip.Height();
    CDC dc;
    dc.Attach(hDC);
    CDIBSurface dsBuffer;
    CPalette* pTempPal = CPalette::FromHandle(pThis->m_hPal);
    dsBuffer.Create(w, h, pTempPal);
    CDC* pDCBuf = dsBuffer.GetDC();
    CPalette* pOldPal = NULL;
    pDCBuf->SelectPalette(pTempPal, FALSE);
    pDCBuf->RealizePalette();
    pDCBuf->BitBlt(0, 0,
                   w, h,
                   &dc,
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
                                pThis->m_rcClip.left, pThis->m_rcClip.top,
                                PALETTEINDEX(*pPixel));

    // Now copy the composite image back to the main DC
    ::BitBlt(hDC,
             x, y,
             w, h,
             pDCBuf->GetSafeHdc(),
             0, 0,
             SRCCOPY);

    // tidy up
    if (pOldPal) pDCBuf->SelectPalette(pOldPal, FALSE);

    // detach the dc from the CDC obejct so the dc won't get
    // destroyed when the CDC object is destroyed
    dc.Detach();

    return NOERROR;
}    

STDMETHODIMP CBitmapObject::XDrawing::SetPalette(HPALETTE hPal)
{
    METHOD_PROLOGUE(CBitmapObject, Drawing);

    if (!hPal) return E_INVALIDARG;

    pThis->m_hPal = hPal;

    // Reload the image and map it to the new palette
    if (pThis->m_wResID) {
        if (pThis->m_dibImage.Load(pThis->m_wResID)) {
            pThis->m_dibImage.MapColorsToPalette(CPalette::FromHandle(pThis->m_hPal));
        }
    }

    return NOERROR;
}

STDMETHODIMP CBitmapObject::XDrawing::GetRect(RECT* pRect)
{
    METHOD_PROLOGUE(CBitmapObject, Drawing);

    if (!pRect) return E_INVALIDARG;

    *pRect = pThis->m_rcClip;

    return NOERROR;
}

