/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 2.00.0102 */
/* at Mon Sep 25 11:13:21 1995
 */
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "winds.h"

extern const MIDL_FORMAT_STRING __MIDLFormatString;

extern const MIDL_FORMAT_STRING __MIDLProcFormatString;

extern RPC_DISPATCH_TABLE WINDSREM_v1_6_DispatchTable;

static const RPC_SERVER_INTERFACE WINDSREM___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0xDDFFFE60,0x36D0,0x11CE,{0x9F,0x2D,0x00,0xAA,0x00,0x51,0x0E,0x3B}},{1,6}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &WINDSREM_v1_6_DispatchTable,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE WINDSREM_v1_6_s_ifspec = (RPC_IF_HANDLE)& WINDSREM___RpcServerInterface;

extern const MIDL_STUB_DESC WINDSREM_StubDesc;

void __RPC_STUB
WINDSREM_RemoteIsServerRunning(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    RpcTryFinally
        {
        
        _RetVal = RemoteIsServerRunning();
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteGetAllAccounts(
    PRPC_MESSAGE _pRpcMessage )
{
    long _M154;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pPipeNumber;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    pPipeNumber = 0;
    RpcTryFinally
        {
        pPipeNumber = &_M154;
        
        _RetVal = RemoteGetAllAccounts(pPipeNumber);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pPipeNumber;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteFinishUpload(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned char __RPC_FAR *szCookie;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szCookie = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[8] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szCookie,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        
        _RetVal = RemoteFinishUpload(szCookie);
        
        _StubMsg.BufferLength = 4U;
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteGetContainerProps(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M155;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwContainerID;
    unsigned long __RPC_FAR *pdwContentCount;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    pdwContentCount = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[14] );
        
        dwContainerID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pdwContentCount = &_M155;
        
        _RetVal = RemoteGetContainerProps(dwContainerID,pdwContentCount);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwContentCount;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteGetContainerRecipients(
    PRPC_MESSAGE _pRpcMessage )
{
    long _M156;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwContainerID;
    unsigned long dwFlags;
    long __RPC_FAR *pPipeNumber;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    pPipeNumber = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[22] );
        
        dwFlags = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        dwContainerID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pPipeNumber = &_M156;
        
        _RetVal = RemoteGetContainerRecipients(
                                       dwFlags,
                                       dwContainerID,
                                       pPipeNumber);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pPipeNumber;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteGetPublicFoldersList(
    PRPC_MESSAGE _pRpcMessage )
{
    long _M157;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    short nFlags;
    long __RPC_FAR *pPipeNumber;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    pPipeNumber = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[32] );
        
        nFlags = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        pPipeNumber = &_M157;
        
        _RetVal = RemoteGetPublicFoldersList(nFlags,pPipeNumber);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pPipeNumber;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteGetPublicFolderMessages(
    PRPC_MESSAGE _pRpcMessage )
{
    long _M158;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwFolderID;
    short nFlags;
    long __RPC_FAR *pPipeNumber;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    pPipeNumber = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[40] );
        
        nFlags = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        _StubMsg.Buffer += 2;
        dwFolderID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pPipeNumber = &_M158;
        
        _RetVal = RemoteGetPublicFolderMessages(
                                        nFlags,
                                        dwFolderID,
                                        pPipeNumber);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pPipeNumber;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteChangePasswordA(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned char __RPC_FAR *szMailbox;
    unsigned char __RPC_FAR *szNewPassword;
    unsigned char __RPC_FAR *szOldPassword;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    szOldPassword = 0;
    szNewPassword = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[50] );
        
        szMailbox = ( unsigned char __RPC_FAR * )_StubMsg.Buffer;
        _StubMsg.Buffer += sizeof( unsigned char  );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOldPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szNewPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        
        _RetVal = RemoteChangePasswordA(
                                szMailbox,
                                szOldPassword,
                                szNewPassword);
        
        _StubMsg.BufferLength = 4U;
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteLogonMailBoxA(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M159;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pdwMailboxID;
    unsigned char __RPC_FAR *szFullName;
    unsigned char __RPC_FAR *szMailbox;
    unsigned char __RPC_FAR *szPassword;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    szPassword = 0;
    szFullName = 0;
    pdwMailboxID = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[64] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        szFullName = _StubMsg.pfnAllocate((32 + 1) * 1);
        pdwMailboxID = &_M159;
        
        _RetVal = RemoteLogonMailBoxA(
                              szMailbox,
                              szPassword,
                              szFullName,
                              pdwMailboxID);
        
        _StubMsg.BufferLength = 12U + 11U + 7U;
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[16] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szFullName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[16] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwMailboxID;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szFullName,
                        &__MIDLFormatString.Format[12] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteLogonMailBoxAndSetNotifA(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M160;
    unsigned long _M161;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pdwMailboxID;
    unsigned long __RPC_FAR *pulConnectionID;
    unsigned char __RPC_FAR *szComputerName;
    unsigned char __RPC_FAR *szFullName;
    unsigned char __RPC_FAR *szMailbox;
    unsigned char __RPC_FAR *szPassword;
    unsigned long ulNotifMask;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    szPassword = 0;
    szFullName = 0;
    pdwMailboxID = 0;
    szComputerName = 0;
    pulConnectionID = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[82] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        ulNotifMask = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        szFullName = _StubMsg.pfnAllocate((32 + 1) * 1);
        pdwMailboxID = &_M160;
        pulConnectionID = &_M161;
        
        _RetVal = RemoteLogonMailBoxAndSetNotifA(
                                         szMailbox,
                                         szPassword,
                                         szFullName,
                                         pdwMailboxID,
                                         szComputerName,
                                         ulNotifMask,
                                         pulConnectionID);
        
        _StubMsg.BufferLength = 12U + 11U + 7U + 7U;
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[26] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szFullName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[26] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwMailboxID;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pulConnectionID;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szFullName,
                        &__MIDLFormatString.Format[22] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteTerminateNotifA(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned char __RPC_FAR *szComputerName;
    unsigned long ulConnectionID;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szComputerName = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[110] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        ulConnectionID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        _RetVal = RemoteTerminateNotifA(szComputerName,ulConnectionID);
        
        _StubMsg.BufferLength = 4U;
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteValidateNotifA(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M162;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pulConnectionID;
    unsigned char __RPC_FAR *szComputerName;
    unsigned char __RPC_FAR *szMailboxName;
    unsigned long ulNotifMask;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szComputerName = 0;
    szMailboxName = 0;
    pulConnectionID = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[118] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailboxName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        ulNotifMask = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pulConnectionID = &_M162;
        
        _RetVal = RemoteValidateNotifA(
                               szComputerName,
                               szMailboxName,
                               ulNotifMask,
                               pulConnectionID);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pulConnectionID;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteOpenMsgUploadPipeA(
    PRPC_MESSAGE _pRpcMessage )
{
    long _M163;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pPipeNumber;
    unsigned char __RPC_FAR *szCookie;
    unsigned char __RPC_FAR *szSenderMailbox;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szSenderMailbox = 0;
    pPipeNumber = 0;
    szCookie = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[134] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szSenderMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        pPipeNumber = &_M163;
        szCookie = _StubMsg.pfnAllocate((32 + 1) * 1);
        
        _RetVal = RemoteOpenMsgUploadPipeA(
                                   szSenderMailbox,
                                   pPipeNumber,
                                   szCookie);
        
        _StubMsg.BufferLength = 4U + 12U + 11U;
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szCookie,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[36] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pPipeNumber;
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szCookie,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[36] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szCookie,
                        &__MIDLFormatString.Format[32] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteSendMsgToAccountA(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned char __RPC_FAR *szCookie;
    unsigned char __RPC_FAR *szHeaderInfo;
    unsigned char __RPC_FAR *szRecipAccount;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szRecipAccount = 0;
    szHeaderInfo = 0;
    szCookie = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[148] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szRecipAccount,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szHeaderInfo,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szCookie,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        
        _RetVal = RemoteSendMsgToAccountA(
                                  szRecipAccount,
                                  szHeaderInfo,
                                  szCookie);
        
        _StubMsg.BufferLength = 4U;
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteOpenMsgDownloadPipeA(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M164;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pPipeNumber;
    unsigned char __RPC_FAR *szMailbox;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    pPipeNumber = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[162] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        pPipeNumber = &_M164;
        
        _RetVal = RemoteOpenMsgDownloadPipeA(szMailbox,pPipeNumber);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pPipeNumber;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteOpenHeaderDownloadPipeA(
    PRPC_MESSAGE _pRpcMessage )
{
    long _M165;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pPipeNumber;
    unsigned char __RPC_FAR *szMailbox;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    pPipeNumber = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[162] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        pPipeNumber = &_M165;
        
        _RetVal = RemoteOpenHeaderDownloadPipeA(szMailbox,pPipeNumber);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pPipeNumber;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteCheckNewMailA(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M166;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pulPending;
    unsigned char __RPC_FAR *szMailbox;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    pulPending = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[162] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        pulPending = &_M166;
        
        _RetVal = RemoteCheckNewMailA(szMailbox,pulPending);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pulPending;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteOpenOneMsgDownloadPipeA(
    PRPC_MESSAGE _pRpcMessage )
{
    long _M167;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pPipeNumber;
    unsigned char __RPC_FAR *szMailbox;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    pPipeNumber = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[162] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        pPipeNumber = &_M167;
        
        _RetVal = RemoteOpenOneMsgDownloadPipeA(szMailbox,pPipeNumber);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pPipeNumber;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteGetRecipientPropsA(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M168;
    unsigned long _M169;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwObjID;
    unsigned long __RPC_FAR *pdwManagerID;
    unsigned long __RPC_FAR *pdwUserType;
    unsigned char __RPC_FAR *szAltPhone;
    unsigned char __RPC_FAR *szComments;
    unsigned char __RPC_FAR *szCompany;
    unsigned char __RPC_FAR *szDepartment;
    unsigned char __RPC_FAR *szFax;
    unsigned char __RPC_FAR *szFullName;
    unsigned char __RPC_FAR *szJobTitle;
    unsigned char __RPC_FAR *szMailboxName;
    unsigned char __RPC_FAR *szManagerAlias;
    unsigned char __RPC_FAR *szManagerName;
    unsigned char __RPC_FAR *szOffice;
    unsigned char __RPC_FAR *szPhone;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    pdwUserType = 0;
    szMailboxName = 0;
    szFullName = 0;
    szJobTitle = 0;
    szOffice = 0;
    szPhone = 0;
    szAltPhone = 0;
    szFax = 0;
    szComments = 0;
    szCompany = 0;
    szDepartment = 0;
    szManagerName = 0;
    szManagerAlias = 0;
    pdwManagerID = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[172] );
        
        dwObjID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pdwUserType = &_M168;
        szMailboxName = _StubMsg.pfnAllocate((16 + 1) * 1);
        szFullName = _StubMsg.pfnAllocate((32 + 1) * 1);
        szJobTitle = _StubMsg.pfnAllocate((32 + 1) * 1);
        szOffice = _StubMsg.pfnAllocate((32 + 1) * 1);
        szPhone = _StubMsg.pfnAllocate((12 + 1) * 1);
        szAltPhone = _StubMsg.pfnAllocate((12 + 1) * 1);
        szFax = _StubMsg.pfnAllocate((12 + 1) * 1);
        szComments = _StubMsg.pfnAllocate((79 + 1) * 1);
        szCompany = _StubMsg.pfnAllocate((32 + 1) * 1);
        szDepartment = _StubMsg.pfnAllocate((32 + 1) * 1);
        szManagerName = _StubMsg.pfnAllocate((32 + 1) * 1);
        szManagerAlias = _StubMsg.pfnAllocate((16 + 1) * 1);
        pdwManagerID = &_M169;
        
        _RetVal = RemoteGetRecipientPropsA(
                                   dwObjID,
                                   pdwUserType,
                                   szMailboxName,
                                   szFullName,
                                   szJobTitle,
                                   szOffice,
                                   szPhone,
                                   szAltPhone,
                                   szFax,
                                   szComments,
                                   szCompany,
                                   szDepartment,
                                   szManagerName,
                                   szManagerAlias,
                                   pdwManagerID);
        
        _StubMsg.BufferLength = 4U + 12U + 13U + 13U + 13U + 13U + 13U + 13U + 13U + 13U + 13U + 13U + 13U + 11U + 7U;
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailboxName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[46] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[56] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szJobTitle,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[66] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szOffice,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[76] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szPhone,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[86] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szAltPhone,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[96] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szFax,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[106] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szComments,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[116] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szCompany,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[126] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szDepartment,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[136] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szManagerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[146] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szManagerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[156] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwUserType;
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailboxName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[46] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szFullName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[56] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szJobTitle,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[66] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szOffice,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[76] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szPhone,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[86] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szAltPhone,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[96] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szFax,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[106] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szComments,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[116] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szCompany,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[126] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szDepartment,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[136] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szManagerName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[146] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szManagerAlias,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[156] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwManagerID;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 16 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szMailboxName,
                        &__MIDLFormatString.Format[42] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szFullName,
                        &__MIDLFormatString.Format[52] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szJobTitle,
                        &__MIDLFormatString.Format[62] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szOffice,
                        &__MIDLFormatString.Format[72] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szPhone,
                        &__MIDLFormatString.Format[82] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szAltPhone,
                        &__MIDLFormatString.Format[92] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szFax,
                        &__MIDLFormatString.Format[102] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szComments,
                        &__MIDLFormatString.Format[112] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szCompany,
                        &__MIDLFormatString.Format[122] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szDepartment,
                        &__MIDLFormatString.Format[132] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szManagerName,
                        &__MIDLFormatString.Format[142] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szManagerAlias,
                        &__MIDLFormatString.Format[152] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteGetDistListPropsA(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M170;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwObjID;
    unsigned long __RPC_FAR *pdwContentCount;
    unsigned char __RPC_FAR *szComments;
    unsigned char __RPC_FAR *szDLAlias;
    unsigned char __RPC_FAR *szDLFullName;
    unsigned char __RPC_FAR *szOwnerAlias;
    unsigned char __RPC_FAR *szOwnerName;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szDLAlias = 0;
    szDLFullName = 0;
    pdwContentCount = 0;
    szOwnerAlias = 0;
    szOwnerName = 0;
    szComments = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[232] );
        
        dwObjID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        szDLAlias = _StubMsg.pfnAllocate((16 + 1) * 1);
        szDLFullName = _StubMsg.pfnAllocate((32 + 1) * 1);
        pdwContentCount = &_M170;
        szOwnerAlias = _StubMsg.pfnAllocate((16 + 1) * 1);
        szOwnerName = _StubMsg.pfnAllocate((32 + 1) * 1);
        szComments = _StubMsg.pfnAllocate((79 + 1) * 1);
        
        _RetVal = RemoteGetDistListPropsA(
                                  dwObjID,
                                  szDLAlias,
                                  szDLFullName,
                                  pdwContentCount,
                                  szOwnerAlias,
                                  szOwnerName,
                                  szComments);
        
        _StubMsg.BufferLength = 12U + 13U + 11U + 13U + 13U + 13U + 11U;
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szDLAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[166] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szDLFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[176] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szOwnerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[186] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szOwnerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[196] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szComments,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[206] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szDLAlias,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[166] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szDLFullName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[176] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwContentCount;
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szOwnerAlias,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[186] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szOwnerName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[196] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szComments,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[206] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 16 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szDLAlias,
                        &__MIDLFormatString.Format[162] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szDLFullName,
                        &__MIDLFormatString.Format[172] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szOwnerAlias,
                        &__MIDLFormatString.Format[182] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szOwnerName,
                        &__MIDLFormatString.Format[192] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szComments,
                        &__MIDLFormatString.Format[202] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteChangePasswordW(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    wchar_t __RPC_FAR *szMailbox;
    wchar_t __RPC_FAR *szNewPassword;
    wchar_t __RPC_FAR *szOldPassword;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    szOldPassword = 0;
    szNewPassword = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[260] );
        
        szMailbox = ( wchar_t __RPC_FAR * )_StubMsg.Buffer;
        _StubMsg.Buffer += sizeof( wchar_t  );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOldPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szNewPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        
        _RetVal = RemoteChangePasswordW(
                                szMailbox,
                                szOldPassword,
                                szNewPassword);
        
        _StubMsg.BufferLength = 4U;
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteLogonMailBoxW(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M171;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pdwMailboxID;
    wchar_t __RPC_FAR *szFullName;
    wchar_t __RPC_FAR *szMailbox;
    wchar_t __RPC_FAR *szPassword;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    szPassword = 0;
    szFullName = 0;
    pdwMailboxID = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[274] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        szFullName = _StubMsg.pfnAllocate((32 + 1) * 2);
        pdwMailboxID = &_M171;
        
        _RetVal = RemoteLogonMailBoxW(
                              szMailbox,
                              szPassword,
                              szFullName,
                              pdwMailboxID);
        
        _StubMsg.BufferLength = 12U + 10U + 7U;
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[224] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szFullName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[224] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwMailboxID;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szFullName,
                        &__MIDLFormatString.Format[220] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteLogonMailBoxAndSetNotifW(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M172;
    unsigned long _M173;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pdwMailboxID;
    unsigned long __RPC_FAR *pulConnectionID;
    wchar_t __RPC_FAR *szComputerName;
    wchar_t __RPC_FAR *szFullName;
    wchar_t __RPC_FAR *szMailbox;
    wchar_t __RPC_FAR *szPassword;
    unsigned long ulNotifMask;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    szPassword = 0;
    szFullName = 0;
    pdwMailboxID = 0;
    szComputerName = 0;
    pulConnectionID = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[292] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        ulNotifMask = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        szFullName = _StubMsg.pfnAllocate((32 + 1) * 2);
        pdwMailboxID = &_M172;
        pulConnectionID = &_M173;
        
        _RetVal = RemoteLogonMailBoxAndSetNotifW(
                                         szMailbox,
                                         szPassword,
                                         szFullName,
                                         pdwMailboxID,
                                         szComputerName,
                                         ulNotifMask,
                                         pulConnectionID);
        
        _StubMsg.BufferLength = 12U + 10U + 7U + 7U;
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[234] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szFullName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[234] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwMailboxID;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pulConnectionID;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szFullName,
                        &__MIDLFormatString.Format[230] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteTerminateNotifW(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    wchar_t __RPC_FAR *szComputerName;
    unsigned long ulConnectionID;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szComputerName = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[320] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        ulConnectionID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        _RetVal = RemoteTerminateNotifW(szComputerName,ulConnectionID);
        
        _StubMsg.BufferLength = 4U;
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteValidateNotifW(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M174;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pulConnectionID;
    wchar_t __RPC_FAR *szComputerName;
    wchar_t __RPC_FAR *szMailboxName;
    unsigned long ulNotifMask;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szComputerName = 0;
    szMailboxName = 0;
    pulConnectionID = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[328] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailboxName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        ulNotifMask = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pulConnectionID = &_M174;
        
        _RetVal = RemoteValidateNotifW(
                               szComputerName,
                               szMailboxName,
                               ulNotifMask,
                               pulConnectionID);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pulConnectionID;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteOpenMsgUploadPipeW(
    PRPC_MESSAGE _pRpcMessage )
{
    long _M175;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pPipeNumber;
    unsigned char __RPC_FAR *szCookie;
    wchar_t __RPC_FAR *szSenderMailbox;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szSenderMailbox = 0;
    pPipeNumber = 0;
    szCookie = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[344] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szSenderMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        pPipeNumber = &_M175;
        szCookie = _StubMsg.pfnAllocate((32 + 1) * 1);
        
        _RetVal = RemoteOpenMsgUploadPipeW(
                                   szSenderMailbox,
                                   pPipeNumber,
                                   szCookie);
        
        _StubMsg.BufferLength = 4U + 12U + 11U;
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szCookie,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[244] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pPipeNumber;
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szCookie,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[244] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szCookie,
                        &__MIDLFormatString.Format[240] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteSendMsgToAccountW(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    wchar_t __RPC_FAR *szCookie;
    wchar_t __RPC_FAR *szHeaderInfo;
    wchar_t __RPC_FAR *szRecipAccount;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szRecipAccount = 0;
    szHeaderInfo = 0;
    szCookie = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[358] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szRecipAccount,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szHeaderInfo,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szCookie,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        
        _RetVal = RemoteSendMsgToAccountW(
                                  szRecipAccount,
                                  szHeaderInfo,
                                  szCookie);
        
        _StubMsg.BufferLength = 4U;
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteOpenMsgDownloadPipeW(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M176;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pPipeNumber;
    wchar_t __RPC_FAR *szMailbox;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    pPipeNumber = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[372] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        pPipeNumber = &_M176;
        
        _RetVal = RemoteOpenMsgDownloadPipeW(szMailbox,pPipeNumber);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pPipeNumber;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteOpenHeaderDownloadPipeW(
    PRPC_MESSAGE _pRpcMessage )
{
    long _M177;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pPipeNumber;
    wchar_t __RPC_FAR *szMailbox;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    pPipeNumber = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[372] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        pPipeNumber = &_M177;
        
        _RetVal = RemoteOpenHeaderDownloadPipeW(szMailbox,pPipeNumber);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pPipeNumber;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteCheckNewMailW(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M178;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pulPending;
    wchar_t __RPC_FAR *szMailbox;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    pulPending = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[372] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        pulPending = &_M178;
        
        _RetVal = RemoteCheckNewMailW(szMailbox,pulPending);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pulPending;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteOpenOneMsgDownloadPipeW(
    PRPC_MESSAGE _pRpcMessage )
{
    long _M179;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pPipeNumber;
    wchar_t __RPC_FAR *szMailbox;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szMailbox = 0;
    pPipeNumber = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[372] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218],
                                       (unsigned char)0 );
        
        pPipeNumber = &_M179;
        
        _RetVal = RemoteOpenOneMsgDownloadPipeW(szMailbox,pPipeNumber);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = *pPipeNumber;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteGetRecipientPropsW(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M180;
    unsigned long _M181;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwObjID;
    unsigned long __RPC_FAR *pdwManagerID;
    unsigned long __RPC_FAR *pdwUserType;
    wchar_t __RPC_FAR *szAltPhone;
    wchar_t __RPC_FAR *szComments;
    wchar_t __RPC_FAR *szCompany;
    wchar_t __RPC_FAR *szDepartment;
    wchar_t __RPC_FAR *szFax;
    wchar_t __RPC_FAR *szFullName;
    wchar_t __RPC_FAR *szJobTitle;
    wchar_t __RPC_FAR *szMailboxName;
    wchar_t __RPC_FAR *szManagerAlias;
    wchar_t __RPC_FAR *szManagerName;
    wchar_t __RPC_FAR *szOffice;
    wchar_t __RPC_FAR *szPhone;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    pdwUserType = 0;
    szMailboxName = 0;
    szFullName = 0;
    szJobTitle = 0;
    szOffice = 0;
    szPhone = 0;
    szAltPhone = 0;
    szFax = 0;
    szComments = 0;
    szCompany = 0;
    szDepartment = 0;
    szManagerName = 0;
    szManagerAlias = 0;
    pdwManagerID = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[382] );
        
        dwObjID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pdwUserType = &_M180;
        szMailboxName = _StubMsg.pfnAllocate((16 + 1) * 2);
        szFullName = _StubMsg.pfnAllocate((32 + 1) * 2);
        szJobTitle = _StubMsg.pfnAllocate((32 + 1) * 2);
        szOffice = _StubMsg.pfnAllocate((32 + 1) * 2);
        szPhone = _StubMsg.pfnAllocate((12 + 1) * 2);
        szAltPhone = _StubMsg.pfnAllocate((12 + 1) * 2);
        szFax = _StubMsg.pfnAllocate((12 + 1) * 2);
        szComments = _StubMsg.pfnAllocate((79 + 1) * 2);
        szCompany = _StubMsg.pfnAllocate((32 + 1) * 2);
        szDepartment = _StubMsg.pfnAllocate((32 + 1) * 2);
        szManagerName = _StubMsg.pfnAllocate((32 + 1) * 2);
        szManagerAlias = _StubMsg.pfnAllocate((16 + 1) * 2);
        pdwManagerID = &_M181;
        
        _RetVal = RemoteGetRecipientPropsW(
                                   dwObjID,
                                   pdwUserType,
                                   szMailboxName,
                                   szFullName,
                                   szJobTitle,
                                   szOffice,
                                   szPhone,
                                   szAltPhone,
                                   szFax,
                                   szComments,
                                   szCompany,
                                   szDepartment,
                                   szManagerName,
                                   szManagerAlias,
                                   pdwManagerID);
        
        _StubMsg.BufferLength = 4U + 12U + 14U + 14U + 14U + 14U + 14U + 14U + 14U + 14U + 14U + 14U + 14U + 10U + 7U;
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailboxName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[254] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[264] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szJobTitle,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[274] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szOffice,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[284] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szPhone,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[294] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szAltPhone,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[304] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szFax,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[314] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szComments,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[324] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szCompany,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[334] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szDepartment,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[344] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szManagerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[354] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szManagerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[364] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwUserType;
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailboxName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[254] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szFullName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[264] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szJobTitle,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[274] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szOffice,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[284] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szPhone,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[294] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szAltPhone,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[304] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szFax,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[314] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szComments,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[324] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szCompany,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[334] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szDepartment,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[344] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szManagerName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[354] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szManagerAlias,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[364] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwManagerID;
        
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 16 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szMailboxName,
                        &__MIDLFormatString.Format[250] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szFullName,
                        &__MIDLFormatString.Format[260] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szJobTitle,
                        &__MIDLFormatString.Format[270] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szOffice,
                        &__MIDLFormatString.Format[280] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szPhone,
                        &__MIDLFormatString.Format[290] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szAltPhone,
                        &__MIDLFormatString.Format[300] );
        
        _StubMsg.MaxCount = 12 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szFax,
                        &__MIDLFormatString.Format[310] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szComments,
                        &__MIDLFormatString.Format[320] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szCompany,
                        &__MIDLFormatString.Format[330] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szDepartment,
                        &__MIDLFormatString.Format[340] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szManagerName,
                        &__MIDLFormatString.Format[350] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szManagerAlias,
                        &__MIDLFormatString.Format[360] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSREM_RemoteGetDistListPropsW(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M182;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwObjID;
    unsigned long __RPC_FAR *pdwContentCount;
    wchar_t __RPC_FAR *szComments;
    wchar_t __RPC_FAR *szDLAlias;
    wchar_t __RPC_FAR *szDLFullName;
    wchar_t __RPC_FAR *szOwnerAlias;
    wchar_t __RPC_FAR *szOwnerName;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSREM_StubDesc);
    
    szDLAlias = 0;
    szDLFullName = 0;
    pdwContentCount = 0;
    szOwnerAlias = 0;
    szOwnerName = 0;
    szComments = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[442] );
        
        dwObjID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        szDLAlias = _StubMsg.pfnAllocate((16 + 1) * 2);
        szDLFullName = _StubMsg.pfnAllocate((32 + 1) * 2);
        pdwContentCount = &_M182;
        szOwnerAlias = _StubMsg.pfnAllocate((16 + 1) * 2);
        szOwnerName = _StubMsg.pfnAllocate((32 + 1) * 2);
        szComments = _StubMsg.pfnAllocate((79 + 1) * 2);
        
        _RetVal = RemoteGetDistListPropsW(
                                  dwObjID,
                                  szDLAlias,
                                  szDLFullName,
                                  pdwContentCount,
                                  szOwnerAlias,
                                  szOwnerName,
                                  szComments);
        
        _StubMsg.BufferLength = 12U + 14U + 10U + 14U + 14U + 14U + 10U;
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szDLAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[374] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szDLFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[384] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szOwnerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[394] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szOwnerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[404] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szComments,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[414] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szDLAlias,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[374] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szDLFullName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[384] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwContentCount;
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szOwnerAlias,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[394] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szOwnerName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[404] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szComments,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[414] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 16 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szDLAlias,
                        &__MIDLFormatString.Format[370] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szDLFullName,
                        &__MIDLFormatString.Format[380] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szOwnerAlias,
                        &__MIDLFormatString.Format[390] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szOwnerName,
                        &__MIDLFormatString.Format[400] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szComments,
                        &__MIDLFormatString.Format[410] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


static const MIDL_STUB_DESC WINDSREM_StubDesc = 
    {
    (void __RPC_FAR *)& WINDSREM___RpcServerInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    0,
    0,
    0,
    0,
    0,
    __MIDLFormatString.Format,
    0, /* -error bounds_check flag */
    0x10001, /* Ndr library version */
    0,
    0x2000066, /* MIDL Version 2.0.102 */
    0
    };

static RPC_DISPATCH_FUNCTION WINDSREM_table[] =
    {
    WINDSREM_RemoteIsServerRunning,
    WINDSREM_RemoteGetAllAccounts,
    WINDSREM_RemoteFinishUpload,
    WINDSREM_RemoteGetContainerProps,
    WINDSREM_RemoteGetContainerRecipients,
    WINDSREM_RemoteGetPublicFoldersList,
    WINDSREM_RemoteGetPublicFolderMessages,
    WINDSREM_RemoteChangePasswordA,
    WINDSREM_RemoteLogonMailBoxA,
    WINDSREM_RemoteLogonMailBoxAndSetNotifA,
    WINDSREM_RemoteTerminateNotifA,
    WINDSREM_RemoteValidateNotifA,
    WINDSREM_RemoteOpenMsgUploadPipeA,
    WINDSREM_RemoteSendMsgToAccountA,
    WINDSREM_RemoteOpenMsgDownloadPipeA,
    WINDSREM_RemoteOpenHeaderDownloadPipeA,
    WINDSREM_RemoteCheckNewMailA,
    WINDSREM_RemoteOpenOneMsgDownloadPipeA,
    WINDSREM_RemoteGetRecipientPropsA,
    WINDSREM_RemoteGetDistListPropsA,
    WINDSREM_RemoteChangePasswordW,
    WINDSREM_RemoteLogonMailBoxW,
    WINDSREM_RemoteLogonMailBoxAndSetNotifW,
    WINDSREM_RemoteTerminateNotifW,
    WINDSREM_RemoteValidateNotifW,
    WINDSREM_RemoteOpenMsgUploadPipeW,
    WINDSREM_RemoteSendMsgToAccountW,
    WINDSREM_RemoteOpenMsgDownloadPipeW,
    WINDSREM_RemoteOpenHeaderDownloadPipeW,
    WINDSREM_RemoteCheckNewMailW,
    WINDSREM_RemoteOpenOneMsgDownloadPipeW,
    WINDSREM_RemoteGetRecipientPropsW,
    WINDSREM_RemoteGetDistListPropsW,
    0
    };
RPC_DISPATCH_TABLE WINDSREM_v1_6_DispatchTable = 
    {
    33,
    WINDSREM_table
    };

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_FORMAT_STRING __MIDLProcFormatString =
    {
        0,
        {
            0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/*  2 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/*  4 */    NdrFcShort( 0x0 ),  /* Type Offset=0 */
/*  6 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/*  8 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 10 */    NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 12 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 14 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 16 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 18 */    NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 20 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 22 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 24 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 26 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 28 */    NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 30 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 32 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x6,        /* FC_SHORT */
/* 34 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 36 */    NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 38 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 40 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x6,        /* FC_SHORT */
/* 42 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 44 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 46 */    NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 48 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 50 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 52 */    NdrFcShort( 0x8 ),  /* Type Offset=8 */
/* 54 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 56 */    NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 58 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 60 */    NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 62 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 64 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 66 */    NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 68 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 70 */    NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 72 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 74 */    NdrFcShort( 0xc ),  /* Type Offset=12 */
/* 76 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 78 */    NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 80 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 82 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 84 */    NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 86 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 88 */    NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 90 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 92 */    NdrFcShort( 0x16 ), /* Type Offset=22 */
/* 94 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 96 */    NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 98 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 100 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 102 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 104 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 106 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 108 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 110 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 112 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 114 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 116 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 118 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 120 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 122 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 124 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 126 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 128 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 130 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 132 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 134 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 136 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 138 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 140 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 142 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 144 */   NdrFcShort( 0x20 ), /* Type Offset=32 */
/* 146 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 148 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 150 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 152 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 154 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 156 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 158 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 160 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 162 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 164 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 166 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 168 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 170 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 172 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 174 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 176 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 178 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 180 */   NdrFcShort( 0x2a ), /* Type Offset=42 */
/* 182 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 184 */   NdrFcShort( 0x34 ), /* Type Offset=52 */
/* 186 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 188 */   NdrFcShort( 0x3e ), /* Type Offset=62 */
/* 190 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 192 */   NdrFcShort( 0x48 ), /* Type Offset=72 */
/* 194 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 196 */   NdrFcShort( 0x52 ), /* Type Offset=82 */
/* 198 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 200 */   NdrFcShort( 0x5c ), /* Type Offset=92 */
/* 202 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 204 */   NdrFcShort( 0x66 ), /* Type Offset=102 */
/* 206 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 208 */   NdrFcShort( 0x70 ), /* Type Offset=112 */
/* 210 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 212 */   NdrFcShort( 0x7a ), /* Type Offset=122 */
/* 214 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 216 */   NdrFcShort( 0x84 ), /* Type Offset=132 */
/* 218 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 220 */   NdrFcShort( 0x8e ), /* Type Offset=142 */
/* 222 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 224 */   NdrFcShort( 0x98 ), /* Type Offset=152 */
/* 226 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 228 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 230 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 232 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 234 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 236 */   NdrFcShort( 0xa2 ), /* Type Offset=162 */
/* 238 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 240 */   NdrFcShort( 0xac ), /* Type Offset=172 */
/* 242 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 244 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 246 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 248 */   NdrFcShort( 0xb6 ), /* Type Offset=182 */
/* 250 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 252 */   NdrFcShort( 0xc0 ), /* Type Offset=192 */
/* 254 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 256 */   NdrFcShort( 0xca ), /* Type Offset=202 */
/* 258 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 260 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 262 */   NdrFcShort( 0xd4 ), /* Type Offset=212 */
/* 264 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 266 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 268 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 270 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 272 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 274 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 276 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 278 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 280 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 282 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 284 */   NdrFcShort( 0xdc ), /* Type Offset=220 */
/* 286 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 288 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 290 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 292 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 294 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 296 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 298 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 300 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 302 */   NdrFcShort( 0xe6 ), /* Type Offset=230 */
/* 304 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 306 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 308 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 310 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 312 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 314 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 316 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 318 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 320 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 322 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 324 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 326 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 328 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 330 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 332 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 334 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 336 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 338 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 340 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 342 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 344 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 346 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 348 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 350 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 352 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 354 */   NdrFcShort( 0xf0 ), /* Type Offset=240 */
/* 356 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 358 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 360 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 362 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 364 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 366 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 368 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 370 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 372 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 374 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 376 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 378 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 380 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 382 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 384 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 386 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 388 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 390 */   NdrFcShort( 0xfa ), /* Type Offset=250 */
/* 392 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 394 */   NdrFcShort( 0x104 ),    /* Type Offset=260 */
/* 396 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 398 */   NdrFcShort( 0x10e ),    /* Type Offset=270 */
/* 400 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 402 */   NdrFcShort( 0x118 ),    /* Type Offset=280 */
/* 404 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 406 */   NdrFcShort( 0x122 ),    /* Type Offset=290 */
/* 408 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 410 */   NdrFcShort( 0x12c ),    /* Type Offset=300 */
/* 412 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 414 */   NdrFcShort( 0x136 ),    /* Type Offset=310 */
/* 416 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 418 */   NdrFcShort( 0x140 ),    /* Type Offset=320 */
/* 420 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 422 */   NdrFcShort( 0x14a ),    /* Type Offset=330 */
/* 424 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 426 */   NdrFcShort( 0x154 ),    /* Type Offset=340 */
/* 428 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 430 */   NdrFcShort( 0x15e ),    /* Type Offset=350 */
/* 432 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 434 */   NdrFcShort( 0x168 ),    /* Type Offset=360 */
/* 436 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 438 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 440 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 442 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 444 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 446 */   NdrFcShort( 0x172 ),    /* Type Offset=370 */
/* 448 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 450 */   NdrFcShort( 0x17c ),    /* Type Offset=380 */
/* 452 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 454 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 456 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 458 */   NdrFcShort( 0x186 ),    /* Type Offset=390 */
/* 460 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 462 */   NdrFcShort( 0x190 ),    /* Type Offset=400 */
/* 464 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 466 */   NdrFcShort( 0x19a ),    /* Type Offset=410 */
/* 468 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */

            0x0
        }
    };

static const MIDL_FORMAT_STRING __MIDLFormatString =
    {
        0,
        {
            0x11, 0xc,  /* FC_RP [alloced_on_stack] [simple_pointer] */
/*  2 */    0x8,        /* FC_LONG */
            0x5c,       /* FC_PAD */
/*  4 */    
            0x11, 0x8,  /* FC_RP [simple_pointer] */
/*  6 */    
            0x22,       /* FC_C_CSTRING */
            0x5c,       /* FC_PAD */
/*  8 */    
            0x11, 0x8,  /* FC_RP [simple_pointer] */
/* 10 */    0x2,        /* FC_CHAR */
            0x5c,       /* FC_PAD */
/* 12 */    
            0x11, 0x0,  /* FC_RP */
/* 14 */    NdrFcShort( 0x2 ),  /* Offset= 2 (16) */
/* 16 */    
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 18 */    0x40,       /* 64 */
            0x0,        /* 0 */
/* 20 */    NdrFcShort( 0x21 ), /* 33 */
/* 22 */    
            0x11, 0x0,  /* FC_RP */
/* 24 */    NdrFcShort( 0x2 ),  /* Offset= 2 (26) */
/* 26 */    
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 28 */    0x40,       /* 64 */
            0x0,        /* 0 */
/* 30 */    NdrFcShort( 0x21 ), /* 33 */
/* 32 */    
            0x11, 0x0,  /* FC_RP */
/* 34 */    NdrFcShort( 0x2 ),  /* Offset= 2 (36) */
/* 36 */    
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 38 */    0x40,       /* 64 */
            0x0,        /* 0 */
/* 40 */    NdrFcShort( 0x21 ), /* 33 */
/* 42 */    
            0x11, 0x0,  /* FC_RP */
/* 44 */    NdrFcShort( 0x2 ),  /* Offset= 2 (46) */
/* 46 */    
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 48 */    0x40,       /* 64 */
            0x0,        /* 0 */
/* 50 */    NdrFcShort( 0x11 ), /* 17 */
/* 52 */    
            0x11, 0x0,  /* FC_RP */
/* 54 */    NdrFcShort( 0x2 ),  /* Offset= 2 (56) */
/* 56 */    
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 58 */    0x40,       /* 64 */
            0x0,        /* 0 */
/* 60 */    NdrFcShort( 0x21 ), /* 33 */
/* 62 */    
            0x11, 0x0,  /* FC_RP */
/* 64 */    NdrFcShort( 0x2 ),  /* Offset= 2 (66) */
/* 66 */    
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 68 */    0x40,       /* 64 */
            0x0,        /* 0 */
/* 70 */    NdrFcShort( 0x21 ), /* 33 */
/* 72 */    
            0x11, 0x0,  /* FC_RP */
/* 74 */    NdrFcShort( 0x2 ),  /* Offset= 2 (76) */
/* 76 */    
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 78 */    0x40,       /* 64 */
            0x0,        /* 0 */
/* 80 */    NdrFcShort( 0x21 ), /* 33 */
/* 82 */    
            0x11, 0x0,  /* FC_RP */
/* 84 */    NdrFcShort( 0x2 ),  /* Offset= 2 (86) */
/* 86 */    
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 88 */    0x40,       /* 64 */
            0x0,        /* 0 */
/* 90 */    NdrFcShort( 0xd ),  /* 13 */
/* 92 */    
            0x11, 0x0,  /* FC_RP */
/* 94 */    NdrFcShort( 0x2 ),  /* Offset= 2 (96) */
/* 96 */    
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 98 */    0x40,       /* 64 */
            0x0,        /* 0 */
/* 100 */   NdrFcShort( 0xd ),  /* 13 */
/* 102 */   
            0x11, 0x0,  /* FC_RP */
/* 104 */   NdrFcShort( 0x2 ),  /* Offset= 2 (106) */
/* 106 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 108 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 110 */   NdrFcShort( 0xd ),  /* 13 */
/* 112 */   
            0x11, 0x0,  /* FC_RP */
/* 114 */   NdrFcShort( 0x2 ),  /* Offset= 2 (116) */
/* 116 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 118 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 120 */   NdrFcShort( 0x50 ), /* 80 */
/* 122 */   
            0x11, 0x0,  /* FC_RP */
/* 124 */   NdrFcShort( 0x2 ),  /* Offset= 2 (126) */
/* 126 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 128 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 130 */   NdrFcShort( 0x21 ), /* 33 */
/* 132 */   
            0x11, 0x0,  /* FC_RP */
/* 134 */   NdrFcShort( 0x2 ),  /* Offset= 2 (136) */
/* 136 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 138 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 140 */   NdrFcShort( 0x21 ), /* 33 */
/* 142 */   
            0x11, 0x0,  /* FC_RP */
/* 144 */   NdrFcShort( 0x2 ),  /* Offset= 2 (146) */
/* 146 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 148 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 150 */   NdrFcShort( 0x21 ), /* 33 */
/* 152 */   
            0x11, 0x0,  /* FC_RP */
/* 154 */   NdrFcShort( 0x2 ),  /* Offset= 2 (156) */
/* 156 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 158 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 160 */   NdrFcShort( 0x11 ), /* 17 */
/* 162 */   
            0x11, 0x0,  /* FC_RP */
/* 164 */   NdrFcShort( 0x2 ),  /* Offset= 2 (166) */
/* 166 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 168 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 170 */   NdrFcShort( 0x11 ), /* 17 */
/* 172 */   
            0x11, 0x0,  /* FC_RP */
/* 174 */   NdrFcShort( 0x2 ),  /* Offset= 2 (176) */
/* 176 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 178 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 180 */   NdrFcShort( 0x21 ), /* 33 */
/* 182 */   
            0x11, 0x0,  /* FC_RP */
/* 184 */   NdrFcShort( 0x2 ),  /* Offset= 2 (186) */
/* 186 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 188 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 190 */   NdrFcShort( 0x11 ), /* 17 */
/* 192 */   
            0x11, 0x0,  /* FC_RP */
/* 194 */   NdrFcShort( 0x2 ),  /* Offset= 2 (196) */
/* 196 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 198 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 200 */   NdrFcShort( 0x21 ), /* 33 */
/* 202 */   
            0x11, 0x0,  /* FC_RP */
/* 204 */   NdrFcShort( 0x2 ),  /* Offset= 2 (206) */
/* 206 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 208 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 210 */   NdrFcShort( 0x50 ), /* 80 */
/* 212 */   
            0x11, 0x8,  /* FC_RP [simple_pointer] */
/* 214 */   0x5,        /* FC_WCHAR */
            0x5c,       /* FC_PAD */
/* 216 */   
            0x11, 0x8,  /* FC_RP [simple_pointer] */
/* 218 */   
            0x25,       /* FC_C_WSTRING */
            0x5c,       /* FC_PAD */
/* 220 */   
            0x11, 0x0,  /* FC_RP */
/* 222 */   NdrFcShort( 0x2 ),  /* Offset= 2 (224) */
/* 224 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 226 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 228 */   NdrFcShort( 0x21 ), /* 33 */
/* 230 */   
            0x11, 0x0,  /* FC_RP */
/* 232 */   NdrFcShort( 0x2 ),  /* Offset= 2 (234) */
/* 234 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 236 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 238 */   NdrFcShort( 0x21 ), /* 33 */
/* 240 */   
            0x11, 0x0,  /* FC_RP */
/* 242 */   NdrFcShort( 0x2 ),  /* Offset= 2 (244) */
/* 244 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 246 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 248 */   NdrFcShort( 0x21 ), /* 33 */
/* 250 */   
            0x11, 0x0,  /* FC_RP */
/* 252 */   NdrFcShort( 0x2 ),  /* Offset= 2 (254) */
/* 254 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 256 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 258 */   NdrFcShort( 0x11 ), /* 17 */
/* 260 */   
            0x11, 0x0,  /* FC_RP */
/* 262 */   NdrFcShort( 0x2 ),  /* Offset= 2 (264) */
/* 264 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 266 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 268 */   NdrFcShort( 0x21 ), /* 33 */
/* 270 */   
            0x11, 0x0,  /* FC_RP */
/* 272 */   NdrFcShort( 0x2 ),  /* Offset= 2 (274) */
/* 274 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 276 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 278 */   NdrFcShort( 0x21 ), /* 33 */
/* 280 */   
            0x11, 0x0,  /* FC_RP */
/* 282 */   NdrFcShort( 0x2 ),  /* Offset= 2 (284) */
/* 284 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 286 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 288 */   NdrFcShort( 0x21 ), /* 33 */
/* 290 */   
            0x11, 0x0,  /* FC_RP */
/* 292 */   NdrFcShort( 0x2 ),  /* Offset= 2 (294) */
/* 294 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 296 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 298 */   NdrFcShort( 0xd ),  /* 13 */
/* 300 */   
            0x11, 0x0,  /* FC_RP */
/* 302 */   NdrFcShort( 0x2 ),  /* Offset= 2 (304) */
/* 304 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 306 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 308 */   NdrFcShort( 0xd ),  /* 13 */
/* 310 */   
            0x11, 0x0,  /* FC_RP */
/* 312 */   NdrFcShort( 0x2 ),  /* Offset= 2 (314) */
/* 314 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 316 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 318 */   NdrFcShort( 0xd ),  /* 13 */
/* 320 */   
            0x11, 0x0,  /* FC_RP */
/* 322 */   NdrFcShort( 0x2 ),  /* Offset= 2 (324) */
/* 324 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 326 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 328 */   NdrFcShort( 0x50 ), /* 80 */
/* 330 */   
            0x11, 0x0,  /* FC_RP */
/* 332 */   NdrFcShort( 0x2 ),  /* Offset= 2 (334) */
/* 334 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 336 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 338 */   NdrFcShort( 0x21 ), /* 33 */
/* 340 */   
            0x11, 0x0,  /* FC_RP */
/* 342 */   NdrFcShort( 0x2 ),  /* Offset= 2 (344) */
/* 344 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 346 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 348 */   NdrFcShort( 0x21 ), /* 33 */
/* 350 */   
            0x11, 0x0,  /* FC_RP */
/* 352 */   NdrFcShort( 0x2 ),  /* Offset= 2 (354) */
/* 354 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 356 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 358 */   NdrFcShort( 0x21 ), /* 33 */
/* 360 */   
            0x11, 0x0,  /* FC_RP */
/* 362 */   NdrFcShort( 0x2 ),  /* Offset= 2 (364) */
/* 364 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 366 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 368 */   NdrFcShort( 0x11 ), /* 17 */
/* 370 */   
            0x11, 0x0,  /* FC_RP */
/* 372 */   NdrFcShort( 0x2 ),  /* Offset= 2 (374) */
/* 374 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 376 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 378 */   NdrFcShort( 0x11 ), /* 17 */
/* 380 */   
            0x11, 0x0,  /* FC_RP */
/* 382 */   NdrFcShort( 0x2 ),  /* Offset= 2 (384) */
/* 384 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 386 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 388 */   NdrFcShort( 0x21 ), /* 33 */
/* 390 */   
            0x11, 0x0,  /* FC_RP */
/* 392 */   NdrFcShort( 0x2 ),  /* Offset= 2 (394) */
/* 394 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 396 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 398 */   NdrFcShort( 0x11 ), /* 17 */
/* 400 */   
            0x11, 0x0,  /* FC_RP */
/* 402 */   NdrFcShort( 0x2 ),  /* Offset= 2 (404) */
/* 404 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 406 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 408 */   NdrFcShort( 0x21 ), /* 33 */
/* 410 */   
            0x11, 0x0,  /* FC_RP */
/* 412 */   NdrFcShort( 0x2 ),  /* Offset= 2 (414) */
/* 414 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 416 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 418 */   NdrFcShort( 0x50 ), /* 80 */

            0x0
        }
    };
