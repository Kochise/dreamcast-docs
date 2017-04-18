#if !defined(AFX_DONTSHOWAGAINDLG_H__D2FB86B7_0872_408C_98FC_90202DFCD723__INCLUDED_)
#define AFX_DONTSHOWAGAINDLG_H__D2FB86B7_0872_408C_98FC_90202DFCD723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DontShowAgainDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDontShowAgainDlg dialog

class CDontShowAgainDlg : public CDialog
{
// Construction
public:
	CDontShowAgainDlg(
        LPCTSTR pszText, 
        BOOL& bShowIt,
        UINT nType = MB_OK | MB_ICONEXCLAMATION, 
        LPCTSTR pszDontAskText = NULL,
        LPCTSTR pszCaption = NULL);

// Dialog Data
	//{{AFX_DATA(CDontShowAgainDlg)
	enum { IDD = IDD_DONT_SHOW_AGAIN };
	CStatic	m_Icon;
	BOOL	m_bDontShowAgain;
	//}}AFX_DATA

    BOOL&   m_bShowIt;
    CString m_sText;
    int     m_nType;
    LPCTSTR m_pszDontShowText;
    LPCTSTR m_pszCaption;

	static int DoMessageBox(LPCTSTR lpszText, BOOL& bShowIt,
        UINT nType = MB_OK | MB_ICONEXCLAMATION,
        LPCTSTR pszDontShowAgainTxt = NULL);
	static int DoMessageBox(int idTextRes, BOOL& bShowIt,
        UINT nType = MB_OK | MB_ICONEXCLAMATION, 
        LPCTSTR pszDontShowAgainTxt = NULL);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDontShowAgainDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDontShowAgainDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDontShowAgain();
	afx_msg void OnYes();
	afx_msg void OnNo();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DONTSHOWAGAINDLG_H__D2FB86B7_0872_408C_98FC_90202DFCD723__INCLUDED_)
