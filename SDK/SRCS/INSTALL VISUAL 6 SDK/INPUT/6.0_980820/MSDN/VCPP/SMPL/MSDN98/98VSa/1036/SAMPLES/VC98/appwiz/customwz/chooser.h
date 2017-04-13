// chooser.h : declaration of the CDialogChooser class
//             This class keeps track of what dialogs to pop up when,
//              and remembers the current custom AppWizard "type" we're
//              creating (see typedlg.[h,cpp])
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

#ifndef __CHOOSER_H__
#define __CHOOSER_H__

// List of the steps we can pop up
enum
{
	DLG_CUSTOMTYPE = 1,
	DLG_ZAP,
	DLG_SEQUENCE,
};

#define NUM_DLGS 3

class CAppWizStepDlg;
class CDialogChooser
{
public:
	CDialogChooser();
	~CDialogChooser();

	// All calls by mfcapwz.dll to CCustomWizAppWiz::Next &
	//  CCustomWizAppWiz::Back are delegated to these member
	//  functions, which keep track of what dialog is up
	//  now, and what to pop up next.
	CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);

	// This class keeps track of the current custom AppWizard type
	//  we plan to create.  This is determined by the
	//  user at step 1 (typedlg.[h,cpp])
	void SetCustomType(int nCustomType)
		{ m_nCustomType = nCustomType; }
	int GetCustomType()
		{ return m_nCustomType; }

protected:
	int m_nCurrDlg;     // Current step's DLG_ enum from above, or 0 for
						//  the intial "New Project" dialog.
	CAppWizStepDlg* m_pDlgs[NUM_DLGS+1];
						// Instances of the dialog classes of our steps
	int m_nCustomType;  // Current custom AppWizard type (enum from typedlg.h)
	void UpdateTitleIfNecessary();
};

#endif //__CHOOSER_H__
