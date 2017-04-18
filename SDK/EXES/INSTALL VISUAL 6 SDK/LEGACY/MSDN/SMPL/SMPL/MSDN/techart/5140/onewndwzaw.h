#if !defined(AFX_ONEWNDWZAW_H__4201C6FD_B268_11D0_88D2_00C04FD235A5__INCLUDED_)
#define AFX_ONEWNDWZAW_H__4201C6FD_B268_11D0_88D2_00C04FD235A5__INCLUDED_

// OneWndWzaw.h : header file
//

class CDialogChooser;

// All function calls made by mfcapwz.dll to this custom AppWizard (except for
//  GetCustomAppWizClass-- see OneWndWz.cpp) are through this class.  You may
//  choose to override more of the CCustomAppWiz virtual functions here to
//  further specialize the behavior of this custom AppWizard.
class COneWndWzAppWiz : public CCustomAppWiz
{
public:
	virtual CAppWizStepDlg* Next(CAppWizStepDlg* pDlg);
	virtual CAppWizStepDlg* Back(CAppWizStepDlg* pDlg);
		
	virtual void InitCustomAppWiz();
	virtual void ExitCustomAppWiz();
	virtual void CustomizeProject(IBuildProject* pProject);

protected:
	CDialogChooser* m_pChooser;
};

// This declares the one instance of the COneWndWzAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global OneWndWzaw.  (Its definition is in OneWndWzaw.cpp.)
extern COneWndWzAppWiz OneWndWzaw;

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ONEWNDWZAW_H__4201C6FD_B268_11D0_88D2_00C04FD235A5__INCLUDED_)
