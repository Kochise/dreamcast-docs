/*++

Copyright (c) 1996 Microsoft Corporation

Module Name:

    CNamCF.h

Abstract:

   Class factory for standard Namespace object.

Author:

Environment:

    User mode

Revision History :

--*/
#ifndef _CNAMCF_H_
#define _CNAMCF_H_


class CSampleDSNamespaceCF : public StdClassFactory
{
public:
    STDMETHOD(CreateInstance)(IUnknown * pUnkOuter, REFIID iid, LPVOID * ppv);
};


#endif

