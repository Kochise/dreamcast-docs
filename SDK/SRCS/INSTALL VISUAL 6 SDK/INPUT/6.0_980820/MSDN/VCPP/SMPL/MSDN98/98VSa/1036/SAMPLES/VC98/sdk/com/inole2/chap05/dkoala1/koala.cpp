/*
 * KOALA.CPP
 * Koala Object Independent of DLL/EXE Servers, Chapter 5
 *
 * Implementation of the CKoala object that works in either
 * an EXE or DLL as it only implements IUnknown.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "koala.h"


/*
 * CKoala::CKoala
 * CKoala::~CKoala
 *
 * Parameters (Constructor):
 *  pUnkOuter       LPUNKNOWN of a controlling unknown.
 *  pfnDestroy      PFNDESTROYED to call when an object
 *                  is destroyed.
 */

CKoala::CKoala(LPUNKNOWN pUnkOuter, PFNDESTROYED pfnDestroy)
    {
    m_cRef=0;
    m_pUnkOuter=pUnkOuter;
    m_pfnDestroy=pfnDestroy;
    return;
    }

CKoala::~CKoala(void)
    {
    return;
    }



/*
 * CKoala::Init
 *
 * Purpose:
 *  Performs any intiailization of a CKoala that's prone to failure
 *  that we also use internally before exposing the object outside.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CKoala::Init(void)
    {
    //Nothing to do.
    return TRUE;
    }




/*
 * CKoala::QueryInterface
 * CKoala::AddRef
 * CKoala::Release
 *
 * Purpose:
 *  IUnknown members for CKoala object.
 */

STDMETHODIMP CKoala::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    /*
     * The only calls for IUnknown are either in a nonaggregated
     * case or when created in an aggregation, so in either case
     * always return our IUnknown for IID_IUnknown.
     */
    if (IID_IUnknown==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CKoala::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CKoala::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    /*
     * Tell the housing that an object is going away so it can
     * shut down if appropriate.
     */
    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0;
    }
