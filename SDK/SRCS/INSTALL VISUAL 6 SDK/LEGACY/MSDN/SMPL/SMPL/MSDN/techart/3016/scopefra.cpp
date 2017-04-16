// scopefra.cpp : implementation file
//

#include "stdafx.h"
#include "fwtest.h"
#include "dlgpanel.h"
#include "rotary.h"
#include "updnctl.h"
#include "scopefra.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScopeFrame

IMPLEMENT_DYNCREATE(CScopeFrame, CMDIChildWnd)

CScopeFrame::CScopeFrame()
{
    m_pPal = NULL;

    m_A.pData = NULL;
    m_A.iPoints = 0;
    m_A.dInterval = 1.0;
    m_A.iPos = 25;
    m_A.dScale = 1.0;
    m_A.bGnd = FALSE;

    m_B.pData = NULL;
    m_B.iPoints = 0;
    m_B.dInterval = 1.0;
    m_B.iPos = 75;
    m_B.dScale = 1.0;
    m_B.bGnd = FALSE;

    m_iXPos = 50;
    m_dXScale = 0.001;
}

CScopeFrame::~CScopeFrame()
{
    // Don't delete m_pPal - it's not ours
}


BEGIN_MESSAGE_MAP(CScopeFrame, CMDIChildWnd)
    //{{AFX_MSG_MAP(CScopeFrame)
    ON_WM_CREATE()
    ON_WM_SIZE()
    ON_WM_ERASEBKGND()
    ON_WM_HSCROLL()
    ON_WM_DRAWITEM()
    ON_BN_CLICKED(IDC_A_GND, OnClickedAGnd)
    ON_BN_CLICKED(IDC_B_GND, OnClickedBGnd)
    ON_CBN_EDITCHANGE(IDC_A_SCALE, OnEditchangeAScale)
    ON_CBN_EDITCHANGE(IDC_B_SCALE, OnEditchangeBScale)
    ON_CBN_EDITCHANGE(IDC_X_SCALE, OnEditchangeXScale)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScopeFrame message handlers

BOOL CScopeFrame::Create(LPCSTR lpszWindowName,
                         const RECT& rc,
                         CMDIFrameWnd* pParentWnd,
                         UINT uiResourceID,
                         CPalette* pPal/*= NULL*/)
{
    m_pPal = pPal;
    return CMDIChildWnd::Create(GetIconWndClass(WS_CHILD|WS_VISIBLE|WS_OVERLAPPEDWINDOW,
                                                uiResourceID),
                                lpszWindowName,
                                WS_CHILD|WS_VISIBLE|WS_OVERLAPPEDWINDOW,
                                rc,
                                pParentWnd);
}

int CScopeFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    // Create the dialog bars in the order we want them positioned
    // Note that we send them the palette we are using.
    m_wndBarBottom.Create(this, IDD_SCOPE_BOTTOM, CBRS_BOTTOM,
                          IDC_SCOPE_BOTTOM, m_pPal);
    m_wndBarLeft.Create(this, IDD_SCOPE_LEFT, CBRS_LEFT,
                        IDC_SCOPE_LEFT, m_pPal);
    m_wndBarRight.Create(this, IDD_SCOPE_RIGHT, CBRS_RIGHT,
                         IDC_SCOPE_RIGHT, m_pPal);
    // Create the screen
    m_wndScreen.Create(this, IDC_SCOPE_SCREEN, m_pPal);
    // Leave everything else until we get sized. It sems that grabbing the
    // dialog bar window handles now will mean they are invalid if the 
    // frame gets resized later.

    // Set the X and Y position rotary control ranges and positions
    CRotaryCtl* pRC;
    pRC = (CRotaryCtl*) m_wndBarLeft.GetDlgItem(IDC_A_POS);
    ASSERT(pRC && pRC->IsKindOf(RUNTIME_CLASS(CRotaryCtl)));
    pRC->SetRange(0, 100);
    pRC->SetPos(m_A.iPos);
    pRC = (CRotaryCtl*) m_wndBarRight.GetDlgItem(IDC_B_POS);
    ASSERT(pRC && pRC->IsKindOf(RUNTIME_CLASS(CRotaryCtl)));
    pRC->SetRange(0, 100);
    pRC->SetPos(m_B.iPos);
    pRC = (CRotaryCtl*) m_wndBarBottom.GetDlgItem(IDC_X_POS);
    ASSERT(pRC && pRC->IsKindOf(RUNTIME_CLASS(CRotaryCtl)));
    pRC->SetRange(0, 100);
    pRC->SetPos(m_iXPos);

    // Set the scale controls
    CUpDnCtl* pUD;
    pUD = (CUpDnCtl*)m_wndBarLeft.GetDlgItem(IDC_A_SCALE);
    pUD->SetButtonText("V", "uV");
    pUD->SetTextSet("10 V/div|"
                    "5 V/div|2 V/div|1 V/div|"
                    "500 mV/div|200 mV/div|100 mV/div");
    pUD->SetCurSel(3);

    pUD = (CUpDnCtl*)m_wndBarRight.GetDlgItem(IDC_B_SCALE);
    pUD->SetButtonText("V", "uV");
    pUD->SetTextSet("10 V/div|"
                    "5 V/div|2 V/div|1 V/div|"
                    "500 mV/div|200 mV/div|100 mV/div");
    pUD->SetCurSel(3);

    pUD = (CUpDnCtl*)m_wndBarBottom.GetDlgItem(IDC_X_SCALE);
    pUD->SetButtonText("s", "us");
    pUD->SetTextSet("1 s/div|500 ms/div|200 ms/div|100 ms/div|"
                    "50 ms/div|20 ms/div|10 ms/div|"
                    "5 ms/div|2 ms/div|1 ms/div|"
                    "500 us/div|200 us/div|100 us/div|"
                    "50 us/div|20 us/div|10 us/div");
    pUD->SetCurSel(9);

    return 0;
}

void CScopeFrame::RecalcLayout()
{
    // Rearrange the control bars and fit the screen in the middle
    RepositionBars(0, 0xFFFF, IDC_SCOPE_SCREEN);
}

void CScopeFrame::PlotData()
{
    // Show what data we have
    m_wndScreen.Erase();

    CDC* pDC = m_wndScreen.GetDC();
    CRect rc;
    m_wndScreen.GetRect(&rc);

    // Plot the A channel
    CPen penA(PS_SOLID, 2, PALETTERGB(0, 255, 0));
    CPen* ppenOld = pDC->SelectObject(&penA);
    Plot(pDC, &m_A, &rc);

    // Plot the B channel
    CPen penB(PS_SOLID, 2, PALETTERGB(255, 255, 0));
    pDC->SelectObject(&penB);
    Plot(pDC, &m_B, &rc);

    pDC->SelectObject(ppenOld);
    // Draw the grid on top
    m_wndScreen.DrawGrid();

    // Show it all
    m_wndScreen.Invalidate();
}

void CScopeFrame::Plot(CDC* pDC, YCHANNEL* pCh, CRect* prc)
{
    int x0, y0;
    double yscale;

    x0 = (m_iXPos - 50) * prc->right / 100;
    y0 = (100 - pCh->iPos) * prc->bottom / 100;
    yscale = -prc->bottom / pCh->dScale / 8;
    int iPixels = prc->right - prc->left;
#if 0
    // Compute approx. how many samples per screen pixel we 
    // are trying to draw
    int iSampPerPix = (int)(m_dXScale * iPixels / 10 / pCh->dInterval);
#endif
    if ((pCh->iPoints < 2) || (pCh->bGnd)) {
        // Just show the base line
        pDC->MoveTo(x0, y0);
        pDC->LineTo(x0+prc->right, y0);
    } else {
        int x1, x2, y1, y2;
        double* pData = pCh->pData;
        int iPoints = pCh->iPoints;
        x1 = x0;
        y1 = y0 + (int)(*pData++ * yscale);
        pDC->MoveTo(x1, y1);
        for (int i = 1; i < iPoints-x0; i++) {
            // compute the time value for this data point
            double dTime = i * pCh->dInterval;
            // compute the x position
            x2 = x0 + (int)(dTime / m_dXScale * iPixels / 10);
            // compute the y position
            y2 = y0 + (int)(*pData++ * yscale);
            // plot the vector if we've moved at all
            if ((x2 != x1) || (y2 != y1)) {
                pDC->LineTo(x2, y2);
                x1 = x2;
                y1 = y2;
            }
            // If we've gone off the end of the screen, stop.
            if (x2 > iPixels) break;
        }
    }
}

double CScopeFrame::GetScale(CUpDnCtl* pUD)
{
    char buf[32];
    int i = 1;
    pUD->GetWindowText(buf, sizeof(buf));
    ASSERT(strlen(buf));
    sscanf(buf, "%d %s", &i, buf);
    double d = i;
    if (!strncmp(buf, "mV", 2)) {
        d /= 1000;
    } else if (!strncmp(buf, "uV", 2)) {
        d /= 1.0e6;
    } 
    return d;
}

void CScopeFrame::OnSize(UINT nType, int cx, int cy)
{
    CMDIChildWnd::OnSize(nType, cx, cy);
    // Plot the base lines
    PlotData();
}

void CScopeFrame::OnEditchangeAScale()
{
    CUpDnCtl* pUD = (CUpDnCtl*) m_wndBarLeft.GetDlgItem(IDC_A_SCALE);
    m_A.dScale = GetScale(pUD);
    PlotData();
}

void CScopeFrame::OnEditchangeBScale()
{
    CUpDnCtl* pUD = (CUpDnCtl*) m_wndBarRight.GetDlgItem(IDC_B_SCALE);
    m_B.dScale = GetScale(pUD);
    PlotData();
}

void CScopeFrame::OnEditchangeXScale()
{
    CUpDnCtl* pUD = (CUpDnCtl*) m_wndBarBottom.GetDlgItem(IDC_X_SCALE);
    char buf[32];
    int i = 1;
    pUD->GetWindowText(buf, sizeof(buf));
    ASSERT(strlen(buf));
    sscanf(buf, "%d %s", &i, buf);
    m_dXScale = i;
    if (!strncmp(buf, "ms", 2)) {
        m_dXScale /= 1000;
    } else if (!strncmp(buf, "us", 2)) {
        m_dXScale /= 1.0e6;
    } 
    PlotData();
}

BOOL CScopeFrame::OnEraseBkgnd(CDC* pDC)
{
    return TRUE; // say we handled it
}

void CScopeFrame::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    // Since all our scroll bars are controls, we can treat them all the same way
    OnScroll(nSBCode, nPos, (CRotaryCtl*)pScrollBar);
}

void CScopeFrame::OnScroll(UINT nSBCode, UINT nPos, CRotaryCtl* pCtl)
{
    // All controls are rotary 0 - 100 so we only get
    // track and position messages. We can do do the generic position change
    // Note: these are NOT scroll bars they just send WM_HSCROLL messages

    // Do the stuff specific to each bar
    // Since we don't have any easy way to identify which bar the message
    // came from just update all the info
    CRotaryCtl* pRC;
    pRC = (CRotaryCtl*) m_wndBarLeft.GetDlgItem(IDC_A_POS);
    m_A.iPos = pRC->GetPos();
    pRC = (CRotaryCtl*) m_wndBarRight.GetDlgItem(IDC_B_POS);
    m_B.iPos = pRC->GetPos();
    pRC = (CRotaryCtl*) m_wndBarBottom.GetDlgItem(IDC_X_POS);
    m_iXPos = pRC->GetPos();

    // Show the changes
    PlotData();

}

void CScopeFrame::SetData(double* pData, int iPoints,
                          double dInterval, int iChannel)
{
    ASSERT((iChannel == 0) || (iChannel == 1));
    ASSERT(pData);
    ASSERT(iPoints > 0);
    ASSERT(dInterval > 0);

    YCHANNEL* pCh = iChannel ? &m_B : &m_A;
    pCh->pData = pData;
    pCh->iPoints = iPoints;
    pCh->dInterval = dInterval;
    PlotData();
}

void CScopeFrame::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    switch (nIDCtl) {
    case IDC_A_GND:
        DrawYButton(&m_A, lpDrawItemStruct);
        break;

    case IDC_B_GND:
        DrawYButton(&m_B, lpDrawItemStruct);
        break;

    default:
        return;
    }
}

void CScopeFrame::OnClickedAGnd()
{
    // Toggle the ground state
    m_A.bGnd = !m_A.bGnd;
    // Redraw the button
    m_wndBarLeft.GetDlgItem(IDC_A_GND)->RedrawWindow();
    // Replot the data
    PlotData();
}

void CScopeFrame::OnClickedBGnd()
{
    // Toggle the ground state
    m_B.bGnd = !m_B.bGnd;
    // Redraw the button
    m_wndBarRight.GetDlgItem(IDC_B_GND)->RedrawWindow();
    // Replot the data
    PlotData();
}

void CScopeFrame::DrawYButton(YCHANNEL* pCh, DRAWITEMSTRUCT* pDI)
{
    switch (pDI->itemAction) {
    case ODA_DRAWENTIRE:
    case ODA_SELECT: {
        // Create a CDC object
        CDC dc;
        dc.Attach(pDI->hDC);
        // Draw the black rectangle arround the outside
        // And fill the center with either the off or on color
        CBrush brCenter;
        if (pCh->bGnd) {
            brCenter.CreateSolidBrush(PALETTERGB(255,255,0));
        } else {
            brCenter.CreateSolidBrush(PALETTERGB(192,192,192));
        }
        CBrush* pbrOld = dc.SelectObject(&brCenter);
        dc.Rectangle(pDI->rcItem.left,
                     pDI->rcItem.top,
                     pDI->rcItem.right,
                     pDI->rcItem.bottom);
        // Done with the brush now
        dc.SelectObject(pbrOld);
        CPen penShadow(PS_SOLID, 1, PALETTERGB(128,128,128));
        CPen* ppenOld = dc.SelectObject(&penShadow);
        if (pDI->itemState & ODS_SELECTED) {
            dc.MoveTo(pDI->rcItem.left+1,
                      pDI->rcItem.bottom-2);
            dc.LineTo(pDI->rcItem.left+1,
                      pDI->rcItem.top+1);
            dc.LineTo(pDI->rcItem.right-2,
                      pDI->rcItem.top+1);
        } else {
            dc.MoveTo(pDI->rcItem.right-2,
                      pDI->rcItem.top+2);
            dc.LineTo(pDI->rcItem.right-2,
                      pDI->rcItem.bottom-2);
            dc.LineTo(pDI->rcItem.left+1,
                      pDI->rcItem.bottom-2);
            if (!pCh->bGnd) {
                CPen penHighlight(PS_SOLID, 1, PALETTERGB(255,255,255));
                dc.SelectObject(&penHighlight);
                dc.MoveTo(pDI->rcItem.left+1,
                          pDI->rcItem.bottom-2);
                dc.LineTo(pDI->rcItem.left+1,
                          pDI->rcItem.top+1);
                dc.LineTo(pDI->rcItem.right-2,
                          pDI->rcItem.top+1);
            }
        }
        // Done with pens
        dc.SelectObject(ppenOld);
        } break;
    default:
        break;
    }
}

