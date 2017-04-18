//=--------------------------------------------------------------------------=
// InvisibleDesignerPPG.H
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for InvisibleDesigner's property pages.
//
#ifndef _INVISIBLEDESIGNERPROPPAGE_H_


// kinda need these
//
#include "PropPage.H"
#include "Resource.H"
#include "Guids.H"

class CInvisibleDesignerGeneralPage : public CPropertyPage {

  public:
    static IUnknown *Create(IUnknown *pUnkOuter);

    // constructor and destructor
    //
    CInvisibleDesignerGeneralPage(IUnknown *pUnkOuter);
    virtual ~CInvisibleDesignerGeneralPage();

  private:
    virtual BOOL DialogProc(HWND, UINT, WPARAM, LPARAM);

};

DEFINE_PROPERTYPAGEOBJECT(InvisibleDesignerGeneral,
    &CLSID_InvisibleDesignerGeneralPage,
    "InvisibleDesigner General Propery Page",
    CInvisibleDesignerGeneralPage::Create,
    IDD_PROPPAGE_INVISIBLEDESIGNERGENERAL,
    IDS_INVISIBLEDESIGNER_GENERALPAGETITLE,
    IDS_INVISIBLEDESIGNER_GENERALDOCSTRING,
    "vb.hlp",
    0);

#define _INVISIBLEDESIGNERPROPPAGE_H_
#endif // _INVISIBLEDESIGNERPROPPAGE_H_
