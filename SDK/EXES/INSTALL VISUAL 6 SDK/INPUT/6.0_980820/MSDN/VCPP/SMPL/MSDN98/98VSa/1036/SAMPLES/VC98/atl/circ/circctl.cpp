// CircCtl.cpp : Implementation of CcircApp and DLL registration.
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#include "stdafx.h"
#include "circ.h"
#include "CircCtl.h"

//const IID IID__CircEvents = {0x19A4FF37,0x9C7E,0x11CD,{0xAE,0xDC,0x00,0xA0,0xC9,0x03,0x48,0x37}};
// {47536F96-F610-11cf-91F0-00A0C903977F}
const GUID CLSID_CCircProps =
{ 0x47536f96, 0xf610, 0x11cf, { 0x91, 0xf0, 0x0, 0xa0, 0xc9, 0x3, 0x97, 0x7f } };

/////////////////////////////////////////////////////////////////////////////
//

HRESULT CCircCtl::OnDraw(ATL_DRAWINFO& di)
{
	USES_CONVERSION;
	if (di.dwDrawAspect != DVASPECT_CONTENT)
		return E_FAIL;

	HDC hdc = di.hdcDraw;
	HDC hic = di.hicTargetDev;
	if (hic == NULL)
		hic = AtlCreateTargetDC(hdc, di.ptd);
	RECT& rc = *(RECT*)di.prcBounds;

	HPEN hFore;
	HBRUSH hBack;
	COLORREF colBack,colFore;
	OleTranslateColor(m_clrForeColor, m_hPalette, &colFore);
	OleTranslateColor(m_clrBackColor, m_hPalette, &colBack);
	hFore = CreatePen(PS_SOLID, 2, colFore);
	hBack = CreateSolidBrush(colBack);
	HGDIOBJ hOldBrush = SelectObject(hdc, hBack);
	HGDIOBJ hOldPen = SelectObject(hdc, hFore);
	Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
	SetTextColor(hdc, RGB(255, 122, 144));
	SetBkMode(hdc, TRANSPARENT);
	TEXTMETRIC tm;
	GetTextMetrics(hic, &tm);
	LPTSTR szCaption = W2T(m_bstrCaption);
	int cbCaption = lstrlen(szCaption);
	int cHeight = (rc.top > rc.bottom) ? -tm.tmHeight/2 : tm.tmHeight/2;
	HFONT hOldFont = NULL;
	if (m_pFont)
	{
		CComPtr<IFont> pFont;
		m_pFont->QueryInterface(IID_IFont, (void**)&pFont);
		HFONT hfont;
		pFont->get_hFont(&hfont);
		hOldFont = (HFONT) SelectObject(hdc, hfont);
	}
	ExtTextOut(hdc ,
			  rc.left + (rc.right - rc.left)/2 - (tm.tmAveCharWidth*cbCaption)/2,
			  rc.top + (rc.bottom - rc.top)/2 - cHeight, 0, &rc,
			   szCaption, cbCaption, 0);
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hBack);
	if (hOldFont)
		SelectObject(hdc, hOldFont);
	if (hic != hdc)
		DeleteDC(hic);
	DeleteObject(hFore);
	DeleteObject(hBack);
	return 0;
}

STDMETHODIMP CCircCtl::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] =
	{
		&IID_ICircCtl,
	};

	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
