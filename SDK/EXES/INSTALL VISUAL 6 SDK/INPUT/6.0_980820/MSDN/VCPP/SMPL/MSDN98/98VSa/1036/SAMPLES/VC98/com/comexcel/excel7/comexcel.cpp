// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Visual C++ Language  Reference and related
// electronic documentation provided with Microsoft Visual C++.
// See these sources for detailed information regarding the
// Microsoft Visual C++ product.

// NOTE: This example will only work with Excel7 in Office95
// Compile with cl /GX comexcel.cpp
// TO DO: Edit the #import paths

#import <xl5en32.olb> rename_namespace("XLDemo") rename("DialogBox", "DialogBoxXL")

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
    using namespace XLDemo;

    try {
    ApplicationPtr pXL("Excel.Application.5");

    pXL->Visible = VARIANT_TRUE;

    WorkbookPtr pBook  = ((WorkbooksPtr) pXL->Workbooks())->Add((long)xlWorksheet);

    WorksheetPtr pSheet = pXL->ActiveSheet;
        
    try {
        // This one will fail
        pSheet->Name = "Market Share?";
    } catch (_com_error &e) {
        dump_com_error(e);
    }

    pSheet->Name = "Market Share!";

    ((RangePtr)pSheet->Range("A2"))->Value = "Company A";
    ((RangePtr)pSheet->Range("B2"))->Value = "Company B";
    ((RangePtr)pSheet->Range("C2"))->Value = "Company C";
    ((RangePtr)pSheet->Range("D2"))->Value = "Company D";

    ((RangePtr)pSheet->Range("A3"))->Value = 75.0;
    ((RangePtr)pSheet->Range("B3"))->Value = 14.0;
    ((RangePtr)pSheet->Range("C3"))->Value = 7.0;
    ((RangePtr)pSheet->Range("D3"))->Value = 4.0;
    
    Sleep(1000);

    RangePtr  pRange  = pSheet->Range("A2:D3");
    ChartPtr  pChart  = ((SheetsPtr) pBook->Charts())->Add();
    
    pChart->ChartWizard((Range*) pRange, (long) xl3DPie, 7L, (long) xlRows,
        1L, 0L, 2L, "Market Share");

    Sleep(6000);

    pBook->Saved = VARIANT_TRUE;
    pXL->Quit();
    } catch(_com_error &e) {
    dump_com_error(e);
    }
}
