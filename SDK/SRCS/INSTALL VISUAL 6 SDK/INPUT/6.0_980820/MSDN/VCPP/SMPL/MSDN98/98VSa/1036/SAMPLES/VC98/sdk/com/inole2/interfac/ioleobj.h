/*
 * IOLEOBJ.H
 *
 * Definitions of a template IOleObject interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _IOLEOBJ_H_
#define _IOLEOBJ_H_

#include <inole.h>

class CImpIOleObject;
typedef class CImpIOleObject *PCImpIOleObject;

class CImpIOleObject : public IOleObject
    {
    private:
        ULONG           m_cRef;      //Interface reference count
        LPVOID          m_pObj;      //Backpointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIOleObject(LPVOID, LPUNKNOWN);
        ~CImpIOleObject(void);

        //IUnknown members that delegate to m_pUnkOuter.
        STDMETHODIMP         QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IOleObject members
        STDMETHODIMP SetClientSite(LPOLECLIENTSITE);
        STDMETHODIMP GetClientSite(LPOLECLIENTSITE *);
        STDMETHODIMP SetHostNames(LPCOLESTR, LPCOLESTR);
        STDMETHODIMP Close(DWORD);
        STDMETHODIMP SetMoniker(DWORD, LPMONIKER);
        STDMETHODIMP GetMoniker(DWORD, DWORD, LPMONIKER *);
        STDMETHODIMP InitFromData(LPDATAOBJECT, BOOL, DWORD);
        STDMETHODIMP GetClipboardData(DWORD, LPDATAOBJECT *);
        STDMETHODIMP DoVerb(LONG, LPMSG, LPOLECLIENTSITE, LONG
            , HWND, LPCRECT);
        STDMETHODIMP EnumVerbs(LPENUMOLEVERB *);
        STDMETHODIMP Update(void);
        STDMETHODIMP IsUpToDate(void);
        STDMETHODIMP GetUserClassID(CLSID *);
        STDMETHODIMP GetUserType(DWORD, LPTSTR *);
        STDMETHODIMP SetExtent(DWORD, LPSIZEL);
        STDMETHODIMP GetExtent(DWORD, LPSIZEL);
        STDMETHODIMP Advise(LPADVISESINK, DWORD *);
        STDMETHODIMP Unadvise(DWORD);
        STDMETHODIMP EnumAdvise(LPENUMSTATDATA *);
        STDMETHODIMP GetMiscStatus(DWORD, DWORD *);
        STDMETHODIMP SetColorScheme(LPLOGPALETTE);
    };


#endif //_IOLEOBJ_H_
