#ifndef __WORKSPCS_H__
#define __WORKSPCS_H__

// Workspcs.h : header file
//

// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.

/////////////////////////////////////////////////////////////////////////////
// CWorkspaces dialog

class CWorkspaces : public CDialog
{
// Construction
public:
	CWorkspaces(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWorkspaces)
	enum { IDD = IDD_WORKSPACES };
	CListCtrl   m_WorkspaceList;
	CButton m_Remove;
	CButton m_Add;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWorkspaces)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList m_ImageList;

	// Generated message map functions
	//{{AFX_MSG(CWorkspaces)
	afx_msg void OnRemove();
	afx_msg void OnAddWorkspace();
	afx_msg void OnMoveDown();
	afx_msg void OnMoveUp();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __WORKSPCS_H__
