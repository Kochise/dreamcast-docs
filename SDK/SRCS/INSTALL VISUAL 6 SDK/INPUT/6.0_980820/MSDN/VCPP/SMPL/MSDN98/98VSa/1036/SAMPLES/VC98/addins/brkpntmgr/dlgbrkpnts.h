#if !defined(AFX_DLGBRKPNTS_H__C1AC211A_8ABF_11D1_B145_000000000000__INCLUDED_)
#define AFX_DLGBRKPNTS_H__C1AC211A_8ABF_11D1_B145_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBrkPnts.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBrkPnts dialog

class CBrkPnts;

class CDlgBrkPnts : public CDialog
{
// Construction
public:
	void UpdateInfo();
	CBrkPnts * m_pBrkPnts;
	int m_cBrks;
	CDlgBrkPnts(CWnd* pParent = NULL);   // standard constructor
	void SetBrkPnts(CBrkPnts *pBrkPnts) {m_pBrkPnts = pBrkPnts;}

// Dialog Data
	//{{AFX_DATA(CDlgBrkPnts)
	enum { IDD = IDD_DLGBRKPNT };
	CEdit	m_ctlEditComment;
	CStatic	m_ctlCount;
	BOOL	m_fSaveOnlyEnabled;
	CString	m_strFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBrkPnts)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgBrkPnts)
	afx_msg void OnButtonbrowse();
	afx_msg void OnButtonload();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonclear();
	afx_msg void OnOutput();
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBRKPNTS_H__C1AC211A_8ABF_11D1_B145_000000000000__INCLUDED_)
