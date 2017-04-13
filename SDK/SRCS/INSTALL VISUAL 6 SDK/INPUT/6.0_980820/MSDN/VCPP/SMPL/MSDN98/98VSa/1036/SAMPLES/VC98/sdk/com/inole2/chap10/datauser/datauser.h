/*
 * DATAUSER.H
 * Data Object User Chapter 10
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _DATAUSER_H_
#define _DATAUSER_H_

#define INC_OLE2
#define CHAPTER10
#include <inole.h>

//Menu Resource ID and Commands
#define IDR_MENU                    1


#define IDM_OBJECTUSEDLL                100
#define IDM_OBJECTUSEEXE                101
#define IDM_OBJECTDATASIZESMALL         102
#define IDM_OBJECTDATASIZEMEDIUM        103
#define IDM_OBJECTDATASIZELARGE         104
#define IDM_OBJECTQUERYGETDATA          105
#define IDM_OBJECTGETDATATEXT           106
#define IDM_OBJECTGETDATABITMAP         107
#define IDM_OBJECTGETDATAMETAFILEPICT   108
#define IDM_OBJECTEXIT                  109

#define IDM_ADVISEMIN                   200
#define IDM_ADVISETEXT                  (IDM_ADVISEMIN+CF_TEXT)
#define IDM_ADVISEBITMAP                (IDM_ADVISEMIN+CF_BITMAP)
#define IDM_ADVISEMETAFILEPICT          (IDM_ADVISEMIN+CF_METAFILEPICT)
#define IDM_ADVISEGETDATA               300
#define IDM_ADVISEREPAINT               301


//DATAUSER.CPP
LRESULT APIENTRY DataUserWndProc(HWND, UINT, WPARAM, LPARAM);


class CAdviseSink;
typedef class CAdviseSink *PCAdviseSink;


/*
 * Application-defined classes and types.
 */

class CApp
    {
    friend LRESULT APIENTRY DataUserWndProc(HWND, UINT, WPARAM
        , LPARAM);

    friend class CAdviseSink;

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle
        BOOL            m_fEXE;             //For tracking menu

        PCAdviseSink    m_pIAdviseSink;

        DWORD           m_dwConn;           //Advise connection
        UINT            m_cfAdvise;         //Advise format
        BOOL            m_fGetData;         //GetData on data change?
        BOOL            m_fRepaint;         //Repaint on data change?

        LPDATAOBJECT    m_pIDataSmall;
        LPDATAOBJECT    m_pIDataMedium;
        LPDATAOBJECT    m_pIDataLarge;

        LPDATAOBJECT    m_pIDataObject;     //Current selection
        UINT            m_cf;
        STGMEDIUM       m_stm;              //Current rendering

        BOOL            m_fInitialized;     //Did CoInitialize work?

    public:
        CApp(HINSTANCE, HINSTANCE, UINT);
        ~CApp(void);
        BOOL Init(void);
        BOOL FReloadDataObjects(BOOL);
        void TryQueryGetData(LPFORMATETC, UINT, BOOL, UINT);
        void Paint(void);
    };


typedef CApp *PAPP;

#define CBWNDEXTRA               sizeof(PAPP)
#define DATAUSERWL_STRUCTURE     0


//This lives with the app to get OnDataChange notifications.

class CAdviseSink : public IAdviseSink
    {
    protected:
        ULONG               m_cRef;
        PAPP                m_pApp;

    public:
        CAdviseSink(PAPP);
        ~CAdviseSink(void);

        STDMETHODIMP QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //We only implement OnDataChange for now.
        STDMETHODIMP_(void)  OnDataChange(LPFORMATETC, LPSTGMEDIUM);
        STDMETHODIMP_(void)  OnViewChange(DWORD, LONG);
        STDMETHODIMP_(void)  OnRename(LPMONIKER);
        STDMETHODIMP_(void)  OnSave(void);
        STDMETHODIMP_(void)  OnClose(void);
    };

#endif //_DATAUSER_H_
