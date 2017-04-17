/*++

Copyright (c) 1991-1998 Microsoft Corporation

Module Name:

    rpc.h

Abstract:

    Master include file for RPC applications.

--*/

#ifndef RPC_NO_WINDOWS_H
#include <windows.h>
#endif // RPC_NO_WINDOWS_H

#ifndef __RPC_H__
#define __RPC_H__

#ifdef __cplusplus
extern "C" {
#endif

#define __RPC_WIN32__
#define __RPC_NT__

typedef void * I_RPC_HANDLE;
typedef long RPC_STATUS;

#define RPC_UNICODE_SUPPORTED
#define __RPC_FAR
#define __RPC_API  __stdcall
#define __RPC_USER __stdcall
#define __RPC_STUB __stdcall
#define RPC_ENTRY  __stdcall

#ifdef THISPREVENTSCOMMFROMCOMPILING
#ifdef IN
#undef IN
#undef OUT
#undef OPTIONAL
#endif /* IN */
#endif

// #include "rpcdce.h"

#include <winerror.h>

#ifdef __cplusplus
}
#endif

#endif // __RPC_H__

