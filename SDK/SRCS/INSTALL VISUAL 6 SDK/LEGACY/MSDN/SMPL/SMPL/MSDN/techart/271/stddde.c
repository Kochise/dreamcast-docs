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

    All objects created by this module are created using _fcalloc
    which allows efficient use of global memory and zero initializes
    each one.

    The DDE Execute command parser is only invoked if the topic
    receiving the execute command has no generic execute function
    associated with it.  This is different from item processing which
    defaults to the generic topic handler if there is no specific item 
    handler.

*/

#include <windows.h>
#include "stddde.h"
#include <malloc.h>
#include <string.h>
#include <ctype.h>

//
// Local constants
//

#define MAXFORMATS      128     // max no of CF formats we will list
#define MAXOPS  ((UINT)128)     // max no of opcodes we can execute
#define MAXRESULTSIZE   256     // largest result string returned

//
// Define the pointer type we use in the exec cmd op table
//

typedef void FAR *POP;
typedef POP FAR *PPOP;

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
HDDEDATA SysReqProtocols(UINT wFmt, HSZ hszTopic, HSZ hszItem);
HDDEDATA SysReqResultInfo(UINT wFmt, HSZ hszTopic, HSZ hszItem);
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
static LPSTR SkipWhiteSpace(LPSTR pszString);
static BOOL ProcessExecRequest(PDDETOPICINFO pTopic, HDDEDATA hData);
static BOOL ParseCmd(LPSTR FAR *ppszCmdLine,
                     PDDETOPICINFO pTopic,
                     LPSTR pszError,
                     UINT uiErrorSize,
                     PPOP pOpTable,
                     UINT uiNops,
                     LPSTR pArgBuf);
static LPSTR ScanForChar(char c, LPSTR *ppStr);
static PDDEEXECCMDFNINFO ScanForCommand(PDDEEXECCMDFNINFO pInfoTable, LPSTR *ppStr);
static LPSTR ScanForString(LPSTR *ppStr, LPSTR pszTerm, LPSTR *ppArgBuf);
static BOOL IsValidStringChar(char c);
static BOOL FAR SysResultExecCmd(PDDETOPICINFO pTopic,
                                 LPSTR pszResult, 
                                 UINT uiResultSize, 
                                 UINT uiNargs, 
                                 LPSTR FAR *ppArgs);

/*
    @doc EXTERNAL

    @api BOOL | InitializeDDE | Initialize all the DDE lists for
        this server and initialize DDEML.

    @parm HANDLE | hInstance | Instance handle of the calling application.

    @parm LPSTR  | pszServiceName | Pointer to a string containing
        the name of the DDE service.

    @parm LPDWORD | pdwDDEInst | A pointer to a DWORD variable to receive
        the instance identifier returned by DDEML. This argument is optional.
        It may be set to NULL.

    @parm PFNCALLBACK | pfnCustomCallback | A pointer to an optional
        custom callback function.  This parameter may be set to NULL in
        which case all the handling will be done by stddde.

    @rdesc The return value is TRUE if the initialization succeeds and
        FALSE if ti fails.

    @comm A number of items are added to the system topic by this
        function which are supported transparently to the application.

*/

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

    AddDDEItem(SZDDESYS_TOPIC, 
               SZ_PROTOCOLS,
               SysFormatList,
               SysReqProtocols,
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

/*
    @doc EXTERNAL

    @api void | UninitializeDDE | Terminate use of DDEML.

    @rdesc There is no return value.

    @comm Any resources used by earlier calls are freed.

*/

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
    // Walk the server topic list, freeing all the other string handles
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

/*
    @doc EXTERNAL

    @api PDDETOPICINFO | FindTopicFromName | Find a topic in the topic list 
        by searching for its string name.

    @parm LPSTR | pszName | A pointer to a string containing the name
        to search for.

    @rdesc The return value is a pointer to a DDETOPICINFO structure if
        the topic is found, otherwise it is NULL.

    @comm The search is not case sensitive.

*/

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

/*
    @doc EXTERNAL

    @api PDDETOPICINFO | FindTopicFromHsz | Find a topic in the topics list
        by searching for its HSZ value.

    @parm HSZ | hszName | The HSZ value to search for.

    @rdesc The return value is a pointer to a DDETOPICINFO structure if
        the topic is found, otherwise it is NULL.

    @comm The search is not case sensitive.

*/

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

/*
    @doc EXTERNAL

    @api PDDEITEMINFO | FindItemFromName | Find an item in the items
        list of a given topic by searching for its string name.

    @parm PDDETOPICINFO | pTopic | Pointer to the DDETOPICINFO structure
        for the topic being searched.

    @parm LPSTR | pszItem | Pointer to the string containing the name
        of the item to search for.

    @rdesc The return value is a pointer to a DDEITEMINFO structure
        if the item is found, otherwise it is NULL.

    @comm The search is not case sensitive.

*/

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

/*
    @doc EXTERNAL

    @api PDDEITEMINFO | FindItemFromHsz | Find an item in the items
        list of a given topic by searching for its HSZ name.

    @parm PDDETOPICINFO | pTopic | Pointer to the DDETOPICINFO structure
        for the topic being searched.

    @parm LPSTR | hszItem | HSZ of the item to search for.

    @rdesc The return value is a pointer to a DDEITEMINFO structure
        if the item is found, otherwise it is NULL.

    @comm The search is not case sensitive.

*/

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

/*
    @doc EXTERNAL

    @api PDDEEXECCMDFNINFO | FindExecCmdFromName | Find a DDE execute command
        from its string name.

    @parm PDDETOPICINFO | pTopic | Pointer to the DDETOPICINFO structure
        for the topic being searched.

    @parm LPSTR | pszCmd | Pointer to the string containing the name
        of the command to search for.

    @rdesc The return value is a pointer to a DDEEXECCMDFNINFO structure
        if the command is found, otherwise it is NULL.

    @comm The search is not case sensitive.

*/

PDDEEXECCMDFNINFO FindExecCmdFromName(PDDETOPICINFO pTopic, LPSTR pszCmd)
{
    PDDEEXECCMDFNINFO pCmd;

    pCmd = pTopic->pCmdList;
    while (pCmd) {

        if (lstrcmpi(pCmd->pszCmdName, pszCmd) == 0) {
            break;
        }

        pCmd = pCmd->pNext;
    }

    return pCmd;
}

/*
    @doc EXTERNAL

    @api PDDETOPICINFO | AddDDETopic | Add a new topic and default processing
        for its item list and formats.

    @parm LPSTR | pszTopic | Pointer to a string containing the name
        of the topic.

    @parm PDDEEXECFN | pfnExec | Pointer to an optional execute command
        processing function.  This argument may be NULL in which case
        the standard execute command parser will be used to process the
        request.

    @parm PDDEREQUESTFN | pfnRequest | Pointer to an optional function
        to handle request requests for items of this topic.  If this 
        function is provided it will be called for any item not having its
        own request function processor.

    @parm PDDEPOKEFN | pfnPoke | Pointer to an optional function
        to handle poke requests for items of this topic.  If this 
        function is provided it will be called for any item not having its
        own poke function processor.

    @rdesc The return value is a pointer to a DDETOPICINFO structure
        if the topic is added or NULL if not.

    @comm If the topic already exists, its information will be updated
        by the call.

*/

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
        pTopic->pCmdList = NULL;

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

/*
    @doc EXTERNAL

    @api BOOL | RemoveDDETopic | Remove a topic from the topics list.

    @parm LPSTR | pszTopic | Pointer to a string containing the 
        name of the topic.

    @rdesc The return value is TRUE if the topic is removed, FALSE
        if not.

    @comm If there is a conversation active on this topic it
        will be disconnected. Removing a topic removes all its
        associated items.

*/

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
            // Remove all the execute command handlers in the topic
            //

            while(pTopic->pCmdList) {

                if (!RemoveDDEExecCmd(lpszTopic,
                                      pTopic->pCmdList->pszCmdName)) {
                    return FALSE; // some error
                }
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

/*
    @doc EXTERNAL

    @api PDDEITEMINFO | AddDDEItem | Add an item to a topic.

    @parm LPSTR | pszTopic | Pointer to a string containing the
        name of the topic to add the item to.

    @parm LPSTR | pszItem | Pointer to a string containing the
        name of the item to add.

    @parm LPWORD | pFormatList | Pointer to a null terminated 
        list of valid clipboard format ids.

    @parm PDDEREQUESTFN | pfnRequest | Pointer to an optional function
        to handle request requests for this item. If this 
        function is not provided then the default action is to call
        the topic generic request processor function if present.

    @parm PDDEPOKEFN | pfnPoke | Pointer to an optional function
        to handle poke requests for this item.  If this 
        function is not provided then the default action is to call
        the topic generic poke processor function if present.

    @rdesc The return value is a pointer to a DDEITEMINFO structure
        if the item is added or NULL if not.

*/

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

/*
    @doc EXTERNAL

    @api BOOL | RemoveDDEItem | Remove an item from a topic.

    @parm LPSTR | pszTopic | Pointer to a string containing the
        name of the topic to remove the item from.

    @parm LPSTR | pszItem | Pointer to a string containing the
        name of the item to remove.

    @rdesc The return value is TRUE if the item is removed, FALSE
        if not.

    @comm Removing all the items from a topic does not remove the topic.

*/

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

/*
    @doc EXTERNAL

    @api PDDEEXECCMDFNINFO | AddDDEExecCmd | Add an execute command
        processor to a topic.

    @parm LPSTR | pszTopic | Pointer to a string containing the
        name of the topic to add the command to.

    @parm LPSTR | pszCmdName | Pointer to a string containing the
        name of the command to add.

    @parm PDDEEXECCMDFN | pfnExecCmd | Pointer to a function to
        handle the command request.

    @parm UINT | uiMinArgs | The minimum number of arguments which
        are valid for this command.

    @parm UINT | uiMaxArgs | The maximum number of arguments which
        are valid for this command.

    @rdesc The return value is a pointer to a DDEEXECCMDFNINFO 
        structure if the command is added successfully, otherwise
        it is NULL.

    @comm If the topic does not exist it will be created. If the
        command already exists, the information will be updated.

    @cb BOOL | DdeExecFn <f DdeExecFn> is a placeholder for
        the application supplied function name.  

    @parm HSZ | hszTopic | HSZ of the topic for which the command
        is being issued.

    @parm HDDEDATA | hData | A DDE data handle to an object containing the
        the command string.

    @rdesc The return value is TRUE if the command is processed with
        no errors, and FALSE if not.

    
*/

PDDEEXECCMDFNINFO AddDDEExecCmd(LPSTR pszTopic, 
                              LPSTR pszCmdName,
                              PDDEEXECCMDFN pExecCmdFn,
                              UINT uiMinArgs,
                              UINT uiMaxArgs)
{
    PDDEEXECCMDFNINFO pCmd = NULL;
    PDDEEXECCMDFNINFO pHead;
    PDDETOPICINFO pTopic;

    //
    // See if we have this topic already
    //

    pTopic = FindTopicFromName(pszTopic);

    if (!pTopic) {

        //
        // We need to add this as a new topic
        //

        pTopic = AddDDETopic(pszTopic,
                             NULL,
                             NULL,
                             NULL);
    }

    if (!pTopic) return NULL;  // failed

    //
    // See if we already have this command
    //

    pCmd = FindExecCmdFromName(pTopic, pszCmdName);

    if (pCmd) {

        //
        // Just update the info in it
        //

        pCmd->pFn = pExecCmdFn;
        pCmd->uiMinArgs = uiMinArgs;
        pCmd->uiMaxArgs = uiMaxArgs;

    } else {

        //
        // Create a new item
        //

        pCmd = _fcalloc(1, sizeof(DDEEXECCMDFNINFO));
        if (!pCmd) return NULL;

        //
        // Fill out the info
        //

        pCmd->pszCmdName = pszCmdName;
        pCmd->pTopic = pTopic;
        pCmd->pFn = pExecCmdFn;
        pCmd->uiMinArgs = uiMinArgs;
        pCmd->uiMaxArgs = uiMaxArgs;

        //
        // Add it to the existing cmd list for this topic
        //

        pHead = pTopic->pCmdList;
        pCmd->pNext = pTopic->pCmdList;
        pTopic->pCmdList = pCmd;

        //
        // If this was the first command added to the list,
        // add the 'Result' command too.  This supports the
        // Execute Control 1 protocol.
        //

        AddDDEExecCmd(pszTopic,
                      SZ_RESULT,
                      SysResultExecCmd,
                      1, 1);

    }

    return pCmd;
}

/*
    @doc EXTERNAL

    @api BOOL | RemoveDDEExecCmd | Remove a command from a topic.

    @parm LPSTR | pszTopic | Pointer to a string containing the
        name of the topic to remove the command from.

    @parm LPSTR | pszCmdName | Pointer to a string containing the
        name of the command to remove.

    @rdesc The return value is TRUE if the command is removed, FALSE
        if not.

*/

BOOL RemoveDDEExecCmd(LPSTR pszTopic, LPSTR pszCmdName)
{
    PDDETOPICINFO pTopic;
    PDDEEXECCMDFNINFO pCmd, pPrevCmd;

    //
    // See if we have this topic
    //

    pTopic = FindTopicFromName(pszTopic);

    if (!pTopic) {
        return FALSE;
    }

    //
    // Walk the topic item list looking for this cmd.
    //

    pPrevCmd = NULL;
    pCmd = pTopic->pCmdList;
    while (pCmd) {

        if (lstrcmpi(pCmd->pszCmdName, pszCmdName) == 0) {

            //
            // Found it.  Unlink it from the list.
            //

            if (pPrevCmd) {

                pPrevCmd->pNext = pCmd->pNext;

            } else {

                pTopic->pCmdList = pCmd->pNext;

            }

            //
            // Free the memory associated with it
            //

            _ffree(pCmd);

            return TRUE;
        }

        pPrevCmd = pCmd;
        pCmd = pCmd->pNext;
    }

    //
    // We don't have that one
    //

    return FALSE;
}

/*
    @doc EXTERNAL

    @api LPSTR | GetCFNameFromId | Get the text name of a clipboard
        format from its id.

    @parm WORD | wFmt | The format tag to return the name for.

    @parm LPSTR | pBuf | Pointer to a buffer to receive the name.

    @parm int | iSize | The size of the buffer.

    @rdesc If found the return value is a pointer to the return string.
        If not found the return buffer contains an empty string.

    @comm This command supports both standard clipboard formats
        and registered ones.

*/

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

/*
    @doc EXTERNAL

    @api WORD | GetCFIdFromName | Get a clipboard format id from its name.

    @parm LPSTR | pszName | Pointer to a string containing the name
        of the format.

    @rdesc The return value is either a standard format id or the
        result of registering the name.  The name supplied is always
        registerd if it is not one of the  standard ones.

*/

WORD GetCFIdFromName(LPSTR pszName)
{
    PCFTAGNAME pCTN;

    //
    // Try for a standard one first
    //

    pCTN = CFNames;
    while (pCTN->wFmt) {
        if (lstrcmpi(pCTN->pszName, pszName) == 0) {
            return pCTN->wFmt;
        }
        pCTN++;
    }

    //
    // Register it
    //

    return RegisterClipboardFormat(pszName);
}

/*
    @doc EXTERNAL

    @api void | PostDDEAdvise | Post a DDE advise notice to DDEML.

    @parm PDDEITEMINFO | pItemInfo | Pointer to a DDEITEMINFO structure
        describing the item.

    @rdesc There is no return value.

*/

void PostDDEAdvise(PDDEITEMINFO pItemInfo)
{
    if (pItemInfo && pItemInfo->pTopic) {
        DdePostAdvise(ServerInfo.dwDDEInstance,
                      pItemInfo->pTopic->hszTopicName,
                      pItemInfo->hszItemName);
    }
}

/*
    @doc INTERNAL

    @api HDDEDATA | StdDDECallback | Callback function from DDEML.

    @parm WORD | wType | The transaction type.

    @parm WORD | wFmt | The data format.

    @parm HCONV | hConv | Handle to the current conversation.

    @parm HSZ | hsz1 | Handle to a DDEML string.

    @parm HSZ | hsz2 | Handle to a DDEML string.

    @parm HDDEDATA | hData | Handle to a DDE data object.

    @parm DWORD | dwData1 | A DWORD parameter.

    @parm DWORD | dwData1 | A DWORD parameter.

    @rdesc The return value can be many things.  It can be a handle to
        a DDE data object, NULL or one of several flag values.  The return
        value depends on the type of transaction.

*/

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

/*
    @doc INTERNAL

    @api BOOL | DoCallback | Process a generic callback.

    @parm WORD | wType | The transaction type.

    @parm WORD | wFmt | The data format.

    @parm HCONV | hConv | Handle to the current conversation.

    @parm HSZ | hszTopic | HSZ for the current topic.

    @parm HSZ | hszItem | HSZ for the current item.

    @parm HDDEDATA | hData | Handle to a DDE data object.

    @parm HDDEDATA * | phReturnData | Pointer to a DDE data handle to
        be set with the data handle of the returned data.

*/

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
        // See if the user supplied a generic function to handle this
        // or, if not, see if there is a command table.  If so run
        // the parser over the command string.
        //

        if (pTopic->pfnExec) {

            //
            // Call the exec function to process it
            //

            if ((*pTopic->pfnExec)(hszTopic, hData)) {

                *phReturnData = (HDDEDATA) DDE_FACK;
                return TRUE;

            }

        } else if (pTopic->pCmdList) {

            //
            // Try to parse and execute the request
            //

            if (ProcessExecRequest(pTopic, hData)) {

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
    // See if this is a supported format
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

    case XTYP_POKE:
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

/*
    @doc INTERNAL

    @api HDDEDATA | SysReqTopics | Process a request for the topic list.

    @parm UINT | wFmt | The format of the data to be returned.

    @parm HSZ | hszTopic | The HSZ of the current topic.

    @parm HSZ | hszItem | The HSZ of the current item.

    @rdesc The return value is a DDE data handle to the data object
        containing the return data.

    @comm Typically the data is returned in CF_TEXT format as
        a tab delimited list of names.

*/

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

/*
    @doc INTERNAL

    @api HDDEDATA | SysReqItems | Process a request for the system item list.

    @parm IUNT | wFmt | The format of the data to be returned.

    @parm HSZ | hszTopic | The HSZ of the current topic.

    @parm HSZ | hszItem | The HSZ of the current item.

    @rdesc The return value is a DDE data handle to the data object
        containing the return data.

    @comm Typically the data is returned in CF_TEXT format as
        a tab delimited list of names.

*/

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

/*
    @doc INTERNAL

    @api HDDEDATA | SysReqFormats | Process a request for the
        system format list.

    @parm IUNT | wFmt | The format of the data to be returned.

    @parm HSZ | hszTopic | The HSZ of the current topic.

    @parm HSZ | hszItem | The HSZ of the current item.

    @rdesc The return value is a DDE data handle to the data object
        containing the return data.

    @comm Typically the data is returned in CF_TEXT format as
        a tab delimited list of names.  The format list is the union
        of all formats supported for all topics of the service.

*/

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

/*
    @doc INTERNAL

    @api HDDEDATA | TopicReqFormats | Process a request for the
        list of formats supported for a given topic.

    @parm IUNT | wFmt | The format of the data to be returned.

    @parm HSZ | hszTopic | The HSZ of the current topic.

    @parm HSZ | hszItem | The HSZ of the current item.

    @rdesc The return value is a DDE data handle to the data object
        containing the return data.

    @comm Typically the data is returned in CF_TEXT format as
        a tab delimited list of names. The list is the union of
        all formats possible for this topic.

*/

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

/*
    @doc INTERNAL

    @api HDDEDATA | SysReqProtocols | Process a request for the
        list of protocols supported by the server.

    @parm IUNT | wFmt | The format of the data to be returned.

    @parm HSZ | hszTopic | The HSZ of the current topic.

    @parm HSZ | hszItem | The HSZ of the current item.

    @rdesc The return value is a DDE data handle to the data object
        containing the return data.

    @comm Typically the data is returned in CF_TEXT format as
        a tab delimited list of names.  The default is to return
        the 'Execute Control 1' protocol.

*/

HDDEDATA SysReqProtocols(UINT wFmt, HSZ hszTopic, HSZ hszItem)
{
    static char sz[] = SZ_EXECUTECONTROL1;

    return DdeCreateDataHandle(ServerInfo.dwDDEInstance,
                               sz,
                               lstrlen(sz)+1,
                               0,
                               hszItem,
                               CF_TEXT,
                               0);
}

/*
    @doc INTERNAL

    @api HDDEDATA | Do WildConnect | Process a wild connect request.

    @parm HSZ | hszTopic | HSZ to the topic being connected to.

    @rdesc The return value is a DDE data handle to an object containing
        a list of topics which match the request.

    @comm Since we only support one service, this is much simpler.  
        If hszTopic is NULL we supply a list of all the topics we
        currently support.  If it's not NULL, we supply a list
        of topics (zero or one items) which match the requested topic.
        The list is terminated by a NULL entry.
*/

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

/*
    @doc INTERNAL

    @api HDDEDATA | MakeDataFromFormatList | Create a data item containing
        the names of all the formats supplied in a list.

    @parm LPWORD | pFmt | Pointer to a NULL terminated list of formats.

    @parm WORD | wFmt | The format to return the result in.

    @parm HSZ | hszItem | The item the list is beign prepared for.

    @rdesc The return value is a DDE data handle to a list of format names.

*/

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

/*
    @doc INTERNAL

    @api void | AddFormatsToList | Add a list of formats to a main
        list.

    @parm LPWORD | pMain | Pointer to the main list.

    @parm int | iMax | The amount of room left in the main list.

    @parm LPWORD | pList | Pointer to the list of formats to add.

    @rdesc There is no return value.

    @comm Each item is only added if it is not already present in the
        main list.

*/

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

/*
    @doc INTERNAL

    @api PDDECONVINFO | FindConversation | Find the first occurence
        of a conversation on a given topic in the conversation list.

    @parm HSZ | hszTopic | HSZ to the topic being searched for.

    @rdesc The return value is a pointer to a DDECONVINFO structure
        describing the conversation.  If no conversation on this
        topic is found the return value is NULL.

*/

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

/*
    @doc INTERNAL

    @api BOOL | AddConversation | Add a conversation to the conversation list.

    @parm HCONV | hConv | Handle to the conversation to add.

    @parm HSZ | hszTopic | HSZ to the topic of the conversation.

    @rdesc The return value is TRUE if the item is added to the
        list, FALSE if not.

*/

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

/*
    @doc INTERNAL

    @api BOOL | RemoveConversation | Remove a conversation form the list.

    @parm HCONV | hConv | Handle of the conversation to remove.

    @parm HSZ | hszTopic | HSZ to the topic of the conversation.

    @rdesc The return value is TRUE if the conversation is
        removed, FALSE if not.

*/

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

/////////////////////////////////////////////////////////////////////
//
// DDE Execute command parser
//
////////////////////////////////////////////////////////////////////

/*
    @doc INTERNAL

    @api BOOL | ProcessExecRequest | Process a DDE execute command line.

    @parm PDDETOPICINFO | pTopic | Pointer to a DDETOPICINFO structure
        describing the topic.

    @parm HDDEDATA | hData | Handle to a DDE data item containing the
        execute command line string.

    @rdesc The return value is TRUE if no errors occur in parsing
        or executing the commands.  It is FALSE if any error occurs.

    @comm Support for the 'Execute Control 1' protocol is provided allowing
        return information to be sent back to the caller.

*/

static BOOL ProcessExecRequest(PDDETOPICINFO pTopic, HDDEDATA hData)
{
    LPSTR pData;
    BOOL bResult = FALSE;
    POP OpTable[MAXOPS];
    PPOP ppOp, ppArg;
    UINT uiNargs;
    LPSTR pArgBuf = NULL;
    char szResult[MAXRESULTSIZE];
    PDDECONVINFO pCI;

    if (!hData) return FALSE;
    pData = (LPSTR) DdeAccessData(hData, NULL);
    if (!pData) return FALSE;

    //
    // Allocate some memory for the string argument buffer
    // Allocate a lot more than we might need so we can avoid
    // doing any space tests.
    //

    pArgBuf = _fcalloc(2, _fstrlen(pData));
    if (!pArgBuf) {
        goto PER_exit;
    }

    //
    // Get a pointer to the current conversation
    //

    pCI = FindConversation(pTopic->hszTopicName);

    //
    // Parse and execute each command in turn.
    // If an error occurs, set the error return string
    // and return FALSE.
    //

    while (pData && *pData) {

        //
        // Parse a single command
        //

        szResult[0] = '\0';
        bResult = ParseCmd(&pData,
                           pTopic,
                           szResult,
                           sizeof(szResult),
                           OpTable,
                           MAXOPS,
                           pArgBuf);

        if (!bResult) {

            //
            // See if the current conversation has a results
            // item to pass the error string back in
            //

            if (pCI && pCI->pResultItem) {

                pCI->pResultItem->hData = 
                    DdeCreateDataHandle(ServerInfo.dwDDEInstance,
                                        szResult,
                                        lstrlen(szResult)+1,
                                        0,
                                        pCI->pResultItem->hszItemName,
                                        CF_TEXT,
                                        0);
    
            }

            goto PER_exit;
        }

        //
        // Execute the op list
        //

        ppOp = OpTable;

        while (*ppOp) {

            //
            // Count the number of args
            //

            uiNargs = 0;
            ppArg = ppOp+1;
            while (*ppArg) {
                uiNargs++;
                ppArg++;
            }

            //
            // Call the function, passing the address of the first arg
            //

            ppArg = ppOp+1;
            szResult[0] = '\0';
            bResult = (*((PDDEEXECCMDFN)*ppOp))(pTopic,
                                                szResult,
                                                sizeof(szResult),
                                                uiNargs,
                                                (LPSTR FAR *)ppArg);
            //
            // See if the current conversation has a results
            // item to pass the result string back in
            //

            if (pCI && pCI->pResultItem) {

                pCI->pResultItem->hData = 
                    DdeCreateDataHandle(ServerInfo.dwDDEInstance,
                                        szResult,
                                        lstrlen(szResult)+1,
                                        0,
                                        pCI->pResultItem->hszItemName,
                                        CF_TEXT,
                                        0);
    
            }
    
            if (!bResult) {
                goto PER_exit;
            }
    
            //
            // move on to the next function
            //
    
            while (*ppOp) ppOp++;
            ppOp++;

        }

    }

    //
    // if we get this far we're done
    //

    bResult = TRUE;

PER_exit:

    DdeUnaccessData(hData);
    if (pArgBuf) {
        _ffree(pArgBuf);
    }

    return bResult;
}

/*
    @doc INTERNAL

    @api BOOL | ParseCmd | Parse a single command.

    @parm LPSTR FAR * | ppszCmdLine | Pointer to a a pointer which addresses
        the command line to be parsed.

    @parm PDDETOPICINFO | pTopic | Pointer to the topic info structure.

    @parm LPSTR | pszError | Pointer to a buffer to receive the error string.

    @parm UINT | uiErrorSize | Size of the error return buffer.

    @parm PPOP | pOpTable | Pointer to a table in which the operator and
        operands are to be inserted.

    @parm UINT | uiNops | The size of the op table.

    @parm LPSTR | pArgBuf | Pointer to a buffer in which the arguments
        are to be constructed.

    @rdesc The return value is TRUE if there are no errors, else it is FALSE.

    @comm Error information may be set in the error return buffer.

*/

static BOOL ParseCmd(LPSTR FAR *ppszCmdLine,
                     PDDETOPICINFO pTopic,
                     LPSTR pszError,
                     UINT uiErrorSize,
                     PPOP pOpTable,
                     UINT uiNops,
                     LPSTR pArgBuf)
{
    LPSTR pCmd, pArg;
    PPOP ppOp = pOpTable;
    PDDEEXECCMDFNINFO pExecFnInfo;
    UINT uiNargs;
    char cTerm;

    *ppOp = NULL;
    pCmd = SkipWhiteSpace(*ppszCmdLine);

    //
    // Scan for a command leadin
    //

    if (!ScanForChar('[', &pCmd)) {
        _fstrncpy(pszError,
                  "Missing '['",
                  uiErrorSize-1);
        return FALSE;
    }

    //
    // Scan for a valid command
    //

    pExecFnInfo = ScanForCommand(pTopic->pCmdList, &pCmd);
    if (!pExecFnInfo) {
        _fstrncpy(pszError,
                  "Invalid Command",
                  uiErrorSize-1);
        return FALSE;
    }

    //
    // Add the function pointer to the opcode list
    //

    *ppOp++ = pExecFnInfo->pFn;

    //
    // Scan for any arguments
    //

    uiNargs = 0;
    if (ScanForChar('(', &pCmd)) {

        //
        // Copy each argument to the op list
        //

        do {

            pArg = ScanForString(&pCmd, &cTerm, &pArgBuf);

            if (pArg) {

                *ppOp++ = pArg;
                uiNargs++;

            }

        } while (cTerm == ',');

        //
        // Confirm we have a terminating ) char
        //

        if ((cTerm != ')')
        && (!ScanForChar(')', &pCmd))) {
            _fstrncpy(pszError,
                      "Missing ')'",
                      uiErrorSize-1);
            return FALSE;
        }

    }   
       
    //
    // Test that we have a terminating ] char
    //

    if (!ScanForChar(']', &pCmd)) {
        _fstrncpy(pszError,
                  "Missing ']'",
                  uiErrorSize-1);
        return FALSE;
    }

    //
    // Test the number of args is correct
    //

    if (uiNargs < pExecFnInfo->uiMinArgs) {
        _fstrncpy(pszError,
                  "Too few arguments",
                  uiErrorSize-1);
        return FALSE;
    }

    if (uiNargs > pExecFnInfo->uiMaxArgs) {
        _fstrncpy(pszError,
                  "Too many arguments",
                  uiErrorSize-1);
        return FALSE;
    }

    //
    // Terminate this op list with a NULL
    //

    *ppOp++ = NULL;

    pCmd = SkipWhiteSpace(pCmd);

    //
    // Put a final NULL on the op list
    //

    *ppOp = NULL;
 
    //
    // Update the buffer pointer
    //

    *ppszCmdLine = pCmd;

    return TRUE;
}

/*
    @doc INTERNAL

    @api BOOL | SysResultExecCmd | Process a DDE Execute 'Result' command.

    @parm PDDETOPICINFO | pTopic | Pointer to a topic info structure.

    @parm LPSTR | pszResult | Pointer the the buffer to receive the 
        result string.

    @parm UINT | uiResultSize | Size of the return buffer.

    @parm UINT | uiNargs | Number of arguments in the argument list.

    @parm LPSTR FAR * | ppArgs | A list of pointers to the arguments.

    @rdesc The return value is TRUE if the command executes with no
        errors, otherwise it is FALSE.

    @comm This command creates a temporary item under the current topic
        which will contain the result of the next command to be executed.

*/

static BOOL FAR SysResultExecCmd(PDDETOPICINFO pTopic,
                                 LPSTR pszResult, 
                                 UINT uiResultSize, 
                                 UINT uiNargs, 
                                 LPSTR FAR *ppArgs)
{
    PDDECONVINFO pCI;

    //
    // Find the conversation info
    //

    pCI = FindConversation(pTopic->hszTopicName);
    if (!pCI) return FALSE; // internal error

    //
    // See if we already have a temporary result item and
    // if we do, get rid of it
    //

    if (pCI->pResultItem) {

        RemoveDDEItem(pTopic->pszTopicName,
                      pCI->pResultItem->pszItemName);
    }

    //
    // Add a new temporary result item to the current conversation
    //

    pCI->pResultItem = AddDDEItem(pTopic->pszTopicName,
                                  ppArgs[0],
                                  SysFormatList,
                                  SysReqResultInfo,
                                  NULL);

    return TRUE;
}

/*
    @doc INTERNAL

    @api HDDEDATA | SysReqResultInfo | Return the 'result' 
        info for a given item and delete the item.

    @parm UINT | wFmt | The format to return the data in.

    @parm HSZ | hszTopic | HSZ value of the topic.

    @parm HSZ | hszItem | HSZ value of the item.

    @rdesc The return value is a DDE data handle to an object containing
        the return string.

    @comm The item is deleted after the data is returned.

*/

HDDEDATA SysReqResultInfo(UINT wFmt, HSZ hszTopic, HSZ hszItem)
{
    HDDEDATA hData;
    PDDETOPICINFO pTopic;
    PDDEITEMINFO pItem;

    //
    // Find the item
    //

    pTopic = FindTopicFromHsz(hszTopic);
    pItem = FindItemFromHsz(pTopic, hszItem);

    //
    // See if it has any data to return
    //

    hData = pItem->hData;

    if (!hData) {

        //
        // Send back an empty string
        //

        hData = DdeCreateDataHandle(ServerInfo.dwDDEInstance,
                                   "",
                                   1,
                                   0,
                                   hszItem,
                                   CF_TEXT,
                                   wFmt);
    }

    //
    // Delete the item
    //

    RemoveDDEItem(pTopic->pszTopicName,
                  pItem->pszItemName);

    return hData;

}

/////////////////////////////////////////////////////////////////////
//
// Utility functions
//
/////////////////////////////////////////////////////////////////////

/*
    @doc INTERNAL

    @api LPSTR | SkipWhiteSpace | Skip over any white space characters.

    @parm LPSTR | pszString | Pointer to the current buffer position.

    @rdesc The return value is a pointer to the first non-white character.

*/

static LPSTR SkipWhiteSpace(LPSTR pszString)
{
    while (pszString && *pszString && isspace(*pszString)) {
        pszString++;
    }
    return pszString;
}

/*
    @doc INTERNAL

    @api LPSTR | ScanForChar | Scan a buffer for a given character.

    @parm char | c | The character to look for.

    @parm LPSTR * | ppStr | Pointer to the current scan pointer.

    @rdesc The return value is a pointer to the character if found,
        NULL if not.

    @comm If the character is found the scan pointer is updated
        to point to the character following the one found.

*/

static LPSTR ScanForChar(char c, LPSTR *ppStr)
{
    LPSTR p;

    p = SkipWhiteSpace(*ppStr);
    if (*p == c) {
        *ppStr = p+1;
        return p;
    }
    return NULL; // not found
}

/*
    @doc INTERNAL

    @api PDDEEXECCMDFNINFO | ScanForCommand | Scan for a valid comamnd.

    @parm PDDEEXECCMDFNINFO | pCmdInfo | Pointer to the current 
        command list.

    @parm LPSTR * | ppStr | Pointer to the current scan pointer.

    @rdesc The return value is a pointer to the command info if 
        found, NULL if not.

    @comm  If found, the scan pointer is updated.

*/

static PDDEEXECCMDFNINFO ScanForCommand(PDDEEXECCMDFNINFO pCmdInfo, 
                                        LPSTR *ppStr)
{
    LPSTR p, pStart;
    char cSave;


    p = pStart = SkipWhiteSpace(*ppStr);

    //
    // Check the first char is alpha
    //

    if (!isalpha(*p)) {
        return NULL;
    }

    //
    // Collect alpha-num chars until we get to a non-alpha.
    //

    while (isalnum(*p)) p++;

    //
    // Terminate the source temporarily with a null
    //

    cSave = *p;
    *p = '\0';

    //
    // Search for a command that matches the name we have
    //

    while (pCmdInfo) {

        if (_fstricmp(pStart, pCmdInfo->pszCmdName) == 0) {

            //
            // Found it, so restore the delimter and
            // return the info pointer
            //

            *p = cSave;
            *ppStr = p;
            return pCmdInfo;
        }
        pCmdInfo = pCmdInfo->pNext;
    }

    //
    // Didn't find it, so restore delimiter and return
    //

    *p = cSave;
    return NULL; // not found
}

/*
    @doc INTERNAL

    @api LPSTR | ScanForString | Scan for a string.

    @parm LPSTR * | ppStr | Pointer to the current scan pointer.

    @parm LPSTR | pszTerm | Pointer to a location to receive the
        character which terminates the string.

    @parm LPSTR * | ppArgBuf | Pointer to the current arg buffer pointer.

    @rdesc The return value is a pointer to the string or NULL if
        an error occurs.

    @comm The scan pointer is updated to point past the string.  The
        arg buffer pointer is updated to point to the next free 
        character.
*/

static LPSTR ScanForString(LPSTR *ppStr, LPSTR pszTerm, LPSTR *ppArgBuf)
{
    LPSTR pIn, pStart, pOut;
    BOOL bInQuotes = FALSE;

    pIn = SkipWhiteSpace(*ppStr);
    pOut = pStart = *ppArgBuf;

    //
    // See if this string is enclosed in quotes
    //

    if (*pIn == '"') {
        bInQuotes = TRUE;
        pIn++;
    }

    do {

        //
        // Test for the end of the string
        //

        if (bInQuotes) {

            if ((*pIn == '"') 
            && (*(pIn+1) != '"')) {
                pIn++;  // skip over the quote
                break;
            }

        } else {

            if (!IsValidStringChar(*pIn)) {
                break;
            }

        }

        //
        // Test for an escape sequence
        //

        if ((*pIn == '"')
        && (*pIn == '"')) {
            pIn++; // skip the escaping first quote
        }

        if (*pIn == '\\') {
            pIn++; // skip the escaping backslash
        }

        //
        // Copy the char to the arg buffer
        //

        *pOut++ = *pIn++;

    } while(*pIn);

    *pOut++ = '\0';

    //
    // Set up the terminating char and update the scan pointer
    //

    *pszTerm = *pIn;
    if (*pIn) {
        *ppStr = pIn+1;
    } else {
        *ppStr = pIn;
    }

    //
    // Update the arg buffer to the next free bit
    //

    *ppArgBuf = pOut;

    return pStart;
}

/*
    @doc INTERNAL

    @api BOOL | IsValidStringChar | Test for a valid string character.

    @parm char | c | The character to test.

    @rdesc The return value is TRUE if the character is valid, FALSE
        if not.

*/

static BOOL IsValidStringChar(char c)
{
    //
    // if it's 0-9 or a-z or A-Z it's ok
    //

    if (isalnum(c)) return TRUE;

    //
    // Test for other valid chars
    //

    switch (c) {
    case '_':
    case '$':
    case '.':
        return TRUE;
        break;

    default:
        break;
    }

    return FALSE;
}
