/*
 * IMONIKER.H
 *
 * Definitions of a template IMoniker interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IMONIKER_H_
#define _IMONIKER_H_

#include <inole.h>

class CImpIMoniker;
typedef class CImpIMoniker *PCImpIMoniker;

class CImpIMoniker : public IMoniker
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIMoniker(LPVOID, LPUNKNOWN);
        ~CImpIMoniker(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetClassID(LPCLSID);

        STDMETHODIMP IsDirty(void);
        STDMETHODIMP Load(LPSTREAM);
        STDMETHODIMP Save(LPSTREAM, BOOL);
        STDMETHODIMP GetSizeMax(ULARGE_INTEGER *);

        STDMETHODIMP BindToObject(LPBC, LPMONIKER
            , REFIID, LPVOID *);
        STDMETHODIMP BindToStorage(LPBC, LPMONIKER
            , REFIID, LPVOID *);
        STDMETHODIMP Reduce(LPBC, DWORD, LPMONIKER *, LPMONIKER *);
        STDMETHODIMP ComposeWith(LPMONIKER, BOOL, LPMONIKER *);
        STDMETHODIMP Enum(BOOL, LPENUMMONIKER *);
        STDMETHODIMP IsEqual(LPMONIKER);
        STDMETHODIMP Hash(LPDWORD);
        STDMETHODIMP IsRunning(LPBC, LPMONIKER, LPMONIKER);
        STDMETHODIMP GetTimeOfLastChange(LPBC, LPMONIKER
            , FILETIME *);
        STDMETHODIMP Inverse(LPMONIKER *);
        STDMETHODIMP CommonPrefixWith(LPMONIKER, LPMONIKER *);
        STDMETHODIMP RelativePathTo(LPMONIKER, LPMONIKER *);
        STDMETHODIMP GetDisplayName(LPBC, LPMONIKER, LPOLESTR *);
        STDMETHODIMP ParseDisplayName(LPBC, LPMONIKER, LPOLESTR
            , ULONG *, LPMONIKER *);
        STDMETHODIMP IsSystemMoniker(LPDWORD);
    };


#endif //_IMONIKER_H_
