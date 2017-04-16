//////////////////////////////////////////////////////////////////////////////
// RecordDlg.h		- Copyright (C) 1997 Microsoft Corporation				//
//					- All rights reserved.									//
// Date				- 12/11/97												//
// Purpose			- Header file for new/edit record dialog				//
//////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_RECORDDLG_H__BCE02A23_71B4_11D1_B887_00AA00C0803B__INCLUDED_)
#define AFX_RECORDDLG_H__BCE02A23_71B4_11D1_B887_00AA00C0803B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CRecordDlg : public CDialog
{
	LPBYTE		m_lpSketchData;
	long		m_nSketchSize;


public:
	CString GetTextData();
	void	SetTextData(const CString& strData);
	
	LPBYTE	GetSketchData();
	long	GetSketchSize();
	void	SetSketchData(LPBYTE lpData, long nSize);

	CRecordDlg(CWnd* pParent = NULL);   
	virtual ~CRecordDlg();

	//{{AFX_DATA(CRecordDlg)
	enum { IDD = IDD_RECORD_DIALOG };
	CButton	m_btnSketch;
	CString	m_strData;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRecordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:

	// Generated message map functions
	//{{AFX_MSG(CRecordDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSketch();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RECORDDLG_H__BCE02A23_71B4_11D1_B887_00AA00C0803B__INCLUDED_)
