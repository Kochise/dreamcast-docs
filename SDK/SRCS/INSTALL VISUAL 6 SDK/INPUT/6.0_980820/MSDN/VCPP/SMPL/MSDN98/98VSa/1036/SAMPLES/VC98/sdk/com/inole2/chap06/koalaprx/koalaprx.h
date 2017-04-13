/*
 * KOALAPRX.H
 * Koala Custom Marshaling Proxy Chapter 6
 *
 * Definitions, classes, and prototypes for a proxy for a
 * custom marshaling Koala object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _KOALAPRX_H_
#define _KOALAPRX_H_


//Get the object definitions
#include "koala.h"

void ObjectDestroyed(void);

//DKOALA.CPP
//This class factory object creates Koala objects.

class CKoalaProxyFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;

    public:
        CKoalaProxyFactory(void);
        ~CKoalaProxyFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID
                                 , PPVOID);
        STDMETHODIMP         LockServer(BOOL);
    };

typedef CKoalaProxyFactory *PCKoalaProxyFactory;

#endif //_KOALAPRX_H_
