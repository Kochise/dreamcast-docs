// phsprite.cpp : implementation file
//

#include "stdafx.h"
#include "gravity.h"
#include "phsprite.h"
#include "spriteno.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhasedSprite

IMPLEMENT_SERIAL(CPhasedSprite, CSprite, 0 /* schema number*/ )

CPhasedSprite::CPhasedSprite()
{
    m_iPhaseHeight = CSprite::GetHeight();
    m_iNumPhases = 1;
    m_iPhase = 0;
}

CPhasedSprite::~CPhasedSprite()
{
}

/////////////////////////////////////////////////////////////////////////////
// CPhasedSprite serialization

void CPhasedSprite::Serialize(CArchive& ar)
{
    CSprite::Serialize(ar);
    if (ar.IsStoring())
    {
        ar << (DWORD) m_iNumPhases;
        ar << (DWORD) m_iPhase;
    }
    else
    {
        DWORD dw;
        ar >> dw; m_iNumPhases = (int) dw;
        ar >> dw; m_iPhase = (int) dw;
        // now generate the other parameters
        SetNumPhases(m_iNumPhases);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CPhasedSprite commands

// Do any initialization after file load etc.
void CPhasedSprite::InitFromDIB()
{
    CSprite::InitFromDIB();
    m_iPhaseHeight = CSprite::GetHeight();
    m_iNumPhases = 1;
    m_iPhase = 0;
}


// get the bounding rectangle
void CPhasedSprite::GetRect(LPRECT pRect)
{
    ASSERT(pRect);
    pRect->left = m_x;
    pRect->top = m_y;
    pRect->right = m_x + GetWidth();
    pRect->bottom = m_y + GetHeight();
}

// Test for a hit in a non-transparent area
BOOL CPhasedSprite::HitTest(CPoint point)
{
    // Test if the point is inside the sprite rectangle
    if ((point.x > m_x) 
    && (point.x < m_x + GetWidth())
    && (point.y > m_y)
    && (point.y < m_y + GetHeight())) {
//        dprintf4("Hit is in sprite rect");
        // See if this point is transparent by testing to
        // see if the pixel value is the same as the top
        // left corner value.  Note that top left of the
        // image is bottom left in the DIB.
        if (GetPixelValue(point.x - m_x, point.y - m_y) != m_bTrans) {
            return TRUE;
        }
    }
    return FALSE;
}

// Divide the DIB into a given number of phases
BOOL CPhasedSprite::SetNumPhases(int iPhases)
{
    if (iPhases < 1) {
        TRACE("Invalid number of phases");
        return FALSE;
    }
    // compute the height of each phase
    int iPhaseHeight = CSprite::GetHeight() / iPhases;
    if (iPhaseHeight < 1) {
        TRACE("Can't make them that small");
        return FALSE;
    }
    // set the new height and phase count
    m_iNumPhases = iPhases;
    m_iPhase = 0;
    m_iPhaseHeight = iPhaseHeight;
    return TRUE;
}

// set the current phase
BOOL CPhasedSprite::SetPhase(int iPhase)
{
    if (iPhase >= m_iNumPhases) {
        TRACE("Invalid phase");
        return FALSE;
    }
    if (iPhase == m_iPhase) return FALSE;
    m_iPhase = iPhase;
    // send a notification to redraw
   if (m_pNotifyObj) {
        CRect rcPos;
        GetRect(&rcPos);
        m_pNotifyObj->Change(this, 
                            CSpriteNotifyObj::IMAGE,
                            &rcPos);
   }
   return TRUE;
}
                                                  
// Render a sprite to a DIB
void CPhasedSprite::Render(CDIB *pDIB, LPRECT pClipRect)
{
    ASSERT(pDIB);
    ASSERT(pClipRect);
    // Get the sprite rect and see if it's visible
    CRect rcDraw;
    GetRect(&rcDraw);
    if (!rcDraw.IntersectRect(pClipRect, &rcDraw)) {
        return; // not visible
    }
    // modify the source y value for the current phase of the sprite
    int ys = rcDraw.top - m_y + m_iPhase * m_iPhaseHeight;
    ASSERT(ys >= 0 && ys < CSprite::GetHeight());
    CopyBits(pDIB,        // dest DIB
             rcDraw.left,                   // dest x
             rcDraw.top,                  // dest y
             rcDraw.right - rcDraw.left,    // width
             rcDraw.bottom - rcDraw.top,    // height
             rcDraw.left - m_x, // source x
             ys,                            // source y
             PALETTEINDEX(m_bTrans));     // trans color index
}
