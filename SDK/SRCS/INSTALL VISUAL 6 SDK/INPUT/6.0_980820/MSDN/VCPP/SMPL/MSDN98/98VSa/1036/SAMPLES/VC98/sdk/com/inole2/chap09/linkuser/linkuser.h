/*
 * LINKUSER.H
 * Link User Chapter 9
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _LINKUSER_H_
#define _LINKUSER_H_

#define INC_OLE2
#define CHAPTER9
#include <inole.h>
#include <idescrip.h>

//Menu Resource ID and Commands
#define IDR_MENU                    1


#define IDM_LINKSHOWDESCRIPTION     100
#define IDM_LINKPARSEANDBIND        101
#define IDM_LINKEXIT                102


//LINKUSER.CPP
LRESULT APIENTRY LinkUserWndProc(HWND, UINT, WPARAM, LPARAM);


class CAdviseSink;
typedef class CAdviseSink *PCAdviseSink;


/*
 * Application-defined classes and types.
 */

#define CMONIKERS       3
#define ID_LISTOLINKS   1000


class CApp
    {
    friend LRESULT APIENTRY LinkUserWndProc(HWND, UINT, WPARAM
        , LPARAM);

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle
        BOOL            m_fInitialized;     //Did CoInitialize work?

        HWND            m_hWndList;         //Listbox display
        IMoniker       *m_rgpmk[CMONIKERS]; //Held monikers

    public:
        CApp(HINSTANCE, HINSTANCE, UINT);
        ~CApp(void);
        BOOL Init(void);

        BOOL CreateMonikers(void);
        BOOL ListInitialize(void);
        void ShowDescription(void);
        void ParseAndBind(void);
        void BindAndShow(IMoniker *, IBindCtx *);
    };


typedef CApp *PAPP;

#define CBWNDEXTRA               sizeof(PAPP)
#define LINKUSERWL_STRUCTURE     0


#endif //_LINKUSER_H_
