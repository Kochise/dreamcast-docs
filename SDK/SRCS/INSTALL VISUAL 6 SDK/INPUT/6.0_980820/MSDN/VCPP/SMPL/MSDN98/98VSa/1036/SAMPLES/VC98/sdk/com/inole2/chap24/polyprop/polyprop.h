/*
 * POLYPROP.H
 * Polyline Property Page, Chapter 24
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _POLYPROP_H_
#define _POLYPROP_H_

#define INC_AUTOMATION
#define INC_CONTROLS
#define INC_CLASSLIB
#define GUIDS_FROM_TYPELIB
#define CHAPTER24
#include <inole.h>

//Get IPolylineControl definitions for the object we work with
#include "..\polyline\ipoly.h"

//Dialog template
#define IDD_POLYLINEPROPS                 100


#define ID_GROUPSTYLE       199
#define ID_LINEMIN          200
#define ID_LINESOLID        200     //(ID_LINEMIN+PS_SOLID)
#define ID_LINEDASH         201     //(ID_LINEMIN+PS_DASH)
#define ID_LINEDOT          202     //(ID_LINEMIN+PS_DOT)
#define ID_LINEDASHDOT      203     //(ID_LINEMIN+PS_DASHDOT)
#define ID_LINEDASHDOTDOT   204     //(ID_LINEMIN+PS_DASHDOTDOT)

#define ID_GROUPCOLORS      300
#define ID_COLORBACK        301
#define ID_COLORLINE        302


//This class factory object creates other objects

class CPolyPPFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;

    public:
        CPolyPPFactory(void);
        ~CPolyPPFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassPPFactory members
        STDMETHODIMP     CreateInstance(LPUNKNOWN, REFIID, PPVOID);
        STDMETHODIMP     LockServer(BOOL);
    };

typedef CPolyPPFactory *PCPolyPPFactory;


//Our property page class

BOOL APIENTRY PolyPropPageProc(HWND, UINT, WPARAM, LPARAM);

class CPolyPropPage : public IPropertyPage
    {
    friend BOOL APIENTRY PolyPropPageProc(HWND, UINT, WPARAM, LPARAM);

    protected:
        ULONG           m_cRef;         //Reference count
        HINSTANCE       m_hInst;        //Module instance
        HWND            m_hDlg;         //Dialog handle

        ULONG           m_cx;           //Dialog size
        ULONG           m_cy;
        UINT            m_cObjects;     //Number of objects
        UINT            m_uIDLastLine;  //Last selected in page
        COLORREF        m_crLastBack;   //Last background color
        COLORREF        m_crLastLine;   //Last line color
        BOOL            m_fDirty;       //Page dirty?

        IPolylineControl **m_ppObj;

        IPropertyPageSite *m_pIPropertyPageSite;    //Frame's

    public:
        CPolyPropPage(HINSTANCE);
        ~CPolyPropPage(void);

        BOOL Init(void);
        void FreeAllObjects(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

    	STDMETHODIMP SetPageSite(LPPROPERTYPAGESITE);
    	STDMETHODIMP Activate(HWND, LPCRECT, BOOL);
    	STDMETHODIMP Deactivate(void);
    	STDMETHODIMP GetPageInfo(LPPROPPAGEINFO);
    	STDMETHODIMP SetObjects(ULONG, LPUNKNOWN *);
    	STDMETHODIMP Show(UINT);
    	STDMETHODIMP Move(LPCRECT);
    	STDMETHODIMP IsPageDirty(void);
    	STDMETHODIMP Apply(void);
    	STDMETHODIMP Help(LPCOLESTR);
    	STDMETHODIMP TranslateAccelerator(LPMSG);
    };

typedef CPolyPropPage *PCPolyPropPage;


#endif //_POLYPROP_H_
