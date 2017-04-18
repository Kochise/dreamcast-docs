/*
 * REUSE.H
 * COM Reusability Demo, Chapter 2
 *
 * Definitions, classes, and prototypes
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _REUSE_H_
#define _REUSE_H_

#define CHAPTER2
#include <inole.h>

#ifndef RC_INVOKED
#include "interfac.h"
#endif

//Menu Resource ID and Commands
#define IDR_MENU                    1


#define IDM_CREATECONTAINMENT               100
#define IDM_CREATEAGGREGATION               101
#define IDM_ANIMALEAT                       102
#define IDM_ANIMALSLEEP                     103
#define IDM_ANIMALPROCREATE                 104
#define IDM_KOALACLIMBEUCALYPTUSTREES       105
#define IDM_KOALAPOUCHOPENSDOWN             106
#define IDM_KOALASLEEPFORHOURSAFTEREATING   107
#define IDM_RELEASE                         108
#define IDM_EXIT                            109


//Global creation functions
BOOL    CreateKoalaContainment(IUnknown **);
BOOL    CreateKoalaAggregation(IUnknown **);
HRESULT CreateAnimal(IUnknown *, REFIID, void **);


//REUSE.CPP
LRESULT APIENTRY ReuseWndProc(HWND, UINT, WPARAM, LPARAM);

class CApp
    {
    friend LRESULT APIENTRY ReuseWndProc(HWND, UINT, WPARAM, LPARAM);

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle
        IUnknown       *m_pIUnknown;        //Current object

    public:
        CApp(HINSTANCE, HINSTANCE, UINT);
        ~CApp(void);

        BOOL        Init(void);
        BOOL        GetInterface(REFIID, void **);
        void inline Message(LPTSTR);
    };


typedef CApp *PAPP;

#define CBWNDEXTRA          sizeof(PAPP)
#define REUSEWL_STRUCTURE   0


#endif //_REUSE_H_
