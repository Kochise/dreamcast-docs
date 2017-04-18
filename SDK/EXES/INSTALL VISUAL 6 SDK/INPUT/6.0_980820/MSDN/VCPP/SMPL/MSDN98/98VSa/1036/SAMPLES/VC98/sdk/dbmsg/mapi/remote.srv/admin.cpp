///////////////////////////////////////////////////////////////////////////////
//
//  File Name 
//      ADMIN.CPP
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
    TCHAR g_szAppTitle[] = TEXT("WINDS Administrator");
    ITEM_TYPE g_LVItemsType = ITEM_UNDEFINED_TYPE;
    HINSTANCE ghInstance = NULL;
    HANDLE ghMemHeap = NULL;
    HANDLE ghCancelEvent;
    HWND ghTreeView, ghListView, ghWnd, ghStatusBar, ghToolBar;
    BOOL gfCancel = FALSE, gfTerminate = FALSE;
    HFONT ghBoldFont = NULL;
    CRITICAL_SECTION csCancel, csRemoteServer;
    TCHAR g_szCurrentServer[64] = { 0 };
    HIMAGELIST g_hImages = NULL, g_hIconImgs = NULL;
    LPVOID g_pctl3d = NULL;

    HRESULT WINAPI ServerChanged
                        (HWND                       hTreeView);

    LRESULT CALLBACK MainWndProc
                        (HWND                       hDlg, 
                         UINT                       message, 
                         WPARAM                     wParam, 
                         LPARAM                     lParam);
    BOOL WINAPI ShowConnectDialog
                        (HWND                       hOwnerWnd,
                         LPTSTR                     szServer,
                         BOOL *                     pfServerIsOnLine);
    BOOL WINAPI IsValidServerName
                        (LPTSTR                     szServerName);
    void WINAPI LoadSettingsFromRegistry
                        (LPTSTR                     szServer);
    void WINAPI SaveSettingsToRegistry
                        (LPTSTR                     szServer);
    void WINAPI HandleItemAction
                        (HWND                       hOwnerWnd,
                         int                        nItem,
                         WORD                       wAction);
    void WINAPI GetServerNameFromTitle
                        (LPTSTR                     szItemTitle,
                         LPTSTR *                   pszServerName);
    HRESULT WINAPI CancelThreadProc
                        ();
}

CNotifLink * gpLink = NULL;

///////////////////////////////////////////////////////////////////////////////
//    WinMain()
//
//    Parameters
//      { Refer to Win32 SDK documentation }
//      
//    Purpose
//      This is the entry function. The application will start executing here.
//      
//    Return Value
//      Return code of the application to the system.
//      
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pszCmdLine, int nCmdLine)
{
    #define WINDOW_CLASSNAME        TEXT("WINDS_ADMIN_CLASS")
    // Check for other instances of this application running. If one is found,
    // bring it to the foreground
    ghWnd = FindWindow (WINDOW_CLASSNAME, NULL);
    if (NULL != ghWnd)
    {
        HWND hChildWnd;
        hChildWnd = GetLastActivePopup (ghWnd);
        if (hChildWnd != ghWnd)
        {
            BringWindowToTop (hChildWnd);
        }
        else
        {
            SetForegroundWindow (ghWnd);
        }
        return 0;
    }

    MSG msg;
    HACCEL hAccel;
    InitTraces (0);
    TraceMessage ("WINDS Admin is initializing");
    ghInstance = hInstance;
    ghMemHeap = GetProcessHeap();

    WNDCLASS wc = { 0 };
    // Register the class for this application
    wc.lpfnWndProc      = MainWndProc;
    wc.hInstance        = ghInstance;
    wc.hIcon            = LoadIcon (ghInstance, MAKEINTRESOURCE (IDI_MAINFRAME));
    wc.lpszMenuName     = MAKEINTRESOURCE (IDM_MENU);
    wc.lpszClassName    = WINDOW_CLASSNAME;
    wc.hbrBackground    = (HBRUSH)(COLOR_BTNFACE);
    if (!RegisterClass (&wc))
    {
        TraceMessage ("WinMain: Failed to register the application class");
        return -1;
    }
    gpLink = new CNotifLink;
    InitializeCriticalSection (&csRemoteServer);
    InitializeCriticalSection (&csCancel);
    
    ghCancelEvent = CreateEvent (NULL, FALSE, FALSE, NULL);    

    if (!g_pctl3d)
    {
        BOOL f;
        g_pctl3d = CTL3D_Initialize(ghInstance);
        CTL3D_AutoSubclass(g_pctl3d, ghInstance, &f);
    }

    InitCommonControls();

    ghWnd = CreateWindowEx (WS_EX_DLGMODALFRAME | WS_EX_APPWINDOW | WS_EX_CONTROLPARENT,
                            WINDOW_CLASSNAME,
                            TEXT("WINDS Administrator"),
                            WS_OVERLAPPED   | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU,
                            100,
                            100,
                            800,
                            500,
                            NULL,
                            NULL,
                            ghInstance,
                            NULL);
    if (NULL == ghWnd)
    {
        PrivateMessageBox (IDS_MSG_NO_INTERNAL_RESOURCES, NULL, 0);
        goto ErrorExit;
    }
    hAccel = LoadAccelerators (ghInstance, MAKEINTRESOURCE (IDA_ACCELTABLE));
    if (NULL == hAccel)
    {
        TraceMessage ("WinMain: Failed to load accelerator table");
    }
    
    ShowWindow (ghWnd, nCmdLine);
    UpdateWindow (ghWnd);

    while (GetMessage (&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator (msg.hwnd, hAccel, &msg))
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }
ErrorExit:

    DeleteCriticalSection (&csCancel);
    DeleteCriticalSection (&csRemoteServer);
    delete gpLink;
    
    // Free any pending RPC binding resources.
    BindToServer (NULL);

    CloseHandle (ghCancelEvent);

    CTL3D_Uninitialize(g_pctl3d);
    g_pctl3d = NULL;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
//    MainWndProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      
LRESULT CALLBACK MainWndProc (HWND    hWnd, 
                              UINT    message, 
                              WPARAM  wParam, 
                              LPARAM  lParam)
{
    static HBRUSH hbrFace = NULL;
    static HMENU hMBPopupMenu, hDLPopupMenu;
    static HCURSOR hCurrentCursor = NULL;
    static BOOL fRPCInProgress = FALSE;
    switch (message)
    {
        case WM_SETCURSOR :
            SetCursor (hCurrentCursor);
            return TRUE;

        case WM_CREATE :
            {
                hCurrentCursor = LoadCursor (NULL, IDC_ARROW);
                g_hIconImgs = ImageList_LoadBitmap (ghInstance, MAKEINTRESOURCE(IDB_ICONS), 32, 2, CLR_NONE);
                g_hImages = ImageList_LoadBitmap (ghInstance, MAKEINTRESOURCE(IDB_OBJECTS), 18, 2, CLR_NONE);
                ImageList_SetBkColor (g_hImages, GetSysColor(COLOR_WINDOW));
                
                if (!CreateListView (hWnd, g_hImages))
                {
                    return -1;
                }
                if (!CreateTreeView (hWnd, g_hImages))
                {
                    return -1;
                }
                if (!CreateToolBar (hWnd))
                {
                    return -1;
                }
                BOOL fServerIsOnline = FALSE;
                LoadSettingsFromRegistry (g_szCurrentServer);
                if (ShowConnectDialog (hWnd, g_szCurrentServer, &fServerIsOnline) &&
                    fServerIsOnline)
                {
                    AddServerToList (g_szCurrentServer, TRUE);
                    gpLink->StartNotification();
                }
                hbrFace = CreateSolidBrush (GetSysColor (COLOR_BTNFACE));
                ghBoldFont = CreateFont (-24,                    // Height
                                         0,                      // Width
                                         0,                      // Escapement
                                         0,                      // Orientation
                                         FW_BOLD,                // Font Weigth
                                         FALSE,                  // Italic?
                                         FALSE,                  // Underlined?
                                         FALSE,                  // Strike out?
                                         ANSI_CHARSET,           // Character set
                                         OUT_STROKE_PRECIS,      // Font precision
                                         CLIP_STROKE_PRECIS,     // Clip precision 
                                         DRAFT_QUALITY,          // Font apperance quality
                                         FF_SWISS,               // Font pitch and family,
                                         TEXT("Arial"));         // Font face name
                CreateStatusBar (hWnd);

                hMBPopupMenu = LoadMenu (ghInstance, MAKEINTRESOURCE (IDM_MAILBOX_POPUP));
                hMBPopupMenu = GetSubMenu (hMBPopupMenu, 0);

                hDLPopupMenu = LoadMenu (ghInstance, MAKEINTRESOURCE (IDM_DISTLIST_POPUP));
                hDLPopupMenu = GetSubMenu (hDLPopupMenu, 0);

                DWORD dwThreadID;
                HANDLE hThread = CreateThread (NULL,
                                               0,
                                               (LPTHREAD_START_ROUTINE)CancelThreadProc,
                                               NULL,
                                               0,
                                               &dwThreadID);
                ASSERTMSG (hThread, "Failed to spawn cancel thread");
                TraceDebugger ("MainWndProc: RPC cancel thread spawned. ID: %X", dwThreadID);
                CloseHandle (hThread);
            }
            break;

        case WM_MEASUREITEM :
            {
                PMEASUREITEMSTRUCT pMIS = (PMEASUREITEMSTRUCT)lParam;
                TEXTMETRIC tm;
                HDC hdc;
                HFONT hFont;
                if (pMIS->CtlType == ODT_LISTVIEW)
                {
                    hFont = (HFONT)SendMessage (ghListView, WM_GETFONT, 0, 0L);
                    hdc = GetDC (ghListView);
                    SelectObject (hdc, hFont);
                    GetTextMetrics (hdc, &tm);
        
                    pMIS->itemHeight = tm.tmHeight + 1;

                    if (pMIS->itemHeight < (18 + 1))
                    {
                        pMIS->itemHeight = 18 + 1;
                    }
                    ReleaseDC (ghListView, hdc);
                }
            }
            return TRUE;

        case WM_DRAWITEM :
            {
                PDRAWITEMSTRUCT pDIS = (PDRAWITEMSTRUCT)lParam;
                if (pDIS->CtlType != ODT_LISTVIEW)
                {
                    return FALSE;
                }
                switch (pDIS->itemAction)
                {
                    case ODA_DRAWENTIRE:
                    case ODA_FOCUS:
                    case ODA_SELECT:
                        DrawListViewItem (pDIS);
                        break;
                }
            }
            return TRUE;

        case WM_PAINT :
            {
                PAINTSTRUCT ps;
                RECT rc;
                GetClientRect (hWnd, &rc);
                BeginPaint (hWnd, &ps);
                FillRect (ps.hdc, &rc, hbrFace);
                EndPaint (hWnd, &ps);
            }
            break;

        case WM_MENUCHAR :
            if (LOWORD(wParam) == 13 && 0 == HIWORD(wParam)) // 13 == RETURN
            {
                PostMessage (hWnd, WM_COMMAND, IDM_FILE_PROPERTIES, 0);
                return (BOOL)1;
            }
            break;

        case WM_VKEYTOITEM :
            if ((HWND)lParam == ghListView)
            {
                if (LOWORD(wParam) == VK_DELETE)
                {
                    PostMessage (hWnd, WM_COMMAND, IDM_FILE_DELETE, 0);
                }
                else
                {
                    if (LOWORD(wParam) == VK_INSERT)
                    {
                        PostMessage (hWnd, WM_COMMAND, IDM_FILE_NEW_MAILBOX, 0);
                    }
                }
            }
            return (BOOL)-1;

        case WM_SYSCOLORCHANGE :
            SendMessage (ghListView, message, wParam, lParam);
            SendMessage (ghTreeView, message, wParam, lParam);
            break;

        case WM_WINDS_RESET_NOTIF_LINK :
            gpLink->EndNotifications();
            gpLink->StartNotification();
            break;
        
        case WM_WINDS_UPDATEHEADERWIDTH :
            UpdateHeaderWidth ((HWND)wParam, (int)lParam);
            break;

        case WM_WINDS_REMOTE_CALL_IN_PROGRESS :
            fRPCInProgress = TRUE;
            SendMessage (ghToolBar, TB_SETSTATE, IDC_CANCEL_REMOTE_CALL, TBSTATE_ENABLED);
            break;

        case WM_WINDS_REMOTE_CALL_COMPLETED :
            hCurrentCursor = LoadCursor (NULL, IDC_ARROW);
            SetCursor (hCurrentCursor);
            SendMessage (ghStatusBar, SB_SETTEXT, 0, (LPARAM)TEXT("Ready"));
            if (wParam)
            {
                ErrorHandler (hWnd, (HRESULT)wParam);
            }
            fRPCInProgress = FALSE;
            SendMessage (ghToolBar, TB_SETSTATE, IDC_CANCEL_REMOTE_CALL, TBSTATE_INDETERMINATE);
            break;

        case WM_NOTIFY :
            switch (((LPNMHDR)lParam)->code)
            {
                case TTN_NEEDTEXT :
                    // Time to display a tool tip text box. Return the ID of
                    // the string in our resource table. The control will
                    // pick it up from there.
                    ((LPTOOLTIPTEXT)lParam)->hinst = ghInstance;
                    ((LPTOOLTIPTEXT)lParam)->lpszText = (LPTSTR)((LPTOOLTIPTEXT)lParam)->hdr.idFrom;
                    break;

                case HDN_ENDTRACK:
                    {
                        HD_NOTIFY *phdn = (HD_NOTIFY *)lParam;
                        PostMessage (hWnd,
                                     WM_WINDS_UPDATEHEADERWIDTH,
                                     (WPARAM)phdn->hdr.hwndFrom,
                                     (LPARAM)phdn->iItem);
                    }
                    break;

                case TVN_SELCHANGED :
                    {
                        DWORD dwThreadID;
                        HANDLE hThread = NULL;
                        NM_TREEVIEW * pNMTV = (NM_TREEVIEW *)lParam;
                        ITEM_TYPE tvItemType = (ITEM_TYPE)pNMTV->itemNew.lParam;
                        // Cancel the remote call in progress, if any
                        if (fRPCInProgress)
                        {
                            SetEvent (ghCancelEvent);
                        }
                        g_LVItemsType = ITEM_UNDEFINED_TYPE;
                        
                        // If necessary, reset the RPC binding to the new server
                        if (S_OK != ServerChanged (ghTreeView))
                        {
                            break;
                        }

                        switch (tvItemType)
                        {
                            case ITEM_SERVER_USER_MAILBOXES :
                                g_LVItemsType = ITEM_SERVER_USER_MAILBOXES;
                                hThread = CreateThread (NULL,
                                                        0,
                                                        (LPTHREAD_START_ROUTINE)GetServerMailboxes,
                                                        (LPVOID)hWnd,
                                                        CREATE_SUSPENDED,
                                                        &dwThreadID);
                                break;
                            case ITEM_SERVER_DIST_LISTS :
                                g_LVItemsType = ITEM_SERVER_DIST_LISTS;
                                hThread = CreateThread (NULL,
                                                        0,
                                                        (LPTHREAD_START_ROUTINE)GetServerDistLists,
                                                        (LPVOID)hWnd,
                                                        CREATE_SUSPENDED,
                                                        &dwThreadID);
                                break;
                            default :
                                ListView_DeleteAllItems (ghListView);
                                break;
                        }
                        if (hThread)
                        {
                            hCurrentCursor = LoadCursor (NULL, IDC_APPSTARTING);
                            SetCursor (hCurrentCursor);
                            ResumeThread (hThread);
                            CloseHandle (hThread);
                            TraceDebugger ("MainWndProc: RPC worker thread spawned. ID: %X", dwThreadID);
                        }
                    }
                    break;

                case NM_RCLICK :
                case NM_DBLCLK :
                    if (((LPNMHDR)lParam)->idFrom == IDC_LISTVIEW)
                    {
                        if (NM_RCLICK == ((LPNMHDR)lParam)->code)
                        {
                            HMENU hMenu = NULL;
                            switch (g_LVItemsType)
                            {
                                case ITEM_SERVER_USER_MAILBOXES :
                                    hMenu = hMBPopupMenu;
                                    break;
                                case ITEM_SERVER_DIST_LISTS :
                                    hMenu = hDLPopupMenu;
                                    break;
                            }
                            POINT pt;
                            GetCursorPos (&pt);
                            TrackPopupMenu (hMenu, 
                                            TPM_CENTERALIGN | TPM_LEFTBUTTON,
                                            pt.x,
                                            pt.y,
                                            0,
                                            hWnd,
                                            NULL);
                        }
                        else
                        {
                            PostMessage (hWnd, WM_COMMAND, IDM_POPUP_MB_PROPS, 0);
                        }
                    }
                    break;
            }
            break;

        case WM_COMMAND :
            // If a background thread is download something, we can't
            // allow many things to happen.
            if (fRPCInProgress && 
                IDM_ABOUT != LOWORD(wParam) &&
                IDC_CANCEL_REMOTE_CALL != LOWORD(wParam) &&
                IDM_FILE_EXIT != LOWORD(wParam))
            {
                PrivateMessageBox (IDS_MSG_WAIT_FOR_COMPLETION,
                                   hWnd,
                                   MB_OK |
                                   MB_ICONEXCLAMATION|
                                   MB_SETFOREGROUND);
                break;
            }
            switch (LOWORD(wParam))
            {
                case IDM_ABOUT :
                    DialogBox (ghInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutDlgProc);
                    break;

                case IDM_SERVER_EXPORT :
                    DialogBox (ghInstance, MAKEINTRESOURCE(IDD_EXPORT), hWnd, ExportDlgProc);
                    break;

                case IDM_SERVER_IMPORT :
                    DialogBox (ghInstance, MAKEINTRESOURCE(IDD_IMPORT), hWnd, ImportDlgProc);
                    break;

                case IDC_CANCEL_REMOTE_CALL :
                    SetEvent (ghCancelEvent);
                    break;

                case IDM_FILE_PROPERTIES :
                case IDM_FILE_DELETE :
                case IDM_POPUP_MB_PROPS :
                case IDM_POPUP_MB_EMPTY :
                case IDM_POPUP_MB_HEADERS :
                case IDM_POPUP_MB_DELETE :
                    {
                        int nItem = ListView_GetNextItem (ghListView, -1, LVNI_FOCUSED | LVNI_ALL);
                        if (-1 == nItem)
                        {
                            break;
                        }
                        HandleItemAction (hWnd, nItem, LOWORD(wParam));
                    }
                    break;

                case IDM_FIND_MAILBOX :
                    break;

                case IDM_FILE_NEW_MAILBOX :
                    CreateNewMailbox (hWnd);
                    break;

                case IDM_FILE_NEW_DISTRIBUTIONLIST :
                    CreateNewDistList (hWnd);
                    break;

                case IDM_VIEW_DISCONNECT :
                    DialogBox (ghInstance, MAKEINTRESOURCE(IDD_REMOVE_SERVER), hWnd, RemoveServersDlgProc);
                    break;

                case IDM_VIEW_CONNECT :
                    {
                        TCHAR szNewServer[64] = { 0 };
                        BOOL fServerIsOnline = FALSE;
                        if (ShowConnectDialog (hWnd, szNewServer, &fServerIsOnline) &&
                            fServerIsOnline)
                        {
                            AddServerToList (szNewServer, (NULL == g_szCurrentServer[0] ? TRUE : FALSE));
                            if (NULL == g_szCurrentServer[0])
                            {
                                lstrcpy (g_szCurrentServer, szNewServer);
                            }
                        }
                    }
                    break;

                case IDM_FILE_EXIT :
                    // Terminate the application
                    PostMessage (hWnd, WM_CLOSE, 0, 0);
                    break;
            }
            break;

        case WM_QUERYENDSESSION :
        case WM_DESTROY :
            gfTerminate = TRUE;
            SetEvent (ghCancelEvent);
            
            DeleteObject (hbrFace);
            DeleteObject (ghBoldFont);
            ImageList_Destroy (g_hImages);
            ImageList_Destroy (g_hIconImgs);
            DestroyWindow (ghListView);
            DestroyWindow (ghTreeView);
            DestroyWindow (ghStatusBar);
            DestroyWindow (ghToolBar);
            DestroyMenu (hMBPopupMenu);
            DestroyMenu (hDLPopupMenu);
            PostQuitMessage (0);
            break;

        default :
            return DefWindowProc (hWnd, message, wParam, lParam);
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
//    HandleItemAction()
//
//    Parameters
//
//    Purpose
//      
//    Return Value
//      
void WINAPI HandleItemAction (HWND hOwnerWnd, int nItem, WORD wAction)
{
    LV_ITEM lvi = { 0 };
    lvi.mask = LVIF_PARAM;
    lvi.iItem = nItem;
    lvi.iSubItem = 0;
    if (FALSE == ListView_GetItem (ghListView, &lvi))
    {
        return;
    }
    switch (wAction)
    {
        case IDM_FILE_PROPERTIES :
        case IDM_POPUP_MB_PROPS :
            switch (g_LVItemsType)
            {
                case ITEM_SERVER_USER_MAILBOXES :
                    ShowMailboxProps (hOwnerWnd, lvi.lParam);
                    break;
                case ITEM_SERVER_DIST_LISTS :
                    ShowDistListProps (hOwnerWnd, lvi.lParam);
                    break;
                case ITEM_SERVER_FOREIGN_MAILBOXES :
                    TraceMessage ("Properties of Foreign Recipient");
                    break;
                case ITEM_SERVER_PUBLIC_FOLDERS :
                    TraceMessage ("Properties of public folder");
                    break;
                case ITEM_SERVER_GATEWAYS :
                    TraceMessage ("Properties of Server gateway");
                    break;
            }
            break;

        case IDM_POPUP_MB_EMPTY :
            if (ITEM_SERVER_USER_MAILBOXES == g_LVItemsType)
            {
                PurgeMailboxMessages (hOwnerWnd, lvi.lParam);
            }
            break;

        case IDM_FILE_DELETE :
        case IDM_POPUP_MB_DELETE :
            switch (g_LVItemsType)
            {
                case ITEM_SERVER_USER_MAILBOXES :
                case ITEM_SERVER_DIST_LISTS :
                    DeleteServerObject (hOwnerWnd, lvi.lParam);
                    break;
                case ITEM_SERVER_FOREIGN_MAILBOXES :
                    TraceMessage ("Delete Foreign Recipient");
                    break;
                case ITEM_SERVER_PUBLIC_FOLDERS :
                    TraceMessage ("Delete Public folder");
                    break;
            }
            break;

        case IDM_POPUP_MB_HEADERS :
            TraceMessage ("View mailbox headers");
            break;
    }
}

///////////////////////////////////////////////////////////////////////////////
//    AboutDlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      Displays a dialog box with the copyright and program information
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK AboutDlgProc (HWND    hDlg, 
                            UINT    message, 
                            WPARAM  wParam, 
                            LPARAM  lParam)
{
    if (WM_INITDIALOG == message)
    {
        CenterDialogBox (hDlg);
        return TRUE;
    }
    else
    {
        if (WM_COMMAND == message && (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL))
        {   
            EndDialog (hDlg, TRUE);
            return TRUE;
        }
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    AddServerToList()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
void WINAPI AddServerToList (LPTSTR szServer, BOOL fExpandRoot)
{
    HTREEITEM hItem, hRoot;
    TV_INSERTSTRUCT tvIns = { 0 };
    TV_ITEM tvItem = 
    {
        TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM,
        NULL,
        0,
        0,
        NULL,
        0,
        IMG_SERVER,
        IMG_SERVER,
        0,
        NULL
    };
    TCHAR szName[128];

    // Add the root item
    wsprintf (szName, TEXT("WINDS Server: %s"), szServer);
    tvItem.pszText = szName,
    tvIns.hParent = NULL;
    tvItem.lParam = (LPARAM)ITEM_REMOTE_SERVER;
    tvIns.item    = tvItem;
    hRoot = TreeView_InsertItem (ghTreeView, &tvIns);

    // Add the "Object Directory" item
    tvItem.pszText = TEXT("Object Directory");
    tvItem.iImage = IMG_MAILABLE_OBJECTS_CLOSE;
    tvItem.iSelectedImage = IMG_MAILABLE_OBJECTS_OPEN;
    tvItem.lParam = (LPARAM)ITEM_OBJECT_DIRECTORY;
    tvIns.hParent = hRoot;
    tvIns.item    = tvItem;
    hItem = TreeView_InsertItem (ghTreeView, &tvIns);

    // Add the "User Mailboxes" item
    tvItem.pszText = TEXT("User Mailboxes");
    tvItem.iImage = IMG_USER;
    tvItem.iSelectedImage = IMG_USER;
    tvItem.lParam  = (LPARAM)ITEM_SERVER_USER_MAILBOXES;
    tvIns.hParent = hItem;
    tvIns.item    = tvItem;
    TreeView_InsertItem (ghTreeView, &tvIns);

    // Add the "Server DLs" item
    tvItem.pszText = TEXT("Server Distribution Lists");
    tvItem.iImage = IMG_MAIL_GROUP;
    tvItem.iSelectedImage = IMG_MAIL_GROUP;
    tvItem.lParam  = (LPARAM)ITEM_SERVER_DIST_LISTS;
    tvIns.hParent = hItem;
    tvIns.item = tvItem;
    TreeView_InsertItem (ghTreeView, &tvIns);

    // Add the "Foreign Entries" item
    tvItem.pszText = TEXT("Foreign Mailboxes");
    tvItem.iImage = IMG_FOREIGN_USER;
    tvItem.iSelectedImage = IMG_FOREIGN_USER;
    tvItem.lParam = (LPARAM)ITEM_SERVER_FOREIGN_MAILBOXES;
    tvItem.lParam = NULL;
    tvIns.hParent = hItem;
    tvIns.item = tvItem;
    TreeView_InsertItem (ghTreeView, &tvIns);

    TreeView_Expand (ghTreeView, hItem, TVE_EXPAND);

    tvItem.pszText = TEXT("Public Folders");
    tvItem.iImage = IMG_SERVER_PUB_FOLDER;
    tvItem.iSelectedImage = IMG_SERVER_PUB_FOLDER;
    tvItem.lParam = (LPARAM)ITEM_SERVER_PUBLIC_FOLDERS;
    tvIns.hParent = hRoot;
    tvIns.item = tvItem;
    TreeView_InsertItem (ghTreeView, &tvIns);

    tvItem.pszText = TEXT("Gateways");
    tvItem.iImage = IMG_SERVER_GATEWAY;
    tvItem.iSelectedImage = IMG_SERVER_GATEWAY;
    tvItem.lParam = (LPARAM)ITEM_SERVER_GATEWAYS;
    tvIns.hParent = hRoot;
    tvIns.item = tvItem;
    hItem = TreeView_InsertItem (ghTreeView, &tvIns);

    tvItem.pszText = TEXT("Exchange Gateway");
    tvItem.iImage = IMG_GATEWAY;
    tvItem.iSelectedImage = IMG_GATEWAY;
    tvItem.lParam = (LPARAM)ITEM_SERVER_GATEWAYS;
    tvIns.hParent = hItem;
    tvIns.item = tvItem;
    TreeView_InsertItem (ghTreeView, &tvIns);

    tvItem.pszText = TEXT("SMTP Gateway");
    tvItem.iImage = IMG_GATEWAY;
    tvItem.iSelectedImage = IMG_GATEWAY;
    tvItem.lParam = (LPARAM)ITEM_SERVER_GATEWAYS;
    tvIns.hParent = hItem;
    tvIns.item = tvItem;
    TreeView_InsertItem (ghTreeView, &tvIns);

    tvItem.pszText = TEXT("FAX Gateway");
    tvItem.iImage = IMG_GATEWAY;
    tvItem.iSelectedImage = IMG_GATEWAY;
    tvItem.lParam = (LPARAM)ITEM_SERVER_GATEWAYS;
    tvIns.hParent = hItem;
    tvIns.item = tvItem;
    TreeView_InsertItem (ghTreeView, &tvIns);

    TreeView_Expand (ghTreeView, hItem, TVE_EXPAND);

    if (fExpandRoot)
    {
        TreeView_Expand (ghTreeView, hRoot, TVE_EXPAND);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    CancelThreadProc()
//
//    Parameters
//
//    Purpose
//
//    Return Value
//
HRESULT WINAPI CancelThreadProc()
{
    while (TRUE)
    {
        WaitForSingleObject (ghCancelEvent, INFINITE);
        if (gfTerminate)
        {
            break; // Out of the WHILE() loop
        }
        EnterCriticalSection (&csCancel);
        gfCancel = TRUE;
        LeaveCriticalSection (&csCancel);
    }
    return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//    LoadSettingsFromRegistry()
//
//    Parameters
//      
//    Purpose
//      
//    Return Value
//      None
//      
void WINAPI LoadSettingsFromRegistry (LPTSTR szServer)
{
    HKEY hAppKey;
    // Try to open the key in the registry, open it with READ rights,
    // and read the data into our strcture
    if (ERROR_SUCCESS == RegOpenKeyEx (HKEY_CURRENT_USER,
                                       WINDS_ADMIN_REGISTRY_KEY,
                                       0,
                                       KEY_READ,
                                       &hAppKey))
    {
        ULONG cbSize = 64;
        DWORD dwError = RegQueryValueEx (hAppKey,
                                         SERVER_SUB_KEY,
                                         NULL,
                                         NULL,
                                         (LPBYTE)szServer,
                                         &cbSize);
        RegCloseKey (hAppKey);
        // If we failed to get the data from the registry we can't return
        // yet, we will proceed to initialize the options with default
        // values
        if (ERROR_SUCCESS == dwError)
        {
            return;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//    SaveSettingsToRegistry()
//
//    Parameters
//
//    Purpose
//      
//    Return Value
//      None
//      
void WINAPI SaveSettingsToRegistry (LPTSTR szServer)
{
    HKEY hAppKey;
    DWORD dwDisposition;
    // Try to open the key in the registry, open it with READ/WRITE rights
    if (ERROR_SUCCESS != RegCreateKeyEx (HKEY_CURRENT_USER,
                                         WINDS_ADMIN_REGISTRY_KEY,
                                         0,
                                         NULL,
                                         REG_OPTION_NON_VOLATILE,
                                         KEY_WRITE,
                                         NULL,
                                         &hAppKey,
                                         &dwDisposition))
    {
        // If we fail to access the registry, we need to get out, we don't
        // have a key opened where to write
        TraceResult ("SaveSettingsToRegistry: Failed to open app key", HRESULT_FROM_WIN32(GetLastError()));
    }
    else
    {
        // With the opened key handle, create a sub entry where we save our
        // structure values. For this sample we just write the entire
        // structure as a big blob of data, which we read the save way.
        if (ERROR_SUCCESS != RegSetValueEx (hAppKey,
                                            SERVER_SUB_KEY,
                                            0,
                                            REG_SZ,
                                            (LPBYTE)szServer,
                                            (1+lstrlen(szServer))*sizeof(TCHAR)))
        {
            TraceResult ("SaveSettingsToRegistry: Failed to save registry values", HRESULT_FROM_WIN32(GetLastError()));
        }
        // Close the handle we have open and return the appropiate flag
        RegCloseKey (hAppKey);
    }
}

///////////////////////////////////////////////////////////////////////////////
//    ShowConnectDialog()
//
//    Parameters
//
//    Purpose
//      
//    Return Value
//      None
//      
BOOL WINAPI ShowConnectDialog (HWND hOwnerWnd, LPTSTR szServer, BOOL * pfServerIsOnLine)
{
    *pfServerIsOnLine = FALSE;
    BOOL bResult = FALSE;
    if (lstrlen(szServer))
    {
        goto ConnectToServer;
    }
ReEnterServerName:
    // Free any previous bindings
    BindToServer (NULL);
    SetCursor (LoadCursor (NULL, IDC_ARROW));
    if (TRUE == DialogBoxParam (ghInstance,
                                MAKEINTRESOURCE(IDD_SERVER_CONNECT),
                                hOwnerWnd,
                                ServerConnectDlgProc,
                                (LPARAM)szServer))
    {
ConnectToServer:
        SetCursor (LoadCursor (NULL, IDC_WAIT));
        HRESULT hResult = BindToServer (szServer);
        if (!hResult)
        {
            RpcTryExcept
            {
                hResult = RemoteAdmIsServerRunning();
                if (!hResult)
                {
                    *pfServerIsOnLine = TRUE;
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
            switch (hResult)
            {
                case S_OK :
                    break;
                case HRESULT_FROM_WIN32(ERROR_HOST_UNREACHABLE) :
                    SetCursor (LoadCursor (NULL, IDC_ARROW));
                    if (IDYES == PrivateMessageBox (IDS_MSG_SERVER_NOT_FOUND,
                                                    hOwnerWnd,
                                                    MB_YESNO |
                                                    MB_ICONSTOP |
                                                    MB_SETFOREGROUND))
                    {
                        goto ReEnterServerName;
                    }
                    break;
                default :
                    TraceResult ("ShowConnectDialog", hResult);
                    goto ReEnterServerName;
                    break;
            }
            bResult = TRUE;
        }
    }
    SetCursor (LoadCursor (NULL, IDC_ARROW));
    BindToServer (g_szCurrentServer);
    return bResult;
}

///////////////////////////////////////////////////////////////////////////////
//    ServerConnectDlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK ServerConnectDlgProc (HWND    hDlg, 
                                    UINT    message, 
                                    WPARAM  wParam, 
                                    LPARAM  lParam)
{
    static LPTSTR szServer;
    switch (message)
    {
        case WM_INITDIALOG :
            szServer = (LPTSTR)lParam;
            CenterDialogBox (hDlg);
            Edit_LimitText (GetDlgItem (hDlg, IDC_SERVER_NAME), 32);
            SetFocus (GetDlgItem (hDlg, IDC_SERVER_NAME));
            if (NULL == g_szCurrentServer[0])
            {
                Button_SetCheck (GetDlgItem (hDlg, IDC_SERVER_DEFAULT), BST_CHECKED);
            }
            Static_SetIcon (GetDlgItem (hDlg, IDC_PAGE_ICON),
                            ImageList_GetIcon (g_hIconImgs, ICON_CONNECT, ILD_NORMAL));
            return TRUE;

        case WM_COMMAND :
            switch (LOWORD(wParam))
            {
                case IDOK :
                    if (GetWindowText (GetDlgItem (hDlg, IDC_SERVER_NAME), szServer, 64))
                    {
                        if (FALSE == IsValidServerName (szServer))
                        {
                            PrivateMessageBox (IDS_MSG_INVALID_SERVER_NAME, hDlg, 0);
                            return TRUE;
                        }
                        BOOL fDuplicate = FALSE;
                        TCHAR szBuffer[128], *szConnectedServer;
                        TV_ITEM tvItem = { 0 };
                        tvItem.mask = TVIF_TEXT;
                        tvItem.pszText = szBuffer;
                        tvItem.cchTextMax = 128;
                        HTREEITEM hItem = TreeView_GetRoot (ghTreeView);
                        while (hItem)
                        {
                            tvItem.hItem = hItem;
                            if (TRUE == TreeView_GetItem (ghTreeView, &tvItem))
                            {
                                GetServerNameFromTitle (szBuffer, &szConnectedServer);
                                if (0 == lstrcmpi(szServer, szConnectedServer))
                                {
                                    fDuplicate = TRUE;
                                    break; // Out of the WHILE() loop
                                }
                            }
                            hItem = TreeView_GetNextItem (ghTreeView, hItem, TVGN_NEXT);
                        }
                        if (fDuplicate)
                        {
                            wParam = IDCANCEL;
                        }
                        else
                        {
                            if (BST_CHECKED == Button_GetCheck (GetDlgItem (hDlg, IDC_SERVER_DEFAULT)))
                            {
                                SaveSettingsToRegistry (szServer);
                            }
                        }
                    }
                    else
                    {
                        return TRUE;
                    }
                    // fall through
                case IDCANCEL :
                    EndDialog (hDlg, (LOWORD(wParam) == IDOK ? TRUE : FALSE));
                    return TRUE;
            }
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    IsValidServerName()
//
//    Parameters
//      pszServerName       Pointer to a string with the UNC name of a
//                          network or local server
//    Purpose
//      Check the string for a server name and determines if the name is a
//      valid UNC name for a network server
//
//    Return Value
//      TRUE if the server name is valid, FALSE otherwise.
//      
BOOL WINAPI IsValidServerName (LPTSTR pszServerName)
{
    // Server name need to be at least "\\x"
    if (lstrlen(pszServerName) < 3)
    {
        return FALSE;
    }
    // The first two character in the string must be "\". This is standard
    // UNC (Universal Naming Convention) for server names
    if (pszServerName[0] != '\\' || pszServerName[1] != '\\')
    {
        return FALSE;
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//    RemoveServersDlgProc()
//
//    Parameters
//      { Refer to Win32 API documentation on dialog procedures }
//
//    Purpose
//      
//    Return Value
//      TRUE if message was handled, FALSE if we don't handle the message
//      
BOOL CALLBACK RemoveServersDlgProc (HWND    hDlg, 
                                    UINT    message, 
                                    WPARAM  wParam, 
                                    LPARAM  lParam)
{
    switch (message)
    {
        case WM_INITDIALOG :
            {
                CenterDialogBox (hDlg);
                CTL3D_Subclass(g_pctl3d, hDlg, CTL3D_ALL);
                HWND hListView = GetDlgItem (hDlg, IDC_SERVER_LIST);
                ListView_SetImageList (hListView, g_hImages, LVSIL_SMALL);
                RECT rc;
                GetClientRect (hListView, &rc);
                LV_COLUMN lvc = { 0 };
                lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
                lvc.fmt = LVCFMT_LEFT;
                lvc.pszText = TEXT("Server Name");
                lvc.cx = rc.right - rc.left;
                ListView_InsertColumn (hListView, 0, &lvc);

                TCHAR szBuffer[128];

                LV_ITEM lvi = { 0 };
                lvi.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
                lvi.iImage = IMG_SERVER;
                
                TV_ITEM tvItem = { 0 };
                tvItem.mask = TVIF_TEXT;
                tvItem.pszText = szBuffer;
                tvItem.cchTextMax = 128;
                HTREEITEM hItem = TreeView_GetRoot (ghTreeView);
                while (hItem)
                {
                    tvItem.hItem = hItem;
                    if (TRUE == TreeView_GetItem (ghTreeView, &tvItem))
                    {
                        GetServerNameFromTitle (szBuffer, &lvi.pszText);
                        lvi.lParam = (LPARAM)hItem;
                        ListView_InsertItem (hListView, &lvi);
                        lvi.iItem++;
                    }
                    hItem = TreeView_GetNextItem (ghTreeView, hItem, TVGN_NEXT);
                }
            }
            return TRUE;

        case WM_COMMAND :
            switch (LOWORD(wParam))
            {
                case IDOK :
                    {
                        HWND hListView = GetDlgItem (hDlg, IDC_SERVER_LIST);
                        TCHAR szBuffer[128];
                        BOOL fSuccess;
                        LV_ITEM lvi = { 0 };
                        lvi.mask = LVIF_TEXT | LVIF_PARAM;
                        lvi.pszText = szBuffer;
                        lvi.cchTextMax = 128;
                        lvi.iItem = ListView_GetNextItem (hListView, -1, LVNI_SELECTED);
                        while (-1 != lvi.iItem)
                        {
                            if (TRUE == ListView_GetItem (hListView, &lvi))
                            {
                                fSuccess = TreeView_DeleteItem (ghTreeView, (HTREEITEM)lvi.lParam);
                                if (fSuccess && 0 == lstrcmpi (g_szCurrentServer, szBuffer))
                                {
                                    gpLink->EndNotifications();
                                    BindToServer (NULL);
                                    ZeroMemory (g_szCurrentServer, sizeof(g_szCurrentServer));
                                    ListView_DeleteAllItems (ghListView);
                                }
                            }
                            lvi.iItem = ListView_GetNextItem (hListView, lvi.iItem, LVNI_SELECTED);
                        }
                    }
                    // fall through
                case IDCANCEL :
                    ListView_SetImageList (GetDlgItem (hDlg, IDC_SERVER_LIST), NULL, LVSIL_SMALL);
                    EndDialog (hDlg, (LOWORD(wParam) == IDOK ? TRUE : FALSE));
                    return TRUE;
            }
    }
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//    GetServerNameFromTitle()
//
//    Parameters
//
//    Purpose
//      
//    Return Value
//      
void WINAPI GetServerNameFromTitle (LPTSTR szItemTitle, LPTSTR * pszServerName)
{
    LPTSTR pStr = &(szItemTitle[lstrlen (szItemTitle)]);
    while ('\\' != *pStr)
    {
        pStr--;
    }
    pStr--;
    *pszServerName = pStr;
}

///////////////////////////////////////////////////////////////////////////////
//    ServerChanged()
//
//    Parameters
//
//    Purpose
//      
//    Return Value
//      
HRESULT WINAPI ServerChanged (HWND hTreeView)
{
    HTREEITEM hParent, hItem = TreeView_GetSelection (hTreeView);
    do
    {
        hParent = TreeView_GetParent (hTreeView, hItem);
        if (hParent)
        {
            hItem = hParent;
        }
    } while (hParent);
    
    LPTSTR szServerName;
    HRESULT hResult = S_OK;;
    TCHAR szBuffer[128];
    TV_ITEM tvItem = { 0 };
    tvItem.mask = TVIF_TEXT;
    tvItem.pszText = szBuffer;
    tvItem.cchTextMax = 128;
    tvItem.hItem = hItem;
    if (TRUE == TreeView_GetItem (hTreeView, &tvItem))
    {
        GetServerNameFromTitle (szBuffer, &szServerName);
        if (szServerName && lstrcmpi (g_szCurrentServer, szServerName) && szServerName[0])
        {
            // Terminate the notifications with the current selected server
            gpLink->EndNotifications();
            // Release the RPC binding resources
            BindToServer (NULL);
            // Copy the server name to the global buffer
            lstrcpy (g_szCurrentServer, szServerName);
            // Set the RPC binding resources to point to the new server
            BindToServer (g_szCurrentServer);
            // Establish notification with the new server we are talking to
            gpLink->StartNotification();
        }
    }
    else
    {
        hResult = E_FAIL;
    }
    return hResult;
}

// End of file for ADMIN.CPP
