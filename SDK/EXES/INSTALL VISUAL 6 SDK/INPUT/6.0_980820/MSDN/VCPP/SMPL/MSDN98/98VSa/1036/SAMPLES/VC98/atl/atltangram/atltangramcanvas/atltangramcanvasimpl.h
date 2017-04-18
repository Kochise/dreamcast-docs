// AtlTangramCanvasImpl.h : Declaration of the CAtlTangramCanvas
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

#ifndef __ATLTANGRAMCANVAS_H_
#define __ATLTANGRAMCANVAS_H_

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAtlTangramCanvas
class ATL_NO_VTABLE CAtlTangramCanvas : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAtlTangramCanvas, &CLSID_AtlTangramCanvas>,
	public IAtlTangramCanvas
{
public:
	CAtlTangramCanvas():
		m_hWnd(NULL),
		m_hbmp(NULL),
		m_pBits(NULL),
		m_hdc(NULL),
		m_hPal(NULL)
	{
		m_sizeDIB.cx = m_sizeDIB.cy = 0; 
	}

	~CAtlTangramCanvas()
	{
		// Select the old bitmap back into the buffer DC.
		if (m_hbmOld)
		{
			::SelectObject(m_hdc, m_hbmOld);
		}

		// Delete bitmap.
		if (m_hbmp) 
		{
			DeleteObject(m_hbmp);
		}

		// Delete DC.
		if (m_hdc) 
		{
			::DeleteDC(m_hdc) ;
		}
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ATLTANGRAMCANVAS)
DECLARE_ONLY_AGGREGATABLE(CAtlTangramCanvas)

BEGIN_COM_MAP(CAtlTangramCanvas)
	COM_INTERFACE_ENTRY(IAtlTangramCanvas)
END_COM_MAP()

// IAtlTangramCanvas
public:
	virtual HRESULT __stdcall Initialize(HWND hWnd, long cx, long cy) ;//Initialize can be called multiple times.
	virtual HRESULT __stdcall Paint(HDC hdcDest, RECT rectUpdate) ;
	virtual HRESULT __stdcall Update(RECT rectUpdate);
	virtual HRESULT __stdcall GetHDC(HDC* phdc ) ; 
	virtual HRESULT __stdcall SetPalette(HPALETTE hPal); 
	virtual HRESULT __stdcall OnQueryNewPalette(HWND hWndReceived) ;
//Member Variables
private:
	// Handle to window associated with this Canvas.
	HWND m_hWnd ; 

	// Handle to dib section.
	HBITMAP m_hbmp ;

	// Handle to old bitmap.
	HBITMAP m_hbmOld ;

	// Pointer to the bits.
	void* m_pBits ;		

	// Size of the canvas.
	SIZE m_sizeDIB ;

	// Handle to the device memory context for the dib section.
	HDC m_hdc ;

	// Handle to the palette used by the dib section.
	HPALETTE m_hPal;
};

#endif //__ATLTANGRAMCANVAS_H_
