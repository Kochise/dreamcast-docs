/* KallistiOS ##version##

   asic_evt_set_handler.c
   Copyright (C)2003 Dan Potter
*/

#ifdef _arch_dreamcast

#include <dc/asic.h>
#include <sys/process.h>

CVSID("$Id: asic_evt_set_handler.c,v 1.1 2003/07/31 00:46:42 bardtx Exp $");

int asic_evt_set_handler(uint32 code, asic_evt_handler handler) {
	return _asic_evt_set_handler(_local_process, code, handler);
}

#endif
