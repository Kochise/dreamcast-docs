// EmpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Emp.h"
#include "EmpDlg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmpDlg dialog

CEmpDlg::CEmpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEmpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEmpDlg)
	m_nEmpNum = 0;
	m_strFirstName = _T("");
	m_strHomePhone = _T("");
	m_strLastName = _T("");
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CEmpDlg::~CEmpDlg()
{	
	if (m_pBiz != NULL)
		delete m_pBiz;
}

void CEmpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEmpDlg)
	DDX_Text(pDX, IDC_EMPNUM, m_nEmpNum);
	DDX_Text(pDX, IDC_FIRSTNAME, m_strFirstName);
	DDX_Text(pDX, IDC_HOMEPHONE, m_strHomePhone);
	DDX_Text(pDX, IDC_LASTNAME, m_strLastName);
	DDX_Text(pDX, IDC_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEmpDlg, CDialog)
	//{{AFX_MSG_MAP(CEmpDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_EDIT_ADD, OnEditAdd)
	ON_BN_CLICKED(ID_EDIT_DELETE, OnEditDelete)
	ON_BN_CLICKED(ID_EDIT_NEXT, OnEditNext)
	ON_BN_CLICKED(ID_EDIT_PREVIOUS, OnEditPrevious)
	ON_BN_CLICKED(ID_EDIT_FIRST, OnEditFirst)
	ON_BN_CLICKED(ID_EDIT_LAST, OnEditLast)
	ON_BN_CLICKED(ID_EDIT_FINDF, OnEditFindF)
	ON_BN_CLICKED(ID_APP_OPEN_RECORD, OnAppOpenRecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmpDlg message handlers

BOOL CEmpDlg::OnInitDialog()
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
								   	
	//Never enable the employee ID
	(GetDlgItem(IDC_EMPNUM))->EnableWindow(FALSE);

	// TODO: Add extra initialization here
	m_pBiz = new CEmpBiz;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEmpDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEmpDlg::OnPaint() 
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

	try 
	{
		m_nEmpNum =  m_pBiz->GetEmployeeId();
		m_strFirstName = m_pBiz->GetFirstName();
		m_strLastName = m_pBiz->GetLastName();
		m_strHomePhone = m_pBiz->GetHomePhone();
		m_strTitle = m_pBiz->GetTitle();
	}
	catch (HRESULT hr)
	{
		MessageBeep(0);
		PopupErrorMessage(hr);
		return ;
	} 

	UpdateData(FALSE); //Invoke Data Exchange (copy member data to form controls)
	return ;
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEmpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CEmpDlg::OnEditAdd() 
{
	// TODO: Add your control notification handler code here
	try
	{
		if(!CommitAlteredEmpRec())
			return;

		m_pBiz->AddRecord();

		OnPaint();
	}
	catch( HRESULT hr )
	{
		MessageBeep(0);
		PopupErrorMessage(hr);
	}
	return ;
}

void CEmpDlg::OnEditDelete() 
{
	// TODO: Add your control notification handler code here
	try
	{
		//Delete method depends on current mode
		m_pBiz->DeleteRecord();
		OnPaint();
	}
	catch( HRESULT hr )
	{
		MessageBeep(0);
		PopupErrorMessage(hr);
	}
	return ;
}

void CEmpDlg::OnEditNext() 
{
	// TODO: Add your control notification handler code here
	if(!CommitAlteredEmpRec()) 
		return;

	try
	{
		if(m_pBiz->MoveNext())
			OnPaint();
		else
			MessageBeep(0);
	}
	catch( HRESULT hr )
	{
		MessageBeep(0);
		PopupErrorMessage(hr);
	}
}

void CEmpDlg::OnEditPrevious() 
{
	// TODO: Add your control notification handler code here
	if(!CommitAlteredEmpRec())
		return;

	try
	{
		if(m_pBiz->MovePrevious())
			OnPaint();
		else
			MessageBeep(0);
	}
	catch( HRESULT hr )
	{
		MessageBeep(0);
		PopupErrorMessage(hr);
	}
}



void CEmpDlg::OnEditFirst() 
{
	// TODO: Add your control notification handler code here
	if(!CommitAlteredEmpRec())
		return;

	try
	{
		if(m_pBiz->MoveFirst())
			OnPaint();
		else
			MessageBeep(0);
	}
	catch( HRESULT hr )
	{
		PopupErrorMessage(hr);
	}
}

void CEmpDlg::OnEditLast() 
{
	// TODO: Add your control notification handler code here
	if(!CommitAlteredEmpRec())
		return;

	try
	{
		if(m_pBiz->MoveLast())
			OnPaint();
		else
			MessageBeep(0);
	}
	catch( HRESULT hr )
	{
		PopupErrorMessage(hr);
	}
}

void CEmpDlg::OnEditFindF() 
{
	try
	{
		if(m_pBiz->FindForward(PrepareCriteria()))
		{
			OnPaint();
		}
		else
		{	//not found.
			MessageBeep(0);
			//.. Should return to the last visited record.
		}
	}
	catch( HRESULT hr )
	{
		MessageBeep(0);
		PopupErrorMessage(hr);
	}
}


BOOL CEmpDlg::CommitAlteredEmpRec()
{
	CString			strOldFirstName, strOldHomePhone, strOldLastName, strOldTitle;
	COleVariant		vFirstName, vHomePhone, vLastName, vTitle, vID;

	if (!m_pBiz->m_fConnected)
		return FALSE;

	//Get current record string values
	try
	{
		strOldFirstName = m_pBiz->GetFirstName();
		strOldLastName = m_pBiz->GetLastName();
		strOldHomePhone = m_pBiz->GetHomePhone();
		strOldTitle = m_pBiz->GetTitle();

		//Force DDX to update member values
		if(!UpdateData())
			return FALSE;

		// Did any fields change value?
		if(
		(m_strFirstName	== strOldFirstName	) &&
		(m_strHomePhone	== strOldHomePhone	) &&
		(m_strLastName	== strOldLastName	) &&
		(m_strTitle		== strOldTitle		) && !m_pBiz->IsAddMode() )
			return TRUE;

		//Save it, dump it or stay on it?
		switch (AfxMessageBox(IDS_PROMPT_COMMIT_EMPREC, MB_YESNOCANCEL))
		{
				case IDYES:
				{
						m_pBiz->UpdateEmpRec(m_strFirstName,
											m_strHomePhone,
											m_strLastName,
											m_strTitle);

					return TRUE;
				}

				case IDNO:
				case IDCANCEL:
				{
					if (m_pBiz->IsAddMode())
						m_pBiz->CancelPendingAdd();
					return TRUE;
				}

				default:
				{
					GetDlgItem(IDC_EMPNUM)->SetFocus();
					return TRUE;
				}
		}
	}
	catch (CMemoryException &memx)
	{
		TCHAR szBuf[256];
		memx.GetErrorMessage(szBuf, sizeof(szBuf), NULL);
		AfxMessageBox(szBuf);
		return FALSE;
	}
	catch(HRESULT hr)
	{
		PopupErrorMessage(hr);
		return FALSE;
	}

	return TRUE;
}

  
							 

CString CEmpDlg::PrepareCriteria()
{
	CString			strCriteria = "";

	//Force DDX to update member values
	if(!UpdateData())
		return strCriteria;

	if(m_strFirstName != "")
		strCriteria = "FirstName = '" + m_strFirstName +"'";
	if(m_strLastName != "")
		strCriteria = strCriteria + ( strCriteria == "" ? "":" AND ") + "LastName = '" + m_strLastName +"'";
	if(m_strHomePhone != "")
		strCriteria = strCriteria + ( strCriteria == "" ? "":" AND ") + "HomePhone = '" + m_strHomePhone +"'";
	if(m_strTitle != "")
		strCriteria = strCriteria + ( strCriteria == "" ? "":" AND ") + "Title = '" + m_strTitle +"'";

	return strCriteria;
}




void CEmpDlg::OnAppOpenRecord() 
{
	// TODO: Add your control notification handler code here

	//Connect to the EMPLOYEE database
	if(!m_pBiz->ConnectToDatabase())
	{
		m_pBiz->m_fConnected = FALSE;
		return;
	}

	m_pBiz->m_fConnected = TRUE;

	GetDlgItem(ID_EDIT_PREVIOUS)->EnableWindow(TRUE);
	GetDlgItem(ID_EDIT_NEXT)->EnableWindow(TRUE);
	GetDlgItem(ID_EDIT_DELETE)->EnableWindow(TRUE);
	GetDlgItem(ID_EDIT_ADD)->EnableWindow(TRUE);
	GetDlgItem(ID_EDIT_LAST)->EnableWindow(TRUE);
	GetDlgItem(ID_EDIT_FIRST)->EnableWindow(TRUE);
	GetDlgItem(ID_EDIT_FINDF)->EnableWindow(TRUE);
	
	OnPaint();
}
