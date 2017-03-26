/* KallistiOS ##version##

   sys/module.h
   Copyright (C)2003 Dan Potter

   $Id: module.h,v 1.1 2003/07/15 07:57:35 bardtx Exp $

*/

#ifndef __SYS_MODULE_H
#define __SYS_MODULE_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* Helper function to make module/driver writing easier */
int kos_do_module(int (*modinit)(int, char **), int (*modshutdown)(), int argc, char **argv);

__END_DECLS

#endif	/* __SYS_TYPES_H */

