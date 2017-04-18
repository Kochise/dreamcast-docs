// sprite.cpp : implementation file
//

#include "stdafx.h"
#include "gravity.h"
#include "sprite.h"
#include "spriteno.h"
#include "spritedl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSprite

IMPLEMENT_SERIAL(CSprite, CObject, 0 /* schema number*/ )

CSprite::CSprite()
{
    m_x = 0;
    m_y = 0;
    m_z = 50;
    m_bTrans = 0;
    m_pNotifyObj = NULL;
}

CSprite::~CSprite()
{
}

/////////////////////////////////////////////////////////////////////////////
// CSprite serialization

void CSprite::Serialize(CArchive& ar)
{
    CDIB::Serialize(ar);
    if (ar.IsStoring()) {
        ar << (DWORD) m_x;
        ar << (DWORD) m_y;
        ar << (DWORD) m_z;
    } else {
        DWORD dw;
        ar >> dw; m_x = (int) dw;
        ar >> dw; m_y = (int) dw;
        ar >> dw; m_z = (int) dw;
        // now generate the other parameters from the DIB
        m_bTrans = GetPixelValue(0,0);
    }
}

/////////////////////////////////////////////////////////////////////////////
// CSprite commands

// Initialize all the sprite parameters 
// which are based on the image
void CSprite::InitFromDIB()
{
    m_bTrans = GetPixelValue(0, 0);
}

// Load a sprite image from a disk file
BOOL CSprite::Load(LPSTR pszFileName)
{
    if (!CDIB::Load(pszFileName)) {
        TRACE("Failed to load");
        return FALSE;
    }
    InitFromDIB();
    return TRUE;
}

// Load a sprite image from a disk file
BOOL CSprite::Load(CFile *fp)
{
    if (!CDIB::Load(fp)) {
        TRACE("Failed to load");
        return FALSE;
    }
    InitFromDIB();
    return TRUE;
}

// Set the Z order
void CSprite::SetZ(int z)
{
    if (m_z != z) {
        m_z = z;
        // See if we have to notify anyone
        if (m_pNotifyObj) {
            m_pNotifyObj->Change(this, CSpriteNotifyObj::ZORDER);
        }
    }
}

// Test for a hit in a non-transparent area
BOOL CSprite::HitTest(CPoint point)
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


// set a new x,y position
void CSprite::SetPosition(int x, int y)
{
    // Save the current position
    CRect rcOld;
    GetRect(&rcOld);
    // move to new position
    m_x = x;
    m_y = y;
    CRect rcNew;
    GetRect(&rcNew);
    // notify that we have moved from our old position to
    // our new position
    if (m_pNotifyObj) {
        m_pNotifyObj->Change(this, 
                             CSpriteNotifyObj::POSITION,
                             &rcOld,
                             &rcNew);
    }
}

                                                  
// Render a sprite to a DIB
void CSprite::Render(CDIB *pDIB, LPRECT pClipRect)
{
    ASSERT(pDIB);
    ASSERT(pClipRect);
    // Get the sprite rect and see if it's visible
    CRect rcDraw;
    GetRect(&rcDraw);
    if (!rcDraw.IntersectRect(pClipRect, &rcDraw)) {
        return; // not visible
    }
    CopyBits(pDIB,        // dest DIB
             rcDraw.left,                   // dest x
             rcDraw.top,                  // dest y
             rcDraw.right - rcDraw.left,    // width
             rcDraw.bottom - rcDraw.top,    // height
             rcDraw.left - m_x, // source x
             rcDraw.top - m_y,  // source y
             PALETTEINDEX(m_bTrans));     // trans color index
}

// Map the image colors to a given palette
int CSprite::MapColorsToPalette(CPalette *pPal)
{
    int i = CDIB::MapColorsToPalette(pPal);
    InitFromDIB(); // reset transparency index value
    return i;
}
