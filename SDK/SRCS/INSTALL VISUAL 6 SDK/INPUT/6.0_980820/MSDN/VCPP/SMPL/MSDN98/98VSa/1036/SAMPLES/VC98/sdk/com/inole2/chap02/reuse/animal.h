/*
 * ANIMAL.H
 *
 * Definition of the aggregatable CAnimal object.
 * Included only from ANIMAL.CPP.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _ANIMAL_H_
#define _ANIMAL_H_


class CImpIAnimal_A;
typedef CImpIAnimal_A *PCImpIAnimal_A;

class CAnimal : public IUnknown
    {
    friend CImpIAnimal_A;

    private:
        DWORD           m_cRef;         //Object reference count
        IUnknown       *m_pUnkOuter;    //Outer unknown, no AddRef

        PCImpIAnimal_A  m_pImpIAnimal;  //Interface implementation

    public:
        CAnimal(IUnknown *);
        ~CAnimal(void);

        BOOL Init(void);

        //IUnknown members, non-delegating
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);
    };


typedef CAnimal *PCAnimal;


class CImpIAnimal_A : public IAnimal
    {
    private:
        DWORD       m_cRef;         //For debugging
        PCAnimal    m_pObj;         //Back pointer
        IUnknown   *m_pUnkOuter;    //Outer unknown, for delegation

    public:
        CImpIAnimal_A(PCAnimal, IUnknown *);
        ~CImpIAnimal_A(void);

        //IUnknown members
        STDMETHODIMP         QueryInterface(REFIID, PPVOID);
        STDMETHODIMP_(DWORD) AddRef(void);
        STDMETHODIMP_(DWORD) Release(void);

        //IAnimal members
        STDMETHODIMP Eat(void);
        STDMETHODIMP Sleep(void);
        STDMETHODIMP Procreate(void);
    };


#endif _ANIMAL_H_
