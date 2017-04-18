/*
 * KOALAC.CPP
 *
 * Koala Object Reusing Animal via Containment, Chapter 2
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */

#include <windows.h>
#include "reuse.h"
#include "koalac.h"


/*
 * CreateKoalaContainment
 *
 * Purpose:
 *  Creates an instance of KoalaC returning an IUnknown
 *  interface.
 *
 * Parameters:
 *  ppUnk           IUnknown ** in which to return the pointer.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CreateKoalaContainment(IUnknown **ppUnk)
    {
    CKoalaC    *pObj;
    HRESULT     hr;

    pObj=new CKoalaC();

    if (NULL==pObj)
        return FALSE;

    if (!pObj->Init())
        return FALSE;

    hr=pObj->QueryInterface(IID_IUnknown, (PPVOID)ppUnk);
    return SUCCEEDED(hr);
    }





/*
 * CKoalaC::CKoalaC
 * CKoalaC::~CKoalaC
 *
 * Constructor Parameters:
 *  None
 */

CKoalaC::CKoalaC(void)
    {
    m_cRef=0;
    m_pImpIAnimal=NULL;
    m_pImpIKoala=NULL;

    m_pIAnimal=NULL;
    return;
    }

CKoalaC::~CKoalaC(void)
    {
    ReleaseInterface(m_pIAnimal);

    DeleteInterfaceImp(m_pImpIKoala);
    DeleteInterfaceImp(m_pImpIAnimal);
    return;
    }



/*
 * CKoalaC::Init
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

BOOL CKoalaC::Init(void)
    {
    HRESULT     hr;

    //Create our interface
    m_pImpIAnimal=new CImpIAnimal_K(this);

    if (NULL==m_pImpIAnimal)
        return FALSE;

    m_pImpIKoala=new CImpIKoala_C(this);

    if (NULL==m_pImpIKoala)
        return FALSE;

    /*
     * Create an instance of the Animal object and save an
     * IAnimal pointer.  We use Animal's global API function
     * for this.
     */
    hr=CreateAnimal(NULL, IID_IAnimal, (void **)&m_pIAnimal);

    if (FAILED(hr))
        return FALSE;

    return TRUE;
    }






/*
 * CKoalaC::QueryInterface
 * CKoalaC::AddRef
 * CKoalaC::Release
 *
 * Purpose:
 *  KoalaC's IUnknown implementation.
 */

STDMETHODIMP CKoalaC::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid)
        *ppv=this;

    if (IID_IAnimal==riid)
        *ppv=m_pImpIAnimal;

    if (IID_IKoala==riid)
        *ppv=m_pImpIKoala;

    if (NULL==*ppv)
        return ResultFromScode(E_NOINTERFACE);

    ((LPUNKNOWN)*ppv)->AddRef();
    return NOERROR;
    }


DWORD CKoalaC::AddRef(void)
    {
    return ++m_cRef;
    }

DWORD CKoalaC::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }




//CImpIAnimal_K interface implementation


/*
 * CImpIAnimal_K::CImpIAnimal_K
 * CImpIAnimal_K::~CImpIAnimal_K
 *
 * Constructor Parameters:
 *  pObj            PCKoalaC to the outer object
 */

CImpIAnimal_K::CImpIAnimal_K(PCKoalaC pObj)
    {
    m_cRef=0;
    m_pObj=pObj;
    return;
    }

CImpIAnimal_K::~CImpIAnimal_K(void)
    {
    return;
    }



/*
 * CImpIAnimal_K::QueryInterface
 * CImpIAnimal_K::AddRef
 * CImpIAnimal_K::Release
 *
 * IUnknown members that delegate to KoalaC
 */

STDMETHODIMP CImpIAnimal_K::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pObj->QueryInterface(riid, ppv);
    }

DWORD CImpIAnimal_K::AddRef(void)
    {
    ++m_cRef;
    return m_pObj->AddRef();
    }

DWORD CImpIAnimal_K::Release(void)
    {
    --m_cRef;
    return m_pObj->Release();
    }



/*
 * CImpIAnimal_K::Eat
 * CImpIAnimal_K::Sleep
 * CImpIAnimal_K::Procreate
 *
 * Purpose:
 *  Empty sample functions, no parameters, return NOERROR
 */

STDMETHODIMP CImpIAnimal_K::Eat(void)
    {
    ODS("KoalaC's IAnimal::Eat called");

    //Call contained object
    m_pObj->m_pIAnimal->Eat();
    return NOERROR;
    }

STDMETHODIMP CImpIAnimal_K::Sleep(void)
    {
    ODS("KoalaC's IAnimal::Sleep called");

    //Call contained object
    m_pObj->m_pIAnimal->Sleep();
    return NOERROR;
    }

STDMETHODIMP CImpIAnimal_K::Procreate(void)
    {
    ODS("KoalaC's IAnimal::Procreate called");

    //Call contained object
    m_pObj->m_pIAnimal->Procreate();
    return NOERROR;
    }




//CImpIKoala_C interface implementation


/*
 * CImpIKoala_C::CImpIKoala_C
 * CImpIKoala_C::~CImpIKoala_C
 *
 * Constructor Parameters:
 *  pObj            PCKoalaC to the outer object
 */

CImpIKoala_C::CImpIKoala_C(PCKoalaC pObj)
    {
    m_cRef=0;
    m_pObj=pObj;
    return;
    }

CImpIKoala_C::~CImpIKoala_C(void)
    {
    return;
    }



/*
 * CImpIKoala_C::QueryInterface
 * CImpIKoala_C::AddRef
 * CImpIKoala_C::Release
 *
 * IUnknown members that delegate to KoalaC
 */

STDMETHODIMP CImpIKoala_C::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pObj->QueryInterface(riid, ppv);
    }

DWORD CImpIKoala_C::AddRef(void)
    {
    ++m_cRef;
    return m_pObj->AddRef();
    }

DWORD CImpIKoala_C::Release(void)
    {
    --m_cRef;
    return m_pObj->Release();
    }



/*
 * CImpIKoala_C::ClimbEucalyptusTrees
 * CImpIKoala_C::PouchOpensDown
 * CImpIKoala_C::SleepForHoursAfterEating
 *
 * Purpose:
 *  Empty sample functions, no parameters, return NOERROR
 */

STDMETHODIMP CImpIKoala_C::ClimbEucalyptusTrees(void)
    {
    ODS("KoalaC's IKoala::ClimbEucalyptusTrees called");
    return NOERROR;
    }

STDMETHODIMP CImpIKoala_C::PouchOpensDown(void)
    {
    ODS("KoalaC's IKoala::PouchOpensDown called");
    return NOERROR;
    }

STDMETHODIMP CImpIKoala_C::SleepForHoursAfterEating(void)
    {
    ODS("KoalaC's IKoala::SleepForHoursAfterEating called");
    return NOERROR;
    }
