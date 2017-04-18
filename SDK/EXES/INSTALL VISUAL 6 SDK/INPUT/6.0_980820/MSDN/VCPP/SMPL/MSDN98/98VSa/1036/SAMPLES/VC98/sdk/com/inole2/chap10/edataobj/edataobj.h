/*
 * EDATAOBJ.H
 * Data Object EXE Chapter 10
 *
 * Definitions, classes, and prototypes for an application that
 * provides DataObject objects to any other object user.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _EDATAOBJ_H_
#define _EDATAOBJ_H_

#include "dataobj.h"


//EDATAOBJ.CPP
LRESULT APIENTRY DataObjectWndProc(HWND, UINT, WPARAM, LPARAM);


class CApp
    {
    friend LRESULT APIENTRY DataObjectWndProc(HWND, UINT
        , WPARAM, LPARAM);

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        LPSTR           m_pszCmdLine;

        HWND            m_hWnd;             //Main window handle
        BOOL            m_fInitialized;     //Did CoInitialize work?

        //We have multiple classes, one for each data size.
        DWORD           m_rgdwRegCO[DOSIZE_CSIZES];
        LPCLASSFACTORY  m_rgpIClassFactory[DOSIZE_CSIZES];

    public:
        CApp(HINSTANCE, HINSTANCE, LPSTR, UINT);
        ~CApp(void);
        BOOL Init(void);
    };


typedef CApp *PAPP;


void ObjectDestroyed(void);


//This class factory object creates Data Objects.

class CDataObjectClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;
        UINT            m_iSize;        //Data size for this class

    public:
        CDataObjectClassFactory(UINT);
        ~CDataObjectClassFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP         CreateInstance(LPUNKNOWN, REFIID
                                 , PPVOID);
        STDMETHODIMP         LockServer(BOOL);
    };

typedef CDataObjectClassFactory *PCDataObjectClassFactory;

#endif //_EDATAOBJ_H_
