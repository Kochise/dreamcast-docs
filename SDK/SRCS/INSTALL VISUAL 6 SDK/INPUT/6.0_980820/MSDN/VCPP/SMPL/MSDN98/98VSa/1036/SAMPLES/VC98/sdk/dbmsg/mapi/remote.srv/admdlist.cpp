///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      ADMDLIST.CPP
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
    HRESULT WINAPI DisplayDistListPropSheets
                        (HWND                       hOwnerWnd,
                         POBJECT_INFO               pObjInfo,
                         BOOL                       fCreate);
    BOOL CALLBACK DLProps1DlgProc
                        (HWND                       hDlg, 
                         UINT                       message, 
                         WPARAM                     wParam, 
                         LPARAM                     lParam);
    BOOL CALLBACK DLProps2DlgProc
                        (HWND                       hDlg, 
                         UINT                       message, 
                         WPARAM                     wParam, 
                         LPARAM                     lParam);
    BOOL CALLBACK DLProps3DlgProc
                        (HWND                       hDlg, 
                         UINT                       message, 
                         WPARAM                     wParam, 
                         LPARAM                     lParam);
    BOOL CALLBACK ModifyListDlgProc
                        (HWND                       hDlg, 
                         UINT                       message, 
                         WPARAM                     wParam, 
                         LPARAM                     lParam);
    BOOL CALLBACK WaitDlgProc
                        (HWND                       hDlg, 
                         UINT                       message, 
                         WPARAM                     wParam, 
                         LPARAM                     lParam);
    void WINAPI AddMembersToPageLV
                        (HWND                       hOwnerWnd,
                         HWND                       hListView,
                         DLM_LIST *                 pMembers);
};

///////////////////////////////////////////////////////////////////////////////
//    GetServerDistLists()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
HRESULT WINAPI GetServerDistLists (HWND hOwnerWnd)
{
    return DownloadBulkInfo (hOwnerWnd, ghListView, ITEM_SERVER_DIST_LISTS);
}

///////////////////////////////////////////////////////////////////////////////
//    DownloadBulkInfo()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
HRESULT WINAPI DownloadBulkInfo (HWND hOwnerWnd, HWND hListView, ITEM_TYPE Type)
{
    LV_ITEM lvi = { 0 };
    lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
    int i = 0;
    long lPipeNum;
    TCHAR achPipeName[128];
    LPTSTR szObjAlias;
    HANDLE hPipe;
    DWORD dwBytesRead;
    DWORD * pdwObjID;
    AB_ENTRY_INFO abEntry = { 0 };
    HRESULT hResult = S_OK;
    EnterCriticalSection (&csRemoteServer);
    SendMessage (hOwnerWnd, WM_WINDS_REMOTE_CALL_IN_PROGRESS, hResult, 0);
    ListView_DeleteAllItems (hListView);
    SendMessage (ghStatusBar, SB_SETTEXT, 0, (LPARAM)TEXT("Connecting to the server..."));
    RpcTryExcept
    {
        // Make the remote call to request the server to open a pipe for the download
        switch (Type)
        {
            case ITEM_SERVER_USER_MAILBOXES :
                hResult = RemoteAdmGetServerMailboxes (&lPipeNum);
                lvi.iImage = IMG_USER_MAILBOX;
                pdwObjID = &(abEntry.Info.MB.dwObjID);
                szObjAlias = abEntry.Info.MB.szMailboxName;
                break;
            case ITEM_SERVER_DIST_LISTS :
                hResult = RemoteAdmGetServerDistLists (&lPipeNum);
                lvi.iImage = IMG_DIST_LIST;
                pdwObjID = &(abEntry.Info.DL.dwObjID);
                szObjAlias = abEntry.Info.DL.szDLAlias;
                break;
            default :
                ASSERTMSG (FALSE, "Unknown item type");
                hResult = E_FAIL;
                break;
        }
        if (!hResult)
        {
            SendMessage (ghStatusBar, SB_SETTEXT, 0, (LPARAM)TEXT("Connection established... Pending pipe connection..."));
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
        SendMessage (ghStatusBar, SB_SETTEXT, 0, (LPARAM)TEXT("Pipe opened. Downloading server information..."));
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
                    TraceResult ("DownloadBulkInfo: Failed to read from the source", hResult);
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
                lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
                lvi.iItem = i;
                lvi.iSubItem = 0;
                lvi.pszText = szObjAlias;
                lvi.lParam = *pdwObjID;
                lvi.iItem = ListView_InsertItem (hListView, &lvi);
                
                switch (Type)
                {
                    case ITEM_SERVER_USER_MAILBOXES :
                        ListView_SetItemText (hListView, lvi.iItem, 1, abEntry.Info.MB.szFullName);
                        ListView_SetItemText (hListView, lvi.iItem, 2, abEntry.Info.MB.szJobTitle);
                        ListView_SetItemText (hListView, lvi.iItem, 3, abEntry.Info.MB.szOffice);
                        ListView_SetItemText (hListView, lvi.iItem, 4, abEntry.Info.MB.szDepartment);
                        ListView_SetItemText (hListView, lvi.iItem, 5, abEntry.Info.MB.szPhone);
                        ListView_SetItemText (hListView, lvi.iItem, 6, abEntry.Info.MB.szFax);
                        break;
                    case ITEM_SERVER_DIST_LISTS :
                        ListView_SetItemText (hListView, lvi.iItem, 1, abEntry.Info.DL.szDLFullName);
                        break;
                }
                i++;
            }
            if (AbortRemoteCall())
            {
                dwBytesRead = 0; // This will cause the DO-WHILE() loop to terminate
                hResult = S_OK; // If the user aborted the call, don't return any error.
            }
        } while (dwBytesRead && !hResult);
        CloseHandle (hPipe);
        SendMessage (ghStatusBar, SB_SETTEXT, 0, (LPARAM)TEXT("Connection Closed..."));
    }
    LeaveCriticalSection (&csRemoteServer);
    TraceResult ("DownloadBulkInfo", hResult);
    SendMessage (hOwnerWnd, WM_WINDS_REMOTE_CALL_COMPLETED, hResult, 0);
    return hResult;
}

///////////////////////////////////////////////////////////////////////////////
//    CreateNewDistList()
//
//    Parameters
//      
//    Purpose
//
//    Return Value
//
void WINAPI CreateNewDistList (HWND hOwnerWnd)
{
    DLM_XMIT_LIST Members = { 0 };
    OBJECT_INFO ObjInfo = { 0 };
    ObjInfo.DL.pMembers = &Members;
    ObjInfo.Type = SERVER_DISTRIBUTION_LIST;
    HRESULT hResult = DisplayDistListPropSheets (hOwnerWnd, &ObjInfo, TRUE);
    if (!hResult)
    {
        RpcTryExcept
        {
            hResult = RemoteAdmCreateDistList ((WINDS_RPC_STRING)ObjInfo.DL.szDLAlias,
                                               (WINDS_RPC_STRING)ObjInfo.DL.szDLFullName,
                                               ObjInfo.DL.dwFlags,
                                               (WINDS_RPC_STRING)ObjInfo.DL.szOwnerAlias,
                                               (WINDS_RPC_STRING)ObjInfo.DL.szOwnerName,
                                               ObjInfo.DL.dwOwnerID,
                                               &Members);
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
        FreeDLMList (&Members);
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
//    ShowDistListProps()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
void WINAPI ShowDistListProps (HWND hOwnerWnd, DWORD dwObjID)
{
    DLM_XMIT_LIST_A Members = { 0 };
    OBJECT_INFO ObjInfo = { 0 };
    ObjInfo.DL.dwObjID = dwObjID;
    ObjInfo.DL.pMembers = &Members;
    ObjInfo.Type = SERVER_DISTRIBUTION_LIST;

    HRESULT hResult = S_OK;
    RpcTryExcept
    {
        hResult = RemoteAdmGetDLProps (dwObjID,
                                       (WINDS_RPC_STRING)ObjInfo.DL.szDLAlias,
                                       (WINDS_RPC_STRING)ObjInfo.DL.szDLFullName,
                                       &ObjInfo.DL.dwFlags,
                                       (WINDS_RPC_STRING)ObjInfo.DL.szOwnerAlias,
                                       (WINDS_RPC_STRING)ObjInfo.DL.szOwnerName,
                                       &ObjInfo.DL.dwOwnerID,
                                       (WINDS_RPC_STRING)ObjInfo.DL.szComments,
                                       &Members);
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
        hResult = DisplayDistListPropSheets (hOwnerWnd, &ObjInfo, FALSE);
        if (S_OK == hResult)
        {
            RpcTryExcept
            {
                hResult = RemoteAdmSetDLProps (dwObjID,
                                               (WINDS_RPC_STRING)ObjInfo.DL.szDLAlias,
                                               (WINDS_RPC_STRING)ObjInfo.DL.szDLFullName,
                                               ObjInfo.DL.dwFlags,
                                               (WINDS_RPC_STRING)ObjInfo.DL.szOwnerAlias,
                                               (WINDS_RPC_STRING)ObjInfo.DL.szOwnerName,
                                               ObjInfo.DL.dwOwnerID,
                                               (WINDS_RPC_STRING)ObjInfo.DL.szComments,
                                               &Members);
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
        FreeDLMList (&Members);
    }
    if (hResult)
    {
        ErrorHandler (hOwnerWnd, hResult);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    DisplayDistListPropSheets()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      
HRESULT WINAPI DisplayDistListPropSheets (HWND           hOwnerWnd,
                                          POBJECT_INFO   pObjInfo,
                                          BOOL           fCreate)
{
    PROPSHEETHEADER psh = { 0 };
    PROPSHEETPAGE psp[3] = { 0 };
    TCHAR szHeaderTitle[64];

    OBJECT_INFO NewObjInfo = *pObjInfo;

    psp[0].dwSize      = sizeof(PROPSHEETPAGE);
    psp[0].dwFlags     = PSP_USETITLE;
    psp[0].hInstance   = ghInstance;
    psp[0].pszTemplate = MAKEINTRESOURCE (IDD_DL_PROPS1);
    psp[0].pfnDlgProc  = DLProps1DlgProc;
    psp[0].pszTitle    = TEXT("General");
    psp[0].lParam      = (LPARAM)&NewObjInfo;
    
    psp[1].dwSize      = sizeof(PROPSHEETPAGE);
    psp[1].dwFlags     = PSP_USETITLE;
    psp[1].hInstance   = ghInstance;
    psp[1].pszTemplate = MAKEINTRESOURCE (IDD_DL_PROPS2);
    psp[1].pfnDlgProc  = DLProps2DlgProc;
    psp[1].pszTitle    = TEXT("Members");
    psp[1].lParam      = (LPARAM)&NewObjInfo;

    psp[2].dwSize      = sizeof(PROPSHEETPAGE);
    psp[2].dwFlags     = PSP_USETITLE;
    psp[2].hInstance   = ghInstance;
    psp[2].pszTemplate = MAKEINTRESOURCE (IDD_DL_PROPS3);
    psp[2].pfnDlgProc  = DLProps3DlgProc;
    psp[2].pszTitle    = TEXT("Ownership");
    psp[2].lParam      = (LPARAM)&NewObjInfo;

    psh.dwSize     = sizeof(PROPSHEETHEADER);
    psh.dwFlags    = PSH_PROPSHEETPAGE | PSH_NOAPPLYNOW;
    psh.hwndParent = hOwnerWnd;
    psh.hInstance  = ghInstance;
    psh.nPages     = sizeof(psp)/sizeof(PROPSHEETPAGE);
    psh.ppsp       = (LPCPROPSHEETPAGE)&psp;
    if (fCreate)
    {
        psh.pszCaption = TEXT("New Distribution List Properties");
        psh.nStartPage = 0;
    }
    else
    {
        wsprintf (szHeaderTitle, TEXT("Distribution List Properties for %s"), pObjInfo->DL.szDLAlias);
        psh.pszCaption = szHeaderTitle;
        psh.nStartPage = 1;
    }

    // If the user hit OK and at least one of the properties changed,
    // we must change the properties on the server
ReEnterProperties:
    if (1 == PropertySheet (&psh) &&
        (fCreate || NewObjInfo.dwData ||
        NewObjInfo.DL.dwFlags != pObjInfo->DL.dwFlags ||
        NewObjInfo.DL.dwOwnerID != pObjInfo->DL.dwOwnerID ||
        lstrcmpi (NewObjInfo.DL.szDLFullName, pObjInfo->DL.szDLFullName) ||
        lstrcmpi (NewObjInfo.DL.szDLAlias, pObjInfo->DL.szDLAlias) ||
        lstrcmpi (NewObjInfo.DL.szComments, pObjInfo->DL.szComments)))
    {
        if (fCreate)
        {
            if (!IsObjAliasValid (hOwnerWnd, NewObjInfo.DL.szDLAlias))
            {
                goto ReEnterProperties;
            }
        }
        if (0 == lstrlen (NewObjInfo.DL.szDLFullName))
        {
            PrivateMessageBox (IDS_MSG_NO_DL_NAME, hOwnerWnd, 0);
            goto ReEnterProperties;
        }
        *pObjInfo = NewObjInfo;
        return S_OK;
    }
    return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    DLProps1DlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK DLProps1DlgProc (HWND    hDlg, 
                               UINT    message, 
                               WPARAM  wParam, 
                               LPARAM  lParam)
{
    static POBJECT_INFO pObjInfo = NULL;
    static HWND hCtlLabel;
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
                SetWindowText (hCtl, pObjInfo->DL.szDLAlias);
                if (0 == pObjInfo->DL.dwObjID)
                {
                    EnableWindow (hCtl, TRUE);
                    Edit_LimitText (hCtl, MAX_ALIAS_SIZE);
                    hCtl = GetDlgItem (hDlg, IDC_OBJECT_ALIAS_LABEL);
                    EnableWindow (hCtl, TRUE);
                }

                hCtl = GetDlgItem (hDlg, IDC_DL_FULLNAME);
                Edit_LimitText (hCtl, MAX_STRING_SIZE);
                SetWindowText (hCtl, pObjInfo->DL.szDLFullName);

                hCtlLabel = GetDlgItem (hDlg, IDC_ICON_TITLE);
                SetWindowText (hCtlLabel, pObjInfo->DL.szDLAlias);
                SetWindowFont (hCtlLabel, ghBoldFont, TRUE);

                if (OBJECT_DISABLED & pObjInfo->DL.dwFlags)
                {
                    Button_SetCheck (GetDlgItem (hDlg, IDC_DISABLE), BST_CHECKED);
                }
                if (HIDE_IN_DIR & pObjInfo->DL.dwFlags)
                {
                    Button_SetCheck (GetDlgItem (hDlg, IDC_HIDE), BST_CHECKED);
                }

                Static_SetIcon (GetDlgItem (hDlg, IDC_PAGE_ICON),
                                ImageList_GetIcon (g_hIconImgs, ICON_LARGE_ENVEL, ILD_NORMAL));
            }
            return TRUE;

        case WM_NOTIFY:
            if (PSN_APPLY == ((LPNMHDR)lParam)->code)
            {
                if (BST_CHECKED == Button_GetCheck (GetDlgItem (hDlg, IDC_DISABLE)))
                {
                    pObjInfo->DL.dwFlags |= OBJECT_DISABLED;
                }
                else
                {
                    pObjInfo->DL.dwFlags &= ~OBJECT_DISABLED;
                }
                if (BST_CHECKED == Button_GetCheck (GetDlgItem (hDlg, IDC_HIDE)))
                {
                    pObjInfo->DL.dwFlags |= HIDE_IN_DIR;
                }
                else
                {
                    pObjInfo->DL.dwFlags &= ~HIDE_IN_DIR;
                }
                GetWindowText (GetDlgItem (hDlg, IDC_OBJECT_ALIAS),
                               pObjInfo->DL.szDLAlias,
                               MAX_ALIAS_SIZE+1);
                GetWindowText (GetDlgItem (hDlg, IDC_DL_FULLNAME),
                               pObjInfo->DL.szDLFullName,
                               MAX_STRING_SIZE+1);
                return PSNRET_NOERROR;
            }
            break;

        case WM_COMMAND :
            if (HIWORD(wParam) == EN_CHANGE && LOWORD(wParam) == IDC_OBJECT_ALIAS)
            {
                GetWindowText ((HWND)lParam, pObjInfo->DL.szDLAlias, MAX_ALIAS_SIZE+1);
                SetWindowText (hCtlLabel, pObjInfo->DL.szDLAlias);
            }
            break;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    DLProps2DlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK DLProps2DlgProc (HWND    hDlg, 
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
                SetWindowText (hCtl, pObjInfo->DL.szDLAlias);
                SetWindowFont (hCtl, ghBoldFont, TRUE);

                hCtl = GetDlgItem (hDlg, IDC_MEMBERS);
                ListView_SetImageList (hCtl, g_hImages, LVSIL_SMALL);

                RECT rc;
                GetClientRect (hCtl, &rc);
                LV_COLUMN lvc;
                lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
                lvc.fmt = LVCFMT_LEFT;
                lvc.pszText = TEXT("Full Name");
                lvc.iSubItem = 0;
                lvc.cx = 160;
                ListView_InsertColumn (hCtl, 0, &lvc);
                lvc.pszText = TEXT("Alias");
                lvc.iSubItem = 1;
                lvc.cx = min (110, (rc.right - rc.left - lvc.cx));
                ListView_InsertColumn (hCtl, 1, &lvc);

                AddMembersToPageLV (hDlg, hCtl, (DLM_LIST *)pObjInfo->DL.pMembers);

                Static_SetIcon (GetDlgItem (hDlg, IDC_PAGE_ICON),
                                ImageList_GetIcon (g_hIconImgs, ICON_DL_MEMBERS, ILD_NORMAL));
            }
            return TRUE;

        case WM_DESTROY :
            ListView_SetImageList (GetDlgItem (hDlg, IDC_MEMBERS), NULL, LVSIL_SMALL);
            break;

        case WM_COMMAND :
            if (LOWORD(wParam) == IDC_MODIFY)
            {
                pObjInfo->pMembers = (DLM_LIST *)pObjInfo->DL.pMembers;
                if (TRUE == DialogBoxParam (ghInstance,
                                            MAKEINTRESOURCE(IDD_ADDTOLIST),
                                            hDlg,
                                            ModifyListDlgProc,
                                            (LPARAM)pObjInfo))
                {
                    AddMembersToPageLV (hDlg, GetDlgItem (hDlg, IDC_MEMBERS), (DLM_LIST *)pObjInfo->DL.pMembers);
                }
            }
            break;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    AddMembersToPageLV()
//
//    Parameters
//
//    Purpose
//      
//    Return Value
//      
void WINAPI AddMembersToPageLV (HWND        hOwnerWnd,
                                HWND        hListView,
                                DLM_LIST *  pMembers)
{
    ListView_DeleteAllItems (hListView);
    int i = 0;
    LV_ITEM lvi = { 0 };
    lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
    WINDS_AB_OBJTYPE Type;
    DLM_LIST * pNode = pMembers;
    while (pNode && pNode->Info.szMemberAlias[0])
    {
        Type = (WINDS_AB_OBJTYPE)pNode->Info.dwMemberType;
        switch (Type)
        {
            case GATEWAY_RECIPIENT :
            case SERVER_USER_MAILBOX :
                lvi.iImage = IMG_USER_MAILBOX;
                break;
            case ITEM_SERVER_DIST_LISTS :
                lvi.iImage = IMG_DIST_LIST;
                break;
            case PUBLIC_FOLDER :
                TraceMessage ("AddMembersToPageLV: Public Folder added - WARNING NYI");
            default :
                goto NextNode;
        }
        lvi.iItem = i;
        lvi.iSubItem = 0;
        lvi.pszText = (LPSTR)pNode->Info.szMemberName;
        lvi.lParam = pNode->Info.dwMemberID;
        lvi.iItem = ListView_InsertItem (hListView, &lvi);
        ListView_SetItemText (hListView, lvi.iItem, 1, (LPSTR)pNode->Info.szMemberAlias);
        i++;
NextNode:
        pNode = pNode->pNext;
    }
}

///////////////////////////////////////////////////////////////////////////////
//    DLProps3DlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK DLProps3DlgProc (HWND    hDlg, 
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
                SetWindowText (hCtl, pObjInfo->DL.szDLAlias);
                SetWindowFont (hCtl, ghBoldFont, TRUE);

                if (DL_OWNED & pObjInfo->DL.dwFlags)
                {
                    SetWindowText (GetDlgItem (hDlg, IDC_DL_OWNER), pObjInfo->DL.szOwnerName);
                    hCtl = GetDlgItem (hDlg, IDC_COMMENTS);
                    SetWindowText (hCtl, pObjInfo->DL.szComments);
                    Edit_LimitText (hCtl, sizeof(pObjInfo->DL.szComments)/sizeof(TCHAR) - 1);
                    hCtl = GetDlgItem (hDlg, IDC_OWNED);
                    Button_SetCheck (hCtl, BST_CHECKED);
                    PostMessage (hDlg, WM_COMMAND, MAKEWPARAM(IDC_OWNED, BN_CLICKED), (LPARAM)hCtl);
                }
                else
                {
                    Button_SetCheck (GetDlgItem (hDlg, IDC_NOT_OWNED), BST_CHECKED);
                }

                Static_SetIcon (GetDlgItem (hDlg, IDC_PAGE_ICON),
                                ImageList_GetIcon (g_hIconImgs, ICON_DL_OWNER, ILD_NORMAL));
            }
            return TRUE;

        case WM_NOTIFY:
            if (PSN_APPLY == ((LPNMHDR)lParam)->code)
            {
                if (BST_CHECKED == Button_GetCheck (GetDlgItem (hDlg, IDC_OWNED)))
                {
                    pObjInfo->DL.dwFlags |= DL_OWNED;
                    TCHAR achBuffer[64] = { 0 };
                    GetWindowText (GetDlgItem (hDlg, IDC_DL_OWNER), achBuffer, 64);
                    if (NULL == achBuffer[0])
                    {
                        pObjInfo->DL.dwFlags &= ~DL_OWNED;
                    }
                    else
                    {
                        GetWindowText (GetDlgItem (hDlg, IDC_COMMENTS), pObjInfo->DL.szComments, sizeof(pObjInfo->DL.szComments)/sizeof(TCHAR));
                    }
                }
                else
                {
                    pObjInfo->DL.dwFlags &= ~DL_OWNED;
                }
                if (!(DL_OWNED & pObjInfo->DL.dwFlags))
                {
                    pObjInfo->DL.dwOwnerID = 0;
                    ZeroMemory (pObjInfo->DL.szOwnerAlias, sizeof(pObjInfo->DL.szOwnerAlias));
                    ZeroMemory (pObjInfo->DL.szOwnerName, sizeof(pObjInfo->DL.szOwnerName));
                    ZeroMemory (pObjInfo->DL.szComments, sizeof(pObjInfo->DL.szComments));
                }
                return PSNRET_NOERROR;
            }
            break;

        case WM_COMMAND :
            switch (LOWORD(wParam))
            {
                case IDC_OWNED :
                case IDC_NOT_OWNED :
                    if (HIWORD(wParam) == BN_CLICKED)
                    {
                        SetFocus ((HWND)lParam);
                        BOOL fEnabled = (LOWORD(wParam) == IDC_OWNED ? TRUE : FALSE);
                        HWND hCtl;
                        hCtl = GetDlgItem (hDlg, IDC_DL_OWNER);
                        EnableWindow (hCtl, fEnabled);
                        hCtl = GetDlgItem (hDlg, IDC_OWNER_LABEL);
                        EnableWindow (hCtl, fEnabled);
                        hCtl = GetDlgItem (hDlg, IDC_MODIFY);
                        EnableWindow (hCtl, fEnabled);
                        hCtl = GetDlgItem (hDlg, IDC_COMMENTS_LABEL);
                        EnableWindow (hCtl, fEnabled);
                        hCtl = GetDlgItem (hDlg, IDC_COMMENTS);
                        EnableWindow (hCtl, fEnabled);
                    }
                    break;

                case IDC_MODIFY :
                    if (TRUE == DialogBoxParam (ghInstance,
                                                MAKEINTRESOURCE(IDD_ONE_MAILBOX),
                                                hDlg,
                                                SelectUserDlgProc,
                                                (LPARAM)pObjInfo))
                    {
                        SetWindowText (GetDlgItem (hDlg, IDC_DL_OWNER), pObjInfo->DL.szOwnerName);
                    }
                    break;
            }
            break;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    SelectUserDlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK SelectUserDlgProc (HWND    hDlg, 
                                 UINT    message, 
                                 WPARAM  wParam, 
                                 LPARAM  lParam)
{
    static POBJECT_INFO pObjInfo;
    switch (message)
    {   
        case WM_INITDIALOG :
            {
                pObjInfo = (POBJECT_INFO)lParam;
                CTL3D_Subclass(g_pctl3d, hDlg, CTL3D_ALL);
                HWND hWaitWnd = CreateDialog (ghInstance, MAKEINTRESOURCE(IDD_DIR_DOWNLOAD_WAIT), hDlg, WaitDlgProc);

                long lPipeNum;
                HANDLE hPipe;
                DWORD dwBytesRead, dwUserID, dwListUserIndex = 0;
                if (SERVER_DISTRIBUTION_LIST == pObjInfo->Type)
                {
                    dwUserID = pObjInfo->DL.dwOwnerID;
                }
                else
                {
                    dwUserID = pObjInfo->MB.dwManagerID;
                }
                AB_ENTRY_INFO abEntry = { 0 };
                HRESULT hResult = S_OK;
                int nTabStops[1] = { 1000 }; // Off the screen
                TCHAR achPipeName[64];
                
                HWND hListView = GetDlgItem (hDlg, IDC_ALL_USERS);
                ListView_SetImageList (hListView, g_hImages, LVSIL_SMALL);
                
                RECT rc;
                GetClientRect (hListView, &rc);
                LV_COLUMN lvc;
                lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
                lvc.fmt = LVCFMT_LEFT;
                lvc.pszText = TEXT("Full Name");
                lvc.iSubItem = 0;
                lvc.cx = 160;
                ListView_InsertColumn (hListView, 0, &lvc);
                lvc.pszText = TEXT("Alias");
                lvc.iSubItem = 1;
                lvc.cx = min (110, (rc.right - rc.left - lvc.cx));
                ListView_InsertColumn (hListView, 1, &lvc);

                int i = 0;
                LV_ITEM lvi = { 0 };
                lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
                lvi.iImage = IMG_USER_MAILBOX;

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
                                TraceResult ("ModifyListDlgProc: Failed to read from the source", hResult);
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
                            lvi.iItem = i;
                            lvi.iSubItem = 0;
                            lvi.pszText = abEntry.Info.MB.szFullName;
                            lvi.lParam = abEntry.Info.MB.dwObjID;
                            lvi.iItem = ListView_InsertItem (hListView, &lvi);
                            ListView_SetItemText (hListView, lvi.iItem, 1, abEntry.Info.MB.szMailboxName);
                            i++;
                            if (abEntry.Info.MB.dwObjID == dwUserID)
                            {
                                dwListUserIndex = abEntry.Info.MB.dwObjID;
                            }
                        }
                    } while (dwBytesRead && !hResult);
                    CloseHandle (hPipe);
                    if (0 != dwListUserIndex)
                    {
                        ListView_SetItemState (hListView,   
                                               dwListUserIndex,
                                               LVIS_FOCUSED | LVIS_SELECTED,
                                               LVIS_FOCUSED | LVIS_SELECTED);
                    }
                }
                DestroyWindow (hWaitWnd);
                if (hResult)
                {
                    ErrorHandler (hDlg, hResult);
                    EndDialog (hDlg, -1);
                }
            }
            return TRUE;

        case WM_COMMAND :
            switch (LOWORD(wParam))
            {
                case IDC_ALL_USERS :
                    if (LBN_DBLCLK == HIWORD(wParam))
                    {
                        PostMessage (hDlg, WM_COMMAND, IDOK, 0);
                    }
                    break;
                case IDOK :
                    {
                        TCHAR achName[MAX_STRING_SIZE+1], achAlias[MAX_ALIAS_SIZE+1];
                        DWORD dwUserID;
                        HWND hListView= GetDlgItem (hDlg, IDC_ALL_USERS);
                        
                        LV_ITEM lvi = { 0 };
                        lvi.mask = LVIF_PARAM | LVIF_TEXT;
                        lvi.iItem = ListView_GetNextItem (hListView, -1, LVNI_FOCUSED | LVNI_ALL);
                        lvi.iSubItem = 0;
                        lvi.pszText = achName;
                        lvi.cchTextMax = MAX_STRING_SIZE+1;
                        if (ListView_GetItem (hListView, &lvi))
                        {
                            dwUserID = lvi.lParam;
                            lvi.mask = LVIF_TEXT;
                            lvi.iSubItem = 1;
                            lvi.pszText = achAlias;
                            lvi.cchTextMax = MAX_ALIAS_SIZE+1;
                            if (FALSE == ListView_GetItem (hListView, &lvi))
                            {
                                wParam = IDCANCEL;
                            }
                        }
                        else
                        {
                            wParam = IDCANCEL;
                        }
                        if (IDOK == wParam)
                        {
                            if (SERVER_DISTRIBUTION_LIST == pObjInfo->Type)
                            {
                                pObjInfo->DL.dwOwnerID = dwUserID;
                            }
                            else
                            {
                                pObjInfo->MB.dwManagerID = dwUserID;
                            }
                            if (SERVER_DISTRIBUTION_LIST == pObjInfo->Type)
                            {
                                lstrcpy (pObjInfo->DL.szOwnerName, achName);
                            }
                            else
                            {
                                lstrcpy (pObjInfo->MB.szManagerName, achName);
                            }
                            if (SERVER_DISTRIBUTION_LIST == pObjInfo->Type)
                            {
                                lstrcpy (pObjInfo->DL.szOwnerAlias, achAlias);
                            }
                            else
                            {
                                lstrcpy (pObjInfo->MB.szManagerAlias, achAlias);
                            }
                        }
                    }
                    // Fall through
                case IDCANCEL :
                    ListView_SetImageList (GetDlgItem (hDlg, IDC_ALL_USERS), NULL, LVSIL_SMALL);
                    EndDialog (hDlg, (LOWORD(wParam) == IDOK ? TRUE : FALSE));
                    return TRUE;
            }
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    WaitDlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK WaitDlgProc (HWND    hDlg, 
                           UINT    message, 
                           WPARAM  wParam, 
                           LPARAM  lParam)
{
    if (WM_INITDIALOG == message)
    {
        CTL3D_Subclass(g_pctl3d, hDlg, CTL3D_ALL);
        Static_SetIcon(GetDlgItem (hDlg, IDC_STOPWATCH), GetAnimatedTimerCursor());
        return TRUE;
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    ModifyListDlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK ModifyListDlgProc (HWND    hDlg, 
                                 UINT    message, 
                                 WPARAM  wParam, 
                                 LPARAM  lParam)
{
    static POBJECT_INFO pObjInfo;
    static HWND hAllUsers, hMembers;
    switch (message)
    {   
        case WM_INITDIALOG :
            {
                pObjInfo = (POBJECT_INFO)lParam;
                CTL3D_Subclass(g_pctl3d, hDlg, CTL3D_ALL);
                HWND hWaitWnd = CreateDialog (ghInstance, MAKEINTRESOURCE(IDD_DIR_DOWNLOAD_WAIT), hDlg, WaitDlgProc);

                long lPipeNum;
                TCHAR achBuffer[128];
                HANDLE hPipe;
                DWORD dwBytesRead;
                AB_ENTRY_INFO abEntry = { 0 };
                HRESULT hResult = S_OK;
                int nTabStops[1];
                nTabStops[0] = 1000; // Off the screen
                
                hAllUsers = GetDlgItem (hDlg, IDC_ALL_USERS);
                hMembers = GetDlgItem (hDlg, IDC_MEMBERS);
                
                ListBox_SetTabStops (hAllUsers, sizeof(nTabStops)/sizeof(int), nTabStops);
                ListBox_SetTabStops (hMembers, sizeof(nTabStops)/sizeof(int), nTabStops);
                RpcTryExcept
                {
                    hResult = RemoteAdmGetGALDirectory (0, &lPipeNum);
                    if (!hResult)
                    {
                        // Construct the download pipe name
                        wsprintf (achBuffer, PIPE_NAME_FORMAT, g_szCurrentServer, lPipeNum);
                        // Create our endpoint and connect    
                        hPipe = CreateFile (achBuffer, 
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
                                TraceResult ("ModifyListDlgProc: Failed to read from the source", hResult);
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
                            switch (abEntry.Type)
                            {
                                case GATEWAY_RECIPIENT :
                                case SERVER_USER_MAILBOX :
                                    if (abEntry.Info.MB.dwObjID != pObjInfo->MB.dwObjID)
                                    {
                                        wsprintf (achBuffer,
                                                  TEXT("%s\t%s\t%d\t%d"),
                                                  abEntry.Info.MB.szFullName,
                                                  abEntry.Info.MB.szMailboxName,
                                                  abEntry.Info.MB.dwObjID,
                                                  abEntry.Type);
                                        ListBox_AddString (hAllUsers, achBuffer);
                                    }
                                    break;
                                case SERVER_DISTRIBUTION_LIST :
                                    if (abEntry.Info.DL.dwObjID != pObjInfo->DL.dwObjID)
                                    {
                                        wsprintf (achBuffer,
                                                  TEXT("%s\t%s\t%d\t%d"),
                                                  abEntry.Info.DL.szDLFullName,
                                                  abEntry.Info.DL.szDLAlias,
                                                  abEntry.Info.DL.dwObjID,
                                                  abEntry.Type);
                                        ListBox_AddString (hAllUsers, achBuffer);
                                    }
                                    break;
                            }
                        }
                    } while (dwBytesRead && !hResult);
                    CloseHandle (hPipe);
                }
                if (!hResult)
                {
                    WINDS_AB_OBJTYPE Type;
                    DLM_LIST * pNode = pObjInfo->pMembers;
                    while (pNode && pNode->Info.szMemberAlias[0])
                    {
                        Type = (WINDS_AB_OBJTYPE)pNode->Info.dwMemberType;
                        wsprintf (achBuffer,
                                  TEXT("%s\t%s\t%d\t%d"),
                                  pNode->Info.szMemberName,
                                  pNode->Info.szMemberAlias,
                                  pNode->Info.dwMemberID,
                                  pNode->Info.dwMemberType);
                        ListBox_AddString (hMembers, achBuffer);
                        pNode = pNode->pNext;
                    }
                }
                DestroyWindow (hWaitWnd);
                if (hResult)
                {
                    ErrorHandler (hDlg, hResult);
                    EndDialog (hDlg, -1);
                }
            }
            return TRUE;

        case WM_COMMAND :
            switch (LOWORD(wParam))
            {
                case IDC_REMOVE_ALL :
                    pObjInfo->dwData = TRUE;
                    ListBox_ResetContent (hMembers);
                    break;
                
                case IDC_MEMBERS :
                    if (LBN_DBLCLK != HIWORD(wParam))
                    {
                        break;
                    }
                    // else fall through
                case IDC_REMOVE_USER :
                    {
                        int nIndex = ListBox_GetCurSel (hMembers);
                        if (LB_ERR != nIndex)
                        {
                            ListBox_DeleteString (hMembers, nIndex);
                            pObjInfo->dwData = TRUE;
                        }
                    }
                    break;

                case IDC_ALL_USERS :
                    if (LBN_DBLCLK != HIWORD(wParam))
                    {
                        break;
                    }
                    // else fall through
                case IDC_ADD_USER :
                    {
                        TCHAR szBuffer[128];
                        int iUsers = ListBox_GetSelCount (hAllUsers);
                        if (iUsers == LB_ERR) // Nothins is selected
                        {
                            break;
                        }
                        int *piList = (int *)HeapAlloc (ghMemHeap, 0, (DWORD)(iUsers * sizeof(int)));
                        if (NULL == piList) // Low system resources
                        {
                            ErrorHandler (hDlg, E_OUTOFMEMORY);
                            break;
                        } 
                        ListBox_GetSelItems (hAllUsers, iUsers, piList);

                        for (int i=0; i<iUsers; i++)
                        {
                            ListBox_GetText (hAllUsers, piList[i], szBuffer);
                            if (LB_ERR == ListBox_FindStringExact (hMembers, -1, szBuffer))
                            {
                                ListBox_AddString (hMembers, szBuffer);
                            }
                            ListBox_SetSel (hMembers, FALSE, i);
                        }
                        pObjInfo->dwData = TRUE;
                        HeapFree (ghMemHeap, 0, piList);
                    }
                    break;

                case IDOK :
                    if (pObjInfo->dwData) // Means that something was changed
                    {
                        TCHAR achBuffer[128];
                        DLM_INFO Info = { 0 };
                        TCHAR * szSubStr;
                        FreeDLMList ((DLM_LIST*)pObjInfo->DL.pMembers);
                        DLM_LIST * pMemberList = (DLM_LIST*)pObjInfo->DL.pMembers;
                        int nCount = ListBox_GetCount (hMembers);
                        for (int i=0; i<nCount; i++)
                        {
                            if (LB_ERR == ListBox_GetText (hMembers, i, achBuffer))
                            {
                                continue;
                            }
                            strtok (achBuffer, "\t");
                            lstrcpy ((LPSTR)Info.szMemberName, achBuffer);

                            szSubStr = strtok (NULL, "\t");
                            lstrcpy ((LPSTR)Info.szMemberAlias, szSubStr);
                            
                            szSubStr = strtok (NULL, "\t");
                            Info.dwMemberID = (DWORD)atol (szSubStr);

                            szSubStr = strtok (NULL, "\t");
                            Info.dwMemberType = (DWORD)atol (szSubStr);

                            if (0 == i)
                            {
                                pMemberList->Info = Info;
                            }
                            else
                            {
                                InsertNewDLMNode (Info, (DLM_XMIT_LIST *)pMemberList);
                            }
                        }
                    }
                    // Fall through
                case IDCANCEL :
                    EndDialog (hDlg, (LOWORD(wParam) == IDOK ? TRUE : FALSE));
                    return TRUE;
            }
    }
    return FALSE;
}

// End of file for ADMDLIST.CPP
