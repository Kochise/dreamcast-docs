/*
 * KOALA.H
 * Koala Object with Custom Interface, Chapter 6
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
#include <ianimal.h>
#include <ikoala.h>

//KOALA.CPP

//CHAPTER6MOD
class CImpIAnimal;
typedef CImpIAnimal *PCImpIAnimal;

class CImpIKoala;
typedef CImpIKoala *PCImpIKoala;
//End CHAPTER6MOD

class CKoala : public IUnknown
    {
    //CHAPTER6MOD
    friend class CImpIAnimal;
    friend class CImpIKoala;
    //End CHAPTER6MOD

    protected:
        ULONG           m_cRef;         //Object reference count
        LPUNKNOWN       m_pUnkOuter;    //Controlling unknown

        PFNDESTROYED    m_pfnDestroy;   //To call on closure

        //CHAPTER6MOD
        PCImpIAnimal    m_pImpIAnimal;  //Our interfaces
        PCImpIKoala     m_pImpIKoala;

        BOOL            m_fJustAte;
        short           m_cSleepAfterEat;
        //CHAPTER6MOD

    public:
        CKoala(LPUNKNOWN, PFNDESTROYED);
        ~CKoala(void);

        BOOL Init(void);

        //Non-delegating object IUnknown
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);
    };

typedef CKoala *PCKoala;


//CHAPTER6MOD
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
//End CHAPTER6MOD

#endif //_KOALA_H_
