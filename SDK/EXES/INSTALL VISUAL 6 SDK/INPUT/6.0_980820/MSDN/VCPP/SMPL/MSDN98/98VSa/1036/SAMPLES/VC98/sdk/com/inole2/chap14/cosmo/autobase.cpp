/*
 * AUTOBASE.CPP
 * Cosmo Chapter 14
 *
 * Base object for Cosmo's OLE Automation support.  This class
 * provides the implementation of IDispatch as well as the code
 * that loads the appropriate type information.  This leaves
 * each specific object to implement it's specific interface and
 * little else.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Right Reserved.
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  INTERNET>kraigb@microsoft.com
 */


#include "cosmo.h"


/*
 * CAutoBase::CAutoBase
 * CAutoBase::~CAutoBase
 *
 * Constructor Parameters:
 *  pv              void * to the frame or document object that
 *                  derived classes will use to access the functions
 *                  they need to implemenet their interface.
 *  hInst           HINSTANCE of the application (for loading
 *                  resources)
 *  riid            REFIID of the interface that this object
 *                  should expose.
 *  rdiid           REFIID of the dispinterface that this
 *                  object should expose.
 *  pfnDestroy      PFNDESTROYED to call when the object
 *                  is destroyed.
 */

CAutoBase::CAutoBase(void *pv, HINSTANCE hInst, REFIID riid
    , REFIID rdiid, PFNDESTROYED pfnDestroy)
    {
    m_cRef=0L;
    m_pfnDestroy=pfnDestroy;

    m_pObj=pv;
    m_hInst=hInst;

    m_iid=riid;
    m_diid=rdiid;

    m_pImpIDispatch=NULL;
    m_pImpIExtConn=NULL;
    return;
    }


CAutoBase::~CAutoBase(void)
    {
    DeleteInterfaceImp(m_pImpIExtConn);
    DeleteInterfaceImp(m_pImpIDispatch);
    return;
    }


/*
 * CAutoBase::Init
 *
 * Purpose:
 *  Performs any intiailization of CAutoBase that's prone to failure
 *  that we also use internally before exposing the object outside.
 *
 * Parameters:
 *  fExtConn        BOOL indicating if we care about external
 *                  connections for shutdown.
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CAutoBase::Init(BOOL fExtConn)
    {
    //The derived class has to supply the IUnknown implementation
    m_pImpIDispatch=new CImpIDispatch(this
        , (IUnknown *)VTableInterface());

    if (NULL==m_pImpIDispatch)
        return FALSE;

    if (fExtConn)
        {
        m_pImpIExtConn=new CImpIExtConn
            ((IUnknown *)VTableInterface());

        if (NULL==m_pImpIExtConn)
            return FALSE;
        }

    return TRUE;
    }



//IDispatch interface implementation

/*
 * CImpIDispatch::CImpIDispatch
 * CImpIDispatch::~CImpIDispatch
 *
 * Parameters (Constructor):
 *  pObj            PCAutoBase to the containing object.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIDispatch::CImpIDispatch(PCAutoBase pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    m_pITypeInfo=NULL;
    return;
    }

CImpIDispatch::~CImpIDispatch(void)
    {
    ReleaseInterface(m_pITypeInfo);
    return;
    }



/*
 * CImpIDispatch::QueryInterface
 * CImpIDispatch::AddRef
 * CImpIDispatch::Release
 *
 * Purpose:
 *  IUnknown members for CImpIDispatch object.
 */

STDMETHODIMP CImpIDispatch::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIDispatch::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIDispatch::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIDispatch::GetTypeInfoCount
 * CImpIDispatch::GetTypeInfo
 */

STDMETHODIMP CImpIDispatch::GetTypeInfoCount(UINT *pctInfo)
    {
    //We implement GetTypeInfo so return 1
    *pctInfo=1;
    return NOERROR;
    }

STDMETHODIMP CImpIDispatch::GetTypeInfo(UINT itInfo, LCID lcid
    , ITypeInfo **ppITypeInfo)
    {
    HRESULT     hr;
    ITypeLib   *pITypeLib;
    ITypeInfo **ppITI=NULL;

    if (0!=itInfo)
        return ResultFromScode(TYPE_E_ELEMENTNOTFOUND);

    if (NULL==ppITypeInfo)
        return ResultFromScode(E_POINTER);

    *ppITypeInfo=NULL;

    /*
     * This switch statement is nicely extensible for other
     * languages and other m_pITypeInfo variables (such as it
     * was used in Beeper #2 (see ..\beeper2\beeper.cpp)
     */
    switch (PRIMARYLANGID(lcid))
        {
        case LANG_NEUTRAL:
        case LANG_ENGLISH:
            ppITI=&m_pITypeInfo;
            break;

        default:
            return ResultFromScode(DISP_E_UNKNOWNLCID);
        }

    //Load a type lib if we don't have the information already.
    if (NULL==*ppITI)
        {
        hr=LoadRegTypeLib(LIBID_CosmoTypeLibrary, 1, 0
            , PRIMARYLANGID(lcid), &pITypeLib);

        /*
         * If LoadRegTypeLib fails, try loading directly from
         * our module with LoadTypeLib.
         */
        if (FAILED(hr))
            {
            const int   cch=512;
            TCHAR       szModule[cch];

            GetModuleFileName(m_pObj->m_hInst, szModule, cch);

            switch (PRIMARYLANGID(lcid))
                {
                case LANG_NEUTRAL:
                case LANG_ENGLISH:
                   #ifdef WIN32ANSI
                    OLECHAR szTemp[512];
                    MultiByteToWideChar(CP_ACP, 0, szModule, -1, szTemp, 512);
                    hr=LoadTypeLib(szTemp, &pITypeLib);
                   #else
                    hr=LoadTypeLib(szModule, &pITypeLib);
                   #endif
                    break;

                /*
                 * Easily extensible with additional languages.
                 * Use LoadTypeLibFromResource or specify
                 * separate .TLB files instead of the module name.
                 * Be sure to use your DIR registry key to find
                 * the right path.
                 */
                }
            }

        if (FAILED(hr))
            return hr;

        //Got the type lib, get type info for the interface we want
        hr=pITypeLib->GetTypeInfoOfGuid(m_pObj->m_iid, ppITI);
        pITypeLib->Release();

        if (FAILED(hr))
            return hr;
        }

    //Ref on ITypeInfo holds type library in memory
    (*ppITI)->AddRef();
    *ppITypeInfo=*ppITI;
    return NOERROR;
    }



/*
 * CImpIDispatch::GetIDsOfNames
 * CImpIDispatch::Invoke
 */

STDMETHODIMP CImpIDispatch::GetIDsOfNames(REFIID riid
    , OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgDispID)
    {
    HRESULT     hr;
    ITypeInfo  *pTI;

    if (IID_NULL!=riid)
        return ResultFromScode(DISP_E_UNKNOWNINTERFACE);

    hr=GetTypeInfo(0, lcid, &pTI);

    if (SUCCEEDED(hr))
        {
        hr=DispGetIDsOfNames(pTI, rgszNames, cNames, rgDispID);
        pTI->Release();
        }

    return hr;
    }

STDMETHODIMP CImpIDispatch::Invoke(DISPID dispID, REFIID riid
    , LCID lcid, unsigned short wFlags, DISPPARAMS *pDispParams
    , VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
    {
    HRESULT     hr;
    ITypeInfo  *pTI;

    if (IID_NULL!=riid)
        return ResultFromScode(DISP_E_UNKNOWNINTERFACE);

    //Get the ITypeInfo for lcid
    hr=GetTypeInfo(0, lcid, &pTI);

    if (FAILED(hr))
        return hr;

    //Note:  this sample doesn't do anything with exceptions.

    //The VTableInterface function gets us the right pointer
    hr=pTI->Invoke(m_pObj->VTableInterface(), dispID, wFlags
        , pDispParams, pVarResult, pExcepInfo, puArgErr);

    pTI->Release();
    return hr;
    }




//IExternalConnection implementation

/*
 * CImpIExtConn::CImpIExtConn
 * CImpIExtConn::~CImpIExtConn
 *
 * Parameters (Constructor):
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIExtConn::CImpIExtConn(LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pUnkOuter=pUnkOuter;
    m_cStrong=0;
    return;
    }

CImpIExtConn::~CImpIExtConn(void)
    {
    return;
    }



/*
 * CImpIExtConn::QueryInterface
 * CImpIExtConn::AddRef
 * CImpIExtConn::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIExtConn.
 */

STDMETHODIMP CImpIExtConn::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIExtConn::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIExtConn::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIExtConn::AddConnection
 *
 * Purpose:
 *  Informs the object that a connection has been made to it.  We
 *  count only strong references.
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

STDMETHODIMP_(DWORD) CImpIExtConn::AddConnection
    (DWORD dwConn, DWORD dwReserved)
    {
    if (EXTCONN_STRONG==dwConn)
        {
        m_cStrong++;
        return m_cStrong;
        }

    return 0L;
    }






/*
 * CImpIExtConn::ReleaseConnection
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
 *  fLastReleaseCloses  BOOL indicating if the last call to this
 *                      function should close the object.
 *
 * Return Value:
 *  DWORD           The number of remaining connection counts on
 *                  the object, used for debugging purposes only.
 */

STDMETHODIMP_(DWORD) CImpIExtConn::ReleaseConnection
    (DWORD dwConn, DWORD dwReserved, BOOL fLastReleaseCloses)
    {
    DWORD       dw=0L;

    if (EXTCONN_STRONG==dwConn)
        {
        dw=--m_cStrong;

        /*
         * Note that in the way we're using this interface we
         * don't care about fLastReleaseCloses.
         */
        if (0L==m_cStrong)
            m_pUnkOuter->Release();     //Closes app or doc
        }

    return dw;
    }
