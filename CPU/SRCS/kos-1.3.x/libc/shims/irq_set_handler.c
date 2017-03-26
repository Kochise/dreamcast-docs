/* KallistiOS ##version##

   irq_set_handler.c
   Copyright (C)2003 Dan Potter
*/

#include <arch/irq.h>
#include <sys/process.h>

CVSID("$Id: irq_set_handler.c,v 1.1 2003/07/31 00:46:42 bardtx Exp $");

int irq_set_handler(irq_t source, irq_handler hnd) {
	return _irq_set_handler(_local_process, source, hnd);
}
