/* KallistiOS ##version##

   arch/dreamcast/include/arch/exec.h
   (c)2002 Dan Potter
   
   $Id: exec.h,v 1.2 2002/06/13 01:13:28 bardtx Exp $
*/

#ifndef __ARCH_EXEC_H
#define __ARCH_EXEC_H

#include <sys/cdefs.h>
__BEGIN_DECLS

/* Replace the currently running image with whatever is at
   the pointer; note that this call will never return. */
void arch_exec_at(const void *image, uint32 length, uint32 address) __noreturn;
void arch_exec(const void *image, uint32 length) __noreturn;

__END_DECLS

#endif	/* __ARCH_EXEC_H */

