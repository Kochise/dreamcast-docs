/*
 * KOALAA.H
 *
 * Definition of the Koala object using Aggregation, Chapter 2
 * Included only from KOALAA.CPP.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _KOALAA_H_
#define _KOALAA_H_


class CImpIKoala_A;
typedef CImpIKoala_A *PCImpIKoala_A;

class CKoalaA : public IUnknown
    {
    friend CImpIKoala_A;

    private:
        DWORD           m_cRef;         //Object reference count

        PCImpIKoala_A   m_pImpIKoala;   //Interface implementation

        IUnknown       *m_pIUnknown;    //From Animal
        IAnimal        *m_pIAnimal;     //From Animal, released

    public:
        CKoalaA(void);
        ~CKoalaA(void);

        BOOL Init(void);

        //IUnknown members, non-delegating
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);
    };


typedef CKoalaA *PCKoalaA;


class CImpIKoala_A : public IKoala
    {
    private:
        DWORD       m_cRef;         //For debugging
        PCKoalaA    m_pObj;         //Back pointer

    public:
        CImpIKoala_A(PCKoalaA);
        ~CImpIKoala_A(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);

        //IKoala members
        STDMETHODIMP ClimbEucalyptusTrees(void);
        STDMETHODIMP PouchOpensDown(void);
        STDMETHODIMP SleepForHoursAfterEating(void);
    };


#endif _KOALAA_H_
