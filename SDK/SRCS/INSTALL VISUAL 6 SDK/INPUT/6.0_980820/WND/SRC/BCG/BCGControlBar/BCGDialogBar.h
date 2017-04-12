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

#if !defined(AFX_BCGDIALOGBAR_H__F8388FA1_30D5_11D3_95C5_00A0C9289F1B__INCLUDED_)
#define AFX_BCGDIALOGBAR_H__F8388FA1_30D5_11D3_95C5_00A0C9289F1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGDialogBar.h : header file
//

#ifndef BCG_NO_SIZINGBAR

#include "bcgcontrolbar.h"
#include "BCGSizingControlBar.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGDialogBar window

class BCGCONTROLBARDLLEXPORT CBCGDialogBar : public CBCGSizingControlBar
{
	DECLARE_SERIAL(CBCGDialogBar)

// Construction
public:
	CBCGDialogBar();

	BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd, BOOL bHasGripper,
			LPCTSTR lpszTemplateName, UINT nStyle, UINT nID);
	BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd, BOOL bHasGripper,
			UINT nIDTemplate, UINT nStyle, UINT nID);

	BOOL Create(CWnd* pParentWnd, LPCTSTR lpszTemplateName,
			UINT nStyle, UINT nID)
	{
		return Create (_T(""), pParentWnd, TRUE /* bHasGripper */,
			lpszTemplateName, nStyle, nID);
	}

	BOOL Create(CWnd* pParentWnd, UINT nIDTemplate,
			UINT nStyle, UINT nID)
	{
		return Create (_T(""), pParentWnd, TRUE /* bHasGripper */,
			nIDTemplate, nStyle, nID);
	}

// Attributes
protected:
	CSize m_sizeDefault;
	BOOL m_bAllowSizing;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGDialogBar)
	//}}AFX_VIRTUAL

    virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
    virtual CSize CalcDynamicLayout(int nLength, DWORD dwMode);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual BOOL ClipPaint () const	{	return FALSE;	}

// Implementation
#ifndef _AFX_NO_OCC_SUPPORT
	// data and functions necessary for OLE control containment
	_AFX_OCC_DIALOG_INFO* m_pOccDialogInfo;
	LPCTSTR m_lpszTemplateName;
	virtual BOOL SetOccDialogInfo(_AFX_OCC_DIALOG_INFO* pOccDialogInfo);

	//{{AFX_MSG(CBCGDialogBar)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg LRESULT HandleInitDialog(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
#endif

public:
	virtual ~CBCGDialogBar();
};

#endif // BCG_NO_SIZINGBAR

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGDIALOGBAR_H__F8388FA1_30D5_11D3_95C5_00A0C9289F1B__INCLUDED_)
