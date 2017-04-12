/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


#if !defined(AFX_HKWARNINGDLG_H__994AF345_15F0_11D3_B9A5_D44F49000000__INCLUDED_)
#define AFX_HKWARNINGDLG_H__994AF345_15F0_11D3_B9A5_D44F49000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HKWarningDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHKWarningDlg dialog

class CHKWarningDlg : public CDialog
{
// Construction
public:
	CHKWarningDlg(CString cKeyComb, CString cKeys, CString cCommands, 
        CString cEditors, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHKWarningDlg)
	enum { IDD = IDD_HOTKEY_WARNING };
	CListCtrl	m_ListCtrl;
	CString	m_sHotKey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHKWarningDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void AddRow(LPCTSTR cKey, LPCTSTR cCommand, LPCTSTR cEditor);

	// Generated message map functions
	//{{AFX_MSG(CHKWarningDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    CString m_cKeyComb;
    CString m_cKeys;
    CString m_cCommands;
    CString m_cEditors;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HKWARNINGDLG_H__994AF345_15F0_11D3_B9A5_D44F49000000__INCLUDED_)
