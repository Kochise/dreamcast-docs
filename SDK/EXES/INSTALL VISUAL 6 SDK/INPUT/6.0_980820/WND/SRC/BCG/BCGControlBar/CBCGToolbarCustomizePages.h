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

// CBCGToolbarCustomizePages.h : header file
//

#ifndef __CBCGTOOLBARCUSTOMIZEPAGES_H__
#define __CBCGTOOLBARCUSTOMIZEPAGES_H__

#ifndef BCG_NO_CUSTOMIZATION

#include "ButtonsList.h"
#include "ButtonsTextList.h"
#include "bcgbarres.h"

#ifndef __AFXTEMPL_H__
	#include "afxtempl.h"
#endif

#include "BCGExCheckList.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGCustomizePage dialog

class CBCGToolbarButton;
class CBCGToolBarImages;
class CBCGToolBar;

class CBCGCustomizePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CBCGCustomizePage)

// Construction
public:
	CBCGCustomizePage();
	~CBCGCustomizePage();

// Operations:
	void SetUserCategory (LPCTSTR lpszCategory);
	void SetAllCategory (LPCTSTR lpszCategory);
	void OnChangeSelButton (CBCGToolbarButton* pButton);

protected:

// Dialog Data
	//{{AFX_DATA(CBCGCustomizePage)
	enum { IDD = IDD_BCGBARRES_PROPPAGE1 };
	CListBox	m_wndCategory;
	CButtonsTextList	m_wndTools;
	CString	m_strButtonDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBCGCustomizePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CBCGCustomizePage)
	afx_msg void OnSelchangeUserTools();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCategory();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Attributes:
protected:

	CBCGToolbarButton*	m_pSelButton;
	CString				m_strUserCategory;
	CString				m_strAllCategory;
};

/////////////////////////////////////////////////////////////////////////////
// CBCGToolbarsPage dialog

class CBCGToolbarsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CBCGToolbarsPage)

// Construction
public:
	CBCGToolbarsPage(CFrameWnd* pParentFrame = NULL);
	~CBCGToolbarsPage();

// Dialog Data
	//{{AFX_DATA(CBCGToolbarsPage)
	enum { IDD = IDD_BCGBARRES_PROPPAGE2 };
	CButton	m_wndTextLabels;
	CButton	m_bntRenameToolbar;
	CButton	m_btnNewToolbar;
	CButton	m_btnDelete;
	CButton	m_btnReset;
	CBCGExCheckList	m_wndToobarList;
	BOOL	m_bTextLabels;
	//}}AFX_DATA

// Operations:
public:
	void ShowToolBar (CBCGToolBar* pToolBar, BOOL bShow);
	void EnableUserDefinedToolbars (BOOL bEnable)
	{
		m_bUserDefinedToolbars = bEnable;
	}

protected:
// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBCGToolbarsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CBCGToolbarsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeToolbarList();
	afx_msg void OnDblclkToolbarList();
	afx_msg void OnReset();
	afx_msg void OnResetAll();
	afx_msg void OnDeleteToolbar();
	afx_msg void OnNewToolbar();
	afx_msg void OnRenameToolbar();
	afx_msg void OnBcgbarresTextLabels();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CBCGToolBar*	m_pSelectedToolbar;
	BOOL			m_bUserDefinedToolbars;
	CFrameWnd*		m_pParentFrame;
};

#endif // BCG_NO_CUSTOMIZATION

#endif // __CBCGTOOLBARCUSTOMIZEPAGES_H__
