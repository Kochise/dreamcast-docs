/* KallistiOS ##version##

   memcpy2.c
   (c)2001 Dan Potter

   $Id: memcpy2.c,v 1.1 2002/02/09 06:15:43 bardtx Exp $
*/

#include <string.h>

/* This variant was added by Dan Potter for its usefulness in 
   working with GBA external hardware. */
void * memcpy2(void *dest, const void *src, size_t count)
{
	unsigned short *tmp = (unsigned short *) dest;
	unsigned short *s = (unsigned short *) src;
	count = count/2;

	while (count--)
		*tmp++ = *s++;

	return dest;
}
