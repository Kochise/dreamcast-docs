// Agg.h : Declaration of the CAgg
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

#include "aggres.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// Aggreg

class CAgg :
	public IDispatchImpl<IAgg, &IID_IAgg, &LIBID_AGGREGLib>,
	public ISupportErrorInfo,
	public CComObjectRoot,
	public CComCoClass<CAgg,&CLSID_CAgg>
{
public:
	CAgg(){}
BEGIN_COM_MAP(CAgg)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IAgg)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()
//DECLARE_NOT_AGGREGATABLE(CAgg)
// Remove the comment from the line above if you don't want your object to
// support aggregation.  The default is to support it

DECLARE_REGISTRY_RESOURCEID(IDR_Agg)
// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IAgg
public:
	STDMETHOD(get_Name)(BSTR* pbstrName);
};
