
// mainfrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "House.h"
#include "mainfrm.h"
#include "outletdl.h"
#include "lightdlg.h"

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
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    m_iNumAppliances = 0;
    for (int i = 0; i < MAX_APPLIANCES; i++) {
        m_pAppliance[i] = NULL;
        m_rcAppliance[i] = CRect (0, 0, 0, 0);
    }
    m_pSelectRect = NULL;
}

CMainFrame::~CMainFrame()
{
    for (int i = 0; i < m_iNumAppliances; i++) {
        ASSERT(m_pAppliance[i]);
        m_pAppliance[i]->Release();
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

    // Create an off-screen buffer for flicker-free repaints
    m_dsBuffer.Create(m_dibBkgnd.GetWidth(),
                      m_dibBkgnd.GetHeight(),
                      &m_pal);

    // Initialize the MFC OLE support
    BOOL b = AfxOleInit();
    ASSERT(b);

    // create each appliance object and set its x and y
    // coordinates in the picture
    m_iNumAppliances = 0;
    dprintf2("Creating lightbulb 1");
    CreateAppliance(CLSID_LightBulb,
                    &m_pAppliance[m_iNumAppliances],
                    145, 122,
                    &m_rcAppliance[m_iNumAppliances]);
    if (m_pAppliance[m_iNumAppliances] != NULL) m_iNumAppliances++;

    dprintf2("Creating lightbulb 2");
    CreateAppliance(CLSID_LightBulb,
                    &m_pAppliance[m_iNumAppliances],
                    358, 122,
                    &m_rcAppliance[m_iNumAppliances]);
    if (m_pAppliance[m_iNumAppliances] != NULL) m_iNumAppliances++;
    
    dprintf2("Creating lightbulb 3");
    CreateAppliance(CLSID_LightBulb,
                    &m_pAppliance[m_iNumAppliances],
                    188, 246,
                    &m_rcAppliance[m_iNumAppliances]);
    if (m_pAppliance[m_iNumAppliances] != NULL) m_iNumAppliances++;

    dprintf2("Creating radio");
    CreateAppliance(CLSID_Radio,
                    &m_pAppliance[m_iNumAppliances],
                    63, 180,
                    &m_rcAppliance[m_iNumAppliances]);
    if (m_pAppliance[m_iNumAppliances] != NULL) m_iNumAppliances++;

    dprintf2("Creating television");
    CreateAppliance(CLSID_Television,
                    &m_pAppliance[m_iNumAppliances],
                    107, 299,
                    &m_rcAppliance[m_iNumAppliances]);
    if (m_pAppliance[m_iNumAppliances] != NULL) m_iNumAppliances++;

    dprintf2("Creating standard lamp");
    CreateAppliance(CLSID_StandardLamp,
                    &m_pAppliance[m_iNumAppliances],
                    351, 255,
                    &m_rcAppliance[m_iNumAppliances]);
    if (m_pAppliance[m_iNumAppliances] != NULL) m_iNumAppliances++;

	return 0;
}

void CMainFrame::CreateAppliance(REFIID riid,
                                 IUnknown** ppIUnknown, 
                                 int x, int y,
                                 CRect* pRect)
{
    ASSERT(ppIUnknown);

    // Create an instance of the object
    HRESULT hr = ::CoCreateInstance(riid,
                                    NULL,
                                    CLSCTX_INPROC_SERVER,
                                    IID_IUnknown,
                                    (LPVOID*)ppIUnknown);
    if (FAILED(hr)) {
        dprintf1("Failed to create object. SCODE: %8.8lXH (%lu)\n",
              GetScode(hr),
              GetScode(hr) & 0x0000FFFF);
        *ppIUnknown = NULL;
        return;
    }
    ASSERT(*ppIUnknown);

    // Get a pointer to the IDrawing interface
    IDrawing* pIDrawing = NULL;
    if ((*ppIUnknown)->QueryInterface(IID_IDrawing, (LPVOID*)&pIDrawing) != S_OK) {
        dprintf1("IDrawing not supported");
        return;
    }

    // Give the COM object a pointer to our palette
    pIDrawing->SetPalette(&m_pal);

    // get the image size
    CRect rc;
    pIDrawing->GetRect(&rc);

    // save the info
    pRect->left = x;
    pRect->right = x + rc.right - rc.left;
    pRect->top = y; 
    pRect->bottom = y + rc.bottom - rc.top;

    // free the interface
    pIDrawing->Release();
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
    // just punt - we do all our own painting
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
	
    // Get a dc to the off-screen buffer
    CDC* pdcBuf = m_dsBuffer.GetDC();
    ASSERT(pdcBuf);

    // copy the background bitmap to the buffer
    m_dibBkgnd.Draw(pdcBuf, 0, 0);

    // Ask each appliance to draw itself to the buffer
    for (int i = 0; i < m_iNumAppliances; i++) {
        DrawObject(pdcBuf,
                   m_pAppliance[i],
                   m_rcAppliance[i].left,
                   m_rcAppliance[i].top);
    }

#if 0
    // See if there is an active selection rect to draw
    if (m_pSelectRect) {

        // Create a pen to use 
        CPen penRect (PS_SOLID, 5, RGB(255, 0, 0));
        CPen* pOldPen = pdcBuf->SelectObject(&penRect);

        // Create a null brush
        CBrush brNull;
        brNull.CreateStockObject(NULL_BRUSH);
        CBrush* pOldBrush = pdcBuf->SelectObject(&brNull);
        
        // create a rectangle a bit bigger than the object
        CRect rect (*m_pSelectRect);
        rect.InflateRect(5, 5);

        // draw the rectangle
        pdcBuf->Rectangle(&rect);

        // tidy up
        pdcBuf->SelectObject(pOldBrush);
        pdcBuf->SelectObject(pOldPen);
    }
#endif

    // Copy the buffer to the screen dc
    ::GdiFlush();
    m_dsBuffer.Draw(&dc);

    pdcBuf->SelectPalette(pOldPal, FALSE);
}

void CMainFrame::DrawObject(CDC* pDC, IUnknown* pIUnknown, int x, int y)
{
    ASSERT(pIUnknown);

    // Get a pointer to the IDrawing interface
    IDrawing* pIDrawing = NULL;
    if (pIUnknown->QueryInterface(IID_IDrawing, (LPVOID*)&pIDrawing) == S_OK) {

        // Ask it to draw
        ASSERT(pIDrawing);
        if (pIDrawing->Draw(pDC, x, y) != S_OK) {
            dprintf1("IDrawing::Draw failed");
        }

        // Release the interface
        pIDrawing->Release();
    } else {

        dprintf1("No IDrawing interface found");
    }
}

void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point) 
{
    // Save the current selection state
    CRect* pOldRect = m_pSelectRect;

    // Set the no selection state
    m_pSelectRect = NULL;

    // See if the mouse hit an object
    for (int i = 0; i < m_iNumAppliances; i++) {
        if (m_rcAppliance[i].PtInRect(point)) {
            m_pSelectRect = &m_rcAppliance[i];
            m_iSelect = i;
        }    
    }

    // See if we need to redraw
    if (m_pSelectRect != pOldRect) {
        Invalidate();
    }
}

void CMainFrame::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
    if(m_pSelectRect == NULL) return; // no selection

    // get the object's IUnknown interface ptr
    IUnknown* pIUnknown = m_pAppliance[m_iSelect];
    ASSERT(pIUnknown);

    // See if it supports the IApplianceUI interface
    IApplianceUI* pIApplianceUI = NULL;
    if (pIUnknown->QueryInterface(IID_IApplianceUI, (LPVOID*)&pIApplianceUI) == S_OK) {

        // Put up the interface
        pIApplianceUI->ShowControl(this);
        pIApplianceUI->Release();
        return;
    }

    // See if it supports the ILight interface
    ILight* pILight = NULL;
    if (pIUnknown->QueryInterface(IID_ILight, (LPVOID*)&pILight) == S_OK) {

        // Put up the interface
        CLightDlg* pDlg = new CLightDlg;
        pDlg->m_pILight = pILight;
        pDlg->m_pParent = this;
        pDlg->Create();
        pILight->Release();
        return;
    }

    // See if it supports the IOutlet interface
    IOutlet* pIOutlet = NULL;
    if (pIUnknown->QueryInterface(IID_IOutlet, (LPVOID*)&pIOutlet) == S_OK) {

        // Put up the interface
        COutletDlg* pDlg = new COutletDlg;
        pDlg->m_pIOutlet = pIOutlet;
        pDlg->m_pParent = this;
        pDlg->Create();
        pIOutlet->Release();
        return;
    }


    // Pretty much a dead loss this one
    AfxMessageBox("This appliance is not controllable");
}
