/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:06:20 1998
 */
/* Compiler settings for replay.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, oldnames
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "replay.h"

#define TYPE_FORMAT_STRING_SIZE   155                               
#define PROC_FORMAT_STRING_SIZE   63                                

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

/* Standard interface: dict, ver. 1.0,
   GUID={0x12345678,0x1234,0xABCD,{0xEF,0x00,0x01,0x23,0x45,0x67,0x89,0xAB}} */


extern RPC_DISPATCH_TABLE dict_DispatchTable;

static const RPC_SERVER_INTERFACE dict___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0x12345678,0x1234,0xABCD,{0xEF,0x00,0x01,0x23,0x45,0x67,0x89,0xAB}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &dict_DispatchTable,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE dict_ServerIfHandle = (RPC_IF_HANDLE)& dict___RpcServerInterface;

extern const MIDL_STUB_DESC dict_StubDesc;

void __RPC_STUB
dict_VDict_New(
    PRPC_MESSAGE _pRpcMessage )
{
    VDict_Status _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    short shared_dict;
    NDR_SCONTEXT v_dict;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dict_StubDesc);
    
    ( VDict __RPC_FAR * )v_dict = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        shared_dict = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        v_dict = NDRSContextUnmarshall( (char *)0, _pRpcMessage->DataRepresentation ); 
        
        
        _RetVal = VDict_New(shared_dict,( VDict __RPC_FAR * )NDRSContextValue(v_dict));
        
        _StubMsg.BufferLength = 20U + 2U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrServerContextMarshall(
                            ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                            ( NDR_SCONTEXT  )v_dict,
                            ( NDR_RUNDOWN  )VDict_rundown);
        
        NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&_RetVal,
                         13);
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dict_VDict_Find(
    PRPC_MESSAGE _pRpcMessage )
{
    VDict_Status _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    Record __RPC_FAR *__RPC_FAR *item;
    NDR_SCONTEXT v_dict;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dict_StubDesc);
    
    ( Record __RPC_FAR *__RPC_FAR * )item = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[8] );
        
        v_dict = NdrServerContextUnmarshall(( PMIDL_STUB_MESSAGE  )&_StubMsg);
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&item,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[12],
                              (unsigned char)0 );
        
        
        _RetVal = VDict_Find(( VDict  )*NDRSContextValue(v_dict),item);
        
        _StubMsg.BufferLength = 4U + 5U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)item,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[12] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)item,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[12] );
        
        NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&_RetVal,
                         13);
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)item,
                        &__MIDL_TypeFormatString.Format[12] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dict_VDict_Next(
    PRPC_MESSAGE _pRpcMessage )
{
    VDict_Status _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    Record __RPC_FAR *__RPC_FAR *item;
    NDR_SCONTEXT v_dict;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dict_StubDesc);
    
    ( Record __RPC_FAR *__RPC_FAR * )item = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[8] );
        
        v_dict = NdrServerContextUnmarshall(( PMIDL_STUB_MESSAGE  )&_StubMsg);
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&item,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[12],
                              (unsigned char)0 );
        
        
        _RetVal = VDict_Next(( VDict  )*NDRSContextValue(v_dict),item);
        
        _StubMsg.BufferLength = 4U + 5U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)item,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[12] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)item,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[12] );
        
        NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&_RetVal,
                         13);
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)item,
                        &__MIDL_TypeFormatString.Format[12] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dict_VDict_Prev(
    PRPC_MESSAGE _pRpcMessage )
{
    VDict_Status _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    Record __RPC_FAR *__RPC_FAR *item;
    NDR_SCONTEXT v_dict;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dict_StubDesc);
    
    ( Record __RPC_FAR *__RPC_FAR * )item = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[8] );
        
        v_dict = NdrServerContextUnmarshall(( PMIDL_STUB_MESSAGE  )&_StubMsg);
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&item,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[12],
                              (unsigned char)0 );
        
        
        _RetVal = VDict_Prev(( VDict  )*NDRSContextValue(v_dict),item);
        
        _StubMsg.BufferLength = 4U + 5U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)item,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[12] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)item,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[12] );
        
        NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&_RetVal,
                         13);
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)item,
                        &__MIDL_TypeFormatString.Format[12] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dict_VDict_Curr_Next(
    PRPC_MESSAGE _pRpcMessage )
{
    Record __RPC_FAR *_M0;
    VDict_Status _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    Record __RPC_FAR *__RPC_FAR *item;
    NDR_SCONTEXT v_dict;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dict_StubDesc);
    
    ( Record __RPC_FAR *__RPC_FAR * )item = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[18] );
        
        v_dict = NdrServerContextUnmarshall(( PMIDL_STUB_MESSAGE  )&_StubMsg);
        
        item = &_M0;
        _M0 = 0;
        
        _RetVal = VDict_Curr_Next(( VDict  )*NDRSContextValue(v_dict),item);
        
        _StubMsg.BufferLength = 4U + 5U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)item,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[42] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)item,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[42] );
        
        NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&_RetVal,
                         13);
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)item,
                        &__MIDL_TypeFormatString.Format[42] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dict_VDict_Curr_Prev(
    PRPC_MESSAGE _pRpcMessage )
{
    Record __RPC_FAR *_M1;
    VDict_Status _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    Record __RPC_FAR *__RPC_FAR *item;
    NDR_SCONTEXT v_dict;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dict_StubDesc);
    
    ( Record __RPC_FAR *__RPC_FAR * )item = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[18] );
        
        v_dict = NdrServerContextUnmarshall(( PMIDL_STUB_MESSAGE  )&_StubMsg);
        
        item = &_M1;
        _M1 = 0;
        
        _RetVal = VDict_Curr_Prev(( VDict  )*NDRSContextValue(v_dict),item);
        
        _StubMsg.BufferLength = 4U + 5U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)item,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[42] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)item,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[42] );
        
        NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&_RetVal,
                         13);
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)item,
                        &__MIDL_TypeFormatString.Format[42] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dict_VDict_Insert(
    PRPC_MESSAGE _pRpcMessage )
{
    VDict_Status _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    Record __RPC_FAR *item;
    NDR_SCONTEXT v_dict;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dict_StubDesc);
    
    ( Record __RPC_FAR * )item = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
        
        v_dict = NdrServerContextUnmarshall(( PMIDL_STUB_MESSAGE  )&_StubMsg);
        
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&item,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20],
                                   (unsigned char)0 );
        
        
        _RetVal = VDict_Insert(( VDict  )*NDRSContextValue(v_dict),item);
        
        _StubMsg.BufferLength = 2U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&_RetVal,
                         13);
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)item,
                        &__MIDL_TypeFormatString.Format[46] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dict_VDict_Delete(
    PRPC_MESSAGE _pRpcMessage )
{
    VDict_Status _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    Record __RPC_FAR *__RPC_FAR *item;
    NDR_SCONTEXT v_dict;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dict_StubDesc);
    
    ( Record __RPC_FAR *__RPC_FAR * )item = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[8] );
        
        v_dict = NdrServerContextUnmarshall(( PMIDL_STUB_MESSAGE  )&_StubMsg);
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&item,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[12],
                              (unsigned char)0 );
        
        
        _RetVal = VDict_Delete(( VDict  )*NDRSContextValue(v_dict),item);
        
        _StubMsg.BufferLength = 4U + 5U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)item,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[12] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)item,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[12] );
        
        NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&_RetVal,
                         13);
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)item,
                        &__MIDL_TypeFormatString.Format[12] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dict_VDict_Get_Dict(
    PRPC_MESSAGE _pRpcMessage )
{
    RDict __RPC_FAR *_M2;
    VDict_Status _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    RDict __RPC_FAR *__RPC_FAR *r_dict;
    NDR_SCONTEXT v_dict;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dict_StubDesc);
    
    ( RDict __RPC_FAR *__RPC_FAR * )r_dict = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[38] );
        
        v_dict = NdrServerContextUnmarshall(( PMIDL_STUB_MESSAGE  )&_StubMsg);
        
        r_dict = &_M2;
        _M2 = 0;
        
        _RetVal = VDict_Get_Dict(( VDict  )*NDRSContextValue(v_dict),r_dict);
        
        _StubMsg.BufferLength = 4U + 5U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)r_dict,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[50] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)r_dict,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[50] );
        
        NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&_RetVal,
                         13);
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)r_dict,
                        &__MIDL_TypeFormatString.Format[50] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dict_VDict_Curr_Item(
    PRPC_MESSAGE _pRpcMessage )
{
    Record __RPC_FAR *_M3;
    VDict_Status _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    Record __RPC_FAR *__RPC_FAR *item;
    NDR_SCONTEXT v_dict;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dict_StubDesc);
    
    ( Record __RPC_FAR *__RPC_FAR * )item = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[18] );
        
        v_dict = NdrServerContextUnmarshall(( PMIDL_STUB_MESSAGE  )&_StubMsg);
        
        item = &_M3;
        _M3 = 0;
        
        _RetVal = VDict_Curr_Item(( VDict  )*NDRSContextValue(v_dict),item);
        
        _StubMsg.BufferLength = 4U + 5U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)item,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[42] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)item,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[42] );
        
        NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&_RetVal,
                         13);
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)item,
                        &__MIDL_TypeFormatString.Format[42] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dict_VDict_Curr_Delete(
    PRPC_MESSAGE _pRpcMessage )
{
    Record __RPC_FAR *_M4;
    VDict_Status _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    Record __RPC_FAR *__RPC_FAR *item;
    NDR_SCONTEXT v_dict;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dict_StubDesc);
    
    ( Record __RPC_FAR *__RPC_FAR * )item = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[18] );
        
        v_dict = NdrServerContextUnmarshall(( PMIDL_STUB_MESSAGE  )&_StubMsg);
        
        item = &_M4;
        _M4 = 0;
        
        _RetVal = VDict_Curr_Delete(( VDict  )*NDRSContextValue(v_dict),item);
        
        _StubMsg.BufferLength = 4U + 5U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)item,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[42] );
        
        _StubMsg.BufferLength += 16;
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)item,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[42] );
        
        NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&_RetVal,
                         13);
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)item,
                        &__MIDL_TypeFormatString.Format[42] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dict_VDict_X_Dict(
    PRPC_MESSAGE _pRpcMessage )
{
    VDict_Status _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    NDR_SCONTEXT v_dict;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dict_StubDesc);
    
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[48] );
        
        v_dict = NdrServerContextUnmarshall(( PMIDL_STUB_MESSAGE  )&_StubMsg);
        
        
        _RetVal = VDict_X_Dict(( VDict  )*NDRSContextValue(v_dict));
        
        _StubMsg.BufferLength = 2U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&_RetVal,
                         13);
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dict_VDict_I_Dict(
    PRPC_MESSAGE _pRpcMessage )
{
    VDict_Status _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    short size;
    NDR_SCONTEXT v_dict;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dict_StubDesc);
    
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[54] );
        
        v_dict = NdrServerContextUnmarshall(( PMIDL_STUB_MESSAGE  )&_StubMsg);
        
        size = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        _RetVal = VDict_I_Dict(( VDict  )*NDRSContextValue(v_dict),size);
        
        _StubMsg.BufferLength = 2U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&_RetVal,
                         13);
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


static const MIDL_STUB_DESC dict_StubDesc = 
    {
    (void __RPC_FAR *)& dict___RpcServerInterface,
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
    0,
    0x303006e, /* MIDL Version 3.3.110 */
    0,
    0,
    0,  /* Reserved1 */
    0,  /* Reserved2 */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static RPC_DISPATCH_FUNCTION dict_table[] =
    {
    dict_VDict_New,
    dict_VDict_Find,
    dict_VDict_Next,
    dict_VDict_Prev,
    dict_VDict_Curr_Next,
    dict_VDict_Curr_Prev,
    dict_VDict_Insert,
    dict_VDict_Delete,
    dict_VDict_Get_Dict,
    dict_VDict_Curr_Item,
    dict_VDict_Curr_Delete,
    dict_VDict_X_Dict,
    dict_VDict_I_Dict,
    0
    };
RPC_DISPATCH_TABLE dict_DispatchTable = 
    {
    13,
    dict_table
    };

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/*  2 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  4 */	NdrFcShort( 0x0 ),	/* Type Offset=0 */
/*  6 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/*  8 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 10 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */
/* 12 */	
			0x50,		/* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 14 */	NdrFcShort( 0xc ),	/* Type Offset=12 */
/* 16 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/* 18 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 20 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */
/* 22 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 24 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */
/* 26 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/* 28 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 30 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */
/* 32 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 34 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */
/* 36 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/* 38 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 40 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */
/* 42 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 44 */	NdrFcShort( 0x32 ),	/* Type Offset=50 */
/* 46 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/* 48 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 50 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */
/* 52 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/* 54 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 56 */	NdrFcShort( 0x8 ),	/* Type Offset=8 */
/* 58 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 60 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x11, 0x0,	/* FC_RP */
/*  2 */	NdrFcShort( 0x2 ),	/* Offset= 2 (4) */
/*  4 */	0x30,		/* FC_BIND_CONTEXT */
			0xa0,		/* 160 */
/*  6 */	0x0,		/* 0 */
			0x1,		/* 1 */
/*  8 */	0x30,		/* FC_BIND_CONTEXT */
			0x40,		/* 64 */
/* 10 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 12 */	
			0x11, 0x10,	/* FC_RP */
/* 14 */	NdrFcShort( 0x2 ),	/* Offset= 2 (16) */
/* 16 */	
			0x12, 0x0,	/* FC_UP */
/* 18 */	NdrFcShort( 0x2 ),	/* Offset= 2 (20) */
/* 20 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 22 */	NdrFcShort( 0x8 ),	/* 8 */
/* 24 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 26 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 28 */	NdrFcShort( 0x4 ),	/* 4 */
/* 30 */	NdrFcShort( 0x4 ),	/* 4 */
/* 32 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 34 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/* 36 */	
			0x5b,		/* FC_END */

			0x6,		/* FC_SHORT */
/* 38 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 40 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 42 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 44 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (16) */
/* 46 */	
			0x11, 0x0,	/* FC_RP */
/* 48 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (20) */
/* 50 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 52 */	NdrFcShort( 0x2 ),	/* Offset= 2 (54) */
/* 54 */	
			0x12, 0x0,	/* FC_UP */
/* 56 */	NdrFcShort( 0x42 ),	/* Offset= 66 (122) */
/* 58 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 60 */	NdrFcShort( 0xc ),	/* 12 */
/* 62 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 64 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x0 ),	/* 0 */
/* 70 */	0x12, 0x0,	/* FC_UP */
/* 72 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (58) */
/* 74 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 76 */	NdrFcShort( 0x4 ),	/* 4 */
/* 78 */	NdrFcShort( 0x4 ),	/* 4 */
/* 80 */	0x12, 0x0,	/* FC_UP */
/* 82 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (58) */
/* 84 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 86 */	NdrFcShort( 0x8 ),	/* 8 */
/* 88 */	NdrFcShort( 0x8 ),	/* 8 */
/* 90 */	0x12, 0x0,	/* FC_UP */
/* 92 */	NdrFcShort( 0xffffffb8 ),	/* Offset= -72 (20) */
/* 94 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 96 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 98 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 100 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 102 */	NdrFcShort( 0x8 ),	/* 8 */
/* 104 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 106 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 108 */	NdrFcShort( 0x4 ),	/* 4 */
/* 110 */	NdrFcShort( 0x4 ),	/* 4 */
/* 112 */	0x12, 0x0,	/* FC_UP */
/* 114 */	NdrFcShort( 0xffffffa2 ),	/* Offset= -94 (20) */
/* 116 */	
			0x5b,		/* FC_END */

			0x6,		/* FC_SHORT */
/* 118 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 120 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 122 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 124 */	NdrFcShort( 0xc ),	/* 12 */
/* 126 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 128 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 134 */	0x12, 0x0,	/* FC_UP */
/* 136 */	NdrFcShort( 0xffffffb2 ),	/* Offset= -78 (58) */
/* 138 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 140 */	NdrFcShort( 0x8 ),	/* 8 */
/* 142 */	NdrFcShort( 0x8 ),	/* 8 */
/* 144 */	0x12, 0x0,	/* FC_UP */
/* 146 */	NdrFcShort( 0xffffffd2 ),	/* Offset= -46 (100) */
/* 148 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 150 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 152 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */

			0x0
        }
    };
