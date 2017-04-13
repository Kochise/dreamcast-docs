
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

#include <assert.h>
#include "stdio.h"
#include "string.h"
#include "dynout.h"

short GrabChunk(long *lSize, unsigned char **ppData)
{
	int cbChunk = rand() % 10000;	// how much memory to grab
	int cChar = 33 + rand()%30;		// what to fill it with

	printf("GrabChunk() allocating %d bytes of '%c'\n",cbChunk,cChar);

	*lSize = (long)cbChunk;
	*ppData = midl_user_allocate(cbChunk);
	memset(*ppData,cChar,cbChunk);

	return 0;
}
