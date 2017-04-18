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

#if !defined(AFX_KEYBOARDPAGE_H__283E6042_54C6_11D2_B110_D085EB8D1B3C__INCLUDED_)
#define AFX_KEYBOARDPAGE_H__283E6042_54C6_11D2_B110_D085EB8D1B3C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// KeyboardPage.h : header file
//

#ifndef BCG_NO_CUSTOMIZATION

#include "bcgbarres.h"
#include "KeyAssign.h"

class CBCGToolbarButton;

/////////////////////////////////////////////////////////////////////////////
// CBCGKeyboardPage dialog

class CBCGKeyboardPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CBCGKeyboardPage)

// Construction
public:
	CBCGKeyboardPage(CFrameWnd* pParentFrame = NULL, BOOL bAutoSet = FALSE);
	~CBCGKeyboardPage();

// Dialog Data
	//{{AFX_DATA(CBCGKeyboardPage)
	enum { IDD = IDD_BCGBARRES_PROPPAGE5 };
	CStatic	m_wndAssignedToTitle;
	CKeyAssign	m_wndNewKey;
	CComboBox	m_wndViewTypeList;
	CStatic	m_wndViewIcon;
	CButton	m_wndRemoveButton;
	CListBox	m_wndCurrentKeysList;
	CListBox	m_wndCommandsList;
	CComboBox	m_wndCategoryList;
	CButton	m_wndAssignButton;
	CString	m_strDesrcription;
	CString	m_strAssignedTo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBCGKeyboardPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CBCGKeyboardPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnAssign();
	afx_msg void OnSelchangeCategory();
	afx_msg void OnSelchangeCommandsList();
	afx_msg void OnSelchangeCurrentKeysList();
	afx_msg void OnRemove();
	afx_msg void OnResetAll();
	afx_msg void OnSelchangeViewType();
	afx_msg void OnUpdateNewShortcutKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Operations:
protected:
	void AddKeyEntry (LPACCEL pEntry);

// Attributes:
protected:
	HACCEL				m_hAccelTable;
	LPACCEL				m_lpAccel;
	int					m_nAccelSize;
	CMultiDocTemplate*	m_pSelTemplate;
	CBCGToolbarButton*	m_pSelButton;
	LPACCEL				m_pSelEntry;
	CFrameWnd*			m_pParentFrame;
	BOOL				m_bAutoSet;
};

#endif // BCG_NO_CUSTOMIZATION

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYBOARDPAGE_H__283E6042_54C6_11D2_B110_D085EB8D1B3C__INCLUDED_)
