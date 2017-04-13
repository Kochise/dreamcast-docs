/*
 * KOALAA.CPP
 *
 * Koala Object Reusing Animal via Aggregation, Chapter 2
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */

#include <windows.h>
#include "reuse.h"
#include "koalaa.h"


/*
 * CreateKoalaAggregation
 *
 * Purpose:
 *  Creates an instance of KoalaA returning an IUnknown
 *  interface.
 *
 * Parameters:
 *  ppUnk           IUnknown ** in which to return the pointer.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 */

BOOL CreateKoalaAggregation(IUnknown **ppUnk)
    {
    CKoalaA    *pObj;
    HRESULT     hr;

    pObj=new CKoalaA();

    if (NULL==pObj)
        return FALSE;

    if (!pObj->Init())
        return FALSE;

    hr=pObj->QueryInterface(IID_IUnknown, (PPVOID)ppUnk);
    return SUCCEEDED(hr);
    }





/*
 * CKoalaA::CKoalaA
 * CKoalaA::~CKoalaA
 *
 * Constructor Parameters:
 *  None
 */

CKoalaA::CKoalaA(void)
    {
    m_cRef=0;
    m_pImpIKoala=NULL;
    m_pIUnknown=NULL;
    m_pIAnimal=NULL;
    return;
    }

CKoalaA::~CKoalaA(void)
    {
    /*
     * Since this KoalaA is not aggregatable, we can use the
     * 32-bit rule under Win16 as well.
     */
    AddRef();
    ReleaseInterface(m_pIAnimal);

    ReleaseInterface(m_pIUnknown);
    DeleteInterfaceImp(m_pImpIKoala);
    return;
    }



/*
 * CKoalaA::Init
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

BOOL CKoalaA::Init(void)
    {
    HRESULT     hr;

    //Create our interface
    m_pImpIKoala=new CImpIKoala_A(this);

    if (NULL==m_pImpIKoala)
        return FALSE;

    /*
     * Create an instance of the Animal object, saving an
     * IUnknown but also saving a released IAnimal.  We use
     * Animal's global API function for this.
     */
    hr=CreateAnimal(this, IID_IUnknown, (void **)&m_pIUnknown);

    if (FAILED(hr))
        return FALSE;

    /*
     * Grab an IAnimal to show the Release rule.  We don't do
     * anything with this pointer, but we want to show the Release.
     */
    hr=m_pIUnknown->QueryInterface(IID_IAnimal, (void **)&m_pIAnimal);

    if (FAILED(hr))
        return FALSE;

    /*
     * In caching the IAnimal pointer we have to fix our
     * reference count.  SInce KoalaC is not aggregatable itself,
     * we can use the 32-bit rule for this case in 16-bit
     * compilations as well.
     *
     * Our reference count may be as little as one at this pointer
     * so calling our own Release (or m_pIAnimal's) is a bad idea.
     * Since we just need to fix the count, we can just decrement
     * m_cRef.  If we have to call someone's Release, then we'd
     * need to wrap that call in m_cRef++ and m_cRef--.
     */
    m_cRef--;

    return TRUE;
    }






/*
 * CKoalaA::QueryInterface
 * CKoalaA::AddRef
 * CKoalaA::Release
 *
 * Purpose:
 *  KoalaA's IUnknown implementation which serves as the outer
 *  unknown in the aggregation.
 */

STDMETHODIMP CKoalaA::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid)
        *ppv=this;

    //Alternately *ppv=m_pIAnimal; works for this case
    if (IID_IAnimal==riid)
        return m_pIUnknown->QueryInterface(riid, ppv);

    if (IID_IKoala==riid)
        *ppv=m_pImpIKoala;

    if (NULL==*ppv)
        return ResultFromScode(E_NOINTERFACE);

    ((LPUNKNOWN)*ppv)->AddRef();
    return NOERROR;
    }


DWORD CKoalaA::AddRef(void)
    {
    return ++m_cRef;
    }

DWORD CKoalaA::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    m_cRef++;       //Artificial count preventing reentrancy
    delete this;
    return 0;
    }






//CImpIKoala_A interface implementation


/*
 * CImpIKoala_A::CImpIKoala_A
 * CImpIKoala_A::~CImpIKoala_A
 *
 * Constructor Parameters:
 *  pObj            PCKoalaA to the outer object
 */

CImpIKoala_A::CImpIKoala_A(PCKoalaA pObj)
    {
    m_cRef=0;
    m_pObj=pObj;
    return;
    }

CImpIKoala_A::~CImpIKoala_A(void)
    {
    return;
    }



/*
 * CImpIKoala_A::QueryInterface
 * CImpIKoala_A::AddRef
 * CImpIKoala_A::Release
 *
 * IUnknown members that delegate to KoalaA
 */

STDMETHODIMP CImpIKoala_A::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pObj->QueryInterface(riid, ppv);
    }

DWORD CImpIKoala_A::AddRef(void)
    {
    ++m_cRef;
    return m_pObj->AddRef();
    }

DWORD CImpIKoala_A::Release(void)
    {
    --m_cRef;
    return m_pObj->Release();
    }



/*
 * CImpIKoala_A::ClimbEucalyptusTrees
 * CImpIKoala_A::PouchOpensDown
 * CImpIKoala_A::SleepForHoursAfterEating
 *
 * Purpose:
 *  Empty sample functions, no parameters, return NOERROR
 */

STDMETHODIMP CImpIKoala_A::ClimbEucalyptusTrees(void)
    {
    ODS("KoalaA's IKoala::ClimbEucalyptusTrees called");
    return NOERROR;
    }

STDMETHODIMP CImpIKoala_A::PouchOpensDown(void)
    {
    ODS("KoalaA's IKoala::PouchOpensDown called");
    return NOERROR;
    }

STDMETHODIMP CImpIKoala_A::SleepForHoursAfterEating(void)
    {
    ODS("KoalaA's IKoala::SleepForHoursAfterEating called");
    return NOERROR;
    }
