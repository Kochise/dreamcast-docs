#if !defined(AFX_REPLACEDLG_H__14334320_B34A_11D0_A217_244106C10000__INCLUDED_)
#define AFX_REPLACEDLG_H__14334320_B34A_11D0_A217_244106C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// ReplaceDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReplaceDlg dialog

class CReplaceDlg : public CDialog
{
// Construction
public:
	bool m_bMatchCase;
	bool m_bRegularExpression;
	bool m_bMatchWholeWord;
	long m_lEmulation;
	CString m_strFindString;
	CString m_strReplaceString;
	CReplaceDlg(CWnd* pParent = NULL);   // standard constructor
	void CommandQuotedString(WPARAM, LPARAM);
	void CommandAnyChar(WPARAM, LPARAM);
	void CommandInRange(WPARAM, LPARAM);
	void CommandNotInRange(WPARAM, LPARAM);
	void CommandBeginOL(WPARAM, LPARAM);
	void CommandEOL(WPARAM, LPARAM);
	void CommandTaggedExp(WPARAM, LPARAM);
	void CommandNot(WPARAM, LPARAM);
	void CommandOr(WPARAM, LPARAM);
	void Command0OrMore(WPARAM, LPARAM);
	void Command1OrMore(WPARAM, LPARAM);
	void CommandGroup(WPARAM, LPARAM);
	void CommandWhitespace(WPARAM, LPARAM);
	void CommandAlphaNumericCharacter(WPARAM, LPARAM);
	void CommandAlphaCharacter(WPARAM, LPARAM);
	void CommandDecDigit(WPARAM, LPARAM);
	void CommandHexNumber(WPARAM, LPARAM);
	void CommandNumber(WPARAM, LPARAM);
	void CommandInteger(WPARAM, LPARAM);
	void CommandCIdentifier(WPARAM, LPARAM);
	void CommandAlphabeticString(WPARAM, LPARAM);
	void CommandFindWhatText(WPARAM, LPARAM);
	void CommandTaggedExpression1(WPARAM, LPARAM);
	void CommandTaggedExpression2(WPARAM, LPARAM);
	void CommandTaggedExpression3(WPARAM, LPARAM);
	void CommandTaggedExpression4(WPARAM, LPARAM);
	void CommandTaggedExpression5(WPARAM, LPARAM);
	void CommandTaggedExpression6(WPARAM, LPARAM);
	void CommandTaggedExpression7(WPARAM, LPARAM);
	void CommandTaggedExpression8(WPARAM, LPARAM);
	void CommandTaggedExpression9(WPARAM, LPARAM);


// Dialog Data
	//{{AFX_DATA(CReplaceDlg)
	enum { IDD = IDD_REPL };
	CEdit	m_ReplaceText;
	CEdit	m_FindText;
	CButton	m_MatchWholeWord;
	CButton	m_RegularExpression;
	CButton	m_MatchCase;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReplaceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CReplaceDlg)
	virtual void OnOK();
	afx_msg void OnRegexpfind();
	afx_msg void OnRegExpReplace();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REPLACEDLG_H__14334320_B34A_11D0_A217_244106C10000__INCLUDED_)
