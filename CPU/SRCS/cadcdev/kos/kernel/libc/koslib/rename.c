/* KallistiOS ##version##

   rename.c
   Copyright (C)2005 Walter van Niftrik
*/

#include <kos/fs.h>

int rename(const char *oldpath, const char *newpath)
{
	return fs_rename(oldpath, newpath);
}
