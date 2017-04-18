/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:08:06 1998
 */
/* Compiler settings for mdlrpc.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, oldnames
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "mdlrpc.h"

#define TYPE_FORMAT_STRING_SIZE   37                                
#define PROC_FORMAT_STRING_SIZE   19                                

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

/* Standard interface: mdlrpc, ver. 1.0,
   GUID={0x5630EAA0,0xCA48,0x1067,{0xB3,0x20,0x00,0xDD,0x01,0x06,0x62,0xDA}} */


extern RPC_DISPATCH_TABLE mdlrpc_DispatchTable;

static const RPC_SERVER_INTERFACE mdlrpc___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0x5630EAA0,0xCA48,0x1067,{0xB3,0x20,0x00,0xDD,0x01,0x06,0x62,0xDA}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &mdlrpc_DispatchTable,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE mdlrpc_ServerIfHandle = (RPC_IF_HANDLE)& mdlrpc___RpcServerInterface;

extern const MIDL_STUB_DESC mdlrpc_StubDesc;

void __RPC_STUB
mdlrpc_MandelCalc(
    PRPC_MESSAGE _pRpcMessage )
{
    LINEBUF _AM0;
    MIDL_STUB_MESSAGE _StubMsg;
    LINEBUF __RPC_FAR *pbBuf;
    PCPOINT pcptLL;
    PLONGRECT prcDraw;
    double precision;
    unsigned long ulThreshold;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &mdlrpc_StubDesc);
    
    ( PCPOINT  )pcptLL = 0;
    ( PLONGRECT  )prcDraw = 0;
    ( LINEBUF __RPC_FAR * )pbBuf = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&pcptLL,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4],
                                   (unsigned char)0 );
        
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&prcDraw,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[16],
                                   (unsigned char)0 );
        
        precision = *(( double __RPC_FAR * )_StubMsg.Buffer)++;
        
        ulThreshold = *(( unsigned long __RPC_FAR * )_StubMsg.Buffer)++;
        
        pbBuf = &_AM0;
        
        MandelCalc(
              pcptLL,
              prcDraw,
              precision,
              ulThreshold,
              pbBuf);
        
        _StubMsg.BufferLength = 2400U;
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        NdrFixedArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                               (unsigned char __RPC_FAR *)pbBuf,
                               (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pbBuf,
                        &__MIDL_TypeFormatString.Format[26] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


static const MIDL_STUB_DESC mdlrpc_StubDesc = 
    {
    (void __RPC_FAR *)& mdlrpc___RpcServerInterface,
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

static RPC_DISPATCH_FUNCTION mdlrpc_table[] =
    {
    mdlrpc_MandelCalc,
    0
    };
RPC_DISPATCH_TABLE mdlrpc_DispatchTable = 
    {
    1,
    mdlrpc_table
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
/*  4 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  6 */	NdrFcShort( 0xc ),	/* Type Offset=12 */
/*  8 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xc,		/* FC_DOUBLE */
/* 10 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 12 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 14 */	NdrFcShort( 0x1a ),	/* Type Offset=26 */
/* 16 */	0x5b,		/* FC_END */
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
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/*  6 */	NdrFcShort( 0x10 ),	/* 16 */
/*  8 */	0xc,		/* FC_DOUBLE */
			0xc,		/* FC_DOUBLE */
/* 10 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 12 */	
			0x11, 0x0,	/* FC_RP */
/* 14 */	NdrFcShort( 0x2 ),	/* Offset= 2 (16) */
/* 16 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 18 */	NdrFcShort( 0x10 ),	/* 16 */
/* 20 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 22 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 24 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 26 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 28 */	NdrFcShort( 0x2 ),	/* Offset= 2 (30) */
/* 30 */	
			0x1d,		/* FC_SMFARRAY */
			0x1,		/* 1 */
/* 32 */	NdrFcShort( 0x960 ),	/* 2400 */
/* 34 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */

			0x0
        }
    };
