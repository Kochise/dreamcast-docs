/*
 * IOLEOBJ.CPP
 * Cosmo Chapter 18
 *
 * Implementation of the IOleObject interface for Polyline.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "cosmo.h"


/*
 * CImpIOleObject::CImpIOleObject
 * CImpIOleObject::~CImpIOleObject
 *
 * Parameters (Constructor):
 *  pObj            PCFigure of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleObject::CImpIOleObject(PCFigure pObj, LPUNKNOWN pUnkOuter)
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
 *
 * Purpose:
 *  Provides the object with a pointer to the IOleClient site
 *  representing the container in which this object resides.
 *
 * Parameters:
 *  pIOleClientSite LPOLECLIENTSITE to the container's interface.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIOleObject::SetClientSite
    (LPOLECLIENTSITE pIOleClientSite)
    {
    if (NULL!=m_pObj->m_pIOleClientSite)
        m_pObj->m_pIOleClientSite->Release();

    m_pObj->m_pIOleClientSite=pIOleClientSite;
    m_pObj->m_pIOleClientSite->AddRef();
    return NOERROR;
    }





/*
 * CImpIOleObject::GetClientSite
 *
 * Purpose:
 *  Asks the object for the client site provided in SetClientSite.
 *  If you have not seen SetClientSite yet, return a NULL in
 *  ppIOleClientSite.
 *
 * Parameters:
 *  ppSite          LPOLECLIENTSITE * in which to store the
 *                  pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIOleObject::GetClientSite(LPOLECLIENTSITE
    *ppSite)
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
 *  pszObj          LPCOLESTR of some name useful in window titles.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIOleObject::SetHostNames(LPCOLESTR pszApp
    , LPCOLESTR pszObj)
    {
    m_pObj->m_fEmbedded=TRUE;
   #ifdef WIN32ANSI
    char        szApp[80], szObj[80];

    szApp[0]=0;
    szObj[0]=0;

    if (NULL!=pszApp)
        {
        WideCharToMultiByte(CP_ACP, 0, pszApp, -1, szApp, 80
            , NULL, NULL);
        }

    if (NULL!=pszObj)
        {
        WideCharToMultiByte(CP_ACP, 0, pszObj, -1, szObj, 80
            , NULL, NULL);
        }

    m_pObj->m_pFR->UpdateEmbeddingUI(TRUE, m_pObj->m_pDoc
        , szApp, szObj);
   #else
    m_pObj->m_pFR->UpdateEmbeddingUI(TRUE, m_pObj->m_pDoc
        , pszApp, pszObj);
   #endif
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

    hWnd=m_pObj->m_pDoc->Window();

    //If object is dirty and we're asked to save, save it and close.
    if (OLECLOSE_SAVEIFDIRTY==dwSaveOption && m_pObj->FIsDirty())
        fSave=TRUE;

    /*
     * If asked to prompt, only do so if dirty, then if we get a
     * YES, save as usual and close.  On NO, just close.  On
     * CANCEL return OLE_E_PROMPTSAVECANCELLED.
     */
    if (OLECLOSE_PROMPTSAVE==dwSaveOption && m_pObj->FIsDirty())
        {
        UINT        uRet;

        uRet=MessageBox(hWnd, (*m_pObj->m_pST)[IDS_CLOSECAPTION]
            , (*m_pObj->m_pST)[IDS_CLOSEPROMPT], MB_YESNOCANCEL);

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
    PostMessage(hWnd, WM_CLOSE, 0, 0L);
    return NOERROR;
    }





/*
 * CImpIOleObject::SetMoniker
 *
 * Purpose:
 *  Informs the object of its moniker or its container's moniker
 *  depending on dwWhich.
 *
 * Parameters:
 *  dwWhich         DWORD describing whether the moniker is the
 *                  object's or the container's.
 *  pmk             LPMONIKER with the name.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::SetMoniker(DWORD dwWhich
    , LPMONIKER pmk)
    {
    //Uninteresting for embeddings only.
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIOleObject::GetMoniker
 *
 * Purpose:
 *  Asks the object for a moniker that can later be used to
 *  reconnect to it.
 *
 * Parameters:
 *  dwAssign        DWORD determining how to assign the moniker to
 *                  to the object.
 *  dwWhich         DWORD describing which moniker the caller wants.
 *  ppmk            LPMONIKER * into which to store the moniker.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::GetMoniker(DWORD dwAssign
    , DWORD dwWhich, LPMONIKER * ppmk)
    {
    //Uninteresting for embeddings only.
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIOleObject::InitFromData
 *
 * Purpose:
 *  Initializes the object from the contents of a data object.
 *
 * Parameters:
 *  pIDataObject    LPDATAOBJECT containing the data.
 *  fCreation       BOOL indicating if this is part of a new
 *                  creation. If FALSE, the container is trying
 *                  to paste here.
 *  dwReserved      DWORD reserved.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::InitFromData(LPDATAOBJECT pIDataObject
    , BOOL fCreation, DWORD dwReserved)
    {
    BOOL    fRet;

    /*
     * If we get a data object here, try to paste from it.  If
     * you've written clipboard code already, this is a snap.
     * We don't really care about fCreation or not since pasting
     * in us blasts away whatever is already here.
     */
    fRet=m_pObj->m_pDoc->PasteFromData(pIDataObject);
    return fRet ? NOERROR : ResultFromScode(E_FAIL);
    }





/*
 * CImpIOleObject::GetClipboardData
 *
 * Purpose:
 *  Returns an IDataObject pointer to the caller representing what
 *  would be on the clipboard if the server did an Edit/Copy using
 *  OleSetClipboard.
 *
 * Parameters:
 *  dwReserved      DWORD reserved.
 *  ppIDataObj      LPDATAOBJECT * into which to store the
 *                  pointer.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::GetClipboardData(DWORD dwReserved
    , LPDATAOBJECT *ppIDataObj)
    {
    /*
     * Again, if you have a function to create a data object for the
     * clipboard, this is a simple implementation.  The one we have
     * does all the compound document formats already.
     */
    *ppIDataObj=m_pObj->m_pDoc->TransferObjectCreate(FALSE);
    return (NULL!=*ppIDataObj) ? NOERROR : ResultFromScode(E_FAIL);
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
 *  hWndParent      HWND of window in which the object can play
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
    HWND            hWnd, hWndT;

    //Find the upper most window
    hWndT=GetParent(m_pObj->m_pDoc->Window());

    while (NULL!=hWndT)
        {
        hWnd=hWndT;
        hWndT=GetParent(hWndT);
        }

    switch (iVerb)
        {
        case OLEIVERB_HIDE:
            ShowWindow(hWnd, SW_HIDE);
            m_pObj->SendAdvise(OBJECTCODE_HIDEWINDOW);
            break;

        case OLEIVERB_PRIMARY:
        case OLEIVERB_OPEN:
        case OLEIVERB_SHOW:
            ShowWindow(hWnd, SW_SHOW);
            SetForegroundWindow(hWnd);
            SetFocus(hWnd);

            m_pObj->SendAdvise(OBJECTCODE_SHOWOBJECT);
            m_pObj->SendAdvise(OBJECTCODE_SHOWWINDOW);
            break;

        default:
            return ResultFromScode(OLEOBJ_S_INVALIDVERB);
        }

    return NOERROR;
    }





/*
 * CImpIOleObject::EnumVerbs
 *
 * Purpose:
 *  Creates an enumerator that knows the object's verbs.  If you
 *  need to change the verb list dynamically, then you'll need to
 *  implement this, otherwise you can return OLE_S_USEREG.
 *
 * Parameters:
 *  ppEnum          LPENUMOLEVERB * into which to return the
 *                  enum.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::EnumVerbs(LPENUMOLEVERB *ppEnum)
    {
    //Trivial implementation if you fill the regDB.
    return ResultFromScode(OLE_S_USEREG);
    }





/*
 * CImpIOleObject::Update
 *
 * Purpose:
 *  Insures that the object is up to date.  This is mostly used for
 *  caching but you must make sure that you recursively call all
 *  nested objects you contain as well.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::Update(void)
    {
    //We're always updated since we don't contain.
    return NOERROR;
    }





/*
 * CImpIOleObject::IsUpToDate
 *
 * Purpose:
 *  Returns if the object is currently up to date, which involves
 *  asking all contained object inside this object if they are up
 *  to date as well.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_FALSE if dirty.
 */

STDMETHODIMP CImpIOleObject::IsUpToDate(void)
    {
    //We're always updated since we don't contain.
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
     * registered as usable from Treat-As dialogs, then you need
     * to return the CLSID of what you are really editing.
     */

    *pClsID=m_pObj->m_clsID;
    return NOERROR;
    }





/*
 * CImpIOleObject::GetUserType
 *
 * Purpose:
 *  Determines the user-presentable name of the object.
 *
 * Parameters:
 *  dwForm          DWORD describing which form of the string is
 *                  desired.
 *  pszType         LPOLESTR * into which to return the pointer to
 *                  the type string.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::GetUserType(DWORD dwForm
    , LPOLESTR *ppszType)
    {
    return ResultFromScode(OLE_S_USEREG);
    }





/*
 * CImpIOleObject::SetExtent
 *
 * Purpose:
 *  Sets the size of the object in HIMETRIC units.
 *
 * Parameters:
 *  dwAspect        DWORD of the aspect affected.
 *  pszl            LPSIZEL containing the new size.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::SetExtent(DWORD dwAspect, LPSIZEL pszl)
    {
    RECT            rc;
    SIZEL           szl;

    if (!(DVASPECT_CONTENT & dwAspect))
        return ResultFromScode(E_FAIL);

    XformSizeInHimetricToPixels(NULL, pszl, &szl);

    //This resizes the window to match the container's size.
    SetRect(&rc, 0, 0, (int)szl.cx, (int)szl.cy);
    m_pObj->m_pPL->SizeSet(&rc, TRUE);

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
    RECT            rc;
    SIZEL           szl;

    if (!(DVASPECT_CONTENT & dwAspect))
        return ResultFromScode(E_FAIL);

    m_pObj->m_pPL->RectGet(&rc);
    szl.cx=rc.right-rc.left;
    szl.cy=rc.bottom-rc.top;

    XformSizeInPixelsToHimetric(NULL, &szl, pszl);
    return NOERROR;
    }





/*
 * CImpIOleObject::Advise
 *
 * Purpose:
 *  Provides an IAdviseSink to the object for notifications.
 *
 * Parameters:
 *  pIAdviseSink    LPADVISESINK to notify.
 *  pdwConn         LPDWORD into which to store a connection key.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
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





/*
 * CImpIOleObject::Unadvise
 *
 * Purpose:
 *  Terminates a previous advise connection from Advise.
 *
 * Parameters:
 *  dwConn          DWORD connection key from Advise.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::Unadvise(DWORD dwConn)
    {
    if (NULL!=m_pObj->m_pIOleAdviseHolder)
        return m_pObj->m_pIOleAdviseHolder->Unadvise(dwConn);

    return ResultFromScode(E_FAIL);
    }





/*
 * CImpIOleObject::EnumAdvise
 *
 * Purpose:
 *  Creates and returns a enumeration of the advises on this object.
 *
 * Parameters:
 *  ppEnum          LPENUMSTATDATA * in which to return the
 *                  enumerator.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::EnumAdvise(LPENUMSTATDATA *ppEnum)
    {
    if (NULL!=m_pObj->m_pIOleAdviseHolder)
        return m_pObj->m_pIOleAdviseHolder->EnumAdvise(ppEnum);

    return ResultFromScode(E_FAIL);
    }





/*
 * CImpIOleObject::GetMiscStatus
 *
 * Purpose:
 *  Returns a set of miscellaneous status flags for the object.
 *
 * Parameters:
 *  dwAspect        DWORD of the aspect in question.
 *  pdwStatus       LPDWORD in which to store the flags.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::GetMiscStatus(DWORD dwAspect
    , LPDWORD pdwStatus)
    {
    return ResultFromScode(OLE_S_USEREG);
    }





/*
 * CImpIOleObject::SetColorScheme
 *
 * Purpose:
 *  Provides the object with the color palette as recommended by
 *  the container application that also knows the palettes of other
 *  objects.  The object here is not required to use these colors.
 *
 * Parameters:
 *  pLP             LPLOGPALETTE providing the colors.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIOleObject::SetColorScheme(LPLOGPALETTE pLP)
    {
    return ResultFromScode(E_NOTIMPL);
    }
