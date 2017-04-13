//
// VdMFCDlg.h: Defines the CVdMFCDlg class, which defines the
//             behavior of the application's main dialog. 
//
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Broadcast Architecture Programmer's Reference.
// For detailed information regarding Broadcast
// Architecture, see the reference.
//
//{{AFX_INCLUDES()
#include "bpcvid.h"
#include "bpcbase.h"
#include "bpcdev.h"
#include "vidtypes.h"
//}}AFX_INCLUDES

#if !defined(AFX_VDMFCDLG_H__4E088A08_0E75_11D1_A073_00A0C9054174__INCLUDED_)
#define AFX_VDMFCDLG_H__4E088A08_0E75_11D1_A073_00A0C9054174__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CVdMFCDlg dialog

class CVdMFCDlg : public CDialog
{
// Construction
public:
	CVdMFCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CVdMFCDlg)
	enum { IDD = IDD_VDMFC_DIALOG };
	CBPCVid	m_CVid;
	long	m_channel;
	CString	m_filename;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVdMFCDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CListBox box;
	CBPCDeviceBase m_id;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CVdMFCDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSetChannel();
	afx_msg void OnPause();
	afx_msg void OnVideoOn();
	afx_msg void OnStop();
	afx_msg void OnSetInput();
	afx_msg void OnSetOutput();
	afx_msg void OnPlay();
	afx_msg void OnSetFile();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	IBPCDeviceBase* m_pDeviceBase;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VDMFCDLG_H__4E088A08_0E75_11D1_A073_00A0C9054174__INCLUDED_)
