/*
 * IPROPPG.H
 *
 * Header for template IPropertyPage interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IPROPPG_H_
#define _IPROPPG_H_

#define INC_CONTROLS
#include <inole.h>

class CImpIPropertyPage;
typedef class CImpIPropertyPage *PCImpIPropertyPage;

class CImpIPropertyPage : public IPropertyPage
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Back pointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIPropertyPage(LPVOID, LPUNKNOWN);
        ~CImpIPropertyPage(void);

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
    };


#endif //_IPROPPG_H_
