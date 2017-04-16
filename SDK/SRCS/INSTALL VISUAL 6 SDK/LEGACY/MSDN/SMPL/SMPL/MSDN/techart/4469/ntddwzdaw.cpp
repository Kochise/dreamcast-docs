// NtDDWzdaw.cpp : implementation file
//

#include "stdafx.h"
#include "NtDDWzd.h"
#include "NtDDWzdaw.h"
#include "chooser.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif






// This is called immediately after the custom AppWizard is loaded.  Initialize
//  the state of the custom AppWizard here.
void CNtDDWzdAppWiz::InitCustomAppWiz()
{
	// Create a new dialog chooser; CDialogChooser's constructor initializes
	//  its internal array with pointers to the steps.
	m_pChooser = new CDialogChooser;

	// Set the maximum number of steps.
	SetNumberOfSteps(LAST_DLG);

	// TODO: Add any other custom AppWizard-wide initialization here.
}

// This is called just before the custom AppWizard is unloaded.
void CNtDDWzdAppWiz::ExitCustomAppWiz()
{
	// Deallocate memory used for the dialog chooser
	ASSERT(m_pChooser != NULL);
	delete m_pChooser;
	m_pChooser = NULL;

	// TODO: Add code here to deallocate resources used by the custom AppWizard
}

// This is called when the user clicks "Create..." on the New Project dialog
//  or "Next" on one of the custom AppWizard's steps.
CAppWizStepDlg* CNtDDWzdAppWiz::Next(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Next(pDlg);
}

// This is called when the user clicks "Back" on one of the custom
//  AppWizard's steps.
CAppWizStepDlg* CNtDDWzdAppWiz::Back(CAppWizStepDlg* pDlg)
{
	// Delegate to the dialog chooser
	return m_pChooser->Back(pDlg);
}

void CNtDDWzdAppWiz::RegisterNewSteps(int i)
{ 
 m_pChooser->RegisterNewSteps(i);
 SetNumberOfSteps(i+LAST_DLG);
};



// Here we define one instance of the CNtDDWzdAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global NtDDWzdaw.
CNtDDWzdAppWiz NtDDWzdaw;

