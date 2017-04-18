// chooser.h : declaration of the CDialogChooser class
//
// This class is where you set up the sequence of steps that will
// be followed in your custom AppWizard.  These steps can include
// both standard AppWizard steps and your own custom steps.
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#ifndef __CHOOSER_H__
#define __CHOOSER_H__

#define LAST_DLG 7

class CDialogChooser
{
public:
	CDialogChooser();
	~CDialogChooser();

	// All calls by mfcapwz.dll to CLogowizAppWiz::Next
	//  & CLogowizAppWiz::Back are delegated to these member
	//  functions, which keep track of what dialog is up
	//  now, and what to pop up next.
	CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);

protected:
	// Current step's index into the current track (defined in chooser.cpp).
	int m_nCurrDlg;

	// Internal array of pointers to the steps
	CAppWizStepDlg* m_pDlgs[LAST_DLG + 1];

	// Current track (MDI/SDI app or dialog-based app; see chooser.cpp).
	int m_nTrack;
};

#endif //__CHOOSER_H__
