// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Visual C++ Language  Reference and related
// electronic documentation provided with Microsoft Visual C++.
// See these sources for detailed information regarding the
// Microsoft Visual C++ product.

// NOTE: This example will only work with Excel8 in Office97
// Compile with cl /GX comexcel.cpp
// TO DO: Edit the #import paths
#pragma message ("Make sure you go to Tools.Options.Directories and add the paths to mso97.dll and vbeext1.olb.  Mso97.dll will usually be in c:\\\"Program Files\"\\\"Microsoft Office\"\\Office, and vbeext1.olb will be in c:\\\"Program Files\"\\\"Common Files\"\\\"Microsoft Shared\"\\VBA")
#import <mso97.dll> no_namespace rename("DocumentProperties", "DocumentPropertiesXL")   
#import <vbeext1.olb> no_namespace   
#import <excel8.olb> rename("DialogBox", "DialogBoxXL") rename("RGB", "RBGXL") rename("DocumentProperties", "DocumentPropertiesXL") no_dual_interfaces

#pragma warning (disable:4192)

#include <stdio.h>
#include <tchar.h>

void dump_com_error(_com_error &e)
{
    _tprintf(_T("Oops - hit an error!\n"));
    _tprintf(_T("\a\tCode = %08lx\n"), e.Error());
    _tprintf(_T("\a\tCode meaning = %s\n"), e.ErrorMessage());
    _bstr_t bstrSource(e.Source());
    _bstr_t bstrDescription(e.Description());
    _tprintf(_T("\a\tSource = %s\n"), (LPCTSTR) bstrSource);
    _tprintf(_T("\a\tDescription = %s\n"), (LPCTSTR) bstrDescription);
}

// If this is placed in the scope of the smart pointers, they must be
// explicitly Release(d) before CoUninitialize() is called.  If any reference
// count is non-zero, a protection fault will occur.
struct StartOle {
    StartOle() { CoInitialize(NULL); }
    ~StartOle() { CoUninitialize(); }
} _inst_StartOle;

void main()
{
    using namespace Excel;

    _ApplicationPtr pXL;

    try {
    pXL.CreateInstance(L"Excel.Application.8");

    pXL->Visible = VARIANT_TRUE;

    WorkbooksPtr pBooks = pXL->Workbooks;
    _WorkbookPtr pBook  = pBooks->Add((long)xlWorksheet);

    _WorksheetPtr pSheet = pXL->ActiveSheet;
        
    try {
        // This one will fail
        pSheet->Name = "Market Share?";
    } catch (_com_error &e) {
        dump_com_error(e);
    }

    pSheet->Name = "Market Share!";

    pSheet->Range["A2"]->Value = "Company A";
    pSheet->Range["B2"]->Value = "Company B";
    pSheet->Range["C2"]->Value = "Company C";
    pSheet->Range["D2"]->Value = "Company D";

    pSheet->Range["A3"]->Value = 75.0;
    pSheet->Range["B3"]->Value = 14.0;
    pSheet->Range["C3"]->Value = 7.0;
    pSheet->Range["D3"]->Value = 4.0;
    
    Sleep(1000);

    RangePtr  pRange  = pSheet->Range["A2:D3"];
    _ChartPtr  pChart  = pBook->Charts->Add();
    
    pChart->ChartWizard((Range*) pRange, (long) xl3DPie, 7L, (long) xlRows,
        1L, 0L, 2L, "Market Share");

    Sleep(6000);

    pBook->Saved = VARIANT_TRUE;
    pXL->Quit();
    } catch(_com_error &e) {
    dump_com_error(e);
    }
}
