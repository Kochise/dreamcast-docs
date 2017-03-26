/* KallistiOS ##version##

   creat.c
   Copyright (C)2005 Walter van Niftrik
*/

#include <fcntl.h>

int creat(const char *pathname, mode_t mode)
{
	return open(pathname, O_CREAT|O_WRONLY|O_TRUNC, mode);
}
