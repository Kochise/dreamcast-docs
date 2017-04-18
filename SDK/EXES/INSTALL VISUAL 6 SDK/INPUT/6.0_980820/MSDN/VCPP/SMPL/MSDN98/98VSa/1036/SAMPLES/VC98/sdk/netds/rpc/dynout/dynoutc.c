
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
// Sample code to show server-side
// memory allocation for an [out] parameter
//
//
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include "dynout.h"

void main(int argc,char **argv)
{
	unsigned char *pr = NULL;
	long lSize;
	int i;
	int bOK;

	RpcTryExcept
	{
		for(;;)
		{
			pr = NULL;	// This is *REALLY* important!

			GrabChunk(&lSize,&pr);
	
			// quick sanity check
			for (i=0, bOK=TRUE; (i < lSize) && bOK; i++)
			{
				if (*pr != pr[i])
				{
					puts("***Error***");
					bOK=FALSE;
					break;
				}
			}

			printf("Returned %d bytes of '%c'\n",lSize,*pr);
			
			midl_user_free(pr);
		}
	}
	RpcExcept(1)
	{
		printf("Err: %u\n",RpcExceptionCode());
	}
	RpcEndExcept
}

void  __RPC_FAR * __RPC_API midl_user_allocate(size_t len)
{
    return malloc(len);
}

void __RPC_API midl_user_free(void __RPC_FAR * ptr)
{

    free(ptr);
}
