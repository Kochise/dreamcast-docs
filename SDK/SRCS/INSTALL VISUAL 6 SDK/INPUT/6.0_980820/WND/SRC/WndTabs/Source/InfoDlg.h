/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// InfoDlg.h : header file
//

#if !defined(AFX_INFODLG_H__BE917126_5C03_11D3_BA1A_000000000000__INCLUDED_)
#define AFX_INFODLG_H__BE917126_5C03_11D3_BA1A_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInfoDlg dialog

class CInfoDlg : public CDialog
{
// Construction
public:
	CInfoDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInfoDlg)
	enum { IDD = IDD_INFO };
	CHyperLink	m_VALink;
	CHyperLink	m_WWhizLink;
	CHyperLink	m_SHLink;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInfoDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void SetVerText(LPCTSTR pName, int nID);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFODLG_H__BE917126_5C03_11D3_BA1A_000000000000__INCLUDED_)
