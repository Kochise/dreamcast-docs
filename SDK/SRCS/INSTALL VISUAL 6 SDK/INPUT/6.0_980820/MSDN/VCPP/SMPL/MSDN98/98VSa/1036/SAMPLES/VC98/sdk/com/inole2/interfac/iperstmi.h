/*
 * IPERSTMI.H
 *
 * Definitions of a template IPersistStreamInit interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IPERSTMI_H_
#define _IPERSTMI_H_

#define INC_CONTROLS
#include <inole.h>

class CImpIPersistStreamInit;
typedef class CImpIPersistStreamInit *PCImpIPersistStreamInit;

class CImpIPersistStreamInit : public IPersistStreamInit
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIPersistStreamInit(LPVOID, LPUNKNOWN);
        ~CImpIPersistStreamInit(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetClassID(LPCLSID);

        STDMETHODIMP IsDirty(void);
        STDMETHODIMP Load(LPSTREAM);
        STDMETHODIMP Save(LPSTREAM, BOOL);
        STDMETHODIMP GetSizeMax(ULARGE_INTEGER *);

        STDMETHODIMP InitNew(void);
    };


#endif  //_IPERSTMI_H_
