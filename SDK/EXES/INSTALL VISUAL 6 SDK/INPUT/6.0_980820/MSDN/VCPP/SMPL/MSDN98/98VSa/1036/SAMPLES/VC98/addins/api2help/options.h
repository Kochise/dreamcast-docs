#ifndef __OPTIONS_H__
#define __OPTIONS_H__

// Options.h : header file
//

// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.


/////////////////////////////////////////////////////////////////////////////
// COptions dialog

class COptions : public CDialog
{
// Construction
public:
	COptions(CString SelectedAPI, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptions)
	enum { IDD = IDD_OPTIONS };
	CEdit   m_TopicID;
	CEdit   m_TopicName;
	CStatic m_Static4;
	CStatic m_Static3;
	CStatic m_Static2;
	CStatic m_Static1;
	CEdit   m_RTFFileName;
	CButton m_RTF;
	CEdit   m_HTMLFileName;
	CButton m_HTML;
	CButton m_BrowseRTF;
	CButton m_BrowseHTML;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strPrototype;

	// Generated message map functions
	//{{AFX_MSG(COptions)
	afx_msg void OnHTML();
	afx_msg void OnRTF();
	afx_msg void OnBrowseHTML();
	afx_msg void OnBrowseRTF();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __OPTIONS_H__
