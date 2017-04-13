// MinObj.h : Declaration of the CMinObj
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

////////////////////////////////////////////////////////////////////////////
// minimal

class CMinObj :
	public IMinObj,
	public CComObjectRoot,
	public CComCoClass<CMinObj,&CLSID_CMinObj>
{
public:
	CMinObj() {}
BEGIN_COM_MAP(CMinObj)
	COM_INTERFACE_ENTRY(IMinObj)
END_COM_MAP()

// making not aggregatable reduces size
DECLARE_NOT_AGGREGATABLE(CMinObj)

// with this macro you can put the object in the object map evan though
// it does not have any self registration capabilities (in our case we
// use an external REG file.
DECLARE_NO_REGISTRY()

// IMinObj
public:
	STDMETHOD(Hello)();
};
