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
//	Header file for PREVEDLG.CPP  


#ifndef prevedlg_h_
#define prevedlg_h_

#include "vconview.h"

//Struct to handle moving of controls based upon availability 
//of pre-verify information from registry and type lib.
typedef struct 
{
	CRect rect;		//Holds top left and bottom right of checbox
	CButton * pCheckBoxCtl;
	BOOL bVisible;	//True if the control is visible.
} CStrCheckBoxPos;

//The number of rows that may be displayed if info not found in typelib or
//registry.
#define NUM_DYNAMIC_CONTROL_ROWS  6


/////////////////////////////////////////////////////////////////////////////
// CPreVerifyDlg dialog

class CPreVerifyDlg : public CDialog
{
// Construction
public:
	CPreVerifyDlg(CWnd* pParent = NULL);   // standard constructor
	void SetView ( CVContainView * pView )
		{ m_pView = pView; }

	//Set to TRUE if the dialog is being displayed in the results dialog to 
	//indicate to the user what pre-verification information was obtained. 
	//Set to FALSE if the dialog is being displayed to obtaine pre-verify 
	//information.
	BOOL m_bResultsOfPreverify; 

	//Holds pointer to view object to access its boolean members during display of
	//pre-verification results.
	CVContainView * m_pView;

	//Set to TRUE if need to display pre-verify questions in pre-verify dialog
	//about whether the control supports props & methods, events & prop 
	//notification, or licensing.
	BOOL m_bEnablePropMethodQuestion;
	BOOL m_bEnableConnPtQuestion;
	BOOL m_bEnableLicensedQuestion;
	BOOL m_bEnableUIQuestion;
	BOOL m_bEnableLinksQuestion;
	BOOL m_bEnablePropPagesQuestion;

// Dialog Data
//		enum { IDD = IDD_PRE_VERIFY };

	//{{AFX_DATA(CPreVerifyDlg)
	enum { IDD = IDD_PRE_VERIFY };
	CButton	m_Accelerators_Yes_Ctl;
	CButton	m_Prop_Pages_Yes_Ctl;
	CStatic	m_Intro_Results_Ctl;
	CStatic	m_Intro_Pre_Verify_Ctl;
	CButton	m_OK_Ctl;
	CButton	m_Cancel_Ctl;
	CButton	m_Links_Yes_Ctl;
	CButton	m_PropsMethods_Yes_Ctl;
	CButton	m_Notifications_Yes_Ctl;
	CButton	m_Licensing_Yes_Ctl;
	CButton	m_Mnemonics_Yes_Ctl;
	CButton	m_Ambients_Yes_Ctl;
	CButton	m_UI_Yes_Ctl;
	CButton	m_Prop_Set_Yes_Ctl;
	BOOL	m_Prop_Set_Yes;
	BOOL	m_UI_Yes;
	BOOL	m_Ambients_Yes;
	BOOL	m_Mnemonics_Yes;
	BOOL	m_Notifications_Yes;
	BOOL	m_PropsMethods_Yes;
	BOOL	m_Licensing_Yes;
	BOOL	m_Links_Yes;
	BOOL	m_Prop_Pages_Yes;
	BOOL	m_Accelerators_Yes;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPreVerifyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ShowAllControls ();
	void SetPreVerifyChkBoxes ();
	void ReadControlPosAndVisibility ();
	void MoveAndDisplayControls ();

	// Generated message map functions
	//{{AFX_MSG(CPreVerifyDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif


