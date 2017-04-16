//=--------------------------------------------------------------------------=
// DifferentInstancePPG.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for DifferentInstance's property pages.
//
#ifndef _DIFFERENTINSTANCEPROPPAGE_H_


// kinda need these
//
#include "PropPage.H"
#include "Resource.H"
#include "Guids.H"

class CDifferentInstanceGeneralPage : public CPropertyPage {

  public:
    static IUnknown *Create(IUnknown *pUnkOuter);

    // constructor and destructor
    //
    CDifferentInstanceGeneralPage(IUnknown *pUnkOuter);
    virtual ~CDifferentInstanceGeneralPage();

  private:
    virtual BOOL DialogProc(HWND, UINT, WPARAM, LPARAM);

};

DEFINE_PROPERTYPAGEOBJECT(DifferentInstanceGeneral,
    &CLSID_DifferentInstanceGeneralPage,
    "DifferentInstance General Propery Page",
    CDifferentInstanceGeneralPage::Create,
    IDD_PROPPAGE_DIFFERENTINSTANCEGENERAL,
    IDS_DIFFERENTINSTANCE_GENERALPAGETITLE,
    IDS_DIFFERENTINSTANCE_GENERALDOCSTRING,
    "vb.hlp",
    0);

#define _DIFFERENTINSTANCEPROPPAGE_H_
#endif // _DIFFERENTINSTANCEPROPPAGE_H_
