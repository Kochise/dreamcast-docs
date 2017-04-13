
//=============================================================================
//  MODULE: RemAPI.c
//
//  Description:
//
//  Bloodhound Parser DLL for SMB Remote APIs
//
//  Modification History
//
//  Steve Hiskey        07/07/94        Created
//=============================================================================

#include "RemAPI.h"


//=============================================================================
//  Forward references.
//=============================================================================

VOID WINAPIV RemAPIFormatSummary(LPPROPERTYINST lpPropertyInst);



//=============================================================================
//  Labeled RemAPI command set.
//=============================================================================
       
LABELED_WORD Commands[] = 
{
    {     0,    "NetShareEnum"},
    {     1,    "NetShareGetInfo"},
    {     2,    "NetShareSetInfo"},
    {     3,    "NetShareAdd"},
    {     4,    "NetShareDel"},
    {     5,    "NetShareCheck"},
    {     6,    "NetSessionEnum"},
    {     7,    "NetSessionGetInfo"},
    {     8,    "NetSessionDel"},
    {     9,    "NetConnectionEnum"},
    {    10,    "NetFileEnum"},
    {    11,    "NetFileGetInfo"},
    {    12,    "NetFileClose"},
    {    13,    "NetServerGetInfo"},
    {    14,    "NetServerSetInfo"},
    {    15,    "NetServerDiskEnum"},
    {    16,    "NetServerAdminCommand"},
    {    17,    "NetAuditOpen"},
    {    18,    "NetAuditClear"},
    {    19,    "NetErrorLogOpen"},
    {    20,    "NetErrorLogClear"},
    {    21,    "NetCharDevEnum"},
    {    22,    "NetCharDevGetInfo"},
    {    23,    "NetCharDevControl"},
    {    24,    "NetCharDevQEnum"},
    {    25,    "NetCharDevQGetInfo"},
    {    26,    "NetCharDevQSetInfo"},
    {    27,    "NetCharDevQPurge"},
    {    28,    "NetCharDevQPurgeSelf"},
    {    29,    "NetMessageNameEnum"},
    {    30,    "NetMessageNameGetInfo"},
    {    31,    "NetMessageNameAdd"},
    {    32,    "NetMessageNameDel"},
    {    33,    "NetMessageNameFwd"},
    {    34,    "NetMessageNameUnFwd"},
    {    35,    "NetMessageBufferSend"},
    {    36,    "NetMessageFileSend"},
    {    37,    "NetMessageLogFileSet"},
    {    38,    "NetMessageLogFileGet"},
    {    39,    "NetServiceEnum"},
    {    40,    "NetServiceInstall"},
    {    41,    "NetServiceControl"},
    {    42,    "NetAccessEnum"},
    {    43,    "NetAccessGetInfo"},
    {    44,    "NetAccessSetInfo"},
    {    45,    "NetAccessAdd"},
    {    46,    "NetAccessDel"},
    {    47,    "NetGroupEnum"},
    {    48,    "NetGroupAdd"},
    {    49,    "NetGroupDel"},
    {    50,    "NetGroupAddUser"},
    {    51,    "NetGroupDelUser"},
    {    52,    "NetGroupGetUsers"},
    {    53,    "NetUserEnum"},
    {    54,    "NetUserAdd"},
    {    55,    "NetUserDel"},
    {    56,    "NetUserGetInfo"},
    {    57,    "NetUserSetInfo"},
    {    58,    "NetUserPasswordSet"},
    {    59,    "NetUserGetGroups"},
    {    60,    "DeadTableEntry"},
    {    61,    "DeadTableEntry"},
    {    62,    "NetWkstaSetUID"},
    {    63,    "NetWkstaGetInfo"},
    {    64,    "NetWkstaSetInfo"},
    {    65,    "NetUseEnum"},
    {    66,    "NetUseAdd"},
    {    67,    "NetUseDel"},
    {    68,    "NetUseGetInfo"},
    {    69,    "NetPrintQEnum"},
    {    70,    "NetPrintQGetInfo"},
    {    71,    "NetPrintQSetInfo"},
    {    72,    "NetPrintQAdd"},
    {    73,    "NetPrintQDel"},
    {    74,    "NetPrintQPause"},
    {    75,    "NetPrintQContinue"},
    {    76,    "NetPrintJobEnum"},
    {    77,    "NetPrintJobGetInfo"},
    {    78,    "NetPrintJobSetInfo"},
    {    79,    "DeadTableEntry"},
    {    80,    "DeadTableEntry"},
    {    81,    "NetPrintJobDel"},
    {    82,    "NetPrintJobPause"},
    {    83,    "NetPrintJobContinue"},
    {    84,    "NetPrintDestEnum"},
    {    85,    "NetPrintDestGetInfo"},
    {    86,    "NetPrintDestControl"},
    {    87,    "NetProfileSave"},
    {    88,    "NetProfileLoad"},
    {    89,    "NetStatisticsGet"},
    {    90,    "NetStatisticsClear"},
    {    91,    "NetRemoteTOD"},
    {    92,    "NetBiosEnum"},
    {    93,    "NetBiosGetInfo"},
    {    94,    "NetServerEnum"},
    {    95,    "I_NetServerEnum"},
    {    96,    "NetServiceGetInfo"},
    {    97,    "DeadTableEntry"},
    {    98,    "DeadTableEntry"},
    {    99,    "DeadTableEntry"},
    {   100,    "DeadTableEntry"},
    {   101,    "DeadTableEntry"},
    {   102,    "DeadTableEntry"},
    {   103,    "NetPrintQPurge"},
    {   104,    "NetServerEnum2"},
    {   105,    "NetAccessGetUserPerms"},
    {   106,    "NetGroupGetInfo"},
    {   107,    "NetGroupSetInfo"},
    {   108,    "NetGroupSetUsers"},
    {   109,    "NetUserSetGroups"},
    {   110,    "NetUserModalsGet"},
    {   111,    "NetUserModalsSet"},
    {   112,    "NetFileEnum2"},
    {   113,    "NetUserAdd2"},
    {   114,    "NetUserSetInfo2"},
    {   115,    "NetUserPasswordSet2"},
    {   116,    "I_NetServerEnum2"},
    {   117,    "NetConfigGet2"},
    {   118,    "NetConfigGetAll2"},
    {   119,    "NetGetDCName"},
    {   120,    "NetHandleGetInfo"},
    {   121,    "NetHandleSetInfo"},
    {   122,    "NetStatisticsGet2"},
    {   123,    "NetBuildGetInfo"},
    {   124,    "NetFileGetInfo2"},
    {   125,    "NetFileClose2"},
    {   126,    "NetServerReqChallenge"},
    {   127,    "NetServerAuthenticate"},
    {   128,    "NetServerPasswordSet"},
    {   129,    "NetAccountDeltas"},
    {   130,    "NetAccountSync"},
    {   131,    "NetUserEnum2"},
    {   132,    "NetWkstaUserLogon"},
    {   133,    "NetWkstaUserLogoff"},
    {   134,    "NetLogonEnum"},
    {   135,    "NetErrorLogRead"},
    {   136,    "I_NetPathType"},
    {   137,    "I_NetPathCanonicalize"},
    {   138,    "I_NetPathCompare"},
    {   139,    "I_NetNameValidate"},
    {   140,    "I_NetNameCanonicalize"},
    {   141,    "I_NetNameCompare"},
    {   142,    "NetAuditRead"},
    {   143,    "NetPrintDestAdd"},
    {   144,    "NetPrintDestSetInfo"},
    {   145,    "NetPrintDestDel"},
    {   146,    "NetUserValidate2"},
    {   147,    "NetPrintJobSetInfo"},
    {   148,    "TI_NetServerDiskEnum"},
    {   149,    "TI_NetServerDiskGetInfo"},
    {   150,    "TI_FTVerifyMirror"},
    {   151,    "TI_FTAbortVerify"},
    {   152,    "TI_FTGetInfo"},
    {   153,    "TI_FTSetInfo"},
    {   154,    "TI_FTLockDisk"},
    {   155,    "TI_FTFixError"},
    {   156,    "TI_FTAbortFix"},
    {   157,    "TI_FTDiagnoseError"},
    {   158,    "TI_FTGetDriveStats"},
    {   159,    "DeadTableEntry"},
    {   160,    "TI_FTErrorGetInfo"},
    {   161,    "DeadTableEntry"},
    {   162,    "DeadTableEntry"},
    {   163,    "NetAccessCheck"},
    {   164,    "NetAlertRaise"},
    {   165,    "NetAlertStart"},
    {   166,    "NetAlertStop"},
    {   167,    "NetAuditWrite"},
    {   168,    "NetIRemoteAPI"},
    {   169,    "NetServiceStatus"},
    {   170,    "I_NetServerRegister"},
    {   171,    "I_NetServerDeregister"},
    {   172,    "I_NetSessionEntryMake"},
    {   173,    "I_NetSessionEntryClear"},
    {   174,    "I_NetSessionEntryGetInfo"},
    {   175,    "I_NetSessionEntrySetInfo"},
    {   176,    "I_NetConnectionEntryMake"},
    {   177,    "I_NetConnectionEntryClear"},
    {   178,    "I_NetConnectionEntrySetInfo"},
    {   179,    "I_NetConnectionEntryGetInfo"},
    {   180,    "I_NetFileEntryMake"},
    {   181,    "I_NetFileEntryClear"},
    {   182,    "I_NetFileEntrySetInfo"},
    {   183,    "I_NetFileEntryGetInfo"},
    {   184,    "AltSrvMessageBufferSend"},
    {   185,    "AltSrvMessageFileSend"},
    {   186,    "I_NetRplWkstaEnum"},
    {   187,    "I_NetRplWkstaGetInfo"},
    {   188,    "I_NetRplWkstaSetInfo"},
    {   189,    "I_NetRplWkstaAdd"},
    {   190,    "I_NetRplWkstaDel"},
    {   191,    "I_NetRplProfileEnum"},
    {   192,    "I_NetRplProfileGetInfo"},
    {   193,    "I_NetRplProfileSetInfo"},
    {   194,    "I_NetRplProfileAdd"},
    {   195,    "I_NetRplProfileDel"},
    {   196,    "I_NetRplProfileClone"},
    {   197,    "I_NetRplBaseProfileEnum"},
    {   198,    "DeadTableEntry"},
    {   199,    "DeadTableEntry"},
    {   200,    "DeadTableEntry"},
    {   201,    "NetServerSetInfo"},
    {   202,    "DeadTableEntry"},
    {   203,    "DeadTableEntry"},
    {   204,    "DeadTableEntry"},
    {   205,    "NetPrintDriverEnum"},
    {   206,    "NetPrintQProcessorEnum"},
    {   207,    "NetPrintPortEnum"},
    {   208,    "NetWriteUpdateLog"},
    {   209,    "NetAccountUpdate"},
    {   210,    "NetAccountConfirmUpdate"},
    {   211,    "NetConfigSet"},
    {   212,    "NetAccountsReplicate"},
};

SET CommandSET = { (sizeof Commands / sizeof(LABELED_BYTE)), Commands };


//=============================================================================
//  RemAPI database.
//=============================================================================

#define REMAPI_SUMMARY      0
#define REMAPI_COMMAND      1

PROPERTYINFO RemAPIDatabase[] =
{
    {   //  REMAPI_SUMMARY
        0,0, 
        "Summary",  
        "Remote API packet", 
        PROP_TYPE_SUMMARY, 
        PROP_QUAL_NONE, 
        0, 
        FORMAT_BUFFER_SIZE, 
        RemAPIFormatSummary},

    {   // REMAPI_COMMAND
        0,0, 
        "Command",     
        "Remote API Command field.", 
        PROP_TYPE_WORD,    
        PROP_QUAL_LABELED_SET, 
        &CommandSET, 
        FORMAT_BUFFER_SIZE, 
        FormatPropertyInstance},
};

DWORD nRemAPIProperties = ((sizeof RemAPIDatabase) / PROPERTYINFO_SIZE);



//=============================================================================
//  Protocol entry points.
//=============================================================================

VOID   WINAPI RemAPIRegister(HPROTOCOL);
VOID   WINAPI RemAPIDeregister(HPROTOCOL);
LPBYTE WINAPI RemAPIRecognizeFrame(HFRAME, LPVOID, LPVOID, DWORD, DWORD, HPROTOCOL, DWORD, LPDWORD, LPHPROTOCOL, LPDWORD);
LPBYTE WINAPI RemAPIAttachProperties(HFRAME, LPVOID, LPVOID, DWORD, DWORD, HPROTOCOL, DWORD, DWORD);
DWORD  WINAPI RemAPIFormatProperties(HFRAME, LPVOID, LPVOID, DWORD, LPPROPERTYINST);

ENTRYPOINTS RemAPIEntryPoints =
{
    RemAPIRegister,
    RemAPIDeregister,
    RemAPIRecognizeFrame,
    RemAPIAttachProperties,
    RemAPIFormatProperties
};

HPROTOCOL hRemAPI = NULL;


DWORD Attached = 0;

//=============================================================================
//  FUNCTION: DLLEntry()
//
//  Modification History
//
//  Steve Hiskey        07/07/94        Created
//=============================================================================

BOOL WINAPI DLLEntry(HANDLE hInstance, ULONG Command, LPVOID Reserved)
{
    //=========================================================================
    //  If we are loading!
    //=========================================================================

    if ( Command == DLL_PROCESS_ATTACH )
    {
        if ( Attached++ == 0 )
        {
            hRemAPI = CreateProtocol("RemAPI", &RemAPIEntryPoints, ENTRYPOINTS_SIZE);
        }
    }

    //=========================================================================
    //  If we are unloading!
    //=========================================================================

    if ( Command == DLL_PROCESS_DETACH )
    {
        if ( --Attached == 0 )
        {
            DestroyProtocol(hRemAPI);
        }
    }

    return TRUE;                    //... Bloodhound parsers ALWAYS return TRUE.
}


//=============================================================================
//  FUNCTION: RemAPIRegister()
//
//  Modification History
//
//  Steve Hiskey        07/07/94        Created
//=============================================================================

VOID WINAPI RemAPIRegister(HPROTOCOL hRemAPIProtocol)
{
    register DWORD i;

    //=========================================================================
    //  Create the property database.
    //=========================================================================

    CreatePropertyDatabase(hRemAPIProtocol, nRemAPIProperties);

    for(i = 0; i < nRemAPIProperties; ++i)
    {
        AddProperty(hRemAPIProtocol, &RemAPIDatabase[i]);
    }

}

//=============================================================================
//  FUNCTION: Deregister()
//
//  Modification History
//
//  Steve Hiskey        07/07/94        Created
//=============================================================================

VOID WINAPI RemAPIDeregister(HPROTOCOL hRemAPIProtocol)
{
    DestroyPropertyDatabase(hRemAPIProtocol);
}

//=============================================================================
//  FUNCTION: RemAPIRecognizeFrame()
//
//  Modification History
//
//  Steve Hiskey        07/07/94        Created
//=============================================================================

LPBYTE WINAPI RemAPIRecognizeFrame(HFRAME          hFrame,                     //... frame handle.
                                LPBYTE          MacFrame,                   //... Frame pointer.
                                LPBYTE          RemAPIFrame,                   //... Relative pointer.
                                DWORD           MacType,                    //... MAC type.
                                DWORD           BytesLeft,                  //... Bytes left.
                                HPROTOCOL       hPreviousProtocol,          //... Previous protocol or NULL if none.
                                DWORD           nPreviousProtocolOffset,    //... Offset of previous protocol.
                                LPDWORD         ProtocolStatusCode,         //... Pointer to return status code in.
                                LPHPROTOCOL     hNextProtocol,              //... Next protocol to call (optional).
                                LPDWORD         InstData)                   //... Next protocol instance data.
{
    *ProtocolStatusCode = PROTOCOL_STATUS_CLAIMED;
    return NULL;
}

//=============================================================================
//  FUNCTION: RemAPIAttachProperties()
//
//  Modification History
//
//  Steve Hiskey        07/07/94        Created
//=============================================================================

LPBYTE WINAPI RemAPIAttachProperties(HFRAME    hFrame,
                                  LPBYTE    Frame,
                                  LPBYTE    RemAPIFrame,
                                  DWORD     MacType,
                                  DWORD     BytesLeft,
                                  HPROTOCOL hPreviousProtocol,
                                  DWORD     nPreviousProtocolOffset,
                                  DWORD     InstData)
{
    if ( InstData == 0 )    // this is a request... SMB said so...
    {
        AttachPropertyInstance(hFrame,
                           RemAPIDatabase[REMAPI_SUMMARY].hProperty,
                           BytesLeft,
                           RemAPIFrame,
                           0, 0, 0);

        AttachPropertyInstance(hFrame,
                           RemAPIDatabase[REMAPI_COMMAND].hProperty,
                           sizeof(WORD),
                           RemAPIFrame,
                           0, 
                           1,   // level
                           0);

    }
    else    // this is a response SMB transact... we don't get told WHAT command the
            // request was... so we have to look back to find the previous frame that 
            // contains our request.
            // This parser assumes that the SMB parser is kind in that it will tell
            // us the frame number of the request frame.  Without this, we would have
            // to get the SMB mid/pid/tid/uid from our frame, find the previous SMB
            // that matches our description, and see what our Remote API command was.
    {
        // The InstData is actually the frame number of the frame that holds the request..
        // If the frame number was 0, then the frame number will be (DWORD)-1.
        DWORD   ReqFrameNum = (InstData==(DWORD)-1)?0:InstData;
        WORD    RemAPICommand;
        HFRAME  hFrameReq;
        LPBYTE  lpReqRemAPI;
        LPBYTE  lpReqFrame;

        // Go get that frame and see what type of remote API we are...
        hFrameReq = GetFrame ( GetFrameCaptureHandle(hFrame), ReqFrameNum );

        if ( hFrameReq == NULL )    // we have a frame number but no frame??
        {   // This should never happen because the SMB parser SAID that we were
            // a remote api AND it gave us a frame number... therefore, hitting
            // this code path implies a bug in either SMB or the kernel.
            #ifdef DEBUG
            DebugBreak ();
            #endif
            return NULL;
        }
        
        lpReqFrame = LockFrame ( hFrameReq );
        lpReqRemAPI = lpReqFrame + GetProtocolStartOffset ( hFrameReq, "REMAPI" );
        RemAPICommand = *(UNALIGNED WORD *)lpReqRemAPI;  // command is the first word.

        // NOW we can attach properties for the response




        UnlockFrame ( hFrameReq );
    }
    return NULL;
}


//==============================================================================
//  FUNCTION: RemAPIFormatSummary()
//
//  Modification History
//
//  Steve Hiskey        07/07/94        Created
//==============================================================================

VOID WINAPIV RemAPIFormatSummary(LPPROPERTYINST lpPropertyInst)
{
    WORD Command = *(UNALIGNED WORD *)lpPropertyInst->lpData;
    LPSTR CommandStr = LookupWordSetString ( &CommandSET, Command );

    DWORD Length = wsprintf(lpPropertyInst->szPropertyText, 
                            "Remote API %s",
                            CommandStr?CommandStr:"Unknown" );
}


//==============================================================================
//  FUNCTION: RemAPIFormatProperties()
//
//  Modification History
//
//  Steve Hiskey        07/07/94        Created
//==============================================================================

DWORD WINAPI RemAPIFormatProperties(HFRAME         hFrame,
                                 LPBYTE         MacFrame,
                                 LPBYTE         FrameData,
                                 DWORD          nPropertyInsts,
                                 LPPROPERTYINST p)
{
    //=========================================================================
    //  Format each property in the property instance table.
    //
    //  The property-specific instance data was used to store the address of a
    //  property-specific formatting function so all we do here is call each
    //  function via the instance data pointer.
    //=========================================================================

    while (nPropertyInsts--)
    {
        ((FORMAT) p->lpPropertyInfo->InstanceData)(p);

        p++;
    }

    return BHERR_SUCCESS;
}
