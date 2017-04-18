/*
 * LICUSER.H
 * Licensed Koala Object User/Client Chapter 5
 *
 * Definitions and structures.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _LICUSER_H_
#define _LICUSER_H_

#define CHAPTER5
#define INC_CONTROLS
#include <inole.h>

//Menu Resource ID and Commands
#define IDR_MENU                    1


#define IDM_CFOBTAINCF              100
#define IDM_CFOBTAINCF2             101
#define IDM_CFRELEASE               102
#define IDM_CFREQUESTLICKEY         103
#define IDM_CLEARLICKEY             104
#define IDM_CFEXIT                  105

#define IDM_OBJECTCREATEINST        200
#define IDM_OBJECTCREATEINSTLIC     201


//LICUSER.CPP
LRESULT APIENTRY LicensedUserWndProc(HWND, UINT, WPARAM, LPARAM);

class CApp
    {
    friend LRESULT APIENTRY LicensedUserWndProc(HWND, UINT, WPARAM
        , LPARAM);

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle
        BOOL            m_fInitialized;     //Did CoInitialize work?

        BOOL            m_fLic;             //True for Lic factory
        IClassFactory  *m_pIClassFac;
        IClassFactory2 *m_pIClassFac2;

        BSTR            m_bstrKey;          //Licence key

    public:
        CApp(HINSTANCE, HINSTANCE, UINT);
        ~CApp(void);

        void ObtainClassFactory(BOOL);
        void ReleaseClassFactory(BOOL);
        void CreateObject(BOOL);

        BOOL Init(void);
        void Message(LPTSTR);
    };


typedef CApp *PAPP;

#define CBWNDEXTRA              sizeof(PAPP)
#define LICUSERWL_STRUCTURE     0


#endif //_LICUSER_H_
