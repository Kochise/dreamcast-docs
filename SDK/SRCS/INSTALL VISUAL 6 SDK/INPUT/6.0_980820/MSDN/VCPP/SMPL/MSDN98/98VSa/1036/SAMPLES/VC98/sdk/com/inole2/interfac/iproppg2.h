/*
 * IPROPPG2.H
 *
 * Header for template IPropertyPage2 interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IPROPPG2_H_
#define _IPROPPG2_H_

#define INC_CONTROLS
#include <inole.h>

class CImpIPropertyPage2;
typedef class CImpIPropertyPage2 *PCImpIPropertyPage2;

class CImpIPropertyPage2 : public IPropertyPage2
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIPropertyPage2(LPVOID, LPUNKNOWN);
        ~CImpIPropertyPage2(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

    	STDMETHODIMP SetPageSite(LPPROPERTYPAGESITE);
    	STDMETHODIMP Activate(HWND, LPCRECT, BOOL);
    	STDMETHODIMP Deactivate(void);
    	STDMETHODIMP GetPageInfo(LPPROPPAGEINFO);
    	STDMETHODIMP SetObjects(ULONG, LPUNKNOWN *);
    	STDMETHODIMP Show(UINT);
    	STDMETHODIMP Move(LPCRECT);
    	STDMETHODIMP IsPageDirty(void);
    	STDMETHODIMP Apply(void);
    	STDMETHODIMP Help(LPCOLESTR);
    	STDMETHODIMP TranslateAccelerator(LPMSG);

        STDMETHODIMP EditProperty(DISPID dispid);
    };


#endif //_IPROPPG2_H_
