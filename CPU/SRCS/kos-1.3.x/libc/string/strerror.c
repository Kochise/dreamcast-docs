/* KallistiOS ##version##

   strerror.c
   Copyright (C)2003 Dan Potter

   $Id: strerror.c,v 1.1 2003/06/23 05:22:15 bardtx Exp $
*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

CVSID("$Id: strerror.c,v 1.1 2003/06/23 05:22:15 bardtx Exp $");

static const char unkerr[] = "Unknown error code";

char * strerror(int num) {
	if (num >= 0 && num < sys_nerr)
		return (char *)sys_errlist[num];

	errno = EINVAL;
	return (char *)unkerr;
}
