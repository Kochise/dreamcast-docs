// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//
/*
    connect.c

    Dialog to establish a DDE connection

*/

#include "dderecon.h"

//
// local data
//

static bShowSystemItems;

//
// local functions
//

BOOL CALLBACK ServerDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);
void ShowTopicList(HWND hDlg);
void ShowItemList(HWND hDlg);
BOOL IsSystemItem(LPSTR lpszItem);
void AddItemsToList(HWND hDlg, BYTE FAR *pData, int idList);

//
// Show the dialog
//

BOOL ConnectDlg(HWND hwndParent, BOOL bSysInfo)
{
    DLGPROC fpDlg;
    BOOL bResult;

    bShowSystemItems = bSysInfo;
    fpDlg = (DLGPROC)MakeProcInstance((FARPROC)ServerDlgProc, hInst);
    bResult = DialogBox(hInst, MAKEINTRESOURCE(SERVERDLG), hwndParent, fpDlg);
    FreeProcInstance((FARPROC)fpDlg);

    return bResult;
}

//
// Connect dlg proc
//

BOOL CALLBACK ServerDlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HCONVLIST hConvList;
    UINT ui;
    HCONV hConv;
    CONVINFO cinfo;
    char buf[128];
    HSZ hszSystem;
    DWORD dwIndex;
    char szService[128];
    char szTopic[128];
    char szItem[128];

    switch (msg) {
    case WM_INITDIALOG:

        //
        // Disable the OK button until we get all the info filled in
        //

        EnableWindow(GetDlgItem(hDlg, IDOK), FALSE);

        //
        // Fill the list section of the combo box with the names
        // of all the DDE services we can find.  Try to establish
        // a conversation with every service which supports the 
        // 'system' topic.  Note we could establish conversation with 
        // all services with all topics but we need to use the system
        // topic later to get the topics list so if the server doesn't
        // support that we can't really use it.
        //

        hszSystem = DdeCreateStringHandle(dwDDEInst,
                                           SZDDESYS_TOPIC,
                                           CP_WINANSI);

        hConvList = DdeConnectList(dwDDEInst,
                                   NULL,
                                   hszSystem,
                                   NULL, // new list
                                   NULL); // default context

        DdeFreeStringHandle(dwDDEInst, hszSystem);

        if (!hConvList) {
            
            //
            // get the error code to see if there is an error
            // or simply no servers available
            //

            ui = DdeGetLastError(dwDDEInst);
            if (ui != DMLERR_NO_ERROR) {
                Error("Failed to connect to a server. Error %u", ui);
            }

        } else {

            //
            // Walk the list adding the server names to our listbox
            //

            hConv = NULL;
            cinfo.cb = sizeof(CONVINFO); // VERY IMPORTANT 
 
            while (hConv = DdeQueryNextServer(hConvList, hConv)) {

                ui = DdeQueryConvInfo(hConv,
                                      (DWORD)QID_SYNC,
                                      &cinfo);

                //
                // Get the name of our service partner (the server)
                //

                DdeQueryString(dwDDEInst, 
                               cinfo.hszSvcPartner,
                               buf, 
                               sizeof(buf), 
                               CP_WINANSI);

                //
                // Add the name to the list box
                //

                SendDlgItemMessage(hDlg,
                                   ID_SVRLIST,
                                   CB_ADDSTRING,
                                   (WPARAM) 0,
                                   (LPARAM)(LPSTR)buf);


            }

            //
            // Free the list handle
            //

            DdeDisconnectList(hConvList);

        }

        //
        // If we have already got a connection, try to select
        // the name in the list, otherwise don't
        // select anything.
        //

        if (lstrlen(szCurrentService) != 0) {

            //
            // Find this one in the list and select it
            //

            dwIndex = SendDlgItemMessage(hDlg,
                                         ID_SVRLIST,
                                         CB_SELECTSTRING,
                                         (WPARAM) 0,
                                         (LPARAM)(LPSTR)szCurrentService);
        }

        //
        // Show the topic list for the currently selected service
        //

        ShowTopicList(hDlg);

        break;

    case WM_COMMAND:

        if (HIWORD(lParam) == CBN_SELCHANGE) {

            //
            // The change to the edit control resulting from the 
            // listbox selection change does not generate a
            // CBN_EDITCHANGE message.  We *Post* it to ourself
            // here so that we will get it after the edit control
            // text has been updated.
            //

            PostMessage(hDlg,
                        WM_COMMAND,
                        wParam,
                        (LPARAM) MAKELONG(GetDlgItem(hDlg, wParam),
                                          CBN_EDITCHANGE));
        }

        switch (wParam) {
        case ID_SVRLIST:
            switch (HIWORD(lParam)) {
            case CBN_EDITCHANGE:
                ShowTopicList(hDlg);
                break;

            default:
                break;
            }
            break;

        case ID_TOPICLIST:
            switch (HIWORD(lParam)) {
            case CBN_EDITCHANGE:
                ShowItemList(hDlg);
                break;

            default:
                break;
            }
            break;

        case ID_ITEMLIST:

            switch (HIWORD(lParam)) {
            case CBN_EDITCHANGE:
                SendDlgItemMessage(hDlg, 
                                   ID_ITEMLIST,
                                   WM_GETTEXT,
                                   (WPARAM) sizeof(buf),
                                   (LPARAM) (LPSTR) buf);
                EnableWindow(GetDlgItem(hDlg, IDOK), lstrlen(buf));
                break;

            default:
                break;
            }
            break;

        case IDOK:

            szService[0] = '\0';
            SendDlgItemMessage(hDlg,
                               ID_SVRLIST,
                               WM_GETTEXT,
                               (WPARAM) sizeof(szService),
                               (LPARAM) (LPSTR) szService);

            szTopic[0] = '\0';
            SendDlgItemMessage(hDlg,
                               ID_TOPICLIST,
                               WM_GETTEXT,
                               (WPARAM) sizeof(szTopic),
                               (LPARAM) (LPSTR) szTopic);

            szItem[0] = '\0';
            SendDlgItemMessage(hDlg,
                               ID_ITEMLIST,
                               WM_GETTEXT,
                               (WPARAM) sizeof(szItem),
                               (LPARAM) (LPSTR) szItem);

            //
            // Try to link to the requested service/topic/item
            //

            EstablishLink(szService, szTopic, szItem);

            EndDialog(hDlg, TRUE);
            break;

        case IDCANCEL:
            EndDialog(hDlg, FALSE);
            break;

        default:
            break;
        }
        break;

    default:
        return FALSE; // say we didn't handle it
        break;
    }

    return TRUE; // say we handled it
}

//
// Show the topic list for the currently selected service
//

void ShowTopicList(HWND hDlg)
{
    char szService[128];
    HSZ hszService, hszSystem, hszItem;
    HCONV hConv;
    HDDEDATA hDDEData;
    DWORD dwResult, dwLength, dwIndex;
    BYTE FAR* pData;

    //
    // Reset the current list contents
    //

    SendDlgItemMessage(hDlg, ID_TOPICLIST, CB_RESETCONTENT, 0, 0);
    SendDlgItemMessage(hDlg, ID_ITEMLIST, CB_RESETCONTENT, 0, 0);

    //
    // Get the name of the current service
    //

    szService[0] = '\0';
    SendDlgItemMessage(hDlg,
                       ID_SVRLIST,
                       WM_GETTEXT,
                       (WPARAM) sizeof(szService),
                       (LPARAM) (LPSTR) szService);
    if (!lstrlen(szService)) {
        return;
    }

    //
    // Connect to the server
    //

    hszSystem = DdeCreateStringHandle(dwDDEInst,
                                      SZDDESYS_TOPIC,
                                      CP_WINANSI);

    hszService = DdeCreateStringHandle(dwDDEInst,
                                       szService,
                                       CP_WINANSI);

    hConv = DdeConnect(dwDDEInst,
                       hszService,
                       hszSystem,
                       NULL);

    //
    // Free the HSZs now
    //

    DdeFreeStringHandle(dwDDEInst, hszSystem);
    DdeFreeStringHandle(dwDDEInst, hszService);

    if (!hConv) {
        return;
    }

    //
    // Try to get the topic list in CF_TEXT format
    //

    hszItem = DdeCreateStringHandle(dwDDEInst,
                                    SZDDESYS_ITEM_TOPICS,
                                    CP_WINANSI);

    hDDEData = DdeClientTransaction(NULL,
                                    0,
                                    hConv,
                                    hszItem,
                                    CF_TEXT,
                                    XTYP_REQUEST,
                                    1000, // ms timeout
                                    &dwResult);

    DdeFreeStringHandle(dwDDEInst, hszItem);

    if (hDDEData) {

        //
        // Lock the data so we can parse it
        //

        pData = DdeAccessData(hDDEData, &dwLength);

        //
        // The topics list is tab delimited and has a NULL terminator
        //

        AddItemsToList(hDlg, pData, ID_TOPICLIST);

        //
        // Done with the data
        //

        DdeUnaccessData(hDDEData);
        DdeFreeDataHandle(hDDEData);

        //
        // If we have a current conversation, select the current
        // topic, else don't select anything
        //

        if (hconvCurrent) {

            dwIndex = SendDlgItemMessage(hDlg,
                                         ID_TOPICLIST,
                                         CB_SELECTSTRING,
                                         (WPARAM) 0,
                                         (LPARAM)(LPSTR)szCurrentTopic);
        }
        

        //
        // Show the item list for this service/topic
        //

        ShowItemList(hDlg);

    }

    //
    // Disconnect the conversation
    //

    DdeDisconnect(hConv);

}

//
// Show the item list for the currently selected service/topic
//

void ShowItemList(HWND hDlg)
{
    char szService[128];
    HSZ hszService, hszTopic, hszItem;
    HCONV hConv;
    HDDEDATA hDDEData;
    DWORD dwResult, dwLength, dwIndex;
    BYTE FAR* pData;
    char szTopic[128];

    //
    // Reset the current list contents
    //

    SendDlgItemMessage(hDlg, ID_ITEMLIST, CB_RESETCONTENT, 0, 0);

    //
    // Get the name of the current service
    //

    szService[0] = '\0';
    SendDlgItemMessage(hDlg,
                       ID_SVRLIST,
                       WM_GETTEXT,
                       (WPARAM) sizeof(szService),
                       (LPARAM) (LPSTR) szService);

    if (!lstrlen(szService)) {
        return;
    }

    //
    // Get the name of the current topic
    //

    szTopic[0] = '\0';
    SendDlgItemMessage(hDlg,
                       ID_TOPICLIST,
                       WM_GETTEXT,
                       (WPARAM) sizeof(szTopic),
                       (LPARAM) (LPSTR) szTopic);

    if (!lstrlen(szTopic)) {
        return;
    }

    //
    // Connect to the server
    //

    hszTopic = DdeCreateStringHandle(dwDDEInst,
                                     szTopic,
                                     CP_WINANSI);

    hszService = DdeCreateStringHandle(dwDDEInst,
                                       szService,
                                       CP_WINANSI);

    hConv = DdeConnect(dwDDEInst,
                       hszService,
                       hszTopic,
                       NULL);

    //
    // Free the HSZs now
    //

    DdeFreeStringHandle(dwDDEInst, hszTopic);
    DdeFreeStringHandle(dwDDEInst, hszService);

    if (!hConv) {
        return;
    }

    //
    // Try to get the item list in CF_TEXT format
    // if the topic is 'system' we use SysItems 
    // rather than TopicItemList.
    //

    if (lstrcmpi(szTopic, SZDDESYS_TOPIC) == 0) {

        hszItem = DdeCreateStringHandle(dwDDEInst,
                                        SZDDESYS_ITEM_SYSITEMS,
                                        CP_WINANSI);
    } else {

        hszItem = DdeCreateStringHandle(dwDDEInst,
                                        SZDDE_ITEM_ITEMLIST,
                                        CP_WINANSI);
    }

    hDDEData = DdeClientTransaction(NULL,
                                    0,
                                    hConv,
                                    hszItem,
                                    CF_TEXT,
                                    XTYP_REQUEST,
                                    1000, // ms timeout
                                    &dwResult);

    DdeFreeStringHandle(dwDDEInst, hszItem);

    if (hDDEData) {

        //
        // Lock the data so we can parse it
        //

        pData = DdeAccessData(hDDEData, &dwLength);

        //
        // The list is tab delimited and has a NULL terminator
        //

        AddItemsToList(hDlg, pData, ID_ITEMLIST);

        //
        // Done with the data
        //

        DdeUnaccessData(hDDEData);
        DdeFreeDataHandle(hDDEData);

        //
        // If we have a current conversation, select the current
        // item, else select nothing.
        //

        if (hconvCurrent) {

            dwIndex = SendDlgItemMessage(hDlg,
                                         ID_ITEMLIST,
                                         CB_SELECTSTRING,
                                         (WPARAM) 0,
                                         (LPARAM)(LPSTR)szCurrentItem);
        }

        if (SendDlgItemMessage(hDlg,
                           ID_ITEMLIST,
                           CB_SETCURSEL,
                           (WPARAM) LOWORD(dwIndex),
                           (LPARAM) 0) != CB_ERR) {

            EnableWindow(GetDlgItem(hDlg, IDOK), TRUE);
        }

    }

    //
    // Disconnect the conversation
    //

    DdeDisconnect(hConv);

}

//
// See if an item is a system one.  To make this routine work in
// both the topics list and the items list it contains both the
// system topic and all the system items.
//

static char *szSysItems[] = {
    SZDDESYS_TOPIC,
    SZDDESYS_ITEM_TOPICS, 
    SZDDESYS_ITEM_SYSITEMS,
    SZDDESYS_ITEM_RTNMSG, 
    SZDDESYS_ITEM_STATUS, 
    SZDDESYS_ITEM_FORMATS,
    SZDDESYS_ITEM_HELP,   
    SZDDE_ITEM_ITEMLIST,  
    NULL
    };

BOOL IsSystemItem(LPSTR lpszItem)
{
    char **pp;

    pp = szSysItems;
    while (*pp) {
        if (!lstrcmp(lpszItem, *pp)) {
            return TRUE;
        }
        pp++;
    }
    return FALSE;
}

//
// Add items from a tab delimited list to a listbox
//

void AddItemsToList(HWND hDlg, BYTE FAR *pData, int idList)
{
    char szItem[128];
    LPSTR pItem;

    //
    // BUGBUG walk the string replacing \t with \0 and count them
    // then add the counted words
    //

    lstrcpy(szItem, "");
    pItem = szItem;
    while (*pData) {

        if (*pData == '\t') {
        
            //
            // Add the current topic to the list
            //

            *pItem = '\0';
            if (lstrlen(szItem)) {

                //
                // See if we want system topics and if not
                // check to ensure this isn't one
                //

                if (!IsSystemItem(szItem) || bShowSystemItems) {

                    SendDlgItemMessage(hDlg,
                                       idList,
                                       CB_ADDSTRING,
                                       (WPARAM) 0,
                                       (LPARAM) (LPSTR) szItem);
                }
            }
            pData++;
            pItem = szItem;
            *pItem = '\0';
        } else {
            *pItem++ = *pData++;
        }
    }

    *pItem = '\0';

    //
    // Add the last topic to the list
    //

    if (lstrlen(szItem)) {
        if (!IsSystemItem(szItem) || bShowSystemItems) {
            SendDlgItemMessage(hDlg,
                               idList,
                               CB_ADDSTRING,
                               (WPARAM) 0,
                               (LPARAM) (LPSTR) szItem);
        }
    }
}
