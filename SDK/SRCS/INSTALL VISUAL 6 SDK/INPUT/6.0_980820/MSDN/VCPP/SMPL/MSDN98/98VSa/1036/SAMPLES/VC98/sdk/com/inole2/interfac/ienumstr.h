/*
 * IENUMSTR.H
 *
 * Definitions of an IEnumString object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IENUMSTR_H_
#define _IENUMSTR_H_

#include <inole.h>

class CEnumString;
typedef class CEnumString *PCEnumString;

class CEnumString : public IEnumString
    {
    private:
        ULONG           m_cRef;     //Object reference count
        LPUNKNOWN       m_pUnkRef;  //IUnknown for ref counting
        ULONG           m_iCur;     //Current element
        ULONG           m_cstr;     //Number of strings in us
        LPOLESTR       *m_prgstr;   //Source of strings

    public:
        CEnumString(LPUNKNOWN, ULONG, LPOLESTR *);
        ~CEnumString(void);

        //IUnknown members that delegate to m_pUnkRef.
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumString members
        STDMETHODIMP Next(ULONG, LPOLESTR *, ULONG *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(IEnumString **);
    };


#endif //_IENUMSTR_H_
