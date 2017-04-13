// cstm1dlg.h : header file
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

/////////////////////////////////////////////////////////////////////////////
// CCustom1Dlg dialog
#ifndef __CUSTMDLG1__
#define __CUSTMDLG1__

//Flags set depending on user choices about sample text.
#define NONE 0
#define READFILE 2
#define ENTERTEXT 3

// Return values from sample text radio buttons.
#define TEXT_FROM_FILE 0
#define TEXT_FROM_KEYBOARD 1
#define NO_SAMPLE_TXT 2

// The number of steps the Wizard will have based on the user selection
#define NO_DATA_STEPS 1
#define READ_FILE_STEPS 2
#define ENTER_DATA_STEPS 2

class CCustom1Dlg : public CAppWizStepDlg
{
// Construction
public:
	CCustom1Dlg();
	virtual BOOL OnDismiss() ;
	static int m_DataSource ;
	CBitmap bTVOnly, bTVandTxtVw, bfromFile, bfromKb, bNoSampletxt,*pSampletxtBMap, * pViewsBMap ;

	void ClearSampleTxtSettings() ;
	//{{AFX_DATA(CCustom1Dlg)
	enum { IDD = IDD_FEATURES };
	CStatic m_PicFrame;
	int     m_TextView;
	int     m_SampleDataSource;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustom1Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DrawBitmaps() ;
	// Generated message map functions
	//{{AFX_MSG(CCustom1Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnNodata();
	afx_msg void OnEditdata();
	afx_msg void OnReadfile();
	afx_msg void OnTextView();
	afx_msg void OnNoTextView();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#endif //  __CUSTMDLG1__
