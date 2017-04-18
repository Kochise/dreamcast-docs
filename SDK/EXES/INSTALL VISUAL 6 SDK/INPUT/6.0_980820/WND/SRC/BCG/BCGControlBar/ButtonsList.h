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

#if !defined(AFX_BUTTONSLIST_H__6656D214_C47F_11D1_A644_00A0C93A70EC__INCLUDED_)
#define AFX_BUTTONSLIST_H__6656D214_C47F_11D1_A644_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ButtonsList.h : header file
//

#ifndef BCG_NO_CUSTOMIZATION

class CBCGToolbarButton;
class CCustToolbarDlg;
class CBCGToolBarImages;

/////////////////////////////////////////////////////////////////////////////
// CButtonsList window

class CButtonsList : public CButton
{
// Construction
public:
	CButtonsList();

// Operations
public:
	void SetImages (CBCGToolBarImages* pImages);
	void AddButton (CBCGToolbarButton* pButton);
	void RemoveButtons ();

	CBCGToolbarButton* GetSelectedButton () const
	{
		return m_pSelButton;
	}

	BOOL SelectButton (int iImage);
	void EnableDragFromList (BOOL bEnable = TRUE)
	{
		m_bEnableDragFromList = bEnable;
	}

protected:
	CBCGToolbarButton* HitTest (POINT point) const;
	void SelectButton (CBCGToolbarButton* pButton);
	void RebuildLocations ();

// Attributes
protected:
	CObList				m_Buttons;			// CBCGToolbarButton list
	CBCGToolBarImages*	m_pImages;
	CSize				m_sizeButton;

	BOOL				m_bInited;

	CBCGToolbarButton*	m_pSelButton;

	int					m_iScrollOffset;
	int					m_iScrollTotal;
	int					m_iScrollPage;
	CScrollBar			m_wndScrollBar;
	BOOL				m_bEnableDragFromList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonsList)
	public:
	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	//}}AFX_VIRTUAL

	virtual void DrawItem (LPDRAWITEMSTRUCT lpDIS);

// Implementation
public:
	virtual ~CButtonsList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CButtonsList)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnSysColorChange();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif // BCG_NO_CUSTOMIZATION

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONSLIST_H__6656D214_C47F_11D1_A644_00A0C93A70EC__INCLUDED_)
