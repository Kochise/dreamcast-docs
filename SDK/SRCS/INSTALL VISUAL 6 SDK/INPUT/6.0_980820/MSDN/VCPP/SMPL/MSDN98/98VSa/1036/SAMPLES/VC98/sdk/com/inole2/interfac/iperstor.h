/*
 * IPERSTOR.H
 *
 * Definitions of a template IPersistStorage interface
 * implementation.  Note that this template includes
 * state flags used in the implementation to track the
 * scribble, no scribble, and hands-off states.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IPERSTOR_H_
#define _IPERSTOR_H_

#include <inole.h>

class CImpIPersistStorage;
typedef class CImpIPersistStorage *PCImpIPersistStorage;

class CImpIPersistStorage : public IPersistStorage
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation
        PSSTATE         m_psState;   //Current State


    public:
        CImpIPersistStorage(LPVOID, LPUNKNOWN);
        ~CImpIPersistStorage(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetClassID(LPCLSID);

        STDMETHODIMP IsDirty(void);
        STDMETHODIMP InitNew(LPSTORAGE);
        STDMETHODIMP Load(LPSTORAGE);
        STDMETHODIMP Save(LPSTORAGE, BOOL);
        STDMETHODIMP SaveCompleted(LPSTORAGE);
        STDMETHODIMP HandsOffStorage(void);
    };


#endif  //_IPERSTOR_H_
