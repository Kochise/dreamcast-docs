/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 2.00.0102 */
/* at Wed Sep 27 11:30:53 1995
 */
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "wdsadm.h"

extern const MIDL_FORMAT_STRING __MIDLFormatString;

extern const MIDL_FORMAT_STRING __MIDLProcFormatString;

extern RPC_DISPATCH_TABLE WINDSADM_v1_0_DispatchTable;

static const RPC_SERVER_INTERFACE WINDSADM___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0x2BC66860,0xE91E,0x11CE,{0xB2,0xF0,0x00,0xAA,0x00,0x51,0x0E,0x3B}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &WINDSADM_v1_0_DispatchTable,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE WINDSADM_v1_0_s_ifspec = (RPC_IF_HANDLE)& WINDSADM___RpcServerInterface;

extern const MIDL_STUB_DESC WINDSADM_StubDesc;

void __RPC_STUB
WINDSADM_RemoteAdmIsServerRunning(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    RpcTryFinally
        {
        
        _RetVal = RemoteAdmIsServerRunning();
        
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
WINDSADM_RemoteAdmDeleteObject(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwObjID;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[2] );
        
        dwObjID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        _RetVal = RemoteAdmDeleteObject(dwObjID);
        
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
WINDSADM_RemoteAdmGetServerMailboxes(
    PRPC_MESSAGE _pRpcMessage )
{
    long _M64;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pPipeNumber;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    pPipeNumber = 0;
    RpcTryFinally
        {
        pPipeNumber = &_M64;
        
        _RetVal = RemoteAdmGetServerMailboxes(pPipeNumber);
        
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
WINDSADM_RemoteAdmGetServerDistLists(
    PRPC_MESSAGE _pRpcMessage )
{
    long _M65;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    long __RPC_FAR *pPipeNumber;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    pPipeNumber = 0;
    RpcTryFinally
        {
        pPipeNumber = &_M65;
        
        _RetVal = RemoteAdmGetServerDistLists(pPipeNumber);
        
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
WINDSADM_RemoteAdmEmptyMailbox(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwMailboxID;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[2] );
        
        dwMailboxID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        _RetVal = RemoteAdmEmptyMailbox(dwMailboxID);
        
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
WINDSADM_RemoteAdmGetGALDirectory(
    PRPC_MESSAGE _pRpcMessage )
{
    long _M66;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwFlags;
    long __RPC_FAR *pPipeNumber;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    pPipeNumber = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[12] );
        
        dwFlags = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pPipeNumber = &_M66;
        
        _RetVal = RemoteAdmGetGALDirectory(dwFlags,pPipeNumber);
        
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
WINDSADM_RemoteAdmTerminateNotifA(
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
                          &WINDSADM_StubDesc);
    
    szComputerName = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[20] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        ulConnectionID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        _RetVal = RemoteAdmTerminateNotifA(szComputerName,ulConnectionID);
        
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
WINDSADM_RemoteAdmValidateNotifA(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M67;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pulConnectionID;
    unsigned char __RPC_FAR *szComputerName;
    unsigned long ulNotifMask;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    szComputerName = 0;
    pulConnectionID = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[28] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        ulNotifMask = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pulConnectionID = &_M67;
        
        _RetVal = RemoteAdmValidateNotifA(
                                  szComputerName,
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
WINDSADM_RemoteAdmCreateMailboxA(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ADM_MAILBOX_INFO_A __RPC_FAR *pMailboxInfo;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    pMailboxInfo = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[40] );
        
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&pMailboxInfo,
                                   (PFORMAT_STRING) &__MIDLFormatString.Format[36],
                                   (unsigned char)0 );
        
        
        _RetVal = RemoteAdmCreateMailboxA(pMailboxInfo);
        
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
WINDSADM_RemoteAdmGetMailboxPropsA(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M68;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ADM_MAILBOX_INFO_A _pMailboxInfoM;
    unsigned long dwObjID;
    ADM_MAILBOX_INFO_A __RPC_FAR *pMailboxInfo;
    unsigned long __RPC_FAR *pdwObjType;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    pdwObjType = 0;
    pMailboxInfo = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[46] );
        
        dwObjID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pdwObjType = &_M68;
        pMailboxInfo = &_pMailboxInfoM;
        
        _RetVal = RemoteAdmGetMailboxPropsA(
                                    dwObjID,
                                    pdwObjType,
                                    pMailboxInfo);
        
        _StubMsg.BufferLength = 4U + 0U + 11U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)pMailboxInfo,
                                   (PFORMAT_STRING) &__MIDLFormatString.Format[36] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwObjType;
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)pMailboxInfo,
                                 (PFORMAT_STRING) &__MIDLFormatString.Format[36] );
        
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
WINDSADM_RemoteAdmSetMailboxPropsA(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ADM_MAILBOX_INFO_A __RPC_FAR *pMailboxInfo;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    pMailboxInfo = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[40] );
        
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&pMailboxInfo,
                                   (PFORMAT_STRING) &__MIDLFormatString.Format[36],
                                   (unsigned char)0 );
        
        
        _RetVal = RemoteAdmSetMailboxPropsA(pMailboxInfo);
        
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
WINDSADM_RemoteAdmCreateDistListA(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwFlags;
    unsigned long dwOwnerID;
    DLM_XMIT_LIST_A __RPC_FAR *pMembers;
    unsigned char __RPC_FAR *szDLAlias;
    unsigned char __RPC_FAR *szDLFullName;
    unsigned char __RPC_FAR *szOwnerAlias;
    unsigned char __RPC_FAR *szOwnerName;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    szDLAlias = 0;
    szDLFullName = 0;
    szOwnerAlias = 0;
    szOwnerName = 0;
    pMembers = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[58] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDLAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDLFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        dwFlags = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOwnerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOwnerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        dwOwnerID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrXmitOrRepAsUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pMembers,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[156],
                                  (unsigned char)0 );
        
        
        _RetVal = RemoteAdmCreateDistListA(
                                   szDLAlias,
                                   szDLFullName,
                                   dwFlags,
                                   szOwnerAlias,
                                   szOwnerName,
                                   dwOwnerID,
                                   pMembers);
        
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
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pMembers,
                        &__MIDLFormatString.Format[102] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSADM_RemoteAdmGetDLPropsA(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M69;
    unsigned long _M70;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwObjID;
    DLM_XMIT_LIST_A __RPC_FAR *pMembers;
    unsigned long __RPC_FAR *pdwFlags;
    unsigned long __RPC_FAR *pdwOwnerID;
    unsigned char __RPC_FAR *szComments;
    unsigned char __RPC_FAR *szDLAlias;
    unsigned char __RPC_FAR *szDLFullName;
    unsigned char __RPC_FAR *szOwnerAlias;
    unsigned char __RPC_FAR *szOwnerName;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    szDLAlias = 0;
    szDLFullName = 0;
    pdwFlags = 0;
    szOwnerAlias = 0;
    szOwnerName = 0;
    pdwOwnerID = 0;
    szComments = 0;
    pMembers = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[84] );
        
        dwObjID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrXmitOrRepAsUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pMembers,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[220],
                                  (unsigned char)0 );
        
        szDLAlias = _StubMsg.pfnAllocate((16 + 1) * 1);
        szDLFullName = _StubMsg.pfnAllocate((32 + 1) * 1);
        pdwFlags = &_M69;
        szOwnerAlias = _StubMsg.pfnAllocate((16 + 1) * 1);
        szOwnerName = _StubMsg.pfnAllocate((32 + 1) * 1);
        pdwOwnerID = &_M70;
        szComments = _StubMsg.pfnAllocate((79 + 1) * 1);
        
        _RetVal = RemoteAdmGetDLPropsA(
                               dwObjID,
                               szDLAlias,
                               szDLFullName,
                               pdwFlags,
                               szOwnerAlias,
                               szOwnerName,
                               pdwOwnerID,
                               szComments,
                               pMembers);
        
        _StubMsg.BufferLength = 12U + 13U + 11U + 13U + 13U + 11U + 13U + 0U + 11U;
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szDLAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[170] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szDLFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[180] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szOwnerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[190] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szOwnerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[200] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szComments,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[210] );
        
        NdrXmitOrRepAsBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pMembers,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[220] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szDLAlias,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[170] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szDLFullName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[180] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwFlags;
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szOwnerAlias,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[190] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szOwnerName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[200] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwOwnerID;
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szComments,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[210] );
        
        NdrXmitOrRepAsMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pMembers,
                                (PFORMAT_STRING) &__MIDLFormatString.Format[220] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 16 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szDLAlias,
                        &__MIDLFormatString.Format[166] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szDLFullName,
                        &__MIDLFormatString.Format[176] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szOwnerAlias,
                        &__MIDLFormatString.Format[186] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szOwnerName,
                        &__MIDLFormatString.Format[196] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szComments,
                        &__MIDLFormatString.Format[206] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pMembers,
                        &__MIDLFormatString.Format[216] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSADM_RemoteAdmSetDLPropsA(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwFlags;
    unsigned long dwObjID;
    unsigned long dwOwnerID;
    DLM_XMIT_LIST_A __RPC_FAR *pMembers;
    unsigned char __RPC_FAR *szComments;
    unsigned char __RPC_FAR *szDLAlias;
    unsigned char __RPC_FAR *szDLFullName;
    unsigned char __RPC_FAR *szOwnerAlias;
    unsigned char __RPC_FAR *szOwnerName;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    szDLAlias = 0;
    szDLFullName = 0;
    szOwnerAlias = 0;
    szOwnerName = 0;
    szComments = 0;
    pMembers = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[120] );
        
        dwObjID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDLAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDLFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        dwFlags = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOwnerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOwnerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        dwOwnerID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComments,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6],
                                       (unsigned char)0 );
        
        NdrXmitOrRepAsUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pMembers,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[234],
                                  (unsigned char)0 );
        
        
        _RetVal = RemoteAdmSetDLPropsA(
                               dwObjID,
                               szDLAlias,
                               szDLFullName,
                               dwFlags,
                               szOwnerAlias,
                               szOwnerName,
                               dwOwnerID,
                               szComments,
                               pMembers);
        
        _StubMsg.BufferLength = 0U + 11U;
        NdrXmitOrRepAsBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pMembers,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[234] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrXmitOrRepAsMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pMembers,
                                (PFORMAT_STRING) &__MIDLFormatString.Format[234] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pMembers,
                        &__MIDLFormatString.Format[230] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSADM_RemoteAdmTerminateNotifW(
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
                          &WINDSADM_StubDesc);
    
    szComputerName = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[152] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[246],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        ulConnectionID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        _RetVal = RemoteAdmTerminateNotifW(szComputerName,ulConnectionID);
        
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
WINDSADM_RemoteAdmValidateNotifW(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M71;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pulConnectionID;
    wchar_t __RPC_FAR *szComputerName;
    unsigned long ulNotifMask;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    szComputerName = 0;
    pulConnectionID = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[160] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[246],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        ulNotifMask = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pulConnectionID = &_M71;
        
        _RetVal = RemoteAdmValidateNotifW(
                                  szComputerName,
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
WINDSADM_RemoteAdmCreateMailboxW(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ADM_MAILBOX_INFO_W __RPC_FAR *pMailboxInfo;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    pMailboxInfo = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[172] );
        
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&pMailboxInfo,
                                   (PFORMAT_STRING) &__MIDLFormatString.Format[276],
                                   (unsigned char)0 );
        
        
        _RetVal = RemoteAdmCreateMailboxW(pMailboxInfo);
        
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
WINDSADM_RemoteAdmGetMailboxPropsW(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M72;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ADM_MAILBOX_INFO_W _pMailboxInfoM;
    unsigned long dwObjID;
    ADM_MAILBOX_INFO_W __RPC_FAR *pMailboxInfo;
    unsigned long __RPC_FAR *pdwObjType;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    pdwObjType = 0;
    pMailboxInfo = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[178] );
        
        dwObjID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pdwObjType = &_M72;
        pMailboxInfo = &_pMailboxInfoM;
        
        _RetVal = RemoteAdmGetMailboxPropsW(
                                    dwObjID,
                                    pdwObjType,
                                    pMailboxInfo);
        
        _StubMsg.BufferLength = 4U + 0U + 11U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)pMailboxInfo,
                                   (PFORMAT_STRING) &__MIDLFormatString.Format[276] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwObjType;
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)pMailboxInfo,
                                 (PFORMAT_STRING) &__MIDLFormatString.Format[276] );
        
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
WINDSADM_RemoteAdmSetMailboxPropsW(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    ADM_MAILBOX_INFO_W __RPC_FAR *pMailboxInfo;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    pMailboxInfo = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[172] );
        
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&pMailboxInfo,
                                   (PFORMAT_STRING) &__MIDLFormatString.Format[276],
                                   (unsigned char)0 );
        
        
        _RetVal = RemoteAdmSetMailboxPropsW(pMailboxInfo);
        
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
WINDSADM_RemoteAdmCreateDistListW(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwFlags;
    unsigned long dwOwnerID;
    DLM_XMIT_LIST_W __RPC_FAR *pMembers;
    wchar_t __RPC_FAR *szDLAlias;
    wchar_t __RPC_FAR *szDLFullName;
    wchar_t __RPC_FAR *szOwnerAlias;
    wchar_t __RPC_FAR *szOwnerName;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    szDLAlias = 0;
    szDLFullName = 0;
    szOwnerAlias = 0;
    szOwnerName = 0;
    pMembers = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[190] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDLAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[246],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDLFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[246],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        dwFlags = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOwnerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[246],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOwnerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[246],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        dwOwnerID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrXmitOrRepAsUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pMembers,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[396],
                                  (unsigned char)0 );
        
        
        _RetVal = RemoteAdmCreateDistListW(
                                   szDLAlias,
                                   szDLFullName,
                                   dwFlags,
                                   szOwnerAlias,
                                   szOwnerName,
                                   dwOwnerID,
                                   pMembers);
        
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
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pMembers,
                        &__MIDLFormatString.Format[342] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSADM_RemoteAdmGetDLPropsW(
    PRPC_MESSAGE _pRpcMessage )
{
    unsigned long _M73;
    unsigned long _M74;
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwObjID;
    DLM_XMIT_LIST_W __RPC_FAR *pMembers;
    unsigned long __RPC_FAR *pdwFlags;
    unsigned long __RPC_FAR *pdwOwnerID;
    wchar_t __RPC_FAR *szComments;
    wchar_t __RPC_FAR *szDLAlias;
    wchar_t __RPC_FAR *szDLFullName;
    wchar_t __RPC_FAR *szOwnerAlias;
    wchar_t __RPC_FAR *szOwnerName;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    szDLAlias = 0;
    szDLFullName = 0;
    pdwFlags = 0;
    szOwnerAlias = 0;
    szOwnerName = 0;
    pdwOwnerID = 0;
    szComments = 0;
    pMembers = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[216] );
        
        dwObjID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrXmitOrRepAsUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pMembers,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[460],
                                  (unsigned char)0 );
        
        szDLAlias = _StubMsg.pfnAllocate((16 + 1) * 2);
        szDLFullName = _StubMsg.pfnAllocate((32 + 1) * 2);
        pdwFlags = &_M73;
        szOwnerAlias = _StubMsg.pfnAllocate((16 + 1) * 2);
        szOwnerName = _StubMsg.pfnAllocate((32 + 1) * 2);
        pdwOwnerID = &_M74;
        szComments = _StubMsg.pfnAllocate((79 + 1) * 2);
        
        _RetVal = RemoteAdmGetDLPropsW(
                               dwObjID,
                               szDLAlias,
                               szDLFullName,
                               pdwFlags,
                               szOwnerAlias,
                               szOwnerName,
                               pdwOwnerID,
                               szComments,
                               pMembers);
        
        _StubMsg.BufferLength = 12U + 14U + 10U + 14U + 14U + 10U + 14U + 0U + 11U;
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szDLAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[410] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szDLFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[420] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szOwnerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[430] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szOwnerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[440] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szComments,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[450] );
        
        NdrXmitOrRepAsBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pMembers,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[460] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szDLAlias,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[410] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szDLFullName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[420] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwFlags;
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szOwnerAlias,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[430] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szOwnerName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[440] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pdwOwnerID;
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szComments,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[450] );
        
        NdrXmitOrRepAsMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pMembers,
                                (PFORMAT_STRING) &__MIDLFormatString.Format[460] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 16 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szDLAlias,
                        &__MIDLFormatString.Format[406] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szDLFullName,
                        &__MIDLFormatString.Format[416] );
        
        _StubMsg.MaxCount = 16 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szOwnerAlias,
                        &__MIDLFormatString.Format[426] );
        
        _StubMsg.MaxCount = 32 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szOwnerName,
                        &__MIDLFormatString.Format[436] );
        
        _StubMsg.MaxCount = 79 + 1;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szComments,
                        &__MIDLFormatString.Format[446] );
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pMembers,
                        &__MIDLFormatString.Format[456] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
WINDSADM_RemoteAdmSetDLPropsW(
    PRPC_MESSAGE _pRpcMessage )
{
    long _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long dwFlags;
    unsigned long dwObjID;
    unsigned long dwOwnerID;
    DLM_XMIT_LIST_W __RPC_FAR *pMembers;
    wchar_t __RPC_FAR *szComments;
    wchar_t __RPC_FAR *szDLAlias;
    wchar_t __RPC_FAR *szDLFullName;
    wchar_t __RPC_FAR *szOwnerAlias;
    wchar_t __RPC_FAR *szOwnerName;
    RPC_STATUS _Status;
    
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &WINDSADM_StubDesc);
    
    szDLAlias = 0;
    szDLFullName = 0;
    szOwnerAlias = 0;
    szOwnerName = 0;
    szComments = 0;
    pMembers = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[252] );
        
        dwObjID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDLAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[246],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDLFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[246],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        dwFlags = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOwnerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[246],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOwnerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[246],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        dwOwnerID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComments,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[246],
                                       (unsigned char)0 );
        
        NdrXmitOrRepAsUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pMembers,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[474],
                                  (unsigned char)0 );
        
        
        _RetVal = RemoteAdmSetDLPropsW(
                               dwObjID,
                               szDLAlias,
                               szDLFullName,
                               dwFlags,
                               szOwnerAlias,
                               szOwnerName,
                               dwOwnerID,
                               szComments,
                               pMembers);
        
        _StubMsg.BufferLength = 0U + 11U;
        NdrXmitOrRepAsBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pMembers,
                                  (PFORMAT_STRING) &__MIDLFormatString.Format[474] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrXmitOrRepAsMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pMembers,
                                (PFORMAT_STRING) &__MIDLFormatString.Format[474] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( long __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pMembers,
                        &__MIDLFormatString.Format[470] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

extern const XMIT_ROUTINE_QUINTUPLE TransmitAsRoutines[];

static const MIDL_STUB_DESC WINDSADM_StubDesc = 
    {
    (void __RPC_FAR *)& WINDSADM___RpcServerInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    0,
    0,
    0,
    0,
    TransmitAsRoutines,
    __MIDLFormatString.Format,
    0, /* -error bounds_check flag */
    0x10001, /* Ndr library version */
    0,
    0x2000066, /* MIDL Version 2.0.102 */
    0
    };

static RPC_DISPATCH_FUNCTION WINDSADM_table[] =
    {
    WINDSADM_RemoteAdmIsServerRunning,
    WINDSADM_RemoteAdmDeleteObject,
    WINDSADM_RemoteAdmGetServerMailboxes,
    WINDSADM_RemoteAdmGetServerDistLists,
    WINDSADM_RemoteAdmEmptyMailbox,
    WINDSADM_RemoteAdmGetGALDirectory,
    WINDSADM_RemoteAdmTerminateNotifA,
    WINDSADM_RemoteAdmValidateNotifA,
    WINDSADM_RemoteAdmCreateMailboxA,
    WINDSADM_RemoteAdmGetMailboxPropsA,
    WINDSADM_RemoteAdmSetMailboxPropsA,
    WINDSADM_RemoteAdmCreateDistListA,
    WINDSADM_RemoteAdmGetDLPropsA,
    WINDSADM_RemoteAdmSetDLPropsA,
    WINDSADM_RemoteAdmTerminateNotifW,
    WINDSADM_RemoteAdmValidateNotifW,
    WINDSADM_RemoteAdmCreateMailboxW,
    WINDSADM_RemoteAdmGetMailboxPropsW,
    WINDSADM_RemoteAdmSetMailboxPropsW,
    WINDSADM_RemoteAdmCreateDistListW,
    WINDSADM_RemoteAdmGetDLPropsW,
    WINDSADM_RemoteAdmSetDLPropsW,
    0
    };
RPC_DISPATCH_TABLE WINDSADM_v1_0_DispatchTable = 
    {
    22,
    WINDSADM_table
    };
void __RPC_USER
DLM_XMIT_LIST_A_XmitTranslateToXmit_0000( PMIDL_STUB_MESSAGE pStubMsg )
{
    DLM_XMIT_LIST_A_to_xmit( (DLM_XMIT_LIST_A __RPC_FAR *) pStubMsg->pPresentedType, 
        (DLM_ARRAY_A __RPC_FAR * __RPC_FAR *) &pStubMsg->pTransmitType );
    
}
void __RPC_USER
DLM_XMIT_LIST_A_XmitTranslateFromXmit_0000( PMIDL_STUB_MESSAGE pStubMsg )
{
    DLM_XMIT_LIST_A_from_xmit( (DLM_ARRAY_A __RPC_FAR *) pStubMsg->pTransmitType, 
        (DLM_XMIT_LIST_A __RPC_FAR *) pStubMsg->pPresentedType ); 
}
void __RPC_USER
DLM_XMIT_LIST_A_XmitFreeXmit_0000( PMIDL_STUB_MESSAGE pStubMsg )
{
    DLM_XMIT_LIST_A_free_xmit( (DLM_ARRAY_A __RPC_FAR *) pStubMsg->pTransmitType );
}
void __RPC_USER
DLM_XMIT_LIST_A_XmitFreeInst_0000( PMIDL_STUB_MESSAGE pStubMsg )
{
    DLM_XMIT_LIST_A_free_inst( (DLM_XMIT_LIST_A __RPC_FAR *) pStubMsg->pPresentedType ); 
}
void __RPC_USER
DLM_XMIT_LIST_W_XmitTranslateToXmit_0001( PMIDL_STUB_MESSAGE pStubMsg )
{
    DLM_XMIT_LIST_W_to_xmit( (DLM_XMIT_LIST_W __RPC_FAR *) pStubMsg->pPresentedType, 
        (DLM_ARRAY_W __RPC_FAR * __RPC_FAR *) &pStubMsg->pTransmitType );
    
}
void __RPC_USER
DLM_XMIT_LIST_W_XmitTranslateFromXmit_0001( PMIDL_STUB_MESSAGE pStubMsg )
{
    DLM_XMIT_LIST_W_from_xmit( (DLM_ARRAY_W __RPC_FAR *) pStubMsg->pTransmitType, 
        (DLM_XMIT_LIST_W __RPC_FAR *) pStubMsg->pPresentedType ); 
}
void __RPC_USER
DLM_XMIT_LIST_W_XmitFreeXmit_0001( PMIDL_STUB_MESSAGE pStubMsg )
{
    DLM_XMIT_LIST_W_free_xmit( (DLM_ARRAY_W __RPC_FAR *) pStubMsg->pTransmitType );
}
void __RPC_USER
DLM_XMIT_LIST_W_XmitFreeInst_0001( PMIDL_STUB_MESSAGE pStubMsg )
{
    DLM_XMIT_LIST_W_free_inst( (DLM_XMIT_LIST_W __RPC_FAR *) pStubMsg->pPresentedType ); 
}

static const XMIT_ROUTINE_QUINTUPLE TransmitAsRoutines[] = 
        {
            
            {
            DLM_XMIT_LIST_A_XmitTranslateToXmit_0000
            ,DLM_XMIT_LIST_A_XmitTranslateFromXmit_0000
            ,DLM_XMIT_LIST_A_XmitFreeXmit_0000
            ,DLM_XMIT_LIST_A_XmitFreeInst_0000
            },
            {
            DLM_XMIT_LIST_W_XmitTranslateToXmit_0001
            ,DLM_XMIT_LIST_W_XmitTranslateFromXmit_0001
            ,DLM_XMIT_LIST_W_XmitFreeXmit_0001
            ,DLM_XMIT_LIST_W_XmitFreeInst_0001
            }

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
/*  2 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/*  4 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/*  6 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/*  8 */    NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 10 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 12 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 14 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 16 */    NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 18 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 20 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 22 */    NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 24 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 26 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 28 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 30 */    NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 32 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
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
/* 40 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 42 */    NdrFcShort( 0x8 ),  /* Type Offset=8 */
/* 44 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 46 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 48 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 50 */    NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 52 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 54 */    NdrFcShort( 0x62 ), /* Type Offset=98 */
/* 56 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 58 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 60 */    NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 62 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 64 */    NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 66 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 68 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 70 */    NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 72 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 74 */    NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 76 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 78 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 80 */    NdrFcShort( 0x66 ), /* Type Offset=102 */
/* 82 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 84 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 86 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 88 */    NdrFcShort( 0xa6 ), /* Type Offset=166 */
/* 90 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 92 */    NdrFcShort( 0xb0 ), /* Type Offset=176 */
/* 94 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 96 */    NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 98 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 100 */   NdrFcShort( 0xba ), /* Type Offset=186 */
/* 102 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 104 */   NdrFcShort( 0xc4 ), /* Type Offset=196 */
/* 106 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 108 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 110 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 112 */   NdrFcShort( 0xce ), /* Type Offset=206 */
/* 114 */   
            0x50,       /* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 116 */   NdrFcShort( 0xd8 ), /* Type Offset=216 */
/* 118 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 120 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 122 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 124 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 126 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 128 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 130 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 132 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 134 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 136 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 138 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 140 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 142 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 144 */   NdrFcShort( 0x4 ),  /* Type Offset=4 */
/* 146 */   
            0x50,       /* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 148 */   NdrFcShort( 0xe6 ), /* Type Offset=230 */
/* 150 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 152 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 154 */   NdrFcShort( 0xf4 ), /* Type Offset=244 */
/* 156 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 158 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 160 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 162 */   NdrFcShort( 0xf4 ), /* Type Offset=244 */
/* 164 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
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
/* 172 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 174 */   NdrFcShort( 0xf8 ), /* Type Offset=248 */
/* 176 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 178 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 180 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 182 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 184 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 186 */   NdrFcShort( 0x152 ),    /* Type Offset=338 */
/* 188 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 190 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 192 */   NdrFcShort( 0xf4 ), /* Type Offset=244 */
/* 194 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 196 */   NdrFcShort( 0xf4 ), /* Type Offset=244 */
/* 198 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 200 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 202 */   NdrFcShort( 0xf4 ), /* Type Offset=244 */
/* 204 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 206 */   NdrFcShort( 0xf4 ), /* Type Offset=244 */
/* 208 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 210 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 212 */   NdrFcShort( 0x156 ),    /* Type Offset=342 */
/* 214 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 216 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 218 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 220 */   NdrFcShort( 0x196 ),    /* Type Offset=406 */
/* 222 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 224 */   NdrFcShort( 0x1a0 ),    /* Type Offset=416 */
/* 226 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 228 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 230 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 232 */   NdrFcShort( 0x1aa ),    /* Type Offset=426 */
/* 234 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 236 */   NdrFcShort( 0x1b4 ),    /* Type Offset=436 */
/* 238 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 240 */   NdrFcShort( 0x0 ),  /* Type Offset=0 */
/* 242 */   
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 244 */   NdrFcShort( 0x1be ),    /* Type Offset=446 */
/* 246 */   
            0x50,       /* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 248 */   NdrFcShort( 0x1c8 ),    /* Type Offset=456 */
/* 250 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 252 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 254 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 256 */   NdrFcShort( 0xf4 ), /* Type Offset=244 */
/* 258 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 260 */   NdrFcShort( 0xf4 ), /* Type Offset=244 */
/* 262 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 264 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 266 */   NdrFcShort( 0xf4 ), /* Type Offset=244 */
/* 268 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 270 */   NdrFcShort( 0xf4 ), /* Type Offset=244 */
/* 272 */   0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 274 */   
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 276 */   NdrFcShort( 0xf4 ), /* Type Offset=244 */
/* 278 */   
            0x50,       /* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 280 */   NdrFcShort( 0x1d6 ),    /* Type Offset=470 */
/* 282 */   0x53,       /* FC_RETURN_PARAM_BASETYPE */
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
            0x11, 0x0,  /* FC_RP */
/* 10 */    NdrFcShort( 0x1a ), /* Offset= 26 (36) */
/* 12 */    
            0x1d,       /* FC_SMFARRAY */
            0x0,        /* 0 */
/* 14 */    NdrFcShort( 0x11 ), /* 17 */
/* 16 */    0x2,        /* FC_CHAR */
            0x5b,       /* FC_END */
/* 18 */    
            0x1d,       /* FC_SMFARRAY */
            0x0,        /* 0 */
/* 20 */    NdrFcShort( 0x21 ), /* 33 */
/* 22 */    0x2,        /* FC_CHAR */
            0x5b,       /* FC_END */
/* 24 */    
            0x1d,       /* FC_SMFARRAY */
            0x0,        /* 0 */
/* 26 */    NdrFcShort( 0xd ),  /* 13 */
/* 28 */    0x2,        /* FC_CHAR */
            0x5b,       /* FC_END */
/* 30 */    
            0x1d,       /* FC_SMFARRAY */
            0x0,        /* 0 */
/* 32 */    NdrFcShort( 0x50 ), /* 80 */
/* 34 */    0x2,        /* FC_CHAR */
            0x5b,       /* FC_END */
/* 36 */    
            0x15,       /* FC_STRUCT */
            0x3,        /* 3 */
/* 38 */    NdrFcShort( 0x18c ),    /* 396 */
/* 40 */    0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 42 */    NdrFcShort( 0xffffffe2 ),   /* Offset= -30 (12) */
/* 44 */    0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 46 */    NdrFcShort( 0xffffffe4 ),   /* Offset= -28 (18) */
/* 48 */    0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 50 */    NdrFcShort( 0xffffffe0 ),   /* Offset= -32 (18) */
/* 52 */    0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 54 */    NdrFcShort( 0xffffffdc ),   /* Offset= -36 (18) */
/* 56 */    0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 58 */    NdrFcShort( 0xffffffde ),   /* Offset= -34 (24) */
/* 60 */    0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 62 */    NdrFcShort( 0xffffffda ),   /* Offset= -38 (24) */
/* 64 */    0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 66 */    NdrFcShort( 0xffffffd6 ),   /* Offset= -42 (24) */
/* 68 */    0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 70 */    NdrFcShort( 0xffffffc6 ),   /* Offset= -58 (12) */
/* 72 */    0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 74 */    NdrFcShort( 0xffffffc8 ),   /* Offset= -56 (18) */
/* 76 */    0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 78 */    NdrFcShort( 0xffffffc4 ),   /* Offset= -60 (18) */
/* 80 */    0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 82 */    NdrFcShort( 0xffffffcc ),   /* Offset= -52 (30) */
/* 84 */    0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 86 */    NdrFcShort( 0xffffffbc ),   /* Offset= -68 (18) */
/* 88 */    0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 90 */    NdrFcShort( 0xffffffb8 ),   /* Offset= -72 (18) */
/* 92 */    0x38,       /* FC_ALIGNM4 */
            0x8,        /* FC_LONG */
/* 94 */    0x8,        /* FC_LONG */
            0x8,        /* FC_LONG */
/* 96 */    0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 98 */    
            0x11, 0x4,  /* FC_RP [alloced_on_stack] */
/* 100 */   NdrFcShort( 0xffffffc0 ),   /* Offset= -64 (36) */
/* 102 */   
            0x11, 0x0,  /* FC_RP */
/* 104 */   NdrFcShort( 0x34 ), /* Offset= 52 (156) */
/* 106 */   
            0x1d,       /* FC_SMFARRAY */
            0x0,        /* 0 */
/* 108 */   NdrFcShort( 0x24 ), /* 36 */
/* 110 */   0x2,        /* FC_CHAR */
            0x5b,       /* FC_END */
/* 112 */   
            0x1d,       /* FC_SMFARRAY */
            0x0,        /* 0 */
/* 114 */   NdrFcShort( 0x14 ), /* 20 */
/* 116 */   0x2,        /* FC_CHAR */
            0x5b,       /* FC_END */
/* 118 */   
            0x15,       /* FC_STRUCT */
            0x3,        /* 3 */
/* 120 */   NdrFcShort( 0x40 ), /* 64 */
/* 122 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 124 */   NdrFcShort( 0xffffffee ),   /* Offset= -18 (106) */
/* 126 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 128 */   NdrFcShort( 0xfffffff0 ),   /* Offset= -16 (112) */
/* 130 */   0x8,        /* FC_LONG */
            0x8,        /* FC_LONG */
/* 132 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 134 */   
            0x1b,       /* FC_CARRAY */
            0x3,        /* 3 */
/* 136 */   NdrFcShort( 0x40 ), /* 64 */
/* 138 */   0x8,        /* 8 */
            0x0,        /*  */
/* 140 */   NdrFcShort( 0xfffffffc ),   /* -4 */
/* 142 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 144 */   NdrFcShort( 0xffffffe6 ),   /* Offset= -26 (118) */
/* 146 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 148 */   
            0x17,       /* FC_CSTRUCT */
            0x3,        /* 3 */
/* 150 */   NdrFcShort( 0x4 ),  /* 4 */
/* 152 */   NdrFcShort( 0xffffffee ),   /* Offset= -18 (134) */
/* 154 */   0x8,        /* FC_LONG */
            0x5b,       /* FC_END */
/* 156 */   0x2d,       /* FC_TRANSMIT_AS */
            0x3,        /* 3 */
/* 158 */   NdrFcShort( 0x0 ),  /* 0 */
/* 160 */   NdrFcShort( 0x44 ), /* 68 */
/* 162 */   NdrFcShort( 0x0 ),  /* 0 */
/* 164 */   NdrFcShort( 0xfffffff0 ),   /* Offset= -16 (148) */
/* 166 */   
            0x11, 0x0,  /* FC_RP */
/* 168 */   NdrFcShort( 0x2 ),  /* Offset= 2 (170) */
/* 170 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 172 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 174 */   NdrFcShort( 0x11 ), /* 17 */
/* 176 */   
            0x11, 0x0,  /* FC_RP */
/* 178 */   NdrFcShort( 0x2 ),  /* Offset= 2 (180) */
/* 180 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 182 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 184 */   NdrFcShort( 0x21 ), /* 33 */
/* 186 */   
            0x11, 0x0,  /* FC_RP */
/* 188 */   NdrFcShort( 0x2 ),  /* Offset= 2 (190) */
/* 190 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 192 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 194 */   NdrFcShort( 0x11 ), /* 17 */
/* 196 */   
            0x11, 0x0,  /* FC_RP */
/* 198 */   NdrFcShort( 0x2 ),  /* Offset= 2 (200) */
/* 200 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 202 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 204 */   NdrFcShort( 0x21 ), /* 33 */
/* 206 */   
            0x11, 0x0,  /* FC_RP */
/* 208 */   NdrFcShort( 0x2 ),  /* Offset= 2 (210) */
/* 210 */   
            0x22,       /* FC_C_CSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 212 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 214 */   NdrFcShort( 0x50 ), /* 80 */
/* 216 */   
            0x11, 0x0,  /* FC_RP */
/* 218 */   NdrFcShort( 0x2 ),  /* Offset= 2 (220) */
/* 220 */   0x2d,       /* FC_TRANSMIT_AS */
            0x3,        /* 3 */
/* 222 */   NdrFcShort( 0x0 ),  /* 0 */
/* 224 */   NdrFcShort( 0x44 ), /* 68 */
/* 226 */   NdrFcShort( 0x0 ),  /* 0 */
/* 228 */   NdrFcShort( 0xffffffb0 ),   /* Offset= -80 (148) */
/* 230 */   
            0x11, 0x0,  /* FC_RP */
/* 232 */   NdrFcShort( 0x2 ),  /* Offset= 2 (234) */
/* 234 */   0x2d,       /* FC_TRANSMIT_AS */
            0x3,        /* 3 */
/* 236 */   NdrFcShort( 0x0 ),  /* 0 */
/* 238 */   NdrFcShort( 0x44 ), /* 68 */
/* 240 */   NdrFcShort( 0x0 ),  /* 0 */
/* 242 */   NdrFcShort( 0xffffffa2 ),   /* Offset= -94 (148) */
/* 244 */   
            0x11, 0x8,  /* FC_RP [simple_pointer] */
/* 246 */   
            0x25,       /* FC_C_WSTRING */
            0x5c,       /* FC_PAD */
/* 248 */   
            0x11, 0x0,  /* FC_RP */
/* 250 */   NdrFcShort( 0x1a ), /* Offset= 26 (276) */
/* 252 */   
            0x1d,       /* FC_SMFARRAY */
            0x1,        /* 1 */
/* 254 */   NdrFcShort( 0x22 ), /* 34 */
/* 256 */   0x5,        /* FC_WCHAR */
            0x5b,       /* FC_END */
/* 258 */   
            0x1d,       /* FC_SMFARRAY */
            0x1,        /* 1 */
/* 260 */   NdrFcShort( 0x42 ), /* 66 */
/* 262 */   0x5,        /* FC_WCHAR */
            0x5b,       /* FC_END */
/* 264 */   
            0x1d,       /* FC_SMFARRAY */
            0x1,        /* 1 */
/* 266 */   NdrFcShort( 0x1a ), /* 26 */
/* 268 */   0x5,        /* FC_WCHAR */
            0x5b,       /* FC_END */
/* 270 */   
            0x1d,       /* FC_SMFARRAY */
            0x1,        /* 1 */
/* 272 */   NdrFcShort( 0xa0 ), /* 160 */
/* 274 */   0x5,        /* FC_WCHAR */
            0x5b,       /* FC_END */
/* 276 */   
            0x15,       /* FC_STRUCT */
            0x3,        /* 3 */
/* 278 */   NdrFcShort( 0x30c ),    /* 780 */
/* 280 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 282 */   NdrFcShort( 0xffffffe2 ),   /* Offset= -30 (252) */
/* 284 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 286 */   NdrFcShort( 0xffffffe4 ),   /* Offset= -28 (258) */
/* 288 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 290 */   NdrFcShort( 0xffffffe0 ),   /* Offset= -32 (258) */
/* 292 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 294 */   NdrFcShort( 0xffffffdc ),   /* Offset= -36 (258) */
/* 296 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 298 */   NdrFcShort( 0xffffffde ),   /* Offset= -34 (264) */
/* 300 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 302 */   NdrFcShort( 0xffffffda ),   /* Offset= -38 (264) */
/* 304 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 306 */   NdrFcShort( 0xffffffd6 ),   /* Offset= -42 (264) */
/* 308 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 310 */   NdrFcShort( 0xffffffc6 ),   /* Offset= -58 (252) */
/* 312 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 314 */   NdrFcShort( 0xffffffc8 ),   /* Offset= -56 (258) */
/* 316 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 318 */   NdrFcShort( 0xffffffc4 ),   /* Offset= -60 (258) */
/* 320 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 322 */   NdrFcShort( 0xffffffcc ),   /* Offset= -52 (270) */
/* 324 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 326 */   NdrFcShort( 0xffffffbc ),   /* Offset= -68 (258) */
/* 328 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 330 */   NdrFcShort( 0xffffffb8 ),   /* Offset= -72 (258) */
/* 332 */   0x38,       /* FC_ALIGNM4 */
            0x8,        /* FC_LONG */
/* 334 */   0x8,        /* FC_LONG */
            0x8,        /* FC_LONG */
/* 336 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 338 */   
            0x11, 0x4,  /* FC_RP [alloced_on_stack] */
/* 340 */   NdrFcShort( 0xffffffc0 ),   /* Offset= -64 (276) */
/* 342 */   
            0x11, 0x0,  /* FC_RP */
/* 344 */   NdrFcShort( 0x34 ), /* Offset= 52 (396) */
/* 346 */   
            0x1d,       /* FC_SMFARRAY */
            0x1,        /* 1 */
/* 348 */   NdrFcShort( 0x48 ), /* 72 */
/* 350 */   0x5,        /* FC_WCHAR */
            0x5b,       /* FC_END */
/* 352 */   
            0x1d,       /* FC_SMFARRAY */
            0x1,        /* 1 */
/* 354 */   NdrFcShort( 0x28 ), /* 40 */
/* 356 */   0x5,        /* FC_WCHAR */
            0x5b,       /* FC_END */
/* 358 */   
            0x15,       /* FC_STRUCT */
            0x3,        /* 3 */
/* 360 */   NdrFcShort( 0x78 ), /* 120 */
/* 362 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 364 */   NdrFcShort( 0xffffffee ),   /* Offset= -18 (346) */
/* 366 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 368 */   NdrFcShort( 0xfffffff0 ),   /* Offset= -16 (352) */
/* 370 */   0x8,        /* FC_LONG */
            0x8,        /* FC_LONG */
/* 372 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 374 */   
            0x1b,       /* FC_CARRAY */
            0x3,        /* 3 */
/* 376 */   NdrFcShort( 0x78 ), /* 120 */
/* 378 */   0x8,        /* 8 */
            0x0,        /*  */
/* 380 */   NdrFcShort( 0xfffffffc ),   /* -4 */
/* 382 */   0x4c,       /* FC_EMBEDDED_COMPLEX */
            0x0,        /* 0 */
/* 384 */   NdrFcShort( 0xffffffe6 ),   /* Offset= -26 (358) */
/* 386 */   0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 388 */   
            0x17,       /* FC_CSTRUCT */
            0x3,        /* 3 */
/* 390 */   NdrFcShort( 0x4 ),  /* 4 */
/* 392 */   NdrFcShort( 0xffffffee ),   /* Offset= -18 (374) */
/* 394 */   0x8,        /* FC_LONG */
            0x5b,       /* FC_END */
/* 396 */   0x2d,       /* FC_TRANSMIT_AS */
            0x3,        /* 3 */
/* 398 */   NdrFcShort( 0x1 ),  /* 1 */
/* 400 */   NdrFcShort( 0x7c ), /* 124 */
/* 402 */   NdrFcShort( 0x0 ),  /* 0 */
/* 404 */   NdrFcShort( 0xfffffff0 ),   /* Offset= -16 (388) */
/* 406 */   
            0x11, 0x0,  /* FC_RP */
/* 408 */   NdrFcShort( 0x2 ),  /* Offset= 2 (410) */
/* 410 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 412 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 414 */   NdrFcShort( 0x11 ), /* 17 */
/* 416 */   
            0x11, 0x0,  /* FC_RP */
/* 418 */   NdrFcShort( 0x2 ),  /* Offset= 2 (420) */
/* 420 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 422 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 424 */   NdrFcShort( 0x21 ), /* 33 */
/* 426 */   
            0x11, 0x0,  /* FC_RP */
/* 428 */   NdrFcShort( 0x2 ),  /* Offset= 2 (430) */
/* 430 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 432 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 434 */   NdrFcShort( 0x11 ), /* 17 */
/* 436 */   
            0x11, 0x0,  /* FC_RP */
/* 438 */   NdrFcShort( 0x2 ),  /* Offset= 2 (440) */
/* 440 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 442 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 444 */   NdrFcShort( 0x21 ), /* 33 */
/* 446 */   
            0x11, 0x0,  /* FC_RP */
/* 448 */   NdrFcShort( 0x2 ),  /* Offset= 2 (450) */
/* 450 */   
            0x25,       /* FC_C_WSTRING */
            0x44,       /* FC_STRING_SIZED */
/* 452 */   0x40,       /* 64 */
            0x0,        /* 0 */
/* 454 */   NdrFcShort( 0x50 ), /* 80 */
/* 456 */   
            0x11, 0x0,  /* FC_RP */
/* 458 */   NdrFcShort( 0x2 ),  /* Offset= 2 (460) */
/* 460 */   0x2d,       /* FC_TRANSMIT_AS */
            0x3,        /* 3 */
/* 462 */   NdrFcShort( 0x1 ),  /* 1 */
/* 464 */   NdrFcShort( 0x7c ), /* 124 */
/* 466 */   NdrFcShort( 0x0 ),  /* 0 */
/* 468 */   NdrFcShort( 0xffffffb0 ),   /* Offset= -80 (388) */
/* 470 */   
            0x11, 0x0,  /* FC_RP */
/* 472 */   NdrFcShort( 0x2 ),  /* Offset= 2 (474) */
/* 474 */   0x2d,       /* FC_TRANSMIT_AS */
            0x3,        /* 3 */
/* 476 */   NdrFcShort( 0x1 ),  /* 1 */
/* 478 */   NdrFcShort( 0x7c ), /* 124 */
/* 480 */   NdrFcShort( 0x0 ),  /* 0 */
/* 482 */   NdrFcShort( 0xffffffa2 ),   /* Offset= -94 (388) */

            0x0
        }
    };
