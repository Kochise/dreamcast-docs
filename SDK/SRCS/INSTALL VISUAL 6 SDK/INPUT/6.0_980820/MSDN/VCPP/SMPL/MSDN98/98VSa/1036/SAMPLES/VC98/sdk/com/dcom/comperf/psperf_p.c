/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 3.03.0110 */
/* at Mon Mar 30 02:34:57 1998
 */
/* Compiler settings for psperf.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "psperf.h"

#define TYPE_FORMAT_STRING_SIZE   35                                
#define PROC_FORMAT_STRING_SIZE   49                                

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


/* Object interface: ICOMPerformance, ver. 0.0,
   GUID={0xDDC68871,0xE08E,0x11cf,{0xA5,0x35,0x00,0xAA,0x00,0x61,0x5B,0x03}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ICOMPerformance_ServerInfo;

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
    0x303006e, /* MIDL Version 3.3.110 */
    0,
    UserMarshalRoutines,
    0,  /* Reserved1 */
    0,  /* Reserved2 */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

static const unsigned short ICOMPerformance_FormatStringOffsetTable[] = 
    {
    0,
    24
    };

static const MIDL_SERVER_INFO ICOMPerformance_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &ICOMPerformance_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ICOMPerformance_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &ICOMPerformance_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(5) _ICOMPerformanceProxyVtbl = 
{
    &ICOMPerformance_ProxyInfo,
    &IID_ICOMPerformance,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *)-1 /* ICOMPerformance::Test1 */ ,
    (void *)-1 /* ICOMPerformance::Test23 */
};

const CInterfaceStubVtbl _ICOMPerformanceStubVtbl =
{
    &IID_ICOMPerformance,
    &ICOMPerformance_ServerInfo,
    5,
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
#error   -Oif or -Oicf, [wire_marshal] or [user_marshal] attribute, more than 32 methods in the interface.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Test1 */

			0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/*  2 */	NdrFcShort( 0x3 ),	/* 3 */
#ifndef _ALPHA_
/*  4 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/*  6 */	NdrFcShort( 0x8 ),	/* 8 */
/*  8 */	NdrFcShort( 0x8 ),	/* 8 */
/* 10 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter l */

/* 12 */	NdrFcShort( 0x48 ),	/* 72 */
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

	/* Procedure Test23 */

/* 24 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 26 */	NdrFcShort( 0x4 ),	/* 4 */
#ifndef _ALPHA_
/* 28 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 30 */	NdrFcShort( 0x0 ),	/* 0 */
/* 32 */	NdrFcShort( 0x8 ),	/* 8 */
/* 34 */	0x6,		/* 6 */
			0x2,		/* 2 */

	/* Parameter szDesc */

/* 36 */	NdrFcShort( 0x8b ),	/* 139 */
#ifndef _ALPHA_
/* 38 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 40 */	NdrFcShort( 0x18 ),	/* Type Offset=24 */

	/* Return value */

/* 42 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 44 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 46 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x12, 0x0,	/* FC_UP */
/*  2 */	NdrFcShort( 0xc ),	/* Offset= 12 (14) */
/*  4 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/*  6 */	NdrFcShort( 0x2 ),	/* 2 */
/*  8 */	0x9,		/* 9 */
			0x0,		/*  */
/* 10 */	NdrFcShort( 0xfffffffc ),	/* -4 */
/* 12 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 14 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 16 */	NdrFcShort( 0x8 ),	/* 8 */
/* 18 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (4) */
/* 20 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 22 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 24 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 26 */	NdrFcShort( 0x0 ),	/* 0 */
/* 28 */	NdrFcShort( 0x4 ),	/* 4 */
/* 30 */	NdrFcShort( 0x0 ),	/* 0 */
/* 32 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (0) */

			0x0
        }
    };

const CInterfaceProxyVtbl * _psperf_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ICOMPerformanceProxyVtbl,
    0
};

const CInterfaceStubVtbl * _psperf_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ICOMPerformanceStubVtbl,
    0
};

PCInterfaceName const _psperf_InterfaceNamesList[] = 
{
    "ICOMPerformance",
    0
};


#define _psperf_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _psperf, pIID, n)

int __stdcall _psperf_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_psperf_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo psperf_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _psperf_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _psperf_StubVtblList,
    (const PCInterfaceName * ) & _psperf_InterfaceNamesList,
    0, // no delegation
    & _psperf_IID_Lookup, 
    1,
    2
};
