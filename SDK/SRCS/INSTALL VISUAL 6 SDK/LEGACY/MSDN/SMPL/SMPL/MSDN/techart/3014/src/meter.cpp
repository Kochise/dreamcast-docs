// meter.cpp : implementation file
//
// @doc

#include "stdafx.h"
#include "animate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeter

CMeter::CMeter(CPalette* pPal /*= NULL*/)
{
    m_pPal = pPal;
    m_hWnd = NULL;

    // Set the background color etc.
    m_clrBkgnd = RGB(0,0,0);
    m_clrText = RGB(192,192,192);

    m_ptCenter = (0, 0);
    // Turn all the needles off
    for (int i = 0; i < MAXSCALES; i++) {
        m_Scale[i].iMin = 0;
        m_Scale[i].iMax = 0;
        m_Scale[i].iValue = 0;
        m_Scale[i].clr = RGB(255,255,255); // white
        m_Scale[i].ptEnd = (0, 0);
    }
    m_Scale[0].iMax = 100;
    m_strCaption = "";
    m_iScaleSplit = 0;
    m_clrLowerScale = RGB(255,255,255);
    m_clrUpperScale = RGB(255,255,255);
}

CMeter::~CMeter()
{
    if (m_hWnd) DestroyWindow();
}


BEGIN_MESSAGE_MAP(CMeter, CWnd)
    //{{AFX_MSG_MAP(CMeter)
    ON_WM_PAINT()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeter message handlers

/*
@mfunc void | CMeter | Create | Creates a new CMeter window.
@syntax BOOL Create(const char* pszCaption, DWORD dwStyle,
const RECT& rect, CWnd* pwndParent, UINT id, CPalette* pPal = NULL);
@parm const char* | pszCaption | The caption text.
@parm DWORD | dwStyle | The style for the window that will be created.
@parm const RECT& | rect | A rectangle desribing the size of the window.
@parm CWnd* | pwndParent | A pointer to the parent window object.
@parm UINT | id | The child window ID.
@parm CPalette* | pPal | A pointer to a palette.
@rdesc The return value is TRUE if the window is created, FALSE if not.
@comm The image of the meter is drawn as a result of calling this function
so in order to avoid needless redrawing, call the setupup functions such
as <mf CMeter::SetNeedleColor> before calling Create.
@xref <c CMeter> <mf CMeter::SetNeedleColor> <mf CMeter::SetScale> <mf CMeter::SetScaleSplit>
<mf CMeter::SetScaleColor> <mf CMeter::SetTextColor> <mf CMeter::SetValue>
*/

BOOL CMeter::Create(const char* pszCaption, DWORD dwStyle,
                    const RECT& rect, CWnd* pwndParent,
                    UINT id, CPalette* pPal /*= NULL*/)
{
    if (pPal) {
        m_pPal = pPal;
    }

    // create the image of the background and cover
    m_iWidth = rect.right - rect.left + 1;
    m_iHeight = rect.bottom - rect.top + 1;
    if (pszCaption) {
        m_strCaption = pszCaption;
    } else {
        m_strCaption = "";
    }
    CreateImages();
    Render();

    if (!m_hWnd) {
        // create the window
        if (!CreateEx(0,
                      AfxRegisterWndClass(0),
                      pszCaption,
                      dwStyle,
                      rect.left,
                      rect.top,
                      m_iWidth,
                      m_iHeight,
                      pwndParent->GetSafeHwnd(),
                      (HMENU)id,
                      NULL)) {
            TRACE("Failed to create wave notification window");
            return FALSE;
        }
    }
    Draw();
    return TRUE;
}

// Create a new set of images and a new buffer
void CMeter::CreateImages()
{
    m_dsBuffer.Create(m_iWidth, m_iHeight, m_pPal);
    m_dsImage.Create(m_iWidth, m_iHeight, m_pPal);

    // Set the center point for the needles
    m_ptCenter.x = m_iWidth / 2;
    m_ptCenter.y = m_iHeight * 7 / 8;

    // Compute the current end points of all the active needles
    for (int i = 0; i < MAXSCALES; i++) {
        if (m_Scale[i].iMin != m_Scale[i].iMax) {
            ComputeNeedleEnd(&m_Scale[i].ptEnd,
                             m_Scale[i].iValue,
                             &m_Scale[i]);
        }
    }

    // Fill the background area
    CRect rcBkgnd;
    m_dsImage.GetRect(&rcBkgnd);
    CBrush brBkgnd (m_clrBkgnd);
    CDC* pdc = m_dsImage.GetDC();
    pdc->FillRect(&rcBkgnd, &brBkgnd);

    int l = rcBkgnd.left;
    int r = rcBkgnd.right - 1;
    int t = rcBkgnd.top;
    int b = rcBkgnd.bottom - 1;

    // Draw the scale
    int rad = b * 2;
    CRect rcScale ((l+r)/2 - rad,
                   b/4,
                   (l+r)/2 + rad,
                   b/4 + 2*rad);
    CPoint ptStart;
    ComputeNeedleEnd(&ptStart, m_Scale[0].iMax, &m_Scale[0]);
    CPoint ptEnd;
    ComputeNeedleEnd(&ptEnd, m_iScaleSplit, &m_Scale[0]);
    CPen penScaleU (PS_SOLID, 3, m_clrUpperScale);
    CPen* pold = pdc->SelectObject(&penScaleU);
    pdc->Arc(&rcScale, ptStart, ptEnd);
    ptStart = ptEnd;
    ComputeNeedleEnd(&ptEnd, m_Scale[0].iMin, &m_Scale[0]);
    CPen penScaleL (PS_SOLID, 3, m_clrLowerScale);
    pdc->SelectObject(&penScaleL);
    pdc->Arc(&rcScale, ptStart, ptEnd);

    // Draw the caption
    pdc->SetBkMode(TRANSPARENT);
    CRect rcText (l, b/2, r, b);
    pdc->SetTextColor(m_clrText);
    pdc->DrawText(m_strCaption, -1,
                  &rcText,
                  DT_CENTER | DT_TOP);

    // Fill the cover areas
    CRect rcCover (rcBkgnd);
    rcCover.top = b * 3 / 4;
    CBrush brCover (RGB(192,192,192));
    pdc->FillRect(&rcCover, &brCover);
    rcCover = rcBkgnd;
    rcCover.bottom = t+5;
    pdc->FillRect(&rcCover, &brCover);
    rcCover = rcBkgnd;
    rcCover.right = l+5;
    pdc->FillRect(&rcCover, &brCover);
    rcCover = rcBkgnd;
    rcCover.left = r-5;
    pdc->FillRect(&rcCover, &brCover);

    // Draw the highlights
    // Note LineTo draws up to but not including the last point
    CPen penWh (PS_SOLID, 1, RGB(255,255,255));
    CPen penBlk (PS_SOLID, 1, RGB(0,0,0));
    CPen penGy (PS_SOLID, 1, RGB(128,128,128));

    // black border
    pdc->SelectObject(&penBlk);
    pdc->MoveTo(l, t);
    pdc->LineTo(r, t);
    pdc->LineTo(r, b);
    pdc->LineTo(l, b);
    pdc->LineTo(l, t);

    // highlights
    pdc->SelectObject(&penWh);
    for (i = 0; i < 2; i++) {
        pdc->MoveTo(r-i-2, t+i+1);
        pdc->LineTo(l+i+1, t+i+1);
        pdc->LineTo(l+i+1, b-i-1);
    }
    pdc->MoveTo(r-6, t+5);
    pdc->LineTo(r-6, b*3/4);
    pdc->LineTo(l+4, b*3/4);

    // lowlights
    pdc->SelectObject(&penGy);
    for (i = 0; i < 3; i++) {
        pdc->MoveTo(r-i-1, t+i+1);
        pdc->LineTo(r-i-1, b-i-1);
        pdc->LineTo(l+i, b-i-1);
    }
    pdc->MoveTo(r-6, t+5);
    pdc->LineTo(l+5, t+5);
    pdc->LineTo(l+5, b*3/4);

    // Cover lines
    pdc->MoveTo(l+5, b*13/16);
    pdc->LineTo(r-4, b*13/16);
    pdc->MoveTo(l+5, b*7/8);
    pdc->LineTo(r-4, b*7/8);
    pdc->MoveTo(l+5, b*15/16);
    pdc->LineTo(r-4, b*15/16);

    pdc->SelectObject(pold);
}

/*
@mfunc void | CMeter | SetScale | Set the extent of a meter scale.
@syntax void SetScale(int iMin, int iMax, int iScale = 0);
@parm int | iMin | The minimum value.
@parm int | iMax | the maximum value.
@parm int | iScale | The index of the scale to set.
@rdesc There is no return value.
@comm Setting the iMin and iMax values to the same value will disable
the selected scale.
@xref <c CMeter> <mf CMeter::SetNeedleColor> <mf CMeter::Create> <mf CMeter::SetScaleSplit>
<mf CMeter::SetScaleColor> <mf CMeter::SetTextColor> <mf CMeter::SetValue>
*/

void CMeter::SetScale(int iMin, int iMax, int iScale)
{
    ASSERT((iScale >= 0) && (iScale < MAXSCALES));
    ASSERT(iMax >= iMin);
    m_Scale[iScale].iMin = iMin;
    m_Scale[iScale].iMax = iMax;
    m_Scale[iScale].iValue = InRange(m_Scale[iScale].iValue,
                                     iScale);
}

/*
@mfunc void | CMeter | SetNeedleColor | Set the color of a meter needle.
@syntax void SetNeedleColor(COLORREF clr, int iScale = 0);
@parm COLORREF | clr | The color of the needle.
@parm int | iScale | The index of the needle to set.
@rdesc There is no return value.
@xref <c CMeter> <mf CMeter::SetScale> <mf CMeter::Create> <mf CMeter::SetScaleSplit>
<mf CMeter::SetScaleColor> <mf CMeter::SetTextColor> <mf CMeter::SetValue>
*/

void CMeter::SetNeedleColor(COLORREF clr, int iScale)
{
    ASSERT((iScale >= 0) && (iScale < MAXSCALES));
    m_Scale[iScale].clr = clr;
}

// Computer a bounding rectange for the needle
void CMeter::GetNeedleRect(CRect* pRect, METERSCALE* ps)
{
    pRect->top = ps->ptEnd.y;
    pRect->bottom = m_ptCenter.y;
    if (ps->ptEnd.x <= m_ptCenter.x) {
        pRect->left = ps->ptEnd.x;
        pRect->right = m_ptCenter.x;
    } else {
        pRect->right = ps->ptEnd.x;
        pRect->left = m_ptCenter.x;
    }
}

void CMeter::ComputeNeedleEnd(CPoint* pPt, int iValue, METERSCALE* ps)
{
    pPt->x = (iValue - ps->iMin) * m_iWidth
                   / (ps->iMax - ps->iMin);
    pPt->y = m_iHeight / 8;

}

/*
@mfunc void | CMeter | SetValue | Set the value of a meter needle.
@syntax void SetValue(int iValue, int iScale = 0);
@parm int | iValue | The value of the needle.
@parm int | iScale | The index of the needle to set.
@rdesc There is no return value.
@comm If the value is less than the scale minimum, the needle is
set to the minimum position. If the value is greater than the maximum
value, the needle is set to the maximum value.
@xref <c CMeter> <mf CMeter::SetScale> <mf CMeter::Create> <mf CMeter::SetScaleSplit>
<mf CMeter::SetScaleColor> <mf CMeter::SetTextColor> <mf CMeter::SetNeedleColor>
*/

void CMeter::SetValue(int iValue, int iScale)
{
    ASSERT((iScale >= 0) && (iScale < MAXSCALES));
    METERSCALE* ps = &m_Scale[iScale];
    if (iValue == ps->iValue) return; // no change
    // Compute a clip rect for the old needle position
    CRect rcOld;
    GetNeedleRect(&rcOld, ps);

    ps->iValue = InRange(iValue, iScale);

    // Compute the new needle position
    ComputeNeedleEnd(&ps->ptEnd, ps->iValue, ps);
    CRect rcNew;
    GetNeedleRect(&rcNew, ps);

    // Compute the area to be redrawn as the union of old and new
    CRect rcDraw = rcOld | rcNew;
    // Inflate the rect slightly to account for the width of
    // the pen
    rcDraw.InflateRect(2, 2);
    // move the bottom of the region up to where the cover ends
    rcDraw.bottom = m_iHeight * 3 / 4;

    // Draw the changes
    Render(&rcDraw);
    Draw(&rcDraw);
}

// Render the current image to the os-buffer
void CMeter::Render(const CRect* pClipRect)
{
    // Copy the top 3/4 of the image (scale bkgnd) to the buffer
    CDC* pdcBuffer = m_dsBuffer.GetDC();
    pdcBuffer->SelectClipRgn(NULL); // reset clip region
    if (pClipRect) {
        pdcBuffer->IntersectClipRect(pClipRect);
    }
    m_dsImage.BitBlt(pdcBuffer, 
                     0, 0,
                     m_iWidth, m_iHeight * 3 / 4,
                     0, 0);

    // Draw each scale needle
    METERSCALE* ps = m_Scale;
    for (int i = 0; i < MAXSCALES; i++) {
        if (ps->iMax != ps->iMin) {    
            CPen pen (PS_SOLID, 2, ps->clr);
            CPen* ppold = pdcBuffer->SelectObject(&pen);
            pdcBuffer->MoveTo(m_ptCenter);
            pdcBuffer->LineTo(ps->ptEnd);
            pdcBuffer->SelectObject(ppold);
        }
        ps++;
    }

    // Copy the left side of the cover
    m_dsImage.BitBlt(pdcBuffer, 
                     0, 0,
                     8, m_iHeight*3/4,
                     0, 0);

    // Copy the right side of the cover
    m_dsImage.BitBlt(pdcBuffer, 
                     m_iWidth-8, 0,
                     8, m_iHeight*3/4,
                     m_iWidth-8, 0);

    // Copy the bottom 1/4 of the image (cover) to the buffer
    m_dsImage.BitBlt(pdcBuffer, 
                     0, m_iHeight*3/4 - 2,
                     m_iWidth, m_iHeight/4 + 2,
                     0, m_iHeight*3/4 - 2);
}

// Draw the image to the window
void CMeter::Draw(const CRect* pClipRect)
{
    CClientDC dc(this);
    CRect rcDraw;

    // see if a clip rect was supplied and use the client area if not
    if (pClipRect) {
        rcDraw = *pClipRect;
    } else {
        GetClientRect(rcDraw);
    }

    // Get the clip box
    CRect rcClip;
    dc.GetClipBox(rcClip);

    // Find a rectangle that describes the intersection of
    // the draw rect and clip rect
    rcDraw &= rcClip;

    // Copy the update rectangle from the off-screen DC to the
    // window DC. Note that DIB origin is lower left corner.
    int w, h, xs, xd, yd, ys;
    w = rcDraw.right - rcDraw.left;
    h = rcDraw.bottom - rcDraw.top;
    xs = xd = rcDraw.left;
    yd = rcDraw.top;
    ys = rcDraw.top;

    // Copy the buffer image to the window
    m_dsBuffer.BitBlt(&dc,
                      xd, yd,
                      w, h,
                      xs, ys);
}

void CMeter::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    Render();
    // Copy the entire buffer image to the window
    m_dsBuffer.Draw(&dc);
}

int CMeter::InRange(int iValue, int iScale)
{
    if (iValue < m_Scale[iScale].iMin) {
        return m_Scale[iScale].iMin;
    }
    if (iValue > m_Scale[iScale].iMax) {
        return m_Scale[iScale].iMax;
    }
    return iValue;
}

/*
@mfunc void | CMeter | SetScaleSplit | Set the split point of scale 0.
@syntax void SetScaleSplit(int ivalue);
@parm int | iValue | The point on the scale at which the color shoul
change.
@rdesc There is no return value.
@xref <c CMeter> <mf CMeter::SetScale> <mf CMeter::Create> <mf CMeter::SetNeedleColor>
<mf CMeter::SetScaleColor> <mf CMeter::SetTextColor> <mf CMeter::SetValue>
*/

void CMeter::SetScaleSplit(int iValue)
{
    m_iScaleSplit = InRange(iValue, 0);
}

/*
@mfunc void | CMeter | SetScaleColor | Set the colors of the meter scale.
@syntax void CMeter::SetScaleColor(COLORREF clrLower, COLORREF clrUpper = 0xFFFFFFFF);
@parm COLORREF | clrLower | The color of the lower part of the scale.
@parm COLORREF | clrUpper | The color of the upper part of the scale.
@rdesc There is no return value.
@comm The upper color may be omitted if the scale has no split.
@xref <c CMeter> <mf CMeter::SetScale> <mf CMeter::Create> <mf CMeter::SetScaleSplit>
<mf CMeter::SetNeedleColor> <mf CMeter::SetTextColor> <mf CMeter::SetValue>
*/

void CMeter::SetScaleColor(COLORREF clrLower, COLORREF clrUpper/*=0xFFFFFFFF*/)
{
    m_clrLowerScale = clrLower;
    if (clrUpper != 0xFFFFFFFF) {
        m_clrUpperScale = clrUpper;
    }
}

/*
@mfunc void | CMeter | SetTextColor | Set the color of the caption text.
@syntax void SetTextColor(COLORREF clr);
@parm COLORREF | clr | The color of the text.
@rdesc There is no return value.
@xref <c CMeter> <mf CMeter::SetScale> <mf CMeter::Create> <mf CMeter::SetScaleSplit>
<mf CMeter::SetScaleColor> <mf CMeter::SetNeedleColor> <mf CMeter::SetValue>
*/

void CMeter::SetTextColor(COLORREF clrText)
{
    m_clrText = clrText;
}
