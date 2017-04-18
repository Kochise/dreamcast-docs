/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:05:33 1998
 */
/* Compiler settings for dunion.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, oldnames
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "dunion.h"

#define TYPE_FORMAT_STRING_SIZE   63                                
#define PROC_FORMAT_STRING_SIZE   17                                

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

/* Standard interface: dunion, ver. 1.0,
   GUID={0x87E5BFA0,0xCA46,0x1067,{0xB3,0x1B,0x00,0xDD,0x01,0x06,0x62,0xDA}} */


extern RPC_DISPATCH_TABLE dunion_DispatchTable;

static const RPC_SERVER_INTERFACE dunion___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0x87E5BFA0,0xCA46,0x1067,{0xB3,0x1B,0x00,0xDD,0x01,0x06,0x62,0xDA}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &dunion_DispatchTable,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE dunion_ServerIfHandle = (RPC_IF_HANDLE)& dunion___RpcServerInterface;

extern const MIDL_STUB_DESC dunion_StubDesc;

void __RPC_STUB
dunion_UnionParamProc(
    PRPC_MESSAGE _pRpcMessage )
{
    DISCRIM_UNION_PARAM_TYPE __RPC_FAR *UnionParam;
    MIDL_STUB_MESSAGE _StubMsg;
    short sDiscrim;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dunion_StubDesc);
    
    ( DISCRIM_UNION_PARAM_TYPE __RPC_FAR * )UnionParam = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrNonEncapsulatedUnionUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR * __RPC_FAR *)&UnionParam,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4],
                                           (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        sDiscrim = *(( short __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        UnionParamProc(UnionParam,sDiscrim);
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = sDiscrim;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)UnionParam,
                        &__MIDL_TypeFormatString.Format[0] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dunion_UnionStructProc(
    PRPC_MESSAGE _pRpcMessage )
{
    DISCRIM_UNION_STRUCT_TYPE __RPC_FAR *UnionStruct;
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dunion_StubDesc);
    
    ( DISCRIM_UNION_STRUCT_TYPE __RPC_FAR * )UnionStruct = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[8] );
        
        NdrComplexStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                    (unsigned char __RPC_FAR * __RPC_FAR *)&UnionStruct,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[48],
                                    (unsigned char)0 );
        
        
        UnionStructProc(UnionStruct);
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)UnionStruct,
                        &__MIDL_TypeFormatString.Format[36] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
dunion_Shutdown(
    PRPC_MESSAGE _pRpcMessage )
{
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &dunion_StubDesc);
    
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


static const MIDL_STUB_DESC dunion_StubDesc = 
    {
    (void __RPC_FAR *)& dunion___RpcServerInterface,
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

static RPC_DISPATCH_FUNCTION dunion_table[] =
    {
    dunion_UnionParamProc,
    dunion_UnionStructProc,
    dunion_Shutdown,
    0
    };
RPC_DISPATCH_TABLE dunion_DispatchTable = 
    {
    3,
    dunion_table
    };

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  2 */	NdrFcShort( 0x0 ),	/* Type Offset=0 */
/*  4 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/*  6 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */
/*  8 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 10 */	NdrFcShort( 0x24 ),	/* Type Offset=36 */
/* 12 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */
/* 14 */	0x5b,		/* FC_END */
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
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x6,		/* FC_SHORT */
/*  6 */	0x26,		/* 38 */
			0x0,		/*  */
#ifndef _ALPHA_
/*  8 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 10 */	NdrFcShort( 0x2 ),	/* Offset= 2 (12) */
/* 12 */	NdrFcShort( 0x4 ),	/* 4 */
/* 14 */	NdrFcShort( 0x3 ),	/* 3 */
/* 16 */	NdrFcLong( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0xffff8006 ),	/* Offset= -32762 (-32742) */
/* 22 */	NdrFcLong( 0x1 ),	/* 1 */
/* 26 */	NdrFcShort( 0xffff800a ),	/* Offset= -32758 (-32732) */
/* 28 */	NdrFcLong( 0x2 ),	/* 2 */
/* 32 */	NdrFcShort( 0xffff8002 ),	/* Offset= -32766 (-32734) */
/* 34 */	NdrFcShort( 0x0 ),	/* Offset= 0 (34) */
/* 36 */	
			0x11, 0x0,	/* FC_RP */
/* 38 */	NdrFcShort( 0xa ),	/* Offset= 10 (48) */
/* 40 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x6,		/* FC_SHORT */
/* 42 */	0x6,		/* 6 */
			0x0,		/*  */
/* 44 */	NdrFcShort( 0xfffffffc ),	/* -4 */
/* 46 */	NdrFcShort( 0xffffffde ),	/* Offset= -34 (12) */
/* 48 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 50 */	NdrFcShort( 0x8 ),	/* 8 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0x0 ),	/* Offset= 0 (54) */
/* 56 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 58 */	0x2,		/* 2 */
			NdrFcShort( 0xffffffed ),	/* Offset= -19 (40) */
			0x5b,		/* FC_END */

			0x0
        }
    };
