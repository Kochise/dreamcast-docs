/*
 * AUTOCLI.H
 * Automation Client Chapter 15
 *
 * Definitions and structures.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */

#ifndef _AUTOCLI_H_
#define _AUTOCLI_H_

#define INC_AUTOMATION
#define CHAPTER14
#define CHAPTER15
#include <inole.h>
#include <shellapi.h>
#include <malloc.h>

//Menu Resource ID and Commands
#define IDR_MENU                    1

#define IDM_GETSOUND                0x0001
#define IDM_BEEP                    0x0002
#define IDM_EXIT                    0x0003

//These match MB_* identifiers for MessageBeep
#define IDM_SETSOUNDDEFAULT         0x0008
#define IDM_SETSOUNDHAND            0x0010
#define IDM_SETSOUNDQUESTION        0x0020
#define IDM_SETSOUNDEXCLAMATION     0x0030
#define IDM_SETSOUNDASTERISK        0x0040

#define IDM_SETSOUNDBOGUS           0x0555


//Stringtable IDs
#define CCHSTRINGMAX                80
#define IDS_MESSAGEEXCEPTION        0
#define IDS_MESSAGEEXCEPTIONSCODE   1
#define IDS_MESSAGEUNKNOWNEXCEPTION 2


//AUTOCLI.CPP
LRESULT APIENTRY AutoClientWndProc(HWND, UINT, WPARAM, LPARAM);
void HelpDirFromCLSID(CLSID, LPTSTR);

class CApp
    {
    friend LRESULT APIENTRY AutoClientWndProc(HWND, UINT, WPARAM
        , LPARAM);

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle
        BOOL            m_fInitialized;     //Did CoInitialize work?
        LCID            m_lcid;             //User locale
        TCHAR           m_szHelpDir[256];   //Object's help directory
        IDispatch      *m_pIDispatch;       //Interface we use

    public:
        CApp(HINSTANCE, HINSTANCE, UINT);
        ~CApp(void);

        BOOL    Init(void);
        HRESULT NameToID(OLECHAR *, DISPID *);
        HRESULT Invoke(DISPID, WORD, DISPPARAMS *, VARIANT *
                    , EXCEPINFO *, UINT *);
        void    Message(LPTSTR);
        UINT    Message(LPTSTR, UINT);
    };


typedef CApp *PCApp;

#define CBWNDEXTRA              sizeof(PCApp)
#define AUTOCLIWL_STRUCTURE     0


#endif //_AUTOCLI_H_
