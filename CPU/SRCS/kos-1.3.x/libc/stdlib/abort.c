/* KallistiOS ##version##

   abort.c
   Copyright (C)2003 Dan Potter

   $Id: abort.c,v 1.3 2003/07/15 07:52:25 bardtx Exp $
*/

#include <stdlib.h>
#include <arch/arch.h>
#include <sys/process.h>

CVSID("$Id: abort.c,v 1.3 2003/07/15 07:52:25 bardtx Exp $");

void abort() {
	if (_local_process->pid == 1)
		arch_abort();
	else
		process_exit(-1);
}

