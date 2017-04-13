#ifndef __CONFIG_H__
#define __CONFIG_H__

// Config.h : header file
//

// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.

/////////////////////////////////////////////////////////////////////////////
// CConfigure dialog

class CConfigure : public CDialog
{
// Construction
public:
	CConfigure(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CConfigure)
	enum { IDD = IDD_CONFIGURATION };
	CButton m_StatusWarnErr;
	CStatic m_StatusText;
	CEdit   m_StatusLine;
	CEdit   m_SendTo;
	CStatic m_SendText;
	CButton m_SendMail;
	CButton m_SendGroup;
	CStatic m_FileName;
	CButton m_CloseWhenDone;
	CButton m_Browse;
	CButton m_BodyGroup;
	CEdit   m_BodyFileName;
	//}}AFX_DATA

	CString m_strSendTo;
	CString m_strStatusLine;
	CString m_strFileToSend;
	BOOL m_bSendFile;
	BOOL m_bIncBuildResults;
	BOOL m_bMailOnEach;
	BOOL m_bCloseWhenDone;
	BOOL m_bSendMail;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigure)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
	protected:
	// Generated message map functions
	//{{AFX_MSG(CConfigure)
	afx_msg void OnWorkspaces();
	afx_msg void OnBrowse();
	afx_msg void OnSendFileAsBody();
	afx_msg void OnBlankBody();
	afx_msg void OnSendMail();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __CONFIG_H__
