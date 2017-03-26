/* This version is for programs. It starts a new thread and then calls your
   main() function. */

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <kos/process.h>
#include <sys/process.h>

/* Defined in atexit.c */
void _atexit_call_all();

/* Our global process ID */
kprocess_t * _local_process = NULL;

/* Defined elsewhere */
int main(int, char **);
void arch_ctors();
void arch_dtors();
void __crtend_pullin();

/* Program entry point */
int start(kprocess_t * proc) {
	int rv;

	_local_process = proc;
	process_set_signal(proc, _libc_signal_handler);

	arch_ctors();
	__crtend_pullin();

	rv = main(process_get_argc(proc), process_get_argv(proc));

	arch_dtors();

	_atexit_call_all();
	process_exit(rv);

	/* not reached */
}
