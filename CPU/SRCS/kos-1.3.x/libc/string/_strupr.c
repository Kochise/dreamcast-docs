/* KallistiOS ##version##

   _strupr.c
   (c)2002 Brian Peek

   $Id: _strupr.c,v 1.1 2002/07/27 00:52:08 bardtx Exp $
*/

#include <string.h>
#include <ctype.h>

char *_strupr(char *string)
{
	char *s;

	for(s = string; *s; s++)
		*s = toupper(*s);
	return string;
}

