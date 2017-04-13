/*
 * ENUMRECT.H
 * C/C++ Enumerator Demonstrtion Chapter 2
 *
 * Definitions, classes, and prototypes
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _ENUMRECT_H_
#define _ENUMRECT_H_

#define CHAPTER2
#include <inole.h>
#ifndef WIN32
#include <malloc.h>
#endif
#include "ienum.h"  //Interface definitions


//Menu Resource ID and Commands
#define IDR_MENU                    1

#define IDM_ENUMCREATEC             100
#define IDM_ENUMCREATECPP           101
#define IDM_ENUMRELEASE             102
#define IDM_ENUMRUNTHROUGH          103
#define IDM_ENUMEVERYTHIRD          104
#define IDM_ENUMRESET               105
#define IDM_ENUMCLONE               106
#define IDM_ENUMEXIT                107


//Number of rects that objects with IEnumRECT support (for demo)
#define CRECTS      15


//Skip the C++ stuff when this file is included from ENUMC.C
#ifdef __cplusplus

//ENUMRECT.CPP
LRESULT APIENTRY EnumWndProc(HWND, UINT, WPARAM, LPARAM);

class CApp
    {
    friend LRESULT APIENTRY EnumWndProc(HWND, UINT, WPARAM, LPARAM);

    protected:
        HINSTANCE       m_hInst;            //WinMain parameters
        HINSTANCE       m_hInstPrev;
        UINT            m_nCmdShow;

        HWND            m_hWnd;             //Main window handle
        PENUMRECT       m_pIEnumRect;       //Enumerator object

    public:
        CApp(HINSTANCE, HINSTANCE, UINT);
        ~CApp(void);

        BOOL Init(void);
        void Message(LPTSTR);
    };


typedef CApp *PAPP;

#define CBWNDEXTRA          sizeof(PAPP)
#define ENUMWL_STRUCTURE    0


//ENUMCPP.CPP

/*
 * The class definition for an object that singly implements
 * IEnumRECT in C++.
 */
class CEnumRect : public IEnumRECT
    {
    private:
        DWORD           m_cRef;         //Reference count
        DWORD           m_iCur;         //Current enum position
        RECT            m_rgrc[CRECTS]; //RECTS we enumerate

    public:
        CEnumRect(void);
        ~CEnumRect(void);

        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IEnumRECT members
        STDMETHODIMP Next(ULONG, LPRECT, ULONG *);
        STDMETHODIMP Skip(ULONG);
        STDMETHODIMP Reset(void);
        STDMETHODIMP Clone(PENUMRECT *);
    };


typedef CEnumRect *PCEnumRect;


//Function that creates one of these objects
BOOL CreateRECTEnumeratorCPP(PENUMRECT *);


//End of __cplusplus

#else

//Start of non __cplusplus definitions

//ENUMC.C

/*
 * The structure definition for an object that singly implements
 * IEnumRECT in C.  We make a class by reusing the elements of
 * the IEnumRECT structure thereby inheriting from it, albeit
 * manually.
 */

typedef struct tagRECTENUMERATOR
    {
    IEnumRECTVtbl  *lpVtbl;
    DWORD           m_cRef;         //Reference count
    DWORD           m_iCur;         //Current enum position
    RECT            m_rgrc[CRECTS]; //RECTS we enumerate
    } RECTENUMERATOR, *PRECTENUMERATOR;


/*
 * In C we have to separately declare member functions with
 * globally unique names, so prefixing with the class name
 * should remove any conflicts.
 */

PRECTENUMERATOR RECTENUM_Constructor(void);
void            RECTENUM_Destructor(PRECTENUMERATOR);

STDMETHODIMP    RECTENUM_QueryInterface(PENUMRECT, REFIID, PPVOID);
STDMETHODIMP_(ULONG) RECTENUM_AddRef(PENUMRECT);
STDMETHODIMP_(ULONG) RECTENUM_Release(PENUMRECT);
STDMETHODIMP    RECTENUM_Next(PENUMRECT, DWORD, LPRECT, LPDWORD);
STDMETHODIMP    RECTENUM_Skip(PENUMRECT, DWORD);
STDMETHODIMP    RECTENUM_Reset(PENUMRECT);
STDMETHODIMP    RECTENUM_Clone(PENUMRECT, PENUMRECT *);


//End of __cplusplus conditions

#endif

#ifdef __cplusplus
extern "C"
    {
#endif
    //Function that creates one of these objects
    BOOL CreateRECTEnumeratorC(PENUMRECT *);
#ifdef __cplusplus
    }
#endif

#endif //_ENUMRECT_H_
