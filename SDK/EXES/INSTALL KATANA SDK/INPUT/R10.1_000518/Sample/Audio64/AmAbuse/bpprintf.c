//-----------------------------------------------------------------------------
//
//	FILE:		bpprintf.c
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

#include <stdarg.h>
#include <stdio.h>
#include <shinobi.h>

#include "bpprintf.h"

//-----------------------------------------------------------------------------
// For a binary/retail type build that uses any of the My...() group of functions comment
// out this constant. If this is left in for a retail build it will fail as there is no
// "console" window to print to...

//#define WRITE_TO_DEBUGGER_CONSOLE

//-----------------------------------------------------------------------------

void bpShowAmError(AM_ERROR *theError)
{
	if (theError)
	{
		bpDebugf("****************************************"
					"***************************************");
		bpDebugf("AM Error #: %u", theError->number);
		bpDebugf("Message: %s", theError->message);
		bpDebugf("****************************************"
					"***************************************");
	}
}

//-----------------------------------------------------------------------------

void bpShowAcError(AC_ERROR_PTR theError)
{
	if (theError)
	{
		bpDebugf("****************************************"
					"***************************************");
		bpDebugf("AC Error #: %u", theError->number);
		bpDebugf("Message: %s", theError->message);
		bpDebugf("****************************************"
					"***************************************");
	}
}

//-----------------------------------------------------------------------------

void bpShowDriverRev(KTU32 *driverImage)
{
	KTU8 majorVersion = 0;
	KTU8 minorVersion = 0;
	KTCHAR localVersion = 0;

	acSystemGetDriverRevision(
			(KTU8*)driverImage, &majorVersion, &minorVersion, &localVersion);

	bpDebugf("----------------------------------------"
				"---------------------------------------");
	bpDebugf("Driver Revision - Major: %u Minor: %u Local: %c",
				majorVersion, minorVersion, localVersion);
	bpDebugf("----------------------------------------"
				"---------------------------------------");
}

//-----------------------------------------------------------------------------

void bpPrintf(KTS16 x, KTS16 y, const KTSTRING format, ...)
{
	va_list argptr;
	KTCHAR buffer[256];
	if (format)
	{
		va_start(argptr, format);
		vsprintf(buffer, format, argptr);
		va_end(argptr);

		njPrint(NJM_LOCATION(x, y), buffer);
	}
}

//-----------------------------------------------------------------------------

void bpDebugf(const KTSTRING format, ...)
{
#if defined(WRITE_TO_DEBUGGER_CONSOLE)
	va_list argptr;
	KTCHAR buffer[256];
	if (format)
	{
		va_start(argptr, format);
		vsprintf(buffer, format, argptr);
		va_end(argptr);

#if defined(WRITE_TO_DEBUGGER_CONSOLE)
		debug_write(1, buffer, strlen(buffer));
#endif
	}
#endif
}


