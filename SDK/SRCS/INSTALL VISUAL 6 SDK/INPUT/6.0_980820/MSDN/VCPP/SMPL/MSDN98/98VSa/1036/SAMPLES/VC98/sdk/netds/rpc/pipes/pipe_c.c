/* this ALWAYS GENERATED file contains the RPC client stubs */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:08:39 1998
 */
/* Compiler settings for pipe.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#if defined( _ALPHA_ )
#include <stdarg.h>
#endif

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

handle_t global_pipe_sample_handle;


static const RPC_CLIENT_INTERFACE pipe_sample___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0x60ceb4a0,0xc2f1,0x11cf,{0x95,0x56,0x00,0xaa,0x00,0x37,0x4e,0x69}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    0,
    RPC_INTERFACE_HAS_PIPES
    };
RPC_IF_HANDLE pipe_sample_v1_0_c_ifspec = (RPC_IF_HANDLE)& pipe_sample___RpcClientInterface;

extern const MIDL_STUB_DESC pipe_sample_StubDesc;

static RPC_BINDING_HANDLE pipe_sample__MIDL_AutoBindHandle;


void ScrambleFile( 
    /* [in] */ unsigned long Action,
    /* [out][in] */ CHAR_PIPE_TYPE __RPC_FAR *pipe_data)
{

    
#if defined( _ALPHA_ )
    va_list vlist;
#endif
    
#if defined( _ALPHA_ )
    va_start(vlist,pipe_data);
    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&pipe_sample_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0],
                  vlist.a0);
#elif defined( _PPC_ ) || defined( _MIPS_ )

    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&pipe_sample_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0],
                  ( unsigned char __RPC_FAR * )&Action,
                  ( unsigned char __RPC_FAR * )&pipe_data);
#else
    NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&pipe_sample_StubDesc,
                  (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0],
                  ( unsigned char __RPC_FAR * )&Action);
#endif
    
}


void ShutDown( void)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&pipe_sample_StubDesc,
                          1);
        
        
        _Handle = global_pipe_sample_handle;
        
        
        _StubMsg.BufferLength = 0U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


static const MIDL_STUB_DESC pipe_sample_StubDesc = 
    {
    (void __RPC_FAR *)& pipe_sample___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &global_pipe_sample_handle,
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
