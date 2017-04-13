/*
 * MALLOC2.H
 * C++ Malloc Demonstration Chapter 2
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _MALLOC2_H_
#define _MALLOC2_H_

#include <inole.h>

//Menu Resource ID and Commands
#define IDR_MENU                1


#define IDM_COGETMALLOC         100
#define IDM_RELEASE             101
#define IDM_ALLOC               102
#define IDM_FREE                103
#define IDM_REALLOC             104
#define IDM_GETSIZE             105
#define IDM_DIDALLOC            106
#define IDM_HEAPMINIMIZE        107
#define IDM_EXIT                108



//MALLOC2.CPP
LRESULT APIENTRY MallocWndProc(HWND, UINT, WPARAM, LPARAM);

//How many allocations we'll perform
#define CALLOCS 10


class CApp
    {
    friend LRESULT APIENTRY MallocWndProc(HWND, UINT, WPARAM, LPARAM);

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle
        IMalloc        *m_pIMalloc;         //From CoGetMalloc

        BOOL            m_fAllocated;       //We have allocations?
        ULONG           m_rgcb[CALLOCS];    //Sizes to allocate
        LPVOID          m_rgpv[CALLOCS];    //Allocated pointers

    public:
        CApp(HINSTANCE, HINSTANCE, UINT);
        ~CApp(void);
        BOOL Init(void);

        void GetAllocator(void);
        BOOL HaveAllocator(void);
        BOOL DoAllocations(BOOL);
        BOOL HaveAllocations(void);
        void FreeAllocations(BOOL);

        void Message(LPTSTR);
    };

typedef CApp *PAPP;


#define CBWNDEXTRA              sizeof(PAPP)
#define MALLOCWL_STRUCTURE      0


#endif //_MALLOC2_H_
