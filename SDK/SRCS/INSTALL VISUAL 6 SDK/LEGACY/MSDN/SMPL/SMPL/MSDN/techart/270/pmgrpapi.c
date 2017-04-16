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
    pmgrpapi.c

    DDE Client DLL demonstration

    Another fine Herman Rodent production

    This DLL provides an API to the Program Manager to allow
    the addition and deletion of groups and items.

    It uses the DDE execute facility in ProgMan.  Each call to
    an API here causes a DDE conversation to be set up, the execute
    request made and the conversation terminated.

*/

#include <windows.h>
#include <ddeml.h>
#include <string.h>
#include "pmgrpapi.h"

//
// global data
//

HINSTANCE hInst;

//
// local functions
//

static BOOL SendExecCmd(LPSTR lpszCmd);





//
// Create a group
//

BOOL FAR PASCAL pmCreateGroup(LPSTR lpszGroup, LPSTR lpszPath)
{
    char buf[256];

    if (lpszPath && lstrlen(lpszPath)) {
        wsprintf(buf, 
                 "[CreateGroup(%s,%s)]",
                 lpszGroup,
                 lpszPath);
    } else {
        wsprintf(buf, 
                 "[CreateGroup(%s)]",
                 lpszGroup);
    }

    return SendExecCmd(buf);
}

//
// Delete group
//

BOOL FAR PASCAL pmDeleteGroup(LPSTR lpszGroup)
{
    char buf[256];

    if (lpszGroup && lstrlen(lpszGroup)) {
        wsprintf(buf, 
                 "[DeleteGroup(%s)]",
                 lpszGroup);
    }

    return SendExecCmd(buf);
}

//
// Show a group
//

BOOL FAR PASCAL pmShowGroup(LPSTR lpszGroup, WORD wCmd)
{
    char buf[256];

    if (lpszGroup && lstrlen(lpszGroup)) {
        wsprintf(buf, 
                 "[ShowGroup(%s,%u)]",
                 lpszGroup,
                 wCmd);
    }

    return SendExecCmd(buf);
}

//
// Add a new item to a group
//

BOOL FAR PASCAL pmAddItem(LPSTR lpszCmdLine,
                          LPSTR lpszCaption,
                          LPSTR lpszIconPath,
                          WORD wIconIndex)
{
    char buf[256];

    if (lpszIconPath && lstrlen(lpszIconPath)) {

        wsprintf(buf, 
                 "[AddItem(%s,%s,%s,%u)]",
                 lpszCmdLine,
                 lpszCaption,
                 lpszIconPath,
                 wIconIndex);
    } else {

        wsprintf(buf, 
                 "[AddItem(%s,%s)]",
                 lpszCmdLine,
                 lpszCaption);
    }

    return SendExecCmd(buf);
}

//
// Delete an item from a group
//

BOOL FAR PASCAL pmDeleteItem(LPSTR lpszItem)
{
    char buf[256];

    if (lpszItem && lstrlen(lpszItem)) {
        wsprintf(buf, 
                 "[DeleteItem(%s)]",
                 lpszItem);
    }

    return SendExecCmd(buf);
}

//
// Delete an item and remember its place to it can
// be replaced by a subsequent call to pmAddItem
//

BOOL FAR PASCAL pmReplaceItem(LPSTR lpszItem)
{
    char buf[256];

    if (lpszItem && lstrlen(lpszItem)) {
        wsprintf(buf, 
                 "[ReplaceItem(%s)]",
                 lpszItem);
    }

    return SendExecCmd(buf);
}

//
// Reload a Program Manager group
//

BOOL FAR PASCAL pmReload(LPSTR lpszGroup)
{
    char buf[256];

    if (lpszGroup && lstrlen(lpszGroup)) {
        wsprintf(buf, 
                 "[ReloadGroup(%s)]",
                 lpszGroup);
    }

    return SendExecCmd(buf);
}

//
// Exit the Program Manager
//

BOOL FAR PASCAL pmExit(BOOL bSaveGroups)
{
    char buf[256];

    wsprintf(buf, 
             "[ExitProgman(%u)]",
             bSaveGroups ? 1 : 0);

    return SendExecCmd(buf);
}

//
// Entry point called from libentry.asm when the 
// DLL is first loaded
//

BOOL FAR PASCAL LibMain(HINSTANCE hInstance, WORD wDataSeg, WORD cbHeap)
{
    hInst = hInstance;        // save our module handle
    return TRUE;
}    

//
// Define the WEP entry point for Windows to call when the DLL
// is about to be unloaded.
//

void FAR PASCAL WEP(WORD wGarbage)
{
    //
    // Do absolutely nothing at all here, since    
    // that's all that is safe to do.
    //
}

//
// Callback function for DDE messages
//

HDDEDATA CALLBACK DDECallback(UINT wType, 
                              UINT wFmt, 
                              HCONV hConv,
                              HSZ hsz1, 
                              HSZ hsz2, 
                              HDDEDATA hDDEData, 
                              DWORD dwData1, 
                              DWORD dwData2)
{
    switch (wType) {

    default:
        return NULL;
        break;
    }
}

//
// Send an execute request to the Program Manager
//

static BOOL SendExecCmd(LPSTR lpszCmd)
{
    DWORD dwDDEInst = 0;
    UINT ui;
    HSZ hszProgman;
    HCONV hConv;
    HDDEDATA hExecData;

    //				   
    // Initialize DDEML
    //

    ui = DdeInitialize(&dwDDEInst,
                       DDECallback,
                       CBF_FAIL_ALLSVRXACTIONS,
                       0l);

    if (ui != DMLERR_NO_ERROR) {
        return FALSE;
    }

    //
    // Initiate a conversation the the PROGMAN service
    // on the PROGMAN topic.
    //

    hszProgman = DdeCreateStringHandle(dwDDEInst,
                                       "PROGMAN",
                                       CP_WINANSI);

    hConv = DdeConnect(dwDDEInst,
                       hszProgman,
                       hszProgman,
                       NULL);

    //
    // Free the HSZ now
    //

    DdeFreeStringHandle(dwDDEInst, hszProgman);

    if (!hConv) {
        return FALSE;
    }

    //
    // Create a data handle for the exec string
    //

    hExecData = DdeCreateDataHandle(dwDDEInst,
                                    lpszCmd,
                                    lstrlen(lpszCmd)+1,
                                    0,
                                    NULL,
                                    0,
                                    0);

    //
    // Send the execute request
    //

    DdeClientTransaction((void FAR *)hExecData,
                         (DWORD)-1,
                         hConv,
                         NULL,
                         0,
                         XTYP_EXECUTE,
                         1000, // ms timeout
                         NULL);

    //
    // Done with the conversation now.
    //

    DdeDisconnect(hConv);

    //
    // Done with DDEML
    //

    DdeUninitialize(dwDDEInst);

    return TRUE;
}
