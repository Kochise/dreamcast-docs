/* KallistiOS ##version##

   os/abi/maple.h
   (c)2000-2001 Dan Potter

   $Id: maple.h,v 1.1 2003/02/27 03:46:31 bardtx Exp $

*/

#ifndef __OS_ABI_MAPLE_H
#define __OS_ABI_MAPLE_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <os/process.h>
#include <dc/maple.h>

/* Specific maple devices */
#include <dc/controller.h>
#include <dc/keyboard.h>
#include <dc/mouse.h>
#include <dc/vmu.h>

typedef struct {
	service_abi_t	hdr;		/* Header info */

	uint8		(*create_addr)(uint8 port, uint8 unit);
	int		(*docmd_block)(int8 cmd, uint8 addr,
				uint8 datalen, void *data,
				maple_frame_t *retframe);
	int		(*rescan_bus)(int quiet);
	uint32		(*device_func)(int port, int unit);
	uint8		(*first_device)(int code);
	uint8		(*first_controller)();
	uint8		(*first_mouse)();
	uint8		(*first_kb)();
	uint8		(*first_lcd)();
	uint8		(*first_vmu)();
	uint32		padding0[32 - 10];

	int		(*cont_get_cond)(uint8 addr, cont_cond_t *cond);
	uint32		padding1[8 - 1];

	int		(*kbd_get_cond)(uint8 addr, kbd_cond_t *cond);
	void		(*kbd_set_queue)(int active);
	int		(*kbd_enqueue)(uint8 keyboard);
	int		(*kbd_get_key)();
	int		(*kbd_poll)(uint8 addr);
	uint32		padding2[8 - 5];

	int		(*mouse_get_cond)(uint8 addr, mouse_cond_t *cond);
	uint32		padding3[8 - 1];

	int		(*vmu_draw_lcd)(uint8 addr, void *bitmap);
	int		(*vmu_block_read)(uint8 addr, uint16 blocknum, uint8 *buffer);
	int		(*vmu_block_write)(uint8 addr, uint16 blocknum, uint8 *buffer);
} abi_maple_t;

__END_DECLS

#endif	/* __OS_ABI_MAPLE_H */

