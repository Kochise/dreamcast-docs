/*

   slinkie/main.h
   Copyright (C)2004 Dan Potter
   
*/

#ifndef __SLINKIE_MAIN_H
#define __SLINKIE_MAIN_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

// Our execution mode
extern int sl_mode;

#define SLMODE_NONE 0	// not initialized yet
#define SLMODE_EXCL 1	// exclusive
#define SLMODE_IMME 2	// immediate
#define SLMODE_COOP 3	// cooperative

// When we exit from exclusive to cooperative mode, that can only mean
// one thing: running a program. This is the address of the program to
// jump to. When this returns, we'll go back to exclusive mode.
extern uint32 sl_exec_addr;

// Our version string
#define SL_VERSTRING "Slinkie " SLINKIE_VERSION

__END_DECLS

#endif	/* __SLINKIE_MAIN_H */

