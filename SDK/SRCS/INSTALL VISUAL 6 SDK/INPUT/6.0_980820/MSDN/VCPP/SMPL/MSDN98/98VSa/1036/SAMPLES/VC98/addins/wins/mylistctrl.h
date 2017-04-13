#if !defined(AFX_MYLISTCTRL_H__C1AC212D_8ABF_11D1_B145_000000000000__INCLUDED_)
#define AFX_MYLISTCTRL_H__C1AC212D_8ABF_11D1_B145_000000000000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyListCtrl.h : header file
//

class CMyListCtrl;

struct SortInfo
{
	int iColumn;
	CMyListCtrl *pList;
};

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl window

typedef void (CALLBACK * LPFNLCOP)(NMHDR* pNMHDR, LRESULT* pResult, LPARAM lParam);
typedef void (CALLBACK * LPFNLCSOP)(NMHDR* pNMHDR, LRESULT* pResult, LPARAM lParam, SortInfo *pSortInfo); // ListControl Sort OPeration

class CMyListCtrl : public CListCtrl
{
// Construction
public:
	CMyListCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetOnClick(LPFNLCOP pfnLCOpHandler, LPARAM lParam);
	void SetOnDblClick(LPFNLCOP pfnLCOpHandler, LPARAM lParam);
	void SetSort(PFNLVCOMPARE pfnSort, LPARAM lParam);
	void SetColClick(LPFNLCSOP pfnLCOpHandler, LPARAM lParam);
	void DoSort(int iCol);

	int GetColumnCount();
	virtual ~CMyListCtrl();
	void SetWidths();
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	int GetCurrentIndex();
	int InsertItem(int nItem, LPCTSTR lpszItem, LPARAM lItemData);


	// Generated message map functions
protected:
	LPFNLCOP m_pfnLCClick;
	LPARAM m_lParamClick;
	LPFNLCSOP m_pfnLCColClick;
	LPARAM m_lParamColClick;
	LPFNLCOP m_pfnLCDblClick;
	LPARAM m_lParamDblClick;
	PFNLVCOMPARE m_pfnSort;
	LPARAM m_lParamSort;

	int m_cCols;
	int m_iIndexCurrent;

	//{{AFX_MSG(CMyListCtrl)
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult); 
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};




/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTCTRL_H__C1AC212D_8ABF_11D1_B145_000000000000__INCLUDED_)
