// typedlg.h : header file.  This dialog is step 1 and is used to select
//              the type of custom AppWizard to create
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

// These enumerate the different types of custom AppWizards we can create.
//  These must be in the same order as the corresponding radio buttons
enum
{
	CUSTOMTYPE_ZAP,
	CUSTOMTYPE_SEQUENCE,
	CUSTOMTYPE_BASE,
	CUSTOMTYPE_MAX,
};

class CCustomTypeDlg : public CAppWizStepDlg
{
// Construction
public:
	CCustomTypeDlg();   // standard constructor
	virtual BOOL OnDismiss();
	void UpdateTitle(const CString& strRoot);

// Dialog Data
	//{{AFX_DATA(CCustomTypeDlg)
	enum { IDD = IDD_CUSTOMAW_TYPE };
	int     m_nCustomType;
	UINT    m_nCustomSteps;
	CString m_strTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomTypeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EnableCustomSteps();
	void SetBitmap();
	UINT m_nBitmap;
	CString m_strLastCustomSteps;   // Remembers #custom steps, before it's reset to 0

	void SetCustomTypeMacros();
	void DefineTitleMacro();

	// Generated message map functions
	//{{AFX_MSG(CCustomTypeDlg)
	afx_msg BOOL OnClickedRadio(UINT nID);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
