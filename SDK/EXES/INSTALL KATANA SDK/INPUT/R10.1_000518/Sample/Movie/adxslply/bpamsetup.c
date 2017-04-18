//-----------------------------------------------------------------------------
//
//	FILE:		bpamsetup.c
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

#include "bpacsetup.h"
#include "bpamsetup.h"

//--------------------------------------------------------------------------

AM_ERROR *bpAmError = KTNULL;

//--------------------------------------------------------------------------
//	Setup the AM system
//--------------------------------------------------------------------------

KTBOOL bpAmSetup(AC_DRIVER_TYPE driverType, KTBOOL usePolling,
	AC_CALLBACK_HANDLER theCallback)
{
	// Initialize the AC layer
	if (!bpAcSetup(driverType, usePolling, theCallback))
	{
		// check acErrorGetLast() and/or amErrorGetLast()
		return (KTFALSE);
	}

	// Get error message pointers
	bpAmError = amErrorGetLast();

	// Initialize the AM layer
	if (!amInit())
	{
		// check acErrorGetLast() and/or amErrorGetLast()
		return (KTFALSE);
	}
		
	return (KTTRUE);
}

//--------------------------------------------------------------------------
//	Shutdown the AM system
//--------------------------------------------------------------------------

void bpAmShutdown(void)
{
	// internally amShutdown() calls acSystemShutdown()
	amShutdown();
}
