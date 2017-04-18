// AtlTangramGdiVisual.h : Declaration of the CAtlTangramGdiVisual

#ifndef __ATLTANGRAMGDIVISUAL_H_
#define __ATLTANGRAMGDIVISUAL_H_

#include "resource.h"       // main symbols
#include "util.h"
#include "AtlEvent_i.h"


/////////////////////////////////////////////////////////////////////////////
// CAtlTangramGdiVisual
class ATL_NO_VTABLE CAtlTangramGdiVisual :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAtlTangramGdiVisual, &CLSID_AtlTangramGdiVisual>,
	public IAtlTangramGdiVisual,
	public IATLTangramModelEvent   // event sink interface
{
public:
	CAtlTangramGdiVisual():
		m_pGdiWorld(0),
		m_pModel(0),
		m_pIConnectionPoint(0),
		m_ptVertices(0),
		m_dwCookie(0),
		m_bSelected(FALSE)
	{
	}

	~CAtlTangramGdiVisual();

DECLARE_REGISTRY_RESOURCEID(IDR_ATLTANGRAMGDIVISUAL)

BEGIN_COM_MAP(CAtlTangramGdiVisual)
	COM_INTERFACE_ENTRY(IAtlTangramGdiVisual)
	COM_INTERFACE_ENTRY(IAtlTangramVisual)
	COM_INTERFACE_ENTRY(IATLTangramModelEvent)
END_COM_MAP()

public:

	// IAtlTangramVisual
	virtual HRESULT __stdcall GetModel( const IID& iid, IUnknown** ppI) ;
	virtual HRESULT __stdcall SetSelected(BOOL bSelected) ;

	// IAtlTangramGdiVisual
	virtual HRESULT __stdcall Initialize(IATLTangramModel* pModel, IAtlTangramGdiWorld* pWorld) ;
	virtual HRESULT __stdcall IsPtIn(POINT pt) ;
	virtual HRESULT __stdcall GetBoundingRect(RECT* pBoundingRect) ;
	virtual HRESULT __stdcall DrawOn(IAtlTangramCanvas* pCanvas) ;

	// ITangramModelEvent
	virtual HRESULT __stdcall OnModelChange() ;

	// Helper function
	void SyncToModel() ;

	HRESULT __stdcall AdviseConnectionPoint(IATLTangramModel* pModel);
	STDMETHOD(ReleaseConnectionPoint)();

// Member Variables
private:
	// Event Sink support.
	IConnectionPoint* m_pIConnectionPoint ;
	DWORD m_dwCookie ;

	// Backpointer to parent World component.
	IAtlTangramGdiWorld* m_pGdiWorld ;

	// Pointer to associated model.
	IATLTangramModel* m_pModel ;

	// Array of vertices.
	POINT* m_ptVertices ;
	long m_cVertices ;

	// Selection status.
	BOOL m_bSelected ;
};

#endif //__ATLTANGRAMGDIVISUAL_H_
