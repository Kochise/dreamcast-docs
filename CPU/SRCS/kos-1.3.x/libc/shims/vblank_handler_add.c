/* KallistiOS ##version##

   vblank_handler_add.c
   Copyright (C)2003 Dan Potter
*/

#ifdef _arch_dreamcast

#include <dc/vblank.h>
#include <sys/process.h>

CVSID("$Id: vblank_handler_add.c,v 1.1 2003/07/31 00:46:42 bardtx Exp $");

int vblank_handler_add(asic_evt_handler hnd) {
	return _vblank_handler_add(_local_process, hnd);
}

#endif
