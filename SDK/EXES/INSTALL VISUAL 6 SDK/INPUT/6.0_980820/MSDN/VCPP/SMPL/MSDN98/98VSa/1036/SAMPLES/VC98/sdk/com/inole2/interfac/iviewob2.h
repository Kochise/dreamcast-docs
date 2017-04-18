/*
 * IVIEWOB2.H
 *
 * Definitions of a template IViewObject2 interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IVIEWOBJ_H_
#define _IVIEWOBJ_H_

#include <inole.h>

class CImpIViewObject2;
typedef class CImpIViewObject2 *PCImpIViewObject2;

class CImpIViewObject2 : public IViewObject
    {
    private:
        ULONG           m_cRef;         //Interface reference count
        LPVOID          m_pObj;         //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter;    //For delegation

    public:
        CImpIViewObject2(LPVOID, LPUNKNOWN);
        ~CImpIViewObject2(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IViewObject members
        STDMETHODIMP Draw(DWORD, LONG, LPVOID, DVTARGETDEVICE *
            , HDC, HDC, LPCRECTL, LPCRECTL, BOOL (CALLBACK *)(DWORD)
            , DWORD);

        STDMETHODIMP GetColorSet(DWORD, LONG, LPVOID
            , DVTARGETDEVICE *, HDC, LPLOGPALETTE *);

        STDMETHODIMP Freeze(DWORD, LONG, LPVOID, LPDWORD);
        STDMETHODIMP Unfreeze(DWORD);
        STDMETHODIMP SetAdvise(DWORD, DWORD, LPADVISESINK);
        STDMETHODIMP GetAdvise(LPDWORD, LPDWORD, LPADVISESINK *);

        //IViewObject2 members
        STDMETHODIMP GetExtent(DWORD, LONG, DVTARGETDEVICE *
            , LPSIZEL);
    };


#endif //_IVIEWOBJ_H_
