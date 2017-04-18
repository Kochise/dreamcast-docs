/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1996-1997 Microsoft Corporation

Module Name:

    d3dmath.h

Abstract:

   Useful 2D and 3D math functions for graphics.

Environment:

    Dragon OS and Windows 95.

-------------------------------------------------------------------*/
#ifndef __D3DMATH_H__
#define __D3DMATH_H__

#include <d3d.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif


#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/*
 * Normalizes the vector v
 */
LPD3DVECTOR
D3DVECTORNormalize(
    LPD3DVECTOR v
    );

/*
 * Calculates cross product of a and b.
 */
LPD3DVECTOR
D3DVECTORCrossProduct(
    LPD3DVECTOR lpd,
    LPD3DVECTOR lpa,
    LPD3DVECTOR lpb
    );

/*
 * lpDst = lpSrc1 * lpSrc2
 * lpDst can be equal to lpSrc1 or lpSrc2
 */
LPD3DMATRIX
MultiplyD3DMATRIX(
    LPD3DMATRIX lpDst,
    LPD3DMATRIX lpSrc1,
    LPD3DMATRIX lpSrc2
    );

/*
 * Set the rotation part of a matrix such that the vector lpD is the new
 * z-axis and lpU is the new y-axis.
 */
LPD3DMATRIX
D3DMATRIXSetRotation(
    LPD3DMATRIX lpM,
    LPD3DVECTOR lpD,
    LPD3DVECTOR lpU
    );

/*
 * Calculates a point along a B-Spline curve defined by four points. p
 * n output, contain the point. t                Position
 * along the curve between p2 and p3.  This position is a float between 0
 * and 1. p1, p2, p3, p4    Points defining spline curve. p, at parameter
 * t along the spline curve
 */
void
spline(
    LPD3DVECTOR p,
    float t,
    LPD3DVECTOR p1,
    LPD3DVECTOR p2,
    LPD3DVECTOR p3,
    LPD3DVECTOR p4
    );



/*
 * Subtracts point B from point A giving Vector V
 */
LPD3DVECTOR
D3DVECTORSubtract(
    LPD3DVECTOR  lpV,
    LPD3DVECTOR  lpA,
    LPD3DVECTOR  lpB
    );


/*
* Transposes the matrix.  Equivalent to inversion for pure rotation matrices
*/
LPD3DMATRIX
D3DMATRIXTranspose(
    LPD3DMATRIX d,
    LPD3DMATRIX a
);

/*
 * Sets the viewing matrix such that
 * from is at the origin
 * at   is on the positive Z axis
 * up is in the Y-Z plane
 */
LPD3DMATRIX
D3DMATRIXSetView(
    LPD3DMATRIX lpM,
    LPD3DVECTOR lpFrom,
    LPD3DVECTOR lpAt,
    LPD3DVECTOR lpUp
    );

/*
 * Rotation of angle radians about an arbitrary axis.
 */
LPD3DMATRIX
D3DMATRIXSetVRotation(
    LPD3DMATRIX lpM,
    LPD3DVECTOR lpAxis,
    double    angle
    );

/*
 * Set a projection matrix with the given
 * near and far clipping planes in viewing units
 * the fov angle in RADIANS
 * and aspect ratio
 */
LPD3DMATRIX
D3DMATRIXSetProjection(
    LPD3DMATRIX lpM,
    D3DVALUE dvN,
    D3DVALUE dvf,
    double   fov,
    D3DVALUE dvAspect
    );


/*
* Set a scale matrix
*/
LPD3DMATRIX
D3DMATRIXSetScale(
    LPD3DMATRIX lpM,
    D3DVALUE    dvXScale,
    D3DVALUE    dvYScale,
    D3DVALUE    dvZScale
    );

/*
*   Returns the magnitude (length) of a vector
*/
D3DVALUE
DVMagnitude(
    LPD3DVECTOR pV
    );
/*
 * Gets the scale factors from a matrix
 */
void
GetScale(
    LPD3DMATRIX lpM,
    D3DVALUE *pdvXScale,
    D3DVALUE *pdvYScale,
    D3DVALUE *pdvZScale
    );


LPD3DVECTOR
VMMultiply(
    LPD3DVECTOR pvDst,
    LPD3DVECTOR pvSrc,
    LPD3DMATRIX pM
    );

void SetRotateXMatrix( D3DMATRIX& mat, FLOAT fRads );
void SetRotateYMatrix( D3DMATRIX& mat, FLOAT fRads );
void SetRotateZMatrix( D3DMATRIX& mat, FLOAT fRads );

#ifdef __cplusplus
};
#endif

#endif // __D3DMATH_H__

