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

#if !defined(AFX_BCGMDICHILDWND_H__3BE44BE6_C83D_11D3_A723_009027900694__INCLUDED_)
#define AFX_BCGMDICHILDWND_H__3BE44BE6_C83D_11D3_A723_009027900694__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGMDIChildWnd.h : header file
//

#include "bcgcontrolbar.h"

class CBCGMDIFrameWnd;

/////////////////////////////////////////////////////////////////////////////
// CBCGMDIChildWnd frame

class BCGCONTROLBARDLLEXPORT CBCGMDIChildWnd : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CBCGMDIChildWnd)
protected:
	CBCGMDIChildWnd();           // protected constructor used by dynamic creation

// Attributes
protected:
	CBCGMDIFrameWnd*	m_pMDIFrame;

// Operations
public:
	void DockControlBarLeftOf(CControlBar* pBar, CControlBar* pLeftOf);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGMDIChildWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CBCGMDIChildWnd();

	// Generated message map functions
	//{{AFX_MSG(CBCGMDIChildWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGMDICHILDWND_H__3BE44BE6_C83D_11D3_A723_009027900694__INCLUDED_)
