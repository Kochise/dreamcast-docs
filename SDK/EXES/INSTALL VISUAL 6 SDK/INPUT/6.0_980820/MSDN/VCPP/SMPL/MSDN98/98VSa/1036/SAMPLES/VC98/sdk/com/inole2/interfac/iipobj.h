/*
 * IIPOBJ.H
 *
 * Definitions of a template IOleInPlaceObject interface
 * implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IIPOBJ_H_
#define _IIPOBJ_H_

#include <inole.h>

class CImpIOleInPlaceObject;
typedef class CImpIOleInPlaceObject *PCImpIOleInPlaceObject;

class CImpIOleInPlaceObject : public IOleInPlaceObject
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIOleInPlaceObject(LPVOID, LPUNKNOWN);
        ~CImpIOleInPlaceObject(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetWindow(HWND *);
        STDMETHODIMP ContextSensitiveHelp(BOOL);
        STDMETHODIMP InPlaceDeactivate(void);
        STDMETHODIMP UIDeactivate(void);
        STDMETHODIMP SetObjectRects(LPCRECT, LPCRECT);
        STDMETHODIMP ReactivateAndUndo(void);
    };


#endif //_IIPOBJ_H_
