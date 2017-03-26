/* KallistiOS 1.2.0

   process.c
   (C)2000-2001 Dan Potter and Jordan DeLong
*/

#include <stdio.h>
#include <string.h>
#include <os/elf.h>
#include <kos/fs.h>
#include <kos/thread.h>
#include <arch/spinlock.h>
#include <arch/dbgio.h>
#include <arch/cache.h>
#include <sys/queue.h>

CVSID("$Id");

/* The multiplexer routine that retrieves services by name for
   running programs; the default one returns no services. */
void *psm_default(const char *svc) { return NULL; }
void* (*ps_multiplexer)(const char *svc) = psm_default;

/* List of running process images */
struct pslist ps_list;
spinlock_t ps_list_mutex;

/* The printk routine that will be called when the kernel wants to
   print a console message. */
void (*ps_printk_func)(const char *msg) = dbgio_write_str;

/* In cache.s */
void flush_icache_range(uint32 start, uint32 len);

/* Loads and relocates an ELF binary from a VFS file. */
elf_prog_t *ps_load(const char *fn) {
	uint32 fd;
	elf_prog_t *rv;

	/* Try to open the file */
	fd = fs_open(fn, O_RDONLY);
	if (fd == 0) {
		printf("Can't open binary file %s\r\n", fn);
		return NULL;
	}

	/* Do the ELF load */
	rv = elf_load(fd);
	if (rv == NULL) {
		printf("Couldn't load ELF file %s\r\n", fn);
		return NULL;
	}

	/* Clear the cache for the loaded area */
	icache_flush_range((uint32)rv->data, rv->size);
	
	return rv;
}

/* Loads an ELF binary from a VFS file and execution of the current
   thread pauses until the binary finishes. If it does not finish,
   execution never returns. */
int ps_load_and_exec(const char *fn, int argc, char **argv) {
	elf_prog_t *prog;

	/* Load the binary */
	/* printf("ps_load_and_exec: loading binary %s\r\n", fn); */
	if ((prog = ps_load(fn)) == NULL)
		return -1;
	strncpy(prog->fn, fn, 255); prog->fn[255] = 0;
	
	/* Add it to the list */
	spinlock_lock(&ps_list_mutex);
	LIST_INSERT_HEAD(&ps_list, prog, pslist);
	spinlock_unlock(&ps_list_mutex);
		
	/* Call the entry point */
	/* printf("Calling entry point %08x\r\n", prog->ko_main); */
	prog->argc = argc;
	prog->argv = argv;
	prog->ko_main(argc, argv);

	/* Remove it from the list and free it */
	spinlock_lock(&ps_list_mutex);
	LIST_REMOVE(prog, pslist);
	spinlock_unlock(&ps_list_mutex);
	elf_free(prog);
	return 0;
}

/* Thread start wrapper */
void ps_fork_start(void *data) {
	elf_prog_t *prog = (elf_prog_t *)data;

	prog->ko_main(prog->argc, prog->argv);

	/* Remove it from the list and free it */
	spinlock_lock(&ps_list_mutex);
	LIST_REMOVE(prog, pslist);
	spinlock_unlock(&ps_list_mutex);
	elf_free(prog);
}

/* Loads an ELF binary and execution of the program begins in a new
   kernel thread. */
kthread_t *ps_load_and_fork(const char *fn, int argc, char **argv) {
	elf_prog_t *prog;
	
	/* Load the binary */
	if ((prog = ps_load(fn)) == NULL)
		return NULL;
	strncpy(prog->fn, fn, 255); prog->fn[255] = 0;

	/* Add it to the list */
	spinlock_lock(&ps_list_mutex);
	LIST_INSERT_HEAD(&ps_list, prog, pslist);
	spinlock_unlock(&ps_list_mutex);
		
	/* Call the entry point in a new thread */
	prog->argc = argc;
	prog->argv = argv;
	return thd_create(ps_fork_start, prog);
}

/* Sets a multiplexer function target (i.e., what programs will
   receive for their ko_get_svc pointer) */
int ps_set_multiplexer(void* (*func)(const char *)) {
	ps_multiplexer = func;
	return 0;
}

/* Sets a kernel console function target (determines where kernel
   output will go from a printf() call). Defaults to serial output. Set
   to NULL to disable all kernel output. */
void * ps_set_printk(void (*print)(const char *str)) {
	void *old = ps_printk_func;
	ps_printk_func = print;
	return old;
}

/* Wrapper for printk: call this to send data to the console output
   device (whatever that might be) */
void ps_printk(const char *str) {
	if (ps_printk_func != NULL)
		ps_printk_func(str);
}

/* set up the service */
#include <os/svcmpx.h>
#include <os/abi/process.h>
static abi_process_t pabi;
static void process_svc_init() {
	memset(&pabi, 0, sizeof(pabi));

	pabi.hdr.version = ABI_MAKE_VER(1, 0, 0);

	pabi.load = ps_load;
	pabi.load_and_exec = ps_load_and_exec;
	pabi.load_and_fork = ps_load_and_fork;

	svcmpx_add_handler("process", &pabi);
}

/* init */
int ps_init() {
	process_svc_init();

	LIST_INIT(&ps_list);
	spinlock_init(&ps_list_mutex);

	return 0;
}

/* shutdown */
int ps_shutdown() {
	svcmpx_remove_handler("process");

	return 0;
}

