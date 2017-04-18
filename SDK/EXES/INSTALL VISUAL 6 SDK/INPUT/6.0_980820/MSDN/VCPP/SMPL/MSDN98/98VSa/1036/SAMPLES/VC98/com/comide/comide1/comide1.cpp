//1
// NOTE: This program will only automate msdev from within itself
//       under _DEBUG build.  Run comide1.exe standalone or from within msdev
//       using BuildExecute (Ctrl-F5), not DebugGo.

// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Visual C++ Language  Reference and related
// electronic documentation provided with Microsoft Visual C++.
// See these sources for detailed information regarding the
// Microsoft Visual C++ product.

#include <stdio.h>
#include <assert.h>
#include <tchar.h>

#import <devshl.dll> no_namespace
#import <devedit.pkg> rename("ReplaceText", "ReplaceTxt") rename("FindText", "FindTxt")

using namespace DSTextEditor;

const int nBufLen = 512;
const int nLives = 4; // nLives must be even

// TO DO: Edit these paths
#pragma message ("Edit the paths at lines 19-21 in comide1.cpp to point to your sample tree.")
LPCTSTR pszSource = _T("d:/samples/com/comide/comide1/comide1.cpp");
LPCTSTR pszProject = _T("d:/samples/com/comide/comide2/comide2.dsw");
LPCTSTR pszProjectSource = _T("d:/samples/com/comide/comide2/comide2.cpp");

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

struct StartUpCom {
    StartUpCom() { CoInitialize(NULL); }
    ~StartUpCom() { CoUninitialize(); }
} _global_com_inst;

void main()
{
    IApplicationPtr pApp;

    try {
    try {
    // Start up existing msdev, if available
    HRESULT hr = pApp.GetActiveObject(L"MSDEV.APPLICATION");
    if (FAILED(hr))
        _com_issue_error(hr);

    } catch(_com_error& e) {
    dump_com_error(e);
    _tprintf(_T("\aNOTE: This is not a TRUE error!!\n"));
    _tprintf(_T("\aStarting up Msdev.exe...........\n"));

    try {
    // Start up fresh instance of msdev
    HRESULT hr = pApp.CreateInstance(L"MSDEV.APPLICATION", NULL, CLSCTX_LOCAL_SERVER);
    if (FAILED(hr))
        _com_issue_error(hr);
    } catch(_com_error& e) {
    dump_com_error(e);
    }

    }

    pApp->Visible = VARIANT_TRUE;

    IDocumentsPtr pDocs = pApp->Documents;

    pDocs->Open(pszProject, "Auto", true);
    pDocs->Open(pszProjectSource);

    ITextDocumentPtr pTextDoc = pApp->ActiveDocument;

    ITextWindowPtr pTextWin = pTextDoc->ActiveWindow;
    pTextWin->WindowState = DSTextEditor::dsWindowStateMaximized;

    ITextSelectionPtr pTextSel = pTextDoc->Selection;

    pTextSel->SelectAll();
    pTextSel->Delete();

    FILE* fptr1 = _tfopen(pszSource, _T("rt"));
    assert(fptr1 != NULL);
    TCHAR buf1[nBufLen];

    while (1)
    {
        assert(!feof(fptr1) && !ferror(fptr1));
        LPTSTR p = _fgetts(buf1, nBufLen, fptr1);
        if (p != buf1)
        {
            assert(feof(fptr1));
            assert(!ferror(fptr1));
            break;
        }
        pTextSel->Text = p;
    }
    fclose(fptr1);

    pTextDoc->Save();
    pTextSel->StartOfDocument();
    pTextSel->SelectLine();

    _bstr_t pb = pTextSel->Text;
    LPTSTR p = (LPTSTR) pb;
    assert(p != NULL && _tcslen(p) > 2);
    assert(isdigit(p[2]));
    int nLife = 0;
    _stscanf(&p[2], _T("%d"), &nLife);
    assert(nLife > 0 && nLife <= 0x100000);

    if (nLife < nLives)
        _stprintf(&p[2], _T("%d"), nLife+1);
    else // nLives must be even
    {
        _stprintf(&p[3], _T("%s"), _T("       "));
        _stprintf(&p[2], _T("%d"), 1);
    }
    pTextSel->LineUp();
    pTextSel->DestructiveInsert(p);
    pTextDoc->Save();

    assert(pTextSel->FindTxt("pszSource", (long) dsMatchFromStart));
    pTextSel->SelectLine();
    if ((nLife % 2) == 1)
        assert(pTextSel->ReplaceTxt("comide1", "comide2", (long) dsMatchForward));
    else
        assert(pTextSel->ReplaceTxt("comide2", "comide1", (long) dsMatchForward));

    assert(pTextSel->FindTxt("pszProject", (long) dsMatchForward));
    pTextSel->SelectLine();
    if ((nLife % 2) == 0)
        assert(pTextSel->ReplaceTxt("comide1", "comide2", (long) dsMatchForward));
    else
        assert(pTextSel->ReplaceTxt("comide2", "comide1", (long) dsMatchForward));

    assert(pTextSel->FindTxt("pszProjectSource", (long) dsMatchForward));
    pTextSel->SelectLine();
    if ((nLife % 2) == 0)
        assert(pTextSel->ReplaceTxt("comide1", "comide2", (long) dsMatchForward));
    else
        assert(pTextSel->ReplaceTxt("comide2", "comide1", (long) dsMatchForward));

    pTextDoc->Save();
    if (nLife < nLives)
    {
        pApp->RebuildAll();
        pTextDoc->Close();
        pApp->ExecuteCommand("BuildExecute");
    }

    pDocs->CloseAll();
    pApp->ExecuteCommand("WorkspaceClose");

    if (nLife >= nLives)
        pApp->Quit();

    } catch(_com_error& e) {
        dump_com_error(e);
    }
}

