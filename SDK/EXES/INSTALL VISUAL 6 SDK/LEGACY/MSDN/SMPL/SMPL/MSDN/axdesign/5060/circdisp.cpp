//=--------------------------------------------------------------------------=
// CirclCtl.Cpp
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
//  The IDispatch implementation for the circle container control
//
#include "IPServer.H"

#include "Guids.H"
#include "CirclCtl.H"
#include "LocalObj.H"
#include "Util.H"
#include "Misc.h"
#include "Globals.H"
#include "Resource.H"

// for ASSERT and FAIL
//
SZTHISFILE


//=--------------------------------------------------------------------------=
// private functions
//
HRESULT _FillException(HRESULT hr, WORD wID, EXCEPINFO *pexcepinfo);


// Type info init:
//
ITypeInfo * g_pTypeInfo = NULL;

//=--------------------------------------------------------------------------=
// CCircleCoControl::GetTypeInfoCount    [IDispatch]
//=--------------------------------------------------------------------------=
// returns the current count of typeinfos we have
//
// Parameters:
//    UINT *                - [out]
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CCircleCoControl::GetTypeInfoCount
(
    UINT *pCount
)
{
    CHECK_POINTER(pCount);

    *pCount = 1;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CCircleCoControl::GetTypeInfo    [IDispatch]
//=--------------------------------------------------------------------------=
// returns our interface typeinfo.
//
// Parameters:
//    UINT                  - [in]  which one
//    LCID                  - [in]  language
//    ITypeInfo **          - [out] duh
//
// Ouput:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CCircleCoControl::GetTypeInfo
(
    UINT        iTypeInfo,
    LCID        lcid,
    ITypeInfo **ppTypeInfoOut
)
{
    // Since this is asking for our static typeinfo, we would like to delegate
    // to our underlying automation object, however, as it's GTI method
    // assumes that we are dual interface based, we can't.  So we have to
    // reimplement this ourselves:


    DWORD       dwPathLen;
    char        szDllPath[MAX_PATH];
    HRESULT     hr;
    ITypeLib   *pTypeLib;
    ITypeInfo **ppTypeInfo;

    // arg checking
    //
    if (iTypeInfo != 0)
        return DISP_E_BADINDEX;

    CHECK_POINTER(ppTypeInfoOut);

    *ppTypeInfoOut = NULL;

    // ppTypeInfo will point to our global holder for this particular
    // type info.  if it's null, then we have to load it up. if it's not
    // NULL, then it's already loaded, and we're happy.
    // crit sect this entire nightmare so we're okay with multiple
    // threads trying to use this object.
    //
    EnterCriticalSection(&g_CriticalSection);
    ppTypeInfo = &g_pTypeInfo;

    if (*ppTypeInfo == NULL) {

        // we don't have the type info around, so go load it.
        //
        hr = LoadRegTypeLib(*g_pLibid, (USHORT)VERSIONOFOBJECT(m_ObjectType),0,
			    LANG_NEUTRAL,
                            &pTypeLib);

        // if, for some reason, we failed to load the type library this
        // way, we're going to try and load the type library directly out of
        // our resources.  this has the advantage of going and re-setting all
        // the registry information again for us.
        //
        if (FAILED(hr)) {

            dwPathLen = GetModuleFileName(g_hInstance, szDllPath, MAX_PATH);
            if (!dwPathLen) {
                hr = E_FAIL;
                goto CleanUp;
            }

            MAKE_WIDEPTR_FROMANSI(pwsz, szDllPath);
            hr = LoadTypeLib(pwsz, &pTypeLib);
            CLEANUP_ON_FAILURE(hr);
        }

        // we've got the Type Library now, so get the type info for the
        // interface we're interested in.
        //
        hr = pTypeLib->GetTypeInfoOfGuid((REFIID)INTERFACEOFOBJECT(m_ObjectType),
                                         ppTypeInfo);
        pTypeLib->Release();
        CLEANUP_ON_FAILURE(hr);

    }

    // we still have to go and addref the Type info object, however, so that
    // the people using it can release it.
    //
    (*ppTypeInfo)->AddRef();
    *ppTypeInfoOut = *ppTypeInfo;
    hr = S_OK;

  CleanUp:
    LeaveCriticalSection(&g_CriticalSection);
    return hr;



}

//=--------------------------------------------------------------------------=
// CCircleCoControl::GetIDsOfNames    [IDispatch]
//=--------------------------------------------------------------------------=
// our implementation if IDispatch::GetIDsOfNames.  fortunately, automation
// can do most of this work for us
//
// Parameters:
//    REFIID                - [in]  IID_NULL
//    OLECHAR **            - [in]  names
//    UINT                  - [in]  cnames
//    LCID                  - [in]  language
//    DISPID *              - [out] dispids
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CCircleCoControl::GetIDsOfNames
(
    REFIID    riid,
    OLECHAR **rgwszNames,
    UINT      cNames,
    LCID      lcid,
    DISPID   *rgdispid
)
{

    HRESULT     hr;
    ITypeInfo  *pTypeInfo;
    UINT x;

    if (!DO_GUIDS_MATCH(riid, IID_NULL))
        return E_INVALIDARG;

    // do a little sanity checking to make sure we don't crash.
    //
    if (cNames == 0) return E_INVALIDARG;
    if (!rgwszNames) return E_INVALIDARG;
    if (!rgdispid) return E_INVALIDARG;

    // set all the DISPIDs to DISPID_UNKNOWN by default
    //
    for (x = 0; x < cNames; x++) rgdispid[x] = DISPID_UNKNOWN;


    MAKE_ANSIPTR_FROMWIDE(pszName, rgwszNames[0]);
    int index = GetIndexFromName(pszName);
    if (index != -1) {
	rgdispid[0] = index + DISPID_CUSTOMOFFSET;
	return (cNames == 1) ? S_OK : DISP_E_UNKNOWNNAME;
    }
    
    // we didn't find it, so just pass it on to OLE automation and
    // let them take care of it.
    //
    hr = GetTypeInfo(0, lcid, &pTypeInfo);
    RETURN_ON_FAILURE(hr);
    
    hr = pTypeInfo->GetIDsOfNames(rgwszNames, cNames, rgdispid);
    pTypeInfo->Release();
    return hr;
       
}

//=--------------------------------------------------------------------------=
// CCircleCoControl::Invoke    [IDispatch]
//=--------------------------------------------------------------------------=
// head for the hills!
//
// Parameters:
//    DISPID            - [in]  identifies the member we're working with.
//    REFIID            - [in]  must be IID_NULL.
//    LCID              - [in]  language we're working under
//    USHORT            - [in]  flags, propput, get, method, etc ...
//    DISPPARAMS *      - [in]  array of arguments.
//    VARIANT *         - [out] where to put result, or NULL if they don't care.
//    EXCEPINFO *       - [out] filled in in case of exception
//    UINT *            - [out] where the first argument with an error is.
//
// Output:
//    HRESULT           - tonnes of them.
//
// Notes:
//    
STDMETHODIMP CCircleCoControl::Invoke
(
    DISPID      dispid,
    REFIID      riid,
    LCID        lcid,
    WORD        wFlags,
    DISPPARAMS *pdispparams,
    VARIANT    *pvarResult,
    EXCEPINFO  *pexcepinfo,
    UINT       *puArgErr
)
{
    
    HRESULT hr;


    // this has to be IID_NULL
    //
    if (!DO_GUIDS_MATCH(riid, IID_NULL))
        return DISP_E_UNKNOWNINTERFACE;

    if (m_state.bUserMode) {

	if (dispid < DISPID_CUSTOMOFFSET || dispid >= DISPID_CUSTOMOFFSET+MAXCIRCLES) {
	    goto Failed;
	}
	
	if (!pvarResult)
	    return E_FAIL;
        
	int index = dispid - DISPID_CUSTOMOFFSET;
	
	if (!m_state.rgCircles[index].bHaveIt) {
	    goto Failed;
	}
		
	hr = CreateObject(index);
	RETURN_ON_FAILURE(hr);
	
	IDispatch * pDisp;
	hr = m_state.rgCircles[index].pCircle->QueryInterface(IID_IDispatch, (void**) &pDisp);
	RETURN_ON_FAILURE(hr);
        
	VariantInit(pvarResult);
	pvarResult -> vt = VT_DISPATCH;
	pvarResult -> pdispVal = pDisp;

	return S_OK;
    }
Failed:
    
    // Let's try to use ITypeInfo to invoke our normal properties and methods

    // This works (even though we are a dispinterface) because we have based the
    // dispinterface on a v-table based interface.

    // See our .odl file for more information
    ITypeInfo * pti;
    
    hr = GetTypeInfo(0,lcid, &pti);
    RETURN_ON_FAILURE(hr);
    
    
    hr = pti->Invoke((HCircleCo *)this, dispid, wFlags, pdispparams, 
		      pvarResult, pexcepinfo, puArgErr);

    QUICK_RELEASE(pti);
    return hr;
    

}


//=--------------------------------------------------------------------------=
// _FillException    [helper]
//=--------------------------------------------------------------------------=
// fills out an excepinfo given an error
//
// Parameters:
//    HRESULT               - [in]  error
//    WORD                  - [in]  resource string with description
//    EXCEPINFO *           - [out] exception to fill out
//
// Output:
//    DISP_E_EXCEPTION
//
// Notes:
//
HRESULT _FillException
(
    HRESULT    hr,
    WORD       wID,
    EXCEPINFO *pexcepinfo
)
{
    if (!pexcepinfo) return hr;

    pexcepinfo->wCode = SCODE_CODE(hr);
    pexcepinfo->scode = hr;

    pexcepinfo->bstrSource = BSTRFROMANSI(g_pszWhatAmI);
    if (!pexcepinfo->bstrSource) return E_OUTOFMEMORY;

    pexcepinfo->dwHelpContext = 0;
    pexcepinfo->bstrHelpFile = BSTRFROMANSI("");
    if (!pexcepinfo->bstrHelpFile) goto OutOfMemory;

    pexcepinfo->bstrDescription = BSTRFROMRESID(wID);
    if (!pexcepinfo->bstrDescription) goto OutOfMemory;

    return DISP_E_EXCEPTION;

  OutOfMemory:
    if (pexcepinfo->bstrSource)
        SysFreeString(pexcepinfo->bstrSource);
    if (pexcepinfo->bstrHelpFile)
        SysFreeString(pexcepinfo->bstrHelpFile);
    if (pexcepinfo->bstrDescription)
        SysFreeString(pexcepinfo->bstrDescription);

    memset(pexcepinfo, 0, sizeof(EXCEPINFO));
    return E_OUTOFMEMORY;
}



STDMETHODIMP CCircleCoControl::put_BrushType
(
    HATCH_TYPE hv
)
{
    if (m_state.hv != hv) {
	m_state.hv = hv;
	InvalidateControl(NULL);
    }

    return S_OK;

}



STDMETHODIMP CCircleCoControl::get_BrushType
(
    HATCH_TYPE FAR* hv
)
{

    *hv = m_state.hv;
    
    return S_OK;
    
}
