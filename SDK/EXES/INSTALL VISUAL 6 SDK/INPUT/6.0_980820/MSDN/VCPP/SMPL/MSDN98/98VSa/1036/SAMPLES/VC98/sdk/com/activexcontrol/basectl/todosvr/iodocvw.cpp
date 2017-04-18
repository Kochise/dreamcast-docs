//=--------------------------------------------------------------------------=
// IODocVw.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1995-1997  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// implementation of the IOleDocumentView interface for CDocumentObject
//
#include "CDocObj.H"

// for ASSERT and FAIL
//
SZTHISFILE

//=--------------------------------------------------------------------------=
// CDocumentObject::SetInPlaceSite	[IOleDocument]
//=--------------------------------------------------------------------------=
// associates a view site with this view
//
// Parameters:
//    IOleInPlaceSite *   - [in] pointer to container's view site object
//
// Output:
//    HRESULT             - S_OK, E_FAIL
//
// Notes: 
//
STDMETHODIMP CDocumentObject::SetInPlaceSite(IOleInPlaceSite* pIPSite)
{
    TRACE("\nCDocumentObject::SetInPlaceSite");

    // if view already has an associated site,
    //    call IOleInPlaceObject::InPlaceDeactivate and release the site
    if (m_pViewSite)
    {
        InPlaceDeactivate();
        QUICK_RELEASE(m_pViewSite);
    }

    // remember the new view site
    m_pViewSite = pIPSite;
    ADDREF_OBJECT(m_pViewSite);

    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::GetInPlaceSite	[IOleDocument]
//=--------------------------------------------------------------------------=
// retrieves the view site associated with this view
//
// Parameters:
//    IOleInPlaceSite**   - [out] location to return pointer to container's 
//                                view site object
//
// Output:
//    HRESULT             - S_OK, E_FAIL
//
// Notes: 
//
STDMETHODIMP CDocumentObject::GetInPlaceSite(IOleInPlaceSite** ppIPSite)
{
    TRACE("\nCDocumentObject::GetInPlaceSite");

    ADDREF_OBJECT(m_pViewSite);
    *ppIPSite = m_pViewSite;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::GetDocument	[IOleDocument]
//=--------------------------------------------------------------------------=
// retrieves the document associated with this view
//
// Parameters:
//    IUnknown**   - [out] location to return pointer to our object
//
// Output:
//    HRESULT      - S_OK
//
// Notes: 
//
STDMETHODIMP CDocumentObject::GetDocument(IUnknown** ppunk)
{
    TRACE("\nCDocumentObject::GetDocument");
    return InternalQueryInterface(IID_IUnknown, (void**)ppunk);
}

//=--------------------------------------------------------------------------=
// CDocumentObject::SetRect	[IOleDocument]
//=--------------------------------------------------------------------------=
// sets the coordinates of the view port for this view
//
// Parameters:
//    LPRECT   - [in] coordinates of viewpoint in client coordinates of the
//                    view window
//
// Output:
//    HRESULT  - S_OK, E_FAIL
//
// Notes: 
//
STDMETHODIMP CDocumentObject::SetRect(LPRECT prcView)
{
    TRACE("\nCDocumentObject::SetRect");

    // SetObjectRects expects object extent to be set, but
    // DocObjects ignore SetExtent. Set m_Size to the size 
    // specified by the view.
    m_Size.cx = prcView->right - prcView->left;
    m_Size.cy = prcView->bottom - prcView->top;

    HRESULT hr = SetObjectRects(prcView, prcView);
    if (SUCCEEDED(hr))
    {
        // SetObjectRects moves but does not resize window so we will 
        // do that here...
        if (m_hwnd) 
            SetWindowPos(m_hwnd, 0, 0, 0, m_Size.cx, m_Size.cy,
                         SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    return hr;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::GetRect	[IOleDocument]
//=--------------------------------------------------------------------------=
// retrieves the coordinates of the view port for this view
//
// Parameters:
//    LPRECT   - [out] location to put the coordinates of the viewpoint in 
//                     client coordinates of the view window
//
// Output:
//    HRESULT  - S_OK, E_UNEXPECTED
//
// Notes: 
//
STDMETHODIMP CDocumentObject::GetRect(LPRECT prcView)
{
    TRACE("\nCDocumentObject::GetRect");
    if (prcView)
    {
        prcView->top    = 0;
        prcView->left   = 0;
        prcView->bottom = m_Size.cy;
        prcView->right  = m_Size.cx;
        return S_OK;
    }
    else
        return E_UNEXPECTED;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::SetRectComplex	[IOleDocument]
//=--------------------------------------------------------------------------=
// sets the coordinates of the view port, scrollbars, and sizebox for this view
//
// Parameters:
//    LPRECT   - [in] coordinates of viewpoint in client coordinates of the
//                    view window
//    LPRECT   - [in] coordinates of horizontal scrollbar in client 
//                    coordinates of the view window
//    LPRECT   - [in] coordinates of vertical scrollbar in client coordinates 
//                    of the view window
//    LPRECT   - [in] coordinates of sizebox in client coordinates of the
//                    view window
//
// Output:
//    HRESULT  - S_OK, E_FAIL, E_NOTIMPL
//
// Notes: 
//      This implementation does not support complex rectangles!
//
STDMETHODIMP CDocumentObject::SetRectComplex(LPRECT prcView, LPRECT prcHScroll,
                                             LPRECT prcVScroll, LPRECT prcSizeBox)
{
    TRACE("\nCDocumentObject::SetRectComplex");
    return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::Show	[IOleDocument]
//=--------------------------------------------------------------------------=
// instructs the view to in-place activate or in-place deactivate itself
//
// Parameters:
//    BOOL     - [in] whether to activate or deactivate
//
// Output:
//    HRESULT  - S_OK, E_OUTOFMEMORY, E_FAIL, E_UNEXPECTED
//
// Notes: 
//
STDMETHODIMP CDocumentObject::Show(BOOL fShow)
{
    TRACE("\nEnter CDocumentObject::Show");

    HRESULT hr;
    if (fShow)
    {
        // inplace activate without UI activate & show the view window
        hr = ActivateAsDocObject(OLEIVERB_INPLACEACTIVATE);
    }
    else
    {
        // UI deactivate
        hr = UIActivate(FALSE);

        // hide the view window
        SetInPlaceVisible(FALSE);
    }

    TRACE("\nLeave CDocumentObject::Show");
    return hr;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::UIActivate	[IOleDocument]
//=--------------------------------------------------------------------------=
// instructs the view to UI activate or deactivate itself
//
// Parameters:
//    BOOL     - [in] whether to activate or deactivate
//
// Output:
//    HRESULT  - S_OK, E_OUTOFMEMORY, E_FAIL, E_UNEXPECTED
//
// Notes: 
//
STDMETHODIMP CDocumentObject::UIActivate(BOOL fUIActivate)
{
    TRACE("\nEnter CDocumentObject::UIActivate");

    HRESULT hr;
    if (fUIActivate)
    {
        // UI activate the view, take focus and bring view window forward
        hr = ActivateAsDocObject(OLEIVERB_UIACTIVATE);
    }
    else
    {
        // UI deactivate
        hr = UIDeactivate();
    }

    TRACE("\nLeave CDocumentObject::UIActivate");
    return hr;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::Open	[IOleDocument]
//=--------------------------------------------------------------------------=
// asks the view to display itself in a separate popup window 
//
// Parameters:
//    none
//
// Output:
//    HRESULT  - S_OK, E_OUTOFMEMORY, E_FAIL, E_UNEXPECTED, E_NOTIMPL
//
// Notes: 
//      This implementation does not support opening a view in a 
//      separate window.
//
STDMETHODIMP CDocumentObject::Open(void)
{
    TRACE("\nCDocumentObject::Open");
    return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::CloseView	[IOleDocument]
//=--------------------------------------------------------------------------=
// instructs the view to close down and release its IOleInPlaceSite pointer
//
// Parameters:
//    ULONG    - [in] reserved
//
// Output:
//    HRESULT  - S_OK
//
// Notes: 
//
STDMETHODIMP CDocumentObject::CloseView(ULONG ulReserved)
{
    TRACE("\nCDocumentObject::CloseView");

    // hide the view
    Show(FALSE);

    // deactivate the object
    SetInPlaceSite(NULL);

    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::SaveViewState	[IOleDocument]
//=--------------------------------------------------------------------------=
// instructs the view to save its state into the given stream
//
// Parameters:
//    IStream* - [in] stream to write to
//
// Output:
//    HRESULT  - S_OK, E_POINTER, E_NOTIMPL
//
// Notes:
//
STDMETHODIMP CDocumentObject::SaveViewState(LPSTREAM pstm)
{
    TRACE("\nCDocumentObject::SaveViewState");

    // Delegate to a virtual function which specific DocObjects can
    // override to save their view state.
    return OnSaveViewState(pstm);
}

//=--------------------------------------------------------------------------=
// CDocumentObject::ApplyViewState	[IOleDocument]
//=--------------------------------------------------------------------------=
// instructs the view to restore its state from the given stream
//
// Parameters:
//    IStream* - [in] stream to read from
//
// Output:
//    HRESULT  - S_OK, E_POINTER, E_NOTIMPL
//
// Notes: 
//
STDMETHODIMP CDocumentObject::ApplyViewState(LPSTREAM pstm)
{
    TRACE("\nCDocumentObject::ApplyViewState");

    // Delegate to a virtual function which specific DocObjects can
    // override to restore their view state.
    return OnApplyViewState(pstm);
}

//=--------------------------------------------------------------------------=
// CDocumentObject::Clone	[IOleDocument]
//=--------------------------------------------------------------------------=
// creates a duplicate view with an identical internal state to the current
// view
//
// Parameters:
//    IOleInPlaceSite*   - [in] pointer to the inplace site for the clone
//   
//    IOleDocumentView** - [out] location for the new view pointer
//
// Output:
//    HRESULT  - S_OK, E_POINTER, E_NOTIMPL
//
// Notes: 
//      This implementation does not support multiple views, therefore
//      it does not support cloning a view.
//
STDMETHODIMP CDocumentObject::Clone(IOleInPlaceSite* pIPSiteNew, 
                                    IOleDocumentView** ppViewNew)
{
    TRACE("\nCDocumentObject::Clone");
    return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::OnSaveViewState	[IOleDocument]
//=--------------------------------------------------------------------------=
// instructs the view to save its state into the given stream
//
// Parameters:
//    IStream* - [in] stream to write to
//
// Output:
//    HRESULT  - S_OK, E_POINTER, E_NOTIMPL
//
// Notes:
//      This function should be overridden by any DocObject which has
//      a view state. OnApplyViewState is the corresponding function
//      which reads the view state back in.
//
HRESULT CDocumentObject::OnSaveViewState(LPSTREAM pstm)
{
    // Default implementation does nothing
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::OnApplyViewState	
//=--------------------------------------------------------------------------=
// instructs the view to restore its state from the given stream
//
// Parameters:
//    IStream* - [in] stream to read from
//
// Output:
//    HRESULT  - S_OK, E_POINTER, E_NOTIMPL
//
// Notes: 
//      This function should be overridden by any DocObject which has
//      a view state. OnSaveViewState is the corresponding function
//      which writes the view state out.
//
HRESULT CDocumentObject::OnApplyViewState(LPSTREAM pstm)
{
    // Default implementation does nothing
    return S_OK;
}

