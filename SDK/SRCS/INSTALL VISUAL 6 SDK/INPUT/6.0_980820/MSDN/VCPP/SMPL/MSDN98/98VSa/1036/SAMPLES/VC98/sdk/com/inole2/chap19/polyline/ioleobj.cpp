/*
 * IOLEOBJ.CPP
 * Polyline Component Chapter 19
 *
 * Implementation of the IOleObject interface for Polyline.  Some of
 * these just pass through to the default handler which does default
 * implementations.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "polyline.h"


/*
 * CImpIOleObject::CImpIOleObject
 * CImpIOleObject::~CImpIOleObject
 *
 * Parameters (Constructor):
 *  pObj            PCPolyline of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleObject::CImpIOleObject(PCPolyline pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleObject::~CImpIOleObject(void)
    {
    return;
    }



/*
 * CImpIOleObject::QueryInterface
 * CImpIOleObject::AddRef
 * CImpIOleObject::Release
 *
 * Purpose:
 *  IUnknown members for CImpIOleObject object.
 */

STDMETHODIMP CImpIOleObject::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIOleObject::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleObject::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }





/*
 * CImpIOleObject::SetClientSite
 * CImpIOleObject::GetClientSite
 *
 * Purpose:
 *  Manages the IOleClientSite pointer of our container.
 */

STDMETHODIMP CImpIOleObject::SetClientSite
    (LPOLECLIENTSITE pIOleClientSite)
    {
    if (NULL!=m_pObj->m_pIOleClientSite)
        m_pObj->m_pIOleClientSite->Release();

    m_pObj->m_pIOleClientSite=pIOleClientSite;

    if (NULL!=m_pObj->m_pIOleClientSite)
        m_pObj->m_pIOleClientSite->AddRef();

    return NOERROR;
    }

STDMETHODIMP CImpIOleObject::GetClientSite(LPOLECLIENTSITE *ppSite)
    {
    //Be sure to AddRef the new pointer you are giving away.
    *ppSite=m_pObj->m_pIOleClientSite;
    m_pObj->m_pIOleClientSite->AddRef();

    return NOERROR;
    }





/*
 * CImpIOleObject::SetHostNames
 *
 * Purpose:
 *  Provides the object with names of the container application and
 *  the object in the container to use in object user interface.
 *
 * Parameters:
 *  pszApp          LPCOLESTR of the container application.
 *  pszObj          LPCOLESTR of some name that is useful in window
 *                  titles.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIOleObject::SetHostNames(LPCOLESTR pszApp
    , LPCOLESTR pszObj)
    {
    if (NULL!=m_pObj->m_hDlg)
        {
        TCHAR       szTemp[128];

       #ifdef WIN32ANSI
        char        szObj[80];
        WideCharToMultiByte(CP_ACP, 0, pszObj, -1, szObj, 80
            , NULL, NULL);
        wsprintf(szTemp, SZPOLYFRAMETITLE, szObj);
       #else
        wsprintf(szTemp, SZPOLYFRAMETITLE, pszObj);
       #endif
        SetWindowText(m_pObj->m_hDlg, szTemp);
        }

    return NOERROR;
    }





/*
 * CImpIOleObject::Close
 *
 * Purpose:
 *  Forces the object to close down its user interface and unload.
 *
 * Parameters:
 *  dwSaveOption    DWORD describing the circumstances under which
 *                  the object is being saved and closed.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::Close(DWORD dwSaveOption)
    {
    HWND        hWnd;
    BOOL        fSave=FALSE;

    hWnd=m_pObj->m_hDlg;

    //If object is dirty and we're asked to save, save it and close.
    if (OLECLOSE_SAVEIFDIRTY==dwSaveOption && m_pObj->m_fDirty)
        fSave=TRUE;

    /*
     * If asked to prompt, only do so if dirty, then if we get a
     * YES, save as usual and close.  On NO, just close.  On
     * CANCEL return OLE_E_PROMPTSAVECANCELLED.
     */
    if (OLECLOSE_PROMPTSAVE==dwSaveOption && m_pObj->m_fDirty)
        {
        TCHAR       szTitle[20];
        TCHAR       szTemp[80];
        UINT        uRet;

        lstrcpy(szTitle, m_pObj->String(IDS_CLOSECAPTION));
        lstrcpy(szTemp, m_pObj->String(IDS_CLOSEPROMPT));

        uRet=MessageBox(hWnd, szTemp, szTitle, MB_YESNOCANCEL);

        if (IDCANCEL==uRet)
            return ResultFromScode(OLE_E_PROMPTSAVECANCELLED);

        if (IDYES==uRet)
            fSave=TRUE;
        }

    if (fSave)
        {
        m_pObj->SendAdvise(OBJECTCODE_SAVEOBJECT);
        m_pObj->SendAdvise(OBJECTCODE_SAVED);
        }

    //We get directly here on OLECLOSE_NOSAVE.
    if (NULL!=hWnd)
        {
        //This hides the window and sends the appropriate notify.
        DoVerb(OLEIVERB_HIDE, NULL, NULL, -1, NULL, NULL);

        m_pObj->SendAdvise(OBJECTCODE_CLOSED);
        PostMessage(hWnd, POLYM_CLOSE, 0, 0L);
        }

    return NOERROR;
    }




/*
 * CImpIOleObject::DoVerb
 *
 * Purpose:
 *  Executes an object-defined action.
 *
 * Parameters:
 *  iVerb           LONG index of the verb to execute.
 *  pMSG            LPMSG describing the event causing the
 *                  activation.
 *  pActiveSite     LPOLECLIENTSITE to the site involved.
 *  lIndex          LONG the piece on which execution is happening.
 *  hWndParent      HWND of the window in which the object can play
 *                  in-place.
 *  pRectPos        LPRECT of the object in hWndParent where the
 *                  object can play in-place if desired.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::DoVerb(LONG iVerb, LPMSG pMSG
    , LPOLECLIENTSITE pActiveSite, LONG lIndex, HWND hWndParent
    , LPCRECT pRectPos)
    {
    HRESULT     hr;

    switch (iVerb)
        {
        case OLEIVERB_HIDE:
            if (NULL!=m_pObj->m_hDlg)
                {
                ShowWindow(m_pObj->m_hDlg, SW_HIDE);
                m_pObj->SendAdvise(OBJECTCODE_HIDEWINDOW);
                }

            break;

        case OLEIVERB_PRIMARY:
        case OLEIVERB_OPEN:
        case OLEIVERB_SHOW:
            /*
             * If we're not running, make sure we are.  In any
             * case, make the dialog visible and insure it has
             * the right parent now.
             */
            hr=NOERROR;
            if (NULL==m_pObj->m_hDlg)
                hr=m_pObj->m_pImpIRunnableObject->Run(NULL);

            if (FAILED(hr) || NULL==m_pObj->m_hDlg)
                return ResultFromScode(E_OUTOFMEMORY);

            ShowWindow(m_pObj->m_hDlg, SW_SHOW);
            SetFocus(m_pObj->m_hDlg);
            m_pObj->SendAdvise(OBJECTCODE_SHOWOBJECT);
            m_pObj->SendAdvise(OBJECTCODE_SHOWWINDOW);

            break;

        default:
            return ResultFromScode(OLEOBJ_S_INVALIDVERB);
        }

    return NOERROR;
    }






/*
 * CImpIOleObject::GetUserClassID
 *
 * Purpose:
 *  Used for linked objects, this returns the class ID of what end
 *  users think they are editing.
 *
 * Parameters:
 *  pClsID          LPCLSID in which to store the CLSID.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::GetUserClassID(LPCLSID pClsID)
    {
    /*
     * If you are not registered to handle data other than yourself,
     * then you can just return your class ID here.  If you are
     * registered as usable from Treat-As dialogs, then you need to
     * return the CLSID of what you are really editing.
     */

    *pClsID=CLSID_Polyline19;
    return NOERROR;
    }





/*
 * CImpIOleObject::SetExtent
 *
 * Purpose:
 *  Sets the size of the object in HIMETRIC units.  Since we're in
 *  a dialog, the size of the object in us is fixed, so we ignore
 *  this call.
 *
 * Parameters:
 *  dwAspect        DWORD of the aspect affected.
 *  pszl            LPSIZEL containing the new size.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::SetExtent(DWORD dwAspect
    , LPSIZEL pszl)
    {
    //Ignored:  no size change in the dialog.
    return NOERROR;
    }





/*
 * CImpIOleObject::GetExtent
 *
 * Purpose:
 *  Retrieves the size of the object in HIMETRIC units.
 *
 * Parameters:
 *  dwAspect        DWORD of the aspect requested
 *  pszl            LPSIZEL into which to store the size.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::GetExtent(DWORD dwAspect, LPSIZEL pszl)
    {
    //Delegate directly to IViewObject2::GetExtent
    return m_pObj->m_pImpIViewObject->GetExtent(dwAspect, -1
        , NULL, pszl);
    }





/*
 * CImpIOleObject::Advise
 * CImpIOleObject::Unadvise
 * CImpIOleObject::EnumAdvise
 *
 * Purpose:
 *  Advisory connection functions.
 */

STDMETHODIMP CImpIOleObject::Advise(LPADVISESINK pIAdviseSink
    , LPDWORD pdwConn)
    {
    if (NULL==m_pObj->m_pIOleAdviseHolder)
        {
        HRESULT     hr;

        hr=CreateOleAdviseHolder(&m_pObj->m_pIOleAdviseHolder);

        if (FAILED(hr))
            return hr;
        }

    return m_pObj->m_pIOleAdviseHolder->Advise(pIAdviseSink
        , pdwConn);
    }


STDMETHODIMP CImpIOleObject::Unadvise(DWORD dwConn)
    {
    if (NULL!=m_pObj->m_pIOleAdviseHolder)
        return m_pObj->m_pIOleAdviseHolder->Unadvise(dwConn);

    return ResultFromScode(E_FAIL);
    }


STDMETHODIMP CImpIOleObject::EnumAdvise(LPENUMSTATDATA *ppEnum)
    {
    if (NULL!=m_pObj->m_pIOleAdviseHolder)
        return m_pObj->m_pIOleAdviseHolder->EnumAdvise(ppEnum);

    return ResultFromScode(E_FAIL);
    }






//Methods not implemented or trivial

STDMETHODIMP CImpIOleObject::SetMoniker(DWORD dwWhich
    , LPMONIKER pmk)
    {
    return ResultFromScode(E_NOTIMPL);
    }

STDMETHODIMP CImpIOleObject::GetMoniker(DWORD dwAssign
    , DWORD dwWhich, LPMONIKER *ppmk)
    {
    return ResultFromScode(E_NOTIMPL);
    }

STDMETHODIMP CImpIOleObject::InitFromData(LPDATAOBJECT pIDataObject
    , BOOL fCreation, DWORD dw)
    {
    return ResultFromScode(E_NOTIMPL);
    }

STDMETHODIMP CImpIOleObject::GetClipboardData(DWORD dwReserved
    , LPDATAOBJECT *ppIDataObj)
    {
    return ResultFromScode(E_NOTIMPL);
    }

STDMETHODIMP CImpIOleObject::Update(void)
    {
    return NOERROR;
    }

STDMETHODIMP CImpIOleObject::IsUpToDate(void)
    {
    return NOERROR;
    }

STDMETHODIMP CImpIOleObject::SetColorScheme(LPLOGPALETTE pLP)
    {
    return ResultFromScode(E_NOTIMPL);
    }



//Methods implemented using registry helper functions in OLE.

STDMETHODIMP CImpIOleObject::EnumVerbs(LPENUMOLEVERB *ppEnum)
    {
    return OleRegEnumVerbs(m_pObj->m_clsID, ppEnum);
    }

STDMETHODIMP CImpIOleObject::GetUserType(DWORD dwForm
    , LPOLESTR *ppszType)
    {
    return OleRegGetUserType(m_pObj->m_clsID, dwForm, ppszType);
    }

STDMETHODIMP CImpIOleObject::GetMiscStatus(DWORD dwAspect
    , LPDWORD pdwStatus)
    {
    return OleRegGetMiscStatus(m_pObj->m_clsID, dwAspect
        , pdwStatus);
    }
