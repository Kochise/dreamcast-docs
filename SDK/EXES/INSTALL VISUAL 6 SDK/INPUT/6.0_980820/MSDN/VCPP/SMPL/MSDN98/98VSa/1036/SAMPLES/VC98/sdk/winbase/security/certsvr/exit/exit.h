//+--------------------------------------------------------------------------
//
// Microsoft Windows
// Copyright (C) Microsoft Corporation, 1996-1997
//
// File:        exit.cpp
//
// Contents:    CCertExit definition
//
//---------------------------------------------------------------------------

#include "resource.h"       // main symbols
#include <certexit.h>

/////////////////////////////////////////////////////////////////////////////
// certexit


class CCertExit: 
    public CComDualImpl<ICertExit, &IID_ICertExit, &LIBID_CERTEXITLib>, 
    public ISupportErrorInfo,
    public CComObjectRoot,
    public CComCoClass<CCertExit, &CLSID_CCertExit>
{
public:
    CCertExit() { m_strConfig = NULL; }
    ~CCertExit();

BEGIN_COM_MAP(CCertExit)
    COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(ICertExit)
    COM_INTERFACE_ENTRY(ISupportErrorInfo)
END_COM_MAP()

DECLARE_NOT_AGGREGATABLE(CCertExit) 

DECLARE_REGISTRY(
    CCertExit,
    wszCLASS_CERTEXIT TEXT(".1"),
    wszCLASS_CERTEXIT,
    IDS_CERTEXIT_DESC,
    THREADFLAGS_BOTH)

    // ISupportsErrorInfo
    STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

    // ICertExit
public:
    STDMETHOD(Initialize)( 
            /* [in] */ BSTR const strConfig,
            /* [retval][out] */ LONG __RPC_FAR *pEventMask);

    STDMETHOD(Notify)(
            /* [in] */ LONG Event,
            /* [in] */ LONG Context);

    STDMETHOD(GetDescription)( 
            /* [retval][out] */ BSTR *pstrDescription);

private:
    // Member variables & private methods here:
    BSTR m_strConfig;
};
