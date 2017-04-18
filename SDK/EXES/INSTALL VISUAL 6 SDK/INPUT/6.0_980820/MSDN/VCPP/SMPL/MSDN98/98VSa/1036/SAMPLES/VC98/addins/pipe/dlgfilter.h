#if !defined(AFX_DLGFILTER_H__BDB2E780_A545_11D1_9505_C04C9504C07C__INCLUDED_)
#define AFX_DLGFILTER_H__BDB2E780_A545_11D1_9505_C04C9504C07C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgFilter.h : header file
//
#include "resource.h"       // main symbols
#include <ObjModel\addguid.h>
#include <ObjModel\appguid.h>
#include <ObjModel\bldguid.h>
#include <ObjModel\textguid.h>
#include <ObjModel\dbgguid.h>
#include "mrustrings.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgFilter dialog

class CDlgFilter : public CDialog
{
// Construction
public:
	void SaveMRU();
	void SetApp(IApplication *pApp);
	CDlgFilter(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFilter)
	enum { IDD = IDD_DIALOGFILTER };
	CStatic	m_ctlWarning;
	CComboBox	m_ctlComboCmd;
	CButton	m_ctlChkTrim;
	CEdit	m_ctlEditOutFile;
	CButton	m_ctlChkPipe;
	CButton	m_ctlChkAppend;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL m_fMidSelection;
	BOOL m_fLineSelection;
	long m_iColStart;
	long m_cbLineLengthFirst;
	long m_cbLineLengthLast;
	BOOL m_fColumnar;
	long m_cbLineLength;
	long m_lEnd;
	long m_lStart;
	long m_iColEnd;
	CString m_strSelFileName;
	CComPtr<IApplication> m_pApp;
	CComQIPtr<ITextDocument, &IID_ITextDocument> m_pDoc;
	CComQIPtr<ITextSelection, &IID_ITextSelection> m_pSel;
	CMRUStrings m_mruCmds;

	// Generated message map functions
	//{{AFX_MSG(CDlgFilter)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBtnbrowsecmd();
	afx_msg void OnClose();
	afx_msg void OnButtonsrcfile();
	afx_msg void OnButtonselection();
	afx_msg void OnButtonstartline();
	afx_msg void OnButtonendline();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFILTER_H__BDB2E780_A545_11D1_9505_C04C9504C07C__INCLUDED_)
