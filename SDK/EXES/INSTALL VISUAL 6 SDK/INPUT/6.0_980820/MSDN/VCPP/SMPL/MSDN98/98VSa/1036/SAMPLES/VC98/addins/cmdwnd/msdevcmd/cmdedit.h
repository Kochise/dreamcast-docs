#if !defined(AFX_CMDEDIT_H__B772029E_B6B0_11D1_8320_00A0C91BC942__INCLUDED_)
#define AFX_CMDEDIT_H__B772029E_B6B0_11D1_8320_00A0C91BC942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CmdEdit.h : header file
//

class CMsdevcmdDlg;
class CCmdEdit;

/////////////////////////////////////////////////////////////////////////////
// CCmdEdit window
typedef BOOL (__cdecl *CmdOp)(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);

class CCmdEdit : public CEdit
{
// Construction
public:
	CCmdEdit();
	void SetParent(CMsdevcmdDlg *pParent);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCmdEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetBrkPntList(CStringArray& rgStrBrks);
	BOOL FSendCommandToMSDEV(CString& rstrCmd);
	void SendCmdToDos(CString& rstrCmd);
	void Append(LPCTSTR szText);
	BOOL FHaveApp();
	HRESULT FindDoc(LPCTSTR szFile, CComPtr<IGenericDocument>& pDoc, BOOL fOkToOpen = TRUE);
	BOOL DoEnableDisableCmds(CString& rstrCmdName, CString& rstrCmd, BOOL fEnable);

	// COMMANDS -- add to m_rgCmds in constructor, ensure string resource exists
	static BOOL CmdGo(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdOpen(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdClose(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdHelp(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdStep(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdStepInto(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdBuild(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdRebuild(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdQuit(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdExit(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdCD(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdCls(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdDos(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdBL(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdBC(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdBP(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdBD(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);
	static BOOL CmdBE(CCmdEdit *pThis, CString& rstrCmdName, CString& rstrCmd);


	BOOL FParseCommand(CString& rstrCmd, CmdOp& rpCmd);
	virtual ~CCmdEdit();

	// Generated message map functions
protected:
	BOOL m_fWin95;
	BOOL m_fWin4;
	CMsdevcmdDlg * m_pDlgParent;
	CString m_strCmd;
	CStringList m_rgStrings;
	CMapStringToPtr m_rgCmds;
	CComPtr<IApplication> m_spApplication;

	//{{AFX_MSG(CCmdEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMDEDIT_H__B772029E_B6B0_11D1_8320_00A0C91BC942__INCLUDED_)
