// rotary.cpp : implementation file
//

#include "stdafx.h"
#include "math.h"
#include "dlgpanel.h"  // for palette message definition
#include "rotary.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

BOOL CRotaryCtl::m_bRegistered = Register();

BOOL CRotaryCtl::Register()
{
    // Register the window class of the control
    WNDCLASS wc;
    wc.style = CS_GLOBALCLASS
             | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = RotaryWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = NULL;
    wc.hIcon = NULL;
    wc.hCursor = ::LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Rotary";

    if (!::RegisterClass(&wc)) {
        ASSERT(0);
        return FALSE;
    } 
    return TRUE;
}

LRESULT CALLBACK RotaryWndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uiMsg) {
    case WM_NCCREATE: {
        // Create a C++ object to handle the messages
        CRotaryCtl* pCtl = new CRotaryCtl;
        ASSERT(pCtl);
        // Attach the window handle to the new object
        BOOL b = pCtl->SubclassWindow(hWnd);
        ASSERT(b);
        return b;
        } break;

    default:
        return ::DefWindowProc(hWnd, uiMsg, wParam, lParam);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CRotaryCtl

IMPLEMENT_DYNCREATE(CRotaryCtl, CWnd)

CRotaryCtl::CRotaryCtl()
{
    m_pPal = NULL;
    m_bGotBackground = FALSE;
    m_iMin = 0;
    m_iMax = 100;
    m_iPos = 50;
    m_bCaptured = FALSE;
}

CRotaryCtl::~CRotaryCtl()
{
    // don't destroy m_pPal - it's not ours
}

WNDPROC* CRotaryCtl::GetSuperWndProcAddr()
{
    // Provide a place for MFC's subclassing
    // mechanism to store the super-class pointer
    static WNDPROC NEAR pfnSuper = NULL;
    return &pfnSuper;
}

BEGIN_MESSAGE_MAP(CRotaryCtl, CWnd)
    //{{AFX_MSG_MAP(CRotaryCtl)
    ON_WM_NCDESTROY()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_ERASEBKGND()
    ON_WM_PAINT()
    ON_WM_SIZE()
    ON_MESSAGE(DLGPANELMSG_SETPALETTE, OnSetPalette)
    ON_WM_MOUSEMOVE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRotaryCtl message handlers

void CRotaryCtl::OnNcDestroy()
{
    CWnd::OnNcDestroy();
    // Make sure the window was destroyed
    ASSERT(m_hWnd == NULL);
    // Destroy this object since it won't be destroyed otherwise
    delete this;
}

LRESULT CRotaryCtl::OnSetPalette(WPARAM wParam, LPARAM lParam)
{
    // A message from the parent telling us what palette to use
    m_pPal = (CPalette*) lParam;
    ASSERT(m_pPal);
    ASSERT(m_pPal->IsKindOf(RUNTIME_CLASS(CPalette)));
    // Rebuild the image
    CreateImage();
    return 0;
}

BOOL CRotaryCtl::OnEraseBkgnd(CDC* pDC)
{
    return TRUE; // say we handled it
}

void CRotaryCtl::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    // See if we have grabbed the background image yet
    if (!m_bGotBackground) {
        // Nope, so do it now
        CDC* pdcBackground = m_dsBackground.GetDC();
        CDC* pdcParent = GetParent()->GetDC();
        CRect rc;
        GetClientRect(&rc);
        // Find the top-left corner coords in the parent window DC
        CPoint pt(rc.left, rc.top);
        ClientToScreen(&pt); // convert our coords to screen coords
        GetParent()->ScreenToClient(&pt); // conver to parent's coords
        pdcBackground->BitBlt(0, 0, 
                              rc.right - rc.left, rc.bottom - rc.top,
                              pdcParent,
                              pt.x, pt.y,
                              SRCCOPY);
        m_bGotBackground = TRUE;
        // Flush the GDi op queue before we do the next bit
        ::GdiFlush();

        // Now render the entire image to the buffer
        Render();
    }

    // Simply copy the buffer to the DC
    m_dsBuffer.Draw(&dc);
}

void CRotaryCtl::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);
    if ((cx < 10) || (cy < 10)) return;

    // Save the size
    m_iWidth = cx;
    m_iHeight = cy;

    // Resize the images and buffer to occupy the client area
    m_dsBuffer.Create(cx, cy, m_pPal);
    m_dsImage.Create(cx, cy, m_pPal);
    m_dsBackground.Create(cx, cy, m_pPal);
    m_bGotBackground = FALSE; // say we need to grab the background again

    // Build a new image
    CreateImage();

    // Render the buffer image and update the display
    Render();
    Invalidate();
}

void CRotaryCtl::CreateImage()
{
    // Start by filling the whole area with the transparency color
    // We use a system color which isn't used elsewhere in the control
    CDC* pDC = m_dsImage.GetDC();
    CPalette* ppalOld = NULL;
    CBrush br;
    if (m_pPal) {
        pDC->SelectPalette(m_pPal, FALSE);
        pDC->RealizePalette();
        br.CreateSolidBrush(PALETTEINDEX(m_pPal->GetNearestPaletteIndex(TRANS_COLOR)));
    } else {
        br.CreateSolidBrush(TRANS_COLOR);
    }
    CRect rc(0, 0, m_iWidth, m_iHeight);
    pDC->FillRect(&rc, &br);

    // Compute the center and outer radius of the tick marks
    m_ptCenter.x = m_iWidth / 2;
    m_ptCenter.y = m_iHeight / 2;
    m_iRadius = min(m_ptCenter.x, m_ptCenter.y) + 1;
    // Make radius an odd number
    if (m_iRadius & 1 == 0) m_iRadius--;
    // cos(pi/4) = sin (pi/4) = 0.7071 = 7071/10000
    int iOffset = m_iRadius * 7071 / 10000;
    pDC->MoveTo(m_ptCenter);
    pDC->LineTo(m_ptCenter.x + iOffset, m_ptCenter.y + iOffset);
    pDC->MoveTo(m_ptCenter);
    pDC->LineTo(m_ptCenter.x + m_iRadius, m_ptCenter.y);
    pDC->MoveTo(m_ptCenter);
    pDC->LineTo(m_ptCenter.x + iOffset, m_ptCenter.y - iOffset);
    pDC->MoveTo(m_ptCenter);
    pDC->LineTo(m_ptCenter.x, m_ptCenter.y - m_iRadius);
    pDC->MoveTo(m_ptCenter);
    pDC->LineTo(m_ptCenter.x - iOffset, m_ptCenter.y - iOffset);
    pDC->MoveTo(m_ptCenter);
    pDC->LineTo(m_ptCenter.x - m_iRadius, m_ptCenter.y);
    pDC->MoveTo(m_ptCenter);
    pDC->LineTo(m_ptCenter.x - iOffset, m_ptCenter.y + iOffset);

    // Draw the knob skirt. Make the pen the transparency color so we
    // get a slight gap between the skirt and the tick marks
    int iSkirtRad = m_iRadius * 8 / 10;
    CBrush brBody;
    brBody.CreateSolidBrush(PALETTERGB(102,102,102));
    CPen penTrans(PS_SOLID, 1, TRANS_COLOR);
    CPen* ppenOld = pDC->SelectObject(&penTrans);
    CBrush* pbrOld = pDC->SelectObject(&brBody);
    pDC->Ellipse(m_ptCenter.x - iSkirtRad, m_ptCenter.y - iSkirtRad,
                 m_ptCenter.x + iSkirtRad + 1, m_ptCenter.y + iSkirtRad + 1);

    // Draw the center
    CPen penTop(PS_SOLID, 1, PALETTERGB(51,51,51));
    CBrush brTop;
    brTop.CreateSolidBrush(PALETTERGB(165,165,165));
    pDC->SelectObject(&penTop);
    pDC->SelectObject(&brTop);
    int iTopRad = m_iRadius / 2;
    pDC->Ellipse(m_ptCenter.x - iTopRad, m_ptCenter.y - iTopRad,
                 m_ptCenter.x + iTopRad + 1, m_ptCenter.y + iTopRad + 1);


    // Tidy up
    pDC->SelectObject(ppenOld);
    pDC->SelectObject(pbrOld);
    if (ppalOld) pDC->SelectPalette(ppalOld, FALSE);
}

void CRotaryCtl::Render()
{
    // Render the image of the control to the buffer
    // Start by blting the the background image to the buffer
    CDC* pDC = m_dsBuffer.GetDC();
    // Don't use CDIB::Draw here as DC operation caching by GDI
    // will mean this op would get done after the next one which
    // does direct pixel manipulation
    m_dsBackground.CopyBits(&m_dsBuffer,
                            0, 0,
                            m_dsBackground.GetWidth(), m_dsBackground.GetHeight(),
                            0, 0);

    // Now transparently blt the image to the buffer
    BYTE* p = (BYTE*) m_dsImage.GetPixelAddress(0, 0);
    COLORREF clr = PALETTEINDEX(*p);
    m_dsImage.CopyBits(&m_dsBuffer,
                       0, 0,
                       m_dsImage.GetWidth(), m_dsImage.GetHeight(),
                       0, 0,
                       clr);

    // Now draw the pointer dot at the correct position
    ASSERT(m_iMax > m_iMin);
    ASSERT((m_iPos >= m_iMin) && (m_iPos <= m_iMax));
    double a = -PI/4 + 3*PI/2 * (m_iMax - m_iPos)/(m_iMax - m_iMin);
    int iRad = m_iRadius * 65/100;
    int x = m_ptCenter.x + (int)(iRad * cos(a));
    int y = m_ptCenter.y - (int)(iRad * sin(a));
    CBrush br;
    br.CreateSolidBrush(PALETTERGB(255,255,255));
    CBrush* pbrOld = pDC->SelectObject(&br);
    CPen pen;
    pen.CreateStockObject(NULL_PEN);
    CPen* ppenOld = pDC->SelectObject(&pen);
    int iInc = max(2, m_iRadius * 1/10);
    pDC->Ellipse(x-iInc, y-iInc, x+iInc+1, y+iInc+1);
    pDC->SelectObject(pbrOld);
    pDC->SelectObject(ppenOld);
}

void CRotaryCtl::OnLButtonDown(UINT nFlags, CPoint point)
{
    ASSERT(!m_bCaptured);
    SetCapture();
    m_bCaptured = TRUE;
    OnMouseMove(nFlags, point);
}

void CRotaryCtl::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_bCaptured) {
        // Calculate the new value from the mouse position
        int x = point.x - m_ptCenter.x;
        int y = m_ptCenter.y - point.y; // make up +ve
        if ((x == 0) && (y == 0)) {
            x = 1;
        }
        double a = atan2(y, x); // -PI <= a <= PI
        if (a < -PI/2) {
            a += 2*PI;
        }
        // -PI/2 <= a <= 3PI/2

        // Correct points beyond min and max
        if (a >= 5*PI/4) {
            m_iPos = m_iMin;
        } else if (a < -PI/4) {
            m_iPos = m_iMax;
        } else {
            m_iPos = m_iMax - (int)((a+PI/4)/(3*PI/2) * (m_iMax - m_iMin));
        }
        ASSERT((m_iPos >= m_iMin) && (m_iPos <= m_iMax));

        // Redraw the control
        Render();
        RedrawWindow();

        // Notify parent
        GetParent()->SendMessage(WM_HSCROLL,
                                 MAKEWPARAM(SB_THUMBTRACK, m_iPos),
                                 (LPARAM)GetSafeHwnd()); 
    }
}

void CRotaryCtl::OnLButtonUp(UINT nFlags, CPoint point)
{
    if (m_bCaptured) {
        ReleaseCapture();
        m_bCaptured = FALSE;

        // Notify parent
        GetParent()->SendMessage(WM_HSCROLL,
                                 MAKEWPARAM(SB_THUMBPOSITION, m_iPos),
                                 (LPARAM)GetSafeHwnd()); 
    }
}

void CRotaryCtl::SetRange(int iMin, int iMax)
{
    ASSERT(iMin < iMax);
    m_iMin = iMin;
    m_iMax = iMax;
    if (m_iPos < m_iMin) {
        m_iPos = m_iMin;
    } else if (m_iPos > m_iMax) {
        m_iPos = m_iMax;
    }
}

void CRotaryCtl::SetPos(int iPos)
{
    ASSERT((iPos >= m_iMin) && (iPos <= m_iMax));
    m_iPos = iPos;
    Render();
    RedrawWindow();
}
