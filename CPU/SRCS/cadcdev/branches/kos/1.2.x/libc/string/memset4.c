/* KallistiOS ##version##

   memset4.c
   (c)2000 Dan Potter

   $Id: memset4.c,v 1.1 2002/02/09 06:15:43 bardtx Exp $
*/

#include <string.h>

/* This variant was added by Dan Potter for its usefulness in 
   working with Dreamcast external hardware. */
void * memset4(void *s, unsigned long c, size_t count)
{
	unsigned long *xs = (unsigned long *) s;
	count = count / 4;

	while (count--)
		*xs++ = c;

	return s;
}

