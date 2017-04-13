//--------------------------------------------------------------------
// Microsoft ADO Samples
//
// (c) 1996 Microsoft Corporation.  All Rights Reserved.
//
// @doc ADORead Sample
//
// @module	ADOrddlg.cpp
//
// @devnote None
//--------------------------------------------------------------------

// ADOReadDlg.cpp : implementation file
//
#define INITGUID
#include "stdafx.h"
#include "ADORead.h"
#include "ADORdDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const LPCTSTR x_lpcszSource = _T("OLE_DB_NWind_Jet;");
const LPCTSTR x_lpcszUser = _T("Admin");

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

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADOReadDlg dialog

CADOReadDlg::CADOReadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CADOReadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CADOReadDlg)
	m_lCacheSize = 100;
	m_strTableQuery = _T("SELECT EmployeeId, LastName, FirstName FROM Employees");
	m_lNumRows = 10;
	m_bDynamic = TRUE;
	m_bKeyset = TRUE;
	m_bStatic = TRUE;
	m_bForwardOnly = TRUE;
	m_strSource = x_lpcszSource; //.. D:\\samples\\Employee.mdb
	m_strProvider = _T("msdasql");
	m_strUser = x_lpcszUser;
	m_lConnectMode  = adModeRead;		
	m_lConnectOption  = adPromptAlways;
//	m_bReadOnly = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_comboBoxOption.Create(CBS_DROPDOWN | CBS_SORT | WS_VSCROLL | WS_GROUP | WS_TABSTOP| WS_CHILD | WS_VISIBLE, 
							CRect(261,7,94,12), this, IDC_ConnectOption);
	m_piConnection = NULL;
}
  
CADOReadDlg::~CADOReadDlg()
{
	if ( m_piConnection != NULL )
		m_piConnection->Release();			 		
	m_piConnection = NULL;
}
                 
void CADOReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CADOReadDlg)
	DDX_Control(pDX, IDC_ConnectMode, m_comboBoxMode);		
	DDX_Control(pDX, IDC_ConnectOption, m_comboBoxOption);
	DDX_Text(pDX, IDC_CACHESIZE, m_lCacheSize);
	DDV_MinMaxLong(pDX, m_lCacheSize, 0, 1200);
	DDX_Text(pDX, IDC_TABLEQUERYEDIT, m_strTableQuery);
	DDX_Text(pDX, IDC_NUMROWS, m_lNumRows);
	DDV_MinMaxLong(pDX, m_lNumRows, 1, 32000);
	DDX_Check(pDX, IDC_Dynamic, m_bDynamic);
	DDX_Check(pDX, IDC_Keyset, m_bKeyset);
	DDX_Check(pDX, IDC_StaticCursor, m_bStatic);
	DDX_Check(pDX, IDC_FORWARDONLY, m_bForwardOnly);
	DDX_Text(pDX, IDC_Source, m_strSource);
	DDV_MaxChars(pDX, m_strSource, 256);
	DDX_Text(pDX, IDC_PROVIDER, m_strProvider);
	DDV_MaxChars(pDX, m_strProvider, 256);
	DDX_Text(pDX, IDC_User, m_strUser);
	DDV_MaxChars(pDX, m_strUser, 256);
	//}}AFX_DATA_MAP

	//Do the manual checks

	//Check the database name parameter
	if(pDX->m_bSaveAndValidate)
	{
		pDX->PrepareEditCtrl(IDC_Source);
		if (m_strSource.IsEmpty()) 
		{
			MessageBox(_T("Missing Jet database name."), _T("ADO Test App Error"), MB_ICONEXCLAMATION );
			pDX->Fail();
		}
	}


	//Check the Table/Query parameter
	if(pDX->m_bSaveAndValidate)
	{
		pDX->PrepareEditCtrl(IDC_TABLEQUERYEDIT);
		if (m_strTableQuery.IsEmpty()) 
		{
			MessageBox(_T("Missing table,query or SQL."), _T("ADO Test App Error"), MB_ICONEXCLAMATION );
			pDX->Fail();
		}
	}
}

BEGIN_MESSAGE_MAP(CADOReadDlg, CDialog)
	//{{AFX_MSG_MAP(CADOReadDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DATABASEBUTTON, OnDatabase)
	ON_BN_CLICKED(ID_EXECUTE, OnExecute)
	ON_CBN_SELCHANGE(IDC_ConnectMode, OnSelchangeConnectMode)
	ON_CBN_SELCHANGE(IDC_ConnectOption, OnSelchangeConnectOption)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADOReadDlg message handlers

BOOL CADOReadDlg::OnInitDialog()
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
	

	//Set default selections
	SetDlgItemText(IDC_CACHESIZE, _T("100"));
	SetDlgItemText(IDC_NUMROWS, _T("10"));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CADOReadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CADOReadDlg::OnPaint() 
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
HCURSOR CADOReadDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CADOReadDlg::OnDatabase() 
{
	CFileDialog*	pcBrowse;	//Need a file open dialog

	pcBrowse = (CFileDialog*)new CFileDialog(TRUE,_T("mdb"),NULL,NULL,_T("Jet Database Files | *.mdb ||"), NULL)	;

	pcBrowse->DoModal();

	(GetDlgItem(IDC_Source))->SetWindowText(pcBrowse->GetPathName());

	delete pcBrowse;
}



void CADOReadDlg::Execute(	
			CursorTypeEnum	cursorType,
			int				iControlID,
			int				iUnitsID
			) 
{
	ADORecordset	*piRecordSet;	
	DWORD			dwStart, dwEnd;
	DWORD			dwDuration;
	LONG			lIndex;
	COleVariant		dbVar;
	COleVariant		vNull;
	HRESULT			hr;
	BSTR			bstrTableQuery;
	VARIANT_BOOL	vbEOF;

	dwStart = timeGetTime();

	//Open recordset 
	hr = CoCreateInstance(CLSID_CADORecordset, NULL, CLSCTX_INPROC_SERVER, IID_IADORecordset, (LPVOID *)&piRecordSet);
	if (FAILED(hr))		goto ErrorExit;

	//Check that recordset was created
	if (piRecordSet != NULL)
	{
		bstrTableQuery = m_strTableQuery.AllocSysString();
		hr = piRecordSet->put_Source(bstrTableQuery);		// convert to bstr 
		if (FAILED(hr))		goto ErrorExit;

		hr = piRecordSet->putref_ActiveConnection(m_piConnection);		
		if (FAILED(hr))		goto ErrorExit;

		//Set the cache size to value supplied by user.
		hr = piRecordSet->put_CacheSize(m_lCacheSize);
		if (FAILED(hr))		goto ErrorExit;
						
		vNull.vt = VT_ERROR;
		vNull.scode = DISP_E_PARAMNOTFOUND;
		hr = piRecordSet->Open(vNull, vNull, cursorType, adLockOptimistic, adCmdUnknown);
		if (FAILED(hr))		goto ErrorExit;

		//Watch for end of record set
		piRecordSet->get_EOF(&vbEOF);
		if (FAILED(hr))		goto ErrorExit;

		for (lIndex = 0L; !vbEOF && lIndex < m_lNumRows; lIndex++)
		{
			//Get the first returned column
			hr = piRecordSet->get_Collect(COleVariant(0L, VT_I4), &dbVar);
			if (FAILED(hr))		goto ErrorExit;

			AddFieldToList(lIndex, &dbVar);
			hr = piRecordSet->MoveNext();
			if (FAILED(hr))		goto ErrorExit;
			piRecordSet->get_EOF(&vbEOF);
			if (FAILED(hr))		goto ErrorExit;
			//			dbVar.Clear();	// release memory
		}

		//Report the estimated execute time (in milliseconds)
		dwEnd = timeGetTime();
		dwDuration = dwEnd - dwStart;
		DisplayQueryTime(iControlID, iUnitsID, dwDuration);
	}
	else
	{
		(GetDlgItem(IDC_DynamicTIME))->SetWindowText(_T("ERROR"));
	}
	
	piRecordSet->Release();
	SysFreeString(bstrTableQuery);
	return ;

 ErrorExit:
	TCHAR szBuf[256];
	wsprintf(szBuf, _T("Error: %d \n"), hr);
	AfxMessageBox(szBuf);

	piRecordSet->Release();
	SysFreeString(bstrTableQuery);
	return ;
}		


//When the Execute button is pressed, run through the selected methods and perform each
//reporting an approximate execution time and listing the first field returned (only if
//it's a string or numeric)

void CADOReadDlg::OnExecute() 
{
	CListBox	*pList = ((CListBox *)(GetDlgItem(IDC_ROWSLIST)));
	HRESULT		hr;
	BSTR		bstrSource;
	BSTR		bstrUser;
	BSTR		bstrProvider;
	CString		strSource, strUser,	strPassword, strProvider;
	static BOOLEAN		fIsFirstTime = TRUE;

	//Update the parameters
	if (!UpdateData(TRUE))
	{
		return;
	}

	// This could take a while, 
	CWaitCursor wait;

	//Clear the list
	pList->ResetContent();

	// Following is a series of database table retrieves using variations
	// on the Recordset object. This isn't a great programming structure,
	// but it shows each method clearly.
	
	//Execute each the requested read methods, recording a time for each
	//Open the database
	if ( m_piConnection == NULL )
	{
		hr = CoInitialize(NULL);
		if (FAILED(hr))		goto ErrorExit;
		hr = CoCreateInstance(CLSID_CADOConnection, NULL, CLSCTX_INPROC_SERVER, IID_IADOConnection, (LPVOID *)&m_piConnection);
		if (FAILED(hr))		goto ErrorExit;
	}		

	(GetDlgItem(IDC_Source))->GetWindowText(strSource);  	
	(GetDlgItem(IDC_User))->GetWindowText(strUser);	   	
	(GetDlgItem(IDC_Password))->GetWindowText(strPassword);
	(GetDlgItem(IDC_PROVIDER))->GetWindowText(strProvider);

	if ( fIsFirstTime || m_strSource != strSource  || m_strUser != strUser	|| 
				m_strPassword != strPassword || m_strProvider != strProvider )
	{
		fIsFirstTime = FALSE;
		m_strSource = strSource ;
		m_strUser = strUser; 
		m_strPassword = strPassword ;
		m_strProvider = strProvider;

		bstrSource = m_strSource.AllocSysString();
		bstrUser = m_strUser.AllocSysString();
		bstrProvider = m_strProvider.AllocSysString();
		if ( bstrProvider == NULL || bstrSource == NULL || bstrUser == NULL)	goto ErrorExit;			 

		if (FAILED(hr = m_piConnection->put_Provider(bstrProvider)))
			goto ErrorExit;

		hr = m_piConnection->Open( bstrSource, bstrUser, NULL, -1 );  //toaddpassword
 		if (FAILED(hr))		goto ErrorExit;

		SysFreeString(bstrProvider);
		SysFreeString(bstrSource);
		SysFreeString(bstrUser);
	}

	//Open recordset on as a Dynamic
	if(m_bDynamic)
	{
		pList->AddString(_T("Dynamic Cursor"));
		pList->AddString(_T("=========================="));
		Execute( adOpenDynamic, IDC_DynamicTIME, IDC_UNITDynamic );
	}
	//Open recordset on as a Keyset
	if(m_bKeyset)
	{
		pList->AddString(_T("Keyset Cursor"));
		pList->AddString(_T("=========================="));
		Execute( adOpenKeyset, IDC_KeysetTIME, IDC_UNITDYNA );
	}
	//Open recordset on as a Static
	if(m_bStatic)
	{
		pList->AddString(_T("Static Cursor"));
		pList->AddString(_T("=========================="));
		Execute( adOpenStatic, IDC_StaticTIME, IDC_UNITSNAP );
	}
	//Open recordset on as ForwardOnly
	if(m_bForwardOnly)
	{
		pList->AddString(_T("ForwardOnly Cursor"));
		pList->AddString(_T("=========================="));
		Execute( adOpenForwardOnly, IDC_FORWARDONLYTIME, IDC_UNITFORWARDONLY );
	} 
	
	return ;

 ErrorExit:
	TCHAR szBuf[256];
	wsprintf(szBuf, _T("Error: %d \n"), hr);
	AfxMessageBox(szBuf);

	SysFreeString(bstrProvider);
	SysFreeString(bstrSource);
	SysFreeString(bstrUser);
	return ;

}


/////////////////////////////////////////////////////////////////////////////
// Other functions

void CADOReadDlg::DisplayQueryTime(int iControlID, int iUnitsID, DWORD dwDuration)
{
	CString strDisp;
	CString strUnits(_T("ms"));
	double	fDuration = dwDuration;
	
	//Did it go into minutes?
	if(fDuration >= 60000.0)
	{
		fDuration = fDuration/60000.0;
		strUnits = _T("M");
	}
	//Did it go to seconds?
	else if(fDuration >= 1000.0)
	{
		fDuration = fDuration/1000.0;
		strUnits = _T("S");
	}

	strDisp.Format(_T("%.2f"), fDuration);

	(GetDlgItem(iUnitsID))->SetWindowText(strUnits);
	(GetDlgItem(iControlID))->SetWindowText(strDisp);

}

void CADOReadDlg::AddFieldToList(LONG lRecordNum, COleVariant *pdbVar)
{
	CString		strDisp;
	CString		strScratch;
	CListBox	*pList = ((CListBox *)(GetDlgItem(IDC_ROWSLIST)));

	//Add record number
	strDisp.Format(_T("%d - "), lRecordNum);
	
	//NOTE: This only works for strings/numerics
	
	switch(pdbVar->vt)
	{
		case VT_BSTR:
		{
			strDisp += (LPCTSTR)pdbVar->bstrVal;
			break;
		}

		case VT_I4:
		{
			strScratch.Format(_T("%d"), pdbVar->lVal);
			strDisp += strScratch;
			break;
		}

		case VT_UI1:
		{
			strScratch.Format(_T("%u"), pdbVar->bVal);
			strDisp += strScratch;
			break;
		}

		case VT_I2:
		{
			strScratch.Format(_T("%d"), pdbVar->iVal);
			strDisp += strScratch;
			break;
		}

		case VT_R4:
		{
			strScratch.Format(_T("%f"), pdbVar->fltVal);
			strDisp += strScratch;
			break;
		}

		case VT_R8 :
		{
			strScratch.Format(_T("%f"), pdbVar->dblVal);
			strDisp += strScratch;
			break;
		}

		default: //
		{
			strDisp += _T("Field type not supported by sample code");
		}

	}
	pList->AddString(strDisp);

}

ConnectPromptEnum rgConnectPrompts[] = {adPromptAlways,
										adPromptComplete,
										adPromptCompleteRequired,
										adPromptNever};

void CADOReadDlg::OnSelchangeConnectOption() 
{
	m_lConnectOption = rgConnectPrompts[m_comboBoxOption.GetCurSel()];
}

ConnectModeEnum rgConnectModes[] = {adModeRead, 
									adModeWrite, 
									adModeReadWrite, 
									adModeShareDenyRead,
									adModeShareDenyWrite,
									adModeShareExclusive,
									adModeShareDenyNone};

void CADOReadDlg::OnSelchangeConnectMode() 
{

	m_lConnectMode = rgConnectModes[m_comboBoxMode.GetCurSel()];
}
