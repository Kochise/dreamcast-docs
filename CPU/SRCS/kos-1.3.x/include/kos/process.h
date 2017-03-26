/* KallistiOS ##version##

   include/kos/process.h
   Copyright (C)2003 Dan Potter

   $Id: process.h,v 1.3 2003/08/01 03:20:37 bardtx Exp $

*/

#ifndef __KOS_PROCESS_H
#define __KOS_PROCESS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <kos/thread.h>
#include <kos/elf.h>
#include <kos/fs.h>

/* Pre-define list/queue types */
struct kprocess;
TAILQ_HEAD(kpqueue, kprocess);
LIST_HEAD(kplist, kprocess);


typedef int (*process_signal_handler_t)(struct kprocess * self, int sig, void * data);

#define PROCESS_MAX_ARGS		16	/* Maximum number of command line args */
#define PROCESS_MAX_ARG_SIZE		256	/* Maximum buffer space for args */

/* Structure describing one process shell. Each process contains zero or
   more threads, and may also group resources like file descriptors, memory
   chunks, etc. In the case that a process contains no threads (e.g. most
   filesystem drivers), it is considered a kernel module. */
typedef struct kprocess {
	/* Process list handle */
	LIST_ENTRY(kprocess)	list;

	/* Parent list handle */
	LIST_ENTRY(kprocess)	parent_list;

	/* Pointer to our parent */
	struct kprocess		* parent;

	/* List of children */
	struct kplist		child_list;

	/* Kernel process id */
	pid_t	pid;

	/* Flags */
	uint32	flags;

	/* Command line buffer; args will be stored in here. */
	char argv_buffer[PROCESS_MAX_ARG_SIZE];

	/* argc/argv for the process; these will point into argv_buffer.
	   This array is what will be passed into main(). */
	int argc;
	char *argv[PROCESS_MAX_ARGS];

	/* ELF program image for this process; if image->data is NULL, it is
	   statically linked into the kernel. */
	elf_prog_t image;

	/* Signal function; if we need to send a signal to a loaded process,
	   this function will be called. If it is NULL, there is no signal
	   function for this process. */
	process_signal_handler_t signal;

	/* Exit value; this value will be set and the process will not
	   actually be destroyed until process_wait is called.
	   PROCESS_ZOMBIE will be set when we enter that state. */
	int exitcode;

	/* Process' file descriptor table. This is inherited from the
	   parent process. */
	struct fs_hnd	* fds[FD_SETSIZE];
} kprocess_t;

/* Process flag values */
#define PROCESS_DEFAULTS	0	/* Defaults: no flags */
#define PROCESS_DAEMON		1	/* Process detached from parent */
#define PROCESS_ZOMBIE		2	/* See 'exitcode' above */

/* Process list; note: do not manipulate directly */
extern struct kplist process_list;

/* Kernel process; this is valid even during a vfork. */
extern kprocess_t * kernel_process;

/* Given a process ID, locates the proc structure */
kprocess_t *process_by_pid(pid_t pid);

/* Called from a "program" type process to signal unload */
void process_exit(int exitcode) __noreturn;

/* New process shell function. When you want to create a new process, this
   function will handle that for you. */
kprocess_t *process_create(kprocess_t * parent, int flags);

/* Given a process handle, this function removes the process from the process
   list. Any remaining resources assigned to this process will be freed. */
int process_destroy(kprocess_t *proc);

/* Return the current thread's kthread struct */
kprocess_t *process_get_current();

/* Modify a process' signal handler */
process_signal_handler_t process_get_signal(kprocess_t * proc);
void process_set_signal(kprocess_t * proc, process_signal_handler_t sig);

/* Retrieve / set process' argc/argv */
int process_get_argc(kprocess_t * proc);
char ** process_get_argv(kprocess_t * proc);
void process_set_args(kprocess_t * proc, int argc, const char *argv[]);

/* Detach the given process from its parent, and reparent it on the kernel */
int process_daemonize(kprocess_t * proc);

/* Call to set the given process as a module */
int process_modulize(kprocess_t * proc);

/* Retrive process' pid */
pid_t process_get_pid(kprocess_t *proc);

/* Wait for a process to be destroyed. If the process is already in
   PROCESS_ZOMBIE, this returns immediately. If nonblock is non-zero, and
   the process hasn't exited yet, then we'll return -1 and set errno.
   Otherwise, the value returned is the exit code from the process. */
int process_wait(kprocess_t * proc);

/* Send a process a signal */
int process_signal(kprocess_t * proc, int sig, void * data);

/* Init */
int process_init();

/* Shutdown */
void process_shutdown();

__END_DECLS

#endif	/* __KOS_PROCESS_H */

