//-----------------------------------------------------------------------------
//
//	FILE:		bpamsetup.h
//
//	DESC:		Boilerplate for Audio64 AM layer initialization.
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

#if !defined(_BPAMSETUP_H_)
#define _BPAMSETUP_H_

#include <ac.h>
#include <a64thunk.h>
#include <am.h>

#include <bpacsetup.h>

#ifdef __cplusplus
extern "C" {
#endif

KTBOOL bpAmSetup(AC_DRIVER_TYPE driverType, KTBOOL usePolling,
	AC_CALLBACK_HANDLER theCallback);
void bpAmShutdown(void);

#ifdef __cplusplus
}
#endif

#endif // _AMSETUP_H_
