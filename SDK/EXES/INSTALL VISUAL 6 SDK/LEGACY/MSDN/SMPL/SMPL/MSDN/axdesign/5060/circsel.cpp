//=--------------------------------------------------------------------------=
// CirclSel.Cpp
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
//
//
#include "IPServer.H"

#include "Guids.H"
#include "CirclCtl.H"
#include "LocalObj.H"
#include "Util.H"
#include "Globals.H"
#include "Resource.H"
#include "misc.h"

// for ASSERT and FAIL
//
SZTHISFILE


// We use this to sink events from our circles

class CEventSink:
    public IPropertyNotifySink
{

public:

    ~CEventSink() { };
    CEventSink(CCircleCoControl * pCircleCo, int index) : 
	m_pCircleCo(pCircleCo), m_index(index) {};

    //=----------------------------------------------------------------------=
    // IUnknown methods
    //
    STDMETHOD(QueryInterface)(REFIID riid, LPVOID FAR* ppvObj);
    STDMETHOD_(ULONG,AddRef)(void) { return ++m_cRefs; };
    STDMETHOD_(ULONG,Release)(void) { 
	ULONG cRefs = --m_cRefs;
	if (!cRefs) {
	    delete this;
	}
	return cRefs;
    };

    STDMETHOD(OnChanged)(DISPID dispid) {
	if (DISPID_COLOR == dispid) {
	    m_pCircleCo->OnChangedColor(m_index);
	}
	else { // dispid == DISPID_NAME
	    m_pCircleCo->OnChangedName(m_index);
	}
	return S_OK;
    };
		
    STDMETHOD(OnRequestEdit)(DISPID dispid) {
	return (m_pCircleCo->InUserMode()) ? S_FALSE : S_OK;
    };

  private:
    CCircleCoControl * m_pCircleCo;
    int m_index;
    int m_cRefs;
};




STDMETHODIMP CEventSink ::QueryInterface
(
    REFIID riid, 
    LPVOID FAR* ppvObj
) 
{
    if (DO_GUIDS_MATCH(IID_IPropertyNotifySink, riid))
	*((IUnknown **)ppvObj) = (IUnknown *)(IPropertyNotifySink *)this;
    else if (DO_GUIDS_MATCH(IID_IUnknown, riid))
	*((IUnknown **)ppvObj) = (IUnknown *)this;
    else
	return E_NOINTERFACE;
    
    // addref the object
    //
    (*((IUnknown **)ppvObj))->AddRef();
    return S_OK;
}

BOOL CCircleCoControl::InUserMode
(
    void
)
{
    return m_state.bUserMode;
}


// checks if a new name is valid: it has to be all alphanumerics and
// the first char must be a letter
BOOL _IsValidName
(
    BSTR bstrName
)
{
    LPSTR pszName;
    
    if (!MiscGetAnsiHeapStr(&pszName, bstrName)) goto OnError;
    
    if (!IsCharAlpha(*pszName)) goto OnError;

    while (*pszName) {
	if (!IsCharAlphaNumeric(*pszName)) goto OnError;
	pszName = CharNext(pszName);
    }

    HeapFree(g_hHeap, 0, pszName);
    return TRUE;
    
OnError:
    HeapFree(g_hHeap, 0, pszName);
    return FALSE;
    
    
}


// if the name has changed, update the typeinfo
void CCircleCoControl::OnChangedName
(
    int index
)
{
    HRESULT hr;
    BSTR bstrNewName;

    CIRCLEINFO * pCI = &(m_state.rgCircles[index]);
    ICircle * pCircle;
    hr = pCI->pCircle->QueryInterface(IID_ICircle, (void**) &pCircle);
    if (FAILED(hr)) return;
    
    hr = pCircle->get_Name(&bstrNewName);
    if (FAILED(hr)) return;

    LPSTR pszName;
    if (!MiscGetAnsiHeapStr(&pszName, bstrNewName)) goto OnError;
    
    int iOld;
    iOld = GetIndexFromName(pszName);
    HeapFree(g_hHeap, 0, pszName);

    if (iOld != -1 && iOld != index) {
	MessageBox(NULL, "Duplicate name","",MB_OK);
	
	// this is necessary so that we won't be called back recursively
	pCI->pCP->Unadvise(pCI->dwCookie);
	
	pCircle->put_Name(pCI->bstrName);
	// reconnect
	pCI->pCP->Advise((IUnknown*)pCI->pPNS,&(pCI->dwCookie));
	goto OnError;
    }
    
    pCircle->Release();
    
    // free the old cached name
    SysFreeString(pCI->bstrName);
    // set it to the new name
    pCI->bstrName = bstrNewName;
    
    // and toggle the typeinfo entries
    DeleteFromTypeInfo(index);
    AddToTypeInfo(index);
    return;

OnError:
    SysFreeString(bstrNewName);
    pCircle->Release();
}


// far simpler, just update the cached color
void CCircleCoControl::OnChangedColor
(
    int index
)
{
    HRESULT hr;
    CIRCLEINFO * pCI = &(m_state.rgCircles[index]);
	
    ICircle * pCircle;
    hr = pCI->pCircle->QueryInterface(IID_ICircle, (void**) &pCircle);
    if (FAILED(hr)) return;
    
    pCircle->get_Color(&(pCI->CV));
    pCircle->Release();
    InvalidateControl(NULL);
}


// attempts to attach a sink to a circle
HRESULT CCircleCoControl::AttachSink 
(
    int index
)
{
    HRESULT hr;
    CIRCLEINFO * pCI = &(m_state.rgCircles[index]);

    pCI->pPNS = new CEventSink(this, index);
    RETURN_ON_NULLALLOC(pCI->pPNS);

    IConnectionPointContainer * pCPC;
    hr = pCI->pCircle->QueryInterface(IID_IConnectionPointContainer, (void **)&pCPC);
    FAILGO(hr);

    hr = pCPC->FindConnectionPoint(IID_IPropertyNotifySink, &(pCI->pCP));
    pCPC -> Release();
    FAILGO(hr);

    hr = pCI->pCP->Advise((IUnknown *)pCI->pPNS, &(pCI->dwCookie));
    FAILGO(hr);
    
    return S_OK;
    
OnError:
    pCI->pPNS -> Release();
    pCI->pPNS = NULL;
    pCI->pCP -> Release();
    pCI->pCP = NULL;
    return hr;
}



void CCircleCoControl::DetachSink 
(
    int index
)
{
    CIRCLEINFO * pCI = &(m_state.rgCircles[index]);

    if (pCI->pCP) {
	pCI->pCP->Unadvise(pCI->dwCookie);
	pCI->pCP->Release();
	pCI->pCP = NULL;
    }
    if (pCI->pPNS) {
	pCI->pPNS->Release();
	pCI->pPNS = NULL;
    }
    pCI->dwCookie = 0;

}


// ISelectionContainer methods:

// dwFlags is either GETOBJS_ALL or GETOBJS_SELECTED
// returns the count of objects indicated by dwFlags
STDMETHODIMP CCircleCoControl::CountObjects
(
    DWORD dwFlags, 
    ULONG * pc
)
{
    if (GETOBJS_ALL == dwFlags) {
	*pc = m_state.dwCircleCount + 1; // |circles| + 1 for the container
    }
    else {
	*pc = 1; // either the container or one of the circles is always selected
    }
    
    return S_OK;

}


// returns IUnknown pointers to objects
// either all, or just the selected ones as indicated above

STDMETHODIMP CCircleCoControl::GetObjects
(
    DWORD dwFlags,
    ULONG cObjects, 
    IUnknown **apUnkObjects
)
{
    // init the array
    for (ULONG i = 0; i < cObjects; i++) {
	apUnkObjects[i] = NULL;
    }	    

    IUnknown * pUnkUs;
    HRESULT hr;
    BOOL bUsedUnkUs = FALSE;


    // We can't pass in ourselves as an object because then the user won't be able to
    // browse our ambients, so we need to pass our extender which we get from our
    // control site
    
    IDispatch * pDisp = NULL;
    hr = m_pControlSite->GetExtendedControl(&pDisp);
    if (SUCCEEDED(hr)) {
	hr = pDisp->QueryInterface(IID_IUnknown, (void**)&pUnkUs);
	pDisp->Release();
    }

    if (FAILED(hr)) {
	// In the fall back case we will use ourselfs aterall
	pUnkUs = (IUnknown*)(ISelectionContainer*)this;
	pUnkUs -> AddRef();
    }
    
    if (GETOBJS_ALL == dwFlags) {
	ULONG x = 0;
	for (int i = 0; i < MAXCIRCLES && x < (int) cObjects; i++) {
	    if (m_state.rgCircles[i].bHaveIt) {
		apUnkObjects[x] = m_state.rgCircles[i].pCircle;
		apUnkObjects[x]->AddRef();
		x++;
	    }
	}
	if (x < (int) cObjects) {
	    apUnkObjects[x] = pUnkUs;
	    bUsedUnkUs = TRUE;
	}
    }
    else { // want selected
	if (cObjects > 0) {
	    if (m_state.iSelectedCircle != -1) {
		apUnkObjects[0] = m_state.rgCircles[m_state.iSelectedCircle].pCircle;
		apUnkObjects[0]->AddRef();
	    }
	    else {
		apUnkObjects[0] = pUnkUs;
		bUsedUnkUs = TRUE;
	    }
	}
    }
    if (!bUsedUnkUs) {
	pUnkUs->Release();
    }
    return S_OK;
    
}


// this is called to tell us that a user has selected a given set of objects
// in the property browser.  we mirror that by drawing it differently

STDMETHODIMP CCircleCoControl::SelectObjects
(
    ULONG cSelect,   
    IUnknown **apUnkSelect, 
    DWORD dwFlags
)
{
    
    // we will only select the first thing it gives us

    int index = -1;
    if (cSelect > 0) {
	// try to see if the selected thing is a circle, the default is the main
	// object
	for (int i = 0; i < MAXCIRCLES; i++) {
	    if (m_state.rgCircles[i].bHaveIt && 
		apUnkSelect[0] == m_state.rgCircles[i].pCircle) {
		index = i;
		break;
	    }
	}
	// This will result up in a call to the host's ITrackSelection mechanism, but it's
	// necessary because the host has to display the main control window in a 
	// different way (with stretch bars) if we accept its selection (which we always do)
	MaybeSelectionChanged(index, FALSE);
    }
        
    return S_OK;
}


HRESULT CCircleCoControl::CallOnSelectChange
(
    ISelectionContainer * pISC
)
{
    HRESULT hr;
    
    if (!m_state.pServiceProvider) {
	hr = m_pClientSite->QueryInterface(IID_IServiceProvider, 
					   (void**) &(m_state.pServiceProvider));
	RETURN_ON_FAILURE(hr);
    }
    ITrackSelection * pITS;
    
    hr =  m_state.pServiceProvider->QueryService(SID_STrackSelection, 
						 IID_ITrackSelection,
						 (void **) &pITS);

    RETURN_ON_FAILURE(hr);

    hr = pITS->OnSelectChange(pISC);
    
    pITS->Release();
    
    return(hr);
    
}
