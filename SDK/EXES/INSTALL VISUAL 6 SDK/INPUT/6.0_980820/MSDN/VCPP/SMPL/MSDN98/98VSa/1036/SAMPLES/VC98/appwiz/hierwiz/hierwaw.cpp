// hierwaw.cpp : implementation file
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
#include "hierwaw.h"
#include "chooser.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// This is called immediately after the custom AppWizard is loaded.  Initialize
//  the state of the custom AppWizard here.
void CHierwizAppWiz::InitCustomAppWiz()
{
	m_pChooser = new CDialogChooser ;
	// There are 2 steps in this custom AppWizard.
	SetNumberOfSteps(2);

}

// This is called just before the custom AppWizard is unloaded.
void CHierwizAppWiz::ExitCustomAppWiz()
{
	//Deallocate memory used by the dialog chooser.
	ASSERT(m_pChooser !=NULL) ;
	delete(m_pChooser) ;
	m_pChooser = NULL ;
}

// This is called when the user clicks "Create..." on the New Project dialog
CAppWizStepDlg* CHierwizAppWiz::Next(CAppWizStepDlg* pDlg)
{
	// Set template macros based on the project name entered by the user.
	return m_pChooser->Next(pDlg) ;
}

CAppWizStepDlg* CHierwizAppWiz::Back(CAppWizStepDlg* pDlg)
{
	return m_pChooser->Back(pDlg) ;
}

// Here we define one instance of the CHierwizAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global hierwiaw.
CHierwizAppWiz hierwizaw;
