/* KallistiOS ##version##

   fs_romdisk_mount.c
   Copyright (C)2003 Dan Potter
*/

#include <kos/fs_romdisk.h>
#include <sys/process.h>

CVSID("$Id: fs_romdisk_mount.c,v 1.1 2003/07/31 00:46:42 bardtx Exp $");

int fs_romdisk_mount(const char * mountpoint, const uint8 *img) {
	return _fs_romdisk_mount(_local_process, mountpoint, img);
}
