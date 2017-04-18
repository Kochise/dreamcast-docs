// chooser.cpp : implementation of the CDialogChooser class
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

#include "stdafx.h"
#include "customwz.h"
#include "sampleaw.h"
#include "chooser.h"
#include "typedlg.h"
#include "zapdlg.h"
#include "seqdlg.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// On construction, create instances of each step we can pop up.
CDialogChooser::CDialogChooser()
{
	m_pDlgs[0] = NULL;

	m_pDlgs[DLG_CUSTOMTYPE] = new CCustomTypeDlg;
	m_pDlgs[DLG_ZAP] = new CZapDlg;
	m_pDlgs[DLG_SEQUENCE] = new CSequenceDlg;

	m_nCurrDlg = 0;     // We start with the New Project dialog
	m_nCustomType = CUSTOMTYPE_ZAP; // Default custom appwiz type is base
}

// On deconstruction, destroy instances of each step.
CDialogChooser::~CDialogChooser()
{
	for (int i=1; i <= NUM_DLGS; i++)
	{
		ASSERT(m_pDlgs[i] != NULL);
		delete m_pDlgs[i];
	}
}

void CDialogChooser::UpdateTitleIfNecessary()
{
	static CString strPreviousRoot;
	CString strCurrentRoot;
	sampleaw.m_Dictionary.Lookup(_T("Root"), strCurrentRoot);
	if (strCurrentRoot != strPreviousRoot)
	{
		// The project name has changed, so update the
		//  default value of the custom AppWizard's title
		((CCustomTypeDlg*) m_pDlgs[DLG_CUSTOMTYPE])->UpdateTitle(strCurrentRoot);
		strPreviousRoot = strCurrentRoot;
	}
}

// On Next, use the custom AppWizard type we're generating to determine what
//  dialog to pop up.
CAppWizStepDlg* CDialogChooser::Next(CAppWizStepDlg* pDlg)
{
	ASSERT(pDlg == m_pDlgs[m_nCurrDlg]);
	ASSERT(0 == m_nCurrDlg || m_nCurrDlg == DLG_CUSTOMTYPE);

	if (pDlg == NULL)   // i.e., if the New Project Dialog is present,
	{
		m_nCurrDlg = DLG_CUSTOMTYPE;    // Then pop up our first step
		UpdateTitleIfNecessary();   // and update title's default
	}
	else if (m_nCustomType == CUSTOMTYPE_ZAP)
	{
		m_nCurrDlg = DLG_ZAP;       // Pop up the zap step
	}
	else    // m_nCustomType == CUSTOMTYPE_SEQUENCE
	{
		m_nCurrDlg = DLG_SEQUENCE;  // Pop up the appwiz sequence step
	}

	return m_pDlgs[m_nCurrDlg];
}

// On Back, determine whether we should go back to the New Project
//  dialog, or back to step 1.
CAppWizStepDlg* CDialogChooser::Back(CAppWizStepDlg* pDlg)
{
	ASSERT(pDlg == m_pDlgs[m_nCurrDlg]);
	ASSERT(0 < m_nCurrDlg && m_nCurrDlg <= NUM_DLGS);

	if (m_nCurrDlg == DLG_CUSTOMTYPE)
		m_nCurrDlg = 0; // If we're on step 1, go to New Project dialog
	else
		m_nCurrDlg = DLG_CUSTOMTYPE;    // Otherwise, go to step 1

	return m_pDlgs[m_nCurrDlg];
}
