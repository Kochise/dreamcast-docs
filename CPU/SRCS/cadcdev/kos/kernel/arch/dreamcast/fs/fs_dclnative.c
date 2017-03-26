/* KallistiOS ##version##

   kernel/arch/dreamcast/fs/fs_dclnative.c
   Copyright (C)2003 Dan Potter

   Portions of various supporting modules are
   Copyright (C)2001 Andrew Kieschnick, imported
   from the GPL'd dc-load-ip sources to a BSD-compatible
   license with permission.
   
*/


#include <arch/dbgio.h>
#include <dc/fs_dclnative.h>
#include <kos/thread.h>
#include <kos/sem.h>
#include <kos/mutex.h>
#include <kos/fs.h>
#include <kos/net.h>

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

#include "dcload-commands.h"
#include "dcload-net.h"
#include "dcload-packet.h"
#include "dcload-syscalls.h"

CVSID("$Id: fs_dclnative.c,v 1.1 2003/04/24 03:03:33 bardtx Exp $");

/*****************************************************************/
/* Administrative details */

/* dcload-ip variables used by all the modules */
uint32	dcln_our_ip;
uint8	dcln_our_mac[6];
uint8	dcln_pkt_buf[1600];
uint32	dcln_tool_ip;
uint8	dcln_tool_mac[6];
uint16	dcln_tool_port;
int	dcln_syscall_retval;
unsigned char *dcln_syscall_data;
int	dcln_escape_loop;

// #define DEBUG
// #define DEBUG_VERBOSE

/* This uses an addition to dc-load-ip 1.0.3 */
typedef struct {
	uint32	toolip;
	uint32	toolport;
	uint32	ourip;
	uint8	toolmac[6];
} hostinfo_t;
static void get_tool_ip() {
	hostinfo_t hi;

	/* Call down to dcload-ip to get the tool IP/port. */
	dcloadsyscall(DCLOAD_GETHOSTINFO, &hi);

	dcln_tool_ip = hi.toolip;
	dcln_tool_port = hi.toolport;
	dcln_our_ip = hi.ourip;
	memcpy(dcln_tool_mac, hi.toolmac, 6);

#ifdef DEBUG
	printf("tool = %08lx/%d, us = %08lx\n",
		dcln_tool_ip, dcln_tool_port, dcln_our_ip);
#endif
}

/* Our output device. This is kind of a turbo hack, but it works since
   the DC only has one possible network device at once. */
static netif_t * outdev = NULL;

/* Packet buffers. We hold these buffers separately to make sure that
   we don't have to use malloc in an interrupt. It's possible, but it
   may fail and we may drop packets that way. As long as we're high
   enough priority, 64 ought to be plenty for anything. */
#define PKT_BUF_CNT 64
static int pkt_tail, pkt_head;
static uint8 * pkt_bufs[PKT_BUF_CNT];
static int pkt_sizes[PKT_BUF_CNT];
static int pkt_cnt;
static semaphore_t * pkt_sem;

/* Network receive. This function will receive all ethernet packets
   destined for our MAC address and process them accordingly. What we'll
   really do here is just queue them up and wake our thread. */
static net_input_func ni_old;
static int dcln_input(netif_t * src, uint8 * pkt, int pktsize) {
	int idx = pkt_head;

#ifdef DEBUG
	printf("received a packet\n");
#endif

	/* No more room to store packets... silently drop it */
	if (pkt_cnt >= PKT_BUF_CNT)
		return 0;

#ifdef DEBUG
	printf("storing it as index %d\n", idx);
#endif

	memcpy(pkt_bufs[idx], pkt, pktsize);
	pkt_sizes[idx] = pktsize;

	pkt_head = (pkt_head + 1) % PKT_BUF_CNT;
	pkt_cnt++;

	sem_signal(pkt_sem);
	thd_schedule(1, 0);

	return 0;
}

/* Transmission function. This is a super turbo hack, but it works. If
   we don't have an output device yet, just scan for the single present
   device and cache it. */
void dcln_tx(uint8 * pkt, int len) {
#ifdef DEBUG
	int i;
	
	printf("transmitting a packet of len %d:\n", len);
#ifdef DEBUG_VERBOSE
	for (i=0; i<len; i++) {
		printf("%02x ", pkt[i]);
		if (i && !(i % 16))
			printf("\n");
	}
	printf("\n");
#endif
#endif
	
	outdev->if_tx(outdev, pkt, len, NETIF_BLOCK);
}

/* Our network-receive loop. This thing wakes when there's something
   to process in the packet queue, and presumably will exit back to
   some code at some point. */
void dcln_rx_loop() {
	int old, i;
	
	while (!dcln_escape_loop) {
		/* Wait for some data to arrive */
#ifdef DEBUG
		printf("waiting for a packet\n");
#endif
		sem_wait(pkt_sem);

#ifdef DEBUG
		printf("received a packet on slot %d w/size %d:\n", pkt_tail, pkt_sizes[pkt_tail]);
#ifdef DEBUG_VERBOSE
		for (i=0; i<pkt_sizes[pkt_tail]; i++) {
			printf("%02x ", pkt_bufs[pkt_tail][i]);
			if (i && !(i % 16))
				printf("\n");
		}
		printf("\n");
#endif
#endif

		/* Process the incoming packet */
		dcln_process_pkt(pkt_bufs[pkt_tail], pkt_sizes[pkt_tail]);

		/* Pull it off the queue */
		old = irq_disable();
		pkt_sizes[pkt_tail] = -1;
		pkt_tail = (pkt_tail + 1) % PKT_BUF_CNT;
		pkt_cnt--;
		irq_restore(old);
	}
	dcln_escape_loop = 0;
}


/*****************************************************************/
/* Actual printk and VFS functionality */

/* Mutex to make sure we don't try to perform more than one op at
   once. There's no technical reason against it, but the protocol
   doesn't assign tags to commands. */
static mutex_t * mutex;

/* Printk replacement */
static dbgio_printk_func old_printk = 0;
void dclnative_printk(const char *str) {
	if (irq_inside_int()) {
		dbgio_write_str(str);
		return;
	}
	mutex_lock(mutex);
	dcln_write(1, str, strlen(str));
	mutex_unlock(mutex);
}

static char *dcload_path = NULL;
uint32 dclnative_open(vfs_handler_t * vfs, const char *fn, int mode) {
    int hnd = 0;
    uint32 h;
    int dcload_mode = 0;

    mutex_lock(mutex);
    
    if (mode & O_DIR) {
        if (fn[0] == '\0') {
            fn = "/";
        }
        hnd = dcln_opendir(fn);
	if (hnd) {
	    if (dcload_path)
		free(dcload_path);
	    if (fn[strlen(fn) - 1] == '/') {
		dcload_path = malloc(strlen(fn)+1);
		strcpy(dcload_path, fn);
	    } else {
		dcload_path = malloc(strlen(fn)+2);
		strcpy(dcload_path, fn);
		strcat(dcload_path, "/");
	    }
	}
    } else { /* hack */
	if ((mode & O_MODE_MASK) == O_RDONLY)
	    dcload_mode = 0;
	if ((mode & O_MODE_MASK) == O_RDWR)
	    dcload_mode = 2 | 0x0200;
	if ((mode & O_MODE_MASK) == O_WRONLY)
	    dcload_mode = 1 | 0x0200;
	if ((mode & O_MODE_MASK) == O_APPEND)
	    dcload_mode =  2 | 8 | 0x0200;
	if (mode & O_TRUNC)
	    dcload_mode |= 0x0400;
	hnd = dcln_open(fn, dcload_mode, 0644);
	hnd++; /* KOS uses 0 for error, not -1 */
    }
    
    h = hnd;

    mutex_unlock(mutex);
    return h;
}

void dclnative_close(uint32 hnd) {
    mutex_lock(mutex);
    
    if (hnd) {
	if (hnd > 100) /* hack */
	    dcln_closedir(hnd);
	else {
	    hnd--; /* KOS uses 0 for error, not -1 */
	    dcln_close(hnd);
	}
    }
    mutex_unlock(mutex);
}

ssize_t dclnative_read(uint32 hnd, void *buf, size_t cnt) {
    ssize_t ret = -1;
    
    mutex_lock(mutex);
    
    if (hnd) {
	hnd--; /* KOS uses 0 for error, not -1 */
	ret = dcln_read(hnd, buf, cnt);
    }
    
    mutex_unlock(mutex);

    return ret;
}

ssize_t dclnative_write(uint32 hnd, const void *buf, size_t cnt) {
    ssize_t ret = -1;
    	
    mutex_lock(mutex);
    
    if (hnd) {
	hnd--; /* KOS uses 0 for error, not -1 */
	ret = dcln_write(hnd, buf, cnt);
    }

    mutex_unlock(mutex);
    return ret;
}

off_t dclnative_seek(uint32 hnd, off_t offset, int whence) {
    off_t ret = -1;

    mutex_lock(mutex);

    if (hnd) {
	hnd--; /* KOS uses 0 for error, not -1 */
	ret = dcln_lseek(hnd, offset, whence);
    }

    mutex_unlock(mutex);
    return ret;
}

off_t dclnative_tell(uint32 hnd) {
    off_t ret = -1;
    
    mutex_lock(mutex);

    if (hnd) {
	hnd--; /* KOS uses 0 for error, not -1 */
	ret = dcln_lseek(hnd, 0, SEEK_CUR);
    }

    mutex_unlock(mutex);
    return ret;
}

size_t dclnative_total(uint32 hnd) {
    size_t ret = -1;
    size_t cur;
	
    mutex_lock(mutex);
	
    if (hnd) {
	hnd--; /* KOS uses 0 for error, not -1 */
	cur = dcln_lseek(hnd, 0, SEEK_CUR);
	ret = dcln_lseek(hnd, 0, SEEK_END);
	dcln_lseek(hnd, cur, SEEK_SET);
    }
	
    mutex_unlock(mutex);
    return ret;
}

/* Not thread-safe, but that's ok because neither is the FS */
static dirent_t dirent;
dirent_t *dclnative_readdir(uint32 hnd) {
    dirent_t *rv = NULL;
    dcload_dirent_t *dcld;
    dcload_stat_t filestat;
    char *fn;

    if (hnd < 100) return NULL; /* hack */

    mutex_lock(mutex);

    dcld = (dcload_dirent_t *)dcln_readdir(hnd);
    
    if (dcld) {
	rv = &dirent;
	strcpy(rv->name, dcld->d_name);
	rv->size = 0;
	rv->time = 0;
	rv->attr = 0; /* what the hell is attr supposed to be anyways? */

	fn = malloc(strlen(dcload_path)+strlen(dcld->d_name)+1);
	strcpy(fn, dcload_path);
	strcat(fn, dcld->d_name);

	if (!dcln_stat(fn, &filestat)) {
	    if (filestat.st_mode & S_IFDIR)
		rv->size = -1;
	    else
		rv->size = filestat.st_size;
	    rv->time = filestat.st_mtime;
	    
	}
	
	free(fn);
    }
    
    mutex_unlock(mutex);
    return rv;
}

int dclnative_rename(vfs_handler_t * vfs, const char *fn1, const char *fn2) {
    int ret;

    mutex_lock(mutex);

    /* really stupid hack, since I didn't put rename() in dcload */

    ret = dcln_link(fn1, fn2);

    if (!ret)
	ret = dcln_unlink(fn1);

    mutex_unlock(mutex);
    return ret;
}

int dclnative_unlink(vfs_handler_t * vfs, const char *fn) {
    int ret;

    mutex_lock(mutex);

    ret = dcln_unlink(fn);

    mutex_unlock(mutex);
    return ret;
}

/* Pull all that together */
static vfs_handler_t vh = {
    { "/pc" },          /* path prefix */
    0, 0,		/* In-kernel, no cacheing */
    NULL,               /* privdata */
    VFS_LIST_INIT,      /* linked list pointer */
    dclnative_open, 
    dclnative_close,
    dclnative_read,
    dclnative_write,
    dclnative_seek,
    dclnative_tell,
    dclnative_total,
    dclnative_readdir,
    NULL,               /* ioctl */
    dclnative_rename,
    dclnative_unlink,
    NULL                /* mmap */
};


/*****************************************************************/
/* Init/shutdown */

int fs_dclnative_init() {
	int i;
	netif_t * n;

	/* Find our output device */
#ifdef DEBUG
	printf("finding device:\n");
#endif
	LIST_FOREACH(n, &net_if_list, if_list) {
		if (n->flags & NETIF_RUNNING) {
			outdev = n;
			break;
		}
	}
	if (!outdev) {
		/* Shouldn't happen... */
		dbgio_write_str("fs_dclnative_init: couldn't find an output device!\n");
		return -1;
	}
#ifdef DEBUG
	printf("found device at %p (%s)\n", outdev, outdev->descr);
#endif

	/* Setup our packet buffers */
	pkt_tail = pkt_head = 0;
	for (i=0; i<PKT_BUF_CNT; i++) {
		pkt_bufs[i] = malloc(1600);
		pkt_sizes[i] = -1;
	}
	pkt_cnt = 0;
	pkt_sem = sem_create(0);

	/* Setup other misc variables */
	dcln_tool_ip = 0;
	memset(dcln_tool_mac, 0, 6);
	dcln_tool_port = 0;
	memcpy(dcln_our_mac, outdev->mac_addr, 6);
	dcln_syscall_retval = 0;
	dcln_escape_loop = 0;

	mutex = mutex_create();

	/* Get the tool IP/port */
	get_tool_ip();

	/* Enable us on the networking. I have no idea why this stupid
	   line warns without the cast. */
#ifdef DEBUG
	printf("setting net target\n");
#endif
	ni_old = net_input_set_target((net_input_func)dcln_input);

	/* Hook printk */
//#ifndef DEBUG
//#else
	thd_sleep(1000);
	dclnative_printk("Test through dcl_native\n");
	dclnative_printk("switching printfs!\n");
	old_printk = dbgio_set_printk(dclnative_printk);
//#endif

	/* Register with VFS */
	return fs_handler_add("/pc", &vh);
}

int fs_dclnative_shutdown() {
	int i;

	dbgio_set_printk(old_printk);

	net_input_set_target(ni_old);
	
	for (i=0; i<PKT_BUF_CNT; i++)
		free(pkt_bufs[i]);

	mutex_destroy(mutex);
	sem_destroy(pkt_sem);

	outdev = NULL;

	return 0;
}

