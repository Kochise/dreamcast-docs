// toolbar.cpp : definition of old backward compatible CToolBar
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
#define _AFX_NO_OLE_SUPPORT
#include <afxpriv.h>
#include "toolbar.h"
#include "globals.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define new DEBUG_NEW

// globals for fast drawing (shared globals)
static HDC hDCGlyphs = NULL;
static HDC hDCMono = NULL;
static HBRUSH hbrDither = NULL;

/////////////////////////////////////////////////////////////////////////////
// Init / Term

static HBITMAP AFXAPI CreateDitherBitmap();

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif


// a special struct that will cleanup automatically
struct _AFX_TOOLBAR_TERM
{
	~_AFX_TOOLBAR_TERM()
	{
		AfxDeleteObject((HGDIOBJ*)&hDCMono);
		AfxDeleteObject((HGDIOBJ*)&hDCGlyphs);
		AfxDeleteObject((HGDIOBJ*)&hbrDither);
	}
};

static const _AFX_TOOLBAR_TERM toolbarTerm;

/////////////////////////////////////////////////////////////////////////////

#ifdef AFX_CORE3_SEG
#pragma code_seg(AFX_CORE3_SEG)
#endif

static HBITMAP AFXAPI CreateDitherBitmap()
{
	struct  // BITMAPINFO with 16 colors
	{
		BITMAPINFOHEADER bmiHeader;
		RGBQUAD      bmiColors[16];
	} bmi;
	memset(&bmi, 0, sizeof(bmi));

	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = 8;
	bmi.bmiHeader.biHeight = 8;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 1;
	bmi.bmiHeader.biCompression = BI_RGB;

	COLORREF clr = ::GetSysColor(COLOR_BTNFACE);
	bmi.bmiColors[0].rgbBlue = GetBValue(clr);
	bmi.bmiColors[0].rgbGreen = GetGValue(clr);
	bmi.bmiColors[0].rgbRed = GetRValue(clr);

	clr = ::GetSysColor(COLOR_BTNHIGHLIGHT);
	bmi.bmiColors[1].rgbBlue = GetBValue(clr);
	bmi.bmiColors[1].rgbGreen = GetGValue(clr);
	bmi.bmiColors[1].rgbRed = GetRValue(clr);

	// initialize the brushes
	long patGray[8];
	for (int i = 0; i < 8; i++)
	   patGray[i] = (i & 1) ? 0xAAAA5555L : 0x5555AAAAL;

	HDC hDC = GetDC(NULL);
	HBITMAP hbm = CreateDIBitmap(hDC, &bmi.bmiHeader, CBM_INIT,
		(LPBYTE)patGray, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS);
	ReleaseDC(NULL, hDC);

	return hbm;
}

// create a mono bitmap mask:
void CToolBar::CreateMask(int iImage, CPoint ptOffset,
	 BOOL bHilite, BOOL bHiliteShadow)
{
	// initalize whole area with 0's
	PatBlt(hDCMono, 0, 0, m_sizeButton.cx-2, m_sizeButton.cy-2, WHITENESS);

	// create mask based on color bitmap
	// convert this to 1's
	SetBkColor(hDCGlyphs, globalData.clrBtnFace);
	BitBlt(hDCMono, ptOffset.x, ptOffset.y, m_sizeImage.cx, m_sizeImage.cy,
		hDCGlyphs, iImage * m_sizeImage.cx, 0, SRCCOPY);

	if (bHilite)
	{
		// convert this to 1's
		SetBkColor(hDCGlyphs, globalData.clrBtnHilite);

		// OR in the new 1's
		BitBlt(hDCMono, ptOffset.x, ptOffset.y, m_sizeImage.cx, m_sizeImage.cy,
			hDCGlyphs, iImage * m_sizeImage.cx, 0, SRCPAINT);

		if (bHiliteShadow)
			BitBlt(hDCMono, 1, 1, m_sizeButton.cx-3, m_sizeButton.cy-3,
				hDCMono, 0, 0, SRCAND);
	}
}

// Raster Ops
#define ROP_DSPDxax  0x00E20746L
#define ROP_PSDPxax  0x00B8074AL

BOOL CToolBar::DrawButton(CDC* pDC, int x, int y, int iImage, UINT nStyle)
{
	ASSERT_VALID(pDC);

	int dx = m_sizeButton.cx;
	int dy = m_sizeButton.cy;
	if (!globalData.bWin4)
	{
		// make the coordinates the interior of the button
		x += 1;
		y += 1;
		dx -= 2;
		dy -= 2;

		// border around button
		pDC->FillSolidRect(x,    y-1,    dx, 1,  globalData.clrWindowFrame);
		pDC->FillSolidRect(x,    y+dy,   dx, 1,  globalData.clrWindowFrame);
		pDC->FillSolidRect(x-1,  y,  1,  dy, globalData.clrWindowFrame);
		pDC->FillSolidRect(x+dx, y,  1,  dy, globalData.clrWindowFrame);
	}

	// interior grey
	pDC->FillSolidRect(x, y, dx, dy, globalData.clrBtnFace);

	// determine offset of bitmap (centered within button)
	CPoint ptOffset;
	ptOffset.x = (dx - m_sizeImage.cx - 1) / 2;
	ptOffset.y = (dy - m_sizeImage.cy) / 2;

	if (nStyle & (TBBS_PRESSED | TBBS_CHECKED))
	{
		// pressed in or checked
		pDC->Draw3dRect(x, y, dx, dy,
			globalData.bWin4 ? globalData.clrWindowFrame : globalData.clrBtnShadow,
			globalData.bWin4 ? globalData.clrBtnHilite : globalData.clrBtnFace);

		if (globalData.bWin4)
		{
			pDC->Draw3dRect(x + 1, y + 1, dx - 2, dy - 2,
				globalData.clrBtnShadow, globalData.clrBtnFace);
		}

		// for any depressed button, add one to the offsets.
		ptOffset.x += 1;
		ptOffset.y += 1;
	}
	else
	{
		// regular button look
		pDC->Draw3dRect(x, y, dx, dy, globalData.clrBtnHilite,
			globalData.bWin4 ? globalData.clrWindowFrame : globalData.clrBtnShadow);
		pDC->Draw3dRect(x + 1, y + 1, dx - 2, dy - 2,
			globalData.clrBtnFace, globalData.clrBtnShadow);
	}

	if ((nStyle & TBBS_PRESSED) || !(nStyle & TBBS_DISABLED))
	{
		// normal image version
		BitBlt(pDC->m_hDC, x + ptOffset.x, y + ptOffset.y,
			m_sizeImage.cx, m_sizeImage.cy,
			hDCGlyphs, iImage * m_sizeImage.cx, 0, SRCCOPY);

		if (nStyle & TBBS_PRESSED)
			return TRUE;        // nothing more to do (rest of style is ignored)
	}

	if (nStyle & (TBBS_DISABLED | TBBS_INDETERMINATE))
	{
		// disabled or indeterminate version
		CreateMask(iImage, ptOffset, TRUE, FALSE);

		pDC->SetTextColor(0L);                  // 0's in mono -> 0 (for ROP)
		pDC->SetBkColor((COLORREF)0x00FFFFFFL); // 1's in mono -> 1

		if (nStyle & TBBS_DISABLED)
		{
			// disabled - draw the hilighted shadow
			HGDIOBJ hbrOld = pDC->SelectObject(globalData.hbrBtnHilite);
			if (hbrOld != NULL)
			{
				// draw hilight color where we have 0's in the mask
				BitBlt(pDC->m_hDC, x + 1, y + 1,
					m_sizeButton.cx - 2, m_sizeButton.cy - 2,
					hDCMono, 0, 0, ROP_PSDPxax);
				pDC->SelectObject(hbrOld);
			}
		}

		//BLOCK: always draw the shadow
		{
			HGDIOBJ hbrOld = pDC->SelectObject(globalData.hbrBtnShadow);
			if (hbrOld != NULL)
			{
				// draw the shadow color where we have 0's in the mask
				BitBlt(pDC->m_hDC, x, y,
					m_sizeButton.cx - 2, m_sizeButton.cy - 2,
					hDCMono, 0, 0, ROP_PSDPxax);
				pDC->SelectObject(hbrOld);
			}
		}
	}

	// if it is checked do the dither brush avoiding the glyph
	if (nStyle & (TBBS_CHECKED | TBBS_INDETERMINATE))
	{
		HGDIOBJ hbrOld = pDC->SelectObject(hbrDither);
		if (hbrOld != NULL)
		{
			ptOffset.x -= globalData.cxBorder2;
			ptOffset.y -= globalData.cyBorder2;
			CreateMask(iImage, ptOffset, ~(nStyle & TBBS_INDETERMINATE),
					nStyle & TBBS_DISABLED);

			pDC->SetTextColor(0L);              // 0 -> 0
			pDC->SetBkColor((COLORREF)0x00FFFFFFL); // 1 -> 1

			ASSERT(globalData.cxBorder2 == globalData.cyBorder2);
			int delta = (nStyle & TBBS_INDETERMINATE) ?
				globalData.bWin4 ? globalData.cxBorder2*2 : 3 : globalData.cxBorder2*2;

			// only draw the dither brush where the mask is 1's
			BitBlt(pDC->m_hDC,
				x + globalData.cxBorder2, y + globalData.cyBorder2, dx-delta, dy-delta,
				hDCMono, 0, 0, ROP_DSPDxax);
			pDC->SelectObject(hbrOld);
		}
	}

	return TRUE;
}

BOOL CToolBar::PrepareDrawButton(DrawState& ds)
{
	ASSERT(m_hbmImageWell != NULL);
	ASSERT(m_sizeButton.cx > 2 && m_sizeButton.cy > 2);

	// We need to kick-start the bitmap selection process.
	ds.hbmOldGlyphs = (HBITMAP)SelectObject(hDCGlyphs, m_hbmImageWell);
	ds.hbmMono = CreateBitmap(m_sizeButton.cx-2, m_sizeButton.cy-2,
					1, 1, NULL);
	ds.hbmMonoOld = (HBITMAP)SelectObject(hDCMono, ds.hbmMono);
	if (ds.hbmOldGlyphs == NULL || ds.hbmMono == NULL || ds.hbmMonoOld == NULL)
	{
		TRACE0("Error: can't draw toolbar.\n");
		AfxDeleteObject((HGDIOBJ*)&ds.hbmMono);
		return FALSE;
	}
	return TRUE;
}

void CToolBar::EndDrawButton(DrawState& ds)
{
	SelectObject(hDCMono, ds.hbmMonoOld);
	AfxDeleteObject((HGDIOBJ*)&ds.hbmMono);
	SelectObject(hDCGlyphs, ds.hbmOldGlyphs);
}

/////////////////////////////////////////////////////////////////////////////
// CToolBar creation etc

struct AFX_TBBUTTON
{
	UINT nID;        // Command ID that this button sends
	UINT nStyle;    // TBBS_ styles
	int iImage;     // index into mondo bitmap of this button's picture
						// or size of this spacer
};

inline AFX_TBBUTTON* CToolBar::_GetButtonPtr(int nIndex) const
{
	ASSERT(nIndex >= 0 && nIndex < m_nCount);
	ASSERT(m_pData != NULL);
	return ((AFX_TBBUTTON*)m_pData) + nIndex;
}

/*
	DIBs use RGBQUAD format:
		0xbb 0xgg 0xrr 0x00

	Reasonably efficient code to convert a COLORREF into an
	RGBQUAD is byte-order-dependent, so we need different
	code depending on the byte order we're targeting.
*/
#define RGB_TO_RGBQUAD(r,g,b)   (RGB(b,g,r))
#define CLR_TO_RGBQUAD(clr)     (RGB(GetBValue(clr), GetGValue(clr), GetRValue(clr)))

HBITMAP AFXAPI LoadSysColorBitmap(HINSTANCE hInst, HRSRC hRsrc)
{
	struct COLORMAP
	{
		// use DWORD instead of RGBQUAD so we can compare two RGBQUADs easily
		DWORD rgbqFrom;
		int iSysColorTo;
	};
	static const COLORMAP sysColorMap[] =
	{
		// mapping from color in DIB to system color
		{ RGB_TO_RGBQUAD(0x00, 0x00, 0x00),  COLOR_BTNTEXT },       // black
		{ RGB_TO_RGBQUAD(0x80, 0x80, 0x80),  COLOR_BTNSHADOW },     // dark grey
		{ RGB_TO_RGBQUAD(0xC0, 0xC0, 0xC0),  COLOR_BTNFACE },       // bright grey
		{ RGB_TO_RGBQUAD(0xFF, 0xFF, 0xFF),  COLOR_BTNHIGHLIGHT }   // white
	};
	const int nMaps = 4;

	HGLOBAL hglb;
	if ((hglb = ::LoadResource(hInst, hRsrc)) == NULL)
		return NULL;

	LPBITMAPINFOHEADER lpBitmap = (LPBITMAPINFOHEADER)LockResource(hglb);
	if (lpBitmap == NULL)
		return NULL;

	// make copy of BITMAPINFOHEADER so we can modify the color table
	const int nColorTableSize = 16;
	UINT nSize = lpBitmap->biSize + nColorTableSize * sizeof(RGBQUAD);
	LPBITMAPINFOHEADER lpBitmapInfo = (LPBITMAPINFOHEADER)::malloc(nSize);
	if (lpBitmapInfo == NULL)
		return NULL;
	memcpy(lpBitmapInfo, lpBitmap, nSize);

	// color table is in RGBQUAD DIB format
	DWORD* pColorTable =
		(DWORD*)(((LPBYTE)lpBitmapInfo) + (UINT)lpBitmapInfo->biSize);

	for (int iColor = 0; iColor < nColorTableSize; iColor++)
	{
		// look for matching RGBQUAD color in original
		for (int i = 0; i < nMaps; i++)
		{
			if (pColorTable[iColor] == sysColorMap[i].rgbqFrom)
			{
				pColorTable[iColor] =
					CLR_TO_RGBQUAD(::GetSysColor(sysColorMap[i].iSysColorTo));
				break;
			}
		}
	}

	int nWidth = (int)lpBitmapInfo->biWidth;
	int nHeight = (int)lpBitmapInfo->biHeight;
	HDC hDCScreen = ::GetDC(NULL);
	HBITMAP hbm = ::CreateCompatibleBitmap(hDCScreen, nWidth, nHeight);
	::ReleaseDC(NULL, hDCScreen);

	if (hbm != NULL)
	{
		HBITMAP hbmOld = (HBITMAP)::SelectObject(hDCGlyphs, hbm);

		LPBYTE lpBits;
		lpBits = (LPBYTE)(lpBitmap + 1);
		lpBits += (1 << (lpBitmapInfo->biBitCount)) * sizeof(RGBQUAD);

		StretchDIBits(hDCGlyphs, 0, 0, nWidth, nHeight, 0, 0, nWidth, nHeight,
			lpBits, (LPBITMAPINFO)lpBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
		SelectObject(hDCGlyphs, hbmOld);
	}

	// free copy of bitmap info struct and resource itself
	::free(lpBitmapInfo);
	::FreeResource(hglb);

	return hbm;
}

#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

CToolBar::CToolBar()
{
	m_hbmImageWell = NULL;
	m_hInstImageWell = NULL;
	m_hRsrcImageWell = NULL;
	m_iButtonCapture = -1;      // nothing captured

	// UISG standard sizes
	m_sizeButton.cx = 24;
	m_sizeButton.cy = 22;
	m_sizeImage.cx = 16;
	m_sizeImage.cy = 15;
	m_cyTopBorder = m_cyBottomBorder = 3;   // 3 pixel for top/bottom gaps

	// adjust sizes when running on Win4
	if (globalData.bWin4)
	{
		m_sizeButton.cx = 23;
		m_cySharedBorder = m_cxSharedBorder = 0;
		m_cxDefaultGap = 8;
	}
	else
	{
		m_cxDefaultGap = 6;
		m_cySharedBorder = m_cxSharedBorder = 1;
	}

	// initialize the toolbar drawing engine
	static BOOL bInitialized;
	if (!bInitialized)
	{
		hDCGlyphs = CreateCompatibleDC(NULL);

		// Mono DC and Bitmap for disabled image
		hDCMono = ::CreateCompatibleDC(NULL);

		HBITMAP hbmGray = ::CreateDitherBitmap();
		if (hbmGray != NULL)
		{
			ASSERT(hbrDither == NULL);
			hbrDither = ::CreatePatternBrush(hbmGray);
			AfxDeleteObject((HGDIOBJ*)&hbmGray);
		}

		if (hDCGlyphs == NULL || hDCMono == NULL || hbrDither == NULL)
			AfxThrowResourceException();
		bInitialized = TRUE;
	}
}

CToolBar::~CToolBar()
{
	AfxDeleteObject((HGDIOBJ*)&m_hbmImageWell);
}

BOOL CToolBar::Create(CWnd* pParentWnd, DWORD dwStyle, UINT nID)
{
	if (pParentWnd != NULL)
		ASSERT_VALID(pParentWnd);   // must have a parent

	// save the style
	m_dwStyle = (dwStyle & CBRS_ALL);
	if (nID == AFX_IDW_TOOLBAR)
		m_dwStyle |= CBRS_HIDE_INPLACE;

	// create the HWND
	CRect rect;
	rect.SetRectEmpty();
	LPCTSTR lpszClass = AfxRegisterWndClass(0, ::LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_BTNFACE+1), NULL);
	if (!CWnd::Create(lpszClass, NULL, dwStyle, rect, pParentWnd, nID))
		return FALSE;

	// Note: Parent must resize itself for control bar to be resized

	return TRUE;
}

void CToolBar::SetSizes(SIZE sizeButton, SIZE sizeImage)
{
	ASSERT_VALID(this);
	ASSERT(sizeButton.cx > 0 && sizeButton.cy > 0);
	ASSERT(sizeImage.cx > 0 && sizeImage.cy > 0);

	// button must be big enough to hold image + 3 pixels on each side
	ASSERT(sizeButton.cx >= sizeImage.cx + 6);
	ASSERT(sizeButton.cy >= sizeImage.cy + 6);

	m_sizeButton = sizeButton;
	m_sizeImage = sizeImage;

	// set height
	Invalidate();   // just to be nice if called when toolbar is visible
}

void CToolBar::SetHeight(int cyHeight)
{
	ASSERT_VALID(this);

	int nHeight = cyHeight;
	if (m_dwStyle & CBRS_BORDER_TOP)
		cyHeight -= globalData.cyBorder2;
	if (m_dwStyle & CBRS_BORDER_BOTTOM)
		cyHeight -= globalData.cyBorder2;
	m_cyBottomBorder = (cyHeight - m_sizeButton.cy) / 2;
	// if there is an extra pixel, m_cyTopBorder will get it
	m_cyTopBorder = cyHeight - m_sizeButton.cy - m_cyBottomBorder;
	if (m_cyTopBorder < 0)
	{
		TRACE1("Warning: CToolBar::SetHeight(%d) is smaller than button.\n",
			nHeight);
		m_cyBottomBorder += m_cyTopBorder;
		m_cyTopBorder = 0;  // will clip at bottom
	}
	// bottom border will be ignored (truncate as needed)
	Invalidate();   // just to be nice if called when toolbar is visible
}

BOOL CToolBar::LoadBitmap(UINT nIDBitmap)
{
	return LoadBitmap(MAKEINTRESOURCE(nIDBitmap));
}

BOOL CToolBar::LoadBitmap(LPCTSTR lpszResourceName)
{
	ASSERT_VALID(this);
	ASSERT(lpszResourceName != NULL);

	AfxDeleteObject((HGDIOBJ*)&m_hbmImageWell);     // get rid of old one

	m_hInstImageWell = AfxFindResourceHandle(lpszResourceName, RT_BITMAP);
	if ((m_hRsrcImageWell = ::FindResource(m_hInstImageWell,
		lpszResourceName, RT_BITMAP)) == NULL)
		return FALSE;

	m_hbmImageWell = LoadSysColorBitmap(m_hInstImageWell, m_hRsrcImageWell);
	return (m_hbmImageWell != NULL);
}

BOOL CToolBar::SetButtons(const UINT* lpIDArray, int nIDCount)
{
	ASSERT_VALID(this);
	ASSERT(nIDCount >= 1);  // must be at least one of them
	ASSERT(lpIDArray == NULL ||
		AfxIsValidAddress(lpIDArray, sizeof(UINT) * nIDCount, FALSE));

	// first allocate array for panes and copy initial data
	if (!AllocElements(nIDCount, sizeof(AFX_TBBUTTON)))
		return FALSE;
	ASSERT(nIDCount == m_nCount);

	if (lpIDArray != NULL)
	{
		int iImage = 0;
		// go through them adding buttons
		AFX_TBBUTTON* pTBB = (AFX_TBBUTTON*)m_pData;
		for (int i = 0; i < nIDCount; i++, pTBB++)
		{
			ASSERT(pTBB != NULL);
			if ((pTBB->nID = *lpIDArray++) == 0)
			{
				// separator
				pTBB->nStyle = TBBS_SEPARATOR;
				// width of separator includes 2 pixel overlap
				pTBB->iImage = m_cxDefaultGap + m_cxSharedBorder * 2;
			}
			else
			{
				// a command button with image
				pTBB->nStyle = TBBS_BUTTON;
				pTBB->iImage = iImage++;
			}
		}
	}
	return TRUE;
}

#ifdef AFX_CORE3_SEG
#pragma code_seg(AFX_CORE3_SEG)
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolBar attribute access

int CToolBar::CommandToIndex(UINT nIDFind) const
{
	ASSERT_VALID(this);

	AFX_TBBUTTON* pTBB = _GetButtonPtr(0);
	for (int i = 0; i < m_nCount; i++, pTBB++)
		if (pTBB->nID == nIDFind)
			return i;
	return -1;
}

UINT CToolBar::GetItemID(int nIndex) const
{
	ASSERT_VALID(this);

	return _GetButtonPtr(nIndex)->nID;
}

void CToolBar::GetItemRect(int nIndex, LPRECT lpRect) const
{
	ASSERT_VALID(this);
	ASSERT(nIndex >= 0 && nIndex < m_nCount);
	ASSERT(AfxIsValidAddress(lpRect, sizeof(RECT)));

	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) ? TRUE : FALSE;
	CRect rect;
	rect.SetRectEmpty();        // only need top and left
	CalcInsideRect(rect, bHorz);
	AFX_TBBUTTON* pTBB = (AFX_TBBUTTON*)m_pData;
	for (int iButton = 0; iButton < nIndex; iButton++, pTBB++)
	{
		ASSERT(pTBB != NULL);
		// skip this button or separator
		if (bHorz)
		{
			rect.left += (pTBB->nStyle & TBBS_SEPARATOR) ?
						pTBB->iImage : m_sizeButton.cx;
			rect.left -= m_cxSharedBorder;    // go back for overlap
		}
		else
		{
			rect.top += (pTBB->nStyle & TBBS_SEPARATOR) ?
						pTBB->iImage : m_sizeButton.cy;
			rect.top -= m_cySharedBorder;    // go back for overlap
		}
	}
	ASSERT(iButton == nIndex);
	ASSERT(pTBB == _GetButtonPtr(nIndex));

	// button or image width
	if (bHorz)
	{
		int cx = (pTBB->nStyle & TBBS_SEPARATOR) ? pTBB->iImage : m_sizeButton.cx;
		lpRect->right = (lpRect->left = rect.left) + cx;
		lpRect->bottom = (lpRect->top = rect.top) + m_sizeButton.cy;
	}
	else
	{
		int cy = (pTBB->nStyle & TBBS_SEPARATOR) ? pTBB->iImage : m_sizeButton.cy;
		lpRect->bottom = (lpRect->top = rect.top) + cy;
		lpRect->right = (lpRect->left = rect.left) + m_sizeButton.cx;
	}
}

UINT CToolBar::GetButtonStyle(int nIndex) const
{
	return _GetButtonPtr(nIndex)->nStyle;
}

void CToolBar::SetButtonStyle(int nIndex, UINT nStyle)
{
	AFX_TBBUTTON* pTBB = _GetButtonPtr(nIndex);
	UINT nOldStyle = pTBB->nStyle;
	if (nOldStyle != nStyle)
	{
		// update the style and invalidate
		pTBB->nStyle = nStyle;

		// invalidate the button only if both styles not "pressed"
		if (!(nOldStyle & nStyle & TBBS_PRESSED))
			InvalidateButton(nIndex);
	}
}

CSize CToolBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	ASSERT_VALID(this);

	CSize size = CControlBar::CalcFixedLayout(bStretch, bHorz);

	CRect rect;
	rect.SetRectEmpty();        // only need top and left
	CalcInsideRect(rect, bHorz);
	AFX_TBBUTTON* pTBB = (AFX_TBBUTTON*)m_pData;
	int nButtonDist = 0;

	if (!bStretch)
	{
		for (int iButton = 0; iButton < m_nCount; iButton++, pTBB++)
		{
			ASSERT(pTBB != NULL);
			// skip this button or separator
			nButtonDist += (pTBB->nStyle & TBBS_SEPARATOR) ?
				pTBB->iImage : (bHorz ? m_sizeButton.cx : m_sizeButton.cy);
			// go back one for overlap
			nButtonDist -= bHorz ? m_cxSharedBorder : m_cySharedBorder;
		}
		if (bHorz)
			size.cx = nButtonDist - rect.Width() + m_cxSharedBorder;
		else
			size.cy = nButtonDist - rect.Height() + m_cySharedBorder;
	}

	if (bHorz)
		size.cy = m_sizeButton.cy - rect.Height(); // rect.Height() < 0
	else
		size.cx = m_sizeButton.cx - rect.Width(); // rect.Width() < 0

	return size;
}

void CToolBar::GetButtonInfo(int nIndex, UINT& nID, UINT& nStyle, int& iImage) const
{
	ASSERT_VALID(this);

	AFX_TBBUTTON* pTBB = _GetButtonPtr(nIndex);
	nID = pTBB->nID;
	nStyle = pTBB->nStyle;
	iImage = pTBB->iImage;
}

void CToolBar::SetButtonInfo(int nIndex, UINT nID, UINT nStyle, int iImage)
{
	ASSERT_VALID(this);

	AFX_TBBUTTON* pTBB = _GetButtonPtr(nIndex);
	pTBB->nID = nID;
	pTBB->iImage = iImage;
	pTBB->nStyle = nStyle;
	InvalidateButton(nIndex);
}

void CToolBar::DoPaint(CDC* pDC)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	CControlBar::DoPaint(pDC);      // draw border

	// if no toolbar loaded, don't draw any buttons
	if (m_hbmImageWell == NULL)
		return;

	BOOL bHorz = m_dwStyle & CBRS_ORIENT_HORZ ? TRUE : FALSE;
	CRect rect;
	GetClientRect(rect);
	CalcInsideRect(rect, bHorz);

	// force the full size of the button
	if (bHorz)
		rect.bottom = rect.top + m_sizeButton.cy;
	else
		rect.right = rect.left + m_sizeButton.cx;

	DrawState ds;
	if (!PrepareDrawButton(ds))
		return;     // something went wrong

	AFX_TBBUTTON* pTBB = (AFX_TBBUTTON*)m_pData;
	for (int iButton = 0; iButton < m_nCount; iButton++, pTBB++)
	{
		ASSERT(pTBB != NULL);
		if (pTBB->nStyle & TBBS_SEPARATOR)
		{
			// separator
			if (bHorz)
				rect.right = rect.left + pTBB->iImage;
			else
				rect.bottom = rect.top + pTBB->iImage;
		}
		else
		{
			if (bHorz)
				rect.right = rect.left + m_sizeButton.cx;
			else
				rect.bottom = rect.top + m_sizeButton.cy;
			if (!globalData.bWin32s || pDC->RectVisible(&rect))
			{
				DrawButton(pDC, rect.left, rect.top,
					pTBB->iImage, pTBB->nStyle);
			}
		}
		// adjust for overlap
		if (bHorz)
			rect.left = rect.right - m_cxSharedBorder;
		else
			rect.top = rect.bottom - m_cySharedBorder;
	}
	EndDrawButton(ds);
}

void CToolBar::InvalidateButton(int nIndex)
{
	ASSERT_VALID(this);

	CRect rect;
	GetItemRect(nIndex, &rect);
	InvalidateRect(rect, FALSE);    // don't erase background
}

int CToolBar::OnToolHitTest(CPoint point, TOOLINFO* pTI) const
{
	ASSERT_VALID(this);

	// check child windows first by calling CControlBar
	int nHit = CControlBar::OnToolHitTest(point, pTI);
	if (nHit != -1)
		return nHit;

	// now hit test against CToolBar buttons
	nHit = ((CToolBar*)this)->HitTest(point);
	if (nHit != -1)
	{
		AFX_TBBUTTON* pTBB = _GetButtonPtr(nHit);
		if (pTI != NULL)
		{
			GetItemRect(nHit, &pTI->rect);
			pTI->uId = pTBB->nID;
			pTI->hwnd = m_hWnd;
			pTI->lpszText = LPSTR_TEXTCALLBACK;
		}
		nHit = pTBB->nID;
	}
	return nHit;
}

int CToolBar::HitTest(CPoint point) // in window relative coords
{
	if (m_pData == NULL)
		return -1;  // no buttons

	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) ? TRUE : FALSE;
	CRect rect;
	rect.SetRectEmpty();        // only need top and left
	CalcInsideRect(rect, bHorz);
	AFX_TBBUTTON* pTBB = (AFX_TBBUTTON*)m_pData;
	ASSERT(pTBB != NULL);
	if (bHorz)
	{
		if (point.y < rect.top || point.y >= rect.top + m_sizeButton.cy)
			return -1;      // no Y hit
		for (int iButton = 0; iButton < m_nCount; iButton++, pTBB++)
		{
			if (point.x < rect.left)
				break;      // missed it
			rect.left += (pTBB->nStyle & TBBS_SEPARATOR) ?
							pTBB->iImage : m_sizeButton.cx;
			if (point.x < rect.left && !(pTBB->nStyle & TBBS_SEPARATOR))
				return iButton;     // hit !
			rect.left -= m_cxSharedBorder;    // go back for overlap
		}
	}
	else
	{
		if (point.x < rect.left || point.x >= rect.left + m_sizeButton.cx)
			return -1;      // no X hit
		for (int iButton = 0; iButton < m_nCount; iButton++, pTBB++)
		{
			if (point.y < rect.top)
				break;      // missed it
			rect.top += (pTBB->nStyle & TBBS_SEPARATOR) ?
							pTBB->iImage : m_sizeButton.cy;
			if (point.y < rect.top && !(pTBB->nStyle & TBBS_SEPARATOR))
				return iButton;     // hit !
			rect.top -= m_cySharedBorder;    // go back for overlap
		}
	}

	return -1;      // nothing hit
}

/////////////////////////////////////////////////////////////////////////////
// CToolBar message handlers

BEGIN_MESSAGE_MAP(CToolBar, CControlBar)
	//{{AFX_MSG_MAP(CToolBar)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CANCELMODE()
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CToolBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	if ((m_iButtonCapture = HitTest(point)) < 0) // nothing hit
	{
		CControlBar::OnLButtonDown(nFlags, point);
		return;
	}

	AFX_TBBUTTON* pTBB = _GetButtonPtr(m_iButtonCapture);
	ASSERT(!(pTBB->nStyle & TBBS_SEPARATOR));

	// update the button before checking for disabled status
	UpdateButton(m_iButtonCapture);
	if (pTBB->nStyle & TBBS_DISABLED)
	{
		m_iButtonCapture = -1;
		return;     // don't press it
	}

	pTBB->nStyle |= TBBS_PRESSED;
	InvalidateButton(m_iButtonCapture);
	UpdateWindow(); // immediate feedback
	SetCapture();
	GetOwner()->SendMessage(WM_SETMESSAGESTRING, (WPARAM)pTBB->nID);
}

void CToolBar::OnMouseMove(UINT /*nFlags*/, CPoint point)
{
	if (m_iButtonCapture >= 0)
	{
		AFX_TBBUTTON* pTBB = _GetButtonPtr(m_iButtonCapture);
		ASSERT(!(pTBB->nStyle & TBBS_SEPARATOR));

		UINT nNewStyle = (pTBB->nStyle & ~TBBS_PRESSED);
		int iButtonCapture = m_iButtonCapture;
		if (GetCapture() != this)
		{
			m_iButtonCapture = -1; // lost capture
			GetOwner()->SendMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);
		}
		else
		{
			// should be pressed if still hitting the captured button
			if (HitTest(point) == m_iButtonCapture)
				nNewStyle |= TBBS_PRESSED;
		}
		SetButtonStyle(iButtonCapture, nNewStyle);
		UpdateWindow(); // immediate feedback
	}
}

void CToolBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_iButtonCapture < 0)
	{
		CControlBar::OnLButtonUp(nFlags, point);
		return;     // not captured
	}

	AFX_TBBUTTON* pTBB = _GetButtonPtr(m_iButtonCapture);
	ASSERT(!(pTBB->nStyle & TBBS_SEPARATOR));
	UINT nIDCmd = 0;

	UINT nNewStyle = (pTBB->nStyle & ~TBBS_PRESSED);
	if (GetCapture() == this)
	{
		// we did not lose the capture
		ReleaseCapture();
		if (HitTest(point) == m_iButtonCapture)
		{
			// give button a chance to update
			UpdateButton(m_iButtonCapture);

			// then check for disabled state
			if (!(pTBB->nStyle & TBBS_DISABLED))
			{
				// pressed, will send command notification
				nIDCmd = pTBB->nID;

				if (pTBB->nStyle & TBBS_CHECKBOX)
				{
					// auto check: three state => down
					if (nNewStyle & TBBS_INDETERMINATE)
						nNewStyle &= ~TBBS_INDETERMINATE;

					nNewStyle ^= TBBS_CHECKED;
				}
			}
		}
	}

	GetOwner()->SendMessage(WM_SETMESSAGESTRING, AFX_IDS_IDLEMESSAGE);

	int iButtonCapture = m_iButtonCapture;
	m_iButtonCapture = -1;
	if (nIDCmd != 0)
		GetOwner()->SendMessage(WM_COMMAND, nIDCmd);    // send command

	SetButtonStyle(iButtonCapture, nNewStyle);
	UpdateButton(iButtonCapture);

	UpdateWindow(); // immediate feedback
}

void CToolBar::OnCancelMode()
{
	CControlBar::OnCancelMode();

	if (m_iButtonCapture >= 0)
	{
		AFX_TBBUTTON* pTBB = _GetButtonPtr(m_iButtonCapture);
		ASSERT(!(pTBB->nStyle & TBBS_SEPARATOR));
		UINT nNewStyle = (pTBB->nStyle & ~TBBS_PRESSED);
		if (GetCapture() == this)
			ReleaseCapture();
		SetButtonStyle(m_iButtonCapture, nNewStyle);
		m_iButtonCapture = -1;
		UpdateWindow();
	}
}

void CToolBar::OnSysColorChange()
{
	// re-initialize global dither brush
	HBITMAP hbmGray = ::CreateDitherBitmap();
	if (hbmGray != NULL)
	{
		HBRUSH hbrNew = ::CreatePatternBrush(hbmGray);
		if (hbrNew != NULL)
		{
			AfxDeleteObject((HGDIOBJ*)&hbrDither);      // free old one
			hbrDither = hbrNew;
		}
		::DeleteObject(hbmGray);
	}

	// re-color bitmap for toolbar
	if (m_hbmImageWell != NULL)
	{
		HBITMAP hbmNew;
		hbmNew = LoadSysColorBitmap(m_hInstImageWell, m_hRsrcImageWell);
		if (hbmNew != NULL)
		{
			::DeleteObject(m_hbmImageWell);     // free old one
			m_hbmImageWell = hbmNew;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CToolBar idle update through CToolCmdUI class

#define CToolCmdUI COldToolCmdUI

class CToolCmdUI : public CCmdUI        // class private to this file !
{
public: // re-implementations only
	virtual void Enable(BOOL bOn);
	virtual void SetCheck(int nCheck);
	virtual void SetText(LPCTSTR lpszText);
};

void CToolCmdUI::Enable(BOOL bOn)
{
	m_bEnableChanged = TRUE;
	CToolBar* pToolBar = (CToolBar*)m_pOther;
	ASSERT(pToolBar != NULL);
	ASSERT_KINDOF(CToolBar, pToolBar);
	ASSERT(m_nIndex < m_nIndexMax);

	UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) & ~TBBS_DISABLED;
	if (!bOn)
		nNewStyle |= TBBS_DISABLED;
	ASSERT(!(nNewStyle & TBBS_SEPARATOR));
	pToolBar->SetButtonStyle(m_nIndex, nNewStyle);
}

void CToolCmdUI::SetCheck(int nCheck)
{
	ASSERT(nCheck >= 0 && nCheck <= 2); // 0=>off, 1=>on, 2=>indeterminate
	CToolBar* pToolBar = (CToolBar*)m_pOther;
	ASSERT(pToolBar != NULL);
	ASSERT_KINDOF(CToolBar, pToolBar);
	ASSERT(m_nIndex < m_nIndexMax);

	UINT nNewStyle = pToolBar->GetButtonStyle(m_nIndex) &
				~(TBBS_CHECKED | TBBS_INDETERMINATE);
	if (nCheck == 1)
		nNewStyle |= TBBS_CHECKED;
	else if (nCheck == 2)
		nNewStyle |= TBBS_INDETERMINATE;
	ASSERT(!(nNewStyle & TBBS_SEPARATOR));
	pToolBar->SetButtonStyle(m_nIndex, nNewStyle | TBBS_CHECKBOX);
}

void CToolCmdUI::SetText(LPCTSTR)
{
	// ignore it
}

void CToolBar::OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler)
{
	CToolCmdUI state;
	state.m_pOther = this;

	state.m_nIndexMax = (UINT)m_nCount;
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax;
	  state.m_nIndex++)
	{
		AFX_TBBUTTON* pTBB = _GetButtonPtr(state.m_nIndex);
		state.m_nID = pTBB->nID;

		// ignore separators
		if (!(pTBB->nStyle & TBBS_SEPARATOR))
			state.DoUpdate(pTarget, bDisableIfNoHndler);
	}

	// update the dialog controls added to the toolbar
	UpdateDialogControls(pTarget, bDisableIfNoHndler);
}

void CToolBar::UpdateButton(int nIndex)
{
	// determine target of command update
	CFrameWnd* pTarget = (CFrameWnd*)GetOwner();
	if (pTarget == NULL || !pTarget->IsFrameWnd())
		pTarget = GetParentFrame();

	// send the update notification
	if (pTarget != NULL)
	{
		CToolCmdUI state;
		state.m_pOther = this;
		state.m_nIndex = nIndex;
		state.m_nIndexMax = (UINT)m_nCount;
		AFX_TBBUTTON* pTBB = _GetButtonPtr(nIndex);
		state.m_nID = pTBB->nID;
		state.DoUpdate(pTarget, pTarget->m_bAutoMenuEnable);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CToolBar diagnostics

#ifdef _DEBUG
void CToolBar::AssertValid() const
{
	CControlBar::AssertValid();
	ASSERT(m_hbmImageWell == NULL ||
		(globalData.bWin32s || ::GetObjectType(m_hbmImageWell) == OBJ_BITMAP));

	if (m_hbmImageWell != NULL)
	{
		ASSERT(m_hRsrcImageWell != NULL);
		ASSERT(m_hInstImageWell != NULL);
	}
}

void CToolBar::Dump(CDumpContext& dc) const
{
	CControlBar::Dump(dc);

	dc << "m_hbmImageWell = " << (UINT)m_hbmImageWell;
	dc << "\nm_hInstImageWell = " << (UINT)m_hInstImageWell;
	dc << "\nm_hRsrcImageWell = " << (UINT)m_hRsrcImageWell;
	dc << "\nm_iButtonCapture = " << m_iButtonCapture;
	dc << "\nm_sizeButton = " << m_sizeButton;
	dc << "\nm_sizeImage = " << m_sizeImage;

	if (dc.GetDepth() > 0)
	{
		for (int i = 0; i < m_nCount; i++)
		{
			AFX_TBBUTTON* pTBB = _GetButtonPtr(i);
			dc << "\ntoolbar button[" << i << "] = {";
			dc << "\n\tnID = " << pTBB->nID;
			dc << "\n\tnStyle = " << pTBB->nStyle;
			if (pTBB->nStyle & TBBS_SEPARATOR)
				dc << "\n\tiImage (separator width) = " << pTBB->iImage;
			else
				dc <<"\n\tiImage (bitmap image index) = " << pTBB->iImage;
			dc << "\n}";
		}
	}

	dc << "\n";
}
#endif

#undef new
#ifdef AFX_INIT_SEG
#pragma code_seg(AFX_INIT_SEG)
#endif

IMPLEMENT_DYNAMIC(CToolBar, CControlBar)
