/*
 * AUTOCLI2.H
 * Automation Client with Property Pages Chapter 16
 *
 * Definitions and structures.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */

#ifndef _AUTOCLI2_H_
#define _AUTOCLI2_H_

#define INC_AUTOMATION
//CHAPTER16MOD
#define INC_CONTROLS
#define CHAPTER16
//End CHAPTER16MOD
#include <inole.h>
#include <shellapi.h>
#include <malloc.h>

//Menu Resource ID and Commands
#define IDR_MENU                    1

#define IDM_GETSOUND                0x0001
#define IDM_BEEP                    0x0002
#define IDM_EXIT                    0x0003

//CHAPTER16MOD
#define IDM_PROPERTIES              0x0004
#define IDM_ENFORCEREADONLY         0x0005
//End CHAPTER16MOD

//These match MB_* identifiers for MessageBeep
#define IDM_SETSOUNDDEFAULT         0x0008
#define IDM_SETSOUNDHAND            0x0010
#define IDM_SETSOUNDQUESTION        0x0020
#define IDM_SETSOUNDEXCLAMATION     0x0030
#define IDM_SETSOUNDASTERISK        0x0040

#define IDM_SETSOUNDBOGUS           0x0555


//Stringtable IDs
#define CCHSTRINGMAX                80
#define IDS_MESSAGEEXCEPTION        0
#define IDS_MESSAGEEXCEPTIONSCODE   1
#define IDS_MESSAGEUNKNOWNEXCEPTION 2

//CHAPTER16MOD
class CPropertyNotifySink;
typedef CPropertyNotifySink *PCPropertyNotifySink;
//End CHAPTER16MOD

//AUTOCLI2.CPP
LRESULT APIENTRY AutoClientWndProc(HWND, UINT, WPARAM, LPARAM);
void HelpDirFromCLSID(CLSID, LPTSTR);

class CApp
    {
    friend LRESULT APIENTRY AutoClientWndProc(HWND, UINT, WPARAM
        , LPARAM);

    //CHAPTER16MOD
    friend CPropertyNotifySink;
    //End CHAPTER16MOD

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle
        BOOL            m_fInitialized;     //Did CoInitialize work?
        LCID            m_lcid;             //User locale
        TCHAR           m_szHelpDir[256];   //Object's help directory
        IDispatch      *m_pIDispatch;       //Object in use

        //CHAPTER16MOD
        BOOL                 m_fReadOnly;   //RequestEdit control
        IPropertyNotifySink *m_pSink;       //Our sink
        IConnectionPoint    *m_pIConnPt;    //Object's connection point
        DWORD                m_dwConn;      //Sink connection
        //End CHAPTER16MOD

    public:
        CApp(HINSTANCE, HINSTANCE, UINT);
        ~CApp(void);

        BOOL    Init(void);
        HRESULT NameToID(OLECHAR *, DISPID *);
        HRESULT Invoke(DISPID, WORD, DISPPARAMS *, VARIANT *
                    , EXCEPINFO *, UINT *);
        void    Message(LPTSTR);
        UINT    Message(LPTSTR, UINT);

        //CHAPTER16MOD
        void    ShowProperties(void);
        //End CHAPTER16MOD
    };


typedef CApp *PCApp;

#define CBWNDEXTRA              sizeof(PCApp)
#define AUTOCLI2WL_STRUCTURE    0


//CHAPTER16MOD

class CPropertyNotifySink : public IPropertyNotifySink
    {
    protected:
        ULONG           m_cRef;      //Reference count
        PCApp           m_pApp;      //Backpointer to the app

    public:
        CPropertyNotifySink(PCApp);
        ~CPropertyNotifySink(void);

        //IPropertyNotifySink interface members
        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP OnChanged(DISPID);
        STDMETHODIMP OnRequestEdit(DISPID);
    };


//End CHAPTER16MOD


#endif //_AUTOCLI2_H_
