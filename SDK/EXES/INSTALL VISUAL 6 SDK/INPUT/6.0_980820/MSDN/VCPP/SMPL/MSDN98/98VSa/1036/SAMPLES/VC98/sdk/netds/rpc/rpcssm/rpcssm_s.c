/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:08:49 1998
 */
/* Compiler settings for rpcssm.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, oldnames
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "rpcssm.h"

#define TYPE_FORMAT_STRING_SIZE   29                                
#define PROC_FORMAT_STRING_SIZE   9                                 

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

/* Standard interface: rpcssm, ver. 1.0,
   GUID={0xA4F1DB00,0xCA47,0x1067,{0xB3,0x1F,0x00,0xDD,0x01,0x06,0x62,0xDA}} */


extern RPC_DISPATCH_TABLE rpcssm_DispatchTable;

static const RPC_SERVER_INTERFACE rpcssm___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0xA4F1DB00,0xCA47,0x1067,{0xB3,0x1F,0x00,0xDD,0x01,0x06,0x62,0xDA}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &rpcssm_DispatchTable,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE rpcssm_ServerIfHandle = (RPC_IF_HANDLE)& rpcssm___RpcServerInterface;

extern const MIDL_STUB_DESC rpcssm_StubDesc;

void __RPC_STUB
rpcssm_InOutList(
    PRPC_MESSAGE _pRpcMessage )
{
    MIDL_STUB_MESSAGE _StubMsg;
    PBOX __RPC_FAR *ppBox;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &rpcssm_StubDesc);
    
    NdrRpcSsEnableAllocate(&_StubMsg);
    ( PBOX __RPC_FAR * )ppBox = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&ppBox,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[0],
                              (unsigned char)0 );
        
        
        InOutList(ppBox);
        
        _StubMsg.BufferLength = 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ppBox,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[0] );
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ppBox,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[0] );
        
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
rpcssm_Shutdown(
    PRPC_MESSAGE _pRpcMessage )
{
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &rpcssm_StubDesc);
    
    NdrRpcSsEnableAllocate(&_StubMsg);
    RpcTryFinally
        {
        
        Shutdown();
        
        }
    RpcFinally
        {
        NdrRpcSsDisableAllocate(&_StubMsg);
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

extern MALLOC_FREE_STRUCT _MallocFreeStruct;

static const MIDL_STUB_DESC rpcssm_StubDesc = 
    {
    (void __RPC_FAR *)& rpcssm___RpcServerInterface,
    NdrRpcSsDefaultAllocate,
    NdrRpcSsDefaultFree,
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

static RPC_DISPATCH_FUNCTION rpcssm_table[] =
    {
    rpcssm_InOutList,
    rpcssm_Shutdown,
    0
    };
RPC_DISPATCH_TABLE rpcssm_DispatchTable = 
    {
    2,
    rpcssm_table
    };

static void __RPC_FAR * __RPC_USER
rpcssm_malloc_wrapper( size_t _Size )
{
    return( malloc( _Size ) );
}

static void  __RPC_USER
rpcssm_free_wrapper( void __RPC_FAR * _p )
{
    free( _p );
}

static MALLOC_FREE_STRUCT _MallocFreeStruct = 
{
    rpcssm_malloc_wrapper,
    rpcssm_free_wrapper
};

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
/*  4 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */
/*  6 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x11, 0x10,	/* FC_RP */
/*  2 */	NdrFcShort( 0x2 ),	/* Offset= 2 (4) */
/*  4 */	
			0x12, 0x0,	/* FC_UP */
/*  6 */	NdrFcShort( 0x2 ),	/* Offset= 2 (8) */
/*  8 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 10 */	NdrFcShort( 0x8 ),	/* 8 */
/* 12 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 14 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 16 */	NdrFcShort( 0x4 ),	/* 4 */
/* 18 */	NdrFcShort( 0x4 ),	/* 4 */
/* 20 */	0x12, 0x0,	/* FC_UP */
/* 22 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (8) */
/* 24 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 26 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */

			0x0
        }
    };
