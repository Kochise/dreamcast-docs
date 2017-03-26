/* KallistiOS ##version##

   perror.c
   Copyright (C)2003 Dan Potter

   $Id: perror.c,v 1.1 2003/06/23 05:22:14 bardtx Exp $
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

CVSID("$Id: perror.c,v 1.1 2003/06/23 05:22:14 bardtx Exp $");

void perror(const char * msg) {
	/* XXX: Should probably write to stderr */
	printf("%s: %s\n", msg, strerror(errno));
}
