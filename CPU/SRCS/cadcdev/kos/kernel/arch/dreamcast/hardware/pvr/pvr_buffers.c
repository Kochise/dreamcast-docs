/* KallistiOS ##version##

   pvr_buffers.c
   Copyright (C)2002,2004 Dan Potter

 */

#include <assert.h>
#include <stdio.h>
#include <dc/pvr.h>
#include <dc/video.h>
#include "pvr_internal.h"

/*

  This module handles buffer allocation for the structures that the
  TA feed into, and which the ISP/TSP read from during the scene
  rendering.

*/

CVSID("$Id: pvr_buffers.c,v 1.6 2003/04/24 03:10:54 bardtx Exp $");


/* Fill Tile Matrix buffers. This function takes a base address and sets up
   the rendering structures there. Each tile of the screen (32x32) receives
   a small buffer space. */
void pvr_init_tile_matrix(int which) {
	volatile pvr_ta_buffers_t	*buf;
	int		x, y;
	uint32		*vr;
	volatile int	*opbs;
	uint32		matbase, opbbase;

	vr = (uint32*)PVR_RAM_BASE;
	buf = pvr_state.ta_buffers + which;
	opbs = pvr_state.opb_size;

	matbase = buf->tile_matrix;
	opbbase = buf->opb;
	
	/* Header of zeros */
	vr += buf->tile_matrix/4;
	for (x=0; x<0x48; x+=4)
		*vr++ = 0;
		
	/* Initial init tile */
	vr[0] = 0x10000000;
	vr[1] = 0x80000000;
	vr[2] = 0x80000000;
	vr[3] = 0x80000000;
	vr[4] = 0x80000000;
	vr[5] = 0x80000000;
	vr += 6;
	
	/* Now the main tile matrix */
#if 0
	dbglog(DBG_KDEBUG, "  Using poly buffers %08lx/%08lx/%08lx/%08lx/%08lx\r\n",
		buf->opb_type[0],
		buf->opb_type[1],
		buf->opb_type[2],
		buf->opb_type[3],
		buf->opb_type[4]);
#endif	/* !NDEBUG */
	for (x=0; x<pvr_state.tw; x++) {
		for (y=0; y<pvr_state.th; y++) {
			/* Control word */
			vr[0] = (y << 8) | (x << 2);

			/* Opaque poly buffer */
			vr[1] = buf->opb_type[0] + opbs[0]*pvr_state.tw*y + opbs[0]*x;
			
			/* Opaque volume mod buffer */
			vr[2] = buf->opb_type[1] + opbs[1]*pvr_state.tw*y + opbs[1]*x;
			
			/* Translucent poly buffer */
			vr[3] = buf->opb_type[2] + opbs[2]*pvr_state.tw*y + opbs[2]*x;
			
			/* Translucent volume mod buffer */
			vr[4] = buf->opb_type[3] + opbs[3]*pvr_state.tw*y + opbs[3]*x;
			
			/* Punch-thru poly buffer */
			vr[5] = buf->opb_type[4] + opbs[4]*pvr_state.tw*y + opbs[4]*x;
			vr += 6;
		}
	}
	vr[-6] |= 1<<31;

	/* Must skip over zeroed header for actual usage */
	buf->tile_matrix += 0x48;
}

/* Fill all tile matrices */
void pvr_init_tile_matrices() {
	int i;

	for (i=0; i<2; i++)
		pvr_init_tile_matrix(i);
}


/* Allocate PVR buffers given a set of parameters

There's some confusion in here that is explained more fully in pvr_internal.h.

The other confusing thing is that texture ram is a 64-bit multiplexed space
rather than a copy of the flat 32-bit VRAM. So in order to maximize the
available texture RAM, the PVR structures for the two frames are broken
up and placed at 0x000000 and 0x400000.

*/
#define BUF_ALIGN 128
#define BUF_ALIGN_MASK (BUF_ALIGN - 1)
void pvr_allocate_buffers(pvr_init_params_t *params) {
	volatile pvr_ta_buffers_t	*buf;
	volatile pvr_frame_buffers_t	*fbuf;
	int	i, j;
	uint32	outaddr, polybuf, sconst, polybuf_alloc;

	/* Set screen sizes; pvr_init has ensured that we have a valid mode
	   and all that by now, so we can freely dig into the vid_mode
	   structure here. */
	pvr_state.w = vid_mode->width;		pvr_state.h = vid_mode->height;
	pvr_state.tw = pvr_state.w / 32;	pvr_state.th = pvr_state.h / 32;

	/* FSAA -> double the tile buffer width */
	if (pvr_state.fsaa)
		pvr_state.tw *= 2;

	/* We can actually handle non-mod-32 heights pretty easily -- just extend
	   the frame buffer a bit, but use a pixel clip for the real mode. */
	if ((pvr_state.h % 32) != 0) {
		pvr_state.h = (pvr_state.h + 32) & ~31;
		pvr_state.th++;
	}
	
	pvr_state.tsize_const = ((pvr_state.th - 1) << 16)
		| ((pvr_state.tw - 1) << 0);

	/* Set clipping parameters */
	pvr_state.zclip = 0.0001f;
	pvr_state.pclip_left = 0;	pvr_state.pclip_right = vid_mode->width - 1;
	pvr_state.pclip_top = 0;	pvr_state.pclip_bottom = vid_mode->height - 1;
	pvr_state.pclip_x = (pvr_state.pclip_right << 16) | (pvr_state.pclip_left);
	pvr_state.pclip_y = (pvr_state.pclip_bottom << 16) | (pvr_state.pclip_top);
	
	/* Look at active lists and figure out how much to allocate
	   for each poly type */
	polybuf = 0;
	pvr_state.list_reg_mask = 1 << 20;
	for (i=0; i<PVR_OPB_COUNT; i++) {
		pvr_state.opb_size[i] = params->opb_sizes[i] * 4;	/* in bytes */
		pvr_state.opb_ind[i] = pvr_state.opb_size[i] * pvr_state.tw * pvr_state.th;
		polybuf += pvr_state.opb_ind[i];

		switch (params->opb_sizes[i]) {
		case PVR_BINSIZE_0:	sconst = 0; break;
		case PVR_BINSIZE_8:	sconst = 1; break;
		case PVR_BINSIZE_16:	sconst = 2; break;
		case PVR_BINSIZE_32:	sconst = 3; break;
		default:		assert_msg(0, "invalid poly_buf_size"); sconst = 2; break;
		}

		if (sconst > 0) {
			pvr_state.lists_enabled |= (1 << i);
			pvr_state.list_reg_mask |= sconst << (4 * i);
		}
	}
	
	/* Initialize each buffer set */
	for (i=0; i<2; i++) {
		/* Frame 0 goes at 0, Frame 1 goes at 0x400000 (half way) */
		if (i == 0)
			outaddr = 0;
		else
			outaddr = 0x400000;

		/* Select a pvr_buffers_t. Note that there's no good reason
		   to allocate the frame buffers at the same time as the TA
		   buffers except that it's handy to do it all in one place. */
		buf = pvr_state.ta_buffers + i;
		fbuf = pvr_state.frame_buffers + i;
	
		/* Vertex buffer */
		buf->vertex = outaddr;
		buf->vertex_size = params->vertex_buf_size;
		outaddr += buf->vertex_size;
	
		/* N-byte align */
		outaddr = (outaddr + BUF_ALIGN_MASK) & ~BUF_ALIGN_MASK;

		/* Object Pointer Buffers */
		/* XXX What the heck is this 0x50580 magic value?? All I 
		   remember about it is that removing it makes it fail. */
		buf->opb_size = 0x50580 + polybuf;
		outaddr += buf->opb_size;
		// buf->poly_buf_size = (outaddr - polybuf) - buf->vertex;
		polybuf_alloc = buf->opb = outaddr - polybuf;

		for (j=0; j<PVR_OPB_COUNT; j++) {
			if (pvr_state.opb_size[j] > 0) {
				buf->opb_type[j] = polybuf_alloc;
				polybuf_alloc += pvr_state.opb_ind[j];
			} else {
				buf->opb_type[j] = 0x80000000;
			}
		}
		outaddr += buf->opb_size;	/* Do we _really_ need this twice? */
	
		/* N-byte align */
		outaddr = (outaddr + BUF_ALIGN_MASK) & ~BUF_ALIGN_MASK;

		/* Tile Matrix */
		buf->tile_matrix = outaddr;
		buf->tile_matrix_size = (18 + 6 * pvr_state.tw * pvr_state.th) * 4;
		outaddr += buf->tile_matrix_size;
	
		/* N-byte align */
		outaddr = (outaddr + BUF_ALIGN_MASK) & ~BUF_ALIGN_MASK;
		
		/* Output buffer */
		fbuf->frame = outaddr;
		fbuf->frame_size = pvr_state.w * pvr_state.h * 2;
		outaddr += fbuf->frame_size;
		
		/* N-byte align */
		outaddr = (outaddr + BUF_ALIGN_MASK) & ~BUF_ALIGN_MASK;
	}

	/* Texture ram is whatever is left */
	pvr_state.texture_base = (outaddr - 0x400000) * 2;

#if 0
	dbglog(DBG_KDEBUG, "pvr: initialized PVR buffers:\n");
	dbglog(DBG_KDEBUG, "  texture RAM begins at %08lx\n", pvr_state.texture_base);
	for (i=0; i<2; i++) {		
		buf = pvr_state.ta_buffers+i;
		fbuf = pvr_state.frame_buffers+i;
		dbglog(DBG_KDEBUG, "  vertex/vertex_size: %08lx/%08lx\n", buf->vertex, buf->vertex_size);
		dbglog(DBG_KDEBUG, "  opb base/opb_size: %08lx/%08lx\n", buf->opb, buf->opb_size);
		dbglog(DBG_KDEBUG, "  opbs per type: %08lx %08lx %08lx %08lx %08lx\n",
			buf->opb_type[0],
			buf->opb_type[1],
			buf->opb_type[2],
			buf->opb_type[3],
			buf->opb_type[4]);
		dbglog(DBG_KDEBUG, "  tile_matrix/tile_matrix_size: %08lx/%08lx\n", buf->tile_matrix, buf->tile_matrix_size);
		dbglog(DBG_KDEBUG, "  frame/frame_size: %08lx/%08lx\n", fbuf->frame, fbuf->frame_size);
	}
	
	dbglog(DBG_KDEBUG, "  list_mask %08lx\n", pvr_state.list_reg_mask);
	dbglog(DBG_KDEBUG, "  opb sizes per type: %08lx/%08lx/%08lx/%08lx/%08lx\n",
		pvr_state.opb_ind[0],
		pvr_state.opb_ind[1],
		pvr_state.opb_ind[2],
		pvr_state.opb_ind[3],
		pvr_state.opb_ind[4]);
	dbglog(DBG_KDEBUG, "  w/h = %d/%d, tw/th = %d/%d\n", pvr_state.w, pvr_state.h,
		pvr_state.tw, pvr_state.th);
	dbglog(DBG_KDEBUG, "  zclip %08lx\n", *((uint32*)&pvr_state.zclip));
	dbglog(DBG_KDEBUG, "  pclip_left/right %08lx/%08lx\n", pvr_state.pclip_left, pvr_state.pclip_right);
	dbglog(DBG_KDEBUG, "  pclip_top/bottom %08lx/%08lx\n", pvr_state.pclip_top, pvr_state.pclip_bottom);
	dbglog(DBG_KDEBUG, "  lists_enabled %08lx\n", pvr_state.lists_enabled);
	dbglog(DBG_KDEBUG, "Free texture memory: %ld bytes\n",
		0x800000 - pvr_state.texture_base);
#endif	/* !NDEBUG */
}


