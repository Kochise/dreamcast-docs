/* this ALWAYS GENERATED file contains the RPC client stubs */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:05:50 1998
 */
/* Compiler settings for repas.idl, repasc.acf:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, oldnames
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#if defined( _ALPHA_ )
#include <stdarg.h>
#endif

#include "repasc.h"

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

handle_t hrepas;


static const RPC_CLIENT_INTERFACE repas___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0x56BF67C0,0x6503,0x1068,{0xBF,0x67,0x00,0xDD,0x01,0x0F,0xBF,0x25}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE repas_ClientIfHandle = (RPC_IF_HANDLE)& repas___RpcClientInterface;

extern const MIDL_STUB_DESC repas_StubDesc;

static RPC_BINDING_HANDLE repas__MIDL_AutoBindHandle;


void ModifyMyWString( 
    /* [out][in] */ CHAR_STRING __RPC_FAR *pStr)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&repas_StubDesc,
                          0);
        
        
        _Handle = hrepas;
        
        
        _StubMsg.BufferLength = 200U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrXmitOrRepAsMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)pStr,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrXmitOrRepAsUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pStr,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[10],
                                  (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


void ModifyMyString( 
    /* [out][in] */ CHAR_STRING __RPC_FAR *pStr)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&repas_StubDesc,
                          1);
        
        
        _Handle = hrepas;
        
        
        _StubMsg.BufferLength = 100U;
        NdrGetBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg, _StubMsg.BufferLength, _Handle );
        
        NdrFixedArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                               (unsigned char __RPC_FAR *)pStr,
                               (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[24] );
        
        NdrSendReceive( (PMIDL_STUB_MESSAGE) &_StubMsg, (unsigned char __RPC_FAR *) _StubMsg.Buffer );
        
        if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[6] );
        
        NdrFixedArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                 (unsigned char __RPC_FAR * __RPC_FAR *)&pStr,
                                 (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[24],
                                 (unsigned char)0 );
        
        }
    RpcFinally
        {
        NdrFreeBuffer( (PMIDL_STUB_MESSAGE) &_StubMsg );
        
        }
    RpcEndFinally
    
}


void Shutdown( void)
{

    RPC_BINDING_HANDLE _Handle	=	0;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryFinally
        {
        NdrClientInitializeNew(
                          ( PRPC_MESSAGE  )&_RpcMessage,
                          ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                          ( PMIDL_STUB_DESC  )&repas_StubDesc,
                          2);
        
        
        _Handle = hrepas;
        
        
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

extern const XMIT_ROUTINE_QUINTUPLE TransmitAsRoutines[1];

static const MIDL_STUB_DESC repas_StubDesc = 
    {
    (void __RPC_FAR *)& repas___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &hrepas,
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
NDR_SHAREABLE void __RPC_USER
WCHAR_STRING_RepAsTranslateToLocal( PMIDL_STUB_MESSAGE pStubMsg )
{
    WCHAR_STRING_to_local( (WCHAR_STRING __RPC_FAR *) pStubMsg->pTransmitType, 
        (CHAR_STRING __RPC_FAR *) pStubMsg->pPresentedType ); 
}
NDR_SHAREABLE void __RPC_USER
WCHAR_STRING_RepAsTranslateFromLocal( PMIDL_STUB_MESSAGE pStubMsg )
{
    WCHAR_STRING_from_local( (CHAR_STRING __RPC_FAR *) pStubMsg->pPresentedType, 
        (WCHAR_STRING __RPC_FAR * __RPC_FAR *) &pStubMsg->pTransmitType );
}
NDR_SHAREABLE void __RPC_USER
WCHAR_STRING_RepAsFreeInst( PMIDL_STUB_MESSAGE pStubMsg )
{
    WCHAR_STRING_free_inst( (WCHAR_STRING __RPC_FAR *) pStubMsg->pTransmitType );
}
NDR_SHAREABLE void __RPC_USER
WCHAR_STRING_RepAsFreeLocal( PMIDL_STUB_MESSAGE pStubMsg )
{
    WCHAR_STRING_free_local( (CHAR_STRING __RPC_FAR *) pStubMsg->pPresentedType ); 
}

static const XMIT_ROUTINE_QUINTUPLE TransmitAsRoutines[1] = 
        {
            
            {
            WCHAR_STRING_RepAsTranslateFromLocal
            ,WCHAR_STRING_RepAsTranslateToLocal
            ,WCHAR_STRING_RepAsFreeInst
            ,WCHAR_STRING_RepAsFreeLocal
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
/*  8 */	NdrFcShort( 0x14 ),	/* Type Offset=20 */
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
/*  2 */	NdrFcShort( 0x8 ),	/* Offset= 8 (10) */
/*  4 */	
			0x1d,		/* FC_SMFARRAY */
			0x1,		/* 1 */
/*  6 */	NdrFcShort( 0xc8 ),	/* 200 */
/*  8 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 10 */	0x2e,		/* FC_REPRESENT_AS */
			0x11,		/* 17 */
/* 12 */	NdrFcShort( 0x0 ),	/* 0 */
/* 14 */	NdrFcShort( 0x64 ),	/* 100 */
/* 16 */	NdrFcShort( 0xc8 ),	/* 200 */
/* 18 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (4) */
/* 20 */	
			0x11, 0x0,	/* FC_RP */
/* 22 */	NdrFcShort( 0x2 ),	/* Offset= 2 (24) */
/* 24 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 26 */	NdrFcShort( 0x64 ),	/* 100 */
/* 28 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */

			0x0
        }
    };
