#if !defined(AFX_DLGADVANCED_H__A2CB0963_922F_11D1_8305_00A0C91BC942__INCLUDED_)
#define AFX_DLGADVANCED_H__A2CB0963_922F_11D1_8305_00A0C91BC942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAdvanced.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAdvanced dialog
class CBrkPnts;


class CDlgAdvanced : public CDialog
{
// Construction
public:
	CDlgAdvanced(CWnd* pParent = NULL);   // standard constructor
	void SetBrkPnts(CBrkPnts *pBrkPnts) {m_pBrkPnts = pBrkPnts;}

// Dialog Data
	//{{AFX_DATA(CDlgAdvanced)
	enum { IDD = IDD_DIALOGADVANCED };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAdvanced)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CBrkPnts * m_pBrkPnts;

	// Generated message map functions
	//{{AFX_MSG(CDlgAdvanced)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADVANCED_H__A2CB0963_922F_11D1_8305_00A0C91BC942__INCLUDED_)
