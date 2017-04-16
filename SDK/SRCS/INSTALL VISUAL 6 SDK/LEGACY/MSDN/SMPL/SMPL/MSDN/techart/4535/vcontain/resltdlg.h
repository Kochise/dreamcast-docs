//OLE Control Container Verification Application, Version 1.00
//
//Copyright (c) 1995-6 Microsoft Corp, All Rights Reserved
//
//	This is a part of the Microsoft Source Code Samples.
//	This source code is only intended as a supplement to
//	the Microsoft Development Tools and/or WinHelp implementation.
//	See these sources for detailed information regarding the
//	Microsoft sample programs.
//
//Revisions:
//	November 30, 1995	mtm		First Implementation
//
//Purpose:
//  Header file for RESLTDLG.CPP


#ifndef resltdlg_h_
#define resltdlg_h_

#include "resource.h"

//Use a forward reference since we just need a pointer to the class here.
class CVContainView;

//Contants for filter check box selections.  These numbers are arbitrary but 
//the difference between mandatory/optional and fail/success need to allow 
//unique combinations.
#define MAN_CHK_VALUE		4
#define OPT_CHK_VALUE		8
#define FAIL_CHK_VALUE		20
#define SUCCESS_CHK_VALUE	30
#define NOT_VERIF_CHK_VALUE 40

//Used in determining if result should be displayed based upon the filter.
//M - mandatory
//O - optional  TRUE
//S - success 
//F - failure
//N - not verified

//Mandatory only options
const int iMS	= MAN_CHK_VALUE + SUCCESS_CHK_VALUE;
const int iMF	= MAN_CHK_VALUE + FAIL_CHK_VALUE;
const int iMN	= MAN_CHK_VALUE + NOT_VERIF_CHK_VALUE;
const int iMFS	= iMS + FAIL_CHK_VALUE;
const int iMSN	= iMS + NOT_VERIF_CHK_VALUE;
const int iMFN	= iMF + NOT_VERIF_CHK_VALUE;
const int iMFSN = iMFS + NOT_VERIF_CHK_VALUE;

//Optional only options
const int iOS  = OPT_CHK_VALUE + SUCCESS_CHK_VALUE;
const int iOF  = OPT_CHK_VALUE + FAIL_CHK_VALUE;
const int iON = OPT_CHK_VALUE + NOT_VERIF_CHK_VALUE;
const int iOFS = iOF + SUCCESS_CHK_VALUE;
const int iOSN = iOS + NOT_VERIF_CHK_VALUE;
const int iOFN = iOF + NOT_VERIF_CHK_VALUE;
const int iOFSN = iOFS + NOT_VERIF_CHK_VALUE;

//Mandatory and Optional combinations
const int iMOS = iMS + OPT_CHK_VALUE;
const int iMOF = iMF + OPT_CHK_VALUE;
const int iMON	= iMN + OPT_CHK_VALUE;
const int iMOFS = iMFS + OPT_CHK_VALUE;
const int iMOFN = iMFN + OPT_CHK_VALUE;
const int iMOSN = iMOS + NOT_VERIF_CHK_VALUE;
const int iMOFSN = iMFSN+ OPT_CHK_VALUE;


//Result objects for displaying the results of each QI and method invocation.
class CResultsObj : public CObject
{
public:
	CString	sResultString;	//Composite string displayed
	BOOL	bMandatory;		//TRUE if mandatory; FALSE optional
	BOOL	bVerified;		//TRUE if method verified; FALSE not verified.
	HRESULT	hResult;		//HRESULT hex value
	BOOL	bSave;			//TRUE if should be written to file on "Save Results".
};


/////////////////////////////////////////////////////////////////////////////
// CResultsDlg dialog

class CResultsDlg : public CDialog
{
// Construction
public:
	CResultsDlg ( CWnd* pParent = NULL );   // standard constructor
	void SetView ( CVContainView * pView )
		{ m_pView = pView; }
	void DisplayResultsInListBox ();
	void InitFilterButtons ();
	int CalculateCheckedTotal ();
	BOOL QueryToDisplay ( const CResultsObj * pResObj, int iTotal );


// Dialog Data
	//{{AFX_DATA(CResultsDlg)
	enum { IDD = IDD_RESULTS };
	CButton	m_chkNotVerified;
	CButton	m_chkSuccess;
	CButton	m_chkOptional;
	CButton	m_chkMandatory;
	CButton	m_chkFail;
	CListBox	m_ctlList;
	CString	m_ManFailures;
	CString	m_ManSuccesses;
	CString	m_OptSuccesses;
	CString	m_NotVerified;
	CString	m_ManNotVerified;
	CString	m_OptNotVerified;
	//}}AFX_DATA

//Attributes
//Member variables for results.
	unsigned short m_uManFailures;
	unsigned short m_uManSuccesses;
	unsigned short m_uManNotVerified;
	unsigned short m_uOptSuccesses;
	unsigned short m_uOptNotVerified;
	CObList m_ResultList;

//Holds pointer to view object to access its boolean members during display 
//of pre-verification results.
	CVContainView * m_pView;

//Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResultsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResultsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnChkFail();
	afx_msg void OnChkMandatory();
	afx_msg void OnChkNotVerified();
	afx_msg void OnChkOptional();
	afx_msg void OnChkSuccess();
	afx_msg void OnSaveToFile();
	afx_msg void OnPreVerify();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif
