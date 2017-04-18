//-----------------------------------------------------------------------------
//
//	FILE:		a64chain.c
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
#include <shinobi.h>
#include <sg_chain.h>
#endif

// STARTDOC -------------------------------------------------------------------
// FUNCTION NAME a64ChainAddHandler
// TERSE DESCRIPTION Chains (installs hook for) event interrupt handler.
//
// FORMAT
//
// #include <a64chain.h>
//
// KTU32 a64ChainAddHandler(KTS16 event, AC_ARM_INTERRUPT_HANDLER isr,
//							KTU32 priority, void *arg)
//
// PARAMETERS
//
// event
//
// isr
//
// priority
//
// arg
//
// RETURN VALUE
//
// non-zero		If successful, the handle for the installed handler.
//
// zero			An error occurred.
//
// FUNCTION
//
// Chains (installs hook for) event interrupt handler.
// ENDDOC ---------------------------------------------------------------------

KTU32 a64ChainAddHandler(KTS16 event, AC_ARM_INTERRUPT_HANDLER isr,
	KTU32 priority, void *arg)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

	return (syChainAddHandler(event, isr, priority, arg));

#else

	//	Provide an alternate thunking here.

#endif
}

// STARTDOC -------------------------------------------------------------------
// FUNCTION NAME a64ChainDeleteHandler
// TERSE DESCRIPTION Deletes (removes hook for) event interrupt handler.
//
// FORMAT
//
// #include <a64chain.h>
//
// void a64ChainDeleteHandler(KTU32 handle)
//
// PARAMETERS
//
// handle
//
// RETURN VALUE
//
// void
//
// FUNCTION
//
// Deletes (removes hook for) event interrupt handler.
// ENDDOC ---------------------------------------------------------------------

void a64ChainDeleteHandler(KTU32 handle)
{
#if defined(AUDIO64_THUNKS_SHINOBI)

	syChainDeleteHandler(handle);

#else

	//	Provide an alternate thunking here.

#endif
}

//-----------------------------------------------------------------------------
//	ahchain.c (end)
//-----------------------------------------------------------------------------
