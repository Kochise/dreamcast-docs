/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:05:58 1998
 */
/* Compiler settings for repas.idl, repass.acf:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, oldnames
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "repass.h"

#define TYPE_FORMAT_STRING_SIZE   31                                
#define PROC_FORMAT_STRING_SIZE   15                                

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

/* Standard interface: repas, ver. 1.0,
   GUID={0x56BF67C0,0x6503,0x1068,{0xBF,0x67,0x00,0xDD,0x01,0x0F,0xBF,0x25}} */


extern RPC_DISPATCH_TABLE repas_DispatchTable;

static const RPC_SERVER_INTERFACE repas___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0x56BF67C0,0x6503,0x1068,{0xBF,0x67,0x00,0xDD,0x01,0x0F,0xBF,0x25}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &repas_DispatchTable,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE repas_ServerIfHandle = (RPC_IF_HANDLE)& repas___RpcServerInterface;

extern const MIDL_STUB_DESC repas_StubDesc;

void __RPC_STUB
repas_ModifyMyWString(
    PRPC_MESSAGE _pRpcMessage )
{
    MIDL_STUB_MESSAGE _StubMsg;
    WCHAR_STRING __RPC_FAR *pStr;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &repas_StubDesc);
    
    ( WCHAR_STRING __RPC_FAR * )pStr = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrFixedArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                 (unsigned char __RPC_FAR * __RPC_FAR *)&pStr,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4],
                                 (unsigned char)0 );
        
        
        ModifyMyWString(pStr);
        
        _StubMsg.BufferLength = 200U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrFixedArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                               (unsigned char __RPC_FAR *)pStr,
                               (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pStr,
                        &__MIDL_TypeFormatString.Format[0] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
repas_ModifyMyString(
    PRPC_MESSAGE _pRpcMessage )
{
    MIDL_STUB_MESSAGE _StubMsg;
    WCHAR_STRING __RPC_FAR *pStr;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &repas_StubDesc);
    
    ( WCHAR_STRING __RPC_FAR * )pStr = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
        
        NdrXmitOrRepAsUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pStr,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20],
                                  (unsigned char)0 );
        
        
        ModifyMyString(pStr);
        
        _StubMsg.BufferLength = 100U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrXmitOrRepAsMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pStr,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[20] );
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pStr,
                        &__MIDL_TypeFormatString.Format[10] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
repas_Shutdown(
    PRPC_MESSAGE _pRpcMessage )
{
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &repas_StubDesc);
    
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

static const MIDL_STUB_DESC repas_StubDesc = 
    {
    (void __RPC_FAR *)& repas___RpcServerInterface,
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

static RPC_DISPATCH_FUNCTION repas_table[] =
    {
    repas_ModifyMyWString,
    repas_ModifyMyString,
    repas_Shutdown,
    0
    };
RPC_DISPATCH_TABLE repas_DispatchTable = 
    {
    3,
    repas_table
    };
NDR_SHAREABLE void __RPC_USER
CHAR_STRING_RepAsTranslateToLocal( PMIDL_STUB_MESSAGE pStubMsg )
{
    CHAR_STRING_to_local( (CHAR_STRING __RPC_FAR *) pStubMsg->pTransmitType, 
        (WCHAR_STRING __RPC_FAR *) pStubMsg->pPresentedType ); 
}
NDR_SHAREABLE void __RPC_USER
CHAR_STRING_RepAsTranslateFromLocal( PMIDL_STUB_MESSAGE pStubMsg )
{
    CHAR_STRING_from_local( (WCHAR_STRING __RPC_FAR *) pStubMsg->pPresentedType, 
        (CHAR_STRING __RPC_FAR * __RPC_FAR *) &pStubMsg->pTransmitType );
}
NDR_SHAREABLE void __RPC_USER
CHAR_STRING_RepAsFreeInst( PMIDL_STUB_MESSAGE pStubMsg )
{
    CHAR_STRING_free_inst( (CHAR_STRING __RPC_FAR *) pStubMsg->pTransmitType );
}
NDR_SHAREABLE void __RPC_USER
CHAR_STRING_RepAsFreeLocal( PMIDL_STUB_MESSAGE pStubMsg )
{
    CHAR_STRING_free_local( (WCHAR_STRING __RPC_FAR *) pStubMsg->pPresentedType ); 
}

static const XMIT_ROUTINE_QUINTUPLE TransmitAsRoutines[1] = 
        {
            
            {
            CHAR_STRING_RepAsTranslateFromLocal
            ,CHAR_STRING_RepAsTranslateToLocal
            ,CHAR_STRING_RepAsFreeInst
            ,CHAR_STRING_RepAsFreeLocal
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
/*  6 */	
			0x50,		/* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  8 */	NdrFcShort( 0xa ),	/* Type Offset=10 */
/* 10 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */
/* 12 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */

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
			0x1d,		/* FC_SMFARRAY */
			0x1,		/* 1 */
/*  6 */	NdrFcShort( 0xc8 ),	/* 200 */
/*  8 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 10 */	
			0x11, 0x0,	/* FC_RP */
/* 12 */	NdrFcShort( 0x8 ),	/* Offset= 8 (20) */
/* 14 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 16 */	NdrFcShort( 0x64 ),	/* 100 */
/* 18 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 20 */	0x2e,		/* FC_REPRESENT_AS */
			0x10,		/* 16 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0xc8 ),	/* 200 */
/* 26 */	NdrFcShort( 0x64 ),	/* 100 */
/* 28 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (14) */

			0x0
        }
    };
