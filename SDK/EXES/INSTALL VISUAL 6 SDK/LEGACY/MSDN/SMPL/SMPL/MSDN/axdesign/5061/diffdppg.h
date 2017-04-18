//=--------------------------------------------------------------------------=
// DifferentDesignerPPG.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for DifferentDesigner's property pages.
//
#ifndef _DIFFERENTDESIGNERPROPPAGE_H_


// kinda need these
//
#include "PropPage.H"
#include "Resource.H"
#include "Guids.H"

class CDifferentDesignerGeneralPage : public CPropertyPage {

  public:
    static IUnknown *Create(IUnknown *pUnkOuter);

    // constructor and destructor
    //
    CDifferentDesignerGeneralPage(IUnknown *pUnkOuter);
    virtual ~CDifferentDesignerGeneralPage();

  private:
    virtual BOOL DialogProc(HWND, UINT, WPARAM, LPARAM);

};

DEFINE_PROPERTYPAGEOBJECT(DifferentDesignerGeneral,
    &CLSID_DifferentDesignerGeneralPage,
    "DifferentDesigner General Propery Page",
    CDifferentDesignerGeneralPage::Create,
    IDD_PROPPAGE_DIFFERENTDESIGNERGENERAL,
    IDS_DIFFERENTDESIGNER_GENERALPAGETITLE,
    IDS_DIFFERENTDESIGNER_GENERALDOCSTRING,
    "vb.hlp",
    0);

#define _DIFFERENTDESIGNERPROPPAGE_H_
#endif // _DIFFERENTDESIGNERPROPPAGE_H_
