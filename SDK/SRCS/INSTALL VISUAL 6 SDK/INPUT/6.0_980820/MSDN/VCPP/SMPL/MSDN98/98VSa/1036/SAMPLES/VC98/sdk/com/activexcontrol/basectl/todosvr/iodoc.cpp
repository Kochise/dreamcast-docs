//=--------------------------------------------------------------------------=
// IODoc.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1995-1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// implementation of the IOleDocument interface for CDocumentObject.
//
#include "CDocObj.H"

// for ASSERT and FAIL
//
SZTHISFILE

//=--------------------------------------------------------------------------=
// CDocumentObject::CreateView	[IOleDocument]
//=--------------------------------------------------------------------------=
// asks the document object to create a new view sub-object
//
// Parameters:
//    IOleInPlaceSite *   - [in] pointer to container's view site object
//    IStream*            - [in] pointer to stream to initialize view with
//    DWORD               - [in] reserved
//    IOleDocumentView*   - [out] address to put interface pointer to new view
//
// Output:
//    HRESULT             - S_OK, E_POINTER, E_OUTOFMEMORY, E_UNEXPECTED, 
//                          E_FAIL
//
// Notes: 
//      This implementation only supports a single view!
//
STDMETHODIMP CDocumentObject::CreateView(IOleInPlaceSite* pIPSite, IStream* pstm, 
                                         DWORD dwReserved, IOleDocumentView** ppView)
{
    TRACE("\nEntering CDocumentObject::CreateView");

    *ppView = NULL;

    if (dwReserved != 0 || m_pDocSite == NULL)
        return E_UNEXPECTED;

    // We only support a single view...so if view site is already
    // set, fail.
    if (m_pViewSite != NULL)
        return E_FAIL;


    // Otherwise, connect the view site to our object
    IOleDocumentView* pView = NULL;
    InternalQueryInterface(IID_IOleDocumentView, (void**)&pView);
    ASSERT(pView != NULL, "object must support IID_IOleDocumentView");

    HRESULT hr = pView->SetInPlaceSite(pIPSite);
    if (SUCCEEDED(hr))
    {
        // Return the IOleDocumentView pointer 
        *ppView = pView;

        // If a saved view state is provided, restore the view state.
        if (pstm)
            hr = pView->ApplyViewState(pstm);
    }
	else
        pView->Release();

    TRACE("\nLeaving CDocumentObject::CreateView");

    return hr;

}

//=--------------------------------------------------------------------------=
// CDocumentObject::GetDocMiscStatus	[IOleDocument]
//=--------------------------------------------------------------------------=
// returns miscellaneous status bits describing the document object
//
// Parameters:
//    DWORD *   - [out] address to put misc status bits in
//
// Output:
//    HRESULT   - S_OK, E_POINTER
//
// Notes:
//
STDMETHODIMP CDocumentObject::GetDocMiscStatus(DWORD* pdwStatus)
{
    TRACE("\nCDocumentObject::GetDocMiscStatus");

	if (pdwStatus)
	{
        // m_ObjectType (from base class CAutomationObject) is the 
        // index into the global object table...
		*pdwStatus = MISCFLAGSOFDOCOBJECT(m_ObjectType);
		return S_OK;
	}
	else
		return E_POINTER;
}

//=--------------------------------------------------------------------------=
// CDocumentObject::EnumViews	[IOleDocument]
//=--------------------------------------------------------------------------=
// creates an enumerator object that enumerates the views of the document object
//
// Parameters:
//    IEnumOleDocumentViews**   - [out] address to put enumerator interface
//    IOleDocumentView**        - [out] address to store single view interface 
//
// Output:
//    HRESULT             - S_OK, E_POINTER, E_OUTOFMEMORY
//
// Notes:
//      This implementation only supports a single view!   
//
STDMETHODIMP CDocumentObject::EnumViews(IEnumOleDocumentViews** ppEnum, 
                                        IOleDocumentView** ppView)
{
    TRACE("\nCDocumentObject::EnumViews");

    if (!ppEnum || !ppView)
        return E_POINTER;

	// Retrieve pointer to our single view
    *ppEnum = NULL;
	return InternalQueryInterface(IID_IOleDocumentView, (void**)ppView);
}
