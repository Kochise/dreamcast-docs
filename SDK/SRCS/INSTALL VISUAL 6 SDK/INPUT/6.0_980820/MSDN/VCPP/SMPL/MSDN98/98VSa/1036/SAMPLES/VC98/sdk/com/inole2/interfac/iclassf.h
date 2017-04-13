/*
 * ICLASSF.H
 *
 * Definitions for a template Class Factory object with the
 * IClassFactory interface.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _ICLASSF_H_
#define _ICLASSF_H_

#include <inole.h>

class CClassFactory;
typedef class CClassFactory *PCClassFactory;

class CClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;         //Reference count on object

    public:
        CClassFactory(void);
        ~CClassFactory(void);

        //IUnknown interface members
        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, LPVOID *);
        STDMETHODIMP LockServer(BOOL);
    };


#endif //_ICLASSF_H_
