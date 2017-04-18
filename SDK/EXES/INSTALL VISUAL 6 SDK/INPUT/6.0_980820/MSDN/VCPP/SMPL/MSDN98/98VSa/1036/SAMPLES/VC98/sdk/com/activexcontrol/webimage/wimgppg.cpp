//=--------------------------------------------------------------------------=
// WImgPPG.Cpp
//=--------------------------------------------------------------------------=
// Copyright 1995 - 1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// property page implementations for WebImage control.
//

#include "IPServer.H"

#include "LocalObj.H"
#include "WImgPPG.H"
#include "WImgCtl.H"
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
//    lParam = (LPARAM)(HRESULT *)hr
//
//  - in this message, you should call FirstControl() to get a pointer to a
//    control, and initialize the values in the property page dialog with
//    values from the control object.  put results from the operation in
//    the HRESULT pointed to by LPARAM.
//
// PPM_APPLY:
//    wParam = 0;
//    lParam = (LPARAM)(HRESULT *)hr
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
//    lParam = (LPARAM)(HRESULT *)hr
//
//  - sent to your dialog when somebody wants you to set the focus to a specific
//    property [typically, one will see a call to this when one returns a page
//    from IPerPropertyBrowsing::MapPropertyToPage].  you can use this
//    to bring up dialogs, or do whatever flaps your flagella.
//


//=--------------------------------------------------------------------------=
// CWebImageGeneralPage::Create
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
IUnknown *CWebImageGeneralPage::Create
(
    IUnknown *pUnkOuter
)
{
    return (IUnknown *)new CWebImageGeneralPage(pUnkOuter);
}

//=--------------------------------------------------------------------------=
// CWebImageGeneralPage::CWebImageGeneralPage
//=--------------------------------------------------------------------------=
// constructor.
//
// Parameters:
//    IUnknown *        - [in] controlling unknown.
//
// Notes:
//
CWebImageGeneralPage::CWebImageGeneralPage
(
    IUnknown *pUnkOuter
)
: CPropertyPage(pUnkOuter, OBJECT_TYPE_PPGWEBIMAGEGENERAL)
{
    // initialize local variables here.
}

//=--------------------------------------------------------------------------=
// CWebImageGeneralPage::~CWebImageGeneralPage
//=--------------------------------------------------------------------------=
// destructor.
//
// Notes:
//
CWebImageGeneralPage::~CWebImageGeneralPage()
{
    // clean up
}

//=--------------------------------------------------------------------------=
// CWebImageGeneralPage::DialogProc
//=--------------------------------------------------------------------------=
// our dialog proc.
//
// Parameters:
//    - see win32sdk docs on DialogProc
//
// Notes:
//
BOOL CWebImageGeneralPage::DialogProc
(
    HWND   hwnd,
    UINT   msg,
    WPARAM wParam,
    LPARAM lParam
)
{
    HRESULT     hr;
    IWebImage *pWebImage;
    IUnknown   *pUnk;
    DWORD       dwDummy;

    switch (msg) {

      // we've been given some new objects, so go and re-set up the dialog page.
      //
      case PPM_NEWOBJECTS:
        {

        pUnk = FirstControl(&dwDummy);
        if (!pUnk) return FALSE;

        hr = pUnk->QueryInterface(IID_IWebImage, (void **)&pWebImage);
        if (FAILED(hr)) return FALSE;

		//VariantInit(&var);
		BSTR bstr;
        pWebImage->get_Image(&bstr);
		//if( var.vt == VT_BSTR )
		//{
          MAKE_ANSIPTR_FROMWIDE(psz, bstr);//var.bstrVal);
          SetDlgItemText(hwnd, IDC_URL, psz);
          SysFreeString(bstr);//var.bstrVal);
		//	}
        pWebImage->Release();
        }
        return TRUE;

      case PPM_APPLY:
        {
        char      szTmp[120];

        // get all the controls we have to update.
        //
        for (pUnk = FirstControl(&dwDummy) ; pUnk; pUnk = NextControl(&dwDummy)) 
		{
            hr = pUnk->QueryInterface(IID_IWebImage, (void **)&pWebImage);
            if (FAILED(hr)) continue;
    
            GetDlgItemText(hwnd, IDC_URL, szTmp, 128);
			//VariantInit(&var);
            //var.vt = VT_BSTR;
			BSTR bstr;
            //var.bstrVal = BSTRFROMANSI(szTmp);
            bstr = BSTRFROMANSI(szTmp);
            ASSERT(bstr, "Maggots!");
            pWebImage->put_Image(bstr);
            SysFreeString(bstr);
            pWebImage->Release();
        }
        }
        return TRUE;

      case WM_COMMAND:
        switch (LOWORD(wParam)) {
          case IDC_URL:
            if (HIWORD(wParam) == EN_CHANGE)
                MakeDirty();
        }
        break;
    }

	return(FALSE);
}
