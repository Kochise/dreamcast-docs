#if !defined(AFX_DLGFILE_H__7900AD64_A65E_11D1_8316_00A0C91BC942__INCLUDED_)
#define AFX_DLGFILE_H__7900AD64_A65E_11D1_8316_00A0C91BC942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFile dialog

class CDlgFile : public CDialog
{
// Construction
public:
	void SetFile(LPCTSTR szFile);
	CString& GetFile();
	CDlgFile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFile)
	enum { IDD = IDD_DIALOGFILE };
	CEdit	m_ctlEditFile;
	CString	m_strFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFile)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFile)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonbrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFILE_H__7900AD64_A65E_11D1_8316_00A0C91BC942__INCLUDED_)
