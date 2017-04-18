/*
 * CONNECT.H
 * Connectable Object Sample, Chapter 4
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

#define CHAPTER4
#define INC_CONTROLS
#include <inole.h>

#ifndef RC_INVOKED
#include "interfac.h"
#include "object.h"
#endif

//Menu Resource ID and Commands
#define IDR_MENU                    1

#define IDM_OBJECTCREATE            100
#define IDM_OBJECTRELEASE           101
#define IDM_OBJECTSINK1CONNECT      102
#define IDM_OBJECTSINK1DISCONNECT   103
#define IDM_OBJECTSINK2CONNECT      104
#define IDM_OBJECTSINK2DISCONNECT   105
#define IDM_OBJECTEXIT              106

#define IDM_TRIGGERQUACK            200
#define IDM_TRIGGERFLAP             201
#define IDM_TRIGGERPADDLE           202



//CONNECT.CPP
LRESULT APIENTRY ConnectWndProc(HWND, UINT, WPARAM, LPARAM);

class CDuckEvents;
typedef CDuckEvents *PCDuckEvents;

//Identifiers for sinks, indices into m_rgpSink below
enum
    {
    SINK1=0,
    SINK2
    };


class CApp
    {
    friend LRESULT APIENTRY ConnectWndProc(HWND, UINT, WPARAM, LPARAM);

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle
        PCDuckEvents    m_rgpSink[2];       //Sinks to connect

        /*
         * We need to have a pointer to the full object in
         * this somewhat contrived example because we have to
         * tell it when to fire notifications.  Usually there
         * will be something else besides a menu as used in
         * this sample to trigger those firings.
         */
        PCConnObject    m_pObj;             //Source object

    protected:
        void              Connect(UINT);
        void              Disconnect(UINT);
        IConnectionPoint *GetConnectionPoint(void);

    public:
        CApp(HINSTANCE, HINSTANCE, UINT);
        ~CApp(void);
        BOOL        Init(void);
        void        Message(LPTSTR);
    };


typedef CApp *PAPP;

#define CBWNDEXTRA          sizeof(PAPP)
#define CONNECTWL_STRUCTURE 0


class CDuckEvents : public IDuckEvents
    {
    private:
        ULONG       m_cRef;     //Reference count
        PAPP        m_pApp;     //For calling Message
        UINT        m_uID;      //Sink identifier

    public:
        //Connection key, public for CApp's usage
        DWORD       m_dwCookie;

    public:
        CDuckEvents(PAPP, UINT);
        ~CDuckEvents(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);

        //IDuckEvents members
        STDMETHODIMP Quack(void);
        STDMETHODIMP Flap(void);
        STDMETHODIMP Paddle(void);
    };

#endif //_CONNECT_H_
