// AtlGdiWorldImpl.h : Declaration of the CAtlGdiWorld
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

#ifndef __ATLGDIWORLD_H_
#define __ATLGDIWORLD_H_
#include "TanType.h"
// STL Headers
#include <new.h>
#include <algorithm>
#include <xmemory>
#include <list>

#include "util.h"
#include "ATLTangramCanvas.h"
#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAtlGdiWorld
class ATL_NO_VTABLE CAtlGdiWorld :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAtlGdiWorld, &CLSID_AtlGdiWorld>,
	public IAtlTangramGdiWorld
{
public:
	CAtlGdiWorld():
		m_pCanvas(0),
		m_pCanvasUnknown(0)
	{
		m_sizedScale.cx = m_sizedScale.cy = 1.0 ;
		m_ptdDeviceOrg.x = m_ptdDeviceOrg.y = 0.0 ;

		::SetRectEmpty(&m_rectUpdate) ;
	}

	~CAtlGdiWorld();

	void FinalRelease()
	{
		TCHAR buf[128];
		wsprintf(buf,_T("World: m_dwRef = %d\n"), m_dwRef);
		ATLTRACE(buf);
		// Release the ICanvas interface on the aggregated object.
		if (m_pCanvas != NULL)
		{
			// Add a reference back to the outer object.
			GetControllingUnknown()->AddRef() ;
			// Remove the reference on the inner and outer objects.
			m_pCanvas->Release() ;
			m_pCanvas = NULL ;
		}
		wsprintf(buf,_T("World: m_dwRef = %d\n"), m_dwRef);
		ATLTRACE(buf);

		// Release our hold on the inner object.
		if (m_pCanvasUnknown != NULL)
		{
			m_pCanvasUnknown->Release() ;
			m_pCanvasUnknown = NULL ;
		}
		wsprintf(buf,_T("World: m_dwRef = %d\n"), m_dwRef);
		ATLTRACE(buf);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ATLTANGRAMGDIVISUAL)
DECLARE_GET_CONTROLLING_UNKNOWN()

BEGIN_COM_MAP(CAtlGdiWorld)
	COM_INTERFACE_ENTRY(IAtlTangramGdiWorld)
	COM_INTERFACE_ENTRY(IAtlTangramWorld)
	COM_INTERFACE_ENTRY_AGGREGATE(IID_IAtlTangramCanvas, m_pCanvasUnknown )
END_COM_MAP()

public:

	// Special Registration
	static void SpecialReg(BOOL bRegister) ;

	// IAtlTangramWorld Members
	HRESULT __stdcall Initialize(HWND hwnd, double logicalCX, double logicalCY) ;
	HRESULT __stdcall DeviceToModel(POINT ptIN, TangramPoint2d* pptOut) ;

	HRESULT __stdcall VisualFromPoint(  POINT pt,
										REFIID iid,
										IUnknown** ppITangramVisual) ;
	HRESULT __stdcall CreateVisualForModel(IATLTangramModel* pModel) ;
	HRESULT __stdcall SelectVisual(IAtlTangramVisual* pSelectedVisual, BOOL bSelect) ;

	HRESULT __stdcall Animate() ;

	// ITangramGdiWorld
	HRESULT __stdcall ModelToDevice(TangramPoint2d ptIn, POINT* pptOut);
	HRESULT __stdcall AddUpdateRect(RECT rectUpdate) ;

private:
	// Members
#pragma warning(disable:4786)
	typedef std::list<IAtlTangramGdiVisual*> CVisualList;
	CVisualList m_VisualList ;
#pragma warning(default:4786)
	// Coordinate Transform
	TangramSize2d m_sizedScale ;
	TangramPoint2d m_ptdDeviceOrg ;

	double dDeviceUnits ;
	double dModelUnits ;

	// Aggregated Canvas Component
	IAtlTangramCanvas* m_pCanvas;
	IUnknown* m_pCanvasUnknown ;

	// Update rectangle
	RECT m_rectUpdate ;
};

#endif //__ATLGDIWORLD_H_
