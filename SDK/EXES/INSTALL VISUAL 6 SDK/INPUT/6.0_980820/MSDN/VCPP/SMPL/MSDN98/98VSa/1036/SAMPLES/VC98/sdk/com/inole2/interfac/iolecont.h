/*
 * IOLECONT.H
 *
 * Definitions of a template IOleItemContainer interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IOLECONT_H_
#define _IOLECONT_H_

#include <inole.h>

class CImpIOleItemContainer;
typedef class CImpIOleItemContainer *PCImpIOleItemContainer;

class CImpIOleItemContainer : public IOleItemContainer
    {
    protected:
        ULONG               m_cRef;
        LPVOID              m_pObj;
        LPUNKNOWN           m_pUnkOuter;

    public:
        CImpIOleItemContainer(LPVOID, LPUNKNOWN);
        ~CImpIOleItemContainer(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP ParseDisplayName(LPBC, LPOLESTR, ULONG *
                         , LPMONIKER *);
        STDMETHODIMP EnumObjects(DWORD, LPENUMUNKNOWN *);
        STDMETHODIMP LockContainer(BOOL);
        STDMETHODIMP GetObject(LPOLESTR, DWORD, LPBINDCTX, REFIID
                         , LPVOID *);
        STDMETHODIMP GetObjectStorage(LPOLESTR, LPBINDCTX, REFIID
                         , LPVOID *);
        STDMETHODIMP IsRunning(LPOLESTR);
    };

#endif  //_IOLECONT_H_
