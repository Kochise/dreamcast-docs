/*
 * KOALA.CPP
 * Koala Object for EXE Servers, Chapter 6
 *
 * Implementation of an object with IExternalConnection.
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

    //CHAPTER6MOD
    m_cStrong=0;
    m_cWeak=0;

    m_pImpIPersist=NULL;
    //End CHAPTER6MOD
    return;
    }

CKoala::~CKoala(void)
    {
    //CHAPTER6MOD
    DeleteInterfaceImp(m_pImpIPersist);
    //End CHAPTER6MOD
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
    //CHAPTER6MOD
    IUnknown   *pUnk=this;

    if (NULL!=m_pUnkOuter)
        pUnk=m_pUnkOuter;

    m_pImpIPersist=new CImpIPersist(this, pUnk);

    //No failure if m_pImpIPersist is NULL, QueryInterface will fail

    return TRUE;
    //End CHAPTER6MOD
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

    //CHAPTER6MOD
    if (IID_IUnknown==riid || IID_IExternalConnection==riid)
        *ppv=this;

    if (IID_IPersist==riid && NULL!=m_pImpIPersist)
        *ppv=m_pImpIPersist;
    //End CHAPTER6MOD

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

    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0;
    }




//CHAPTER6MOD
/*
 * CKoala::AddConnection
 *
 * Purpose:
 *  Informs the object that a strong connection has been made to it.
 *
 * Parameters:
 *  dwConn          DWORD identifying the type of connection, taken
 *                  from the EXTCONN enumeration.
 *  dwReserved      DWORD reserved.  This is used inside OLE and
 *                  should not be validated.
 *
 * Return Value:
 *  DWORD           The number of connection counts on the
 *                  object, used for debugging purposes only.
 */

STDMETHODIMP_(DWORD) CKoala::AddConnection(DWORD dwConn
    , DWORD dwReserved)
    {
    DWORD       dwRet;
    TCHAR       szTemp[80];

    if (EXTCONN_STRONG & dwConn)
        {
        dwRet=++m_cStrong;
        wsprintf(szTemp
            , TEXT("AddConnection cStrong=%lu"), m_cStrong);
        }

   #ifdef WIN32
    if (EXTCONN_WEAK & dwConn)
        {
        dwRet=++m_cWeak;
        wsprintf(szTemp
            , TEXT("ReleaseConnection cWeak=%lu"), m_cWeak);
        }
   #endif

   #ifndef WIN32
    ODS(szTemp);
   #else
    MessageBox(NULL, szTemp
        , TEXT("EKoala3: CKoala::IExternalConnection"), MB_OK);
   #endif

    return dwRet;
    }



/*
 * CKoala::ReleaseConnection
 *
 * Purpose:
 *  Informs an object that a connection has been taken away from
 *  it in which case the object may need to shut down.
 *
 * Parameters:
 *  dwConn              DWORD identifying the type of connection,
 *                      taken from the EXTCONN enumeration.
 *  dwReserved          DWORD reserved.  This is used inside OLE and
 *                      should not be validated.
 *  dwRerved            DWORD reserved
 *  fLastReleaseCloses  BOOL indicating if the last call to this
 *                      function should close the object.
 *
 * Return Value:
 *  DWORD           The number of remaining connection counts on
 *                  the object, used for debugging purposes only.
 */

STDMETHODIMP_(DWORD) CKoala::ReleaseConnection(DWORD dwConn
    , DWORD dwReserved, BOOL fLastReleaseCloses)
    {
    DWORD       dwRet;
    TCHAR       szTemp[80];

    if (EXTCONN_STRONG & dwConn)
        {
        /*
         * Note:  We don't need to close ourselves when the last
         * strong lock is removed; we're just implementing this
         * interface for demonstration.
         */

        dwRet=--m_cStrong;
        wsprintf(szTemp
            , TEXT("ReleaseConnection cStrong=%lu"), m_cStrong);
        }

   #ifdef WIN32
    if (EXTCONN_WEAK & dwConn)
        {
        dwRet=--m_cWeak;
        wsprintf(szTemp
            , TEXT("ReleaseConnection cWeak=%lu"), m_cWeak);
        }
   #endif

   #ifndef WIN32
    ODS(szTemp);
   #else
    MessageBox(NULL, szTemp
        , TEXT("EKoala3: CKoala::IExternalConnection"), MB_OK);
   #endif

    return dwRet;
    }




///IPersist implementation

/*
 * CImpIPersist:CImpIPersist
 * CImpIPersist::~CImpIPersist
 *
 * Constructor Parameters:
 *  pObj            PCKoala pointing to the object we live in.
 *  pUnkOuter       LPUNKNOWN of the controlling unknown.
 */

CImpIPersist::CImpIPersist(PCKoala pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIPersist::~CImpIPersist(void)
    {
    return;
    }



/*
 * CImpIPersist::QueryInterface
 * CImpIPersist::AddRef
 * CImpIPersist::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIPersist.
 */

STDMETHODIMP CImpIPersist::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPersist::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPersist::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIPersist::GetClassID
 *
 * Purpose:
 *  Returns the CLSID of the object represented by this interface.
 *
 * Parameters:
 *  pClsID          LPCLSID in which to store our CLSID.
 */

STDMETHODIMP CImpIPersist::GetClassID(LPCLSID pClsID)
    {
    *pClsID=CLSID_Koala;
    return NOERROR;
    }

//End CHAPTER6MOD
