// NTSerdlg.cpp : implementation file
//

#include "stdafx.h"
#include "NTServCtrl.h"
#include "NTSerdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNTServCtrlDlg dialog

CNTServCtrlDlg::CNTServCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNTServCtrlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNTServCtrlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_uiTimer = 0;
}

void CNTServCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNTServCtrlDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNTServCtrlDlg, CDialog)
	//{{AFX_MSG_MAP(CNTServCtrlDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_QUERY, OnQuery)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNTServCtrlDlg message handlers

BOOL CNTServCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	
	// Set the default service name
    SetDlgItemText(IDC_SERVNAME, "NT Service Demonstration");

    // Start the auto-update timer
    m_uiTimer = SetTimer(1, 1000, NULL); // 1 second interval

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNTServCtrlDlg::OnPaint() 
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
HCURSOR CNTServCtrlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNTServCtrlDlg::OnQuery() 
{
	ShowState();
}

void CNTServCtrlDlg::OnStart() 
{
    // Get the service name
    char szServiceName[64];
    szServiceName[0] = '\0';
    GetDlgItemText(IDC_SERVNAME, szServiceName, sizeof(szServiceName));
    if (strlen(szServiceName) == 0) return;
     
    // open the service control manager
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    ASSERT(hSCM);   

    // open the service
    SC_HANDLE hService = OpenService(hSCM,
                                     szServiceName,
                                     SERVICE_ALL_ACCESS);
    ASSERT(hService);

    // start the service
    BOOL b = StartService(hService, 0, NULL);
    if(!b) {
        DWORD dwErr = GetLastError();
        ASSERT(0);
    }

    // close the service handle
    CloseServiceHandle(hService);

    // close the service control manager handle
    CloseServiceHandle(hSCM);

	ShowState();
}

void CNTServCtrlDlg::OnStop() 
{
    // Get the service name
    char szServiceName[64];
    szServiceName[0] = '\0';
    GetDlgItemText(IDC_SERVNAME, szServiceName, sizeof(szServiceName));
    if (strlen(szServiceName) == 0) return;
     
    // open the service control manager
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    ASSERT(hSCM);   

    // open the service
    SC_HANDLE hService = OpenService(hSCM,
                                     szServiceName,
                                     SERVICE_ALL_ACCESS);
    ASSERT(hService);

    // stop the service
    SERVICE_STATUS ss;
    BOOL b = ControlService(hService,
                            SERVICE_CONTROL_STOP,
                            &ss);
    if(!b) {
        DWORD dwErr = GetLastError();
        ASSERT(0);
    }

    // close the service handle
    CloseServiceHandle(hService);

    // close the service control manager handle
    CloseServiceHandle(hSCM);

	ShowState();
}

void CNTServCtrlDlg::ShowState()
{
    // Get the service name
    char szServiceName[64];
    szServiceName[0] = '\0';
    DWORD dwState = 0xFFFFFFFF;
    DWORD dwErr = 0xFFFFFFFF;
    GetDlgItemText(IDC_SERVNAME, szServiceName, sizeof(szServiceName));
    if (strlen(szServiceName) != 0) {
     
        // open the service control manager
        SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
        ASSERT(hSCM);   

        // open the service
        SC_HANDLE hService = OpenService(hSCM,
                                         szServiceName,
                                         SERVICE_ALL_ACCESS);
        if (hService) {

            // Get the current status
            SERVICE_STATUS ss;
            memset(&ss, 0, sizeof(ss));
            BOOL b = QueryServiceStatus(hService,
                                        &ss);
            if(!b) {
                DWORD dwErr = GetLastError();
                ASSERT(0);
            } else {
                dwErr = ss.dwWin32ExitCode;
                dwState = ss.dwCurrentState;

                // If the service is running, send a control request
                // to get its current status
                if (dwState == SERVICE_RUNNING) {
                    b = ::ControlService(hService,
                                         SERVICE_CONTROL_INTERROGATE,
                                         &ss);
                    if (b) {
                        dwErr = ss.dwWin32ExitCode;
                        dwState = ss.dwCurrentState;
                    }
                }
            }

            // close the service handle
            CloseServiceHandle(hService);
        }

        // close the service control manager handle
        CloseServiceHandle(hSCM);
    }

    // See what we got
    char buf[64];
    if (dwErr == 0xFFFFFFFF) {
        SetDlgItemText(IDC_EXITCODE, "<unknown>");
    } else {
        sprintf(buf, "%8.8lXH (%d)", dwErr, dwErr);
        SetDlgItemText(IDC_EXITCODE, buf);
    }

    switch (dwState) {
    case SERVICE_STOPPED:
        strcpy(buf, "Stopped");
        break;
    case SERVICE_START_PENDING:
        strcpy(buf, "Start pending");
        break;
    case SERVICE_STOP_PENDING:
        strcpy(buf, "Stop pending");
        break;
    case SERVICE_RUNNING:
        strcpy(buf, "Running");
        break;
    case SERVICE_CONTINUE_PENDING:
        strcpy(buf, "Continue pending");
        break;
    case SERVICE_PAUSE_PENDING:
        strcpy(buf, "Pause pending");
        break;
    case SERVICE_PAUSED:
        strcpy(buf, "Paused");
        break;
    default:
        strcpy(buf, "<Unknown>");
        break;
    }
    SetDlgItemText(IDC_STATE, buf);
}

void CNTServCtrlDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if (m_uiTimer != 0) {
	    KillTimer(1);
	}	
}

void CNTServCtrlDlg::OnTimer(UINT nIDEvent) 
{
	// Update the status
	ShowState();
}
