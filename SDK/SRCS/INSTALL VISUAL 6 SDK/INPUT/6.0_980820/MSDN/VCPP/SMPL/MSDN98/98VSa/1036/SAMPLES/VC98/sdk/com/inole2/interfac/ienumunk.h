/*
 * IENUMUNK.H
 *
 * Definitions of a template IEnumUnknown enumerator.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IENUMUNK_H_
#define _IENUMUNK_H_

#include <inole.h>

class CEnumUnknown;
typedef class CEnumUnknown *PCEnumUnknown;

class CEnumUnknown : public IEnumUnknown
    {
    private:
        ULONG           m_cRef;     //Object reference count
        LPUNKNOWN       m_pUnkRef;  //IUnknown for ref counting
        ULONG           m_iCur;     //Current element
        ULONG           m_cUnk;     //Number of unknowns in us
        LPUNKNOWN      *m_prgUnk;   //Source of unknowns

    public:
        CEnumUnknown(LPUNKNOWN, ULONG, LPUNKNOWN *);
        ~CEnumUnknown(void);

        //IUnknown members that delegate to m_pUnkRef.
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumUnknown members
        STDMETHODIMP Next(ULONG, LPUNKNOWN *, ULONG *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(IEnumUnknown **);
    };


#endif //_IENUMUNK_H_
