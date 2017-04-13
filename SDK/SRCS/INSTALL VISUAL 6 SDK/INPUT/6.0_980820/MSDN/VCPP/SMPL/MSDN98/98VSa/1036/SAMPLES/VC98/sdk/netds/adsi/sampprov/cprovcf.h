/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CProvCf.h

Abstract:

    Class Factory for Provider Object
Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CPROVCF_H_
#define _CPROVCF_H_

class CSampleDSProviderCF : public StdClassFactory
{
public:
    STDMETHOD(CreateInstance)(IUnknown * pUnkOuter, REFIID iid, LPVOID * ppv);
};


#endif

