//=--------------------------------------------------------------------------=
// ToDoCtl.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1995-1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
#include "IPServer.H"

#include "Guids.H"
#include "ToDoCtl.H"
#include "LocalObj.H"
#include "Util.H"
#include "Globals.H"
#include "Resource.H"

#include <commctrl.h>

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
const GUID *rgToDoPropPages [] = {
    &CLSID_ToDoGeneralPage
};

//=--------------------------------------------------------------------------=
// Custum Verb information
//
// TODO: add any custom verbs here in an array, using the VERBINFO structure.
//       then mark the controld def'n in ToDoCtl.H with
//       this verb array
//


//=--------------------------------------------------------------------------=
// CToDoControl::Create
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
IUnknown *CToDoControl::Create(IUnknown *pUnkOuter)
{
    // make sure we return the private unknown so that we support aggegation
    // correctly!
    //
    CToDoControl *pNew = new CToDoControl(pUnkOuter);
    return pNew->PrivateUnknown();
}

//=--------------------------------------------------------------------------=
// CToDoControl::CToDoControl
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
CToDoControl::CToDoControl(IUnknown* pUnkOuter)
    : CDocumentObject(pUnkOuter, OBJECT_TYPE_CTLTODO, (IDispatch *)this)
{
    // initialize anything here ...
    //
    memset(&m_state, 0, sizeof(TODOCTLSTATE));

    // TODO: initialize anything you need to here.

}
#pragma warning(default:4355)  // using 'this' in constructor

//=--------------------------------------------------------------------------=
// CToDoControl::~CToDoControl
//=--------------------------------------------------------------------------=
// "We all labour against our own cure, for death is the cure of all diseases"
//    - Sir Thomas Browne (1605 - 82)
//
// Notes:
//
CToDoControl::~CToDoControl ()
{
    // TODO: clean up anything here.
}

//=--------------------------------------------------------------------------=
// CToDoControl:RegisterClassData
//=--------------------------------------------------------------------------=
// register the window class information for your control here.
// this information will automatically get cleaned up for you on DLL shutdown.
//
// Output:
//    BOOL            - FALSE means fatal error.
//
// Notes:
//
BOOL CToDoControl::RegisterClassData(void)
{
    WNDCLASS wndclass;

    // subclass a windows ListView control.
    //
    if (!::GetClassInfo(g_hInstance, WC_LISTVIEW, &wndclass))
        return FALSE;

    // this doesn't need a critical section for apartment threading support
    // since it's already in a critical section in CreateInPlaceWindow
    //
    SUBCLASSWNDPROCOFCONTROL(OBJECT_TYPE_CTLTODO) = (WNDPROC)wndclass.lpfnWndProc;
    wndclass.lpfnWndProc = COleControl::ControlWindowProc;
    wndclass.lpszClassName = WNDCLASSNAMEOFCONTROL(OBJECT_TYPE_CTLTODO);

    return RegisterClass(&wndclass);
}

//=--------------------------------------------------------------------------=
// CToDoControl::BeforeCreateWindow
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
// Notes:
//
BOOL CToDoControl::BeforeCreateWindow
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
    lstrcpy(pszWindowTitle, "ToDo");
    return TRUE;
}

//=--------------------------------------------------------------------------=
// CToDoControl::InternalQueryInterface
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
HRESULT CToDoControl::InternalQueryInterface
(
    REFIID  riid,
    void  **ppvObjOut
)
{
    IUnknown *pUnk;

    *ppvObjOut = NULL;

    // TODO: if you want to support any additional interrfaces, then you should
    // indicate that here.  never forget to call the base class version in the
    // case where you don't support the given interface.
    //
    if (DO_GUIDS_MATCH(riid, IID_IToDo)) {
        pUnk = (IUnknown *)(IToDo *)this;
    } else{
        return CDocumentObject::InternalQueryInterface(riid, ppvObjOut);
    }

    pUnk->AddRef();
    *ppvObjOut = (void *)pUnk;
    return S_OK;
}

//=--------------------------------------------------------------------------=
// CToDoControl::LoadTextState
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
STDMETHODIMP CToDoControl::LoadTextState
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
// CToDoControl::LoadBinaryState
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
STDMETHODIMP CToDoControl::LoadBinaryState
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
// CToDoControl::SaveTextState
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
STDMETHODIMP CToDoControl::SaveTextState
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
// CToDoControl::SaveBinaryState
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
STDMETHODIMP CToDoControl::SaveBinaryState
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
// CToDoControl::OnDraw
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
HRESULT CToDoControl::OnDraw
(
    DWORD    dvAspect,
    HDC      hdcDraw,
    LPCRECTL prcBounds,
    LPCRECTL prcWBounds,
    HDC      hicTargetDevice,
    BOOL     fOptimize
)
{
    // TODO: put your drawing code here ...
    //
    return DoSuperClassPaint(hdcDraw, prcBounds);
}

//=--------------------------------------------------------------------------=
// CToDoControl::WindowProc
//=--------------------------------------------------------------------------=
// window procedure for this control.  nothing terribly exciting.
//
// Parameters:
//     see win32sdk on window procs.
//
// Notes:
//
LRESULT CToDoControl::WindowProc
(
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam
)
{
    // TODO: handle any messages here, like in a normal window
    // proc.  note that for special keys, you'll want to override and
    // implement OnSpecialKey.
    //
    return CallWindowProc((WNDPROC)(FARPROC)SUBCLASSWNDPROCOFCONTROL(OBJECT_TYPE_CTLTODO), (HWND) m_hwnd, msg, wParam, lParam);
}

//=--------------------------------------------------------------------------=
// CToDoControl::AboutBox
//=--------------------------------------------------------------------------=
// prints up an about box.  fweeeee.
//
// Notes:
//
void CToDoControl::AboutBox
(
    void
)
{
    // TODO: Ideally, one would use DialogBox, and some sort of Dialog Box here if
    // they wanted a slightly more interesting About Box ...  you should
    // still call ModalDialog first, however.
    //
    ModalDialog(TRUE);
    MessageBox(NULL, "Sample DocObject Server", "About ToDo", MB_OK | MB_TASKMODAL);
    ModalDialog(FALSE);
}
