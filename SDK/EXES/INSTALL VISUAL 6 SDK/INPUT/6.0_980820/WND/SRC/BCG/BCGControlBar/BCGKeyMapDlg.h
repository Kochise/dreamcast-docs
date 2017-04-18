//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of BCGControlBar library.
// You may use, compile or redistribute it as part of your application 
// for free. You cannot redistribute it as a part of a software development 
// library without the agreement of the author. If the sources are 
// distributed along with the application, you should leave the original 
// copyright notes in the source code without any changes.
// This code can be used WITHOUT ANY WARRANTIES on your own risk.
// 
// For the latest updates to this library, check my site:
// http://welcome.to/bcgsoft
// 
// Stas Levin <bcgsoft@yahoo.com>
//*******************************************************************************

// Created by Herbert Griebel

#if !defined(AFX_BCGKEYMAPDLG_H__BD41B8C2_5025_11D4_9A06_E906E7563969__INCLUDED_)
#define AFX_BCGKEYMAPDLG_H__BD41B8C2_5025_11D4_9A06_E906E7563969__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGKeyMapDlg.h : header file
//

#ifndef BCG_NO_CUSTOMIZATION

#include "bcgcontrolbar.h"
#include "bcgbarres.h"
#include "BCGButton.h"

class CBCGToolbarCustomize;

/////////////////////////////////////////////////////////////////////////////
// CBCGKeyMapDlg dialog

class BCGCONTROLBARDLLEXPORT CBCGKeyMapDlg : public CDialog
{
// Construction
public:
	CBCGKeyMapDlg(CFrameWnd* pWndParentFrame,
				BOOL bEnablePrint = FALSE);   // standard constructor
	~CBCGKeyMapDlg();

// Dialog Data
	//{{AFX_DATA(CBCGKeyMapDlg)
	enum { IDD = IDD_BCGBARRES_KEYMAP };
	CStatic	m_wndAccelLabel;
	CListCtrl	m_KeymapList;
	CComboBox	m_wndCategoryList;
	CStatic		m_wndViewIcon;
	CComboBox	m_wndViewTypeList;
	CBCGButton	m_ButtonPrint;
	CBCGButton	m_ButtonCopy;
	//}}AFX_DATA

	CFrameWnd*				m_pWndParentFrame;
	HACCEL					m_hAccelTable;
	LPACCEL					m_lpAccel;
	int						m_nAccelSize;
	CBCGToolbarCustomize*	m_pDlgCust;
	int						m_nSortedCol;
	BOOL					m_bSortAscending;
	const BOOL				m_bEnablePrint;
	HINSTANCE				m_hInstDefault;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGKeyMapDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

	virtual void CopyKeyMap ();
	virtual void PrintKeyMap ();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBCGKeyMapDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeViewType();
	afx_msg void OnSelchangeCategory();
	afx_msg void OnCopy();
	afx_msg void OnPrint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void SetColumnsWidth ();
};

#endif // BCG_NO_CUSTOMIZATION

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGKEYMAPDLG_H__BD41B8C2_5025_11D4_9A06_E906E7563969__INCLUDED_)
