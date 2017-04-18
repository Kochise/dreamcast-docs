#if !defined(AFX_DLGWINMGR_H__C1AC212C_8ABF_11D1_B145_000000000000__INCLUDED_)
#define AFX_DLGWINMGR_H__C1AC212C_8ABF_11D1_B145_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWinMgr.h : header file
//

#include "MyListCtrl.h"
#include "dirlist.h"
#include "resource.h"
#include "winsapp.h"


enum {
	COL_FILENAME = 0,
	COL_TIME,
	COL_EXT,
	COL_DIRNAME,
	COL_SIZE,
	COL_DEBUGSIZE,
};


/////////////////////////////////////////////////////////////////////////////
// CDlgWinMgr dialog

class CWindowsList; // FORWARD

class CDlgWinMgr : public CDialog
{
// Construction
public:
	void DoClear();
	void SetButtonStates();
	int FillList();
	void SetVars(BOOL fAutoVis, BOOL fAutoDir, BOOL fAutoSize, int iSortedCol, long lSize);
	void GetVars(BOOL& fAutoVis, BOOL& fAutoDir, BOOL& fAutoSize, int& iSortedCol, long& lSize);
	void SetDirList(CDirList* pList, CWindowsList *pWndList);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CDlgWinMgr(CWnd* pParent = NULL);   // standard constructor

	static int CALLBACK MySort(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
	static void CALLBACK OnListClick(NMHDR *pNMHDR, LRESULT *pResult, LPARAM lParam);
	static void CALLBACK OnListDblClick(NMHDR *pNMHDR, LRESULT *pResult, LPARAM lParam);
	static void CALLBACK OnColClick(NMHDR *pNMHDR, LRESULT *pResult, LPARAM lParam, SortInfo *pSortInfo);

// Dialog Data
	//{{AFX_DATA(CDlgWinMgr)
	enum { IDD = IDD_DLGWINMGR };
	CButton	m_ctlSelectAll;
	CButton	m_ctlRefresh;
	CButton	m_ctlOpen;
	CButton	m_ctlMakeList;
	CButton	m_ctlLoad;
	CButton	m_ctlInvert;
	CButton	m_ctlClose;
	CMyListCtrl	m_ctlListWinMgr;
	BOOL	m_fAutoDir;
	BOOL	m_fAutoSize;
	BOOL	m_fAutoVis;
	//}}AFX_DATA
	int m_iSortedCol;
	long m_lSize;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWinMgr)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CToolTipCtrl m_tooltip;
	CWindowsList * m_pWndList;
	CDirList *m_pdirList;
	TCHAR m_szToolTipBuffer[256];

	// Generated message map functions
	//{{AFX_MSG(CDlgWinMgr)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonclose();
	afx_msg void OnButtoninvertsel();
	afx_msg void OnButtonopen();
	afx_msg void OnButtonselectall();
	afx_msg void OnButtonmakelist();
	afx_msg void OnButtonloadlist();
	afx_msg void OnButtonrefresh();
	afx_msg void OnButtonminwins();
	afx_msg void OnButtonclear();
	afx_msg void OnNotify( NMHDR * pNotifyStruct, LRESULT * result );
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWINMGR_H__C1AC212C_8ABF_11D1_B145_000000000000__INCLUDED_)
