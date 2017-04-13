#if !defined(AFX_DLGNOTE_H__336AB173_9104_11D1_82FF_00A0C91BC942__INCLUDED_)
#define AFX_DLGNOTE_H__336AB173_9104_11D1_82FF_00A0C91BC942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgNote.h : header file
//

class CMarkIt;

/////////////////////////////////////////////////////////////////////////////
// CDlgNote dialog

class CDlgNote : public CDialog
{
// Construction
public:
	CDlgNote(CWnd* pParent = NULL);   // standard constructor
	void SetMarkIt(CMarkIt *pMarkIt) { m_pMarkIt = pMarkIt; }


// Dialog Data
	//{{AFX_DATA(CDlgNote)
	enum { IDD = IDD_DIALOGNOTE };
	CString	m_strNote;
	CString	m_strLogFile;
	BOOL	m_fEcho;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNote)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMarkIt * m_pMarkIt;

	// Generated message map functions
	//{{AFX_MSG(CDlgNote)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonbrowse();
	virtual void OnOK();
	afx_msg void OnButtonDump();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNOTE_H__336AB173_9104_11D1_82FF_00A0C91BC942__INCLUDED_)
