/*
 * IIPFRAME.H
 *
 * Definitions of a template IOleInPlaceFrame interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IIPFRAME_H_
#define _IIPFRAME_H_

#include <inole.h>

class CImpIOleInPlaceFrame;
typedef class CImpIOleInPlaceFrame *PCImpIOleInPlaceFrame;

class CImpIOleInPlaceFrame : public IOleInPlaceFrame
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIOleInPlaceFrame(LPVOID, LPUNKNOWN);
        ~CImpIOleInPlaceFrame(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetWindow(HWND *);
        STDMETHODIMP ContextSensitiveHelp(BOOL);
        STDMETHODIMP GetBorder(LPRECT);
        STDMETHODIMP RequestBorderSpace(LPCBORDERWIDTHS);
        STDMETHODIMP SetBorderSpace(LPCBORDERWIDTHS);
        STDMETHODIMP SetActiveObject(LPOLEINPLACEACTIVEOBJECT
            , LPCOLESTR);
        STDMETHODIMP InsertMenus(HMENU, LPOLEMENUGROUPWIDTHS);
        STDMETHODIMP SetMenu(HMENU, HOLEMENU, HWND);
        STDMETHODIMP RemoveMenus(HMENU);
        STDMETHODIMP SetStatusText(LPCOLESTR);
        STDMETHODIMP EnableModeless(BOOL);
        STDMETHODIMP TranslateAccelerator(LPMSG, WORD);
    };


#endif //_IIPFRAME_H_
