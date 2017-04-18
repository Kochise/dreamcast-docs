/*
 * ANIMAL.CPP
 *
 * Aggregatable Animal Object Implementation, Chapter 2
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */

#include <windows.h>
#include "reuse.h"
#include "animal.h"


/*
 * CreateAnimal
 *
 * Purpose:
 *  Creates an instance of Animal returning a requested interface
 *  pointer.
 *
 * Parameters:
 *  pUnkOuter       IUnknown * holding the outer unknown.  Can
 *                  be NULL.
 *  riid            REFIID interface requested by the caller.
 *  ppv             void ** in which to return the interface pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, CLASS_E_NOAGREGATION if
 *                  IUnknown is not requested with non-NULL pUnkOuter,
 *                  or other error as appropriate.
 */

HRESULT CreateAnimal(IUnknown *pUnkOuter, REFIID riid, void **ppv)
    {
    CAnimal    *pObj;

    //If aggregation is on, check riid==IID_IUnknown
    if (NULL!=pUnkOuter && riid!=IID_IUnknown)
        return ResultFromScode(CLASS_E_NOAGGREGATION);

    pObj=new CAnimal(pUnkOuter);

    if (NULL==pObj)
        return E_OUTOFMEMORY;

    if (!pObj->Init())
        return E_FAIL;

    return pObj->QueryInterface(riid, (PPVOID)ppv);
    }





/*
 * CAnimal::CAnimal
 * CAnimal::~CAnimal
 *
 * Constructor Parameters:
 *  pUnkOuter       IUnknown * holding the outer unknown.  Can
 *                  be NULL.
 */

CAnimal::CAnimal(IUnknown *pUnkOuter)
    {
    m_cRef=0;
    m_pImpIAnimal=NULL;

    //No AddRef necessary if non-NULL as we're nested.
    m_pUnkOuter=pUnkOuter;
    return;
    }

CAnimal::~CAnimal(void)
    {
    DeleteInterfaceImp(m_pImpIAnimal);
    return;
    }



/*
 * CAnimal::Init
 *
 * Purpose:
 *  Instantiates the interface implementations for this object.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if initialization succeeds, FALSE otherwise.
 */

BOOL CAnimal::Init(void)
    {
    IUnknown   *pUnkOuter=m_pUnkOuter;

    //Set up the right unknown for delegation
    if (NULL==pUnkOuter)
        pUnkOuter=this;

    m_pImpIAnimal=new CImpIAnimal_A(this, pUnkOuter);

    if (NULL==m_pImpIAnimal)
        return FALSE;

    return TRUE;
    }






/*
 * CAnimal::QueryInterface
 * CAnimal::AddRef
 * CAnimal::Release
 *
 * Purpose:
 *  Non-delegating IUnknown implementation.
 */

STDMETHODIMP CAnimal::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid)
        *ppv=this;

    if (IID_IAnimal==riid)
        *ppv=m_pImpIAnimal;

    if (NULL==*ppv)
        return ResultFromScode(E_NOINTERFACE);

    ((LPUNKNOWN)*ppv)->AddRef();
    return NOERROR;
    }


DWORD CAnimal::AddRef(void)
    {
    return ++m_cRef;
    }

DWORD CAnimal::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }




//CImpIAnimal_A interface implementation


/*
 * CImpIAnimal_A::CImpIAnimal_A
 * CImpIAnimal_A::~CImpIAnimal_A
 *
 * Constructor Parameters:
 *  pObj            PCAnimal to the outer object
 *  pUnkOuter       IUnknown * to which to delegate.
 */

CImpIAnimal_A::CImpIAnimal_A(PCAnimal pObj, IUnknown *pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;  //No AddRef, we're nested
    return;
    }

CImpIAnimal_A::~CImpIAnimal_A(void)
    {
    return;
    }



/*
 * CImpIAnimal_A::QueryInterface
 * CImpIAnimal_A::AddRef
 * CImpIAnimal_A::Release
 *
 * IUnknown members that delegate to m_pUnkOuter, whatever it is.
 */

STDMETHODIMP CImpIAnimal_A::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

DWORD CImpIAnimal_A::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

DWORD CImpIAnimal_A::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIAnimal_A::Eat
 * CImpIAnimal_A::Sleep
 * CImpIAnimal_A::Procreate
 *
 * Purpose:
 *  Empty sample functions, no parameters, return NOERROR
 */

STDMETHODIMP CImpIAnimal_A::Eat(void)
    {
    ODS("Animal's IAnimal::Eat called");
    return NOERROR;
    }

STDMETHODIMP CImpIAnimal_A::Sleep(void)
    {
    ODS("Animal's IAnimal::Sleep called");
    return NOERROR;
    }

STDMETHODIMP CImpIAnimal_A::Procreate(void)
    {
    ODS("Animal's IAnimal::Procreate called");
    return NOERROR;
    }
