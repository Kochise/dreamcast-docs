/*
    @doc EXTERNAL STRUCTURE

    @types CFTAGNAME | This structure is used to store
        information on a clipboard id and its text name.

    @field WORD | wFmt | The format id.

    @field LPSTR | pszName | A pointer to the string name.

*/

/*
    @doc EXTERNAL STRUCTURE

    @types DDEEXECCMDFNINFO | This structure is used to store
        information on a DDE execute command processor function.

    @field struct _DDEEXECCMDFNINFO FAR * | pNext | Pointer to the next item
        in the list.

    @field struct _DDETOPICINFO FAR * | pTopic | Pointer to the topic 
        it belongs to.

    @field LPSTR | pszCmdName | The name of the command.

    @field PDDEEXECCMDFN | pFn | A pointer to the function which will be
        called to process the command.

    @field UINT | uiMinArgs | Min number of arguments accepted by
        this command.

    @field UINT | uiMaxArgs | Max number of arguments accepted by 
        this command.

*/

/*
    @doc EXTERNAL STRUCTURE

    @types DDEITEMINFO | This structure is used to store
        information on a DDE item.

    @field struct _DDEITEMINFO FAR * | pNext | Pointer to the next item
        in the list of items.

    @field LPSTR | pszItemName | Pointer to its string name
    
    @field HSZ | hszItemName | DDE string handle for the name

    @field struct _DDETOPICINFO FAR * | pTopic | Pointer to the topic
        it belongs to.

    @field LPWORD | pFormatList | Pointer to a null terminated
        list of clipboard format words.

    @field PDDEREQUESTFN | pfnRequest | Pointer to the item 
        specific request processor.

    @field PDDEPOKEFN | pfnPoke | Pointer to the item specific
        poke processor.

    @field HDDEDATA | hData | Data handle for this item. This is only used
        by stddde.c when the item is a special 'Result' item and may be used
        as required for other items.

*/

/*
    @doc EXTERNAL STRUCTURE

    @types DDETOPICINFO | This structure is used to store
        information on a DDE topic.

    @field struct _DDETOPICINFO FAR * | pNext | Pointer to the next topic
        in the topic list.

    @field LPSTR | pszTopicName | Pointer to its string name.

    @field HSZ | hszTopicName | DDE string handle for the name.

    @field PDDEITEMINFO | pItemList | Pointer to the item list for
        this topic.

    @field PDDEEXECFN | pfnExec | Pointer to the generic execute processor
        for this topic.

    @field PDDEREQUESTFN | pfnRequest | Pointer to the generic request 
        processor for this topic.

    @field PDDEPOKEFN | pfnPoke | Pointer to the generic poke processor
        for this topic.

    @field PDDEEXECCMDFNINFO | pCmdList | Pointer to the execute 
        command list for this topic.

*/

/*
    @doc EXTERNAL STRUCTURE

    @types DDECONVINFO | This structure is used to store
        information on a DDE conversation.

    @field struct _DDECONVINFO FAR * | pNext | Pointer to the next one
        in the conversation list.

    @field HCONV | hConv | Handle to the conversation.

    @field HSZ | hszTopicName | HSZ for the topic of the conversation.

    @field PDDEITEMINFO | pResultItem | Pointer to a temporary result item
        used to support the 'Result' topic.

*/

/*
    @doc EXTERNAL STRUCTURE

    @types DDESERVERINFO | This structure is used to store
        information on a DDE server which has only one service.

    @field LPSTR | lpszServiceName | Pointer to the service string name.

    @field HSZ | hszServiceName | DDE string handle for the name.

    @field PDDETOPICINFO | pTopicList | Pointer to the topic list.

    @field DWORD | dwDDEInstance | DDE Instance value.

    @field PFNCALLBACK | pfnStdCallback | Pointer to standard 
        DDE callback function.

    @field PFNCALLBACK | pfnCustomCallback | Pointer to a custom 
        DDE callback function.

    @field PDDECONVINFO | pConvList | Pointer to the active conversation 
        list.

*/
