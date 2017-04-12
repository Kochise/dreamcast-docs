/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// SelectCharDialog.h : header file
//

#if !defined(AFX_SELECTCHARDIALOG_H__23566FE1_4E19_11D3_BA02_000000000000__INCLUDED_)
#define AFX_SELECTCHARDIALOG_H__23566FE1_4E19_11D3_BA02_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSelectCharDialog dialog

class CSelectCharDialog : public CDialog
{
// Construction
public:
	CSelectCharDialog(int ch, CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CSelectCharDialog)
	enum { IDD = IDD_SELECTCHAR };
	CString	m_Char;
	int		m_iCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectCharDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CSelectCharDialog)
	afx_msg void OnRunprog();
	afx_msg void OnChangeLimitcharacter();
	afx_msg void OnChangeCharcode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTCHARDIALOG_H__23566FE1_4E19_11D3_BA02_000000000000__INCLUDED_)
