// typedlg.cpp : implementation file
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

#include "stdafx.h"
#include "customwz.h"
#include "sampleaw.h"
#include "typedlg.h"
#include "options.h"
#include "paint.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CCustomTypeDlg dialog


CCustomTypeDlg::CCustomTypeDlg()
	: CAppWizStepDlg(CCustomTypeDlg::IDD)
{
	//{{AFX_DATA_INIT(CCustomTypeDlg)
	m_nCustomType = CUSTOMTYPE_ZAP;
	m_nCustomSteps = 1;
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
	m_strLastCustomSteps = _T("1");
	SetBitmap();
}


void CCustomTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CAppWizStepDlg::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCustomTypeDlg)
	DDX_Radio(pDX, IDC_ZAP, m_nCustomType);
	DDX_Text(pDX, IDC_STEPS, m_nCustomSteps);
	DDV_MinMaxUInt(pDX, m_nCustomSteps, 0, 9);
	DDX_Text(pDX, IDC_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
	EnableCustomSteps();
}

// Base default title of custom AppWizard off of project name.  This is called
//  by CDialogChooser when the New Project dialog is dimissed with a
//  new project name.
void CCustomTypeDlg::UpdateTitle(const CString& strRoot)
{
	m_strTitle = strRoot + _T(" AppWizard");
}

BEGIN_MESSAGE_MAP(CCustomTypeDlg, CAppWizStepDlg)
	//{{AFX_MSG_MAP(CCustomTypeDlg)
	ON_COMMAND_EX(IDC_ZAP, OnClickedRadio)
	ON_COMMAND_EX(IDC_SEQUENCE, OnClickedRadio)
	ON_COMMAND_EX(IDC_CUSTOM, OnClickedRadio)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCustomTypeDlg message handlers

#define STEP1_LEFT          8
#define STEP1_TOP           40
#define STEP1_WIDTH         179
#define STEP1_HEIGHT        180

// Override OnPaint to draw pictures on the left side
void CCustomTypeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	PaintBackground(&dc, this);

	CDC dcMem;
	if (!dcMem.CreateCompatibleDC(&dc))
		return;

	// Picture
	PaintBitmap(m_nBitmap, STEP1_LEFT, STEP1_TOP, STEP1_WIDTH, STEP1_HEIGHT, &dc, &dcMem);
}


// Set member variable to the bitmap ID corresponding to the currently
//  selected custom AppWizard type
void CCustomTypeDlg::SetBitmap()
{
	static UINT nBmps[] = {IDB_STEP1A, IDB_STEP1B, IDB_STEP1C};
	ASSERT (m_nCustomType >= 0 && m_nCustomType < 3);
	m_nBitmap = nBmps[m_nCustomType];
}

// This handler allows us to dynamically change the bitmap as soon
//  as a new custom AppWizard type is selected.  We also change the number
//  of steps accordingly, since two of the options add an extra
//  step after this one.
BOOL CCustomTypeDlg::OnClickedRadio(UINT nID)
{
	switch(nID)
	{
	case IDC_ZAP:
		m_nCustomType = CUSTOMTYPE_ZAP;
		SetNumberOfSteps(2);
		break;
	case IDC_CUSTOM:
		m_nCustomType = CUSTOMTYPE_BASE;
		SetNumberOfSteps(1);
		break;
	case IDC_SEQUENCE:
		m_nCustomType = CUSTOMTYPE_SEQUENCE;
		SetNumberOfSteps(2);
		break;
	default:
		ASSERT(FALSE);
	}
	SetBitmap();
	sampleaw.SetCustomType(m_nCustomType);
	EnableCustomSteps();

	// Invalidate the portion of this dialog on which we draw the picture
	CRect rect(STEP1_LEFT, STEP1_TOP, STEP1_LEFT + STEP1_WIDTH, STEP1_TOP + STEP1_HEIGHT);
	RedrawWindow(&rect, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	return TRUE;
}

// If we're basing a custom AppWizard off of a project, that custom AppWizard
//  must have 0 steps.  Thus, we must disable the "How many custom steps?"
//  control when appropriate.
void CCustomTypeDlg::EnableCustomSteps()
{
	BOOL bEnable = (m_nCustomType == CUSTOMTYPE_BASE || m_nCustomType == CUSTOMTYPE_SEQUENCE);
	GetDlgItem(IDC_STC_STEPS)->EnableWindow(bEnable);
	if (!GetDlgItem(IDC_STEPS)->EnableWindow(bEnable))
		// Remember number of custom steps if it was previously enabled
		GetDlgItem(IDC_STEPS)->GetWindowText(m_strLastCustomSteps);

	if (bEnable == TRUE)
		GetDlgItem(IDC_STEPS)->SetWindowText(m_strLastCustomSteps);
	else
		GetDlgItem(IDC_STEPS)->SetWindowText(_T("0"));
}

//  These must be in the same order as the corresponding radio buttons &
//   CUSTOMTYPE enum
static LPCTSTR lpszCustomTypeMacros[] =
{
	_T("CUSTOMTYPE_ZAP"),
	_T("CUSTOMTYPE_SEQUENCE"),
	_T("CUSTOMTYPE_BASE"),
};

// Sets the macro corresponding to the custom AppWizard type (resets the others)
void CCustomTypeDlg::SetCustomTypeMacros()
{
	for (UINT i=0; i < CUSTOMTYPE_MAX; i++)
		DefineBoolMacro(lpszCustomTypeMacros[i], FALSE);

	ASSERT(m_nCustomType >= 0 && m_nCustomType <= 2);
	DefineBoolMacro(lpszCustomTypeMacros[m_nCustomType], TRUE);
}

// Sets the macro for the custom AppWizard's title
void CCustomTypeDlg::DefineTitleMacro()
{
	DefineStringMacro(_T("AW_TITLE"), m_strTitle);
}

// Set step-related template macros before dismissing
BOOL CCustomTypeDlg::OnDismiss()
{
	ASSERT (0 <= m_nCustomType && m_nCustomType < CUSTOMTYPE_MAX);
	if (!UpdateData(TRUE))
		return FALSE;

	g_options.m_nCustomType = m_nCustomType;
	g_options.m_nCustomSteps = m_nCustomSteps;
	g_options.DefineDlgMacros();
	SetCustomTypeMacros();
	DefineTitleMacro();
	return TRUE;
}
