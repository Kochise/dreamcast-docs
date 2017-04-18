// options.cpp : implementation of COptions class
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

#include "stdafx.h"
#include "customwz.h"
#include "sampleaw.h"
#include "options.h"
#include "typedlg.h"
#include "seqdlg.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// On construction, set the default values of user-selectable options
COptions::COptions()
{
	m_nCustomType = CUSTOMTYPE_ZAP;
	m_nCustomSteps = 1;
	m_nApwzSeq = APWZSEQ_EXE;
}

#define FIRST_DLG_RSC 129   // For entries in generated custom appwiz's resource.h


// These must be in the same order as the corresponding enum & radio buttons
static LPCTSTR lpszApwzSeqMacros[] =
{
	_T("APWZSEQ_EXE"),
	_T("APWZSEQ_DLL"),
};

// Defines step-related template macros, which depend on which
//  options were selected.
void COptions::DefineDlgMacros()
{
	for (UINT i=0; i < APWZSEQ_MAX; i++)
		DefineBoolMacro(lpszApwzSeqMacros[i], FALSE);

	// Determine the number of standard AppWizard steps in the generated
	//  custom AppWizard
	int nApwzSteps = 0;
	if (m_nCustomType == CUSTOMTYPE_SEQUENCE)
	{
		nApwzSteps = (m_nApwzSeq == APWZSEQ_EXE) ?
			NUM_APWZ_EXE_STEPS : NUM_APWZ_DLL_STEPS;

		// Set macro corresponding to the AppWizard sequence (exe or dll) off of which
		//  we're basing this custom AppWizard (reset the others).
		ASSERT(m_nApwzSeq == 0 || m_nApwzSeq == 1);
		DefineBoolMacro(lpszApwzSeqMacros[m_nApwzSeq], TRUE);
	}

	// Set custom-dialog-dependent macros as appropriate

	DefineBoolMacro(_T("HAS_NEW_STEPS"), m_nCustomSteps != 0);

	ASSERT(m_nCustomSteps < 10);

	DefineIntMacro(_T("NUM_NEW_STEPS"), m_nCustomSteps);
	DefineIntMacro(_T("MPDLGS_INDEX_LAST"), m_nCustomSteps + nApwzSteps);
	DefineIntMacro(_T("LAST_DOCTRACK_INDEX"), m_nCustomSteps + NUM_APWZ_EXE_DOC_STEPS);
	DefineIntMacro(_T("LAST_DLGTRACK_INDEX"), m_nCustomSteps + NUM_APWZ_EXE_DLG_STEPS);

	CString strCustomIndices;
	for (i=0; i < m_nCustomSteps; i++)
	{
		DefineIntMacro(_T("ITERATOR"), i, i+1);
		DefineIntMacro(_T("DLGID_VALUE"), i,  i + FIRST_DLG_RSC);
		DefineIntMacro(_T("MPDLGS_INDEX"), i, nApwzSteps + i + 1);

		CString strCustomIndex;
		strCustomIndex.Format(_T(", %d"), nApwzSteps + i + 1);
		strCustomIndices += strCustomIndex;
	}
	DefineStringMacro(_T("CUSTOM_INDICES"), strCustomIndices);
}

// Create one global instance of this class anyone can see.
COptions g_options;
