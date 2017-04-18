/*
 * IIPFRAME.CPP
 *
 * Template IOleInPlaceFrame interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iipframe.h"


/*
 * CImpIOleInPlaceFrame::CImpIOleInPlaceFrame
 * CImpIOleInPlaceFrame::~CImpIOleInPlaceFrame
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleInPlaceFrame::CImpIOleInPlaceFrame(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleInPlaceFrame::~CImpIOleInPlaceFrame(void)
    {
    return;
    }



/*
 * CImpIOleInPlaceFrame::QueryInterface
 * CImpIOleInPlaceFrame::AddRef
 * CImpIOleInPlaceFrame::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIOleInPlaceFrame.
 */

STDMETHODIMP CImpIOleInPlaceFrame::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIOleInPlaceFrame::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleInPlaceFrame::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIOleInPlaceFrame::GetWindow
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

STDMETHODIMP CImpIOleInPlaceFrame::GetWindow(HWND *phWnd)
    {
    return ResultFromScode(E_FAIL);
    }




/*
 * CImpIOleInPlaceFrame::ContextSensitiveHelp
 *
 * Purpose:
 *  Instructs the object on which this interface is implemented to
 *  enter or leave a context-sensitive help mode.
 *
 * Parameters:
 *  fEnterMode      BOOL TRUE to enter the mode, FALSE otherwise.
 */

STDMETHODIMP CImpIOleInPlaceFrame::ContextSensitiveHelp(
    BOOL fEnterMode)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceFrame::GetBorder
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

STDMETHODIMP CImpIOleInPlaceFrame::GetBorder(LPRECT prcBorder)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceFrame::RequestBorderSpace
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

STDMETHODIMP CImpIOleInPlaceFrame::RequestBorderSpace(
    LPCBORDERWIDTHS pBW)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceFrame::SetBorderSpace
 *
 * Purpose:
 *  Called when the object now officially requests that the
 *  container surrender border space it previously allowed
 *  in RequestBorderSpace.  The container should resize windows
 *  appropriately to surrender this space.
 *
 * Parameters:
 *  pBW             LPCBORDERWIDTHS containing the amount of space
 *                  from each side of the relevant window that the
 *                  object is now reserving.
 */

STDMETHODIMP CImpIOleInPlaceFrame::SetBorderSpace(
    LPCBORDERWIDTHS pBW)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceFrame::SetActiveObject
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

STDMETHODIMP CImpIOleInPlaceFrame::SetActiveObject(
    LPOLEINPLACEACTIVEOBJECT pIIPActiveObj, LPCOLESTR pszObj)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceFrame::InsertMenus
 *
 * Purpose:
 *  Instructs the container to place its in-place menu items where
 *  necessary in the given menu and to fill in elements 0, 2, and 4
 *  of the OLEMENUGROUPWIDTHS array to indicate how many top-level
 *  items are in each group.
 *
 * Parameters:
 *  hMenu           HMENU in which to add popups.
 *  pMGW            LPOLEMENUGROUPWIDTHS in which to store the
 *                  width of each container menu group.
 */

STDMETHODIMP CImpIOleInPlaceFrame::InsertMenus(HMENU hMenu
    , LPOLEMENUGROUPWIDTHS pMGW)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceFrame::SetMenu
 *
 * Purpose:
 *  Instructs the container to replace whatever menu it's currently
 *  using with the given menu and to call OleSetMenuDescritor so
 *  OLE knows to whom to dispatch messages.
 *
 * Parameters:
 *  hMenu           HMENU to show.
 *  hOLEMenu        HOLEMENU to the menu descriptor.
 *  hWndObj         HWND of the active object to which messages
 *                  are dispatched.  Usually a frame window.
 */

STDMETHODIMP CImpIOleInPlaceFrame::SetMenu(HMENU hMenu
    , HOLEMENU hOLEMenu, HWND hWndObj)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceFrame::RemoveMenus
 *
 * Purpose:
 *  Asks the container to remove any menus it put into hMenu in
 *  InsertMenus.
 *
 * Parameters:
 *  hMenu           HMENU from which to remove the container's
 *                  items.
 */

STDMETHODIMP CImpIOleInPlaceFrame::RemoveMenus(HMENU hMenu)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceFrame::SetStatusText
 *
 * Purpose:
 *  Asks the container to place some text in a status line, if
 *  one exists.  If the container does not have a status line it
 *  should return E_FAIL here in which case the object could
 *  display its own.
 *
 * Parameters:
 *  pszText         LPCOLESTR to display.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, S_TRUNCATED if not all
 *                  of the text could be displayed, or E_FAIL if
 *                  the container has no status line.
 */

STDMETHODIMP CImpIOleInPlaceFrame::SetStatusText(LPCOLESTR pszText)
    {
    return ResultFromScode(E_FAIL);
    }




/*
 * CImpIOleInPlaceFrame::EnableModeless
 *
 * Purpose:
 *  Instructs the container to show or hide any modeless popup
 *  windows that it may be using.
 *
 * Parameters:
 *  fEnable         BOOL indicating to enable/show the windows
 *                  (TRUE) or to hide them (FALSE).
 */

STDMETHODIMP CImpIOleInPlaceFrame::EnableModeless(BOOL fEnable)
    {
    return NOERROR;
    }




/*
 * CImpIOleInPlaceFrame::TranslateAccelerator
 *
 * Purpose:
 *  When dealing with an in-place object from an EXE server, this
 *  is called to give the container a chance to process accelerators
 *  after the server has looked at the message.
 *
 * Parameters:
 *  pMSG            LPMSG for the container to examine.
 *  wID             WORD identifier in the container's accelerator
 *                  table (from IOleInPlaceSite::GetWindowContext)
 *                  for this message (OLE does some translation
 *                  before calling).
 *
 * Return Value:
 *  HRESULT         NOERROR if the keystroke was used,
 *                  S_FALSE otherwise.
 */

STDMETHODIMP CImpIOleInPlaceFrame::TranslateAccelerator(LPMSG pMSG
    , WORD wID)
    {
    return ResultFromScode(S_FALSE);
    }
