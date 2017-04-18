#include <windows.h>
#include "vector2d.h"
#include <stdlib.h>
#include <math.h>

/***********************************************************************

  FUNCTION   : LibMain 

  PARAMETERS : (HANDLE, DWORD, LPVOID)  

  PURPOSE    : LibMain is called by Windows when
               the DLL is initialized, Thread Attached, and other times.
               Refer to SDK documentation, as to the different ways this
               may be called.
             
               The LibMain function should perform additional initialization
               tasks required by the DLL.  In this example, no initialization
               tasks are required.  LibMain should return a value of 1 if
               the initialization is successful.
               
  RETURNS    : 

  COMMENTS   :

  HISTORY    : - created - denniscr

************************************************************************/

INT  APIENTRY LibMain(HANDLE hInst, DWORD ul_reason_being_called, LPVOID lpReserved)
{
    return 1;

    UNREFERENCED_PARAMETER(hInst);
    UNREFERENCED_PARAMETER(ul_reason_being_called);
    UNREFERENCED_PARAMETER(lpReserved);
}

/***********************************************************************

vSubtractVectors 

The vSubtractVectors function subtracts the components of a two 
dimensional vector from another. The resultant vector 
c = (a1 - b1, a2 - b2).

Parameters

v0	A pointer to a VECTOR2D structure containing the components 
    of the first two dimensional vector.
v1	A pointer to a VECTOR2D structure containing the components 
    of the second two dimensional vector.
vt	A pointer to a VECTOR2D structure in which the components 
    of the two dimensional vector obtained from the subtraction of 
    the first two are placed.

Return value

A pointer to a VECTOR2D structure containing the new vector obtained 
from the subtraction of the first two parameters.

HISTORY    : - created - denniscr

************************************************************************/

PVECTOR2D APIENTRY vSubtractVectors(PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v)
{
  if (v0 == NULL || v1 == NULL)
    v = (PVECTOR2D)NULL;
  else
  {
    v->x = v0->x - v1->x;
    v->y = v0->y - v1->y;
  }
  return(v);
}

/***********************************************************************

vAddVectors 

The vAddVectors function adds the components of a two dimensional vector 
from another. The resultant vector c = (a1 + b1, a2  + b2).

Parameters

v0	A pointer to a VECTOR2D structure containing the components of the 
    first two dimensional vector.
v1	A pointer to a VECTOR2D structure containing the components of the 
    second two dimensional vector.
v	A pointer to a VECTOR2D structure in which the components of the two 
    dimensional vector obtained from the addition of the first two are placed.

Return value

A pointer to a VECTOR2D structure containing the new vector obtained from 
the addition of the first two parameters.

HISTORY    : - created - denniscr

************************************************************************/

PVECTOR2D APIENTRY vAddVectors(PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v)
{
  if (v0 == NULL || v1 == NULL)
    v = (PVECTOR2D)NULL;
  else
  {
    v->x = v0->x + v1->x;
    v->y = v0->y + v1->y;
  }
  return(v);
}

/***********************************************************************

vScaleVector 

The vScaleVector function scales the components of a vector by a user 
supplied scaling factor.

Parameters

v0	A pointer to a VECTOR2D structure containing the components of 
    the two dimensional vector to be scaled.
dScaling	The value by which to scale the components of v0
v	A pointer to a VECTOR2D structure in which the results of 
    multiplying (scaling) the components of v0 by dScaling are stored.

Return value

A pointer to a VECTOR2D structure containing the scaled vector.

HISTORY    : - created - denniscr

************************************************************************/

PVECTOR2D APIENTRY vScaleVector(PVECTOR2D v0, double dScaling, PVECTOR2D v)
{
  if (v0 == NULL)
    v = (PVECTOR2D)NULL;
  else
  {
    if (dScaling != 0)
    {
      v->x = (v0->x *= dScaling);
      v->y = (v0->y *= dScaling);
	}
  }
  return(v);
}

/***********************************************************************

vLinearCombination

The vLinearCombination function scales the components of two vectors 
and adds them together to form a new vector having the linear combination. 
The resultant vector is where u and v are scaling factors and a and b are 
vectors is c = ua + vb.

Parameters

ptScale	A pointer to a VECTOR2D structure containing the scaling values
v0	A pointer to a VECTOR2D structure containing the first of two vectors 
    to be combined linearly.
v1	A pointer to a VECTOR2D structure containing the second of two vectors 
    to be combined linearly. 
v	A pointer to a VECTOR2D structure in which the results of linearly 
    combining vectors v0 and v1 are stored.

Return value

A pointer to a VECTOR2D structure containing a vector which is the result 
of the linear combination.

HISTORY    : - created - denniscr

************************************************************************/

PVECTOR2D APIENTRY vLinearCombination(PVECTOR2D vScale, PVECTOR2D v0, PVECTOR2D v1, PVECTOR2D v)
{
  if (vScale == NULL || v0 == NULL || v1 == NULL)
    v = (PVECTOR2D)NULL;
  else
  {
    v->x = vScale->x * v0->x + vScale->y * v1->x;
    v->y = vScale->x * v0->y + vScale->y * v1->y;
  }
  return(v);
}

/***********************************************************************

vVectorSquared

The vVectorSquared function squares each of the components of the 
vector and adds then together to produce the squared value of the 
vector. SquaredValue = a.x * a.x + a.y * a.y.

Parameters

v0	A pointer to a VECTOR2D structure containing the vector upon which 
to determine the squared value.

Return value

A double value which is the squared value of the vector. 

HISTORY    : - created - denniscr

************************************************************************/

double APIENTRY vVectorSquared(PVECTOR2D v0)
{
  double dSqLen;

  if (v0 == NULL)
    dSqLen = 0.0;
  else
    dSqLen = (double)(v0->x * v0->x) + (double)(v0->y * v0->y);
  return (dSqLen);
}

/***********************************************************************

vVectorMagnitude

The vVectorMagnitude function determines the length of a vector by 
summing the squares of each of the components of the vector. The 
magnitude is equal to a.x * a.x + a.y * a.y.

Parameters

v0	A pointer to a VECTOR2D structure containing the vector upon 
    which to determine the magnitude.

Return value

A double value which is the magnitude of the vector. 

HISTORY    : - created - denniscr

************************************************************************/

double APIENTRY vVectorMagnitude(PVECTOR2D v0)
{
  double dMagnitude;

  if (v0 == NULL)
    dMagnitude = 0.0;
  else
    dMagnitude = sqrt(vVectorSquared(v0));
  return (dMagnitude);
}

/***********************************************************************

vNormalizeVector

A normalized vector is a vector with a length of one. The resultant 
vector is often called a unit vector. The vNormalizeVector function 
converts a vector into a normalized vector. To normalize   
a vector, the vector is scaled by the reciprocal of the magnitude 
of the vector: cn = c * 1/|c|.

Parameters

v0	A pointer to a VECTOR2D structure containing the vector to normalize.

Return value

Void.

HISTORY    : - created - denniscr

************************************************************************/

void APIENTRY vNormalizeVector(PVECTOR2D v0)
{
  double dMagnitude = vVectorMagnitude(v0);

  v0->x /= dMagnitude;
  v0->y /= dMagnitude;
}

/***********************************************************************

vDotProduct

The function vDotProduct computes the dot product of two vectors. The 
dot product of two vectors is the sum of the products of the components 
of the vectors ie: for the vectors a and b, dotprod = a1 * a2 + b1 * b2.

Parameters

v0	A pointer to a VECTOR2D structure containing the first vector used 
    for obtaining a dot product.
v1	A pointer to a VECTOR2D structure containing the second vector used 
    for obtaining a dot product.

Return value

A double value containing the scalar dot product value.

HISTORY    : - created - denniscr

************************************************************************/

double APIENTRY vDotProduct(PVECTOR2D v0, PVECTOR2D v1)
{
  return ((v0 == NULL || v1 == NULL) ? 0.0 
                                     : (v0->x * v1->x) + (v0->y * v1->y));
}

/***********************************************************************

vNormalVector

The function vNormalVector computes the vector that is normal to a given 
vector. For the vector a, the normal vector n = (-ay, ax).

Parameters

v0	A pointer to a VECTOR2D structure containing the vector vector for 
    which a normal vector is sought.
v	A pointer to a VECTOR2D structure containing the computed normal 
    vector.

Return value

A pointer to a VECTOR2D structure containing the normal vector.

HISTORY    : - created - denniscr

************************************************************************/

PVECTOR2D APIENTRY vNormalVector(PVECTOR2D v0, PVECTOR2D v)
{
  if (v0 == NULL)
    v = (PVECTOR2D)NULL;
  else
  {
    v->x = -v0->y;
    v->y = v0->x;
  }
  return(v);
}

/***********************************************************************

vVectorAngle

The function vVectorAngle computes the cosine of the angle between 
two vectors.

Parameters

v0	A pointer to a VECTOR2D structure containing the first vector.
v1	A pointer to a VECTOR2D structure containing the second vector.

Return value

A double value indicating the cosine of the angle between the two 
vectors is returned.

HISTORY    : - created - denniscr

************************************************************************/

double APIENTRY vVectorAngle(PVECTOR2D v0, PVECTOR2D v1)
{
  double vangle;

  if (v0 == NULL || v1 == NULL)
    vangle = 0.0;
  else
  {
    vNormalizeVector(v0);
    vNormalizeVector(v1);
	vangle = vDotProduct(v0, v1);
  }
  return(vangle);
}

/***********************************************************************

vPointNormalForm

The function vPointNormalForm computes the components of the point 
normal equation of a line in a plane. vector that is normal to a 
given vector. For the vector a, the normal vector n = (-ay, ax).

Parameters

v0	A pointer to a VECTOR2D structure containing the vector 
    for which a normal vector is sought.
v	A pointer to a VECTOR2D structure containing the computed 
    normal vector.

Return value

A pointer to a VECTOR2D structure containing the normal vector.

HISTORY    : - created - denniscr

************************************************************************/

BOOL APIENTRY vPointNormalForm(POINT pt0, POINT pt1, PPOINTNORMAL ppnPointNormal)
{
  VECTOR2D v, vNormal;

  POINTS2VECTOR2D(pt0, pt1, v);

  if (v.x == 0 && v.y == 0)
    return(FALSE);

  vNormalVector(&v, &vNormal);

  ppnPointNormal->vNormal.x = vNormal.x;
  ppnPointNormal->vNormal.y = vNormal.y;
  ppnPointNormal->D = vDotProduct(&vNormal, (PVECTOR2D)&pt0);
  return(TRUE);
}

/***********************************************************************

vProjectAndResolve

The function vProjectAndResolve resolves a vector into two vector 
components. The first is a vector obtained by projecting vector v0 onto 
v1. The second is a vector that is perpendicular (normal) to the 
projected vector. It extends from the head of the projected vector 
v1 to the head of the original vector v0.

Parameters

v0	   A pointer to a VECTOR2D structure containing the first vector 
v1	   A pointer to a VECTOR2D structure containing the second vector
ppProj A pointer to a PROJECTION structure containing the resolved 
       vectors and their lengths.

Return value

void.

HISTORY    : - created - denniscr

************************************************************************/

void APIENTRY vProjectAndResolve(PVECTOR2D v0, PVECTOR2D v1, PPROJECTION ppProj)
{
  VECTOR2D ttProjection, ttOrthogonal;
  double proj1;
  //
  //obtain projection vector
  //
  //c = a * b
  //    ----- b
  //    |b|^2
  //
  proj1 = vDotProduct(v0, v1)/vDotProduct(v1, v1);
  ttProjection.x = v1->x * proj1;
  ttProjection.y = v1->y * proj1;
  //
  //obtain perpendicular projection : e = a - c
  //
  vSubtractVectors(v0, &ttProjection, &ttOrthogonal);
  //
  //fill PROJECTION structure with appropriate values
  //
  ppProj->LenProjection = vVectorMagnitude(&ttProjection);
  ppProj->LenPerpProjection = vVectorMagnitude(&ttOrthogonal);

  ppProj->ttProjection.x = ttProjection.x;
  ppProj->ttProjection.y = ttProjection.y;
  ppProj->ttPerpProjection.x = ttOrthogonal.x;
  ppProj->ttPerpProjection.y = ttOrthogonal.y;
}

/***********************************************************************

vIsPerpendicular

The function vIsPerpendicular determines if two vectors are perpendicular 
to one another. This is done by testing the dot product of the two vectors. 
If the dot product is zero then the vectors are perpendicular.

Parameters

v0	A pointer to a VECTOR2D structure containing the first vector.
v1	A pointer to a VECTOR2D structure containing the second vector.

Return value

A BOOL value. TRUE if the two vectors are perpendicular. 
              FALSE if the vectors are not perpendicular.

HISTORY    : - created - denniscr

************************************************************************/

BOOL APIENTRY vIsPerpendicular(PVECTOR2D v0, PVECTOR2D v1)
{
  double product;

  if (v0 == NULL || v1 == NULL)
    product = 0.0;
  else
    product = vDotProduct(v0, v1);

  return (((product == 0.0) ? TRUE : FALSE));
}

/***********************************************************************

vDistFromPointToLine

The function vDistFromPointToLine computes the distance from the point 
ptTest to the line defined by endpoints pt0 and pt1. This is done by 
resolving the the vector from pt0 to ptTest into its components. The 
length of the component vector that is attached to the head of the 
vector from pt0 to ptTest is the distance of ptTest from the line.

Parameters

pt0    A pointer to a POINT structure containing the first endpoint of the 
       line.
pt1	   A pointer to a POINT structure containing the second endpoint of the 
       line.
ptTest A pointer to a POINT structure containing the point for which the 
       distance from the line is to be computed.

Return value

A double value that contains the distance of ptTest to the line defined 
  by the endpoints pt0 and pt1.

HISTORY    : - created - denniscr
************************************************************************/

double APIENTRY vDistFromPointToLine(LPPOINT pt0, LPPOINT pt1, LPPOINT ptTest)
{
  VECTOR2D ttLine, ttTest;
  PROJECTION pProjection;

  POINTS2VECTOR2D(*pt0, *pt1, ttLine);
  POINTS2VECTOR2D(*pt0, *ptTest, ttTest);

  vProjectAndResolve(&ttTest, &ttLine, &pProjection);
 
  return(pProjection.LenPerpProjection);
}

