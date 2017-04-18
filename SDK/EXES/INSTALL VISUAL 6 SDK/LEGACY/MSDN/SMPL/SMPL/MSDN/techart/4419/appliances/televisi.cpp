// televisi.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\impiunk.h"
#include "appliances.h"
#include "..\include\idrawing.h"
#include "..\include\iapplianceui.h"
#include "resource.h"
#include "televisi.h"
#include "tvdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTelevision

IMPLEMENT_DYNCREATE(CTelevision, CCmdTarget)

CTelevision::CTelevision()
{
	TRACE("CTelevision::CTelevision()\n");
    m_pPal = NULL;
    m_bIsOn = FALSE;

    // Load the image
    m_dibImage.Load(IDR_DIB_TV);

	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CTelevision::~CTelevision()
{
	TRACE("CTelevision::~CTelevision()\n");
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	AfxOleUnlockApp();
}

void CTelevision::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CTelevision, CCmdTarget)
	//{{AFX_MSG_MAP(CTelevision)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CTelevision, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CTelevision)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CTelevision, "Television", 0x44434a22, 0x4374, 0x11ce, 0x9e, 0xe8, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf)

BEGIN_INTERFACE_MAP(CTelevision, CCmdTarget)
    INTERFACE_PART(CTelevision, IID_IDrawing, Drawing)
    INTERFACE_PART(CTelevision, IID_IApplianceUI, ApplianceUI)
END_INTERFACE_MAP()

// IUnknown for IDrawing
    IMPLEMENT_IUNKNOWN(CTelevision, Drawing)

// IDrawing methods
STDMETHODIMP CTelevision::XDrawing::Draw(CDC* pDC, int x, int y)
{
    METHOD_PROLOGUE(CTelevision, Drawing);

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

STDMETHODIMP CTelevision::XDrawing::SetPalette(CPalette* pPal)
{
    METHOD_PROLOGUE(CTelevision, Drawing);

    if (!pPal) return E_INVALIDARG;

    pThis->m_pPal = pPal;

    // Reload the image and map it to the new palette
    pThis->m_dibImage.Load(IDR_DIB_TV);
    pThis->m_dibImage.MapColorsToPalette(pThis->m_pPal);

    return NOERROR;
}

STDMETHODIMP CTelevision::XDrawing::GetRect(CRect* pRect)
{
    METHOD_PROLOGUE(CTelevision, Drawing);

    if (!pRect) return E_INVALIDARG;

    pThis->m_dibImage.GetRect(pRect);

    return NOERROR;
}

// IUnknown for IApplianceUI
    IMPLEMENT_IUNKNOWN(CTelevision, ApplianceUI)

// IApplianceUI methods
STDMETHODIMP CTelevision::XApplianceUI::ShowControl(CWnd* pParent)
{
    METHOD_PROLOGUE(CTelevision, ApplianceUI);
    CTelevisionDlg* pDlg = new CTelevisionDlg;
    pDlg->m_pTV = pThis;
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
