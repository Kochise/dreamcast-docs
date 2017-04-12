/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

#if !defined(AFX_CUSTOMIZECTXMENUDLG_H__5E304741_62CD_4C67_814F_EA300C9E8EFF__INCLUDED_)
#define AFX_CUSTOMIZECTXMENUDLG_H__5E304741_62CD_4C67_814F_EA300C9E8EFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomizeCtxMenuDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomizeCtxMenuDlg dialog

class CCustomizeCtxMenuDlg : public CHHDialog
{
// Construction
public:
	CCustomizeCtxMenuDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCustomizeCtxMenuDlg)
	enum { IDD = IDD_CTX_MENU_GROUPS };
	int		m_MenuClip;
	int		m_MenuDS;
	int		m_MenuFM;
	int		m_MenuWM;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomizeCtxMenuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCustomizeCtxMenuDlg)
	afx_msg void OnResetMenus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    DECLARE_HELP_IDS()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMIZECTXMENUDLG_H__5E304741_62CD_4C67_814F_EA300C9E8EFF__INCLUDED_)
