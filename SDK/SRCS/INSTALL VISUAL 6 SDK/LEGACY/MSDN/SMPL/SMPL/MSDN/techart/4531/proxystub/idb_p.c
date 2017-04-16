/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 2.00.0102 */
/* at Wed Oct 18 18:02:19 1995
 */
//@@MIDL_FILE_HEADING(  )

#include "rpcproxy.h"
#include "..\interface\idb.h"


extern const MIDL_FORMAT_STRING __MIDLFormatString;

extern const MIDL_FORMAT_STRING __MIDLProcFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

HRESULT __stdcall IDB_Read_Proxy( 
    IDB __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [in] */ short nRow,
    /* [size_is][out] */ LPWSTR lpszData)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
            
            
            
            
            _StubMsg.BufferLength = 2U + 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nTable;
            
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nRow;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[0] );
            
            NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR * __RPC_FAR *)&lpszData,
                                           (PFORMAT_STRING) &__MIDLFormatString.Format[4],
                                           (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = 80;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[0],
                         ( void __RPC_FAR * )lpszData);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDB_Read_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LPWSTR lpszData;
    short nRow;
    short nTable;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lpszData = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[0] );
        
        nTable = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        nRow = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        lpszData = _StubMsg.pfnAllocate(80 * 2);
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDB *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Read(
        (IDB *) ((CStdStubBuffer *)This)->pvServerObject,
        nTable,
        nRow,
        lpszData);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 12U + 10U;
        _StubMsg.MaxCount = 80;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)lpszData,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[4] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = 80;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)lpszData,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[4] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 80;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpszData,
                        &__MIDLFormatString.Format[0] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IDB_Write_Proxy( 
    IDB __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [in] */ short nRow,
    /* [in] */ LPCWSTR lpszData)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
            
            
            
            
            _StubMsg.BufferLength = 2U + 2U + 12U;
            NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)lpszData,
                                           (PFORMAT_STRING) &__MIDLFormatString.Format[12] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nTable;
            
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nRow;
            
            NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)lpszData,
                                         (PFORMAT_STRING) &__MIDLFormatString.Format[12] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[10] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDB_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LPCWSTR lpszData;
    short nRow;
    short nTable;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lpszData = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[10] );
        
        nTable = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        nRow = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&lpszData,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[12],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDB *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Write(
         (IDB *) ((CStdStubBuffer *)This)->pvServerObject,
         nTable,
         nRow,
         lpszData);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IDB_Create_Proxy( 
    IDB __RPC_FAR * This,
    /* [out] */ REFSHORT nTable,
    /* [in] */ LPCWSTR lpszName)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
            
            
            
            
            _StubMsg.BufferLength = 12U;
            NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)lpszName,
                                           (PFORMAT_STRING) &__MIDLFormatString.Format[12] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)lpszName,
                                         (PFORMAT_STRING) &__MIDLFormatString.Format[12] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[20] );
            
            *nTable = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer += 2;
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[14],
                         ( void __RPC_FAR * )nTable);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDB_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    short _M6;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LPCWSTR lpszName;
    REFSHORT nTable;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    nTable = 0;
    lpszName = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[20] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&lpszName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[12],
                                       (unsigned char)0 );
        
        nTable = &_M6;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDB *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Create(
          (IDB *) ((CStdStubBuffer *)This)->pvServerObject,
          nTable,
          lpszName);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 2U + 6U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( short __RPC_FAR * )_StubMsg.Buffer)++ = *nTable;
        
        _StubMsg.Buffer += 2;
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IDB_Delete_Proxy( 
    IDB __RPC_FAR * This,
    /* [in] */ short nTable)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
            
            
            
            
            _StubMsg.BufferLength = 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nTable;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[30] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDB_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    short nTable;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[30] );
        
        nTable = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDB *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Delete((IDB *) ((CStdStubBuffer *)This)->pvServerObject,nTable);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IDB_GetNumTables_Proxy( 
    IDB __RPC_FAR * This,
    /* [out] */ REFSHORT nNumTables)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      7);
            
            
            
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[34] );
            
            *nNumTables = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer += 2;
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[14],
                         ( void __RPC_FAR * )nNumTables);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDB_GetNumTables_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    short _M7;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    REFSHORT nNumTables;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    nNumTables = 0;
    RpcTryFinally
        {
        nNumTables = &_M7;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDB *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetNumTables((IDB *) ((CStdStubBuffer *)This)->pvServerObject,nNumTables);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 2U + 6U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( short __RPC_FAR * )_StubMsg.Buffer)++ = *nNumTables;
        
        _StubMsg.Buffer += 2;
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IDB_GetTableName_Proxy( 
    IDB __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [size_is][out] */ LPWSTR lpszName)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      8);
            
            
            
            
            _StubMsg.BufferLength = 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nTable;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[40] );
            
            NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR * __RPC_FAR *)&lpszName,
                                           (PFORMAT_STRING) &__MIDLFormatString.Format[22],
                                           (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = 80;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[18],
                         ( void __RPC_FAR * )lpszName);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDB_GetTableName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LPWSTR lpszName;
    short nTable;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lpszName = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[40] );
        
        nTable = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        lpszName = _StubMsg.pfnAllocate(80 * 2);
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDB *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetTableName(
                (IDB *) ((CStdStubBuffer *)This)->pvServerObject,
                nTable,
                lpszName);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 12U + 10U;
        _StubMsg.MaxCount = 80;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)lpszName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[22] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = 80;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)lpszName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[22] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 80;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpszName,
                        &__MIDLFormatString.Format[18] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IDB_GetNumRows_Proxy( 
    IDB __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [out] */ REFSHORT nRows)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      9);
            
            
            
            
            _StubMsg.BufferLength = 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nTable;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[48] );
            
            *nRows = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer += 2;
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[14],
                         ( void __RPC_FAR * )nRows);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDB_GetNumRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    short _M10;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    REFSHORT nRows;
    short nTable;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    nRows = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[48] );
        
        nTable = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        nRows = &_M10;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDB *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetNumRows(
              (IDB *) ((CStdStubBuffer *)This)->pvServerObject,
              nTable,
              nRows);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 2U + 6U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( short __RPC_FAR * )_StubMsg.Buffer)++ = *nRows;
        
        _StubMsg.Buffer += 2;
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CInterfaceProxyVtbl _IDBProxyVtbl = 
{
    &IID_IDB,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IDB_Read_Proxy ,
    IDB_Write_Proxy ,
    IDB_Create_Proxy ,
    IDB_Delete_Proxy ,
    IDB_GetNumTables_Proxy ,
    IDB_GetTableName_Proxy ,
    IDB_GetNumRows_Proxy
};


static const PRPC_STUB_FUNCTION IDB_table[] =
{
    IDB_Read_Stub,
    IDB_Write_Stub,
    IDB_Create_Stub,
    IDB_Delete_Stub,
    IDB_GetNumTables_Stub,
    IDB_GetTableName_Stub,
    IDB_GetNumRows_Stub
};

const CInterfaceStubVtbl _IDBStubVtbl =
{
    &IID_IDB,
    0,
    10,
    &IDB_table[-3],
    CStdStubBuffer_METHODS
};


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

HRESULT __stdcall IDBAccess_Read_Proxy( 
    IDBAccess __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [in] */ short nRow,
    /* [size_is][out] */ LPWSTR lpszData)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
            
            
            
            
            _StubMsg.BufferLength = 2U + 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nTable;
            
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nRow;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[56] );
            
            NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR * __RPC_FAR *)&lpszData,
                                           (PFORMAT_STRING) &__MIDLFormatString.Format[32],
                                           (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = 80;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[28],
                         ( void __RPC_FAR * )lpszData);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDBAccess_Read_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LPWSTR lpszData;
    short nRow;
    short nTable;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lpszData = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[56] );
        
        nTable = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        nRow = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        lpszData = _StubMsg.pfnAllocate(80 * 2);
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDBAccess *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Read(
        (IDBAccess *) ((CStdStubBuffer *)This)->pvServerObject,
        nTable,
        nRow,
        lpszData);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 12U + 10U;
        _StubMsg.MaxCount = 80;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)lpszData,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[32] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = 80;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)lpszData,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[32] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 80;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpszData,
                        &__MIDLFormatString.Format[28] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IDBAccess_Write_Proxy( 
    IDBAccess __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [in] */ short nRow,
    /* [in] */ LPCWSTR lpszData)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
            
            
            
            
            _StubMsg.BufferLength = 2U + 2U + 12U;
            NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)lpszData,
                                           (PFORMAT_STRING) &__MIDLFormatString.Format[12] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nTable;
            
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nRow;
            
            NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)lpszData,
                                         (PFORMAT_STRING) &__MIDLFormatString.Format[12] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[10] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDBAccess_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LPCWSTR lpszData;
    short nRow;
    short nTable;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lpszData = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[10] );
        
        nTable = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        nRow = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&lpszData,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[12],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDBAccess *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Write(
         (IDBAccess *) ((CStdStubBuffer *)This)->pvServerObject,
         nTable,
         nRow,
         lpszData);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CInterfaceProxyVtbl _IDBAccessProxyVtbl = 
{
    &IID_IDBAccess,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IDBAccess_Read_Proxy ,
    IDBAccess_Write_Proxy
};


static const PRPC_STUB_FUNCTION IDBAccess_table[] =
{
    IDBAccess_Read_Stub,
    IDBAccess_Write_Stub
};

const CInterfaceStubVtbl _IDBAccessStubVtbl =
{
    &IID_IDBAccess,
    0,
    5,
    &IDBAccess_table[-3],
    CStdStubBuffer_METHODS
};


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

HRESULT __stdcall IDBManage_Create_Proxy( 
    IDBManage __RPC_FAR * This,
    /* [out] */ REFSHORT nTable,
    /* [in] */ LPCWSTR lpszName)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
            
            
            
            
            _StubMsg.BufferLength = 12U;
            NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)lpszName,
                                           (PFORMAT_STRING) &__MIDLFormatString.Format[12] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)lpszName,
                                         (PFORMAT_STRING) &__MIDLFormatString.Format[12] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[20] );
            
            *nTable = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer += 2;
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[14],
                         ( void __RPC_FAR * )nTable);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDBManage_Create_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    short _M17;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LPCWSTR lpszName;
    REFSHORT nTable;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    nTable = 0;
    lpszName = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[20] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&lpszName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[12],
                                       (unsigned char)0 );
        
        nTable = &_M17;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDBManage *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Create(
          (IDBManage *) ((CStdStubBuffer *)This)->pvServerObject,
          nTable,
          lpszName);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 2U + 6U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( short __RPC_FAR * )_StubMsg.Buffer)++ = *nTable;
        
        _StubMsg.Buffer += 2;
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IDBManage_Delete_Proxy( 
    IDBManage __RPC_FAR * This,
    /* [in] */ short nTable)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
            
            
            
            
            _StubMsg.BufferLength = 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nTable;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[30] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDBManage_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    short nTable;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[30] );
        
        nTable = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDBManage *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Delete((IDBManage *) ((CStdStubBuffer *)This)->pvServerObject,nTable);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CInterfaceProxyVtbl _IDBManageProxyVtbl = 
{
    &IID_IDBManage,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IDBManage_Create_Proxy ,
    IDBManage_Delete_Proxy
};


static const PRPC_STUB_FUNCTION IDBManage_table[] =
{
    IDBManage_Create_Stub,
    IDBManage_Delete_Stub
};

const CInterfaceStubVtbl _IDBManageStubVtbl =
{
    &IID_IDBManage,
    0,
    5,
    &IDBManage_table[-3],
    CStdStubBuffer_METHODS
};


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

HRESULT __stdcall IDBInfo_GetNumTables_Proxy( 
    IDBInfo __RPC_FAR * This,
    /* [out] */ REFSHORT nNumTables)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
            
            
            
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[34] );
            
            *nNumTables = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer += 2;
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[14],
                         ( void __RPC_FAR * )nNumTables);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDBInfo_GetNumTables_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    short _M18;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    REFSHORT nNumTables;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    nNumTables = 0;
    RpcTryFinally
        {
        nNumTables = &_M18;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDBInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetNumTables((IDBInfo *) ((CStdStubBuffer *)This)->pvServerObject,nNumTables);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 2U + 6U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( short __RPC_FAR * )_StubMsg.Buffer)++ = *nNumTables;
        
        _StubMsg.Buffer += 2;
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IDBInfo_GetTableName_Proxy( 
    IDBInfo __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [size_is][out] */ LPWSTR lpszName)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
            
            
            
            
            _StubMsg.BufferLength = 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nTable;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[66] );
            
            NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR * __RPC_FAR *)&lpszName,
                                           (PFORMAT_STRING) &__MIDLFormatString.Format[42],
                                           (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = 80;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[38],
                         ( void __RPC_FAR * )lpszName);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDBInfo_GetTableName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LPWSTR lpszName;
    short nTable;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    lpszName = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[66] );
        
        nTable = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        lpszName = _StubMsg.pfnAllocate(80 * 2);
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDBInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetTableName(
                (IDBInfo *) ((CStdStubBuffer *)This)->pvServerObject,
                nTable,
                lpszName);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 12U + 10U;
        _StubMsg.MaxCount = 80;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)lpszName,
                                       (PFORMAT_STRING) &__MIDLFormatString.Format[42] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = 80;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)lpszName,
                                     (PFORMAT_STRING) &__MIDLFormatString.Format[42] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = 80;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)lpszName,
                        &__MIDLFormatString.Format[38] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT __stdcall IDBInfo_GetNumRows_Proxy( 
    IDBInfo __RPC_FAR * This,
    /* [in] */ short nTable,
    /* [out] */ REFSHORT nRows)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        RpcTryFinally
            {
            NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
            
            
            
            
            _StubMsg.BufferLength = 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nTable;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[48] );
            
            *nRows = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
            
            _StubMsg.Buffer += 2;
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDLFormatString.Format[14],
                         ( void __RPC_FAR * )nRows);
        _RetVal = NdrProxyErrorHandler(GetExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IDBInfo_GetNumRows_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    short _M21;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    REFSHORT nRows;
    short nTable;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    nRows = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDLProcFormatString.Format[48] );
        
        nTable = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        nRows = &_M21;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IDBInfo *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetNumRows(
              (IDBInfo *) ((CStdStubBuffer *)This)->pvServerObject,
              nTable,
              nRows);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 2U + 6U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( short __RPC_FAR * )_StubMsg.Buffer)++ = *nRows;
        
        _StubMsg.Buffer += 2;
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
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

const CInterfaceProxyVtbl _IDBInfoProxyVtbl = 
{
    &IID_IDBInfo,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IDBInfo_GetNumTables_Proxy ,
    IDBInfo_GetTableName_Proxy ,
    IDBInfo_GetNumRows_Proxy
};


static const PRPC_STUB_FUNCTION IDBInfo_table[] =
{
    IDBInfo_GetNumTables_Stub,
    IDBInfo_GetTableName_Stub,
    IDBInfo_GetNumRows_Stub
};

const CInterfaceStubVtbl _IDBInfoStubVtbl =
{
    &IID_IDBInfo,
    0,
    6,
    &IDBInfo_table[-3],
    CStdStubBuffer_METHODS
};

#pragma data_seg(".rdata")

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_FORMAT_STRING __MIDLProcFormatString =
    {
        0,
        {
			0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/*  2 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/*  4 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  6 */	NdrFcShort( 0x0 ),	/* Type Offset=0 */
/*  8 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 10 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 12 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 14 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 16 */	NdrFcShort( 0xa ),	/* Type Offset=10 */
/* 18 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 20 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 22 */	NdrFcShort( 0xe ),	/* Type Offset=14 */
/* 24 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 26 */	NdrFcShort( 0xa ),	/* Type Offset=10 */
/* 28 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 30 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 32 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 34 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 36 */	NdrFcShort( 0xe ),	/* Type Offset=14 */
/* 38 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 40 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 42 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 44 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */
/* 46 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 48 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 50 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 52 */	NdrFcShort( 0xe ),	/* Type Offset=14 */
/* 54 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 56 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 58 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 60 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 62 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */
/* 64 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 66 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 68 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 70 */	NdrFcShort( 0x26 ),	/* Type Offset=38 */
/* 72 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */

			0x0
        }
    };

static const MIDL_FORMAT_STRING __MIDLFormatString =
    {
        0,
        {
			0x11, 0x0,	/* FC_RP */
/*  2 */	NdrFcShort( 0x2 ),	/* Offset= 2 (4) */
/*  4 */	
			0x25,		/* FC_C_WSTRING */
			0x44,		/* FC_STRING_SIZED */
/*  6 */	0x40,		/* 64 */
			0x0,		/* 0 */
/*  8 */	NdrFcShort( 0x50 ),	/* 80 */
/* 10 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 12 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 14 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 16 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 18 */	
			0x11, 0x0,	/* FC_RP */
/* 20 */	NdrFcShort( 0x2 ),	/* Offset= 2 (22) */
/* 22 */	
			0x25,		/* FC_C_WSTRING */
			0x44,		/* FC_STRING_SIZED */
/* 24 */	0x40,		/* 64 */
			0x0,		/* 0 */
/* 26 */	NdrFcShort( 0x50 ),	/* 80 */
/* 28 */	
			0x11, 0x0,	/* FC_RP */
/* 30 */	NdrFcShort( 0x2 ),	/* Offset= 2 (32) */
/* 32 */	
			0x25,		/* FC_C_WSTRING */
			0x44,		/* FC_STRING_SIZED */
/* 34 */	0x40,		/* 64 */
			0x0,		/* 0 */
/* 36 */	NdrFcShort( 0x50 ),	/* 80 */
/* 38 */	
			0x11, 0x0,	/* FC_RP */
/* 40 */	NdrFcShort( 0x2 ),	/* Offset= 2 (42) */
/* 42 */	
			0x25,		/* FC_C_WSTRING */
			0x44,		/* FC_STRING_SIZED */
/* 44 */	0x40,		/* 64 */
			0x0,		/* 0 */
/* 46 */	NdrFcShort( 0x50 ),	/* 80 */

			0x0
        }
    };

const CInterfaceProxyVtbl * _idb_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IDBProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IDBAccessProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IDBManageProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IDBInfoProxyVtbl,
    0
};

const CInterfaceStubVtbl * _idb_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IDBStubVtbl,
    ( CInterfaceStubVtbl *) &_IDBAccessStubVtbl,
    ( CInterfaceStubVtbl *) &_IDBManageStubVtbl,
    ( CInterfaceStubVtbl *) &_IDBInfoStubVtbl,
    0
};

PCInterfaceName const _idb_InterfaceNamesList[] = 
{
    "IDB",
    "IDBAccess",
    "IDBManage",
    "IDBInfo",
    0
};


#define _idb_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _idb, pIID, n)

int __stdcall _idb_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _idb, 4, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _idb, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _idb, 4, *pIndex )
    
}

const ExtendedProxyFileInfo idb_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _idb_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _idb_StubVtblList,
    (const PCInterfaceName * ) & _idb_InterfaceNamesList,
    0, // no delegation
    & _idb_IID_Lookup, 
    4,
    1
};
