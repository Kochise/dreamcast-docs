//=--------------------------------------------------------------------------=
// ToDoPPG.H
//=--------------------------------------------------------------------------=
// Copyright 1995-1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// class declaration for ToDo's property pages.
//
#ifndef _TODOPPG_H_


// kinda need these
//
#include "PropPage.H"
#include "Resource.H"
#include "Guids.H"

class CToDoGeneralPage : public CPropertyPage {

  public:
    static IUnknown *Create(IUnknown *pUnkOuter);

    // constructor and destructor
    //
    CToDoGeneralPage(IUnknown *pUnkOuter);
    virtual ~CToDoGeneralPage();

  private:
    virtual BOOL DialogProc(HWND, UINT, WPARAM, LPARAM);

};

DEFINE_PROPERTYPAGEOBJECT(ToDoGeneral,
    &CLSID_ToDoGeneralPage,
    "ToDo General Propery Page",
    CToDoGeneralPage::Create,
    IDD_PROPPAGE_TODOGENERAL,
    IDS_TODO_GENERALPAGETITLE,
    IDS_TODO_GENERALDOCSTRING,
    "vb.hlp",
    0);

#define _TODOPPG_H_
#endif // _TODOPPG_H_
