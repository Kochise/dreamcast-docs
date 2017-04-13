/*
 * BEEPER.CPP
 * Beeper Automation Object #2 Chapter 14
 *
 * Implementation of the CBeeper class demonstrating the use of
 * functions like ITypeInfo::Invoke (same as DispInboke) and
 * ITypeInfo::GetIDOfNames (same as DispGetIDOfNames) where the
 * type information is taken from a type library.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "beeper.h"

extern HINSTANCE g_hInst;


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
    m_pImpIDispatch=NULL;
    return;
    }


CBeeper::~CBeeper(void)
    {
    DeleteInterfaceImp(m_pImpIDispatch);
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

    if (NULL!=m_pUnkOuter)
        pIUnknown=m_pUnkOuter;

    m_pImpIDispatch=new CImpIDispatch(this, pIUnknown);

    if (NULL==m_pImpIDispatch)
        return FALSE;

    return TRUE;
    }




/*
 * CBeeper::QueryInterface
 * CBeeper::AddRef
 * CBeeper::Release
 */

STDMETHODIMP CBeeper::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    /*
     * The only calls for IUnknown are either in a nonaggregated
     * case or when created in an aggregation, so in either case
     * always return our IUnknown for IID_IUnknown.
     *
     * Note that IBeeper is implemented on CBeeper, and we must
     * also expose that custom interface through QueryInterface.
     */
    if (IID_IUnknown==riid || IID_IBeeper==riid)
        *ppv=this;

    /*
     * QueryInterface must respond not only to IID_IDispatch for
     * the primary automation interface, but also to the IID of the
     * dispinterface itself, which in our case is DIID_DIBeeper.
     */
    if (IID_IDispatch==riid || DIID_DIBeeper==riid)
        *ppv=m_pImpIDispatch;

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
 *  lSound          long, new sound to save after validation
 *
 * Return Value: (Get only):
 *  long            Current sound.
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
         * Since we cannot return a value to ITypeInfo::Invoke to
         * indicate an exception condition, we'll use
         * m_pImpIDispatch->Exception to raise them.  Before
         * CImpIDispatch::Invoke calls ITypeInfo::Invoke, it clears
         * the exception.  CImpIDispatch::Exception sets an
         * exception, so when ITypeInfo::Invoke returns, our Invoke
         * can store exception information as necessary.
         */
        m_pImpIDispatch->Exception(EXCEPTION_INVALIDSOUND);
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
 *  long           The sound played.
 */

STDMETHODIMP_(long) CBeeper::Beep(void)
    {
    MessageBeep((UINT)m_lSound);
    return m_lSound;
    }





//IDispatch interface implementation

/*
 * CImpIDispatch::CImpIDispatch
 * CImpIDispatch::~CImpIDispatch
 *
 * Parameters (Constructor):
 *  pObj            PCBeeper of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIDispatch::CImpIDispatch(PCBeeper pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;

    //These are created as needed in GetTypeInfo
    m_pITINeutral=NULL;
    m_pITIGerman=NULL;

    return;
    }

CImpIDispatch::~CImpIDispatch(void)
    {
    ReleaseInterface(m_pITIGerman);
    ReleaseInterface(m_pITINeutral);
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
 *
 * Purpose:
 *  Returns the number of type information (ITypeInfo) interfaces
 *  that the object provides (0 or 1).
 *
 * Parameters:
 *  pctInfo         UINT * to the location to receive
 *                  the count of interfaces.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error code.
 */

STDMETHODIMP CImpIDispatch::GetTypeInfoCount(UINT *pctInfo)
    {
    //We implement GetTypeInfo so return 1
    *pctInfo=1;
    return NOERROR;
    }




/*
 * CImpIDispatch::GetTypeInfo
 *
 * Purpose:
 *  Retrieves type information for the automation interface.  This
 *  is used anywhere that the right ITypeInfo interface is needed
 *  for whatever LCID is applicable.  Specifically, this is used
 *  from within GetIDsOfNames and Invoke.
 *
 * Parameters:
 *  itInfo          UINT reserved.  Must be zero.
 *  lcid            LCID providing the locale for the type
 *                  information.  If the object does not support
 *                  localization, this is ignored.
 *  ppITypeInfo     ITypeInfo ** in which to store the ITypeInfo
 *                  interface for the object.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error code.
 */

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
     * Since we returned one from GetTypeInfoCount, this function
     * can be called for a specific locale.  We support English,
     * German, and neutral (defaults to English) locales.  Anything
     * else is an error.
     *
     * After this switch statement, ppITI will either be NULL or
     * a valid pointer in it after.  If NULL, we know we need to
     * load type information, retrieve the ITypeInfo we want, and
     * then store it in *ppITI.
     */
    switch (PRIMARYLANGID(lcid))
        {
        case LANG_NEUTRAL:
        case LANG_ENGLISH:
            ppITI=&m_pITINeutral;
            break;

        case LANG_GERMAN:
            ppITI=&m_pITIGerman;
            break;

        default:
            return ResultFromScode(DISP_E_UNKNOWNLCID);
        }

    //Load a type lib if we don't have the information already.
    if (NULL==*ppITI)
        {
        /*
         * The type libraries are registered under 0 (neutral),
         * 7 (German), and 9 (English) with no specific sub-
         * language, which would make them 407 or 409 and such.
         * If you are sensitive to sub-languages, then use the
         * full LCID instead of just the LANGID as done here.
         */
        hr=LoadRegTypeLib(LIBID_BeeperTypeLibrary, 1, 0
            , PRIMARYLANGID(lcid), &pITypeLib);

        /*
         * If LoadRegTypeLib fails, try loading directly with
         * LoadTypeLib, which will register the library for us.
         * Note that there's no default case here because the
         * prior switch will have filtered lcid already.
         *
         * NOTE:  You should prepend your DIR registry key to the
         * .TLB name so you don't depend on it being it the PATH.
         * This sample will be updated later to reflect this.
         */
        if (FAILED(hr))
            {
            switch (PRIMARYLANGID(lcid))
                {
                case LANG_NEUTRAL:
                case LANG_ENGLISH:
                    hr=LoadTypeLib(OLETEXT("BEEP0000.TLB"), &pITypeLib);
                    break;

                case LANG_GERMAN:
                    hr=LoadTypeLib(OLETEXT("BEEP0007.TLB"), &pITypeLib);
                    break;
                }
            }

        if (FAILED(hr))
            return hr;

        //Got the type lib, get type info for the interface we want
        hr=pITypeLib->GetTypeInfoOfGuid(DIID_DIBeeper, ppITI);
        pITypeLib->Release();

        if (FAILED(hr))
            return hr;
        }

    /*
     * Note:  the type library is still loaded since we have
     * an ITypeInfo from it.
     */

    (*ppITI)->AddRef();
    *ppITypeInfo=*ppITI;
    return NOERROR;
    }









/*
 * CImpIDispatch::GetIDsOfNames
 *
 * Purpose:
 *  Converts text names into DISPIDs to pass to Invoke
 *
 * Parameters:
 *  riid            REFIID reserved.  Must be IID_NULL.
 *  rgszNames       OLECHAR ** pointing to the array of names to be
 *                  mapped.
 *  cNames          UINT number of names to be mapped.
 *  lcid            LCID of the locale.
 *  rgDispID        DISPID * caller allocated array containing IDs
 *                  corresponging to those names in rgszNames.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error code.
 */

STDMETHODIMP CImpIDispatch::GetIDsOfNames(REFIID riid
    , OLECHAR **rgszNames, UINT cNames, LCID lcid, DISPID *rgDispID)
    {
    HRESULT     hr;
    ITypeInfo  *pTI;

    if (IID_NULL!=riid)
        return ResultFromScode(DISP_E_UNKNOWNINTERFACE);

    //Get the right ITypeInfo for lcid.
    hr=GetTypeInfo(0, lcid, &pTI);

    if (SUCCEEDED(hr))
        {
        hr=DispGetIDsOfNames(pTI, rgszNames, cNames, rgDispID);
        pTI->Release();
        }

    return hr;
    }



/*
 * CImpIDispatch::Invoke
 *
 * Purpose:
 *  Calls a method in the dispatch interface or manipulates a
 *  property.
 *
 * Parameters:
 *  dispID          DISPID of the method or property of interest.
 *  riid            REFIID reserved, must be IID_NULL.
 *  lcid            LCID of the locale.
 *  wFlags          USHORT describing the context of the invocation.
 *  pDispParams     DISPPARAMS * to the array of arguments.
 *  pVarResult      VARIANT * in which to store the result.  Is
 *                  NULL if the caller is not interested.
 *  pExcepInfo      EXCEPINFO * to exception information.
 *  puArgErr        UINT * in which to store the index of an
 *                  invalid parameter if DISP_E_TYPEMISMATCH
 *                  is returned.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error code.
 */

STDMETHODIMP CImpIDispatch::Invoke(DISPID dispID, REFIID riid
    , LCID lcid, unsigned short wFlags, DISPPARAMS *pDispParams
    , VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
    {
    HRESULT     hr;
    ITypeInfo  *pTI;

    //riid is supposed to be IID_NULL always
    if (IID_NULL!=riid)
        return ResultFromScode(DISP_E_UNKNOWNINTERFACE);

    //Get the ITypeInfo for lcid
    hr=GetTypeInfo(0, lcid, &pTI);

    if (FAILED(hr))
        return hr;

    /*
     * Clear exceptions.  Note that this mechanism only works
     * for a single-thread, which is fine for the initial 32-bit
     * release of OLE but not a long-term solution.  See Beeper3
     * for a way of handling multi-thread exceptions.
     */
    m_wException=EXCEPTION_NONE;

    //This is exactly what DispInvoke does--so skip the overhead.
    hr=pTI->Invoke((IBeeper *)m_pObj, dispID, wFlags
        , pDispParams, pVarResult, pExcepInfo, puArgErr);

    /*
     * Check if an exception was raised.  Again, this is not
     * thread-safe.
     */
    if (EXCEPTION_NONE!=m_wException)
        {
        pExcepInfo->scode
            =(SCODE)MAKELONG(m_wException, PRIMARYLANGID(lcid));
        FillException(pExcepInfo);
        hr=ResultFromScode(DISP_E_EXCEPTION);
        }

    pTI->Release();
    return hr;
    }




/*
 * CImpIDispatch::Exception
 *
 * Purpose:
 *  Raises an exception for CImpIDispatch::Invoke from within
 *  ITypeInfo::Invoke.  This simply sets the m_wException variable
 *  to the exception code.  Invoke will pick this up and fill in
 *  the exception structure as necessary.
 *
 * Parameters:
 *  wException      WORD exception code.
 */

void CImpIDispatch::Exception(WORD wException)
    {
    /*
     * Note: calls to this function will be wrapped in a critical
     * section on Win32 because this is always called from within
     * DispInvoke which we wrapped above in Invoke.
     */
    m_wException=wException;
    return;
    }




/*
 * FillException
 *
 * Purpose:
 *  Callback function pointed to in IDispatch::Invoke that fills
 *  an EXCEPINFO structure based on the code stored inside
 *  Invoke.  This is a nice mechanism to keep all the management
 *  of error code strings and help IDs centralized in one place,
 *  even across many different automation objects within the same
 *  application.  It also keeps Invoke cleaner.
 *
 * Parameters:
 *  pExcepInfo      EXCEPINFO * to fill.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, error code otherwise.
 */

HRESULT STDAPICALLTYPE FillException(EXCEPINFO *pExcepInfo)
    {
    SCODE       scode;
    LANGID      langID;
    USHORT      wCode;
    HRESULT     hr;
    LPTSTR      psz;
    LPOLESTR    pszHelp;
    UINT        idsSource;
    UINT        idsException;

    if (NULL==pExcepInfo)
        return ResultFromScode(E_INVALIDARG);

    scode=pExcepInfo->scode;
    langID=HIWORD(scode);
    wCode=LOWORD(scode);

    //Allocate BSTRs for source and description strings
    psz=(LPTSTR)malloc(1024*sizeof(TCHAR));

    if (NULL==psz)
        return ResultFromScode(E_OUTOFMEMORY);

    hr=NOERROR;

    switch (wCode)
        {
        case EXCEPTION_INVALIDSOUND:
            //Fill in unused information, macro in inole.h
            INITEXCEPINFO(*pExcepInfo);
            pExcepInfo->wCode=wCode;

            pExcepInfo->dwHelpContext=HID_SOUND_PROPERTY_LIMITATIONS;

            //We registered a HELPDIR so we don't include paths
            pszHelp=OLETEXT("beep0000.hlp");
            idsSource=IDS_0_EXCEPTIONSOURCE;
            idsException=IDS_0_EXCEPTIONINVALIDSOUND;

            //Get the localized source and exception strings
            switch (langID)
                {
                case LANG_GERMAN:
                    idsSource=IDS_7_EXCEPTIONSOURCE;
                    idsException=IDS_7_EXCEPTIONINVALIDSOUND;
                    pszHelp=OLETEXT("beep0007.hlp");
                    break;

                case LANG_ENGLISH:
                case LANG_NEUTRAL:
                default:
                    break;
                }

            break;

        default:
            hr=ResultFromScode(E_FAIL);
        }

    if (SUCCEEDED(hr))
        {
        pExcepInfo->bstrHelpFile=SysAllocString(pszHelp);

       #ifdef WIN32ANSI
        OLECHAR     szTemp[256];

        LoadString(g_hInst, idsSource, psz, 256);
        MultiByteToWideChar(CP_ACP, 0, psz, -1, szTemp, 256);
        pExcepInfo->bstrSource=SysAllocString(szTemp);

        LoadString(g_hInst, idsException, psz, 256);
        MultiByteToWideChar(CP_ACP, 0, psz, -1, szTemp, 256);
        pExcepInfo->bstrDescription=SysAllocString(szTemp);
       #else
        LoadString(g_hInst, idsSource, psz, 1024);
        pExcepInfo->bstrSource=SysAllocString(psz);
        LoadString(g_hInst, idsException, psz, 1024);
        pExcepInfo->bstrDescription=SysAllocString(psz);
       #endif
        }

    free(psz);
    return hr;
    }
