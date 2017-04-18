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
  Module Name:		kmstatus.h

  Abstract:
	KAMUI = Kamui is Abstruction Model that is Ultimate Interface for PowerVR.
	'kmstatus.h' is kamui status header.

  Environment:

  Notes:
	KMSTATUS_XXXXX style

  Revision History:

--*/
#if !defined(__kamui_status_h)
#define __kamui_status_h

typedef enum _tagKMSTATUS{
/*
 * Kamui Function result is OK. means NO ERROR.
 */
		KMSTATUS_SUCCESS                     		= 0L	,


/*
 *	
 */
		KMSTATUS_INVALID_DISPLAY_MODE        		= 1L	,

/*
 *
 */
		KMSTATUS_INVALID_VIDEO_MODE        			= 2L	,

/*
 *
 */
		KMSTATUS_NOT_ENOUGH_MEMORY           		= 3L	,

/*
 * 
 */
		KMSTATUS_INVALID_TEXTURE_TYPE				= 4L	,

/*
 * 
 */
		KMSTATUS_INVALID_MIPMAPED_TEXTURE			= 5L	,

/*
 * 
 */
		KMSTATUS_CANT_FLIP_SURFACE					= 6L	,

/*
 * 
 */
		KMSTATUS_INVALID_ADDRESS					= 7L	,

/*
 * 
 */
		KMSTATUS_HARDWARE_NOT_PRESENTED				= 8L	,


/*
 * 
 */
		KMSTATUS_INVALID_SETTING					= 9L	,

/*
 * 
 */
		KMSTATUS_INVALID_VERTEX_TYPE				= 10L	,

/*
 * Vertex List type.
 */
		KMSTATUS_INVALID_LIST_TYPE					= 11L	,

/*
 * for kmLoadTextureBlock
 */
		KMSTATUS_INVALID_BLOCKNUMBER				= 12L	,

/*
 * for kmQueryFinishFlushVertexBuffer
 */
		KMSTATUS_LAST_LIST_UNDER_DMA				= 13L	,

/*
 * for kmActivateFrameBuffer
 */
		KMSTATUS_INVALID_SURFACE					= 14L	,
		KMSTATUS_INVALID_SURFACE_TYPE				= 15L	,
		KMSTATUS_INVALID_SURFACE_SIZE				= 16L	,

/*
 * for kmQueryFinishLastTextureDMA
 */
		KMSTATUS_NOT_FINISH_DMA						= 17L	,

/*
 * passed value is out of range. 
 */
		KMSTATUS_OUT_OF_RANGE						= 18L	,

/*
 * KAMUI Rendering Status
 */
		KMSTATUS_UNDER_RENDER						= 102L	,
		KMSTATUS_FINISH_RENDER						= 103L	,
		KMSTATUS_UNDER_DISPLAY						= 104L	,
		KMSTATUS_FINISH_ALL_SEQUENCE				= 105L	,

/*
 * called function is not implemented.
 */
		KMSTATUS_NOT_IMPLEMENTED					= 120L	,

/*
 * KAMUI DMA Routine Status.
 */
		KMSTATUS_UNDER_DMA							= 0x0100	,
		KMSTATUS_FINISH_DMA							= 0x0101	,
		KMSTATUS_DMA_BUSY							= 0x0102	,
		KMSTATUS_QUEUE_EMPTY						= 0x0103	,

/*
 * Invalid parameter ... temporary error code....
 *	玉虫色のエラーコードだから、将来は破棄する。
 */
		KMSTATUS_INVALID_PARAMETER					= 0x0ddddL	,
		KMSTATUS_ERROR								= 0x0eeeeL

}KMSTATUS;
#endif
