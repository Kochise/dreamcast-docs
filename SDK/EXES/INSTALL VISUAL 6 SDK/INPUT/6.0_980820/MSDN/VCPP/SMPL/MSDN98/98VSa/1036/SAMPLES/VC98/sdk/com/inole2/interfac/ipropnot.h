/*
 * IPROPNOT.H
 *
 * Header for template IPropertyNotifySink interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IPROPNOT_H_
#define _IPROPNOT_H_

#define INC_CONTROLS
#include <inole.h>

class CImpIPropertyNotifySink;
typedef class CImpIPropertyNotifySink *PCImpIPropertyNotifySink;

class CImpIPropertyNotifySink : public IPropertyNotifySink
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIPropertyNotifySink(LPVOID, LPUNKNOWN);
        ~CImpIPropertyNotifySink(void);

        //IPropertyNotifySink interface members
        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP OnChanged(DISPID);
        STDMETHODIMP OnRequestEdit(DISPID);
    };

#endif //_IPROPNOT_H_
