/* KallistiOS ##version##

   dc/vblank.h
   Copyright (C)2003 Dan Potter

   $Id: vblank.h,v 1.1 2003/04/24 03:07:20 bardtx Exp $
*/

#ifndef __DC_VBLANK_H
#define __DC_VBLANK_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <dc/asic.h>

/** Add a vblank handler. The function will be called at the start of every
    vertical blanking period with the same parameters that were passed to
    the original ASIC handler. Returns <0 on failure or a handle otherwise. */
int vblank_handler_add(asic_evt_handler hnd);

/** Remove a vblank handler. Pass the handle returned from
    vblank_handler_add. */
int vblank_handler_remove(int handle);

/** Initialize the vblank handler. This must be called after the asic module
    is initialized. */
int vblank_init();

/** Shut down the vblank handler. */
int vblank_shutdown();


__END_DECLS

#endif	/* __DC_VBLANK_H */

