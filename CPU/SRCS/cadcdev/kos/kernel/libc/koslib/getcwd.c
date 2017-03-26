/* KallistiOS ##version##

   getcwd.c
   Copyright (C)2005 Walter van Niftrik
*/

#include <string.h>
#include <errno.h>

#include <kos/fs.h>

char *getcwd(char *buf, size_t size)
{
	const char *wd = fs_getwd();

	if (strlen(wd) + 1 > size) {
		errno = ERANGE;
		return NULL;
	}

	strcpy(buf, wd);
	return buf;
}
