// MFCTangramConfigDlg.h: Declaration of CMFCTangramConfigDlg
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#if !defined(AFX_MFCTANGRAMCONFIGDLG_H__D1CF42E1_B039_11D0_B69F_00A0C903487A__INCLUDED_)
#define AFX_MFCTANGRAMCONFIGDLG_H__D1CF42E1_B039_11D0_B69F_00A0C903487A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MFCTangramConfigDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMFCTangramConfigDlg dialog

class CMFCTangramConfigDlg : public CDialog
{
// Construction
public:
	CMFCTangramConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMFCTangramConfigDlg)
	enum { IDD = IDD_CONFIG_DIALOG };
	CListBox    m_listWorld;
	BOOL    m_bLocalModel;
	//}}AFX_DATA

	CLSID m_clsid ;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCTangramConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMFCTangramConfigDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCTANGRAMCONFIGDLG_H__D1CF42E1_B039_11D0_B69F_00A0C903487A__INCLUDED_)
