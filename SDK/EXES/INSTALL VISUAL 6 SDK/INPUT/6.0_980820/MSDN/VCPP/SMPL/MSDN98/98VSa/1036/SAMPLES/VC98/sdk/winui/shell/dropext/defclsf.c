
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1995-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//
// This file contains the implementation of SHCreateDefClassObject
//

#include "priv.h"

//=========================================================================
// CDefClassFactory class
//=========================================================================

STDMETHODIMP CDefClassFactory_QueryInterface(IClassFactory FAR * pcf, REFIID riid, LPVOID FAR* ppvObj);
ULONG STDMETHODCALLTYPE CDefClassFactory_AddRef(IClassFactory FAR * pcf);
ULONG STDMETHODCALLTYPE CDefClassFactory_Release(IClassFactory FAR * pcf);
STDMETHODIMP CDefClassFactory_CreateInstance(IClassFactory FAR * pcf, LPUNKNOWN pUnkOuter,
                              REFIID riid,
                              LPVOID FAR* ppvObject);
STDMETHODIMP CDefClassFactory_LockServer(IClassFactory FAR * pcf, BOOL fLock);

//
// CDefClassFactory: Class definition
//
#pragma data_seg(".text")
IClassFactoryVtbl c_vtblAppUIClassFactory = {
            CDefClassFactory_QueryInterface,
            CDefClassFactory_AddRef,
            CDefClassFactory_Release,
            CDefClassFactory_CreateInstance,
	    CDefClassFactory_LockServer
};
#pragma data_seg()

typedef struct
{
    IClassFactory      cf;		
    UINT               cRef;		// Reference count
    LPFNCREATEINSTANCE lpfnCI;		// CreateInstance callback entry
    UINT FAR *         pcRefDll;	// Reference count of the DLL
    const IID FAR *    riidInst;		// Optional interface for instance
} CDefClassFactory;

//
// CDefClassFactory::QueryInterface
//
STDMETHODIMP CDefClassFactory_QueryInterface(IClassFactory FAR * pcf, REFIID riid, LPVOID FAR* ppvObj)
{
    register CDefClassFactory * this=IToClassN(CDefClassFactory, cf, pcf);
    if (IsEqualIID(riid, &IID_IClassFactory)
     || IsEqualIID(riid, &IID_IUnknown))
    {
	(LPCLASSFACTORY)*ppvObj = &this->cf;
	this->cRef++;
        return NOERROR;
    }
    return ResultFromScode(E_NOINTERFACE);
}

//
// CDefClassFactory::AddRef
//
ULONG STDMETHODCALLTYPE CDefClassFactory_AddRef(IClassFactory FAR * pcf)
{
    register CDefClassFactory * this=IToClassN(CDefClassFactory, cf, pcf);
    return (++this->cRef);
}

//
// CDefClassFactory::Release
//
ULONG STDMETHODCALLTYPE CDefClassFactory_Release(IClassFactory FAR * pcf)
{
    register CDefClassFactory * this=IToClassN(CDefClassFactory, cf, pcf);
    if (--this->cRef > 0)
	return this->cRef;

    if (this->pcRefDll) {
	(*this->pcRefDll)--;
    }
    LocalFree((HLOCAL)this);

    return 0;
}

//
// CDefClassFactory::CDefClassFactory
//
STDMETHODIMP CDefClassFactory_CreateInstance(IClassFactory FAR * pcf, LPUNKNOWN pUnkOuter,
                              REFIID riid,
                              LPVOID FAR* ppvObject)
{
    register CDefClassFactory * this=IToClassN(CDefClassFactory, cf, pcf);

    //
    // We don't support aggregation at all.
    //
    if (pUnkOuter)
    {
	return ResultFromScode(CLASS_E_NOAGGREGATION);
    }

    //
    // if this->riidInst is specified, they should match.
    //
    if (this->riidInst==NULL
     || IsEqualIID(riid, this->riidInst)
     || IsEqualIID(riid, &IID_IUnknown))
    {
	return this->lpfnCI(pUnkOuter, riid, ppvObject);
    }

    return ResultFromScode(E_NOINTERFACE);
}

//
// CDefClassFactory::LockServer
//
STDMETHODIMP CDefClassFactory_LockServer(IClassFactory FAR * pcf, BOOL fLock)
{
    // REVIEW: Is this appropriate?
    return ResultFromScode(E_NOTIMPL);
}


//
// CDefClassFactory constructor
//
CDefClassFactory * NEAR PASCAL CDefClassFactory_Create(
	    LPFNCREATEINSTANCE lpfnCI, UINT FAR * pcRefDll, REFIID riidInst)
{
    register CDefClassFactory * pacf;
    pacf = (CDefClassFactory *)LocalAlloc(LPTR, sizeof(CDefClassFactory));
    if (pacf)
    {
	pacf->cf.lpVtbl = &c_vtblAppUIClassFactory;
	pacf->cRef++;  // pacf->cRef=0; (generates smaller code)
	pacf->pcRefDll = pcRefDll;
	pacf->lpfnCI = lpfnCI;
	pacf->riidInst = riidInst;
	if (pcRefDll) {
	    (*pcRefDll)++;
	}
    }
    return pacf;
}


// BUGBUG: remove this for build 86

STDAPI Shell_CreateDefClassObject(REFIID riid, LPVOID FAR* ppv,
			 LPFNCREATEINSTANCE lpfnCI, UINT FAR * pcRefDll,
			 REFIID riidInst)
{
    MessageBeep(0);
    // DebugMsg(DM_TRACE, "Shell_CreateDefClassObject: obsolete, use SHCreateDefClassObject");
    return SHCreateDefClassObject(riid, ppv, lpfnCI, pcRefDll, riidInst);
}

//
// creates a simple default implementation of IClassFactory
//
// Parameters:
//  riid     -- Specifies the interface to the class object
//  ppv      -- Specifies the pointer to LPVOID where the class object pointer
//               will be returned.
//  lpfnCI   -- Specifies the callback entry for instanciation.
//  pcRefDll -- Specifies the address to the DLL reference count (optional)
//  riidInst -- Specifies the interface to the instance (optional).
//
// Notes:
//   The riidInst will be specified only if the instance of the class
//  support only one interface.
//
STDAPI SHCreateDefClassObject(REFIID riid, LPVOID FAR* ppv,
			 LPFNCREATEINSTANCE lpfnCI, UINT FAR * pcRefDll,
			 REFIID riidInst)
{
    // The default class factory supports only IClassFactory interface
    if (IsEqualIID(riid, &IID_IClassFactory))
    {
	CDefClassFactory * pacf = CDefClassFactory_Create(lpfnCI, pcRefDll, riidInst);
	if (pacf)
	{
	    (IClassFactory FAR *)*ppv = &pacf->cf;
	    return NOERROR;
	}
	return ResultFromScode(E_OUTOFMEMORY);
    }
    return ResultFromScode(E_NOINTERFACE);
}
