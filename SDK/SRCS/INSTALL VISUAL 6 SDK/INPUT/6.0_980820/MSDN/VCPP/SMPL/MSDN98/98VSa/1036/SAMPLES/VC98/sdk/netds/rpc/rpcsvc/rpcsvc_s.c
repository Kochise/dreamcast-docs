/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:08:56 1998
 */
/* Compiler settings for rpcsvc.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "rpcsvc.h"

#define TYPE_FORMAT_STRING_SIZE   395                               
#define PROC_FORMAT_STRING_SIZE   141                               

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;

extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;

/* Standard interface: RpcServiceSample, ver. 1.0,
   GUID={0x15cd3850,0x28ca,0x11ce,{0xa4,0xe8,0x00,0xaa,0x00,0x61,0x16,0xcb}} */


extern RPC_DISPATCH_TABLE RpcServiceSample_v1_0_DispatchTable;

static const RPC_SERVER_INTERFACE RpcServiceSample___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0x15cd3850,0x28ca,0x11ce,{0xa4,0xe8,0x00,0xaa,0x00,0x61,0x16,0xcb}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &RpcServiceSample_v1_0_DispatchTable,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE RpcServiceSample_v1_0_s_ifspec = (RPC_IF_HANDLE)& RpcServiceSample___RpcServerInterface;

extern const MIDL_STUB_DESC RpcServiceSample_StubDesc;

void __RPC_STUB
RpcServiceSample_Ping(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        
        _RetVal = Ping(Binding);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_CheckSecurity(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        
        _RetVal = CheckSecurity(Binding);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_BufferIn1(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    byte ( __RPC_FAR *Buffer )[  ];
    unsigned long BufferLength;
    unsigned long BufferSize;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    Buffer = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[4] );
        
        NdrConformantVaryingArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                             (unsigned char __RPC_FAR * __RPC_FAR *)&Buffer,
                                             (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[0],
                                             (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        BufferLength = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        BufferSize = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        _RetVal = BufferIn1(
                    Binding,
                    *Buffer,
                    BufferLength,
                    BufferSize);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        if ( Buffer )
            _StubMsg.pfnFree( Buffer );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_BufferIn2(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    byte ( __RPC_FAR *Buffer )[ 16384 ];
    unsigned long BufferLength;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    Buffer = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[16] );
        
        NdrVaryingArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&Buffer,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[14],
                                   (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        BufferLength = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        _RetVal = BufferIn2(
                    Binding,
                    *Buffer,
                    BufferLength);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        if ( Buffer )
            _StubMsg.pfnFree( Buffer );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_BufferIn3(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    byte ( __RPC_FAR *Buffer )[  ];
    unsigned long BufferLength;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    Buffer = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[26] );
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&Buffer,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[28],
                                      (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        BufferLength = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        _RetVal = BufferIn3(
                    Binding,
                    *Buffer,
                    BufferLength);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_BufferOut1(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    byte ( __RPC_FAR *Buffer )[ 16384 ];
    unsigned long _M13;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pBufferLength;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    Buffer = 0;
    ( unsigned long __RPC_FAR * )pBufferLength = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[36] );
        
        NdrVaryingArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&Buffer,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[38],
                                   (unsigned char)0 );
        
        pBufferLength = &_M13;
        
        _RetVal = BufferOut1(
                     Binding,
                     *Buffer,
                     pBufferLength);
        
        _StubMsg.BufferLength = 4U + 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pBufferLength;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        if ( Buffer )
            _StubMsg.pfnFree( Buffer );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_BufferOut2(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    byte ( __RPC_FAR *Buffer )[  ];
    unsigned long BufferSize;
    unsigned long _M14;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pBufferLength;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    Buffer = 0;
    ( unsigned long __RPC_FAR * )pBufferLength = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[48] );
        
        BufferSize = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        Buffer = _StubMsg.pfnAllocate(BufferSize * 1);
        pBufferLength = &_M14;
        
        _RetVal = BufferOut2(
                     Binding,
                     *Buffer,
                     BufferSize,
                     pBufferLength);
        
        _StubMsg.BufferLength = 12U + 11U + 7U;
        _StubMsg.MaxCount = BufferSize;
        _StubMsg.Offset = 0;
        _StubMsg.ActualCount = pBufferLength ? *pBufferLength : 0;
        
        NdrConformantVaryingArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                             (unsigned char __RPC_FAR *)*Buffer,
                                             (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[56] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        _StubMsg.MaxCount = BufferSize;
        _StubMsg.Offset = 0;
        _StubMsg.ActualCount = pBufferLength ? *pBufferLength : 0;
        
        NdrConformantVaryingArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                           (unsigned char __RPC_FAR *)*Buffer,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[56] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pBufferLength;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        if ( Buffer )
            _StubMsg.pfnFree( Buffer );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_BufferOut3(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BUFFER _pBufferM;
    BUFFER __RPC_FAR *pBuffer;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    ( BUFFER __RPC_FAR * )pBuffer = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[62] );
        
        pBuffer = &_pBufferM;
        pBuffer -> Buffer = 0;
        
        _RetVal = BufferOut3(Binding,pBuffer);
        
        _StubMsg.BufferLength = 0U + 11U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)pBuffer,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[84] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)pBuffer,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[84] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pBuffer,
                        &__MIDL_TypeFormatString.Format[70] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_BufferOut4(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    byte ( __RPC_FAR *Buffer )[  ];
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned long __RPC_FAR *pBufferLength;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    Buffer = 0;
    ( unsigned long __RPC_FAR * )pBufferLength = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[70] );
        
        pBufferLength = ( unsigned long __RPC_FAR * )_StubMsg.Buffer;
        _StubMsg.Buffer += sizeof( unsigned long  );
        
        Buffer = _StubMsg.pfnAllocate(*pBufferLength * 1);
        
        _RetVal = BufferOut4(
                     Binding,
                     *Buffer,
                     pBufferLength);
        
        _StubMsg.BufferLength = 4U + 11U + 7U;
        _StubMsg.MaxCount = pBufferLength ? *pBufferLength : 0;
        
        NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)*Buffer,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[104] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        _StubMsg.MaxCount = pBufferLength ? *pBufferLength : 0;
        
        NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)*Buffer,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[104] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++ = *pBufferLength;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        if ( Buffer )
            _StubMsg.pfnFree( Buffer );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_StructsIn1(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    struct BAD1 ( __RPC_FAR *array )[ 50 ];
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    array = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[82] );
        
        NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&array,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[130],
                                   (unsigned char)0 );
        
        
        _RetVal = StructsIn1(Binding,*array);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrComplexArrayFree( &_StubMsg,
                             (unsigned char __RPC_FAR *)array,
                             &__MIDL_TypeFormatString.Format[130] );
        
        if ( array )
            _StubMsg.pfnFree( array );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_StructsIn2(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    struct BAD2 ( __RPC_FAR *array )[ 50 ];
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    array = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[90] );
        
        NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&array,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[160],
                                   (unsigned char)0 );
        
        
        _RetVal = StructsIn2(Binding,*array);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrComplexArrayFree( &_StubMsg,
                             (unsigned char __RPC_FAR *)array,
                             &__MIDL_TypeFormatString.Format[160] );
        
        if ( array )
            _StubMsg.pfnFree( array );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_StructsIn3(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    struct GOOD ( __RPC_FAR *array )[ 50 ];
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    array = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[98] );
        
        NdrFixedArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                 (unsigned char __RPC_FAR * __RPC_FAR *)&array,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[186],
                                 (unsigned char)0 );
        
        
        _RetVal = StructsIn3(Binding,*array);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_ListIn(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    PLIST pList;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    ( PLIST  )pList = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[106] );
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&pList,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[196],
                              (unsigned char)0 );
        
        
        _RetVal = ListIn(Binding,pList);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pList,
                        &__MIDL_TypeFormatString.Format[196] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_ListOut1(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LIST _pListHeadM;
    LIST __RPC_FAR *pListHead;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    ( LIST __RPC_FAR * )pListHead = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[114] );
        
        pListHead = &_pListHeadM;
        pListHead -> pNext = 0;
        
        _RetVal = ListOut1(Binding,pListHead);
        
        _StubMsg.BufferLength = 0U + 11U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)pListHead,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[200] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)pListHead,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[200] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pListHead,
                        &__MIDL_TypeFormatString.Format[220] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_ListOut2(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LIST _pListHeadM;
    LIST __RPC_FAR *pListHead;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    NdrRpcSsEnableAllocate(&_StubMsg);
    Binding = _pRpcMessage->Handle;
    ( LIST __RPC_FAR * )pListHead = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[114] );
        
        pListHead = &_pListHeadM;
        pListHead -> pNext = 0;
        
        _RetVal = ListOut2(Binding,pListHead);
        
        _StubMsg.BufferLength = 0U + 11U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)pListHead,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[200] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)pListHead,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[200] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrRpcSsDisableAllocate(&_StubMsg);
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_UnionCall1(
    PRPC_MESSAGE _pRpcMessage )
{
    BAD_UNION ( __RPC_FAR *ArrayOfUnions )[  ];
    handle_t Binding;
    unsigned long Length;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    ArrayOfUnions = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[122] );
        
        Length = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&ArrayOfUnions,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[264],
                                   (unsigned char)0 );
        
        
        _RetVal = UnionCall1(
                     Binding,
                     Length,
                     *ArrayOfUnions);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = Length;
        
        NdrComplexArrayFree( &_StubMsg,
                             (unsigned char __RPC_FAR *)ArrayOfUnions,
                             &__MIDL_TypeFormatString.Format[264] );
        
        if ( ArrayOfUnions )
            _StubMsg.pfnFree( ArrayOfUnions );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
RpcServiceSample_UnionCall2(
    PRPC_MESSAGE _pRpcMessage )
{
    handle_t Binding;
    error_status_t _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    GOOD_UNION __RPC_FAR *pUnionContainingArrays;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &RpcServiceSample_StubDesc);
    
    Binding = _pRpcMessage->Handle;
    ( GOOD_UNION __RPC_FAR * )pUnionContainingArrays = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[132] );
        
        NdrComplexStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                    (unsigned char __RPC_FAR * __RPC_FAR *)&pUnionContainingArrays,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[380],
                                    (unsigned char)0 );
        
        
        _RetVal = UnionCall2(Binding,pUnionContainingArrays);
        
        _StubMsg.BufferLength = 4U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        *(( error_status_t __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pUnionContainingArrays,
                        &__MIDL_TypeFormatString.Format[282] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

extern MALLOC_FREE_STRUCT _MallocFreeStruct;

static const MIDL_STUB_DESC RpcServiceSample_StubDesc = 
    {
    (void __RPC_FAR *)& RpcServiceSample___RpcServerInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    0, /* -error bounds_check flag */
    0x10001, /* Ndr library version */
    &_MallocFreeStruct,
    0x303006e, /* MIDL Version 3.3.110 */
    0,
    0,
    0,  /* Reserved1 */
    0,  /* Reserved2 */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static RPC_DISPATCH_FUNCTION RpcServiceSample_table[] =
    {
    RpcServiceSample_Ping,
    RpcServiceSample_CheckSecurity,
    RpcServiceSample_BufferIn1,
    RpcServiceSample_BufferIn2,
    RpcServiceSample_BufferIn3,
    RpcServiceSample_BufferOut1,
    RpcServiceSample_BufferOut2,
    RpcServiceSample_BufferOut3,
    RpcServiceSample_BufferOut4,
    RpcServiceSample_StructsIn1,
    RpcServiceSample_StructsIn2,
    RpcServiceSample_StructsIn3,
    RpcServiceSample_ListIn,
    RpcServiceSample_ListOut1,
    RpcServiceSample_ListOut2,
    RpcServiceSample_UnionCall1,
    RpcServiceSample_UnionCall2,
    0
    };
RPC_DISPATCH_TABLE RpcServiceSample_v1_0_DispatchTable = 
    {
    17,
    RpcServiceSample_table
    };

static void __RPC_FAR * __RPC_USER
RpcServiceSample_malloc_wrapper( size_t _Size )
{
    return( malloc( _Size ) );
}

static void  __RPC_USER
RpcServiceSample_free_wrapper( void __RPC_FAR * _p )
{
    free( _p );
}

static MALLOC_FREE_STRUCT _MallocFreeStruct = 
{
    RpcServiceSample_malloc_wrapper,
    RpcServiceSample_free_wrapper
};

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/*  2 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/*  4 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/*  6 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  8 */	NdrFcShort( 0x0 ),	/* Type Offset=0 */
/* 10 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 12 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 14 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/* 16 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/* 18 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 20 */	NdrFcShort( 0xe ),	/* Type Offset=14 */
/* 22 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 24 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/* 26 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/* 28 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 30 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */
/* 32 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 34 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/* 36 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/* 38 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 40 */	NdrFcShort( 0x26 ),	/* Type Offset=38 */
/* 42 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 44 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */
/* 46 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/* 48 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/* 50 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 52 */	NdrFcShort( 0x38 ),	/* Type Offset=56 */
/* 54 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 56 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 58 */	NdrFcShort( 0x34 ),	/* Type Offset=52 */
/* 60 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/* 62 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/* 64 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 66 */	NdrFcShort( 0x46 ),	/* Type Offset=70 */
/* 68 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/* 70 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/* 72 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 74 */	NdrFcShort( 0x68 ),	/* Type Offset=104 */
/* 76 */	
			0x50,		/* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 78 */	NdrFcShort( 0x72 ),	/* Type Offset=114 */
/* 80 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/* 82 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/* 84 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 86 */	NdrFcShort( 0x82 ),	/* Type Offset=130 */
/* 88 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/* 90 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/* 92 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 94 */	NdrFcShort( 0xa0 ),	/* Type Offset=160 */
/* 96 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/* 98 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/* 100 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 102 */	NdrFcShort( 0xba ),	/* Type Offset=186 */
/* 104 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/* 106 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/* 108 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 110 */	NdrFcShort( 0xc4 ),	/* Type Offset=196 */
/* 112 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/* 114 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/* 116 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 118 */	NdrFcShort( 0xdc ),	/* Type Offset=220 */
/* 120 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/* 122 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/* 124 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 126 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 128 */	NdrFcShort( 0x108 ),	/* Type Offset=264 */
/* 130 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */
/* 132 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xf,		/* FC_IGNORE */
/* 134 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 136 */	NdrFcShort( 0x11a ),	/* Type Offset=282 */
/* 138 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x10,		/* FC_ERROR_STATUS_T */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			
			0x1c,		/* FC_CVARRAY */
			0x0,		/* 0 */
/*  2 */	NdrFcShort( 0x1 ),	/* 1 */
/*  4 */	0x29,		/* 41 */
			0x0,		/*  */
#ifndef _ALPHA_
/*  6 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/*  8 */	0x29,		/* 41 */
			0x0,		/*  */
#ifndef _ALPHA_
/* 10 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 12 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 14 */	
			0x1f,		/* FC_SMVARRAY */
			0x0,		/* 0 */
/* 16 */	NdrFcShort( 0x4000 ),	/* 16384 */
/* 18 */	NdrFcShort( 0x4000 ),	/* 16384 */
/* 20 */	NdrFcShort( 0x1 ),	/* 1 */
/* 22 */	0x29,		/* 41 */
			0x0,		/*  */
#ifndef _ALPHA_
/* 24 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 26 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 28 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 30 */	NdrFcShort( 0x1 ),	/* 1 */
/* 32 */	0x29,		/* 41 */
			0x0,		/*  */
#ifndef _ALPHA_
/* 34 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 36 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 38 */	
			0x1f,		/* FC_SMVARRAY */
			0x0,		/* 0 */
/* 40 */	NdrFcShort( 0x4000 ),	/* 16384 */
/* 42 */	NdrFcShort( 0x4000 ),	/* 16384 */
/* 44 */	NdrFcShort( 0x1 ),	/* 1 */
/* 46 */	0x29,		/* 41 */
			0x54,		/* FC_DEREFERENCE */
#ifndef _ALPHA_
/* 48 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 50 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 52 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 54 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 56 */	
			0x1c,		/* FC_CVARRAY */
			0x0,		/* 0 */
/* 58 */	NdrFcShort( 0x1 ),	/* 1 */
/* 60 */	0x29,		/* 41 */
			0x0,		/*  */
#ifndef _ALPHA_
/* 62 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 64 */	0x29,		/* 41 */
			0x54,		/* FC_DEREFERENCE */
#ifndef _ALPHA_
/* 66 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 68 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 70 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 72 */	NdrFcShort( 0xc ),	/* Offset= 12 (84) */
/* 74 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 76 */	NdrFcShort( 0x1 ),	/* 1 */
/* 78 */	0x19,		/* 25 */
			0x0,		/*  */
/* 80 */	NdrFcShort( 0x0 ),	/* 0 */
/* 82 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 84 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 86 */	NdrFcShort( 0x8 ),	/* 8 */
/* 88 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 90 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 92 */	NdrFcShort( 0x4 ),	/* 4 */
/* 94 */	NdrFcShort( 0x4 ),	/* 4 */
/* 96 */	0x12, 0x0,	/* FC_UP */
/* 98 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (74) */
/* 100 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 102 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 104 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 106 */	NdrFcShort( 0x1 ),	/* 1 */
/* 108 */	0x29,		/* 41 */
			0x54,		/* FC_DEREFERENCE */
#ifndef _ALPHA_
/* 110 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 112 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 114 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 116 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 118 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 120 */	NdrFcShort( 0x8 ),	/* 8 */
/* 122 */	NdrFcShort( 0x0 ),	/* 0 */
/* 124 */	NdrFcShort( 0x0 ),	/* Offset= 0 (124) */
/* 126 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 128 */	0x3e,		/* FC_STRUCTPAD2 */
			0x5b,		/* FC_END */
/* 130 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 132 */	NdrFcShort( 0x32 ),	/* 50 */
/* 134 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 138 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 142 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 144 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (118) */
/* 146 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 148 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 150 */	NdrFcShort( 0x8 ),	/* 8 */
/* 152 */	NdrFcShort( 0x0 ),	/* 0 */
/* 154 */	NdrFcShort( 0x0 ),	/* Offset= 0 (154) */
/* 156 */	0xd,		/* FC_ENUM16 */
			0x8,		/* FC_LONG */
/* 158 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 160 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 162 */	NdrFcShort( 0x32 ),	/* 50 */
/* 164 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 168 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 172 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 174 */	NdrFcShort( 0xffffffe6 ),	/* Offset= -26 (148) */
/* 176 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 178 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 180 */	NdrFcShort( 0xc ),	/* 12 */
/* 182 */	0xe,		/* FC_ENUM32 */
			0x8,		/* FC_LONG */
/* 184 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 186 */	
			0x1d,		/* FC_SMFARRAY */
			0x3,		/* 3 */
/* 188 */	NdrFcShort( 0x258 ),	/* 600 */
/* 190 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 192 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (178) */
/* 194 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 196 */	
			0x12, 0x0,	/* FC_UP */
/* 198 */	NdrFcShort( 0x2 ),	/* Offset= 2 (200) */
/* 200 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 202 */	NdrFcShort( 0x8 ),	/* 8 */
/* 204 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 206 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 208 */	NdrFcShort( 0x0 ),	/* 0 */
/* 210 */	NdrFcShort( 0x0 ),	/* 0 */
/* 212 */	0x12, 0x0,	/* FC_UP */
/* 214 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (200) */
/* 216 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 218 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 220 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 222 */	NdrFcShort( 0xffffffea ),	/* Offset= -22 (200) */
/* 224 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 226 */	0x9,		/* 9 */
			0x0,		/*  */
/* 228 */	NdrFcShort( 0xfffffff8 ),	/* -8 */
/* 230 */	NdrFcShort( 0x2 ),	/* Offset= 2 (232) */
/* 232 */	NdrFcShort( 0x8 ),	/* 8 */
/* 234 */	NdrFcShort( 0x2 ),	/* 2 */
/* 236 */	NdrFcLong( 0x1 ),	/* 1 */
/* 240 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32520) */
/* 242 */	NdrFcLong( 0x2 ),	/* 2 */
/* 246 */	NdrFcShort( 0xffff800b ),	/* Offset= -32757 (-32511) */
/* 248 */	NdrFcShort( 0x0 ),	/* Offset= 0 (248) */
/* 250 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 252 */	NdrFcShort( 0x10 ),	/* 16 */
/* 254 */	NdrFcShort( 0x0 ),	/* 0 */
/* 256 */	NdrFcShort( 0x0 ),	/* Offset= 0 (256) */
/* 258 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 260 */	0x4,		/* 4 */
			NdrFcShort( 0xffffffdb ),	/* Offset= -37 (224) */
			0x5b,		/* FC_END */
/* 264 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x7,		/* 7 */
/* 266 */	NdrFcShort( 0x0 ),	/* 0 */
/* 268 */	0x29,		/* 41 */
			0x0,		/*  */
#ifndef _ALPHA_
/* 270 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 272 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 276 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 278 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (250) */
/* 280 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 282 */	
			0x11, 0x0,	/* FC_RP */
/* 284 */	NdrFcShort( 0x60 ),	/* Offset= 96 (380) */
/* 286 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 288 */	0x9,		/* 9 */
			0x0,		/*  */
/* 290 */	NdrFcShort( 0xfffffffc ),	/* -4 */
/* 292 */	NdrFcShort( 0x2 ),	/* Offset= 2 (294) */
/* 294 */	NdrFcShort( 0x4 ),	/* 4 */
/* 296 */	NdrFcShort( 0x2 ),	/* 2 */
/* 298 */	NdrFcLong( 0x1 ),	/* 1 */
/* 302 */	NdrFcShort( 0xa ),	/* Offset= 10 (312) */
/* 304 */	NdrFcLong( 0x2 ),	/* 2 */
/* 308 */	NdrFcShort( 0x26 ),	/* Offset= 38 (346) */
/* 310 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (309) */
/* 312 */	
			0x12, 0x0,	/* FC_UP */
/* 314 */	NdrFcShort( 0xc ),	/* Offset= 12 (326) */
/* 316 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 318 */	NdrFcShort( 0x4 ),	/* 4 */
/* 320 */	0x19,		/* 25 */
			0x0,		/*  */
/* 322 */	NdrFcShort( 0x0 ),	/* 0 */
/* 324 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 326 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 328 */	NdrFcShort( 0x8 ),	/* 8 */
/* 330 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 332 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 334 */	NdrFcShort( 0x4 ),	/* 4 */
/* 336 */	NdrFcShort( 0x4 ),	/* 4 */
/* 338 */	0x12, 0x0,	/* FC_UP */
/* 340 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (316) */
/* 342 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 344 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 346 */	
			0x12, 0x0,	/* FC_UP */
/* 348 */	NdrFcShort( 0xc ),	/* Offset= 12 (360) */
/* 350 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 352 */	NdrFcShort( 0x8 ),	/* 8 */
/* 354 */	0x19,		/* 25 */
			0x0,		/*  */
/* 356 */	NdrFcShort( 0x0 ),	/* 0 */
/* 358 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 360 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 362 */	NdrFcShort( 0x8 ),	/* 8 */
/* 364 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 366 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 368 */	NdrFcShort( 0x4 ),	/* 4 */
/* 370 */	NdrFcShort( 0x4 ),	/* 4 */
/* 372 */	0x12, 0x0,	/* FC_UP */
/* 374 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (350) */
/* 376 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 378 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 380 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 382 */	NdrFcShort( 0x8 ),	/* 8 */
/* 384 */	NdrFcShort( 0x0 ),	/* 0 */
/* 386 */	NdrFcShort( 0x0 ),	/* Offset= 0 (386) */
/* 388 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 390 */	0x0,		/* 0 */
			NdrFcShort( 0xffffff97 ),	/* Offset= -105 (286) */
			0x5b,		/* FC_END */

			0x0
        }
    };
