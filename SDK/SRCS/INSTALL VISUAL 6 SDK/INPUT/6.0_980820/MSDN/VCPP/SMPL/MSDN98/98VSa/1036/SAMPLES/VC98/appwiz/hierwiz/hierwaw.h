// hierwaw.h : header file
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

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see hierwiz.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CHierwizAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);

	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();

protected:
	CDialogChooser * m_pChooser ;
};

// This declares the one instance of the CHierwizAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global Hierwizaw.  (Its definition is in hierwaw.cpp.)
extern CHierwizAppWiz hierwizaw;
