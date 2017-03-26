/* KallistiOS ##version##

   errno.c
   Copyright (C)2003 Dan Potter

   $Id: errno.c,v 1.2 2003/06/23 05:21:30 bardtx Exp $
*/

#include <errno.h>
#include <kos/thread.h>

CVSID("$Id: errno.c,v 1.2 2003/06/23 05:21:30 bardtx Exp $");

int * __error() {
	return thd_get_errno(thd_get_current());
}
