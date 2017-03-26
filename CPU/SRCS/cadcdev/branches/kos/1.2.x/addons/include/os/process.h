/* KallistiOS ##version##

   os/process.h
   (c)2000-2001 Dan Potter

   $Id: process.h,v 1.1 2003/02/27 03:46:31 bardtx Exp $ 
  
*/

#ifndef __OS_PROCESS_H
#define __OS_PROCESS_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <os/elf.h>
#include <kos/thread.h>

/* Maximum size of a service name */
#define MAX_SVC_LEN	64

/* All service ABIs should include one of these as their first member;
   all "padding" array elements should _always_ be set to zero. */
typedef struct {
	uint32		version;	/* Lower three bytes are Major.Minor.Micro */
	uint32		padding[16-1];	/* Future expansion */
} service_abi_t;

/* Macros for accessing/creating version codes */
#define ABI_VER_MAJOR(v) ((v >> 16) & 0xff)
#define ABI_VER_MINOR(v) ((v >> 8) & 0xff)
#define ABI_VER_MICRO(v) ((v >> 0) & 0xff)
#define ABI_MAKE_VER(MAJOR, MINOR, MICRO) \
	( (((MAJOR) & 0xff) << 16) \
	| (((MINOR) & 0xff) << 8) \
	| (((MICRO) & 0xff) << 0) )


/* All these functions are located in process.c */
extern void* (*ps_multiplexer)(const char *svc);

/* Default multiplexer function */
void* psm_default(const char *svc);

/* Loads and relocates an ELF binary from a VFS file. */
elf_prog_t *ps_load(const char *fn);

/* Loads an ELF binary from a VFS file and execution of the current
   thread pauses until the binary finishes. If it does not finish,
   execution never returns. */
int ps_load_and_exec(const char *fn, int argc, char **argv);

/* Loads an ELF binary and execution of the program begins in a new
   kernel thread. */
kthread_t *ps_load_and_fork(const char *fn, int argc, char **argv);

/* Sets a multiplexer function target (i.e., what programs will
   receive for their ko_get_svc pointer) */
int ps_set_multiplexer(void* (*func)(const char *));

/* Sets a kernel console function target (determines where kernel
   output will go from a printf() call). Defaults to serial output. Set
   to NULL to disable all kernel output. */
void * ps_set_printk(void (*print)(const char *str));

/* Wrapper for printk: call this to send data to the console output
   device (whatever that might be) */
void ps_printk(const char *str);

/* initialization and shutdown */
int ps_init();
int ps_shutdown();

__END_DECLS

#endif	/* __KALLISTI_PROCESS_H */

