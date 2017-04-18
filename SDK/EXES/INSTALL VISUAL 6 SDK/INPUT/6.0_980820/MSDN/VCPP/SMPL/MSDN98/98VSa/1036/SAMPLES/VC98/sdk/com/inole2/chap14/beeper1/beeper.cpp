/*
 * BEEPER.CPP
 * Beeper Automation Object #1 Chapter 14
 *
 * Implementation of the CBeeper class which demonstrate a fully
 * custom IDispatch implementation that only supports mapping of
 * names to IDs through IDispatch::GetIDsOfNames.
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
    if (NULL==m_pszScratch)
        free(m_pszScratch);

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

    //Pre-allocate scratch space for IDispatch::GetIDsOfNames
    m_pszScratch=(LPTSTR)malloc(256*sizeof(TCHAR));

    if (NULL==m_pszScratch)
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
    if (IID_IUnknown==riid)
        *ppv=this;

    /*
     * QueryInterface must respond not only to IID_IDispatch for
     * the primary automation interface, but also to the DIID of the
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

    //Inform the server about destruction so it can handle shutdown
    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0L;
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
    return;
    }

CImpIDispatch::~CImpIDispatch(void)
    {
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
    //We don't implement GetTypeInfo, so return 0
    *pctInfo=0;
    return NOERROR;
    }




/*
 * CImpIDispatch::GetTypeInfo
 *
 * Purpose:
 *  Retrieves type information for the automation interface.
 *
 * Parameters:
 *  itinfo          UINT reserved.  Must be zero.
 *  lcid            LCID providing the locale for the type
 *                  information.  If the object does not support
 *                  localization, this is ignored.
 *  pptinfo         ITypeInfo ** in which to store the ITypeInfo
 *                  interface for the object.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error code.
 */

STDMETHODIMP CImpIDispatch::GetTypeInfo(UINT itinfo, LCID lcid
    , ITypeInfo **pptInfo)
    {
    /*
     * Since we returned zero from GetTypeInfoCount, this function
     * should not be called.  If it is, be sure to NULL the pptInfo
     * pointer according to normal out-parameter rules.
     */
    *pptInfo=NULL;
    return ResultFromScode(E_NOTIMPL);
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
    int         i;
    int         idsMin;
    LPTSTR      psz;

    if (IID_NULL!=riid)
        return ResultFromScode(DISP_E_UNKNOWNINTERFACE);

    /*
     * This function will support English and German languages,
     * where in English we have a "Sound" property and "Beep"
     * method; in German these are "Ton" and "Peip" This particular
     * coding will handle either language identically, so a
     * controller using even both languages simultaneously can work
     * with this same automation object.
     *
     * To check the passed LCID, we use the PRIMARYLANGID macro
     * to check for LANG_ENGLISH and LANG_GERMAN, which means we
     * support any dialect of english (US, UK, AUS, CAN, NZ, EIRE)
     * and german (GER, SWISS, AUS).  The high byte of an LCID
     * specifies the sub-language, and the macro here strips that
     * differentiation.
     *
     * Note that LANG_NEUTRAL is considered here to be English.
     */

    //Set up idsMin to the right stringtable in our resources
    switch (PRIMARYLANGID(lcid))
        {
        case LANG_NEUTRAL:
        case LANG_ENGLISH:
            idsMin=IDS_0_NAMESMIN;
            break;

        case LANG_GERMAN:
            idsMin=IDS_7_NAMESMIN;
            break;

        default:
            return ResultFromScode(DISP_E_UNKNOWNLCID);
        }

    /*
     * The index in this loop happens to correspond to the DISPIDs
     * for each element which also matches the stringtable entry
     * ordering, where i+idsMin is the string to compare.  If we
     * find a match, i is the DISPID to return.
     */
    rgDispID[0]=DISPID_UNKNOWN;
    hr=ResultFromScode(DISP_E_UNKNOWNNAME);

    psz=m_pObj->m_pszScratch;

    for (i=0; i < CNAMES; i++)
        {
        /*
         * If we had more than one name per method or property,
         * we'd need to loop over the cNames parameter as well.
         */

        LoadString(g_hInst, idsMin+i, psz, 256);

       #ifdef WIN32ANSI
        char        szTemp[80];

        WideCharToMultiByte(CP_ACP, 0, rgszNames[0], -1
            , szTemp, 80, NULL, NULL);
        if (0==lstrcmpi(psz, szTemp))
       #else
        if (0==lstrcmpi(psz, rgszNames[0]))
       #endif
            {
            //Found a match, return the DISPID
            rgDispID[0]=i;
            hr=NOERROR;
            break;
            }
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

    //riid is supposed to be IID_NULL always
    if (IID_NULL!=riid)
        return ResultFromScode(DISP_E_UNKNOWNINTERFACE);

    /*
     * There is nothing locale-sensitive in any of our properties
     * or methods.  Some automation objects may have currency,
     * date/time, or string values in properties or methods which
     * would be sensitive to lcid; be sure the handle them properly.
     */


    /*
     * Process the invoked member or property.  For members,
     * call whatever functions are necessary to carry out the
     * action.  For properties, either return the value you have
     * or change it according to wFlags.
     *
     * This object supports one property and one method:
     *  ID 0    "Sound" property, a long that must be one of
     *          MB_OK, MB_ICONHAND, MB_ICONQUESTION,
     *          MB_ICONEXCLAMATION, and MB_ICONASTERISK.
     *  ID 1    "Beep" method, no parameters, return value of type
     *          long which is the sound that was played.
     *
     * Note that the IDs are assigned in the implementation of
     * IDispatch::GetIDsOfNames.
     */

    switch (dispID)
        {
        case PROPERTY_SOUND:
            /*
             * Some controllers might not be able to differentiate
             * between a property get and a function call, so we
             * have to handle both as a property get here.
             */
            if (DISPATCH_PROPERTYGET & wFlags
                || DISPATCH_METHOD & wFlags)
                {
                //Make sure we have a place for the result
                if (NULL==pVarResult)
                    return ResultFromScode(E_INVALIDARG);

                VariantInit(pVarResult);
                V_VT(pVarResult)=VT_I4;
                V_I4(pVarResult)=m_pObj->m_lSound;
                return NOERROR;
                }
            else
                {
                //DISPATCH_PROPERTYPUT
                long        lSound;
                int         c;
                VARIANT     vt;

                //Validate parameter count
                if (1!=pDispParams->cArgs)
                    return ResultFromScode(DISP_E_BADPARAMCOUNT);

                //Check that we have a named DISPID_PROPERTYPUT
                c=pDispParams->cNamedArgs;
                if (1!=c || (1==c && DISPID_PROPERTYPUT
                    !=pDispParams->rgdispidNamedArgs[0]))
                    return ResultFromScode(DISP_E_PARAMNOTOPTIONAL);

                /*
                 * Try to coerce the new property value into a
                 * type VT_I4.  VariantChangeType will do this for
                 * us and return an appropriate error code if the
                 * type cannot be coerced.  On error we store 0
                 * (first parameter) into puArgErr.
                 *
                 * We could also use DispGetParam here to do the
                 * same thing:
                 *   DispGetParam(pDispParams, 0, VT_I4
                 *       , &vtNew, puArgErr);
                 */
                VariantInit(&vt);
                hr=VariantChangeType(&vt, &pDispParams->rgvarg[0]
                    , 0, VT_I4);

                if (FAILED(hr))
                    {
                    if (NULL!=puArgErr)
                        *puArgErr=0;

                    return hr;
                    }

                //With the right type, now check the right value
                lSound=vt.lVal;

                if (MB_OK!=lSound && MB_ICONEXCLAMATION!=lSound
                    && MB_ICONQUESTION!=lSound && MB_ICONHAND!=lSound
                    && MB_ICONASTERISK!=lSound)
                    {
                    if (NULL==pExcepInfo)
                        return ResultFromScode(E_INVALIDARG);

                    /*
                     * This is the right place for an exception--
                     * the best we can tell the caller with a
                     * return value is something like E_INVALIDARG.
                     * But that doesn't at all indiate the problem.
                     * So we use EXCEPTION_INVALIDSOUND and the
                     * FillException callback to fill the EXCEPINFO.
                     *
                     * Note:  DispTest and Visual Basic 3 don't
                     * support deferred filling of the EXCEPINFO
                     * structure; Visual Basic 4 does.  Even if you
                     * don't use deferred filling, a separate
                     * function is still useful as you can just call
                     * it here to fill the structure immediately.
                     *
                     * Deferred fill-in code would appear:
                     *
                     *   INITEXCEPINFO(*pExcepInfo);
                     *   pExcepInfo->scode
                     *       =(SCODE)MAKELONG(EXCEPTION_INVALIDSOUND
                     *       , PRIMARYLANGID(lcid));
                     *   pExcepInfo->pfnDeferredFillIn=FillException;
                     */

                    /*
                     * So we can make a localized exception, we'll
                     * store the language ID and our exception code
                     * into the scode field; in FillException we move
                     * the code into wCode and clear scode.  Otherwise
                     * there's no way to tell FillException about
                     * the locale.
                     */

                    pExcepInfo->scode
                        =(SCODE)MAKELONG(EXCEPTION_INVALIDSOUND
                        , PRIMARYLANGID(lcid));
                    FillException(pExcepInfo);
                    return ResultFromScode(DISP_E_EXCEPTION);
                    }

                //Everything checks out:  save the new value
                m_pObj->m_lSound=lSound;
                }

            break;


        case METHOD_BEEP:
            if (!(DISPATCH_METHOD & wFlags))
                return ResultFromScode(DISP_E_MEMBERNOTFOUND);

            if (0!=pDispParams->cArgs)
                return ResultFromScode(DISP_E_BADPARAMCOUNT);

            MessageBeep((UINT)m_pObj->m_lSound);

            //The result of this method is the sound we played
            if (NULL!=pVarResult)
                {
                VariantInit(pVarResult);
                V_VT(pVarResult)=VT_I4;
                V_I4(pVarResult)=m_pObj->m_lSound;
                }

            break;

        default:
            return ResultFromScode(DISP_E_MEMBERNOTFOUND);
        }

    return NOERROR;
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

    /*
     * Parts of our implementation that raise exceptions put the
     * WORD exception code in the loword of scode and the LANGID
     * in the hiword.
     */
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

            /*
             * DispTest and Visual Basic 3 ignore the help file and
             * context ID.  A complete controller such as Visual
             * Basic 4 checks if these fields are set, and if so,
             * displays a Help button in a message box.  If Help
             * is pressed, the controller calls WinHelp with this
             * filename and context ID for complete integration.
             *
             * The sources for beeper.hlp are in
             * \inole\chap14\beephelp along with the actual help
             * file.  For this sample I assume it's on C drive.
             * Normally you'll want to read your own HELPDIR
             * registry entry from under TypeLib and prepend that
             * to the name of the help file, but since this sample
             * doesn't have a type library, that entry doesn't
             * exist so I just hard-code it.
             */
            pExcepInfo->dwHelpContext=HID_SOUND_PROPERTY_LIMITATIONS;

            //Set defaults
            pszHelp=OLETEXT("c:\\inole\\chap14\\beephelp\\beep0000.hlp");
            idsSource=IDS_0_EXCEPTIONSOURCE;
            idsException=IDS_0_EXCEPTIONINVALIDSOUND;

            //Get the localized source and exception strings
            switch (langID)
                {
                case LANG_GERMAN:
                    idsSource=IDS_7_EXCEPTIONSOURCE;
                    idsException=IDS_7_EXCEPTIONINVALIDSOUND;
                    pszHelp=OLETEXT("c:\\inole\\chap14\\beephelp\\beep0007.hlp");
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
