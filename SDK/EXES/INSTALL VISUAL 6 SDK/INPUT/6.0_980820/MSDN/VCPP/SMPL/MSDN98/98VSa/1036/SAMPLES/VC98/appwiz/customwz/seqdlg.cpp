// seqdlg.cpp : implementation file
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

#include "stdafx.h"
#include "customwz.h"
#include "seqdlg.h"
#include "sampleaw.h"
#include "typedlg.h"
#include "options.h"
#include "paint.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Retrieve language suffix ("enu" or "fra", etc.)
void GetLangSuffix(CString& strLang)
{
	int nLeftParen = strLang.Find(_T('('));
	ASSERT(nLeftParen != -1);
	strLang = strLang.Mid(nLeftParen+1);    // Now, strLang starts at the DLL name
	strLang.MakeLower();
	int nPeriod = strLang.Find(_T('.'));
	ASSERT(nPeriod != -1);
	ASSERT(strLang.Left(5) == _T("appwz"));
	strLang = strLang.Mid(5, nPeriod-5);
}

/////////////////////////////////////////////////////////////////////////////
// CSequenceDlg dialog


CSequenceDlg::CSequenceDlg()
	: CAppWizStepDlg(CSequenceDlg::IDD)
{
	//{{AFX_DATA_INIT(CSequenceDlg)
	m_nApwzSeq = APWZSEQ_EXE;
	//}}AFX_DATA_INIT
	SetSeqBitmap();
	DefineDefaultLangMacros();
}

void CSequenceDlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSequenceDlg)
	DDX_Radio(pDX, IDC_APWZ_SEQ, m_nApwzSeq);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSequenceDlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CSequenceDlg)
	ON_COMMAND_EX(IDC_APWZ_SEQ, OnClickedRadio)
	ON_WM_PAINT()
	ON_COMMAND_EX(IDC_APWZ_SEQ2, OnClickedRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSequenceDlg message handlers

#define STEP2AB_LEFT            8
#define STEP2AB_TOP             40
#define STEP2AB_WIDTH           179
#define STEP2AB_HEIGHT          180

// Override OnPaint to draw pictures on the left side
void CSequenceDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	PaintBackground(&dc, this);

	CDC dcMem;
	if (!dcMem.CreateCompatibleDC(&dc))
		return;

	// picture
	PaintBitmap(m_nSeqBitmap, STEP2AB_LEFT, STEP2AB_TOP, STEP2AB_WIDTH, STEP2AB_HEIGHT, &dc, &dcMem);
}

// Set member variable to the bitmap ID corresponding to the currently
//  selected AppWizard sequence
void CSequenceDlg::SetSeqBitmap()
{
	static UINT nBmps[] = {IDB_STEP2A, IDB_STEP2B};
	ASSERT (m_nApwzSeq == 0 || m_nApwzSeq == 1);
	m_nSeqBitmap = nBmps[m_nApwzSeq];
}

// This handler allows us to dynamically change the bitmap as soon
//  as a new AppWizard sequence is selected.
BOOL CSequenceDlg::OnClickedRadio(UINT nID)
{
	UpdateData(TRUE);
	SetSeqBitmap();

	// Invalidate the portion of this dialog on which we draw the picture
	CRect rect(STEP2AB_LEFT, STEP2AB_TOP, STEP2AB_LEFT + STEP2AB_WIDTH, STEP2AB_TOP + STEP2AB_HEIGHT);
	RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	EnableLangListbox(m_nApwzSeq == APWZSEQ_EXE);

	return TRUE;
}

void CSequenceDlg::DefineDefaultLangMacros()
{
	ScanForAvailableLanguages(m_strlLanguages);

	// m_strlLanguages is now a stringlist whose entries are of the form:
	//  "U.S. English (appwzenu.dll);0x040904e4"  For the purposes of the
	//  listbox, we want to strip out the translation identifiers
	//  (0x040904e4).  However, we retain the POSITION in m_strlLanguages
	//  for each entry, so that when we generate the custom AppWizard, its
	//  code will correctly call SetSupportedLanguages with the original
	//  entries that AppWizard gave us here, complete with the translation
	//  identifiers (see InitLangList() below).

	POSITION pos = m_strlLanguages.GetHeadPosition();
	int nLanguageCount = 0;
	CString strSupportedLangs;
	while (pos != NULL)
	{
		CString strLang = m_strlLanguages.GetNext(pos);
		strSupportedLangs += _T("\\n") + strLang;
		GetLangSuffix(strLang);
		DefineStringMacro(_T("CUSTOM_LANG_SUFFIX"), nLanguageCount++, strLang);
	}

	ASSERT(!strSupportedLangs.IsEmpty());
	strSupportedLangs = strSupportedLangs.Mid(2);   // Chop off leading '\n'
	DefineStringMacro(_T("SUPPORTED_LANGS"), strSupportedLangs);
	DefineIntMacro(_T("NUM_CUSTOM_LANGS"), nLanguageCount);
}

// Set macros corresponding to the languages selected
#define MAX_SELECTED_LANGS 32
BOOL CSequenceDlg::DefineLangMacros()
{
	CString strSupportedLangs;
	int pnSelectedLangs[MAX_SELECTED_LANGS];
	CListBox* pList = (CListBox*) GetDlgItem(IDC_LANGS);
	int nSelCount = pList->GetSelCount();

	if (nSelCount > MAX_SELECTED_LANGS)
	{
		// We use a stack-allocated, static-size array for storing the
		//  listbox selections, since it's cheaper than using the heap.
		//  Print error in the unlikely event there are over 32 languages
		//  installed & selected.
		CString strPrompt;
		strPrompt.LoadString(IDP_TOO_MANY_LANGS);
		strPrompt.Format(strPrompt, MAX_SELECTED_LANGS);
		AfxMessageBox(strPrompt);
		return FALSE;
	}

	// Make sure at least one language is selected
	if (nSelCount == 0)
	{
		AfxMessageBox(IDP_NO_LANGS_SELECTED);
		return FALSE;
	}

	// Go through listbox and make a string of the names of the selected
	//  languages.  The string will be of the form:
	//  "U.S. English (appwzenu.dll)\nFrench (appwzfra.dll)"
	pList->GetSelItems(MAX_SELECTED_LANGS, pnSelectedLangs);

	for (int i=0; i < nSelCount; i++)
	{
		POSITION pos = (POSITION) pList->GetItemData(pnSelectedLangs[i]);
		CString strLang = m_strlLanguages.GetAt(pos);
		strSupportedLangs += _T("\\n") + strLang;

		// Retrieve language suffix ("enu" or "fra", etc.)
		GetLangSuffix(strLang);
		DefineStringMacro(_T("CUSTOM_LANG_SUFFIX"), i, strLang);
	}

	ASSERT(!strSupportedLangs.IsEmpty());
	strSupportedLangs = strSupportedLangs.Mid(2);   // Chop off leading '\n'
	DefineStringMacro(_T("SUPPORTED_LANGS"), strSupportedLangs);
	DefineIntMacro(_T("NUM_CUSTOM_LANGS"), nSelCount);

	return TRUE;
}


// Set step-related template macros before dismissing
BOOL CSequenceDlg::OnDismiss()
{
	if (!UpdateData(TRUE))
		return FALSE;

	if (m_nApwzSeq == APWZSEQ_EXE && !DefineLangMacros())
		return FALSE;

	g_options.m_nApwzSeq = m_nApwzSeq;
	g_options.DefineDlgMacros();

	return TRUE;
}

void CSequenceDlg::EnableLangListbox(BOOL bEnable)
{
	GetDlgItem(IDC_LANGS)->EnableWindow(bEnable);
	GetDlgItem(IDC_LANGS_STATIC)->EnableWindow(bEnable);
}

void CSequenceDlg::InitLangList()
{
	CListBox* pList = (CListBox*) GetDlgItem(IDC_LANGS);

	int i = 0;
	POSITION pos = m_strlLanguages.GetHeadPosition();
	while (pos != NULL)
	{
		POSITION posCurrent = pos;
		CString strLang = m_strlLanguages.GetNext(pos);
		int nSemicolon = strLang.Find(_T(';'));
		ASSERT(nSemicolon != -1);

		// Add the entry minus the translation ID to the listbox
		i = pList->AddString(strLang.Left(nSemicolon));

		// Retain original POSITION for use when generating the wizard
		pList->SetItemData(i, (DWORD) posCurrent);
	}

	// By default, the custom AppWizard will support the languages AppWizard
	//  supports.  Thus, we start off the listbox by selecting all languages.
	if (i == 0)
		pList->SetSel(0, TRUE);
	else
		pList->SelItemRange(TRUE, 0, i);

	EnableLangListbox(m_nApwzSeq == APWZSEQ_EXE);
}


BOOL CSequenceDlg::OnInitDialog()
{
	CAppWizStepDlg::OnInitDialog();
	InitLangList();

	return TRUE;
}
