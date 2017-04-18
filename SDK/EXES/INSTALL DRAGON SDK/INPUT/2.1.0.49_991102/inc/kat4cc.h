/*==========================================================================;
 *
 *  Copyright (c) 1998 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       kat4cc.h
 *  Content:    Katana-specific FourCC codes for DirectDraw
 *
 ***************************************************************************/

#ifndef __KAT4CC_INCLUDED__
#define __KAT4CC_INCLUDED__


//
// UYVY: Video-memory only 422 (16bpp) surface with direct R/W access 
// upon locking
//
#define FOURCC_UYVY  MAKEFOURCC('U', 'Y', 'V', 'Y')

//
// DCY0 (katana-specific format): System-memory 420 (12bpp) 
// READ-ONLY surface which copies the entire frame loaded over to a 
// standard (UYVY-style) video memory surface upon unlocking
//
#define FOURCC_DCY0  MAKEFOURCC('D', 'C', 'Y', '0')

//
// PNBM (katana-specific format):
// Perturbed normal bump map.
//
#define FOURCC_PNBM	 MAKEFOURCC('P', 'N', 'B', 'M')

#endif  // !__KAT4CC_INCLUDED__

