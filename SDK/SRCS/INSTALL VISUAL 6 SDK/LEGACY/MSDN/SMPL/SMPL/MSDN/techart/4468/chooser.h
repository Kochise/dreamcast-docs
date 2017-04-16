// chooser.h : declaration of the CDialogChooser class
//             This class keeps track of what dialogs to pop up when.

#ifndef __CHOOSER_H__
#define __CHOOSER_H__

#define LAST_DLG 3

class CDialogChooser
{
public:
	CDialogChooser();
	~CDialogChooser();

	// All calls by mfcapwz.dll to CNtDDWzdAppWiz::Next
	//  & CNtDDWzdAppWiz::Back are delegated to these member
	//  functions, which keep track of what dialog is up
	//  now, and what to pop up next.
	CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);
    BOOL RegisterNewSteps(int);
    void NukeAddlStepArray();
protected:
	// Current step's index into the internal array m_pDlgs
	int m_nCurrDlg;

	// Internal array of pointers to the steps
	CAppWizStepDlg* m_pDlgs[LAST_DLG + 1];
	CAppWizStepDlg** m_iNewStepArray;
	int m_iAddlSteps;
};

#endif //__CHOOSER_H__
