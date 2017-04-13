/*
 * IADVSNK2.H
 *
 * Definitions of a template IAdviseSink2 interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IADVSNK2_H_
#define _IADVSNK2_H_

#include <inole.h>

class CImpIAdviseSink2;
typedef class CImpIAdviseSink2 *PCImpIAdviseSink2;

class CImpIAdviseSink2 : public IAdviseSink2
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIAdviseSink2(LPVOID, LPUNKNOWN);
        ~CImpIAdviseSink2(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IAdviseSink
        STDMETHODIMP_(void)  OnDataChange(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP_(void)  OnViewChange(DWORD, LONG);
        STDMETHODIMP_(void)  OnRename(LPMONIKER);
        STDMETHODIMP_(void)  OnSave(void);
        STDMETHODIMP_(void)  OnClose(void);

        //IAdviseSink2
        STDMETHODIMP_(void)  OnLinkSrcChange(LPMONIKER);
    };


#endif //_IADVSNK2_H_
