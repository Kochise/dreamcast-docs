/*
 * OBJUSER2.H
 * Koala Client #2 Chapter 6
 *
 * Definitions and structures.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _OBJUSER2_H_
#define _OBJUSER2_H_

#define CHAPTER6
#define INC_OLEUI
#include <inole.h>

//Menu Resource ID and Commands
#define IDR_MENU                    1


#define IDM_OBJECTCREATE            100
#define IDM_OBJECTGETCLASSID        101
#define IDM_OBJECTRELEASE           102
#define IDM_OBJECTEXIT              103



//OBJUSER.CPP
LRESULT APIENTRY ObjectUserWndProc(HWND, UINT, WPARAM, LPARAM);

class CMessageFilter;
typedef CMessageFilter *PCMessageFilter;

class CApp
    {
    friend LRESULT APIENTRY ObjectUserWndProc(HWND, UINT, WPARAM
        , LPARAM);
    friend class CMessageFilter;

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle

        LPUNKNOWN       m_pIUnknown;        //IUnknown interface
        BOOL            m_fInitialized;     //Did CoInitialize work?

        PCMessageFilter m_pMsgFilter;       //Our message filter

    public:
        CApp(HINSTANCE, HINSTANCE, UINT);
        ~CApp(void);

        BOOL Init(void);
        void Message(LPTSTR);
    };

typedef CApp *PAPP;

#define CBWNDEXTRA              sizeof(PAPP)
#define OBJUSERWL_STRUCTURE     0


//Message Filter Object

class CMessageFilter : public IMessageFilter
    {
    protected:
        ULONG           m_cRef;      //Object reference count
        PAPP            m_pApp;
        HWND            m_hDlg;      //Dialog handle

    private:
        UINT    DisplayBusyDialog(HTASK, DWORD);

    public:
        CMessageFilter(PAPP);
        ~CMessageFilter(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP_(DWORD) HandleInComingCall(DWORD, HTASK
           #ifdef WIN32
            , DWORD, LPINTERFACEINFO);
           #else
            , DWORD, DWORD);
           #endif
        STDMETHODIMP_(DWORD) RetryRejectedCall(HTASK, DWORD, DWORD);
        STDMETHODIMP_(DWORD) MessagePending(HTASK, DWORD, DWORD);
    };



#endif //_OBJUSER2_H_
