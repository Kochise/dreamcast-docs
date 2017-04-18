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
//	Dialog to obtain pre-verification infomation from user.
//FUNCTIONS:

#include "stdafx.h"
#include "prevedlg.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPreVerifyDlg dialog

CPreVerifyDlg::CPreVerifyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPreVerifyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPreVerifyDlg)
	m_Prop_Set_Yes = FALSE;
	m_UI_Yes = FALSE;
	m_Ambients_Yes = FALSE;
	m_Mnemonics_Yes = FALSE;
	m_Notifications_Yes = FALSE;
	m_PropsMethods_Yes = FALSE;
	m_Licensing_Yes = FALSE;
	m_Links_Yes = FALSE;
	m_Prop_Pages_Yes = FALSE;
	m_Accelerators_Yes = FALSE;
	//}}AFX_DATA_INIT
}


void CPreVerifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPreVerifyDlg)
	DDX_Control(pDX, IDC_ACCELERATORS_YES, m_Accelerators_Yes_Ctl);
	DDX_Control(pDX, IDC_PROP_PAGES_YES, m_Prop_Pages_Yes_Ctl);
	DDX_Control(pDX, IDC_INTRO_RESULTS, m_Intro_Results_Ctl);
	DDX_Control(pDX, IDC_INTRO_PRE_VERIFY, m_Intro_Pre_Verify_Ctl);
	DDX_Control(pDX, IDOK, m_OK_Ctl);
	DDX_Control(pDX, IDCANCEL, m_Cancel_Ctl);
	DDX_Control(pDX, IDC_LINKS_YES, m_Links_Yes_Ctl);
	DDX_Control(pDX, IDC_PROPSMETHODS_YES, m_PropsMethods_Yes_Ctl);
	DDX_Control(pDX, IDC_NOTIFICATIONS_YES, m_Notifications_Yes_Ctl);
	DDX_Control(pDX, IDC_LICENSING_YES, m_Licensing_Yes_Ctl);
	DDX_Control(pDX, IDC_MNEMONICS_YES, m_Mnemonics_Yes_Ctl);
	DDX_Control(pDX, IDC_AMBIENT_YES, m_Ambients_Yes_Ctl);
	DDX_Control(pDX, IDC_UI_YES, m_UI_Yes_Ctl);
	DDX_Control(pDX, IDC_PROP_SET_YES, m_Prop_Set_Yes_Ctl);
	DDX_Check(pDX, IDC_PROP_SET_YES, m_Prop_Set_Yes);
	DDX_Check(pDX, IDC_UI_YES, m_UI_Yes);
	DDX_Check(pDX, IDC_AMBIENT_YES, m_Ambients_Yes);
	DDX_Check(pDX, IDC_MNEMONICS_YES, m_Mnemonics_Yes);
	DDX_Check(pDX, IDC_NOTIFICATIONS_YES, m_Notifications_Yes);
	DDX_Check(pDX, IDC_PROPSMETHODS_YES, m_PropsMethods_Yes);
	DDX_Check(pDX, IDC_LICENSING_YES, m_Licensing_Yes);
	DDX_Check(pDX, IDC_LINKS_YES, m_Links_Yes);
	DDX_Check(pDX, IDC_PROP_PAGES_YES, m_Prop_Pages_Yes);
	DDX_Check(pDX, IDC_ACCELERATORS_YES, m_Accelerators_Yes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPreVerifyDlg, CDialog)
	//{{AFX_MSG_MAP(CPreVerifyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPreVerifyDlg message handlers

//Structures to hold positions of dynamic control rows.
CStrCheckBoxPos	checkboxPos [NUM_DYNAMIC_CONTROL_ROWS];

//***************************************************************************
//METHOD NAME:			
//	CPreVerifyDlg::OnInitDialog
//PURPOSE:
//Called in response to the WM_INITDIALOG message during creation but 
//immediately before the 	dialog box is displayed. Here we initialize 
//the display of pre-verification questions based 	upon our ability to
//determine information from the type library or the registry. 
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	TRUE - if the focus is not set to a control
//	FALSE - if you set the focus to a control
//***************************************************************************
BOOL CPreVerifyDlg::OnInitDialog () 
{
	ASSERT ( this != NULL );
	
	//First call base class.
	CDialog::OnInitDialog ();

	if ( m_bResultsOfPreverify )
	{
		//Display the results of the previously run pre-verification process.
		//Change the introduction line in the dialog.
		m_Intro_Results_Ctl.ShowWindow ( SW_SHOW );
		m_Intro_Pre_Verify_Ctl.ShowWindow ( SW_HIDE );	

		//Make all controls visible that are hidden.  These are all but the
		//first three which are always diplayed.
		ShowAllControls ();

		//Set all check boxes according to what pre-verify info was obtained.
		SetPreVerifyChkBoxes ();
	}
	else
	{
		//Obtain pre-verification information prior to verification process.
		//The first three prompts are constant.  Read all positions of the 
		//remaining prompts and their check boxes into an array.
		ReadControlPosAndVisibility ();

		//Position the controls and display them if appropriate.
		MoveAndDisplayControls ();
	}

	return TRUE;  
}


//***************************************************************************
//METHOD NAME:			
//	CPreVerifyDlg::ShowAllControls
//PURPOSE:
//	Displays all the controls that are by default hidden in the dialog box.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None.
//***************************************************************************
void CPreVerifyDlg::ShowAllControls ()
{
	m_Links_Yes_Ctl.ShowWindow ( SW_SHOW );
	m_UI_Yes_Ctl.ShowWindow ( SW_SHOW );
	m_Licensing_Yes_Ctl.ShowWindow ( SW_SHOW );
	m_PropsMethods_Yes_Ctl.ShowWindow ( SW_SHOW );
	m_Notifications_Yes_Ctl.ShowWindow ( SW_SHOW );
	m_Prop_Pages_Yes_Ctl.ShowWindow ( SW_SHOW );
}


//**************************************************************************
//METHOD NAME:			
//	CPreVerifyDlg::SetPreVerifyChkBoxes
//PURPOSE:
//	Sets the check boxes to reflect the results of pre-verification.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None.
//***************************************************************************
void CPreVerifyDlg::SetPreVerifyChkBoxes ()
{		
	m_Prop_Set_Yes_Ctl.SetCheck ( m_pView->m_bPropSets  );
	m_UI_Yes_Ctl.SetCheck ( m_pView->m_bUI );
	m_Ambients_Yes_Ctl.SetCheck ( m_pView->m_bAmbients  );
	m_Mnemonics_Yes_Ctl.SetCheck ( m_pView->m_bMnemonics );
	m_Accelerators_Yes_Ctl.SetCheck ( m_pView->m_bAccelerators );
	m_Notifications_Yes_Ctl.SetCheck ( m_pView->m_bConnPoints  );
	m_PropsMethods_Yes_Ctl.SetCheck ( m_pView->m_bPropsMethods );
	m_Licensing_Yes_Ctl.SetCheck ( m_pView->m_bLicensed );
	m_Links_Yes_Ctl.SetCheck ( m_pView->m_bLinks );
	m_Prop_Pages_Yes_Ctl.SetCheck ( m_pView->m_bPropPages );
}


//***************************************************************************
//METHOD NAME:			
//	CPreVerifyDlg::ReadControlPosAndVisibility
//PURPOSE:
//	Reads in all the coordinates (top, left, bottom, and right) of the label
//  controls and their accompanying checkboxes.  These controls are not 
//  visible initially.  These values are used to adjust the vertical positions
//  of the controls based upon which information is not available from the 
//  type library and registry.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None.
//***************************************************************************
void CPreVerifyDlg::ReadControlPosAndVisibility ()
{
	CRect rect;

	ASSERT ( this != NULL );

	//Read in all positions of checkboxes.
	//Use the m_bEnable_____Question member to determine if the checkbox,
	//should be shown.
	//Licensing question checkbox.
	m_Licensing_Yes_Ctl.GetWindowRect ( &rect );
	ScreenToClient ( & rect );
	checkboxPos[0].rect = rect;
	checkboxPos[0].pCheckBoxCtl = &m_Licensing_Yes_Ctl;
	checkboxPos[0].bVisible = m_bEnableLicensedQuestion;

	//UI question checkbox.
	m_UI_Yes_Ctl.GetWindowRect ( &rect );
	ScreenToClient ( & rect );
	checkboxPos[1].rect = rect;
	checkboxPos[1].pCheckBoxCtl = &m_UI_Yes_Ctl;
	checkboxPos[1].bVisible = m_bEnableUIQuestion;

	//Props and methods question checkbox.
	m_PropsMethods_Yes_Ctl.GetWindowRect ( &rect );
	ScreenToClient ( & rect );
	checkboxPos[2].rect = rect;
	checkboxPos[2].pCheckBoxCtl = &m_PropsMethods_Yes_Ctl;
	checkboxPos[2].bVisible = m_bEnablePropMethodQuestion;

	//Notification question checkbox.
	m_Notifications_Yes_Ctl.GetWindowRect ( &rect );
	ScreenToClient ( & rect );
	checkboxPos[3].rect = rect;
	checkboxPos[3].pCheckBoxCtl = &m_Notifications_Yes_Ctl;
	checkboxPos[3].bVisible = m_bEnableConnPtQuestion;

	//Property pages question checkbox.
	m_Prop_Pages_Yes_Ctl.GetWindowRect ( &rect );	
	ScreenToClient ( & rect );
	checkboxPos[4].rect = rect;
	checkboxPos[4].pCheckBoxCtl = &m_Prop_Pages_Yes_Ctl;
	checkboxPos[4].bVisible = m_bEnablePropPagesQuestion;

	//External links question checkbox.
	m_Links_Yes_Ctl.GetWindowRect ( &rect );	
	ScreenToClient ( & rect );
	checkboxPos[5].rect = rect;
	checkboxPos[5].pCheckBoxCtl = &m_Links_Yes_Ctl;
	checkboxPos[5].bVisible = m_bEnableLinksQuestion;

}


//***************************************************************************
//METHOD NAME:			
//	CPreVerifyDlg::MoveAndDisplayControls
//PURPOSE:
//	A question the checkbox control.  This should be shown if 
//  the information could not be pre-verified from the registry or type 
//  library. Determine this	and display the questions in a contigous top 
//  to bottom order without any empty lines in 	between the dialog.  
//  adjust the size of the dialog and the position of the Ok and Cancel
//	buttons depending upon the amount of questions not displayed. 
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None.
//***************************************************************************
void CPreVerifyDlg::MoveAndDisplayControls()
{
	ASSERT( this != NULL );

	//TRUE if there is a new slot open; initially no higher slots open.
	BOOL bHigherSlotAvailable = FALSE;
	CRect nextCheckboxSlotPos;	//Holds next pos to draw next checkbox control
	CRect dlgBoxRect;			//Holds bounding coords of dialog box 
								//which may change as questions shown.
	CRect CToSRect;				//Holds client coords to be converted to 
								//screen coords.
	CRect okRect, cancelRect;	//OK and Cancel button coords used for moving 
								//them later if needed
	int iTopHiddenControl = 0;
	int iHeightQuestion;
	int iTotVerticalDeduction = 0;	//Used to move the bottom of dlgbox and 
									//OK/Cancel at end

	//Get the initial coords of the dialog window to allow vertical resizing 
	//based upon questions not being shown.  
	GetWindowRect ( &dlgBoxRect );

	ASSERT_POINTER ( &dlgBoxRect, CRect );

	//Calculate the width between questions to add to the deducted area.
	iHeightQuestion = checkboxPos[1].rect.top - checkboxPos[0].rect.bottom;

	//Initialize the next position.
	nextCheckboxSlotPos = checkboxPos[0].rect;

	for ( int i=0; i < NUM_DYNAMIC_CONTROL_ROWS; i++ )
		{
		if ( checkboxPos[i].bVisible )
			{
			if ( bHigherSlotAvailable )
				{
				//Combine that open slot's (entry with index 
				//iTopHiddenControl) and bottom values with the left and right
				//values of the control. 
				nextCheckboxSlotPos.top = 
								checkboxPos[iTopHiddenControl].rect.top;
				nextCheckboxSlotPos.bottom = 
								checkboxPos[iTopHiddenControl].rect.bottom;
				nextCheckboxSlotPos.left = checkboxPos[i].rect.left;
				nextCheckboxSlotPos.right = checkboxPos[i].rect.right;
				}
			
			//Draw the control at this location.
			checkboxPos[i].pCheckBoxCtl->MoveWindow ( nextCheckboxSlotPos );
			checkboxPos[i].pCheckBoxCtl->ShowWindow ( SW_SHOW );

			//Increment to point to next slot possibly since this 
			//slot is taken now.
			iTopHiddenControl += 1;
			nextCheckboxSlotPos = checkboxPos[i+1].rect;
			}

		else
			{
			//Deduct vertical height of question not shown from vertical 
			//length of verify dialog box.
			iTotVerticalDeduction += checkboxPos[i].rect.bottom - 
								checkboxPos[i].rect.top + iHeightQuestion;
			
			//Once set, this will never be false again.  A TRUE value means
			//that at least one question was not shown.
			bHigherSlotAvailable = TRUE;
			}
		}

	//Redraw dialog window with smaller vertical border and OK/Cancel buttons
	//moved up if at least one question was not shown.
	if ( bHigherSlotAvailable )
		{
		dlgBoxRect.bottom -= iTotVerticalDeduction;

		//Set OK button's new vertical coords.
		m_OK_Ctl.GetWindowRect ( &okRect );
		ScreenToClient ( & okRect );
		okRect.bottom -= iTotVerticalDeduction;
		okRect.top -= iTotVerticalDeduction;

		//Set Cancel button's new vertical coords.
		m_Cancel_Ctl.GetWindowRect ( &cancelRect );
		ScreenToClient ( & cancelRect );
		cancelRect.bottom -= iTotVerticalDeduction;
		cancelRect.top -= iTotVerticalDeduction;

		//Draw the dialog box and the OK/Cancel buttons at the new vertical 
		//coords.
		MoveWindow( dlgBoxRect );
		m_OK_Ctl.MoveWindow( okRect );
		m_Cancel_Ctl.MoveWindow( cancelRect );
		}
}

