// mypanel.cpp

#include "stdafx.h"
#include "mycplapp.h"

LONG CMyPanel::OnInquire(UINT uAppNum, NEWCPLINFO* pInfo) 
{
    // Fill in the data
    pInfo->dwSize = sizeof(NEWCPLINFO); // important
    pInfo->dwFlags = 0;
    pInfo->dwHelpContext = 0;
    pInfo->lData = 0;
    pInfo->hIcon = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_MYICON));
    strcpy(pInfo->szName, "My Applet");
    strcpy(pInfo->szInfo, "My Control Panel Applet");
    strcpy(pInfo->szHelpFile, "");
    return 0; // OK (don't send CPL_INQUIRE msg)
}

LONG CMyPanel::OnDblclk(HWND hwndCPl, UINT uAppNum, LONG lData)
{
    // Create the dialog box using the parent window handle
    CMyDialog dlg(CWnd::FromHandle(hwndCPl));

    // Set the default value
    dlg.m_iMyValue = 0;

    // Read the current state from the registry
    // Try opening the registry key:
    // HKEY_CURRENT_USER\Control Panel\<AppName>
    HKEY hcpl;
    if (RegOpenKeyEx(HKEY_CURRENT_USER,
                     "Control Panel",
                     0,
                     KEY_QUERY_VALUE,
                     &hcpl) == ERROR_SUCCESS) {
        HKEY happ;
        if (RegOpenKeyEx(hcpl,
                         "MyPanel",
                         0,
                         KEY_QUERY_VALUE,
                         &happ) == ERROR_SUCCESS) {
            // Yes we are installed
            DWORD dwType = 0;
            DWORD dwSize = sizeof(dlg.m_iMyValue);
            RegQueryValueEx(happ,
                            "MyValue",
                            NULL,
                            &dwType,
                            (BYTE*)&dlg.m_iMyValue,
                            &dwSize);
            RegCloseKey(happ);
        }
        RegCloseKey(hcpl);
    }

    // Show the dialog box
    if (dlg.DoModal() != IDOK) return 0;

    // Update the registry
    // Try creating/opening the registry key
    if (RegOpenKeyEx(HKEY_CURRENT_USER,
                     "Control Panel",
                     0,
                     KEY_WRITE,
                     &hcpl) == ERROR_SUCCESS) {
        HKEY happ;
        DWORD dwDisp;
        if (RegCreateKeyEx(hcpl,
                           "MyPanel",
                           0,
                           "",
                           REG_OPTION_NON_VOLATILE,
                           KEY_WRITE,
                           NULL,
                           &happ,
                           &dwDisp) == ERROR_SUCCESS) {
            // Set the value
            RegSetValueEx(happ,
                          "MyValue",
                          0,
                          REG_DWORD,
                          (BYTE*)&dlg.m_iMyValue,
                          sizeof(dlg.m_iMyValue));

            // Finished with keys
            RegCloseKey(happ);
        }
        RegCloseKey(hcpl);
    }

    return 0;
}
