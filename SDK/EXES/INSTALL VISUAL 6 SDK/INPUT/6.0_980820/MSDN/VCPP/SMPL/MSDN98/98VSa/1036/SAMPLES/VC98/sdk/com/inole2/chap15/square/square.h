/*
 * SQUARE.H
 * Square Automation Object Chapter 15
 *
 * Definitions, classes, and prototypes for an EXE that
 * provides Square objects to automation controllers
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _SQUARE_H_
#define _SQUARE_H_

//Get the object definitions
#define INC_AUTOMATION
#define CHAPTER15
#define GUIDS_FROM_TYPELIB
#include <inole.h>
#include <math.h>

#include "isquare.h"

LRESULT APIENTRY MainWndProc(HWND, UINT, WPARAM, LPARAM);

class CApp
    {
    friend LRESULT APIENTRY MainWndProc(HWND, UINT, WPARAM, LPARAM);

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        LPSTR           m_pszCmdLine;
        UINT            m_nCmdShow;

        BOOL            m_fInitialized;     //Did CoInitialize work?
        LPCLASSFACTORY  m_pIClassFactory;   //Our class factory
        DWORD           m_dwRegCO;          //Registration key

    public:
        CApp(HINSTANCE, HINSTANCE, LPSTR, UINT);
        ~CApp(void);
        BOOL Init(void);
    };

typedef CApp *PCApp;


void ObjectDestroyed(void);


class CSquareClassFactory : public IClassFactory
    {
    protected:
        ULONG           m_cRef;
        HWND            m_hWnd;         //Main window (hidden)
        HINSTANCE       m_hInst;        //Module instance

    public:
        CSquareClassFactory(HWND, HINSTANCE);
        ~CSquareClassFactory(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IClassFactory members
        STDMETHODIMP  CreateInstance(LPUNKNOWN, REFIID, PPVOID);
        STDMETHODIMP  LockServer(BOOL);
    };

typedef CSquareClassFactory *PCSquareClassFactory;


//Information for the window in which we draw
LRESULT APIENTRY SquareWndProc(HWND, UINT, WPARAM, LPARAM);

#define SZCLASSSQUARE       TEXT("SquareWindow")


class CSquare : public ISphereSquare
    {
    friend LRESULT APIENTRY SquareWndProc(HWND, UINT, WPARAM
        , LPARAM);

    protected:
        ULONG           m_cRef;         //Object reference count
        HWND            m_hWnd;         //Drawing window.

        ITypeInfo      *m_pITypeInfo;   //Loaded
        IUnknown       *m_pIUnkDisp;    //From CreateStdDispatch

        //Plotting variables
        double          m_cRadius;      //Edge length
        double          m_dTheta;       //Angle
        double          m_dDeclin;      //Declination

        int             m_xOrg, m_yOrg; //Origin point
        int             m_cx, m_cy;     //Window size
        int             m_xPos, m_yPos; //Window position

        COLORREF        m_crLinePos;    //Positive line color
        HPEN            m_hPenPos;      //Positive line pen

        COLORREF        m_crLineNeg;    //Negative line color
        HPEN            m_hPenNeg;      //Negative line pen

        COLORREF        m_crBack;       //Background color

    public:
        CSquare(void);
        ~CSquare(void);

        BOOL        Init(HWND, HINSTANCE);
        void        CreatePens(BOOL, BOOL);
        void        Draw(HDC);

        //IUnknown Members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //ISphereSquare members
        STDMETHODIMP_(double) get_Radius(void);
        STDMETHODIMP_(void) put_Radius(double);
        STDMETHODIMP_(double) get_Theta(void);
        STDMETHODIMP_(void) put_Theta(double);
        STDMETHODIMP_(double) get_Declination(void);
        STDMETHODIMP_(void) put_Declination(double);
        STDMETHODIMP_(long) get_BackColor(void);
        STDMETHODIMP_(void) put_BackColor(long);
        STDMETHODIMP_(long) get_LineColorPositive(void);
        STDMETHODIMP_(void) put_LineColorPositive(long);
        STDMETHODIMP_(long) get_LineColorNegative(void);
        STDMETHODIMP_(void) put_LineColorNegative(long);
        STDMETHODIMP_(void) Draw(void);
        STDMETHODIMP_(void) SetCenterPoint(int, int);
        STDMETHODIMP_(void) ShowWindow(int);
        STDMETHODIMP_(void) SetWindowPosition(int, int);
        STDMETHODIMP_(void) SetWindowSize(int, int);
    };

typedef CSquare *PCSquare;


#define CBSQUAREWNDEXTRA        sizeof(PCSquare)
#define SQWL_STRUCTURE          0

//Handy constant
#define PI 3.1415926535

#endif //_SQUARE_H_
