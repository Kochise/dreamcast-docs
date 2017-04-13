/*
 * IIPSITE.H
 *
 * Definitions of a template IOleInPlaceSite interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IIPSITE_H_
#define _IIPSITE_H_

#include <inole.h>

class CImpIOleInPlaceSite;
typedef class CImpIOleInPlaceSite *PCImpIOleInPlaceSite;

class CImpIOleInPlaceSite : public IOleInPlaceSite
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIOleInPlaceSite(LPVOID, LPUNKNOWN);
        ~CImpIOleInPlaceSite(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetWindow(HWND *);
        STDMETHODIMP ContextSensitiveHelp(BOOL);
        STDMETHODIMP CanInPlaceActivate(void);
        STDMETHODIMP OnInPlaceActivate(void);
        STDMETHODIMP OnUIActivate(void);
        STDMETHODIMP GetWindowContext(LPOLEINPLACEFRAME *
            , LPOLEINPLACEUIWINDOW *, LPRECT, LPRECT
            , LPOLEINPLACEFRAMEINFO);
        STDMETHODIMP Scroll(SIZE);
        STDMETHODIMP OnUIDeactivate(BOOL);
        STDMETHODIMP OnInPlaceDeactivate(void);
        STDMETHODIMP DiscardUndoState(void);
        STDMETHODIMP DeactivateAndUndo(void);
        STDMETHODIMP OnPosRectChange(LPCRECT);
    };


#endif //_IIPSITE_H_
