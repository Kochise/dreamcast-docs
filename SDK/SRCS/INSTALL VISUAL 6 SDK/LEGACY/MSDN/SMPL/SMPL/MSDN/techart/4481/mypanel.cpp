// mypanel.cpp

#include "stdafx.h"
#include "ntservcpl.h"

LONG CMyPanel::OnInquire(UINT uAppNum, NEWCPLINFO* pInfo) 
{
    // Fill in the data
    pInfo->dwSize = sizeof(NEWCPLINFO); // important
    pInfo->dwFlags = 0;
    pInfo->dwHelpContext = 0;
    pInfo->lData = 0;
    pInfo->hIcon = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_MYICON));
    strcpy(pInfo->szName, "My Service");
    strcpy(pInfo->szInfo, MYSERVICENAME);
    strcpy(pInfo->szHelpFile, "");
    return 0; // OK (don't send CPL_INQUIRE msg)
}

LONG CMyPanel::OnDblclk(HWND hwndCPl, UINT uAppNum, LONG lData)
{
    // Create the dialog box using the parent window handle
    CMyDialog dlg(CWnd::FromHandle(hwndCPl));

    // Set the default values
    dlg.m_iStartParam = -1;
	dlg.m_iIncParam = -1;
	dlg.m_iCurrent = -1;

    // Read the current state from the registry
    // Try opening the registry key:
    // HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\<AppName>\...
    HKEY hkey;
	char szKey[256];
	strcpy(szKey, "SYSTEM\\CurrentControlSet\\Services\\");
	strcat(szKey, MYSERVICENAME);
	strcat(szKey, "\\Parameters");
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                     szKey,
                     0,
                     KEY_ALL_ACCESS,
                     &hkey) == ERROR_SUCCESS) {
        // Yes we are installed
        DWORD dwType = 0;
        DWORD dwSize = sizeof(dlg.m_iStartParam);
        RegQueryValueEx(hkey,
                        "Start",
                        NULL,
                        &dwType,
                        (BYTE*)&dlg.m_iStartParam,
                        &dwSize);
        dwSize = sizeof(dlg.m_iIncParam);
        RegQueryValueEx(hkey,
                        "Inc",
                        NULL,
                        &dwType,
                        (BYTE*)&dlg.m_iIncParam,
                        &dwSize);
    } else {

		// Key doesn't exist so create it
	    DWORD dwDisp;
	    RegCreateKeyEx(HKEY_LOCAL_MACHINE,
	                   szKey,
	                   0,
	                   "",
	                   REG_OPTION_NON_VOLATILE,
	                   KEY_WRITE,
	                   NULL,
	                   &hkey,
	                   &dwDisp);
	}

    // Show the dialog box
    if (dlg.DoModal() == IDOK) {
	    // Update the registry values
	    RegSetValueEx(hkey,
	                  "Start",
	                  0,
	                  REG_DWORD,
	                  (BYTE*)&dlg.m_iStartParam,
	                  sizeof(dlg.m_iStartParam));
	    RegSetValueEx(hkey,
	                  "Inc",
	                  0,
	                  REG_DWORD,
	                  (BYTE*)&dlg.m_iIncParam,
	                  sizeof(dlg.m_iIncParam));

	}

    // Finished with key
    RegCloseKey(hkey);

    return 0;
}

