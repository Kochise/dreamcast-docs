// sprite.cpp : implementation file
// @doc

#include "stdafx.h"
#include "animate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSprite

IMPLEMENT_SERIAL(CSprite, CDIB, 0 /* schema number*/ )

CSprite::CSprite()
{
    m_x = 0;
    m_y = 0;
    m_z = 50;
    m_bTransIndex = 0;
    m_pNotifyObj = NULL;
}

CSprite::~CSprite()
{
}

// Set the initial state of the sprite from its DIB image
void CSprite::Initialize()
{
    // Get the address of the top, left pixel
    BYTE* p = (BYTE*)GetPixelAddress(0, 0);
    ASSERT(p);
    // get the pixel value and save it
    m_bTransIndex = *p;
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
        Initialize();
    }
}

/////////////////////////////////////////////////////////////////////////////
// CSprite commands

/*
@mfunc void | CSprite | Render | Render the sprite image to a DIB.
@syntax virtual void Render(CDIB* pDIB, CRect* pClipRect = NULL);
@rdesc The return value is the X coordinate of the sprite.
@comm If no clip rectangle is supplied, the entire image is rendered.
@xref <c CSprite> <c CDIB>
*/

void CSprite::Render(CDIB* pDIB, CRect* pClipRect)
{
    ASSERT(pDIB);

    // Get the sprite rectangle
    CRect rcDraw;
    GetRect(&rcDraw);

    // If a clip rectangle was supplied, see if the sprite
    // is visible in the rectangle
    if (pClipRect) {
        if (!rcDraw.IntersectRect(pClipRect, &rcDraw)) {
            return; // not visible
        }
    }
    // Copy the image of the sprite
    CopyBits(pDIB,        // dest DIB
             rcDraw.left,                   // dest x
             rcDraw.top,                  // dest y
             rcDraw.right - rcDraw.left,    // width
             rcDraw.bottom - rcDraw.top,    // height
             rcDraw.left - m_x, // source x
             rcDraw.top - m_y,  // source y
             PALETTEINDEX(m_bTransIndex));     // trans color index
}

// Load a sprite image from a disk file
BOOL CSprite::Load(char* pszFileName)
{
    if (!CDIB::Load(pszFileName)) {
        return FALSE;
    }
    Initialize();
    return TRUE;
}

// Load a sprite image from a disk file
BOOL CSprite::Load(CFile *fp)
{
    if (!CDIB::Load(fp)) {
        return FALSE;
    }
    Initialize();
    return TRUE;
}

// Load a sprite image from a resource
BOOL CSprite::Load(WORD wResid)
{
    if (!CDIB::Load(wResid)) {
        return FALSE;
    }
    Initialize();
    return TRUE;
}

// Map colors to palette 
BOOL CSprite::MapColorsToPalette(CPalette *pPal)
{
    BOOL bResult = CDIB::MapColorsToPalette(pPal);
    // get the transparency info again
    // Note: local call only don't any derived class
    CSprite::Initialize();
    return bResult;
}

// get the bounding rectangle
void CSprite::GetRect(RECT* pRect)
{
    ASSERT(pRect);
    pRect->left = m_x;
    pRect->top = m_y;
    pRect->right = m_x + GetWidth();
    pRect->bottom = m_y + GetHeight();
}

/*
@mfunc void | CSprite | HitTest | Test for a hit in a non-transparent area
of the sprite.
@syntax virtual BOOL HitTest(CPoint point);
@parm CPoint | point | The coordinate to test.
@rdesc The return value is TRUE if the test coordinate lies in
a visible part of the sprite image.
@comm The coordinate must be relative to the top-left corner of the
window containing the sprite.
@xref <c CSprite> <c CDIB>
*/

// Test for a hit in a non-transparent area
BOOL CSprite::HitTest(CPoint point)
{
    // Test if the point is inside the sprite rectangle
    if ((point.x > m_x) 
    && (point.x < m_x + GetWidth())
    && (point.y > m_y)
    && (point.y < m_y + GetHeight())) {
        // See if this point is transparent by testing to
        // see if the pixel value is the same as the top
        // left corner value.  Note that top left of the
        // image is bottom left in the DIB.
        BYTE* p = (BYTE*)GetPixelAddress(point.x - m_x, point.y - m_y);
        if (*p != m_bTransIndex) {
            return TRUE; // hit
        }
    }
    return FALSE;
}

/*
@mfunc void | CSprite | SetPosition | Set new X and Y coordinates.
@syntax virtual void SetPosition(int x, int y);
@parm int | x | The X coordinate.
@parm int | y | The Y coordinate.
@rdesc There is no return value.
@comm The coordinate must be relative to the top-left corner of the
window containing the sprite. If a notification object has been set it's
Change function is called with CSpriteNotifyObj::POSITION to inform it
of the position change.
@xref <c CSprite> <c CDIB>
*/

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

/*
@mfunc void | CSprite | SetZ | Set a new Z order value.
@syntax virtual void SetZ(int z);
@parm int | z | The Z order value.
@rdesc There is no return value.
@comm If a notification object has been set it's
Change function is called with CSpriteNotifyObj::ZORDER to inform it
of the z order change.
@xref <c CSprite> <c CDIB>
*/

// Set a new Z order
void CSprite::SetZ(int z)
{
    if (m_z != z) {
        m_z = z;
        // See if we have to notify anyone
        if (m_pNotifyObj) {
            CRect rc;
            GetRect(&rc);
            m_pNotifyObj->Change(this,
                                 CSpriteNotifyObj::ZORDER,
                                 &rc);
        }
    }
}
