/*
 * FIGURE.CPP
 * Cosmo Handler Chapter 19
 *
 * Implementation of the CFigure class that we expose as a
 * CosmoFigure Object in this handler.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "hcosmo.h"


/*
 * CFigure:CFigure
 * CFigure::~CFigure
 *
 * Constructor Parameters:
 *  pUnkOuter       LPUNKNOWN of the controlling unknown.
 *  pfnDestroy      PFNDESTROYED to call when object is destroyed.
 *  hInst           HINSTANCE of the application we're in.
 */

CFigure::CFigure(LPUNKNOWN pUnkOuter, PFNDESTROYED pfnDestroy
    , HINSTANCE hInst)
    {
    m_cRef=0;
    m_pUnkOuter=pUnkOuter;
    m_pfnDestroy=pfnDestroy;
    m_clsID=CLSID_CosmoFigure;

    m_cf=RegisterClipboardFormat(SZPOLYLINECLIPFORMAT);

    //NULL any contained interfaces initially.
    m_pImpIOleObject     =NULL;
    m_pImpIViewObject2   =NULL;
    m_pImpIPersistStorage=NULL;
    m_pImpIAdviseSink    =NULL;

    m_pDefIUnknown       =NULL;
    m_pDefIOleObject     =NULL;
    m_pDefIViewObject2   =NULL;
    m_pDefIPersistStorage=NULL;
    m_pDefIDataObject    =NULL;

    m_pIAdvSinkView      =NULL;
    m_dwAdviseFlags      =0;
    m_dwAdviseAspects    =0;
    m_dwFrozenAspects    =0;

    return;
    }


CFigure::~CFigure(void)
    {
    LPUNKNOWN       pIUnknown=this;

    if (NULL!=m_pUnkOuter)
        pIUnknown=m_pUnkOuter;

    /*
     * In aggregation, release cached pointers but
     * AddRef the controlling unknown first.
     */
    if (NULL!=m_pDefIOleObject)
        {
        pIUnknown->AddRef();
        m_pDefIOleObject->Release();
        }

    if (NULL!=m_pDefIViewObject2)
        {
        pIUnknown->AddRef();
        m_pDefIViewObject2->Release();
        }

    if (NULL!=m_pDefIDataObject)
        {
        pIUnknown->AddRef();
        m_pDefIDataObject->Release();
        }

    if (NULL!=m_pDefIPersistStorage)
        {
        pIUnknown->AddRef();
        m_pDefIPersistStorage->Release();
        }

    ReleaseInterface(m_pIAdvSinkView);
    ReleaseInterface(m_pDefIUnknown)

    DeleteInterfaceImp(m_pImpIAdviseSink);
    DeleteInterfaceImp(m_pImpIPersistStorage);
    DeleteInterfaceImp(m_pImpIViewObject2);
    DeleteInterfaceImp(m_pImpIOleObject);

    return;
    }




/*
 * CFigure::Init
 *
 * Purpose:
 *  Performs any intiailization of a CFigure that's prone to failure
 *  that we also use internally before exposing the object outside
 *  this DLL.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the function is successful,
 *                  FALSE otherwise.
 */

BOOL CFigure::Init(void)
    {
    LPUNKNOWN       pIUnknown=this;
    HRESULT         hr;
    DWORD           dwConn;
    FORMATETC       fe;

    if (NULL!=m_pUnkOuter)
        pIUnknown=m_pUnkOuter;

    //First create our interfaces.
    m_pImpIOleObject=new CImpIOleObject(this, pIUnknown);

    if (NULL==m_pImpIOleObject)
        return FALSE;

    m_pImpIViewObject2=new CImpIViewObject2(this, pIUnknown);

    if (NULL==m_pImpIViewObject2)
        return FALSE;

    m_pImpIPersistStorage=new CImpIPersistStorage(this, pIUnknown);

    if (NULL==m_pImpIPersistStorage)
        return FALSE;

    m_pImpIAdviseSink=new CImpIAdviseSink(this, pIUnknown);

    if (NULL==m_pImpIAdviseSink)
        return FALSE;

    /*
     * Get an IUnknown on the default handler, passing pIUnknown
     * as the controlling unknown.  The extra reference count is to
     * prevent us from going away accidentally.
     */
    m_cRef++;

    hr=OleCreateDefaultHandler(CLSID_CosmoFigure, pIUnknown
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
    hr=m_pDefIUnknown->QueryInterface(IID_IOleObject
        , (PPVOID)&m_pDefIOleObject);

    if (FAILED(hr))
        return FALSE;

    pIUnknown->Release();

    hr=m_pDefIUnknown->QueryInterface(IID_IViewObject2
        , (PPVOID)&m_pDefIViewObject2);

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

    //Set up an advise on native data so we can keep in sync
    SETDefFormatEtc(fe, m_cf, TYMED_HGLOBAL);
    m_pDefIDataObject->DAdvise(&fe, 0, m_pImpIAdviseSink, &dwConn);

    return TRUE;
    }





/*
 * CFigure::QueryInterface
 * CFigure::AddRef
 * CFigure::Release
 *
 * Purpose:
 *  IUnknown members for CFigure object.
 */

STDMETHODIMP CFigure::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    /*
     * The only calls we get here for IUnknown are either in a non-
     * aggregated case or when we're created in an aggregation, so
     * in either we always return our IUnknown for IID_IUnknown.
     */
    if (IID_IUnknown==riid)
        *ppv=this;

    if (IID_IPersist==riid || IID_IPersistStorage==riid)
        *ppv=m_pImpIPersistStorage;

    if (IID_IOleObject==riid)
        *ppv=m_pImpIOleObject;

    if (IID_IViewObject==riid || IID_IViewObject2==riid)
        *ppv=m_pImpIViewObject2;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    /*
     * Only expose default handler interfaces that you explicitly
     * know you are aggregating.  You cannot just blindly
     * delegate any other QueryInterface to the handler because
     * it may return interfaces you do not expect...such as a
     * newer version of an interface you implement in the handler.
     * We know as a handler that we must provide IDataObject,
     * IOleCache[2], IOleCacheControl, and IRunnableObject, and
     * these we get from the default handler.
     */

    if (IID_IDataObject==riid || IID_IOleCache==riid
        || IID_IOleCache2==riid || IID_IOleCacheControl==riid
        || IID_IRunnableObject==riid)
        return m_pDefIUnknown->QueryInterface(riid, ppv);

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CFigure::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CFigure::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    m_cRef++;
    delete this;
    return 0;
    }





/*
 * CFigure::Draw
 *
 * Purpose:
 *  Paints the current window to an hDC which might be a printer.
 *
 * Parameters:
 *  hDC             HDC to draw on, could be a metafile or
 *                  printer DC.
 *  pRect           LPRECT defining hDC bounds in which to draw.
 *  dwAspect        DWORD aspect to draw.
 *  ptd             DVTARGETDEVICE * containing device info.
 *  hICDev          HDC containing the IC for the device.
 *  ppl             PPOLYLINEDATA from which to draw.
 *
 * Return Value:
 *  None
 */

void CFigure::Draw(HDC hDC, LPRECT pRect, DWORD dwAspect
    , DVTARGETDEVICE *ptd, HDC hICDev, PPOLYLINEDATA ppl)
    {
    HBRUSH          hBrush;
    HPEN            hPen;
    HGDIOBJ         hObj1, hObj2;
    UINT            i, j;
    int             nDC;
    POINTS          pt1,pt2;
    POINT           rgpt[CPOLYLINEPOINTS];

    nDC=SaveDC(hDC);

    for (i=0; i < ppl->cPoints; i++)
        {
        rgpt[i].x=ppl->rgpt[i].x;
        rgpt[i].y=ppl->rgpt[i].y;
        }

    hPen=CreatePen(ppl->iLineStyle, 1, ppl->rgbLine);
    hObj1=SelectObject(hDC, hPen);

    hBrush=CreateSolidBrush(ppl->rgbBackground);
    hObj2=SelectObject(hDC, hBrush);
    SetBkColor(hDC, ppl->rgbBackground);

    //If we have one point, draw a dot to indicate it's position.
    if (1==m_pl.cPoints)
        {
        pt1.x=(short)rgpt[0].x;
        pt1.y=(short)rgpt[0].y;
        PointScale(pRect, &pt1, TRUE);
        SetPixel(hDC, pt1.x, pt1.y, m_pl.rgbLine);
        }
    else
        {
        //Erase the background for bitmaps and metafiles.
        SelectObject(hDC, GetStockObject(NULL_PEN));
        Rectangle(hDC, pRect->left, pRect->top, pRect->right+1
            , pRect->bottom+1);
        SelectObject(hDC, hPen);

        for (i=0; i < ppl->cPoints; i++)
            {
            for (j=i; j < ppl->cPoints; j++)
                {
                pt1.x=(short)rgpt[i].x;
                pt1.y=(short)rgpt[i].y;
                pt2.x=(short)rgpt[j].x;
                pt2.y=(short)rgpt[j].y;
                PointScale(pRect, &pt1, TRUE);
                PointScale(pRect, &pt2, TRUE);
                MoveToEx(hDC, pt1.x, pt1.y, NULL);
                LineTo(hDC, pt2.x, pt2.y);
                }
            }
        }

    SelectObject(hDC, hObj1);
    SelectObject(hDC, hObj2);
    DeleteObject(hBrush);
    DeleteObject(hPen);

    RestoreDC(hDC, nDC);
    return;
    }







/*
 * CFIgure::PointScale
 *
 * Purpose:
 *  Scales a point from a 0-32767 coordinate to a rectangle relative
 *  coordinate.
 *
 * Parameters:
 *  pRect           LPRECT in which to scale.
 *  ppt             LPPOINTS to convert
 *  fUnused         BOOL of no use.
 *
 * Return Value:
 *  None
 */

void CFigure::PointScale(LPRECT pRect, LPPOINTS ppt, BOOL fUnused)
    {
    DWORD   cx, cy;

    cx=(DWORD)(pRect->right-pRect->left);
    cy=(DWORD)(pRect->bottom-pRect->top);

    //Must use DWORD to insure proper scaling.
    ppt->x=pRect->left+(UINT)(((DWORD)ppt->x*cx) >> 15);
    ppt->y=pRect->top+(UINT)(((DWORD)ppt->y*cy) >> 15);

    return;
    }
