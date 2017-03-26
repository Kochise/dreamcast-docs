/*++

  COPYRIGHT        (C) NEC        Corporation 1997 - 1999

  All rights reserved by NEC Corporation. This program must be
  used solely for the purpose for which it was furnished by NEC
  Corporation. No part of this program may be reproduced or
  disclosed to others, in any form, without the prior written
  permission of NEC Corporation.
  Use of copyright notice does not evidence publication of this
  program.

  Author     :		T.Hirata(NEC Software,Ltd.)
  Module Name:      km2strip.h

  Abstract:
    Kamui is Low-Level PowerVR Driver.
    'km2strip.h' defines kamui2 strip context structure.

  Environment:
    ANSI C Compiler

  Notes:
    defines for strip context / vertex context.

  Revision History:

--*/
#if !defined(__kamui2_strip_h)
#define __kamui2_strip_h

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * Bit Depth
 */
#define KM_BITDEPTH_16		1
#define KM_BITDEPTH_24		2
#define KM_BITDEPTH_32		3

/*
 * Pixel Format.
 */
#define KM_PIXELFORMAT_ARGB1555			(0x00000000)
#define KM_PIXELFORMAT_RGB565			(0x08000000)
#define KM_PIXELFORMAT_ARGB4444			(0x10000000)
#define KM_PIXELFORMAT_YUV422			(0x18000000)
#define KM_PIXELFORMAT_BUMP				(0x20000000)
#define KM_PIXELFORMAT_PALETTIZED_4BPP	(0x28000000)
#define KM_PIXELFORMAT_PALETTIZED_8BPP	(0x30000000)

/*
 * Texture Suraface paramter.
 */
#define KM_SURFACEFLAGS_MIPMAPED		(0x80000000)
#define KM_SURFACEFLAGS_VQ				(0x40000000)
#define KM_SURFACEFLAGS_NOTWIDDLED		(0x04000000)
#define KM_SURFACEFLAGS_TWIDDLED		(0x00000000)
#define KM_SURFACEFLAGS_STRIDE			(0x02000000)
#define KM_SURFACEFLAGS_PALETTIZED		(0x00008000)
#define KM_SURFACEFLAGS_VSIZE8			(0x00000000)
#define KM_SURFACEFLAGS_VSIZE16			(0x00000001)
#define KM_SURFACEFLAGS_VSIZE32			(0x00000002)
#define KM_SURFACEFLAGS_VSIZE64			(0x00000003)
#define KM_SURFACEFLAGS_VSIZE128		(0x00000004)
#define KM_SURFACEFLAGS_VSIZE256		(0x00000005)
#define KM_SURFACEFLAGS_VSIZE512		(0x00000006)
#define KM_SURFACEFLAGS_VSIZE1024		(0x00000007)
#define KM_SURFACEFLAGS_USIZE8			(0x00000000)
#define KM_SURFACEFLAGS_USIZE16			(0x00000008)
#define KM_SURFACEFLAGS_USIZE32			(0x00000010)
#define KM_SURFACEFLAGS_USIZE64			(0x00000018)
#define KM_SURFACEFLAGS_USIZE128		(0x00000020)
#define KM_SURFACEFLAGS_USIZE256		(0x00000028)
#define KM_SURFACEFLAGS_USIZE512		(0x00000030)
#define KM_SURFACEFLAGS_USIZE1024		(0x00000038)

/*
 * FrameBuffer Suraface paramter
 */
#define KM_SURFACEFLAGS_FULLSCREENBUFFER	(0x00000000)
#define KM_SURFACEFLAGS_STRIPBUFFER			(0x00000001)

/*
 * Texture Map size:
 */
#define KM_MAPSIZE_1		1
#define KM_MAPSIZE_2		2
#define KM_MAPSIZE_4		4
#define KM_MAPSIZE_8		8
#define KM_MAPSIZE_16		16
#define KM_MAPSIZE_32		32
#define KM_MAPSIZE_64		64
#define KM_MAPSIZE_128		128
#define KM_MAPSIZE_256		256
#define KM_MAPSIZE_512		512
#define KM_MAPSIZE_1024		1024

/*
 *	MipMap D Adjust
 */
#define KM_MIPMAP_D_ADJUST_0_25		(0x00000001)	/* D=0.25 */
#define KM_MIPMAP_D_ADJUST_0_50		(0x00000002)	/* D=0.50 */
#define KM_MIPMAP_D_ADJUST_0_75		(0x00000003)	/* D=0.75 */
#define KM_MIPMAP_D_ADJUST_1_00		(0x00000004)	/* D=1.00 */
#define KM_MIPMAP_D_ADJUST_1_25		(0x00000005)	/* D=1.25 */
#define KM_MIPMAP_D_ADJUST_1_50		(0x00000006)	/* D=1.50 */
#define KM_MIPMAP_D_ADJUST_1_75		(0x00000007)	/* D=1.75 */
#define KM_MIPMAP_D_ADJUST_2_00		(0x00000008)	/* D=2.00 */
#define KM_MIPMAP_D_ADJUST_2_25		(0x00000009)	/* D=2.25 */
#define KM_MIPMAP_D_ADJUST_2_50		(0x0000000A)	/* D=2.50 */
#define KM_MIPMAP_D_ADJUST_2_75		(0x0000000B)	/* D=2.75 */
#define KM_MIPMAP_D_ADJUST_3_00		(0x0000000C)	/* D=3.00 */
#define KM_MIPMAP_D_ADJUST_3_25		(0x0000000D)	/* D=3.25 */
#define KM_MIPMAP_D_ADJUST_3_50		(0x0000000E)	/* D=3.50 */
#define KM_MIPMAP_D_ADJUST_3_75		(0x0000000F)	/* D=3.75 */

/*
 * ParamType Data for KMVERTEXCONTEXT structure
 */
#define KM_PARAM_POLYGON   			(0x04)	/* 100	*/
#define KM_PARAM_MODIFIERVOLUME		(0x04)	/* 100	*/
#define KM_PARAM_SPRITE				(0x05)	/* 101  */

/*
 * KMPARAMTYPE
 */
typedef enum {
    KM_POLYGON	        = 0,	/* Triange Polygon				*/
    KM_MODIFIERVOLUME	= 1,	/* Modifier Volume(Shadow/Light)*/
    KM_SPRITE	        = 2	    /* Sprite(Quad)					*/
}KMPARAMTYPE;

/*
 * ShadowMode
 */
typedef enum
{
	KM_NORMAL_POLYGON		= 0,
	KM_CHEAPSHADOW_POLYGON	= 2
}KMSHADOWMODE;

/*
 * KMCOLORTYPE
 */
typedef enum {
    KM_PACKEDCOLOR	            = 0,	/* 32bit ARGB packed color format	*/
    KM_FLOATINGCOLOR	        = 1,	/* 32bit * 4 floating color format	*/
    KM_INTENSITY	            = 2,	/* Intensity format					*/
    KM_INTENSITY_PREV_FACE_COL	= 3		/* Intensity format(Prev Face Color)*/
}KMCOLORTYPE;

/*
 * KMUVFORMAT
 */
typedef enum {
    KM_32BITUV	                = 0,	/* 32bit float format(UV)	*/
    KM_16BITUV	                = 1	    /* 16bit float format(UV)	*/
}KMUVFORMAT;

/*
 * Modifier Volume Valiant
 */
typedef enum {
    KM_NOMODIFIER	    = 0,	/* No Modifier */
    KM_MODIFIER_A	    = 1	    /* ModifierA   */
}KMMODIFIER;


/*
 * KMDEPTHMODE
 */
typedef enum
{
    KM_IGNORE	            = 0,
    KM_LESS	                = 1,
    KM_EQUAL	            = 2,
    KM_LESSEQUAL	        = 3,
    KM_GREATER	            = 4,
    KM_NOTEQUAL	            = 5,
    KM_GREATEREQUAL	        = 6,
    KM_ALWAYS	            = 7
} KMDEPTHMODE;

/*
 * KMCULLINGMODE 
 */
typedef enum
{
    KM_NOCULLING	            = 0,    /* No Culling				*/
    KM_CULLSMALL	            = 1,    /* Small Polygon Culling	*/
    KM_CULLCCW	                = 2,    /* Cull Counter Clockwise	*/
    KM_CULLCW	                = 3	    /* Cull Clockwise			*/
} KMCULLINGMODE;


/*
 * KMSHADINGMODE
 */
typedef enum
{
    KM_NOTEXTUREFLAT	        = 0,
    KM_NOTEXTUREGOURAUD	        = 1,
    KM_TEXTUREFLAT	            = 2,
    KM_TEXTUREGOURAUD	        = 3
} KMSHADINGMODE;

/*
 * KMFOGMODE
 */
typedef enum
{
    KM_FOGTABLE		=	0,
    KM_FOGVERTEX	=	1,
    KM_NOFOG		=	2,
	KM_FOGTABLE_2	=	3
} KMFOGMODE;

/*
 * KMBLENDINGMODE
 */
typedef enum
{
    KM_BOTHINVSRCALPHA,
    KM_BOTHSRCALPHA,
    KM_DESTALPHA,
    KM_DESTCOLOR,
    KM_INVDESTALPHA,
    KM_INVDESTCOLOR,
    KM_INVSRCALPHA,
    KM_INVSRCCOLOR,
    KM_SRCALPHA,
    KM_SRCCOLOR,
    KM_ONE,
    KM_ZERO
} KMBLENDINGMODE;

/*
 * KMCLAMPMODE
 */

typedef enum
{
    KM_NOCLAMP  = 0,
    KM_CLAMP_V  = 1,
    KM_CLAMP_U  = 2,
    KM_CLAMP_UV = 3
} KMCLAMPMODE;

/*
 * KMFLIPMODE
 */
typedef enum
{
    KM_NOFLIP	= 0,
    KM_FLIP_V   = 1,
    KM_FLIP_U   = 2,
    KM_FLIP_UV  = 3
} KMFLIPMODE;

/*
 * KMFILTERMODE
 */
typedef enum
{
    KM_POINT_SAMPLE     = 0,
    KM_BILINEAR         = 1,
    KM_TRILINEAR_A      = 2,
    KM_TRILINEAR_B      = 3
} KMFILTERMODE;

/*
 * Texture Shading mode
 */
typedef enum
{
	KM_DECAL			= 0,
    KM_MODULATE         = 1,
    KM_DECAL_ALPHA      = 2,
    KM_MODULATE_ALPHA   = 3
} KMTEXTURESHADINGMODE;

/*
 *  Rendering Context Definisions
 *	    Must be describe PerVertex definisions.
 */
typedef enum
{
    KM_PARAMTYPE            = 0x00100000, /* Parameter Type. */
    KM_LISTTYPE             = 0x00200000, /* List Type. */
	KM_STRIPLENGTH			= 0x08000000, /* Strip Length */
	KM_USERCLIPMODE			= 0x10000000, /* UserClip Mode */
    KM_COLORTYPE            = 0x00400000, /* Color Type. */
    KM_UVFORMAT				= 0x00800000, /* UV Format. */
    KM_DEPTHMODE            = 0x00000001, /* Set Depth mode. */
    KM_CULLINGMODE          = 0x00000002, /* Set Culling mode  */
    KM_SCREENCOORDINATION	= 0x00000004, /* Set Coordinate type */
    KM_SHADINGMODE          = 0x00000008, /* Texture Gouraud, Texture Flat, Non-Texture Gouraud */
    KM_MODIFIER             = 0x00000010, /* Modifier Volume Valiant No or A */
    KM_ZWRITEDISABLE        = 0x00000020, /* Z Write Disable or not */
    KM_SRCBLENDINGMODE      = 0x00000040, /* Blending Mode */
    KM_DSTBLENDINGMODE      = 0x00000080, /* Blending Mode */
    KM_SRCSELECT			= 0x01000000, /* Blending Mode */
    KM_DSTSELECT			= 0x02000000, /* Blending Mode */
	KM_FOGMODE              = 0x00000100, /* Fog Non or Vertex or Table */
    KM_USESPECULAR          = 0x00000200, /* Specular Highlighted or not */
    KM_USEALPHA             = 0x00000400, /* Alpha Blended or not */
    KM_IGNORETEXTUREALPHA   = 0x00000800, /* Ignore Texture Alpha */
    KM_CLAMPUV              = 0x00001000, /* Texture Clamping */
    KM_FLIPUV               = 0x00002000, /* Texture Flipping */
    KM_FILTERMODE           = 0x00004000, /* Point-sample or Bilinear or Trilinear */
    KM_SUPERSAMPLE          = 0x00008000, /* Anisotoropic Filter */
    KM_MIPMAPDADJUST        = 0x00010000, /* MipMap D Adjust */
    KM_TEXTURESHADINGMODE   = 0x00020000, /* Modulate or Decal Alpha or Modulate Alpha */
    KM_COLORCLAMP           = 0x00040000, /* Color Clamping */
    KM_PALETTEBANK          = 0x00080000, /* Palette Bank */
    KM_DCALCEXACT	        = 0x04000000  /* D Calc Exact */
} KMRENDERSTATE;

/*
 * Modifier
 */
#define	KM_MODIFIER_NORMAL_POLY			(0)
#define	KM_MODIFIER_INCLUDE_FIRST_POLY	(KM_MODIFIER_NORMAL_POLY)
#define	KM_MODIFIER_EXCLUDE_FIRST_POLY	(KM_MODIFIER_NORMAL_POLY)
#define	KM_MODIFIER_INCLUDE_LAST_POLY	(1 << 29)
#define	KM_MODIFIER_EXCLUDE_LAST_POLY	(2 << 29)


/*
 * UserClip 
 */
typedef	enum
{
    KM_USERCLIP_DISABLE =0,     /*  UserClip Disable	*/
    KM_USERCLIP_RESERVE =1,     /*  Reserved			*/
    KM_USERCLIP_INSIDE  =2,     /*  UserClip Inside		*/
    KM_USERCLIP_OUTSIDE =3	    /*  UserClip Outside	*/
} KMUSERCLIPMODE;


/*
 * Kamui's Vertex Type.
 */
typedef enum {
    KM_VERTEXTYPE_00,           /* Vertex data Type 0	*/
    KM_VERTEXTYPE_01,           /* Vertex data Type 1	*/
    KM_VERTEXTYPE_02,           /* Vertex data Type 2	*/
    KM_VERTEXTYPE_03,           /* Vertex data Type 3	*/
    KM_VERTEXTYPE_04,           /* Vertex data Type 4	*/
    KM_VERTEXTYPE_05,           /* Vertex data Type 5	*/
    KM_VERTEXTYPE_06,           /* Vertex data Type 6	*/
    KM_VERTEXTYPE_07,           /* Vertex data Type 7	*/
    KM_VERTEXTYPE_08,           /* Vertex data Type 8	*/
    KM_VERTEXTYPE_09,           /* Vertex data Type 9	*/
    KM_VERTEXTYPE_10,           /* Vertex data Type 10	*/
    KM_VERTEXTYPE_11,           /* Vertex data Type 11	*/
    KM_VERTEXTYPE_12,           /* Vertex data Type 12	*/
    KM_VERTEXTYPE_13,           /* Vertex data Type 13	*/
    KM_VERTEXTYPE_14,           /* Vertex data Type 14	*/
    KM_VERTEXTYPE_15,           /* Vertex data Type 15	*/
    KM_VERTEXTYPE_16,           /* Vertex data Type 16	*/
    KM_VERTEXTYPE_17            /* Vertex data Type 17	*/
}KMVERTEXTYPE;

/*
 * Vertex Flag(Normal or EndofStrip)
 */
#define KM_VERTEXPARAM_NORMAL			(0xE0000000)
#define KM_VERTEXPARAM_ENDOFSTRIP		(0xF0000000)

/*
 * for kmInitStripContext/kmRegisterDefaultStripContext
 */
#define	KM_STRIPCONTEXT_USER00				  (0)
#define	KM_STRIPCONTEXT_USER01				  (1)
#define	KM_STRIPCONTEXT_USER02				  (2)
#define	KM_STRIPCONTEXT_USER03				  (3)
#define	KM_STRIPCONTEXT_USER04				  (4)
#define	KM_STRIPCONTEXT_USER05				  (5)
#define	KM_STRIPCONTEXT_USER06				  (6)
#define	KM_STRIPCONTEXT_USER07				  (7)
#define	KM_STRIPCONTEXT_USER08				  (8)
#define	KM_STRIPCONTEXT_USER09				  (9)

/*
	xxxx xxxx xxxx xxxx  xxxx xxxx xxxx xxxx 
                     ||     |    |      ++++ LISTTYPE
                     ||     |    +---------- SYSTEM(if 0 then ignore  LISTTYPE)
                     ||     +--------------- GOURAUD
                     ++--------------------- MODIFIER(first/normal/last)
*/
#define	KM_STRIPCONTEXT_SYSTEM				(0x00000100)
#define	KM_STRIPCONTEXT_SYS_FLAT			(0x00000000 | KM_STRIPCONTEXT_SYSTEM)
#define	KM_STRIPCONTEXT_SYS_GOURAUD			(0x00001000 | KM_STRIPCONTEXT_SYSTEM)

#define	KM_STRIPCONTEXT_SYS_NORMAL_MODIFIER			(0x00000000 | KM_STRIPCONTEXT_SYSTEM)
#define	KM_STRIPCONTEXT_SYS_INCLUDE_FIRST_MODIFIER	(0x00000000 | KM_STRIPCONTEXT_SYSTEM)
#define	KM_STRIPCONTEXT_SYS_EXCLUDE_FIRST_MODIFIER	(0x00000000 | KM_STRIPCONTEXT_SYSTEM)
#define	KM_STRIPCONTEXT_SYS_INCLUDE_LAST_MODIFIER	(0x00010000 | KM_STRIPCONTEXT_SYSTEM)
#define	KM_STRIPCONTEXT_SYS_EXCLUDE_LAST_MODIFIER	(0x00020000 | KM_STRIPCONTEXT_SYSTEM)


#ifdef __cplusplus
}
#endif 

#endif /*  __kamui_enum_h	*/

