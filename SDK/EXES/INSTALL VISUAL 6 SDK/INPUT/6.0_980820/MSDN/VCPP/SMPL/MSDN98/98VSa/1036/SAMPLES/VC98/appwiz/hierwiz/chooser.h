// chooser.h : declaration of the CDialogChooser class
//             This class keeps track of what dialogs to pop up when.
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

#ifndef __CHOOSER_H__
#define __CHOOSER_H__

#define LAST_DLG 3
#define START_PAGE      0   //start page
#define FEATURES_PAGE   1   //features page (CCustom1Dlg)
#define LOADFILE_PAGE   2   //load sample file page (CLoadFileDlg)
#define EDITDATA_PAGE   3   //edit sample data page (CEditDlg)

class CDialogChooser
{
public:
	CDialogChooser();
	~CDialogChooser();

	// All calls by mfcapwz.dll to CCustdeadAppWiz::Next
	//  & CCustdeadAppWiz::Back are delegated to these member
	//  functions, which keep track of what dialog is up
	//  now, and what to pop up next.
	CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);

protected:
	// Current step's index into the internal array m_pDlgs
	int m_nCurrDlg;
	CCustom1Dlg pg1 ;
	// Internal array of pointers to the steps
	CAppWizStepDlg* m_pDlgs[LAST_DLG + 1];
};

#endif //__CHOOSER_H__
