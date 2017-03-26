/*
     PLIB - A Suite of Portable Game Libraries
     Copyright (C) 2001  Steve Baker
 
     This library is free software; you can redistribute it and/or
     modify it under the terms of the GNU Library General Public
     License as published by the Free Software Foundation; either
     version 2 of the License, or (at your option) any later version.
 
     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Library General Public License for more details.
 
     You should have received a copy of the GNU Library General Public
     License along with this library; if not, write to the Free
     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 
     For further information visit http://plib.sourceforge.net

     $Id: sgIsect.cc,v 1.1 2002/02/03 05:32:43 bardtx Exp $
*/


#include <dcplib/sg.h>

/*
  Determine the origin and unit direction vector of a line
  formed by the intersection of two planes.
  Returned point will lie on axis that was used to
  determine intersection.
         Norman Vine - nhv@yahoo.com
*/

int sgIsectPlanePlane ( sgVec3 point, sgVec3 dir,
                        sgVec4 plane1, sgVec4 plane2 )
{
  /* Determine intersection line direction. */

  sgVectorProductVec3 ( dir, plane1, plane2 ) ;

  SGfloat dnorm = sgLengthVec3 ( dir ) ;

  /* If planes are parallel then fail */

  if ( dnorm < FLT_EPSILON )
  {
    sgZeroVec3 ( point ) ;
    sgZeroVec3 ( dir   ) ;
    return false ;
  }

  /* Determine intersection point with the best suited coordinate plane. */

  SGfloat abs ;
  SGfloat maxabs = sgAbs(dir[0]);
  int index = 0;

  if ((abs = sgAbs(dir[1])) > maxabs) { maxabs = abs ; index = 1; }
  if ((abs = sgAbs(dir[2])) > maxabs) { maxabs = abs ; index = 2; }

  switch ( index )
  {
    case 0:
      sgSetVec3( point,
             SG_ZERO,
             (plane1[2] * plane2[3] - plane2[2] * plane1[3]) / dir[0],
             (plane2[1] * plane1[3] - plane1[1] * plane2[3]) / dir[0] );
      break;
    case 1:
      sgSetVec3( point,
             (plane2[2] * plane1[3] - plane1[2] * plane2[3]) / dir[1],
             SG_ZERO,
             (plane1[0] * plane2[3] - plane2[0] * plane1[3]) / dir[1] );
      break;
    case 2:
      sgSetVec3( point, 
             (plane1[1] * plane2[3] - plane2[1] * plane1[3]) / dir[2],
             (plane2[0] * plane1[3] - plane1[0] * plane2[3]) / dir[2],
             SG_ZERO );
      break;
    default: return false ;  /* Impossible */
  }

  /* Normalize the direction */

  sgScaleVec3( dir, SG_ONE / dnorm );
  return true;
}



/*
   Find the intersection of an infinite line with a plane
   (the line being defined by a point and direction).

   Norman Vine -- nhv@yahoo.com  (with hacks by Steve)
*/

int sgIsectInfLinePlane( sgVec3 dst, sgVec3 l_org, sgVec3 l_vec, sgVec4 plane )
{
  SGfloat tmp = sgScalarProductVec3 ( l_vec, plane ) ;

  /* Is line parallel to plane? */

  if ( sgAbs ( tmp ) < FLT_EPSILON )
    return false ;
 
  sgScaleVec3 ( dst, l_vec, -( sgScalarProductVec3 ( l_org, plane )
                                                + plane[3] ) / tmp ) ;
  sgAddVec3  ( dst, l_org ) ;

  return true ;
}



/*
  Given the origin and direction vector for two lines
  find their intersection - or the point closest to
  both lines if they don't intersect.

  Norman Vine -- nhv@yahoo.com
*/

int sgIsectInfLineInfLine( sgVec3 dst,
           sgVec3 l1_org, sgVec3 l1_vec,
           sgVec3 l2_org, sgVec3 l2_vec )
{
  sgVec3 vec_l1, vec_l2 ;

  sgNormalizeVec3 ( vec_l1, l1_vec ) ;
  sgNormalizeVec3 ( vec_l2, l2_vec ) ;

  /* Connecting line 'C' is perpendicular to both */

  sgVec3 perp ;
  sgVectorProductVec3 ( perp, vec_l1, vec_l2 ) ;

  /* check for near-parallel lines */

  SGfloat dist = sgScalarProductVec3 ( perp, perp ) ;

  if ( dist < FLT_EPSILON )
  {
    /* degenerate: lines parallel - any point will do. */

    sgCopyVec3 ( dst, l2_org ) ;
    return true ;
  }
  
  /*
    Form a plane containing the line A and C,
    and another containing B and C
  */

  sgScaleVec3 ( perp, SG_ONE / sgSqrt( dist ) ) ;
 
  sgVec4 pa ;
  sgVec4 pb ;
  sgVec3 tmp ;

  sgVectorProductVec3 ( tmp, perp, vec_l1 ) ;
  sgNormalizeVec3     ( tmp );
  sgMakePlane         ( pa, tmp, l1_org ) ;

  sgVectorProductVec3 ( tmp, perp, vec_l2 ) ;
  sgNormalizeVec3     ( tmp );
  sgMakePlane         ( pb, tmp, l2_org ) ;

  sgVec3 tmp_org, tmp_vec ;

  if ( ! sgIsectPlanePlane( tmp_org, tmp_vec, pa, pb ) )
  {
    /* This *shouldn't* ever happen because we already
      tested for parallel lines - but with roundoff
      errors, it *might* in borderline cases so...
    */

    sgCopyVec3 ( dst, l2_org ) ;
    return false ;
  }
 
  if ( ! sgIsectInfLinePlane ( dst, l2_org, vec_l2, pa ) )
  {
    sgCopyVec3 ( dst, l2_org ) ;
    return false ;
  }

  return true ;
}


/*
  Intersect the line segment from v1->v2 with the 'plane'.
  'dst' is the intersection point and the return
  result is in the range 0..1 if the intersection lies
  between v1 and v2, >1 if beyond v2 and <0 if before v1.
  FLT_MAX is returned if the vector does not intersect
  the plane.

  Steve Baker
*/

SGfloat sgIsectLinesegPlane ( sgVec3 dst, sgVec3 v1, sgVec3 v2, sgVec4 plane )
{
  sgVec3 delta ;

  sgSubVec3 ( delta, v2, v1 ) ;

  SGfloat p = sgScalarProductVec3 ( plane, delta ) ;

  if ( p == SG_ZERO )
  {
    dst [ 0 ] = dst [ 1 ] = dst [ 2 ] = FLT_MAX ;
    return FLT_MAX ;
  }

  float s = - ( sgScalarProductVec3 ( plane, v1 ) + plane[3] ) / p ;

  sgScaleVec3 ( dst, delta, s ) ;
  sgAddVec3   ( dst, dst, v1 ) ;

  return s ;
}


