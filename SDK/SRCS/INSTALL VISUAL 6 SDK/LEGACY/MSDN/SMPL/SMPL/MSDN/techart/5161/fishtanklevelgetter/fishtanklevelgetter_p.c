/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 3.01.75 */
/* at Mon Jul 14 09:24:35 1997
 */
/* Compiler settings for FishTankLevelGetter.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY

#include "rpcproxy.h"
#include "FishTankLevelGetter.h"

#define TYPE_FORMAT_STRING_SIZE   43                                
#define PROC_FORMAT_STRING_SIZE   97                                

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


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ILevelGetter, ver. 0.0,
   GUID={0x7F0DFAA2,0xF56D,0x11D0,{0xA9,0x80,0x00,0x20,0x18,0x2A,0x70,0x50}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ILevelGetter_ServerInfo;

#pragma code_seg(".orpc")
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[1];

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    0, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x301004b, /* MIDL Version 3.1.75 */
    0,
    UserMarshalRoutines,
    0,  /* Reserved1 */
    0,  /* Reserved2 */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static const unsigned short ILevelGetter_FormatStringOffsetTable[] = 
    {
    0,
    24,
    48,
    72
    };

static const MIDL_SERVER_INFO ILevelGetter_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ILevelGetter_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ILevelGetter_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ILevelGetter_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(7) _ILevelGetterProxyVtbl = 
{
    &ILevelGetter_ProxyInfo,
    &IID_ILevelGetter,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *)-1 /* ILevelGetter::GetLowestPossibleSafeLevel */ ,
    (void *)-1 /* ILevelGetter::GetHighestPossibleSafeLevel */ ,
    (void *)-1 /* ILevelGetter::GetCurrentLevel */ ,
    (void *)-1 /* ILevelGetter::GetTextMessage */
};

const CInterfaceStubVtbl _ILevelGetterStubVtbl =
{
    &IID_ILevelGetter,
    &ILevelGetter_ServerInfo,
    7,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[1] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure GetLowestPossibleSafeLevel */

			0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/*  2 */	NdrFcShort( 0x3 ),	/* 3 */
#ifndef _ALPHA_
/*  4 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x10 ),	/* 16 */
/* 10 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter plLowestSafeLevel */

/* 12 */	NdrFcShort( 0x2150 ),	/* 8528 */
#ifndef _ALPHA_
/* 14 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 16 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 18 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 20 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 22 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetHighestPossibleSafeLevel */

/* 24 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 26 */	NdrFcShort( 0x4 ),	/* 4 */
#ifndef _ALPHA_
/* 28 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 30 */	NdrFcShort( 0x0 ),	/* 0 */
/* 32 */	NdrFcShort( 0x10 ),	/* 16 */
/* 34 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter plHighestSafeLevel */

/* 36 */	NdrFcShort( 0x2150 ),	/* 8528 */
#ifndef _ALPHA_
/* 38 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 40 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 42 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 44 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 46 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCurrentLevel */

/* 48 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 50 */	NdrFcShort( 0x5 ),	/* 5 */
#ifndef _ALPHA_
/* 52 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x10 ),	/* 16 */
/* 58 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter plCurrentLevel */

/* 60 */	NdrFcShort( 0x2150 ),	/* 8528 */
#ifndef _ALPHA_
/* 62 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 64 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 66 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 68 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 70 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetTextMessage */

/* 72 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 74 */	NdrFcShort( 0x6 ),	/* 6 */
#ifndef _ALPHA_
/* 76 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 78 */	NdrFcShort( 0x0 ),	/* 0 */
/* 80 */	NdrFcShort( 0x8 ),	/* 8 */
/* 82 */	0x5,		/* 5 */
			0x2,		/* 2 */

	/* Parameter ppbstrMessage */

/* 84 */	NdrFcShort( 0x2113 ),	/* 8467 */
#ifndef _ALPHA_
/* 86 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 88 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 90 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 92 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 94 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  2 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/*  4 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  6 */	NdrFcShort( 0x1a ),	/* Offset= 26 (32) */
/*  8 */	
			0x13, 0x0,	/* FC_OP */
/* 10 */	NdrFcShort( 0xc ),	/* Offset= 12 (22) */
/* 12 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 14 */	NdrFcShort( 0x2 ),	/* 2 */
/* 16 */	0x9,		/* 9 */
			0x0,		/*  */
/* 18 */	NdrFcShort( 0xfffffffc ),	/* -4 */
/* 20 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 22 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 24 */	NdrFcShort( 0x8 ),	/* 8 */
/* 26 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (12) */
/* 28 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 30 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 32 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x4 ),	/* 4 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (8) */

			0x0
        }
    };

const CInterfaceProxyVtbl * _FishTankLevelGetter_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ILevelGetterProxyVtbl,
    0
};

const CInterfaceStubVtbl * _FishTankLevelGetter_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ILevelGetterStubVtbl,
    0
};

PCInterfaceName const _FishTankLevelGetter_InterfaceNamesList[] = 
{
    "ILevelGetter",
    0
};


#define _FishTankLevelGetter_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _FishTankLevelGetter, pIID, n)

int __stdcall _FishTankLevelGetter_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_FishTankLevelGetter_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo FishTankLevelGetter_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _FishTankLevelGetter_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _FishTankLevelGetter_StubVtblList,
    (const PCInterfaceName * ) & _FishTankLevelGetter_InterfaceNamesList,
    0, // no delegation
    & _FishTankLevelGetter_IID_Lookup, 
    1,
    2
};
