// MainFrm.h : interface of the CMFCMainFrame class
//
// This is a part of the Active Template Library.
// Copyright (C) 1996-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Active Template Library product.

#if !defined(AFX_MAINFRM_H__D1CF42D5_B039_11D0_B69F_00A0C903487A__INCLUDED_)
#define AFX_MAINFRM_H__D1CF42D5_B039_11D0_B69F_00A0C903487A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

///////////////////////////////////////////////////////////
//
// Includes and forward references.1
//
#include "tantype.h"
#include <afxtempl.h>

interface IATLTangramModel ;
interface IAtlTangramVisual ;
interface IAtlTangramWorld ;

class CMFCMainFrame : public CFrameWnd
{
public:
	CMFCMainFrame();

// Attributes
public:
	static CString s_strClassName ;

	// Interface pointer to World.
	IAtlTangramWorld* m_pWorld ;

	// Model List
	typedef CTypedPtrList< CPtrList, IATLTangramModel* > CModelList ;
	CModelList m_ModelList ;

	// Selection
	IAtlTangramVisual* m_pSelectedVisual ;
	TangramSize2d m_sizedDiff;

// Helper functions
public:
	// Used to register window class and create window.
	BOOL Create() ;

	// Initializes the components.
	BOOL Initialize(int cx, int cy);

	// Function for handling mouse button down messages.
	void DoButtonDown(UINT nWhichButton, CPoint point) ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMFCMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMFCMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__D1CF42D5_B039_11D0_B69F_00A0C903487A__INCLUDED_)
