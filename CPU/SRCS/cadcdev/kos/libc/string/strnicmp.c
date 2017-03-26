/* KallistiOS ##version##

   strnicmp.c
   (c)2000 Dan Potter

   $Id: strnicmp.c,v 1.2 2002/02/13 10:44:50 andrewk Exp $
*/

#include <string.h>

/* Works like strncmp, but not case sensitive */
int strnicmp(const char * cs, const char * ct, int count) {
	int c1, c2, res = 0;

	while(count) {
		c1 = *cs++; c2 = *ct++;
		if (c1 >= 'A' && c1 <= 'Z') c1 += 'a' - 'A';
		if (c2 >= 'A' && c2 <= 'Z') c2 += 'a' - 'A';
		if ((res = c1 - c2) != 0 || (!*cs && !*ct))
			break;
		count--;
	}

	return res;
}

/* Provides strncasecmp also (same thing) */
int strncasecmp(const char *cs, const char *ct, int count) {
	return strnicmp(cs, ct, count);
}

