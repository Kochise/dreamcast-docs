/*
 * IENUMVRB.H
 *
 * Definitions of an IEnumOLEVERB object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IENUMVRB_H_
#define _IENUMVRB_H_

#include <inole.h>

class CEnumOLEVERB;
typedef class CEnumOLEVERB *PCEnumOLEVERB;

class CEnumOLEVERB : public IEnumOLEVERB
    {
    private:
        ULONG           m_cRef;     //Object reference count
        LPUNKNOWN       m_pUnkRef;  //IUnknown for ref counting
        ULONG           m_iCur;     //Current element
        ULONG           m_cVerb;    //Number of verbs in us
        LPOLEVERB      *m_prgVerb;  //Source of verbs

    public:
        CEnumOLEVERB(LPUNKNOWN, ULONG, LPOLEVERB *);
        ~CEnumOLEVERB(void);

        //IUnknown members that delegate to m_pUnkRef.
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumOLEVERB members
        STDMETHODIMP Next(ULONG, LPOLEVERB, ULONG *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(IEnumOLEVERB **);
    };


#endif //_IENUMVRB_H_
