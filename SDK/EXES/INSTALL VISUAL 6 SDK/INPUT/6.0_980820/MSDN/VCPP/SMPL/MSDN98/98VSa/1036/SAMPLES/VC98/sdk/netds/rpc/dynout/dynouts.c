
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1995-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/
//
// Copyright 1996-1997 Microsoft Corporation.  All Rights Reserved.
//
//
// Sample code to show server-side
// memory allocation for an [out] parameter
//
//

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "dynout.h"

#ifdef NODEBUG
#define CHECK_STATUS(x)
#define TRACE(s)
#else
#define CHECK_STATUS(x)	{if (x!=RPC_S_OK) { printf("RPC Err: %d\nfile = %s, line=%d.",x,__FILE__,__LINE__); exit(x);}}
#define TRACE(s)	puts(s)
#endif

void main(int argc,char **argv)
{
	RPC_STATUS			rpcStatus;
	RPC_BINDING_VECTOR  *vectBinding;
	unsigned char 		*szEntryName;

	TRACE("RpcServerRegisterIf");
	rpcStatus=RpcServerRegisterIf(MemStuff_v1_0_s_ifspec,0,0);
	CHECK_STATUS(rpcStatus);

	TRACE("RpcServerUseAllProtseqs");
	rpcStatus=RpcServerUseAllProtseqs(RPC_C_PROTSEQ_MAX_REQS_DEFAULT,NULL);
	CHECK_STATUS(rpcStatus);

	TRACE("RpcServerInqBindings");
	rpcStatus=RpcServerInqBindings(&vectBinding);
	CHECK_STATUS(rpcStatus);

	TRACE("RpcNsBindingExport");
	szEntryName="/.:/MyServer";
	rpcStatus=RpcNsBindingExport(RPC_C_NS_SYNTAX_DEFAULT,szEntryName,MemStuff_v1_0_s_ifspec,vectBinding,NULL);
	CHECK_STATUS(rpcStatus);

	TRACE("RpcEpRegister");
	rpcStatus=RpcEpRegister(MemStuff_v1_0_s_ifspec,
				vectBinding,
				NULL,NULL);
	CHECK_STATUS(rpcStatus);

	TRACE("RpcBindingVectorFree");
	rpcStatus=RpcBindingVectorFree(&vectBinding);
	CHECK_STATUS(rpcStatus);

	puts("\n\n");
	puts("(C) Microsoft New Zealand Limited. Written by Michael Howard, " __DATE__);
	puts("\nListening....");

	rpcStatus=RpcServerListen(1,RPC_C_LISTEN_MAX_CALLS_DEFAULT,FALSE);
	CHECK_STATUS(rpcStatus);
}

void  __RPC_FAR * __RPC_API midl_user_allocate(size_t len)
{
    return malloc(len);
}

void __RPC_API midl_user_free(void __RPC_FAR * ptr)
{
    free(ptr);
}
