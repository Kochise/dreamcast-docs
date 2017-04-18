//=--------------------------------------------------------------------------=
// DifferentInstanceCtl.Cpp
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
#include "DiffICtl.H"
#include "LocalObj.H"
#include "Util.H"
#include "Globals.H"
#include "Resource.H"

// for ASSERT and FAIL
//
SZTHISFILE


//=--------------------------------------------------------------------------=
// all the events in this control
//
// TODO: add events here ...
//

//=--------------------------------------------------------------------------=
// array describing all of our property pages.  these clsids are typically
// in guids.h
//
// TODO: add any additional property page guids here ...
//
const GUID *rgDifferentInstancePropPages [] = {
    &CLSID_DifferentInstanceGeneralPage
};



static char s_szMessage [] = "This is the Different Instance Object.";


//=--------------------------------------------------------------------------=
// CDifferentInstanceControl::Create
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
IUnknown *CDifferentInstanceControl::Create
(
    IUnknown *pUnkOuter
)
{
    // make sure we return the private unknown so that we support aggegation
    // correctly!
    //
    CDifferentInstanceControl *pNew = new CDifferentInstanceControl(pUnkOuter);
    return pNew->PrivateUnknown();
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceControl::CDifferentInstanceControl
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
CDifferentInstanceControl::CDifferentInstanceControl
(
    IUnknown *pUnkOuter
)
: COleControl(pUnkOuter, OBJECT_TYPE_CTLDIFFERENTINSTANCE, (IDispatch *)this)
{
    m_bstrMyString = NULL;

}
#pragma warning(default:4355)  // using 'this' in constructor

//=--------------------------------------------------------------------------=
// CDifferentInstanceControl::~CDifferentInstanceControl
//=--------------------------------------------------------------------------=
// "We all labour against our own cure, for death is the cure of all diseases"
//    - Sir Thomas Browne (1605 - 82)
//
// Notes:
//
CDifferentInstanceControl::~CDifferentInstanceControl ()
{
    if (m_bstrMyString) SysFreeString(m_bstrMyString);
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceControl:RegisterClassData
//=--------------------------------------------------------------------------=
// register the window class information for your control here.
// this information will automatically get cleaned up for you on DLL shutdown.
//
// Output:
//    BOOL            - FALSE means fatal error.
//
// Notes:
//
BOOL CDifferentInstanceControl::RegisterClassData
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
    wndclass.lpszClassName  = WNDCLASSNAMEOFCONTROL(OBJECT_TYPE_CTLDIFFERENTINSTANCE);

    return RegisterClass(&wndclass);
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceControl::BeforeCreateWindow
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
BOOL CDifferentInstanceControl::BeforeCreateWindow
(
    DWORD *pdwWindowStyle,
    DWORD *pdwExWindowStyle,
    LPSTR  pszWindowTitle
)
{
    // TODO: users should set the values of *pdwWindowStyle, *pdwExWindowStyle,
    // and pszWindowTitle so that the call to CreateWindowEx can use them. setting
    // them here instead of calling SetWindowStyle in WM_CREATE is a huge perf win
    // if you don't use this function, then you can probably just remove it.
    //
    return TRUE;
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceControl::InternalQueryInterface
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
HRESULT CDifferentInstanceControl::InternalQueryInterface
(
    REFIID  riid,
    void  **ppvObjOut
)
{
    IUnknown *pUnk;

    *ppvObjOut = NULL;

    // TODO: if you want to support any additional interrfaces, then you should
    // indicate that here.  never forget to call COleControl's version in the
    // case where you don't support the given interface.
    //
    if (DO_GUIDS_MATCH(riid, IID_IDifferentInstance)) {
        pUnk = (IUnknown *)(IDifferentInstance *)this;
    } else{
        return COleControl::InternalQueryInterface(riid, ppvObjOut);
    }

    pUnk->AddRef();
    *ppvObjOut = (void *)pUnk;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceControl::LoadTextState
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
STDMETHODIMP CDifferentInstanceControl::LoadTextState
(
    IPropertyBag *pPropertyBag,
    IErrorLog    *pErrorLog
)
{
    // TODO: implement your text load code here.
    //
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceControl::LoadBinaryState
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
STDMETHODIMP CDifferentInstanceControl::LoadBinaryState
(
    IStream *pStream
)
{
    LPWSTR  pwsz;
    HRESULT hr;
    long l;

    // just load in the properties that the DifferentDesigner saved out
    //
    hr = pStream->Read(&l, sizeof(l), NULL);
    RETURN_ON_FAILURE(hr);

    pwsz = (LPWSTR)HeapAlloc(g_hHeap, 0, l * sizeof(WCHAR));
    if (!pwsz) return E_OUTOFMEMORY;

    hr = pStream->Read(pwsz, l * sizeof(WCHAR), NULL);
    RETURN_ON_FAILURE(hr);

    m_bstrMyString = SysAllocString(pwsz);
    if (!m_bstrMyString) return E_OUTOFMEMORY;
    HeapFree(g_hHeap, 0, pwsz);

    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceControl::SaveTextState
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
STDMETHODIMP CDifferentInstanceControl::SaveTextState
(
    IPropertyBag *pPropertyBag,
    BOOL          fWriteDefaults
)
{
    // TODO: implement your text save code here.
    //
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceControl::SaveBinaryState
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
//    - it is important that you seek to the end of where you saved your
//      properties when you're done with the IStream.
//
STDMETHODIMP CDifferentInstanceControl::SaveBinaryState
(
    IStream *pStream
)
{
    // TODO: implement your binary save state code here.  to prevent this from being
    // a massive performance sink, you should probably try to organize your
    // properties in such a way that enables you to do just one IStream::Read
    // in the LoadBinaryState function.  fast is good.
    //
    return S_OK;
}


//=--------------------------------------------------------------------------=
// CDifferentInstanceControl::OnDraw
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
HRESULT CDifferentInstanceControl::OnDraw
(
    DWORD    dvAspect,
    HDC      hdcDraw,
    LPCRECTL prcBounds,
    LPCRECTL prcWBounds,
    HDC      hicTargetDevice,
    BOOL     fOptimize
)
{
    RECT rc;
    COLORREF rgbOld;
    COLORREF rgbback;

    rc = *((RECT *)prcBounds);
    DrawEdge(hdcDraw, &rc, EDGE_SUNKEN, BF_RECT);
    InflateRect(&rc, -2, -2);
    rgbOld = SetTextColor(hdcDraw, RGB(255, 0, 0));
    rgbback = SetBkColor(hdcDraw, RGB(0, 0, 0));
    DrawText(hdcDraw, s_szMessage, -1, &rc, DT_WORDBREAK);
    if (!fOptimize) {
        SetTextColor(hdcDraw, rgbOld);
        SetBkColor(hdcDraw, rgbback);
    }
    return S_OK;
    
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceControl::WindowProc
//=--------------------------------------------------------------------------=
// window procedure for this control.  nothing terribly exciting.
//
// Parameters:
//     see win32sdk on window procs [sans HWND -- it's in m_hwnd if you have one]
//
// Notes:
//
LRESULT CDifferentInstanceControl::WindowProc
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
    return OcxDefWindowProc(msg, wParam, lParam);
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceControl::get_MyString    [IDifferentInstance]
//=--------------------------------------------------------------------------=
//
// Parameters:
//    BSTR *            - [out]
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CDifferentInstanceControl::get_MyString
(
    BSTR *pbstr
)
{
    CHECK_POINTER(pbstr);

    *pbstr = SysAllocString(m_bstrMyString ? m_bstrMyString : L"");
    return *pbstr ? S_OK : E_OUTOFMEMORY;
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceCOntrol::put_MyString    [IDifferentInstance]
//=--------------------------------------------------------------------------=
//
// Parameters:
//    BSTR                  - [in]
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CDifferentInstanceControl::put_MyString
(
    BSTR bstr
)
{
    if (m_bstrMyString) SysFreeString(m_bstrMyString);

    m_bstrMyString = COPYBSTR(bstr ? bstr : L"");
    return m_bstrMyString ? S_OK : E_OUTOFMEMORY;
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceControl::AboutBox
//=--------------------------------------------------------------------------=
// prints up an about box.  fweeeee.
//
// Notes:
//
void CDifferentInstanceControl::AboutBox
(
    void
)
{
    // TODO: Ideally, one would use DialogBox, and some sort of Dialog Box here if
    // they wanted a slightly more interesting About Box ...  you should
    // still call ModalDialog first, however.
    //
    ModalDialog(TRUE);
    MessageBox(NULL, "This is My Control", "About DifferentInstance", MB_OK | MB_TASKMODAL);
    ModalDialog(FALSE);
}

