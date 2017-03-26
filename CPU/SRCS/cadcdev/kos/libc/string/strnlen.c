/* KallistiOS ##version##

   strnlen.c
   (c)2000 Dan Potter

   $Id: strnlen.c,v 1.1 2002/02/09 06:15:43 bardtx Exp $
*/


#include <string.h>

size_t strnlen(const char * s, size_t count) {
	const char *t = s;

	while (count-- && *t != '\0') t++;
	return t - s;
}
