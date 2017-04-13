// seqdlg.h : header file.  This dialog contains options for basing a
//             custom AppWizard off of a standard AppWizard sequence
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

// These must match the order of the corresponding radio buttons
enum
{
	APWZSEQ_EXE,
	APWZSEQ_DLL,
	APWZSEQ_MAX,
};

/////////////////////////////////////////////////////////////////////////////
// CSequenceDlg dialog

class CSequenceDlg : public CAppWizStepDlg
{
// Construction
public:
	CSequenceDlg();   // standard constructor
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CSequenceDlg)
	enum { IDD = IDD_APWZ_SEQUENCE };
	int     m_nApwzSeq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSequenceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetSeqBitmap();    // Sets m_nSeqBitmap according to options
	UINT m_nSeqBitmap;      // IDB_ of bitmap to show
	void DefineDefaultLangMacros();
	BOOL DefineLangMacros();
	void InitLangList();
	void EnableLangListbox(BOOL bEnable);
	CStringList m_strlLanguages;

	// Generated message map functions
	//{{AFX_MSG(CSequenceDlg)
	afx_msg BOOL OnClickedRadio(UINT nID);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
