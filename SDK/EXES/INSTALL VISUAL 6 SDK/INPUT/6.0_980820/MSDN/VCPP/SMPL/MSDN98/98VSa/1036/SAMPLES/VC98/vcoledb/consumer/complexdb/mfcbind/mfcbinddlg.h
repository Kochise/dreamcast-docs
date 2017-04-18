// MFCBindDlg.h : header file
//

#if !defined(AFX_MFCBINDDLG_H__CBD34999_B780_11D1_9580_0060088F4223__INCLUDED_)
#define AFX_MFCBINDDLG_H__CBD34999_B780_11D1_9580_0060088F4223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMFCBindDlg dialog

class CMFCBindDlg : public CDialog
{
// Construction
public:
	CMFCBindDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
	//{{AFX_DATA(CMFCBindDlg)
	enum { IDD = IDD_MFCBIND_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCBindDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFCBindDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCBINDDLG_H__CBD34999_B780_11D1_9580_0060088F4223__INCLUDED_)
