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
    link.c

    Establish a named link

*/

#include "dderecon.h"
#include <string.h>

//
// Global data
//

char szCurrentService[DDENAMESIZE];
char szCurrentTopic[DDENAMESIZE];
char szCurrentItem[DDENAMESIZE];
HCONV hconvCurrent = NULL;

//
// local functions
//

BOOL IsServiceAvailable(LPSTR szService);

//
// Create a link to a named service/topic/item
//

void EstablishLink(LPSTR lpszService, LPSTR lpszTopic, LPSTR lpszItem)
{
    char buf[256];
    HCONV hconvNew;
    HSZ hszService, hszTopic, hszItem;
    DWORD dwResult, dwLength;
    BYTE FAR* pData;
    HDDEDATA hDDEData;
    int i;
    UINT ui;
    BOOL bResult;

    //
    // Establish if the server of our service is currently running
    //

    if (! IsServiceAvailable(lpszService)) {

        //
        // Only ask if not in auto connect mode
        //

        if (!bAutoConnect) {

            //
            //  Ask the user if we want to try to start it
            //

            wsprintf(buf,
                     "The '%s' service is not running.  Do you want "
                     "to start the '%s.EXE' application?",
                     lpszService,
                     _fstrupr(lpszService));

            i = MessageBox(hwndMain,
                           buf,
                           szAppName,
                           MB_ICONQUESTION | MB_YESNO);

            if (i != IDYES) {

                return;

            }
        }

        //
        // Try to run the server.  Note that we assume the server
        // name is the same as the service name with .EXE appended
        // to it.  We also provide the topic name as a command line
        // argument so that the server can open this 'file' if required.
        // We also assume it can be found on the Windows search path.
        //

        wsprintf(buf,
                 "%s.EXE %s", 
                 lpszService,
                 lpszTopic);

        ui = WinExec(buf, SW_SHOWNOACTIVATE);
        if (ui < 32) {
            Error("'%s.EXE' could not be started.  DOS returned error %d", 
                  lpszService,
                  ui);
            return;
        }

        //
        // Bring our window back to the top
        //

        BringWindowToTop(hwndMain);

    }

    //
    // Connect to the server
    //

    hszTopic = DdeCreateStringHandle(dwDDEInst,
                                     lpszTopic,
                                     CP_WINANSI);

    hszService = DdeCreateStringHandle(dwDDEInst,
                                       lpszService,
                                       CP_WINANSI);

    hconvNew = DdeConnect(dwDDEInst,
                          hszService,
                          hszTopic,
                          NULL);

    //
    // Free the HSZs now
    //

    DdeFreeStringHandle(dwDDEInst, hszTopic);
    DdeFreeStringHandle(dwDDEInst, hszService);

    if (!hconvNew) {
        Status("Couldn't connect to: %s|%s", lpszService, lpszTopic);
        return;
    }

    //
    // Try to get the item we are interrested in
    //

    hszItem = DdeCreateStringHandle(dwDDEInst,
                                    lpszItem,
                                    CP_WINANSI);

    hDDEData = DdeClientTransaction(NULL,
                                    0,
                                    hconvNew,
                                    hszItem,
                                    CF_TEXT,
                                    XTYP_REQUEST,
                                    1000, // ms timeout
                                    &dwResult);

    DdeFreeStringHandle(dwDDEInst, hszItem);

    if (hDDEData) {

        //
        // Lock the data so we can access it
        //

        pData = DdeAccessData(hDDEData, &dwLength);

        if (pData) {

            //
            // Just show it
            //

            Status("%s", pData);
        }

        //
        // Done with the data
        //

        DdeUnaccessData(hDDEData);
        DdeFreeDataHandle(hDDEData);

    } else {

        Status("couldn't get any data");
        return;

    }

    //
    // Get rid of any old conversation
    //

    if (hconvCurrent) {

        DdeDisconnect(hconvCurrent);
        
    }

    hconvCurrent = hconvNew;


    //
    // Set up an advise request to get any changes
    //

    hszItem = DdeCreateStringHandle(dwDDEInst,
                                    lpszItem,
                                    CP_WINANSI);

    bResult = (BOOL) LOWORD(DdeClientTransaction(NULL,
                                    0,
                                    hconvNew,
                                    hszItem,
                                    CF_TEXT,
                                    XTYP_ADVSTART,
                                    (DWORD)TIMEOUT_ASYNC,
                                    &dwResult));

    DdeFreeStringHandle(dwDDEInst, hszItem);


    //
    // Show what we're connected to now
    //

    wsprintf(buf, 
             "Service: %s, Topic: %s, Item: %s",
             lpszService,
             lpszTopic,
             lpszItem);
    SetWindowText(hwndLinkInfo, buf);
    
    //
    // Save the global values
    //

    lstrcpy(szCurrentService, lpszService);
    lstrcpy(szCurrentTopic, lpszTopic);
    lstrcpy(szCurrentItem, lpszItem);

    if (!bResult) {

        Status("Failed to set up advise request");
    }
}

//
// See if a DDE service is currently available
// by making a wild conenct request.
//

BOOL IsServiceAvailable(LPSTR lpszService)
{
    HSZ hszService;
    HCONV hConv;

    hszService = DdeCreateStringHandle(dwDDEInst,
                                       lpszService,
                                       CP_WINANSI);

    //
    // Try to connect to any topic
    //

    hConv = DdeConnect(dwDDEInst,
                       hszService,
                       NULL,
                       NULL);

    //
    // Free the HSZs now
    //

    DdeFreeStringHandle(dwDDEInst, hszService);

    if (hConv) {

        DdeDisconnect(hConv);

        return TRUE;
    }

    return FALSE;
}
