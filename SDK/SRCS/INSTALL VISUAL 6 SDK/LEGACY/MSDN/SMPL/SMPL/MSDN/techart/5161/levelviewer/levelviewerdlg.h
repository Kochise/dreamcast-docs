// LevelViewerDlg.h : header file
//

#if !defined(AFX_LEVELVIEWERDLG_H__7423445E_F528_11D0_A980_0020182A7050__INCLUDED_)
#define AFX_LEVELVIEWERDLG_H__7423445E_F528_11D0_A980_0020182A7050__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CLevelViewerDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CLevelViewerDlg dialog

interface ILevelGetter;

class CLevelViewerDlg : public CDialog
{
	DECLARE_DYNAMIC(CLevelViewerDlg);
	friend class CLevelViewerDlgAutoProxy;

public:
	CLevelViewerDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CLevelViewerDlg();

	//{{AFX_DATA(CLevelViewerDlg)
	enum { IDD = IDD_LEVELVIEWER_DIALOG };
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CLevelViewerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CLevelViewerDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	void ClearMembers();
	void SetNewData(const CLSID& clsid, const IID& iid);

	ILevelGetter* m_pILevelGetter;
	CString m_sLastCalled;

	// Generated message map functions
	//{{AFX_MSG(CLevelViewerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnFish();
	afx_msg void OnGas();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEVELVIEWERDLG_H__7423445E_F528_11D0_A980_0020182A7050__INCLUDED_)
