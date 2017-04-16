//=--------------------------------------------------------------------------=
// Circle.Cpp
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
#include "Circle.H"
#include "LocalObj.H"
#include "Util.H"
#include "Globals.H"
#include "Resource.H"

// for ASSERT and FAIL
//
SZTHISFILE



//=--------------------------------------------------------------------------=
// CCircleObject::Create
//=--------------------------------------------------------------------------=
// global static function that creates an instance of the control and returns
// an IUnknown pointer for it.
//
// Parameters:
//    IUnknown *        - [in] controlling unknown for aggregation
//
// Output:
//    IUnknown *        - new object.
//
// Notes:
//
IUnknown *CCircleObject::Create
(
    IUnknown *pUnkOuter
)
{
    // make sure we return the private unknown so that we support aggegation
    // correctly!
    //
    CCircleObject *pNew = new CCircleObject(pUnkOuter);
    
    pNew->m_state.color = COLOR_RED;
    pNew->m_state.bstrName = SysAllocString(L"Circle");
    if (!pNew->m_state.bstrName) {
	delete pNew;
	return NULL;
    }

    return pNew->PrivateUnknown();
}

//=--------------------------------------------------------------------------=
// CCircleObject::CCircleObject
//=--------------------------------------------------------------------------=
// "Being born is like being kidnapped.  And then sold into slavery."
//    - andy warhol (1928 - 87)
//
// Parameters:
//    IUnknown *        - [in]
//
// Notes:
//
#pragma warning(disable:4355)  // using 'this' in constructor
CCircleObject::CCircleObject
(
    IUnknown *pUnkOuter
)
: CAutomationObjectWEvents(pUnkOuter, OBJECT_TYPE_CIRCLEOBJECT, (IDispatch *)this)
{
    // initialize anything here ...
    //
    memset(&m_state, 0, sizeof(CIRCLEOBJECTSTATE));

		
}
#pragma warning(default:4355)  // using 'this' in constructor

//=--------------------------------------------------------------------------=
// CCircleObject::~CircleObject
//=--------------------------------------------------------------------------=
// "We all labour against our own cure, for death is the cure of all diseases"
//    - Sir Thomas Browne (1605 - 82)
//
// Notes:
//
CCircleObject::~CCircleObject ()
{
    // TODO: clean up anything here.
    SysFreeString(m_state.bstrName);

}

//=--------------------------------------------------------------------------=
// CCircleObject::InternalQueryInterface
//=--------------------------------------------------------------------------=
// qi for things only we support.
//
// Parameters:
// Parameters:
//    REFIID        - [in]  interface they want
//    void **       - [out] where they want to put the resulting object ptr.
//
// Output:
//    HRESULT       - S_OK, E_NOINTERFACE
//
// Notes:
//
HRESULT CCircleObject::InternalQueryInterface
(
    REFIID  riid,
    void  **ppvObjOut
)
{
    IUnknown *pUnk;

    *ppvObjOut = NULL;

    // TODO: if you want to support any additional interfaces, then you should
    // indicate that here.  never forget to call COleControl's version in the
    // case where you don't support the given interface.
    //
    if (DO_GUIDS_MATCH(riid, IID_ICircle)) {
        pUnk = (IUnknown *)(ICircle *)this;
    } else{
        return CAutomationObjectWEvents::InternalQueryInterface(riid, ppvObjOut);
    }

    pUnk->AddRef();
    *ppvObjOut = (void *)pUnk;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CCircleObject::get_Name
//=--------------------------------------------------------------------------=
// retrieves the name
//
// Parameters:
// BSTR*            - [out]  where to put the name
//
// Output:
//    HRESULT       - S_OK, E_OUTOFMEMORY
//
// Notes:
//
STDMETHODIMP CCircleObject::get_Name
(
    BSTR FAR* pbstrName
)
{
    BSTR bstrTemp;

    bstrTemp = SysAllocString(m_state.bstrName);
    
    if (!bstrTemp) {
	return E_OUTOFMEMORY;
    }
    
    *pbstrName = bstrTemp;
    
    return S_OK;

}



//=--------------------------------------------------------------------------=
// CCircleObject::put_Name
//=--------------------------------------------------------------------------=
// changes the name to a new one
//
// Parameters:
// BSTR             - [in]  new name
//
// Output:
//    HRESULT       - S_OK, E_OUTOFMEMORY
//
// Notes:
//
STDMETHODIMP CCircleObject::put_Name
(
    BSTR bstrName
)
{
    BSTR bstrTemp;

    BOOL bOK = m_cpPropNotify.DoOnRequestEdit(DISPID_NAME);
    if (!bOK) {
	return E_FAIL;
    }
    
    bstrTemp = SysAllocString(bstrName);
    if (!bstrTemp) {
	return E_OUTOFMEMORY;
    }
    
    SysFreeString(m_state.bstrName);
    m_state.bstrName = bstrTemp;
    
    m_cpPropNotify.DoOnChanged(DISPID_NAME);

    return S_OK;
}
 
//=--------------------------------------------------------------------------=
// CCircleObject::get_Color
//=--------------------------------------------------------------------------=
// retrieves the object's color
//
// Parameters:
// COLOR_TYPE*     - [out]  color
//
// Output:
//    HRESULT       - S_OK
//
// Notes:
//
STDMETHODIMP CCircleObject::get_Color 
(
    COLOR_TYPE * pCV
)
{
    *pCV = m_state.color;

    return S_OK;
}
 
//=--------------------------------------------------------------------------=
// CCircleObject::put_Color
//=--------------------------------------------------------------------------=
// changes the object's color
//
// Parameters:
// COLOR_TYPE      - [in]  color
//
// Output:
//    HRESULT       - S_OK, E_INVALIDARG
//
// Notes:
//
STDMETHODIMP CCircleObject::put_Color
(
    COLOR_TYPE CV
)
{

    if (CV < COLOR_RED || CV > COLOR_BLUE) {
	return E_INVALIDARG;
    }

    m_state.color = CV;

    m_cpPropNotify.DoOnChanged(DISPID_COLOR);

    return S_OK;
    
}
 
//=--------------------------------------------------------------------------=
// CCircleObject::Act
//=--------------------------------------------------------------------------=
// invokes the object's OnAction event
//
// Parameters:
//
// Output:
//    HRESULT       - 
//
// Notes:
//
STDMETHODIMP CCircleObject::Act
(
    void
)
{

    if (m_state.fActing) {
	return E_FAIL;
    }
    
    m_state.fActing = TRUE;
    EVENTINFO eventinfo;

    eventinfo.dispid = DISPID_ONACTION;
    eventinfo.cParameters = 0;
    eventinfo.rgTypes = NULL;

    FireEvent(&eventinfo);
    m_state.fActing = FALSE;

    return S_OK;

}








