// animtvw.cpp : implementation of the CAnimTestView class
//

#include "stdafx.h"
#include "animtest.h"
#include "animtdoc.h"
#include "animtvw.h"
#include "math.h"
#include "vudlg.h"
#include "recorddl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimTestView

IMPLEMENT_DYNCREATE(CAnimTestView, COSBView)

BEGIN_MESSAGE_MAP(CAnimTestView, COSBView)
    //{{AFX_MSG_MAP(CAnimTestView)
    ON_COMMAND(ID_TEST_DIBSURF, OnTestDibsurf)
    ON_COMMAND(ID_TEST_METER, OnTestMeter)
    ON_COMMAND(ID_TEST_DIBSURFNP, OnTestDibsurfnp)
    ON_WM_TIMER()
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_COMMAND(ID_TEST_VU, OnTestVu)
    ON_COMMAND(ID_TEST_RECORD, OnTestRecord)
    ON_COMMAND(ID_TEST_WAVEFILE, OnTestWavefile)
    ON_WM_SIZE()
    ON_COMMAND(ID_TEST_WAVERES, OnTestWaveres)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimTestView construction/destruction

CAnimTestView::CAnimTestView()
{
    m_bIdle = TRUE;
    m_angle = 0.0;
}

CAnimTestView::~CAnimTestView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CAnimTestView drawing

void CAnimTestView::OnDraw(CDC* pDC)
{
    CAnimTestDoc* pDoc = GetDocument();
    COSBView::OnDraw(pDC);
}

void CAnimTestView::DrawTriangle()
{
    // Draw a triangle to the off-screen buffer
    // and copy the buffer to the window
    CDC* pdc = GetBufferDC();
    ASSERT(pdc);
    COLORREF clr = PALETTERGB(rand() % 255,
                              rand() % 255,
                              rand() % 255);
    CPen penRed (PS_SOLID, 1, clr);
    CBrush brRed (clr);
    CPen* pOldPen = pdc->SelectObject(&penRed);
    CBrush* pOldBrush = pdc->SelectObject(&brRed);
    CRect rc;
    GetClientRect(&rc);
    int x = (rc.right + rc.left) / 2;
    int y = (rc.bottom + rc.top) / 2;
    POINT points[] = {x-150-x/3, y,
                      x+50-x/3,y+50, 
                      x-100-x/3,y+100};
    m_angle += 0.2;
    Rotate(points, 3, m_angle, x, y);
    int iPoints = sizeof(points)/sizeof(POINT);
    pdc->Polygon(points, iPoints);
    pdc->SelectObject(pOldPen);
    pdc->SelectObject(pOldBrush);

    // Compute the clip rect
    CRect rcClip (points[0].x, points[0].y, points[0].x, points[0].y);
    for (int i=0; i<iPoints; i++) {
        if (points[i].x < rcClip.left) rcClip.left = points[i].x;
        if (points[i].y < rcClip.top) rcClip.top = points[i].y;
        if (points[i].x > rcClip.right) rcClip.right = points[i].x;
        if (points[i].y > rcClip.bottom) rcClip.bottom = points[i].y;
    }

    COSBView::Draw(&rcClip);
}

/////////////////////////////////////////////////////////////////////////////
// CAnimTestView diagnostics

#ifdef _DEBUG
void CAnimTestView::AssertValid() const
{
    COSBView::AssertValid();
}

void CAnimTestView::Dump(CDumpContext& dc) const
{
    COSBView::Dump(dc);
}

CAnimTestDoc* CAnimTestView::GetDocument() // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimTestDoc)));
    return (CAnimTestDoc*) m_pDocument;
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnimTestView message handlers

void CAnimTestView::OnTestDibsurf()
{
    CAnimTestDoc* pDoc = GetDocument();
    TestDIBSurf(pDoc->m_pPal);
}

void CAnimTestView::OnTestDibsurfnp()
{
    TestDIBSurf(NULL);
}

void CAnimTestView::TestDIBSurf(CPalette* pPal)
{
    m_bIdle = FALSE;
    DWORD dwStart = timeGetTime();

    CDIBSurface* pSurf = new CDIBSurface;
    ASSERT(pSurf);
    CRect rcWnd;
    GetClientRect(&rcWnd);
    int w = (rcWnd.right - rcWnd.left) / 2;
    int h = (rcWnd.bottom - rcWnd.top) / 2;
    pSurf->Create(w, h, pPal);
    CDC* pdc = pSurf->GetDC();

    // Fill the entire area
    CBrush brBlue (PALETTERGB(212,0,212));
    CRect rcSurf;
    pSurf->GetRect(&rcSurf);
    pdc->FillRect(&rcSurf, &brBlue);

    // Draw an ellipse
    CPen penGreen (PS_SOLID, 1, PALETTERGB(212,170,42));
    CBrush brGreen (PALETTERGB(212,170,42));
    CPen* pOldPen = pdc->SelectObject(&penGreen);
    CBrush* pOldBrush = pdc->SelectObject(&brGreen);
    pdc->Ellipse(&rcSurf);
    pdc->SelectObject(pOldPen);
    pdc->SelectObject(pOldBrush);

    // Copy the surface to the window
    CClientDC dc(this); 

    for (int i = 0; i < 100; i++) {
        pSurf->BitBlt(&dc,
                      rand() % w, rand() % h,
                      w, h,
                      0, 0);
    }

    // delete the DIBSurface
    delete pSurf;

    DWORD dwStop = timeGetTime();
    char buf[128];
    sprintf(buf, "Elapsed time: %lu ms", dwStop - dwStart);
    AfxMessageBox(buf);
    m_bIdle = TRUE;
}

void CAnimTestView::OnTestMeter()
{
    m_bIdle = FALSE;
    // Create a meter window and cycle it through a
    // variety of states, then destroy it.

    CAnimTestDoc* pDoc = GetDocument();
    CMeter meter(pDoc->m_pPal);
    CRect rcWnd;
    GetClientRect(&rcWnd);
    CBrush br (PALETTERGB(192,192,192));
    CClientDC dc (this);
    dc.FillRect(&rcWnd, &br);
    rcWnd.InflateRect(-20, -20); // shrink it a bit

    meter.SetScale(0, 100, 0);
    meter.SetScale(0, 100, 1);
    meter.SetNeedleColor(PALETTERGB(170,212,212), 1);
    meter.SetScaleSplit(50);
    meter.SetScaleColor(PALETTERGB(212,42,212), PALETTERGB(212,212,85));
    meter.SetTextColor(PALETTERGB(166,202,240));
    meter.Create("Wildly Wavy",
                 WS_CHILD | WS_VISIBLE,
                 rcWnd,
                 this,
                 1);
    DWORD dwStart = timeGetTime();

    for (int c = 0; c < 1; c++) {
        meter.SetNeedleColor(PALETTERGB(85,212,85), 0);
        for (int i = 0; i <= 100; i++) {
            meter.SetValue(i, 0);
            meter.SetValue(100-i, 1);
        }
        meter.SetNeedleColor(PALETTERGB(212, 0,212), 0);
        for (i = 100; i >= 0; i--) {
            meter.SetValue(i, 0);
            meter.SetValue(100-i, 1);
        }
    }

    DWORD dwStop = timeGetTime();
    char buf[128];
    sprintf(buf, "Elapsed time: %lu ms", dwStop - dwStart);
    AfxMessageBox(buf);
    m_bIdle = TRUE;
}



void CAnimTestView::OnTimer(UINT nIDEvent)
{
    if (m_bIdle) DrawTriangle();
}

void CAnimTestView::Idle()
{
    DrawTriangle();
}

int CAnimTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (COSBView::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    // Start the updates
    theApp.SetIdleView(this);
    return 0;
}

void CAnimTestView::OnDestroy()
{
    COSBView::OnDestroy();
}

void CAnimTestView::Rotate(POINT* ppt, int iPoints, double a, int x, int y)
{
    double sin_a = sin(a);
    double cos_a = cos(a);
    while (iPoints) {
        // Translate to the origin
        ppt->x -= x;
        ppt->y -= y;

        // Rotate
        double x1 = ppt->x * cos_a - ppt->y * sin_a;
        double y1 = ppt->y * cos_a + ppt->x * sin_a;
        ppt->x = (int)x1;
        ppt->y = (int)y1;

        // Translate back out from the origin
        ppt->x += x;
        ppt->y += y;

        ppt++;
        iPoints--;
    }
}

void CAnimTestView::OnTestVu()
{
    m_bIdle = FALSE;
    CVUDlg dlg;
#if 0 // use our own palette
    CAnimTestDoc* pDoc = GetDocument();	// 9/28/95 NigelT Added palette
    dlg.m_pPal = pDoc->m_pPal;			// 9/28/95 NigelT Added palette
#else // let the meter supply the palette
#endif
    dlg.DoModal();
    m_bIdle = TRUE;
}

void CAnimTestView::OnTestRecord()
{
    CRecordDlg dlg;
#if 0 // use our own palette
    CAnimTestDoc* pDoc = GetDocument();	// 9/28/95 NigelT Added palette
    dlg.m_pPal = pDoc->m_pPal;			// 9/28/95 NigelT Added palette
#else // let the dialog supply the palette
#endif
    dlg.DoModal();
    if (dlg.m_pWave) delete dlg.m_pWave;
}

void CAnimTestView::OnTestWavefile()
{
    CWave* pWave = new CWave(CWave::flagAutoDestruct);
    pWave->AddRef();
    if (!pWave->Load((char*)NULL)) {
        pWave->Release;
        return;
    }
    pWave->Play();
    pWave->Release();
}

void CAnimTestView::OnSize(UINT nType, int cx, int cy)
{
    // Just start again
    CAnimTestDoc* pDoc = GetDocument();
    pDoc->Restart(cx, cy);   
}

void CAnimTestView::OnTestWaveres()
{
    CWave* pWave = new CWave(CWave::flagAutoDestruct);
    pWave->AddRef();
    if (!pWave->LoadResource(IDR_WAVERES)) {
        pWave->Release;
        AfxMessageBox("Failed to load wave resorce");
        return;
    }
    pWave->Play();
    pWave->Release();
}
