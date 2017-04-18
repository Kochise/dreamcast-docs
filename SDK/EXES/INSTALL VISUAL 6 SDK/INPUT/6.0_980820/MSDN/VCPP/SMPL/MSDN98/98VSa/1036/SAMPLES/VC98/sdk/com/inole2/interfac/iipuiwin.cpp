/*
 * IIPUIWIN.CPP
 *
 * Template IOleInPlaceUIWIndow interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iipuiwin.h"


/*
 * CImpIOleInPlaceUIWindow::CImpIOleInPlaceUIWindow
 * CImpIOleInPlaceUIWindow::~CImpIOleInPlaceUIWindow
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleInPlaceUIWindow::CImpIOleInPlaceUIWindow(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleInPlaceUIWindow::~CImpIOleInPlaceUIWindow(void)
    {
    return;
    }



/*
 * CImpIOleInPlaceUIWindow::QueryInterface
 * CImpIOleInPlaceUIWindow::AddRef
 * CImpIOleInPlaceUIWindow::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIOleInPlaceUIWindow.
 */

STDMETHODIMP CImpIOleInPlaceUIWindow::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIOleInPlaceUIWindow::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleInPlaceUIWindow::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIOleInPlaceUIWindow::GetWindow
 *
 * Purpose:
 *  Retrieves the handle of the window associated with the object
 *  on which this interface is implemented.
 *
 * Parameters:
 *  phWnd           HWND * in which to store the window handle.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, E_FAIL if no window.
 */

STDMETHODIMP CImpIOleInPlaceUIWindow::GetWindow(HWND *phWnd)
    {
    return ResultFromScode(E_FAIL);
    }




/*
 * CImpIOleInPlaceUIWindow::ContextSensitiveHelp
 *
 * Purpose:
 *  Instructs the object on which this interface is implemented to
 *  enter or leave a context-sensitive help mode.
 *
 * Parameters:
 *  fEnterMode      BOOL TRUE to enter the mode, FALSE otherwise.
 */

STDMETHODIMP CImpIOleInPlaceUIWindow::ContextSensitiveHelp(
    BOOL fEnterMode)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceUIWindow::GetBorder
 *
 * Purpose:
 *  Returns the rectangle in which the container is willing to
 *  negotiate about an object's adornments.
 *
 * Parameters:
 *  prcBorder       LPRECT in which to store the rectangle.
 *
 * Return Value:
 *  HRESULT         NOERROR if all is well, INPLACE_E_NOTOOLSPACE
 *                  if there is no negotiable space.
 */

STDMETHODIMP CImpIOleInPlaceUIWindow::GetBorder(LPRECT prcBorder)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceUIWindow::RequestBorderSpace
 *
 * Purpose:
 *  Asks the container if it can surrender the amount of space
 *  in pBW that the object would like for it's adornments.  The
 *  container does nothing but validate the spaces on this call.
 *
 * Parameters:
 *  pBW             LPCBORDERWIDTHS containing the requested space.
 *                  The values are the amount of space requested
 *                  from each side of the relevant window.
 *
 * Return Value:
 *  HRESULT         NOERROR if we can give up space,
 *                  INPLACE_E_NOTOOLSPACE otherwise.
 */

STDMETHODIMP CImpIOleInPlaceUIWindow::RequestBorderSpace(
    LPCBORDERWIDTHS pBW)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceUIWindow::SetBorderSpace
 *
 * Purpose:
 *  Called when the object now officially requests that the
 *  container surrender border space it previously allowed in
 *  RequestBorderSpace.  The container should resize windows
 *  appropriately to surrender this space.
 *
 * Parameters:
 *  pBW             LPCBORDERWIDTHS containing the amount of space
 *                  from each side of the relevant window that the
 *                  object is now reserving.
 */

STDMETHODIMP CImpIOleInPlaceUIWindow::SetBorderSpace(
    LPCBORDERWIDTHS pBW)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceUIWindow::SetActiveObject
 *
 * Purpose:
 *  Provides the container with the object's IOleInPlaceActiveObject
 *  pointer and a name of the object to show in the container's
 *  caption.
 *
 * Parameters:
 *  pIIPActiveObj   LPOLEINPLACEACTIVEOBJECT of interest.
 *  pszObj          LPCOLESTR to use in the container's caption bar.
 */

STDMETHODIMP CImpIOleInPlaceUIWindow::SetActiveObject(
    LPOLEINPLACEACTIVEOBJECT pIIPActiveObj, LPCOLESTR pszObj)
    {
    return NOERROR;
    }
