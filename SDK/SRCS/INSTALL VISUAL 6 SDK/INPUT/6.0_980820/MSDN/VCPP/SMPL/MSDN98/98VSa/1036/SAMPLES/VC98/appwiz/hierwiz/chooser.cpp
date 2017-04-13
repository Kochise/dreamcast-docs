// chooser.cpp : Implements the CDialogChooser class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "hierwiz.h"
#include "chooser.h"
#include "loadfile.h"
#include "editdlg.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// On construction, set up internal array with pointers to each step.
CDialogChooser::CDialogChooser()
{
	m_pDlgs[START_PAGE] = NULL;

	m_pDlgs[FEATURES_PAGE] = new CCustom1Dlg;
	m_pDlgs[LOADFILE_PAGE] = new CLoadFileDlg ;
	m_pDlgs[EDITDATA_PAGE] = new CEditDlg;

	m_nCurrDlg = 0;
}
// Remember where the custom steps begin, so we can delete them in
//  the destructor
#define FIRST_CUSTOM_STEP 1
#define LAST_CUSTOM_STEP 3

// The destructor deletes entries in the internal array corresponding to
//  custom steps.
CDialogChooser::~CDialogChooser()
{
	for (int i = FIRST_CUSTOM_STEP; i <= LAST_CUSTOM_STEP; i++)
	{
		ASSERT(m_pDlgs[i] != NULL);
		delete m_pDlgs[i];
	}
}

// Use the internal array to determine the next step.
CAppWizStepDlg* CDialogChooser::Next(CAppWizStepDlg* pDlg)
{
	ASSERT(0 <= m_nCurrDlg && m_nCurrDlg < LAST_DLG);

	m_nCurrDlg++ ;
	if(pDlg == m_pDlgs[FEATURES_PAGE]) // If the features page is active
		return m_pDlgs[CCustom1Dlg::m_DataSource] ;

	return m_pDlgs[m_nCurrDlg] ;
}

// Use the internal array to determine the previous step.
CAppWizStepDlg* CDialogChooser::Back(CAppWizStepDlg* pDlg)
{
	ASSERT(1 <= m_nCurrDlg && m_nCurrDlg <= LAST_DLG);

	m_nCurrDlg--;
	if(pDlg == m_pDlgs[FEATURES_PAGE])
		return m_pDlgs[START_PAGE];
	else
		return m_pDlgs[FEATURES_PAGE];
}
