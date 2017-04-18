// AdvancedFTPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AdvancedFTP.h"
#include "AdvancedFTPDlg.h"

#define xTRACEMODE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DIRECTORYLABEL			"<DIR>"
#define SITECONNECTION_TIMEOUT	5000
#define FTPCONNECTION_TIMEOUT	5000
#define REQUEST_TIMEOUT			10000
#define STATUS_CALLBACK_TIMEOUT	2000
#define LV_COL_FILE				0
#define LV_COL_ATTR				1
#define LV_COL_SIZE				2
#define LV_COL_DATE				3
#define LV_COL_STATUS			1

enum
	{
	SHOWSTATUS_EXIT,
	SHOWSTATUS_DISPLAYMSG
	};

struct SHAREDDATA
	{
	char cSite[_MAX_PATH];
	char cUsername[_MAX_PATH];
	char cPassword[_MAX_PATH];
	HINTERNET hInternetConnection;
	HINTERNET hFTPSession;
	HINTERNET hResultHandle;
	HANDLE hHandleCreatedEvent;
	HANDLE hUpdateStatusSignal;
	HANDLE hExitSiteConnectionThread;
	HANDLE hRequestCompleted;
	HWND hSendStatusToHwnd;
	int iStatusType;
	HANDLE hStatusText;
	LPSTR pStatusText;
	CRITICAL_SECTION * Status_Critical_Section;
	int iUniqueID;
	} Shared_Data;

VOID CALLBACK InternetCallback (HINTERNET hInternet, DWORD dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength);
UINT CALLBACK CallbackThread_Proc(LPVOID lParm);
UINT CALLBACK StatusThread_Proc(LPVOID lParm);
UINT CALLBACK SiteConnectThread_Proc(LPVOID lParm);
void ShowStatus(SHAREDDATA * pData, LPSTR pStatus);
void ShowStatus(SHAREDDATA * pData, CString Status);



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
// CAdvancedFTPDlg dialog

CAdvancedFTPDlg::CAdvancedFTPDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdvancedFTPDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdvancedFTPDlg)
	m_DownloadDirectory = _T("");
	m_FTPSite = _T("");
	m_Password = _T("");
	m_Username = _T("");
	m_ProxyServer = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdvancedFTPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdvancedFTPDlg)
	DDX_Control(pDX, IDC_TOTALPROGRESS, m_TotalProgress);
	DDX_Control(pDX, IDC_FTPLISTNG, m_FTPList);
	DDX_Control(pDX, IDC_DOWNLOADLISTING, m_DownloadList);
	DDX_Text(pDX, IDC_DOWNLOADDIR, m_DownloadDirectory);
	DDX_Text(pDX, IDC_FTPSITE, m_FTPSite);
	DDX_Text(pDX, IDC_PASSWORD, m_Password);
	DDX_Text(pDX, IDC_USERNAME, m_Username);
	DDX_Text(pDX, IDC_PROXYSERVER, m_ProxyServer);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAdvancedFTPDlg, CDialog)
	//{{AFX_MSG_MAP(CAdvancedFTPDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADDALL, OnAddall)
	ON_BN_CLICKED(ID_HELP, OnHelp)
	ON_BN_CLICKED(IDC_ADDSELECTED, OnAddselected)
	ON_BN_CLICKED(IDC_BROWSEDIR, OnBrowsedir)
	ON_BN_CLICKED(IDC_DOWNLOAD, OnDownload)
	ON_BN_CLICKED(IDC_GETDIRECTORYLISTING, OnGetdirectorylisting)
	ON_BN_CLICKED(IDC_REMOVEALL, OnRemoveall)
	ON_BN_CLICKED(IDC_REMOVESELECTED, OnRemoveselected)
	ON_BN_CLICKED(IDC_CANCELOPERATION, OnCanceloperation)
	ON_NOTIFY(NM_DBLCLK, IDC_FTPLISTNG, OnDblclkFtplistng)
	ON_BN_CLICKED(IDC_SITECONNECT, OnSiteconnect)
	ON_BN_CLICKED(IDC_SITEDISCONNECT, OnSitedisconnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvancedFTPDlg message handlers

BOOL CAdvancedFTPDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	int iWidth;
	RECT Rect;
	CString Msg;

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

	// Initialize edit vars
	m_FTPSite = "ftp.microsoft.com";
	m_Username = "anonymous";
	m_Password = "anonymous@microsoft.com";
	m_ProxyServer = "ftp-gw";
	m_DownloadDirectory = "c:\\ftp";

	// set up list view columns
	iWidth = m_FTPList.GetStringWidth(" XXXXXXXXXXXXXXXX ");
	m_FTPList.InsertColumn(LV_COL_FILE, "Filename", LVCFMT_LEFT, iWidth, -1);
	m_DownloadList.InsertColumn(LV_COL_FILE, "Filename", LVCFMT_LEFT, iWidth, -1);
	iWidth = m_DownloadList.GetStringWidth(" XXXXXXXXXX ");
	m_FTPList.InsertColumn(LV_COL_ATTR, "Attributes", LVCFMT_CENTER, iWidth, -1);
	m_DownloadList.InsertColumn(LV_COL_STATUS, "Status", LVCFMT_CENTER, iWidth, -1);
	iWidth = m_DownloadList.GetStringWidth(" XXXXXXXXX ");
	m_FTPList.InsertColumn(LV_COL_SIZE, "Size", LVCFMT_RIGHT, iWidth, -1);
	m_DownloadList.InsertColumn(LV_COL_SIZE, "Size", LVCFMT_RIGHT, iWidth, -1);

	// initialize other vars
	hWaitForHandleCreation = ::CreateEvent(NULL, TRUE, TRUE, NULL);
	Shared_Data.hUpdateStatusSignal = ::CreateEvent(NULL, FALSE, TRUE, NULL);
	Shared_Data.hExitSiteConnectionThread = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	Shared_Data.hRequestCompleted = ::CreateEvent(NULL, TRUE, TRUE, NULL);

	Shared_Data.hStatusText = ::GlobalAlloc(GHND, 255);
	Shared_Data.pStatusText = (LPSTR)::GlobalLock(Shared_Data.hStatusText);
	Shared_Data.iStatusType = SHOWSTATUS_DISPLAYMSG;
	Shared_Data.Status_Critical_Section = new CRITICAL_SECTION;
	::InitializeCriticalSection(Shared_Data.Status_Critical_Section);

	//Create susupended threads
#ifndef TRACEMODE
	SetupWorkerThreads();
#endif // #ifndef TRACEMODE	

	// create status bar
	GetWindowRect(&Rect);
	Rect.top = Rect.bottom - 32;
	StatusBar.Create(WS_CHILD | WS_VISIBLE | CCS_BOTTOM, Rect, this, IDS_STATUSBARID);
	m_hStatusBarCtrl = StatusBar.m_hWnd;
	Shared_Data.hSendStatusToHwnd = StatusBar.m_hWnd;

	// make connection to internet
	ShowStatus(&Shared_Data, "Connecting to Internet");
	if (ConnectToInternet())
		{
		Msg = "Connected to Internet";
		}
	else
		{
		Msg = "Could not make initial Internet connection";
		}
	ShowStatus(&Shared_Data, Msg);

	// set up initial ui
	GetDlgItem(IDC_SITECONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SITEDISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_GETDIRECTORYLISTING)->EnableWindow(FALSE);
	GetDlgItem(IDC_ADDALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_ADDSELECTED)->EnableWindow(FALSE);
	GetDlgItem(IDC_REMOVESELECTED)->EnableWindow(FALSE);
	GetDlgItem(IDC_REMOVEALL)->EnableWindow(FALSE);
	GetDlgItem(IDC_DOWNLOAD)->EnableWindow(FALSE);

	// update display control
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAdvancedFTPDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAdvancedFTPDlg::OnDestroy()
{
	// close internet connection
	CloseInternetConnection();

	// release events
	if (hWaitForHandleCreation != (HANDLE)NULL)
		{
		::CloseHandle(hWaitForHandleCreation);
		}

	if (Shared_Data.hUpdateStatusSignal != (HANDLE)NULL)
		{
		::CloseHandle(Shared_Data.hUpdateStatusSignal);
		}

	if (Shared_Data.hExitSiteConnectionThread != (HANDLE)NULL)
		{
		::CloseHandle(Shared_Data.hExitSiteConnectionThread);
		}

	if (Shared_Data.hRequestCompleted != (HANDLE)NULL)
		{
		::CloseHandle(Shared_Data.hRequestCompleted);
		}

	// tell other threads to exit
	Shared_Data.iStatusType = SHOWSTATUS_EXIT;
	::SetEvent(Shared_Data.hUpdateStatusSignal);
	::SetEvent(Shared_Data.hExitSiteConnectionThread);

	// release other resources
	::GlobalUnlock(Shared_Data.hStatusText);
	::GlobalFree(Shared_Data.hStatusText);
	::DeleteCriticalSection(Shared_Data.Status_Critical_Section);
	delete Shared_Data.Status_Critical_Section;

	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAdvancedFTPDlg::OnPaint() 
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
HCURSOR CAdvancedFTPDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAdvancedFTPDlg::OnHelp() 
{
	// TODO: Add your control notification handler code here
	
}

void CAdvancedFTPDlg::OnBrowsedir() 
{
	// TODO: Add your control notification handler code here
	
}

void CAdvancedFTPDlg::OnDownload() 
	{
	int i;
	CString InputSpec;
	CString OutputSpec;
	CString Label;

	// update vars from user data
	UpdateData(TRUE);

	// set up progress controls
	i = m_DownloadList.GetItemCount();
	m_TotalProgress.SetRange(0, i);
	m_TotalProgress.SetStep(1);

	// get index to first file to download
	i = m_DownloadList.GetNextItem(-1, LVNI_ALL);

	// while more files to download
	Shared_Data.iUniqueID = 1;
	while (i != -1)
		{
		// get name of file and create full spec with site name
		Label = m_DownloadList.GetItemText(i, LV_COL_FILE);
		//InputSpec.Format("ftp://%s/%s", m_FTPSite, Label);
		InputSpec.Format("%s", Label);
		OutputSpec.Format("%s\\%s", m_DownloadDirectory, Label);

		// download file
		Label.Format("start download of %s\n", OutputSpec);
		::OutputDebugString(Label);
		DownloadFile(Shared_Data.hFTPSession, InputSpec, OutputSpec, (DWORD)&Shared_Data);
		Label.Format("end download of %s\n", OutputSpec);
		::OutputDebugString(Label);

		// update display
		m_TotalProgress.StepIt();
		m_DownloadList.SetItemText(i, LV_COL_STATUS, "Done");
		UpdateData(FALSE);
		Shared_Data.iUniqueID++;

		// get next file to download
		i = m_DownloadList.GetNextItem(i, LVNI_ALL);
		}
	}

void CAdvancedFTPDlg::OnGetdirectorylisting() 
{
	// enumerate directory
	EnumerateDirectory();

	// enable controls
	GetDlgItem(IDC_ADDALL)->EnableWindow(TRUE);
	GetDlgItem(IDC_ADDSELECTED)->EnableWindow(TRUE);
	GetDlgItem(IDC_REMOVESELECTED)->EnableWindow(TRUE);
	GetDlgItem(IDC_REMOVEALL)->EnableWindow(TRUE);
	GetDlgItem(IDC_DOWNLOAD)->EnableWindow(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// Start of List Control routines
/////////////////////////////////////////////////////////////////////////////
void CAdvancedFTPDlg::OnAddall() 
{
	CString Msg;

	// transfer all files from FTP listing to download listing
	TransferLines(&m_DownloadList, &m_FTPList, 0);

	// display status
	Msg.Format("%d files added.", m_DownloadList.GetItemCount());
	ShowStatus(&Shared_Data, Msg);
	return;
}

void CAdvancedFTPDlg::OnAddselected() 
{
	CString Msg;

	// transfer only selected files from FTP listing to download listing
	TransferLines(&m_DownloadList, &m_FTPList, LVNI_SELECTED);

	// display status
	Msg.Format("%d files added.", m_DownloadList.GetItemCount());
	ShowStatus(&Shared_Data, Msg);
	return;
}

void CAdvancedFTPDlg::OnRemoveall() 
{
	CString Msg;

	// transfer all files from download listing to FTP listing
	TransferLines(&m_FTPList, &m_DownloadList, 0);

	// display status
	Msg.Format("%d files removed.", m_DownloadList.GetItemCount());
	ShowStatus(&Shared_Data, Msg);
	return;
}

void CAdvancedFTPDlg::OnRemoveselected() 
{
	CString Msg;

	// transfer only selected files from download listing to FTP listing
	TransferLines(&m_FTPList, &m_DownloadList, LVNI_SELECTED);

	// display status
	Msg.Format("%d files removed.", m_DownloadList.GetItemCount());
	ShowStatus(&Shared_Data, Msg);
	return;
}

void CAdvancedFTPDlg::TransferLines(CListCtrl * pListCtrlTo, CListCtrl * pListCtrlFrom, int iFlags)
	{
	int i;
	int iLineCount = 0;
	CString Label;
	int iStartAt = -1;
	
	// get index to first file to transfer
	i = pListCtrlFrom->GetNextItem(iStartAt, LVNI_ALL | iFlags);

	// while more files to transfer
	while (i != -1)
		{
		// we don't transfer directories
		Label = pListCtrlFrom->GetItemText(i, LV_COL_ATTR);
		if (Label != DIRECTORYLABEL)
			{
			// transfer specific file
			CopyListCtrlLine(pListCtrlTo, iLineCount++, pListCtrlFrom, i, TRUE);
			}
		else
			{
			pListCtrlFrom->SetItemState(i, 0, LVNI_SELECTED);
			if (iFlags != LVNI_SELECTED)
				{
				iStartAt = i;
				}
			}

		// get index to next file
		i = pListCtrlFrom->GetNextItem(iStartAt, LVNI_ALL | iFlags);
		}

	return;
	}

BOOL CAdvancedFTPDlg::CopyListCtrlLine(CListCtrl * pListCtrlTo, int iToLine, CListCtrl * pListCtrlFrom, int iFromLine, BOOL bDelete)
	{
	CString Label;
	int iResult;

	// get name of file to copy from src control
	Label = pListCtrlFrom->GetItemText(iFromLine, LV_COL_FILE);

	// create new line in dest control
	iResult = pListCtrlTo->InsertItem(iToLine, Label);

	// get other file info from src and copy into new dest line
	Label = pListCtrlFrom->GetItemText(iFromLine, LV_COL_ATTR);
	pListCtrlTo->SetItemText(iResult, LV_COL_ATTR, Label);
	Label = pListCtrlFrom->GetItemText(iFromLine, LV_COL_SIZE);
	pListCtrlTo->SetItemText(iResult, LV_COL_SIZE, Label);

	// delete src line if requested
	if (bDelete)
		{
		pListCtrlFrom->DeleteItem(iFromLine);
		}

	return(TRUE);
	}

/////////////////////////////////////////////////////////////////////////////
// End of List Control routines
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Start of Message/Status routines
/////////////////////////////////////////////////////////////////////////////
void ShowStatus(SHAREDDATA * pData, LPSTR pStatus)
	{
	CString Msg = pStatus;
	::EnterCriticalSection(pData->Status_Critical_Section);
	::OutputDebugString(Msg + "\n");
	strcpy(pData->pStatusText, pStatus);
	::PulseEvent(pData->hUpdateStatusSignal);
	::LeaveCriticalSection(pData->Status_Critical_Section);
	}

void ShowStatus(SHAREDDATA * pData, CString Status)
	{
	// show status text
	ShowStatus(pData, Status.GetBuffer(Status.GetLength()));
	}

/////////////////////////////////////////////////////////////////////////////
// End of Message/Status routines
/////////////////////////////////////////////////////////////////////////////


//**********************************************************************
// CAdvancedFTPDlg::InternetCallback
//
// Purpose: Internet callback function used during asynchronous calls
//          to Wininet
// Parameters:
//    HINTERNET hInternet - Upon first entry into the callback (during
//    the INTERNET_STATUS_HANDLE_CREATED status this value contains the
//    handle passed in on the original call to the asynchronous Wininet
//    API.  Upon INTERNET_STATUS_HANDLE_CREATED this value contains 
//    the return value of the asynchronous Wininet API
//
//    DWORD dwContext - an application defined value to associated with
//    the callback.  For this application this is a pointer to an
//    instanct of a CAdvancedFTPDlg class (this)
//
//    DWORD dwInternetStatus - status value (INTERNET_STATUS_*)
//
//    LPVOID lpvStatusInformation - value returned by callback function
//    specific to the STATUS type
//
//    DWORD dwStatusInformationLength
//********************************************************************
void CALLBACK InternetCallback (HINTERNET hInternet, DWORD dwContext, DWORD dwInternetStatus, LPVOID lpvStatusInformation, DWORD dwStatusInformationLength)
	{
	CString Msg;
	SHAREDDATA * Data = (SHAREDDATA *)dwContext;
	LPINTERNET_ASYNC_RESULT piar = (LPINTERNET_ASYNC_RESULT)(lpvStatusInformation);
	LPSTR pStr = (LPSTR)(lpvStatusInformation);

	// show full debugging info
	Msg.Format("h = %ld(%x), s = %ld(%x), v = %ld(%x), l = %ld(%x)", 
			hInternet,
			hInternet,
			dwInternetStatus,
			dwInternetStatus,
			lpvStatusInformation,
			lpvStatusInformation,
			dwStatusInformationLength,
			dwStatusInformationLength);
	::OutputDebugString(Msg + "\n");
	ShowStatus(Data, Msg);

	// act upon status code
	switch(dwInternetStatus)
		{
		// Looking up the IP address of the name contained in lpvStatusInformation. 
		case INTERNET_STATUS_RESOLVING_NAME:
			Msg.Format("Resolving %s ...", pStr);
			ShowStatus(Data, Msg);
			break;

		// Successfully found the IP address of the name contained in
		// lpvStatusInformation. 
		case INTERNET_STATUS_NAME_RESOLVED:
			Msg.Format("Resolved %s ...", pStr);
			ShowStatus(Data, Msg);
			break;

		// Connecting to the socket address (SOCKADDR) pointed to by
		// lpvStatusInformation. 
		case INTERNET_STATUS_CONNECTING_TO_SERVER:
			Msg.Format("Connecting to Server %s...", pStr);
			ShowStatus(Data, Msg);
			break;

		// Successfully connected to the socket address (SOCKADDR) pointed to by
		// lpvStatusInformation. 
		case INTERNET_STATUS_CONNECTED_TO_SERVER:
			Msg.Format("Connected to %s ...", pStr);
			ShowStatus(Data, Msg);
			break;

		// Sending the information request to the server. The lpvStatusInformation
		// parameter is NULL. 
		case INTERNET_STATUS_SENDING_REQUEST:
			Msg = "Sending request ";
			ShowStatus(Data, Msg);
			break;

		// Successfully sent the information request to the server. The
		// lpvStatusInformation parameter is NULL. 
		case INTERNET_STATUS_REQUEST_SENT:
			Msg.Format("Sent Request (result = %ld, error = %ld)", piar->dwResult, piar->dwError);
			ShowStatus(Data, Msg);
			break;

		// Waiting for the server to respond to a request. The
		// lpvStatusInformation parameter is NULL. 
		case INTERNET_STATUS_RECEIVING_RESPONSE:
			Msg = "Receiving response ";
			ShowStatus(Data, Msg);
			break;

		// Successfully received a response from the server. The
		// lpvStatusInformation parameter is NULL. 
		case INTERNET_STATUS_RESPONSE_RECEIVED:
			Msg.Format("Received response (result = %ld, error = %ld)", piar->dwResult, piar->dwError);
			ShowStatus(Data, Msg);
			break;

		// Closing the connection to the server. The lpvStatusInformation parameter
		// is NULL. 
		case INTERNET_STATUS_CLOSING_CONNECTION:
			Msg = "Closing connection ";
			ShowStatus(Data, Msg);
			break;

		// Successfully closed the connection to the server. The lpvStatusInformation
		// parameter is NULL. 
		case INTERNET_STATUS_CONNECTION_CLOSED:
			Msg = "Closed connection ";
			ShowStatus(Data, Msg);
			break;

		// Used by InternetConnect to indicate it has created the new handle.
		// This lets the application call InternetCloseHandle from another thread,
		// if the connect is taking too long. 
		case INTERNET_STATUS_HANDLE_CREATED:
			// get new handle from structure
			piar = (LPINTERNET_ASYNC_RESULT)(lpvStatusInformation);

			// store for future use
			Data->hResultHandle = (HINTERNET)piar->dwResult;

			// let caller know handle was created
			::SetEvent(Data->hHandleCreatedEvent);

			Msg.Format("Handle created (result = %ld, error = %ld)", piar->dwResult, piar->dwError);
			ShowStatus(Data, Msg);
			break;

		// This handle value is now terminated 
		case INTERNET_STATUS_HANDLE_CLOSING:
			Msg.Format("Handle closing (result = %ld, error = %ld)", piar->dwResult, piar->dwError);
			ShowStatus(Data, Msg);
			break;

		// An asynchronous operation has been completed.
		// See InternetOpen for details on INTERNET_FLAG_ASYNC.
		case INTERNET_STATUS_REQUEST_COMPLETE:
			//check the INTERNET_ASYNC_RESULT structure for error information
			piar = (LPINTERNET_ASYNC_RESULT)(lpvStatusInformation);
			if (!(piar->dwResult))
				{
				Msg.Format("Internet Request Completed - Error (result = %ld, error = %ld)", piar->dwResult, piar->dwError);
				ShowStatus(Data, Msg);
				switch (piar->dwError)
					{
					//standard error returned from FtpFindFirstFile 
					//and InternetFindNextFile
					case ERROR_NO_MORE_FILES:
						break;
					case ERROR_INTERNET_EXTENDED_ERROR:
						//error triggered when the server can pass back
						//more information on what went wrong.
						break;
					case 1:
						//no problem - this would be a boolean return value
						//representing success
						break;
					default:
						//this would be a good place to check for all the
						//INTERNET_ERROR_* messages (for example, 
						//INTERNET_ERROR_NAME_NOT_RESOLVED) to give more
						//descriptive output to the user
						return;
					}
				}
			else
				{
				Msg.Format("Internet Request Completed - Result (result = %ld, error = %ld)", piar->dwResult, piar->dwError);
				ShowStatus(Data, Msg);
				}
			::SetEvent(Data->hRequestCompleted);
			break;
		}
	return;
	}


void CAdvancedFTPDlg::OnCanceloperation() 
	{
	// set cancel flag
	m_CancelOperation = TRUE;	
	}

//////////////////////////////////////////////////////////////////////////////////////////
// End of routines used for MESSAGE_MAP ON_MESSAGE routines
//////////////////////////////////////////////////////////////////////////////////////////

BOOL CAdvancedFTPDlg::ConnectToInternet() 
{
	CString Msg;
	LPSTR pProxyServer;
	HINTERNET hConnection;
	BOOL bResult = FALSE;

	// show wait cursor
	AfxGetApp()->DoWaitCursor(1);

	// Initialize no-cancellation policy
	m_CancelOperation = FALSE;

	// get proxy name
	pProxyServer = m_ProxyServer.GetBuffer(m_ProxyServer.GetLength());

	// make initial connection to the Internet
	hConnection = ::InternetOpen(
						"Microsoft Internet Explorer",
						//"AsyncFtp",
						INTERNET_OPEN_TYPE_PROXY,
						pProxyServer,
						NULL,
						INTERNET_FLAG_ASYNC);
	if (hConnection != (HINTERNET)NULL)
		{
		bResult = TRUE;

		// store shared data
		Shared_Data.hInternetConnection = hConnection;

		// set up Internet status callback
		Callback_Thread->ResumeThread();

		// update display controls
		UpdateData(FALSE);
		}

	// show normal cursor
	AfxGetApp()->DoWaitCursor(-1);

	return(bResult);
}

BOOL CAdvancedFTPDlg::ConnectToSite() 
{
	// show wait cursor
	AfxGetApp()->DoWaitCursor(1);

	// get values from user
	UpdateData(TRUE);

	strcpy(Shared_Data.cSite, m_FTPSite.GetBuffer(m_FTPSite.GetLength()));
	strcpy(Shared_Data.cUsername, m_Username.GetBuffer(m_Username.GetLength()));
	strcpy(Shared_Data.cPassword, m_Password.GetBuffer(m_Password.GetLength()));

	// set up shared data, make connection to site
	Shared_Data.hHandleCreatedEvent = hWaitForHandleCreation;
	Shared_Data.hResultHandle = (HINTERNET)NULL;
	::ResetEvent(Shared_Data.hExitSiteConnectionThread);
	SetupSiteThreads();
	SiteConnect_Thread->ResumeThread();
	::WaitForSingleObject(SiteConnect_Thread->m_hThread, REQUEST_TIMEOUT);

	// show normal cursor
	AfxGetApp()->DoWaitCursor(-1);

	return(TRUE);
	}

BOOL CAdvancedFTPDlg::EnumerateDirectory() 
{
	CString Msg;
	BOOL bResult = FALSE;
	int iResult;
	int iLineCount;
	HINTERNET hConnection;
	HINTERNET hCreateedConnection;

	// show wait cursor
	AfxGetApp()->DoWaitCursor(1);

	// Initialize no-cancellation policy
	m_CancelOperation = FALSE;

	// clean up list
	m_FTPList.DeleteAllItems();

	// find first file
	ShowStatus(&Shared_Data, "Making connection to FTP directory...");
	Shared_Data.hHandleCreatedEvent = hWaitForHandleCreation;
	Shared_Data.hResultHandle = (HINTERNET)NULL;
	::ResetEvent(hWaitForHandleCreation);
	hConnection = ::FtpFindFirstFile(
					Shared_Data.hFTPSession,
					"*.*",
					&m_sWFD,
					0,
					0);
	::WaitForSingleObject(hWaitForHandleCreation, REQUEST_TIMEOUT);
	hCreateedConnection = Shared_Data.hResultHandle;
	ShowStatus(&Shared_Data, "Connected to FTP directory");

	if (hCreateedConnection != (HINTERNET)NULL)
		{
		bResult = TRUE;

		// process directory
		ShowStatus(&Shared_Data, "Enumerating directory");
		iLineCount = 0;
		m_FTPList.DeleteAllItems();
		bResult = TRUE;
		while (bResult)
			{
			// set up line of data in columns
			Msg.Format("%s", m_sWFD.cFileName);
			iResult = m_FTPList.InsertItem(iLineCount, Msg);
			if ((m_sWFD.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
				{
				Msg.Format("%9ld", m_sWFD.nFileSizeLow);
				m_FTPList.SetItemText(iResult, LV_COL_SIZE, Msg);
				}
			else
				{
				Msg = DIRECTORYLABEL;
				m_FTPList.SetItemText(iResult, LV_COL_ATTR, Msg);
				}

			// incrment to next line
			iLineCount++;
			
			// if we are to cancel then do so
			if (m_CancelOperation)
				{
				break;
				}

			// get next file at ftp site
			bResult = ::InternetFindNextFile(
						hCreateedConnection,
						&m_sWFD);
			}
			
		// display status
		Msg.Format("%d files enumerated", iLineCount);
		ShowStatus(&Shared_Data, Msg);
		AfxGetApp()->DoWaitCursor(-1);
		
		// close down file connections
		::InternetCloseHandle(hCreateedConnection);

		// update display controls
		UpdateData(FALSE);
		}

	// close other handle if given
	if (hConnection != (HINTERNET)NULL)
		{
		::InternetCloseHandle(hConnection);
		}

	// show normal cursor
	AfxGetApp()->DoWaitCursor(1);

	return(bResult);
}

BOOL CAdvancedFTPDlg::CloseSiteConnection() 
{
	// close down site and internet connections
	::InternetCloseHandle(Shared_Data.hFTPSession);
	::SetEvent(Shared_Data.hExitSiteConnectionThread);
	return(TRUE);
}

BOOL CAdvancedFTPDlg::CloseInternetConnection() 
{
	// close down internet connection
	::InternetCloseHandle(Shared_Data.hInternetConnection);
	return(TRUE);
}

void CAdvancedFTPDlg::OnDblclkFtplistng(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	int i;
	CString SubDir;

	if (pNMListView->hdr.code == NM_DBLCLK)
		{
		UpdateData(TRUE);

		i = m_FTPList.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		
		SubDir = m_FTPList.GetItemText(i, LV_COL_FILE);
//		m_FTPSite = m_FTPSite + "/";
//		m_FTPSite = m_FTPSite + SubDir;
//		UpdateData(FALSE);

		::FtpSetCurrentDirectory(Shared_Data.hFTPSession, SubDir);
		EnumerateDirectory();
		}

	*pResult = 0;
}

/////////////////////////////////////////////////////////////////////////////
// Start of Thread routines
/////////////////////////////////////////////////////////////////////////////
BOOL CAdvancedFTPDlg::SetupWorkerThreads()
	{
#ifndef TRACEMODE
	// create thread to handle asyncronous call from Internet callback
	Callback_Thread = AfxBeginThread(
						CallbackThread_Proc,
						(LPVOID)&Shared_Data,
						THREAD_PRIORITY_NORMAL,
						0,
						CREATE_SUSPENDED,
						NULL);

	// create thread to handle independent status updating
	Status_Thread = AfxBeginThread(
						StatusThread_Proc,
						(LPVOID)&Shared_Data,
						THREAD_PRIORITY_NORMAL,
						0,
						0,
						NULL);
#endif //#ifndef TRACEMODE
	return(TRUE);
	}

BOOL CAdvancedFTPDlg::SetupSiteThreads()
	{
#ifndef TRACEMODE
	// create thread to perform FTP site connection
	SiteConnect_Thread = AfxBeginThread(
						SiteConnectThread_Proc,
						(LPVOID)&Shared_Data,
						THREAD_PRIORITY_NORMAL,
						0,
						CREATE_SUSPENDED,
						NULL);
#endif //#ifndef TRACEMODE
	return(TRUE);
	}

UINT CAdvancedFTPDlg::CallbackThread_Proc(LPVOID lParm)
	{
	INTERNET_STATUS_CALLBACK dwISC;
	SHAREDDATA * Data = (SHAREDDATA *)lParm;
	DWORD dwResult;

	// set up Internet status callback
	dwISC = ::InternetSetStatusCallback(Data->hInternetConnection, InternetCallback); 
	if (INTERNET_INVALID_STATUS_CALLBACK == dwISC)
		{
		ASSERT(0);
		}

	AfxEndThread(dwResult);
	return(dwResult);
	}

UINT CAdvancedFTPDlg::StatusThread_Proc(LPVOID lParm)
	{
	SHAREDDATA * Data = (SHAREDDATA *)lParm;
	DWORD dwResult;

	while (TRUE)
		{
//		::OutputDebugString(Data->pStatusText);
		::WaitForSingleObject(Data->hUpdateStatusSignal, STATUS_CALLBACK_TIMEOUT);
		if (Data->iStatusType == SHOWSTATUS_EXIT)
			{
			break;
			}
		::SendMessage(Data->hSendStatusToHwnd, SB_SETTEXT, (WPARAM)0, (LPARAM)(LPSTR)Data->pStatusText);
		}

	AfxEndThread(dwResult);
	return(dwResult);
	}

UINT CAdvancedFTPDlg::SiteConnectThread_Proc(LPVOID lParm)
	{
	SHAREDDATA * Data = (SHAREDDATA * )lParm;
	CString Msg;
	LPSTR pFTPSite;
	LPSTR pUsername;
	LPSTR pPassword;
	HINTERNET hConnection;

	// get values from user
	pFTPSite = Data->cSite;
	pUsername = Data->cUsername;
	if (strlen(pUsername) == 0)
		{
		pUsername = NULL;
		}
	pPassword = Data->cPassword;
	if (strlen(pPassword) == 0)
		{
		pPassword = NULL;
		}

	// set wait flag to 'wait for handle creation'
	::ResetEvent(Data->hHandleCreatedEvent);
	
	// make connection to ftp site
	hConnection = ::InternetConnect(
						Data->hInternetConnection,
						pFTPSite,
						INTERNET_INVALID_PORT_NUMBER,
						pUsername,
						pPassword,
						INTERNET_SERVICE_FTP,
						0,
						(DWORD)lParm);

	// Wait for API to create handle
	::WaitForSingleObject(Data->hHandleCreatedEvent, SITECONNECTION_TIMEOUT);
	Data->hFTPSession = Data->hResultHandle;

	// do not shutdown this thread until finished work
	::WaitForSingleObject(Data->hExitSiteConnectionThread, INFINITE);

	AfxEndThread((DWORD)Data->hResultHandle);
	return((DWORD)Data->hResultHandle);
	}

/////////////////////////////////////////////////////////////////////////////
// End of Thread routines
/////////////////////////////////////////////////////////////////////////////

void CAdvancedFTPDlg::OnSiteconnect() 
	{
	CString Msg;
	
	// make connection to site
	Msg.Format("Connecting to %s...", m_FTPSite);
	ShowStatus(&Shared_Data, Msg);
	if (ConnectToSite())
		{
		Msg.Format("Connected to %s", m_FTPSite);
		GetDlgItem(IDC_SITECONNECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_SITEDISCONNECT)->EnableWindow(TRUE);
		GetDlgItem(IDC_GETDIRECTORYLISTING)->EnableWindow(TRUE);
		}
	else
		{
		Msg.Format("Could not connect to %s", m_FTPSite);
		}
	ShowStatus(&Shared_Data, Msg);
}

void CAdvancedFTPDlg::OnSitedisconnect() 
	{
	// close site connection
	CString Msg;
	Msg.Format("Disconnecting from %s...", m_FTPSite);
	ShowStatus(&Shared_Data, Msg);
	if (CloseSiteConnection())
		{
		Msg.Format("Disconnected from %s", m_FTPSite);
		GetDlgItem(IDC_SITECONNECT)->EnableWindow(TRUE);
		GetDlgItem(IDC_SITEDISCONNECT)->EnableWindow(FALSE);
		GetDlgItem(IDC_GETDIRECTORYLISTING)->EnableWindow(FALSE);
		GetDlgItem(IDC_ADDALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_ADDSELECTED)->EnableWindow(FALSE);
		GetDlgItem(IDC_REMOVESELECTED)->EnableWindow(FALSE);
		GetDlgItem(IDC_REMOVEALL)->EnableWindow(FALSE);
		GetDlgItem(IDC_DOWNLOAD)->EnableWindow(FALSE);
		}
	else
		{
		Msg.Format("Could not disconnected from %s", m_FTPSite);
		}
	ShowStatus(&Shared_Data, Msg);
	}

long CAdvancedFTPDlg::DownloadFile(HINTERNET hFTPSession, CString InputFileSpec, CString OutputFileSpec, DWORD dwContext)
	{
	BOOL bResult;
	long lResult = 0L;
	SHAREDDATA * Data = (SHAREDDATA *)dwContext;

	// get file from ftp site
	::ResetEvent(Data->hRequestCompleted);
	bResult = ::FtpGetFile(
				hFTPSession,
				InputFileSpec,
				OutputFileSpec,
				FALSE,
				FILE_ATTRIBUTE_NORMAL,
				FTP_TRANSFER_TYPE_BINARY,
				dwContext);
	::WaitForSingleObject(Data->hRequestCompleted, INFINITE);

	return(lResult);
	}

