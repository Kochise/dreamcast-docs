///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      ADMMBOX.CPP
//
//  Description
//
//  Author
//      Irving De la Cruz
//
//  Revision: 1.7
//
// Written for Microsoft Windows Developer Support
// Copyright (c) 1995-1996 Microsoft Corporation. All rights reserved.
//
#include "ADMIN.H"
#include "COMMON.H"

extern "C"
{
    HRESULT WINAPI DisplayMailboxPropSheets
                        (HWND                       hOwnerWnd,
                         POBJECT_INFO               pObjInfo,
                         BOOL                       fCreate);
    BOOL CALLBACK MBProps1DlgProc
                        (HWND                       hDlg, 
                         UINT                       message, 
                         WPARAM                     wParam, 
                         LPARAM                     lParam);
    BOOL CALLBACK MBProps2DlgProc
                        (HWND                       hDlg, 
                         UINT                       message, 
                         WPARAM                     wParam, 
                         LPARAM                     lParam);
    BOOL CALLBACK MBProps3DlgProc
                        (HWND                       hDlg, 
                         UINT                       message, 
                         WPARAM                     wParam, 
                         LPARAM                     lParam);
    BOOL CALLBACK MBProps4DlgProc
                        (HWND                       hDlg, 
                         UINT                       message, 
                         WPARAM                     wParam, 
                         LPARAM                     lParam);
    BOOL CALLBACK MBProps5DlgProc
                        (HWND                       hDlg, 
                         UINT                       message, 
                         WPARAM                     wParam, 
                         LPARAM                     lParam);
    BOOL CALLBACK MBProps6DlgProc
                        (HWND                       hDlg, 
                         UINT                       message, 
                         WPARAM                     wParam, 
                         LPARAM                     lParam);

    void WINAPI RemoveSpaces
                        (LPTSTR *                   ppStr,
                         UINT                       uMaxChars);
    HRESULT WINAPI ExportDirectoryToFile
                        (HWND                       hOwnerWnd);
    HRESULT WINAPI ImportDirectoryFromFile
                        (HWND                       hOwnerWnd);
};

///////////////////////////////////////////////////////////////////////////////
//    ExportDirectoryToFile()
//
//    Parameters
//
//    Purpose
//      
//    Return Value
//      
HRESULT WINAPI ExportDirectoryToFile (HWND hOwnerWnd)
{
    LPTSTR szExportFile = (LPTSTR)GetWindowLong (hOwnerWnd, GWL_USERDATA);
    HWND hLabel = GetDlgItem (hOwnerWnd, IDC_MAILBOX_LABEL);
    SetWindowText (hLabel, TEXT(""));
    HRESULT hResult = S_OK;
    long lPipeNum;
    TCHAR achPipeName[128];
    HANDLE hPipe;
    DWORD dwBytesRead, dwBytesWritten;
    AB_ENTRY_INFO abEntry = { 0 };
    char achCRLF[] = "\r\n", achComma[] = ", ", chQuote = '"';
    HANDLE hFile = CreateFile (szExportFile,
                               GENERIC_WRITE,
                               FILE_SHARE_READ,
                               NULL,
                               CREATE_ALWAYS,
                               FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 
                               NULL);
    if (INVALID_HANDLE_VALUE == hFile)
    {
        hResult = HRESULT_FROM_WIN32 (GetLastError());
        goto ExportFinished;
    }
    RpcTryExcept
    {
        hResult = RemoteAdmGetServerMailboxes (&lPipeNum);
        if (!hResult)
        {
            // Construct the download pipe name
            wsprintf (achPipeName, PIPE_NAME_FORMAT, g_szCurrentServer, lPipeNum);
            // Create our endpoint and connect    
            hPipe = CreateFile (achPipeName, 
                                GENERIC_READ,
                                0,
                                NULL,
                                OPEN_EXISTING,
                                0,
                                NULL);
            if (INVALID_HANDLE_VALUE == hPipe)
            {
                hResult = HRESULT_FROM_WIN32(GetLastError());
            }
        }
    }
    RpcExcept(1)
    {        
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    if (!hResult)
    {
        do
        {
            // Read from the pipe
            if (!ReadFile (hPipe, &abEntry, sizeof(AB_ENTRY_INFO), &dwBytesRead, NULL))
            {
                hResult = HRESULT_FROM_WIN32(GetLastError());
                if (HRESULT_FROM_WIN32(ERROR_BROKEN_PIPE)   != hResult &&   // For Windows NT
                    HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED) != hResult)     // For Windows 95
                {
                    // There was an error and we can't continue
                    TraceResult ("ExportDirectoryToFile: Failed to read from the source", hResult);
                }
                else
                {
                    // If the pipe was broken, it means the server finished writing
                    // to the it, so we are finished reading from it.
                    hResult = S_OK;
                }
            }
            else
            {
                SetWindowText (hLabel, abEntry.Info.MB.szMailboxName);
                WriteFile (hFile, abEntry.Info.MB.szMailboxName, lstrlen (abEntry.Info.MB.szMailboxName), &dwBytesWritten, NULL);
                WriteFile (hFile, achComma, 2, &dwBytesWritten, NULL);
                WriteFile (hFile, abEntry.Info.MB.szFullName, lstrlen (abEntry.Info.MB.szFullName), &dwBytesWritten, NULL);
                WriteFile (hFile, achComma, 2, &dwBytesWritten, NULL);
                WriteFile (hFile, abEntry.Info.MB.szJobTitle, lstrlen (abEntry.Info.MB.szJobTitle), &dwBytesWritten, NULL);
                WriteFile (hFile, achComma, 2, &dwBytesWritten, NULL);
                WriteFile (hFile, abEntry.Info.MB.szOffice, lstrlen (abEntry.Info.MB.szOffice), &dwBytesWritten, NULL);
                WriteFile (hFile, achComma, 2, &dwBytesWritten, NULL);
                WriteFile (hFile, abEntry.Info.MB.szPhone, lstrlen (abEntry.Info.MB.szPhone), &dwBytesWritten, NULL);
                WriteFile (hFile, achComma, 2, &dwBytesWritten, NULL);
                WriteFile (hFile, abEntry.Info.MB.szCompany, lstrlen (abEntry.Info.MB.szCompany), &dwBytesWritten, NULL);
                WriteFile (hFile, achComma, 2, &dwBytesWritten, NULL);
                WriteFile (hFile, abEntry.Info.MB.szDepartment, lstrlen (abEntry.Info.MB.szDepartment), &dwBytesWritten, NULL);
                WriteFile (hFile, achComma, 2, &dwBytesWritten, NULL);
                WriteFile (hFile, abEntry.Info.MB.szAltPhone, lstrlen (abEntry.Info.MB.szAltPhone), &dwBytesWritten, NULL);
                WriteFile (hFile, achComma, 2, &dwBytesWritten, NULL);
                WriteFile (hFile, abEntry.Info.MB.szFax, lstrlen (abEntry.Info.MB.szFax), &dwBytesWritten, NULL);
                WriteFile (hFile, achComma, 2, &dwBytesWritten, NULL);
                WriteFile (hFile, abEntry.Info.MB.szComments, lstrlen (abEntry.Info.MB.szComments), &dwBytesWritten, NULL);

                WriteFile (hFile, achCRLF, 2, &dwBytesWritten, NULL);
            }
            if (AbortRemoteCall())
            {
                break; // Out of the DO-WHILE() loop
            }
        } while (dwBytesRead && !hResult);
        CloseHandle (hPipe);
    }
    CloseHandle (hFile);
    SetWindowText (hLabel, TEXT("Done!"));
ExportFinished:
    PostMessage (hOwnerWnd, WM_WINDS_EXPORT_FINISHED, hResult, 0);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    ImportDirectoryFromFile()
//
//    Parameters
//
//    Purpose
//      
//    Return Value
//      
HRESULT WINAPI ImportDirectoryFromFile (HWND hOwnerWnd)
{
    LPTSTR szImportFile = (LPTSTR)GetWindowLong (hOwnerWnd, GWL_USERDATA);
    HWND hLabel = GetDlgItem (hOwnerWnd, IDC_MAILBOX_LABEL);
    SetWindowText (hLabel, TEXT(""));
    HWND hListBox = GetDlgItem (hOwnerWnd, IDC_IMPORT_LIST);
    TCHAR szBuffer[256];
    
    MAILBOX_INFO MB = { 0 };
    DWORD i, dwBytesRead = 1;
    TCHAR achBuffer[4096], *szSubStr, achEmpty[] = TEXT("");
    HRESULT hResult = S_OK;
    HANDLE hFile = CreateFile (szImportFile,
                               GENERIC_READ,
                               FILE_SHARE_READ,
                               NULL,
                               OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, 
                               NULL);
    if (INVALID_HANDLE_VALUE == hFile)
    {
        hResult = HRESULT_FROM_WIN32(GetLastError());
        goto ImportFinished;
    }
    do
    {
        ZeroMemory (achBuffer, sizeof(achBuffer));
        ZeroMemory (&MB, sizeof(MAILBOX_INFO));
        for (i=0; i<4096 && !hResult && dwBytesRead; i++)
        {
            if (!ReadFile (hFile, &(achBuffer[i]), 1, &dwBytesRead, NULL))
            {
                hResult = HRESULT_FROM_WIN32(GetLastError());
                TraceResult ("ImportDirectoryToFile: Failed to read from the source", hResult);
            }
            else
            {
                if (achBuffer[i] == '\n')
                {
                    break;  // Out of the FOR() loop
                }
            }
        }
        i = lstrlen(achBuffer);
        if (hResult || (!dwBytesRead && 0 == i))
        {
            break;
        }
        if (i>1 && '\n' == achBuffer[i - 1])
        {
            achBuffer[i - 1] = 0;
        }
        if (i>2 && '\r' == achBuffer[i - 2])
        {
            achBuffer[i - 2] = 0;
        }
        
        if (AbortRemoteCall())
        {
            break; // Out of the DO-WHILE() loop
        }
        
        // Get the ALIAS of the mailbox
        szSubStr = strtok (achBuffer, ",");
        if (NULL == szSubStr) { szSubStr = achEmpty; }
        RemoveSpaces (&szSubStr, MAX_ALIAS_SIZE);
        SetWindowText (hLabel, szSubStr);
        if (!IsObjAliasValid (NULL, szSubStr))
        {
            wsprintf (szBuffer, TEXT("%s\tFAILED: Invalid object alias name"), szSubStr);
            ListBox_AddString (hListBox, szBuffer);
            continue;
        }
        lstrcpy (MB.szMailboxName, szSubStr);
        CharUpper (MB.szMailboxName);

        // Get the FULL NAME of the mailbox owner
        szSubStr = strtok (NULL, ",");
        if (NULL == szSubStr) { szSubStr = achEmpty; }
        RemoveSpaces (&szSubStr, MAX_STRING_SIZE);
        lstrcpy (MB.szFullName, szSubStr);

        // Get the JOB TITLE of the mailbox owner
        szSubStr = strtok (NULL, ",");
        if (NULL == szSubStr) { szSubStr = achEmpty; }
        RemoveSpaces (&szSubStr, MAX_STRING_SIZE);
        lstrcpy (MB.szJobTitle, szSubStr);

        // Get the OFFICE LOCATION of the mailbox owner
        szSubStr = strtok (NULL, ",");
        if (NULL == szSubStr) { szSubStr = achEmpty; }
        RemoveSpaces (&szSubStr, MAX_STRING_SIZE);
        lstrcpy (MB.szOffice, szSubStr);

        // Get the PHONE NUMBER of the mailbox owner
        szSubStr = strtok (NULL, ",");
        if (NULL == szSubStr) { szSubStr = achEmpty; }
        RemoveSpaces (&szSubStr, MAX_PHONE_SIZE);
        lstrcpy (MB.szPhone, szSubStr);
        
        // Get the COMPANY of the mailbox owner
        szSubStr = strtok (NULL, ",");
        if (NULL == szSubStr) { szSubStr = achEmpty; }
        RemoveSpaces (&szSubStr, MAX_STRING_SIZE);
        lstrcpy (MB.szCompany, szSubStr);
        
        // Get the DEPARTMENT of the mailbox owner
        szSubStr = strtok (NULL, ",");
        if (NULL == szSubStr) { szSubStr = achEmpty; }
        RemoveSpaces (&szSubStr, MAX_STRING_SIZE);
        lstrcpy (MB.szDepartment, szSubStr);

        // Get the ALTERNATE PHONE NUMBER of the mailbox owner
        szSubStr = strtok (NULL, ",");
        if (NULL == szSubStr) { szSubStr = achEmpty; }
        RemoveSpaces (&szSubStr, MAX_PHONE_SIZE);
        lstrcpy (MB.szAltPhone, szSubStr);
        
        // Get the FAX NUMBER of the mailbox owner
        szSubStr = strtok (NULL, ",");
        if (NULL == szSubStr) { szSubStr = achEmpty; }
        RemoveSpaces (&szSubStr, MAX_PHONE_SIZE);
        lstrcpy (MB.szFax, szSubStr);
        
        // Get the COMMENTS of the mailbox
        szSubStr = strtok (NULL, ",");
        if (NULL == szSubStr) { szSubStr = achEmpty; }
        RemoveSpaces (&szSubStr, MAX_COMMENT_SIZE);
        lstrcpy (MB.szComments, szSubStr);

        lstrcpy (MB.szPassword, TEXT("PASSWORD"));
        
        if (AbortRemoteCall())
        {
            break; // Out of the DO-WHILE() loop
        }
        RpcTryExcept
        {
            hResult = RemoteAdmCreateMailbox ((ADM_MAILBOX_INFO*)&MB);
        }
        RpcExcept(1)
        {        
            // If we got here is because there was an error while call was made
            // or when it was about to be made.
            hResult = RpcExceptionCode();
            if (RPC_S_SERVER_UNAVAILABLE == hResult)
            {
                hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
            }
            else
            {
                hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
            }
        }
        RpcEndExcept
        if (hResult)
        {
            if (HRESULT_FROM_WIN32(ERROR_USER_EXISTS) == hResult)
            {
                wsprintf (szBuffer, TEXT("%s\tFAILED: The object already exists in the directory"), MB.szMailboxName);
            }
            else
            {
                wsprintf (szBuffer, TEXT("%s\tFAILED: Error %X"), MB.szMailboxName, hResult);
            }
        }
        else
        {
            lstrcpy (szBuffer, MB.szMailboxName);
            lstrcat (szBuffer, TEXT("\tSuccessfully Imported"));
        }
        ListBox_AddString (hListBox, szBuffer);

        if (hResult &&
            hResult != HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE) &&
            HRESULT_FACILITY(hResult) != FACILITY_RPC)
        {
            hResult = S_OK;
        }
        if (AbortRemoteCall())
        {
            break; // Out of the DO-WHILE() loop
        }
    } while (!hResult && dwBytesRead);
    CloseHandle (hFile);
    SetWindowText (hLabel, TEXT("Done!"));
ImportFinished:
    PostMessage (hOwnerWnd, WM_WINDS_IMPORT_FINISHED, hResult, 0);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    RemoveSpaces()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
void WINAPI RemoveSpaces (LPTSTR * ppStr, UINT uMaxChars)
{
    LPTSTR pStr = *ppStr;
    // On an empty string, return. Nothing to do here
    if (0 == *pStr) 
    {
        return;
    }
    while (' ' == *pStr || '\t' == *pStr)
    {
        pStr++;
    }
    *ppStr = pStr;
    // On an empty string or a single chracter stringm, return.
    int i = lstrlen (pStr);
    if (0 == *pStr || i < 2)
    {
        return;
    }
    pStr = &(pStr[i]);
    while (' ' == *pStr || '\t' == *pStr || NULL == *pStr)
    {
        *pStr = NULL;
        pStr--;
    }
    if (uMaxChars < (UINT)lstrlen (*ppStr))
    {
        (*ppStr)[uMaxChars] = NULL;
    }
}

///////////////////////////////////////////////////////////////////////////////
//    CreateNewMailbox()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
void WINAPI CreateNewMailbox (HWND hOwnerWnd)
{
    OBJECT_INFO ObjInfo = { 0 };
    lstrcpy (ObjInfo.MB.szPassword, TEXT("PASSWORD"));
    ObjInfo.Type = SERVER_USER_MAILBOX;
    HRESULT hResult = DisplayMailboxPropSheets (hOwnerWnd, &ObjInfo, TRUE);
    if (!hResult)
    {
        RpcTryExcept
        {
            hResult = RemoteAdmCreateMailbox ((ADM_MAILBOX_INFO*)&ObjInfo.MB);
        }
        RpcExcept(1)
        {        
            // If we got here is because there was an error while call was made
            // or when it was about to be made.
            hResult = RpcExceptionCode();
            if (RPC_S_SERVER_UNAVAILABLE == hResult)
            {
                hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
            }
            else
            {
                hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
            }
        }
        RpcEndExcept
    }
    else
    {
        if (S_FALSE == hResult)
        {
            hResult = S_OK;
        }
    }
    if (hResult)
    {
        ErrorHandler (hOwnerWnd, hResult);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    DeleteServerObject()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
void WINAPI DeleteServerObject (HWND hOwnerWnd, DWORD dwObjID)
{
    if (IDNO == PrivateMessageBox (IDS_MSG_CONFIRM_OBJECT_DELETE,
                                   hOwnerWnd,
                                   MB_YESNO | MB_ICONEXCLAMATION))
    {
        return;
    }
    HRESULT hResult = S_OK;
    RpcTryExcept
    {
        hResult = RemoteAdmDeleteObject (dwObjID);
    }
    RpcExcept(1)
    {        
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    if (hResult)
    {
        ErrorHandler (hOwnerWnd, hResult);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    ShowMailboxProps()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
void WINAPI ShowMailboxProps (HWND hOwnerWnd, DWORD dwObjID)
{
    OBJECT_INFO ObjInfo = { 0 };
    ObjInfo.MB.dwObjID = dwObjID;
    ObjInfo.Type = SERVER_USER_MAILBOX;
    HRESULT hResult = S_OK;
    DWORD dwObjType;
    RpcTryExcept
    {
        hResult = RemoteAdmGetMailboxProps (dwObjID, &dwObjType, (ADM_MAILBOX_INFO*)&ObjInfo.MB);
    }
    RpcExcept(1)
    {        
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    if (!hResult)
    {
        hResult = DisplayMailboxPropSheets (hOwnerWnd, &ObjInfo, FALSE);
        if (S_OK == hResult)
        {
            RpcTryExcept
            {
                hResult = RemoteAdmSetMailboxProps ((ADM_MAILBOX_INFO*)&ObjInfo.MB);
            }
            RpcExcept(1)
            {        
                // If we got here is because there was an error while call was made
                // or when it was about to be made.
                hResult = RpcExceptionCode();
                if (RPC_S_SERVER_UNAVAILABLE == hResult)
                {
                    hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
                }
                else
                {
                    hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
                }
            }
            RpcEndExcept
        }
        if (S_FALSE == hResult)
        {
            hResult = S_OK;
        }
    }
    if (hResult)
    {
        ErrorHandler (hOwnerWnd, hResult);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    DisplayMailboxPropSheets()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
HRESULT WINAPI DisplayMailboxPropSheets (HWND           hOwnerWnd,
                                         POBJECT_INFO   pObjInfo,
                                         BOOL           fCreate)
{
    PROPSHEETHEADER psh = { 0 };
    PROPSHEETPAGE psp[6] = { 0 };
    TCHAR szHeaderTitle[64];

    OBJECT_INFO NewObjInfo = *pObjInfo;

    psp[0].dwSize      = sizeof(PROPSHEETPAGE);
    psp[0].dwFlags     = PSP_USETITLE;
    psp[0].hInstance   = ghInstance;
    psp[0].pszTemplate = MAKEINTRESOURCE (IDD_MB_PROPS1);
    psp[0].pfnDlgProc  = MBProps1DlgProc;
    psp[0].pszTitle    = TEXT("General");
    psp[0].lParam      = (LPARAM)&NewObjInfo;
    
    psp[1].dwSize      = sizeof(PROPSHEETPAGE);
    psp[1].dwFlags     = PSP_USETITLE;
    psp[1].hInstance   = ghInstance;
    psp[1].pszTemplate = MAKEINTRESOURCE (IDD_MB_PROPS2);
    psp[1].pfnDlgProc  = MBProps2DlgProc;
    psp[1].pszTitle    = TEXT("Phones");
    psp[1].lParam      = (LPARAM)&NewObjInfo;

    psp[2].dwSize      = sizeof(PROPSHEETPAGE);
    psp[2].dwFlags     = PSP_USETITLE;
    psp[2].hInstance   = ghInstance;
    psp[2].pszTemplate = MAKEINTRESOURCE (IDD_MB_PROPS3);
    psp[2].pfnDlgProc  = MBProps3DlgProc;
    psp[2].pszTitle    = TEXT("Organization");
    psp[2].lParam      = (LPARAM)&NewObjInfo;

    psp[3].dwSize      = sizeof(PROPSHEETPAGE);
    psp[3].dwFlags     = PSP_USETITLE;
    psp[3].hInstance   = ghInstance;
    psp[3].pszTemplate = MAKEINTRESOURCE (IDD_MB_PROPS4);
    psp[3].pfnDlgProc  = MBProps4DlgProc;
    psp[3].pszTitle    = TEXT("Account Security");
    psp[3].lParam      = (LPARAM)&NewObjInfo;

    psp[4].dwSize      = sizeof(PROPSHEETPAGE);
    psp[4].dwFlags     = PSP_USETITLE;
    psp[4].hInstance   = ghInstance;
    psp[4].pszTemplate = MAKEINTRESOURCE (IDD_MB_PROPS5);
    psp[4].pfnDlgProc  = MBProps5DlgProc;
    psp[4].pszTitle    = TEXT("Delegate Access");
    psp[4].lParam      = (LPARAM)&NewObjInfo;

    psp[5].dwSize      = sizeof(PROPSHEETPAGE);
    psp[5].dwFlags     = PSP_USETITLE;
    psp[5].hInstance   = ghInstance;
    psp[5].pszTemplate = MAKEINTRESOURCE (IDD_MB_PROPS6);
    psp[5].pfnDlgProc  = MBProps6DlgProc;
    psp[5].pszTitle    = TEXT("Auto Reply");
    psp[5].lParam      = (LPARAM)&NewObjInfo;

    psh.dwSize     = sizeof(PROPSHEETHEADER);
    psh.dwFlags    = PSH_PROPSHEETPAGE | PSH_NOAPPLYNOW;
    psh.hwndParent = hOwnerWnd;
    psh.hInstance  = ghInstance;
    psh.nPages     = sizeof(psp)/sizeof(PROPSHEETPAGE);
    psh.ppsp       = (LPCPROPSHEETPAGE)&psp;
    if (fCreate)
    {
        psh.pszCaption  = TEXT("New Mailbox Properties");
    }
    else
    {
        wsprintf (szHeaderTitle, TEXT("Mailbox Properties for %s"), pObjInfo->MB.szMailboxName);
        psh.pszCaption  = szHeaderTitle;
    }

    // If the user hit OK and at least one of the properties changed,
    // we must change the properties on the server
ReEnterProperties:
    if (1 == PropertySheet (&psh) &&
        (fCreate || 
        (NewObjInfo.MB.dwFlags != pObjInfo->MB.dwFlags ||
         NewObjInfo.MB.dwManagerID != pObjInfo->MB.dwManagerID ||
         lstrcmpi (NewObjInfo.MB.szFullName,    pObjInfo->MB.szFullName) ||
         lstrcmpi (NewObjInfo.MB.szPassword,    pObjInfo->MB.szPassword) ||
         lstrcmpi (NewObjInfo.MB.szJobTitle,    pObjInfo->MB.szJobTitle) ||
         lstrcmpi (NewObjInfo.MB.szOffice,      pObjInfo->MB.szOffice) ||
         lstrcmpi (NewObjInfo.MB.szPhone,       pObjInfo->MB.szPhone) ||
         lstrcmpi (NewObjInfo.MB.szAltPhone,    pObjInfo->MB.szAltPhone) ||
         lstrcmpi (NewObjInfo.MB.szFax,         pObjInfo->MB.szFax) ||
         lstrcmpi (NewObjInfo.MB.szCompany,     pObjInfo->MB.szCompany) ||
         lstrcmpi (NewObjInfo.MB.szDepartment,  pObjInfo->MB.szDepartment) ||
         lstrcmpi (NewObjInfo.MB.szManagerAlias,pObjInfo->MB.szManagerAlias) ||
         lstrcmpi (NewObjInfo.MB.szManagerName,pObjInfo->MB.szManagerName) ||
         lstrcmpi (NewObjInfo.MB.szComments,  pObjInfo->MB.szComments))))
    {
        if (fCreate)
        {
            psh.nStartPage = 0;
            if (!IsObjAliasValid (hOwnerWnd, NewObjInfo.MB.szMailboxName))
            {
                goto ReEnterProperties;
            }
        }
        if (0 == lstrlen (NewObjInfo.MB.szFullName))
        {
            PrivateMessageBox (IDS_MSG_NO_USER_NAME, hOwnerWnd, 0);
            psh.nStartPage = 0;
            goto ReEnterProperties;
        }
        if (0 == lstrlen (NewObjInfo.MB.szPassword))
        {
            PrivateMessageBox (IDS_MSG_NO_PASSWORD, hOwnerWnd, 0);
            psh.nStartPage = 2;
            goto ReEnterProperties;
        }
        *pObjInfo = NewObjInfo;
        return S_OK;
    }
    return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    IsObjAliasValid()
//
//    Parameters
//
//    Purpose
//      
//    Return Value
//      
BOOL WINAPI IsObjAliasValid (HWND hOwnerWnd, LPTSTR szObjAlias)
{
    TCHAR achTempAlias[MAX_ALIAS_SIZE+1];
    lstrcpy (achTempAlias, szObjAlias);
    szObjAlias[0] = NULL;
    int iChars = lstrlen (achTempAlias);
    if (0 == iChars)
    {
        if (hOwnerWnd)
        {
            PrivateMessageBox (IDS_MSG_NO_OBJECT_ALIAS, hOwnerWnd, 0);
        }
        return FALSE;
    }
    if (!isalpha (achTempAlias[0]))
    {
        if (hOwnerWnd)
        {
            PrivateMessageBox (IDS_MSG_INVALID_OBJECT_ALIAS, hOwnerWnd, 0);
        }
        return FALSE;
    }
    
    for (int i=1; i<iChars; i++)
    {
        if (!isdigit(achTempAlias[i]) &&
            !isalpha(achTempAlias[i]) &&
            '-' != achTempAlias[i] &&
            '_' != achTempAlias[i])
        {
            if (hOwnerWnd)
            {
                PrivateMessageBox (IDS_MSG_INVALIS_CHARS_IN_ALIAS, hOwnerWnd, 0);
            }
            return FALSE;
        }
    }
    lstrcpy (szObjAlias, achTempAlias);
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//    MBProps1DlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK MBProps1DlgProc (HWND    hDlg, 
                               UINT    message, 
                               WPARAM  wParam, 
                               LPARAM  lParam)
{
    static POBJECT_INFO pObjInfo = NULL;
    static HWND hAliasLabel;
    switch (message)
    {
        case WM_INITDIALOG :
            {
                // The pointer to the folder object came in the PROPSHEETPAGE
                // structure. The lParam of this message has a pointer to the
                // structure used to create this page. Get the OBJECT_INFO
                // pointer and save it.
                pObjInfo = (POBJECT_INFO)((PROPSHEETPAGE *)lParam)->lParam;
                CTL3D_Subclass(g_pctl3d, hDlg, CTL3D_ALL);
                HWND hCtl = GetDlgItem (hDlg, IDC_OBJECT_ALIAS);
                SetWindowText (hCtl, pObjInfo->MB.szMailboxName);
                if (0 == pObjInfo->MB.dwObjID)
                {
                    EnableWindow (hCtl, TRUE);
                    Edit_LimitText (hCtl, MAX_ALIAS_SIZE);
                    hCtl = GetDlgItem (hDlg, IDC_OBJECT_ALIAS_LABEL);
                    EnableWindow (hCtl, TRUE);
                }

                hCtl = GetDlgItem (hDlg, IDC_MAILBOX_OWNER);
                Edit_LimitText (hCtl, MAX_STRING_SIZE);
                SetWindowText (hCtl, pObjInfo->MB.szFullName);

                hCtl = GetDlgItem (hDlg, IDC_MAILBOX_JOBTITLE);
                Edit_LimitText (hCtl, MAX_STRING_SIZE);
                SetWindowText (hCtl, pObjInfo->MB.szJobTitle);

                hCtl = GetDlgItem (hDlg, IDC_MAILBOX_OFFICE);
                Edit_LimitText (hCtl, MAX_STRING_SIZE);
                SetWindowText (hCtl, pObjInfo->MB.szOffice);

                hAliasLabel = GetDlgItem (hDlg, IDC_ICON_TITLE);
                SetWindowText (hAliasLabel, pObjInfo->MB.szMailboxName);
                SetWindowFont (hAliasLabel, ghBoldFont, TRUE);

                if (OBJECT_DISABLED & pObjInfo->MB.dwFlags)
                {
                    Button_SetCheck (GetDlgItem (hDlg, IDC_DISABLE), BST_CHECKED);
                }
                if (HIDE_IN_DIR & pObjInfo->MB.dwFlags)
                {
                    Button_SetCheck (GetDlgItem (hDlg, IDC_HIDE), BST_CHECKED);
                }
                Static_SetIcon (GetDlgItem (hDlg, IDC_PAGE_ICON),
                                ImageList_GetIcon (g_hIconImgs, ICON_MAILBOX, ILD_NORMAL));
            }
            return TRUE;

        case WM_NOTIFY :
            if (PSN_APPLY == ((LPNMHDR)lParam)->code)
            {
                if (BST_CHECKED == Button_GetCheck (GetDlgItem (hDlg, IDC_DISABLE)))
                {
                    pObjInfo->MB.dwFlags |= OBJECT_DISABLED;
                }
                else
                {
                    pObjInfo->MB.dwFlags &= ~OBJECT_DISABLED;
                }
                if (BST_CHECKED == Button_GetCheck (GetDlgItem (hDlg, IDC_HIDE)))
                {
                    pObjInfo->MB.dwFlags |= HIDE_IN_DIR;
                }
                else
                {
                    pObjInfo->MB.dwFlags &= ~HIDE_IN_DIR;
                }
                GetWindowText (GetDlgItem (hDlg, IDC_OBJECT_ALIAS),
                               pObjInfo->MB.szMailboxName,
                               MAX_ALIAS_SIZE+1);
                GetWindowText (GetDlgItem (hDlg, IDC_MAILBOX_OWNER),
                               pObjInfo->MB.szFullName,
                               MAX_STRING_SIZE+1);
                GetWindowText (GetDlgItem (hDlg, IDC_MAILBOX_JOBTITLE),
                               pObjInfo->MB.szJobTitle,
                               MAX_STRING_SIZE+1);
                GetWindowText (GetDlgItem (hDlg, IDC_MAILBOX_OFFICE),
                               pObjInfo->MB.szOffice,
                               MAX_STRING_SIZE+1);
                
                return PSNRET_NOERROR;
            }
            break;

        case WM_COMMAND :
            if (HIWORD(wParam) == EN_CHANGE && LOWORD(wParam) == IDC_OBJECT_ALIAS)
            {
                GetWindowText ((HWND)lParam, pObjInfo->MB.szMailboxName, MAX_ALIAS_SIZE+1);
                SetWindowText (hAliasLabel, pObjInfo->MB.szMailboxName);
            }
            break;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    MBProps2DlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK MBProps2DlgProc (HWND    hDlg, 
                               UINT    message, 
                               WPARAM  wParam, 
                               LPARAM  lParam)
{
    static POBJECT_INFO pObjInfo = NULL;
    switch (message)
    {   
        case WM_INITDIALOG :
            {
                // The pointer to the folder object came in the PROPSHEETPAGE
                // structure. The lParam of this message has a pointer to the
                // structure used to create this page. Get the OBJECT_INFO
                // pointer and save it.
                pObjInfo = (POBJECT_INFO)((PROPSHEETPAGE *)lParam)->lParam;
                
                CTL3D_Subclass(g_pctl3d, hDlg, CTL3D_ALL);
                HWND hCtl = GetDlgItem (hDlg, IDC_MAILBOX_PHONE);
                Edit_LimitText (hCtl, MAX_PHONE_SIZE);
                SetWindowText (hCtl, pObjInfo->MB.szPhone);

                hCtl = GetDlgItem (hDlg, IDC_MAILBOX_FAX);
                Edit_LimitText (hCtl, MAX_PHONE_SIZE);
                SetWindowText (hCtl, pObjInfo->MB.szFax);

                hCtl = GetDlgItem (hDlg, IDC_MAILBOX_ALTPHONE);
                Edit_LimitText (hCtl, MAX_PHONE_SIZE);
                SetWindowText (hCtl, pObjInfo->MB.szAltPhone);

                hCtl = GetDlgItem (hDlg, IDC_ICON_TITLE);
                SetWindowText (hCtl, pObjInfo->MB.szMailboxName);
                SetWindowFont (hCtl, ghBoldFont, TRUE);
                Static_SetIcon (GetDlgItem (hDlg, IDC_PAGE_ICON),
                                ImageList_GetIcon (g_hIconImgs, ICON_PHONE_HAND, ILD_NORMAL));
            }
            return TRUE;

        case WM_NOTIFY :
            if (PSN_APPLY == ((LPNMHDR)lParam)->code)
            {
                GetWindowText (GetDlgItem (hDlg, IDC_MAILBOX_PHONE),
                               pObjInfo->MB.szPhone,
                               MAX_PHONE_SIZE+1);
                GetWindowText (GetDlgItem (hDlg, IDC_MAILBOX_FAX),
                               pObjInfo->MB.szFax,
                               MAX_PHONE_SIZE+1);
                GetWindowText (GetDlgItem (hDlg, IDC_MAILBOX_ALTPHONE),
                               pObjInfo->MB.szAltPhone,
                               MAX_PHONE_SIZE+1);
                return PSNRET_NOERROR;
            }
            break;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    MBProps3DlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK MBProps3DlgProc (HWND    hDlg, 
                               UINT    message, 
                               WPARAM  wParam, 
                               LPARAM  lParam)
{
    static POBJECT_INFO pObjInfo = NULL;
    switch (message)
    {   
        case WM_INITDIALOG :
            {
                // The pointer to the folder object came in the PROPSHEETPAGE
                // structure. The lParam of this message has a pointer to the
                // structure used to create this page. Get the OBJECT_INFO
                // pointer and save it.
                pObjInfo = (POBJECT_INFO)((PROPSHEETPAGE *)lParam)->lParam;
                
                CTL3D_Subclass(g_pctl3d, hDlg, CTL3D_ALL);
                HWND hCtl = GetDlgItem (hDlg, IDC_MAILBOX_PHONE);
                Edit_LimitText (hCtl, MAX_PHONE_SIZE);
                SetWindowText (hCtl, pObjInfo->MB.szPhone);

                hCtl = GetDlgItem (hDlg, IDC_COMPANY);
                Edit_LimitText (hCtl, MAX_STRING_SIZE);
                SetWindowText (hCtl, pObjInfo->MB.szCompany);

                hCtl = GetDlgItem (hDlg, IDC_DEPARTMENT);
                Edit_LimitText (hCtl, MAX_STRING_SIZE);
                SetWindowText (hCtl, pObjInfo->MB.szDepartment);
                
                hCtl = GetDlgItem (hDlg, IDC_MANAGER);
                Edit_LimitText (hCtl, MAX_STRING_SIZE);
                SetWindowText (hCtl, pObjInfo->MB.szManagerName);

                hCtl = GetDlgItem (hDlg, IDC_MAILBOX_COMMENTS);
                Edit_LimitText (hCtl, MAX_COMMENT_SIZE);
                SetWindowText (hCtl, pObjInfo->MB.szComments);

                
                hCtl = GetDlgItem (hDlg, IDC_ICON_TITLE);
                SetWindowText (hCtl, pObjInfo->MB.szMailboxName);
                SetWindowFont (hCtl, ghBoldFont, TRUE);
                Static_SetIcon (GetDlgItem (hDlg, IDC_PAGE_ICON),
                                ImageList_GetIcon (g_hIconImgs, ICON_WORLD, ILD_NORMAL));
            }
            return TRUE;

        case WM_NOTIFY :
            if (PSN_APPLY == ((LPNMHDR)lParam)->code)
            {
                GetWindowText (GetDlgItem (hDlg, IDC_COMPANY),
                               pObjInfo->MB.szCompany,
                               MAX_STRING_SIZE+1);
                GetWindowText (GetDlgItem (hDlg, IDC_DEPARTMENT),
                               pObjInfo->MB.szDepartment,
                               MAX_STRING_SIZE+1);
                GetWindowText (GetDlgItem (hDlg, IDC_MAILBOX_COMMENTS),
                               pObjInfo->MB.szComments,
                               MAX_COMMENT_SIZE+1);
                return PSNRET_NOERROR;
            }
            break;

        case WM_COMMAND :
            if (LOWORD(wParam) == IDC_BROWSE)
            {
                if (TRUE == DialogBoxParam (ghInstance,
                                            MAKEINTRESOURCE(IDD_ONE_MAILBOX),
                                            hDlg,
                                            SelectUserDlgProc,
                                            (LPARAM)pObjInfo))
                {
                    SetWindowText (GetDlgItem (hDlg, IDC_MANAGER), pObjInfo->MB.szManagerName);
                }
            }
            break;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    MBProps4DlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK MBProps4DlgProc (HWND    hDlg, 
                               UINT    message, 
                               WPARAM  wParam, 
                               LPARAM  lParam)
{
    static POBJECT_INFO pObjInfo = NULL;
    switch (message)
    {   
        case WM_INITDIALOG :
            {
                // The pointer to the folder object came in the PROPSHEETPAGE
                // structure. The lParam of this message has a pointer to the
                // structure used to create this page. Get the OBJECT_INFO
                // pointer and save it.
                pObjInfo = (POBJECT_INFO)((PROPSHEETPAGE *)lParam)->lParam;
                CTL3D_Subclass(g_pctl3d, hDlg, CTL3D_ALL);
                HWND hCtl = GetDlgItem (hDlg, IDC_MAILBOX_PASSWORD);
                Edit_LimitText (hCtl, MAX_PASSWORD_SIZE);
                SetWindowText (hCtl, pObjInfo->MB.szPassword);

                hCtl = GetDlgItem (hDlg, IDC_ICON_TITLE);
                SetWindowText (hCtl, pObjInfo->MB.szMailboxName);
                SetWindowFont (hCtl, ghBoldFont, TRUE);
                Static_SetIcon (GetDlgItem (hDlg, IDC_PAGE_ICON),
                                ImageList_GetIcon (g_hIconImgs, ICON_KEY, ILD_NORMAL));
            }
            return TRUE;

        case WM_NOTIFY :
            if (PSN_APPLY == ((LPNMHDR)lParam)->code)
            {
                GetWindowText (GetDlgItem (hDlg, IDC_MAILBOX_PASSWORD),
                               pObjInfo->MB.szPassword,
                               MAX_STRING_SIZE+1);
                return PSNRET_NOERROR;
            }
            break;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    MBProps5DlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK MBProps5DlgProc (HWND    hDlg, 
                               UINT    message, 
                               WPARAM  wParam, 
                               LPARAM  lParam)
{
    static POBJECT_INFO pObjInfo = NULL;
    switch (message)
    {   
        case WM_INITDIALOG :
            {
                // The pointer to the folder object came in the PROPSHEETPAGE
                // structure. The lParam of this message has a pointer to the
                // structure used to create this page. Get the OBJECT_INFO
                // pointer and save it.
                pObjInfo = (POBJECT_INFO)((PROPSHEETPAGE *)lParam)->lParam;
                CTL3D_Subclass(g_pctl3d, hDlg, CTL3D_ALL);
                HWND hCtl = GetDlgItem (hDlg, IDC_ICON_TITLE);
                SetWindowText (hCtl, pObjInfo->MB.szMailboxName);
                SetWindowFont (hCtl, ghBoldFont, TRUE);

                hCtl = GetDlgItem (hDlg, IDC_NYI_LABEL);
                SetWindowFont (hCtl, ghBoldFont, TRUE);

                Static_SetIcon (GetDlgItem (hDlg, IDC_PAGE_ICON),
                                ImageList_GetIcon (g_hIconImgs, ICON_PEOPLE, ILD_NORMAL));
                Static_SetIcon (GetDlgItem (hDlg, IDC_CONSTRUCT_ICON),
                                ImageList_GetIcon (g_hIconImgs, ICON_CONSTRUCT, ILD_NORMAL));
            }
            return TRUE;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    MBProps6DlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK MBProps6DlgProc (HWND    hDlg, 
                               UINT    message, 
                               WPARAM  wParam, 
                               LPARAM  lParam)
{
    static POBJECT_INFO pObjInfo = NULL;
    switch (message)
    {   
        case WM_INITDIALOG :
            {
                // The pointer to the folder object came in the PROPSHEETPAGE
                // structure. The lParam of this message has a pointer to the
                // structure used to create this page. Get the OBJECT_INFO
                // pointer and save it.
                pObjInfo = (POBJECT_INFO)((PROPSHEETPAGE *)lParam)->lParam;
                CTL3D_Subclass(g_pctl3d, hDlg, CTL3D_ALL);
                HWND hCtl = GetDlgItem (hDlg, IDC_ICON_TITLE);
                SetWindowText (hCtl, pObjInfo->MB.szMailboxName);
                SetWindowFont (hCtl, ghBoldFont, TRUE);

                hCtl = GetDlgItem (hDlg, IDC_NYI_LABEL);
                SetWindowFont (hCtl, ghBoldFont, TRUE);

                Static_SetIcon (GetDlgItem (hDlg, IDC_PAGE_ICON),
                                ImageList_GetIcon (g_hIconImgs, ICON_AUTO_REPLY, ILD_NORMAL));
                Static_SetIcon (GetDlgItem (hDlg, IDC_CONSTRUCT_ICON),
                                ImageList_GetIcon (g_hIconImgs, ICON_CONSTRUCT, ILD_NORMAL));
            }
            return TRUE;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    GetServerMailboxes()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
HRESULT WINAPI GetServerMailboxes (HWND hOwnerWnd)
{
    return DownloadBulkInfo (hOwnerWnd, ghListView, ITEM_SERVER_USER_MAILBOXES);
}

///////////////////////////////////////////////////////////////////////////////
//    PurgeMailboxMessages()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
void WINAPI PurgeMailboxMessages (HWND hOwnerWnd, DWORD dwObjID)
{
    if (IDNO == PrivateMessageBox (IDS_MSG_CONFIRM_MB_MSGS_PURGE,
                                   hOwnerWnd,
                                   MB_YESNO | MB_ICONEXCLAMATION))
    {
        return;
    }
    HRESULT hResult = S_OK;
    RpcTryExcept
    {
        hResult = RemoteAdmEmptyMailbox (dwObjID);
    }
    RpcExcept(1)
    {        
        // If we got here is because there was an error while call was made
        // or when it was about to be made.
        hResult = RpcExceptionCode();
        if (RPC_S_SERVER_UNAVAILABLE == hResult)
        {
            hResult = HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE);
        }
        else
        {
            hResult = MAKE_HRESULT(1, FACILITY_RPC, hResult);
        }
    }
    RpcEndExcept
    if (hResult)
    {
        ErrorHandler (hOwnerWnd, hResult);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    BrowseFileName()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
BOOL WINAPI BrowseFileName (HWND hOwnerWnd, LPTSTR szFileName, BOOL fImport)
{
    szFileName[0] = NULL;
    // Filter for files for the browse file dialog box
    static LPTSTR szFilter = TEXT("Comma Delimeted (*.CSV)\0*.CSV\0All Files (*.*)\0*.*\0");
    OPENFILENAME ofn = { 0 };
    ofn.lStructSize  = sizeof(OPENFILENAME);
    ofn.hwndOwner    = hOwnerWnd;
    ofn.hInstance    = ghInstance;
    ofn.lpstrFilter  = szFilter;
    ofn.nFilterIndex = 1;
    ofn.lpstrFile    = szFileName;
    ofn.nMaxFile     = _MAX_PATH;
    ofn.lpstrTitle   = TEXT("WINDS Administrator - File Browse");
    ofn.lpstrDefExt  = TEXT("*.CSV");
    if (fImport)
    {
        ofn.Flags = OFN_HIDEREADONLY |
                    OFN_PATHMUSTEXIST |
                    OFN_FILEMUSTEXIST;
    }
    else
    {
        ofn.Flags = OFN_HIDEREADONLY |
                    OFN_OVERWRITEPROMPT |
                    OFN_CREATEPROMPT    |
                    OFN_NOREADONLYRETURN;
    }
    
    BOOL fReturn; 
    if (fImport)
    {
        fReturn = GetOpenFileName (&ofn);
    }
    else
    {
        fReturn = GetSaveFileName (&ofn);
    }
    return fReturn;
}

///////////////////////////////////////////////////////////////////////////////
//    ExportDlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK ExportDlgProc (HWND    hDlg, 
                             UINT    message, 
                             WPARAM  wParam, 
                             LPARAM  lParam)
{
    static BOOL fMailboxes, fGwayDirs;
    TCHAR szFile[_MAX_PATH];
    switch (message)
    {
        case WM_INITDIALOG :
            CenterDialogBox (hDlg);
            SetFocus (GetDlgItem (hDlg, IDC_BROWSE));
            Button_SetCheck (GetDlgItem (hDlg, IDC_MAILBOXES), BST_CHECKED);
            Button_SetCheck (GetDlgItem (hDlg, IDC_GW_DIRECTORIES), BST_CHECKED);
            fMailboxes = fGwayDirs = TRUE;
            Static_SetIcon (GetDlgItem (hDlg, IDC_PAGE_ICON),
                            ImageList_GetIcon (g_hIconImgs, ICON_LABELS, ILD_NORMAL));
            return TRUE;

        case WM_COMMAND :
            switch (LOWORD(wParam))
            {
                case IDC_MAILBOXES :
                case IDC_GW_DIRECTORIES :
                    if (HIWORD(wParam) == BN_CLICKED)
                    {
                        if (LOWORD(wParam) == IDC_MAILBOXES)
                        {
                            fMailboxes = !fMailboxes;
                        }
                        else
                        {
                            fGwayDirs = !fGwayDirs;
                        }
                        if (fGwayDirs || fMailboxes)
                        {
                            EnableWindow (GetDlgItem (hDlg, IDOK), TRUE);
                        }
                        else
                        {
                            EnableWindow (GetDlgItem (hDlg, IDOK), FALSE);
                        }
                    }
                    break;

                case IDC_BROWSE :
                    if (BrowseFileName (hDlg, szFile, FALSE))
                    {
                        SetWindowText (GetDlgItem (hDlg, IDC_FILENAME), szFile);
                    }
                    break;

                case IDOK :
                    if (!GetWindowText (GetDlgItem (hDlg, IDC_FILENAME), szFile, _MAX_PATH))
                    {
                        break;
                    }
                    DialogBoxParam (ghInstance,
                                    MAKEINTRESOURCE (IDD_EXPORT_STATE),
                                    hDlg,
                                    ExportProgressDlgProc,
                                    (LPARAM)szFile);
                    break;

                case IDCANCEL :
                    EndDialog (hDlg, TRUE);
                    return TRUE;
            }
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    ImportDlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK ImportDlgProc (HWND    hDlg, 
                             UINT    message, 
                             WPARAM  wParam, 
                             LPARAM  lParam)
{
    TCHAR szFile[_MAX_PATH];
    switch (message)
    {
        case WM_INITDIALOG :
            CenterDialogBox (hDlg);
            PostMessage (hDlg, WM_COMMAND, IDC_BROWSE, 0);
            Static_SetIcon (GetDlgItem (hDlg, IDC_PAGE_ICON),
                            ImageList_GetIcon (g_hIconImgs, ICON_CLIP, ILD_NORMAL));
            return TRUE;

        case WM_COMMAND :
            switch (LOWORD(wParam))
            {
                case IDC_BROWSE :
                    if (BrowseFileName (hDlg, szFile, TRUE))
                    {
                        SetWindowText (GetDlgItem (hDlg, IDC_FILENAME), szFile);
                    }
                    break;

                case IDOK :
                    if (!GetWindowText (GetDlgItem (hDlg, IDC_FILENAME), szFile, _MAX_PATH))
                    {
                        break;
                    }
                    DialogBoxParam (ghInstance,
                                    MAKEINTRESOURCE (IDD_IMPORT_STATE),
                                    hDlg,
                                    ImportProgressDlgProc,
                                    (LPARAM)szFile);
                    break;

                case IDCANCEL :
                    EndDialog (hDlg, TRUE);
                    return TRUE;
            }
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    ImportProgressDlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK ImportProgressDlgProc (HWND    hDlg, 
                                     UINT    message, 
                                     WPARAM  wParam, 
                                     LPARAM  lParam)
{
    switch (message)
    {
        case WM_INITDIALOG :
            {
                SetWindowLong (hDlg, GWL_USERDATA, (long)lParam);
                CTL3D_Subclass(g_pctl3d, hDlg, CTL3D_ALL);
                
                Static_SetIcon (GetDlgItem (hDlg, IDC_STOPWATCH), GetAnimatedTimerCursor());
                
                SetWindowFont (GetDlgItem (hDlg, IDC_ICON_TITLE), ghBoldFont, FALSE);
                SetWindowFont (GetDlgItem (hDlg, IDC_MAILBOX_LABEL), ghBoldFont, FALSE);

                int nTabStops[1] = { 80 };
                ListBox_SetTabStops (GetDlgItem (hDlg, IDC_IMPORT_LIST), sizeof(nTabStops)/sizeof(int), nTabStops);

                PostMessage (hDlg, WM_WINDS_IMPORT_START, 0, 0);
            }
            return TRUE;

        case WM_WINDS_IMPORT_START :
            {
                DWORD dwThreadID;
                HANDLE hThread = CreateThread (NULL,
                                               0,
                                               (LPTHREAD_START_ROUTINE)ImportDirectoryFromFile,
                                               (LPVOID)hDlg,
                                               0,
                                               &dwThreadID);
                if (hThread)
                {
                    CloseHandle (hThread);
                }
                else
                {
                    PostMessage (hDlg,
                                 WM_WINDS_IMPORT_FINISHED,
                                 HRESULT_FROM_WIN32(GetLastError()),
                                 0);
                }
            }
            break;

        case WM_WINDS_IMPORT_FINISHED :
            EnableWindow (GetDlgItem (hDlg, IDOK), TRUE);
            EnableWindow (GetDlgItem (hDlg, IDCANCEL), FALSE);
            Static_SetIcon (GetDlgItem (hDlg, IDC_STOPWATCH),
                            ImageList_GetIcon (g_hIconImgs, ICON_TIMEUP, ILD_NORMAL));
            if (wParam)
            {
                ErrorHandler (hDlg, wParam);
            }
            break;

        case WM_COMMAND :
            switch (LOWORD(wParam))
            {
                case IDCANCEL :
                    SetEvent (ghCancelEvent);
                    break;

                case IDOK :
                    EndDialog (hDlg, TRUE);
                    return TRUE;
            }
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    ExportProgressDlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK ExportProgressDlgProc (HWND    hDlg, 
                                     UINT    message, 
                                     WPARAM  wParam, 
                                     LPARAM  lParam)
{
    switch (message)
    {
        case WM_INITDIALOG :
            {
                SetWindowLong (hDlg, GWL_USERDATA, (long)lParam);
                CTL3D_Subclass(g_pctl3d, hDlg, CTL3D_ALL);
                
                Static_SetIcon (GetDlgItem (hDlg, IDC_STOPWATCH), GetAnimatedTimerCursor());
                
                SetWindowFont (GetDlgItem (hDlg, IDC_ICON_TITLE), ghBoldFont, FALSE);
                SetWindowFont (GetDlgItem (hDlg, IDC_MAILBOX_LABEL), ghBoldFont, FALSE);

                PostMessage (hDlg, WM_WINDS_EXPORT_START, 0, 0);
            }
            return TRUE;

        case WM_WINDS_EXPORT_START :
            {
                DWORD dwThreadID;
                HANDLE hThread = CreateThread (NULL,
                                               0,
                                               (LPTHREAD_START_ROUTINE)ExportDirectoryToFile,
                                               (LPVOID)hDlg,
                                               0,
                                               &dwThreadID);
                if (hThread)
                {
                    CloseHandle (hThread);
                }
                else
                {
                    PostMessage (hDlg,
                                 WM_WINDS_EXPORT_FINISHED,
                                 HRESULT_FROM_WIN32(GetLastError()),
                                 0);
                }
            }
            break;

        case WM_WINDS_EXPORT_FINISHED :
            TraceMessage ("Export Finished");
            EnableWindow (GetDlgItem (hDlg, IDOK), TRUE);
            EnableWindow (GetDlgItem (hDlg, IDCANCEL), FALSE);
            Static_SetIcon (GetDlgItem (hDlg, IDC_STOPWATCH),
                            ImageList_GetIcon (g_hIconImgs, ICON_TIMEUP, ILD_NORMAL));
            if (wParam)
            {
                ErrorHandler (hDlg, wParam);
            }
            break;

        case WM_COMMAND :
            switch (LOWORD(wParam))
            {
                case IDCANCEL :
                    SetEvent (ghCancelEvent);
                    break;

                case IDOK :
                    EndDialog (hDlg, TRUE);
                    return TRUE;
            }
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    GetAnimatedTimerCursor()
//
//    Parameters
//
//    Purpose
//      
//    Return Value
//      
HCURSOR WINAPI GetAnimatedTimerCursor()
{
    static HCURSOR hCursor = NULL;
    if (hCursor)
    {
        return hCursor;
    }
    HMODULE hModule;
    HRSRC hResource;
    DWORD dwBytes, dwSize;
    TCHAR szANIFile[MAX_PATH];
    GetTempPath (MAX_PATH, szANIFile);
    lstrcat (szANIFile, TEXT("__WINDS_TIMER__CURSOR.ANI"));
    HANDLE hResBits, hFile = CreateFile (szANIFile,
                                         GENERIC_WRITE,
                                         0,
                                         NULL,
                                         CREATE_ALWAYS,
                                         FILE_ATTRIBUTE_NORMAL,
                                         NULL);
    if (INVALID_HANDLE_VALUE == hFile)
    {   
        TraceResult ("GetAnimatedTimerCursor: Failed to create temp file", HRESULT_FROM_WIN32(GetLastError()));
    }
    else
    {
        hModule = GetModuleHandle (NULL);
        hResource = FindResource (hModule, TEXT("#5000"), RT_RCDATA);
        hResBits = LoadResource (hModule, hResource);
        dwSize = SizeofResource (hModule, hResource);
        WriteFile (hFile, (LPVOID)hResBits, dwSize, &dwBytes, NULL);
        CloseHandle (hFile);
        FreeResource (hResource);
        hCursor = LoadCursorFromFile (szANIFile);
        DeleteFile (szANIFile);
    }
    return hCursor;
}

// End of file for ADMMBOX.CPP
