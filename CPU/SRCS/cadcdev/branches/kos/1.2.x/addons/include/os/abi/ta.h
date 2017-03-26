/* KallistiOS ##version##

   os/abi/ta.h
   (c)2000-2001 Dan Potter

   $Id: ta.h,v 1.1 2003/02/27 03:46:31 bardtx Exp $

*/

#ifndef __OS_ABI_TA_H
#define __OS_ABI_TA_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <os/process.h>

#if 0	/* Broken for now */

#include <dc/ta.h>

typedef struct {
	service_abi_t	hdr;		/* Header info */

	/* KOS 0.7 */
	void		(*hw_init)();
	void		(*hw_shutdown)();
	void		(*send_queue)(void *sql, int size);
	void		(*begin_render)();
	void		(*commit_poly_hdr)(void *polyhdr);
	void		(*commit_vertex)(void *vertex, int size);
	void		(*commit_eol)();
	void		(*finish_frame)();
	void		(*poly_hdr_col)(poly_hdr_t *target, int translucent);
	void		(*poly_hdr_txr)(poly_hdr_t *target, int translucent,
				int textureformat, int tw, int th, uint32 textureaddr,
				int filtering);

	/* KOS 0.8 */
	void		(*set_buffer_config)(uint32 listmask,
				uint32 buffersize, uint32 vertsize);
	void		(*txr_release_all)();
	uint32		(*txr_allocate)(uint32 size);
	void		(*txr_load)(uint32 dest, void *src, int size);
	void *		(*txr_map)(uint32 loc);

	/* KOS 1.0 */
	void		(*begin_texture)(uint32 txr, uint32 *rx, uint32 *ry);
	uint32		padding0[32 - 16];
	
	/* Warning: this is likely to change at any given time */
	ta_bkg_poly	*bkg;
} abi_ta_t;

#endif

__END_DECLS

#endif	/* __OS_ABI_TA_H */

