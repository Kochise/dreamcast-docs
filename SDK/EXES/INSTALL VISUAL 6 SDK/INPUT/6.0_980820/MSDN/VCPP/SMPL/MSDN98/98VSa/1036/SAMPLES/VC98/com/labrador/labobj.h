// LabObj.h : Declaration of the CLabrador
//
// This is a part of the ActiveX Template Library.
// Copyright (C) 1996 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// ActiveX Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// ActiveX Template Library product.

#include "labres.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// Beeper

class CLabrador :
    public IMammal,
    public IDog,
    public CComObjectRoot,
    public CComCoClass<CLabrador, &CLSID_Labrador>
{
public:
    CLabrador();
BEGIN_COM_MAP(CLabrador)
    COM_INTERFACE_ENTRY(IMammal)
    COM_INTERFACE_ENTRY(IDog)
END_COM_MAP()
DECLARE_NOT_AGGREGATABLE(CLabrador)
DECLARE_REGISTRY(CLabrador, _T("LABRADOR.Labrador.1"), _T("LABRADOR.Labrador.1"), IDS_LABRADOR_DESC, THREADFLAGS_BOTH)

// IDog
    STDMETHOD(GetPetName)(MY_BSTR pStr);
    STDMETHOD(SetPetName)(MY_BSTR pStr);
    STDMETHOD(IsBarking)(BOOL* pBool);

// IMammal
    STDMETHOD(GetSpeciesName)(MY_BSTR pStr);
    STDMETHOD(IsAlive)(BOOL* pBool);

private:
    WCHAR   m_szPetName[32];
    WCHAR   m_szSpeciesName[32];
    BOOL    m_bIsBarking;
    BOOL    m_bIsAlive;
};
