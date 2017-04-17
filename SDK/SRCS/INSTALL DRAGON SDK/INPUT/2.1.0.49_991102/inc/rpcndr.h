/*++
THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
PARTICULAR PURPOSE.
Copyright (c) 1995-1998  Microsoft Corporation

Module Name:

rpcndr.h

Abstract:

Notes:


--*/

#ifndef __RPCNDR_H__
#define __RPCNDR_H__

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *  Other MIDL base types / predefined types:
 ****************************************************************************/

#define small char
typedef unsigned char byte;
typedef unsigned char boolean;

#ifndef _WCHAR_T_DEFINED
typedef unsigned short wchar_t;
#define _WCHAR_T_DEFINED
#endif

#ifndef _SIZE_T_DEFINED
typedef unsigned int size_t;
#define _SIZE_T_DEFINED
#endif

#if   (_MSC_VER >= 800)
#define __RPC_CALLEE       __stdcall
#else
#define __RPC_CALLEE
#endif

/****************************************************************************
 * Special things for VC5 Com support
 ****************************************************************************/

#if _MSC_VER >= 1100
#define DECLSPEC_UUID(x)    __declspec(uuid(x))
#else
#define DECLSPEC_UUID(x)
#endif

#if _MSC_VER >= 1100
#define EXTERN_GUID(itf,l1,s1,s2,c1,c2,c3,c4,c5,c6,c7,c8)  \
  EXTERN_C const IID __declspec(selectany) itf = {l1,s1,s2,{c1,c2,c3,c4,c5,c6,c7,c8}}
#else
#define EXTERN_GUID(itf,l1,s1,s2,c1,c2,c3,c4,c5,c6,c7,c8) EXTERN_C const IID itf
#endif


#ifdef CONST_VTABLE
#define CONST_VTBL const
#else
#define CONST_VTBL
#endif


#ifdef __cplusplus
}
#endif

#endif /* __RPCNDR_H__ */
