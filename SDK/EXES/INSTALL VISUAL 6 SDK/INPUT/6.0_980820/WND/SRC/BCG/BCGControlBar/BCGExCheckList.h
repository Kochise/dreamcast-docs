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

#if !defined(AFX_BCGEXCHECKLIST_H__A2154114_301B_11D2_8BE6_00A0C9B05590__INCLUDED_)
#define AFX_BCGEXCHECKLIST_H__A2154114_301B_11D2_8BE6_00A0C9B05590__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BCGExCheckList.h : header file
//

#ifndef BCG_NO_CUSTOMIZATION

/////////////////////////////////////////////////////////////////////////////
// CBCGExCheckList window

class CBCGExCheckList : public CCheckListBox
{
// Construction
public:
	CBCGExCheckList();

// Attributes
protected:
	CArray<BOOL, BOOL>	m_arCheckData;

// Operations
public:
	void EnableCheck (int nIndex, BOOL bEnable = TRUE);
	BOOL IsCheckEnabled (int nIndex) const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGExCheckList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGExCheckList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGExCheckList)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	LRESULT OnLBAddString(WPARAM wParam, LPARAM lParam);
	LRESULT OnLBInsertString(WPARAM wParam, LPARAM lParam);
	LRESULT OnLBResetContent(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	void OnNewString (int iIndex);
};

#endif // BCG_NO_CUSTOMIZATION

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGEXCHECKLIST_H__A2154114_301B_11D2_8BE6_00A0C9B05590__INCLUDED_)
