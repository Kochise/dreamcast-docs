/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:06:10 1998
 */
/* Compiler settings for xmit.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, oldnames
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "xmit.h"

#define TYPE_FORMAT_STRING_SIZE   33                                
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

/* Standard interface: xmit, ver. 1.0,
   GUID={0x56BF67C0,0x6503,0x1068,{0xBF,0x67,0x00,0xDD,0x01,0x0F,0xBF,0x25}} */


extern RPC_DISPATCH_TABLE xmit_DispatchTable;

static const RPC_SERVER_INTERFACE xmit___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0x56BF67C0,0x6503,0x1068,{0xBF,0x67,0x00,0xDD,0x01,0x0F,0xBF,0x25}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &xmit_DispatchTable,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE xmit_ServerIfHandle = (RPC_IF_HANDLE)& xmit___RpcServerInterface;

extern const MIDL_STUB_DESC xmit_StubDesc;

void __RPC_STUB
xmit_ModifyListProc(
    PRPC_MESSAGE _pRpcMessage )
{
    MIDL_STUB_MESSAGE _StubMsg;
    DOUBLE_LINK_TYPE __RPC_FAR *pHead;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &xmit_StubDesc);
    
    ( DOUBLE_LINK_TYPE __RPC_FAR * )pHead = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrXmitOrRepAsUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pHead,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[22],
                                  (unsigned char)0 );
        
        
        ModifyListProc(pHead);
        
        _StubMsg.BufferLength = 0U;
        NdrXmitOrRepAsBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)pHead,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[22] );
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrXmitOrRepAsMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pHead,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[22] );
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pHead,
                        &__MIDL_TypeFormatString.Format[0] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
xmit_Shutdown(
    PRPC_MESSAGE _pRpcMessage )
{
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &xmit_StubDesc);
    
    RpcTryFinally
        {
        
        Shutdown();
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

extern const XMIT_ROUTINE_QUINTUPLE TransmitAsRoutines[1];

static const MIDL_STUB_DESC xmit_StubDesc = 
    {
    (void __RPC_FAR *)& xmit___RpcServerInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    0,
    0,
    0,
    0,
    TransmitAsRoutines,
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

static RPC_DISPATCH_FUNCTION xmit_table[] =
    {
    xmit_ModifyListProc,
    xmit_Shutdown,
    0
    };
RPC_DISPATCH_TABLE xmit_DispatchTable = 
    {
    2,
    xmit_table
    };

NDR_SHAREABLE void __RPC_USER
DOUBLE_LINK_TYPE_XmitTranslateToXmit( PMIDL_STUB_MESSAGE pStubMsg )
{
    DOUBLE_LINK_TYPE_to_xmit( (DOUBLE_LINK_TYPE __RPC_FAR *) pStubMsg->pPresentedType, 
        (DOUBLE_XMIT_TYPE __RPC_FAR * __RPC_FAR *) &pStubMsg->pTransmitType );
}
NDR_SHAREABLE void __RPC_USER
DOUBLE_LINK_TYPE_XmitTranslateFromXmit( PMIDL_STUB_MESSAGE pStubMsg )
{
    DOUBLE_LINK_TYPE_from_xmit( (DOUBLE_XMIT_TYPE __RPC_FAR *) pStubMsg->pTransmitType, 
        (DOUBLE_LINK_TYPE __RPC_FAR *) pStubMsg->pPresentedType ); 
}
NDR_SHAREABLE void __RPC_USER
DOUBLE_LINK_TYPE_XmitFreeXmit( PMIDL_STUB_MESSAGE pStubMsg )
{
    DOUBLE_LINK_TYPE_free_xmit( (DOUBLE_XMIT_TYPE __RPC_FAR *) pStubMsg->pTransmitType );
}
NDR_SHAREABLE void __RPC_USER
DOUBLE_LINK_TYPE_XmitFreeInst( PMIDL_STUB_MESSAGE pStubMsg )
{
    DOUBLE_LINK_TYPE_free_inst( (DOUBLE_LINK_TYPE __RPC_FAR *) pStubMsg->pPresentedType ); 
}

static const XMIT_ROUTINE_QUINTUPLE TransmitAsRoutines[1] = 
        {
            
            {
            DOUBLE_LINK_TYPE_XmitTranslateToXmit
            ,DOUBLE_LINK_TYPE_XmitTranslateFromXmit
            ,DOUBLE_LINK_TYPE_XmitFreeXmit
            ,DOUBLE_LINK_TYPE_XmitFreeInst
            }

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
			0x11, 0x0,	/* FC_RP */
/*  2 */	NdrFcShort( 0x14 ),	/* Offset= 20 (22) */
/*  4 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/*  6 */	NdrFcShort( 0x2 ),	/* 2 */
/*  8 */	0x6,		/* 6 */
			0x0,		/*  */
/* 10 */	NdrFcShort( 0xfffffffe ),	/* -2 */
/* 12 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 14 */	
			0x17,		/* FC_CSTRUCT */
			0x1,		/* 1 */
/* 16 */	NdrFcShort( 0x2 ),	/* 2 */
/* 18 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (4) */
/* 20 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 22 */	0x2d,		/* FC_TRANSMIT_AS */
			0x21,		/* 33 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */
/* 26 */	NdrFcShort( 0xc ),	/* 12 */
/* 28 */	NdrFcShort( 0x0 ),	/* 0 */
/* 30 */	NdrFcShort( 0xfffffff0 ),	/* Offset= -16 (14) */

			0x0
        }
    };
