// sampleaw.cpp: implementation of CSampleAppWiz class.
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

#include "stdafx.h"
#include "customwz.h"
#include "sampleaw.h"
#include "chooser.h"
#include "zap.h"
#include "options.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The CSampleAppWiz class.  Here we override many member functions of
//  CCustomAppWiz.

// Initialize state of this custom AppWizard.
void CSampleAppWiz::InitCustomAppWiz()
{
	m_pChooser = new CDialogChooser;
	m_bOverrideProcessing = FALSE;
	SetNumberOfSteps(2);                    // Initially two steps
	// Set the macro corresponding to the Custom AppWizard target type.
	//  This is used in mfcapwz.dll when it creates the target.
	DefineBoolMacro(_T("PROJTYPE_CUSTOMAW"), TRUE);
}

// Before exiting, deallocate memory used for the dialog chooser
void CSampleAppWiz::ExitCustomAppWiz()
{
	ASSERT(m_pChooser != NULL);
	delete m_pChooser;
	m_pChooser = NULL;
}

// This custom AppWizard only targets Win32 platform, so don't display
//  any others.
void CSampleAppWiz::GetPlatforms(CStringList& Platforms)
{
	POSITION pos = Platforms.GetHeadPosition();
	while (pos != NULL)
	{
		POSITION posCurr = pos;
		CString strPlatform = Platforms.GetNext(pos);
		if (strPlatform.Left(5) != _T("Win32"))
			Platforms.RemoveAt(posCurr);
	}
}

// Set options & macros derived from project name entered by end-user.
void SetRootOptions()
{
	// Set "FILEBASE" macro
	CString strFileBase;
	sampleaw.m_Dictionary.Lookup(_T("Root"), strFileBase);
	DefineStringMacro(_T("filebase"), strFileBase);
}

// If the end-user clicks next, let the dialog chooser decide
//  what to pop up next.
CAppWizStepDlg* CSampleAppWiz::Next(CAppWizStepDlg* pDlg)
{
	// If the end-user is dismissing the New Project dialog,
	//  call DefineRootMacros
	if (pDlg == NULL)
		SetRootOptions();

	return m_pChooser->Next(pDlg);
}

// If the end-user clicks back, let the dialog chooser decide
//  what to pop up.
CAppWizStepDlg* CSampleAppWiz::Back(CAppWizStepDlg* pDlg)
{
	return m_pChooser->Back(pDlg);
}

// We override LoadTemplate as part of implementing the project
//  zapper.
LPCTSTR CSampleAppWiz::LoadTemplate(LPCTSTR lpszTemplateName,
		DWORD& rdwSize, HINSTANCE hInstance)
{
	// If the resource we're loading contains a backslash in it...
	if (_tcschr(lpszTemplateName, _T('\\')))
	{
		// ... then it's a file we're about to zap (see CZap).
		m_bOverrideProcessing = TRUE;               // Remember we're overriding parsing
		return m_Zap.LoadFile(lpszTemplateName, rdwSize);// Prepare the zapper for this file
	}

	// Otherwise, defer to the base class implementation of LoadTemplate
	m_bOverrideProcessing = FALSE;

	// But first, be sure to define GENERATED_NEWPROJ_INF_FILES if it's time
	if (!_tcsicmp(lpszTemplateName, _T("newnwprj.inf")))
		m_Zap.DefineGeneratedNewprojInfMacro();

	return CCustomAppWiz::LoadTemplate(lpszTemplateName, rdwSize, hInstance);
}

// We override ProcessTemplate as part of implementing the project
//  zapper.
void CSampleAppWiz::ProcessTemplate(LPCTSTR lpszInput, DWORD dwSize, OutputStream* pOutput)
{
	// If we set m_bOverrideProcessing in LoadTemplate, then we're about
	//  zap this file.
	if (m_bOverrideProcessing)
	{
		// Zap the file into a template
		m_Zap.ZapFile(lpszInput, dwSize, pOutput);
		return;
	}

	// We're not zapping this file, so defer to the base class
	//  implementation of ProcessTemplate
	CCustomAppWiz::ProcessTemplate(lpszInput, dwSize, pOutput);
}

// We override PostProcessTemplate as part of implementing the project
//  zapper.
void CSampleAppWiz::PostProcessTemplate(LPCTSTR szTemplate)
{
	// If we set m_bOverrideProcessing in LoadTemplate, then we've just
	//  zapped this file.  Unload it.
	if (m_bOverrideProcessing)
	{
		m_Zap.UnloadFile();
		m_bOverrideProcessing = FALSE;
	}
}

// The dialog chooser keeps track of which type of custom AppWizard we're
//  creating (based on project, based on appwiz sequence, or base) so it
//  knows what dialog to pop up next.  Any request to set or get the
//  custom AppWizard type goes through the chooser.

void CSampleAppWiz::SetCustomType(int nCustomType)
{
	m_pChooser->SetCustomType(nCustomType);
}

int CSampleAppWiz::GetCustomType()
{
	return m_pChooser->GetCustomType();
}


// Create one global instance of this class anyone can see.
CSampleAppWiz sampleaw;
