//=--------------------------------------------------------------------------=
// DifferentInstancePPG.Cpp
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// property page implementations for DifferentInstance control.
//
#include "IPServer.H"

#include "LocalObj.H"
#include "DiffIPPG.H"
#include "DiffICtl.H"
#include "Resource.H"
#include "Util.H"


// for ASSERT and FAIL
//
SZTHISFILE

//=--------------------------------------------------------------------------=
// Property Page messages
//=--------------------------------------------------------------------------=
// in addition to regular windows messages you'll receive for a dialog box,
// you'll receive the following messages in your property page implementation:
//
// PPM_NEWOBJECTS:
//    wParam = 0;
//    lParam = (LPARAM)(HRESULT *)&hr
//
//  - in this message, you should call FirstControl() to get a pointer to a
//    control, and initialize the values in the property page dialog with
//    values from the control object.  put results from the operation in
//    the HRESULT pointed to by LPARAM.
//
// PPM_APPLY:
//    wParam = 0;
//    lParam = (LPARAM)(HRESULT *)&hr
//
//  - this message is sent to your dialog whenever the user clicks APPLY or OK
//    in the dialog.  you should have a loop with the following code in it:
//
//      for (pUnk = FirstControl(&dwCookie) ; pUnk; pUnk = NextControl(&dwCookie)) {
//            hr = pUnk->QueryInterface(IID_IMyCtlInterface, (void **)&pMyCtl);
//            // set properties here!!!
//      }
//
//    call PropPageException() if there is an error while setting propertites
//    to show the exception set up by the property set routine.
//
// PPM_EDITPROPERTY:
//    wParam = dispid
//    lParam = (LPARAM)(HRESULT *)&hr
//
//  - sent to your dialog when somebody wants you to set the focus to a specific
//    property [typically, one will see a call to this when one returns a page
//    from IPerPropertyBrowsing::MapPropertyToPage].  you can use this
//    to bring up dialogs, or do whatever flaps your flagella.
//
// PPM_FREEOBJECTS:
//    wParam = 0
//    lParam = (LPARAM)(HRESULT *)&hr
//
// - sent to your dialog when you should free up any objects.  some people will
//   find it interesting to QI and store objects in the PPM_INITOBJECTS message.
//   this message tells the prop page that these objects are no longer valid,
//   and any stashing of objects should be terminated.
//

//=--------------------------------------------------------------------------=
// CDifferentInstanceGeneralPage::Create
//=--------------------------------------------------------------------------=
// global static creation function.
//
// Parameters:
//    IUnknown *    - [in] controlling unknown
//
// Output:
//    IUnknown *    - new prop page.
//
// Notes:
//
IUnknown *CDifferentInstanceGeneralPage::Create
(
    IUnknown *pUnkOuter
)
{
    return (IUnknown *)new CDifferentInstanceGeneralPage(pUnkOuter);
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceGeneralPage::CDifferentInstanceGeneralPage
//=--------------------------------------------------------------------------=
// constructor.
//
// Parameters:
//    IUnknown *        - [in] controlling unknown.
//
// Notes:
//
CDifferentInstanceGeneralPage::CDifferentInstanceGeneralPage
(
    IUnknown *pUnkOuter
)
: CPropertyPage(pUnkOuter, OBJECT_TYPE_PPGDIFFERENTINSTANCEGENERAL)
{
    // initialize local variables here.
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceGeneralPage::~CDifferentInstanceGeneralPage
//=--------------------------------------------------------------------------=
// destructor.
//
// Notes:
//
CDifferentInstanceGeneralPage::~CDifferentInstanceGeneralPage()
{
    // clean up
}

//=--------------------------------------------------------------------------=
// CDifferentInstanceGeneralPage::DialogProc
//=--------------------------------------------------------------------------=
// our dialog proc.
//
// Parameters:
//    - see win32sdk docs on DialogProc
//
// Notes:
//
BOOL CDifferentInstanceGeneralPage::DialogProc
(
    HWND   hwnd,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam
)
{
    // TODO: add support for your property page here.  this is a normal dialog
    //       proc.  make sure you handle PPM_NEWOBJECTS and PPM_APPLY.
    //
    return FALSE;
}
