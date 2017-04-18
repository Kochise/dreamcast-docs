/*
 * POLYLINE.CPP
 * Polyline Component Chapter 21
 *
 * Implementation of the CPolyline class that we expose as a
 * component object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "polyline.h"


/*
 * CPolyline:CPolyline
 * CPolyline::~CPolyline
 *
 * Constructor Parameters:
 *  pUnkOuter       LPUNKNOWN of the controlling unknown.
 *  pfnDestroy      PFNDESTROYED to call when an object is
 *                  destroyed.
 *  hInst           HINSTANCE of the application we're in.
 */

CPolyline::CPolyline(LPUNKNOWN pUnkOuter, PFNDESTROYED pfnDestroy
    , HINSTANCE hInst)
    {
    m_hWnd=NULL;
    m_hInst=hInst;

    m_cRef=0;
    m_pUnkOuter=pUnkOuter;
    m_pfnDestroy=pfnDestroy;
    m_fDirty=FALSE;

    m_pImpIPolyline=NULL;
    m_pImpIConnPtCont=NULL;

    m_pAdv=NULL;
    m_pConnPt=NULL;

    m_pST  =NULL;
    m_cf   =0;
    m_clsID=CLSID_Polyline19;

    m_pIStorage=NULL;
    m_pIStream =NULL;

    m_pImpIPersistStorage=NULL;
    m_pImpIPersistStreamInit=NULL;

    m_pImpIDataObject   =NULL;
    m_pIDataAdviseHolder=NULL;

    m_pDefIUnknown       =NULL;
    m_pDefIDataObject    =NULL;
    m_pDefIViewObject    =NULL;
    m_pDefIPersistStorage=NULL;

    m_pIOleAdviseHolder =NULL;
    m_pImpIOleObject    =NULL;
    m_pIOleClientSite   =NULL;
    m_pImpIViewObject   =NULL;
    m_pIAdviseSink      =NULL;

    m_dwFrozenAspects   =0;
    m_dwAdviseAspects   =0;
    m_dwAdviseFlags     =0;

    m_pImpIRunnableObject=NULL;
    m_hDlg=NULL;

    //CHAPTER21MOD
    m_pImpIExternalConnection=NULL;
    m_fLockContainer=FALSE;
    m_dwRegROT=0L;
    //End CHAPTER21MOD

    return;
    }


CPolyline::~CPolyline(void)
    {
    LPUNKNOWN       pIUnknown=this;

    if (NULL!=m_pUnkOuter)
        pIUnknown=m_pUnkOuter;

    if (NULL!=m_pST)
        delete m_pST;

    if (NULL!=m_hDlg)
        DestroyWindow(m_hDlg);

    /*
     * In aggregation, release cached pointers but
     * AddRef the controlling unknown first.  The 
     * extra reference count protects from reentrancy.
     */

    m_cRef++;

    pIUnknown->AddRef();
    pIUnknown->AddRef();
    pIUnknown->AddRef();

    ReleaseInterface(m_pDefIViewObject);
    ReleaseInterface(m_pDefIDataObject);
    ReleaseInterface(m_pDefIPersistStorage);

    m_cRef--; 

    //Cached pointer rules do not apply to IUnknown
    ReleaseInterface(m_pDefIUnknown);

    ReleaseInterface(m_pIAdviseSink);

    //CHAPTER21MOD
    if (m_fLockContainer)
        {
        LPOLECONTAINER  pIOleCont;

        if (SUCCEEDED(m_pIOleClientSite
            ->GetContainer(&pIOleCont)))
            {
            pIOleCont->LockContainer(FALSE);
            pIOleCont->Release();
            }
        }
    //End CHAPTER21MOD
    ReleaseInterface(m_pIOleClientSite);
    ReleaseInterface(m_pIOleAdviseHolder);

    DeleteInterfaceImp(m_pImpIOleObject);
    DeleteInterfaceImp(m_pImpIViewObject);
    DeleteInterfaceImp(m_pImpIRunnableObject);

    //CHAPTER21MOD
    //Anything we might have registered in IRunnableObject::Run
    INOLE_RevokeAsRunning(&m_dwRegROT);

    DeleteInterfaceImp(m_pImpIExternalConnection);
    //End CHAPTERw21MOD

    ReleaseInterface(m_pIDataAdviseHolder);
    DeleteInterfaceImp(m_pImpIDataObject);

    DeleteInterfaceImp(m_pImpIPersistStreamInit);
    DeleteInterfaceImp(m_pImpIPersistStorage);
    ReleaseInterface(m_pIStream);
    ReleaseInterface(m_pIStorage);

    DeleteInterfaceImp(m_pImpIConnPtCont);
    DeleteInterfaceImp(m_pImpIPolyline);

    ReleaseInterface(m_pAdv);
    ReleaseInterface(m_pConnPt);

    return;
    }




/*
 * CPolyline::Init
 *
 * Purpose:
 *  Performs any intiailization of a CPolyline that's prone to
 *  failure that we also use internally before exposing the
 *  object outside this DLL.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CPolyline::Init(void)
    {
    LPUNKNOWN       pIUnknown=this;
    HRESULT         hr;

    if (NULL!=m_pUnkOuter)
        pIUnknown=m_pUnkOuter;

    m_pST=new CStringTable(m_hInst);

    if (!m_pST->Init(IDS_POLYLINEMIN, IDS_POLYLINEMAX))
        return FALSE;

    m_cf=RegisterClipboardFormat(SZPOLYLINECLIPFORMAT);

    m_pImpIPersistStorage=new CImpIPersistStorage(this, pIUnknown);

    if (NULL==m_pImpIPersistStorage)
        return FALSE;

    m_pImpIPersistStreamInit=new CImpIPersistStreamInit(this
        , pIUnknown);

    if (NULL==m_pImpIPersistStreamInit)
        return FALSE;

    m_pImpIPolyline=new CImpIPolyline(this, pIUnknown);

    if (NULL==m_pImpIPolyline)
        return FALSE;

    m_pImpIConnPtCont=new CImpIConnPtCont(this, pIUnknown);

    if (NULL==m_pImpIConnPtCont)
        return FALSE;

    m_pConnPt=new CConnectionPoint(this);

    if (NULL==m_pConnPt)
        return FALSE;

    m_pConnPt->AddRef();    //Reversed in destructor

    m_pImpIDataObject=new CImpIDataObject(this, pIUnknown);

    if (NULL==m_pImpIDataObject)
        return FALSE;

    m_pImpIOleObject=new CImpIOleObject(this, pIUnknown);

    if (NULL==m_pImpIOleObject)
        return FALSE;

    m_pImpIViewObject=new CImpIViewObject(this, pIUnknown);

    if (NULL==m_pImpIViewObject)
        return FALSE;

    m_pImpIRunnableObject=new CImpIRunnableObject(this, pIUnknown);

    if (NULL==m_pImpIRunnableObject)
        return FALSE;

    //CHAPTER21MOD
    m_pImpIExternalConnection=new CImpIExternalConnection(this
        , pIUnknown);

    if (NULL==m_pImpIExternalConnection)
        return FALSE;
    //End CHAPTER21MOD

    /*
     * We're sitting at ref count 0 and the next call will AddRef a
     * few times and Release a few times.  This insures we don't
     * delete ourselves prematurely.
     */
    m_cRef++;

    //Aggregate OLE's cache for IOleCache* interfaces.
    hr=CreateDataCache(pIUnknown, CLSID_Polyline19
        , IID_IUnknown, (PPVOID)&m_pDefIUnknown);

    if (FAILED(hr))
        return FALSE;

    /*
     * NOTE:  The spec specifically states that any interfaces
     * besides IUnknown that we obtain on an aggregated object
     * should be Released immediately after we QueryInterface for
     * them because the QueryInterface will AddRef us, and since
     * we would not release these interfaces until we were
     * destroyed, we'd never go away because we'd never get a zero
     * ref count.
     */

    //Now try to get other interfaces to which we delegate
    hr=m_pDefIUnknown->QueryInterface(IID_IViewObject2
        , (PPVOID)&m_pDefIViewObject);

    if (FAILED(hr))
        return FALSE;

    pIUnknown->Release();

    hr=m_pDefIUnknown->QueryInterface(IID_IDataObject
        , (PPVOID)&m_pDefIDataObject);

    if (FAILED(hr))
        return FALSE;

    pIUnknown->Release();

    hr=m_pDefIUnknown->QueryInterface(IID_IPersistStorage
        , (PPVOID)&m_pDefIPersistStorage);

    if (FAILED(hr))
        return FALSE;

    pIUnknown->Release();

    m_cRef--;
    m_pImpIPolyline->New();

    return TRUE;
    }







/*
 * CPolyline::QueryInterface
 * CPolyline::AddRef
 * CPolyline::Release
 *
 * Purpose:
 *  IUnknown members for CPolyline object.
 */

STDMETHODIMP CPolyline::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid)
        *ppv=this;

    if (IID_IConnectionPointContainer==riid)
        *ppv=m_pImpIConnPtCont;

    if (IID_IPolyline10==riid)
        *ppv=m_pImpIPolyline;

    if (IID_IPersistStorage==riid)
        *ppv=m_pImpIPersistStorage;

    if (IID_IPersist==riid || IID_IPersistStream==riid
        || IID_IPersistStreamInit==riid)
        *ppv=m_pImpIPersistStreamInit;

    if (IID_IDataObject==riid)
        *ppv=m_pImpIDataObject;

    if (IID_IOleObject==riid)
        *ppv=m_pImpIOleObject;

    if (IID_IViewObject==riid || IID_IViewObject2==riid)
        *ppv=m_pImpIViewObject;

    if (IID_IRunnableObject==riid)
        *ppv=m_pImpIRunnableObject;

    //CHAPTER21MOD
    if (IID_IExternalConnection==riid)
        *ppv=m_pImpIExternalConnection;
    //End CHAPTER21MOD

    //Use the default handler's cache.
    if (IID_IOleCache==riid || IID_IOleCache2==riid)
        return m_pDefIUnknown->QueryInterface(riid, ppv);

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CPolyline::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CPolyline::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    if (NULL!=m_pfnDestroy)
        (*m_pfnDestroy)();

    delete this;
    return 0L;
    }







/*
 * CPolyline::RectConvertMappings
 *
 * Purpose:
 *  Converts the contents of a rectangle from device (MM_TEXT) or
 *  HIMETRIC to the other.
 *
 * Parameters:
 *  pRect           LPRECT containing the rectangle to convert.
 *  fToDevice       BOOL TRUE to convert from HIMETRIC to device,
 *                  FALSE to convert device to HIMETRIC.
 *
 * Return Value:
 *  None
 */

void CPolyline::RectConvertMappings(LPRECT pRect, BOOL fToDevice)
    {
    HDC      hDC;
    int      iLpx, iLpy;

    if (NULL==pRect)
        return;

    hDC=GetDC(NULL);
    iLpx=GetDeviceCaps(hDC, LOGPIXELSX);
    iLpy=GetDeviceCaps(hDC, LOGPIXELSY);
    ReleaseDC(NULL, hDC);

    if (fToDevice)
        {
        pRect->left=MulDiv(iLpx, pRect->left, HIMETRIC_PER_INCH);
        pRect->top =MulDiv(iLpy, pRect->top , HIMETRIC_PER_INCH);

        pRect->right =MulDiv(iLpx, pRect->right, HIMETRIC_PER_INCH);
        pRect->bottom=MulDiv(iLpy, pRect->bottom,HIMETRIC_PER_INCH);
        }
    else
        {
        pRect->left=MulDiv(pRect->left, HIMETRIC_PER_INCH, iLpx);
        pRect->top =MulDiv(pRect->top , HIMETRIC_PER_INCH, iLpy);

        pRect->right =MulDiv(pRect->right, HIMETRIC_PER_INCH, iLpx);
        pRect->bottom=MulDiv(pRect->bottom,HIMETRIC_PER_INCH, iLpy);
        }

    return;
    }



/*
 * CPolyline::DataSet
 *
 * Purpose:
 *  Sets the current data in this Polyline to a given structure.
 *
 * Parameters:
 *  pplIn           PPOLYLINEDATA to initialize to.
 *  fSizeToData     BOOL indicating if we're to size to the data
 *                  or scale it.
 *  fNotify         BOOL indicating if we're to send an advise
 *                  on this change.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise a
 *                  POLYLINE_E_ value.
 */

STDMETHODIMP CPolyline::DataSet(PPOLYLINEDATA pplIn
    , BOOL fSizeToData, BOOL fNotify)
    {
    RECT            rc;

    /*
     * Copy the structure in pplIn and repaint to reflect the
     * new point set.  Note that unlike the RectSet message, we
     * do no scaling, assuming that the rect in the structure
     * is appropriate for the data.
     */

    if (NULL==pplIn)
        return ResultFromScode(POLYLINE_E_INVALIDPOINTER);

    m_pl=*pplIn;
    m_fDirty=TRUE;

    /*
     * If we're scaling the window to fit the data, then use
     * RectSet passing our current rectangle as the new one.
     * That makes sure that the data won't change but that the
     * window is resized.
     */

    if (fSizeToData)
        {
        POINT       pt;

        /*
         * Get our offset in the parent window so we can RectSet
         * to the right place since RectSet expects rectangle in
         * parent coordinates and we get it in client coordinates.
         */
        if (NULL!=m_hWnd)
            {
            GetWindowRect(m_hWnd, &rc);
            pt.x=rc.left;
            pt.y=rc.top;
            ScreenToClient(GetParent(m_hWnd), &pt);
            RECTSTORECT(m_pl.rc, rc);
            OffsetRect(&rc, pt.x, pt.y);

            //This will also cause a repaint.
            m_pImpIPolyline->RectSet(&rc, fNotify);
            }
        }
    else
        {
        if (NULL!=m_hWnd)
            {
            //Make sure we're updated.
            InvalidateRect(m_hWnd, NULL, TRUE);
            UpdateWindow(m_hWnd);
            }
        }

    SendAdvise(OBJECTCODE_DATACHANGED);
    return NOERROR;
    }







/*
 * CPolyline::DataGet
 *
 * Purpose:
 *  Retrieves the Polyline's current data.
 *
 * Parameters:
 *  pplIn           PPOLYLINEDATA into which we copy the data.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise a
 *                  POLYLINE_E_ value.
 */

STDMETHODIMP CPolyline::DataGet(PPOLYLINEDATA pplIn)
    {
    if (NULL==pplIn)
        return ResultFromScode(POLYLINE_E_INVALIDPOINTER);

    *pplIn=m_pl;
    return NOERROR;
    }






/*
 * CPolyline::RenderNative
 *
 * Purpose:
 *  Retrieves the Polyline's data in a global memory handle.
 *
 * Parameters:
 *  phMem           HGLOBAL * in which to store the handle.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise a
 *                  POLYLINE_E_ value.
 */

STDMETHODIMP CPolyline::RenderNative(HGLOBAL *phMem)
    {
    HGLOBAL         hMem;
    PPOLYLINEDATA   ppl;
    HRESULT         hr=ResultFromScode(POLYLINE_E_INVALIDPOINTER);

    if (NULL==phMem)
        return ResultFromScode(POLYLINE_E_INVALIDPOINTER);

    hMem=GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, CBPOLYLINEDATA);

    if (NULL!=hMem)
        {
        ppl=(PPOLYLINEDATA)GlobalLock(hMem);
        hr=DataGet(ppl);

        GlobalUnlock(hMem);

        if (FAILED(hr))
            {
            GlobalFree(hMem);
            hMem=NULL;
            }
        }

    *phMem=hMem;
    return hr;
    }




/*
 * CPolyline::RenderBitmap
 *
 * Purpose:
 *  Creates a bitmap image of the current Polyline.
 *
 * Parameters:
 *  phBmp           HBITMAP * in which to return the bitmap.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise a
 *                  POLYLINE_E_ value.
 */

STDMETHODIMP CPolyline::RenderBitmap(HBITMAP *phBmp)
    {
    HDC             hDC;
    HDC             hMemDC;
    HBITMAP         hBmp;
    RECT            rc;
    HGDIOBJ         hObj;

    if (NULL==phBmp)
        return ResultFromScode(POLYLINE_E_INVALIDPOINTER);

    //Render a bitmap the size of the current rectangle.
    hDC=GetDC(m_hWnd);
    hMemDC=CreateCompatibleDC(hDC);

    GetClientRect(m_hWnd, &rc);
    hBmp=CreateCompatibleBitmap(hDC, rc.right, rc.bottom);

    if (NULL!=hBmp)
        {
        //Draw the POLYLINEDATA into the bitmap.
        hObj=SelectObject(hMemDC, hBmp);
        Draw(hMemDC, FALSE, TRUE, &rc, NULL);
        SelectObject(hMemDC, hObj);
        }

    DeleteDC(hMemDC);
    ReleaseDC(m_hWnd, hDC);

    *phBmp=hBmp;
    return NOERROR;
    }



//RenderMetafile not necessary--now part of RenderMetafilePict.



/*
 * CPolyline::RenderMetafilePict
 *
 * Purpose:
 *  Renders the current Polyline into a METAFILEPICT structure in
 *  global memory.
 *
 * Parameters:
 *  phMem           HGLOBAL * in which to return the
 *                  METAFILEPICT.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise a
 *                  POLYLINE_E_ value.
 */

STDMETHODIMP CPolyline::RenderMetafilePict(HGLOBAL *phMem)
    {
    HGLOBAL         hMem;
    HMETAFILE       hMF;
    LPMETAFILEPICT  pMF;
    RECT            rc;
    HDC             hDC;

    if (NULL==phMem)
        return ResultFromScode(POLYLINE_E_INVALIDPOINTER);

    //Create a memory metafile and return its handle.
    hDC=(HDC)CreateMetaFile(NULL);

    if (NULL==hDC)
        return ResultFromScode(STG_E_MEDIUMFULL);

    SetMapMode(hDC, MM_ANISOTROPIC);
    GetClientRect(m_hWnd, &rc);
    SetWindowOrgEx(hDC, 0, 0, NULL);
    SetWindowExtEx(hDC, rc.right, rc.bottom, NULL);

    Draw(hDC, TRUE, TRUE, &rc, NULL);
    hMF=CloseMetaFile(hDC);

    if (NULL==hMF)
        return ResultFromScode(STG_E_MEDIUMFULL);

    //Allocate the METAFILEPICT structure.
    hMem=GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE
        , sizeof(METAFILEPICT));

    if (NULL==hMem)
        {
        DeleteMetaFile(hMF);
        return ResultFromScode(E_FAIL);
        }

    /*
     * Global lock only fails in PMODE if the selector is invalid
     * (like it was discarded) or references a 0 length segment,
     * neither of which can happen here.
     */
    pMF=(LPMETAFILEPICT)GlobalLock(hMem);

    pMF->hMF=hMF;
    pMF->mm=MM_ANISOTROPIC;

    //Insert the extents in MM_HIMETRIC units.
    GetClientRect(m_hWnd, &rc);
    RectConvertMappings(&rc, FALSE);
    pMF->xExt=rc.right;
    pMF->yExt=rc.bottom;

    GlobalUnlock(hMem);

    *phMem=hMem;
    return NOERROR;
    }



/*
 * CPolyline::Instance
 *
 * Purpose:
 *  Provides access to the module instance.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HINSTANCE       The instance handle of the module.
 */

HINSTANCE CPolyline::Instance(void)
    {
    return m_hInst;
    }



/*
 * CPolyline::String
 *
 * Purpose:
 *  Provides string lookup in the Polyline string table.
 *
 * Parameters:
 *  uID             UINT of the string to return.
 *
 * Return Value:
 *  LPTSTR          Pointer to the string.
 */

LPTSTR CPolyline::String(UINT uID)
    {
    return PSZ(uID);
    }




/*
 * CPolyline::SendAdvise
 *
 * Purpose:
 *  Calls the appropriate IOleClientSite or IAdviseSink member
 *  function for various events such as closure, renaming, etc.
 *
 * Parameters:
 *  uCode           UINT OBJECTCODE_* identifying the notification.
 *
 * Return Value:
 *  None
 */

void CPolyline::SendAdvise(UINT uCode)
    {
    DWORD       dwAspect=DVASPECT_CONTENT | DVASPECT_THUMBNAIL;

    switch (uCode)
        {
        case OBJECTCODE_SAVED:
            if (NULL!=m_pIOleAdviseHolder)
                m_pIOleAdviseHolder->SendOnSave();
            break;

        case OBJECTCODE_CLOSED:
            if (NULL!=m_pIOleAdviseHolder)
                m_pIOleAdviseHolder->SendOnClose();

            break;

        case OBJECTCODE_RENAMED:
            //Call IOleAdviseHolder::SendOnRename (later)
            break;

        case OBJECTCODE_SAVEOBJECT:
            if (m_fDirty && NULL!=m_pIOleClientSite)
                m_pIOleClientSite->SaveObject();

            m_fDirty=FALSE;
            break;

        case OBJECTCODE_DATACHANGED:
            m_fDirty=TRUE;

            //No flags are necessary here.
            if (NULL!=m_pIDataAdviseHolder)
                {
                m_pIDataAdviseHolder->SendOnDataChange
                    (m_pImpIDataObject, 0, 0);
                }

            if (NULL!=m_pIAdviseSink
                & (dwAspect & m_dwAdviseAspects))
                {
                m_pIAdviseSink->OnViewChange(dwAspect
                    & m_dwAdviseAspects, 0);
                }

            break;

        case OBJECTCODE_SHOWWINDOW:
            if (NULL!=m_pIOleClientSite)
                m_pIOleClientSite->OnShowWindow(TRUE);

            break;

        case OBJECTCODE_HIDEWINDOW:
            if (NULL!=m_pIOleClientSite)
                m_pIOleClientSite->OnShowWindow(FALSE);

            break;

        case OBJECTCODE_SHOWOBJECT:
            if (NULL!=m_pIOleClientSite)
                m_pIOleClientSite->ShowObject();

            break;
        }

    return;
    }
