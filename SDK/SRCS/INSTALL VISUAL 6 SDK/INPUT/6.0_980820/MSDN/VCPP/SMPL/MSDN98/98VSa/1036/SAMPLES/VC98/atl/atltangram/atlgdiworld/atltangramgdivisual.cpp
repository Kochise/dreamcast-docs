// AtlTangramGdiVisual.cpp : Implementation of CAtlTangramGdiVisual
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
#include "ATLGdiWorld.h"
#include "AtlTangramGdiVisual.h"
#include "ATLModel.h"


/////////////////////////////////////////////////////////////////////////////
// CAtlTangramGdiVisual

///////////////////////////////////////////////////////////
//
// Destructor
//
CAtlTangramGdiVisual::~CAtlTangramGdiVisual()
{

	// We keep a strong reference to the model.
	// Therefore, we need to release it here.
	m_pModel->Release() ;
	m_pModel = NULL ;

	// We maintain a weak reference to GdiWorld to avoid
	// reference cycles. A weak reference means that we
	// do not AddRef or Release the pointer.
	//m_pGdiWorld->Release() ;
	//m_pGdiWorld = NULL ;


	// Delete the vertex array.
	if (m_ptVertices != NULL)
	{
		delete [] m_ptVertices ;
	}

}

///////////////////////////////////////////////////////////
//
//                      IAtlTangramGdiVisual
//
///////////////////////////////////////////////////////////
//
// IAtlTangramGdiVisual::Initialize Implementation
//
HRESULT CAtlTangramGdiVisual::Initialize(IATLTangramModel* pModel, IAtlTangramGdiWorld* pWorld)
{
	if (!IsValidInterface(pModel) || !IsValidInterface(pWorld))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	if (m_pModel != NULL || m_pGdiWorld != NULL)
	{
		// Cannot re-initialize.
		ASSERT(0) ;
		return E_FAIL ;
	}

	// Keep a strong reference to the model.
	m_pModel = pModel ;
	m_pModel->AddRef() ;

	// To avoid a cyclical reference count, we have a weak reference to GdiWorld.
	// Therefore, we do not AddRef this pointer.
	m_pGdiWorld = pWorld ;

	// Get the number of vertices in the model.
	HRESULT hr = m_pModel->GetNumberOfVertices(&m_cVertices) ;
	ASSERT_HRESULT(hr) ;

	// Create an array to hold the vertices.
	m_ptVertices = new POINT[m_cVertices] ;

	//  ----- Set up event sync -----
	return  AdviseConnectionPoint(pModel);
}

///////////////////////////////////////////////////////////
//
// IAtlTangramGdiVisual::DrawOn Implementation
//
HRESULT CAtlTangramGdiVisual::DrawOn(IAtlTangramCanvas* pCanvas)
{
	// Preconditions.
	if (!IsValidInterface(pCanvas))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	// Get a device context to draw on from the canvas.
	HDC hDC ;
	HRESULT hr = pCanvas->GetHDC(&hDC) ;
	ASSERT_HRESULT(hr) ;

	// Make a pen.
	HPEN hPen = ::CreatePen(PS_SOLID, 1, m_bSelected ? RGB(255,0,0) : RGB(128,128,128)) ;
	HPEN hOldPen = (HPEN) ::SelectObject(hDC, hPen) ;

	// Make a brush.
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(hDC, ::GetStockObject(m_bSelected ? NULL_BRUSH : LTGRAY_BRUSH)) ;

	// Draw the polygon.
	::Polygon(hDC, m_ptVertices, m_cVertices) ;

	// CleanUp
	::SelectObject(hDC, hOldPen) ;
	::SelectObject(hDC, hOldBrush) ;

	::DeleteObject(hPen) ;

	return S_OK ;
}


///////////////////////////////////////////////////////////
//
// IAtlTangramGdiVisual::IsPtIn Implementation
//
HRESULT CAtlTangramGdiVisual::IsPtIn(POINT pt)
{
	ASSERT( m_ptVertices != NULL) ;
	ASSERT( m_cVertices != 0) ;

	// Create a region.
	HRGN hrgnPolygon = ::CreatePolygonRgn(m_ptVertices, m_cVertices, ALTERNATE) ;

	// Is point in region?
	BOOL bResult = ::PtInRegion(hrgnPolygon, pt.x, pt.y) ;

	// Cleanup
	::DeleteObject(hrgnPolygon) ;

	// Return the results.
	return (bResult) ? S_OK : S_FALSE ;
}

///////////////////////////////////////////////////////////
//
// IAtlTangramGdiVisual::GetBoundingRect
//
// Results:
//          S_FALSE -   If the boundary doesn't make sense.
//
HRESULT CAtlTangramGdiVisual::GetBoundingRect(RECT* pBoundingRect)
{
	if (!IsValidAddress(pBoundingRect, sizeof(RECT), TRUE))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

	HRESULT hr = S_OK ;
	// Create a region.
	HRGN hrgnPolygon = ::CreatePolygonRgn(m_ptVertices, m_cVertices, ALTERNATE) ;

	// Get the bounding box for the region.
	RECT rect ;
	int bRgnType = ::GetRgnBox(hrgnPolygon, &rect) ;
	if (bRgnType == NULLREGION || bRgnType == ERROR)
	{
		::SetRectEmpty(pBoundingRect) ;
		hr = S_FALSE ;
	}
	else
	{
		// Add room for the pen width boundary.
		pBoundingRect->top    = rect.top    - 2 ;
		pBoundingRect->bottom = rect.bottom + 2 ;
		pBoundingRect->left   = rect.left   - 2 ;
		pBoundingRect->right  = rect.right  + 2 ;
	}

	// Cleanup
	::DeleteObject(hrgnPolygon) ;

	return hr ;
}

///////////////////////////////////////////////////////////
//
//                      ITangramVisual
//
///////////////////////////////////////////////////////////
//
// ITangramVisual::SetSelected Implementation.
//
HRESULT CAtlTangramGdiVisual::SetSelected(BOOL bSelected)
{
	m_bSelected = bSelected ;

	// Add the boundary to the update region.
	RECT rectBounding;
	GetBoundingRect(&rectBounding) ;
	HRESULT hr = m_pGdiWorld->AddUpdateRect(rectBounding) ;
	ASSERT_HRESULT(hr) ;

	hr = m_pGdiWorld->Animate() ;
	ASSERT_HRESULT(hr) ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
// IAtlTangramGdiVisual::GetModel Implementation
//
HRESULT CAtlTangramGdiVisual::GetModel(const IID& iid, IUnknown** ppI)
{
	if (!IsValidInterfaceOutParam(ppI))
	{
		ASSERT(0) ;
		return E_POINTER ;
	}

   return m_pModel->QueryInterface(iid, (void**)ppI)  ;
}

///////////////////////////////////////////////////////////
//
//                  ITangramModelEvent
//
///////////////////////////////////////////////////////////
//
// ITangramModelEvent::OnModelChange
//
HRESULT __stdcall CAtlTangramGdiVisual::OnModelChange()
{
	// Get Current Bounding Rectangle
	RECT rectBounding;
	GetBoundingRect(&rectBounding) ;
	HRESULT hr = m_pGdiWorld->AddUpdateRect(rectBounding) ;
	ASSERT_HRESULT(hr) ;

	// Get the new vertices.
	SyncToModel() ;

	// Get New Bounding Rectangle
	GetBoundingRect(&rectBounding) ;
	hr = m_pGdiWorld->AddUpdateRect(rectBounding) ;
	ASSERT_HRESULT(hr) ;

	hr = m_pGdiWorld->Animate() ;
	ASSERT_HRESULT(hr) ;

	return S_OK ;
}

///////////////////////////////////////////////////////////
//
//                  Helper Functions
//
///////////////////////////////////////////////////////////
//
//
//
void CAtlTangramGdiVisual::SyncToModel()
{
	// Create an array to hold the new vertices.
	TangramPoint2d* pointds = new TangramPoint2d[m_cVertices] ;

	// Get the vertices from the model.
	HRESULT hr = m_pModel->GetVertices(m_cVertices, pointds) ;
	ASSERT_HRESULT(hr) ;

	// Convert the vertices to our coordinates.
	for (int i = 0 ; i < m_cVertices ; i++)
	{
		hr = m_pGdiWorld->ModelToDevice(pointds[i], &m_ptVertices[i]) ;
		ASSERT_HRESULT(hr) ;
	}

	// Cleanup.
	delete [] pointds;
}

STDMETHODIMP CAtlTangramGdiVisual::ReleaseConnectionPoint()
{
	HRESULT hr = S_OK;
	// Release the event source component.
	if (m_pIConnectionPoint != NULL)
	{
		// We no longer need to be enformed of events
		hr = m_pIConnectionPoint->Unadvise(m_dwCookie) ;
		ASSERT_HRESULT(hr) ;

		m_pIConnectionPoint->Release() ;
	}
	return hr;
}

HRESULT __stdcall CAtlTangramGdiVisual::AdviseConnectionPoint(IATLTangramModel* pModel)
{
	// Get the connection point container from the model.
	IConnectionPointContainer* pContainer = NULL ;
	HRESULT hr = pModel->QueryInterface(IID_IConnectionPointContainer, (void**)&pContainer) ;
	if(!SUCCEEDED(hr))
		return hr;

	// Get our desired connection point. Cache the pointer so we can
	// UnAdvise() the connection point when we're done sinking on it
	hr = pContainer->FindConnectionPoint(IID_IATLTangramModelEvent, &m_pIConnectionPoint) ;
	pContainer->Release() ;
	if(!SUCCEEDED(hr))
		return hr;

	// Advise the model that we are sinking its event source
	return m_pIConnectionPoint->Advise(GetUnknown(), &m_dwCookie) ;
}
