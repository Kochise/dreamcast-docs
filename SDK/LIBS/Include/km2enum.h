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
  Module Name:		km2enum.h

  Abstract:
    Kamui is Low-Level PowerVR Driver.
    'km2enum.h' is kamui2 define constant values.

  Environment:
    ANSI C Compiler. 

  Notes:
    Kamui2 enum.

  Revision History:

--*/
#if !defined(__kamui2_enum_h)
#define __kamui2_enum_h

#ifdef __cplusplus
extern "C" {
#endif 

/*++
 KAMUI target device
 -------------------

 for kmInitDevice();

--*/
typedef enum
{
    KM_DREAMCAST = 0x000000,	        /*  xxxx xxx0 xxxx xxxxb	*/
    KM_NAOMI     = 0x010000             /*  xxxx xxx1 xxxx xxxxb	*/
}KMDEVICE;


/*
// KM_DSPMODE_XXXX
// ---------------
//  Bit order : Little Endian:?
//  xxxx xxxx xxxx xxxx
//             ||| ||||
//             ||| |||+---- VGA	= 1     ; 0x01  = KM_VGA
//             ||| ||+----- NTSC= 0     ; 0x00  = KM_NTSC
//             ||| ||       PAL = 1     ; 0x02  = KM_PAL
//             ||| |+------ NI  = 0     ; 0x00  = Enable Interlace Flicker Fliter on NTSC/PAL
//             ||| |        I   = 1     ; 0x04  = Interlace
//             ||| +--------PNI = 1     : 0x08  = pseudo-non-interlace
//             ||+--------- 320 = 0     ; 0x00
//             ||           640 = 1     ; 0x10
//             |+---------- 240 = 0     ; 0x00
//             |            480 = 1     ; 0x20
//             +----------- EXT = 1     ; 0x40  = PAL DisplayArea Extension
//
*/
typedef enum
{
    KM_NTSC = 0,	        /*  xxxx xx00b	*/
    KM_VGA  = 1,	        /*  xxxx xxx1b	*/
    KM_PAL  = 2 	        /*	xxxx xx10b	*/

}KMVIDEOMODE;

/*
 * KMVIDEOMODE
 *
 *	(@1) ... Same line display    		: Even / Odd Frame:
 *	(@2) ... Pseudo-Non-Interlace		: Disable Flicker Filter
 *	(@3) ... Non-Interlace Flicker Free	: Enable Interlace Flicker Fliter (Pseudo-None-Interlace...)
 *           If you select this mode then you have to update each frame data  in 16.66ms.
 *           Your scene data should be able to finish renderring in 16.66ms by PowerVR2 Renderring Engine.
 */

#define KM_DSPMODE_NONINTERLACE			(0x00)      /*  xxxx 00xxb	*/
#define KM_DSPMODE_INTERLACE    		(0x04)      /*  xxxx 01xxb	*/
#define KM_DSPMODE_PSEUDONONINTERLACE	(0x08)      /*  xxxx 10xxb	*/

#define KM_DSPMODE_WIDTH_320    		(0x000)     /*  xxx0 xxxxb	*/
#define KM_DSPMODE_WIDTH_640    		(0x010)     /*  xxx1 xxxxb	*/

#define KM_DSPMODE_HEIGHT_240   		(0x000)     /*  xx0x xxxxb	*/
#define KM_DSPMODE_HEIGHT_480   		(0x020)     /*  xx1x xxxxb	*/
#define KM_DSPMODE_HEIGHT_EXT			(0x040)		/*  x1xx xxxxb	*/

#define KM_DSPMODE_320x240      (KM_DSPMODE_WIDTH_320 | KM_DSPMODE_HEIGHT_240)           /*  xx00 xxxxb	*/
#define KM_DSPMODE_640x240      (KM_DSPMODE_WIDTH_640 | KM_DSPMODE_HEIGHT_240)           /*  xx01 xxxxb	*/
#define KM_DSPMODE_320x480      (KM_DSPMODE_WIDTH_320 | KM_DSPMODE_HEIGHT_480)           /*  xx10 xxxxb	*/
#define KM_DSPMODE_640x480      (KM_DSPMODE_WIDTH_640 | KM_DSPMODE_HEIGHT_480)           /*  xx11 xxxxb	*/

#define KM_DSPMODE_640x240_EXT  (KM_DSPMODE_WIDTH_640 | KM_DSPMODE_HEIGHT_240 | KM_DSPMODE_HEIGHT_EXT)
#define KM_DSPMODE_640x480_EXT  (KM_DSPMODE_WIDTH_640 | KM_DSPMODE_HEIGHT_480 | KM_DSPMODE_HEIGHT_EXT)
																					     /*  x111 xxxxb	*/

typedef enum
{
    KM_DSPMODE_VGA320x240       =	(KM_VGA  | KM_DSPMODE_NONINTERLACE		 | KM_DSPMODE_320x240),		/* VGA  320x240 60Hz	              			*/
    KM_DSPMODE_VGA320x480       =	(KM_VGA  | KM_DSPMODE_NONINTERLACE		 | KM_DSPMODE_320x480),		/* VGA  320x480 60Hz	              			*/
    KM_DSPMODE_VGA640x240       =	(KM_VGA  | KM_DSPMODE_NONINTERLACE		 | KM_DSPMODE_640x240),		/* VGA  640x240 60Hz	              			*/
    KM_DSPMODE_VGA640x480       =	(KM_VGA  | KM_DSPMODE_NONINTERLACE		 | KM_DSPMODE_640x480),		/* VGA  640x480 60Hz	              			*/
    KM_DSPMODE_NTSCNI320x240	=	(KM_NTSC | KM_DSPMODE_NONINTERLACE       | KM_DSPMODE_320x240),		/* NTSC 320x240 60Hz Non-Interlace		  (@1)	*/
    KM_DSPMODE_NTSCI320x240	    =	(KM_NTSC | KM_DSPMODE_INTERLACE          | KM_DSPMODE_320x240),		/* NTSC 320x240 30Hz Interlace					*/
    KM_DSPMODE_NTSCNI640x240	=	(KM_NTSC | KM_DSPMODE_NONINTERLACE       | KM_DSPMODE_640x240),		/* NTSC 640x240 60Hz Non-Interlace		  (@1)	*/
    KM_DSPMODE_NTSCI640x240	    =	(KM_NTSC | KM_DSPMODE_INTERLACE          | KM_DSPMODE_640x240),		/* NTSC 640x240 30Hz Interlace					*/
    KM_DSPMODE_NTSCNI320x480FF	=	(KM_NTSC | KM_DSPMODE_NONINTERLACE       | KM_DSPMODE_320x480),		/* NTSC 320x480 60Hz Non-Interlace FF     (@3)	*/
    KM_DSPMODE_NTSCNI320x480	=	(KM_NTSC | KM_DSPMODE_PSEUDONONINTERLACE | KM_DSPMODE_320x480),		/* NTSC 320x480 60Hz Pseudo-Non-Interlace (@2)	*/
    KM_DSPMODE_NTSCI320x480	    =	(KM_NTSC | KM_DSPMODE_INTERLACE          | KM_DSPMODE_320x480),		/* NTSC 320x480 30Hz Interlace					*/
    KM_DSPMODE_NTSCNI640x480FF  =	(KM_NTSC | KM_DSPMODE_NONINTERLACE       | KM_DSPMODE_640x480),		/* NTSC 640x480 60Hz Non-Interlace FF     (@3)	*/
    KM_DSPMODE_NTSCNI640x480    =	(KM_NTSC | KM_DSPMODE_PSEUDONONINTERLACE | KM_DSPMODE_640x480),		/* NTSC 640x480 60Hz Pseudo-Non-Interlace (@2)	*/
    KM_DSPMODE_NTSCI640x480	    =	(KM_NTSC | KM_DSPMODE_INTERLACE          | KM_DSPMODE_640x480),		/* NTSC 640x480 30Hz Interlace					*/
    KM_DSPMODE_PALNI320x240	    =	(KM_PAL  | KM_DSPMODE_NONINTERLACE       | KM_DSPMODE_320x240),		/* PAL  320x240 50Hz Non-Interlace				*/
    KM_DSPMODE_PALI320x240	    =	(KM_PAL  | KM_DSPMODE_INTERLACE          | KM_DSPMODE_320x240),		/* PAL  320x240 25Hz Interlace					*/
    KM_DSPMODE_PALNI640x240	    =	(KM_PAL  | KM_DSPMODE_NONINTERLACE       | KM_DSPMODE_640x240),		/* PAL  640x240 50Hz Non-Interlace		  (@1)	*/
    KM_DSPMODE_PALNI640x240EXT  =	(KM_PAL  | KM_DSPMODE_NONINTERLACE       | KM_DSPMODE_640x240_EXT),	/* PAL  640x240 50Hz Non-Interlace		  (@1)	*/
    KM_DSPMODE_PALI640x240	    =	(KM_PAL  | KM_DSPMODE_INTERLACE          | KM_DSPMODE_640x240),		/* PAL  640x240 25Hz Interlace					*/
    KM_DSPMODE_PALNI320x480FF   =	(KM_PAL  | KM_DSPMODE_NONINTERLACE       | KM_DSPMODE_320x480),		/* PAL  320x480 50Hz Non-Interlace FF     (@3)	*/
    KM_DSPMODE_PALNI320x480	    =	(KM_PAL  | KM_DSPMODE_PSEUDONONINTERLACE | KM_DSPMODE_320x480),		/* PAL  320x480 50Hz Pseudo-Non-Interlace (@2)	*/
    KM_DSPMODE_PALI320x480	    =	(KM_PAL  | KM_DSPMODE_INTERLACE          | KM_DSPMODE_320x480),		/* PAL  320x480 25Hz Interlace					*/
    KM_DSPMODE_PALNI640x480FF   =	(KM_PAL  | KM_DSPMODE_NONINTERLACE		 | KM_DSPMODE_640x480),		/* PAL  640x480 50Hz Non-Interlace FF     (@3)	*/
    KM_DSPMODE_PALNI640x480	    =	(KM_PAL  | KM_DSPMODE_PSEUDONONINTERLACE | KM_DSPMODE_640x480),		/* PAL  640x480 50Hz Pseudo-Non-Interlace (@2)	*/
    KM_DSPMODE_PALI640x480	    =	(KM_PAL  | KM_DSPMODE_INTERLACE          | KM_DSPMODE_640x480), 	/* PAL  640x480 25Hz Interlace					*/
    KM_DSPMODE_PALNI640x480FFEXT=	(KM_PAL  | KM_DSPMODE_NONINTERLACE		 | KM_DSPMODE_640x480_EXT),	/* PAL  640x480 50Hz Non-Interlace FF     (@3)	*/
    KM_DSPMODE_PALNI640x480EXT  =	(KM_PAL  | KM_DSPMODE_PSEUDONONINTERLACE | KM_DSPMODE_640x480_EXT),	/* PAL  640x480 50Hz Pseudo-Non-Interlace (@2)	*/
    KM_DSPMODE_PALI640x480EXT   =	(KM_PAL  | KM_DSPMODE_INTERLACE          | KM_DSPMODE_640x480_EXT) 	/* PAL  640x480 25Hz Interlace					*/
}KMDISPLAYMODE;

#define	KM_DSPMODE_VGA 		KM_DSPMODE_VGA640x480
/*
 * KMBPPMODE
 */
typedef enum {
    KM_DSPBPP_RGB565	= 0,
    KM_DSPBPP_RGB555	= 1,
    KM_DSPBPP_ARGB1555	= 3,
    KM_DSPBPP_RGB888	= 4,
    KM_DSPBPP_ARGB8888	= 5
}KMBPPMODE;

/*
 * PAL Extended mode Virtical Height
 */
typedef enum {
	KM_PALEXT_HEIGHT_RATIO_1_033 = 0,	/* 247 || 495 */
	KM_PALEXT_HEIGHT_RATIO_1_066 = 1,	/* 255 || 511 */
	KM_PALEXT_HEIGHT_RATIO_1_100 = 2,	/* 263 || 527 */
	KM_PALEXT_HEIGHT_RATIO_1_133 = 3,	/* 271 || 543 */
	KM_PALEXT_HEIGHT_RATIO_1_166 = 4,	/* 279 || 559 */
}KMPALEXTHEIGHT;

/*
 * DISPLAY Holizontal Level Adjust Mode for User Clipping.
 */
typedef enum _tagKMADJUSTTYPE
{
	KM_LEVEL_ADJUST_NORMAL,
	KM_LEVEL_ADJUST_HALF
}KMADJUSTTYPE;

/*
 * Virtical FilterMode. 480 line mode only.
 *
 *  NO_FILTER	 ... No use virtical filter
 *  NORMAL		 ... Use Virtical Filter.
 *  SQUARE_PIXEL ... Compress to square pixel.
 *
 */
typedef enum _tagKM_VIRTICAL_FILETERMODE
{
	KM_VIRTICAL_FILTER_NO_FILTER	= (0),
	KM_VIRTICAL_FILTER_NORMAL		= (1),
	KM_VIRTICAL_FILTER_SQUARE_PIXEL	= (2)
}KM_VIRTICAL_FILETERMODE;


/*
 * Display Information Index.
 */
typedef enum _tagKMDISPLAYINFO
{
	KMDISPLAYINFO_SCREEN_WIDTH,
	KMDISPLAYINFO_SCREEN_HEIGHT,
	KMDISPLAYINFO_SCREEN_BPPMODE,
	KMDISPLAYINFO_SCREEN_BITDEPTH,
	KMDISPLAYINFO_FRAMEBUFFER_WIDTH,
	KMDISPLAYINFO_FRAMEBUFFER_HEIGHT,
	KMDISPLAYINFO_FRAMEBUFFER_STRIDE_WIDTH,
	KMDISPLAYINFO_SCREEN_COORD_WIDTH,
	KMDISPLAYINFO_SCREEN_COORD_HEIGHT
}KMDISPLAYINFO,*PKMDISPLAYINFO;


/*
 *	SystemConfigration flags
 *         xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx 
 *                      |    |         |  |||   ||
 *                      |    |         |  |||   |+--- Enable FrameBuffer Clear 
 *                      |    |         |  |||   +---- Enable Strip Buffer.
 *                      |    |         |  ||+-------- Enable 2VLaytency Model.
 *                      |    |         |  |+--------- No Wait VSync.
 *                      |    |         |  +---------- Separate Each Vertex Buffer Base address.
 *                      |    |         +------------- Alignment Texture address 2K bytes boundary.
 *                      |    +----------------------- Reserved(deleted ; Useed in  Direct Mode. cf. kmXxxxXxxxDirect();)
 *                      +---------------------------- Enable DMAWait
 */
#define KM_CONFIGFLAG_ENABLE_CLEAR_FRAMEBUFFER	(0x00000001)	/* FrameBuffer: NoClear 					*/
#define KM_CONFIGFLAG_ENABLE_STRIPBUFFER		(0x00000002)	/* Enable Strip Buffer						*/
#define KM_CONFIGFLAG_ENABLE_2V_LATENCY			(0x00000010)	/* Enable 2V Latency						*/
#define KM_CONFIGFLAG_NOWAITVSYNC				(0x00000020)	/* No WaitVsync								*/
#define KM_CONFIGFLAG_SEPARATE_EACH_PASS		(0x00000040)	/* Separate Each Vertex Buffer Base address.*/
#define KM_CONFIGFLAG_ALIGN_TEXTURE_2K_BOUNDARY	(0x00000100)	/* Alignment Texture address 2K bytes boundary.*/
/*#define KM_CONFIGFLAG_USEDIRECTMODE			(0x00010000)*/	/* DirectMode was deleted from kamui2		*/
#define KM_CONFIGFLAG_NOWAIT_FINISH_TEXTUREDMA	(0x00100000)	/* Detect FinishTexDMA  					*/

/*
 * TEXTURE FORMAT TYPE
 */
#define KM_TEXTURE_TWIDDLED	            (0x0100)
#define KM_TEXTURE_TWIDDLED_MM	        (0x0200)
#define KM_TEXTURE_VQ	                (0x0300)
#define KM_TEXTURE_VQ_MM	            (0x0400)
#define KM_TEXTURE_PALETTIZE4	        (0x0500)
#define KM_TEXTURE_PALETTIZE4_MM	    (0x0600)
#define KM_TEXTURE_PALETTIZE8	        (0x0700)
#define KM_TEXTURE_PALETTIZE8_MM	    (0x0800)
#define KM_TEXTURE_RECTANGLE	        (0x0900)
#define KM_TEXTURE_RECTANGLE_MM	        (0x0A00)	/* Reserved : Can't use. */
#define KM_TEXTURE_STRIDE	            (0x0B00)
#define KM_TEXTURE_STRIDE_MM	        (0x0C00)	/* Reserved : Can't use. */
#define KM_TEXTURE_TWIDDLED_RECTANGLE   (0x0D00)
#define KM_TEXTURE_BMP                  (0x0E00)	/* Converted to Twiddled */
#define KM_TEXTURE_BMP_MM               (0x0F00)	/* Converted to Twiddled MM */
#define KM_TEXTURE_SMALLVQ              (0x1000)
#define KM_TEXTURE_SMALLVQ_MM           (0x1100)

/*
 * TEXTURE COLOR FORMAT
 */
#define KM_TEXTURE_ARGB1555             (0x00)
#define KM_TEXTURE_RGB565               (0x01)
#define KM_TEXTURE_ARGB4444             (0x02)
#define KM_TEXTURE_YUV422               (0x03)
#define KM_TEXTURE_BUMP                 (0x04)
#define KM_TEXTURE_RGB555               (0x05) 	/* for PCX compatible only.	*/
#define KM_TEXTURE_YUV420               (0x06) 	/* for YUV converter */

/*
 *  YUV Texture format code (for kmLoadYUVTexture)
 */
#define KM_TEXTURE_YUV_MULTI		(0x00000100)
#define KM_TEXTURE_YUV_SINGLE		(0x00000200)

/*
 * Surface Type:
 */
#define KM_SURFACETYPE_FRAMEBUFFER			1
#define KM_SURFACETYPE_TEXTURE				2
#define KM_SURFACETYPE_SMALLVQ_TEXTURE		3


/*
 * Palette Color Depth
 */
typedef enum{
	KM_PALETTE_16BPP_ARGB1555,
	KM_PALETTE_16BPP_RGB565,
	KM_PALETTE_16BPP_ARGB4444,
	KM_PALETTE_32BPP_ARGB8888
}KMPALETTEMODE;

/*
 * Palette Entry Size for kmSetPaletteBank
 */
typedef enum {
    KM_PALETTE_ENTRY_16		= 16,
    KM_PALETTE_ENTRY_256	= 256
} KMPALETTE_ENTRY_SIZE;

/*
 * Pass Information.
 */
#define KM_PASSINFO_AUTOSORT				(0x00)
#define KM_PASSINFO_PRESORT					(0x01)
#define KM_PASSINFO_ENABLE_Z_CLEAR			(0x00)
#define KM_PASSINFO_DISABLE_Z_CLEAR			(0x02)

#define KM_PASSINFO_USE_ANOTHERLIST			(0x80)		/* kmUseAnotherModifier(); for each pass 					*/
#define KM_PASSINFO_UA_TRMOD_AS_OPMOD		(0x10)		/* translucent modifier use as opaque modifier.				*/
#define KM_PASSINFO_UA_OPMOD_AS_TRMOD		(0x20)		/* opaque modifier use as translucent modifier.				*/
#define KM_PASSINFO_UA_DISCADING_TRANSPOLY	(0x40)		/* discarding translucent polygon by PunchThrough Polygon 	*/

/*
 * Object Pointer Block Allocator Control Parameter.
 */
typedef enum _tagKMOPBMODE{
	KM_OPB_ALLOCCTRL_NOLIST		=	(0x0),
	KM_OPB_ALLOCCTRL_SMALL		=	(0x01),
	KM_OPB_ALLOCCTRL_NORMAL		=	(0x02),
	KM_OPB_ALLOCCTRL_LARGE		=	(0x03)
}KMOPBMODE;

/*
 * For kmGenerateFogTable
 */
#define		KM_FOGTYPE_NONE			0	/* NO FOG */
#define		KM_FOGTYPE_LINEAR		1	/* LINEAR FOG */
#define		KM_FOGTYPE_EXPONENTIAL	2	/* EXPONENTIAL FOG : f = e ^ -( density * z ) */
#define		KM_FOGTYPE_EXPONENTIAL2	3	/* EXPONENTIAL SQUARED FOG : f = e ^ -( density * z )^2 */

/*
 *	kmRender Flags
 */
#define KM_RENDER_FLIP  	(0)
#define KM_RENDER_NOFLIP	(1)

/*
 * KMLISTTYPE
 */
typedef	enum
{
    KM_OPAQUE_POLYGON		=0,	    /*	Opaque Polygon				*/
    KM_OPAQUE_MODIFIER		=1,	    /*	Opaque Modifier Volume		*/
    KM_TRANS_POLYGON		=2,	    /*	Translucent Polygon			*/
    KM_TRANS_MODIFIER		=3,	    /*	Translucent Modifier Volume	*/
	KM_PUNCHTHROUGH_POLYGON	=4		/*  PunchThrough Polygon		*/
} KMLISTTYPE;

/*
 * Latency Model
 */
typedef	enum
{
    KM_LATENCYMODEL_3V =0,     /*  3V Latency Model(Default)	*/
    KM_LATENCYMODEL_2V =1      /*  2V Latency Model			*/
} KMLATENCYMODEL;

/*
 * VertexBuffer Model
 */
typedef	enum
{
	KM_VERTEXBUFMODEL_NORMAL 					= 0x00,
	KM_VERTEXBUFMODEL_NOBUF_OPAQUE_POLYGON 		= (0x20 | KM_OPAQUE_POLYGON		),
	KM_VERTEXBUFMODEL_NOBUF_OPAQUE_MODIFIER  	= (0x20 | KM_OPAQUE_MODIFIER	),
	KM_VERTEXBUFMODEL_NOBUF_TRANS_POLYGON		= (0x20 | KM_TRANS_POLYGON		),
	KM_VERTEXBUFMODEL_NOBUF_TRANS_MODIFIER  	= (0x20 | KM_TRANS_MODIFIER		),
	KM_VERTEXBUFMODEL_NOBUF_PUNCH_THROUGH 	 	= (0x20 | KM_PUNCHTHROUGH_POLYGON)
} KMVERTEXBUFMODEL;

/*
 * Vertex List Status.
 */
#define KM_VERTEX_LIST_MASK_SCENE_STATE			(0x00000003)
#define	KM_VERTEX_LIST_BEFORE_BEGINING_SCENE	(0x00000000)	/* before kmBeginScene(); 						 */
#define	KM_VERTEX_LIST_UNDERCONSTRUCT_SCENE		(0x00000001)	/* after  kmBeginScene(); to before kmRender();  */
#define	KM_VERTEX_LIST_LAUNCHED_SCENE			(0x00000002)	/* after  kmRender();     to before kmEndScene();*/

#define KM_VERTEX_LIST_SUPRESS_TEXTURE_DMA_MASK	(0x00000004)
#define KM_VERTEX_LIST_SUPRESS_TEXTURE_DMA		(0x00000004)	/* Suppress Async copy from kmBeginPass to kmEndPass in 2VLatency */

/*
 * Get System Metrics Command 
 */
#define KMSYSTEMMETRICS_VERTEXBUFFER_INFO		(0x00000001)
#define KMSYSTEMMETRICS_RENDERPERFORM_INFO		(0x00000002)
#define KMSYSTEMMETRICS_TIMEOUT_INFO			(0x00000004)
#define KMSYSTEMMETRICS_FRAMEBUFFER_INFO		(0x00000008)
#define KMSYSTEMMETRICS_NATIVE_INFO				(0x00000010)

/*
 * Define Fatal Error Reason.
 * -------------------------
 * means of KMFATALERRORDATA.dwReason:
 *
 * xxxx xxxx xxxx xxxx xxxx xxxx xxxx xxxx 
 *                                     |||
 *                                     +++- error reason?
 *
 */
#define KM_FATAL_ERR_NOQEUE_INTR		(0x01)		/* DMA was requested but DMA Queue isn't left.    */
#define KM_FATAL_ERR_OVERFLW_VTXBUF		(0x02)		/* Display list have over flowed in vertex buffer.*/
#define KM_FATAL_ERR_TOO_MANY_VTX		(0x03)		/* Too many Vertex,Native buffer overflow.		  */
#define KM_FATAL_ERR_V_NOT_RESPOND		(0x04)		/* V-Sync Interrupt                               */

#ifdef __cplusplus
}
#endif 

#endif /*  __kamui_enum_h	*/

