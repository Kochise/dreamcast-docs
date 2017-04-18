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


// Our name: (has to be the same thing as the name of our dynamic coclass)
//
char g_pszWhatAmI [] = "MyCircleContainer";

// Count of instances of us which are alive:
//
long g_cContainers = 0;

// stream name for the runtime object.
//
static WCHAR s_wszRuntimeSaveStream [] = L"RuntimeSaveStream";

// property strings:
//

WCHAR wszTypeLibGuid []=                   L"TypeLibGuid";
WCHAR wszTypeInfoGuid []=                  L"TypeInfoGuid";
WCHAR wszTICookie []=                      L"TICookie";
WCHAR wszCircleNum []=                     L"CircleNumber";
WCHAR wszCircleCount []=                   L"CircleCount";
WCHAR wszBrushType [] =                    L"BrushType";
WCHAR wszX []=                             L"X";
WCHAR wszY []=                             L"Y";
WCHAR wszLeft []=                          L"Left";
WCHAR wszTop []=                           L"Top";
WCHAR wszRight []=                         L"Right";
WCHAR wszBottom []=                        L"Bottom";
WCHAR wszName []=                          L"Name";
WCHAR wszColor []=                         L"Color";


// This class is used to help us persist the information for each circle.
// Normally, you would make the circle do this, but since we also want
// to persist out a lot of ambients, this is easier.

class CPersistenceHelper:
    public IPersistPropertyBag 
{

public:

    ~CPersistenceHelper() { };
    CPersistenceHelper(CIRCLEINFO * pCI) : m_pCI(pCI), m_cRefs(1) { };

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

    // IPersist methods
    //
    STDMETHOD(GetClassID)(LPCLSID lpClassID) { return E_NOTIMPL; };
	    
    // IPersistPropertyBag methods
    //
    STDMETHOD(InitNew)(void) { return E_NOTIMPL; };
    STDMETHOD(Load)(LPPROPERTYBAG pPropBag, LPERRORLOG pErrorLog);
    STDMETHOD(Save)(LPPROPERTYBAG pPropBag, BOOL fClearDirty, BOOL fSaveAllProperties);

  private:
    CIRCLEINFO * m_pCI;
    ULONG m_cRefs;
};




STDMETHODIMP CPersistenceHelper::QueryInterface
(
    REFIID riid, 
    LPVOID FAR* ppvObj
) 
{
    if (DO_GUIDS_MATCH(IID_IPersistPropertyBag, riid))
	*((IUnknown **)ppvObj) = (IUnknown *)(IPersistPropertyBag *)this;
    else if (DO_GUIDS_MATCH(IID_IUnknown, riid))
	*((IUnknown **)ppvObj) = (IUnknown *)this;
    else
	return E_NOINTERFACE;
    
    // addref the object
    //
    (*((IUnknown **)ppvObj))->AddRef();
    return S_OK;
}


STDMETHODIMP CPersistenceHelper::Load
(
    LPPROPERTYBAG pPropBag, 
    LPERRORLOG pErrorLog
)
{
    // Loads all the ambients of the circle, plus its color and name
    
    HRESULT hr;
    VARIANT v;
    
    v.vt = VT_I4;
    hr = pPropBag->Read(wszLeft, &v, pErrorLog);
    RETURN_ON_FAILURE(hr);
    m_pCI->lLeft = v.lVal;

    hr = pPropBag->Read(wszRight, &v, pErrorLog);
    RETURN_ON_FAILURE(hr);
    m_pCI->lRight = v.lVal;

    hr = pPropBag->Read(wszTop, &v, pErrorLog);
    RETURN_ON_FAILURE(hr);
    m_pCI->lTop = v.lVal;

    hr = pPropBag->Read(wszBottom, &v, pErrorLog);
    RETURN_ON_FAILURE(hr);
    m_pCI->lBottom = v.lVal;

    hr = pPropBag->Read(wszX, &v, pErrorLog);
    RETURN_ON_FAILURE(hr);
    m_pCI->lCX = v.lVal;

    hr = pPropBag->Read(wszY, &v, pErrorLog);
    RETURN_ON_FAILURE(hr);
    m_pCI->lCY = v.lVal;

    hr = pPropBag->Read(wszColor, &v, pErrorLog);
    RETURN_ON_FAILURE(hr);
    m_pCI->CV = (COLOR_TYPE)v.lVal;
    
    v.vt = VT_BSTR;
    hr = pPropBag->Read(wszName, &v, pErrorLog);
    RETURN_ON_FAILURE(hr);
    m_pCI->bstrName = v.bstrVal;

    return S_OK;
}


STDMETHODIMP CPersistenceHelper::Save
(
    LPPROPERTYBAG pPropBag, 
    BOOL fClearDirty, 
    BOOL fSaveAllProperties
)
{
    // we always save out all properties, regardless of the default switch
    HRESULT hr;
    VARIANT v;
	
    v.vt = VT_I4;
    v.lVal = m_pCI->lLeft;
    hr = pPropBag->Write(wszLeft, &v);
    RETURN_ON_FAILURE(hr);

    v.lVal = m_pCI->lRight;
    hr = pPropBag->Write(wszRight, &v);
    RETURN_ON_FAILURE(hr);

    v.lVal = m_pCI->lTop;
    hr = pPropBag->Write(wszTop, &v);
    RETURN_ON_FAILURE(hr);

    v.lVal = m_pCI->lBottom;
    hr = pPropBag->Write(wszBottom, &v);
    RETURN_ON_FAILURE(hr);

    v.lVal = m_pCI->lCX;
    hr = pPropBag->Write(wszX, &v);
    RETURN_ON_FAILURE(hr);

    v.lVal = m_pCI->lCY;
    hr = pPropBag->Write(wszY, &v);
    RETURN_ON_FAILURE(hr);

    v.lVal = m_pCI->CV;
    hr = pPropBag->Write(wszColor, &v);
    RETURN_ON_FAILURE(hr);
    
    v.vt = VT_BSTR;
    v.bstrVal = m_pCI->bstrName;
    hr = pPropBag->Write(wszName, &v);
    RETURN_ON_FAILURE(hr);

    return S_OK;
}

	

//=--------------------------------------------------------------------------=
// CCircleCoControl::Create
//=--------------------------------------------------------------------------=
// global static function that creates an instance of the control an returns
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
IUnknown *CCircleCoControl::Create
(
    IUnknown *pUnkOuter
)
{
    // make sure we return the private unknown so that we support aggegation
    // correctly!
    //
    CCircleCoControl *pNew = new CCircleCoControl(pUnkOuter);
    return pNew->PrivateUnknown();
}

//=--------------------------------------------------------------------------=
// CCircleCoControl::CCircleCoControl
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
CCircleCoControl::CCircleCoControl
(
    IUnknown *pUnkOuter
)
: COleControl(pUnkOuter, OBJECT_TYPE_CTLCIRCLECO, (IDispatch *)this)
{

    memset(&m_state, 0, sizeof(CIRCLECOCTLSTATE));
    m_state.iSelectedCircle = -1;
    m_state.hv = HATCH_NONE;
    InterlockedIncrement(&g_cContainers);

}
#pragma warning(default:4355)  // using 'this' in constructor

//=--------------------------------------------------------------------------=
// CCircleCoControl::~CCircleCoControl
//=--------------------------------------------------------------------------=
// "We all labour against our own cure, for death is the cure of all diseases"
//    - Sir Thomas Browne (1605 - 82)
//
// Notes:
//
CCircleCoControl::~CCircleCoControl ()
{

    QUICK_RELEASE(m_state.pServiceProvider);
    QUICK_RELEASE(m_state.pctiCoClass);
    QUICK_RELEASE(m_state.pRuntimeDispinterface);
    QUICK_RELEASE(m_state.pCircleTI);

    for (int i = 0; i < MAXCIRCLES; i++) {
	if (m_state.rgCircles[i].pPNS) {
	    DetachSink(i);
	}
	QUICK_RELEASE(m_state.rgCircles[i].pCircle);
	if (m_state.rgCircles[i].bstrName) {
	    SysFreeString(m_state.rgCircles[i].bstrName);
	}
    }

    EnterCriticalSection(&g_CriticalSection);
    g_cContainers--;
    if (!g_cContainers && g_pTypeInfo) {
        g_pTypeInfo->Release();
        g_pTypeInfo = NULL;
    }
    LeaveCriticalSection(&g_CriticalSection);

}

//=--------------------------------------------------------------------------=
// CConnectionDesigner::InitializeNewState
//=--------------------------------------------------------------------------=
// called from InitNew()
//
// Parameters:
//    none
//
// Output:
//    BOOL          - false means failure
//
// Notes:
//
BOOL CCircleCoControl::InitializeNewState
(
    void
)
{
    // create the three guids that we'll need for our typeinfo work
    //
    if (FAILED(CoCreateGuid(&m_state.guidTypeLib))) return FALSE;
    if (FAILED(CoCreateGuid(&m_state.guidTypeInfo))) return FALSE;

    m_state.dwTICookie = 0;


    // Tell the host to select the main object
    MaybeSelectionChanged(-1, TRUE);

    return TRUE;
}

//=--------------------------------------------------------------------------=
// CCircleCoControl:RegisterClassData
//=--------------------------------------------------------------------------=
// register the window class information for your control here.
// this information will automatically get cleaned up for you on DLL shutdown.
//
// Output:
//    BOOL            - FALSE means fatal error.
//
// Notes:
//
BOOL CCircleCoControl::RegisterClassData
(
    void
)
{
    WNDCLASS wndclass;

    // TODO: register any additional information you find interesting here.
    //       this method is only called once for each type of control
    //
    memset(&wndclass, 0, sizeof(WNDCLASS));
    wndclass.style          = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
    wndclass.lpfnWndProc    = COleControl::ControlWindowProc;
    wndclass.hInstance      = g_hInstance;
    wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wndclass.lpszClassName  = WNDCLASSNAMEOFCONTROL(OBJECT_TYPE_CTLCIRCLECO);

    return RegisterClass(&wndclass);
}

//=--------------------------------------------------------------------------=
// CCircleCoControl::BeforeCreateWindow
//=--------------------------------------------------------------------------=
// called just before the window is created.  Great place to set up the
// window title, etc, so that they're passed in to the call to CreateWindowEx.
// speeds things up slightly.
//
// Parameters:
//    DWORD *            - [out] dwWindowFlags
//    DWORD *            - [out] dwExWindowFlags
//    LPSTR              - [out] name of window to create
//
// Output:
//    BOOL               - false means fatal error
//
// Notes:
//
BOOL CCircleCoControl::BeforeCreateWindow
(
    DWORD *pdwWindowStyle,
    DWORD *pdwExWindowStyle,
    LPSTR  pszWindowTitle
)
{

    if (!GetAmbientProperty(DISPID_AMBIENT_USERMODE, VT_BOOL, (void *)&m_state.bUserMode)) {
	MessageBox(NULL,"Unable to retrieve ambient property","",MB_OK);
        return FALSE;
    }


    return TRUE;
}

//=--------------------------------------------------------------------------=
// CCircleCoControl::InternalQueryInterface
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
HRESULT CCircleCoControl::InternalQueryInterface
(
    REFIID  riid,
    void  **ppvObjOut
)
{
    IUnknown *pUnk;

    *ppvObjOut = NULL;

    if (DO_GUIDS_MATCH(riid, IID_IProvideDynamicClassInfo)) {
        pUnk = (IUnknown *)(IProvideDynamicClassInfo *)this;
    } else{
    if (DO_GUIDS_MATCH(riid, IID_ISelectionContainer)) {
	// we need to support ISC for the STrackSelection service to work
	pUnk = (IUnknown *)(ISelectionContainer *)this; 
    } else {
        return COleControl::InternalQueryInterface(riid, ppvObjOut);
    }
    }

    pUnk->AddRef();
    *ppvObjOut = (void *)pUnk;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CCircleCoControl::LoadTextState
//=--------------------------------------------------------------------------=
// load in our text state for this control.
//
// Parameters:
//    IPropertyBag *        - [in] property bag to read from
//    IErrorLog *           - [in] errorlog object to use with proeprty bag
//
// Output:
//    HRESULT
//
// Notes:
//    - NOTE: if you have a binary object, then you should pass an unknown
//      pointer to the property bag, and it will QI it for IPersistStream, and
//      get said object to do a Load()
//
STDMETHODIMP CCircleCoControl::LoadTextState
(
    IPropertyBag *pPropertyBag,
    IErrorLog    *pErrorLog
)
{
    VARIANT v;
    HRESULT hr;
    WCHAR   wszTmp[25];
    char    szTmp[25];


    // load in typeinfo information we saved out [guids and cookie]
    //
    v.vt = VT_BSTR;
    v.bstrVal = NULL;
    hr = pPropertyBag->Read(wszTypeLibGuid, &v, pErrorLog);
    if (FAILED(hr)) {
        FAIL("We should really have this guid [benign assertion, not a bug]");
        m_state.guidTypeLib = IID_NULL;
    } else  {
        CLSIDFromString(v.bstrVal, &m_state.guidTypeLib);
        SysFreeString(v.bstrVal);
    }
    v.bstrVal = NULL;
    hr = pPropertyBag->Read(wszTypeInfoGuid, &v, pErrorLog);
    if (FAILED(hr)) {
        FAIL("We should really have this guid [benign assertion, not a bug]");
        m_state.guidTypeLib = IID_NULL;
    } else  {
        CLSIDFromString(v.bstrVal, &m_state.guidTypeInfo);
        SysFreeString(v.bstrVal);
    }

    // cookie
    v.vt = VT_I4;
    v.lVal = 0;
    pPropertyBag->Read(wszTICookie, &v, pErrorLog);
    m_state.dwTICookie = (DWORD)v.lVal;

    pPropertyBag->Read(wszCircleNum, &v, pErrorLog);
    m_state.dwCircleNum = (DWORD)v.lVal;

    pPropertyBag->Read(wszCircleCount, &v, pErrorLog);
    m_state.dwCircleCount = (DWORD)v.lVal;

    pPropertyBag->Read(wszBrushType, &v, pErrorLog);
    m_state.hv = (HATCH_TYPE)v.lVal;

    v.vt = VT_UNKNOWN;
    for (int i = 0; i < (int) m_state.dwCircleNum; i++) {

	// this is the heading under which we saved out our circle
        wsprintf(szTmp, "Circle%d", i);
	MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wszTmp, sizeof(wszTmp) / sizeof(WCHAR));
	
	IUnknown * pPH = (IUnknown *) new CPersistenceHelper(&(m_state.rgCircles[i]));
	RETURN_ON_NULLALLOC(pPH);
	
        RETURN_ON_NULLALLOC(pPH);
        v.punkVal = pPH;

        // try to read it in!
        //
        hr = pPropertyBag->Read(wszTmp, &v, pErrorLog);
	pPH->Release();
	RETURN_ON_FAILURE(hr);

	hr = CreateObject(i);
	if (FAILED(hr)) {
	    m_state.rgCircles[i].bHaveIt = FALSE;
	    SysFreeString(m_state.rgCircles[i].bstrName);
	    // this will tell our host that our typeinfo is different from it's cache
	    // and that it needs to ask for it from us again before going into 
	    // runmode
	    m_state.dwTICookie++;
	}

    }
    
    MaybeSelectionChanged(-1, TRUE);

    return S_OK;
}

//=--------------------------------------------------------------------------=
// CCircleCoControl::LoadBinaryState
//=--------------------------------------------------------------------------=
// loads in our binary state using streams.
//
// Parameters:
//    IStream *            - [in] stream to write to.
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CCircleCoControl::LoadBinaryState
(
    IStream *pStream
)
{
    HRESULT hr;

    // In a real object this would be implemented to make as few calls to
    // Read as possible.  But for simplicity and clarity we read in
    // everything individually

    hr = pStream->Read(&m_state.guidTypeLib, sizeof(GUID), NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Read(&m_state.guidTypeInfo, sizeof(GUID), NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Read(&m_state.dwCircleNum, sizeof(DWORD), NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Read(&m_state.dwCircleCount, sizeof(DWORD), NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Read(&m_state.hv, sizeof(DWORD), NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Read(&m_state.rgCircles, sizeof(CIRCLEINFO) * MAXCIRCLES, NULL);
    RETURN_ON_FAILURE(hr);

    for (int i= 0; i < MAXCIRCLES; i ++) {
	m_state.rgCircles[i].pCircle = NULL;
	m_state.rgCircles[i].bstrName = NULL;
	if (!m_state.rgCircles[i].bHaveIt) {
	    continue;
	}
	UINT uiSize;
	hr = pStream->Read(&uiSize, sizeof(UINT), NULL);
	m_state.rgCircles[i].bstrName = SysAllocStringLen(NULL,uiSize);
	hr = pStream->Read((LPBYTE)m_state.rgCircles[i].bstrName, uiSize, NULL);
	RETURN_ON_FAILURE(hr);

	hr = CreateObject(i);
	if (FAILED(hr)) {
	    m_state.rgCircles[i].bHaveIt = FALSE;
	    SysFreeString(m_state.rgCircles[i].bstrName);
	    // this will tell our host that our typeinfo is different from it's cache
	    // and that it needs to ask for it from us again before going into 
	    // runmode
	    m_state.dwTICookie++;
	}
    }

    return S_OK;
}

//=--------------------------------------------------------------------------=
// CCircleCoControl::SaveTextState
//=--------------------------------------------------------------------------=
// saves out the text state for this control using a property bag.
//
// Parameters:
//    IPropertyBag *        - [in] the property bag with which to work.
//    BOOL                  - [in] if TRUE, then write out ALL properties, even
//                            if they're their the default value ...
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CCircleCoControl::SaveTextState
(
    IPropertyBag *pPropertyBag,
    BOOL          fWriteDefaults
)
{

    // we always write out all properties
    
    HRESULT hr;
    VARIANT v;
    WCHAR wszTmp[25];
    char szTmp[25];
    LPWSTR pwsz;

    v.vt = VT_BSTR;
    StringFromCLSID(m_state.guidTypeLib, &pwsz);
    v.bstrVal = COPYBSTR(pwsz);
    CoTaskMemFree(pwsz);
    if (!v.bstrVal) return E_OUTOFMEMORY;
    hr = pPropertyBag->Write(wszTypeLibGuid, &v);
    SysFreeString(v.bstrVal);
    RETURN_ON_FAILURE(hr);

    StringFromCLSID(m_state.guidTypeInfo, &pwsz);
    v.bstrVal = COPYBSTR(pwsz);
    CoTaskMemFree(pwsz);
    if (!v.bstrVal) return E_OUTOFMEMORY;
    hr = pPropertyBag->Write(wszTypeInfoGuid, &v);
    SysFreeString(v.bstrVal);
    RETURN_ON_FAILURE(hr);

    // cookie
    v.vt = VT_I4;
    v.lVal = (LONG)m_state.dwTICookie;
    hr = pPropertyBag->Write(wszTICookie, &v);
    RETURN_ON_FAILURE(hr);

    v.lVal = (LONG)m_state.dwCircleNum;
    hr = pPropertyBag->Write(wszCircleNum, &v);
    RETURN_ON_FAILURE(hr);

    v.lVal = (LONG)m_state.dwCircleCount;
    hr = pPropertyBag->Write(wszCircleCount, &v);
    RETURN_ON_FAILURE(hr);

    v.lVal = (LONG)m_state.hv;
    hr = pPropertyBag->Write(wszBrushType, &v);
    RETURN_ON_FAILURE(hr);

    v.vt = VT_UNKNOWN;
    int x = 0;
    for (int i = 0; i < MAXCIRCLES; i++ ) {
	if (!m_state.rgCircles[i].bHaveIt) {
	    continue;
	}
	IUnknown * pPH = (IUnknown *) new CPersistenceHelper(&(m_state.rgCircles[i]));
	RETURN_ON_NULLALLOC(pPH);

	v.punkVal = pPH;
        wsprintf(szTmp, "Circle%d", x);
        MultiByteToWideChar(CP_ACP, 0, szTmp, -1, wszTmp, sizeof(wszTmp) / sizeof(WCHAR));
        hr = pPropertyBag->Write(wszTmp, &v);
	pPH->Release();
        RETURN_ON_FAILURE(hr);
	x++;
    }

    return S_OK;
}

//=--------------------------------------------------------------------------=
// CCircleCoControl::SaveBinaryState
//=--------------------------------------------------------------------------=
// save out the binary state for this control, using the given IStream object.
//
// Parameters:
//    IStream  *             - [in] save to which you should save.
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CCircleCoControl::SaveBinaryState
(
    IStream *pStream
)
{
    HRESULT hr;

    hr = pStream->Write(&m_state.guidTypeLib, sizeof(GUID), NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Write(&m_state.guidTypeInfo, sizeof(GUID), NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Write(&m_state.dwCircleNum, sizeof(DWORD), NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Write(&m_state.dwCircleCount, sizeof(DWORD), NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Write(&m_state.hv, sizeof(DWORD), NULL);
    RETURN_ON_FAILURE(hr);

    hr = pStream->Write(&m_state.rgCircles, sizeof(CIRCLEINFO) * MAXCIRCLES, NULL);
    RETURN_ON_FAILURE(hr);

    for (int i= 0; i < MAXCIRCLES; i ++) {
	if (!m_state.rgCircles[i].bHaveIt) {
	    continue;
	}
	UINT uiSize = SysStringByteLen(m_state.rgCircles[i].bstrName) + sizeof(WCHAR);
	hr = pStream->Write(&uiSize, sizeof(UINT), NULL);
	RETURN_ON_FAILURE(hr);
	hr = pStream->Write((LPBYTE)m_state.rgCircles[i].bstrName ,uiSize,NULL);
	RETURN_ON_FAILURE(hr);
    }
    
    return S_OK;
}


// Convert from Virtual (0 to 1000) to real (Client) coordinates

void ConvertCoordsV2R
(
    int * piLeft,
    int * piTop, 
    int iLeft, 
    int iTop, 
    RECTL & rcView
)
{

    *piLeft = iLeft * (rcView.right - rcView.left) / AREASIZE + rcView.left;
    *piTop = iTop * (rcView.bottom - rcView.top) / AREASIZE + rcView.top;

}

// Convert from real (client) to virtual (0 to 1000) coordinates
void ConvertCoordsR2V
(
    int * piLeft,
    int * piTop, 
    int iLeft, 
    int iTop, 
    RECTL & rcView
)
{

    if (rcView.right == rcView.left) {
	*piLeft = 0;
    }
    else {
	*piLeft = (iLeft - rcView.left) * AREASIZE / (rcView.right - rcView.left);
    }

    if (rcView.bottom == rcView.top) {
	*piTop = 0;
    }
    else {
	*piTop = (iTop - rcView.top) * AREASIZE / (rcView.bottom - rcView.top);
    }

}


//=--------------------------------------------------------------------------=
// CCircleCoControl::OnDraw
//=--------------------------------------------------------------------------=
// "I don't very much enjoy looking at paintings in general.  i know too
//  much about them.  i take them apart."
//    - georgia o'keeffe (1887-1986)
//
// Parameters:
//    DWORD              - [in]  drawing aspect
//    HDC                - [in]  HDC to draw to
//    LPCRECTL           - [in]  rect we're drawing to
//    LPCRECTL           - [in]  window extent and origin for meta-files
//    HDC                - [in]  HIC for target device
//    BOOL               - [in]  can we optimize dc handling?
//
// Output:
//    HRESULT
//
// Notes:
//
HRESULT CCircleCoControl::OnDraw
(
    DWORD    dvAspect,
    HDC      hdcDraw,
    LPCRECTL prcBounds,
    LPCRECTL prcWBounds,
    HDC      hicTargetDevice,
    BOOL     fOptimize
)
{

    HRESULT hr;

    // save our size information
    m_state.rcLastView = *prcBounds;
    
    HPEN hOldPen = NULL;
    HBRUSH hOldBrush = NULL;

    HPEN hBlackPen = CreatePen(PS_SOLID, 5, RGB(0,0,0));
    RETURN_ON_NULLALLOC(hBlackPen);

    COLORREF crRed, crGreen, crBlue;
    
    crRed = RGB(255,0,0);
    crGreen = RGB(0,255,0);
    crBlue = RGB(0,0,255);
    
    int iStyle;
    BOOL bSolidBrush;

    if (m_state.hv == HATCH_NONE) {
	bSolidBrush = TRUE;
    }
    else {
	bSolidBrush = FALSE;
	switch (m_state.hv) {
	case HATCH_DIAGONAL1 :  iStyle = HS_BDIAGONAL; break;
	case HATCH_DIAGONAL2:   iStyle = HS_FDIAGONAL; break;
	case HATCH_CROSS:       iStyle = HS_CROSS; break;
	case HATCH_DIAGCROSS:   iStyle = HS_DIAGCROSS; break;
	case HATCH_HORIZONTAL:  iStyle = HS_HORIZONTAL; break;
	case HATCH_VERTICAL:    iStyle = HS_VERTICAL; break;
	default:
	    ASSERT(0, "Bad brush type");
	}
    }

    
    struct ColorTable {
	COLOR_TYPE cv;
	COLORREF    cr;
	HPEN       hPen;
	HBRUSH     hBrush;
    } rgTable[3] = {
	{COLOR_RED, RGB(255,0,0), NULL, NULL},
	{COLOR_BLUE, RGB(0,0,255), NULL, NULL},
	{COLOR_GREEN, RGB(0,255,0), NULL, NULL}
    };
    
    for (int i = 0; i<MAXCIRCLES; i++) {
	CIRCLEINFO * pCI = &(m_state.rgCircles[i]);
	if (!pCI->bHaveIt) {
	    continue;
	}
	
	int iLeft, iRight, iTop, iBottom;
	ConvertCoordsV2R(&iLeft, &iTop, pCI->lLeft, pCI->lTop, m_state.rcLastView);
	ConvertCoordsV2R(&iRight, &iBottom, pCI->lRight, pCI->lBottom, m_state.rcLastView);
		
	int c;
	for (c = 0; c< 3 && pCI->CV != rgTable[c].cv; c++);
	ASSERT(pCI->CV == rgTable[c].cv, "Bad color value.");
	
	HPEN hPen;

	if (i != m_state.iSelectedCircle) {
	    if (!rgTable[c].hPen) {
		rgTable[c].hPen = CreatePen(PS_SOLID, 1, rgTable[c].cr);
		if (!rgTable[c].hPen) {
		    hr = E_OUTOFMEMORY;
		    goto CleanUp;
		}
	    }
	    hPen = rgTable[c].hPen;
	}
	else {
	    hPen = hBlackPen;
	}
	if (!rgTable[c].hBrush) {
	    if (bSolidBrush) {
		rgTable[c].hBrush = CreateSolidBrush(rgTable[c].cr);
	    } 
	    else {
		rgTable[c].hBrush = CreateHatchBrush(iStyle, rgTable[c].cr);
	    }
	    if (!rgTable[c].hBrush) {
		hr = E_OUTOFMEMORY;
		goto CleanUp;
	    }
	}

	if (!hOldPen) {
//[10/7/96, IvoSa]	    hOldPen = SelectObject(hdcDraw, hPen);
	    hOldPen = (struct HPEN__ *) SelectObject(hdcDraw, hPen);
//[10/7/96, IvoSa]	    hOldBrush = SelectObject(hdcDraw, rgTable[c].hBrush);
	    hOldBrush = (struct HBRUSH__ *) SelectObject(hdcDraw, rgTable[c].hBrush);
	    if (!hOldPen || !hOldBrush) {
		hr = E_OUTOFMEMORY;
		goto CleanUp;
	    }
	}
	else {
	    if (
		!SelectObject(hdcDraw, hPen)
		||
		!SelectObject(hdcDraw, rgTable[c].hBrush)
		) {
		hr = E_OUTOFMEMORY;
		goto CleanUp;
	    }
	}
	
	if (!Ellipse(hdcDraw, iLeft, iTop, iRight, iBottom)) {
	    hr = E_FAIL;
	    goto CleanUp;
	}
    }
    
    hr = S_OK;

CleanUp:
    
    if (hOldPen) {
	SelectObject(hdcDraw,hOldPen);
    }
    if (hOldBrush) {
	SelectObject(hdcDraw,hOldBrush);
    }

    DeleteObject(hBlackPen);

    for (int c = 0; c<3; c++) {
	if (rgTable[c].hPen) {
	    DeleteObject(rgTable[c].hPen);
	}
	if (rgTable[c].hBrush) {
	    DeleteObject(rgTable[c].hBrush);
	}
    }
    
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CCircleCoControl::WindowProc
//=--------------------------------------------------------------------------=
// window procedure for this control.  nothing terribly exciting.
//
// Parameters:
//     see win32sdk on window procs [sans HWND -- it's in m_hwnd if you have one]
//
// Notes:
//
LRESULT CCircleCoControl::WindowProc
(
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam
)
{
    // TODO: handle any messages here, like in a normal window
    // proc.  note that for special keys, you'll want to override and
    // implement OnSpecialKey.
    // if you're a windowed OCX, you should be able to use any of the
    // win32 API routines except for SetFocus.  you should always use
    // OcxSetFocus()
    //

    switch (msg) {
    case WM_RBUTTONUP: {
	if (!m_state.bUserMode) {
	    AddDeleteCircle((DWORD)LOWORD(lParam), (DWORD)HIWORD(lParam));
	    return 0;
	}
	break;
    }
    case WM_LBUTTONUP : {
	if (m_state.bUserMode) {
	    TryToFireEvent((DWORD)LOWORD(lParam), (DWORD)HIWORD(lParam));
	}
	else {
	    SelectCircle((DWORD)LOWORD(lParam), (DWORD)HIWORD(lParam));
	}
	return 0;
    }
    case WM_LBUTTONDBLCLK : {
	if (!m_state.bUserMode) {
	    TryToViewCode((DWORD)LOWORD(lParam), (DWORD)HIWORD(lParam));
	    return 0;
	}
	break;
    }
    }
    return OcxDefWindowProc(msg, wParam, lParam);
}


//=--------------------------------------------------------------------------=
// CCircleCoControl::GetClassInfo    [IProvideDynamicClassInfo]
//=--------------------------------------------------------------------------=
// returns our current type info
//
// Parameters:
//    ITypeInfo **            - [out] current type info
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CCircleCoControl::GetClassInfo
(
    ITypeInfo **ppTypeInfo
)
{
    return COleControl::GetClassInfo(ppTypeInfo);
}

//=--------------------------------------------------------------------------=
// CCircleCoControl::GetDynamicClassInfo    [IProvideDynamicClassInfo]
//=--------------------------------------------------------------------------=
// returns our current type info
//
// Parameters:
//    ITypeInfo **            - [out]
//    DWORD *                 - [out] cookie.
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CCircleCoControl::GetDynamicClassInfo
(
    ITypeInfo **ppTypeInfo,
    DWORD      *pdwCookie
)
{


    HRESULT hr;
    
    if (pdwCookie)
        *pdwCookie = m_state.dwTICookie;

    if (!ppTypeInfo)
        return S_OK;

    hr = CreateRuntimeTypeInfo();
    RETURN_ON_FAILURE(hr);

    // now just pass this out and addref it.
    //
    return m_state.pctiCoClass->QueryInterface(IID_ITypeInfo, (void **)ppTypeInfo);

}

//=--------------------------------------------------------------------------=
// CCircleCoControl::FreezeShape    [IProvideDynamicClassInfo]
//=--------------------------------------------------------------------------=
// you're not allowed to change your type info any more.
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CCircleCoControl::FreezeShape
(
    void
)
{
    // we don't change our type info when this matters
    //
    return S_OK;
}



int CCircleCoControl::GetIndexFromName
(
    LPSTR pszQuery
)
{
    int iFound = -1;
    
    for (int i = 0; i < MAXCIRCLES && iFound == -1; i++) {
	if (!m_state.rgCircles[i].pCircle) {
	    continue;
	}
	LPSTR pszName;
	if (!MiscGetAnsiHeapStr(&pszName, m_state.rgCircles[i].bstrName)) {
	    return -1;
	}
	if (!lstrcmpi(pszQuery, pszName)) {
	    iFound = i;
	}
	HeapFree(g_hHeap, 0, pszName);
    }

    return iFound;
}


// Selects a circle found at the given client coordinates
void CCircleCoControl::SelectCircle
(
    DWORD dwX,
    DWORD dwY
)
{

    int index = GetIndexFromCoords(dwX,dwY);
    MaybeSelectionChanged(index, FALSE);
}
	


// returns the index of a circle enclosing the give client coordinates
// or -1 if none
int CCircleCoControl::GetIndexFromCoords
(
    DWORD dwX,
    DWORD dwY
)
{
    int iX, iY;

    ConvertCoordsR2V(&iX, &iY, (int) dwX, (int) dwY, m_state.rcLastView);

    long lInCircleSquare = CIRCLERADIUS * CIRCLERADIUS;
    
    for (int i = 0; i < MAXCIRCLES; i++) {
	CIRCLEINFO * pCI = &(m_state.rgCircles[i]);
	
	if (!pCI->bHaveIt) {
	    continue;
	}
	
	long lDist = 
	    (iX - pCI->lCX) * (iX - pCI->lCX) + 
	    (iY - pCI->lCY) * (iY - pCI->lCY);

	if (lDist <= lInCircleSquare) {
	    return i;
	}
    }
    return -1;
}



void CCircleCoControl::TryToViewCode
(
    DWORD dwX,
    DWORD dwY
)
{

    HRESULT hr;
    ICodeNavigate * pNavigate;

    int index = GetIndexFromCoords(dwX, dwY);
    
    if (!m_state.pServiceProvider) {
	hr = m_pClientSite->QueryInterface(IID_IServiceProvider, 
				      (void**) &(m_state.pServiceProvider));
	if (FAILED(hr)) return;
    }
    
    hr = m_state.pServiceProvider->QueryService(SID_SCodeNavigate, IID_ICodeNavigate, 
						(void **) &pNavigate);
    if (FAILED(hr)) return;

    if (index == -1) {
	MAKE_WIDEPTR_FROMANSI(pwstr, g_pszWhatAmI);
	if (pwstr) {
	    pNavigate->DisplayDefaultEventHandler(pwstr);
	}
    }
    else {
	pNavigate->DisplayDefaultEventHandler(m_state.rgCircles[index].bstrName);
    }
    
    pNavigate->Release();

}
	

// runmode procedure invoked when a user clicks on a circle
// the given coords are client coords

void CCircleCoControl::TryToFireEvent
(
    DWORD dwX,
    DWORD dwY
)
{

    HRESULT hr;
    int index = GetIndexFromCoords(dwX, dwY);

    MaybeSelectionChanged(index, FALSE);
    
    if (index != -1) {
	ICircle * pCircle;
	if (SUCCEEDED(m_state.rgCircles[index].pCircle->
		      QueryInterface(IID_ICircle, (void **)&pCircle))) {
	    hr = pCircle->Act();
	    pCircle->Release();
	    // Now, fire our own color event:
	    if (SUCCEEDED(hr)) {
		EVENTINFO eventinfo;
		VARTYPE rgI2[1] = { VT_I2 };
		
		eventinfo.dispid = DISPID_ONCOLORACTED;
		eventinfo.cParameters = 1;
		eventinfo.rgTypes = rgI2;
		
		FireEvent (&eventinfo, m_state.rgCircles[index].CV);
	    }
	    
	}
	return;
    }
}


// Called whenever a new object may be selected
// index is the index of the circle, or -1 if none
// bForceRedraw indicates whether to
//   * - redraw the window
//   * - notify the host of a change in selection
// if the selection really is different from the old one (false)
// or always (true)

void CCircleCoControl::MaybeSelectionChanged
(
    int index,
    BOOL bForceRedraw
)
{

    if (m_state.iSelectedCircle != index) {
	bForceRedraw = TRUE;
	m_state.iSelectedCircle = index;
    }
    if (bForceRedraw) {
	if (!m_state.bUserMode) {
	    // we only tell the host of a new selection in design mode
	    CallOnSelectChange((ISelectionContainer*)this);
	}
	InvalidateControl(NULL);
    }
}


// Called whenever the user clicks the right mouse button which
// indicates a circle addition/deletion
// the coordinates are in a client mapping

void CCircleCoControl::AddDeleteCircle
(
    DWORD dwX,
    DWORD dwY
)
{
    int iX, iY;
    int iFree = -1;

    ConvertCoordsR2V(&iX, &iY, (int) dwX, (int) dwY, m_state.rcLastView);

    long lInCircleSquare = CIRCLERADIUS * CIRCLERADIUS;

    // used to tell if the new circle would be too close to another
    long lTwoCircleSeparation = 4*lInCircleSquare;
    
    for (int i = 0; i < MAXCIRCLES; i++) {
	CIRCLEINFO * pCI = &(m_state.rgCircles[i]);
	
	if (!pCI->bHaveIt) {
	    // remember the free spot for later
	    iFree = i;
	    continue;
	}
	
	long lDist = 
	    (iX - pCI->lCX) * (iX - pCI->lCX) + 
	    (iY - pCI->lCY) * (iY - pCI->lCY);

	if (lDist <= lInCircleSquare) {
	    // if the point is within a circle, try to delete it
	    DeleteCircle(i);
	    return;
	}
	
	if (lDist <= lTwoCircleSeparation) {
	    // if the circles would overlap, don't allow it
	    MaybeSelectionChanged(-1, FALSE);
	    MessageBox (NULL,"Too close","",MB_OK);
	    return;
	}
    }
    
    if (iFree == -1) {
	// if we already have 10 circles, don't allow a new one
	MaybeSelectionChanged(-1, FALSE);
	MessageBox (NULL,"Too many circles","",MB_OK);
	return;
    }    
    
    char buff[50];
    while (TRUE) {
	// generate a new, unique name
	wsprintf(buff,"Circle%d",m_state.dwCircleNum++);
	
	int iFound = GetIndexFromName(buff);
	if (iFound == -1) {
	    break;
	}
    }
    
    BSTR  bstrNewName = (BSTR )MakeWideStrFromAnsi(buff,STR_BSTR);
    if (!bstrNewName) return;
    m_state.rgCircles[iFree].bstrName = bstrNewName;
    m_state.rgCircles[iFree].bHaveIt = TRUE;
    m_state.rgCircles[iFree].pCircle = NULL;
    m_state.rgCircles[iFree].lCX = iX;
    m_state.rgCircles[iFree].lCY = iY;
    m_state.rgCircles[iFree].lLeft = iX - CIRCLERADIUS;
    m_state.rgCircles[iFree].lTop = iY - CIRCLERADIUS;
    m_state.rgCircles[iFree].lRight = iX + CIRCLERADIUS;
    m_state.rgCircles[iFree].lBottom = iY + CIRCLERADIUS;
    m_state.rgCircles[iFree].CV = COLOR_RED;
    
    if (!SUCCEEDED(CreateObject(iFree))) {
	SysFreeString(bstrNewName);
	m_state.rgCircles[iFree].bHaveIt = FALSE;
	return;
    }
    
    m_state.dwCircleCount ++;
    MaybeSelectionChanged(iFree, FALSE);
    
    // mark ourselves as dirty so the new circle will be saved out
    m_fDirty = TRUE;
}

// attempts to delete the circle indicated by index
void CCircleCoControl::DeleteCircle
(
    int index
)
{

    ASSERT(m_state.rgCircles[index].bHaveIt,"Trying to delete a circle I don't have");
    
    DetachSink(index);
    DeleteFromTypeInfo(index);

    SysFreeString(m_state.rgCircles[index].bstrName);
    m_state.rgCircles[index].bstrName = NULL;
    m_state.rgCircles[index].bHaveIt = FALSE;
    QUICK_RELEASE(m_state.rgCircles[index].pCircle);
    m_state.rgCircles[index].pCircle = NULL;
    m_state.dwCircleCount --;
    MaybeSelectionChanged(-1, TRUE);
    m_fDirty = TRUE;

}


//=--------------------------------------------------------------------------=
// CCircleCoControl::AmbientPropertyChagned
//=--------------------------------------------------------------------------=
// an ambient has changed
//
// Parameters:
//    DISPID                    - [in]  dispid that changed
//
// Notes:
//
void CCircleCoControl::AmbientPropertyChanged
(
    DISPID dispid
)
{

    if (dispid != DISPID_AMBIENT_USERMODE)
        return;

    // get the new value from the host
    //
    if (!GetAmbientProperty(DISPID_AMBIENT_USERMODE, VT_BOOL, (void *)&m_state.bUserMode)) {
	MessageBox(NULL,"Unable to retrieve ambient property","",MB_OK);
        return;
    }
}


// Attempts to create a new circle at the given index
// the ambient information should already be setup

HRESULT CCircleCoControl::CreateObject
(
    int index
)
{
    HRESULT hr;

    if (m_state.rgCircles[index].pCircle) {
	return S_OK;
    }

    hr = AddToTypeInfo(index);
    RETURN_ON_FAILURE(hr);

    hr = CoCreateInstance(CLSID_Circle, NULL, CLSCTX_ALL, IID_IUnknown, 
			  (void **) &(m_state.rgCircles[index].pCircle));
    FAILGO(hr);

    ICircle * pCircle;
    hr = m_state.rgCircles[index].pCircle->QueryInterface(IID_ICircle, (void**) &pCircle);
    FAILGO(hr);
    
    pCircle->put_Name(m_state.rgCircles[index].bstrName);
    pCircle->put_Color(m_state.rgCircles[index].CV);
    pCircle->Release();
    hr = AttachSink(index);
    FAILGO(hr);
    
    return S_OK;
    
OnError:
    DeleteFromTypeInfo(index);
    RELNULL(m_state.rgCircles[index].pCircle);
    return hr;
}


void CCircleCoControl::BeforeDestroyWindow
(
    void
)
{
    if (m_state.bUserMode) {
	return;
    }
 
    // This releases a reference count the host has on us and allows us to
    // destruct safely
    
    CallOnSelectChange(NULL);
   
}



// Start out with the main container selected
BOOL CCircleCoControl::AfterCreateWindow
(
    void
)
{

    MaybeSelectionChanged(-1, TRUE);
    return TRUE;

}


