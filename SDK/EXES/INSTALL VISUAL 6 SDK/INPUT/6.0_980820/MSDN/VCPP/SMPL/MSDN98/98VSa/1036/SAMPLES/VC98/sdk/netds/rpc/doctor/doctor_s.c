/* this ALWAYS GENERATED file contains the RPC server stubs */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:06:39 1998
 */
/* Compiler settings for doctor.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, oldnames
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#include "doctor.h"

#define TYPE_FORMAT_STRING_SIZE   11                                
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

/* Standard interface: doctor, ver. 1.0,
   GUID={0xC2557720,0xCA46,0x1067,{0xB3,0x1C,0x00,0xDD,0x01,0x06,0x62,0xDA}} */


extern RPC_DISPATCH_TABLE doctor_DispatchTable;

static const RPC_SERVER_INTERFACE doctor___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0xC2557720,0xCA46,0x1067,{0xB3,0x1C,0x00,0xDD,0x01,0x06,0x62,0xDA}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    &doctor_DispatchTable,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE doctor_ServerIfHandle = (RPC_IF_HANDLE)& doctor___RpcServerInterface;

extern const MIDL_STUB_DESC doctor_StubDesc;

void __RPC_STUB
doctor_Analyze(
    PRPC_MESSAGE _pRpcMessage )
{
    MIDL_STUB_MESSAGE _StubMsg;
    unsigned char __RPC_FAR *pszInOut;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &doctor_StubDesc);
    
    ( unsigned char __RPC_FAR * )pszInOut = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&pszInOut,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4],
                                       (unsigned char)0 );
        
        
        Analyze(pszInOut);
        
        _StubMsg.BufferLength = 12U;
        _StubMsg.MaxCount = STRSIZE;
        
        NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)pszInOut,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        _pRpcMessage->BufferLength = _StubMsg.BufferLength;
        
        _Status = I_RpcGetBuffer( _pRpcMessage ); 
        if ( _Status )
            RpcRaiseException( _Status );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *) _pRpcMessage->Buffer;
        
        _StubMsg.MaxCount = STRSIZE;
        
        NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)pszInOut,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = STRSIZE;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pszInOut,
                        &__MIDL_TypeFormatString.Format[0] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

void __RPC_STUB
doctor_Shutdown(
    PRPC_MESSAGE _pRpcMessage )
{
    MIDL_STUB_MESSAGE _StubMsg;
    RPC_STATUS _Status;
    
    ((void)(_Status));
    NdrServerInitializeNew(
                          _pRpcMessage,
                          &_StubMsg,
                          &doctor_StubDesc);
    
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


static const MIDL_STUB_DESC doctor_StubDesc = 
    {
    (void __RPC_FAR *)& doctor___RpcServerInterface,
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

static RPC_DISPATCH_FUNCTION doctor_table[] =
    {
    doctor_Analyze,
    doctor_Shutdown,
    0
    };
RPC_DISPATCH_TABLE doctor_DispatchTable = 
    {
    2,
    doctor_table
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
/*  2 */	NdrFcShort( 0x2 ),	/* Offset= 2 (4) */
/*  4 */	
			0x22,		/* FC_C_CSTRING */
			0x44,		/* FC_STRING_SIZED */
/*  6 */	0x40,		/* 64 */
			0x0,		/* 0 */
/*  8 */	NdrFcShort( 0x1f4 ),	/* 500 */

			0x0
        }
    };
