/* @doc
 *
 * @module KOALA.CPP - Koala Object DLL/EXE Chapter 4 |
 *
 * Implementation of the CKoala and CImpIPersist objects that
 * works in either an EXE or DLL.
 *
 * Copyright (c)1993 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Software Design Engineer
 * Microsoft Systems Developer Relations
 *
 * Autoduck example by Eric Artzt (erica@microsoft.com)
 */


#include "koala.h"


/* @mfunc <c CKoala> constructor.
 */

CKoala::CKoala(
    LPUNKNOWN pUnkOuter,        //@parm LPUNKNOWN of a controlling unknown.
    LPFNDESTROYED pfnDestroy)   //@parm Function to call when an object
    {                           //       is destroyed.
    m_cRef=0;
    m_pUnkOuter=pUnkOuter;
    m_pfnDestroy=pfnDestroy;

    //NULL any contained interfaces initially.
    m_pIPersist=NULL;

    return;
    }


/* @mfunc <c CKoala> destructor.
 */

CKoala::~CKoala(void)
    {
    //Free contained interfaces.
    if (NULL!=m_pIPersist)
        delete m_pIPersist;     //Interface does not free itself.

    return;
    }



/*
 * @mfunc Performs any intiailization of a CKoala that's prone to failure
 *  that we also use internally before exposing the object outside.
 *
 * @rdesc TRUE if the function is successful, FALSE otherwise.
 */

BOOL CKoala::FInit(void)
    {
    LPUNKNOWN       pIUnknown=(LPUNKNOWN)this;

    if (NULL!=m_pUnkOuter)
        pIUnknown=m_pUnkOuter;

    //Allocate contained interfaces.
    m_pIPersist=new CImpIPersist(this, pIUnknown);

    return (NULL!=m_pIPersist);
    }


/* @mfunc <i IUnknown> member for <o CKoala> object.
 */
 
STDMETHODIMP CKoala::QueryInterface(REFIID riid, LPLPVOID ppv)
    {
    *ppv=NULL;

    /*
     * The only calls for IUnknown are either in a nonaggregated
     * case or when created in an aggregation, so in either case
     * always return our IUnknown for IID_IUnknown.
     */
    if (IsEqualIID(riid, IID_IUnknown))
        *ppv=(LPVOID)this;

    /*
     * For IPersist we return our contained interface.  For EXEs we
     * have to return our interface for IPersistStorage as well
     * since OLE 2.0 doesn't support IPersist implementations by
     * themselves (assumed only to be a base class).  If a user
     * asked for an IPersistStorage and used it, they would crash--
     * but this is a demo, not a real object.
     */
    if (IsEqualIID(riid, IID_IPersist)
        || IsEqualIID(riid, IID_IPersistStorage))
        *ppv=(LPVOID)m_pIPersist;

    //AddRef any interface we'll return.
    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


/* @mfunc <i IUnknown> member for <o CKoala> object.
 */
 
STDMETHODIMP_(ULONG) CKoala::AddRef(void)
    {
    return ++m_cRef;
    }


/* @mfunc <i IUnknown> member for <o CKoala> object.
 */
 
STDMETHODIMP_(ULONG) CKoala::Release(void)
    {
    ULONG       cRefT;

    cRefT=--m_cRef;

    if (0L==m_cRef)
        {
        /*
         * Tell the housing that an object is going away so it can
         * shut down if appropriate.
         */
        if (NULL!=m_pfnDestroy)
            (*m_pfnDestroy)();

        delete this;
        }

    return cRefT;
    }



/* @mfunc <c CImpIPersist> constructor.
 */

CImpIPersist::CImpIPersist(
    LPCKoala pObj,              //@parm LPCKoala of the object we're in.
    LPUNKNOWN pUnkOuter)        //@parm LPUNKNOWN to which we delegate.
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

/*
 * @mfunc <c CImpIPersist> destructor.
 */

CImpIPersist::~CImpIPersist(void)
    {
    return;
    }






/* @mfunc <i IUnknown> member for <o CImpIPersist> object.
 */
 
STDMETHODIMP CImpIPersist::QueryInterface(REFIID riid
    , LPLPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


/* @mfunc <i IUnknown> member for <o CImpIPersist> object.
 */
 
STDMETHODIMP_(ULONG) CImpIPersist::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

/* @mfunc <i IUnknown> member for <o CImpIPersist> object.
 */
 
STDMETHODIMP_(ULONG) CImpIPersist::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * @mfunc Returns the Class ID of this object.
 *
 * @rdesc NOERROR always.
 */

STDMETHODIMP CImpIPersist::GetClassID(
    LPCLSID pClsID)                     //@parm Where to return our class ID.
    {
    *pClsID=CLSID_Koala;
    return NOERROR;
    }
