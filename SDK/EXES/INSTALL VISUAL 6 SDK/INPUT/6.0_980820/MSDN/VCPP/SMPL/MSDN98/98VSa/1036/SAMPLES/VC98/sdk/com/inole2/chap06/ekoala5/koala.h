/*
 * KOALA.H
 * Koala Object with Custom Marshaling, Chapter 6
 *
 * Classes that implement the CKoala object with a custom interface
 * to demonstrate local/remote transparency.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _KOALA_H_
#define _KOALA_H_

#define CHAPTER6
#include <inole.h>


/*
 * Marshaling packet data structure as used by our IMarshal.
 * This is duplicated in ..\koalaprx\koala.h.
 */
typedef struct
    {
    HWND        hWnd;       //Message window
    } KOALAMARSHAL, *PKOALAMARSHAL;

//Intertask messages, duplicated in ..\koalaprx\koala.h.
#define MSG_RELEASE             1000
#define MSG_EAT                 1001
#define MSG_SLEEP               1002
#define MSG_PROCREATE           1003
#define MSG_SLEEPAFTEREATING    1004



//KOALA.CPP

LRESULT APIENTRY ObjectWndProc(HWND, UINT, WPARAM, LPARAM);

class CKoala : public IMarshal
    {
    friend LRESULT APIENTRY KoalaWndProc(HWND, UINT, WPARAM, LPARAM);

    protected:
        ULONG           m_cRef;         //Object reference count
        PFNDESTROYED    m_pfnDestroy;   //To call on closure

        HWND            m_hWnd;         //For marshaling

        BOOL            m_fJustAte;
        short           m_cSleepAfterEat;

    public:
        CKoala(PFNDESTROYED);
        ~CKoala(void);

        BOOL    Init(HINSTANCE, HWND);
        DWORD   HandleCall(UINT, LPARAM);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetUnmarshalClass(REFIID, LPVOID, DWORD
            , LPVOID, DWORD, LPCLSID);
        STDMETHODIMP GetMarshalSizeMax(REFIID, LPVOID, DWORD
            , LPVOID, DWORD, LPDWORD);
        STDMETHODIMP MarshalInterface(LPSTREAM, REFIID, LPVOID
            , DWORD, LPVOID, DWORD);
        STDMETHODIMP UnmarshalInterface(LPSTREAM, REFIID, LPVOID *);
        STDMETHODIMP ReleaseMarshalData(LPSTREAM);
        STDMETHODIMP DisconnectObject(DWORD);
    };

typedef CKoala *PCKoala;


#define CBOBJECTWNDEXTRA        sizeof(PCKoala)
#define OBJECTWL_STRUCTURE      0


#endif //_KOALA_H_
