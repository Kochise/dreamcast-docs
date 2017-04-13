/*
 * KOALAC.H
 *
 * Definition of the Koala object using containment, Chapter 2
 * Included only from KOALAC.CPP.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _KOALAC_H_
#define _KOALAC_H_

class CImpIAnimal_K;
typedef CImpIAnimal_K *PCImpIAnimal_K;

class CImpIKoala_C;
typedef CImpIKoala_C *PCImpIKoala_C;

class CKoalaC : public IUnknown
    {
    friend CImpIAnimal_K;
    friend CImpIKoala_C;

    private:
        DWORD           m_cRef;         //Object reference count

        PCImpIAnimal_K  m_pImpIAnimal;  //Interface implementation
        PCImpIKoala_C   m_pImpIKoala;   //Interface implementation

        IAnimal        *m_pIAnimal;     //From Animal

    public:
        CKoalaC(void);
        ~CKoalaC(void);

        BOOL Init(void);

        //IUnknown members, non-delegating
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);
    };


typedef CKoalaC *PCKoalaC;


class CImpIAnimal_K : public IAnimal
    {
    private:
        DWORD       m_cRef;         //For debugging
        PCKoalaC    m_pObj;         //Back pointer

    public:
        CImpIAnimal_K(PCKoalaC);
        ~CImpIAnimal_K(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);

        //IAnimal members
        STDMETHODIMP Eat(void);
        STDMETHODIMP Sleep(void);
        STDMETHODIMP Procreate(void);
    };


class CImpIKoala_C : public IKoala
    {
    private:
        DWORD       m_cRef;         //For debugging
        PCKoalaC    m_pObj;         //Back pointer

    public:
        CImpIKoala_C(PCKoalaC);
        ~CImpIKoala_C(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);

        //IKoala members
        STDMETHODIMP ClimbEucalyptusTrees(void);
        STDMETHODIMP PouchOpensDown(void);
        STDMETHODIMP SleepForHoursAfterEating(void);
    };


#endif _KOALAC_H_
