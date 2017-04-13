/*
 * ISPPROPP.H
 *
 * Header for template ISpecifyPropertyPages interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _ISPPROPP_H_
#define _ISPPROPP_H_

#define INC_CONTROLS
#include <inole.h>

class CImpISpecifyPropertyPages;
typedef class CImpISpecifyPropertyPages *PCImpISpecifyPropertyPages;

class CImpISpecifyPropertyPages : public ISpecifyPropertyPages
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpISpecifyPropertyPages(LPVOID, LPUNKNOWN);
        ~CImpISpecifyPropertyPages(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetPages(CAUUID *);
    };


#endif //_ISPPROPP_H_
