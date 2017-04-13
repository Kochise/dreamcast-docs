/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 3.00.44 */
/* at Wed Nov 06 19:30:10 1996
 */
/* Compiler settings for iball.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include "rpcproxy.h"
#include "iball.h"

#define TYPE_FORMAT_STRING_SIZE   31                                
#define PROC_FORMAT_STRING_SIZE   31                                

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


/* Object interface: IBall, ver. 0.0,
   GUID={0xF002da32,0x0000,0x0000,{0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [propget][id] */ HRESULT STDMETHODCALLTYPE IBall_get_Ball_Proxy( 
    IBall __RPC_FAR * This,
    /* [out] */ POINT __RPC_FAR *pOrg,
    /* [out] */ POINT __RPC_FAR *pExt,
    /* [retval][out] */ COLORREF __RPC_FAR *pcrColor)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    MIDL_memset(
               pOrg,
               0,
               sizeof( POINT  ));
    MIDL_memset(
               pExt,
               0,
               sizeof( POINT  ));
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
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&pOrg,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4],
                                       (unsigned char)0 );
            
            NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&pExt,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4],
                                       (unsigned char)0 );
            
            *pcrColor = *(( COLORREF __RPC_FAR * )_StubMsg.Buffer)++;
            
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
                         ( void __RPC_FAR * )pOrg);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[0],
                         ( void __RPC_FAR * )pExt);
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[12],
                         ( void __RPC_FAR * )pcrColor);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IBall_get_Ball_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    COLORREF _M0;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    POINT _pExtM;
    POINT _pOrgM;
    POINT __RPC_FAR *pExt;
    POINT __RPC_FAR *pOrg;
    COLORREF __RPC_FAR *pcrColor;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    pOrg = 0;
    pExt = 0;
    pcrColor = 0;
    RpcTryFinally
        {
        pOrg = &_pOrgM;
        pExt = &_pExtM;
        pcrColor = &_M0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IBall *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> get_Ball(
            (IBall *) ((CStdStubBuffer *)This)->pvServerObject,
            pOrg,
            pExt,
            pcrColor);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 0U + 11U + 7U;
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)pOrg,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR *)pExt,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)pOrg,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                 (unsigned char __RPC_FAR *)pExt,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        *(( COLORREF __RPC_FAR * )_StubMsg.Buffer)++ = *pcrColor;
        
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [id] */ HRESULT STDMETHODCALLTYPE IBall_Reset_Proxy( 
    IBall __RPC_FAR * This,
    /* [in] */ RECT __RPC_FAR *pNewRect,
    /* [in] */ short nBallSize)
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
            
            _StubMsg.BufferLength = 0U + 5U;
            NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)pNewRect,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)pNewRect,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
            
            *(( short __RPC_FAR * )_StubMsg.Buffer)++ = nBallSize;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
            
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

void __RPC_STUB IBall_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    short nBallSize;
    RECT __RPC_FAR *pNewRect;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    pNewRect = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
        
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&pNewRect,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20],
                                   (unsigned char)0 );
        
        nBallSize = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IBall *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Reset(
         (IBall *) ((CStdStubBuffer *)This)->pvServerObject,
         pNewRect,
         nBallSize);
        
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


/* [id] */ HRESULT STDMETHODCALLTYPE IBall_Move_Proxy( 
    IBall __RPC_FAR * This,
    /* [in] */ BOOL bAlive,
    /* [retval][out] */ BOOL __RPC_FAR *bRet)
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
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = bAlive;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
            
            *bRet = *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++;
            
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[12],
                         ( void __RPC_FAR * )bRet);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IBall_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BOOL _M1;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BOOL bAlive;
    BOOL __RPC_FAR *bRet;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    bRet = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
        
        bAlive = *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++;
        
        bRet = &_M1;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IBall *) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Move(
        (IBall *) ((CStdStubBuffer *)This)->pvServerObject,
        bAlive,
        bRet);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = *bRet;
        
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
    0x300002c, /* MIDL Version 3.0.44 */
    0,
    0,
    0,  /* Reserved1 */
    0,  /* Reserved2 */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

const CINTERFACE_PROXY_VTABLE(6) _IBallProxyVtbl = 
{
    &IID_IBall,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IBall_get_Ball_Proxy ,
    IBall_Reset_Proxy ,
    IBall_Move_Proxy
};


static const PRPC_STUB_FUNCTION IBall_table[] =
{
    IBall_get_Ball_Stub,
    IBall_Reset_Stub,
    IBall_Move_Stub
};

const CInterfaceStubVtbl _IBallStubVtbl =
{
    &IID_IBall,
    0,
    6,
    &IBall_table[-3],
    CStdStubBuffer_METHODS
};

#pragma data_seg(".rdata")

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
            
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/*  2 */    NdrFcShort( 0x0 ),  /* Type Offset=0 */
/*  4 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/*  6 */    NdrFcShort( 0x0 ),  /* Type Offset=0 */
/*  8 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 10 */    NdrFcShort( 0xc ),  /* Type Offset=12 */
/* 12 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 14 */    
            0x4d,       /* FC_IN_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 16 */    NdrFcShort( 0x10 ), /* Type Offset=16 */
/* 18 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x6,        /* FC_SHORT */
/* 20 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 22 */    0x4e,       /* FC_IN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */
/* 24 */    
            0x51,       /* FC_OUT_PARAM */
#ifndef _ALPHA_
            0x1,        /* x86, MIPS & PPC Stack size = 1 */
#else
            0x2,        /* Alpha Stack size = 2 */
#endif
/* 26 */    NdrFcShort( 0xc ),  /* Type Offset=12 */
/* 28 */    0x53,       /* FC_RETURN_PARAM_BASETYPE */
            0x8,        /* FC_LONG */

            0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
            0x11, 0x4,  /* FC_RP [alloced_on_stack] */
/*  2 */    NdrFcShort( 0x2 ),  /* Offset= 2 (4) */
/*  4 */    
            0x15,       /* FC_STRUCT */
            0x3,        /* 3 */
/*  6 */    NdrFcShort( 0x8 ),  /* 8 */
/*  8 */    0x8,        /* FC_LONG */
            0x8,        /* FC_LONG */
/* 10 */    0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */
/* 12 */    
            0x11, 0xc,  /* FC_RP [alloced_on_stack] [simple_pointer] */
/* 14 */    0x8,        /* FC_LONG */
            0x5c,       /* FC_PAD */
/* 16 */    
            0x11, 0x0,  /* FC_RP */
/* 18 */    NdrFcShort( 0x2 ),  /* Offset= 2 (20) */
/* 20 */    
            0x15,       /* FC_STRUCT */
            0x3,        /* 3 */
/* 22 */    NdrFcShort( 0x10 ), /* 16 */
/* 24 */    0x8,        /* FC_LONG */
            0x8,        /* FC_LONG */
/* 26 */    0x8,        /* FC_LONG */
            0x8,        /* FC_LONG */
/* 28 */    0x5c,       /* FC_PAD */
            0x5b,       /* FC_END */

            0x0
        }
    };

const CInterfaceProxyVtbl * _iball_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IBallProxyVtbl,
    0
};

const CInterfaceStubVtbl * _iball_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IBallStubVtbl,
    0
};

PCInterfaceName const _iball_InterfaceNamesList[] = 
{
    "IBall",
    0
};


#define _iball_CHECK_IID(n) IID_GENERIC_CHECK_IID( _iball, pIID, n)

int __stdcall _iball_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_iball_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo iball_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _iball_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _iball_StubVtblList,
    (const PCInterfaceName * ) & _iball_InterfaceNamesList,
    0, // no delegation
    & _iball_IID_Lookup, 
    1,
    1
};
