// msdevcmdDlg.h : header file
//

#if !defined(AFX_MSDEVCMDDLG_H__B772028D_B6B0_11D1_8320_00A0C91BC942__INCLUDED_)
#define AFX_MSDEVCMDDLG_H__B772028D_B6B0_11D1_8320_00A0C91BC942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CmdEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CMsdevcmdDlg dialog

class CMsdevcmdDlg : public CDialog
{
// Construction
public:
	CMsdevcmdDlg(CWnd* pParent = NULL);	// standard constructor
	~CMsdevcmdDlg();
	void Pin(BOOL fPin, BOOL fShow = TRUE);

// Dialog Data
	//{{AFX_DATA(CMsdevcmdDlg)
	enum { IDD = IDD_MSDEVCMD_DIALOG };
	CButton	m_ctlBtnPinned;
	CCmdEdit	m_ctlEditCmd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsdevcmdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBitmap m_bmNotPinned;
	CBitmap m_bmPinned;
	BOOL m_fTopMost;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMsdevcmdDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnPin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSDEVCMDDLG_H__B772028D_B6B0_11D1_8320_00A0C91BC942__INCLUDED_)
