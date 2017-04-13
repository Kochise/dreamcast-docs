/*
 * IPROPPSI.H
 *
 * Header for template IPropertyPageSite interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IPROPPSI_H_
#define _IPROPPSI_H_

#define INC_CONTROLS
#include <inole.h>

class CImpIPropertyPageSite;
typedef class CImpIPropertyPageSite *PCImpIPropertyPageSite;

class CImpIPropertyPageSite : public IPropertyPageSite
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIPropertyPageSite(LPVOID, LPUNKNOWN);
        ~CImpIPropertyPageSite(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

    	STDMETHODIMP OnStatusChange(DWORD);
    	STDMETHODIMP GetLocaleID(LCID *);
    	STDMETHODIMP GetPageContainer(LPUNKNOWN *);
    	STDMETHODIMP TranslateAccelerator(LPMSG);
    };


#endif //_IPROPPSI_H_
