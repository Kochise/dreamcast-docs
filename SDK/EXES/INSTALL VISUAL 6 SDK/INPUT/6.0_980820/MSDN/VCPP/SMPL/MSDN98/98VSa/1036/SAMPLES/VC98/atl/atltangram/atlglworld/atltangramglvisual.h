// AtlTangramGLVisual.h : Declaration of the CAtlTangramGLVisual
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

#ifndef __ATLTANGRAMGLVISUAL_H_
#define __ATLTANGRAMGLVISUAL_H_

#include "resource.h"       // main symbols
#include "AtlEvent_i.h"
#include "ATLTangramCanvas.h"
#include "AtlGLWorld.h"


interface IConnectionPoint ;
interface IAtlTangramWorld;
interface IAtlTangramGLWorld;
interface IAtlTangramGLVisual;

/////////////////////////////////////////////////////////////////////////////
// CAtlTangramGLVisual
class ATL_NO_VTABLE CAtlTangramGLVisual :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAtlTangramGLVisual, &CLSID_AtlTangramGLVisual>,
	public IAtlTangramGLVisual,
	public IATLTangramModelEvent
{
public:
	///////////////////////////////////////////////////////////
	//
	// Constructor
	//
	CAtlTangramGLVisual::CAtlTangramGLVisual()
	:   m_pModel(NULL),
		m_pWorld(NULL),
		m_bSelected(FALSE),
		m_pIConnectionPoint(NULL),
		m_dwCookie(0),
		m_bFirstEvent(FALSE)
	{
	}

	~CAtlTangramGLVisual();

DECLARE_REGISTRY_RESOURCEID(IDR_ATLTANGRAMGLVISUAL)
DECLARE_GET_CONTROLLING_UNKNOWN();

BEGIN_COM_MAP(CAtlTangramGLVisual)
	COM_INTERFACE_ENTRY(IAtlTangramGLVisual)
	COM_INTERFACE_ENTRY(IAtlTangramVisual)
	COM_INTERFACE_ENTRY(IATLTangramModelEvent)
END_COM_MAP()


public:
	HRESULT __stdcall AdviseConnectionPoint(IATLTangramModel* pModel);
	STDMETHOD(ReleaseConnectionPoint)();
	// IAtlTangramVisual
	virtual HRESULT __stdcall GetModel( const IID& iid, IUnknown** ppI) ;
	virtual HRESULT __stdcall SetSelected(BOOL bSelected) ;

	// ITangramModelEvent
	virtual HRESULT __stdcall OnModelChange() ;

	// IAtlTangramGLVisual
	virtual HRESULT __stdcall Initialize(   IATLTangramModel* pModel,
											IAtlTangramGLWorld* pWorld) ;
	virtual HRESULT __stdcall DrawOn(IAtlTangramCanvas* pCanvas) ;

// Members
private:
	// Event Sink support.
	IConnectionPoint* m_pIConnectionPoint ;
	DWORD m_dwCookie ;

	// Backpointer to parent World component.
	IAtlTangramGLWorld* m_pWorld;

	// Pointer to associated model.
	IATLTangramModel* m_pModel ;

	// Array of vertices.
	TangramPoint2d* m_ptVertices ;
	long m_cVertices ;

	// Selection status.
	BOOL m_bSelected ;

	// Set to TRUE when the visual has been notified by the model.
	BOOL m_bFirstEvent;

};

#endif //__ATLTANGRAMGLVISUAL_H_
