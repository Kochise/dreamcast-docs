/*
 * IPROVINF.H
 *
 * Header for template IProvideClassInfo interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IPROVINF_H_
#define _IPROVINF_H_

#define INC_CONTROLS
#include <inole.h>

class CImpIProvideClassInfo;
typedef class CImpIProvideClassInfo *PCImpIProvideClassInfo;

class CImpIProvideClassInfo : public IProvideClassInfo
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIProvideClassInfo(LPVOID, LPUNKNOWN);
        ~CImpIProvideClassInfo(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetClassInfo(LPTYPEINFO *);
    };


#endif //_IPROVINF_H_
