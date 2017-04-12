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

// Created by Rui Godinho Lopes <ruiglopes@yahoo.com>
//
//////////////////////////////////////////////////////////////////////

#ifndef BCG_NO_DIALOG

//********************************************************************
//
// BCGDialog.h : header file
//
// REVISION HISTORY
// ----------------
// 0.00 31june2000 - Rui Godinho Lopes <ruiglopes@yahoo.com>
//   creation
//
//********************************************************************

#if !defined(AFX_BCGDIALOG_H__09800B11_4F60_11D4_AB0C_000000000000__INCLUDED_)
#define AFX_BCGDIALOG_H__09800B11_4F60_11D4_AB0C_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "bcgcontrolbar.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGDialog dialog

class BCGCONTROLBARDLLEXPORT CBCGDialog : public CDialog
{
	friend class CBCGPopupMenu;

	DECLARE_DYNAMIC(CBCGDialog)

// Construction
public:
	CBCGDialog();
	CBCGDialog(UINT nIDTemplate, CWnd *pParent= NULL);
	CBCGDialog(LPCTSTR lpszTemplateName, CWnd *pParentWnd= NULL);

protected:
	void CommonConstruct ();

// Attributes:
public:
	enum BackgroundLocation
	{
		BACKGR_TILE,
		BACKGR_TOPLEFT,
		BACKGR_TOPRIGHT,
		BACKGR_BOTTOMLEFT,
		BACKGR_BOTTOMRIGHT,
	};

protected:
	HBITMAP				m_hBkgrBitmap;
	CSize				m_sizeBkgrBitmap;
	CBrush				m_brBkgr;
	BackgroundLocation	m_BkgrLocation;
	BOOL				m_bAutoDestroyBmp;

// Operations:
public:
	void SetBackgroundColor (COLORREF color, BOOL bRepaint = TRUE);
	void SetBackgroundImage (HBITMAP hBitmap, 
							BackgroundLocation location = BACKGR_TILE,
							BOOL bAutoDestroy = TRUE,
							BOOL bRepaint = TRUE);
	BOOL SetBackgroundImage (UINT uiBmpResId,
							BackgroundLocation location = BACKGR_TILE,
							BOOL bRepaint = TRUE);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	//{{AFX_MSG(CBCGDialog)
	afx_msg void OnActivate(UINT nState, CWnd *pWndOther, BOOL bMinimized);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	BOOL ProcessMouseClick (POINT pt);
	BOOL ProcessMouseMove (POINT pt);
	void SetActiveMenu (CBCGPopupMenu* pMenu);
};

#endif // BCG_NO_DIALOG

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGDIALOG_H__09800B11_4F60_11D4_AB0C_000000000000__INCLUDED_)
