/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:39:58 1998
 */
/* Compiler settings for papint.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, app_config, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "papint.h"

#define TYPE_FORMAT_STRING_SIZE   27                                
#define PROC_FORMAT_STRING_SIZE   69                                

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


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ISharePaper, ver. 0.0,
   GUID={0x0002da31,0x0000,0x0000,{0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

HRESULT STDMETHODCALLTYPE ISharePaper_InitPaper_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [out][in] */ RECT __RPC_FAR *pWinRect,
    /* [out] */ BOOL __RPC_FAR *pbFirst)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)pWinRect,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)pWinRect,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&pWinRect,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4],
                                       (unsigned char)0 );
            
            *pbFirst = *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[0],
                         ( void __RPC_FAR * )pWinRect);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[14],
                         ( void __RPC_FAR * )pbFirst);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISharePaper_InitPaper_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BOOL _M0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    RECT __RPC_FAR *pWinRect;
    BOOL __RPC_FAR *pbFirst;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( RECT __RPC_FAR * )pWinRect = 0;
    ( BOOL __RPC_FAR * )pbFirst = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&pWinRect,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4],
                                   (unsigned char)0 );
        
        pbFirst = &_M0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> InitPaper(
             (ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject,
             pWinRect,
             pbFirst);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 11U + 7U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)pWinRect,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)pWinRect,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = *pbFirst;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISharePaper_Lock_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [in] */ BOOL bLock)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = bLock;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[10] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISharePaper_Lock_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BOOL bLock;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[10] );
        
        bLock = *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Lock((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject,bLock);
        
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


HRESULT STDMETHODCALLTYPE ISharePaper_Load_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [out] */ RECT __RPC_FAR *pWinRect)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               pWinRect,
               0,
               sizeof( RECT  ));
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
            
            NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&pWinRect,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4],
                                       (unsigned char)0 );
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[18],
                         ( void __RPC_FAR * )pWinRect);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISharePaper_Load_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    RECT _pWinRectM;
    RECT __RPC_FAR *pWinRect;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( RECT __RPC_FAR * )pWinRect = 0;
    RpcTryFinally
        {
        pWinRect = &_pWinRectM;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Load((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject,pWinRect);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 11U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)pWinRect,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)pWinRect,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISharePaper_Save_Proxy( 
    ISharePaper __RPC_FAR * This)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[20] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISharePaper_Save_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Save((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject);
        
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


HRESULT STDMETHODCALLTYPE ISharePaper_InkStart_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [in] */ SHORT nX,
    /* [in] */ SHORT nY,
    /* [in] */ SHORT nInkWidth,
    /* [in] */ COLORREF crInkColor)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      7);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 2U + 2U + 2U + 6U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nX;
            
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nY;
            
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nInkWidth;
            
            _StubMsg.Buffer += 2;
            *(( COLORREF __RPC_FAR * )_StubMsg.Buffer)++ = crInkColor;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISharePaper_InkStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    COLORREF crInkColor;
    SHORT nInkWidth;
    SHORT nX;
    SHORT nY;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
        
        nX = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        nY = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        nInkWidth = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        _StubMsg.Buffer += 2;
        crInkColor = *(( COLORREF __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> InkStart(
            (ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject,
            nX,
            nY,
            nInkWidth,
            crInkColor);
        
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


HRESULT STDMETHODCALLTYPE ISharePaper_InkDraw_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [in] */ SHORT nX,
    /* [in] */ SHORT nY)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      8);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 2U + 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nX;
            
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nY;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[32] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISharePaper_InkDraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    SHORT nX;
    SHORT nY;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[32] );
        
        nX = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        nY = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> InkDraw(
           (ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject,
           nX,
           nY);
        
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


HRESULT STDMETHODCALLTYPE ISharePaper_InkStop_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [in] */ SHORT nX,
    /* [in] */ SHORT nY)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      9);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 2U + 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nX;
            
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nY;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[32] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISharePaper_InkStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    SHORT nX;
    SHORT nY;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[32] );
        
        nX = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        nY = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> InkStop(
           (ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject,
           nX,
           nY);
        
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


HRESULT STDMETHODCALLTYPE ISharePaper_GetInk_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [in] */ LONG lIndex,
    /* [out] */ SHORT __RPC_FAR *pnInkType,
    /* [out] */ SHORT __RPC_FAR *pnX,
    /* [out] */ SHORT __RPC_FAR *pnY,
    /* [out] */ SHORT __RPC_FAR *pnInkWidth,
    /* [out] */ COLORREF __RPC_FAR *pcrInkColor)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      10);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( LONG __RPC_FAR * )_StubMsg.Buffer)++ = lIndex;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[38] );
            
            *pnInkType = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
            
            *pnX = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
            
            *pnY = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
            
            *pnInkWidth = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
            
            *pcrInkColor = *(( COLORREF __RPC_FAR * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[22],
                         ( void __RPC_FAR * )pnInkType);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[22],
                         ( void __RPC_FAR * )pnX);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[22],
                         ( void __RPC_FAR * )pnY);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[22],
                         ( void __RPC_FAR * )pnInkWidth);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[14],
                         ( void __RPC_FAR * )pcrInkColor);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISharePaper_GetInk_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    SHORT _M1;
    SHORT _M2;
    SHORT _M3;
    SHORT _M4;
    COLORREF _M5;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LONG lIndex;
    COLORREF __RPC_FAR *pcrInkColor;
    SHORT __RPC_FAR *pnInkType;
    SHORT __RPC_FAR *pnInkWidth;
    SHORT __RPC_FAR *pnX;
    SHORT __RPC_FAR *pnY;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( SHORT __RPC_FAR * )pnInkType = 0;
    ( SHORT __RPC_FAR * )pnX = 0;
    ( SHORT __RPC_FAR * )pnY = 0;
    ( SHORT __RPC_FAR * )pnInkWidth = 0;
    ( COLORREF __RPC_FAR * )pcrInkColor = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[38] );
        
        lIndex = *(( LONG __RPC_FAR * )_StubMsg.Buffer)++;
        
        pnInkType = &_M1;
        pnX = &_M2;
        pnY = &_M3;
        pnInkWidth = &_M4;
        pcrInkColor = &_M5;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetInk(
          (ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject,
          lIndex,
          pnInkType,
          pnX,
          pnY,
          pnInkWidth,
          pcrInkColor);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 2U + 2U + 2U + 2U + 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = *pnInkType;
        
        *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = *pnX;
        
        *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = *pnY;
        
        *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = *pnInkWidth;
        
        *(( COLORREF __RPC_FAR * )_StubMsg.Buffer)++ = *pcrInkColor;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


HRESULT STDMETHODCALLTYPE ISharePaper_Erase_Proxy( 
    ISharePaper __RPC_FAR * This)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      11);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[20] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISharePaper_Erase_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Erase((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject);
        
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


HRESULT STDMETHODCALLTYPE ISharePaper_Resize_Proxy( 
    ISharePaper __RPC_FAR * This,
    /* [in] */ LONG lWidth,
    /* [in] */ LONG lHeight)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      12);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( LONG __RPC_FAR * )_StubMsg.Buffer)++ = lWidth;
            
            *(( LONG __RPC_FAR * )_StubMsg.Buffer)++ = lHeight;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[62] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISharePaper_Resize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LONG lHeight;
    LONG lWidth;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[62] );
        
        lWidth = *(( LONG __RPC_FAR * )_StubMsg.Buffer)++;
        
        lHeight = *(( LONG __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Resize(
          (ISharePaper *) ((CStdStubBuffer *)This)->pvServerObject,
          lWidth,
          lHeight);
        
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

const CINTERFACE_PROXY_VTABLE(13) _ISharePaperProxyVtbl = 
{
    &IID_ISharePaper,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISharePaper_InitPaper_Proxy ,
    ISharePaper_Lock_Proxy ,
    ISharePaper_Load_Proxy ,
    ISharePaper_Save_Proxy ,
    ISharePaper_InkStart_Proxy ,
    ISharePaper_InkDraw_Proxy ,
    ISharePaper_InkStop_Proxy ,
    ISharePaper_GetInk_Proxy ,
    ISharePaper_Erase_Proxy ,
    ISharePaper_Resize_Proxy
};


static const PRPC_STUB_FUNCTION ISharePaper_table[] =
{
    ISharePaper_InitPaper_Stub,
    ISharePaper_Lock_Stub,
    ISharePaper_Load_Stub,
    ISharePaper_Save_Stub,
    ISharePaper_InkStart_Stub,
    ISharePaper_InkDraw_Stub,
    ISharePaper_InkStop_Stub,
    ISharePaper_GetInk_Stub,
    ISharePaper_Erase_Stub,
    ISharePaper_Resize_Stub
};

const CInterfaceStubVtbl _ISharePaperStubVtbl =
{
    &IID_ISharePaper,
    0,
    13,
    &ISharePaper_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IPaperSink, ver. 0.0,
   GUID={0x0002da34,0x0000,0x0000,{0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

HRESULT STDMETHODCALLTYPE IPaperSink_Locked_Proxy( 
    IPaperSink __RPC_FAR * This)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[20] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPaperSink_Locked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Locked((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject);
        
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


HRESULT STDMETHODCALLTYPE IPaperSink_Unlocked_Proxy( 
    IPaperSink __RPC_FAR * This)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[20] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPaperSink_Unlocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Unlocked((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject);
        
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


HRESULT STDMETHODCALLTYPE IPaperSink_Loaded_Proxy( 
    IPaperSink __RPC_FAR * This)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[20] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPaperSink_Loaded_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Loaded((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject);
        
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


HRESULT STDMETHODCALLTYPE IPaperSink_Saved_Proxy( 
    IPaperSink __RPC_FAR * This)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[20] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPaperSink_Saved_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Saved((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject);
        
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


HRESULT STDMETHODCALLTYPE IPaperSink_InkStart_Proxy( 
    IPaperSink __RPC_FAR * This,
    /* [in] */ SHORT nX,
    /* [in] */ SHORT nY,
    /* [in] */ SHORT nInkWidth,
    /* [in] */ COLORREF crInkColor)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      7);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 2U + 2U + 2U + 6U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nX;
            
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nY;
            
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nInkWidth;
            
            _StubMsg.Buffer += 2;
            *(( COLORREF __RPC_FAR * )_StubMsg.Buffer)++ = crInkColor;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPaperSink_InkStart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    COLORREF crInkColor;
    SHORT nInkWidth;
    SHORT nX;
    SHORT nY;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
        
        nX = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        nY = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        nInkWidth = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        _StubMsg.Buffer += 2;
        crInkColor = *(( COLORREF __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> InkStart(
            (IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject,
            nX,
            nY,
            nInkWidth,
            crInkColor);
        
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


HRESULT STDMETHODCALLTYPE IPaperSink_InkDraw_Proxy( 
    IPaperSink __RPC_FAR * This,
    /* [in] */ SHORT nX,
    /* [in] */ SHORT nY)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      8);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 2U + 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nX;
            
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nY;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[32] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPaperSink_InkDraw_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    SHORT nX;
    SHORT nY;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[32] );
        
        nX = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        nY = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> InkDraw(
           (IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject,
           nX,
           nY);
        
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


HRESULT STDMETHODCALLTYPE IPaperSink_InkStop_Proxy( 
    IPaperSink __RPC_FAR * This,
    /* [in] */ SHORT nX,
    /* [in] */ SHORT nY)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      9);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 2U + 2U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nX;
            
            *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++ = nY;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[32] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPaperSink_InkStop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    SHORT nX;
    SHORT nY;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[32] );
        
        nX = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        nY = *(( SHORT __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> InkStop(
           (IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject,
           nX,
           nY);
        
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


HRESULT STDMETHODCALLTYPE IPaperSink_Erased_Proxy( 
    IPaperSink __RPC_FAR * This)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      10);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[20] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPaperSink_Erased_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Erased((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject);
        
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


HRESULT STDMETHODCALLTYPE IPaperSink_Resized_Proxy( 
    IPaperSink __RPC_FAR * This,
    /* [in] */ LONG lWidth,
    /* [in] */ LONG lHeight)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      11);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( LONG __RPC_FAR * )_StubMsg.Buffer)++ = lWidth;
            
            *(( LONG __RPC_FAR * )_StubMsg.Buffer)++ = lHeight;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[62] );
            
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
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPaperSink_Resized_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LONG lHeight;
    LONG lWidth;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[62] );
        
        lWidth = *(( LONG __RPC_FAR * )_StubMsg.Buffer)++;
        
        lHeight = *(( LONG __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Resized(
           (IPaperSink *) ((CStdStubBuffer *)This)->pvServerObject,
           lWidth,
           lHeight);
        
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

const CINTERFACE_PROXY_VTABLE(12) _IPaperSinkProxyVtbl = 
{
    &IID_IPaperSink,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IPaperSink_Locked_Proxy ,
    IPaperSink_Unlocked_Proxy ,
    IPaperSink_Loaded_Proxy ,
    IPaperSink_Saved_Proxy ,
    IPaperSink_InkStart_Proxy ,
    IPaperSink_InkDraw_Proxy ,
    IPaperSink_InkStop_Proxy ,
    IPaperSink_Erased_Proxy ,
    IPaperSink_Resized_Proxy
};


static const PRPC_STUB_FUNCTION IPaperSink_table[] =
{
    IPaperSink_Locked_Stub,
    IPaperSink_Unlocked_Stub,
    IPaperSink_Loaded_Stub,
    IPaperSink_Saved_Stub,
    IPaperSink_InkStart_Stub,
    IPaperSink_InkDraw_Stub,
    IPaperSink_InkStop_Stub,
    IPaperSink_Erased_Stub,
    IPaperSink_Resized_Stub
};

const CInterfaceStubVtbl _IPaperSinkStubVtbl =
{
    &IID_IPaperSink,
    0,
    12,
    &IPaperSink_table[-3],
    CStdStubBuffer_METHODS
};


/* Standard interface: __MIDL_itf_papint_0008, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */

#pragma data_seg(".rdata")

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			
			0x50,		/* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  2 */	NdrFcShort( 0x0 ),	/* Type Offset=0 */
/*  4 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  6 */	NdrFcShort( 0xe ),	/* Type Offset=14 */
/*  8 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 10 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 12 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 14 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 16 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */
/* 18 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 20 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 22 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 24 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 26 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 28 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 30 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 32 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 34 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 36 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 38 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 40 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 42 */	NdrFcShort( 0x16 ),	/* Type Offset=22 */
/* 44 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 46 */	NdrFcShort( 0x16 ),	/* Type Offset=22 */
/* 48 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 50 */	NdrFcShort( 0x16 ),	/* Type Offset=22 */
/* 52 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 54 */	NdrFcShort( 0x16 ),	/* Type Offset=22 */
/* 56 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 58 */	NdrFcShort( 0xe ),	/* Type Offset=14 */
/* 60 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 62 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 64 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 66 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x11, 0x0,	/* FC_RP */
/*  2 */	NdrFcShort( 0x2 ),	/* Offset= 2 (4) */
/*  4 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/*  6 */	NdrFcShort( 0x10 ),	/* 16 */
/*  8 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 10 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 12 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 14 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 16 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 18 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 20 */	NdrFcShort( 0xfffffff0 ),	/* Offset= -16 (4) */
/* 22 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 24 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

const CInterfaceProxyVtbl * _papint_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ISharePaperProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPaperSinkProxyVtbl,
    0
};

const CInterfaceStubVtbl * _papint_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ISharePaperStubVtbl,
    ( CInterfaceStubVtbl *) &_IPaperSinkStubVtbl,
    0
};

PCInterfaceName const _papint_InterfaceNamesList[] = 
{
    "ISharePaper",
    "IPaperSink",
    0
};


#define _papint_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _papint, pIID, n)

int __stdcall _papint_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _papint, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _papint, 2, *pIndex )
    
}

const ExtendedProxyFileInfo papint_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _papint_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _papint_StubVtblList,
    (const PCInterfaceName * ) & _papint_InterfaceNamesList,
    0, // no delegation
    & _papint_IID_Lookup, 
    2,
    1
};
