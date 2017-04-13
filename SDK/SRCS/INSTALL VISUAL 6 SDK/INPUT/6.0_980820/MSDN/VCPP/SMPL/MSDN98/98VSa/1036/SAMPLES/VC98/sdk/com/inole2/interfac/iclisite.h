/*
 * ICLISITE.H
 *
 * Definitions of a template IOleClientSite interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _ICLISITE_H_
#define _ICLISITE_H_

#include <inole.h>

class CImpIOleClientSite;
typedef class CImpIOleClientSite *PCImpIOleClientSite;

class CImpIOleClientSite : public IOleClientSite
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIOleClientSite(LPVOID, LPUNKNOWN);
        ~CImpIOleClientSite(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP SaveObject(void);
        STDMETHODIMP GetMoniker(DWORD, DWORD, LPMONIKER *);
        STDMETHODIMP GetContainer(LPOLECONTAINER *);
        STDMETHODIMP ShowObject(void);
        STDMETHODIMP OnShowWindow(BOOL);
        STDMETHODIMP RequestNewObjectLayout(void);
    };


#endif //_ICLISITE_H_
