/*
 -  C L I E N T . C
 -
 *    Purpose:
 *      Sample routing mail client for the MAPI SDK.
 *      Exclusively uses the Extended MAPI interface.
 *
 *  Copyright 1986-1996, Microsoft Corporation. All Rights Reserved.
 *
 */

#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <windowsx.h>
#ifdef _WIN32
#include <objerror.h>
#include <objbase.h>
#endif
#ifdef WIN16
#include <compobj.h>
#endif
#include <mapiutil.h>
#include <mapidbg.h>
#include <mapix.h>
#include <mapiwin.h>
#include <pdkver.h>
#include <mapiform.h>
#include <ole2.h>
#include <wrap3d.h>

#define USES_IID_IMAPIStatus 1
#define USES_IID_IMessage  1
#include <mapiguid.h>

#include "client.h"
#include "bitmap.h"
#include "route.h"
#ifdef _WIN32
#include "chsfld.h"
#endif

#ifdef WIN16
#define GWL_USERDATA    DWL_USER
#endif


/* Application instance */
HANDLE hInst;
                            
/* Static Data */

static ULONG cbeidFolderToView;
static LPENTRYID lpeidFolderToView = NULL;

LPADRBOOK pabAddrB = NULL;
LPMAPISESSION pses = NULL;
LPMDB pmdb = NULL;
LPMAPIFOLDER pfldOutBox = NULL;
LPSPropValue pvalSentMailEID = NULL;
HCURSOR hWaitCur;

LPVOID lpCtl3d = NULL;      /* 3D control context */

#ifdef _WIN32
/* Choose folder stuff */
HMODULE             g_hChsFldDll;
HRPICKFOLDER        g_lpfnHrPickFolder;
ULONG               cbCFDState = 0;
LPBYTE              pbCFDState = NULL;
#endif /*_WIN32 */

int PASCAL
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpszCmd, int nCmdShow)
{
    MSG msg;

    if (!hPrevInst)
        if (!InitApplication (hInstance))
            return (FALSE);

    if (!InitInstance (hInstance, nCmdShow))
        return (FALSE);

    while (GetMessage (&msg, 0, 0, 0))
    {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }

    DeinitApplication ();

    return (msg.wParam);
}

/*
 -  InitApplication
 -
 *  Purpose:
 *      Initialize the application.
 *
 *  Parameters:
 *      hInstance   - Instance handle
 *
 *  Returns:
 *      True/False
 *
 */

BOOL
InitApplication (HANDLE hInstance)
{
    WNDCLASS wc;

    wc.style = 0;
    wc.lpfnWndProc = MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (hInstance, "NoMail");
    wc.hCursor = LoadCursor (0, IDC_ARROW);
    wc.hbrBackground = GetStockObject (WHITE_BRUSH);
    wc.lpszMenuName = "MailMenu";
    wc.lpszClassName = "RoutingSample";

    return (RegisterClass (&wc));
}

/*
 -  InitInstance
 -
 *  Purpose:
 *      Initialize this instance.
 *
 *  Parameters:
 *      hInstance   - Instance handle
 *      nCmdShow    - Do we show the window?
 *
 *  Returns:
 *      True/False
 *
 */

BOOL
InitInstance (HANDLE hInstance, int nCmdShow)
{
    HWND hWnd;
    BOOL fInit;
    BOOL f;

    hInst = hInstance;

    fInit = InitMAPI(0);

    if (!lpCtl3d)
    {
        lpCtl3d = CTL3D_Initialize(hInstance);
        CTL3D_AutoSubclass(lpCtl3d, hInstance, &f);
    }

    hWnd = CreateWindow ("RoutingSample", "Routing Sample", WS_OVERLAPPEDWINDOW,
        5, 5, 550, 75, 0, 0, hInst, NULL);

    if (!hWnd)
        return (FALSE);

    ShowWindow (hWnd, nCmdShow);
    UpdateWindow (hWnd);

    hWaitCur = LoadCursor(0, IDC_WAIT);

    if (fInit)
    {
        if (ClientLogon (hWnd))
            ToggleMenuState (hWnd, TRUE);
    }

    return (fInit);
}

BOOL
InitMAPI (HWND hWnd)
{
    HRESULT hr;

    hr = MAPIInitialize(NULL);
    if(hr)
    {
        MakeMessageBox(hWnd, GetScode(hr), IDS_MAPIINIF, NULL, MBS_ERROR);
        return FALSE;
    }
    return TRUE;
}

void
DeinitApplication ()
{
    DeinitMAPI ();

    CTL3D_Uninitialize(lpCtl3d);
    lpCtl3d = NULL;

#ifdef _WIN32
    if(g_hChsFldDll)
        FreeLibrary(g_hChsFldDll);
        
#endif /* _WIN32 */
}

void
DeinitMAPI ()
{
    MAPIUninitialize();

}

/*
 *  Log on to MAPI
 *  
 *  Error messages are in subroutings.
 *
 *  Globals:
 *      pses        MAPI session handle
 *      pmdb        MAPI message store object
 *      pabAddrB    MAPI address book object
 *      pfldOutBox  Out folder
 *      pvalSentMailEID     EntryID of the "Sent mail" folder
 */

BOOL ClientLogon (HWND hWnd)
{
    HRESULT hr;
    /* We should not yet be logged on*/
    Assert(pses == NULL);
    Assert(pmdb == NULL);

    
        /* MAPILogon might yield control to Windows. So to prevent the user
    from clicking "logon" while we are in the process of loggin on we
    have to disable it*/

    SecureMenu(hWnd, TRUE);

    /* Create a MAPI session*/
    hr = MAPILogonEx((ULONG) hWnd, NULL, NULL,
            MAPI_EXTENDED | MAPI_EXPLICIT_PROFILE | MAPI_LOGON_UI |
            MAPI_NEW_SESSION, &pses);
    if(hr)
    {
        SecureMenu(hWnd, FALSE);
        pses = NULL;
        if (GetScode(hr) != MAPI_E_USER_CANCEL)
            MakeMessageBox (hWnd, GetScode(hr), IDS_LOGONFAIL, NULL, MBS_ERROR);
        return FALSE;
    }


    pmdb = OpenDefaultStore(hWnd);
    if (!pmdb) goto err;

    pabAddrB = OpenAddressBook(hWnd);
    if (!pabAddrB) goto err;

    if(!OpenOutFolder(hWnd, &pfldOutBox)) goto err;
    
    /* retrieve the EntryID of the sentmail folder and change the property tag
        so that it is ready to use on a message*/
    hr = HrGetOneProp((LPMAPIPROP)pmdb, PR_IPM_SENTMAIL_ENTRYID, &pvalSentMailEID);
    if(hr)
    {
        goto err;
    }
    pvalSentMailEID->ulPropTag = PR_SENTMAIL_ENTRYID;

    return TRUE;

err:
    
    ClientLogoff(hWnd);
    SecureMenu(hWnd, FALSE);
    
    return FALSE;
}

/*
 *  Releases  the global objects and logs off MAPI.
 *
 *  Globals:
 *      pses        Extended-MAPI session object
 *      pmdb        Extended-MAPI message store object
 *      pabAddrB        Address Book
 *      pfldOutBox  out folder
 *      pvalSetmailEID contains EID of the "Sent" folder
 */
VOID
ClientLogoff (HWND hWnd)
{

#ifdef _WIN32
    MAPIFreeBuffer(pbCFDState);
    pbCFDState = NULL;
    cbCFDState = 0;
#endif

    UlRelease(pfldOutBox);
    pfldOutBox = NULL;

    UlRelease(pmdb);
    pmdb = NULL;

    UlRelease(pabAddrB);
    pabAddrB = NULL;

    MAPIFreeBuffer(pvalSentMailEID);
    pvalSentMailEID = NULL;

    pses->lpVtbl->Logoff(pses, (ULONG)hWnd, MAPI_LOGOFF_UI, 0);
    UlRelease(pses);
    pses = NULL;

    SetWindowText(hWnd, "Routing Sample");
}

LPMDB
OpenDefaultStore(HWND hWnd)
{
    HRESULT hr;
    LPMDB lpmdb = NULL;
    LPMAPITABLE ptable = NULL;
    LPSRowSet prows = NULL;
    LPSPropValue pvalProp = NULL;
    static SizedSPropTagArray(2, columns) =
                { 2, { PR_DEFAULT_STORE, PR_ENTRYID} };
    SPropValue valDefStore;
    SPropertyRestriction restpropDefStore;
    SRestriction restDefStore;

    
    valDefStore.ulPropTag = PR_DEFAULT_STORE;
    valDefStore.dwAlignPad = 0;
    valDefStore.Value.b = TRUE;

    restpropDefStore.relop = RELOP_EQ;
    restpropDefStore.ulPropTag = PR_DEFAULT_STORE;
    restpropDefStore.lpProp = &valDefStore;

    restDefStore.rt = RES_PROPERTY;
    restDefStore.res.resProperty = restpropDefStore;

    hr = pses->lpVtbl->GetMsgStoresTable(pses, 0, &ptable);
    if (HR_FAILED(hr))
    {
        MakeMessageBox (hWnd, GetScode(hr), IDS_STORETBLFAIL, NULL, MBS_ERROR);
        goto ret;
    }

    
    hr = HrQueryAllRows(ptable, (LPSPropTagArray) &columns, &restDefStore, NULL, 0, &prows);
    if (HR_FAILED(hr))
    {
        MakeMessageBox (hWnd, GetScode(hr), IDS_QUERYROWFAIL, NULL, MBS_ERROR);
        goto ret;
    }

    if (prows == NULL || prows->cRows == 0
        || prows->aRow[0].lpProps[1].ulPropTag != PR_ENTRYID)
    {
        MakeMessageBox (hWnd, 0L, IDS_NODEFAULTSTORE, NULL, MBS_ERROR);
        goto ret;
    }
    
    Assert(prows->cRows == 1);

    hr = pses->lpVtbl->OpenMsgStore(pses, (ULONG)hWnd,
                        prows->aRow[0].lpProps[1].Value.bin.cb,
                        (LPENTRYID)prows->aRow[0].lpProps[1].Value.bin.lpb,
                        NULL, MDB_WRITE | MAPI_DEFERRED_ERRORS, &lpmdb);
    if (HR_FAILED(hr))
    {
        if (GetScode(hr) != MAPI_E_USER_CANCEL)
            MakeMessageBox (hWnd, GetScode(hr), IDS_OPENSTOREFAIL, NULL, MBS_ERROR);
        Assert(lpmdb == NULL);
        goto ret;
    }
    if(hr) /*if we have a warning, display it and succeed */
    {
        LPMAPIERROR perr = NULL;

        pses->lpVtbl->GetLastError(pses, hr, 0, &perr);
        MakeMessageBox(hWnd, GetScode(hr), IDS_OPENSTOREWARN, perr, MBS_ERROR);
        MAPIFreeBuffer(perr);
    }


    Assert(lpmdb != NULL);

    hr = HrGetOneProp((LPMAPIPROP)lpmdb, PR_DISPLAY_NAME, &pvalProp);
    if(!hr)
    {   
        char buf[128];

        wsprintf(buf, "Routing Sample: %s", pvalProp->Value.lpszA);

        SetWindowText(hWnd, buf);
        MAPIFreeBuffer(pvalProp);
    }
                    
ret:
    FreeProws(prows);
    UlRelease(ptable);

    return lpmdb;
}


#ifdef _WIN32
BOOL FGetFoldChooser(void)
{
    UINT uiErrMode;
    
    if(g_lpfnHrPickFolder)
        return TRUE;

    Assert(!g_hChsFldDll);

    uiErrMode = SetErrorMode(SEM_NOOPENFILEERRORBOX);

    g_hChsFldDll = LoadLibrary(szChsFldDllName);

    SetErrorMode(uiErrMode);

    if(g_hChsFldDll)
    {
        if((g_lpfnHrPickFolder = (HRPICKFOLDER)GetProcAddress(g_hChsFldDll,
                                        szChsFldFnName)))
        {
            return TRUE;
        }

        DebugTrace("route.cli: GetProcAddress for %s failed", szChsFldFnName);
        
        FreeLibrary(g_hChsFldDll);
        g_hChsFldDll = NULL;
    }
    else
    {
        DebugTrace("smpfrm: failed to load choose folder dll\n");
    }

    return FALSE;
}
#endif /* _WIN32 */

/*
 -  MainWndProc
 -
 *   Purpose:
 *      Main Window Procedure.
 *      Handles the menu bar and standard window messages.
 *
 *   Parameters:
 *       hWnd
 *       message
 *       wParam
 *       lParam
 *
 *   Returns:
 *
 *
 */

LONG FAR PASCAL
MainWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    HANDLE_MSG(hWnd, WM_COMMAND, MAIN_OnCommand);
    
    case WM_ENDSESSION:
        DestroyWindow (hWnd);
        break;

    case WM_CLOSE:
    case WM_DESTROY:
        if (pses)
            ClientLogoff (hWnd);

        PostQuitMessage (0);
        break;

    default:
        return (DefWindowProc (hWnd, msg, wParam, lParam));
    }
    return FALSE;
}


LONG MAIN_OnCommand(HWND hWnd, int id, HWND hwndCtl, UINT codeNotify)
{
    HRESULT hr;
#ifndef _WIN32
    LPDIALOGDATA pDialogData;
#endif
    LPMESSAGE pmsgOutgoing = NULL;
    ULONG ulMsgToken = 0;
    
    switch (id)
    {
    case IDM_NEWFORM:
        {
            LPMAPIFORMMGR pfmmgr = NULL;
            LPMAPIFORMINFO pfminfo = NULL;          
            LPSPropValue pvalMsgClass = NULL;
            LPMESSAGE pmsgForm = NULL;

            hr = MAPIOpenFormMgr(pses, &pfmmgr);
            if(!hr)
            {
                hr = pfmmgr->lpVtbl->SelectForm(pfmmgr, (ULONG) hWnd, 0, NULL, NULL, &pfminfo);

                if(!hr)
                {
                    
                    /*Get the form's msg class */
                    hr = HrGetOneProp((LPMAPIPROP)pfminfo, PR_MESSAGE_CLASS, &pvalMsgClass);
                    DebugTraceResult(HrGetOneProp, hr);
                    
                    if(!hr)
                    {
                        /*create new message*/
                        if(CreateOutMessage(&pmsgForm))
                        {
                            hr = pses->lpVtbl->PrepareForm(pses, NULL, pmsgForm, (LPULONG) &ulMsgToken);
                            if(S_OK != GetScode(hr))
                            {
                                DebugTrace("Client: PrepareForm failed");
                                break;
                            }
                            UlRelease(pmsgForm);
                            pmsgForm = NULL;
                
                            hr = pses->lpVtbl->ShowForm(pses, (ULONG) hWnd, pmdb, pfldOutBox,
                                                        NULL, ulMsgToken, NULL, MAPI_NEW_MESSAGE,
                                                        0, MSGFLAG_UNSENT | MSGFLAG_READ, 0,
                                                        pvalMsgClass->Value.lpszA );
                            if(S_OK != GetScode(hr))
                            MakeMessageBox(hWnd, GetScode(hr), IDS_SHOWFORM, NULL, MBS_ERROR);
                        }
                        else
                            MakeMessageBox(hWnd, 1, IDS_CRTOUTMSG, NULL, MBS_ERROR);
                    }

                    MAPIFreeBuffer(pvalMsgClass);
                    UlRelease(pfminfo);
                }

                UlRelease(pfmmgr);
            }
        }
                
        break;              
                

    case IDM_LOGON:
        if (!pses)
        {
            if (ClientLogon (hWnd))
                ToggleMenuState (hWnd, TRUE);
        }
        break;
    
    case IDM_LOGOFF:
        if (pses)
        {
            ClientLogoff (hWnd);
            ToggleMenuState (hWnd, FALSE);
        }
        break;                  
        
    case IDM_HIER:
        Assert(pses);
        //on win32 use the sample Choose Folder Dialog
#ifdef _WIN32 
        {
            HRESULT hr;
            LPMAPIFOLDER pfld = NULL;
            LPMDB pmdbNew = NULL;

            if(!FGetFoldChooser())
                return TRUE;
                
            hr = (*g_lpfnHrPickFolder)(NULL, hWnd, pses, &pfld, &pmdbNew,
                                    &cbCFDState, &pbCFDState);
            if(HR_SUCCEEDED(hr))
            {
                LPSPropValue pval = NULL;

                UlRelease(pmdb);
                pmdb = pmdbNew;
                pmdbNew = NULL;

                hr = HrGetOneProp((LPMAPIPROP)pmdb, PR_DISPLAY_NAME, &pval);
                if(!hr)
                {   
                    char buf[128];

                    wsprintf(buf, "Routing Sample: %s", pval->Value.lpszA);

                    SetWindowText(hWnd, buf);
                    MAPIFreeBuffer(pval);
                    pval = NULL;
                }

    
                hr = HrGetOneProp((LPMAPIPROP)pfld, PR_ENTRYID, &pval);
                if(!hr)
                {
                    cbeidFolderToView = pval->Value.bin.cb;
                    lpeidFolderToView = (LPENTRYID)pval->Value.bin.lpb;

                    DialogBox (hInst, "InBox", hWnd, InBoxDlgProc);

                    cbeidFolderToView = 0;
                    lpeidFolderToView = NULL;

                    MAPIFreeBuffer(pval);
                }
                
                UlRelease(pfld);
            }
        }

#else

        
        Assert(pmdb);
        if (pDialogData = CreateDialogData (iHierarchy))
            DialogBoxParam (hInst, "HierarchyTable", hWnd, CommonDlgProc, (LPARAM)pDialogData);
#endif /* _WIN32 */
        break;

#ifndef _WIN32        
    case IDM_OPEN:
        Assert(pses);
        if (pDialogData = CreateDialogData (iStores))
            DialogBoxParam (hInst, "OpenStore", hWnd, CommonDlgProc, (LPARAM)pDialogData);
        break;
#endif /* _WIN32 */
                                                                      
    case IDM_ROUTE:
        Assert(pses);
        DialogBoxParam(hInst, "RouteNote", hWnd, RouteNoteDlgProc, (LPARAM) NULL );
        break;

    case IDM_READ:
        Assert(pses);
        Assert(pmdb);
        Assert(lpeidFolderToView == NULL);

        {
            /* Get the entry ID of the Inbox from the message store. */
            if ((hr = pmdb->lpVtbl->GetReceiveFolder(pmdb,
                    "IPM", 0,
                    &cbeidFolderToView, &lpeidFolderToView, NULL))
                        == hrSuccess)
            {
                DialogBox (hInst, "InBox", hWnd, InBoxDlgProc);
                MAPIFreeBuffer(lpeidFolderToView);
                lpeidFolderToView = NULL;
            }
            else
                MakeMessageBox (hWnd, GetScode(hr), IDS_GETRCVFAIL, NULL, MBS_ERROR);
        }
        break;

    case IDM_SEND:
        Assert(pses);
        {
            if(CreateOutMessage(&pmsgOutgoing))
            {
                hr = pses->lpVtbl->PrepareForm(pses, NULL, pmsgOutgoing, (LPULONG) &ulMsgToken);
                if(S_OK != GetScode(hr))
                {
                    DebugTrace("Client: PrepareForm failed");
                    break;
                }
                UlRelease(pmsgOutgoing);
                pmsgOutgoing = NULL;
                
                hr = pses->lpVtbl->ShowForm(pses, (ULONG) hWnd, pmdb, pfldOutBox, NULL, ulMsgToken,
                                            NULL, MAPI_NEW_MESSAGE, 0, MSGFLAG_UNSENT | MSGFLAG_READ, 0, "IPM.Note");
                if(S_OK != GetScode(hr))
                    MakeMessageBox(hWnd, GetScode(hr), IDS_SHOWFORM, NULL, MBS_ERROR);
            }
            else
                MakeMessageBox(hWnd, 1, IDS_CRTOUTMSG, NULL, MBS_ERROR);                

        }
        break;
          
    case IDM_ABOUT:
        DialogBox (hInst, "AboutBox", hWnd, AboutDlgProc);
        break;
    

    case IDM_EXIT:
        if (pses)
            ClientLogoff (hWnd);
    
        PostQuitMessage (0);
        break;

        default:
            return TRUE;
    }

    return FALSE;
}
    

/*
 *  Displays an About dialog for the sample client.
 */

BOOL CALLBACK
AboutDlgProc (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    char    rgchVersion[80];

    switch (msg)
    {
    case WM_INITDIALOG:
        wsprintf(rgchVersion, "Version %d.%d.%d (%s)", rmj, rmm, rup,
            szVerName && *szVerName ? szVerName : "BUDDY");
        SetDlgItemText(hDlg, IDC_VERSION, rgchVersion);
        return TRUE;

    case WM_COMMAND:
        if (wParam == IDOK || wParam == IDCANCEL)
        {
            EndDialog (hDlg, TRUE);
            return TRUE;
        }
        break;
    }
    return FALSE;
}
            


/*
 *  Handles the Inbox list view, its command buttons.
 *  The main window is a listbox presenting a summary line for
 *  each message in the Inbox. There are command buttons for
 *  refreshing the list, displaying a message, and deleting a
 *  message.
 *
 *  All operations are on single messages; multiple selection is
 *  not supported.
 *
 *  The EntryID of the folder to examine is passed in using
 *  the global lpeidFolderToView.
 */

BOOL CALLBACK
InBoxDlgProc (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LPMSGID lpMsgIdList = NULL;
    HCURSOR hOldCur;
    LPMESSAGE pmsgRead = NULL;
    ULONG ulObjType = 0;
    ULONG ulMsgToken = 0;
    LPINBOXDATA pIBData = NULL;

    switch (msg)
    {
    case WM_INITDIALOG:
        if(MAPIAllocateBuffer(sizeof(INBOXDATA), &pIBData))
        {
            EndDialog(hDlg, FALSE);
            return TRUE;
        }
        
        hOldCur = SetCursor(hWaitCur);

        ZeroMemory(pIBData, sizeof(INBOXDATA));
        
        InitBmps(hDlg, IDC_MSG);

        /* Populate List Box with all messages in InBox. */
        PopulateMessages(hDlg, pIBData);

        SetCursor(hOldCur);
        SetFocus (GetDlgItem (hDlg, IDC_MSG));
        SetWindowLong(hDlg, GWL_USERDATA, (LONG)pIBData);
        return TRUE;
        break;

    case WM_SETFOCUS:
        SetFocus (GetDlgItem (hDlg, IDC_MSG));
        break;

    case WM_MEASUREITEM:
        /* Sets the height of the owner-drawn List-Box */
        MeasureItem(hDlg, (MEASUREITEMSTRUCT *)lParam);
        break;

    case WM_DRAWITEM:
        DrawItem((DRAWITEMSTRUCT *)lParam);
        break;

    case WM_CHARTOITEM:     /* don't select item by character*/
        return  -2;

    /* Handled by IDC_DELETE */
    case WM_DELETEITEM:
        return TRUE;
    HANDLE_MSG(hDlg, WM_COMMAND, INBOX_OnCommand);
        break;
    }

    return FALSE;
}

void INBOX_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
    LPMSGID lpMsgNode = NULL;
    LPINBOXDATA pibData = NULL;
    HCURSOR hOldCur;
    UINT nIndex;
    RECT Rect;
    LPMESSAGE pmsgRead = NULL;
    ULONG ulObjType = 0;
    HRESULT hr;
    ULONG ulMsgToken = 0;
    ULONG cProps = 0;
    LPSPropValue pvalProps = NULL;
    LONG lStat = 0, lFlags = 0, lAccess = 0;
    LPSTR lpszMsgClass = "IPM.Note";

    enum { PRSTAT, PRFLAGS, PRACCESS, PRCLASS, PRDIM};      /* used to retrieve props*/
    SizedSPropTagArray(PRDIM, sptaSFProps) =                /*required for ShowForm call*/
    { PRDIM, {PR_MSG_STATUS, PR_MESSAGE_FLAGS, PR_ACCESS_LEVEL, PR_MESSAGE_CLASS} };

    
    switch (id)
    {
    
    case IDC_FLUSH:
        hr = DeliverNow(hDlg);
        if(hr)
            break;
         /*fall through if the flush was succesfull*/
    case IDC_NEW:
        
        pibData = (LPINBOXDATA)GetWindowLong(hDlg, GWL_USERDATA);
        if(!pibData)
        {
            DebugTrace("Client: userdata == 0 (inboxdlgproc)");
        }
        hOldCur = SetCursor(hWaitCur);
    
        /* Destroy the old message list. */
        FreeMsgList (pibData->lpMsgIdList);
        pibData->lpMsgIdList = NULL;

        /* Populate List Box with all messages in InBox. */
        PopulateMessages(hDlg, pibData);
        
        SetCursor(hOldCur);
        break;

    case IDC_MSG:
        if(codeNotify != LBN_DBLCLK)
        break;
        /* FALL THROUGH to read the double-clicked message */
    
    case IDC_READ:
        nIndex = (UINT)ListBox_GetCurSel(GetDlgItem(hDlg, IDC_MSG));
        if (nIndex == LB_ERR)
        break;
    
        lpMsgNode = (LPMSGID)ListBox_GetItemData(GetDlgItem(hDlg, IDC_MSG), nIndex);
        if (lpMsgNode)
        {   
            hr = pmdb->lpVtbl->OpenEntry(pmdb, lpMsgNode->cbEID, lpMsgNode->lpEID,
                                NULL, MAPI_BEST_ACCESS | MAPI_DEFERRED_ERRORS,
                                &ulObjType, (LPUNKNOWN FAR *) &pmsgRead);
    
            if(S_OK != GetScode(hr))
            {
                LPMAPIERROR perr = NULL;
                
                pmdb->lpVtbl->GetLastError(pmdb, hr, 0, &perr);
                MakeMessageBox(hDlg, GetScode(hr), IDS_READFAIL, perr, MBS_ERROR);
                MAPIFreeBuffer(perr);
                DebugTrace("Client: OpenEntry failed");
                break;
            }
            else
            { 
                Assert(ulObjType == MAPI_MESSAGE);
    
                lpMsgNode->fUnRead = FALSE;
        
                /* get all the props in one call */
                hr = pmsgRead->lpVtbl->
                GetProps(pmsgRead, (LPSPropTagArray)&sptaSFProps, 0,
                                                    &cProps, &pvalProps);
                if(HR_SUCCEEDED(hr))
                {
                    if(pvalProps[PRSTAT].ulPropTag == PR_MSG_STATUS) 
                        lStat = pvalProps[PRSTAT].Value.l;
                    if(pvalProps[PRFLAGS].ulPropTag == PR_MESSAGE_FLAGS)
                        lFlags = pvalProps[PRFLAGS].Value.l;
                    if(pvalProps[PRACCESS].ulPropTag == PR_ACCESS_LEVEL)
                        lAccess = pvalProps[PRACCESS].Value.l;
                    if(pvalProps[PRCLASS].ulPropTag == PR_MESSAGE_CLASS)
                        lpszMsgClass = pvalProps[PRCLASS].Value.lpszA;
                }
                
                else
                {
                    DebugTrace("Client: GetProps (for ShowForm) failed");
                    break;
                }
                
                if (!lstrcmpi(lpszMsgClass, lpszSmplRTMsgClass))
                {
                    DialogBoxParam(hInst, "RouteNote", hDlg, RouteNoteDlgProc, (LPARAM) pmsgRead);
                    /* RouteNoteDlgPropc will release pmsgRead*/
                }
                else
                {                                   
                    hr = pses->lpVtbl->PrepareForm(pses, NULL, pmsgRead, (LPULONG) &ulMsgToken);
                    if(S_OK != GetScode(hr))
                    {
                        DebugTrace("Client: PrepareForm failed");
                        MAPIFreeBuffer(pvalProps);
                        break;
                    }
                    UlRelease(pmsgRead);
                    pmsgRead = NULL;
                    hr = pses->lpVtbl->ShowForm(pses, (ULONG) hDlg, pmdb, pfldOutBox, NULL, ulMsgToken,
                                            NULL, 0, lStat, lFlags, lAccess, lpszMsgClass);
                    
                }
            }
            
        }
        
        MAPIFreeBuffer(pvalProps);
        pvalProps = NULL;
        /* Update the Messages List-Box with new icon */
        lpMsgNode = NULL;

        ListBox_GetItemRect(GetDlgItem(hDlg, IDC_MSG),nIndex, (LPARAM) &Rect);
        InvalidateRect(GetDlgItem(hDlg, IDC_MSG), &Rect, FALSE);
        
        break;
        
    case IDC_DELETE:
        {
        ENTRYLIST el;
        SBinary sb;
        
        nIndex = (UINT)ListBox_GetCurSel(GetDlgItem(hDlg, IDC_MSG));
        if (nIndex == LB_ERR)
            break;
    
        pibData = (LPINBOXDATA)GetWindowLong(hDlg, GWL_USERDATA);
        if(!pibData)
        {
            DebugTrace("Client: userdata == 0 (inboxdlgproc)");
        }
        
        lpMsgNode = (LPMSGID) ListBox_GetItemData(GetDlgItem(hDlg, IDC_MSG),
                                                nIndex);
        if (lpMsgNode)
        {   
            sb.cb = lpMsgNode->cbEID;
            sb.lpb = (LPBYTE)lpMsgNode->lpEID;
            el.cValues = 1;
            el.lpbin = &sb;

            hr = pibData->pfld->lpVtbl->
                    DeleteMessages(pibData->pfld, &el, 0, NULL, 0);
            DeleteMsgNode (lpMsgNode, &pibData->lpMsgIdList);
        }

        ListBox_DeleteString(GetDlgItem(hDlg, IDC_MSG), nIndex);
        }
        break;
    
    case IDC_CLOSE:
    case IDCANCEL:
        pibData = (LPINBOXDATA)GetWindowLong(hDlg, GWL_USERDATA);
        if(!pibData)
        {
            DebugTrace("Client: userdata == 0 (inboxdlgproc)");
            
        }
        
        FreeMsgList (pibData->lpMsgIdList);
        pibData->lpMsgIdList = NULL;
        UlRelease(pibData->pfld);
        pibData->pfld = NULL;
        MAPIFreeBuffer(pibData);
        pibData = NULL;
        DeInitBmps();
        EndDialog (hDlg, TRUE);
        break;
    
    default:
        break;
    }
}

/*
 *  DeliverNow flushes outbound and inboud queues.
 *
 */
HRESULT DeliverNow(HWND hWnd)
{
    HRESULT hr;
    LPMAPISTATUS pstatSpooler = NULL;
    ULONG ulObjType = 0;
    LPMAPITABLE ptblStatus = NULL;
    SizedSPropTagArray(1, columns) =
                { 1, { PR_ENTRYID} };
    SPropValue valSpooler;
    SPropertyRestriction restpropSpooler;
    SRestriction restSpooler;
    LPSRowSet prows = NULL;
    
    /*Build property restriction (PR_RESOURCE_TYPE == MAPI_SPOOLER)*/
    valSpooler.ulPropTag = PR_RESOURCE_TYPE;
    valSpooler.dwAlignPad = 0;
    valSpooler.Value.l = MAPI_SPOOLER;

    restpropSpooler.relop = RELOP_EQ;
    restpropSpooler.ulPropTag = PR_RESOURCE_TYPE;
    restpropSpooler.lpProp = &valSpooler;

    restSpooler.rt = RES_PROPERTY;
    restSpooler.res.resProperty = restpropSpooler;

    /*open session status table*/
    hr = pses->lpVtbl->GetStatusTable(pses, 0, &ptblStatus);
    if(hr)
    {
        DebugTraceResult(GetStatusTable, hr);
        goto err;
    }

    /*find a row corresponding to the spooler*/
    hr = HrQueryAllRows(ptblStatus, (LPSPropTagArray) &columns, &restSpooler, NULL, 0, &prows);
    if (HR_FAILED(hr))
    {
        DebugTraceResult(HrQueryAllRows, hr);
        goto err;
    }

    Assert(prows && prows->cRows == 1); /*hope the spooler is always there */
    Assert(prows->aRow[0].lpProps[0].ulPropTag == PR_ENTRYID);
    
    /*open spooler as a status object*/
    hr = pses->lpVtbl->
            OpenEntry(pses, prows->aRow->lpProps->Value.bin.cb,
                        (LPENTRYID)prows->aRow->lpProps->Value.bin.lpb,
                        &IID_IMAPIStatus, MAPI_BEST_ACCESS, &ulObjType,
                        (LPUNKNOWN FAR *) &pstatSpooler);
    if(hr)
    {
        DebugTraceResult(OpenEntry, hr);
        goto err;
    }

    Assert(ulObjType == MAPI_STATUS);

    /*call FlushQueues()*/
    hr = pstatSpooler->lpVtbl->FlushQueues(pstatSpooler, (ULONG) hWnd, 0, NULL, 
                                            FLUSH_DOWNLOAD | FLUSH_UPLOAD);
    if(hr)
    {
        DebugTraceResult(FlushQueues, hr);
        goto err;
    }
    
    /*release all used objects*/

err:
    UlRelease(ptblStatus);
    FreeProws(prows);
    UlRelease(pstatSpooler);

    return hr;
}

    /*
 -  MakeMessageBox
 -
 *  Purpose:
 *      Gets resource string and displays an error message box.
 *
 *  Parameters:
 *      hWnd            - Handle to parent window
 *      sc              - SCODE
 *      idString        - Resource ID of message in StringTable
 *      perr            - pointer to MAPIERROR from last GetLastError
 *      fStyle          - style for MessageBox
 *
 *  Returns:
 *      Void
 *
 */

void
MakeMessageBox (HWND hWnd, SCODE sc, UINT idString, LPMAPIERROR perr, UINT fStyle)
{
    char szMessage[512];
    char szbuf[256];

    if(!LoadString (hInst, idString, szMessage, 255))
        return;

    if(perr)
    {
        wsprintf(szbuf, "\n%s\n%s\nLowLevelError: 0x%08lx context: %ld ", (perr->lpszError ? perr->lpszError:""),
                        perr->lpszComponent ? perr->lpszComponent:"", perr->ulLowLevelError, perr->ulContext);
        lstrcat(szMessage, szbuf);
    }
    if (sc)
    {
        wsprintf (szbuf, "\nReturn Code: 0x%08lx", sc);
        lstrcat (szMessage, szbuf);
    }

    MessageBox (hWnd, szMessage, "Sample Routing Form", fStyle);
}


/*
 * Common Dialog Proc for store and folder listboxes
 *
 */
BOOL CALLBACK
CommonDlgProc (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    MEASUREITEMSTRUCT *pmis;
    DRAWITEMSTRUCT *pdis;
    HCURSOR hOldCur;
    LPDIALOGDATA pdd = (LPDIALOGDATA) GetWindowLong(hDlg, DWL_USER);

    switch (msg)
    {
    case WM_INITDIALOG:
        /* Remember the address of our dialog data*/
        SetWindowLong(hDlg, DWL_USER, lParam);
        pdd = (LPDIALOGDATA)lParam;
        Assert(pdd->poarHead == NULL);

        /*/ Load up the rows of the dialog*/
        hOldCur = SetCursor(hWaitCur);
        PopulateStores (hDlg, &pdd->poarHead, pdd->iDlgType,
            pdd->cbEntryID, pdd->lpEntryID);
        SetCursor(hOldCur);

        SetFocus (GetDlgItem (hDlg, IDC_MSG));
        return TRUE;

    case WM_DESTROY:
        /* Discard our dialog data*/
        FreeOarList(&pdd->poarHead);
        MAPIFreeBuffer(pdd);
        return TRUE;

    case WM_SETFOCUS:
        SetFocus (GetDlgItem (hDlg, IDC_MSG));
        break;

    case WM_MEASUREITEM:
        /* Sets the height of the owner-drawn List-Box */
        pmis = (MEASUREITEMSTRUCT *) lParam;
        pmis->itemHeight = 15;
        break;

    case WM_DRAWITEM:
        pdis = (DRAWITEMSTRUCT *) lParam;
        DrawOarItem (pdis, pdd->iDlgType);
        break;

    case WM_CHARTOITEM:     /* don't select item by character*/
        return -2;

    /* Handled by IDC_DELETE */
    case WM_DELETEITEM:
        return TRUE;

//  HANDLE_MSG(hDlg, WM_COMMAND, Common_OnCommand);
    case WM_COMMAND:
        return ((Common_OnCommand)((hDlg), (int)(wParam), (HWND)(LOWORD(lParam)), 0L));

    }   /* switch (msg) */

    return FALSE;
}


BOOL Common_OnCommand(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify)
{
    LPDIALOGDATA pdd = (LPDIALOGDATA) GetWindowLong(hDlg, DWL_USER);

    switch (id)
    {
    case IDC_MSG:
        if(codeNotify != LBN_DBLCLK)
            break;
            /* FALL THROUGH to read the double-clicked store */

    case IDC_DOWN:
    case IDC_READ:
        /*/ open a Hierarchy or Store*/
    {
            /*/ Open one of the items in the list*/
        LPMDB pmdbTemp;
        UINT nIndex;
        LPOAR poar;
        LPSPropValue pProp;
        LPSPropValue pvalProp = NULL;
        HRESULT hr;

        nIndex = (UINT)ListBox_GetCurSel(GetDlgItem(hDlg, IDC_MSG));

        if (nIndex == LB_ERR)
            return TRUE;

        poar = (LPOAR) ListBox_GetItemData(GetDlgItem(hDlg, IDC_MSG), nIndex);

        if (!poar)
            return TRUE;

                /* PropFindProp from mapiutil.h */
        pProp = PpropFindProp(poar->lpProps,  poar->cValues, PR_ENTRYID);
        
        Assert(pProp);
        /*/ Every row should have an EntryID */
        
        if (pdd->iDlgType == iStores)
        {
            hr = pses->lpVtbl->OpenMsgStore(pses,
                (ULONG)hDlg,
                pProp->Value.bin.cb,
                (LPENTRYID)pProp->Value.bin.lpb,
                NULL, MDB_WRITE, &pmdbTemp);

            if (HR_FAILED(hr))
            {
                if (GetScode(hr) != MAPI_E_USER_CANCEL)
                    MakeMessageBox (hDlg, GetScode(hr), IDS_OPENSTOREFAIL, NULL, MBS_ERROR);
                return TRUE;
                }
            if(hr) /*if we have a warning*/
            {
                LPMAPIERROR perr = NULL;

                pses->lpVtbl->GetLastError(pses, hr, 0, &perr);
                MakeMessageBox(hDlg, GetScode(hr), IDS_OPENSTOREWARN, perr, MBS_ERROR);
                MAPIFreeBuffer(perr);
            }


            Assert(hr == hrSuccess);    /* no warnings (for now?)*/

            UlRelease(pmdb);
            pmdb = pmdbTemp;

            /*Change the caption of the main window */
            hr = HrGetOneProp((LPMAPIPROP)pmdb, PR_DISPLAY_NAME, &pvalProp);
            if(!hr)
            {
                char buf[128];
            
                wsprintf(buf, "Routing Sample: %s", pvalProp->Value.lpszA);
                SetWindowText(GetParent(hDlg), buf);

                MAPIFreeBuffer(pvalProp);
                pvalProp = NULL;
            }
                    
            EndDialog (hDlg, TRUE);
            return TRUE;
        }

        Assert (pdd->iDlgType == iHierarchy);

        if (id == IDC_DOWN)
        {
            LPDIALOGDATA pDialogData;
            if (pDialogData = CreateDialogData (iHierarchy))
            {
                pDialogData->cbEntryID = pProp->Value.bin.cb;
                pDialogData->lpEntryID = (LPENTRYID)pProp->Value.bin.lpb;
                DialogBoxParam (hInst, "HierarchyTable", hDlg, CommonDlgProc, (LPARAM)pDialogData);
            }

        }
        else    /* IDC_READ */
        {
            /* OPEN a contents table*/
            Assert(lpeidFolderToView == NULL);
            cbeidFolderToView = pProp->Value.bin.cb;
            lpeidFolderToView = (LPENTRYID)pProp->Value.bin.lpb;
            DialogBox (hInst, "InBox", hDlg, InBoxDlgProc);
            lpeidFolderToView = NULL;
        }
    }
    return TRUE;

    case IDC_CLOSE:
    case IDCANCEL:
        EndDialog (hDlg, TRUE);
        return TRUE;

    }

    return TRUE;
}

/*
 -  PopulateStores
 -
 *  Accumulate all the rows of a table onto the OAR list.
 *  idlgType indicates iStores, iHierarchy.
 *
 *  If iHierarchy, the EntryID of the folder is in cb/lpeid.
 */

VOID
PopulateStores ( HWND hDlg, LPOAR FAR * ppoarHead, int idlgType,
        ULONG cb, LPENTRYID lpeid)
{
    HRESULT hr;
    SCODE sc;
    LPMAPIFOLDER pfld = NULL;
    LPMAPITABLE ptable = NULL;
    LPSRowSet prows = NULL;
    LPSPropValue pvalProp = NULL;
    UINT idx;

    /* Get the list of available message stores or folderes from MAPI*/
    Assert(pses);

    switch (idlgType)
    {
    case iStores:
        if (hr = pses->lpVtbl->GetMsgStoresTable(pses, 0, &ptable))
        {
            MakeMessageBox (hDlg, GetScode(hr), IDS_STORETBLFAIL, NULL, MBS_ERROR);
            goto ret;
        }
        break;
    case iHierarchy:
        {
            ULONG ulObjType;
            if (hr = pmdb->lpVtbl->OpenEntry(pmdb, cb, lpeid, NULL,
                                MAPI_DEFERRED_ERRORS,
                            &ulObjType, (LPUNKNOWN FAR *) &pfld))
            {
                MakeMessageBox (hDlg, GetScode(hr), IDS_OPENFOLDERFAIL, NULL, MBS_ERROR);
                goto ret;
            }
            Assert(ulObjType == MAPI_FOLDER);
            if (hr = pfld->lpVtbl->GetHierarchyTable(pfld, MAPI_DEFERRED_ERRORS,
                                                        &ptable))
            {
                MakeMessageBox (hDlg, GetScode(hr), IDS_STORETBLFAIL, NULL, MBS_ERROR);
                goto ret;
            }
            hr = HrGetOneProp((LPMAPIPROP)pfld, PR_DISPLAY_NAME, &pvalProp);
            if(!hr)
            {
                if(*pvalProp->Value.lpszA)
                    SetWindowText(hDlg, pvalProp->Value.lpszA);
                MAPIFreeBuffer(pvalProp);
                pvalProp = NULL;
            }
                    
        }
        break;
    default:
        Assert(0);
    }

    if(hr = HrQueryAllRows(ptable, NULL, NULL, NULL, 1000l, &prows))
    {
        MakeMessageBox (hDlg, GetScode(hr), IDS_QUERYROWFAIL, NULL, MBS_ERROR);
        goto ret;
    }
    for(idx = 0; idx < prows->cRows; ++idx)
    {
        LPOAR poar = NULL;
        sc = MAPIAllocateBuffer(sizeof(OAR), &poar);
        if (sc)
        {
            hr = ResultFromScode(sc);
            FreeProws(prows);   /* free ENTIRE row*/
            break;
        }
        /*/ Transfer the data of the row to our OAR structure.*/
        poar->cValues = prows->aRow[idx].cValues;
        poar->lpProps = prows->aRow[idx].lpProps;

        /* Put OAR at head of the list*/
        if (*ppoarHead)
            (*ppoarHead)->lpPrev = poar;
        poar->lpPrev = NULL;
        poar->lpNext = (*ppoarHead);
        *ppoarHead  = poar;

        ListBox_AddString(GetDlgItem(hDlg, IDC_MSG), (LONG) poar);
    }
    
    MAPIFreeBuffer(prows);  /* free OUTER buffer only*/

ret:
    UlRelease(ptable);
    UlRelease(pfld);
}

/*
 -  FreeOarList
 -
 *  Free the memory of the rows on the screen.
 *  Zero the pointer passed in.
 */
VOID
FreeOarList (LPOAR FAR *ppoarHead)
{
    LPOAR poar = *ppoarHead;

    while (poar)
    {
        LPOAR poarTemp = poar;

        poar = poarTemp->lpNext;
        MAPIFreeBuffer(poarTemp->lpProps);
        MAPIFreeBuffer(poarTemp);
    }

    *ppoarHead = NULL;
}

/*
 -  DrawOarItem
 -
 *  Purpose:
 *      Paint the client area of the owner-drawn listbox.
 *
 *  Parameters:
 *      pdis        - Pointer to a DRAWITEMSTRUCT
 *
 *  Returns:
 *      void
 *
 */

VOID
DrawOarItem (DRAWITEMSTRUCT FAR * pdis, int idlgType)
{
    HBRUSH hSolidBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
    HBRUSH hOldBrush = SelectObject(pdis->hDC, hSolidBrush);

    if (ODA_DRAWENTIRE & pdis->itemAction)
    {
        LPOAR poar;
        LPSPropValue pProp;
        UINT c;

        /* Clear the item Rectangle */

        PatBlt (pdis->hDC, pdis->rcItem.left, pdis->rcItem.top,
            pdis->rcItem.right - pdis->rcItem.left,
            pdis->rcItem.bottom - pdis->rcItem.top, PATCOPY);

        /* Draw the item */

        poar = (LPOAR) pdis->itemData;

        for (pProp = poar->lpProps, c = (UINT)poar->cValues;
            c > 0;
            c-- , pProp++)
        {
            /* Identify the Default Store*/
            if (idlgType == iStores
                    && pProp->ulPropTag == PR_DEFAULT_STORE && pProp->Value.b)
                TextOut (pdis->hDC, pdis->rcItem.left + 10, pdis->rcItem.top+2,
                    TEXT(">"), 1);

            if (pProp->ulPropTag == PR_DISPLAY_NAME)
                TextOut (pdis->hDC, pdis->rcItem.left + 20, pdis->rcItem.top+2,
                    pProp->Value.LPSZ,
                    lstrlen (pProp->Value.LPSZ));

        }

        /* Invert item rectangle if item is selected */

        if (ODS_SELECTED & pdis->itemState)
            PatBlt (pdis->hDC, pdis->rcItem.left, pdis->rcItem.top,
                pdis->rcItem.right - pdis->rcItem.left,
                pdis->rcItem.bottom - pdis->rcItem.top, DSTINVERT);

        /* Draw a focus rectangle if item has focus */

        if (ODS_FOCUS & pdis->itemState)
            DrawFocusRect (pdis->hDC, &pdis->rcItem);
    }
    else
    {
        /* Invert the item if the selection state is changing */

        if (ODA_SELECT & pdis->itemAction)
            PatBlt (pdis->hDC, pdis->rcItem.left, pdis->rcItem.top,
                pdis->rcItem.right - pdis->rcItem.left,
                pdis->rcItem.bottom - pdis->rcItem.top, DSTINVERT);

        /* Draw a focus if the focus state is changing */

        if (ODA_FOCUS & pdis->itemAction)
            DrawFocusRect (pdis->hDC, &pdis->rcItem);
    }

    SelectObject(pdis->hDC, hOldBrush);
    DeleteObject(hSolidBrush);
}


/* Fill the lppMsgIdList with info about the messages in the specified folder. */
enum { E_EID=0, E_SUBJECT, E_SENDER_NAME, E_MSG_DEL_TIME, E_FLAGS, E_PRIORITY, E_CONVERS_KEY,
        E_SEARCH_KEY, E_CLASS, E_RECORD_KEY, E_PTINBOXDIM};
SizedSPropTagArray(E_PTINBOXDIM, ptInbox) =
{
    E_PTINBOXDIM,
    {
        PR_ENTRYID,
        PR_SUBJECT,
        PR_SENDER_NAME,
        PR_MESSAGE_DELIVERY_TIME,
        PR_MESSAGE_FLAGS,
        PR_PRIORITY,
        PR_CONVERSATION_KEY,
        PR_SEARCH_KEY,
        PR_MESSAGE_CLASS,
        PR_RECORD_KEY
    }
};

VOID
PopulateMessages( HWND hDlg, LPINBOXDATA pibData )
{
    LPMAPIFOLDER pfld = pibData->pfld;
    LPMAPITABLE ptable = NULL;
    LPSRowSet prows = NULL;
    HRESULT hr;
    ULONG ulType;
    SizedSSortOrderSet(1, sos) =
        { 1, 0, 0, { PR_MESSAGE_DELIVERY_TIME, TABLE_SORT_ASCEND } };
    UINT nIndex;
    LPMSGID lpMsgNode;
    LPSPropValue pvalProp = NULL;

    ListBox_ResetContent(GetDlgItem(hDlg, IDC_MSG));

    if(!pfld)
    {
        /* Open the right folder, and get the list of messages. */
        hr = pmdb->lpVtbl->OpenEntry(pmdb,cbeidFolderToView, lpeidFolderToView,
                                 NULL, MAPI_BEST_ACCESS | MAPI_DEFERRED_ERRORS,
                                    &ulType, (LPUNKNOWN FAR *)&pfld);
        if(GetScode(hr) != S_OK)    goto ret;

        Assert(ulType == MAPI_FOLDER);
        pibData->pfld = pfld;
        hr = HrGetOneProp((LPMAPIPROP)pfld, PR_DISPLAY_NAME, &pvalProp);
        if(!hr)
        {
            if(*pvalProp->Value.lpszA)
                SetWindowText(hDlg, pvalProp->Value.lpszA);
            MAPIFreeBuffer(pvalProp);
            pvalProp = NULL;
        }
    }
    hr = pfld->lpVtbl->GetContentsTable(pfld, MAPI_DEFERRED_ERRORS, &ptable);
    if (hr)
        goto ret;

    if (hr = HrQueryAllRows(ptable, (LPSPropTagArray) &ptInbox, NULL,
        (LPSSortOrderSet) &sos, 0, &prows))
    {
        MakeMessageBox (hDlg, GetScode(hr), IDS_QUERYROWFAIL, NULL, MBS_ERROR);
        goto ret;
    }

    for (nIndex = 0; nIndex < prows->cRows; ++nIndex)
    {
        lpMsgNode = MakeMsgNode(prows->aRow + nIndex);

        if (lpMsgNode)
        {
            InsertMsgNode(lpMsgNode, &pibData->lpMsgIdList);

            ListBox_AddString(GetDlgItem(hDlg, IDC_MSG),(LONG) lpMsgNode);
        }
    }
    FreeProws(prows);

    

ret:
    UlRelease(ptable);
}

/*
 -  MakeMsgNode
 -
 *  Purpose:
 *      Allocate memory for a new MSGID node and initialize its
 *      data members to the values passed in.
 *      A separate allocation is used for each property which is pretty
 *      wastefull. This can be changed to a smarter allocation scheme.
 *
 *  Parameters:
 *      
 *  Return:
 *      lpMsgNode       - Pointer to new node
 */

LPMSGID
MakeMsgNode (LPSRow prow)
{
    LPMSGID lpMsgNode = NULL;

    if (!prow)
        goto err;

    if (MAPIAllocateBuffer (sizeof (MSGID), (LPVOID far *) & lpMsgNode))
        goto err;

    ZeroMemory(lpMsgNode, sizeof (MSGID));

    if(prow->lpProps[E_FLAGS].ulPropTag == PR_MESSAGE_FLAGS)
    {
        lpMsgNode->fHasAttach = !!(prow->lpProps[E_FLAGS].Value.l & MSGFLAG_HASATTACH);
        lpMsgNode->fUnRead = !(prow->lpProps[E_FLAGS].Value.l & MSGFLAG_READ);
    }

    if(prow->lpProps[E_EID].ulPropTag == PR_ENTRYID)
    {   
        if (MAPIAllocateMore(prow->lpProps[E_EID].Value.bin.cb, lpMsgNode,
                    (LPVOID FAR *)&lpMsgNode->lpEID))
            goto err;
        CopyMemory(lpMsgNode->lpEID, prow->lpProps[E_EID].Value.bin.lpb, prow->lpProps[E_EID].Value.bin.cb);
        lpMsgNode->cbEID = prow->lpProps[E_EID].Value.bin.cb;
    }

    if(prow->lpProps[E_SENDER_NAME].ulPropTag == PR_SENDER_NAME)
    {
        if (MAPIAllocateMore (lstrlen (prow->lpProps[E_SENDER_NAME].Value.LPSZ) + 1,
                    lpMsgNode, (LPVOID far *) & lpMsgNode->lpszFrom))
        goto err;
        lstrcpy (lpMsgNode->lpszFrom, prow->lpProps[E_SENDER_NAME].Value.LPSZ);
    }
        
    if(prow->lpProps[E_SUBJECT].ulPropTag == PR_SUBJECT)
    {
        if (MAPIAllocateMore (lstrlen (prow->lpProps[E_SUBJECT].Value.LPSZ) + 1, lpMsgNode,
                    (LPVOID far *) & lpMsgNode->lpszSubject))
            goto err;
        lstrcpy (lpMsgNode->lpszSubject, prow->lpProps[E_SUBJECT].Value.LPSZ);
    }
    
    if(prow->lpProps[E_MSG_DEL_TIME].ulPropTag == PR_MESSAGE_DELIVERY_TIME)
    {
        if (MAPIAllocateMore (32, lpMsgNode,(LPVOID far *) & lpMsgNode->lpszDateRec))
            goto err;
        FormatFILETIME (&prow->lpProps[E_MSG_DEL_TIME].Value.ft, lpMsgNode->lpszDateRec);
    }
    
    return lpMsgNode;

err:
    MAPIFreeBuffer (lpMsgNode);
    return NULL;
}

/*
 -  InsertMsgNode
 -
 *  Purpose:
 *      We insert the nodes
 *      at the beginning of the list.  This can be
 *      replaced with a routine that inserts sorted on
 *      different criteria, like DateReceived, From, or
 *      Subject.
 *
 *  Parameters:
 *      lpMsgNode       - Pointer to a MSGID node
 *      lppMsgHead      - Pointer to the head of the list
 *
 *  Return:
 *      Void.
 */

void
InsertMsgNode (LPMSGID lpMsgNode, LPMSGID * lppMsgHead)
{
    if (*lppMsgHead)
    {
        lpMsgNode->lpNext = *lppMsgHead;
        (*lppMsgHead)->lpPrev = lpMsgNode;
    }
    else
        lpMsgNode->lpNext = NULL;

    /* The next 2 assignments are here in case the node came from somewhere */
    /* other than a call to MakeMsgNode () in which case we aren't sure */
    /* they're already NULL. */

    lpMsgNode->lpPrev = NULL;
    *lppMsgHead = lpMsgNode;
}

/*
 -  DeleteMsgNode
 -
 *  Purpose:
 *      Removes the node passed in from the list.  This
 *      may seem like a strange way to do this but it's
 *      not, because the Owner-Drawn List Box gives us
 *      direct access to elements in the list that makes
 *      it easier to do things this way.
 *
 *  Parameters:
 *      lpMsgNode       - Pointer to the MSGID node to delete
 *      lppMsgHead      - Pointer to the head of the list
 *
 *  Return:
 *      Void.
 */

void
DeleteMsgNode (LPMSGID lpMsgNode, LPMSGID * lppMsgHead)
{
    if (!lpMsgNode)
        return;

    if (lpMsgNode->lpPrev)
    {
        /* Adjust Previous node to point to Next*/
        Assert(*lppMsgHead != lpMsgNode);
        lpMsgNode->lpPrev->lpNext = lpMsgNode->lpNext;
    }
    else
    {
        /*/ Adjust Head to point to Next*/
        Assert(*lppMsgHead == lpMsgNode);
        *lppMsgHead = lpMsgNode->lpNext;
    }

    /* Adjust next node to point to Previous*/

    if (lpMsgNode->lpNext)
        lpMsgNode->lpNext->lpPrev = lpMsgNode->lpPrev;

    MAPIFreeBuffer (lpMsgNode);
    return;
}



/*
 -  FindNode
 -
 *  Purpose:
 *      Returns a pointer to the node with EntryID equal to *pEntryID.
 *      Returns NULL if node doesn't exist.
 *
 *  Parameters:
 *      lpMsgHead       - Pointer to the head of the list
 *      pEntryID + cbEntryID    - Message ID to search for
 *
 *  Return:
 *      lpMsgNode       - Pointer to the node returned
 */

LPMSGID
FindNode (LPMSGID lpMsgHead, LPENTRYID pEntryID, ULONG cbEntryID)
{
    ULONG fl;
    HRESULT hr;

    Assert(pmdb);

    while (lpMsgHead)
    {
        hr = pmdb->lpVtbl->CompareEntryIDs(pmdb, cbEntryID, pEntryID, lpMsgHead->cbEID, lpMsgHead->lpEID,
                                            0, &fl);
        if(S_OK != GetScode(hr))
            return NULL;
        if(fl)
            break;

        lpMsgHead = lpMsgHead->lpNext;
    }

    return lpMsgHead;
}

/*
 -  FreeMsgList
 -
 *  Purpose:
 *      Walks down the MsgList and frees each node.
 *
 *  Parameters:
 *      lpMsgHead       - Pointer to the head of the list
 *
 *  Return:
 *      Void.
 */

void
FreeMsgList (LPMSGID lpMsgHead)
{
    LPMSGID lpT;

    while (lpMsgHead)
    {
        lpT = lpMsgHead;
        lpMsgHead = lpMsgHead->lpNext;
        MAPIFreeBuffer (lpT);
    }
}

/*
 -  ToggleMenuState
 -
 *  Purpose:
 *      Enables/Disables menu items depending on the session state.
 *
 *  Parameters:
 *      hWnd            - handle to the window/dialog who called us
 *      fLoggedOn       - TRUE if logged on, FALSE if logged off
 *
 *  Return:
 *      Void.
 */

void ToggleMenuState(HWND hWnd, BOOL fLoggedOn)
{
    EnableMenuItem (GetMenu (hWnd), IDM_HIER,     !fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_OPEN,     !fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_LOGOFF,   !fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_ROUTE,    !fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_READ,     !fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_SEND,     !fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_NEWFORM,  !fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_LOGON,    fLoggedOn);
    EnableMenuItem (GetMenu (hWnd), IDM_EXIT,       FALSE);
}

//
//  SecureMenu
//
//  Purpose:
//      Enables/Disables Logon and Exit menu items.
//      CMCLogon might yield control to Windows, so the user might be able to
//      access the window menu (for example click Logon) after we call
//      MAPILogon, but before it returns.
//
//  Parameters:
//      hWnd            - handle to the window/dialog who called us
//      fBeforeLogon    - TRUE when this function is called when we are about
//                      to call MAPILogon, FALSE if called after logon (failed)
//                      if Logon succeddes ToggleMenuState is called instead of
//                      this function.
//
//  Return:
//      Void.
//


void SecureMenu(HWND hWnd, BOOL fBeforeLogon)
{
    EnableMenuItem (GetMenu (hWnd), IDM_LOGON, fBeforeLogon);
    EnableMenuItem (GetMenu (hWnd), IDM_EXIT,  fBeforeLogon);
}


/*
 *  Formats a Win32 file time as a MAPI date/time string.
 *  NOTE: converts from GMT to local time.
 */
void FormatFILETIME(FILETIME *pft, LPSTR szTime)
{
    FILETIME        ft;
    SYSTEMTIME      systime;

    FileTimeToLocalFileTime(pft, &ft);
    FileTimeToSystemTime(&ft, &systime);
    wsprintf(szTime,
        "%04.4d/%02.2d/%02.2d %02.2d:%02.2d",
        systime.wYear, systime.wMonth, systime.wDay,
        systime.wHour, systime.wMinute);
}

/*
 *  Create a data block used in CommonDlgProc to remember
 *  the entire chain of rows in the scrolling list box.
 */
LPDIALOGDATA
CreateDialogData (int iDlgType)
{
    LPDIALOGDATA pDialogData;

    SCODE sc;

    sc = MAPIAllocateBuffer(sizeof(DIALOGDATA), &pDialogData);
    if (sc)
    {
        MakeMessageBox (0, MAPI_E_NOT_ENOUGH_MEMORY, IDS_OPERATION, NULL, MBS_ERROR);
        return NULL;
    }

    pDialogData->iDlgType = iDlgType;
    pDialogData->poarHead = NULL;
    pDialogData->cbEntryID = 0;
    pDialogData->lpEntryID = NULL;
    return pDialogData;
}

