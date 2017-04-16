// ResltDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VControl.h"
#include "VConCtl.h"
#include "ResltDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResultsDialog dialog


CResultsDialog::CResultsDialog( CWnd* pParent /*=NULL*/ )
	: CDialog(CResultsDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResultsDialog)
	m_checkFailures = FALSE;
	m_checkMandatory = FALSE;
	m_checkOptional = FALSE;
	m_checkSuccess = FALSE;
	//}}AFX_DATA_INIT
}


void CResultsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResultsDialog)
	DDX_Control(pDX, IDC_LIST_RESULT_TEXT, m_listboxResuls);
	DDX_Check(pDX, IDC_CHK_FAIL, m_checkFailures);
	DDX_Check(pDX, IDC_CHK_MANDATORY, m_checkMandatory);
	DDX_Check(pDX, IDC_CHK_OPTIONAL, m_checkOptional);
	DDX_Check(pDX, IDC_CHK_SUCCESS, m_checkSuccess);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResultsDialog, CDialog)
	//{{AFX_MSG_MAP(CResultsDialog)
	ON_BN_CLICKED(IDC_CHK_FAIL, OnChkFail)
	ON_BN_CLICKED(IDC_CHK_MANDATORY, OnChkMandatory)
	ON_BN_CLICKED(IDC_CHK_OPTIONAL, OnChkOptional)
	ON_BN_CLICKED(IDC_CHK_SUCCESS, OnChkSuccess)
	ON_BN_CLICKED(IDC_RESULTSFILE, OnResultsfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResultsDialog message handlers

BOOL CResultsDialog::OnInitDialog() 
{

	CDialog::OnInitDialog();

	//Enable horizontal scroll bar.
	CListBox * listBox = ( CListBox  * ) GetDlgItem ( IDC_LIST_RESULT_TEXT);
	listBox->SetHorizontalExtent ( 900 );

	m_checkFailures = TRUE;
	m_checkMandatory = TRUE;
	m_checkOptional = TRUE;
	m_checkSuccess = TRUE;
	
	FillResultsListBox();

	//Display message box showing compliance status.
	if ( m_nMandatoryFailures > 0 )
	{
		AfxMessageBox ( IDS_CONTROL_FAILED );
	}
	else
	{
		AfxMessageBox ( IDS_CONTROL_PASSED );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CResultsDialog::OnChkFail() 
{
	UpdateData(TRUE);
	FillResultsListBox();
}

void CResultsDialog::OnChkMandatory() 
{
	UpdateData(TRUE);
	FillResultsListBox();
}

void CResultsDialog::OnChkOptional() 
{
	UpdateData(TRUE);
	FillResultsListBox();
}

void CResultsDialog::OnChkSuccess() 
{
	UpdateData(TRUE);
	FillResultsListBox();
}

void CResultsDialog::FillResultsListBox(void)
{
	m_listboxResuls.ResetContent();

	m_nMandatoryFailures = 0;
	m_nMandatorySuccesses = 0;
	m_nOptionalTests = 0;

	// Iterate through all the interfaces and all the methods on those interfaces
	// and display the appropriate results according to the checkboxes
	CString* pstrOutputText;
	CString strMandatory;
	for ( int nInterfaceCount = 0; nInterfaceCount <= m_pInterfaceResultsArray->GetUpperBound(); nInterfaceCount++ )
	{
		CInterfaceVerificationResult* pInterfaceResult = (CInterfaceVerificationResult*)m_pInterfaceResultsArray->GetAt(nInterfaceCount);

		if ( ShouldDisplay(pInterfaceResult) )
		{

			pstrOutputText = pInterfaceResult->GetDescription();
			strMandatory.LoadString( pInterfaceResult->IsMandatory() ? IDS_MANDATORY : IDS_OPTIONAL );
			m_listboxResuls.AddString( *pstrOutputText +  " " + strMandatory + " : " + *pInterfaceResult->GetResult() );
		}
		// Iterate through all the method results on the interface result
		CObArray* pMethodArray = pInterfaceResult->GetMethodResultArray();
		for ( int nMethodCount = 0; nMethodCount <= pMethodArray->GetUpperBound(); nMethodCount++ )
		{
			CVerificationResult* pMethodResult = (CVerificationResult*)pMethodArray->GetAt(nMethodCount);
			if ( ShouldDisplay(pMethodResult) )
			{
				pstrOutputText = pMethodResult->GetDescription();
				strMandatory.LoadString( pMethodResult->IsMandatory() ? IDS_MANDATORY : IDS_OPTIONAL );
				m_listboxResuls.AddString("\t" + *pstrOutputText + " " + strMandatory + " : " + *pMethodResult->GetResult() );
			}
		}
	}
	SetDlgItemInt( IDC_MANDATORYSUCCCESS, m_nMandatorySuccesses );
	SetDlgItemInt( IDC_MANDATORYFAILURES, m_nMandatoryFailures );
	SetDlgItemInt( IDC_OPTIONALTESTS, m_nOptionalTests );

	UpdateData(FALSE);
}

BOOL CResultsDialog::ShouldDisplay(CVerificationResult* pResult)
{
	BOOL bDisplay = FALSE;

	if ( pResult->IsMandatory() )
	{
		if ( pResult->IsVerified() )
		{
			m_nMandatorySuccesses++;
			if ( m_checkSuccess && 	m_checkMandatory )
			{
				bDisplay = TRUE;
			}
		}
		else
		{
			m_nMandatoryFailures++;
			if ( m_checkFailures && m_checkMandatory )
			{
				bDisplay = TRUE;
			}
		}
	}
	else
	{
		m_nOptionalTests++;
		if ( m_checkSuccess && m_checkOptional )
		{
			bDisplay = TRUE;
		}
	}
	
	return bDisplay;
}

void CResultsDialog::OnResultsfile() 
{

	// Send all the results to a text file
	// First create the file
	try
	{
		CFileDialog fileDialog( FALSE, _T("txt") );
		if ( fileDialog.DoModal() == IDOK )
		{
		
			CFile* pLogFile = new CFile( fileDialog.GetPathName(), CFile::modeCreate | CFile::modeWrite );
			ASSERT( pLogFile != NULL );

			// Iterate through all the interfaces and all the methods on those interfaces
			// and ouput the results to the file
			CString strOutputText;
			CString strMandatory;
			for ( int nInterfaceCount = 0; nInterfaceCount <= m_pInterfaceResultsArray->GetUpperBound(); nInterfaceCount++ )
			{
				CInterfaceVerificationResult* pInterfaceResult = (CInterfaceVerificationResult*)m_pInterfaceResultsArray->GetAt(nInterfaceCount);
				strMandatory.LoadString( pInterfaceResult->IsMandatory() ? IDS_MANDATORY : IDS_OPTIONAL );
				strOutputText = *pInterfaceResult->GetDescription() + " " + strMandatory + " : " + *pInterfaceResult->GetResult() + "\r\n";
				pLogFile->Write( strOutputText, strOutputText.GetLength() );

				// Iterate through all the method results on the interface result
				CObArray* pMethodArray = pInterfaceResult->GetMethodResultArray();
				for ( int nMethodCount = 0; nMethodCount <= pMethodArray->GetUpperBound(); nMethodCount++ )
				{
					CVerificationResult* pMethodResult = (CVerificationResult*)pMethodArray->GetAt(nMethodCount);
					strMandatory.LoadString( pMethodResult->IsMandatory() ? IDS_MANDATORY : IDS_OPTIONAL );
					strOutputText = "\t" + *pMethodResult->GetDescription() + " " + strMandatory + " : " + *pMethodResult->GetResult() + "\r\n";
					pLogFile->Write( strOutputText, strOutputText.GetLength() );
				}
			}

			pLogFile->Close();
			delete pLogFile;
		}
	}
	catch (CFileException e)
	{
		AfxMessageBox( IDS_UNABLETOCREATEFILE );
	}
}
