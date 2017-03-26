/* KallistiOS ##version##

   mkdir.c
   Copyright (C)2005 Walter van Niftrik
*/

#include <kos/fs.h>

int mkdir(const char *pathname, mode_t mode)
{
	return fs_mkdir(pathname);
}
