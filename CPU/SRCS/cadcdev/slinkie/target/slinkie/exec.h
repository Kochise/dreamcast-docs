/*

   slinkie/exec.h
   Copyright (C)2004 Dan Potter
   
*/

#ifndef __SLINKIE_EXEC_H
#define __SLINKIE_EXEC_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

// Execute the program at addr, and put args and argv in the first two
// argument slots.
int exec(uint32 addr, int args, char ** argv);

// Can be called from the executed program to exit immediately.
void exec_exit();

__END_DECLS

#endif	/* __SLINKIE_EXEC_H */

