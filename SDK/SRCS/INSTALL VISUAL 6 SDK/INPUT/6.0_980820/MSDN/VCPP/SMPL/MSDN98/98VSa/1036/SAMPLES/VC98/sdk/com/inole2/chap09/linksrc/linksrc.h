/*
 * LINKSRC.H
 * Link Source Server Chapter 9
 *
 * Definitions, classes, and prototypes for an application that
 * serves file objects and support moniker binding.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _LINKSRC_H_
#define _LINKSRC_H_

#include "objects.h"

#define IDR_MENU            1

#define IDM_FILECREATEGOOP  100
#define IDM_FILEEXIT        101


//Name of streams in the source file that holds description text.
#define SZDESCRIPTION       OLETEXT("Description")



//LINKSRC.CPP
LRESULT APIENTRY LinkSrcWndProc(HWND, UINT, WPARAM, LPARAM);

class CApp
    {
    friend LRESULT APIENTRY LinkSrcWndProc(HWND, UINT, WPARAM, LPARAM);

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        LPSTR           m_pszCmdLine;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle

        BOOL            m_fEmbedding;       //-Embedding found?
        BOOL            m_fInitialized;     //Did CoInitialize work?
        LPCLASSFACTORY  m_pIClassFactory;   //Our class factory
        DWORD           m_dwRegCO;          //Registration key

    public:
        CApp(HINSTANCE, HINSTANCE, LPSTR, UINT);
        ~CApp(void);
        BOOL Init(void);

        void     CreateSampleFile(LPTSTR);
        HRESULT  CreateStore(IStorage *, LPTSTR, LPTSTR, UINT);
        HRESULT  WriteDescription(IStorage *, LPTSTR);
    };

typedef CApp *PAPP;

#define CBWNDEXTRA              sizeof(PAPP)
#define LINKSRCWL_STRUCTURE     0


void ObjectDestroyed(void);


//LINKSRC.CPP

class CFileObjectFactory : public IClassFactory
    {
    protected:
        ULONG                       m_cRef;

    public:
        CFileObjectFactory(void);
        ~CFileObjectFactory(void);

        //IUnknown members
        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP CreateInstance(LPUNKNOWN, REFIID, PPVOID);
        STDMETHODIMP LockServer(BOOL);
    };

typedef CFileObjectFactory *PCFileObjectFactory;

#endif //_LINKSRC_H_
