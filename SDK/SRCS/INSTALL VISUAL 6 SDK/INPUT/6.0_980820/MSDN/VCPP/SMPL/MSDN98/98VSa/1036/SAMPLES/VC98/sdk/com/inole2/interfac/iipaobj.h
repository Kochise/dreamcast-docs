/*
 * IIPAOBJ.H
 *
 * Definitions of a template IOleInPlaceActiveObject interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IIPAOBJ_H_
#define _IIPAOBJ_H_

#include <inole.h>

class CImpIOleInPlaceActiveObject;
typedef CImpIOleInPlaceActiveObject *PCImpIOleInPlaceActiveObject;

class CImpIOleInPlaceActiveObject
    : public IOleInPlaceActiveObject
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIOleInPlaceActiveObject(LPVOID, LPUNKNOWN);
        ~CImpIOleInPlaceActiveObject(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetWindow(HWND *);
        STDMETHODIMP ContextSensitiveHelp(BOOL);
        STDMETHODIMP TranslateAccelerator(LPMSG);
        STDMETHODIMP OnFrameWindowActivate(BOOL);
        STDMETHODIMP OnDocWindowActivate(BOOL);
        STDMETHODIMP ResizeBorder(LPCRECT, LPOLEINPLACEUIWINDOW
            , BOOL);
        STDMETHODIMP EnableModeless(BOOL);
    };


#endif //_IIPAOBJ_H_
