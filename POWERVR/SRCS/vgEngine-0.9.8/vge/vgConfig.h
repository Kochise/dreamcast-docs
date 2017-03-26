//
// C++ Interface: vgConfig
//
// Description: Build Configuration, you can switch on/off some vgEngine features here.
//
//
// Author: Marian Krivos <nezmar@tutok.sk>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

/**
 * 0 = position of the point(0,0) is in bottom-left corner
 * 1 = position of the point(0,0) is in top-left corner
 * default is 0
 */ 
#define VGE_CONFIG_Y_GROWS_TO_DOWN      0

/**
 * 0 = vgEngine doesn't support dashed lines (faster rendering)
 * 1 = vgEngine does support dashed lines (slow rendering)
 * default is 1
 */ 
#define VGE_CONFIG_DASHED_LINE          1

/**
 * 0 = vertices doesn't try 'shorten path' optimization pass in the rasterizer
 * 1 = the path does try 'shorten path' optimization pass in the rasterizer
 * default is 1
 */ 
#define VGE_CONFIG_SHORTEN_PATH         1

/**
 * 0 = pixel blending is hard-wired to 'alpha blending' (faster rendering)
 * 1 = 1 pixel blending is controlled by vgBlendMode() function (slower rendering)
 * default is 0
 */ 
#define VGE_CONFIG_COMP_OP              0   

/**
 * 0 = text drawing (TTF) via 'freetype' library is disabled
 * 1 = text drawing (TTF) via 'freetype' library is enabled
 * default is 1
 */ 
#define VGE_CONFIG_FREETYPE             1
