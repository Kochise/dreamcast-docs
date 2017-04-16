// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "House.h"

#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    m_pLightBulb1 = NULL;
    m_pLightBulb2 = NULL;
}

CMainFrame::~CMainFrame()
{
    if (m_pLightBulb1) {
        delete m_pLightBulb1;
        m_pLightBulb1 = NULL;
    }
    if (m_pLightBulb2) {
        m_pLightBulb2->Release();
        m_pLightBulb2 = NULL;
    }
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
    // Load the background image
    m_dibBkgnd.Load(IDR_DIB_BKGND);

    // Create a palette from the image
    m_pal.Create(&m_dibBkgnd);

    // create the main room light bulb object
    dprintf2("Creating C++ lightbulb");
    m_pLightBulb1 = new CLightBulb;
    ASSERT(m_pLightBulb1);
    m_pLightBulb1->Create(IDR_DIB_LIGHTBULB_ON, &m_pal);

    // Initialize the OLE support
    BOOL b = AfxOleInit();
    ASSERT(b);

    // create a COM light bulb for one of the other rooms
    dprintf2("Creating COM lightbulb");
    HRESULT hr = ::CoCreateInstance(CLSID_LightBulb,
                                    NULL,
                                    CLSCTX_INPROC_SERVER,
                                    IID_IUnknown,
                                    (LPVOID*)&m_pLightBulb2);
    if (FAILED(hr)) {
        dprintf1("Failed to create object. SCODE: %8.8lXH (%lu)\n",
              GetScode(hr),
              GetScode(hr) & 0x0000FFFF);
        m_pLightBulb2 = NULL;
    }
    ASSERT(m_pLightBulb2);

    // Get a pointer to the IDrawing interface
    IDrawing* pIDrawing = NULL;
    if (m_pLightBulb2->QueryInterface(IID_IDrawing, (LPVOID*)&pIDrawing) == S_OK) {

        // Give the COM object a pointer to our palette
        pIDrawing->SetPalette(&m_pal);

        // free the interface
        pIDrawing->Release();
    } else {
        dprintf1("Failed to set palette in COM object");
    }

	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnPaletteChanged(CWnd* pFocusWnd) 
{
    // See if the change was caused by us and ignore it if not
    if (pFocusWnd != this) {
        OnQueryNewPalette();
    }
}

BOOL CMainFrame::OnQueryNewPalette() 
{
    // We are going active so realize our palette
    CDC* pdc = GetDC();
    CPalette *poldpal = pdc->SelectPalette(&m_pal, FALSE);
    UINT u = pdc->RealizePalette();
    ReleaseDC(pdc);
    if (u != 0) {
        // some colors changed so we need to do a repaint
        InvalidateRect(NULL, TRUE); // repaint the lot
        return TRUE; // say we did something
    }
    return FALSE; // say we did nothing
}


BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) 
{
    // We simply draw the background bitmap to the DC
    CPalette *pOldPal = pDC->SelectPalette(&m_pal, FALSE);
    pDC->RealizePalette();
    m_dibBkgnd.Draw(pDC, 0, 0);
    pDC->SelectPalette(pOldPal, FALSE);
    return TRUE;
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
    if (IsIconic()) return;

    // Resize the parent window so that the client area
    // is just big enough for the picture.
    CRect rcWnd;
    GetWindowRect(&rcWnd);
    CRect rcClient;
    GetClientRect(&rcClient);
    int w = m_dibBkgnd.GetWidth();
    int h = m_dibBkgnd.GetHeight();

    rcWnd.right += w - (rcClient.right - rcClient.left);
    rcWnd.bottom += h - (rcClient.bottom - rcClient.top);
    MoveWindow(rcWnd.left,
                rcWnd.top,
                rcWnd.right - rcWnd.left,
                rcWnd.bottom - rcWnd.top,
                TRUE);
}


void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
    CPalette* pOldPal = dc.SelectPalette(&m_pal, FALSE);
    dc.RealizePalette();
	
    // Ask the main room light bulb to draw itself
    if (m_pLightBulb1) {
        m_pLightBulb1->Draw(&dc, 186, 247);
    }

    // Ask the top left room light bulb to draw itself
    if (m_pLightBulb2) {

        // Get a pointer to the IDrawing interface
        IDrawing* pIDrawing = NULL;
        if (m_pLightBulb2->QueryInterface(IID_IDrawing, (LPVOID*)&pIDrawing) == S_OK) {

            // Ask it to draw
            ASSERT(pIDrawing);
            if (pIDrawing->Draw(&dc, 135, 121) != S_OK) {
                dprintf1("IDrawing::Draw failed");
            }

            // Release the interface
            pIDrawing->Release();
        } else {

            dprintf1("No IDrawing interface found");
        }
    }

    dc.SelectPalette(pOldPal, FALSE);
}
