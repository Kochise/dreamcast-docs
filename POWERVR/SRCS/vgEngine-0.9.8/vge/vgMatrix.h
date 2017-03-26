//
// C++ Interface: vgMatrix
//
// Description: 
//
//
// Author: root <root@majo>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "agg_trans_affine.h"

/**
 *  @ingroup matrix
 *  @{
 *  VGMatrix is used throughout vgEngine to convert between different coordinate spaces. 
 *  A VGMatrix holds an affine transformation, such as a scale, rotation or a combination of these. 
 *  The transformation of a point (x,y) is given by: 
 *  @code
 *  x_new = xx * x + xy * y + x0;
 *  y_new = yx * x + yy * y + y0;
 *  @endcode
 *  The current transformation matrix of a vgEngine, represented as a VGMatrix,
 *  defines the transformation from user-space coordinates to device-space coordinates. 
 *  @}
 */ 
typedef agg::trans_affine VGMatrix;
