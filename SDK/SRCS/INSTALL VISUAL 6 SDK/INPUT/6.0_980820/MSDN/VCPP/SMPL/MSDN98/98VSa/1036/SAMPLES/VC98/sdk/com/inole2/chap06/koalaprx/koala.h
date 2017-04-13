/*
 * KOALA.H
 * Koala Custom Marshaling Proxy Chapter 6
 *
 * Classes that implement the CKoala object exposed from this
 * proxy server that communicates with a local Koala through
 * custom marshaling.
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
#ifdef WIN32
#include <ianimal.h>
#include <ikoala.h>
#else
//Non-MIDL generated versions
#include <ianim16.h>
#include <ikoala16.h>
#endif



/*
 * Marshaling packet data structure as used by our IMarshal.
 * This is duplicated in ..\ekoala5\koala.h.
 */
typedef struct
    {
    HWND        hWnd;       //Message window
    } KOALAMARSHAL, *PKOALAMARSHAL;

//Intertask messages, duplicated in ..\ekoala5\koala.h.
#define MSG_RELEASE             1000
#define MSG_EAT                 1001
#define MSG_SLEEP               1002
#define MSG_PROCREATE           1003
#define MSG_SLEEPAFTEREATING    1004


//KOALA.CPP
class CImpIAnimal;
typedef CImpIAnimal *PCImpIAnimal;

class CImpIKoala;
typedef CImpIKoala *PCImpIKoala;

class CImpIMarshal;
typedef CImpIMarshal *PCImpIMarshal;


class CKoala : public IUnknown
    {
    friend class CImpIAnimal;
    friend class CImpIKoala;
    friend class CImpIMarshal;

    protected:
        ULONG           m_cRef;         //Object reference count
        LPUNKNOWN       m_pUnkOuter;    //Controlling unknown

        PFNDESTROYED    m_pfnDestroy;   //To call on closure

        PCImpIAnimal    m_pImpIAnimal;  //Our interfaces
        PCImpIKoala     m_pImpIKoala;
        PCImpIMarshal   m_pImpIMarshal;

        BOOL            m_fJustAte;
        short           m_cSleepAfterEat;

        HWND            m_hWndLocal;    //Local object

    public:
        CKoala(LPUNKNOWN, PFNDESTROYED);
        ~CKoala(void);

        BOOL    Init(void);
        DWORD   CallLocal(UINT, LPARAM, BOOL);

        //Non-delegating object IUnknown
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);
    };

typedef CKoala *PCKoala;


//IAnimal interface implementation

class CImpIAnimal : public IAnimal
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        PCKoala         m_pObj;      //Back pointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIAnimal(PCKoala, LPUNKNOWN);
        ~CImpIAnimal(void);

        //IUnknown members
        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IAnimal members
        STDMETHODIMP Eat(LPTSTR, LPTSTR, short);
        STDMETHODIMP Sleep(short *);
        STDMETHODIMP Procreate(short *);
        STDMETHODIMP WhatKindOfAnimal(IID *);
    };


//IKoala interface implementation

class CImpIKoala : public IKoala
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        PCKoala         m_pObj;      //Back pointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIKoala(PCKoala, LPUNKNOWN);
        ~CImpIKoala(void);

        //IUnknown members
        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //IKoala members
        STDMETHODIMP ClimbEucalyptusTree(short);
        STDMETHODIMP PouchOpensDown(void);
        STDMETHODIMP SleepAfterEating(short);
    };


class CImpIMarshal : public IMarshal
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        PCKoala         m_pObj;      //Back pointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIMarshal(PCKoala, LPUNKNOWN);
        ~CImpIMarshal(void);

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

#endif //_KOALA_H_
