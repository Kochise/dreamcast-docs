// radio.cpp : implementation file
//

#include "stdafx.h"
#include "..\include\impiunk.h"
#include "appliances.h"
#include "..\include\idrawing.h"
#include "..\include\iapplianceui.h"
#include "resource.h"
#include "radio.h"
#include "radiodlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRadio

IMPLEMENT_DYNCREATE(CRadio, CCmdTarget)

CRadio::CRadio()
{
	TRACE("CRadio::CRadio()\n");
    m_pPal = NULL;
    m_bIsOn = FALSE;
    m_iStation = 1;

    // Load the image
    m_dibImage.Load(IDR_DIB_RADIO);

	EnableAutomation();
	
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	
	AfxOleLockApp();
}

CRadio::~CRadio()
{
	TRACE("CRadio::~CRadio()\n");
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	
	// Make sure the tune stops
    m_mciTune.Stop();

	AfxOleUnlockApp();
}

void CRadio::OnFinalRelease()
{
	// When the last reference for an automation object is released
	//	OnFinalRelease is called.  This implementation deletes the 
	//	object.  Add additional cleanup required for your object before
	//	deleting it from memory.

	delete this;
}


BEGIN_MESSAGE_MAP(CRadio, CCmdTarget)
	//{{AFX_MSG_MAP(CRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CRadio, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CRadio)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

IMPLEMENT_OLECREATE(CRadio, "Radio", 0x44434a20, 0x4374, 0x11ce, 0x9e, 0xe8, 0x0, 0xaa, 0x0, 0x42, 0x31, 0xbf)

BEGIN_INTERFACE_MAP(CRadio, CCmdTarget)
    INTERFACE_PART(CRadio, IID_IDrawing, Drawing)
    INTERFACE_PART(CRadio, IID_IApplianceUI, ApplianceUI)
END_INTERFACE_MAP()

// IUnknown for IDrawing
    IMPLEMENT_IUNKNOWN(CRadio, Drawing)

// IDrawing methods
STDMETHODIMP CRadio::XDrawing::Draw(CDC* pDC, int x, int y)
{
    METHOD_PROLOGUE(CRadio, Drawing);

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

STDMETHODIMP CRadio::XDrawing::SetPalette(CPalette* pPal)
{
    METHOD_PROLOGUE(CRadio, Drawing);

    if (!pPal) return E_INVALIDARG;

    pThis->m_pPal = pPal;

    // Reload the image and map it to the new palette
    pThis->m_dibImage.Load(IDR_DIB_RADIO);
    pThis->m_dibImage.MapColorsToPalette(pThis->m_pPal);

    return NOERROR;
}

STDMETHODIMP CRadio::XDrawing::GetRect(CRect* pRect)
{
    METHOD_PROLOGUE(CRadio, Drawing);

    if (!pRect) return E_INVALIDARG;

    pThis->m_dibImage.GetRect(pRect);

    return NOERROR;
}

// IUnknown for IApplianceUI
    IMPLEMENT_IUNKNOWN(CRadio, ApplianceUI)

// IApplianceUI methods
STDMETHODIMP CRadio::XApplianceUI::ShowControl(CWnd* pParent)
{
    METHOD_PROLOGUE(CRadio, ApplianceUI);
    CRadioDlg* pDlg = new CRadioDlg;
    pDlg->m_pRadio = pThis;
    pDlg->Create(pParent);
    return NOERROR;
}

/////////////////////////////////////////////////////////////////
// Direct object control functions 

void CRadio::Power(BOOL b)
{
    if (b == m_bIsOn) return;
    m_bIsOn = b;

    if (!m_bIsOn) {
        
        // Stop any tune that's playing
        m_mciTune.Stop();

    } else {

        // Play the current selection
        SetStation(m_iStation);
    }
}

BOOL CRadio::SetStation(int iStation)
{
    // radio has four stations 1 - 4
    if ((iStation < 1) || (iStation > 4)) return FALSE;
    m_iStation = iStation;
    if (!m_bIsOn) return TRUE;

    // Start this tune playing
    m_mciTune.Stop();

    char szTune[32];
    sprintf(szTune, "radio%d.mid", m_iStation);
    if (!m_mciTune.OpenFile(szTune)) {
        AfxMessageBox("Station not on the air.\n(Can't find MIDI file.)");
        return FALSE;
    }
    m_mciTune.Play();
    return TRUE;
}

