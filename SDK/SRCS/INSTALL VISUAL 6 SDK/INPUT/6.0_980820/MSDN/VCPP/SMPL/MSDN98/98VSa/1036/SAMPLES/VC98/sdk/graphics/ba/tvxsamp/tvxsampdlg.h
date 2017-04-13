// TVXSampDlg.h : TV Viewer sample application
//
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Broadcast Architecture Programmer's Reference.
// For detailed information regarding Broadcast
// Architecture, see the reference.
//
//
//


#if !defined(AFX_TVXSAMPDLG_H__FF521029_0CE4_11D1_98AE_080009DC95C5__INCLUDED_)
#define AFX_TVXSAMPDLG_H__FF521029_0CE4_11D1_98AE_080009DC95C5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTVXSampDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CTVXSampDlg dialog

class CTVXSampDlg : public CDialog
{
	DECLARE_DYNAMIC(CTVXSampDlg);
	friend class CTVXSampDlgAutoProxy;

// Construction
public:
	CTVXSampDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CTVXSampDlg();

// Dialog Data
	//{{AFX_DATA(CTVXSampDlg)
	enum { IDD = IDD_TVXSAMP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTVXSampDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CTVXSampDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	//{{AFX_MSG(CTVXSampDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	afx_msg void OnSetReminder();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TVXSAMPDLG_H__FF521029_0CE4_11D1_98AE_080009DC95C5__INCLUDED_)
