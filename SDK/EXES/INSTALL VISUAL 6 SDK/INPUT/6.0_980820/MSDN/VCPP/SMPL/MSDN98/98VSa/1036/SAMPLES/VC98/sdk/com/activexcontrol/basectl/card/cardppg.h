//=--------------------------------------------------------------------------=
// CardPPG.H
//=--------------------------------------------------------------------------=
// Copyright 1996 - 1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for Card's property pages.
//
#ifndef _CARDPROPPAGE_H_


// kinda need these
//
#include "PropPage.H"
#include "Resource.H"
#include "Guids.H"

class CCardGeneralPage : public CPropertyPage {

  public:
    static IUnknown *Create(IUnknown *pUnkOuter);

    // constructor and destructor
    //
    CCardGeneralPage(IUnknown *pUnkOuter);
    virtual ~CCardGeneralPage();

  private:
    virtual BOOL DialogProc(HWND, UINT, WPARAM, LPARAM);

};

DEFINE_PROPERTYPAGEOBJECT(CardGeneral,
    &CLSID_CardGeneralPage,
    "Card General Propery Page",
    CCardGeneralPage::Create,
    IDD_PROPPAGE_CARDGENERAL,
    IDS_CARD_GENERALPAGETITLE,
    IDS_CARD_GENERALDOCSTRING,
    "vb.hlp",
    0);

#define _CARDPROPPAGE_H_
#endif // _CARDPROPPAGE_H_
