/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

// TabActivationShortcutsDlg.h : header file
//

#if !defined(AFX_TABACTIVATIONSHORTCUTSDLG_H__DE9BD3BD_BC8A_4595_B0C4_40C569DBD6D2__INCLUDED_)
#define AFX_TABACTIVATIONSHORTCUTSDLG_H__DE9BD3BD_BC8A_4595_B0C4_40C569DBD6D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ShortcutsDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CTabActivationShortcutsDlg dialog

class CTabActivationShortcutsDlg : public CHHDialog, CShortcutsBase
{
// Construction
public:
	CTabActivationShortcutsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTabActivationShortcutsDlg)
	enum { IDD = IDD_SHORTCUTS_TABS };
	BOOL	m_bGotoAlt;
	BOOL	m_bGotoControl;
	BOOL	m_bGotoShift;
	int		m_GotoKey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabActivationShortcutsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabActivationShortcutsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnGenerateShortcuts();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABACTIVATIONSHORTCUTSDLG_H__DE9BD3BD_BC8A_4595_B0C4_40C569DBD6D2__INCLUDED_)
