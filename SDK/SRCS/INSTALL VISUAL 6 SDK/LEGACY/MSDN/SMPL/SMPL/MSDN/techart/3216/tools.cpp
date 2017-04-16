////////////////////////////////////////////////////////////////////////////
// tools.cpp

#include "stdafx.h"
#include "MarkPnt.h"
#include "tools.h"

///////////////////////////////////////////////////////////////////////////
// CDrawingTool

IMPLEMENT_DYNCREATE(CDrawingTool, CSprite)

CDrawingTool::CDrawingTool()
{
}

CDrawingTool::~CDrawingTool()
{
}

void CDrawingTool::Load(UINT uiID, CPalette* pPal)
{
    ASSERT(uiID);
    ASSERT(pPal);
    BOOL b = CSprite::Load(uiID);
    ASSERT(b);
    MapColorsToPalette(pPal);
}

///////////////////////////////////////////////////////////////////////////
// CCrayon

CCrayon::CCrayon()
{
}

CCrayon::~CCrayon()
{
}

COLORREF CCrayon::GetColor()
{
    BYTE* p = (BYTE*) GetPixelAddress(5, GetHeight() - 5);
    RGBQUAD* t = GetClrTabAddress();
    return PALETTERGB(t[*p].rgbRed,
                      t[*p].rgbGreen,
                      t[*p].rgbBlue);
}


///////////////////////////////////////////////////////////////////////////
// CEraser

CEraser::CEraser()
{
}

CEraser::~CEraser()
{
}

COLORREF CEraser::GetColor()
{
    return PALETTERGB(178, 178, 178);
}

