/*
 * QUERY.H
 * QueryInterface and Multiple Interface Sample, Chapter 2
 *
 * Definitions, classes, and prototypes
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _QUERY_H_
#define _QUERY_H_

#define CHAPTER2
#include <inole.h>

#ifndef RC_INVOKED
#include "interfac.h"
#include "object1.h"
#include "object2.h"
#include "object3.h"
#endif

//Menu Resource ID and Commands
#define IDR_MENU                    1

#define IDM_OBJECTCREATE1           100
#define IDM_OBJECTCREATE2           101
#define IDM_OBJECTCREATE3           102
#define IDM_OBJECTRELEASE           103
#define IDM_OBJECTGETMESSAGE        104
#define IDM_OBJECTGETSTRING         105
#define IDM_OBJECTEXIT              106


//QUERY.CPP
LRESULT APIENTRY QueryWndProc(HWND, UINT, WPARAM, LPARAM);

class CApp
    {
    friend LRESULT APIENTRY QueryWndProc(HWND, UINT, WPARAM, LPARAM);

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
        void        Message(LPTSTR);
    };


typedef CApp *PAPP;

#define CBWNDEXTRA          sizeof(PAPP)
#define QUERYWL_STRUCTURE   0


#endif //_QUERY_H_
