//-----------------------------------------------------------------------------
//
//	FILE:		a64dma.c
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

#include <ac.h>
#include <a64thunk.h>
#include <am.h>

#if defined(AUDIO64_THUNKS_SHINOBI)
#include <sg_syg2.h>
#endif

// STARTDOC -------------------------------------------------------------------
// FUNCTION NAME a64DmaResumeAll
// TERSE DESCRIPTION Resumes all G2 DMA channels.
//
// FORMAT
//
// #include <a64dma.h>
//
// KTBOOL a64DmaResumeAll(void)
//
// PARAMETERS
//
// void
//
// RETURN VALUE
//
// KTTRUE		If successful.
//
// KTFALSE		An error occurred.
//
// FUNCTION
//
// Resumes all G2 DMA channels.
// ENDDOC ---------------------------------------------------------------------

KTBOOL a64DmaResumeAll(void)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

	return (syG2DmaResumeAll() == SYE_G2_ERR_NOTHING);

#else

	//	Provide an alternate thunking here.

#endif
}

// STARTDOC -------------------------------------------------------------------
// FUNCTION NAME a64DmaSuspendAll
// TERSE DESCRIPTION Suspends all G2 DMA channels.
//
// FORMAT
//
// #include <a64dma.h>
//
// KTBOOL a64DmaSuspendAll(void)
//
// PARAMETERS
//
// void
//
// RETURN VALUE
//
// KTTRUE		If successful.
//
// KTFALSE		An error occurred.
//
// FUNCTION
//
// Suspends all G2 DMA channels; required when directly accessing G2 bus data.
// ENDDOC ---------------------------------------------------------------------

KTBOOL a64DmaSuspendAll(void)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

	return (syG2DmaSuspendAll() == SYE_G2_ERR_NOTHING);

#else

	//	Provide an alternate thunking here.

#endif
}

//-----------------------------------------------------------------------------
//	ahdma.c (end)
//-----------------------------------------------------------------------------
