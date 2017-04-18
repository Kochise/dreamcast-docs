//=--------------------------------------------------------------------------=
// CDocObj.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1995 - 1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// implementation of CDocumentObject, which provides basic DocObject server
// support. This file contains overrides of basic inplace editing support.
// See iodoc.cpp and iodocvw.cpp for implementations of required interfaces
// for DocObject server support.
// 
#include <IPServer.H>
#include <Globals.H>
#include "CDocObj.H"

// for ASSERT and FAIL
//
SZTHISFILE

//=--------------------------------------------------------------------------=
// CDocumentObject::CDocumentObject
//=--------------------------------------------------------------------------=
//
// Parameters:
//    IUnknown*        - [in]
//    int              - [in]
//    void*            - [in]
//
// Notes:
//
CDocumentObject::CDocumentObject(IUnknown* pUnkOuter, int iPrimaryDispatch, 
                                 void* pMainInterface)
   : BASECLASS(pUnkOuter, iPrimaryDispatch, pMainInterface)
{
    m_fDocObj   = FALSE;
    m_pDocSite  = NULL;
    m_pViewSite = NULL;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::~CDocumentObject
//=--------------------------------------------------------------------------=
//
// Notes:
//
CDocumentObject::~CDocumentObject()
{
    ASSERT(m_pDocSite == NULL, "CDocumentObject::m_pDocSite not properly released");
    ASSERT(m_pViewSite == NULL, "CDocumentObject::m_pViewSite not properly released");
}


//=--------------------------------------------------------------------------=
// CDocumentObject::InternalQueryInterface
//=--------------------------------------------------------------------------=
// qi for things only we support.
//
// Parameters:
// Parameters:
//    REFIID       - [in]  interface they want
//    void**       - [out] where they want to put the resulting object ptr.
//
// Output:
//    HRESULT      - S_OK, E_NOINTERFACE
//
// Notes:
//
HRESULT CDocumentObject::InternalQueryInterface(REFIID riid, void** ppvObjOut)
{
    // Check for interfaces we implement
    if (DO_GUIDS_MATCH(riid, IID_IOleDocument)) 
        *ppvObjOut = (void *)(IOleDocument*)this; 
    else if (DO_GUIDS_MATCH(riid, IID_IOleDocumentView))
        *ppvObjOut = (void *)(IOleDocumentView*)this; 
    else
        // delegate to super-class for automation interfaces, etc ...
        //
        return BASECLASS::InternalQueryInterface(riid, ppvObjOut);

    // we like the interface, so addref and return
    //
    ((IUnknown *)(*ppvObjOut))->AddRef();
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::SetClientSite
//=--------------------------------------------------------------------------=
// determines whether object can and should activate as a DocObject
//
// Parameters:
//    IOleClientSite*        - [in] pointer to client site.
//
// Output:
//    HRESULT                - S_OK
//
// Notes:
//
HRESULT CDocumentObject::SetClientSite(IOleClientSite* pClientSite)
{
    TRACE("\nCDocumentObject::SetClientSite");

    // perform regular SetClientSite processing
    HRESULT hr = BASECLASS::SetClientSite(pClientSite);
    if (FAILED(hr))
        return hr;

	// If we have a document site pointer, 
	//    release it and set docobj flag FALSE
	RELEASE_OBJECT(m_pDocSite);
    m_fDocObj = FALSE;

	// If we got a client site,
	if (pClientSite != NULL)
    {
        // If the client site supports IID_IOleDocumentSite,
        //    save the document site pointer
        //    and set docobj flag TRUE
		hr = pClientSite->QueryInterface(IID_IOleDocumentSite, 
                                         (void**)&m_pDocSite);
        if (SUCCEEDED(hr))
            m_fDocObj = TRUE;
    }
	return S_OK;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::DoVerb    [IOleObject]
//=--------------------------------------------------------------------------=
// Requests an object to perform an action in response to an end-user's
// action.
//
// Parameters:
//    LONG             - [in]  verb to be performed
//    LPMSG            - [in]  event that invoked the verb
//    IOleClientSite * - [in]  the controls active client site
//    LONG             - [in]  reserved
//    HWND             - [in]  handle of window containing the object.
//    LPCRECT          - [in]  pointer to objects's display rectangle
//
// Output:
//    HRESULT          - S_OK, OLE_E_NOTINPLACEACTIVE, OLE_E_CANT_BINDTOSOURCE,
//                       DV_E_LINK, OLEOBJ_S_CANNOT_DOVERB_NOW, OLEOBJ_S_INVALIDHWND,
//                       OLEOBJ_E_NOVERBS, OLEOBJ_S_INVALIDVERB, MK_E_CONNECT,
//                       OLE_CLASSDIFF, E_NOTIMPL
//
// Notes:
//
STDMETHODIMP CDocumentObject::DoVerb
(
    LONG            lVerb,
    LPMSG           pMsg,
    IOleClientSite *pActiveSite,
    LONG            lIndex,
    HWND            hwndParent,
    LPCRECT         prcPosRect
)
{
    TRACE("\nCDocumentObject::DoVerb");

    // if we're acting as a docobj
    if (m_fDocObj)
    {
        switch (lVerb)
        {
        // call IOleDocumentSite::ActivateMe for Show, Open, InPlaceActivate and UIActivate Verbs
        case OLEIVERB_SHOW:
        case OLEIVERB_UIACTIVATE:
        case OLEIVERB_OPEN:
        case OLEIVERB_INPLACEACTIVATE:
            return m_pDocSite->ActivateMe(NULL);

        // return E_INVALIDARG for Hide Verb
        case OLEIVERB_HIDE:
            return E_INVALIDARG;

        // otherwise, just do normal processing
        default:
            break;
        }
    }
    
    // if we're not acting as a docobj, just do normal processing    
    return BASECLASS::DoVerb(lVerb, pMsg, pActiveSite, lIndex,
                             hwndParent, prcPosRect);

}

//=--------------------------------------------------------------------------=
// CDocumentObject::SetExtent    [IOleObject]
//=--------------------------------------------------------------------------=
// Informs the control of how much display space its container has assigned it.
//
// Parameters:
//    DWORD            - [in] which form or 'aspect'  is to be displayed.
//    SIZEL *          - [in] size limit for the control.
//
// Output:
//    HRESULT          - S_OK, E_FAIL, OLE_E_NOTRUNNING
//
// Notes:
//
STDMETHODIMP CDocumentObject::SetExtent(DWORD dwDrawAspect, SIZEL *psizel)
{
    TRACE("\nCDocumentObject::SetExtent");

    // ignore SetExtent calls if we are a docobj
    if (m_fDocObj)
        return S_OK;

    // otherwise do normal processing
    return BASECLASS::SetExtent(dwDrawAspect, psizel);
}

//=--------------------------------------------------------------------------=
// CDocumentObject::Unadvise    [IOleObject]
//=--------------------------------------------------------------------------=
// Deletes a previously established advisory connection.
//
// Parameters:
//    DWORD         - [in] connection cookie
//
// Output:
//    HRESULT       - S_OK, E_FAIL, OLE_E_NOCONNECTION
//
// Notes:
//      This override is included to work around a problem observed 
//      interacting with Office Binder. When activated as a docobj, 
//      IOleObject::Advise is not getting called. However, when deactivated, 
//      IOleObject::Unadvise *is* called. Since no advise holder was ever 
//      created, the base class method asserts.
// 
//      All this function does is prevent the assert from getting hit.
//
STDMETHODIMP CDocumentObject::Unadvise(DWORD dwConnection)
{
    if (!dwConnection) {
        TRACE("\nSomebody called Unadvise on IOleObject without calling Advise!");
        return OLE_E_NOCONNECTION;
    }

    return BASECLASS::Unadvise(dwConnection);
}


//=--------------------------------------------------------------------------=
// CDocumentObject::ActivateAsDocObject
//=--------------------------------------------------------------------------=
// activates a document object, and depending on the verb, optionally 
// ui activates it as well.
//
// Parameters:
//    LONG         - [in] the verb that caused us to activate
//
// Output:
//    HRESULT      - S_OK, E_UNEXPECTED
//
// Notes:
//      This implementation is based on COleControl::InPlaceActivate.
//      COleControl::InPlaceActivate is called when a CDocumentObject
//      is being used as a control or normal embedding, not this function.
//
HRESULT CDocumentObject::ActivateAsDocObject(LONG lVerb)
{
    TRACE("\nEntering CDocumentObject::ActivateAsDocObject");

    HRESULT hr = S_OK;

    // if our view site has not been set, report an error
    if (!m_pViewSite)
    {
        hr = E_UNEXPECTED;
        goto LeaveMethod;
    }

    // if we don't have a client site, then there's not much to do.
    //
    if (!m_pClientSite)
        goto LeaveMethod;


    // get an InPlaceSite pointer
    //
    if (!m_pInPlaceSite) {
        hr = m_pClientSite->QueryInterface(IID_IOleInPlaceSite, (void **)&m_pInPlaceSite);
        if (FAILED(hr))
            goto LeaveMethod;
    }

    // if we're not already active, go and do it.
    //
    if (!m_fInPlaceActive) {
        OLEINPLACEFRAMEINFO InPlaceFrameInfo;
        RECT rcPos, rcClip;

        // ask for permission and notify the container we're going active.
        //
        hr = m_pInPlaceSite->CanInPlaceActivate();
        if (hr != S_OK) 
        {
            if (FAILED(hr))
                hr = E_FAIL;
            goto LeaveMethod;
        }

        hr = m_pInPlaceSite->OnInPlaceActivate();
        if (FAILED(hr))
            goto LeaveMethod;

        m_fInPlaceActive = TRUE;
        InPlaceFrameInfo.cb = sizeof(OLEINPLACEFRAMEINFO);

        // get our parent window
        //
        hr = m_pInPlaceSite->GetWindow(&m_hwndParent);
        if (!FAILED(hr))
            // get our display and clipping rectangles
            //
            hr = m_pInPlaceSite->GetWindowContext(&m_pInPlaceFrame, &m_pInPlaceUIWindow,
                                                  &rcPos, &rcClip, &InPlaceFrameInfo);
        if (FAILED(hr)) {
            InPlaceDeactivate();
            goto LeaveMethod;
        }

        // make sure we'll display ourselves in the correct location with the correct size
        //    SetObjectRects expects object extent to be set, but
	  //    DocObjects ignore SetExtent. Set m_Size to the size 
	  //    specified for the view.
	  m_Size.cx = rcPos.right - rcPos.left;
	  m_Size.cy = rcPos.bottom - rcPos.top;
        SetObjectRects(&rcPos, &rcClip);

        // create the window, and display it. 
        //
        CreateInPlaceWindow(rcPos.left, rcPos.top, TRUE);
    }

    if (!m_fInPlaceVisible)
        SetInPlaceVisible(TRUE);

    // if we weren't asked to UIActivate, then we're done.
    //
    if (lVerb != OLEIVERB_PRIMARY && lVerb != OLEIVERB_UIACTIVATE)
        goto LeaveMethod;

    // if we're not already UI active, do sow now.
    //
    if (!m_fUIActive) {
        m_fUIActive = TRUE;

        // inform the container of our intent
        //
        m_pInPlaceSite->OnUIActivate();

        // take the focus  [which is what UI Activation is all about !]
        //
        SetFocus(TRUE);

        // set up the active object [us] with the container.
        //
        m_pInPlaceFrame->SetActiveObject((IOleInPlaceActiveObject *)this, NULL);
        if (m_pInPlaceUIWindow)
            m_pInPlaceUIWindow->SetActiveObject((IOleInPlaceActiveObject *)this, NULL);

        // we have to explicitly say we don't wany any border space.
        //
        m_pInPlaceFrame->SetBorderSpace(NULL);
        if (m_pInPlaceUIWindow)
            m_pInPlaceUIWindow->SetBorderSpace(NULL);
    }

LeaveMethod:
    TRACE("\nLeaving CDocumentObject::ActivateAsDocObject");
    return hr;
}
