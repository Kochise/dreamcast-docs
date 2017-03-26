/* KallistiOS ##version##

   memset2.c
   (c)2001 Dan Potter

   $Id: memset2.c,v 1.1 2002/02/09 06:15:43 bardtx Exp $
*/

#include <string.h>

/* This variant was added by Dan Potter for its usefulness in 
   working with GBA external hardware. */
void * memset2(void *s, unsigned short c, size_t count)
{
	unsigned short *xs = (unsigned short *) s;
	count = count / 2;

	while (count--)
		*xs++ = c;

	return s;
}

