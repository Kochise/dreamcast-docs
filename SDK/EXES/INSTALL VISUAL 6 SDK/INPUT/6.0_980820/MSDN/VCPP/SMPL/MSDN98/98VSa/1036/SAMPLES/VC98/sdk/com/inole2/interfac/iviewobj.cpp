/*
 * IVIEWOBJ.CPP
 *
 * Template IViewObject interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iviewobj.h"


/*
 * CImpIViewObject::CImpIViewObject
 * CImpIViewObject::~CImpIViewObject
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIViewObject::CImpIViewObject(LPVOID pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIViewObject::~CImpIViewObject(void)
    {
    return;
    }




/*
 * CImpIViewObject::QueryInterface
 * CImpIViewObject::AddRef
 * CImpIViewObject::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIViewObject.
 */

STDMETHODIMP CImpIViewObject::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIViewObject::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIViewObject::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }






/*
 * CImpIViewObject::Draw
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
 *  pRectBounds     LPCRECTL describing the rectangle in which
 *                  to draw.
 *  pRectWBounds    LPCRECTL describing the placement rectangle
 *                  if part of what you draw is another metafile.
 *  pfnContinue     Function to call periodically during
 *                  long repaints.
 *  dwContinue      DWORD extra information to pass to the
 *                  pfnContinue.
 */

STDMETHODIMP CImpIViewObject::Draw(DWORD dwAspect, LONG lindex
    , void *pvAspect, DVTARGETDEVICE *ptd, HDC hICDev
    , HDC hDC, LPCRECTL pRectBounds, LPCRECTL pRectWBounds
    , BOOL (CALLBACK *pfnContinue) (DWORD), DWORD dwContinue)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIViewObject::GetColorSet
 *
 * Purpose:
 *  Retrieves the color palette used by the object.
 *
 * Parameters:
 *  dwAspect        DWORD aspect of interest.
 *  lindex          LONG piece of interest.
 *  pvAspect        LPVOID with extra information, always NULL.
 *  ptd             DVTARGETDEVICE * containing device info.
 *  hICDev          HDC containing the IC for the device.
 *  ppColorSet      LPLOGPALETTE * into which to return the
 *                  pointer to the palette in this color set.
 */

STDMETHODIMP CImpIViewObject::GetColorSet(DWORD dwDrawAspect
    , LONG lindex, LPVOID pvAspect, DVTARGETDEVICE *ptd
    , HDC hICDev, LPLOGPALETTE *ppColorSet)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIViewObject::Freeze
 *
 * Purpose:
 *  Freezes the view of a particular aspect such that data
 *  changes do not affect the view.
 *
 * Parameters:
 *  dwAspect        DWORD aspect to freeze.
 *  lindex          LONG piece index under consideration.
 *  pvAspect        LPVOID for further information, always NULL.
 *  pdwFreeze       LPDWORD in which to return the key.
 */

STDMETHODIMP CImpIViewObject::Freeze(DWORD dwAspect, LONG lindex
    , LPVOID pvAspect, LPDWORD pdwFreeze)
    {
    return ResultFromScode(E_NOTIMPL);
    }






/*
 * CImpIViewObject::Unfreeze
 *
 * Purpose:
 *  Thaws an aspect frozen in Freeze.
 *
 * Parameters:
 *  dwFreeze        DWORD key returned from Freeze.
 */

STDMETHODIMP CImpIViewObject::Unfreeze(DWORD dwFreeze)
    {
    return ResultFromScode(E_NOTIMPL);
    }





/*
 * CImpIViewObject::SetAdvise
 *
 * Purpose:
 *  Provides an advise sink to the view object enabling
 *  notifications for a specific aspect.
 *
 * Parameters:
 *  dwAspects       DWORD describing the aspects of interest.
 *  dwAdvf          DWORD containing advise flags.
 *  pIAdviseSink    LPADVISESINK to notify.
 */

STDMETHODIMP CImpIViewObject::SetAdvise(DWORD dwAspects
    , DWORD dwAdvf, LPADVISESINK pIAdviseSink)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIViewObject::GetAdvise
 *
 * Purpose:
 *  Returns the last known IAdviseSink seen by SetAdvise.
 *
 * Parameters:
 *  pdwAspects      LPDWORD in which to store the last
 *                  requested aspects.
 *  pdwAdvf         LPDWORD in which to store the last
 *                  requested flags.
 *  ppIAdvSink      LPADVISESINK * in which to store the
 *                  IAdviseSink.
 */

STDMETHODIMP CImpIViewObject::GetAdvise(DWORD *pAspects
    , DWORD *pAdvf, LPADVISESINK *ppAdvSink)
    {
    return ResultFromScode(E_NOTIMPL);
    }






