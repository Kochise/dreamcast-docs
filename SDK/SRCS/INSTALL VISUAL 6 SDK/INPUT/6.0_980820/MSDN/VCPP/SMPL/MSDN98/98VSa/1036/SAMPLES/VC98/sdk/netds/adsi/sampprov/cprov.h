/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CProv.h

Abstract:

  Provides Moniker support for Ole Ds GetObject

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CPROV_H_
#define _CPROV_H_

class CSampleDSProvider :  INHERIT_TRACKING,
                        public IParseDisplayName
{
public:

    /* IUnknown methods */
    STDMETHOD(QueryInterface)(THIS_ REFIID riid, LPVOID FAR* ppvObj) ;

    DECLARE_STD_REFCOUNTING

    /* IParseDisplayName */
    STDMETHOD(ParseDisplayName)(THIS_ IBindCtx* pbc,
                                      WCHAR* szDisplayName,
                                      ULONG* pchEaten,
                                      IMoniker** ppmk);
    CSampleDSProvider::CSampleDSProvider();

    CSampleDSProvider::~CSampleDSProvider();

    static HRESULT Create(CSampleDSProvider FAR * FAR * ppProvider);

    HRESULT
    CSampleDSProvider::ResolvePathName(IBindCtx* pbc,
                    WCHAR* szDisplayName,
                    ULONG* pchEaten,
                    IMoniker** ppmk
                    );

protected:

};

#endif

