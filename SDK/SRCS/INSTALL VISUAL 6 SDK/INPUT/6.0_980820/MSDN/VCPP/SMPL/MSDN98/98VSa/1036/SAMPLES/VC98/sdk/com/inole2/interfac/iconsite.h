/*
 * ICONSITE.H
 *
 * Definitions of a template IOleControlSite interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _ICONSITE_H_
#define _ICONSITE_H_

#define INC_CONTROLS
#include <inole.h>

class CImpIOleControlSite;
typedef class CImpIOleControlSite *PCImpIOleControlSite;

class CImpIOleControlSite : public IOleControlSite
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIOleControlSite(LPVOID, LPUNKNOWN);
        ~CImpIOleControlSite(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP OnControlInfoChanged(void);
        STDMETHODIMP LockInPlaceActive(BOOL);
        STDMETHODIMP GetExtendedControl(LPDISPATCH *);
        STDMETHODIMP TransformCoords(POINTL *, POINTF *, DWORD);
        STDMETHODIMP TranslateAccelerator(LPMSG, DWORD);
        STDMETHODIMP OnFocus(BOOL);
        STDMETHODIMP ShowPropertyFrame(void);
    };


#endif //_ICONSITE_H_
