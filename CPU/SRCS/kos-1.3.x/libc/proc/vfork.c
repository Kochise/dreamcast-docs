/* KallistiOS ##version##

   vfork.c
   Copyright (C)2003 Dan Potter
*/

#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <kos/process.h>
#include <sys/process.h>
#include <kos/elf.h>

CVSID("$Id: vfork.c,v 1.2 2003/07/15 07:52:25 bardtx Exp $");

/* This module implements something like the vfork() system call from
   3.0BSD. This is basically a cheap way to use fork/exec() without
   requiring an MMU, and without a bunch of process copying overhead.
   The advantage to doing this over using a spawn() type call is that
   you get to go in and muck with the child process before it starts.
   It goes something like this:

   - Parent calls process_vfork(). _local_process is temporarily replaced
     with the proces shell of the new child process.
   - "Child" can muck around with the environment now (like calling dup2 on
     the child's file descriptors, etc).
   - On failure, "child" calls process_unvfork(). This destroys the new
     process shell and switches _local_process back. No further action
     is required.
   - On success, "child" performs an process_execv(). _local_process is
     changed back. An ELF image is loaded into the new process shell and
     executed.

   Also significant is that our vfork and exec calls are a little different
   than the standard BSD ones. BSD vfork() returns a pid_t to the parent 
   eventually and zero to the child, while we always return a kprocess_t *
   to the "child". The vfork only ever returns to one place, which is
   the parent caller in the new child context. Also note that we only
   implement execv().

   If the function which called vfork() returns without calling exec() or
   exit(), calls process_exit, etc, then the results are undefined (likely
   a system crash, zombie process shells and memory pages at the least).

   It's a bit complex but it provides a very simple method for parents
   spawning child processes and still getting a chance to hack at their
   fds and such before the child starts to execute.

   Note: Some functions should be avoided between the vfork() and exec()
   calls. Most notably, calls to malloc(), free(), etc.

   So just to get that straight, here's a quick example...

   BSD way:

   int result;
   pid_t p = vfork();
   if (!p) {
      // Do munging here...
      if (execv("/foo.elf", args) < 0)
         _exit(-1);
   } else {
      if (p < 0)
         result = -1;
      else
         waitpid(p, &result, 0);
      if (result < 0) {
         // Failure mode
      }
   }

   KOS way:

   kprocess_t * p = process_vfork();
   if (!p) {
      // Failure mode
   }

   // Do munging here...

   if (process_execv("/foo.elf", argc, argv) < 0) {
      // Failure mode
   } else {
      result = process_wait(p);
   }
*/

/* This is our "temporary" storage for the parent's process struct. We'll
   replace this on the call to exec or exit. */
static kprocess_t * vfork_old_proc = NULL;

kprocess_t * process_vfork() {
	kprocess_t * np;

	/* Make sure we're not nesting vfork calls */
	assert( vfork_old_proc == NULL );

	/* Create a new process shell like we're spawning */
	np = process_create(_local_process, PROCESS_DEFAULTS);
	if (np == NULL)
		return NULL;

	/* Change us to be the "child process" for a moment */
	vfork_old_proc = _local_process;
	_local_process = np;

	return np;
}

int process_unvfork() {
	kprocess_t * np;

	/* Make sure we were called after vfork */
	assert( vfork_old_proc != NULL );
	
	/* Get the child process shell */
	np = _local_process;

	/* Switch back to the parent shell */
	_local_process = vfork_old_proc;
	vfork_old_proc = NULL;

	/* Destroy the aborted child shell */
	process_destroy(np);

	/* Clear it out of the zombie list */
	process_wait(np);

	return 0;
}

static int exec_common(const char * path, int argc, const char *argv[]) {
	kprocess_t * np;
	const char * largv[1] = { path };

	/* Make sure we were called after vfork */
	assert( vfork_old_proc != NULL );

	/* Get the child process shell */
	np = _local_process;

	/* Load up the ELF */
	if (elf_load(path, np, &np->image) < 0) {
		process_unvfork();
		return -1;
	}

	/* Setup its args */
	if (!argv) {
		argv = largv;
		argc = 1;
	}
	process_set_args(np, argc, argv);

	/* Create a new thread for the process */
	if (thd_create(np->image.start, (void *)np) == NULL) {
		process_unvfork();
		return -1;
	}

	/* Ok, coast is clear -- switch us back to the parent shell */
	_local_process = vfork_old_proc;
	vfork_old_proc = NULL;

	return 0;
}

int process_execv(const char * path, int argc, const char *argv[]) {
	return exec_common(path, argc, argv);
}
