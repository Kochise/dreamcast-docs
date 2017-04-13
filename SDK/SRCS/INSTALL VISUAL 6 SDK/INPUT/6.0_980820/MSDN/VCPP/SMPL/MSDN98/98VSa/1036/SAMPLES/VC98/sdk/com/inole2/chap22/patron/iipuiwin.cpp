/*
 * IIPUIWIN.CPP
 * Patron Chapter 22
 *
 * IOleInPlaceUIWindow interface implementation for Patron's
 * documents.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CImpIOleInPlaceUIWindow::CImpIOleInPlaceUIWindow
 * CImpIOleInPlaceUIWindow::~CImpIOleInPlaceUIWindow
 *
 * Parameters (Constructor):
 *  pDoc            PCPatronDoc of the document we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleInPlaceUIWindow::CImpIOleInPlaceUIWindow(PCPatronDoc pDoc
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pDoc=pDoc;
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
 *  IUnknown members for CImpIOleInPlaceUIWindow object.
 */

STDMETHODIMP CImpIOleInPlaceUIWindow::QueryInterface(REFIID riid
    , PPVOID ppv)
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
 *  HRESULT         NOERROR if successful, E_FAIL if there is no
 *                  window.
 */

STDMETHODIMP CImpIOleInPlaceUIWindow::GetWindow(HWND *phWnd)
    {
    *phWnd=m_pDoc->m_hWnd;
    return NOERROR;
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
 *
 * Return Value:
 *  HRESULT         NOERROR or an appropriate error code.
 */

STDMETHODIMP CImpIOleInPlaceUIWindow::ContextSensitiveHelp
    (BOOL fEnterMode)
    {
   #ifdef MDI
    //Only MDI documents care
    if (NULL!=m_pDoc->m_pIOleIPActiveObject)
        {
        m_pDoc->m_pIOleIPActiveObject->ContextSensitiveHelp
           (fEnterMode);
        }
   #endif
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
 *  HRESULT         NOERROR if all is well, INPLACE_E_NOTOOLSPACE if
 *                  there is no negotiable space.
 */

STDMETHODIMP CImpIOleInPlaceUIWindow::GetBorder(LPRECT prcBorder)
    {
    if (NULL==prcBorder)
        return ResultFromScode(E_INVALIDARG);

    /*
     * All of the document window space is available for negotiation
     * since we can resize the Pages window to anything we want.  So
     * we just return the entire client rectangle here.
     */
    GetClientRect(m_pDoc->m_hWnd, prcBorder);
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

STDMETHODIMP CImpIOleInPlaceUIWindow::RequestBorderSpace
    (LPCBORDERWIDTHS pBW)
    {
    //We don't have any restrictions, so we always return NOERROR.
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
 *                  from each side of the relevant window that
 *                  the object is now reserving.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIOleInPlaceUIWindow::SetBorderSpace
    (LPCBORDERWIDTHS pBW)
    {
    RECT        rc;
    HWND        hWndDoc;
    HWND        hWndPages;
    POINT       pt1, pt2;

    if (NULL==pBW)
        return NOERROR;

    /*
     * Now we just have to resize the Pages window to make room for
     * the object's tools or resize it to occupy the full document
     * if we're reverting to normal.
     */

    hWndDoc=m_pDoc->m_hWnd;
    hWndPages=m_pDoc->m_pPG->Window();

    //Get the current offset of the Pages
    GetWindowRect(hWndPages, &rc);
    SETPOINT(pt1, rc.left, rc.top);
    SETPOINT(pt2, rc.right, rc.bottom);
    ScreenToClient(hWndDoc, &pt1);
    ScreenToClient(hWndDoc, &pt2);

    GetClientRect(hWndDoc, &rc);

    if (NULL!=pBW)
        {
        rc.left+=pBW->left;
        rc.right-=pBW->right;
        rc.top+=pBW->top;
        rc.bottom-=pBW->bottom;
        }

    //Only move Pages if necessary
    if (!(pt1.x==rc.left && pt1.y==rc.top
        && pt2.x==rc.right && pt2.y==rc.bottom))
        {
        SendMessage(hWndDoc, WM_SETREDRAW, FALSE, 0L);
        ShowWindow(hWndPages, SW_HIDE);

        m_pDoc->m_pPG->RectSet(&rc, FALSE);

        /*
         * Scroll the Pages in the opposite direction to keep
         * objects steady.
         */

        SendScrollPosition(hWndPages, WM_HSCROLL, pBW->left-pt1.x);
        SendScrollPosition(hWndPages, WM_VSCROLL, pBW->top-pt1.y);

        SendMessage(hWndDoc, WM_SETREDRAW, TRUE, 0L);
        ShowWindow(hWndPages, SW_SHOW);
        }


    return NOERROR;
    }




/*
 * CImpIOleInPlaceUIWindow::SetActiveObject
 *
 * Purpose:
 *  Provides the container with the object's IOleInPlaceActiveObject
 *  pointer.
 *
 * Parameters:
 *  pIIPActiveObj   LPOLEINPLACEACTIVEOBJECT of interest.
 *  pszObj          LPCOLESTR naming the object.  Not used.
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIOleInPlaceUIWindow::SetActiveObject(
    LPOLEINPLACEACTIVEOBJECT pIIPActiveObj, LPCOLESTR pszObj)
    {
    if (NULL!=m_pDoc->m_pIOleIPActiveObject)
        m_pDoc->m_pIOleIPActiveObject->Release();

    //NULLs m_pIOleIPActiveObject if pIIPActiveObj is NULL
    m_pDoc->m_pIOleIPActiveObject=pIIPActiveObj;

    if (NULL!=m_pDoc->m_pIOleIPActiveObject)
        m_pDoc->m_pIOleIPActiveObject->AddRef();

    return NOERROR;
    }
