//--------------------------------------------------------------------
// Microsoft ADO Samples
//
// (c) 1996 Microsoft Corporation.  All Rights Reserved.
//
// @doc GetRows Sample
//
// @module	getrdlg.cpp
//
// @devnote None
//--------------------------------------------------------------------

#define INITGUID

#include "stdafx.h"
#include "GetRows.h"
#include "GetRDlg.h"

const LPCTSTR x_lpcszSource = _T("OLE_DB_NWind_Jet");
const LPCTSTR x_lpcszUser = _T("Admin");				    
const LPCTSTR x_lpcszPassword = _T("");
const LPCTSTR x_lpcszSQL = _T("select EmployeeId, LastName, FirstName from Employees");

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	 //{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetRowsDlg dialog

CGetRowsDlg::CGetRowsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetRowsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetRowsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);		
	m_piConnection = NULL;
	m_piEmpRecordSet = NULL;
	m_strSource = x_lpcszSource;
	m_strUser = x_lpcszUser;
	m_strPassword = x_lpcszPassword;
	m_strSQL = x_lpcszSQL;
}

CGetRowsDlg::~CGetRowsDlg()
{
	if ( m_piConnection != NULL )
		m_piConnection->Release();			 		
	if ( m_piEmpRecordSet != NULL )
		m_piEmpRecordSet->Release();			
	m_piConnection = NULL;
	m_piEmpRecordSet = NULL;
}


void CGetRowsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetRowsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetRowsDlg, CDialog)
	//{{AFX_MSG_MAP(CGetRowsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDD_EXECUTE, OnExecute)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetRowsDlg message handlers

BOOL CGetRowsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGetRowsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGetRowsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGetRowsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CGetRowsDlg::OnExecute() 
{
	BSTR		bstrSource = NULL;
	BSTR		bstrUser = NULL;
	BSTR		bstrPassword = NULL;
	BSTR		bstrSQL = NULL;
	HRESULT		hr;
	COleVariant	vNull;
						
	//Open the database and the recordset	
	if ( m_piConnection == NULL || m_piEmpRecordSet == NULL)
	{
		hr = CoInitialize(NULL);
		if (FAILED(hr))		goto ErrorExit;

		hr = CoCreateInstance(CLSID_CADOConnection, NULL, CLSCTX_INPROC_SERVER, IID_IADOConnection, (LPVOID *)&m_piConnection);
		if (FAILED(hr))		goto ErrorExit;

		bstrSource = m_strSource.AllocSysString();
		bstrUser = m_strUser.AllocSysString();
		bstrPassword = m_strPassword.AllocSysString();
		bstrSQL = m_strSQL.AllocSysString();
		if ( bstrSource == NULL || bstrUser == NULL || bstrSQL == NULL )	
			goto ErrorExit;

		hr = m_piConnection->Open( bstrSource, bstrUser, bstrPassword, adOpenUnspecified /* -1 */ ); 
 		if (FAILED(hr))		goto ErrorExit;


  		hr = CoCreateInstance(CLSID_CADORecordset, NULL, CLSCTX_INPROC_SERVER, IID_IADORecordset, (LPVOID *)&m_piEmpRecordSet);
		if (FAILED(hr))		goto ErrorExit;

		hr = m_piEmpRecordSet->put_Source(bstrSQL);	
		if (FAILED(hr))		goto ErrorExit;

		hr = m_piEmpRecordSet->putref_ActiveConnection(m_piConnection);		
		if (FAILED(hr))		goto ErrorExit;	

		vNull.vt = VT_ERROR;
		vNull.scode = DISP_E_PARAMNOTFOUND;
		hr = m_piEmpRecordSet->Open(vNull, vNull, adOpenKeyset, adLockOptimistic, adCmdUnknown);		
		if (FAILED(hr))		goto ErrorExit;
	}
				
	// Perform the two GetRows functions
	hr = DoGetRows();
 	if (FAILED(hr))		goto ErrorExit;

	// Reset the recordset
	m_piEmpRecordSet->MoveFirst();

	SysFreeString(bstrSource);
	SysFreeString(bstrUser);	 
	SysFreeString(bstrPassword);
	SysFreeString(bstrSQL);
	
	return ;

ErrorExit:
	TCHAR szBuf[256];
	wsprintf(szBuf, _T("Error: %d \n"), hr);
	AfxMessageBox(szBuf);

	SysFreeString(bstrSource);
	SysFreeString(bstrUser);
	SysFreeString(bstrPassword);
	SysFreeString(bstrSQL);
	return ;
}


// Perform standard GetRows against the Employee table
HRESULT CGetRowsDlg::DoGetRows() 
{
	HRESULT			hr;
	COleVariant		vBookmark, rgvFields;
	COleVariant		cRows;
	COleVariant		varField, varNewField;
	CString			strLBRow;
	LONG			lNumOfCol, lNumRecords;
	LONG			lIndex[2];
	CListBox		*pListBox = (CListBox *)GetDlgItem(IDD_GETROWSLIST);

	//Perform GetRows on Employee table

	//Start from the current place		 	
	vBookmark.vt = VT_ERROR;
	vBookmark.scode = DISP_E_PARAMNOTFOUND;	
	
	//Get all columns.   	 	
	rgvFields.vt = VT_ERROR;
	rgvFields.scode = DISP_E_PARAMNOTFOUND;	

	if (!m_piEmpRecordSet)
		return E_NOINTERFACE;

	hr = m_piEmpRecordSet->GetRows(	adGetRowsRest, //MAX_EMP_REC,// non-optional, 
									vBookmark,
									rgvFields,
									&cRows		 
									);
	if (FAILED(hr)) goto ErrorExit;


	//Find out how many records were actually retrieved
	//(SafeArrays are 1-based)
	lNumOfCol = 2;
	SafeArrayGetUBound(cRows.parray, 2, &lNumRecords);

	//Clear the listbox
	pListBox->ResetContent();
	
	for (lIndex[1] = 0; lIndex[1] <= lNumRecords; lIndex[1]++)
	{
		strLBRow.Empty();//Clear the string

		for (lIndex[0] = 0; lIndex[0] <= lNumOfCol; lIndex[0]++)   // get 3 columns
		{
			SafeArrayGetElement(cRows.parray, &lIndex[0], &varField);
			
			hr = VariantChangeType(&varNewField, &varField, 0, VT_BSTR);

			if(hr == S_OK)
			{
				strLBRow += (LPCWSTR)varNewField.bstrVal;
				strLBRow += _T(", ");
			}
			varField.Clear();
			varNewField.Clear();
		}
		pListBox->AddString(strLBRow);
	}

	return hr;

ErrorExit:
	TCHAR szBuf[256];
	wsprintf(szBuf, _T("Error: %d \n"), hr);
	AfxMessageBox(szBuf);

	return hr;
}

