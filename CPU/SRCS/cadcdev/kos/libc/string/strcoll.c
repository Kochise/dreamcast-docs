/* KallistiOS ##version##

   strcoll.c
   Copyright (C)2003 Dan Potter

   $Id: strnicmp.c,v 1.2 2002/02/13 10:44:50 andrewk Exp $
*/

#include <string.h>

/* We don't have locales, so just call strcmp */
int strcoll(const char * c1, const char * c2) {
	return strcmp(c1, c2);
}
