/*
 * BEEPPROP.H
 * Beeper Property Page, Chapter 16
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _BEEPPROP_H_
#define _BEEPPROP_H_

#define INC_AUTOMATION
#define INC_CONTROLS
#define GUIDS_FROM_TYPELIB
#define CHAPTER16
#include <inole.h>

//Get IBeeper definitions for the object we work with
#include "..\beeper6\ibeeper.h"

//Strings
#define IDS_0_PAGETITLE                 0
#define IDS_7_PAGETITLE                 1

#define CCHSTRINGMAX                    30

//Dialog template
#define IDD_BEEPERPROPS_0               101
#define IDD_BEEPERPROPS_7               102

//These match MB_* identifiers for ease of passing to Windows
#define IDC_BEEPDEFAULT                 0x0008
#define IDC_BEEPHAND                    0x0010
#define IDC_BEEPQUESTION                0x0020
#define IDC_BEEPEXCLAMATION             0x0030
#define IDC_BEEPASTERISK                0x0040


//This class factory object creates other objects

class CBeeperPPFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;

    public:
        CBeeperPPFactory(void);
        ~CBeeperPPFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassPPFactory members
        STDMETHODIMP     CreateInstance(LPUNKNOWN, REFIID, PPVOID);
        STDMETHODIMP     LockServer(BOOL);
    };

typedef CBeeperPPFactory *PCBeeperPPFactory;


//Our property page class

BOOL APIENTRY BeepPropPageProc(HWND, UINT, WPARAM, LPARAM);

class CBeeperPropPage : public IPropertyPage
    {
    friend BOOL APIENTRY BeepPropPageProc(HWND, UINT, WPARAM, LPARAM);

    protected:
        ULONG           m_cRef;         //Reference count
        HINSTANCE       m_hInst;        //Module instance
        UINT            m_uIDTemplate;  //Dialog ID
        HWND            m_hDlg;         //Dialog handle

        ULONG           m_cx;           //Dialog size
        ULONG           m_cy;
        UINT            m_cObjects;     //Number of objects
        LCID            m_lcid;         //Current locale
        UINT            m_uIDLastSound; //Last selected in page
        BOOL            m_fDirty;       //Page dirty?
        IBeeper       **m_ppIBeeper;    //Objects to notify

        IPropertyPageSite *m_pIPropertyPageSite;    //Frame's

    public:
        CBeeperPropPage(HINSTANCE);
        ~CBeeperPropPage(void);

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

typedef CBeeperPropPage *PCBeeperPropPage;


#endif //_BEEPPROP_H_
