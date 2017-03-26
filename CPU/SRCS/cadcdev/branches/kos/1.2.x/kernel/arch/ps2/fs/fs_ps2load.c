/* KallistiOS ##version##

   kernel/arch/ps2/fs/fs_ps2load.c
   Copyright (c)2002 Andrew Kieschnick
   Copyright (c)2002 Dan Potter

*/

/*

This is a rewrite of Dan Potter's fs_serconsole to use the dcload / dc-tool
fileserver and console. 

printf goes to the dc-tool console
/pc corresponds to / on the system running dc-tool

Modified for ps2-load-ip by Dan Potter.

*/

#include <ps2/fs_ps2load.h>
#include <kos/thread.h>
#include <arch/spinlock.h>
#include <arch/dbgio.h>
#include <kos/fs.h>

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

CVSID("$Id: fs_ps2load.c,v 1.1 2002/11/06 08:36:40 bardtx Exp $");

static spinlock_t mutex = SPINLOCK_INITIALIZER;

static uint32 * ps2lip_block = NULL;
static int (*ps2lip_syscall)(int code, ...) = NULL;

static dbgio_printk_func old_printk = 0;

/* static void * lwip_dclsc = 0;

#define dclsc(...) ({ \
    int rv; \
    if (lwip_dclsc) \
	rv = (*(int (*)()) lwip_dclsc)(__VA_ARGS__); \
    else \
	rv = plain_dclsc(__VA_ARGS__); \
    rv; \
}) */

/* Printk replacement */

void ps2load_printk(const char *str) {
    /* if (lwip_dclsc && irq_inside_int())
	return; */
    spinlock_lock(&mutex);
    ps2lip_syscall(PS2LOAD_WRITE, 1, str, strlen(str));
    spinlock_unlock(&mutex);
}

static char *ps2load_path = NULL;
uint32 ps2load_open(vfs_handler_t * vfs, const char *fn, int mode) {
    int hnd = 0;
    uint32 h;
    int ps2load_mode = 0;
    
    /* if (lwip_dclsc && irq_inside_int())
	return 0; */

    spinlock_lock(&mutex);
    
    if (mode & O_DIR) {
        if (fn[0] == '\0') {
            fn = "/";
        }
	hnd = ps2lip_syscall(PS2LOAD_OPENDIR, fn);
	if (hnd) {
	    if (ps2load_path)
		free(ps2load_path);
	    if (fn[strlen(fn) - 1] == '/') {
		ps2load_path = malloc(strlen(fn)+1);
		strcpy(ps2load_path, fn);
	    } else {
		ps2load_path = malloc(strlen(fn)+2);
		strcpy(ps2load_path, fn);
		strcat(ps2load_path, "/");
	    }
	}
    } else { /* hack */
	if ((mode & O_MODE_MASK) == O_RDONLY)
	    ps2load_mode = 0;
	if ((mode & O_MODE_MASK) == O_RDWR)
	    ps2load_mode = 2 | 0x0200;
	if ((mode & O_MODE_MASK) == O_WRONLY)
	    ps2load_mode = 1 | 0x0200;
	if ((mode & O_MODE_MASK) == O_APPEND)
	    ps2load_mode =  2 | 8 | 0x0200;
	if (mode & O_TRUNC)
	    ps2load_mode |= 0x0400;
	hnd = ps2lip_syscall(PS2LOAD_OPEN, fn, ps2load_mode, 0644);
	hnd++; /* KOS uses 0 for error, not -1 */
    }
    
    h = hnd;

    spinlock_unlock(&mutex);
    return h;
}

void ps2load_close(uint32 hnd) {
    /* if (lwip_dclsc && irq_inside_int())
	return; */

    spinlock_lock(&mutex);
    
    if (hnd) {
	if (hnd > 100) /* hack */
	    ps2lip_syscall(PS2LOAD_CLOSEDIR, hnd);
	else {
	    hnd--; /* KOS uses 0 for error, not -1 */
	    ps2lip_syscall(PS2LOAD_CLOSE, hnd);
	}
    }
    spinlock_unlock(&mutex);
}

ssize_t ps2load_read(uint32 hnd, void *buf, size_t cnt) {
    ssize_t ret = -1;
    
    /* if (lwip_dclsc && irq_inside_int())
	return 0; */

    spinlock_lock(&mutex);
    
    if (hnd) {
	hnd--; /* KOS uses 0 for error, not -1 */
	ret = ps2lip_syscall(PS2LOAD_READ, hnd, buf, cnt);
    }
    
    spinlock_unlock(&mutex);
    return ret;
}

ssize_t ps2load_write(uint32 hnd, const void *buf, size_t cnt) {
    ssize_t ret = -1;
    	
    /* if (lwip_dclsc && irq_inside_int())
	return 0; */

    spinlock_lock(&mutex);
    
    if (hnd) {
	hnd--; /* KOS uses 0 for error, not -1 */
	ret = ps2lip_syscall(PS2LOAD_WRITE, hnd, buf, cnt);
    }

    spinlock_unlock(&mutex);
    return ret;
}

off_t ps2load_seek(uint32 hnd, off_t offset, int whence) {
    off_t ret = -1;

    /* if (lwip_dclsc && irq_inside_int())
	return 0; */

    spinlock_lock(&mutex);

    if (hnd) {
	hnd--; /* KOS uses 0 for error, not -1 */
	ret = ps2lip_syscall(PS2LOAD_LSEEK, hnd, offset, whence);
    }

    spinlock_unlock(&mutex);
    return ret;
}

off_t ps2load_tell(uint32 hnd) {
    off_t ret = -1;
    
    /* if (lwip_dclsc && irq_inside_int())
	return 0; */

    spinlock_lock(&mutex);

    if (hnd) {
	hnd--; /* KOS uses 0 for error, not -1 */
	ret = ps2lip_syscall(PS2LOAD_LSEEK, hnd, 0, SEEK_CUR);
    }

    spinlock_unlock(&mutex);
    return ret;
}

size_t ps2load_total(uint32 hnd) {
    size_t ret = -1;
    size_t cur;
	
    /* if (lwip_dclsc && irq_inside_int())
	return 0; */

    spinlock_lock(&mutex);
	
    if (hnd) {
	hnd--; /* KOS uses 0 for error, not -1 */
	cur = ps2lip_syscall(PS2LOAD_LSEEK, hnd, 0, SEEK_CUR);
	ret = ps2lip_syscall(PS2LOAD_LSEEK, hnd, 0, SEEK_END);
	ps2lip_syscall(PS2LOAD_LSEEK, hnd, cur, SEEK_SET);
    }
	
    spinlock_unlock(&mutex);
    return ret;
}

/* Not thread-safe, but that's ok because neither is the FS */
static dirent_t dirent;
dirent_t *ps2load_readdir(uint32 hnd) {
    dirent_t *rv = NULL;
    ps2load_dirent_t *dcld;
    ps2load_stat_t filestat;
    char *fn;

    /* if (lwip_dclsc && irq_inside_int())
	return 0; */

    if (hnd < 100) return NULL; /* hack */

    spinlock_lock(&mutex);

    dcld = (ps2load_dirent_t *)ps2lip_syscall(PS2LOAD_READDIR, hnd);
    
    if (dcld) {
	rv = &dirent;
	strcpy(rv->name, dcld->d_name);
	rv->size = 0;
	rv->time = 0;
	rv->attr = 0; /* what the hell is attr supposed to be anyways? */

	fn = malloc(strlen(ps2load_path)+strlen(dcld->d_name)+1);
	strcpy(fn, ps2load_path);
	strcat(fn, dcld->d_name);

	if (!ps2lip_syscall(PS2LOAD_STAT, fn, &filestat)) {
	    if (filestat.st_mode & S_IFDIR)
		rv->size = -1;
	    else
		rv->size = filestat.st_size;
	    rv->time = filestat.st_mtime;
	    
	}
	
	free(fn);
    }
    
    spinlock_unlock(&mutex);
    return rv;
}

int ps2load_rename(vfs_handler_t * vfs, const char *fn1, const char *fn2) {
    int ret;

    /* if (lwip_dclsc && irq_inside_int())
	return 0; */

    spinlock_lock(&mutex);

    /* really stupid hack, since I didn't put rename() in dcload */

    ret = ps2lip_syscall(PS2LOAD_LINK, fn1, fn2);

    if (!ret)
	ret = ps2lip_syscall(PS2LOAD_UNLINK, fn1);

    spinlock_unlock(&mutex);
    return ret;
}

int ps2load_unlink(vfs_handler_t * vfs, const char *fn) {
    int ret;

    /* if (lwip_dclsc && irq_inside_int())
	return 0; */

    spinlock_lock(&mutex);

    ret = ps2lip_syscall(PS2LOAD_UNLINK, fn);

    spinlock_unlock(&mutex);
    return ret;
}

/* Pull all that together */
static vfs_handler_t vh = {
    { "/pc" },          /* path prefix */
    0, 0,		/* In-kernel, no cacheing */
    NULL,               /* privdata */
    VFS_LIST_INIT,      /* linked list pointer */
    ps2load_open, 
    ps2load_close,
    ps2load_read,
    ps2load_write,
    ps2load_seek,
    ps2load_tell,
    ps2load_total,
    ps2load_readdir,
    NULL,               /* ioctl */
    ps2load_rename,
    ps2load_unlink,
    NULL                /* mmap */
};

/* Call this before arch_init_all (or any call to dbgio_*) to use ps2load's
   console output functions. */
void fs_ps2load_init_console() {
	/* Check for ps2load */
	if (!ps2lip_block) {
		ps2lip_block = (uint32 *)(*PS2LOADBLOCKPTR);
		if (ps2lip_block == NULL)
			return;
		if (ps2lip_block[0] != PS2LOADMAGICVALUE) {
			ps2lip_block = NULL;
			return;
		}
	}
	ps2lip_syscall = (int (*)(int, ...))ps2lip_block[2];

	// This still sucks
	// old_printk = dbgio_set_printk(ps2load_printk);
}

/* Call fs_ps2load_init_console() before calling fs_ps2load_init() */
int fs_ps2load_init() {
	/* Check for ps2load */
	if (!ps2lip_block)
		return -1;

    /* Check for combination of KOS networking and dcload-ip */
    /* if ((dcload_type == DCLOAD_TYPE_IP) && (__kos_init_flags & INIT_NET)) {
	dbglog(DBG_INFO, "dc-load console support disabled (network enabled)\n");
	if (old_printk) {
	    dbgio_set_printk(old_printk);
	    old_printk = 0;
	}
	return -1;
    } */

	/* Register with VFS */
	return fs_handler_add("/pc", &vh);
}

int fs_ps2load_shutdown() {
	/* Check for ps2load */
	if (!ps2lip_block)
		return -1;

	return fs_handler_remove(&vh);
}

#if 0
/* used for dcload-ip + lwIP
 * assumes fs_dcload_init() was previously called
 */
int fs_dcload_init_lwip(void *p)
{
    /* Check for combination of KOS networking and dcload-ip */
    if ((dcload_type == DCLOAD_TYPE_IP) && (__kos_init_flags & INIT_NET)) {
	lwip_dclsc = p;

	old_printk = dbgio_set_printk(dcload_printk);

	dbglog(DBG_INFO, "dc-load console support enabled (lwIP)\n");
    } else
	return -1;

    /* Register with VFS */
    return fs_handler_add("/pc", &vh);
}
#endif

