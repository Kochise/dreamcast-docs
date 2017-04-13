// ATLTangramModel.h : Declaration of the CATLTangramModel
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

#ifndef __ATLTANGRAMMODEL_H_
#define __ATLTANGRAMMODEL_H_

#include "resource.h"       // main symbols
#include "CPAtlModel.h"
#include "ATLModel.h"


/////////////////////////////////////////////////////////////////////////////
// CATLTangramModel
class ATL_NO_VTABLE CATLTangramModel :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CATLTangramModel, &CLSID_ATLTangramModel>,
	public IConnectionPointContainerImpl<CATLTangramModel>,
	public CProxyIATLTangramModelEvent<CATLTangramModel>,
	public IATLTangramModel,
	public IATLTangramTransform
{
public:
	CATLTangramModel()
	:   m_pVertices(NULL),
		m_pTransformVertices(NULL),
		m_cVertices(0),
		m_dDegrees(0.0),        // Zero Degrees
		m_cosDegrees(1.0),      // cos(0) = 1.0
		m_sinDegrees(0.0)       // sin(0) = 0.0
	{
		m_ptdTranslate.x = 0.0 ;
		m_ptdTranslate.y = 0.0 ;
	}

	~CATLTangramModel()
	{
		if (m_pVertices != NULL)
		{
			delete [] m_pVertices ;
		}

		if (m_pTransformVertices != NULL)
		{
			delete [] m_pTransformVertices ;
		}
	}

#ifndef _LOCAL_SERVER
DECLARE_REGISTRY_RESOURCEID(IDR_ATLTANGRAMMODEL)
#else
DECLARE_REGISTRY_RESOURCEID(IDR_IDRATLTANGRAMEXE)
#endif

BEGIN_COM_MAP(CATLTangramModel)
	COM_INTERFACE_ENTRY(IATLTangramModel)
	COM_INTERFACE_ENTRY(IATLTangramTransform)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CATLTangramModel)
	CONNECTION_POINT_ENTRY(IID_IATLTangramModelEvent)
END_CONNECTION_POINT_MAP()



public:
	// IATLTangramModel Methods
	virtual HRESULT __stdcall GetNumberOfVertices(long* pNumVertices) ;
	virtual HRESULT __stdcall GetVertices(long cVertices, TangramPoint2d* points) ;
	virtual HRESULT __stdcall SetVertices(long cVertices, TangramPoint2d* points) ;

	// IATLTangramTransform
	virtual HRESULT __stdcall Translate(double x, double y) ;
	virtual HRESULT __stdcall GetTranslation(TangramPoint2d* point);
	virtual HRESULT __stdcall Rotate(double fDegrees) ;
	virtual HRESULT __stdcall GetRotation( double* pRotation) ;

// Internal Helper Functions
private:
	// Applies the current transform to the vertices.
	void applyTransform() ;

// Members variables.
private:
	// Untransformed vertices in model co-ordinates.
	TangramPoint2d* m_pVertices;

	// Transformed vertices in model co-ordintes.
	TangramPoint2d* m_pTransformVertices ;

	// Number of vertices in this model.
	int m_cVertices ;

	// Angle of rotation in degrees.
	double m_dDegrees ;

	// Cache for the cos of the angle of rotation.
	double m_cosDegrees;

	// Cache for the sin of the angle of rotation.
	double m_sinDegrees;

	// Point to translate the origin.
	TangramPoint2d m_ptdTranslate ;

	// Connection Point support
//  IConnectionPoint* m_pConnectionPoint ;
};

#endif //__ATLTANGRAMMODEL_H_
