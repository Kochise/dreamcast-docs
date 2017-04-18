//-----------------------------------------------------------------------------
//
//	FILE:		bpprintf.h
//
//	DESC:		Boilerplate for miscellaneous Audio64 debugging.
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

#if !defined(_BPPRINTF_H_)
#define _BPPRINTF_H_

#include <ac.h>
#include <a64thunk.h>
#include <am.h>

#ifdef __cplusplus
extern "C" {
#endif

void bpDebugf(const KTSTRING format, ...);
void bpPrintf(KTS16 x, KTS16 y, const KTSTRING format, ...);

void bpShowDriverRev(KTU32 *driverImage);

void bpShowAcError(AC_ERROR_PTR theError);
void bpShowAmError(AM_ERROR *theError);

#ifdef __cplusplus
}
#endif

#endif	//	_BPPRINTF_H_
