// sampleaw.cpp: implementation of CSampleAppWiz class.  This is where we
//                  override many of CCustomAppWiz's member functions.
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//
#include "zap.h"

class CDialogChooser;

class CSampleAppWiz : public CCustomAppWiz
{
public:
	virtual void GetPlatforms(CStringList& pPlatforms);

	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);

	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();

	virtual LPCTSTR LoadTemplate(LPCTSTR lpszTemplateName,
		DWORD& rdwSize, HINSTANCE hInstance = NULL);

	virtual void ProcessTemplate(LPCTSTR lpszInput, DWORD dwSize, OutputStream* pOutput);
	virtual void PostProcessTemplate(LPCTSTR szTemplate);

	void SetCustomType(int nCustomType);
	int GetCustomType();

	CZap m_Zap;

protected:
	CDialogChooser* m_pChooser;
	BOOL m_bOverrideProcessing;
};

extern CSampleAppWiz sampleaw;
