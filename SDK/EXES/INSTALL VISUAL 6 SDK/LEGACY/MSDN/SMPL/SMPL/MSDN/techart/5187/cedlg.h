//////////////////////////////////////////////////////////////////////////////
// CEDlg.h			- Copyright (C) 1997 Microsoft Corporation				//
//					- All rights reserved.									//
// Date				- 12/11/97												//
// Purpose			- Header for main dialog class							//
//////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CEDLG_H__0B2CE6F7_71A5_11D1_B887_00AA00C0803B__INCLUDED_)
#define AFX_CEDLG_H__0B2CE6F7_71A5_11D1_B887_00AA00C0803B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CRecordDlg;
class CCEDlg : public CDialog
{

public:

	CCEDlg(CWnd* pParent = NULL);	

// Dialog Data
	//{{AFX_DATA(CCEDlg)
	enum { IDD = IDD_CE_DIALOG };
	CListBox	m_Results;
	CButton	m_btnRemove;
	CButton	m_btnNew;
	CButton	m_btnEdit;
	CString	m_strData;
	CString	m_strResult;
	CString	m_strSearch;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCEDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL


protected:
	BOOL AddRecord(CRecordDlg& dlg);
	void RemoveRecord(CEOID oid);
	void DisplayTextData();
	void DisplayAllContaining(const CString& strSearch);

	HICON			m_hIcon;
	CCeDBDatabase	mDatabase;

	// Generated message map functions
	//{{AFX_MSG(CCEDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeSearch();
	afx_msg void OnSelchangeResultbox();
	afx_msg void OnNew();
	afx_msg void OnRemove();
	afx_msg void OnEdit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CEDLG_H__0B2CE6F7_71A5_11D1_B887_00AA00C0803B__INCLUDED_)
