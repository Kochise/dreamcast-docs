/*
 * ISIMPSIT.H
 *
 * Header for template ISimpleFrameSite interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _ISIMPSIT_H_
#define _ISIMPSIT_H_

#define INC_CONTROLS
#include <inole.h>

class CImpISimpleFrameSite;
typedef class CImpISimpleFrameSite *PCImpISimpleFrameSite;

class CImpISimpleFrameSite : public ISimpleFrameSite
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpISimpleFrameSite(LPVOID, LPUNKNOWN);
        ~CImpISimpleFrameSite(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP CImpISimpleFrameSite::PreMessageFilter(HWND
            , UINT, WPARAM, LPARAM, LRESULT *, DWORD *);
        STDMETHODIMP CImpISimpleFrameSite::PostMessageFilter(HWND
            , UINT, WPARAM, LPARAM, LRESULT *, DWORD);
    };


#endif //_ISIMPSIT_H_
