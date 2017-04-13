/* this ALWAYS GENERATED file contains the RPC client stubs */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 03:08:24 1998
 */
/* Compiler settings for picklp.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext, oldnames
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#include <string.h>
#if defined( _ALPHA_ )
#include <stdarg.h>
#endif

#include "picklp.h"

#define TYPE_FORMAT_STRING_SIZE   53                                
#define PROC_FORMAT_STRING_SIZE   21                                

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

/* Pickling interface: proc_pickle, ver. 1.0,
   GUID={0xB75AF600,0x9CF4,0x11CD,{0xA0,0x76,0x08,0x00,0x2B,0x2B,0xD7,0x11}} */

handle_t ImplicitPicHandle;


static const RPC_CLIENT_INTERFACE proc_pickle___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0xB75AF600,0x9CF4,0x11CD,{0xA0,0x76,0x08,0x00,0x2B,0x2B,0xD7,0x11}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    0,
    0
    };
RPC_IF_HANDLE proc_pickle_ClientIfHandle = (RPC_IF_HANDLE)& proc_pickle___RpcClientInterface;

extern const MIDL_STUB_DESC proc_pickle_StubDesc;

static RPC_BINDING_HANDLE proc_pickle__MIDL_AutoBindHandle;


/* [decode][encode] */ void ProcPickle( 
    /* [string][out][in] */ unsigned char __RPC_FAR *pTextId,
    /* [out][in] */ OBJECT1 __RPC_FAR *pObject1,
    /* [out][in] */ OBJECT2 __RPC_FAR *pObject2)
{

#if defined( _ALPHA_ )
    va_list vlist;

    va_start(vlist,pObject2);
#endif

    NdrMesProcEncodeDecode(
                          ImplicitPicHandle,
                          ( PMIDL_STUB_DESC  )&proc_pickle_StubDesc,
                          ( PFORMAT_STRING  )&__MIDL_ProcFormatString.Format[0],
                          ( unsigned char __RPC_FAR * )&pTextId,
                          ( unsigned char __RPC_FAR * )&pObject1,
                          ( unsigned char __RPC_FAR * )&pObject2);
    
}


static const MIDL_STUB_DESC proc_pickle_StubDesc = 
    {
    (void __RPC_FAR *)& proc_pickle___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &ImplicitPicHandle,
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

#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			0x32,		/* FC_BIND_PRIMITIVE */
			0x70,		/* 112 */
/*  2 */	NdrFcShort( 0x0 ),	/* 0 */
#ifndef _ALPHA_
/*  4 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/*  6 */	
			0x50,		/* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  8 */	NdrFcShort( 0x0 ),	/* Type Offset=0 */
/* 10 */	
			0x50,		/* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 12 */	NdrFcShort( 0x4 ),	/* Type Offset=4 */
/* 14 */	
			0x50,		/* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 16 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */
/* 18 */	0x5b,		/* FC_END */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  2 */	
			0x22,		/* FC_C_CSTRING */
			0x5c,		/* FC_PAD */
/*  4 */	
			0x11, 0x0,	/* FC_RP */
/*  6 */	NdrFcShort( 0x8 ),	/* Offset= 8 (14) */
/*  8 */	
			0x1d,		/* FC_SMFARRAY */
			0x3,		/* 3 */
/* 10 */	NdrFcShort( 0x10 ),	/* 16 */
/* 12 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 14 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 16 */	NdrFcShort( 0x14 ),	/* 20 */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* Offset= 0 (20) */
/* 22 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 24 */	NdrFcShort( 0xfffffff0 ),	/* Offset= -16 (8) */
/* 26 */	0x6,		/* FC_SHORT */
			0x3e,		/* FC_STRUCTPAD2 */
/* 28 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 30 */	
			0x11, 0x0,	/* FC_RP */
/* 32 */	NdrFcShort( 0xc ),	/* Offset= 12 (44) */
/* 34 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 36 */	NdrFcShort( 0x2 ),	/* 2 */
/* 38 */	0x6,		/* 6 */
			0x0,		/*  */
/* 40 */	NdrFcShort( 0xfffffffe ),	/* -2 */
/* 42 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 44 */	
			0x17,		/* FC_CSTRUCT */
			0x1,		/* 1 */
/* 46 */	NdrFcShort( 0x2 ),	/* 2 */
/* 48 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (34) */
/* 50 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */

			0x0
        }
    };
