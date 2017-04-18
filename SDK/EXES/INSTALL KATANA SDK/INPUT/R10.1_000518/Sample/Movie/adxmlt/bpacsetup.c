//-----------------------------------------------------------------------------
//
//	FILE:		bpacsetup.c
//
//	DESC:		Boilerplate for Audio64 AC layer initialization.
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

//-----------------------------------------------------------------------------

AC_ERROR_PTR bpAcError = KTNULL;

//-----------------------------------------------------------------------------
//	Setup the AC system
//-----------------------------------------------------------------------------

KTBOOL bpAcSetup(AC_DRIVER_TYPE driverType, KTBOOL usePolling,
	AC_CALLBACK_HANDLER theCallback)
{
	KTU32 *driverImage = KTNULL;
	KTU32 driverImageSize = 0;
	KTU32 driverSize = 0;
	KTSTRING driverName = KTNULL;

	// Get error message pointer
	bpAcError = acErrorGetLast();

	// Init my file system for the example
	a64FileInit();

	// install a callback handler
	acIntInstallCallbackHandler(theCallback);

	// Initialize the interrupt system
	if (!acIntInit())
	{
		// check acErrorGetLast()
		return (KTFALSE);
	}

	// Determine driver type/name
	if (driverType == AC_DRIVER_DA)
	{
		driverName = AC_DRIVER_NAME_DA;
	}
	else if (driverType == AC_DRIVER_MIDI)
	{
		driverName = AC_DRIVER_NAME_MIDI;
	}
	else
	{
		acErrorSet(AC_OUT_OF_RANGE_PARAMETER,
						"bpAcSetup - driverType is invalid");
		return (KTFALSE);
	}

	// Get the size of the driver
	if (!a64FileGetSize(driverName, &driverSize))
	{
		// check acErrorGetLast()
		return (KTFALSE);
	}
	driverImageSize = SECTOR_ALIGN(driverSize);

	// Get a temp buffer (aligned driver size)
	driverImage = (KTU32*)syMalloc(driverImageSize);
	if (!driverImage)
	{
		// check acErrorGetLast()
		return (KTFALSE);
	}

	// Load the driver (aligned driver size)
	if (!a64FileLoad(driverName, driverImage, driverImageSize))
	{
		// check acErrorGetLast()
		return (KTFALSE);
	}

	// Install the driver (actual driver size)
	if (!acSystemInit(driverType, driverImage, driverSize, usePolling))
	{
		// check acErrorGetLast()
		return (KTFALSE);
	}

	// free the temp buffer
	syFree(driverImage);

	return (KTTRUE);
}

//-----------------------------------------------------------------------------
//	Shutdown the AC system
//-----------------------------------------------------------------------------
  
void bpAcShutdown(void)
{
	acSystemShutdown();
}
