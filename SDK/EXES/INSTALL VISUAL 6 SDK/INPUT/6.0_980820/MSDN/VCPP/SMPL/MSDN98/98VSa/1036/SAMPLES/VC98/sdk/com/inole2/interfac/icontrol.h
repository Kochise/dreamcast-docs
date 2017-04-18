/*
 * ICONTROL.H
 *
 * Definitions of a template IOleControl interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _ICONTROL_H_
#define _ICONTROL_H_

#define INC_CONTROLS
#include <inole.h>

class CImpIOleControl;
typedef class CImpIOleControl *PCImpIOleControl;

class CImpIOleControl : public IOleControl
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIOleControl(LPVOID, LPUNKNOWN);
        ~CImpIOleControl(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetControlInfo(LPCONTROLINFO);
        STDMETHODIMP OnMnemonic(LPMSG);
        STDMETHODIMP OnAmbientPropertyChange(DISPID);
        STDMETHODIMP FreezeEvents(BOOL);
    };


#endif //_ICONTROL_H_
