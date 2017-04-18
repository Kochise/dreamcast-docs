/*
 * OBJUSER3.H
 * Koala Client #3 Chapter 6
 *
 * Definitions and structures.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _OBJUSER3_H_
#define _OBJUSER3_H_

#define CHAPTER6
#include <inole.h>
#ifdef WIN32
#include <ianimal.h>
#include <ikoala.h>
#else
//Non-MIDL generated versions
#include <ianim16.h>
#include <ikoala16.h>
#endif

//Menu Resource ID and Commands
#define IDR_MENU                    1


#define IDM_OBJECTCREATE            100
#define IDM_OBJECTRELEASE           101
#define IDM_ANIMALEAT               102
#define IDM_ANIMALSLEEP             103
#define IDM_ANIMALPROCREATE         104
#define IDM_ANIMALWHATKIND          105
#define IDM_KOALACLIMB              106
#define IDM_KOALAPOUCH              107
#define IDM_KOALASLEEP              108
#define IDM_OBJECTEXIT              109



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


#endif //_OBJUSER3_H_
