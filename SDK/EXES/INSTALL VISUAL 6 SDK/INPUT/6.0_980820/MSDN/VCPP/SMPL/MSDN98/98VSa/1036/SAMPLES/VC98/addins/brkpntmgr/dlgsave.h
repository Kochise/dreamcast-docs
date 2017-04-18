#if !defined(AFX_CDlgSave_H__C1AC211B_8ABF_11D1_B145_000000000000__INCLUDED_)
#define AFX_CDlgSave_H__C1AC211B_8ABF_11D1_B145_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CDlgSave.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSave dialog

class CBrkPnts;

#include "subdialog.h"

class CDlgSave : public CSubDialog
{
// Construction
public:
	void SetStats(BOOL fUpdate = FALSE);
	int m_cBrks;
	CDlgSave(CWnd* pParent = NULL);   // standard constructor
	void SetBrkPnts(CBrkPnts *pBrkPnts) {m_pBrkPnts = pBrkPnts;}
	~CDlgSave();
	BOOL Create(CWnd *pParent);

// Dialog Data
	//{{AFX_DATA(CDlgSave)
	enum { IDD = IDD_DLGSAVE };
	BOOL	m_fSaveOnlyEnabled;
	CString	m_strFile;
	BOOL	m_fOutputWnd;
	CString	m_strComment;
	BOOL	m_fOld;
	CString	m_strStats;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSave)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrkPnts * m_pBrkPnts;
	
	// Generated message map functions
	//{{AFX_MSG(CDlgSave)
	afx_msg void OnButtonbrowse();
	afx_msg void OnButtonload();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonclear();
	afx_msg void OnSave();
	afx_msg void OnOK();
	afx_msg void OnBtnoutputwnd();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDlgSave_H__C1AC211B_8ABF_11D1_B145_000000000000__INCLUDED_)
