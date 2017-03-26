/* KallistiOS ##version##
       
   pvr_internal.h
   (C)2002 Dan Potter

 */

#ifndef __PVR_INTERNAL_H
#define __PVR_INTERNAL_H

/* Various implementation details are contained in here; this should only ever
   be included by modules in this directory.

   Everything from here down is considered internal to the implementation
   and may change without notice. So please don't rely on it in your
   code. If something is needed from this, an external interface should
   be added to dc/pvr.h. */

#include <kos/sem.h>

/**** State stuff ***************************************************/

/* The internal workings of the PVR2 are quite complex, and thank goodness
   we have the TA to help us with this setup process for each frame, or
   it'd be a LOT more work!

   Basically you have three different sets of buffers while registering
   scene data:

   1) Vertex buffer: this is a PVR RAM buffer that holds processed vertex
      data as it is fed to the TA
   2) Object pointer buffer: this is essentially an array of lists which
      holds data about which objects appear may appear in which tiles; for
      some odd reason, it grows down (probably so you don't have to pre-size
      vertex and OPB buffers, kinda like heap and stack)
   3) Tile matrix: this has a fixed-size entry for each tile on that will
      be rendered to; each active list must have a pointer into the OPB,
      or an "end of list" marker to mark it as have no OPB space

   As the TA collects data, the buffers may start to overflow if you have
   a lot of polygons, and that's what the grow space is about. It is
   initially using a fairly small amount of PVR RAM to hold the data
   structures, but as it overflows the bins for each tile, it must 
   allocate a new block.

   Now one small key point about all this: the buffers are interleaved to
   make the page numbers match up. Here is an illustration:

   +----------------------------------+----------------------------------+
   |         Buffer 0                 |            Buffer 1              |
   |                                  |                                  |
   |  Frame 0      |  Reg. Buffer 0   |  Frame 1        | Reg. Buffer 1  |
   |               |                  |                 |                |
   +----------------------------------+----------------------------------+

   The ISP/TSP and the TA are two independent pieces of the PVR which work
   in parallel to implement a simple rendering pipeline. While we are
   registering things with the TA, the ISP/TSP are rendering a frame. So
   there are three agents at work here: TA registration, ISP/TSP rendering,
   and an implicit third, the current _view_ frame (what the user is looking
   at). Here's the combinations this setup uses:

   Tick		TA		ISP/TSP			View
   0		->0		-			0
   1		->1		rb0->f0			1
   2		->0		rb1->f1			0
   3		->1		rb0->f0			1
   ...

   So initially the user is viewing frame 0, the ISP/TSP are doing nothing,
   and the TA is registering into reg buffer 0. When the registration is
   complete and a SCANINT is received, we switch the view to frame 1 (which
   is still blank), switch registration to reg buffer 1, and begin rendering
   from reg buffer 0 to frame buffer 0 (which is hidden). At the next SCANINT,
   we switch the view to frame 0 again (which now has contents), switch TA
   registration back to frame 0, and begin rendering from reg buffer 1 into
   frame 1.

   If this is complicated to you, then don't worry. I've been playing with
   it for over a year now and still barely understand it ^_^;;
 */

/* Note that these must match the list types in pvr.h; these are here
   mainly because they're easier to type =) */
#define PVR_OPB_OP	0	/* Array indeces for these structures */
#define PVR_OPB_OM	1
#define PVR_OPB_TP	2
#define PVR_OPB_TM	3
#define PVR_OPB_PT	4
#define PVR_OPB_COUNT	5

/* Buffers structure: keeps track of buffers for each frame */
typedef struct {
	uint32	vertex, vertex_size;		/* Vertex buffer */
	uint32	opb, opb_size;			/* Object pointer buffers, size */
	uint32	opb_type[PVR_OPB_COUNT];	/* Object pointer buffers (of each type) */
	uint32	tile_matrix, tile_matrix_size;	/* Tile matrix, size */
	uint32	frame, frame_size;		/* Output frame buffer, size */
} pvr_buffers_t;

/* PVR status structure; not only will this hold status information,
   but it will also server as the wait object for the frame-complete
   genwaits. */
typedef struct {
	/* If this is zero, then this state isn't valid */
	int		valid;

	/* General runtime config */
	uint32		list_reg_mask;			/* Active lists register mask */
	int		view_page;			/* Which frame is being viewed currently */
	int		opb_open_list;			/* Which list is open for registration, if any? */
	int		opb_open_list_cnt;		/* Prims submitted in this list */
	uint32		opb_closed;			/* (1 << idx) for each list which has been closed */
	uint32		opb_completed;			/* (1 << idx) for each list which has completed registration */
	uint32		opb_completed_full;		/* opb_completed's value when we're ready to render */
	int		render_completed;		/* 1 if the last started render has finished */
	int		flip_completed;			/* 1 if the flip we were waiting on has finished */
	
	/* Memory pointers */
	pvr_buffers_t	buffers[2];			/* Per-frame buffer pointers */
	uint32		texture_base;			/* Start of texture RAM */
	int		opb_size[PVR_OPB_COUNT];	/* opb size flags */
	uint32		opb_ind[PVR_OPB_COUNT];		/* Individual opb sizes (in bytes) */

	/* Screen size / clipping constants */
	int		w, h;				/* Screen width, height */
	int		tw, th;				/* Screen tile width, height */
	uint32		tsize_const;			/* Screen tile size constant */
	float		zclip;				/* Z clip plane */
	uint32		pclip_left, pclip_right;	/* X pixel clip constants */
	uint32		pclip_top, pclip_bottom;	/* Y pixel clip constants */
	uint32		pclip_x, pclip_y;		/* Composited clip constants */
	uint32		bg_color;			/* Background color in ARGB format */
	
	/* Running statistics on the PVR system. All vars are in terms
	   of milliseconds. */
	uint32		vbl_count;			/* VBlank counter for animations and such */
	uint64		frame_last_time;		/* When did the last frame completion occur? */
	uint64		reg_start_time;			/* When did the last registration begin? */
	uint64		rnd_start_time;			/* When did the last render begin? */
	uint32		frame_last_len;			/* VBlank-to-VBlank length for the last frame (1.0/FrameRate) */
	uint32		reg_last_len;			/* Registration time for the last frame */
	uint32		rnd_last_len;			/* Render time for the last frame */
	uint32		vtx_buf_used;			/* Vertex buffer used size for the last frame */
	uint32		vtx_buf_used_max;		/* Maximum used vertex buffer size */

	/* Wait-ready semaphore: this will be signaled whenever the pvr_wait_ready()
	   call should be ready to return. */
	semaphore_t	* ready_sem;

	/* Handle for the vblank interrupt */
	int		vbl_handle;
} pvr_state_t;

/* There will be exactly one of these in KOS (in pvr_globals.c) */
extern volatile pvr_state_t pvr_state;

/* Background plane structure */
typedef struct pvr_bkg_poly {
	uint32		flags1, flags2;
	uint32		dummy;
	float		x1, y1, z1;
	uint32		argb1;
	float		x2, y2, z2;
	uint32		argb2;
	float		x3, y3, z3;
	uint32		argb3;
} pvr_bkg_poly_t;

/**** pvr_buffers.c ***************************************************/

/* Initialize buffers for TA/ISP/TSP usage */
void pvr_allocate_buffers(pvr_init_params_t *params);

/* Fill in a single tile matrix (used by pvr_init_tile_matrices) */
void pvr_init_tile_matrix(int which);

/* Fill the tile matrices (after it's initialized) */
void pvr_init_tile_matrices();


/**** pvr_misc.c ******************************************************/

/* What event is happening (for pvr_sync_stats)? */
#define PVR_SYNC_VBLANK		1	/* VBlank IRQ */
#define PVR_SYNC_REGSTART	2	/* Registration started */
#define PVR_SYNC_REGDONE	3	/* Registration complete */
#define PVR_SYNC_RNDSTART	4	/* Render started */
#define PVR_SYNC_RNDDONE	5	/* Render complete IRQ */
#define PVR_SYNC_VBLRNDDONE	6	/* VBlank + Render complete */

/* Update statistical counters */
void pvr_sync_stats(int event);

/* Synchronize the viewed page with what's in pvr_state */
void pvr_sync_view_page();

/* Synchronize the registration buffer with what's in pvr_state */
void pvr_sync_reg_buffer();

/* Begin a render operation that has been queued completely */
void pvr_begin_queued_render();

/* Generate synthetic polygon headers for the given list type (to submit
   blank lists that the user forgot) */
void pvr_blank_polyhdr(int type);
   

/**** pvr_irq.c *******************************************************/

/* Interrupt handler for PVR events */
void pvr_int_handler(uint32 code);


#endif

