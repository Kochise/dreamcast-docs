/* KallistiOS ##version##

   rmdir.c
   Copyright (C)2005 Walter van Niftrik
*/

#include <kos/fs.h>

int rmdir(const char *pathname)
{
	return fs_rmdir(pathname);
}
