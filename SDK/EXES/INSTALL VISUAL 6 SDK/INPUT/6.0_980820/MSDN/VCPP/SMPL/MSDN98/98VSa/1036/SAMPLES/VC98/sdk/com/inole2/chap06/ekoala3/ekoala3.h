/*
 * EKOALA3.H
 * Koala Object EXE Server Chapter 6
 *
 * Definitions, classes, and prototypes for an application that
 * provides Koala objects to any other object user.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _EKOALA3_H_
#define _EKOALA3_H_


//Get the object definitions
#include "koala.h"

//CHAPTER6MOD
#define IDR_MENU            1
#define IDM_CALLBLOCK       100
#define IDM_CALLDELAY       101
//End CHAPTER6MOD


//EKOALA3.CPP
LRESULT APIENTRY KoalaWndProc(HWND, UINT, WPARAM, LPARAM);

//CHAPTER6MOD
class CMessageFilter;
typedef CMessageFilter *PCMessageFilter;
//End CHAPTER6MOD

class CApp
    {
    friend LRESULT APIENTRY KoalaWndProc(HWND, UINT, WPARAM, LPARAM);
    friend class CMessageFilter;

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        LPSTR           m_pszCmdLine;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle

        BOOL            m_fInitialized;     //Did CoInitialize work?
        LPCLASSFACTORY  m_pIClassFactory;   //Our class factory
        DWORD           m_dwRegCO;          //Registration key

        //CHAPTER6MOD
        PCMessageFilter m_pMsgFilter;   //Message filter object
        BOOL            m_fBlock;
        BOOL            m_fDelay;
        //End CHAPTER6MOD

    public:
        CApp(HINSTANCE, HINSTANCE, LPSTR, UINT);
        ~CApp(void);
        BOOL Init(void);
    };

typedef CApp *PAPP;

#define CBWNDEXTRA              sizeof(PAPP)
#define KOALAWL_STRUCTURE       0


void ObjectDestroyed(void);

//CHAPTER6MOD
//MSGFILT.CPP
//Message Filter Object

class CMessageFilter : public IMessageFilter
    {
    protected:
        ULONG           m_cRef;      //Object reference count
        PAPP            m_pApp;

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
//End CHAPTER6MOD


//This class factory object creates Koala objects.

//CHAPTER6MOD
//EKOALA3.CPP
class CImpIExternalConnection;
typedef class CImpIExternalConnection *PCImpIExternalConnection;
//End CHAPTER6MOD

class CKoalaClassFactory : public IClassFactory
    {
    //CHAPTER6MOD
    friend class CImpIExternalConnection;
    //End CHAPTER6MOD

    protected:
        ULONG                       m_cRef;
        //CHAPTER6MOD
        PCImpIExternalConnection    m_pImpIExtConn;
        //End CHAPTER6MOD

    public:
        CKoalaClassFactory(void);
        ~CKoalaClassFactory(void);

        //IUnknown members
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, PPVOID);
        STDMETHODIMP LockServer(BOOL);
    };

typedef CKoalaClassFactory *PCKoalaClassFactory;


//CHAPTER6MOD
class CImpIExternalConnection : public IExternalConnection
    {
    protected:
        ULONG               m_cRef;      //Interface reference count
        PCKoalaClassFactory m_pObj;      //Back pointer to the object
        LPUNKNOWN           m_pUnkOuter; //For delegation

        DWORD               m_cStrong;
        DWORD               m_cWeak;

    public:
        CImpIExternalConnection(PCKoalaClassFactory, LPUNKNOWN);
        ~CImpIExternalConnection(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP_(DWORD) AddConnection(DWORD, DWORD);
        STDMETHODIMP_(DWORD) ReleaseConnection(DWORD, DWORD, BOOL);
    };

//End CHAPTER6MOD

#endif //_EKOALA3_H_
