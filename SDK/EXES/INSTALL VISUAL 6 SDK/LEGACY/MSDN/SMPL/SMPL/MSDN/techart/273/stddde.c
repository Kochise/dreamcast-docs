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
    stddde.c

    This module implements basic DDE support for an application.
    It supports the system topic and allows topics and items to
    be dynamically added and removed while the application is running.
    It only supports CF_TEXT for system items.

    It assumes that there is only one service provided and that
    the server is never too busy to process a command.

    All objects created by this module are created using _calloc
    which allows efficient use of global memory and zero initializes
    each one.

*/

#include <windows.h>
#include "stddde.h"
#include <malloc.h>
#include <string.h>

//
// Local constants
//

#define MAXFORMATS  128     // max no of CF formats we will list

//
// Local data 
//

static DDESERVERINFO ServerInfo;

//
// Format lists
//

static WORD SysFormatList[] = {
    CF_TEXT,
    NULL};

//
// Standard format name lookup table
//

CFTAGNAME CFNames[] = {
    CF_TEXT,        SZCF_TEXT,       
    CF_BITMAP,      SZCF_BITMAP,     
    CF_METAFILEPICT,SZCF_METAFILEPICT,
    CF_SYLK,        SZCF_SYLK,       
    CF_DIF,         SZCF_DIF,        
    CF_TIFF,        SZCF_TIFF,       
    CF_OEMTEXT,     SZCF_OEMTEXT,    
    CF_DIB,         SZCF_DIB,        
    CF_PALETTE,     SZCF_PALETTE,    
    CF_PENDATA,     SZCF_PENDATA,    
    CF_RIFF,        SZCF_RIFF,       
    CF_WAVE,        SZCF_WAVE,       
    NULL,           NULL
    };

//
// Local functions
//

HDDEDATA SysReqTopics(UINT wFmt, HSZ hszTopic, HSZ hszItem);
HDDEDATA SysReqItems(UINT wFmt, HSZ hszTopic, HSZ hszItem);
HDDEDATA SysReqFormats(UINT wFmt, HSZ hszTopic, HSZ hszItem);
HDDEDATA TopicReqFormats(UINT wFmt, HSZ hszTopic, HSZ hszItem);
HDDEDATA FAR PASCAL __export StdDDECallback(WORD wType,
                                 WORD wFmt,
                                 HCONV hConv,
                                 HSZ hsz1,
                                 HSZ hsz2,
                                 HDDEDATA hData,
                                 DWORD dwData1,
                                 DWORD dwData2);
HDDEDATA DoWildConnect(HSZ hszTopic);
BOOL DoCallback(WORD wType,
                WORD wFmt,
                HCONV hConv,
                HSZ hsz1,
                HSZ hsz2,
                HDDEDATA hData,
                HDDEDATA *phReturnData);
HDDEDATA MakeDataFromFormatList(LPWORD pFmt, WORD wFmt, HSZ hszItem);
void AddFormatsToList(LPWORD pMain, int iMax, LPWORD pList);
static BOOL AddConversation(HCONV hConv, HSZ hszTopic);
static BOOL RemoveConversation(HCONV hConv, HSZ hszTopic);
static PDDECONVINFO FindConversation(HSZ hszTopic);

//
// Initialize all the DDE lists for this server and 
// initialize DDEML.
//

BOOL InitializeDDE(HANDLE hInstance,
                   LPSTR lpszServiceName,
                   LPDWORD lpdwDDEInst,
                   PFNCALLBACK lpfnCustomCallback,
                   DWORD dwFilterFlags)
{
    UINT uiResult;

    //
    // Make a proc instance for the standard callback
    //

    ServerInfo.pfnStdCallback = 
                (PFNCALLBACK) MakeProcInstance((FARPROC) StdDDECallback,
                                               hInstance);

    //
    // Make sure the application hasn't requested any filter options 
    // which will prevent us from working correctly.
    //

    dwFilterFlags &= !( CBF_FAIL_CONNECTIONS 
                      | CBF_SKIP_CONNECT_CONFIRMS
                      | CBF_SKIP_DISCONNECTS);

    //
    // Initialize DDEML.  Note that DDEML doesn't make any callbacks
    // during initialization so we don't need to worry about the
    // custom callback yet.
    //

    uiResult = DdeInitialize(&ServerInfo.dwDDEInstance,
                             ServerInfo.pfnStdCallback,
                             dwFilterFlags,
                             0);

    if (uiResult != DMLERR_NO_ERROR) return FALSE;

    //
    // make a proc instance for the custom callback if there is one
    //

    if (lpfnCustomCallback) {

        ServerInfo.pfnCustomCallback = 
                (PFNCALLBACK) MakeProcInstance((FARPROC) lpfnCustomCallback,
                                               hInstance);
    }

    //
    // Return the DDE instance id if it was requested
    //

    if (lpdwDDEInst) {

        *lpdwDDEInst = ServerInfo.dwDDEInstance;
    }

    //
    // Copy the service name and create a DDE name handle for it
    //

    ServerInfo.lpszServiceName = lpszServiceName;
    ServerInfo.hszServiceName = DdeCreateStringHandle(ServerInfo.dwDDEInstance,
                                                      lpszServiceName,
                                                      CP_WINANSI);

    //
    // Add all the system topic items to the service tree
    //

    AddDDEItem(SZDDESYS_TOPIC,
               SZDDESYS_ITEM_TOPICS,
               SysFormatList,
               SysReqTopics,
               NULL);

    AddDDEItem(SZDDESYS_TOPIC,
               SZDDESYS_ITEM_SYSITEMS,
               SysFormatList,
               SysReqItems,
               NULL);

    AddDDEItem(SZDDESYS_TOPIC,
               SZDDE_ITEM_ITEMLIST,
               SysFormatList,
               SysReqItems,
               NULL);

    AddDDEItem(SZDDESYS_TOPIC,
               SZDDESYS_ITEM_FORMATS,
               SysFormatList,
               SysReqFormats,
               NULL);


    //
    // Register the name of our service
    //

    DdeNameService(ServerInfo.dwDDEInstance, 
                   ServerInfo.hszServiceName,
                   NULL,
                   DNS_REGISTER);

    return TRUE;
}

//
// Tidy up and close down DDEML
//

void UninitializeDDE(void)
{
    PDDETOPICINFO pTopic;
    PDDEITEMINFO pItem;

    //
    // Unregister the service name
    //

    DdeNameService(ServerInfo.dwDDEInstance, 
                   ServerInfo.hszServiceName,
                   NULL,
                   DNS_UNREGISTER);

    //
    // free the name handle
    //

    DdeFreeStringHandle(ServerInfo.dwDDEInstance, ServerInfo.hszServiceName);

    //
    // Walk the server topic tree, freeing all the other string handles
    //

    pTopic = ServerInfo.pTopicList;
    while (pTopic) {

        DdeFreeStringHandle(ServerInfo.dwDDEInstance, pTopic->hszTopicName);
        pTopic->hszTopicName = NULL;

        //
        // Free any item handles it owns
        //

        pItem = pTopic->pItemList;
        while (pItem) {

            DdeFreeStringHandle(ServerInfo.dwDDEInstance, pItem->hszItemName);
            pItem->hszItemName = NULL;

            pItem = pItem->pNext;
        }

        pTopic = pTopic->pNext;
    }

    //
    // Release DDEML
    //

    DdeUninitialize(ServerInfo.dwDDEInstance);
    ServerInfo.dwDDEInstance = NULL;

    //
    // Free any proc instances we created
    //

    if (ServerInfo.pfnCustomCallback) {
        FreeProcInstance((FARPROC)ServerInfo.pfnCustomCallback);
        ServerInfo.pfnCustomCallback = NULL;
    }

    FreeProcInstance((FARPROC)ServerInfo.pfnStdCallback);
    ServerInfo.pfnStdCallback = NULL;

}

//
// Find a topic by its name
//

PDDETOPICINFO FindTopicFromName(LPSTR lpszName)
{
    PDDETOPICINFO pTopic;

    pTopic = ServerInfo.pTopicList;
    while (pTopic) {

        if (lstrcmpi(pTopic->pszTopicName, lpszName) == 0) {
            break;
        }

        pTopic = pTopic->pNext;
    }

    return pTopic;
}

//
// Find a topic by its HSZ
//

PDDETOPICINFO FindTopicFromHsz(HSZ hszName)
{
    PDDETOPICINFO pTopic;

    pTopic = ServerInfo.pTopicList;
    while (pTopic) {

        if (DdeCmpStringHandles(pTopic->hszTopicName, hszName) == 0) {
            break;
        }

        pTopic = pTopic->pNext;
    }

    return pTopic;
}

//
// Find an item by its name in a topic 
//

PDDEITEMINFO FindItemFromName(PDDETOPICINFO pTopic, LPSTR lpszItem)
{
    PDDEITEMINFO pItem;

    pItem = pTopic->pItemList;
    while (pItem) {

        if (lstrcmpi(pItem->pszItemName, lpszItem) == 0) {
            break;
        }

        pItem = pItem->pNext;
    }

    return pItem;
}

//
// Find an item by its HSZ in a topic 
//

PDDEITEMINFO FindItemFromHsz(PDDETOPICINFO pTopic, HSZ hszItem)
{
    PDDEITEMINFO pItem;

    pItem = pTopic->pItemList;
    while (pItem) {

        if (DdeCmpStringHandles(pItem->hszItemName, hszItem) == 0) {
            break;
        }

        pItem = pItem->pNext;
    }

    return pItem;
}

//
// Add a new topic and default processing for its item list and formats
//

PDDETOPICINFO AddDDETopic(LPSTR lpszTopic,
                          PDDEEXECFN pfnExec,
                          PDDEREQUESTFN pfnRequest,
                          PDDEPOKEFN pfnPoke)   
{
    PDDETOPICINFO pTopic;

    //
    // See if we already have this topic
    //

    pTopic = FindTopicFromName(lpszTopic);

    if (pTopic) {

        //
        // We already have this one so just update its info
        //

        pTopic->pfnExec = pfnExec;
        pTopic->pfnRequest = pfnRequest;
        pTopic->pfnPoke = pfnPoke;

    } else {

        //
        // Create a new topic
        //

        pTopic = _fcalloc(1, sizeof(DDETOPICINFO));
        if (!pTopic) return NULL;

        //
        // Fill out the info
        //

        pTopic->pszTopicName = lpszTopic;
        pTopic->hszTopicName = DdeCreateStringHandle(ServerInfo.dwDDEInstance,
                                                    lpszTopic,
                                                    CP_WINANSI);
        pTopic->pItemList = NULL;
        pTopic->pfnExec = pfnExec;
        pTopic->pfnRequest = pfnRequest;
        pTopic->pfnPoke = pfnPoke;

        //
        // Add it to the list
        //

        pTopic->pNext = ServerInfo.pTopicList;
        ServerInfo.pTopicList = pTopic;

        //
        // Add handlers for its item list and formats.
        //

        AddDDEItem(lpszTopic,
                   SZDDE_ITEM_ITEMLIST,
                   SysFormatList,
                   SysReqItems,
                   NULL);

        AddDDEItem(lpszTopic,
                   SZDDESYS_ITEM_FORMATS,
                   SysFormatList,
                   TopicReqFormats,
                   NULL);

    }

    return pTopic;
}

//
// Remove a topic and all its items.  If there is an active
// conversation on the topic then disconnect it.
//

BOOL RemoveDDETopic(LPSTR lpszTopic)
{
    PDDETOPICINFO pTopic, pPrevTopic;
    PDDECONVINFO pCI;

    //
    // See if we have this topic by walking the list
    //

    pPrevTopic = NULL;
    pTopic = ServerInfo.pTopicList;
    while (pTopic) {

        if (lstrcmpi(pTopic->pszTopicName, lpszTopic) == 0) {

            //
            // Found it. Disconnect any active conversations on this topic
            //

            while (pCI = FindConversation(pTopic->hszTopicName)) {

                //
                // Tell DDEML to disconnect it
                //

                DdeDisconnect(pCI->hConv);

                //
                // We don't get notified until later that it's gone
                // so remove it from the list now so we won't keep
                // finding it in this loop.
                // When DDEML sends the disconnect notification later
                // it won't be there to remove but that doesn't matter.
                //

                RemoveConversation(pCI->hConv, pCI->hszTopicName);

            }

            //
            // Free all the items in the topic
            //
        
            while(pTopic->pItemList) {
        
                if (!RemoveDDEItem(lpszTopic, 
                                   pTopic->pItemList->pszItemName)) {
                    return FALSE; // some error
                }    
            }
        
            //
            // Unlink it from the list.
            //

            if (pPrevTopic) {

                pPrevTopic->pNext = pTopic->pNext;

            } else {

                ServerInfo.pTopicList = pTopic->pNext;

            }

            //
            // Release its string handle
            //
        
            DdeFreeStringHandle(ServerInfo.dwDDEInstance,
                                pTopic->hszTopicName);
        
            //
            // Free the memory associated with it
            //
        
            _ffree(pTopic);
        
            return TRUE;

        }

        pTopic = pTopic->pNext;
    }

    //
    // We don't have this topic
    //

    return FALSE;
}

//
// Add a new item.
//

PDDEITEMINFO AddDDEItem(LPSTR lpszTopic, 
                        LPSTR lpszItem, 
                        LPWORD lpFormatList,
                        PDDEREQUESTFN lpReqFn, 
                        PDDEPOKEFN lpPokeFn)
{
    PDDEITEMINFO pItem = NULL;
    PDDETOPICINFO pTopic;

    //
    // See if we have this topic already
    //

    pTopic = FindTopicFromName(lpszTopic);

    if (!pTopic) {

        //
        // We need to add this as a new topic
        //

        pTopic = AddDDETopic(lpszTopic,
                             NULL,
                             NULL,
                             NULL);
    }

    if (!pTopic) return NULL;  // failed

    //
    // See if we already have this item
    //

    pItem = FindItemFromName(pTopic, lpszItem);

    if (pItem) {

        //
        // Just update the info in it
        //

        pItem->pfnRequest = lpReqFn;
        pItem->pfnPoke = lpPokeFn;
        pItem->pFormatList = lpFormatList;

    } else {

        //
        // Create a new item
        //

        pItem = _fcalloc(1, sizeof(DDEITEMINFO));
        if (!pItem) return NULL;

        //
        // Fill out the info
        //

        pItem->pszItemName = lpszItem;
        pItem->hszItemName = DdeCreateStringHandle(ServerInfo.dwDDEInstance,
                                                   lpszItem,
                                                   CP_WINANSI);
        pItem->pTopic = pTopic;
        pItem->pfnRequest = lpReqFn;
        pItem->pfnPoke = lpPokeFn;
        pItem->pFormatList = lpFormatList;

        //
        // Add it to the existing item list for this topic
        //

        pItem->pNext = pTopic->pItemList;
        pTopic->pItemList = pItem;

    }

    return pItem;
}

//
// Remove an item from a topic.
//

BOOL RemoveDDEItem(LPSTR lpszTopic, LPSTR lpszItem)
{
    PDDETOPICINFO pTopic;
    PDDEITEMINFO pItem, pPrevItem;

    //
    // See if we have this topic
    //

    pTopic = FindTopicFromName(lpszTopic);

    if (!pTopic) {
        return FALSE;
    }

    //
    // Walk the topic item list looking for this item.
    //

    pPrevItem = NULL;
    pItem = pTopic->pItemList;
    while (pItem) {

        if (lstrcmpi(pItem->pszItemName, lpszItem) == 0) {

            //
            // Found it.  Unlink it from the list.
            //

            if (pPrevItem) {

                pPrevItem->pNext = pItem->pNext;

            } else {

                pTopic->pItemList = pItem->pNext;

            }

            //
            // Release its string handle
            //

            DdeFreeStringHandle(ServerInfo.dwDDEInstance,
                                pItem->hszItemName);

            //
            // Free the memory associated with it
            //

            _ffree(pItem);

            return TRUE;
        }

        pPrevItem = pItem;
        pItem = pItem->pNext;
    }

    //
    // We don't have that one
    //

    return FALSE;
}

//
// Get the text name of a Clipboard format from its id
//

LPSTR GetCFNameFromId(WORD wFmt, LPSTR lpBuf, int iSize)
{
    PCFTAGNAME pCTN;

    //
    // Try for a standard one first
    //

    pCTN = CFNames;
    while (pCTN->wFmt) {
        if (pCTN->wFmt == wFmt) {
            _fstrncpy(lpBuf, pCTN->pszName, iSize);
            return lpBuf;
        }
        pCTN++;
    }

    //
    // See if it's a registered one
    //

    if (GetClipboardFormatName(wFmt, lpBuf, iSize) == 0) {

        //
        // Nope.  It's unknown
        //

        *lpBuf = '\0';
    }

    return lpBuf;
}

//
// Post an advise request about an item
//

void PostDDEAdvise(PDDEITEMINFO pItemInfo)
{
    if (pItemInfo && pItemInfo->pTopic) {
        DdePostAdvise(ServerInfo.dwDDEInstance,
                      pItemInfo->pTopic->hszTopicName,
                      pItemInfo->hszItemName);
    }
}

//
// DDE callback function called from DDEML
//

HDDEDATA FAR PASCAL __export StdDDECallback(WORD wType,
                                 WORD wFmt,
                                 HCONV hConv,
                                 HSZ hsz1,
                                 HSZ hsz2,
                                 HDDEDATA hData,
                                 DWORD dwData1,
                                 DWORD dwData2)
{
    HDDEDATA hDdeData = NULL;

    switch (wType) {
    case XTYP_CONNECT_CONFIRM:

        //
        // Add a new conversation to the list
        //

        AddConversation(hConv, hsz1);
        break;

    case XTYP_DISCONNECT:

        //
        // Remove a conversation from the list
        //

        RemoveConversation(hConv, hsz1);
        break;

    case XTYP_WILDCONNECT:

        //
        // We only support wild connects to either a NULL service
        // name or to the name of our own service.
        //

        if ((hsz2 == NULL)
        || !DdeCmpStringHandles(hsz2, ServerInfo.hszServiceName)) {

            return DoWildConnect(hsz1);

        }
        break;

        //
        // For all other messages we see if we want them here
        // and if not, they get passed on to the user callback
        // if one is defined.
        //

    case XTYP_ADVSTART:
    case XTYP_CONNECT:
    case XTYP_EXECUTE:
    case XTYP_REQUEST:
    case XTYP_ADVREQ:
    case XTYP_ADVDATA:
    case XTYP_POKE:

        //
        // Try and process them here first.
        //

        if (DoCallback(wType,
                       wFmt,
                       hConv,
                       hsz1,
                       hsz2,
                       hData,
                       &hDdeData)) {

            return hDdeData;
        }

        //
        // Fall Through to allow the custom callback a chance
        //

    default:

        if (ServerInfo.pfnCustomCallback != NULL) {

            return(ServerInfo.pfnCustomCallback(wType,  
                                                wFmt, 
                                                hConv, 
                                                hsz1, 
                                                hsz2, 
                                                hData,
                                                dwData1, 
                                                dwData2));
        }
    }

    return (HDDEDATA) NULL;
}

//
// Process a generic callback
//

BOOL DoCallback(WORD wType,
                WORD wFmt,
                HCONV hConv,
                HSZ hszTopic,
                HSZ hszItem,
                HDDEDATA hData,
                HDDEDATA *phReturnData)
{
    PDDETOPICINFO pTopic;
    PDDEITEMINFO pItem;
    LPWORD pFormat;
    PDDEPOKEFN pfnPoke;
    CONVINFO ci;
    PDDEREQUESTFN pfnRequest;


    //
    // See if we know the topic
    //

    pTopic = FindTopicFromHsz(hszTopic);
    if (!pTopic) {

        return FALSE;

    }

    //
    // See if this is an execute request for the topic
    //

    if (wType == XTYP_EXECUTE) {

        //
        // See if the user supplied a function to handle this
        //

        if (pTopic->pfnExec) {

            //
            // Call the exec function to process it
            //

            if ((*pTopic->pfnExec)(wFmt, hszTopic, hData)) {

                *phReturnData = (HDDEDATA) DDE_FACK;
                return TRUE;

            }

        }

        //
        // Either no function or it didn't get handled by the function
        //

        *phReturnData = (HDDEDATA) DDE_FNOTPROCESSED;
        return TRUE;
    }

    //
    // See if this is a connect request. Accept it if it is.
    //

    if (wType == XTYP_CONNECT) {

        *phReturnData = (HDDEDATA) TRUE;
        return TRUE;
    }

    //
    // For any other transaction we need to be sure this is an
    // item we support and in some cases, that the format requested
    // is supported for that item.
    //

    pItem = FindItemFromHsz(pTopic, hszItem);
    if (!pItem) {

        //
        // Not an item we support
        //

        return FALSE;
    }

    //
    // See f this is a supported format
    //

    pFormat = pItem->pFormatList;
    while (*pFormat) {

        if (*pFormat == wFmt) break;
        pFormat++;
    }

    if (! *pFormat) return FALSE; // not one we support

    //
    // Now just do whatever is required for each specific transaction
    //

    switch (wType) {
    case XTYP_ADVSTART:

        //
        // Start an advise request.  Topic/item and format are ok.
        //

        *phReturnData = (HDDEDATA) TRUE;
        break;

    case XTYP_ADVDATA:

        //
        // Some data for us. See if we have a poke function for 
        // this item or for this topic in general.
        //

        *phReturnData = (HDDEDATA) DDE_FNOTPROCESSED;
        pfnPoke = pItem->pfnPoke;
        if (!pfnPoke) pfnPoke = pTopic->pfnPoke;
        if (pfnPoke) {

            if ((*pfnPoke)(wFmt, hszTopic, hszItem, hData)) {

                //
                // Data at the server has changed.  See if we
                // did this ourself (from a poke) or if it's from
                // someone else.  If it came from elsewhere then post
                // an advise notice of the change.
                //

                ci.cb = sizeof(CONVINFO);
                if (DdeQueryConvInfo(hConv, (DWORD)QID_SYNC, &ci)) {

                    if (! (ci.wStatus & ST_ISSELF)) {

                        //
                        // It didn't come from us
                        //

                        DdePostAdvise(ServerInfo.dwDDEInstance,
                                      hszTopic,
                                      hszItem);
                    }
                }

                *phReturnData = (HDDEDATA) DDE_FACK; // say we took it

            }
        }
        break;

    case XTYP_POKE:

        //
        // Make sure we're not trying to poke ourself and just
        // post an advise so we'll get it as and ADVDATA transaction
        // a bit later.
        //

        *phReturnData = (HDDEDATA) DDE_FNOTPROCESSED; 
        ci.cb = sizeof (CONVINFO);
        if (DdeQueryConvInfo(hConv, (DWORD)QID_SYNC, &ci)) {

            if (!(ci.wStatus & ST_ISSELF)) {

                //
                // Not trying to poke ourself in the foot so
                // send the advise notice
                //

                DdePostAdvise(ServerInfo.dwDDEInstance,
                              hszTopic,
                              hszItem);
                *phReturnData = (HDDEDATA) DDE_FACK; // say we took it
            }
        }
        break;

    case XTYP_ADVREQ:
    case XTYP_REQUEST:

        //
        // Attempt to start an advise or get the data on a topic/item
        // See if we have a request function for this item or
        // a generic one for the topic
        //

        pfnRequest = pItem->pfnRequest;
        if (!pfnRequest) pfnRequest = pTopic->pfnRequest;
        if (pfnRequest) {

            *phReturnData = (*pfnRequest)(wFmt, hszTopic, hszItem);

        } else {

            *phReturnData = (HDDEDATA) NULL;

        }
        break;

    default:
        break;
    }

    //
    // Say we processed the transaction in some way
    //

    return TRUE;

}

//
// Return the current topics list
//

HDDEDATA SysReqTopics(UINT wFmt, HSZ hszTopic, HSZ hszItem)
{
    HDDEDATA hData;
    PDDETOPICINFO pTopic;
    int cb, cbOffset;

    //
    // Create an empty data object to fill
    //

    hData = DdeCreateDataHandle(ServerInfo.dwDDEInstance,
                                NULL,
                                0,
                                0,
                                hszItem,
                                wFmt,
                                0);
    pTopic = ServerInfo.pTopicList;
    cbOffset = 0;
    while (pTopic) {

        //
        // put in a tab delimiter unless this is the first item
        //

        if (cbOffset != 0) {
            DdeAddData(hData, SZ_TAB, lstrlen(SZ_TAB), cbOffset);
            cbOffset += lstrlen(SZ_TAB);
        }

        //
        // Copy the string name of the topic
        //

        cb = lstrlen(pTopic->pszTopicName);
        DdeAddData(hData, pTopic->pszTopicName, cb, cbOffset);
        cbOffset += cb;

        pTopic = pTopic->pNext;

    }

    //
    // Put a NULL on the end
    //

    DdeAddData(hData, "", 1, cbOffset);

    return hData;
}

//
// Return the system item list
//

HDDEDATA SysReqItems(UINT wFmt, HSZ hszTopic, HSZ hszItem)
{
    HDDEDATA hData;
    PDDETOPICINFO pTopic;
    PDDEITEMINFO pItem;
    int cb, cbOffset;

    //
    // Find the system topic
    //

    pTopic = FindTopicFromHsz(hszTopic);
    if (!pTopic) return NULL;

    //
    // Create an empty data object to fill
    //

    hData = DdeCreateDataHandle(ServerInfo.dwDDEInstance,
                                NULL,
                                0,
                                0,
                                hszItem,
                                wFmt,
                                0);

    //
    // Walk the item list
    //

    cbOffset = 0;
    pItem = pTopic->pItemList;
    while (pItem) {

        //
        // put in a tab delimiter unless this is the first item
        //

        if (cbOffset != 0) {
            DdeAddData(hData, SZ_TAB, lstrlen(SZ_TAB), cbOffset);
            cbOffset += lstrlen(SZ_TAB);
        }

        //
        // Copy the string name of the item
        //

        cb = lstrlen(pItem->pszItemName);
        DdeAddData(hData, pItem->pszItemName, cb, cbOffset);
        cbOffset += cb;

        pItem = pItem->pNext;

    }

    //
    // Put a NULL on the end
    //

    DdeAddData(hData, "", 1, cbOffset);

    return hData;
}

//
// Return the system formats list which is the union of
// all formats supported.
//

HDDEDATA SysReqFormats(UINT wFmt, HSZ hszTopic, HSZ hszItem)
{
    HDDEDATA hData;
    PDDETOPICINFO pTopic;
    PDDEITEMINFO pItem;
    WORD wFormats[MAXFORMATS];

    wFormats[0] = NULL; // start with an empty list

    //
    // Create an empty data object to fill
    //

    hData = DdeCreateDataHandle(ServerInfo.dwDDEInstance,
                                NULL,
                                0,
                                0,
                                hszItem,
                                wFmt,
                                0);

    //
    // Walk the topic list
    //

    pTopic = ServerInfo.pTopicList;
    while (pTopic) {

        //
        // Walk the item list for this topic
        //
    
        pItem = pTopic->pItemList;
        while (pItem) {
    
            //
            // Walk the formats list for this item
            // adding each one to the main list if unique
            //
    
            AddFormatsToList(wFormats, MAXFORMATS, pItem->pFormatList);
    
            pItem = pItem->pNext;
        }

        pTopic = pTopic->pNext;
    }

    //
    // Walk the table and build the text form
    //

    return MakeDataFromFormatList(wFormats, wFmt, hszItem);

}

//
// Return a topic formats list. This is the union of all
// the formats supported by this topic.
//

HDDEDATA TopicReqFormats(UINT wFmt, HSZ hszTopic, HSZ hszItem)
{
    HDDEDATA hData;
    PDDETOPICINFO pTopic;
    PDDEITEMINFO pItem;
    WORD wFormats[MAXFORMATS];

    //
    // Find the topic info
    //

    pTopic = FindTopicFromHsz(hszTopic);
    if (!pTopic) return NULL;

    wFormats[0] = NULL; // start with an empty list

    //
    // Create an empty data object to fill
    //

    hData = DdeCreateDataHandle(ServerInfo.dwDDEInstance,
                                NULL,
                                0,
                                0,
                                hszItem,
                                wFmt,
                                0);

    //
    // Walk the item list for this topic
    //

    pItem = pTopic->pItemList;
    while (pItem) {

        //
        // Walk the formats list for this item
        // adding each one to the main list if unique
        //

        AddFormatsToList(wFormats, MAXFORMATS, pItem->pFormatList);

        pItem = pItem->pNext;
    }

    //
    // Walk the table and build the text form
    //

    return MakeDataFromFormatList(wFormats, wFmt, hszItem);

}

//
// Process a wild connect request.
// Since we only support one service, this is much simpler.  
// If hszTopic is NULL we supply a list of all the topics we
// currently support.  If it's not NULL, we supply a list
// of topics (zero or one items) which match the requested topic.
// The list is terminated by a NULL entry.
//

HDDEDATA DoWildConnect(HSZ hszTopic)
{
    PDDETOPICINFO pTopic;
    int iTopics = 0;
    HDDEDATA hData;
    PHSZPAIR pHszPair;

    //
    // See how many topics we will be returning
    //

    if (hszTopic == NULL) {

        //
        // Count all the topics we have
        //

        pTopic = ServerInfo.pTopicList;
        while (pTopic) {
            iTopics++;
            pTopic = pTopic->pNext;
        }

    } else {

        //
        // See if we have this topic in our list
        //

        pTopic = ServerInfo.pTopicList;
        while (pTopic) {
            if (DdeCmpStringHandles(pTopic->hszTopicName, hszTopic) == 0) {
                iTopics++;
                break;
            }
            pTopic = pTopic->pNext;
        }
    }

    //
    // If we have no match or no topics at all, just return
    // NULL now to refuse the connect
    //

    if (!iTopics) return (HDDEDATA) NULL;

    //
    // Allocate a chunk of DDE data big enough for all the HSZPAIRS
    // we'll be sending back plus space for a NULL entry on the end
    //

    hData = DdeCreateDataHandle(ServerInfo.dwDDEInstance,
                                NULL,
                                (iTopics + 1) * sizeof(HSZPAIR),
                                0,
                                NULL,
                                0,
                                0);

    //
    // Check we actually got it.
    //

    if (!hData) return (HDDEDATA) NULL;

    pHszPair = (PHSZPAIR) DdeAccessData(hData, NULL);

    //
    // Copy the topic data
    //

    if (hszTopic == NULL) {

        //
        // Copy all the topics we have (includes the system topic)
        //

        pTopic = ServerInfo.pTopicList;
        while (pTopic) {

            pHszPair->hszSvc = ServerInfo.hszServiceName;
            pHszPair->hszTopic = pTopic->hszTopicName;

            pHszPair++;
            pTopic = pTopic->pNext;
        }

    } else {

        //
        // Just copy the one topic asked for
        //

        pHszPair->hszSvc = ServerInfo.hszServiceName;
        pHszPair->hszTopic = hszTopic;

        pHszPair++;

    }

    //
    // Put the terminator on the end
    //

    pHszPair->hszSvc = NULL;
    pHszPair->hszTopic = NULL;

    //
    // Finished with the data block
    //

    DdeUnaccessData(hData);

    //
    // Return the block handle
    //

    return hData;
}

HDDEDATA MakeDataFromFormatList(LPWORD pFmt, WORD wFmt, HSZ hszItem)
{
    HDDEDATA hData;
    int cbOffset, cb;
    char buf[256];

    //
    // Create an empty data object to fill
    //

    hData = DdeCreateDataHandle(ServerInfo.dwDDEInstance,
                                NULL,
                                0,
                                0,
                                hszItem,
                                wFmt,
                                0);

    //
    // Walk the format list
    //

    cbOffset = 0;
    while (*pFmt) {

        //
        // put in a tab delimiter unless this is the first item
        //

        if (cbOffset != 0) {
            DdeAddData(hData, SZ_TAB, lstrlen(SZ_TAB), cbOffset);
            cbOffset += lstrlen(SZ_TAB);
        }

        //
        // Copy the string name of the format
        //

        GetCFNameFromId(*pFmt, buf, sizeof(buf));
        cb = lstrlen(buf);
        DdeAddData(hData, buf, cb, cbOffset);
        cbOffset += cb;

        pFmt++;

    }

    //
    // Put a NULL on the end
    //

    DdeAddData(hData, "", 1, cbOffset);

    return hData;
}

//
// Add a list of formats to main list ensuring that each item
// only exists in the list once.
//

void AddFormatsToList(LPWORD pMain, int iMax, LPWORD pList)
{
    LPWORD pFmt, pLast;
    int iCount;

    if (!pMain || !pList) return;

    //
    // Count what we have to start with
    //

    iCount = 0;
    pLast = pMain;
    while (*pLast) {
        pLast++;
        iCount++;
    }

    //
    // Walk the new list ensuring we don't add the item if there
    // isn't room or we have it already.
    //

    while ((iCount < iMax) && *pList) {

        //
        // See if we have this one
        //

        pFmt = pMain;
        while (*pFmt) {

            if (*pFmt == *pList) {

                //
                // Already got this one
                //

                goto next_fmt; // I know.  I hate this too.
            }

            pFmt++;
        }

        //
        // Put it on the end of the list
        //

        *pLast++ = *pList;
        iCount++;

next_fmt:

        pList++;
    }

    //
    // Stick a null on the end to terminate the list
    //

    *pLast = NULL;
}

//
// Find the first occurence of a topic conversation in our list
//

static PDDECONVINFO FindConversation(HSZ hszTopic)
{
    PDDECONVINFO pCI;

    //
    // Try to find the info in the list
    //

    pCI = ServerInfo.pConvList;
    while (pCI) {

        if (DdeCmpStringHandles(pCI->hszTopicName, hszTopic) == 0) {

            return pCI;

        }
    
        pCI = pCI->pNext;
    }

    return NULL;
}

//
// Add a conversation to our list
//

static BOOL AddConversation(HCONV hConv, HSZ hszTopic)
{
    PDDECONVINFO pCI;

    //
    // Allocate some memory for the info and fill it in
    //

    pCI = _fcalloc(1, sizeof(DDECONVINFO));
    if (!pCI) {
        return FALSE;
    }

    pCI->hConv = hConv;
    pCI->hszTopicName = hszTopic;

    //
    // Add it into the list
    //

    pCI->pNext = ServerInfo.pConvList;
    ServerInfo.pConvList = pCI;

    return TRUE;
}

//
// Remove a conversation from our list
//

static BOOL RemoveConversation(HCONV hConv, HSZ hszTopic)
{
    PDDECONVINFO pCI, pPrevCI;

    //
    // Try to find the info in the list
    //

    pCI = ServerInfo.pConvList;
    pPrevCI = NULL;
    while (pCI) {

        if ((pCI->hConv == hConv)
        &&  (DdeCmpStringHandles(pCI->hszTopicName,hszTopic) == 0)) {

            //
            // Found it. Unlink it from the list
            //

            if (pPrevCI) {

                pPrevCI->pNext = pCI->pNext;

            } else {

                ServerInfo.pConvList = pCI->pNext;

            }

            //
            // Free the memory
            //

            _ffree(pCI);

            return TRUE;

        }

        pPrevCI = pCI;
        pCI = pCI->pNext;
    }

    //
    // Not in the list
    //

    return FALSE;
}
