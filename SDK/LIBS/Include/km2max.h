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
  Module Name:		km2max.h

  Abstract:
	Kamui2 is Low-Level PowerVR Driver.
	'km2max.h' defines the maximum values to use in kamui2 system.

  Environment:
	ANSI C Compiler.

  Notes:
	kamui2 system limitations.

  Revision History:

--*/
#if !defined(__km2maxlimit_h_)
#define __km2maxlimit_h_
/*
 * Maximum Values.
 */

#define	KM_MAX_DISPLAY_LIST				(5)

/*
 * Maximum Display List
 *	Opaque Polygon.
 *	Opaque Modifier
 *	Translucent Polygon
 *	Translucent Modifier
 *	Punchthrough Polygon
 */
#define	KM_MAX_DISPLAY_LIST_PASS		(8)

/*
 * Maximum of Vertex Buffer.
 *#Does anyone use 8 vertex buffer?
 */
#define	KM_MAX_VERTEX_BUFFER			(8)

/*
 * Kamui2 allow quadrupe buffer.
 */
#define	KM_MAX_FRAME_BUFFER				(4)

/*
 * Native Buffer
 */
#define KM_MAX_NATIVE_BUFFER 			(2)

/*
 * Palette entry count.
 */
#define KM_PALETTE_ENTRY 				(1024)

/*
 * Fog Table Entry.
 */
#define KM_FOG_ENTRY					(128)


/*
 * KM_MAX_RENDER_TIME is prepared for KMSYSTEMMETRICS structure.
 * KMSYSTEMMETRICS stores up to preserve renderring time in 8 times of the pasts
 */
#define KM_MAX_RENDER_TIME				(8)

#endif
