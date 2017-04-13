/*
 * IIPAOBJ.CPP
 * Polyline Component Chapter 24
 *
 * IOleInPlaceActiveObject interface implementation for Polyline
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "polyline.h"


/*
 * CImpIOleInPlaceActiveObject::CImpIOleInPlaceActiveObject
 * CImpIOleInPlaceActiveObject::~CImpIOleInPlaceActiveObject
 *
 * Parameters (Constructor):
 *  pObj            PCPolyline of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIOleInPlaceActiveObject::CImpIOleInPlaceActiveObject
    (PCPolyline pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIOleInPlaceActiveObject::~CImpIOleInPlaceActiveObject(void)
    {
    return;
    }



/*
 * CImpIOleInPlaceActiveObject::QueryInterface
 * CImpIOleInPlaceActiveObject::AddRef
 * CImpIOleInPlaceActiveObject::Release
 *
 * Purpose:
 *  IUnknown members for CImpIOleInPlaceActiveObject object.
 */

STDMETHODIMP CImpIOleInPlaceActiveObject::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    /*
     * This interface should be stand-alone on an object such that a
     * container cannot QueryInterface for it through any other
     * object interface, relying instead of calls to SetActiveObject
     * for it.  By implementing QueryInterface here ourselves, we
     * prevent such abuses.  Note that reference counting still uses
     * CFigure.
     */

    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IOleWindow==riid
        || IID_IOleInPlaceActiveObject==riid)
        *ppv=this;

    //AddRef any interface we'll return.
    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CImpIOleInPlaceActiveObject::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIOleInPlaceActiveObject::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIOleInPlaceActiveObject::GetWindow
 *
 * Purpose:
 *  Retrieves the handle of the window associated with the object on
 *  which this interface is implemented.
 *
 * Parameters:
 *  phWnd           HWND * in which to store the window handle.
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, E_FAIL if there is no
 *                  window.
 */

STDMETHODIMP CImpIOleInPlaceActiveObject::GetWindow(HWND *phWnd)
    {
    *phWnd=m_pObj->m_pHW->Window();;
    return NOERROR;
    }




/*
 * CImpIOleInPlaceActiveObject::ContextSensitiveHelp
 *
 * Purpose:
 *  Instructs the object on which this interface is implemented to
 *  enter or leave a context-sensitive help mode.
 *
 * Parameters:
 *  fEnterMode      BOOL TRUE to enter the mode, FALSE otherwise.
 *
 * Return Value:
 *  HRESULT         NOERROR or an error code.
 */

STDMETHODIMP CImpIOleInPlaceActiveObject::ContextSensitiveHelp
    (BOOL fEnterMode)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIOleInPlaceActiveObject::TranslateAccelerator
 *
 * Purpose:
 *  Requests that the active in-place object translate the message
 *  given in pMSG if appropriate.  This is only called for DLL
 *  servers where the container's message loop is running.  EXE
 *  servers have control of the message loop so this will not be
 *  called in such cases.
 *
 * Parameters:
 *  pMSG            LPMSG to the message to translate.
 *
 * Return Value:
 *  HRESULT         NOERROR if translates, S_FALSE if not.
 */

STDMETHODIMP CImpIOleInPlaceActiveObject::TranslateAccelerator
    (LPMSG pMSG)
    {
    //We have no accelerators, but this is called anyway
    return ResultFromScode(S_FALSE);
    }




/*
 * CImpIOleInPlaceActiveObject::OnFrameWindowActivate
 *
 * Purpose:
 *  Informs the in-place object that the container's frame window
 *  was either activated or deactivated.  Not currently used.
 *
 * Parameters:
 *  fActivate       BOOL TRUE if the frame is active,
 *                  FALSE otherwise
 *
 * Return Value:
 *  HRESULT         NOERROR or an error code.
 */

STDMETHODIMP CImpIOleInPlaceActiveObject::OnFrameWindowActivate
    (BOOL fActivate)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIOleInPlaceActiveObject::OnDocWindowActivate
 *
 * Purpose:
 *  Informs the in-place object that the document window in the
 *  container is either becoming active or deactive.  On this call
 *  the object must either add or remove frame-level tools,
 *  including the mixed menu, depending on fActivate.
 *
 * Parameters:
 *  fActivate       BOOL TRUE if the document is active,
 *                  FALSE otherwise
 *
 * Return Value:
 *  HRESULT         NOERROR or an error code.
 */

STDMETHODIMP CImpIOleInPlaceActiveObject::OnDocWindowActivate
    (BOOL fActivate)
    {
    if (NULL==m_pObj->m_pIOleIPFrame)
        return NOERROR;

    if (fActivate)
        {
       #ifdef WIN32ANSI
        OLECHAR     szTemp[40];

        MultiByteToWideChar(CP_ACP, 0
            , (*m_pObj->m_pST)[IDS_USERTYPE], -1, szTemp, 40);
        m_pObj->m_pIOleIPFrame->SetActiveObject(this
            , szTemp);
       #else
        m_pObj->m_pIOleIPFrame->SetActiveObject(this
            , (*m_pObj->m_pST)[IDS_USERTYPE]);
       #endif

        m_pObj->m_pIOleIPFrame->SetMenu(m_pObj->m_hMenuShared
            , m_pObj->m_hOLEMenu, m_pObj->m_hWnd);

        //Nothing to do with tools.
        }
    else
        {
        m_pObj->m_pIOleIPFrame->SetActiveObject(NULL, NULL);
        }

    return NOERROR;
    }




/*
 * CImpIOleInPlaceActiveObject::ResizeBorder
 *
 * Purpose:
 *  Informs the object that the frame or document size changed in
 *  which case the object may need to resize any of its frame or
 *  document-level tools to match.
 *
 * Parameters:
 *  pRect           LPCRECT indicating the new size of the window
 *                  of interest.
 *  pIUIWindow      LPOLEINPLACEUIWINDOW pointing to an
 *                  IOleInPlaceUIWindow interface on the container
 *                  object of interest.  We use this to do
 *                  border-space negotiation.
 *
 *  fFrame          BOOL indicating if the frame was resized (TRUE)
 *                  or the document (FALSE)
 *
 * Return Value:
 *  HRESULT         NOERROR or an error code.
 */

STDMETHODIMP CImpIOleInPlaceActiveObject::ResizeBorder(LPCRECT pRect
    , LPOLEINPLACEUIWINDOW pIUIWindow, BOOL fFrame)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIOleInPlaceActiveObject::EnableModeless
 *
 * Purpose:
 *  Instructs the object to show or hide any modeless popup windows
 *  that it may be using when activated in-place.
 *
 * Parameters:
 *  fEnable         BOOL indicating to enable/show the windows
 *                  (TRUE) or to hide them (FALSE).
 *
 * Return Value:
 *  HRESULT         NOERROR or an error code.
 */

STDMETHODIMP CImpIOleInPlaceActiveObject::EnableModeless
    (BOOL fActivate)
    {
    return ResultFromScode(E_NOTIMPL);
    }
