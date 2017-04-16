/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 3.01.75 */
/* at Thu Jan 08 00:20:49 1998
 */
/* Compiler settings for FinSrvr.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: none
*/
//@@MIDL_FILE_HEADING(  )

#define USE_STUBLESS_PROXY

#include "rpcproxy.h"
#include "FinSrvr.h"

#define TYPE_FORMAT_STRING_SIZE   885                               
#define PROC_FORMAT_STRING_SIZE   217                               

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


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IPerfmonObject, ver. 0.0,
   GUID={0x3DBD6FB0,0xFFA7,0x11d0,{0x9F,0x8C,0x40,0x00,0x04,0x49,0x13,0x41}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPerfmonObject_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IPerfmonObject_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    24,
    48,
    72,
    96
    };

static const MIDL_SERVER_INFO IPerfmonObject_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IPerfmonObject_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IPerfmonObject_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IPerfmonObject_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(12) _IPerfmonObjectProxyVtbl = 
{
    &IPerfmonObject_ProxyInfo,
    &IID_IPerfmonObject,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IPerfmonObject::GetName */ ,
    (void *)-1 /* IPerfmonObject::GetHelp */ ,
    (void *)-1 /* IPerfmonObject::GetIndex */ ,
    (void *)-1 /* IPerfmonObject::GetNumCounters */ ,
    (void *)-1 /* IPerfmonObject::GetCounters */
};


static const PRPC_STUB_FUNCTION IPerfmonObject_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IPerfmonObjectStubVtbl =
{
    &IID_IPerfmonObject,
    &IPerfmonObject_ServerInfo,
    12,
    &IPerfmonObject_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IPerfmonCounter, ver. 0.0,
   GUID={0x3DBD6FB1,0xFFA7,0x11d0,{0x9F,0x8C,0x40,0x00,0x04,0x49,0x13,0x41}} */


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPerfmonCounter_ServerInfo;

#pragma code_seg(".orpc")
static const unsigned short IPerfmonCounter_FormatStringOffsetTable[] = 
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    120,
    144,
    168,
    72,
    192
    };

static const MIDL_SERVER_INFO IPerfmonCounter_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    __MIDL_ProcFormatString.Format,
    &IPerfmonCounter_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IPerfmonCounter_ProxyInfo =
    {
    &Object_StubDesc,
    __MIDL_ProcFormatString.Format,
    &IPerfmonCounter_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };

CINTERFACE_PROXY_VTABLE(12) _IPerfmonCounterProxyVtbl = 
{
    &IPerfmonCounter_ProxyInfo,
    &IID_IPerfmonCounter,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *)-1 /* IPerfmonCounter::Collect */ ,
    (void *)-1 /* IPerfmonCounter::GetName */ ,
    (void *)-1 /* IPerfmonCounter::GetHelp */ ,
    (void *)-1 /* IPerfmonCounter::GetIndex */ ,
    (void *)-1 /* IPerfmonCounter::GetDataType */
};


static const PRPC_STUB_FUNCTION IPerfmonCounter_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2,
    NdrStubCall2
};

CInterfaceStubVtbl _IPerfmonCounterStubVtbl =
{
    &IID_IPerfmonCounter,
    &IPerfmonCounter_ServerInfo,
    12,
    &IPerfmonCounter_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IFinSessn, ver. 0.0,
   GUID={0x0166BE92,0x87E2,0x11D1,{0x8D,0xB5,0x20,0x4C,0x4F,0x4F,0x50,0x20}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")
CINTERFACE_PROXY_VTABLE(7) _IFinSessnProxyVtbl = 
{
    0,
    &IID_IFinSessn,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IFinSessn_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IFinSessnStubVtbl =
{
    &IID_IFinSessn,
    0,
    7,
    &IFinSessn_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: ICFinCntrs, ver. 0.0,
   GUID={0x0166BE94,0x87E2,0x11D1,{0x8D,0xB5,0x20,0x4C,0x4F,0x4F,0x50,0x20}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2];

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

CINTERFACE_PROXY_VTABLE(7) _ICFinCntrsProxyVtbl = 
{
    0,
    &IID_ICFinCntrs,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfoCount */ ,
    0 /* (void *)-1 /* IDispatch::GetTypeInfo */ ,
    0 /* (void *)-1 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION ICFinCntrs_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _ICFinCntrsStubVtbl =
{
    &IID_ICFinCntrs,
    0,
    7,
    &ICFinCntrs_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
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

	/* Procedure GetName */

			0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/*  2 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/*  4 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x8 ),	/* 8 */
/* 10 */	0x5,		/* 5 */
			0x2,		/* 2 */

	/* Parameter pName */

/* 12 */	NdrFcShort( 0x2113 ),	/* 8467 */
#ifndef _ALPHA_
/* 14 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 16 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */

	/* Return value */

/* 18 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 20 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 22 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetHelp */

/* 24 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 26 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 28 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 30 */	NdrFcShort( 0x0 ),	/* 0 */
/* 32 */	NdrFcShort( 0x8 ),	/* 8 */
/* 34 */	0x5,		/* 5 */
			0x2,		/* 2 */

	/* Parameter pHelp */

/* 36 */	NdrFcShort( 0x2113 ),	/* 8467 */
#ifndef _ALPHA_
/* 38 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 40 */	NdrFcShort( 0x2a ),	/* Type Offset=42 */

	/* Return value */

/* 42 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 44 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 46 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetIndex */

/* 48 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 50 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 52 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x10 ),	/* 16 */
/* 58 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter pIndex */

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

	/* Procedure GetIndex */


	/* Procedure GetNumCounters */

/* 72 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 74 */	NdrFcShort( 0xa ),	/* 10 */
#ifndef _ALPHA_
/* 76 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 78 */	NdrFcShort( 0x0 ),	/* 0 */
/* 80 */	NdrFcShort( 0x10 ),	/* 16 */
/* 82 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter pIndex */


	/* Parameter pNumCounters */

/* 84 */	NdrFcShort( 0x2150 ),	/* 8528 */
#ifndef _ALPHA_
/* 86 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 88 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */


	/* Return value */

/* 90 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 92 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 94 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetCounters */

/* 96 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 98 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 100 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 104 */	NdrFcShort( 0x8 ),	/* 8 */
/* 106 */	0x5,		/* 5 */
			0x2,		/* 2 */

	/* Parameter pCounters */

/* 108 */	NdrFcShort( 0x13 ),	/* 19 */
#ifndef _ALPHA_
/* 110 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 112 */	NdrFcShort( 0x38 ),	/* Type Offset=56 */

	/* Return value */

/* 114 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 116 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 118 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Collect */

/* 120 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 122 */	NdrFcShort( 0x7 ),	/* 7 */
#ifndef _ALPHA_
/* 124 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 128 */	NdrFcShort( 0x8 ),	/* 8 */
/* 130 */	0x5,		/* 5 */
			0x2,		/* 2 */

	/* Parameter pVariant */

/* 132 */	NdrFcShort( 0x4113 ),	/* 16659 */
#ifndef _ALPHA_
/* 134 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 136 */	NdrFcShort( 0x34a ),	/* Type Offset=842 */

	/* Return value */

/* 138 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 140 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 142 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetName */

/* 144 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 146 */	NdrFcShort( 0x8 ),	/* 8 */
#ifndef _ALPHA_
/* 148 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 152 */	NdrFcShort( 0x8 ),	/* 8 */
/* 154 */	0x5,		/* 5 */
			0x2,		/* 2 */

	/* Parameter pName */

/* 156 */	NdrFcShort( 0x2113 ),	/* 8467 */
#ifndef _ALPHA_
/* 158 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 160 */	NdrFcShort( 0x358 ),	/* Type Offset=856 */

	/* Return value */

/* 162 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 164 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 166 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetHelp */

/* 168 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 170 */	NdrFcShort( 0x9 ),	/* 9 */
#ifndef _ALPHA_
/* 172 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 174 */	NdrFcShort( 0x0 ),	/* 0 */
/* 176 */	NdrFcShort( 0x8 ),	/* 8 */
/* 178 */	0x5,		/* 5 */
			0x2,		/* 2 */

	/* Parameter pHelp */

/* 180 */	NdrFcShort( 0x2113 ),	/* 8467 */
#ifndef _ALPHA_
/* 182 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 184 */	NdrFcShort( 0x366 ),	/* Type Offset=870 */

	/* Return value */

/* 186 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 188 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 190 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetDataType */

/* 192 */	0x33,		/* FC_AUTO_HANDLE */
			0x64,		/* 100 */
/* 194 */	NdrFcShort( 0xb ),	/* 11 */
#ifndef _ALPHA_
/* 196 */	NdrFcShort( 0xc ),	/* x86, MIPS, PPC Stack size/offset = 12 */
#else
			NdrFcShort( 0x18 ),	/* Alpha Stack size/offset = 24 */
#endif
/* 198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 200 */	NdrFcShort( 0xe ),	/* 14 */
/* 202 */	0x4,		/* 4 */
			0x2,		/* 2 */

	/* Parameter pDataType */

/* 204 */	NdrFcShort( 0x2150 ),	/* 8528 */
#ifndef _ALPHA_
/* 206 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 208 */	0x6,		/* FC_SHORT */
			0x0,		/* 0 */

	/* Return value */

/* 210 */	NdrFcShort( 0x70 ),	/* 112 */
#ifndef _ALPHA_
/* 212 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 214 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  2 */	NdrFcShort( 0x1a ),	/* Offset= 26 (28) */
/*  4 */	
			0x13, 0x0,	/* FC_OP */
/*  6 */	NdrFcShort( 0xc ),	/* Offset= 12 (18) */
/*  8 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 10 */	NdrFcShort( 0x2 ),	/* 2 */
/* 12 */	0x9,		/* 9 */
			0x0,		/*  */
/* 14 */	NdrFcShort( 0xfffffffc ),	/* -4 */
/* 16 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 18 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 20 */	NdrFcShort( 0x8 ),	/* 8 */
/* 22 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (8) */
/* 24 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 26 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 28 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 30 */	NdrFcShort( 0x0 ),	/* 0 */
/* 32 */	NdrFcShort( 0x4 ),	/* 4 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (4) */
/* 38 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 40 */	NdrFcShort( 0x2 ),	/* Offset= 2 (42) */
/* 42 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 44 */	NdrFcShort( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x4 ),	/* 4 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0xffffffd2 ),	/* Offset= -46 (4) */
/* 52 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 54 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 56 */	
			0x11, 0x10,	/* FC_RP */
/* 58 */	NdrFcShort( 0x2 ),	/* Offset= 2 (60) */
/* 60 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 62 */	NdrFcLong( 0x0 ),	/* 0 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x0 ),	/* 0 */
/* 70 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 72 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 74 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 76 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 78 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 80 */	NdrFcShort( 0x2fa ),	/* Offset= 762 (842) */
/* 82 */	
			0x13, 0x0,	/* FC_OP */
/* 84 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (822) */
/* 86 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x6,		/* FC_SHORT */
/* 88 */	0x6,		/* 6 */
			0x0,		/*  */
/* 90 */	NdrFcShort( 0xfffffff8 ),	/* -8 */
/* 92 */	NdrFcShort( 0x2 ),	/* Offset= 2 (94) */
/* 94 */	NdrFcShort( 0x10 ),	/* 16 */
/* 96 */	NdrFcShort( 0x29 ),	/* 41 */
/* 98 */	NdrFcLong( 0x3 ),	/* 3 */
/* 102 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32658) */
/* 104 */	NdrFcLong( 0x11 ),	/* 17 */
/* 108 */	NdrFcShort( 0xffff8002 ),	/* Offset= -32766 (-32658) */
/* 110 */	NdrFcLong( 0x2 ),	/* 2 */
/* 114 */	NdrFcShort( 0xffff8006 ),	/* Offset= -32762 (-32648) */
/* 116 */	NdrFcLong( 0x4 ),	/* 4 */
/* 120 */	NdrFcShort( 0xffff800a ),	/* Offset= -32758 (-32638) */
/* 122 */	NdrFcLong( 0x5 ),	/* 5 */
/* 126 */	NdrFcShort( 0xffff800c ),	/* Offset= -32756 (-32630) */
/* 128 */	NdrFcLong( 0xb ),	/* 11 */
/* 132 */	NdrFcShort( 0xffff8006 ),	/* Offset= -32762 (-32630) */
/* 134 */	NdrFcLong( 0xa ),	/* 10 */
/* 138 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32622) */
/* 140 */	NdrFcLong( 0x6 ),	/* 6 */
/* 144 */	NdrFcShort( 0xca ),	/* Offset= 202 (346) */
/* 146 */	NdrFcLong( 0x7 ),	/* 7 */
/* 150 */	NdrFcShort( 0xffff800c ),	/* Offset= -32756 (-32606) */
/* 152 */	NdrFcLong( 0x8 ),	/* 8 */
/* 156 */	NdrFcShort( 0xffffff68 ),	/* Offset= -152 (4) */
/* 158 */	NdrFcLong( 0xd ),	/* 13 */
/* 162 */	NdrFcShort( 0xffffff9a ),	/* Offset= -102 (60) */
/* 164 */	NdrFcLong( 0x9 ),	/* 9 */
/* 168 */	NdrFcShort( 0xb8 ),	/* Offset= 184 (352) */
/* 170 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 174 */	NdrFcShort( 0xc4 ),	/* Offset= 196 (370) */
/* 176 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 180 */	NdrFcShort( 0x242 ),	/* Offset= 578 (758) */
/* 182 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 186 */	NdrFcShort( 0x240 ),	/* Offset= 576 (762) */
/* 188 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 192 */	NdrFcShort( 0x23e ),	/* Offset= 574 (766) */
/* 194 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 198 */	NdrFcShort( 0x23c ),	/* Offset= 572 (770) */
/* 200 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 204 */	NdrFcShort( 0x23a ),	/* Offset= 570 (774) */
/* 206 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 210 */	NdrFcShort( 0x228 ),	/* Offset= 552 (762) */
/* 212 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 216 */	NdrFcShort( 0x226 ),	/* Offset= 550 (766) */
/* 218 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 222 */	NdrFcShort( 0x22c ),	/* Offset= 556 (778) */
/* 224 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 228 */	NdrFcShort( 0x222 ),	/* Offset= 546 (774) */
/* 230 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 234 */	NdrFcShort( 0x224 ),	/* Offset= 548 (782) */
/* 236 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 240 */	NdrFcShort( 0x222 ),	/* Offset= 546 (786) */
/* 242 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 246 */	NdrFcShort( 0x220 ),	/* Offset= 544 (790) */
/* 248 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 252 */	NdrFcShort( 0x21e ),	/* Offset= 542 (794) */
/* 254 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 258 */	NdrFcShort( 0x21c ),	/* Offset= 540 (798) */
/* 260 */	NdrFcLong( 0x10 ),	/* 16 */
/* 264 */	NdrFcShort( 0xffff8002 ),	/* Offset= -32766 (-32502) */
/* 266 */	NdrFcLong( 0x12 ),	/* 18 */
/* 270 */	NdrFcShort( 0xffff8006 ),	/* Offset= -32762 (-32492) */
/* 272 */	NdrFcLong( 0x13 ),	/* 19 */
/* 276 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32484) */
/* 278 */	NdrFcLong( 0x16 ),	/* 22 */
/* 282 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32478) */
/* 284 */	NdrFcLong( 0x17 ),	/* 23 */
/* 288 */	NdrFcShort( 0xffff8008 ),	/* Offset= -32760 (-32472) */
/* 290 */	NdrFcLong( 0xe ),	/* 14 */
/* 294 */	NdrFcShort( 0x200 ),	/* Offset= 512 (806) */
/* 296 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 300 */	NdrFcShort( 0x206 ),	/* Offset= 518 (818) */
/* 302 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 306 */	NdrFcShort( 0x1c4 ),	/* Offset= 452 (758) */
/* 308 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 312 */	NdrFcShort( 0x1c2 ),	/* Offset= 450 (762) */
/* 314 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 318 */	NdrFcShort( 0x1c0 ),	/* Offset= 448 (766) */
/* 320 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 324 */	NdrFcShort( 0x1ba ),	/* Offset= 442 (766) */
/* 326 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 330 */	NdrFcShort( 0x1b4 ),	/* Offset= 436 (766) */
/* 332 */	NdrFcLong( 0x0 ),	/* 0 */
/* 336 */	NdrFcShort( 0x0 ),	/* Offset= 0 (336) */
/* 338 */	NdrFcLong( 0x1 ),	/* 1 */
/* 342 */	NdrFcShort( 0x0 ),	/* Offset= 0 (342) */
/* 344 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (343) */
/* 346 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 348 */	NdrFcShort( 0x8 ),	/* 8 */
/* 350 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 352 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 354 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 358 */	NdrFcShort( 0x0 ),	/* 0 */
/* 360 */	NdrFcShort( 0x0 ),	/* 0 */
/* 362 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 364 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 366 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 368 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 370 */	
			0x13, 0x0,	/* FC_OP */
/* 372 */	NdrFcShort( 0x170 ),	/* Offset= 368 (740) */
/* 374 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x48,		/* 72 */
/* 376 */	NdrFcShort( 0x8 ),	/* 8 */
/* 378 */	NdrFcShort( 0x8 ),	/* 8 */
/* 380 */	NdrFcLong( 0x8 ),	/* 8 */
/* 384 */	NdrFcShort( 0x4c ),	/* Offset= 76 (460) */
/* 386 */	NdrFcLong( 0xd ),	/* 13 */
/* 390 */	NdrFcShort( 0x6c ),	/* Offset= 108 (498) */
/* 392 */	NdrFcLong( 0x9 ),	/* 9 */
/* 396 */	NdrFcShort( 0x88 ),	/* Offset= 136 (532) */
/* 398 */	NdrFcLong( 0xc ),	/* 12 */
/* 402 */	NdrFcShort( 0xb0 ),	/* Offset= 176 (578) */
/* 404 */	NdrFcLong( 0x10 ),	/* 16 */
/* 408 */	NdrFcShort( 0xc8 ),	/* Offset= 200 (608) */
/* 410 */	NdrFcLong( 0x2 ),	/* 2 */
/* 414 */	NdrFcShort( 0xe0 ),	/* Offset= 224 (638) */
/* 416 */	NdrFcLong( 0x3 ),	/* 3 */
/* 420 */	NdrFcShort( 0xf8 ),	/* Offset= 248 (668) */
/* 422 */	NdrFcLong( 0x14 ),	/* 20 */
/* 426 */	NdrFcShort( 0x110 ),	/* Offset= 272 (698) */
/* 428 */	NdrFcShort( 0x0 ),	/* Offset= 0 (428) */
/* 430 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 432 */	NdrFcShort( 0x4 ),	/* 4 */
/* 434 */	0x18,		/* 24 */
			0x0,		/*  */
/* 436 */	NdrFcShort( 0x0 ),	/* 0 */
/* 438 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 440 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 442 */	NdrFcShort( 0x4 ),	/* 4 */
/* 444 */	NdrFcShort( 0x0 ),	/* 0 */
/* 446 */	NdrFcShort( 0x1 ),	/* 1 */
/* 448 */	NdrFcShort( 0x0 ),	/* 0 */
/* 450 */	NdrFcShort( 0x0 ),	/* 0 */
/* 452 */	0x13, 0x0,	/* FC_OP */
/* 454 */	NdrFcShort( 0xfffffe4c ),	/* Offset= -436 (18) */
/* 456 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 458 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 460 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 462 */	NdrFcShort( 0x8 ),	/* 8 */
/* 464 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 466 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 468 */	NdrFcShort( 0x4 ),	/* 4 */
/* 470 */	NdrFcShort( 0x4 ),	/* 4 */
/* 472 */	0x11, 0x0,	/* FC_RP */
/* 474 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (430) */
/* 476 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 478 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 480 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 482 */	NdrFcShort( 0x0 ),	/* 0 */
/* 484 */	0x18,		/* 24 */
			0x0,		/*  */
/* 486 */	NdrFcShort( 0x0 ),	/* 0 */
/* 488 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 492 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 494 */	NdrFcShort( 0xfffffe4e ),	/* Offset= -434 (60) */
/* 496 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 498 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 500 */	NdrFcShort( 0x8 ),	/* 8 */
/* 502 */	NdrFcShort( 0x0 ),	/* 0 */
/* 504 */	NdrFcShort( 0x6 ),	/* Offset= 6 (510) */
/* 506 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 508 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 510 */	
			0x11, 0x0,	/* FC_RP */
/* 512 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (480) */
/* 514 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 516 */	NdrFcShort( 0x0 ),	/* 0 */
/* 518 */	0x18,		/* 24 */
			0x0,		/*  */
/* 520 */	NdrFcShort( 0x0 ),	/* 0 */
/* 522 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 526 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 528 */	NdrFcShort( 0xffffff50 ),	/* Offset= -176 (352) */
/* 530 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 532 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 534 */	NdrFcShort( 0x8 ),	/* 8 */
/* 536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 538 */	NdrFcShort( 0x6 ),	/* Offset= 6 (544) */
/* 540 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 542 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 544 */	
			0x11, 0x0,	/* FC_RP */
/* 546 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (514) */
/* 548 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 550 */	NdrFcShort( 0x4 ),	/* 4 */
/* 552 */	0x18,		/* 24 */
			0x0,		/*  */
/* 554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 556 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 558 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 560 */	NdrFcShort( 0x4 ),	/* 4 */
/* 562 */	NdrFcShort( 0x0 ),	/* 0 */
/* 564 */	NdrFcShort( 0x1 ),	/* 1 */
/* 566 */	NdrFcShort( 0x0 ),	/* 0 */
/* 568 */	NdrFcShort( 0x0 ),	/* 0 */
/* 570 */	0x13, 0x0,	/* FC_OP */
/* 572 */	NdrFcShort( 0xfa ),	/* Offset= 250 (822) */
/* 574 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 576 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 578 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 580 */	NdrFcShort( 0x8 ),	/* 8 */
/* 582 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 584 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 586 */	NdrFcShort( 0x4 ),	/* 4 */
/* 588 */	NdrFcShort( 0x4 ),	/* 4 */
/* 590 */	0x11, 0x0,	/* FC_RP */
/* 592 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (548) */
/* 594 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 596 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 598 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 600 */	NdrFcShort( 0x1 ),	/* 1 */
/* 602 */	0x19,		/* 25 */
			0x0,		/*  */
/* 604 */	NdrFcShort( 0x0 ),	/* 0 */
/* 606 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 608 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 610 */	NdrFcShort( 0x8 ),	/* 8 */
/* 612 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 614 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 616 */	NdrFcShort( 0x4 ),	/* 4 */
/* 618 */	NdrFcShort( 0x4 ),	/* 4 */
/* 620 */	0x13, 0x0,	/* FC_OP */
/* 622 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (598) */
/* 624 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 626 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 628 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 630 */	NdrFcShort( 0x2 ),	/* 2 */
/* 632 */	0x19,		/* 25 */
			0x0,		/*  */
/* 634 */	NdrFcShort( 0x0 ),	/* 0 */
/* 636 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 638 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 640 */	NdrFcShort( 0x8 ),	/* 8 */
/* 642 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 644 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 646 */	NdrFcShort( 0x4 ),	/* 4 */
/* 648 */	NdrFcShort( 0x4 ),	/* 4 */
/* 650 */	0x13, 0x0,	/* FC_OP */
/* 652 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (628) */
/* 654 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 656 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 658 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 660 */	NdrFcShort( 0x4 ),	/* 4 */
/* 662 */	0x19,		/* 25 */
			0x0,		/*  */
/* 664 */	NdrFcShort( 0x0 ),	/* 0 */
/* 666 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 668 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 670 */	NdrFcShort( 0x8 ),	/* 8 */
/* 672 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 674 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 676 */	NdrFcShort( 0x4 ),	/* 4 */
/* 678 */	NdrFcShort( 0x4 ),	/* 4 */
/* 680 */	0x13, 0x0,	/* FC_OP */
/* 682 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (658) */
/* 684 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 686 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 688 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 690 */	NdrFcShort( 0x8 ),	/* 8 */
/* 692 */	0x19,		/* 25 */
			0x0,		/*  */
/* 694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 696 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 698 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 700 */	NdrFcShort( 0x8 ),	/* 8 */
/* 702 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 704 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 706 */	NdrFcShort( 0x4 ),	/* 4 */
/* 708 */	NdrFcShort( 0x4 ),	/* 4 */
/* 710 */	0x13, 0x0,	/* FC_OP */
/* 712 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (688) */
/* 714 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 716 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 718 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 720 */	NdrFcShort( 0x8 ),	/* 8 */
/* 722 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 724 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 726 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 728 */	NdrFcShort( 0x8 ),	/* 8 */
/* 730 */	0x6,		/* 6 */
			0x0,		/*  */
/* 732 */	NdrFcShort( 0xffffffe8 ),	/* -24 */
/* 734 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 736 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (718) */
/* 738 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 740 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 742 */	NdrFcShort( 0x18 ),	/* 24 */
/* 744 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (726) */
/* 746 */	NdrFcShort( 0x0 ),	/* Offset= 0 (746) */
/* 748 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 750 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 752 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 754 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffe83 ),	/* Offset= -381 (374) */
			0x5b,		/* FC_END */
/* 758 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 760 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 762 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 764 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 766 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 768 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 770 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 772 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 774 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 776 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 778 */	
			0x13, 0x0,	/* FC_OP */
/* 780 */	NdrFcShort( 0xfffffe4e ),	/* Offset= -434 (346) */
/* 782 */	
			0x13, 0x10,	/* FC_OP */
/* 784 */	NdrFcShort( 0xfffffcf4 ),	/* Offset= -780 (4) */
/* 786 */	
			0x13, 0x10,	/* FC_OP */
/* 788 */	NdrFcShort( 0xfffffd28 ),	/* Offset= -728 (60) */
/* 790 */	
			0x13, 0x10,	/* FC_OP */
/* 792 */	NdrFcShort( 0xfffffe48 ),	/* Offset= -440 (352) */
/* 794 */	
			0x13, 0x10,	/* FC_OP */
/* 796 */	NdrFcShort( 0xfffffe56 ),	/* Offset= -426 (370) */
/* 798 */	
			0x13, 0x10,	/* FC_OP */
/* 800 */	NdrFcShort( 0x2 ),	/* Offset= 2 (802) */
/* 802 */	
			0x13, 0x0,	/* FC_OP */
/* 804 */	NdrFcShort( 0xfffffcdc ),	/* Offset= -804 (0) */
/* 806 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 808 */	NdrFcShort( 0x10 ),	/* 16 */
/* 810 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 812 */	0x2,		/* FC_CHAR */
			0x38,		/* FC_ALIGNM4 */
/* 814 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 816 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 818 */	
			0x13, 0x0,	/* FC_OP */
/* 820 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (806) */
/* 822 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 824 */	NdrFcShort( 0x20 ),	/* 32 */
/* 826 */	NdrFcShort( 0x0 ),	/* 0 */
/* 828 */	NdrFcShort( 0x0 ),	/* Offset= 0 (828) */
/* 830 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 832 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 834 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 836 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 838 */	NdrFcShort( 0xfffffd10 ),	/* Offset= -752 (86) */
/* 840 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 842 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 844 */	NdrFcShort( 0x1 ),	/* 1 */
/* 846 */	NdrFcShort( 0x10 ),	/* 16 */
/* 848 */	NdrFcShort( 0x0 ),	/* 0 */
/* 850 */	NdrFcShort( 0xfffffd00 ),	/* Offset= -768 (82) */
/* 852 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 854 */	NdrFcShort( 0x2 ),	/* Offset= 2 (856) */
/* 856 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 858 */	NdrFcShort( 0x0 ),	/* 0 */
/* 860 */	NdrFcShort( 0x4 ),	/* 4 */
/* 862 */	NdrFcShort( 0x0 ),	/* 0 */
/* 864 */	NdrFcShort( 0xfffffca4 ),	/* Offset= -860 (4) */
/* 866 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/* 868 */	NdrFcShort( 0x2 ),	/* Offset= 2 (870) */
/* 870 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 872 */	NdrFcShort( 0x0 ),	/* 0 */
/* 874 */	NdrFcShort( 0x4 ),	/* 4 */
/* 876 */	NdrFcShort( 0x0 ),	/* 0 */
/* 878 */	NdrFcShort( 0xfffffc96 ),	/* Offset= -874 (4) */
/* 880 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 882 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

const CInterfaceProxyVtbl * _FinSrvr_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IFinSessnProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ICFinCntrsProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPerfmonObjectProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPerfmonCounterProxyVtbl,
    0
};

const CInterfaceStubVtbl * _FinSrvr_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IFinSessnStubVtbl,
    ( CInterfaceStubVtbl *) &_ICFinCntrsStubVtbl,
    ( CInterfaceStubVtbl *) &_IPerfmonObjectStubVtbl,
    ( CInterfaceStubVtbl *) &_IPerfmonCounterStubVtbl,
    0
};

PCInterfaceName const _FinSrvr_InterfaceNamesList[] = 
{
    "IFinSessn",
    "ICFinCntrs",
    "IPerfmonObject",
    "IPerfmonCounter",
    0
};

const IID *  _FinSrvr_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define _FinSrvr_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _FinSrvr, pIID, n)

int __stdcall _FinSrvr_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _FinSrvr, 4, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _FinSrvr, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _FinSrvr, 4, *pIndex )
    
}

const ExtendedProxyFileInfo FinSrvr_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _FinSrvr_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _FinSrvr_StubVtblList,
    (const PCInterfaceName * ) & _FinSrvr_InterfaceNamesList,
    (const IID ** ) & _FinSrvr_BaseIIDList,
    & _FinSrvr_IID_Lookup, 
    4,
    2
};
