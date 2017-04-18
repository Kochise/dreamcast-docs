//-----------------------------------------------------------------------------
//
//	FILE:		a64file.h
//
//	DESC:		Audio64 hooks for porting G2 DMA function support.
//
//				The Audio64 library contains Audio64 hook functions that map
//				(thunk) to appropriate functions in the Shinobi library. If
//				needed, these may be overridden by explicitly including this
//				module in your object file list and substituting alternate
//				support.
//
//				NOTE:	The public/exported function names MUST be the only
//						globally visible symbols.
//
//	HISTORY:	2000.01.xx	Reworked samples/boilerplates for R10 release.
//
//-----------------------------------------------------------------------------
//	COPYRIGHT (C) SEGA OF AMERICA DREAMCAST, INC. 1998, 1999, 2000
//	All rights reserved.
//
//	Information and source code samples contained herein are provided "as-is",
//	without representations or warranties, and are subject to change without
//	notice.
//
//	SEGA OF AMERICA DREAMCAST, INC. cannot support modifications or derivative
//	works created from the sample source code provided. Developers may use,
//	reproduce, and modify portions or entire sections of the sample source
//	code for the purposes of creating Dreamcast applications.
//
//	Sample source code contained herein may not be appropriate for use under
//	all circumstances. Please consult Developer documentation provided along
//	with your Dreamcast unit for additional information and suggestions.
//-----------------------------------------------------------------------------

#ifndef _A64FILE_H
#define _A64FILE_H

#include <actypes.h>

//-----------------------------------------------------------------------------
//	The Audio64 library is built with AUDIO64_THUNKS_SHINOBI defined.
//-----------------------------------------------------------------------------

#if !defined(AUDIO64_THUNKS_SHINOBI)
#define AUDIO64_THUNKS_SHINOBI
#endif

//-----------------------------------------------------------------------------

// A64_FILE_MAX_HANDLES must be sync'd with FILES (sbinit.c)
#define A64_FILE_MAX_HANDLES		8

typedef enum
{
	A64_FILE_NOP,
	A64_FILE_READ_NEEDED,
	A64_FILE_READ_PENDING,
	A64_FILE_READ_COMPLETE,
	A64_FILE_READ_BUSY,
	A64_FILE_READ_ERROR
} A64_FILE_STATUS;

//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

KTBOOL a64FileInit(void);
KTBOOL a64FileOpen(KTSTRING fileName, KTU32 *fd);
KTBOOL a64FileClose(KTU32 *fd);
KTBOOL a64FileRead(KTU32 fd, KTU8 *buffer, KTU32 size);
KTBOOL a64FileReadAsync(KTU32 fd, KTU8 *buffer, KTU32 size);
KTBOOL a64FileGetSize(KTSTRING fileName, KTU32 *size);
KTBOOL a64FileRewind(KTU32 fd);
KTBOOL a64FileLoad(KTSTRING fileName, KTU32 *buffer, KTU32 size);
A64_FILE_STATUS a64FileGetStatus(KTU32 fd);

#ifdef __cplusplus
}
#endif

#endif	// _A64FILE_H
