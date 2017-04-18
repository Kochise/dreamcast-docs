/*
 * OBJUSER.H
 * Koala Object User/Client Chapter 5
 *
 * Definitions and structures.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _OBJUSER_H_
#define _OBJUSER_H_

#define CHAPTER5
#include <inole.h>

//Menu Resource ID and Commands
#define IDR_MENU                    1


#define IDM_OBJECTUSEDLL            100
#define IDM_OBJECTUSEEXE            101
#define IDM_OBJECTCREATECOGCO       102
#define IDM_OBJECTCREATECOCI        103
#define IDM_OBJECTADDREF            104
#define IDM_OBJECTRELEASE           105
#define IDM_OBJECTEXIT              106



//OBJUSER.CPP
LRESULT APIENTRY ObjectUserWndProc(HWND, UINT, WPARAM, LPARAM);

class CApp
    {
    friend LRESULT APIENTRY ObjectUserWndProc(HWND, UINT, WPARAM
        , LPARAM);

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle
        BOOL            m_fEXE;             //Menu selection

        ULONG           m_cRefOurs;         //Our use of the object
        LPUNKNOWN       m_pIUnknown;        //IUnknown interface
        BOOL            m_fInitialized;     //Did CoInitialize work?

    public:
        CApp(HINSTANCE, HINSTANCE, UINT);
        ~CApp(void);

        BOOL Init(void);
        void Message(LPTSTR);
    };


typedef CApp *PAPP;

#define CBWNDEXTRA              sizeof(PAPP)
#define OBJUSERWL_STRUCTURE     0


#endif //_OBJUSER_H_
