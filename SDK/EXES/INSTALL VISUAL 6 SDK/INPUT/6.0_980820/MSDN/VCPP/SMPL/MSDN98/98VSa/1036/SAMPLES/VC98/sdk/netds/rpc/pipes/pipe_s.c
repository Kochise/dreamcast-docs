/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:08:39 1998
 */
/* Compiler settings for pipe.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "pipe.h"

#define TYPE_FORMAT_STRING_SIZE   15                                
#define PROC_FORMAT_STRING_SIZE   27                                

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

/* Standard interface: pipe_sample, ver. 1.0,
   GUID={0x60ceb4a0,0xc2f1,0x11cf,{0x95,0x56,0x00,0xaa,0x00,0x37,0x4e,0x69}} */


extern const MIDL_SERVER_INFO pipe_sample_ServerInfo;

extern RPC_DISPATCH_TABLE pipe_sample_v1_0_DispatchTable;

static const RPC_SERVER_INTERFACE pipe_sample___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0x60ceb4a0,0xc2f1,0x11cf,{0x95,0x56,0x00,0xaa,0x00,0x37,0x4e,0x69}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &pipe_sample_v1_0_DispatchTable,
    0,
    0,
    0,
    &pipe_sample_ServerInfo,
    RPC_INTERFACE_HAS_PIPES
    };
RPC_IF_HANDLE pipe_sample_v1_0_s_ifspec = (RPC_IF_HANDLE)& pipe_sample___RpcServerInterface;

extern const MIDL_STUB_DESC pipe_sample_StubDesc;

void __RPC_STUB
pipe_sample_ShutDown(
    PRPC_MESSAGE _pRpcMessage )
{
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &pipe_sample_StubDesc);
    
    RpcTryFinally
        {
        
        ShutDown();
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


static const MIDL_STUB_DESC pipe_sample_StubDesc = 
    {
    (void __RPC_FAR *)& pipe_sample___RpcServerInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    0, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
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

static RPC_DISPATCH_FUNCTION pipe_sample_table[] =
    {
    NdrServerCall2,
    pipe_sample_ShutDown,
    0
    };
RPC_DISPATCH_TABLE pipe_sample_v1_0_DispatchTable = 
    {
    2,
    pipe_sample_table
    };

static const SERVER_ROUTINE pipe_sample_ServerRoutineTable[] = 
    {
    (SERVER_ROUTINE)ScrambleFile,
    (SERVER_ROUTINE)ShutDown
    };

static const unsigned short pipe_sample_FormatStringOffsetTable[] = 
    {
    0,
    24
    };

static const MIDL_SERVER_INFO pipe_sample_ServerInfo = 
    {
    &pipe_sample_StubDesc,
    pipe_sample_ServerRoutineTable,
    __MIDL_ProcFormatString.Format,
    pipe_sample_FormatStringOffsetTable,
    0,
    0,
    0,
    0
    };

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, idl pipes.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure ScrambleFile */

			0x32,		/* FC_BIND_PRIMITIVE */
			0x40,		/* 64 */
/*  2 */	NdrFcShort( 0x0 ),	/* 0 */
#ifndef _ALPHA_
/*  4 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/*  6 */	NdrFcShort( 0x8 ),	/* 8 */
/*  8 */	NdrFcShort( 0x0 ),	/* 0 */
/* 10 */	0x8,		/* 8 */
			0x2,		/* 2 */

	/* Parameter Action */

/* 12 */	NdrFcShort( 0x48 ),	/* 72 */
#ifndef _ALPHA_
/* 14 */	NdrFcShort( 0x0 ),	/* x86, MIPS, PPC Stack size/offset = 0 */
#else
			NdrFcShort( 0x0 ),	/* Alpha Stack size/offset = 0 */
#endif
/* 16 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pipe_data */

/* 18 */	NdrFcShort( 0x11c ),	/* 284 */
#ifndef _ALPHA_
/* 20 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 22 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */
/* 24 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x11, 0x0,	/* FC_RP */
/*  2 */	NdrFcShort( 0x4 ),	/* Offset= 4 (6) */
/*  4 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/*  6 */	0xb5,		/* FC_PIPE */
			0x0,		/* 0 */
/*  8 */	NdrFcShort( 0xfffffffc ),	/* Offset= -4 (4) */
/* 10 */	NdrFcShort( 0x1 ),	/* 1 */
/* 12 */	NdrFcShort( 0x1 ),	/* 1 */

			0x0
        }
    };
