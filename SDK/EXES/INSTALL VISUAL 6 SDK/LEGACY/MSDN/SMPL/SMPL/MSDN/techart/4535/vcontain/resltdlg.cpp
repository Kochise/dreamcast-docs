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
//	Displays results of verification in a dialog box.

#include "stdafx.h"
#include "prevedlg.h"
#include "resltdlg.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultsDlg dialog


CResultsDlg::CResultsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResultsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResultsDlg)
	m_ManFailures = _T("");
	m_ManSuccesses = _T("");
	m_OptSuccesses = _T("");
	m_NotVerified = _T("");
	m_ManNotVerified = _T("");
	m_OptNotVerified = _T("");
	//}}AFX_DATA_INIT
}


void CResultsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultsDlg)
	DDX_Control(pDX, IDC_CHK_NOT_VERIFIED, m_chkNotVerified);
	DDX_Control(pDX, IDC_CHK_SUCCESS, m_chkSuccess);
	DDX_Control(pDX, IDC_CHK_OPTIONAL, m_chkOptional);
	DDX_Control(pDX, IDC_CHK_MANDATORY, m_chkMandatory);
	DDX_Control(pDX, IDC_CHK_FAIL, m_chkFail);
	DDX_Control(pDX, IDC_LIST_RESULT_TEXT, m_ctlList);
	DDX_Text(pDX, IDC_MAN_FAILURES, m_ManFailures);
	DDX_Text(pDX, IDC_MAN_SUCCESS, m_ManSuccesses);
	DDX_Text(pDX, IDC_OPT_SUCCESS, m_OptSuccesses);
	DDX_Text(pDX, IDC_NOT_VERIFIED, m_NotVerified);
	DDX_Text(pDX, IDC_MAN_NOT_VERIFIED, m_ManNotVerified);
	DDX_Text(pDX, IDC_OPT_NOT_VERIFIED, m_OptNotVerified);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResultsDlg, CDialog)
	//{{AFX_MSG_MAP(CResultsDlg)
	ON_BN_CLICKED(IDC_CHK_FAIL, OnChkFail)
	ON_BN_CLICKED(IDC_CHK_MANDATORY, OnChkMandatory)
	ON_BN_CLICKED(IDC_CHK_NOT_VERIFIED, OnChkNotVerified)
	ON_BN_CLICKED(IDC_CHK_OPTIONAL, OnChkOptional)
	ON_BN_CLICKED(IDC_CHK_SUCCESS, OnChkSuccess)
	ON_BN_CLICKED(IDC_SAVE_TO_FILE, OnSaveToFile)
	ON_BN_CLICKED(IDC_PRE_VERIFY, OnPreVerify)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP ()

/////////////////////////////////////////////////////////////////////////////
// CResultsDlg message handlers

//***************************************************************************
//METHOD NAME:			
//	CResultsDlg::OnInitDialog 
//PURPOSE:
//	Called after the CResultsDlg object has been created but just prior to it
//  being shown. Inits the filter buttons to all checked to display all 
//  results initially, then displays them in the list box.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
BOOL CResultsDlg::OnInitDialog () 
{
	ASSERT( this != NULL );

	//Enable horizontal scroll bar.
	CListBox * listBox = ( CListBox  * ) GetDlgItem ( IDC_LIST_RESULT_TEXT);
	listBox->SetHorizontalExtent ( 650 );

	//If all the interfaces were tested, see it there were no mandatory 
	//failures or mandatory not verifieds. If so, then the control was compliant
	//with the guidelines.  Display a compliance message just before showing
	//the results dialog.
	if ( m_pView->m_bAllInterfacesTested )
	{
		if ( ( m_uManFailures > 0 ) || ( m_uManNotVerified > 0 ) )
		{
			AfxMessageBox ( IDS_CONTROL_FAILED );
		}
		else
		{
			AfxMessageBox ( IDS_CONTROL_PASSED );
		}
	}

	CDialog::OnInitDialog ();
	InitFilterButtons ();
	DisplayResultsInListBox ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//***************************************************************************
//METHOD NAME:			
//	CResultsDlg::InitFilterButtons
//PURPOSE:
//  Check all buttons so full display of all results intitially shown.	
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CResultsDlg::InitFilterButtons ()
{
	ASSERT( this != NULL );

	m_chkMandatory.SetCheck ( TRUE );
	m_chkOptional.SetCheck ( TRUE );
	m_chkSuccess.SetCheck ( TRUE );
	m_chkFail.SetCheck ( TRUE );
	m_chkNotVerified.SetCheck ( TRUE );
}


//***************************************************************************
//METHOD NAME:			
//	CResultsDlg::DisplayResultsInListBox
//PURPOSE:
//	Shows results strings for each interface or method in the list box if 
//  they correspond to the checked filter buttons.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CResultsDlg::DisplayResultsInListBox ()
{	
	ASSERT ( this != NULL );

	CString sResultString;
	CString sManOrOpt;
	CString sMandatory;  //Holds text for optional or mandatory.

	//Clear the list box of previous entries.  Do this before everything so 
	//if one of the invalid filter combinations check for immediately below 
	//exists, the listbox will not be left in a state where the filter does
	//not match what is shown in the list box.
	m_ctlList.ResetContent ();
	
	//Calculate the numerical total of the checked values.
	int iTotal = CalculateCheckedTotal ();

	POSITION pos = m_ResultList.GetHeadPosition ();

	//Iterate through each result entry and display it only if its filter box
	//is checked.
	while( pos != NULL )
	{
		CResultsObj * pResObj = ( CResultsObj * ) m_ResultList.GetNext ( pos );
		ASSERT ( pResObj != NULL );
		ASSERT_POINTER ( pResObj, CResultsObj );

		//Determine if the result string should be displayed based upon filter 
		//check boxes.
		if ( pResObj != NULL )
		{
			if ( QueryToDisplay ( pResObj, iTotal) )
			{
				m_ctlList.AddString ( pResObj->sResultString );

				//This result string will be written to the file if user 
				//selects Save.
				pResObj->bSave = TRUE;
			}

			else
			{
				//This result string will not be written to the file if user 
				//selects Save.
				pResObj->bSave = FALSE;
			}
		}
	}	
}


//***************************************************************************
//METHOD NAME:			
//	CResultsDlg::CalculateCheckedTotal
//PURPOSE:
//	Sums up the values associated with the checked filter buttons to be used 
//	by DisplayResultsInListBox.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	Total weighted value of checked filter buttons.
//***************************************************************************
int CResultsDlg::CalculateCheckedTotal ()
{
	ASSERT ( this != NULL );

	int uTempTotal = 0;

	if ( m_chkMandatory.GetCheck () )
	{
		uTempTotal = MAN_CHK_VALUE;
	}

	if ( m_chkOptional.GetCheck () )
	{
		uTempTotal += OPT_CHK_VALUE;
	}

	if ( m_chkFail.GetCheck () )
	{
		uTempTotal += FAIL_CHK_VALUE;
	}

	if ( m_chkSuccess.GetCheck () )
	{
		uTempTotal += SUCCESS_CHK_VALUE;
	}

	if ( m_chkNotVerified.GetCheck () )
	{
		uTempTotal += NOT_VERIF_CHK_VALUE;
	}

	return uTempTotal;
}



//***************************************************************************
//METHOD NAME:			
//	CResultsDlg::QueryToDisplay
//PURPOSE:
//	Compare the total value of all the checked filter buttons with this 
//	result object to decide it it should be displayed or not for this filter
//  condition.
//INPUT PARAMETER(s):	
//	const CResultsObj * pResObj - Current result object
//	int iTotal - Current numeric representation of filter buttons checked.
//OUTPUT PARAMETER(s):
//	TRUE - If it should be displayed.
//	FALSE - If it should NOT be displayed.
//RETURN VALUE:
//	None
//***************************************************************************
BOOL CResultsDlg::QueryToDisplay ( const CResultsObj * pResObj, int iTotal )
{
	ASSERT ( this != NULL );
	ASSERT ( pResObj != NULL );
	ASSERT_POINTER ( pResObj, CResultsObj );

	//If all criteria checked, MOFSN, display this record since there is
	//not criteria checking needed to do.
	if ( iTotal == iMOFSN )
	{
		return TRUE;
	}

	if ( pResObj->bMandatory )
	{
		switch( iTotal )
		{
			//This result string is for a mandatory interface.  Check against
			//success and failure method and interface possiblities.
			case iMF:
			case iMOF:
				//Display if mandatory and returned E_NOINTERFACE or E_NOTIMPL.
				if ( ( pResObj->bVerified ) && 
				   ( ( pResObj->hResult == E_NOINTERFACE ) || 
					 ( pResObj->hResult == E_NOTIMPL) ) )
				{
					return TRUE;
				}

				break;

			case iMS:
			case iMOS:
				//Display if mandatory success result.
				if ( ( pResObj->bVerified ) && 
				   ( ( pResObj->hResult != E_NOINTERFACE ) && 
					 ( pResObj->hResult != E_NOTIMPL ) ) )
				{
					return TRUE;
				}

				break;

			case iMFS:
			case iMOFS:
			//Don't care about hResult; just whether it was verified or not.
			if ( pResObj->bVerified ) 
			{
				return TRUE;
			}

			break;

			case iMN:
			case iMON:
				//Don't check hResult for Not Verified checkbox.
				if ( ! pResObj->bVerified )
				{
					return TRUE;
				}

				break;

			case iMSN:
			case iMOSN:
				//If verified succesfully or not verified at all
				if ( ( ! pResObj->bVerified ) ||
				   ( ( pResObj->bVerified ) && 
				   ( ( pResObj->hResult != E_NOINTERFACE )
					&& ( pResObj->hResult != E_NOTIMPL ) ) ) )
				{
					 return TRUE;
				}

				break;

			case iMFN:
			case iMOFN:
				//If failed or not verified at all
				if ( ( ! pResObj->bVerified ) || 
					 ( ( pResObj->bVerified ) && 
					 ( ( pResObj->hResult == E_NOINTERFACE ) || 
					   ( pResObj->hResult == E_NOTIMPL) ) ) )
				{
					 return TRUE;
				}

				break;

			case iMFSN:
			case iMOFSN:
				//Display whether failed, success, or 
				//not verified since all checked.
				return TRUE;
				break;
		}  //End switch
	}

	else 
	{
		//This result string is for an optional interface. 
		switch(iTotal)
		{
			case iOS:
			case iMOS:
			case iOFS:
			case iMOFS:
				//Display if optional success result.  As long as an optional 
				//was verified, it was a success.
				if ( pResObj->bVerified ) 
				{
					return TRUE;
				}

				break;
			
			case iON:
			case iMON: 
			case iOFN:
			case iMOFN:
				//Don't check hResult for Not Verified checkbox.
				if ( ! pResObj->bVerified )
				{
					return TRUE;
				}

				break;

			case iOSN:
			case iMOSN:
			case iOFSN:
			case iMOFSN:
				//Display whether failed, success, or not verified since all 
				//checked.
				return TRUE;
				break;
		}
	}
	
	//No combinations of the filter check boxes matched the result record so 
	//don't display.
	return FALSE;
}



//***************************************************************************
//METHOD NAME:			
//	CResultsDlg::OnSaveToFile
//PURPOSE:
//	Allows the user to save to a file of their choice the results displayed in
//	the results dialog box.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CResultsDlg::OnSaveToFile () 
{
	CString sManOrOpt;
	CString sFileName;
	CString sPathName;
	//Save the results in an ASCII file to disk using the common dialogs.
	CFileDialog dlg( FALSE,			//Construct File Save As box.
			_T ( "txt" ),			//Default file extension
			_T ( "VCONTAIN.TXT" ),	//Default file name
			OFN_CREATEPROMPT |
			OFN_OVERWRITEPROMPT );

	if ( dlg.DoModal () != IDOK )
	{
		return;
	}

	//Get the filename and save the result array to that file..
	sPathName = dlg.GetPathName ();

	CFile file;
	CFileException fe;

	if ( ! file.Open( sPathName, CFile::modeCreate | CFile::modeReadWrite |
					CFile::shareExclusive, &fe ) )
	{
		AfxMessageBox ( IDS_E_CANT_SAVE );
	}

	else
	{
		//Loop through result array, which contains results for every 
		//interface and method previously verified, and show only those which
		//are applicable to the results filter combination (mandatory, 
		//optional, success, failure, or verified).  This is determined by
		//the bSave member being set to TRUE. Add carriage return to each line.
		CString sFileResultString;
		POSITION pos = m_ResultList.GetHeadPosition ();
		
		sFileResultString.GetBuffer ( MAX_RESULT_STRING );
		
		while( pos != NULL )
		{
			CResultsObj * pResObj = 
							( CResultsObj * ) m_ResultList.GetNext ( pos );
			ASSERT ( pResObj != NULL );
			ASSERT_POINTER ( pResObj, CResultsObj );

			if ( ( pResObj != NULL ) && ( pResObj->bSave ) )
			{
				sFileResultString.Format ( "%s\r\n", pResObj->sResultString	);
				file.Write ( sFileResultString, sFileResultString.GetLength () );
			}
		}
	
	sFileResultString.ReleaseBuffer ();
	file.Close ();
	}	
}


//***************************************************************************
//METHOD NAME:			
//	CResultsDlg::OnPreVerify
//PURPOSE:
//	Allows the user to view the results of the pre-verification process in 
//the results dialog.
//INPUT PARAMETER(s):	
//	None
//OUTPUT PARAMETER(s):
//	None
//RETURN VALUE:
//	None
//***************************************************************************
void CResultsDlg::OnPreVerify () 
{
	CPreVerifyDlg dlg;
	
	//Set the view pointer to allow access to the view's boolean pre-vefify 
	//member variables.
	dlg.SetView ( m_pView );

	//Set to TRUE since the dialog is being displayed in the results dialog to 
	//indicate to the user what pre-verification information was obtained. 
	dlg.m_bResultsOfPreverify = TRUE;
	dlg.DoModal ();
}


//***************************************************************************
//Member functions to update the filtered results based upon checked boxes.
//***************************************************************************
void CResultsDlg::OnChkFail () 
{
	DisplayResultsInListBox ();
}

void CResultsDlg::OnChkMandatory () 
{
	DisplayResultsInListBox ();
}

void CResultsDlg::OnChkNotVerified () 
{
	DisplayResultsInListBox ();
}

void CResultsDlg::OnChkOptional () 
{
	DisplayResultsInListBox ();
}

void CResultsDlg::OnChkSuccess () 
{
	DisplayResultsInListBox ();
}


