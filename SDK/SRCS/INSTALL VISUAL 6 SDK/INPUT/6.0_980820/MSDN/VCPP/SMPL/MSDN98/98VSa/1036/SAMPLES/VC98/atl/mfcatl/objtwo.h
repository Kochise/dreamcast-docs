// ObjTwo.h : header file
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


/////////////////////////////////////////////////////////////////////////////
// CObjectTwo: ATL implementation

class CObjectTwo :
	public IDispatchImpl<IObjectTwo, &IID_IObjectTwo, &LIBID_MfcAtl>,
	public CComObjectRoot,
	public CComCoClass<CObjectTwo, &CLSID_ObjectTwo>
{
public:
	CBeeper();
	BEGIN_COM_MAP(CObjectTwo)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IObjectTwo)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CObjectTwo)

	DECLARE_REGISTRY(CObjectTwo, _T("MfcAtl.ObjectTwo.1"), _T("MfcAtl.ObjectTwo"), IDS_OBJECT_TWO_DESC, THREADFLAGS_APARTMENT)
// IObjectTwo
public:
	STDMETHOD(get_SayHello)(BSTR* bstr);
};
