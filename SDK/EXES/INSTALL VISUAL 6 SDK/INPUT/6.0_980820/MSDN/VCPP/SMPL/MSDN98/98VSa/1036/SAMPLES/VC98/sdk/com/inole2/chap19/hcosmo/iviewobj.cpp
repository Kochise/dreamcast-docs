/*
 * IVIEWOBJ.CPP
 * Cosmo Handler Chapter 19
 *
 * Implementation of the IViewObject2 interface for Cosmo Handler.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "hcosmo.h"


/*
 * CImpIViewObject2::CImpIViewObject2
 * CImpIViewObject2::~CImpIViewObject2
 *
 * Parameters (Constructor):
 *  pObj            PCFigure of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIViewObject2::CImpIViewObject2(PCFigure pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIViewObject2::~CImpIViewObject2(void)
    {
    return;
    }




/*
 * CImpIViewObject2::QueryInterface
 * CImpIViewObject2::AddRef
 * CImpIViewObject2::Release
 */

STDMETHODIMP CImpIViewObject2::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIViewObject2::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIViewObject2::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIViewObject2::Draw
 *
 * Purpose:
 *  Draws the object on the given hDC specifically for the requested
 *  aspect, device, and within the appropriate bounds.
 *
 * Parameters:
 *  dwAspect        DWORD aspect to draw.
 *  lindex          LONG index of the piece to draw.
 *  pvAspect        LPVOID for extra information, always NULL.
 *  ptd             DVTARGETDEVICE * containing device
 *                  information.
 *  hICDev          HDC containing the IC for the device.
 *  hDC             HDC on which to draw.
 *  pRectBounds     LPCRECTL describing the rectangle in which to
 *                  draw.
 *  pRectWBounds    LPCRECTL describing the placement rectangle if
 *                  part of what you draw is another metafile.
 *  pfnContinue     Function to call periodically during long
 *                  repaints.
 *  dwContinue      DWORD extra information for pfnContinue.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIViewObject2::Draw(DWORD dwAspect, LONG lindex
    , void *pvAspect, DVTARGETDEVICE *ptd, HDC hICDev
    , HDC hDC, LPCRECTL pRectBounds, LPCRECTL pRectWBounds
    , BOOL (CALLBACK *pfnContinue) (DWORD), DWORD dwContinue)
    {
    RECT            rc;
    POLYLINEDATA    pl;
    PPOLYLINEDATA   ppl=&m_pObj->m_pl;

    RECTFROMRECTL(rc, *pRectBounds);

    //Delegate iconic and printed representations.
    if (!((DVASPECT_CONTENT | DVASPECT_THUMBNAIL) & dwAspect))
        {
        return m_pObj->m_pDefIViewObject2->Draw(dwAspect, lindex
            , pvAspect, ptd, hICDev, hDC, pRectBounds, pRectWBounds
            , pfnContinue, dwContinue);
        }


    /*
     * If we're asked to draw a frozen aspect, use the data from
     * a copy we made in IViewObject2::Freeze.  Otherwise use the
     * current data.
     */
    if (dwAspect & m_pObj->m_dwFrozenAspects)
        {
        //Point to the data to actually use.
        if (DVASPECT_CONTENT==dwAspect)
            ppl=&m_pObj->m_plContent;
        else
            ppl=&m_pObj->m_plThumbnail;
        }


    //Make a copy so we can modify it
    memcpy(&pl, ppl, CBPOLYLINEDATA);

    /*
     * If we're going to a printer, check if it's color capable.
     * if not, then use black on white for this figure.
     */
    if (NULL!=hICDev)
        {
        if (GetDeviceCaps(hICDev, NUMCOLORS) <= 2)
            {
            pl.rgbBackground=RGB(255, 255, 255);
            pl.rgbLine=RGB(0, 0, 0);
            }
        }

    m_pObj->Draw(hDC, &rc, dwAspect, ptd, hICDev, &pl);
    return NOERROR;
    }




/*
 * CImpIViewObject2::GetColorSet
 *
 * Purpose:
 *
 * Parameters:
 *  dwAspect        DWORD aspect of interest.
 *  lindex          LONG piece of interest.
 *  pvAspect        LPVOID containing extra information, always
 *                  NULL.
 *  ptd             DVTARGETDEVICE * containing device
 *                  information.
 *  hICDev          HDC containing the IC for the device.
 *  ppColorSet      LPLOGPALETTE * into which to return the
 *                  pointer to the palette in this color set.
 *
 * Return Value:
 *  HRESULT         NOERROR on success, S_FALSE if not supported.
 */

STDMETHODIMP CImpIViewObject2::GetColorSet(DWORD dwDrawAspect
    , LONG lindex, LPVOID pvAspect, DVTARGETDEVICE *ptd
    , HDC hICDev, LPLOGPALETTE *ppColorSet)
    {
    return ResultFromScode(S_FALSE);
    }






/*
 * CImpIViewObject2::Freeze
 *
 * Purpose:
 *  Freezes the view of a particular aspect such that data changes
 *  do not affect the view.
 *
 * Parameters:
 *  dwAspect        DWORD aspect to freeze.
 *  lindex          LONG piece index under consideration.
 *  pvAspect        LPVOID for further information, always NULL.
 *  pdwFreeze       LPDWORD in which to return the key.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIViewObject2::Freeze(DWORD dwAspect, LONG lindex
    , LPVOID pvAspect, LPDWORD pdwFreeze)
    {
    //Delegate any aspect we don't handle.
    if (!((DVASPECT_CONTENT | DVASPECT_THUMBNAIL) & dwAspect))
        {
        return m_pObj->m_pDefIViewObject2->Freeze(dwAspect, lindex
            , pvAspect, pdwFreeze);
        }

    if (dwAspect & m_pObj->m_dwFrozenAspects)
        {
        *pdwFreeze=dwAspect + FREEZE_KEY_OFFSET;
        return ResultFromScode(VIEW_S_ALREADY_FROZEN);
        }

    m_pObj->m_dwFrozenAspects |= dwAspect;


    /*
     * For whatever aspects become frozen, make a copy of the data.
     * Later when drawing, if such a frozen aspect is requested,
     * we'll draw from this data rather than from our current data.
     */
    if (DVASPECT_CONTENT & dwAspect)
        {
        memcpy(&m_pObj->m_plContent, &m_pObj->m_pl
            , CBPOLYLINEDATA);
        }

    if (DVASPECT_THUMBNAIL & dwAspect)
        {
        memcpy(&m_pObj->m_plThumbnail, &m_pObj->m_pl
            , CBPOLYLINEDATA);
        }

    if (NULL!=pdwFreeze)
        *pdwFreeze=dwAspect + FREEZE_KEY_OFFSET;

    return NOERROR;
    }






/*
 * CImpIViewObject2::Unfreeze
 *
 * Purpose:
 *  Thaws an aspect frozen in Freeze.  We expect that a container
 *  will redraw us after freezing if necessary, so we don't send
 *  any sort of notification here.
 *
 * Parameters:
 *  dwFreeze        DWORD key returned from Freeze.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIViewObject2::Unfreeze(DWORD dwFreeze)
    {
    DWORD       dwAspect=dwFreeze - FREEZE_KEY_OFFSET;

    //Delegate any aspect we don't handle.
    if (!((DVASPECT_CONTENT | DVASPECT_THUMBNAIL) & dwAspect))
        return m_pObj->m_pDefIViewObject2->Unfreeze(dwFreeze);

    //The aspect to unfreeze is in the key.
    m_pObj->m_dwFrozenAspects &= ~(dwAspect);

    /*
     * Since we always kept our current data up to date, we don't
     * have to do anything here like requesting data again.
     * Because we removed dwAspect from m_dwFrozenAspects, Draw
     * will again use the current data.
     */

    return NOERROR;
    }





/*
 * CImpIViewObject2::SetAdvise
 *
 * Purpose:
 *  Provides an advise sink to the view object enabling
 *  notifications for a specific aspect.
 *
 * Parameters:
 *  dwAspects       DWORD describing the aspects of interest.
 *  dwAdvf          DWORD containing advise flags.
 *  pIAdviseSink    LPADVISESINK to notify.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIViewObject2::SetAdvise(DWORD dwAspects
    , DWORD dwAdvf, LPADVISESINK pIAdviseSink)
    {
    //Pass anything we don't support on through
    if (!((DVASPECT_CONTENT | DVASPECT_THUMBNAIL) & dwAspects))
        {
        return m_pObj->m_pDefIViewObject2->SetAdvise(dwAspects
            , dwAdvf, pIAdviseSink);
        }

    if (NULL!=m_pObj->m_pIAdvSinkView)
        m_pObj->m_pIAdvSinkView->Release();

    m_pObj->m_dwAdviseAspects=dwAspects;
    m_pObj->m_dwAdviseFlags=dwAdvf;

    m_pObj->m_pIAdvSinkView=pIAdviseSink;

    if (NULL!=m_pObj->m_pIAdvSinkView)
        m_pObj->m_pIAdvSinkView->AddRef();

    return NOERROR;
    }




/*
 * CImpIViewObject2::GetAdvise
 *
 * Purpose:
 *  Returns the last known IAdviseSink seen by SetAdvise.
 *
 * Parameters:
 *  pdwAspects      LPDWORD in which to store the last requested
 *                  aspects.
 *  pdwAdvf         LPDWORD in which to store the last requested
 *                  flags.
 *  ppIAdvSink      LPADVISESINK * in which to store the
 *                  IAdviseSink.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIViewObject2::GetAdvise(LPDWORD pdwAspects
    , LPDWORD pdwAdvf, LPADVISESINK *ppAdvSink)
    {
    if (NULL==m_pObj->m_pIAdvSinkView)
        {
        return m_pObj->m_pDefIViewObject2->GetAdvise(pdwAspects
            , pdwAdvf, ppAdvSink);
        }

    if (NULL==ppAdvSink)
        return ResultFromScode(E_INVALIDARG);
    else
        {
        *ppAdvSink=m_pObj->m_pIAdvSinkView;
        m_pObj->m_pIAdvSinkView->AddRef();
        }

    if (NULL!=pdwAspects)
        *pdwAspects=m_pObj->m_dwAdviseAspects;

    if (NULL!=pdwAdvf)
        *pdwAdvf=m_pObj->m_dwAdviseFlags;

    return NOERROR;
    }




/*
 * CImpIViewObject2::GetExtent
 *
 * Purpose:
 *  Retrieves the extents of the object's display.
 *
 * Parameters:
 *  dwAspect        DWORD of the aspect of interest.
 *  lindex          LONG index of the piece of interest.
 *  ptd             DVTARGETDEVICE * with device information.
 *  pszl            LPSIZEL to the structure in which to return
 *                  the extents.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIViewObject2::GetExtent(DWORD dwAspect, LONG lindex
    , DVTARGETDEVICE *ptd, LPSIZEL pszl)
    {
    HDC         hDC;
    int         iXppli, iYppli;
    RECT        rc;

    /*
     * We can answer for CONTENT/THUMBNAIL, but try the server for
     * others. In addition, always delegate is the server is running
     * since it has a window to define the size.
     */
    if (!((DVASPECT_CONTENT | DVASPECT_THUMBNAIL) & dwAspect)
        || OleIsRunning(m_pObj->m_pDefIOleObject))
        return m_pObj->m_pDefIOleObject->GetExtent(dwAspect, pszl);

    /*
     * The size is in the rc field of the POLYLINEDATA structure
     * which we now have to convert to HIMETRIC.
     */

    hDC=GetDC(NULL);
    iXppli=GetDeviceCaps(hDC, LOGPIXELSX);
    iYppli=GetDeviceCaps(hDC, LOGPIXELSY);

    RECTSTORECT(m_pObj->m_pl.rc, rc);
    pszl->cx=(long)MulDiv(HIMETRIC_PER_INCH
        , (rc.right-rc.left), iXppli);

    pszl->cy=(long)MulDiv(HIMETRIC_PER_INCH
        , (rc.bottom-rc.top), iYppli);

    ReleaseDC(NULL, hDC);
    return NOERROR;
    }
