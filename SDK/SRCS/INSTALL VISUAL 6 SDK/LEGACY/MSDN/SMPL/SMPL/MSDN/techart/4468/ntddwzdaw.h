// NtDDWzdaw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see NtDDWzd.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.



class CNtDDWzdAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
    void RegisterNewSteps(int i);
//    virtual void ProcessTemplate( LPCTSTR lpszInput, DWORD dwSize, OutputStream* pOutput );
//    virtual void PostProcessTemplate( LPCTSTR szTemplate)
//	 { AfxMessageBox(szTemplate);};


protected:
	CDialogChooser* m_pChooser;
};

// This declares the one instance of the CNtDDWzdAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global NtDDWzdaw.  (Its definition is in NtDDWzdaw.cpp.)
extern CNtDDWzdAppWiz NtDDWzdaw;
