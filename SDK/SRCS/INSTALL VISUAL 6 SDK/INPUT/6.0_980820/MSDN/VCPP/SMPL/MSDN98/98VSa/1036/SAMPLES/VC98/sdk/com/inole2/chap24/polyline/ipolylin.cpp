/*
 * IPOLYLIN.CPP
 * Polyline Component Chapter 24
 *
 * Implementation of the IPolyline10 interface that we expose on the
 * CPolyline object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "polyline.h"


/*
 * CImpIPolyline:CImpIPolyline
 * CImpIPolyline::~CImpIPolyline
 *
 * Constructor Parameters:
 *  pObj            PCPolyline pointing to the object we live in.
 *  pUnkOuter       LPUNKNOWN of the controlling unknown.
 */

CImpIPolyline::CImpIPolyline(PCPolyline pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }


CImpIPolyline::~CImpIPolyline(void)
    {
    return;
    }




/*
 * CImpIPolyline::QueryInterface
 * CImpIPolyline::AddRef
 * CImpIPolyline::Release
 */

STDMETHODIMP CImpIPolyline::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPolyline::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPolyline::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }





/*
 * CImpIPolyline::Init
 *
 * Purpose:
 *  Instantiates a polyline window within a given parent.  The
 *  parent may be a main application window, could be an MDI child
 *  window. We really do not care.
 *
 * Parameters:
 *  hWndParent      HWND of the parent of this window
 *  pRect           LPRECT that this window should occupy
 *  dwStyle         DWORD containing the window's style flags
 *  uID             UINT ID to associate with this window
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise E_OUTOFMEMORY
 */

STDMETHODIMP CImpIPolyline::Init(HWND hWndParent, LPRECT pRect
    , DWORD dwStyle, UINT uID)
    {
    SCODE           sc;

    m_pObj->m_hWnd=CreateWindowEx(WS_EX_NOPARENTNOTIFY
        , SZCLASSPOLYLINE, SZCLASSPOLYLINE, dwStyle, pRect->left
        , pRect->top, pRect->right-pRect->left
        , pRect->bottom-pRect->top, hWndParent, (HMENU)uID
        , m_pObj->m_hInst, m_pObj);

    sc=(NULL!=m_pObj->m_hWnd) ? S_OK : E_OUTOFMEMORY;
    return ResultFromScode(sc);
    }




/*
 * CImpIPolyline::New
 *
 * Purpose:
 *  Cleans out and reinitializes the data to defaults.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR always
 */

STDMETHODIMP CImpIPolyline::New(void)
    {
    PPOLYLINEDATA   ppl=&m_pObj->m_pl;
    UINT            i;
    RECT            rc;

    ppl->wVerMaj=VERSIONMAJOR;
    ppl->wVerMin=VERSIONMINOR;

    //Our rectangle is the size of our window's client area.
    if (NULL!=m_pObj->m_hWnd)
        {
        GetClientRect(m_pObj->m_hWnd, &rc);
        RECTTORECTS(rc, ppl->rc);
        }
    else
        {
        SetRect(&rc, 0, 0, 100, 100);       //Something reasonable
        RECTTORECTS(rc, ppl->rc);
        }

    //Clean out the POLYLINEDATA structure and repaint the window.
    for (i=0; i< CPOLYLINEPOINTS; i++)
        {
        ppl->rgpt[i].x=0;
        ppl->rgpt[i].y=0;
        }

    ppl->cPoints      =0;
    ppl->rgbBackground=GetSysColor(COLOR_WINDOW);
    ppl->rgbLine      =GetSysColor(COLOR_WINDOWTEXT);
    ppl->iLineStyle   =PS_SOLID;

    //This is now conditional since we may not yet have a window.
    if (NULL!=m_pObj->m_hWnd)
        {
        InvalidateRect(m_pObj->m_hWnd, NULL, TRUE);
        UpdateWindow(m_pObj->m_hWnd);
        m_pObj->m_fDirty=TRUE;
        }

    m_pObj->SendAdvise(OBJECTCODE_DATACHANGED);
    return NOERROR;
    }






/*
 * CImpIPolyline::Undo
 *
 * Purpose:
 *  Reverses previous actions in a Polyline.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         S_OK if we can Undo more, S_FALSE otherwise.
 */

STDMETHODIMP CImpIPolyline::Undo(void)
    {
    SCODE           sc;

    //Decrement the number of active points and repaint.
    if (m_pObj->m_pl.cPoints > 0)
        {
        m_pObj->m_pl.cPoints--;
        InvalidateRect(m_pObj->m_hWnd, NULL, TRUE);
        UpdateWindow(m_pObj->m_hWnd);
        }

    if (NULL!=m_pObj->m_pAdv)
        {
        m_pObj->m_fDirty=TRUE;
        m_pObj->m_pAdv->OnPointChange();
        }

    m_pObj->SendAdvise(OBJECTCODE_DATACHANGED);

    //Return if we can undo any more.
    sc=(0!=m_pObj->m_pl.cPoints) ? S_OK : S_FALSE;
    return ResultFromScode(sc);
    }






/*
 * CImpIPolyline::Window
 *
 * Purpose:
 *  Returns the window handle associated with this polyline.
 *
 * Parameters:
 *  phWnd           HWND * in which to return the window handle.
 *
 * Return Value:
 *  HRESULT         NOERROR always.
 */

STDMETHODIMP CImpIPolyline::Window(HWND *phWnd)
    {
    *phWnd=m_pObj->m_hWnd;
    return NOERROR;
    }






/*
 * CImpIPolyline::RectGet
 *
 * Purpose:
 *  Returns the rectangle of the Polyline in parent coordinates.
 *
 * Parameters:
 *  pRect           LPRECT in which to return the rectangle.
 *
 * Return Value:
 *  HRESULT         NOERROR always
 */

STDMETHODIMP CImpIPolyline::RectGet(LPRECT pRect)
    {
    RECT            rc;
    POINT           pt;

    if (NULL==m_pObj->m_hWnd)
        {
        SetRect(pRect, 0, 0, 150, 150); //Reasonable default
        return NOERROR;
        }

    //Retrieve the size of our rectangle in parent coordinates.
    GetWindowRect(m_pObj->m_hWnd, &rc);
    pt.x=rc.left;
    pt.y=rc.top;
    ScreenToClient(GetParent(m_pObj->m_hWnd), &pt);

    SetRect(pRect, pt.x, pt.y, pt.x+(rc.right-rc.left)
        , pt.y+(rc.bottom-rc.top));

    return NOERROR;
    }





/*
 * CImpIPolyline::SizeGet
 *
 * Purpose:
 *  Retrieves the size of the Polyline in parent coordinates.
 *
 * Parameters:
 *  pRect           LPRECT in which to return the size.  The right
 *                  and bottom fields will contain the dimensions.
 *
 * Return Value:
 *  HRESULT         NOERROR always
 */

STDMETHODIMP CImpIPolyline::SizeGet(LPRECT pRect)
    {
    RectGet(pRect);
    return NOERROR;
    }






/*
 * CImpIPolyline::RectSet
 *
 * Purpose:
 *  Sets a new rectangle for the Polyline which sizes to fit.
 *
 * Parameters:
 *  pRect           LPRECT containing the new rectangle.
 *  fNotify         BOOL indicating if we're to notify anyone of
 *                  the change.
 *
 * Return Value:
 *  HRESULT         NOERROR always
 */

STDMETHODIMP CImpIPolyline::RectSet(LPRECT pRect, BOOL fNotify)
    {
    UINT            cx, cy;
    RECT            rc;

    //Scale the points from our current size to the new size
    cx=pRect->right-pRect->left;
    cy=pRect->bottom-pRect->top;

    SetRect(&rc, 0, 0, cx, cy);
    RECTTORECTS(rc, m_pObj->m_pl.rc);

    if (NULL!=m_pObj->m_hWnd)
        {
        SetWindowPos(m_pObj->m_hWnd, NULL, pRect->left, pRect->top
            , cx, cy, SWP_NOZORDER);
        InvalidateRect(m_pObj->m_hWnd, NULL, TRUE);
        }

    if (fNotify && NULL!=m_pObj->m_pAdv)
        {
        m_pObj->m_fDirty=TRUE;
        m_pObj->m_pAdv->OnSizeChange();
        }

    return NOERROR;
    }







/*
 * CImpIPolyline::SizeSet
 *
 * Purpose:
 *  Sets a new size for the Polyline which sizes to fit.
 *
 * Parameters:
 *  pRect           LPRECT containing the new rectangle.
 *  fNotify         BOOL indicating if we're to notify anyone of
 *                  the change.
 *
 * Return Value:
 *  HRESULT         NOERROR always
 */

STDMETHODIMP CImpIPolyline::SizeSet(LPRECT pRect, BOOL fNotify)
    {
    UINT            cx, cy;

    //Scale the points from our current size to the new size
    cx=pRect->right-pRect->left;
    cy=pRect->bottom-pRect->top;

    if (NULL!=m_pObj->m_hWnd)
        {
        SetWindowPos(m_pObj->m_hWnd, NULL, 0, 0, (UINT)cx, (UINT)cy
            , SWP_NOMOVE | SWP_NOZORDER);
        InvalidateRect(m_pObj->m_hWnd, NULL, TRUE);
        }

    if (fNotify && NULL!=m_pObj->m_pAdv)
        {
        m_pObj->m_fDirty=TRUE;
        m_pObj->m_pAdv->OnSizeChange();
        }

    return NOERROR;
    }






/*
 * CImpIPolyline::ColorSet
 *
 * Purpose:
 *  Changes for background or line color in the Polyline
 *
 * Parameters:
 *  iColor          UINT index of the color to change.
 *  cr              COLORREF new color to use.
 *  pcrPrev         COLORREF * in whch to store the
 *                  previous color.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise a
 *                  POLYLINE_E_ value.
 */

STDMETHODIMP CImpIPolyline::ColorSet(UINT iColor, COLORREF cr
    , COLORREF *pcrPrev)
    {
    COLORREF        crRet;

    if (NULL==pcrPrev)
        return ResultFromScode(POLYLINE_E_INVALIDPOINTER);

    switch (iColor)
        {
        case POLYLINECOLOR_BACKGROUND:
            crRet=m_pObj->m_pl.rgbBackground;
            m_pObj->m_pl.rgbBackground=cr;
            break;

        case POLYLINECOLOR_LINE:
            crRet=m_pObj->m_pl.rgbLine;
            m_pObj->m_pl.rgbLine=cr;
            break;
        }

    //If the color changed, repaint
    if (crRet!=cr)
        {
        if (NULL!=m_pObj->m_pAdv)
            {
            m_pObj->m_fDirty=TRUE;
            m_pObj->m_pAdv->OnColorChange();
            }

        InvalidateRect(m_pObj->m_hWnd, NULL, TRUE);
        UpdateWindow(m_pObj->m_hWnd);

        m_pObj->SendAdvise(OBJECTCODE_DATACHANGED);
        }

    *pcrPrev=crRet;
    return NOERROR;
    }







/*
 * CImpIPolyline::ColorGet
 *
 * Purpose:
 *  Retrieves one of the colors currently in use by the Polyline.
 *
 * Parameters:
 *  iColor          UINT identifying the color of interest.
 *  pcr             COLORREF * in which to return the color.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise a
 *                  POLYLINE_E_ value.
 */

STDMETHODIMP CImpIPolyline::ColorGet(UINT iColor, COLORREF *pcr)
    {
    COLORREF        crRet;

    if (NULL==pcr)
        return ResultFromScode(POLYLINE_E_INVALIDPOINTER);

    crRet=(POLYLINECOLOR_BACKGROUND==iColor)
        ? m_pObj->m_pl.rgbBackground : m_pObj->m_pl.rgbLine;

    *pcr=crRet;
    return NOERROR;
    }








/*
 * CImpIPolyline::LineStyleSet
 *
 * Purpose:
 *  Changes the line style in use by the Polyline
 *
 * Parameters:
 *  iStyle          UINT style of the line to use.
 *  piPrev          UINT * in which to store the previous style.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise a
 *                  POLYLINE_E_ value.
 */

STDMETHODIMP CImpIPolyline::LineStyleSet(UINT iStyle, UINT *piPrev)
    {
    UINT            uRet;

    uRet=(UINT)m_pObj->m_pl.iLineStyle;

    if (NULL==piPrev)
        return ResultFromScode(POLYLINE_E_INVALIDPOINTER);

    //Validate the line style
    if (PS_SOLID==iStyle || PS_DASH==iStyle || PS_DOT==iStyle
        || PS_DASHDOT==iStyle || PS_DASHDOTDOT==iStyle)
        {
        m_pObj->m_pl.iLineStyle=iStyle;

        if (uRet!=(UINT)m_pObj->m_pl.iLineStyle)
            {
            if (NULL!=m_pObj->m_pAdv)
                {
                m_pObj->m_fDirty=TRUE;
                m_pObj->m_pAdv->OnLineStyleChange();
                }

            InvalidateRect(m_pObj->m_hWnd, NULL, TRUE);
            UpdateWindow(m_pObj->m_hWnd);

            m_pObj->SendAdvise(OBJECTCODE_DATACHANGED);
            }
        }

    *piPrev=uRet;
    return NOERROR;
    }







/*
 * CImpIPolyline::LineStyleGet
 *
 * Purpose:
 *  Retrieves the current line style in use in the Polyline
 *
 * Parameters:
 *  piStyle         UINT * in which to store the style.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, otherwise a
 *                  POLYLINE_E_ value.
 */

STDMETHODIMP CImpIPolyline::LineStyleGet(UINT *piStyle)
    {
    if (NULL==piStyle)
        return ResultFromScode(POLYLINE_E_INVALIDPOINTER);

    *piStyle=m_pObj->m_pl.iLineStyle;
    return NOERROR;
    }
