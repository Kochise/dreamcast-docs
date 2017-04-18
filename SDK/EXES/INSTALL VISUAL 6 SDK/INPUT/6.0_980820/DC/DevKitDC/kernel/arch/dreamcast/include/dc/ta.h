/* KallistiOS 1.1.6

   ta.h
   (c)2000-2001 Dan Potter
   
   $Id: ta.h,v 1.3 2002/01/05 07:33:51 bardtx Exp $
*/

#ifndef __DC_TA_H
#define __DC_TA_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>

/* TA buffers structure: keeps track of buffers for each frame */
typedef struct {
	uint32		vertex, vertex_size;		/* Vertex buffer */
	uint32		poly_buf, poly_buf_size;	/* Poly buffers, size */
	uint32		poly_bufs[5];			/* Poly buffers (of each type) */
	uint32		tile_matrix, tile_matrix_size;	/* Tile matrix, size */
	uint32		frame, frame_size;		/* Output frame buffer, size */
} ta_buffers_t;

/* TA status structure: svcmpx friendly =) */
typedef struct {
	ta_buffers_t	buffers[2];			/* Frame TA buffer pointers */
	uint32		texture_base;			/* Start of texture RAM */
	uint32		lists;				/* Active lists bitmask */
	uint32		list_mask;			/* Active lists register mask */
	uint32		poly_buf_ind;			/* Individual poly type pb size */
	uint32		poly_buf_size;			/* Poly buffer size flag */
	int		w, h;				/* Screen width, height */
	int		tw, th;				/* Screen tile width, height */
	uint32		tsize_const;			/* Screen tile size constant */
	float		zclip;				/* Z clip plane */
	uint32		pclip_left, pclip_right;	/* X clip constants */
	uint32		pclip_top, pclip_bottom;	/* Y clip constants */
	uint32		pclip_x, pclip_y;		/* Composted clip constants */
	
	/* Initial config parameters are only read at hardware init */
	uint32		lists_to_alloc;			/* Lists to allocate */
	uint32		buffer_size;			/* Buffer size flag */
	uint32		vertex_buf_size;		/* Vertex buffer size */

	/* Running statistics on the PVR system */
        uint32          frame_counter;			/* Frame counter for animations and such */
} ta_state_t;

/* TA state structure */
extern ta_state_t ta_state;

/* TA lists that you can activate */
#define TA_LIST_OPAQUE_POLYS    1
#define TA_LIST_TRANS_POLYS     2
#define TA_LIST_OPAQUE_MODS     4
#define TA_LIST_TRANS_MODS      8
#define TA_LIST_PUNCH_THRU      16

/* Polygon buffer sizes */
#define TA_POLYBUF_0            0
#define TA_POLYBUF_8            8
#define TA_POLYBUF_16           16
#define TA_POLYBUF_32           32


/* Background plane data: this is a sort of truncated normal
   polygon data set. I'm assuming it's stored in internalized
   PVR format. It's a three-vertex polygon strip. */
typedef struct {
	uint32		flags1, flags2;
	uint32		dummy;
	float		x1, y1, z1;
	uint32		argb1;
	float		x2, y2, z2;
	uint32		argb2;
	float		x3, y3, z3;
	uint32		argb3;
} ta_bkg_poly;

/* Global background data structure; this is used during the
   rendering process. */
extern ta_bkg_poly *ta_bkg;


/* Polygon header; each polygon you send to the TA needs to have
   this as its first structure. For flags info, see maiwe's doc. */
typedef struct {
	uint32	flags1, flags2, flags3, flags4;
	uint32	dummy1, dummy2, dummy3, dummy4;
} poly_hdr_t;

/* Vertex structure; each polygon has three or more of these
   arranged in a structure called a strip. If bit 28 is set
   in the flags word, it signifies the end of a strip. Note that
   technically multiple strips don't have to be adjacent but
   they are still part of the same polygon. */

/* Opaque Colored vertex */
typedef struct {
	uint32	flags;
	float	x, y, z;
	float	a, r, g, b;
} vertex_oc_t;

/* Opaque Textured vertex */
typedef struct {
	uint32	flags;
	float	x, y, z, u, v;
	uint32	dummy1, dummy2;
	float	a, r, g, b;
	float	oa, or, og, ob;
} vertex_ot_t;

/* Current page */
extern int ta_curpage;

/* Set the active list mask and buffer sizes ; note that this can ONLY be
   done before hdwr_init has been called, or AFTER hdwr_shutdown has
   been called. */
void ta_set_buffer_config(uint32 listmask, uint32 buffersize, uint32 vertsize);

/* Prepare the TA for page flipped 3D */
void ta_init(int lists, int binsize, int vertbuf);

/* Do the same as ta_init, but with default values (opaque/translucent polys,
   32-object buffers, 512k of vertex space) */
void ta_init_defaults();

/* Turn off TA -- including turning off pesky interrupts */
void ta_shutdown();

/* Send a store queue full of data to the TA */
void ta_send_queue(void *sql, int size);

/* Begin the rendering process for one frame */
void ta_begin_render();

/* Setup the various TA variables for rendering the current frame into a
   texture buffer. Note that the tile array can't be rearranged on the fly,
   so the output frame will always be the same as the real display frame.
   However, the texture size will be scaled up to the next power-of-2,
   e.g., 640x480 will become 1024x512. */
void ta_begin_texture(uint32 txr, uint32 *rx, uint32 *ry);

/* Do TA hardware init/shutdown */
void ta_hw_init();
void ta_hw_shutdown();

/* Commit a polygon header to the TA */
void ta_commit_poly_hdr(void *polyhdr);

/* Commit a vertex to the TA; include sizeof() parameter */
void ta_commit_vertex(void *vertex, int size);

/* Commit an end-of-list to the TA */
void ta_commit_eol();

/* Finish rendering a frame; this assumes you have written
   a completed display list to the TA. It sets everything up and
   waits for the next vertical blank period to switch buffers. */
void ta_finish_frame();

/* Build a polygon header from the given parameters */
void ta_poly_hdr_col(poly_hdr_t *target, int translucent);
void ta_poly_hdr_txr(poly_hdr_t *target, int translucent,
	int textureformat, int tw, int th, uint32 textureaddr,
	int filtering);

/* Release all allocated texture space (start at zero) */
void ta_txr_release_all();

/* Allocate space for a texture of the given size; the returned value
   must still be run through ta_txr_map() to get the proper address. */
uint32 ta_txr_allocate(uint32 size);

/* Load texture data into the PVR ram */
void ta_txr_load(uint32 dest, void *src, int size);

/* Return a pointer to write to the texture ram directly */
void *ta_txr_map(uint32 loc);

/* Vertex constants */
#define TA_VERTEX_NORMAL	0xe0000000
#define TA_VERTEX_EOL		0xf0000000

/* Translucency constants */
#define TA_OPAQUE		0
#define TA_TRANSLUCENT		1

/* Texture format constants */
#define TA_NO_TEXTURE		0

#define TA_ARGB1555		((0<<1) | 1)	/* Flat versions */
#define TA_RGB565		((1<<1) | 1)
#define TA_ARGB4444		((2<<1) | 1)
#define TA_YUV422		((3<<1) | 1)
#define TA_BUMP			((4<<1) | 1)
#define TA_PAL4BPP		((5<<1) | 1)
#define TA_PAL8BPP		((6<<1) | 1)

#define TA_ARGB1555_TWID	(0<<1)		/* Twiddled versions */
#define TA_RGB565_TWID		(1<<1)
#define TA_ARGB4444_TWID	(2<<1)
#define TA_YUV422_TWID		(3<<1)
#define TA_BUMP_TWID		(4<<1)

/* Filtering constants */
#define TA_NO_FILTER		0
#define TA_BILINEAR_FILTER	1

/* Inline TA commit functions (thanks to Vincent Penne) */

/* Post SH-4 first queue */
#define ta_commit32_inline(src) \
  /* Post the first queue */ \
  asm volatile( \
  " mov     #0xe0,r0 \n" \
  " shll16  r0 \n" \
  " shll8   r0 \n" \
  " mov.l   @%0+,r1 \n" \
  " mov.l   r1,@(0,r0) \n" \
  " mov.l   @%0+,r1 \n" \
  " mov.l   r1,@(4,r0) \n" \
  " mov.l   @%0+,r1 \n" \
  " mov.l   r1,@(8,r0) \n" \
  " mov.l   @%0+,r1 \n" \
  " mov.l   r1,@(12,r0) \n" \
  " mov.l   @%0+,r1 \n" \
  " mov.l   r1,@(16,r0) \n" \
  " mov.l   @%0+,r1 \n" \
  " mov.l   r1,@(20,r0) \n" \
  " mov.l   @%0+,r1 \n" \
  " mov.l   r1,@(24,r0) \n" \
  " mov.l   @%0+,r1 \n" \
  " mov.l   r1,@(28,r0) \n" \
  " add     #-32,%0 \n" \
  " pref    @r0 \n" \
  : \
  : "r" ((int)(src))\
  : "r0", "r1")

/* Post SH-4 first queue */
#define ta_commit32_nocopy() \
  /* Post the first queue */ \
  asm volatile( \
  " mov #0xe0,r0 \n" \
  " shll16 r0 \n" \
  " shll8 r0 \n" \
  " pref @r0 \n" \
  : \
  : \
  : "r0")


__END_DECLS

#endif	/* __DC_TA_H */

