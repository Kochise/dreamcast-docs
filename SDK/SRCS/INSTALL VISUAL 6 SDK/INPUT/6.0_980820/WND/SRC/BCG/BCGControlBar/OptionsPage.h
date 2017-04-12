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

#if !defined(AFX_OPTIONSPAGE_H__B7BDB592_32E1_11D3_A724_0090274409AC__INCLUDED_)
#define AFX_OPTIONSPAGE_H__B7BDB592_32E1_11D3_A724_0090274409AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionsPage.h : header file
//

#ifndef BCG_NO_CUSTOMIZATION

/////////////////////////////////////////////////////////////////////////////
// CBCGOptionsPage dialog

class CBCGOptionsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CBCGOptionsPage)

// Construction
public:
	CBCGOptionsPage(BOOL bIsMenuBarExist = FALSE);
	~CBCGOptionsPage();

// Dialog Data
	//{{AFX_DATA(CBCGOptionsPage)
	enum { IDD = IDD_BCGBARRES_PROPPAGE6 };
	CButton	m_wndLook2000;
	CButton	m_wndLargeIcons;
	CButton	m_wndRUMenus;
	CButton	m_wndResetUsageBtn;
	CStatic	m_wndRuMenusLine;
	CStatic	m_wndRuMenusTitle;
	CButton	m_wndShowAllMenusDelay;
	CButton	m_wndShowShortcutKeys;
	BOOL	m_bShowTooltips;
	BOOL	m_bShowShortcutKeys;
	BOOL	m_bRecentlyUsedMenus;
	BOOL	m_bShowAllMenusDelay;
	BOOL	m_bLargeIcons;
	BOOL	m_bLook2000;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBCGOptionsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CBCGOptionsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OShowTooltipsWithKeys();
	afx_msg void OnShowTooltips();
	afx_msg void OnResetUsageData();
	afx_msg void OnShowRecentlyUsedMenus();
	afx_msg void OnShowMenusDelay();
	afx_msg void OnLargeIcons();
	afx_msg void OnBcgbarresLook2000();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Attributes:
protected:
	BOOL m_bIsMenuBarExist;
};

#endif // BCG_NO_CUSTOMIZATION

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSPAGE_H__B7BDB592_32E1_11D3_A724_0090274409AC__INCLUDED_)
