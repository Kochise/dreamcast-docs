// Based On Code From CVSIn by Jerzy Kaczorowski (www.cvsin.org) 

// ToolbarSetup.h : header file
//

#if !defined(AFX_TOOLBARSETUP_H__35CE8803_5F7F_11D4_95B0_00A04B093AA3__INCLUDED_)
#define AFX_TOOLBARSETUP_H__35CE8803_5F7F_11D4_95B0_00A04B093AA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CToolbarSetup dialog

class CToolbarSetup : public CHHDialog
{
	// Construction
public:
	CToolbarSetup(CWnd* pParent = NULL);   // standard constructor
	
	// Dialog Data
	//{{AFX_DATA(CToolbarSetup)
	enum { IDD = IDD_TOOLBAR_SETUP };
	CCheckListBox	m_CommandsListBox;
	CString	m_strDescription;
	//}}AFX_DATA
	
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolbarSetup)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CToolbarSetup)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListCommands();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
	DECLARE_HELP_IDS();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBARSETUP_H__35CE8803_5F7F_11D4_95B0_00A04B093AA3__INCLUDED_)
