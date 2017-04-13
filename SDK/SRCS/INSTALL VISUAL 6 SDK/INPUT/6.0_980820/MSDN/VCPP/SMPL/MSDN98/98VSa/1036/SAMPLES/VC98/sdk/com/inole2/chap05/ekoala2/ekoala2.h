/*
 * EKOALA2.H
 * Koala Object EXE Self-Registering Server Chapter 5
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


#ifndef _EKOALA2_H_
#define _EKOALA2_H_


//Get the object definitions
#include "koala.h"


//EKOALA2.CPP
LRESULT APIENTRY KoalaWndProc(HWND, UINT, WPARAM, LPARAM);

class CApp
    {
    friend LRESULT APIENTRY KoalaWndProc(HWND, UINT, WPARAM, LPARAM);

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        LPSTR           m_pszCmdLine;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle

        BOOL            m_fInitialized;     //Did CoInitialize work?
        LPCLASSFACTORY  m_pIClassFactory;   //Our class factory
        DWORD           m_dwRegCO;          //Registration key

    private:
        BOOL SetKeyAndValue(LPTSTR, LPTSTR, LPTSTR);

    public:
        CApp(HINSTANCE, HINSTANCE, LPSTR, UINT);
        ~CApp(void);
        BOOL Init(void);
        void RegisterServer(void);
        void UnregisterServer(void);
    };

typedef CApp *PAPP;

#define CBWNDEXTRA              sizeof(PAPP)
#define KOALAWL_STRUCTURE       0


void ObjectDestroyed(void);


//This class factory object creates Koala objects.

class CKoalaClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;

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

#endif //_EKOALA2_H_
