/* KallistiOS ##version##

   sys/process.h
   Copyright (C)2003 Dan Potter

   $Id: process.h,v 1.2 2003/07/15 07:52:24 bardtx Exp $
*/

#ifndef __SYS_PROCESS_H
#define __SYS_PROCESS_H

#include <kos/process.h>

/* This var is located in crt0, and should be filled with the process'
   proc struct pointer upon entry. */
extern kprocess_t * _local_process;


/* These functions implement something similar to 3.0BSD's vfork() and
   execv() calls. However, because of KOS process semantics these work a bit
   differently. See proc/vfork.c for more info. */

/* "vfork" to a new process shell */
kprocess_t * process_vfork();

/* Reverses the effects of process_vfork(). You can use this in case you
   didn't even get to execv(). */
int process_unvfork();

/* After completing vfork() and doing any other setup, call this to start
   a new process. Whether it succeeds or not, this call always undoes the
   effects of process_vfork() before returning. If failure is returned, no
   further action is required. If success is returned, process_wait must
   be used to clean the zombie that will be left behind. */
int process_execv(const char * image, int argc, const char **argv);


#endif	/* __SYS_PROCESS_H */


