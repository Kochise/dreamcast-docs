/*
 * BEEPER.CPP
 * Simple Automation Object #5 Chapter 14
 *
 * Implementation of the CBeeper class demonstrating the use of
 * CreateStdDispatch instead of DispInvoke, DispGetIDOfNames, and
 * a custom IDispatch implementation.  In this case we don't have
 * our own IDispatch at all, which CreateStdDispatch provides for
 * us, but at the loss of multiple language support and the ability
 * to define exception.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "beeper.h"


/*
 * CBeeper::CBeeper
 * CBeeper::~CBeeper
 *
 * Parameters (Constructor):
 *  pUnkOuter       LPUNKNOWN of a controlling unknown.
 *  pfnDestroy      PFNDESTROYED to call when an object
 *                  is destroyed.
 */

CBeeper::CBeeper(LPUNKNOWN pUnkOuter, PFNDESTROYED pfnDestroy)
    {
    m_cRef=0;
    m_pUnkOuter=pUnkOuter;
    m_pfnDestroy=pfnDestroy;

    m_lSound=0;
    m_pITINeutral=NULL;
    m_pIUnkStdDisp=NULL;
    return;
    }


CBeeper::~CBeeper(void)
    {
    ReleaseInterface(m_pIUnkStdDisp);
    ReleaseInterface(m_pITINeutral);
    return;
    }



/*
 * CBeeper::Init
 *
 * Purpose:
 *  Performs any intiailization of a CBeeper that's prone to failure
 *  that we also use internally before exposing the object outside.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CBeeper::Init(void)
    {
    LPUNKNOWN       pIUnknown=this;
    ITypeLib       *pITypeLib;
    HRESULT         hr;

    if (NULL!=m_pUnkOuter)
        pIUnknown=m_pUnkOuter;

    /*
     * Load our type library.  Since this sample uses
     * CreateStdDispatch we can only support one locale,
     * which is neutral (English) in this case.
     */

    if (FAILED(LoadRegTypeLib(LIBID_BeeperTypeLibrary, 1, 0
        , LANG_NEUTRAL, &pITypeLib)))
        {
        /*
         * If LoadRegTypeLib fails, try loading directly with
         * LoadTypeLib, which will register the library for us.
         *
         * NOTE:  You should prepend your DIR registry key to the
         * .TLB name so you don't depend on it being it the PATH.
         * This sample will be updated later to reflect this.
         */
        if (FAILED(LoadTypeLib(OLETEXT("BEEP0000.TLB"), &pITypeLib)))
            return FALSE;
        }

    //Get the type information out of the type library.
    hr=pITypeLib->GetTypeInfoOfGuid(DIID_DIBeeper, &m_pITINeutral);

    if (FAILED(hr))
        {
        pITypeLib->Release();
        return FALSE;
        }

    m_pImpIProvideCI=new CImpIProvideClassInfo(this, pITypeLib);
    pITypeLib->Release();

    if (FAILED(hr))
        return FALSE;

    /*
     * CreateStdDispatch always returns an IUnknown pointer
     * because such is required in aggregation, which is
     * involved here.  In other words, the Beeper is aggregating
     * on the OLE-provided "StdDispatch" object in order to
     * directly expose IDispatch from that object.  See the
     * implementation of QueryInterface.
     */
    hr=CreateStdDispatch(pIUnknown, (IBeeper *)this, m_pITINeutral
        , &m_pIUnkStdDisp);

    if (FAILED(hr))
        return FALSE;

    return TRUE;
    }



/*
 * CBeeper::QueryInterface
 * CBeeper::AddRef
 * CBeeper::Release
 *
 * Purpose:
 *  IUnknown members for CBeeper object.
 */

STDMETHODIMP CBeeper::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    /*
     * The only calls for IUnknown are either in a nonaggregated
     * case or when created in an aggregation, so in either case
     * always return our IUnknown for IID_IUnknown.
     */
    if (IID_IUnknown==riid || IID_IBeeper==riid)
        *ppv=this;

    /*
     * We specifically have to ask the object returned from
     * CreateStdDispatch for our dispinterface.  Note that
     * it only understands IID_IDispatch and not DIID_DIBeeper,
     * so we convert requests for DIID_DIBeeper into IID_IDispatch
     * which amounts to exactly the same thing.
     */
    if (IID_IDispatch==riid || DIID_DIBeeper==riid)
        return m_pIUnkStdDisp->QueryInterface(IID_IDispatch, ppv);

    //AddRef any interface we'll return.
    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CBeeper::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CBeeper::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    //Inform the server about destruction so it can handle shutdown
    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0L;
    }



//IBeeper interface functions

/*
 * CBeeper::get_Sound
 * CBeeper::put_Sound
 *
 * Purpose:
 *  Functions called from DispInvoke to handle the Sound property.
 *
 * Parameters (Set only):
 *  lSound          long, new sound to save after validation.
 *
 * Return Value: (Get only):
 *  ULONG           Current sound.
 */

STDMETHODIMP_(long) CBeeper::get_Sound(void)
    {
    return m_lSound;
    }


STDMETHODIMP_(void) CBeeper::put_Sound(long lSound)
    {
    if (MB_OK!=lSound && MB_ICONEXCLAMATION!=lSound
        && MB_ICONQUESTION!=lSound && MB_ICONHAND!=lSound
        && MB_ICONASTERISK!=lSound)
        {
        /*
         * We cannot return error information to the StdDispatch
         * given the way we've defined the return value of this
         * methods, so we can't raise an exception.
         */
        return;
        }

    m_lSound=lSound;
    return;
    }



/*
 * CBeeper::Beep
 *
 * Purpose:
 *  Function called from DispInvoke to invoke the Beep method.
 *
 * Return Value:
 *  long            The sound played.
 */

STDMETHODIMP_(long) CBeeper::Beep(void)
    {
    MessageBeep((UINT)m_lSound);
    return m_lSound;
    }




/*
 * Since CreateStdDispatch provides an IDispatch implementation
 * for us, there's no specific code for that interface needed here.
 *
 * So to not get rid of too much code, we'll add an
 * IProvideClassInfo
 */



/*
 * CImpIProvideClassInfo::CImpIProvideClassInfo
 * CImpIProvideClassInfo::~CImpIProvideClassInfo
 *
 * Parameters (Constructor):
 *  pUnkOuter       LPUNKNOWN of a controlling unknown.
 *  pITypeLib       ITypeLib * to return from this interface.
 */

CImpIProvideClassInfo::CImpIProvideClassInfo(LPUNKNOWN pUnkOuter
    , ITypeLib *pITypeLib)
    {
    m_cRef=0;
    m_pUnkOuter=pUnkOuter;

    /*
     * Get the coclass type info.  If this fails then we'll
     * just fail GetClassInfo below.
     */
    m_pITI=NULL;
    pITypeLib->GetTypeInfoOfGuid(CLSID_Beeper, &m_pITI);
    return;
    }


CImpIProvideClassInfo::~CImpIProvideClassInfo(void)
    {
    ReleaseInterface(m_pITI);
    return;
    }


/*
 * CImpIProvideClassInfo::QueryInterface
 * CImpIProvideClassInfo::AddRef
 * CImpIProvideClassInfo::Release
 *
 * Purpose:
 *  IUnknown members for CImpIProvideClassInfo object.
 */

STDMETHODIMP CImpIProvideClassInfo::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIProvideClassInfo::AddRef(void)
    {
    return m_pUnkOuter->AddRef();
    }


STDMETHODIMP_(ULONG) CImpIProvideClassInfo::Release(void)
    {
    return m_pUnkOuter->Release();
    }




/*
 * CImpIProvideClassInfo::GetClassInfo
 *
 * Purpose:
 *  Returns the type information for this coclass.
 *
 * Parameters:
 *  ppITI           ITypeInfo ** in which to store the ITypeInfo
 *                  for this coclass.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, error otherwise.
 */

STDMETHODIMP CImpIProvideClassInfo::GetClassInfo(ITypeInfo **ppITI)
    {
    if (NULL==ppITI)
        return ResultFromScode(E_POINTER);

    *ppITI=m_pITI;

    if (NULL!=m_pITI)
        {
        m_pITI->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_FAIL);
    }
