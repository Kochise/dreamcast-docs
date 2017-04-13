/*
 * IIPUIWIN.H
 *
 * Definitions of a template IOleInPlaceUIWindow interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IIPUIWIN_H_
#define _IIPUIWIN_H_

#include <inole.h>

class CImpIOleInPlaceUIWindow;
typedef class CImpIOleInPlaceUIWindow *PCImpIOleInPlaceUIWindow;

class CImpIOleInPlaceUIWindow : public IOleInPlaceUIWindow
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //Fr delegation

    public:
        CImpIOleInPlaceUIWindow(LPVOID, LPUNKNOWN);
        ~CImpIOleInPlaceUIWindow(void);

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
    };


#endif //_IIPUIWIN_H_
