/* KallistiOS ##version##

   kos.h
   (c)2001 Dan Potter

   $Id: kos.h,v 1.25 2003/05/23 02:18:45 bardtx Exp $
*/

#ifndef __KOS_H
#define __KOS_H

/* The ultimate for the truly lazy: include and go! No more figuring out
   which headers to include for your project. */

#include <kos/cdefs.h>
__BEGIN_DECLS

#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <kos/fs.h>
#include <kos/fs_builtin.h>
#include <kos/fs_romdisk.h>
#include <kos/fs_ramdisk.h>
#include <kos/fs_pty.h>
#include <kos/limits.h>
#include <kos/thread.h>
#include <kos/sem.h>
#include <kos/mutex.h>
#include <kos/cond.h>
#include <kos/genwait.h>
#include <kos/library.h>
#include <kos/net.h>
#include <kos/nmmgr.h>
#include <kos/exports.h>
#include <kos/dbgio.h>

#include <arch/arch.h>
#include <arch/cache.h>
#include <arch/irq.h>
#include <arch/spinlock.h>
#include <arch/timer.h>
#include <arch/types.h>
#include <arch/exec.h>
#include <arch/stack.h>

#ifdef _arch_dreamcast
#	include <arch/mmu.h>

#	include <dc/biosfont.h>
#	include <dc/cdrom.h>
#	include <dc/fs_dcload.h>
#	include <dc/fs_iso9660.h>
#	include <dc/fs_vmu.h>
#	include <dc/asic.h>
#	include <dc/maple.h>
#	include <dc/maple/controller.h>
#	include <dc/maple/keyboard.h>
#	include <dc/maple/mouse.h>
#	include <dc/maple/vmu.h>
#	include <dc/maple/sip.h>
#	include <dc/maple/purupuru.h>
#	include <dc/vmu_pkg.h>
#	include <dc/spu.h>
#	include <dc/pvr.h>
#	include <dc/video.h>
#	include <dc/fmath.h>
#	include <dc/matrix.h>
#	include <dc/sound/stream.h>
#	include <dc/sound/sfxmgr.h>
#	include <dc/net/broadband_adapter.h>
#	include <dc/net/lan_adapter.h>
#	include <dc/modem/modem.h>
#	include <dc/sq.h>
#	include <dc/ubc.h>
#	include <dc/flashrom.h>
#	include <dc/vblank.h>
#	include <dc/vmufs.h>
#	include <dc/scif.h>
#elif _arch_gba	/* _arch_dreamcast */
#	include <gba/keys.h>
#	include <gba/sprite.h>
#	include <gba/video.h>
#	include <gba/dma.h>
#	include <gba/sound.h>
#elif _arch_ps2 /* _arch_gba */
#	include <ps2/ioports.h>
#	include	<ps2/fs_ps2load.h>
#	include <ps2/sbios.h>
#else	/* _arch_ps2 */
#	error Invalid architecture or no architecture specified
#endif

__END_DECLS

#endif

