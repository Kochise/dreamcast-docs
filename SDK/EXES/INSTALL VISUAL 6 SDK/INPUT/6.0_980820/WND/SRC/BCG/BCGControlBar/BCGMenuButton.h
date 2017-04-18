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

#if !defined(AFX_BCGMENUBUTTON_H__49B675A4_C3E1_11D3_A722_009027900694__INCLUDED_)
#define AFX_BCGMENUBUTTON_H__49B675A4_C3E1_11D3_A722_009027900694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGMenuButton.h : header file
//

#include "BCGButton.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGMenuButton window

class BCGCONTROLBARDLLEXPORT CBCGMenuButton : public CBCGButton
{
	DECLARE_DYNAMIC(CBCGMenuButton)

	friend class CBCGPopupMenu;

// Construction
public:
	CBCGMenuButton();

// Attributes
public:
	BOOL	m_bRightArrow;
	HMENU	m_hMenu;
	int		m_nMenuResult;
	BOOL	m_bStayPressed;

protected:
	BOOL	m_bMenuIsActive;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGMenuButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGMenuButton();
	virtual CSize SizeToContent (BOOL bCalcOnly = FALSE);

protected:
	virtual void OnDraw (CDC* pDC, const CRect& rect, UINT uiState);
	virtual void OnShowMenu ();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGMenuButton)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg UINT OnGetDlgCode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGMENUBUTTON_H__49B675A4_C3E1_11D3_A722_009027900694__INCLUDED_)
