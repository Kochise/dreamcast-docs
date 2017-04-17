/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (C) 1998 Microsoft Corporation. All Rights Reserved.

Module Name:

    d3dmath.c

Abstract:

    File ripped from util directory.  Eventually D3DStrip will just
    include the appropriate library.

-------------------------------------------------------------------*/

#include "d3dmath.hpp"


#ifdef DEBUG

#define assert(a) if (!(a)) { DebugBreak();}

#else

#define assert(a)

#endif

extern D3DMATRIX           g_matIdent;               // Global identity matrix.

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    D3DVECTORNormalize

Description:

    Normalizes the vector v to unit length.
    If the vector is degenerate the same vector is returned.

Arguments:

    pV -  Vector to normalize

Return Value:
    Pointer to the vector passed in.

-------------------------------------------------------------------*/
LPD3DVECTOR
D3DVECTORNormalize(
    LPD3DVECTOR pV
    )
{
    float vx, vy, vz, inv_mod;

    assert(pV != NULL);

    vx = pV->x;
    vy = pV->y;
    vz = pV->z;

    if ((vx != 0) || (vy != 0) || (vz != 0)) {
        inv_mod = (float)(1.0f / (float)sqrt(vx * vx + vy * vy + vz * vz));
        pV->x = vx * inv_mod;
        pV->y = vy * inv_mod;
        pV->z = vz * inv_mod;
    }
    return pV;
}


/*
 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    D3DVECTORCrossProduct

Description:

    Calculates cross product of vectors A and B.  D = A x B

Arguments:

    pD -  Pointer to vector to receive result

    pA -  Pointer to vector A

    pB -  Pointer to vector B

Return Value:

    Pointer to result - pD

-------------------------------------------------------------------*/
LPD3DVECTOR
D3DVECTORCrossProduct(
    LPD3DVECTOR pD,
    LPD3DVECTOR pA,
    LPD3DVECTOR pB
    )
{

    assert(pD != NULL);
    assert(pA != NULL);
    assert(pB != NULL);

    pD->x = pA->y * pB->z - pA->z * pB->y;
    pD->y = pA->z * pB->x - pA->x * pB->z;
    pD->z = pA->x * pB->y - pA->y * pB->x;
    return pD;
}


typedef D3DVALUE MYMAT[4][4];
typedef MYMAT *PMYMAT;

typedef D3DVALUE MYVEC[3];
typedef MYVEC *PMYVEC;

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    MultiplyD3DMATRIX

Description:

    Concatenates two 4x4 matricies together to form a combined tranform matrix.
    pDst = pSrc1 * pSrc2

Arguments:

    pDst  -  Pointer to matrix to receive the result.
              lpDst can be equal to lpSrc1 or lpSrc2

    pSrc1 -  Pointer to first matrix operand

    pSrc2 -  Pointer to second matrix operand


Return Value:

   Pointer to result - pDst
-------------------------------------------------------------------*/
LPD3DMATRIX
MultiplyD3DMATRIX(
    LPD3DMATRIX pDst,
    LPD3DMATRIX pSrc1,
    LPD3DMATRIX pSrc2
    )
{
    PMYMAT pM1 = (PMYMAT)pSrc1;
    PMYMAT pM2 = (PMYMAT)pSrc2;
    MYMAT D;

    int i, r, c;

    assert(pSrc1 != NULL);
    assert(pSrc2 != NULL);
    assert(pDst != NULL);

    for (r = 0; r < 4; r++) {
        for (c = 0; c < 4; c++) {
            D[r][c] = (float)0.0;
            for (i = 0; i < 4; i++)
                D[r][c] += (*pM1)[r][i] * (*pM2)[i][c];
        }
    }
    memcpy(pDst, D, sizeof(D3DMATRIX));

    return pDst;
}



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    VMMultiply

Description:

    Multiplies a 3D vector with a 4x4 matrix to generate a transformed vector.
    pvDst = pvSrc * pM

Arguments:

    pvDst - Pointer to vector to receive the result.  May be the same as pvSrc

    pvSrc - Pointer to vector to transform

    pM    - Pointer to 4x4 matrix to transform the vector

Return Value:

   Pointer to result - pvDst
-------------------------------------------------------------------*/
LPD3DVECTOR
VMMultiply(
    LPD3DVECTOR pvDst,
    LPD3DVECTOR pvSrc,
    LPD3DMATRIX pM
    )
{
    PMYMAT pmymat = (PMYMAT)pM;
    MYVEC D;
    PMYVEC pvsrc = (PMYVEC) pvSrc;
    int i, r;

    assert(pvDst != NULL);
    assert(pvSrc != NULL);
    assert(pM != NULL);

    for (r = 0; r < 3; r++) {
        D[r] = D3DVAL(0.0);
        for (i = 0; i < 3; i++)
            D[r] += (*pvsrc)[i] * (*pmymat)[i][r];
    }
    memcpy(pvDst, D, sizeof(D3DVECTOR));
    return pvDst;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    D3DMATRIXSetRotation

Description:

    Set the rotation part of a matrix such that the vector lpD is the new
    z-axis and lpU is the new y-axis.
    NOTE:  The function only modifies the upper left 3x3 of the matrix.  Row 4 and column 4 are untouched.

Arguments:

    pM - Pointer to matrix to be modified.

    pD - Pointer to a vector defining the Z-axis (Direction)

    pU - Pointer to a vector defining the Y- Axis (Up)

Return Value:

   Pointer to the new matrix - pM

-------------------------------------------------------------------*/
LPD3DMATRIX
D3DMATRIXSetRotation(
    LPD3DMATRIX pM,
    LPD3DVECTOR pD,
    LPD3DVECTOR pU
    )
{
    float t;
    D3DVECTOR d, u, r;

    assert(pM != NULL);
    assert(pD != NULL);
    assert(pU != NULL);

    /*
     * Normalize the direction vector.
     */
    d.x = pD->x;
    d.y = pD->y;
    d.z = pD->z;
    D3DVECTORNormalize(&d);

    u.x = pU->x;
    u.y = pU->y;
    u.z = pU->z;
    /*
     * Project u into the plane defined by d and normalize.
     */
    t = u.x * d.x + u.y * d.y + u.z * d.z;
    u.x -= d.x * t;
    u.y -= d.y * t;
    u.z -= d.z * t;
    D3DVECTORNormalize(&u);

    /*
     * Calculate the vector pointing along the matrix x axis (in a right
     * handed coordinate system) using cross product.
     */
    D3DVECTORCrossProduct(&r, &u, &d);

    pM->_11 = r.x;
    pM->_12 = r.y;
    pM->_13 = r.z;

    pM->_21 = u.x;
    pM->_22 = u.y;
    pM->_23 = u.z;

    pM->_31 = d.x;
    pM->_32 = d.y;
    pM->_33 = d.z;

    return pM;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    spline

Description:

    Calculates a point along a cubic B-Spline curve.


    NOTE:  Points and vectors should be different types because they are mathematically distinct but
           D3D does not have that concept so D3DVECTOR is used to represent points.

Arguments:

    p -  Pointer to the point

    t -  Position along the spline

    p1 - First control point

    p2 - Second control point

    p3 - Third control point

    p4 - Fourth control point

-------------------------------------------------------------------*/
void
spline(
    LPD3DVECTOR p,
    float t,
    LPD3DVECTOR p1,
    LPD3DVECTOR p2,
    LPD3DVECTOR p3,
    LPD3DVECTOR p4
    )
{
    float t2, t3;
    float m1, m2, m3, m4;

    assert(p != NULL);
    assert(p1 != NULL);
    assert(p2 != NULL);
    assert(p3 != NULL);
    assert(p4 != NULL);
//    assert(t >= 0.0);
    assert(t <= 1.0f);

    t2 = t * t;
    t3 = t2 * t;

    m1 = (float)((-1.0f * t3) + ( 2.0f * t2) + (-1.0f * t));
    m2 = (float)(( 3.0f * t3) + (-5.0f * t2) + ( 0.0f * t) + 2.0f);
    m3 = (float)((-3.0f * t3) + ( 4.0f * t2) + ( 1.0f * t));
    m4 = (float)(( 1.0f * t3) + (-1.0f * t2) + ( 0.0f * t));

    m1 /= 2.0f;
    m2 /= 2.0f;
    m4 /= 2.0f;

    p->x = p1->x * m1 + p2->x * m2 + p3->x * m3 + p4->x * m4;
    p->y = p1->y * m1 + p2->y * m2 + p3->y * m3 + p4->y * m4;
    p->z = p1->z * m1 + p2->z * m2 + p3->z * m3 + p4->z * m4;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    D3DMATRIXSetProjection

Description:

    Set a projection matrix with the given
    near and far clipping planes in viewing units
    the fov angle in RADIANS
    and aspect ratio

    Destroys the current contents of the destination matrix.

Arguments:

    OUT pM      -   Matrix to receive projection matrix

    IN  dvNear   -  Distance to near clipping plane

    IN  dvFar    -  Distance to far clipping plane

    IN  fov      -  whole field of view angle in radians

    IN  dvAspect -  The aspect ratio Y/X of the viewing plane

Return Value:

    pM

-------------------------------------------------------------------*/
LPD3DMATRIX
D3DMATRIXSetProjection(
    LPD3DMATRIX pM,
    D3DVALUE    dvNear,
    D3DVALUE    dvFar,
    double      fov,
    D3DVALUE    dvAspect
)
{
    D3DVALUE dvTfov   = D3DVAL((float)tan((float)fov/2.0f));
    D3DVALUE dvFFN   = dvFar / (dvFar - dvNear);

    assert(pM);

    pM->_11 = D3DVAL(1.0);
    pM->_12 = D3DVAL(0.0);
    pM->_13 = D3DVAL(0.0);
    pM->_14 = D3DVAL(0.0);

    pM->_21 = D3DVAL(0.0);
    pM->_22 = D3DVAL(1/dvAspect);
    pM->_23 = D3DVAL(0.0);
    pM->_24 = D3DVAL(0.0);

    pM->_31 = D3DVAL(0.0);
    pM->_32 = D3DVAL(0.0);
    pM->_33 = dvTfov * dvFFN;
    pM->_34 = dvTfov;

    pM->_41 = D3DVAL(0.0);
    pM->_42 = D3DVAL(0.0);
    pM->_43 = -dvNear * dvTfov * dvFFN;
    pM->_44 = D3DVAL(0.0);

    return pM;
}


//-----------------------------------------------------------------------------
// Name: SetRotateXMatrix()
// Desc: Create Rotation matrix about X axis
//-----------------------------------------------------------------------------
VOID SetRotateXMatrix( D3DMATRIX& mat, FLOAT fRads )
{
    mat = g_matIdent;
    mat._22 =  (FLOAT)cos( fRads );
    mat._23 =  (FLOAT)sin( fRads );
    mat._32 = -(FLOAT)sin( fRads );
    mat._33 =  (FLOAT)cos( fRads );
}




//-----------------------------------------------------------------------------
// Name: SetRotateYMatrix()
// Desc: Create Rotation matrix about Y axis
//-----------------------------------------------------------------------------
void SetRotateYMatrix( D3DMATRIX& mat, FLOAT fRads )
{
    mat = g_matIdent;
    mat._11 =  (FLOAT)cos( fRads );
    mat._13 = -(FLOAT)sin( fRads );
    mat._31 =  (FLOAT)sin( fRads );
    mat._33 =  (FLOAT)cos( fRads );
}




//-----------------------------------------------------------------------------
// Name: SetRotateZMatrix()
// Desc: Create Rotation matrix about Z axis
//-----------------------------------------------------------------------------
void SetRotateZMatrix( D3DMATRIX& mat, FLOAT fRads )
{
    mat = g_matIdent;
    mat._11  =  (FLOAT)cos( fRads );
    mat._12  =  (FLOAT)sin( fRads );
    mat._21  = -(FLOAT)sin( fRads );
    mat._22  =  (FLOAT)cos( fRads );
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    D3DMATRIXSetScale

Description:

    Creates a non-uniform scale matrix.
    Destroys the current contents of the destination matrix.

Arguments:

    OUT pM       -  Matrix to receive scale matrix

    IN  dvXScale -  X scale factor

    IN  dvYScale -  Y scale factor

    IN  dvZScale -  Z scale factor

Return Value:

   pM
-------------------------------------------------------------------*/
LPD3DMATRIX
D3DMATRIXSetScale(
    LPD3DMATRIX pM,
    D3DVALUE dvXScale,
    D3DVALUE dvYScale,
    D3DVALUE dvZScale
)
{

    assert(pM != NULL);

    pM->_11 = dvXScale;
    pM->_12 = D3DVAL(0.0);
    pM->_13 = D3DVAL(0.0);
    pM->_14 = D3DVAL(0.0);

    pM->_21 = D3DVAL(0.0);
    pM->_22 = dvYScale;
    pM->_23 = D3DVAL(0.0);
    pM->_24 = D3DVAL(0.0);

    pM->_31 = D3DVAL(0.0);
    pM->_32 = D3DVAL(0.0);
    pM->_33 = dvZScale;
    pM->_34 = D3DVAL(0.0);

    pM->_41 = D3DVAL(0.0);
    pM->_42 = D3DVAL(0.0);
    pM->_43 = D3DVAL(0.0);
    pM->_44 = D3DVAL(1.0);

    return pM;
}



/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DVMagnitude

Description:

    Computes the magnitude (length) of a vector

Arguments:

    pV - vector to compute length

Return Value:

    magnitude of the vector

-------------------------------------------------------------------*/
D3DVALUE
DVMagnitude(
    LPD3DVECTOR pV
)
{


    D3DVALUE dvMag;
    assert(pV != NULL);

    dvMag = D3DVAL(
        sqrt(
            (pV->x * pV->x) +
            (pV->y * pV->y) +
            (pV->z * pV->z))
        );

    return dvMag;

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetScale

Description:

    Retreives the X, Y,  and Z scale factors from the matrix.

Arguments:

     IN  pM        - Matrix to extract scale factors from

     OUT pdvXScale - X-Scale factor

     OUT pdvYScale - Y-Scale factor

     OUT pdvZScale - Z-Scale factor

-------------------------------------------------------------------*/
void
GetScale(
    LPD3DMATRIX pM,
    D3DVALUE *pdvXScale,
    D3DVALUE *pdvYScale,
    D3DVALUE *pdvZScale
)
{
    assert(pM != NULL);

    *pdvXScale = DVMagnitude((LPD3DVECTOR)&(pM->_11));
    *pdvYScale = DVMagnitude((LPD3DVECTOR)&(pM->_21));
    *pdvZScale = DVMagnitude((LPD3DVECTOR)&(pM->_31));
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    D3DMATRIXSetVRotation

Description:

   Creates a matrix for rotation of angle radians about an arbitrary axis.
   Destroys the current contents of the destination matrix.

Arguments:

   OUT pM      - Matrix to receive rotation matrix

   IN  pAxis   - Axis to rotate about.  Normalized before use.

   IN  angle   - Angle in radians to rotate about the axis.

Return Value:

   pM
-------------------------------------------------------------------*/
LPD3DMATRIX
D3DMATRIXSetVRotation(
    LPD3DMATRIX pM,
    LPD3DVECTOR pAxis,
    double angle
    )
{
    D3DVECTOR axis = *pAxis;

    D3DVALUE c = D3DVAL(cos(angle));
    D3DVALUE s = D3DVAL(sin(angle));
    D3DVALUE t = D3DVAL(1.0) - c;

    assert(pM);
    assert(pAxis);
    assert((pAxis->x != D3DVAL(0.0)) ||
           (pAxis->y != D3DVAL(0.0)) ||
           (pAxis->z!= D3DVAL(0.0)));

    D3DVECTORNormalize(&axis);
    pM->_11 = t * axis.x * axis.x + c;
    pM->_12 = t * axis.x * axis.y + s * axis.z;
    pM->_13 = t * axis.x * axis.z - s * axis.y;
    pM->_14 = D3DVAL(0.0);

    pM->_21 = t * axis.y * axis.x - s * axis.z;
    pM->_22 = t * axis.y * axis.y + c;
    pM->_23 = t * axis.y * axis.z + s * axis.x;
    pM->_24 = D3DVAL(0.0);

    pM->_31 = t * axis.z * axis.x + s * axis.y;
    pM->_32 = t * axis.z * axis.y - s * axis.x;
    pM->_33 = t * axis.z * axis.z + c;
    pM->_34 = D3DVAL(0.0);


    pM->_41 = D3DVAL(0.0);
    pM->_42 = D3DVAL(0.0);
    pM->_43 = D3DVAL(0.0);
    pM->_44 = D3DVAL(1.0);

    return pM;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    D3DVECTORSubtract

Description:

    Subtracts point B from point A giving Vector V.

    NOTE:  Points and vectors should be different types because they are mathematically distinct
           but D3D does not have that concept so D3DVECTOR is used to represent points.

Arguments:

   OUT pV  -  vector to reseive result

   IN  pA  - vector representing point A.

   IN  pB  - vector representing point B.

Return Value:

   pV

-------------------------------------------------------------------*/
LPD3DVECTOR
D3DVECTORSubtract(
    LPD3DVECTOR  pV,
    LPD3DVECTOR  pA,
    LPD3DVECTOR  pB
    )
{
    assert(pV);
    assert(pA);
    assert(pB);
    pV->x = pA->x - pB->x;
    pV->y = pA->y - pB->y;
    pV->z = pA->z - pB->z;

    return pV;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    D3DMATRIXSetView

Description:

    Sets the viewing matrix such that
    from is at the origin
    at   is on the positive Z axis
    up   is in the Y-Z plane


   Destroys the current contents of the destination matrix.
Arguments:

   OUT pM      -  Pointer to matrix to receive view matrix

   IN  pFrom   -  Location of the eye

   IN  pAt     -  Point looked at

   IN  pUp     -  Vector describing the up direction.  Cannot be parallel to (At - From)

Return Value:

   pM
-------------------------------------------------------------------*/
LPD3DMATRIX
D3DMATRIXSetView(
    LPD3DMATRIX pM,
    LPD3DVECTOR pFrom,
    LPD3DVECTOR pAt,
    LPD3DVECTOR pUp
    )
{
    D3DVECTOR los;              // Line of sight

    assert(pM);
    assert(pFrom);
    assert(pAt);
    assert(pUp);

    D3DVECTORSubtract(&los, pAt, pFrom);

    assert((los.x != D3DVAL(0.0)) ||
           (los.y != D3DVAL(0.0)) ||
           (los.z != D3DVAL(0.0)));

    // Generate the rotation part of the matrix
    D3DMATRIXSetRotation(pM, &los, pUp);

    // Make sure the matrix is completely initialized
    pM->_14 = D3DVAL(0.0);
    pM->_24 = D3DVAL(0.0);
    pM->_34 = D3DVAL(0.0);
    pM->_41 = D3DVAL(0.0);
    pM->_42 = D3DVAL(0.0);
    pM->_43 = D3DVAL(0.0);
    pM->_44 = D3DVAL(1.0);

    D3DMATRIXTranspose(pM, pM);

    // Preconcatenate translational component
    pM->_41 = -(pFrom->x * pM->_11 + pFrom->y * pM->_21 + pFrom->z * pM->_31);
    pM->_42 = -(pFrom->x * pM->_12 + pFrom->y * pM->_22 + pFrom->z * pM->_32);
    pM->_43 = -(pFrom->x * pM->_13 + pFrom->y * pM->_23 + pFrom->z * pM->_33);

    return pM;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    D3DMATRIXTranspose

Description:

   Transposes a matrix.  Transpose is equivalent to Inverse for pure
   rotation matrices.
   Destroys the current contents of the destination matrix.
Arguments:

  OUT pDest  - Destination matrix

  IN  pSrc   - Source matrix

Return Value:

   Pointer to the transposed matrix
-------------------------------------------------------------------*/
LPD3DMATRIX
D3DMATRIXTranspose(
    LPD3DMATRIX pDest,
    LPD3DMATRIX pSrc
    )
{
    D3DMATRIX tmp;

    assert(pDest);
    assert(pSrc);

    tmp._11 = pSrc->_11;
    tmp._12 = pSrc->_21;
    tmp._13 = pSrc->_31;
    tmp._14 = pSrc->_41;

    tmp._21 = pSrc->_12;
    tmp._22 = pSrc->_22;
    tmp._23 = pSrc->_32;
    tmp._24 = pSrc->_42;

    tmp._31 = pSrc->_13;
    tmp._32 = pSrc->_23;
    tmp._33 = pSrc->_33;
    tmp._34 = pSrc->_43;

    tmp._41 = pSrc->_14;
    tmp._42 = pSrc->_24;
    tmp._43 = pSrc->_34;
    tmp._44 = pSrc->_44;

    *pDest = tmp;

    return pDest;
}

