// RenderStocks.cpp: implementation of the CRenderStocks class.
//
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "RenderStocks.h"
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRenderStocks::CRenderStocks()
: m_pDC(0), m_pBitmap(0), m_textLenInPixels(0)
{
	// load display strings.
	//
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	VERIFY(m_strWaiting.LoadString(IDS_WAITING));
	VERIFY(m_strNoStocks.LoadString(IDS_NO_STOCKS));
	m_strAllStocks = m_strNoStocks;
}

CRenderStocks::~CRenderStocks()
{
	if (m_pDC)
		delete m_pDC;
	if (m_pBitmap)
		delete m_pBitmap;
}


// Iterate through given enumerator and create a string composed of stocks.
// The resulting string will be display in the control.
//
void CRenderStocks::SetData(IEnumString * pEnum)
{
	USES_CONVERSION;
	LPOLESTR    s;

	m_strAllStocks = _T("");
	while (pEnum->Next(1, &s, 0) == S_OK)
	{
		m_strAllStocks += OLE2T(s);
		m_strAllStocks += _T("   ");
		::CoTaskMemFree(s);
	}
	if (m_strAllStocks.IsEmpty())
		m_strAllStocks = m_strNoStocks;

	ReCalcTextLen();
	Reset();
}

// Render the next step in the "scroll" sequence, that is, scroll the text to
// the left.
//
void CRenderStocks::RenderNext()
{
	if (m_textLenInPixels + m_xPosOfText == 0)
		Reset();
	CRect   r = m_rcDCBounds;
	r.left = m_xPosOfText--;
	m_pDC->SetBkColor(m_clrBack);
	m_pDC->FillSolidRect(m_rcDCBounds, m_clrBack);
	m_pDC->SetTextColor(m_clrFore);
	m_pDC->DrawText(m_strAllStocks, -1, r, DT_SINGLELINE | DT_VCENTER);
}

// Reset the rendering at the beginning.  Text scrolls into view from the right, moving to the
// left.  Also start with the first stock.
//
void CRenderStocks::Reset()
{
	m_xPosOfText = m_rcDCBounds.Width();
}

// Return the backbuffer so it can be drawn on to the display DC.
//
CDC* CRenderStocks::GetDC()
{
	return m_pDC;
}

// Set the control for which this rendering object was created for.
// The control is queryed for fore and back color, font and size.
//
void CRenderStocks::Init(CDC* pDC, const CRect& rcBounds)
{
	delete m_pDC;
	m_pDC = new CDC();
	m_pDC->CreateCompatibleDC(pDC);

	SetDCBounds(rcBounds);
	Reset();
}

// Draw current stock animation onto given DC.  That is, draw the draw buffer
// onto given DC.
//
void CRenderStocks::DrawOnto(CDC* pDC, const CRect& rcBounds)
{
	pDC->BitBlt(rcBounds.left, rcBounds.top, rcBounds.Width(), rcBounds.Height(),
				GetDC(), 0, 0, SRCCOPY);

}


// Control has resized, recreate draw buffer and reset.
//
void CRenderStocks::CtrlResized(CDC* pDC, const CRect& rcBounds)
{
	SetDCBounds(rcBounds);
	delete m_pBitmap;
	m_pBitmap = new CBitmap();
	m_pBitmap->CreateCompatibleBitmap(pDC, m_rcDCBounds.Width(),
									  m_rcDCBounds.Height());
	m_pDC->SelectObject(m_pBitmap);

	Reset();
}

// Colors have changed, set cached colors from control.
//
void CRenderStocks::ColorsChanged(COLORREF clrFore, COLORREF clrBack)
{
	m_clrBack = clrBack;
	m_clrFore = clrFore;
}

void CRenderStocks::SetTextToNoStocks()
{
	m_strAllStocks = m_strNoStocks;
	Reset();
}

void CRenderStocks::SetTextToWaiting()
{
	m_strAllStocks = m_strWaiting;
	Reset();
}

// Font has changed, select it into the draw buffer and recalculate text length.
//
void CRenderStocks::FontChanged(CComPtr<IFontDisp>& pFont)
{
	if (pFont && m_pDC)
	{
		CComPtr<IFont> pIFont;
		pFont->QueryInterface(IID_IFont, (void**)&pIFont);
		HFONT hfont;
		pIFont->get_hFont(&hfont);
		m_pDC->SelectObject(hfont);
		ReCalcTextLen();
	}
}

// Calculate text length of currently selected font.
//
void CRenderStocks::ReCalcTextLen()
{
	if (m_pDC)
		m_textLenInPixels = m_pDC->GetTextExtent(m_strAllStocks).cx;
}
