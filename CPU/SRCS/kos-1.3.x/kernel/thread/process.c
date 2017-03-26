/* KallistiOS ##version##

   kernel/process.c
   Copyright (C)2003 Dan Potter
*/

#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <arch/irq.h>
#include <sys/process.h>
#include <kos/genwait.h>

#include <kos/mm.h>
#include <kos/sem.h>
#include <kos/cond.h>
#include <kos/fs_romdisk.h>

CVSID("$Id: process.c,v 1.4 2003/08/01 03:20:26 bardtx Exp $");

/*

With KOS 1.3.x, we re-introduce the idea of a process. It's a little bit
different from the standard *n*x concept of a process. Basically in KOS,
a process is a memory image plus a collection of resources associated with
that image, such as threads, sync objects, file descriptors, etc. A
process is also capable of receiving "signals", which are similar to
*n*x signals.

We have two kinds of processes: modules and programs. Modules are somewhat
like DOS TSRs in that they execute their startup code in the context of
the loading thread and they have no threads of their own per se (or
rather, they can start them, but they don't get a new one by default).
Programs will be started in a new thread; when their last thread
terminates, they will be terminated.

The difference is not in how we handle them (they are handled identically
here) but in their crt0. For a module, the program presumably sets some
things up (like calling nmmgr_handler_add) and then goes dormant by
returning without creating threads. Later on when we want it to go away, we
send it a SIGQUIT signal, which will trigger it calling
nmmgr_handler_remove or whatnot. We then verify that all of its resources
are destroyed, including the memory image. For a program, its crt0 starts
its main() in a new thread and then returns immediately. When its main
thread exits, it calls process_exit(), which does the same resource
verification and destruction as above and then calls thd_exit().

*/

/*****************************************************************************/

/* Process list */
static struct kplist process_list;

/*****************************************************************************/
/* Debug */
#include <arch/dbgio.h>

int process_print_list(int (*pf)(const char *fmt, ...)) {
	kprocess_t *cur;

	pf("All processes (may not be deterministic):\n");
	pf("pid\tppid\tflags\t\tbase\t\tname\n");
	
	LIST_FOREACH(cur, &process_list, list) {
		pf("%d\t", cur->pid);
		if (cur->parent)
			pf("%d\t", cur->parent->pid);
		else
			pf("n/a\t");
		pf("%08lx\t", cur->flags);
		if (cur->image.data)
			pf("%p\t", cur->image.data);
		else
			pf("n/a\t\t");
		pf("%s\n", cur->argv[0]);
	}
	pf("--end of list--\n");

	return 0;
}

/*****************************************************************************/
/* Returns a fresh process ID for each new thread */

/* Highest process id (used when assigning next process id) */
static pid_t pid_highest;


/* Return the next available process id (assumes wraparound will not run
   into old processes). */
static pid_t process_next_free() {
	int id;
	id = pid_highest++;
	return id;
}

/* Given a process ID, locates the process structure */
kprocess_t *process_by_pid(pid_t pid) {
	kprocess_t *np;

	LIST_FOREACH(np, &process_list, list) {
		if (np->pid == pid)
			return np;
	}

	return NULL;
}


/*****************************************************************************/

/* Terminate the current process. The calling thread must belong to the
   process to be terminated. */
void process_exit(int exitcode) {
	kprocess_t * proc;

	proc = process_get_current();
	assert( proc );

	proc->exitcode = exitcode;

	/* Make sure our resources are destroyed */
	process_destroy(proc);

	/* Block and terminate us */
	thd_exit();

	/* not reached */
}


/*****************************************************************************/
/* Process creation and deletion */

kprocess_t * process_create(kprocess_t * parent, int flags) {
	int		oldirq = 0;
	kprocess_t	* np;
	pid_t		pid;

	oldirq = irq_disable();
	np = NULL;

	/* Get a new process id */
	pid = process_next_free();

	if (pid >= 0) {
		/* Create a new process structure */
		np = malloc(sizeof(kprocess_t));
		if (np != NULL) {
			/* Clear out potentially unused stuff */
			memset(np, 0, sizeof(kprocess_t));

			/* Populate the context */
			np->pid = pid;
			np->parent = parent;
			np->flags = flags;
			strcpy(np->argv_buffer, "[un-named process]");
			np->argc = 1;
			np->argv[0] = np->argv_buffer;
			np->argv[1] = NULL;
			np->signal = NULL;
			np->exitcode = 0;
			LIST_INIT(&np->child_list);

			/* If a parent was passed in, inherit their fds and
			   add this proc to their child list. */
			if (parent) {
				fs_fdtbl_copy(parent, np);
				LIST_INSERT_HEAD(&parent->child_list, np, parent_list);
			}

			/* Insert it into the process list */
			LIST_INSERT_HEAD(&process_list, np, list);
		}
	}

	irq_restore(oldirq);
	return np;
}

int process_destroy(kprocess_t * proc) {
	int		oldirq = 0, cnt;
	kprocess_t	* cp, * np, * parent;
	pid_t		pid;

	oldirq = irq_disable();

	/* If any threads were waiting on this process, then go ahead
	   and unblock them. */
	genwait_wake_all(proc);

	/* Free up the process image */
	if (proc->image.data)
		elf_free(&proc->image);

	/* Free any process resources */
	pid = proc->pid;
	sem_freeall(proc);
	cond_freeall(proc);
	arch_remove_process(proc);
	fs_romdisk_unmount_proc(proc);
	fs_fdtbl_destroy(proc);
	cnt = mm_pfreeall(proc);
	if (cnt > 0) {
		dbglog(DBG_KDEBUG, "process_destroy: freed %d pages for %s(%d)\n", cnt, proc->argv[0], pid);
	}
                                                
	/* ZOMBIE the process and un-DAEMON it */
	proc->flags = (proc->flags & ~PROCESS_DAEMON) | PROCESS_ZOMBIE;

	/* If we have any child processes, reparent them to the kernel */
	cp = LIST_FIRST(&proc->child_list);
	while (cp) {
		np = LIST_NEXT(cp, parent_list);
		LIST_REMOVE(cp, parent_list);
		LIST_INSERT_HEAD(&_local_process->child_list, cp, parent_list);
		cp->parent = _local_process;
		cp = np;
	}

	/* Save the parent in case they are quicker than we are */
	parent = proc->parent;

	irq_restore(oldirq);

	/* Signal the parent that the child died */
	/* XXX What if the parent dies before we get to call it? */
	if (parent)
		process_signal(parent, SIGCHLD, proc);

	return 0;
}

/*****************************************************************************/
/* Process attribute functions */

process_signal_handler_t process_get_signal(kprocess_t * proc) {
	return proc->signal;
}

void process_set_signal(kprocess_t * proc, process_signal_handler_t sig) {
	proc->signal = sig;
}

int process_get_argc(kprocess_t * proc) {
	return proc->argc;
}

char ** process_get_argv(kprocess_t * proc) {
	return proc->argv;
}

void process_set_args(kprocess_t * proc, int argc, const char *argv[]) {
	int i, o, l;

	/* Can't have more than PROCESS_MAX_ARGS arguments */
	if (argc > PROCESS_MAX_ARGS)
		argc = PROCESS_MAX_ARGS;

	/* Copy each into the arrays */
	for (i=0,o=0; i<argc; i++) {
		/* Do we have enough space left? */
		l = strlen(argv[i]) + 1;
		if ((o + l) > PROCESS_MAX_ARG_SIZE)
			break;

		/* Yep... add another argv pointer. */
		proc->argv[i] = proc->argv_buffer + o;

		/* And copy it in */
		strcpy(proc->argv[i], argv[i]);

		/* Scoot up our output */
		o += l;
	}

	/* Take the final count from the array index in case we ran out */
	proc->argc = i;
}

/* The currently executing process. Note that although threads are owned by
   processes, this doesn't always determine the actual process that is
   running. For example, a client program could call through some hoops into
   an FS handler with its own process, but the "current process" is still
   the calling process. Use with care. */
kprocess_t *process_get_current() {
	return thd_get_current()->pshell;
}

/* This is read-only */
pid_t process_get_pid(kprocess_t * proc) {
	return proc->pid;
}

/*****************************************************************************/

int process_daemonize(kprocess_t * proc) {
	int		oldirq = 0;

	/* Can't reparent the kernel :) */
	if (proc == _local_process) {
		errno = EINVAL;
		return -1;
	}

	oldirq = irq_disable();

	/* Remove the process from its current parent */
	LIST_REMOVE(proc, parent_list);

	/* Add it to the kernel */
	LIST_INSERT_HEAD(&_local_process->child_list, proc, parent_list);
	proc->parent = _local_process;

	/* Set the daemon flag so the parent will go ahead */
	proc->flags |= PROCESS_DAEMON;

	/* Wake the parent if applicable */
	genwait_wake_all(proc);

	irq_restore(oldirq);

	return 0;
}

int process_modulize(kprocess_t * proc) {
	/* First reparent us to the kernel and detach from the parent */
	if (process_daemonize(proc) < 0)
		return -1;

	/* And now, my friend, your usefulness is at an end! */
	thd_exit();

	/* NOT REACHED */
}

/*****************************************************************************/

/* Send a signal to a process */
int process_signal(kprocess_t * proc, int sig, void * data) {
	if (!proc->signal)
		return -1;
	return proc->signal(proc, sig, data);
}

/* Wait for a process to exit and retrieve its exit code */
int process_wait(kprocess_t * proc) {
	int		oldirq = 0;
	int		rv;
	kprocess_t	* p = NULL;

	/* Can't scan for NULL processes */
	if (proc == NULL) {
		errno = EINVAL;
		return -1;
	}

	if (irq_inside_int()) {
		dbglog(DBG_WARNING, "process_wait(%p) called inside an interrupt!\n", proc);
		errno = EPERM;
		return -1;
	}
	oldirq = irq_disable();

again:	
	/* Search the process list and make sure that this process hasn't
	   already died and been deallocated. */
	LIST_FOREACH(p, &process_list, list) {
		if (p == proc)
			break;
	}

	/* Did we find anything? */
	if (p != proc) {
		errno = EINVAL;
		rv = -1;
		p = NULL;
	} else {
		/* Is it zombied or daemonized? */
		while (!(proc->flags & PROCESS_ZOMBIE) && !(proc->flags & PROCESS_DAEMON)) {
			/* Wait for the target process to die or modulize */
			genwait_wait(proc, "process_wait", 0, NULL);

			/* Just in case someone else zipped in and freed this process before we
			   got a chance, verify it again from the top. */
			goto again;
		}

		/* Get its exit code */
		rv = proc->exitcode;

		/* Finish destroying the process if necessary */
		if (!(proc->flags & PROCESS_DAEMON)) {
			LIST_REMOVE(proc, parent_list);
			LIST_REMOVE(proc, list);
			/* We defer free'ing until we're out of the IRQ disable */
		} else {
			proc->flags &= ~PROCESS_DAEMON;
			p = NULL;
		}
	}

	irq_restore(oldirq);

	/* Free the proc if necessary */
	if (p)
		free(p);

	/* Make sure we specify no error, in case the process returned -1 */
	errno = 0;

	return rv;
}

/*****************************************************************************/
/* Init/shutdown */

/* Bootstrap process with proper future pid */
static kprocess_t tmp_proc = {
	{ 0 },
	{ 0 },
	NULL,
	{ 0 },
	1,
	0,
	"",
	1,
	{ "[kernel]" }
};

/* Kernel process struct (for malloc et al) */
kprocess_t * _local_process = &tmp_proc;

/* This is valid even during a vfork */
kprocess_t * kernel_process = NULL;

/* This process will not be cleaned by ksighnd below. It's assumed that
   main() is waiting for it. */
/* XXX This is somewhat hackish */
kprocess_t * controlling_proc = NULL;

/* Default signal handler */
int process_ksighnd(kprocess_t * proc, int sig, void * data) {
	if (sig == SIGQUIT)
		arch_exit();
	else if (sig == SIGCHLD) {
		if ((kprocess_t *)data == controlling_proc)
			return 0;

		/* Catch and clean the zombie */
		process_wait((kprocess_t *)data);
		return 0;
	} else
		return 0;
}

/* Init */
int process_init() {
	/* Initialize handle counters */
	pid_highest = 1;

	/* Initialize the process list */
	LIST_INIT(&process_list);

	/* Setup a kernel process for the currently running "main" thread */
	_local_process = process_create(NULL, PROCESS_DEFAULTS);
	kernel_process = _local_process;
	strcpy(_local_process->argv_buffer, "[kernel]");
	_local_process->argc = 1;
	_local_process->argv[0] = _local_process->argv_buffer;

	process_set_signal(_local_process, process_ksighnd);

	return 0;
}

/* Shutdown */
void process_shutdown() {
	kprocess_t *n1, *n2;

	/* Kill remaining processes */
	n1 = LIST_FIRST(&process_list);
	while (n1 != NULL) {
		n2 = LIST_NEXT(n1, list);
		free(n1);
		n1 = n2;
	}

	_local_process = &tmp_proc;
}


