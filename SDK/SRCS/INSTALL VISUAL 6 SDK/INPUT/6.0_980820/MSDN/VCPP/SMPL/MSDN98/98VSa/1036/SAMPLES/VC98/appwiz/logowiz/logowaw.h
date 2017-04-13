// logowaw.h : header file
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

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see logowiz.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class CLogowizAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);

	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();

protected:
	CDialogChooser* m_pChooser;
};

// This declares the one instance of the CLogowizAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global Logowizaw.  (Its definition is in logowaw.cpp.)
extern CLogowizAppWiz logowizaw;
