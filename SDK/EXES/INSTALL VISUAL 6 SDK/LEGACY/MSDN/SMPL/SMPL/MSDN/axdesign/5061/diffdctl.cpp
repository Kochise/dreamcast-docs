//=--------------------------------------------------------------------------=
// DifferentDesignerCtl.Cpp
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
#include "DiffDCtl.H"
#include "LocalObj.H"
#include "Util.H"
#include "Globals.H"
#include "Resource.H"

// for ASSERT and FAIL
//
SZTHISFILE

#define RUNTIME_MISCSTATUS     OLEMISC_SETCLIENTSITEFIRST|OLEMISC_ACTIVATEWHENVISIBLE|OLEMISC_RECOMPOSEONRESIZE|OLEMISC_CANTLINKINSIDE|OLEMISC_INSIDEOUT

// stream name for the runtime object.
//
static WCHAR s_wszRuntimeSaveStream [] = L"RuntimeSaveStream";
static char s_szMessage [] = "This is a simple Visual Designer with different visual instance object.";

#define STREAMHDR_SIGNATURE 0x12344321  // Signature to identify our format (avoid crashes!)

typedef struct tagSTREAMHDR {

    DWORD  dwSignature;     // Signature.
    size_t cbWritten;       // Number of bytes written

} STREAMHDR;


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
const GUID *rgDifferentDesignerPropPages [] = {
    &CLSID_DifferentDesignerGeneralPage
};

//=--------------------------------------------------------------------------=
// Custum Verb information
//
// TODO: add any custom verbs here in an array, using the VERBINFO structure.
//       then mark the controld def'n in DifferentDesignerCtl.H with
//       this verb array
//


//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::Create
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
IUnknown *CDifferentDesignerControl::Create
(
    IUnknown *pUnkOuter
)
{
    // make sure we return the private unknown so that we support aggegation
    // correctly!
    //
    CDifferentDesignerControl *pNew = new CDifferentDesignerControl(pUnkOuter);
    return pNew->PrivateUnknown();
}

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::CDifferentDesignerControl
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
CDifferentDesignerControl::CDifferentDesignerControl
(
    IUnknown *pUnkOuter
)
: COleControl(pUnkOuter, OBJECT_TYPE_CTLDIFFERENTDESIGNER, (IDispatch *)this)
{
    m_bstrMyString = NULL;
}
#pragma warning(default:4355)  // using 'this' in constructor

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::~CDifferentDesignerControl
//=--------------------------------------------------------------------------=
// "We all labour against our own cure, for death is the cure of all diseases"
//    - Sir Thomas Browne (1605 - 82)
//
// Notes:
//
CDifferentDesignerControl::~CDifferentDesignerControl ()
{
    if (m_bstrMyString) SysFreeString(m_bstrMyString);
}

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl:RegisterClassData
//=--------------------------------------------------------------------------=
// register the window class information for your control here.
// this information will automatically get cleaned up for you on DLL shutdown.
//
// Output:
//    BOOL            - FALSE means fatal error.
//
// Notes:
//
BOOL CDifferentDesignerControl::RegisterClassData
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
    wndclass.lpszClassName  = WNDCLASSNAMEOFCONTROL(OBJECT_TYPE_CTLDIFFERENTDESIGNER);

    return RegisterClass(&wndclass);
}

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::BeforeCreateWindow
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
BOOL CDifferentDesignerControl::BeforeCreateWindow
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
// CDifferentDesignerControl::InternalQueryInterface
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
HRESULT CDifferentDesignerControl::InternalQueryInterface
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
    if (DO_GUIDS_MATCH(riid, IID_IDifferentDesigner)) {
        pUnk = (IUnknown *)(IDifferentDesigner *)this;
    } else if (DO_GUIDS_MATCH(riid, IID_IActiveDesigner)) {
        pUnk = (IUnknown *)(IActiveDesigner *)this;
    } else {
        return COleControl::InternalQueryInterface(riid, ppvObjOut);
    }

    pUnk->AddRef();
    *ppvObjOut = (void *)pUnk;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::LoadTextState
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
STDMETHODIMP CDifferentDesignerControl::LoadTextState
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
// CDifferentDesignerControl::LoadBinaryState
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
STDMETHODIMP CDifferentDesignerControl::LoadBinaryState
(
    IStream *pStream
)
{
    // TODO: implement your binary load code here.  to prevent this from being
    // a massive performance sink, you should probably try to organize your
    // properties in such a way that enables you to do just one IStream::Read
    // in the LoadBinaryState function.  fast is good.
    //
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::SaveTextState
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
STDMETHODIMP CDifferentDesignerControl::SaveTextState
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
// CDifferentDesignerControl::SaveBinaryState
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
STDMETHODIMP CDifferentDesignerControl::SaveBinaryState
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
// CDifferentDesignerControl::OnDraw
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
HRESULT CDifferentDesignerControl::OnDraw
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
    rgbOld = SetTextColor(hdcDraw, RGB(255, 0, 255));
    rgbback = SetBkColor(hdcDraw, GetSysColor(COLOR_WINDOW));
    DrawText(hdcDraw, s_szMessage, -1, &rc, DT_WORDBREAK);
    if (!fOptimize) {
        SetTextColor(hdcDraw, rgbOld);
        SetBkColor(hdcDraw, rgbback);
    }
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::WindowProc
//=--------------------------------------------------------------------------=
// window procedure for this control.  nothing terribly exciting.
//
// Parameters:
//     see win32sdk on window procs [sans HWND -- it's in m_hwnd if you have one]
//
// Notes:
//
LRESULT CDifferentDesignerControl::WindowProc
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
// CDifferentDesignerControl::get_MyString    [IInvisibleDesigner]
//=--------------------------------------------------------------------------=
// returns current string
//
// Parameters:
//    BSTR *            - [out]
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CDifferentDesignerControl::get_MyString
(
    BSTR *pbstr
)
{
    CHECK_POINTER(pbstr);

    *pbstr = COPYBSTR(m_bstrMyString ? m_bstrMyString : L"");
    return *pbstr ? S_OK : E_OUTOFMEMORY;
}

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::put_MyString    [IInvisibleDesigner]
//=--------------------------------------------------------------------------=
//
// Parameters:
//    BSTR          - [in] new string
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CDifferentDesignerControl::put_MyString
(
    BSTR bstr
)
{
    if (m_bstrMyString) SysFreeString(m_bstrMyString);

    m_bstrMyString = COPYBSTR(bstr ? bstr : L"");
    return m_bstrMyString ? S_OK : E_OUTOFMEMORY;
}

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::AboutBox    [IDifferentDesigner]
//=--------------------------------------------------------------------------=
// prints up an about box.  fweeeee.
//
// Notes:
//
void CDifferentDesignerControl::AboutBox
(
    void
)
{
    // TODO: Ideally, one would use DialogBox, and some sort of Dialog Box here if
    // they wanted a slightly more interesting About Box ...  you should
    // still call ModalDialog first, however.
    //
    ModalDialog(TRUE);
    MessageBox(NULL, "This is My Control", "About DifferentDesigner", MB_OK | MB_TASKMODAL);
    ModalDialog(FALSE);
}


//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::GetRuntimeClassID    [IActiveDesigner]
//=--------------------------------------------------------------------------=
// returns the classid of the qcdrunmode.dll dude.
//
// Parameters:
//    CLSID *               - [out] duh.
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CDifferentDesignerControl::GetRuntimeClassID
(
    CLSID *pclsid
)
{
    CHECK_POINTER(pclsid);

    *pclsid = CLSID_DifferentInstance;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::GetRuntimeMiscStatusFlags    [IActiveDesigner]
//=--------------------------------------------------------------------------=
// returns the misc status flags for the runtiem object.
//
// Parameters:
//    DWORD *               - [out] duh.
//
// Output:
//    HRESULT
//
// Notes:
//
STDMETHODIMP CDifferentDesignerControl::GetRuntimeMiscStatusFlags
(
    DWORD *pdwMiscStatus
)
{
    CHECK_POINTER(pdwMiscStatus);

    *pdwMiscStatus = RUNTIME_MISCSTATUS;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::QueryPersistenceInterface    [IActiveDesigner]
//=--------------------------------------------------------------------------=
// do we support the given interface for persistence for the runmode object?
//
// Parameters:
//    REFIID                - [in] guess.
//
// Output:
//    HRESULT               - S_OK yep, S_FALSE nope, otherwise error
//
// Notes:
//
STDMETHODIMP CDifferentDesignerControl::QueryPersistenceInterface
(
    REFIID riid
)
{
    switch (riid.Data1)
        {
        case Data1_IPersistStreamInit:
            if (riid == IID_IPersistStreamInit)
                return S_OK;
        case Data1_IPersistStream:
            if (riid == IID_IPersistStream)
                return S_OK;
        case Data1_IPersistStorage:
            if (riid == IID_IPersistStorage)
                return S_OK;
        }

    return S_FALSE;
}

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::SaveRuntimeState    [IActiveDesigner]
//=--------------------------------------------------------------------------=
// given a persistence object and an interface, save out the runtime state
// using that object.
//
// Parameters:
//    REFIID                - [in] the interface the object is
//    void *                - [in] the medium
//
// Output:
//    HRESULT
//
// Notes:
//
//[10/8/96, IvoSa] STDMETHODIMP CDifferentDesignerControl::SaveRuntimeState
//[10/8/96, IvoSa] (
//[10/8/96, IvoSa]	   REFIID riid,
//[10/8/96, IvoSa]     void  *pMedium
//[10/8/96, IvoSa] )
STDMETHODIMP CDifferentDesignerControl::SaveRuntimeState
(  REFIID riidPersist, 
   REFIID riidObjStgMed, 
   void *pMedium
)
{
    IStream *pStream;
    long     l;
    HRESULT  hr;
    LPWSTR   pwsz;

    // get ourselves an IStream
    //
//[10/8/96, IvoSa]     switch (riid.Data1)
     switch (riidObjStgMed.Data1)
        {
        case Data1_IStream:
            pStream = (IStream *)pMedium;
            pStream->AddRef();
            break;
        case Data1_IStorage:
            // we're just going to save out to the CONTENTES stream.
            //
            hr = ((IStorage *)pMedium)->CreateStream(s_wszRuntimeSaveStream, STGM_WRITE | STGM_SHARE_EXCLUSIVE | STGM_CREATE,
                                        0, 0, &pStream);
            RETURN_ON_FAILURE(hr);
            break;

        default:
            FAIL("Gaaak! Bogus persistence interface!");
        }

    // save out some basectl 'standard' state, since the loading
    // control will look for it in the stream
    //
    hr = SaveStandardState(pStream);
    CLEANUP_ON_FAILURE(hr);

    // save out our property
    //
    if (m_bstrMyString) {
        pwsz = m_bstrMyString;
        l = SysStringLen(m_bstrMyString) + 1;
    } else {
        pwsz = L"";
        l = 1;
    }

    hr = pStream->Write(&l, sizeof(l), NULL);
    CLEANUP_ON_FAILURE(hr);
    hr = pStream->Write(pwsz, l * sizeof(WCHAR), NULL);

  CleanUp:
    pStream->Release();
    return hr;
}

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::GetExtensibilityObject    [IActiveDesigner]
//=--------------------------------------------------------------------------=
// no idea.
//
// Parameters:
//    IDispatch **            - [out] the extensibility object.
//
// Output:
//    HRESULT
//
// Notes:
//    - homey don't play that.
//
STDMETHODIMP CDifferentDesignerControl::GetExtensibilityObject
(
    IDispatch **ppExtensibilityObject
)
{
    CHECK_POINTER(ppExtensibilityObject);
    *ppExtensibilityObject = NULL;

    return E_NOTIMPL;
}

//=--------------------------------------------------------------------------=
// CDifferentDesignerControl::SaveStandardState    [ helper ]
//=--------------------------------------------------------------------------=
//
// Parameters:
//    IStream *            - [in]
//
// Output:
//    HRESULT
//
// Notes:
//
HRESULT CDifferentDesignerControl::SaveStandardState
(
    IStream *pStream
)
{
    STREAMHDR streamhdr = { STREAMHDR_SIGNATURE, sizeof(SIZEL) };
    HRESULT hr;
    SIZEL   slHiMetric;

    // first thing to do is write out our stream hdr structure.
    //
    hr = pStream->Write(&streamhdr, sizeof(STREAMHDR), NULL);
    RETURN_ON_FAILURE(hr);

    // the only properties we're currently persisting here are the size
    // properties for this control.  make sure we do that in HiMetric
    //
    PixelToHiMetric(&m_Size, &slHiMetric);

    hr = pStream->Write(&slHiMetric, sizeof(slHiMetric), NULL);
    return hr;
}

