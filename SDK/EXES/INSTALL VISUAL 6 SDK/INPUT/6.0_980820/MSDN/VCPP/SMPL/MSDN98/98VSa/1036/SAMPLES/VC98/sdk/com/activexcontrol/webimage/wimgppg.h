//=--------------------------------------------------------------------------=
// WImgPPG.H
//=--------------------------------------------------------------------------=
// Copyright 1995 - 1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for WebImage's property pages.
//
#ifndef _WEBIMAGEPROPPAGE_H_


// kinda need these
//
#include "PropPage.H"
#include "Resource.H"
#include "Guids.H"

class CWebImageGeneralPage : public CPropertyPage {

  public:
    static IUnknown *Create(IUnknown *pUnkOuter);

    // constructor and destructor
    //
    CWebImageGeneralPage(IUnknown *pUnkOuter);
    virtual ~CWebImageGeneralPage();

  private:
    virtual BOOL DialogProc(HWND, UINT, WPARAM, LPARAM);

};

DEFINE_PROPERTYPAGEOBJECT(WebImageGeneral,
    &CLSID_WebImageGeneralPage,
    "WebImage General Propery Page",
    CWebImageGeneralPage::Create,
    IDD_PROPPAGE_WEBIMAGEGENERAL,
    IDS_WEBIMAGE_GENERALPAGETITLE,
    IDS_WEBIMAGE_GENERALDOCSTRING,
    "vb.hlp",
    0);

#define _WEBIMAGEPROPPAGE_H_
#endif // _WEBIMAGEPROPPAGE_H_
