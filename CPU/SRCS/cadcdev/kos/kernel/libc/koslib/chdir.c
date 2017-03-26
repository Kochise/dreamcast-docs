/* KallistiOS ##version##

   chdir.c
   Copyright (C)2005 Walter van Niftrik
*/

#include <kos/fs.h>

int chdir(const char *path)
{
	return fs_chdir(path);
}
