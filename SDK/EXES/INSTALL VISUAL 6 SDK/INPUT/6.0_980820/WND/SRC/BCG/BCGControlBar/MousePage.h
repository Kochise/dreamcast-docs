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

#if !defined(AFX_MOUSEPAGE_H__0A141F64_E9CA_11D1_90D2_00A0C9B05590__INCLUDED_)
#define AFX_MOUSEPAGE_H__0A141F64_E9CA_11D1_90D2_00A0C9B05590__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MousePage.h : header file
//

#ifndef BCG_NO_CUSTOMIZATION

#include "bcgbarres.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGMousePage dialog

class CBCGMousePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CBCGMousePage)

// Construction
public:
	CBCGMousePage();
	~CBCGMousePage();

// Operations:
protected:
	void EnableDblClickControls (BOOL bEnable = TRUE);
	BOOL SelectCommand (UINT uiCmd);

// Attributes:
protected:
	int									m_iCurrViewId;
	CImageList							m_ViewsImages;

// Dialog Data
	//{{AFX_DATA(CBCGMousePage)
	enum { IDD = IDD_BCGBARRES_PROPPAGE4 };
	CListCtrl	m_wndListOfViews;
	CListBox	m_wndListOfCommands;
	CStatic	m_wndCommandDescription;
	CString	m_strCommandDescription;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CBCGMousePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CBCGMousePage)
	afx_msg void OnNoDblcliick();
	afx_msg void OnUseDblcliick();
	afx_msg void OnSelchangeListOfCommands();
	afx_msg void OnItemchangedListViews(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // BCG_NO_CUSTOMIZATION

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSEPAGE_H__0A141F64_E9CA_11D1_90D2_00A0C9B05590__INCLUDED_)
