//=--------------------------------------------------------------------------=
// InvisibleInstanceObj.Cpp
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// the InvisibleInstance object
//
//
#include "IPServer.H"

#include "LocalObj.H"
#include "InvsIObj.H"
#include "CtrlObj.h"
#include "autoobj.h"

#include "Util.H"

// for ASSERT and FAIL
//
SZTHISFILE

//=--------------------------------------------------------------------------=
// CInvisibleInstance::Create
//=--------------------------------------------------------------------------=
// creates a new InvisibleInstance object.
//
// Parameters:
//    IUnknown *        - [in] controlling unkonwn
//
// Output:
//    IUnknown *        - new object.
//
// Notes:
//
IUnknown *CInvisibleInstance::Create
(
    IUnknown *pUnkOuter
)
{
    // make sure we return the private unknown so that we support aggegation
    // correctly!
    //
    CInvisibleInstance *pNew = new CInvisibleInstance(pUnkOuter);
    return pNew->PrivateUnknown();
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::CInvisibleInstance
//=--------------------------------------------------------------------------=
// create the object and initialize the refcount
//
// Parameters:
//    IUnknown *    - [in] controlling unknown
//
// Notes:
//
#pragma warning(disable:4355)  // using 'this' in constructor
CInvisibleInstance::CInvisibleInstance
(
    IUnknown *pUnkOuter
)
: CAutomationObjectWEvents(pUnkOuter, OBJECT_TYPE_OBJINVISIBLEINSTANCE, (void *)this) 
{

	// for siting
	m_pClientSite = NULL;

	// MyString property
	m_bstrMyString = NULL;  	
  
}
#pragma warning(default:4355)  // using 'this' in constructor

//=--------------------------------------------------------------------------=
// CInvisibleInstance::~CInvisibleInstance
//=--------------------------------------------------------------------------=
// "We all labour against our own cure, for death is the cure of all diseases"
//    - Sir Thomas Browne (1605 - 82)
//
// Notes:
//
CInvisibleInstance::~CInvisibleInstance ()
{
    if (m_bstrMyString) SysFreeString(m_bstrMyString);

	if (m_pClientSite) ((IUnknown *)m_pClientSite)->Release();
	
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::InternalQueryInterface
//=--------------------------------------------------------------------------=
// the controlling unknown will call this for us in the case where they're
// looking for a specific interface.
//
// Parameters:
//    REFIID        - [in]  interface they want
//    void **       - [out] where they want to put the resulting object ptr.
//
// Output:
//    HRESULT       - S_OK, E_NOINTERFACE
//
// Notes:
//
HRESULT CInvisibleInstance::InternalQueryInterface
(
    REFIID riid,
    void **ppvObjOut
)
{
    CHECK_POINTER(ppvObjOut);

    // we support IInvisibleInstance and ISupportErrorInfo
    //
    if (DO_GUIDS_MATCH(riid, IID_IInvisibleInstance)) {
	*ppvObjOut = (void *)(IInvisibleInstance *)this;
	AddRef();
	return S_OK;
    } else if (DO_GUIDS_MATCH(riid, IID_ISupportErrorInfo)) {
	*ppvObjOut = (void *)(ISupportErrorInfo *)this;
	AddRef();
	return S_OK;
    } else if (DO_GUIDS_MATCH(riid, IID_IPersistStreamInit)) {
	*ppvObjOut = (void *)(IPersistStreamInit *)this;
	AddRef();
	return S_OK;
	} else if (DO_GUIDS_MATCH(riid, IID_IOleObject)) {
	*ppvObjOut = (void *)(IOleObject *)this;
	AddRef();
	return S_OK;
	} 

    // call the super-class version and see if it can oblige.
   
    return CAutomationObjectWEvents::InternalQueryInterface(riid, ppvObjOut);
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::GetClassID    [IPersist]
//=--------------------------------------------------------------------------=
// returns our classid
//
// Parameters:
//    CLSID *           - [out]
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::GetClassID
(
    CLSID *pclsid
)
{
	CHECK_POINTER(pclsid);

	*pclsid = CLSID_InvisibleInstance;
	return S_OK;

}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::get_Mystring    [IInvisibleInstance]
//=--------------------------------------------------------------------------=
//
// Parameters:
//    BSTR *                - [out]
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::get_MyString
(
    BSTR *pbstr
)
{
    ASSERT(m_bstrMyString, "Gaaak!");

    *pbstr = COPYBSTR(m_bstrMyString);
    return *pbstr ? S_OK : E_OUTOFMEMORY;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::put_MyString    [IInvisibleInstance]
//=--------------------------------------------------------------------------=
//
// Parameters:
//    BSTR              - [in]
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::put_MyString
(
    BSTR bstr
)
{
    if (m_bstrMyString) SysFreeString(m_bstrMyString);

    m_bstrMyString = COPYBSTR(bstr ? bstr : L"");
    return m_bstrMyString ? S_OK : E_OUTOFMEMORY;
}



//=--------------------------------------------------------------------------=
// CInvisibleInstance::Load    [IPersistStreamInit]
//=--------------------------------------------------------------------------=
//
//  Parameters:
//      LPSTREAM                - [in] pStm: points to the IStorage instance from which
//                                      to load or run the object
//
//  Output:
//      HRESULT
//
//  Notes: Implemented by m_p 7/5/96
//
//
STDMETHODIMP CInvisibleInstance::Load
(
	LPSTREAM pStm
)

{
    LPWSTR  pwsz;
    HRESULT hr;
    long l;

    // just load in the properties that the InivisibleDesigner saved out
    //
    hr = pStm->Read(&l, sizeof(l), NULL);
    RETURN_ON_FAILURE(hr);


    pwsz = (LPWSTR)HeapAlloc(g_hHeap, 0, l * sizeof(WCHAR));
    if (!pwsz) return E_OUTOFMEMORY;

    hr = pStm->Read(pwsz, l * sizeof(WCHAR), NULL);
    RETURN_ON_FAILURE(hr);

    m_bstrMyString = SysAllocString(pwsz);

    if (!m_bstrMyString) return  E_OUTOFMEMORY;
    HeapFree(g_hHeap, 0, pwsz);

    return S_OK;
}



//=--------------------------------------------------------------------------=
// CInvisibleInstance::Save    [IPersistStreamInit]
//=--------------------------------------------------------------------------=
//
//  Parameters:
//      LPSTORAGE               - [in] pStm: points to the IStream instance in 
//                                      which the object is to be saved
//      BOOL                    - [in] fClearDirty
//
//  Output:
//      HRESULT
//
//  Notes: Implemented by m_p 7/5/96
//
//
STDMETHODIMP CInvisibleInstance::Save
(
	LPSTREAM pStm, BOOL fClearDirty
)
{
	return S_OK;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::GetSizeMax    [IPersistStreamInit]
//=--------------------------------------------------------------------------=
//
//  Parameters:
//
//  ULARGE_INTEGER* pcbSize     //Receives a pointer to the size of the stream needed to
//  Output:
//      HRESULT
//
//  Notes: Implemented by m_p 7/5/96
//
//
STDMETHODIMP CInvisibleInstance::GetSizeMax
(
	ULARGE_INTEGER* pcbSize
)
{
	return S_OK;
}



//=--------------------------------------------------------------------------=
// CInvisibleInstance::InitNew    [IPersistStreamInit]
//=--------------------------------------------------------------------------=
//
//
//  Output:
//      HRESULT
//
//  Notes: Implemented by m_p 7/5/96
//
//
STDMETHODIMP CInvisibleInstance::InitNew
(
	void
)
{
	return S_OK;
}



//=--------------------------------------------------------------------------=
// CInvisibleInstance::IsDirty   [IPersistStreamInit]
//=--------------------------------------------------------------------------=
//
//  Parameters:
//
//  Output:
//      HRESULT
//
//  Notes: Implemented by m_p 7/5/96
//
//
STDMETHODIMP CInvisibleInstance::IsDirty
(
	
)
{
	return S_OK;
}
	


//=--------------------------------------------------------------------------=
// CInvisibleInstance::SetClientSite    [IOleObject]
//=--------------------------------------------------------------------------=
// informs the embedded object [control] of it's client site [display
// location] within it's container
//
// Parameters:
//    IOleClientSite *        - [in] pointer to client site.
//
// Output:
//    HRESULT                 - S_OK, E_UNEXPECTED
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::SetClientSite
(
    IOleClientSite *pClientSite
)
{
     
	// Release Object
   if (m_pClientSite) 
	{ 
		IUnknown *pUnk = (m_pClientSite); 
		(m_pClientSite) = NULL; 
		pUnk->Release(); 
	}


    m_pClientSite = pClientSite;

	// Addref object
	if (m_pClientSite) (m_pClientSite)->AddRef();

  
    return S_OK;
}


//=--------------------------------------------------------------------------=
// CInvisibleInstance::GetClientSite    [IOleObject]
//=--------------------------------------------------------------------------=
// obtains a pointer to the controls client site.
//
// Parameters:
//    IOleClientSite **        - [out]
//
// Output:
//    HRESULT                  - S_OK
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::GetClientSite
(
    IOleClientSite **ppClientSite
)
{
	 if (!(ppClientSite) || IsBadWritePtr((void *)(ppClientSite), sizeof(void *))) 
	 {
		return E_POINTER;
	 }		

     *ppClientSite = m_pClientSite;
  
	 return S_OK;
}




//=--------------------------------------------------------------------------=
// CInvisibleInstance::SetHostNames    [IOleObject]
//=--------------------------------------------------------------------------=
// Provides the control with the name of its container application and the
// compound document in which it is embedded
//
// Parameters:
//    LPCOLESTR        - [in] name of container application
//    LPCOLESTR        - [in] name of container document
//
// Output:
//    HRESULT          - S_OK
//
// Notes:
//    - we don't care about this
//
STDMETHODIMP CInvisibleInstance::SetHostNames
(
    LPCOLESTR szContainerApp,
    LPCOLESTR szContainerObject
)
{
    // we don't care about these
    //
    return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::Close    [IOleObject]
//=--------------------------------------------------------------------------=
// Changes the control from the running to the loaded state
//
// Parameters:
//    DWORD             - [in] indicates whether to save the object before closing
//
// Output:
//    HRESULT           - S_OK, OLE_E_PROMPTSAVECANCELLED
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::Close
(
    DWORD dwSaveOption
)
{
   return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::SetMoniker    [IOleObject]
//=--------------------------------------------------------------------------=
// Notifies an object of its container's moniker, the object's own moniker
// relative to the container, or the object's full moniker
//
// Parameters:
//    DWORD                - [in] which moniker is being set
//    IMoniker *           - [in] the moniker
//
// Output:
//    HRESULT              - S_OK, E_FAIL
//
// Notes:
//    - we don't support monikers.
//
STDMETHODIMP CInvisibleInstance::SetMoniker
(
    DWORD     dwWhichMoniker,
    IMoniker *pMoniker
)
{
    return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::GetMoniker    [IOleObject]
//=--------------------------------------------------------------------------=
// Returns a embedded object's moniker, which the caller can use to link to
// the object
//
// Parameters:
//    DWORD            - [in]  how it's assigned
//    DWORD            - [in]  which moniker
//    IMoniker **      - [out] duh.
//
// Output:
//    HRESULT          - E_NOTIMPL
//
// Notes:
//    - we don't support monikers
//
STDMETHODIMP CInvisibleInstance::GetMoniker
(
    DWORD      dwAssign,
    DWORD      dwWhichMoniker,
    IMoniker **ppMonikerOut
)
{
    return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::InitFromData    [IOleObject]
//=--------------------------------------------------------------------------=
// Initializes a newly created object with data from a specified data object,
// which can reside either in the same container or on the Clipboard
//
// Parameters:
//    IDataObject*    - [in] data object with the data
//    BOOL            - [in] how object is created
//    DWORD           - reserved
//
// Output:
//    HRESULT         - S_OK, S_FALSE, E_NOTIMPL, OLE_E_NOTRUNNING
//
// Notes:
//    - we don't have data object support
//
STDMETHODIMP CInvisibleInstance::InitFromData
(
    IDataObject *pDataObject,
    BOOL         fCreation,
    DWORD        dwReserved
)
{
    return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::GetClipboardData    [IOleObject]
//=--------------------------------------------------------------------------=
// Retrieves a data object containing the current contents of the control.
// Using the pointer to this data object, it is possible to create a new control
// with the same data as the original
//
// Parameters:
//    DWORD          - reserved
//    IDataObject ** - [out] data object for this control
//
// Output:
//    HREUSLT        - S_OK, E_NOTIMPL, OLE_E_NOTRUNNING
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::GetClipboardData
(
    DWORD         dwReserved,
    IDataObject **ppDataObject
)
{
    *ppDataObject = NULL;        // be a good neighbour
    return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::DoVerb    [IOleObject]
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
STDMETHODIMP CInvisibleInstance::DoVerb
(
    LONG            lVerb,
    LPMSG           pMsg,
    IOleClientSite *pActiveSite,
    LONG            lIndex,
    HWND            hwndParent,
    LPCRECT         prcPosRect
)
{
   return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::EnumVerbs    [IOleObject]
//=--------------------------------------------------------------------------=
// create an enumerator object for the verbs this object supports.
//
// Parameters:
//    IEnumOleVERB **    - [out] new enumerator.
//
// Output:
//    HRESULT            - S_OK, E_OUTOFMEMORY
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::EnumVerbs
(
    IEnumOLEVERB **ppEnumVerbs
)
{
   return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::Update    [IOleObject]
//=--------------------------------------------------------------------------=
// Updates an object handler's or link object's data or view caches.
//
// Output:
//    HRESULT            - S_OK
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::Update
(
    void
)
{
    // nothing to do!!!
    //
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::IsUpToDate    [IOleObject]
//=--------------------------------------------------------------------------=
// Checks recursively whether or not an object is up to date.
//
// Output:
//    HRESULT        - S_OK, S_FALSE, OLE_E_UNVAILABLE
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::IsUpToDate
(
    void
)
{
    // we're always up to date
    //
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::GetUserClassID    [IOleObject]
//=--------------------------------------------------------------------------=
// Returns the controls class identifier, the CLSID corresponding to the
// string identifying the object to an end user.
//
// Parameters:
//    CLSID *      - [in] where to put the CLSID
//
// Output:
//    HRESULT      - S_OK, E_FAIL
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::GetUserClassID
(
    CLSID *pclsid
)
{
    // this is the same as IPersist::GetClassID
    //
    return GetClassID(pclsid);
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::GetUserType    [IOleObject]
//=--------------------------------------------------------------------------=
// Retrieves the user-type name of the control for display in user-interface
// elements such as menus, list boxes, and dialog boxes.
//
// Parameters:
//    DWORD        - [in]  specifies the form of the type name.
//    LPOLESTR *   - [out] where to put user type
//
// Output:
//    HRESULT      - S_OK, OLE_S_USEREG, E_OUTOFMEMORY
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::GetUserType
(
    DWORD     dwFormOfType,
    LPOLESTR *ppszUserType
)
{
    return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::SetExtent    [IOleObject]
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
STDMETHODIMP CInvisibleInstance::SetExtent
(
    DWORD  dwDrawAspect,
    SIZEL *psizel
)
{
    return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::GetExtent    [IOleObject]
//=--------------------------------------------------------------------------=
// Retrieves the control's current display size.
//
// Parameters:
//    DWORD            - [in] aspect
//    SIZEL *          - [in] where to put results
//
// Output:
//    S_OK, E_INVALIDARG
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::GetExtent
(
    DWORD  dwDrawAspect,
    SIZEL *pSizeLOut
)
{
return E_NOTIMPL;
    // dead code
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::Advise    [IOleObject]
//=--------------------------------------------------------------------------=
// establishes and advisory connection between the control and the container,
// in which the control will notify the container of certain events.
//
// Parameters:
//    IAdviseSink *     - [in]  advise sink of calling object
//    DWORD             - [out] cookie
//
// Output:
//    HRESULT           - S_OK, E_OUTOFMEMORY
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::Advise
(
    IAdviseSink *pAdviseSink,
    DWORD       *pdwConnection
)
{
    return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::Unadvise    [IOleObject]
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
//
STDMETHODIMP CInvisibleInstance::Unadvise
(
    DWORD dwConnection
)
{
   return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::EnumAdvise    [IOleObject]
//=--------------------------------------------------------------------------=
// Enumerates the advisory connections registered for an object, so a container
// can know what to release prior to closing down.
//
// Parameters:
//    IEnumSTATDATA **    - [out] where to put enumerator
//
// Output:
//    HRESULT             - S_OK, E_FAIL, E_NOTIMPL
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::EnumAdvise
(
    IEnumSTATDATA **ppEnumOut
)
{
   return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::GetMiscStatus    [IOleObject]
//=--------------------------------------------------------------------------=
// Returns a value indicating the status of an object at creation and loading.
//
// Parameters:
//    DWORD         - [in]  aspect desired
//    DWORD *       - [out] where to put the bits.
//
// Output:
//    HRESULT       - S_OK, OLE_S_USEREG, CO_E_CLASSNOTREG, CO_E_READREGDB
//
// Notes:
//
STDMETHODIMP CInvisibleInstance::GetMiscStatus
(
    DWORD  dwAspect,
    DWORD *pdwStatus
)
{
    return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CInvisibleInstance::SetColorScheme    [IOleObject]
//=--------------------------------------------------------------------------=
// Specifies the color palette that the object application should use when it
// edits the specified object.
//
// Parameters:
//    LOGPALETTE *     - [in] new palette
//
// Output:
//    HRESULT          - S_OK, E_NOTIMPL, OLE_E_PALETTE, OLE_E_NOTRUNNING
//
// Notes:
//    - we don't care.
//
STDMETHODIMP CInvisibleInstance::SetColorScheme
(
    LOGPALETTE *pLogpal
)
{
    // OVERRIDE: control writers can use this if they want to
    //
    return S_OK;
}

//=--------------------------------------------------------------------------=
// COleControl::OnSetClientSite    [overrideable]
//=--------------------------------------------------------------------------=
// controls should implement this if they hold on to anything off the site.
// this is important to correctly support aggregation.  they must free up
// everything they hold on to, and if m_pClientSite is not NULL, then they
// can re-establish things as they wish.
//
// Parameters:
//    none
//
// Output:
//    HRESULT
//
// Notes:
//
//HRESULT CInvisibleInstance::OnSetClientSite
//(
//    void
//)
//{
    // by default, the framework frees up everything in SetClientSite
//    //
//    return S_OK;
//}
