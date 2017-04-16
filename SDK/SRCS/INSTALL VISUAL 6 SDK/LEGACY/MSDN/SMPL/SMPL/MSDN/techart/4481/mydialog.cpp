// mydialog.cpp : implementation file
//

#include "stdafx.h"
#include "NTServCpl.h"
//#include "mydialog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDialog dialog


CMyDialog::CMyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDialog)
	m_iStartParam = 0;
	m_iIncParam = 0;
	//}}AFX_DATA_INIT
	m_uiTimer = 0;
    m_iCurrent = -1;
}


void CMyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDialog)
	DDX_Text(pDX, IDC_START, m_iStartParam);
	DDX_Text(pDX, IDC_INC, m_iIncParam);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyDialog, CDialog)
	//{{AFX_MSG_MAP(CMyDialog)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyDialog message handlers

BOOL CMyDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Start the status update timer
	m_uiTimer = SetTimer(1, 500, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMyDialog::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// Kill the update timer
	if (m_uiTimer) KillTimer(1);
}

#define SERVICE_CONTROL_USER 128 // not in sdk headers

void CMyDialog::OnTimer(UINT nIDEvent) 
{
	// Update the current status
	SERVICE_STATUS ss;
	DWORD dwErr = 0;

    // open the service control manager
    SC_HANDLE hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    ASSERT(hSCM);   

    // open the service
    SC_HANDLE hService = OpenService(hSCM,
                                     MYSERVICENAME,
                                     SERVICE_ALL_ACCESS);
    if (hService) {

		// Send the update status message to the service
	    BOOL b = ControlService(hService, 
	    			            SERVICE_CONTROL_USER + 0,
	    			            &ss);
		if (!b) dwErr = GetLastError();

	    // close the service handle
	    CloseServiceHandle(hService);

	} else {
		dwErr = GetLastError();
	}

    // close the service control manager handle
    CloseServiceHandle(hSCM);

	if (dwErr == 0) {
		// Read the current status from the registry
	    HKEY hkey;
		char szKey[256];
		strcpy(szKey, "SYSTEM\\CurrentControlSet\\Services\\");
		strcat(szKey, MYSERVICENAME);
		strcat(szKey, "\\Status");
	    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
	                     szKey,
	                     0,
	                     KEY_QUERY_VALUE,
	                     &hkey) == ERROR_SUCCESS) {
	        // Yes we are installed
	        DWORD dwType = 0;
	        DWORD dwSize = sizeof(m_iCurrent);
	        RegQueryValueEx(hkey,
	                        "Current",
	                        NULL,
	                        &dwType,
	                        (BYTE*)&m_iCurrent,
	                        &dwSize);
	        RegCloseKey(hkey);
		}

		// update the display
		SetDlgItemInt(IDC_CURRENT, m_iCurrent);
		SetDlgItemText(IDC_MSG, "Service active");
	} else {
		char buf[256];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
					  NULL,
					  dwErr,
					  0,
					  buf,
					  sizeof(buf),
					  NULL);
		SetDlgItemText(IDC_CURRENT, "");
		SetDlgItemText(IDC_MSG, buf);
	}	
}
