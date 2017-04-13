// AtlTangramCanvasImpl.cpp : Implementation of CAtlTangramCanvas
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
#include "ATLTangramCanvas.h"
#include "AtlTangramCanvasImpl.h"

/////////////////////////////////////////////////////////////////////////////
// CAtlTangramCanvas
//

///////////////////////////////////////////////////////////
//
// Initialize
//  
HRESULT CAtlTangramCanvas::Initialize(HWND hWnd, long cx, long cy)
{
	// Hard coded to 8 bits per pixel.
	int ibitcount = 8 ; 

	// Preconditions.
	if ( hWnd == NULL || !::IsWindow(hWnd) || cx <= 0 || cy <= 0)
	{
		// Definsive code.
		ASSERT(hWnd != NULL) ;
		ASSERT(::IsWindow(hWnd)) ;
		ASSERT(cx > 0);
		ASSERT(cy > 0);

		return E_INVALIDARG ;
	}

	// Cache a copy of the window handle.
	m_hWnd = hWnd ; 

	// Destroy parts of objects if we are recreating it.
	if ((m_hdc != NULL) || (m_hbmp != NULL))
	{	
//		destroy() ;
	}

	// Save size for drawing later.
	m_sizeDIB.cx = cx ;
	m_sizeDIB.cy = cy ;

	// Create a BITMAPINFOHEADER structure to describe the DIB
	BITMAPINFOHEADER BIH ;
	int iSize = sizeof(BITMAPINFOHEADER) ;
	memset(&BIH, 0, iSize);

	// Fill in the header info.
	BIH.biSize = iSize;
	BIH.biWidth = cx;
	BIH.biHeight = cy;
	BIH.biPlanes = 1;
	BIH.biBitCount = ibitcount;
	BIH.biCompression = BI_RGB;

	// Create a new DC.
	m_hdc = ::CreateCompatibleDC(NULL) ;


	// Create the DIB section.
	m_hbmp = CreateDIBSection(	m_hdc,
								(BITMAPINFO*)&BIH,
								DIB_PAL_COLORS,
								&m_pBits,
								NULL,
								0);

	ASSERT(m_hbmp);
	ASSERT(m_pBits);

	// Select the new bitmap into the buffer DC
	if (m_hbmp)
	{
		m_hbmOld = (HBITMAP)::SelectObject(	m_hdc, 
											m_hbmp);
	}

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//	Transfer the dib section to a DC. 
//	Called in response to paint and draw messages.
//
HRESULT CAtlTangramCanvas::Paint(HDC hdcDest, RECT rectUpdate)
{
	// Preconditions
	if ( hdcDest == NULL)
	{
		ASSERT(hdcDest != NULL) ;
		return E_INVALIDARG ;
	}

	// Select in a palette if we have one.
	HPALETTE hPalOld = NULL;
	if (m_hPal)
	{
		hPalOld = ::SelectPalette(hdcDest, (HPALETTE)m_hPal, 0);
		::RealizePalette(hdcDest);
	}

	// If the rectangle is empty or null, repaint the entire area.
	RECT rect, rectNull ;
	::SetRectEmpty(&rectNull) ;
	::CopyRect(&rect, &rectUpdate) ;
	if (::EqualRect(&rect, &rectNull) || ::IsRectEmpty(&rect))
	{
		// Note: you do not need to select the palette into
		// the memory DC because the DIB section is using palette
		// index values not colors
		::BitBlt(hdcDest, 0, 0,
					m_sizeDIB.cx, m_sizeDIB.cy,
					m_hdc, 
					0,0,
					SRCCOPY);
	}
	else
	{
		// Just repaint the updated area.
		::BitBlt(hdcDest,
				rect.left, rect.top,
				rect.right - rect.left, rect.bottom - rect.top,
				m_hdc, 
				rect.left, rect.top,
				SRCCOPY);
		}

	// We are done with the palette
	if (hPalOld) 
	{
		::SelectPalette(hdcDest, hPalOld, 0);		
	}

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//	Update
//
HRESULT CAtlTangramCanvas::Update(RECT rectUpdate)
{

	HDC hdcDest = ::GetDC(m_hWnd) ;
	Paint(hdcDest, rectUpdate) ;
	::ReleaseDC(m_hWnd, hdcDest);

	return S_OK ;
}



///////////////////////////////////////////////////////////
//
//	GetHDC
//
HRESULT CAtlTangramCanvas::GetHDC(HDC* phdc)
{
	// Pre conditions.
	if (!IsValidAddress(phdc, sizeof(HDC), TRUE))
	{
		ASSERT(0) ;
		return E_FAIL ;
	}

	// Return device context.
	*phdc = m_hdc ;
	return S_OK ;
}


///////////////////////////////////////////////////////////
//
// Set the color table in the DIB section.
//
HRESULT __stdcall CAtlTangramCanvas::SetPalette(HPALETTE hPal) 
{
	if (hPal == NULL)
	{
		ASSERT(hPal != NULL);
		return E_INVALIDARG ;
	}

	// Keep a copy of the palette around for painting.
	m_hPal = hPal ;

	// get the colors from the palette
	int iColors = 0;
	::GetObject(hPal, sizeof(iColors), &iColors) ;

	ASSERT(iColors > 0);
	PALETTEENTRY* pPE = new PALETTEENTRY[iColors];
	::GetPaletteEntries(hPal, 0, iColors, pPE);

	// Build a table of RGBQUADS
	RGBQUAD* pRGB = new RGBQUAD[iColors];
	ASSERT(pRGB);
	for (int i = 0; i < iColors; i++) {
		pRGB[i].rgbRed = pPE[i].peRed;
		pRGB[i].rgbGreen = pPE[i].peGreen;
		pRGB[i].rgbBlue = pPE[i].peBlue;
		pRGB[i].rgbReserved = 0;
	}
	
	::SetDIBColorTable(m_hdc, 
					   0, iColors,
					   pRGB);

	delete [] pRGB;
	delete [] pPE;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//	Called when the main window gets a QueryNewPalette or a
//	PaletteChanged message.
//
HRESULT __stdcall CAtlTangramCanvas::OnQueryNewPalette(HWND hWndReceived)
{
	if (hWndReceived == NULL)
	{
		return E_FAIL ;
	}

	if (m_hPal)
	{
		HDC hdc = ::GetDC(hWndReceived) ;
		::SelectPalette(hdc, m_hPal, FALSE) ;
		UINT u = ::RealizePalette(hdc) ;
		::ReleaseDC(hWndReceived, hdc) ;
		if (u != 0)
		{
			::InvalidateRect(hWndReceived, NULL, TRUE) ;
		}
	}
	return S_OK ;
}