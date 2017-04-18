/* this ALWAYS GENERATED file contains the RPC client stubs */


/* File created by MIDL compiler version 2.00.0102 */
/* at Mon Sep 25 11:13:21 1995
 */
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#if defined( _ALPHA_ )
#include <stdarg.h>
#endif

#include "winds.h"


extern const MIDL_FORMAT_STRING __MIDLFormatString;

extern const MIDL_FORMAT_STRING __MIDLProcFormatString;
handle_t hWINDSREM;


static const RPC_CLIENT_INTERFACE WINDSREM___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0xDDFFFE60,0x36D0,0x11CE,{0x9F,0x2D,0x00,0xAA,0x00,0x51,0x0E,0x3B}},{1,6}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE WINDSREM_v1_6_c_ifspec = (RPC_IF_HANDLE)& WINDSREM___RpcClientInterface;

extern const MIDL_STUB_DESC WINDSREM_StubDesc;

static RPC_BINDING_HANDLE WINDSREM__MIDL_AutoBindHandle;


long RemoteIsServerRunning( void)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          0);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 0U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[0] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteGetAllAccounts( 
    /* [out] */ long __RPC_FAR *pPipeNumber)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          1);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 0U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[2] );
        
        *pPipeNumber = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteFinishUpload( 
    /* [string][in] */ unsigned char __RPC_FAR *szCookie)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          2);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szCookie,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szCookie,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[8] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteGetContainerProps( 
    /* [in] */ unsigned long dwContainerID,
    /* [out] */ unsigned long __RPC_FAR *pdwContentCount)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          3);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 4U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = dwContainerID;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[14] );
        
        *pdwContentCount = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteGetContainerRecipients( 
    /* [in] */ unsigned long dwFlags,
    /* [in] */ unsigned long dwContainerID,
    /* [out] */ long __RPC_FAR *pPipeNumber)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          4);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = dwFlags;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = dwContainerID;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[22] );
        
        *pPipeNumber = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteGetPublicFoldersList( 
    /* [in] */ short nFlags,
    /* [out] */ long __RPC_FAR *pPipeNumber)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          5);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 2U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nFlags;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[32] );
        
        *pPipeNumber = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteGetPublicFolderMessages( 
    /* [in] */ short nFlags,
    /* [in] */ unsigned long dwFolderID,
    /* [out] */ long __RPC_FAR *pPipeNumber)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          6);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 2U + 6U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nFlags;
        
        _StubMsg.Buffer += 2;
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = dwFolderID;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[40] );
        
        *pPipeNumber = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteChangePasswordA( 
    /* [in] */ unsigned char __RPC_FAR *szMailbox,
    /* [string][in] */ unsigned char __RPC_FAR *szOldPassword,
    /* [string][in] */ unsigned char __RPC_FAR *szNewPassword)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          7);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 1U + 12U + 13U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szOldPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szNewPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        *(( unsigned char __RPC_FAR * )_StubMsg.Buffer)++ = *szMailbox;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szOldPassword,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szNewPassword,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[50] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteLogonMailBoxA( 
    /* [string][in] */ unsigned char __RPC_FAR *szMailbox,
    /* [string][in] */ unsigned char __RPC_FAR *szPassword,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwMailboxID)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          8);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U + 13U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szPassword,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[64] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[16],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *pdwMailboxID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteLogonMailBoxAndSetNotifA( 
    /* [string][in] */ unsigned char __RPC_FAR *szMailbox,
    /* [string][in] */ unsigned char __RPC_FAR *szPassword,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwMailboxID,
    /* [string][in] */ unsigned char __RPC_FAR *szComputerName,
    /* [in] */ unsigned long ulNotifMask,
    /* [out] */ unsigned long __RPC_FAR *pulConnectionID)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          9);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U + 13U + 13U + 11U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szPassword,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szComputerName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = ulNotifMask;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[82] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[26],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *pdwMailboxID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        *pulConnectionID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteTerminateNotifA( 
    /* [string][in] */ unsigned char __RPC_FAR *szComputerName,
    /* [in] */ unsigned long ulConnectionID)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          10);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U + 11U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szComputerName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = ulConnectionID;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[110] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteValidateNotifA( 
    /* [string][in] */ unsigned char __RPC_FAR *szComputerName,
    /* [string][in] */ unsigned char __RPC_FAR *szMailboxName,
    /* [in] */ unsigned long ulNotifMask,
    /* [out] */ unsigned long __RPC_FAR *pulConnectionID)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          11);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U + 13U + 11U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailboxName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szComputerName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailboxName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = ulNotifMask;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[118] );
        
        *pulConnectionID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteOpenMsgUploadPipeA( 
    /* [string][in] */ unsigned char __RPC_FAR *szSenderMailbox,
    /* [out] */ long __RPC_FAR *pPipeNumber,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szCookie)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          12);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szSenderMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szSenderMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[134] );
        
        *pPipeNumber = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szCookie,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[36],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteSendMsgToAccountA( 
    /* [string][in] */ unsigned char __RPC_FAR *szRecipAccount,
    /* [string][in] */ unsigned char __RPC_FAR *szHeaderInfo,
    /* [string][in] */ unsigned char __RPC_FAR *szCookie)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          13);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U + 13U + 13U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szRecipAccount,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szHeaderInfo,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szCookie,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szRecipAccount,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szHeaderInfo,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szCookie,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[148] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteOpenMsgDownloadPipeA( 
    /* [string][in] */ unsigned char __RPC_FAR *szMailbox,
    /* [out] */ unsigned long __RPC_FAR *pPipeNumber)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          14);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[162] );
        
        *pPipeNumber = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteOpenHeaderDownloadPipeA( 
    /* [string][in] */ unsigned char __RPC_FAR *szMailbox,
    /* [out] */ long __RPC_FAR *pPipeNumber)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          15);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[162] );
        
        *pPipeNumber = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteCheckNewMailA( 
    /* [string][in] */ unsigned char __RPC_FAR *szMailbox,
    /* [out] */ unsigned long __RPC_FAR *pulPending)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          16);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[162] );
        
        *pulPending = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteOpenOneMsgDownloadPipeA( 
    /* [string][in] */ unsigned char __RPC_FAR *szMailbox,
    /* [out] */ long __RPC_FAR *pPipeNumber)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          17);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[6] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[162] );
        
        *pPipeNumber = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteGetRecipientPropsA( 
    /* [in] */ unsigned long dwObjID,
    /* [out] */ unsigned long __RPC_FAR *pdwUserType,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szMailboxName,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szFullName,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szJobTitle,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szOffice,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szPhone,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szAltPhone,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szFax,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szComments,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szCompany,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szDepartment,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szManagerName,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szManagerAlias,
    /* [out] */ unsigned long __RPC_FAR *pdwManagerID)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          18);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 4U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = dwObjID;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[172] );
        
        *pdwUserType = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailboxName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[46],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[56],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szJobTitle,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[66],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOffice,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[76],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szPhone,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[86],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szAltPhone,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[96],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szFax,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[106],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComments,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[116],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szCompany,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[126],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDepartment,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[136],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szManagerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[146],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szManagerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[156],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *pdwManagerID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteGetDistListPropsA( 
    /* [in] */ unsigned long dwObjID,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szDLAlias,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szDLFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwContentCount,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szOwnerAlias,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szOwnerName,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szComments)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          19);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 4U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = dwObjID;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[232] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDLAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[166],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDLFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[176],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *pdwContentCount = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOwnerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[186],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOwnerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[196],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComments,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[206],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteChangePasswordW( 
    /* [in] */ wchar_t __RPC_FAR *szMailbox,
    /* [string][in] */ wchar_t __RPC_FAR *szOldPassword,
    /* [string][in] */ wchar_t __RPC_FAR *szNewPassword)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          20);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 2U + 12U + 14U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szOldPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szNewPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        *(( wchar_t __RPC_FAR * )_StubMsg.Buffer)++ = *szMailbox;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szOldPassword,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szNewPassword,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[260] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteLogonMailBoxW( 
    /* [string][in] */ wchar_t __RPC_FAR *szMailbox,
    /* [string][in] */ wchar_t __RPC_FAR *szPassword,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwMailboxID)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          21);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U + 14U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szPassword,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[274] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[224],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *pdwMailboxID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteLogonMailBoxAndSetNotifW( 
    /* [string][in] */ wchar_t __RPC_FAR *szMailbox,
    /* [string][in] */ wchar_t __RPC_FAR *szPassword,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwMailboxID,
    /* [string][in] */ wchar_t __RPC_FAR *szComputerName,
    /* [in] */ unsigned long ulNotifMask,
    /* [out] */ unsigned long __RPC_FAR *pulConnectionID)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          22);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U + 14U + 14U + 10U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szPassword,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szPassword,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szComputerName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = ulNotifMask;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[292] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[234],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *pdwMailboxID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        *pulConnectionID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteTerminateNotifW( 
    /* [string][in] */ wchar_t __RPC_FAR *szComputerName,
    /* [in] */ unsigned long ulConnectionID)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          23);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U + 10U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szComputerName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = ulConnectionID;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[320] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteValidateNotifW( 
    /* [string][in] */ wchar_t __RPC_FAR *szComputerName,
    /* [string][in] */ wchar_t __RPC_FAR *szMailboxName,
    /* [in] */ unsigned long ulNotifMask,
    /* [out] */ unsigned long __RPC_FAR *pulConnectionID)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          24);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U + 14U + 10U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szComputerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailboxName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szComputerName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailboxName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = ulNotifMask;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[328] );
        
        *pulConnectionID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteOpenMsgUploadPipeW( 
    /* [string][in] */ wchar_t __RPC_FAR *szSenderMailbox,
    /* [out] */ long __RPC_FAR *pPipeNumber,
    /* [size_is][string][out] */ unsigned char __RPC_FAR *szCookie)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          25);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szSenderMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szSenderMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[344] );
        
        *pPipeNumber = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szCookie,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[244],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteSendMsgToAccountW( 
    /* [string][in] */ wchar_t __RPC_FAR *szRecipAccount,
    /* [string][in] */ wchar_t __RPC_FAR *szHeaderInfo,
    /* [string][in] */ wchar_t __RPC_FAR *szCookie)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          26);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U + 14U + 14U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szRecipAccount,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szHeaderInfo,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szCookie,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szRecipAccount,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szHeaderInfo,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szCookie,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[358] );
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteOpenMsgDownloadPipeW( 
    /* [string][in] */ wchar_t __RPC_FAR *szMailbox,
    /* [out] */ unsigned long __RPC_FAR *pPipeNumber)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          27);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[372] );
        
        *pPipeNumber = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteOpenHeaderDownloadPipeW( 
    /* [string][in] */ wchar_t __RPC_FAR *szMailbox,
    /* [out] */ long __RPC_FAR *pPipeNumber)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          28);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[372] );
        
        *pPipeNumber = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteCheckNewMailW( 
    /* [string][in] */ wchar_t __RPC_FAR *szMailbox,
    /* [out] */ unsigned long __RPC_FAR *pulPending)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          29);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[372] );
        
        *pulPending = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteOpenOneMsgDownloadPipeW( 
    /* [string][in] */ wchar_t __RPC_FAR *szMailbox,
    /* [out] */ long __RPC_FAR *pPipeNumber)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          30);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 12U;
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)szMailbox,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)szMailbox,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[218] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[372] );
        
        *pPipeNumber = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteGetRecipientPropsW( 
    /* [in] */ unsigned long dwObjID,
    /* [out] */ unsigned long __RPC_FAR *pdwUserType,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szMailboxName,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szFullName,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szJobTitle,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szOffice,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szPhone,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szAltPhone,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szFax,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szComments,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szCompany,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szDepartment,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szManagerName,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szManagerAlias,
    /* [out] */ unsigned long __RPC_FAR *pdwManagerID)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          31);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 4U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = dwObjID;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[382] );
        
        *pdwUserType = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szMailboxName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[254],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[264],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szJobTitle,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[274],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOffice,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[284],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szPhone,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[294],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szAltPhone,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[304],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szFax,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[314],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComments,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[324],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szCompany,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[334],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDepartment,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[344],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szManagerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[354],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szManagerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[364],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *pdwManagerID = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


long RemoteGetDistListPropsW( 
    /* [in] */ unsigned long dwObjID,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szDLAlias,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szDLFullName,
    /* [out] */ unsigned long __RPC_FAR *pdwContentCount,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szOwnerAlias,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szOwnerName,
    /* [size_is][string][out] */ wchar_t __RPC_FAR *szComments)
{

    RPC_BINDING_HANDLE _Handle  =   0;
    
    long _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&WINDSREM_StubDesc,
                          32);
        
        
        _Handle = hWINDSREM;
        
        
        _StubMsg.BufferLength = 4U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = dwObjID;
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[442] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDLAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[374],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szDLFullName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[384],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *pdwContentCount = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOwnerAlias,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[394],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szOwnerName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[404],
                                       (unsigned char)0 );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szComments,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[414],
                                       (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        _RetVal = *(( long __RPC_FAR * )_StubMsg.Buffer)++;
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
    return _RetVal;
}


static const MIDL_STUB_DESC WINDSREM_StubDesc = 
    {
    (void __RPC_FAR *)& WINDSREM___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &hWINDSREM,
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
