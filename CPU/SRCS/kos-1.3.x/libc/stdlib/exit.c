/* KallistiOS ##version##

   exit.c
   Copyright (C)2003 Dan Potter

   $Id: exit.c,v 1.2 2003/07/15 07:52:25 bardtx Exp $
*/

#include <stdlib.h>
#include <arch/arch.h>
#include <sys/process.h>

/* exit() */
void exit(int code) {
	_atexit_call_all();

	if (_local_process->pid == 1)
		arch_exit();
	else
		process_exit(code);
}
