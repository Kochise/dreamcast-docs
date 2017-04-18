// RenderStocks.h: interface for the CRenderStocks class.
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

#if !defined (__RENDERSTOCKS_H__)
#define __RENDERSTOCKS_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//////////////////////////////////////////////////////////////////////////////
// CRenderStocks
//
// Draws stock information into a draw buffer, stepping to the left on each pass.
// Later is drawn onto a DC supplied by the control.
//
class CRenderStocks
{
public:
	CRenderStocks();
	virtual ~CRenderStocks();

	void            Reset();
	void            RenderNext();
	void            SetData(IEnumString* pEnum);
	CDC*            GetDC();
	void            Init(CDC* pDC, const CRect& rcBounds);
	void            CtrlResized(CDC* pDC, const CRect& rcBounds);
	void            DrawOnto(CDC* pDC, const CRect& rcBounds);
	void            FontChanged(CComPtr<IFontDisp>& pFont);
	void            ColorsChanged(COLORREF clrFore, COLORREF clrBack);
	void            SetTextToNoStocks();
	void            SetTextToWaiting();

protected:
	int             m_xPosOfText;       // x position of text being rendered.
	CString         m_strAllStocks;     // string containing all the stock info
										// being rendered.
	CDC*            m_pDC;              // draw buffer to render on.
	CBitmap*        m_pBitmap;          // bitmap object.
	COLORREF        m_clrBack;          // background color.
	COLORREF        m_clrFore;          // text color.
	CRect           m_rcDCBounds;       // control bounds.
	int             m_textLenInPixels;  // text length.
	CString         m_strWaiting;       // display string when stock info is
										// being downloaded from web.
	CString         m_strNoStocks;      // display string when there are no
										// stocks to be shown.
	void            ReCalcTextLen();

	// need to offset the give rect to 0,0 for the render DC.
	// Windowed activation will already be at 0,0 but windowless activation
	// may not be.
	//
	void            SetDCBounds(const CRect& r)
	{
		m_rcDCBounds = r;
		m_rcDCBounds.OffsetRect(-m_rcDCBounds.left, -m_rcDCBounds.top);
	}
};

#endif // __RENDERSTOCKS_H__
