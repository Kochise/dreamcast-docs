/*
 * IPERPBRO.H
 *
 * Header for template IPerPropertyBrowsing interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IPERPBRO_H_
#define _IPERPBRO_H_

#define INC_CONTROLS
#include <inole.h>

class CImpIPerPropertyBrowsing;
typedef class CImpIPerPropertyBrowsing *PCImpIPerPropertyBrowsing;

class CImpIPerPropertyBrowsing : public IPerPropertyBrowsing
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIPerPropertyBrowsing(LPVOID, LPUNKNOWN);
        ~CImpIPerPropertyBrowsing(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP OnStatusChange(DWORD);
        STDMETHODIMP GetDisplayString(DISPID, BSTR *);
        STDMETHODIMP MapPropertyToPage(DISPID, LPCLSID);
        STDMETHODIMP GetPredefinedStrings(DISPID, CALPOLESTR *
        	, CADWORD *);
        STDMETHODIMP GetPredefinedValue(DISPID, DWORD, VARIANT *);
    };


#endif //_IPERPBRO_H_
