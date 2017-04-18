//-----------------------------------------------------------------------------
//
//	FILE:		a64chain.h
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

#if !defined(_A64CHAIN_H_)
#define _A64CHAIN_H_

#include <actypes.h>

//-----------------------------------------------------------------------------
//	The Audio64 library is built with AUDIO64_THUNKS_SHINOBI defined.
//-----------------------------------------------------------------------------

#if !defined(AUDIO64_THUNKS_SHINOBI)
#define AUDIO64_THUNKS_SHINOBI
#endif

//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

#define MyAddChain			a64ChainAddHandler		// compatility mapping
#define MyRemoveChain		a64ChainDeleteHandler	// compatility mapping

KTU32 a64ChainAddHandler(KTS16 event, AC_ARM_INTERRUPT_HANDLER isr,
	KTU32 priority, void *arg);
void a64ChainDeleteHandler(KTU32 handle);

#ifdef __cplusplus
}
#endif

#endif	// _A64CHAIN_H_
