/*
 * KOALA.H
 * Koala Object for EXE Servers, Chapter 6
 *
 * Classes that implement an object with IExternalConnection.
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

//KOALA.CPP

//CHAPTER6MOD
class CImpIPersist;
typedef CImpIPersist *PCImpIPersist;

class CKoala : public IExternalConnection
//End CHAPTER6MOD
    {
    protected:
        ULONG           m_cRef;         //Object reference count
        LPUNKNOWN       m_pUnkOuter;    //Controlling unknown
        PFNDESTROYED    m_pfnDestroy;   //To call on closure

        //CHAPTER6MOD
        DWORD           m_cStrong;      //Strong lock count
        DWORD           m_cWeak;        //Weak lock count

        PCImpIPersist   m_pImpIPersist; //Another interface
        //End CHAPTER6MOD

    public:
        CKoala(LPUNKNOWN, PFNDESTROYED);
        ~CKoala(void);

        BOOL Init(void);

        //Non-delegating object IUnknown
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        //CHAPTER6MOD
        STDMETHODIMP_(DWORD) AddConnection(DWORD, DWORD);
        STDMETHODIMP_(DWORD) ReleaseConnection(DWORD, DWORD, BOOL);
        //End CHAPTER6MOD
    };

typedef CKoala *PCKoala;


//CHAPTER6MOD

class CImpIPersist : public IPersist
    {
    protected:
        ULONG           m_cRef;      //Interface reference count
        PCKoala         m_pObj;      //Back pointer to the object
        LPUNKNOWN       m_pUnkOuter; //For delegation

    public:
        CImpIPersist(PCKoala, LPUNKNOWN);
        ~CImpIPersist(void);

        STDMETHODIMP QueryInterface(REFIID, LPVOID *);
        STDMETHODIMP_(ULONG) AddRef(void);
        STDMETHODIMP_(ULONG) Release(void);

        STDMETHODIMP GetClassID(LPCLSID);
    };

//End CHAPTER6MOD

#endif //_KOALA_H_
