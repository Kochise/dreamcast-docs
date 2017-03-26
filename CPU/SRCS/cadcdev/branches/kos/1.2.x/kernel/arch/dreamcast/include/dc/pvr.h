/* KallistiOS ##version##

   kernel/arch/dreamcast/include/dc/pvr.h
   (C)2002 Dan Potter

   $Id: pvr.h,v 1.28 2003/04/24 03:13:45 bardtx Exp $

   Low-level PVR 3D interface for the DC
   Note: this API does _not_ handle any sort of transformations
    (including perspective!) so for that, you should look to KGL.
*/


#ifndef __DC_PVR_H
#define __DC_PVR_H

#include <sys/cdefs.h>
__BEGIN_DECLS

#include <arch/types.h>
#include <dc/sq.h>
#include <kos/img.h>

/* Data types ********************************************************/

/* PVR texture memory pointer; unlike the old "TA" system, PVR pointers
   in the new system are actually SH-4 compatible pointers and can
   be used directly in place of ta_txr_map(). */
typedef void * pvr_ptr_t;

/* PVR list specification */
typedef uint32 pvr_list_t;

/* Polygon context; you should use this more human readable format for
   specifying your polygon contexts, and then compile them into polygon
   headers (below) when you are ready to start using them.

   This has embedded structures in it for two reasons; the first reason
   is to make it easier for me to add new stuff later without breaking
   existing code. The second reason is to make it more readable and
   usable.
*/ 
typedef struct {
	int		list_type;
	struct {
		int		alpha;
		int		shading;
		int		fog_type;
		int		culling;
		int		color_clamp;
		int		clip_mode;
		int		modifier_mode;
	} gen;
	struct {
		int		src, dst;
		int		src_enable, dst_enable;
	} blend;
	struct {
		int		color;
		int		uv;
		int		modifier;
	} fmt;
	struct {
		int		comparison;
		int		write;
	} depth;
	struct {
		int		enable;
		int		filter;		/* none, bi-linear, tri-linear, etc */
		int		mipmap;
		int		mipmap_bias;
		int		uv_flip;
		int		uv_clamp;
		int		alpha;
		int		env;
		int		width;
		int		height;
		int		format;		/* bit format, vq, twiddle, stride */
		pvr_ptr_t	base;		/* texture location */
	} txr;
} pvr_poly_cxt_t;

/* Constants for the above structure; thanks to Benoit Miller for these */
/* list_type */
#define PVR_LIST_OP_POLY		0	/* opaque poly */
#define PVR_LIST_OP_MOD			1	/* opaque modifier */
#define PVR_LIST_TR_POLY		2	/* translucent poly */
#define PVR_LIST_TR_MOD			3	/* translucent modifier */
#define PVR_LIST_PT_POLY		4	/* punch-thru poly */

#define PVR_SHADE_FLAT			0	/* shading */
#define PVR_SHADE_GOURAUD		1

#define PVR_DEPTHCMP_NEVER		0	/* depth_comparison */
#define PVR_DEPTHCMP_LESS		1
#define PVR_DEPTHCMP_EQUAL		2
#define PVR_DEPTHCMP_LEQUAL		3
#define PVR_DEPTHCMP_GREATER		4
#define PVR_DEPTHCMP_NOTEQUAL		5
#define PVR_DEPTHCMP_GEQUAL		6
#define PVR_DEPTHCMP_ALWAYS		7

#define PVR_CULLING_NONE		0	/* culling */
#define PVR_CULLING_SMALL		1
#define PVR_CULLING_CCW			2
#define PVR_CULLING_CW			3

#define PVR_DEPTHWRITE_ENABLE		0	/* depth_write */
#define PVR_DEPTHWRITE_DISABLE		1

#define PVR_TEXTURE_DISABLE		0	/* txr_enable */
#define PVR_TEXTURE_ENABLE		1

#define PVR_BLEND_ZERO			0	/* src_blend / dst_blend */
#define PVR_BLEND_ONE			1
#define PVR_BLEND_DESTCOLOR		2
#define PVR_BLEND_INVDESTCOLOR		3
#define PVR_BLEND_SRCALPHA		4
#define PVR_BLEND_INVSRCALPHA		5
#define PVR_BLEND_DESTALPHA		6
#define PVR_BLEND_INVDESTALPHA		7

#define PVR_BLEND_DISABLE		0	/* src_blend_enable / dst_blend_enable */
#define PVR_BLEND_ENABLE		1

#define PVR_FOG_TABLE			0	/* fog_type */
#define PVR_FOG_VERTEX			1
#define PVR_FOG_DISABLE			2
#define PVR_FOG_TABLE2			3

#define PVR_USERCLIP_DISABLE		0	/* clip_mode */
#define PVR_USERCLIP_INSIDE		2
#define PVR_USERCLIP_OUTSIDE		3

#define PVR_CLRCLAMP_DISABLE		0	/* color_clamp */
#define PVR_CLRCLAMP_ENABLE		1

#define PVR_ALPHA_DISABLE		0	/* alpha */
#define PVR_ALPHA_ENABLE		1

#define PVR_TXRALPHA_ENABLE		0	/* txr_alpha */
#define PVR_TXRALPHA_DISABLE		1

#define PVR_UVFLIP_NONE			0	/* txr_uvflip */
#define PVR_UVFLIP_V			1
#define PVR_UVFLIP_U			2
#define PVR_UVFLIP_UV			3

#define PVR_UVCLAMP_NONE		0	/* txr_uvclamp */
#define PVR_UVCLAMP_V			1
#define PVR_UVCLAMP_U			2
#define PVR_UVCLAMP_UV			3

#define PVR_FILTER_NONE			0	/* txr_filter */
#define PVR_FILTER_NEAREST		0
#define PVR_FILTER_BILINEAR		2
#define PVR_FILTER_TRILINEAR1		4
#define PVR_FILTER_TRILINEAR2		6

#define PVR_MIPBIAS_NORMAL		PVR_MIPBIAS_1_00	/* txr_mipmap_bias */
#define PVR_MIPBIAS_0_25		1
#define PVR_MIPBIAS_0_50		2
#define PVR_MIPBIAS_0_75		3
#define PVR_MIPBIAS_1_00		4
#define PVR_MIPBIAS_1_25		5
#define PVR_MIPBIAS_1_50		6
#define PVR_MIPBIAS_1_75		7
#define PVR_MIPBIAS_2_00		8
#define PVR_MIPBIAS_2_25		9
#define PVR_MIPBIAS_2_50		10
#define PVR_MIPBIAS_2_75		11
#define PVR_MIPBIAS_3_00		12
#define PVR_MIPBIAS_3_25		13
#define PVR_MIPBIAS_3_50		14
#define PVR_MIPBIAS_3_75		15

/* txr_env */
#define PVR_TXRENV_REPLACE		0	/* C = Ct, A = At */
#define PVR_TXRENV_MODULATE		1	/* C = Cs * Ct, A = At */
#define PVR_TXRENV_DECAL		2	/* C = (Cs * At) + (Cs * (1-At)), A = As */
#define PVR_TXRENV_MODULATEALPHA	3	/* C = Cs * Ct, A = As * At */

#define PVR_MIPMAP_DISABLE		0	/* txr_mipmap */
#define PVR_MIPMAP_ENABLE		1

#define PVR_TXRFMT_NONE			0		/* txr_format */
#define PVR_TXRFMT_VQ_DISABLE		(0 << 30)
#define PVR_TXRFMT_VQ_ENABLE		(1 << 30)
#define PVR_TXRFMT_ARGB1555		(0 << 27)
#define PVR_TXRFMT_RGB565		(1 << 27)
#define PVR_TXRFMT_ARGB4444		(2 << 27)
#define PVR_TXRFMT_YUV422		(3 << 27)
#define PVR_TXRFMT_BUMP			(4 << 27)
#define PVR_TXRFMT_PAL4BPP		(5 << 27)
#define PVR_TXRFMT_PAL8BPP		(6 << 27)
#define PVR_TXRFMT_TWIDDLED		(0 << 26)
#define PVR_TXRFMT_NONTWIDDLED		(1 << 26)
#define PVR_TXRFMT_NOSTRIDE		(0 << 21)
#define PVR_TXRFMT_STRIDE		(1 << 21)

/* OR one of these into your texture format if you need it. Note that
   these coincide with the twiddled/stride bits, so you can't have a 
   non-twiddled/strided texture that's paletted! */
#define PVR_TXRFMT_8BPP_PAL(x)		((x) << 25)
#define PVR_TXRFMT_4BPP_PAL(x)		((x) << 21)

#define PVR_CLRFMT_ARGBPACKED		0	/* color_format */
#define PVR_CLRFMT_4FLOATS		1
#define PVR_CLRFMT_INTENSITY		2
#define PVR_CLRFMT_INTENSITY_PREV	3

#define PVR_UVFMT_32BIT			0	/* txr_uv_format */
#define PVR_UVFMT_16BIT			1

#define PVR_MODIFIER_DISABLE		0	/* modifier_format */
#define PVR_MODIFIER_ENABLE		1

#define PVR_MODIFIER_CHEAP_SHADOW	0	
#define PVR_MODIFIER_NORMAL		1

#define PVR_MODIFIER_OTHER_POLY		0	/* PM1 modifer instruction */
#define PVR_MODIFIER_FIRST_POLY		1	/* ...in inclusion vol */
#define PVR_MODIFIER_LAST_POLY		2	/* ...in exclusion vol */


/* "Polygon header" -- this is the hardware equivalent of a rendering
   context; you'll create one of these from your pvr_poly_context_t and
   use it for submission to the hardware. */
typedef struct {
	uint32		cmd;			/* TA command */
	uint32		mode1, mode2, mode3;	/* mode parameters */
	uint32		d1, d2, d3, d4;		/* dummies */
} pvr_poly_hdr_t;

/* Generic vertex type; the PVR chip itself supports many more vertex
   types, but this is the main one that can be used with both textured
   and non-textured polygons, and is fairly fast. You can find other
   variants below. */
typedef struct {
	uint32		flags;			/* vertex flags */
	float		x, y, z;		/* the coodinates */
	float		u, v;			/* texture coords */
	uint32		argb;			/* vertex color */
	uint32		oargb;			/* offset color */
} pvr_vertex_t;

/* Textured, packed color, affected by modifer volume. Note that this
   vertex type has two copies of colors, offset colors and texture 
   coords. The second set of texture coords, colors, and offset colors
   are used when enclosed within a modifer volume */
typedef struct {
	uint32 flags;				/* vertex flags */
	float x, y, z;				/* the coordinates */
	float u0, v0;				/* texture coords 0 */
	uint32 argb0;				/* vertex color 0 */
	uint32 oargb0;				/* offset color 0 */
	float u1, v1;				/* texture coords 1 */
	uint32 argb1;				/* vertex color 1 */
	uint32 oargb1;				/* offset color 1 */
	uint32 d1, d2, d3, d4;			/* dummies */
} pvr_vertex_tpcm_t;

/* This vertex is only for modifer volumes */
typedef struct {
	uint32 flags;				/* vertex flags */
	float ax, ay, az;			/* 3 sets of coordinates */
	float bx, by, bz;
	float cx, cy, cz;
	uint32 d1, d2, d3, d4, d5, d6;		/* dummies */
} pvr_modifier_vol_t;

/* Small macro for packing float color values */
#define PVR_PACK_COLOR(a, r, g, b) ( \
	( ((uint8)( a * 255 ) ) << 24 ) | \
	( ((uint8)( r * 255 ) ) << 16 ) | \
	( ((uint8)( g * 255 ) ) << 8 ) | \
	( ((uint8)( b * 255 ) ) << 0 ) )

/* ... other vertex structs omitted for now ... */

/* Constants that apply to all primitives */
#define PVR_CMD_POLYHDR		0x80840000	/* sublist, striplength=2 */
#define PVR_CMD_VERTEX		0xe0000000
#define PVR_CMD_VERTEX_EOL	0xf0000000
#define PVR_CMD_USERCLIP	0x20000000
#define PVR_CMD_MODIFIER	0x80040000

/* Constants and bitmasks for handling polygon headers; note that thanks
   to the arrangement of constants above, this is mainly a matter of bit
   shifting to compile it... */
#define PVR_TA_CMD_TYPE_SHIFT		24
#define PVR_TA_CMD_TYPE_MASK		(7 << PVR_TA_CMD_TYPE_SHIFT)

#define PVR_TA_CMD_USERCLIP_SHIFT	16
#define PVR_TA_CMD_USERCLIP_MASK	(3 << PVR_TA_CMD_USERCLIP_SHIFT) 
	
#define PVR_TA_CMD_CLRFMT_SHIFT		4
#define PVR_TA_CMD_CLRFMT_MASK		(7 << PVR_TA_CMD_CLRFMT_SHIFT)

#define PVR_TA_CMD_SHADE_SHIFT		1
#define PVR_TA_CMD_SHADE_MASK		(1 << PVR_TA_CMD_SHADE_SHIFT)

#define PVR_TA_CMD_UVFMT_SHIFT		0
#define PVR_TA_CMD_UVFMT_MASK		(1 << PVR_TA_CMD_UVFMT_SHIFT)
	
#define PVR_TA_CMD_MODIFIER_SHIFT	7
#define PVR_TA_CMD_MODIFIER_MASK	(1 <<  PVR_TA_CMD_MODIFIER_SHIFT)
	
#define PVR_TA_CMD_MODIFIERMODE_SHIFT	6
#define PVR_TA_CMD_MODIFIERMODE_MASK	(1 <<  PVR_TA_CMD_MODIFIERMODE_SHIFT)

#define PVR_TA_PM1_DEPTHCMP_SHIFT	29
#define PVR_TA_PM1_DEPTHCMP_MASK	(7 << PVR_TA_PM1_DEPTHCMP_SHIFT)

#define PVR_TA_PM1_CULLING_SHIFT	27
#define PVR_TA_PM1_CULLING_MASK		(3 << PVR_TA_PM1_CULLING_SHIFT)

#define PVR_TA_PM1_DEPTHWRITE_SHIFT	26
#define PVR_TA_PM1_DEPTHWRITE_MASK	(1 << PVR_TA_PM1_DEPTHWRITE_SHIFT)

#define PVR_TA_PM1_TXRENABLE_SHIFT	25
#define PVR_TA_PM1_TXRENABLE_MASK	(1 << PVR_TA_PM1_TXRENABLE_SHIFT)

#define PVR_TA_PM1_MODIFIERINST_SHIFT	29 
#define PVR_TA_PM1_MODIFIERINST_MASK	(2 <<  PVR_TA_PM1_MODIFIERINST_SHIFT)

#define PVR_TA_PM2_SRCBLEND_SHIFT	29
#define PVR_TA_PM2_SRCBLEND_MASK	(7 << PVR_TA_PM2_SRCBLEND_SHIFT)

#define PVR_TA_PM2_DSTBLEND_SHIFT	26
#define PVR_TA_PM2_DSTBLEND_MASK	(7 << PVR_TA_PM2_DSTBLEND_SHIFT)

#define PVR_TA_PM2_SRCENABLE_SHIFT	25
#define PVR_TA_PM2_SRCENABLE_MASK	(1 << PVR_TA_PM2_SRCENABLE_SHIFT)

#define PVR_TA_PM2_DSTENABLE_SHIFT	24
#define PVR_TA_PM2_DSTENABLE_MASK	(1 << PVR_TA_PM2_DSTENABLE_SHIFT)

#define PVR_TA_PM2_FOG_SHIFT		22
#define PVR_TA_PM2_FOG_MASK		(3 << PVR_TA_PM2_FOG_SHIFT)

#define PVR_TA_PM2_CLAMP_SHIFT		21
#define PVR_TA_PM2_CLAMP_MASK		(1 << PVR_TA_PM2_CLAMP_SHIFT)

#define PVR_TA_PM2_ALPHA_SHIFT		20
#define PVR_TA_PM2_ALPHA_MASK		(1 << PVR_TA_PM2_ALPHA_SHIFT)

#define PVR_TA_PM2_TXRALPHA_SHIFT	19
#define PVR_TA_PM2_TXRALPHA_MASK	(1 << PVR_TA_PM2_TXRALPHA_SHIFT)

#define PVR_TA_PM2_UVFLIP_SHIFT		17
#define PVR_TA_PM2_UVFLIP_MASK		(3 << PVR_TA_PM2_UVFLIP_SHIFT)

#define PVR_TA_PM2_UVCLAMP_SHIFT	15
#define PVR_TA_PM2_UVCLAMP_MASK		(3 << PVR_TA_PM2_UVCLAMP_SHIFT)

#define PVR_TA_PM2_FILTER_SHIFT		12
#define PVR_TA_PM2_FILTER_MASK		(7 << PVR_TA_PM2_FILTER_SHIFT)

#define PVR_TA_PM2_MIPBIAS_SHIFT	8
#define PVR_TA_PM2_MIPBIAS_MASK		(15 << PVR_TA_PM2_MIPBIAS_SHIFT)

#define PVR_TA_PM2_TXRENV_SHIFT		6
#define PVR_TA_PM2_TXRENV_MASK		(3 << PVR_TA_PM2_TXRENV_SHIFT)

#define PVR_TA_PM2_USIZE_SHIFT		3
#define PVR_TA_PM2_USIZE_MASK		(7 << PVR_TA_PM2_USIZE_SHIFT)

#define PVR_TA_PM2_VSIZE_SHIFT		0
#define PVR_TA_PM2_VSIZE_MASK		(7 << PVR_TA_PM2_VSIZE_SHIFT)

#define PVR_TA_PM3_MIPMAP_SHIFT		31
#define PVR_TA_PM3_MIPMAP_MASK		(1 << PVR_TA_PM3_MIPMAP_SHIFT)

#define PVR_TA_PM3_TXRFMT_SHIFT		0
#define PVR_TA_PM3_TXRFMT_MASK		0xffffffff



/**** Register macros ***************************************************/

/* We use these macros to do all PVR register access, so that it's
   simple later on to hook them for debugging or whatnot. */

#define PVR_GET(REG) (* ( (uint32*)( 0xa05f8000 + (REG) ) ) )
#define PVR_SET(REG, VALUE) PVR_GET(REG) = (VALUE)

/* The registers themselves; these are from Maiwe's powervr-reg.txt */
/* Note that 2D specific registers have been excluded for now (like
   vsync, hsync, v/h size, etc) */

#define PVR_ID			0x0000		/* Chip ID */
#define PVR_REVISION		0x0004		/* Chip revision */
#define PVR_RESET		0x0008		/* Reset pins */
#define PVR_ISP_START		0x0014		/* Start the ISP/TSP */
#define PVR_UNK_0018		0x0018		/* ?? */
#define PVR_ISP_VERTBUF_ADDR	0x0020		/* Vertex buffer address for scene rendering */
#define PVR_ISP_TILEMAT_ADDR	0x002c		/* Tile matrix address for scene rendering */
#define PVR_SPANSORT_CFG	0x0030		/* ?? -- write 0x101 for now */
#define PVR_FB_CFG_1		0x0044		/* Framebuffer config 1 */
#define PVR_FB_CFG_2		0x0048		/* Framebuffer config 2 */
#define PVR_RENDER_MODULO	0x004c		/* Render modulo */
#define PVR_RENDER_ADDR		0x0060		/* Render output address */
#define PVR_RENDER_ADDR_2	0x0064		/* Output for strip-buffering */
#define PVR_PCLIP_X		0x0068		/* Horizontal clipping area */
#define PVR_PCLIP_Y		0x006c		/* Vertical clipping area */
#define PVR_CHEAP_SHADOW	0x0074		/* Cheap shadow control */
#define PVR_OBJECT_CLIP		0x0078		/* Distance for polygon culling */
#define PVR_UNK_007C		0x007c		/* ?? -- write 0x0027df77 for now */
#define PVR_UNK_0080		0x0080		/* ?? -- write 7 for now */
#define PVR_TEXTURE_CLIP	0x0084		/* Distance for texture clipping */
#define PVR_BGPLANE_Z		0x0088		/* Distance for background plane */
#define PVR_BGPLANE_CFG		0x008c		/* Background plane config */
#define PVR_UNK_0098		0x0098		/* ?? -- write 0x00800408 for now */
#define PVR_UNK_00A0		0x00a0		/* ?? -- write 0x20 for now */
#define PVR_UNK_00A8		0x00a8		/* ?? -- write 0x15d1c951 for now */
#define PVR_FOG_TABLE_COLOR	0x00b0		/* Table fog color */
#define PVR_FOG_VERTEX_COLOR	0x00b4		/* Vertex fog color */
#define PVR_FOG_DENSITY		0x00b8		/* Fog density coefficient */
#define PVR_COLOR_CLAMP_MAX	0x00bc		/* RGB Color clamp max */
#define PVR_COLOR_CLAMP_MIN	0x00c0		/* RGB Color clamp min */
#define PVR_GUN_POS		0x00c4		/* Light gun position */
#define PVR_UNK_00C8		0x00c8		/* ?? -- write same as border H in 00d4 << 16 */
#define PVR_VPOS_IRQ		0x00cc		/* Vertical position IRQ */
#define PVR_TEXTURE_MODULO	0x00e4		/* Output texture width modulo */
#define PVR_VIDEO_CFG		0x00e8		/* Misc video config */
#define PVR_SCALER_CFG		0x00f4		/* Smoothing scaler */
#define PVR_PALETTE_CFG		0x0108		/* Palette format */
#define PVR_SYNC_STATUS		0x010c		/* V/H blank status */
#define PVR_UNK_0110		0x0110		/* ?? -- write 0x93f39 for now */
#define PVR_UNK_0114		0x0114		/* ?? -- write 0x200000 for now */
#define PVR_UNK_0118		0x0118		/* ?? -- write 0x8040 for now */
#define PVR_TA_OPB_START	0x0124		/* Object Pointer Buffer start for TA usage */
#define PVR_TA_VERTBUF_START	0x0128		/* Vertex buffer start for TA usage */
#define PVR_TA_OPB_END		0x012c		/* OPB end for TA usage */
#define PVR_TA_VERTBUF_END	0x0130		/* Vertex buffer end for TA usage */
#define PVR_TA_OPB_POS		0x0134		/* Top used memory location in OPB for TA usage */
#define PVR_TA_VERTBUF_POS	0x0138		/* Top used memory location in vertbuf for TA usage */
#define PVR_TILEMAT_CFG		0x013c		/* Tile matrix size config */
#define PVR_OPB_CFG		0x0140		/* Active lists / list size */
#define PVR_TA_INIT		0x0144		/* Initialize vertex reg. params */
#define PVR_YUV_ADDR		0x0148		/* YUV conversion destination */
#define PVR_YUV_CFG_1		0x014c		/* YUV configuration */
#define PVR_UNK_0160		0x0160		/* ?? */
#define PVR_TA_OPB_INIT		0x0164		/* Object pointer buffer position init */
#define PVR_FOG_TABLE_BASE	0x0200		/* Base of the fog table */
#define PVR_PALETTE_TABLE_BASE	0x1000		/* Base of the palette table */

/* Useful memory locations */
#define PVR_TA_INPUT		0x10000000	/* TA command input */
#define PVR_RAM_BASE		0xa5000000	/* PVR RAM (raw) */
#define PVR_RAM_INT_BASE	0xa4000000	/* PVR RAM (interleaved) */
#define PVR_RAM_SIZE		(8*1024*1024)	/* RAM size in bytes */
#define PVR_RAM_TOP		(PVR_RAM_BASE + PVR_RAM_SIZE)		/* Top of raw PVR RAM */
#define PVR_RAM_INT_TOP		(PVR_RAM_INT_BASE + PVR_RAM_SIZE)	/* Top of int PVR RAM */

/* Register content defines, as needed; these will be filled in over time
   as the implementation requires them. There's too many to do otherwise. */

#define PVR_RESET_ALL		0xffffffff	/* PVR_RESET */
#define PVR_RESET_NONE		0x00000000
#define PVR_RESET_TA		0x00000001
#define PVR_RESET_ISPTSP	0x00000002

#define PVR_ISP_START_GO	0xffffffff	/* PVR_ISP_START */

#define PVR_TA_INIT_GO		0x80000000	/* PVR_TA_INIT */


/* Initialization ****************************************************/

/* Initialization and shutdown: stuff you should only ever have to do
   once in your program. */

/* Bin sizes */
#define PVR_BINSIZE_0			0
#define PVR_BINSIZE_8			8
#define PVR_BINSIZE_16			16
#define PVR_BINSIZE_32			32

/* You'll fill in this structure before calling init */
typedef struct {
	/* Bin sizes: opaque polygons, opaque modifiers, translucent
	   polygons, translucent modifiers, punch-thrus */
	int		opb_sizes[5];

	/* Vertex buffer size (should be a nice round number) */
	int		vertex_buf_size;
} pvr_init_params_t;

/* Initialize the PVR chip to ready status, enabling the specified lists
   and using the specified parameters; note that bins and vertex buffers
   come from the texture memory pool! Expects that a 2D mode was 
   initialized already using the vid_* API. */
int pvr_init(pvr_init_params_t *params);

/* Simpler function which initializes the PVR using 16/16 for the opaque
   and translucent lists, and 0's for everything else; 512k of vertex
   buffer. This is equivalent to the old ta_init_defaults() for now. */
int pvr_init_defaults();

/* Shut down the PVR chip from ready status, leaving it in 2D mode as it
   was before the init. */
int pvr_shutdown();


/* Misc parameters ***************************************************/

/* These are miscellaneous parameters you can set which affect the
   rendering process. */

/* Set the background plane color (the area of the screen not covered by
   any other polygons) */
void pvr_set_bg_color(float r, float g, float b);

/* Return the current VBlank count */
int pvr_get_vbl_count();

/* Statistics structure */
typedef struct pvr_stats {
	uint32		enabled_list_mask;	/* Which lists are enabled? */
	uint32		vbl_count;		/* VBlank count */
	uint32		frame_last_time;	/* Ready-to-Ready length for the last frame in milliseconds */
	float		frame_rate;		/* Current frame rate (per second) */
	uint32		reg_last_time;		/* Registration time for the last frame in milliseconds */
	uint32		rnd_last_time;		/* Rendering time for the last frame in milliseconds */
	uint32		vtx_buffer_used;	/* Number of bytes used in the vertex buffer for the last frame */
	uint32		vtx_buffer_used_max;	/* Number of bytes used in the vertex buffer for the largest frame */
	/* ... more later as it's implemented ... */
} pvr_stats_t;

/* Fill in a statistics structure (above) from current data. This
   is a super-set of frame count. */
int pvr_get_stats(pvr_stats_t *stat);


/* Palette management ************************************************/

/* In addition to its 16-bit truecolor modes, the PVR also supports some
   nice paletted modes. These aren't useful for super high quality images
   most of the time, but they can be useful for doing some interesting
   special effects, like the old cheap "worm hole". */

/* Palette formats */
#define PVR_PAL_ARGB1555	0
#define PVR_PAL_RGB565		1
#define PVR_PAL_ARGB4444	2
#define PVR_PAL_ARGB8888	3

/* Set the palette format */
void pvr_set_pal_format(int fmt);

/* Set a palette value; note that the format of the table is variable,
   so for maximum speed we simply let the user decide what to do here. */
static inline void pvr_set_pal_entry(uint32 idx, uint32 value) {
	PVR_SET(PVR_PALETTE_TABLE_BASE + 4*idx, value);
}


/* Hardware Fog parameters *******************************************/

/* Thanks to Paul Boese for figuring this stuff out */

/* Set the fog table color */
void pvr_fog_table_color(float a, float r, float g, float b);

/* Set the fog vertex color */
void pvr_fog_vertex_color(float a, float r, float g, float b);

/* Set the fog far depth */
void pvr_fog_far_depth(float d);

/* Initialize the fog table using an exp2 algorithm (like GL_EXP2) */
void pvr_fog_table_exp2(float density);

/* Initialize the fog table using an exp algorithm (like GL_EXP) */
void pvr_fog_table_exp(float density);

/* Initialize the fog table using a linear algorithm (like GL_LINEAR) */
void pvr_fog_table_linear(float start, float end);

/* Set a custom fog table from float values */
void pvr_fog_table_custom(float tbl1[]);


/* Memory management *************************************************/

/* PVR memory management in KOS uses a modified dlmalloc; see the
   source file pvr_mem_core.c for more info. */

/* Allocate a chunk of memory from texture space; the returned value
   will be relative to the base of texture memory (zero-based) */
pvr_ptr_t pvr_mem_malloc(size_t size);

/* Free a previously allocated chunk of memory */
void pvr_mem_free(pvr_ptr_t chunk);

/* Return the number of bytes available still in the memory pool */
uint32 pvr_mem_available();

/* Reset the memory pool, equivalent to freeing all textures currently
   residing in RAM. */
void pvr_mem_reset();

/* Check the memory block list to see what's allocated */
/* Only available if you've enabled KM_DBG in pvr_mem.c */
void pvr_mem_print_list();

/* Print some statistics (like mallocstats) */
void pvr_mem_stats();

/* Scene rendering ***************************************************/

/* This API is used to submit triangle strips to the PVR via the TA
   interace in the chip. 

   An important side note about the PVR is that all primitive types
   must be submitted grouped together. If you have 10 polygons for each
   list type, then the PVR must receive them via the TA by list type,
   with a list delimiter in between.

   So there are two modes you can use here. The first mode allows you to
   submit data directly to the TA. Your data will be forwarded to the
   chip for processing as it is fed to the PVR module. If your data
   is easily sorted into the primitive types, then this is the fastest
   mode for submitting data.

   The second mode allows you to submit data via main-RAM vertex buffers,
   which will be queued until the proper primitive type is active. In this
   case, each piece of data is copied into the vertex buffer while the
   wrong list is activated, and when the proper list becomes activated,
   the data is all sent at once. Ideally this would be via DMA, right 
   now it is by store queues. This has the advantage of allowing you to
   send data in any order and have the PVR functions resolve how it should
   get sent to the hardware, but it is slower.

   The nice thing is that any combination of these modes can be used. You
   can assign a vertex buffer for any list, and it will be used to hold the
   incoming vertex data until the proper list has come up. Or if the proper
   list is already up, the data will be submitted directly. So if most of
   your polygons are opaque, and you only have a couple of translucents,
   you can set a small buffer to gather translucent data and then it will
   get sent when you do a pvr_end_scene().

   Thanks to Mikael Kalms for the idea for this API.

   Another somewhat subtle point that bears mentioning is that in the normal
   case (interrupts enabled) an interrupt handler will automatically take
   care of starting a frame rendering (after scene_finish()) and also
   flipping pages when appropriate. */

/* Setup a vertex buffer for one of the list types. If the specified list type
   already has a vertex buffer, it will be replaced by the new one; if NULL
   is specified as a buffer location, the list type will be switched to direct
   mode. The old buffer location will be returned (if any). */
void * pvr_set_vertex_buffer(pvr_list_t list, void * buffer, int len);

/* Begin collecting data for a frame of 3D output to the off-screen
   frame buffer */
void pvr_scene_begin();

/* Begin collecting data for a frame of 3D output to the specified texture;
   pass in the size of the buffer in rx and ry, and the return values in
   rx and ry will be the size actually used (if changed). Note that
   currently this only supports screen-sized output! */
void pvr_scene_begin_txr(pvr_ptr_t txr, uint32 *rx, uint32 *ry);

/* Begin collecting data for the given list type. Lists do not have to be
   submitted in any particular order, but all types of a list must be 
   submitted at once. If the given list has already been closed, then an
   error (-1) is returned. */
int pvr_list_begin(pvr_list_t list);

/* End collecting data for the current list type. Lists can never be opened
   again within a single frame once they have been closed. Thus submitting
   a primitive that belongs in a closed list is considered an error. Closing
   a list that is already closed is also an error (-1). Note that if you open
   a list but do not submit any primitives, a blank one will be submitted to
   satisfy the hardware. */
int pvr_list_finish();

/* Submit a primitive of the _current_ list type; note that any values
   submitted in this fashion will go directly to the hardware without any
   sort of buffering, and submitting a primitive of the wrong type will
   quite likely ruin your scene. Note that this also will not work if you
   haven't begun any list types (i.e., all data is queued). Returns -1 for
   failure. */
int pvr_prim(void * data, int size);

/* Initialize a state variable for Direct Rendering; variable should be
   of the type pvr_dr_state_t */
#define pvr_dr_init(vtx_buf_ptr) do { \
	(vtx_buf_ptr) = 0; \
	QACR0 = ((((uint32)PVR_TA_INPUT) >> 26) << 2) & 0x1c; \
	QACR1 = ((((uint32)PVR_TA_INPUT) >> 26) << 2) & 0x1c; \
} while (0)
#define pvr_dr_state_t uint32

/* Obtain the target address for Direct Rendering; this will return a
   write-only destination address where a primitive should be written to get
   ready to submit it to the TA in DR mode. You must pass in a variable
   which was initialized with pvr_dr_init(). */
#define pvr_dr_target(vtx_buf_ptr) \
	({ (vtx_buf_ptr) ^= 32; \
	   (pvr_vertex_t *)(0xe0000000 | (vtx_buf_ptr)); \
	})

/* Commit a primitive written into the Direct Rendering target address; pass
   the address returned by pvr_dr_target(). */
#define pvr_dr_commit(addr) __asm__ __volatile__("pref @%0" : : "r" (addr))

/* Submit a primitive of the given list type; if the requested list is not
   the current list, then the data will be queued in a vertex buffer if
   available, otherwise it will be submitted directly. If a vertex buffer
   doesn't exist when one is needed, an error (-1) is returned. */
int pvr_list_prim(pvr_list_t list, void * data, int size);

/* Called to flush buffered data of the given list type to the hardware
   processor. If there is no vertex buffer for the given type, then an error
   (-1) is returned. The list must have been started with pvr_begin_list(). */
int pvr_list_flush(pvr_list_t list);

/* Call this after you have finished submitting all data for a frame; once
   this has been called, you can not submit any more data until one of the
   pvr_scene_begin() functions is called again. An error (-1) is returned if
   you have not started a scene already. */
int pvr_scene_finish();

/* Block the caller until the PVR system is ready for another frame to be
   started. The PVR system allocates enough space for two frames: one in
   data collection mode, and another in rendering mode. If a frame is 
   currently rendering, and another frame has already been closed, then the
   caller cannot do anything else until the rendering frame completes. Note
   also that the new frame cannot be activated except during a vertical
   blanking period, so this essentially waits until a rendered frame is
   complete _AND_ a vertical blank happens. Returns -1 if the wait times
   out. Note that once this returns, the PVR system is ready for another
   frame's data to be collected. */
int pvr_wait_ready();

/* Same thing as above, but in non-blocking form; returns -1 if the PVR isn't
   ready; returns 0 when the PVR has accepted your frame and is ready for
   more. */
int pvr_check_ready();


/* Primitive handling ************************************************/

/* These functions help you prepare primitives for loading into the
   PVR for scene processing. */

/* Compile a polygon context into a polygon header */
void pvr_poly_compile(pvr_poly_hdr_t *dst, pvr_poly_cxt_t *src);

/* Create a colored polygon context with parameters similar to
   the old "ta" function `ta_poly_hdr_col' */
void pvr_poly_cxt_col(pvr_poly_cxt_t *dst, pvr_list_t list);

/* Create a textured polygon context with parameters similar to
   the old "ta" function `ta_poly_hdr_txr' */
void pvr_poly_cxt_txr(pvr_poly_cxt_t *dst, pvr_list_t list,
	int textureformat, int tw, int th, pvr_ptr_t textureaddr,
	int filtering);


/* Texture handling **************************************************/

/* Helper functions for handling texture tasks of various kinds. */

/* Load raw texture data from an SH-4 buffer into PVR RAM */
void pvr_txr_load(void * src, pvr_ptr_t dst, uint32 count);

/* Constants for texture loading */
#define PVR_TXRLOAD_4BPP	0x01	/* Basic pixel formats */
#define PVR_TXRLOAD_8BPP	0x02
#define PVR_TXRLOAD_16BPP	0x03
#define PVR_TXRLOAD_FMT_MASK	0x0f

#define PVR_TXRLOAD_VQ_LOAD		0x10	/* Do VQ encoding (not supported yet, if ever) */
#define PVR_TXRLOAD_INVERT_Y		0x20	/* Invert the Y axis while loading */
#define PVR_TXRLOAD_FMT_VQ		0x40	/* Texture is already VQ encoded */
#define PVR_TXRLOAD_FMT_TWIDDLED	0x80	/* Texture is already twiddled */
#define PVR_TXRLOAD_FMT_NOTWIDDLE	0x80	/* Same sorta thing -- don't twiddle it */
#define PVR_TXRLOAD_DMA			0x8000	/* Use DMA to load the texture */
#define PVR_TXRLOAD_NONBLOCK		0x4000	/* Use non-blocking loads (only for DMA) */
#define PVR_TXRLOAD_SQ			0x2000	/* Use store queues to load */

/* Load texture data from an SH-4 buffer into PVR RAM, twiddling it
   in the process, among other things (see pvr_texture.c for more
   details) */
void pvr_txr_load_ex(void * src, pvr_ptr_t dst, uint32 w, uint32 h, uint32 flags);

/* Load a KOS Platform Independent Image (subject to restraint checking) */
void pvr_txr_load_kimg(kos_img_t *img, pvr_ptr_t dst, uint32 flags);


/* PVR DMA ***********************************************************/

/** Load a texture using PVR DMA. If block is non-zero, then the function
    will not return until the texture DMA is complete. Otherwise, check
    the value of pvr_dma_complete() to see if things are ready. */
void pvr_txr_load_dma(void * src, pvr_ptr_t dest, uint32 count, int block);

/** Returns non-zero if PVR DMA is inactive. */
int pvr_dma_complete();

/** Initialize PVR DMA */
void pvr_dma_init();

/** Shut down PVR DMA */
void pvr_dma_shutdown();

/*********************************************************************/


__END_DECLS

#endif

