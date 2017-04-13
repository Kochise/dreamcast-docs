// OBJECTS.H : declarations for CMyCircle, CMyCircleCollection
//          and CMyCircleCollectionContainer
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

#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include "circcres.h"

/////////////////////////////////////////////////////////////////////////////
// class CMyCircle : user defined object for enumeration

class CMyCircle :
	public IDispatchImpl<IMyCircle, &IID_IMyCircle, &LIBID_CIRCCOLLLib>,
	public ISupportErrorInfo,
	public CComObjectRoot
{
public:
	CMyCircle();
BEGIN_COM_MAP(CMyCircle)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IMyCircle)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
DECLARE_NOT_AGGREGATABLE(CMyCircle)

// IMyCircle
	STDMETHOD(get_XCenter)(double* pXCenter);
	STDMETHOD(put_XCenter)(double xCenter);
	STDMETHOD(get_YCenter)(double* pYCenter);
	STDMETHOD(put_YCenter)(double yCenter);
	STDMETHOD(get_Radius)(double* pRadius);
	STDMETHOD(put_Radius)(double Radius);
	STDMETHOD(get_Label)(BSTR* bstrLabel);
	STDMETHOD(put_Label)(BSTR bstrLAbel);
//ISupportErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		return (InlineIsEqualGUID(IID_IMyCircle,riid)) ? S_OK : S_FALSE;
	}

// Attributes
protected:
	double          m_xCenter;
	double          m_yCenter;
	double          m_Radius;
	CComBSTR        m_bstrLabel;

	friend class CMyCircleCollection;
};

///////////////////////////////////////////////////////////////////////////
// class CMyCircleCollectionCreator

class CMyCircleCollectionCreator :
	public IDispatchImpl<IMyCircleCollectionCreator, &IID_IMyCircleCollectionCreator, &LIBID_CIRCCOLLLib>,
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CMyCircleCollectionCreator,&CLSID_MyCircleCollectionCreator>
{
public:
	BEGIN_COM_MAP(CMyCircleCollectionCreator)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IMyCircleCollectionCreator)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CMyCircleCollectionCreator)
	DECLARE_REGISTRY(CMyCircleCollectionCreator, _T("CircColl.MyCircleCollection.1"), _T("CircColl.MyCircleCollection.1"), IDS_CIRCLECOLL_DESC, THREADFLAGS_BOTH)

// IMyCircleCollectionCreator
	STDMETHOD(GetCircles)(short n, VARIANT* retval);
//ISupportErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		return (InlineIsEqualGUID(IID_IMyCircleCollectionCreator,riid)) ? S_OK : S_FALSE;
	}
};


///////////////////////////////////////////////////////////////////////////
// class CMyCircleCollection

class CMyCircleCollection :
	public IDispatchImpl<IMyCircleCollection, &IID_IMyCircleCollection, &LIBID_CIRCCOLLLib>,
	public ISupportErrorInfo,
	public CComObjectRoot
{
public:
	BEGIN_COM_MAP(CMyCircleCollection)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IMyCircleCollection)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CMyCircleCollection)
	CMyCircleCollection()
	{
		m_VarVect = NULL;
		m_nSize = 0;
	}
	~CMyCircleCollection()
	{
		delete [] m_VarVect;
	}

// IMyCircleCollection methods
	STDMETHOD(get_Count)(long* retval);
	STDMETHOD(get_Item)(long Index, VARIANT* retval);
	STDMETHOD(get__NewEnum)(IUnknown** retval);
//ISupportErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		return (InlineIsEqualGUID(IID_IMyCircleCollection,riid)) ? S_OK : S_FALSE;
	}

// helpers
public:
	void Init(short n);
protected:
// internal data
	CComVariant* m_VarVect;
	int m_nSize;
};

///////////////////////////////////////////////////////////////////////////

#endif // __OBJECTS_H__
