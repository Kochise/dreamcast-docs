//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of BCGControlBar library.
// You may use, compile or redistribute it as part of your application 
// for free. You cannot redistribute it as a part of a software development 
// library without the agreement of the author. If the sources are 
// distributed along with the application, you should leave the original 
// copyright notes in the source code without any changes.
// This code can be used WITHOUT ANY WARRANTIES on your own risk.
// 
// For the latest updates to this library, check my site:
// http://welcome.to/bcgsoft
// 
// Stas Levin <bcgsoft@yahoo.com>
//*******************************************************************************

#if !defined(AFX_TOOLBARNAMEDLG_H__E52278EA_EB02_11D1_90D8_00A0C9B05590__INCLUDED_)
#define AFX_TOOLBARNAMEDLG_H__E52278EA_EB02_11D1_90D8_00A0C9B05590__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ToolbarNameDlg.h : header file
//

#include "bcgbarres.h"

/////////////////////////////////////////////////////////////////////////////
// CToolbarNameDlg dialog

class CToolbarNameDlg : public CDialog
{
// Construction
public:
	CToolbarNameDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CToolbarNameDlg)
	enum { IDD = IDD_BCGBARRES_TOOLBAR_NAME };
	CButton	m_btnOk;
	CString	m_strToolbarName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolbarNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CToolbarNameDlg)
	afx_msg void OnUpdateToolbarName();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBARNAMEDLG_H__E52278EA_EB02_11D1_90D8_00A0C9B05590__INCLUDED_)
