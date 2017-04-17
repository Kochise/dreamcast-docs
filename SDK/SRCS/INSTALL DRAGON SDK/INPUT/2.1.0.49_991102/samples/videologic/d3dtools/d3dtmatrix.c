/*****************************************************************************
  Name : D3DTMatrix.c
  Date : July 1998
  Platform : ANSI compatible
 
  * Description : 
  This file is part of the TOOLS library (D3DTools.lib) used
  with the SDK demos for PowerVR series 2.

  Set of mathematical functions involving matrices and vectors.
  
  The general matrix format used in these functions is the D3D
  format (D3DMATRIX). The matrix format is of the form:

				  (	11 12 13 14 )
				  (	21 22 23 24 )
			  M = (	31 32 33 34 )
				  (	41 42 43 44 )

  
  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#include <math.h>
#include <d3d.h>
#include <shintr.h> /* For SH4 built-in APIs */
#include "D3DTMatrix.h"



/*******************************************************************************
 * Function Name  : D3DTMatrixReset
 * Input/Output	  : *pMatrix
 * Globals used	  : None
 * Description    : Reset matrix to identity matrix.
 *
 *******************************************************************************/
void D3DTMatrixReset(D3DMATRIX *pMatrix)
{
	pMatrix->_11=1.0f;			pMatrix->_12=0.0f;		pMatrix->_13=0.0f;			pMatrix->_14=0.0f;	
	pMatrix->_21=0.0f;			pMatrix->_22=1.0f;		pMatrix->_23=0.0f;			pMatrix->_24=0.0f;	
	pMatrix->_31=0.0f;			pMatrix->_32=0.0f;		pMatrix->_33=1.0f;			pMatrix->_34=0.0f;	
	pMatrix->_41=0.0f;			pMatrix->_42=0.0f;		pMatrix->_43=0.0f;			pMatrix->_44=1.0f;	
}


/*******************************************************************************
 * Function Name  : D3DTMatrixMultiply
 * Inputs		  : *pMatrixA, *pMatrixB
 * Output		  : *pResultMatrix
 * Globals used	  : None
 * Description    : Multiply pMatrixA by pMatrixB and assign the result
 *					in pResultMatrix (pResultMatrix = pMatrixA * pMatrixB).
 *					A copy of the result matrix (ret) is done is the function
 *					because *pResultMatrix can be a parameter (*pMatrixA or
 *					*pMatrixB).
 *
 *******************************************************************************/
void D3DTMatrixMultiply(D3DMATRIX *pResultMatrix, const D3DMATRIX *pMatrixA, const D3DMATRIX *pMatrixB)  
{
    //_Multiply4dM((float *)pResultMatrix, (float *)pMatrixA, (float *)pMatrixB);

#if 1
	D3DMATRIX ret;

	/* Perform calculation on a dummy matrix (ret) */
	ret._11 = pMatrixA->_11*pMatrixB->_11 + pMatrixA->_12*pMatrixB->_21 + pMatrixA->_13*pMatrixB->_31 + pMatrixA->_14*pMatrixB->_41;
	ret._12 = pMatrixA->_11*pMatrixB->_12 + pMatrixA->_12*pMatrixB->_22 + pMatrixA->_13*pMatrixB->_32 + pMatrixA->_14*pMatrixB->_42;
	ret._13 = pMatrixA->_11*pMatrixB->_13 + pMatrixA->_12*pMatrixB->_23 + pMatrixA->_13*pMatrixB->_33 + pMatrixA->_14*pMatrixB->_43;
	ret._14 = pMatrixA->_11*pMatrixB->_14 + pMatrixA->_12*pMatrixB->_24 + pMatrixA->_13*pMatrixB->_34 + pMatrixA->_14*pMatrixB->_44;

	ret._21 = pMatrixA->_21*pMatrixB->_11 + pMatrixA->_22*pMatrixB->_21 + pMatrixA->_23*pMatrixB->_31 + pMatrixA->_24*pMatrixB->_41;
	ret._22 = pMatrixA->_21*pMatrixB->_12 + pMatrixA->_22*pMatrixB->_22 + pMatrixA->_23*pMatrixB->_32 + pMatrixA->_24*pMatrixB->_42;
	ret._23 = pMatrixA->_21*pMatrixB->_13 + pMatrixA->_22*pMatrixB->_23 + pMatrixA->_23*pMatrixB->_33 + pMatrixA->_24*pMatrixB->_43;
	ret._24 = pMatrixA->_21*pMatrixB->_14 + pMatrixA->_22*pMatrixB->_24 + pMatrixA->_23*pMatrixB->_34 + pMatrixA->_24*pMatrixB->_44;

	ret._31 = pMatrixA->_31*pMatrixB->_11 + pMatrixA->_32*pMatrixB->_21 + pMatrixA->_33*pMatrixB->_31 + pMatrixA->_34*pMatrixB->_41;
	ret._32 = pMatrixA->_31*pMatrixB->_12 + pMatrixA->_32*pMatrixB->_22 + pMatrixA->_33*pMatrixB->_32 + pMatrixA->_34*pMatrixB->_42;
	ret._33 = pMatrixA->_31*pMatrixB->_13 + pMatrixA->_32*pMatrixB->_23 + pMatrixA->_33*pMatrixB->_33 + pMatrixA->_34*pMatrixB->_43;
	ret._34 = pMatrixA->_31*pMatrixB->_14 + pMatrixA->_32*pMatrixB->_24 + pMatrixA->_33*pMatrixB->_34 + pMatrixA->_34*pMatrixB->_44;

	ret._41 = pMatrixA->_41*pMatrixB->_11 + pMatrixA->_42*pMatrixB->_21 + pMatrixA->_43*pMatrixB->_31 + pMatrixA->_44*pMatrixB->_41;
	ret._42 = pMatrixA->_41*pMatrixB->_12 + pMatrixA->_42*pMatrixB->_22 + pMatrixA->_43*pMatrixB->_32 + pMatrixA->_44*pMatrixB->_42;
	ret._43 = pMatrixA->_41*pMatrixB->_13 + pMatrixA->_42*pMatrixB->_23 + pMatrixA->_43*pMatrixB->_33 + pMatrixA->_44*pMatrixB->_43;
	ret._44 = pMatrixA->_41*pMatrixB->_14 + pMatrixA->_42*pMatrixB->_24 + pMatrixA->_43*pMatrixB->_34 + pMatrixA->_44*pMatrixB->_44;

	/* Copy result in pResultMatrix */
	pResultMatrix->_11=ret._11;
	pResultMatrix->_12=ret._12;
	pResultMatrix->_13=ret._13;
	pResultMatrix->_14=ret._14;

	pResultMatrix->_21=ret._21;
	pResultMatrix->_22=ret._22;
	pResultMatrix->_23=ret._23;
	pResultMatrix->_24=ret._24;

	pResultMatrix->_31=ret._31;
	pResultMatrix->_32=ret._32;
	pResultMatrix->_33=ret._33;
	pResultMatrix->_34=ret._34;

	pResultMatrix->_41=ret._41;
	pResultMatrix->_42=ret._42;
	pResultMatrix->_43=ret._43;
	pResultMatrix->_44=ret._44;
#endif
}   


/*******************************************************************************
 * Function Name  : D3DTMatrixTranslate
 * Input/Output	  : *pMatrix
 * Inputs		  : fX, fY, fZ
 * Globals used	  : None
 * Description    : Translate matrix *pMatrix by fX, fY and fZ.
 *
 *******************************************************************************/
void D3DTMatrixTranslate(D3DMATRIX *pMatrix, const float fX, const float fY, const float fZ)
{
	pMatrix->_41+=fX;
	pMatrix->_42+=fY;
	pMatrix->_43+=fZ;				
}   


/*******************************************************************************
 * Function Name  : D3DTMatrixRotate
 * Input/Output	  : *pMatrix
 * Input		  : fXAngle, fYAngle, fZAngle
 * Globals used	  : None
 * Description    : Apply X, Y and Z rotations to matrix *pMatrix.
 *
 *******************************************************************************/
void D3DTMatrixRotate(D3DMATRIX *pMatrix, const float fXAngle, const float fYAngle, const float fZAngle)
{
	D3DMATRIX	rot;
	float		fCosine, fSine;

	/* X Rotation */

    /* Precompute cos and sin */
	fCosine=(float)cos(fXAngle);
    fSine=(float)sin(fXAngle);
    
	/* Create the trigonometric matrix corresponding to X Rotation */
	rot._11=1.0f;			rot._12=0.0f;		rot._13=0.0f;			rot._14=0.0f;	
	rot._21=0.0f;			rot._22=fCosine;	rot._23=fSine;			rot._24=0.0f;	
	rot._31=0.0f;			rot._32=-fSine;		rot._33=fCosine;		rot._34=0.0f;	
	rot._41=0.0f;			rot._42=0.0f;		rot._43=0.0f;			rot._44=1.0f;	

	/* Multiply the given matrix with this trigonometric matrix */
	D3DTMatrixMultiply(pMatrix, pMatrix, &rot);

	/* Y Rotation */

	/* Precompute cos and sin */
	fCosine=(float)cos(fYAngle);
    fSine=(float)sin(fYAngle);
    
	/* Create the trigonometric matrix corresponding to Y Rotation */
	rot._11=fCosine;		rot._12=0.0f;		rot._13=-fSine;			rot._14=0.0f;	
	rot._21=0.0f;			rot._22=1.0f;		rot._23=0.0f;			rot._24=0.0f;	
	rot._31=fSine;			rot._32=0.0f;		rot._33=fCosine;		rot._34=0.0f;	
	rot._41=0.0f;			rot._42=0.0f;		rot._43=0.0f;			rot._44=1.0f;	

	/* Multiply the given matrix with this trigonometric matrix */
	D3DTMatrixMultiply(pMatrix, pMatrix, &rot);

	/* Z Rotation */
	
	/* Precompute cos and sin */
	fCosine=(float)cos(fZAngle);
    fSine=(float)sin(fZAngle);
    
	/* Create the trigonometric matrix corresponding to Z Rotation */
	rot._11=fCosine;		rot._12=fSine;		rot._13=0.0f;			rot._14=0.0f;	
	rot._21=-fSine;			rot._22=fCosine;	rot._23=0.0f;			rot._24=0.0f;	
	rot._31=0.0f;			rot._32=0.0f;		rot._33=1.0f;			rot._34=0.0f;	
	rot._41=0.0f;			rot._42=0.0f;		rot._43=0.0f;			rot._44=1.0f;	

	/* Multiply the given matrix with this trigonometric matrix */
	D3DTMatrixMultiply(pMatrix, pMatrix, &rot);
}


/*******************************************************************************
 * Function Name  : D3DTMatrixScale
 * Input/Output	  : *pMatrix
 * Input		  : fFactor
 * Globals used	  : None
 * Description    : Scale matrix pMatrix by the homogeneous factor fFactor.
 *
 *******************************************************************************/
void D3DTMatrixScale(D3DMATRIX *pMatrix, const float fFactor)
{
	pMatrix->_11*=fFactor;	
	pMatrix->_22*=fFactor;
	pMatrix->_33*=fFactor;
	//pMatrix->_44*=fFactor;
}


/*******************************************************************************
 * Function Name  : D3DTMatrixInverse
 * Input/Output	  : *pMatrix
 * Globals used	  : None
 * Description    : Compute the inverse matrix of pMatrix.
 *					The matrix must be of the form :  
 * 					A 0
 *					C 1 
 *					Where A is a 3x3 matrix and C is a 1x3 matrix.
 *
 *******************************************************************************/
void D3DTMatrixInverse(D3DMATRIX *pMatrix)
{
	D3DMATRIX		DummyMatrix;
	float			det_1;
	float			pos, neg, temp;

    /* Calculate the determinant of submatrix A and determine if the
       the matrix is singular as limited by the float precision
       floating-point data representation. */
    pos = neg = 0.0f;
    temp =  pMatrix->_11 * pMatrix->_22 * pMatrix->_33;
    if (temp >= 0.0f) pos += temp; else neg += temp;
    temp =  pMatrix->_12 * pMatrix->_23 * pMatrix->_31;
    if (temp >= 0.0f) pos += temp; else neg += temp;
    temp =  pMatrix->_13 * pMatrix->_21 * pMatrix->_32;
    if (temp >= 0.0f) pos += temp; else neg += temp;
    temp = -pMatrix->_13 * pMatrix->_22 * pMatrix->_31;
    if (temp >= 0.0f) pos += temp; else neg += temp;
    temp = -pMatrix->_12 * pMatrix->_21 * pMatrix->_33;
    if (temp >= 0.0f) pos += temp; else neg += temp;
    temp = -pMatrix->_11 * pMatrix->_23 * pMatrix->_32;
    if (temp >= 0.0f) pos += temp; else neg += temp;
    det_1 = pos + neg;

    /* Is the submatrix A singular? */
    if ((det_1 == 0.0f) || ((float)fabs(det_1 / (pos - neg)) < 0.00000001f)) 
	{
        /* Matrix M has no inverse */
        OutputDebugString(TEXT("Matrix has no inverse : singular matrix\n"));
        return;
    }
    else 
	{
        /* Calculate inverse(A) = adj(A) / det(A) */
        det_1 = 1.0f / det_1;
        DummyMatrix._11 =   ( pMatrix->_22 * pMatrix->_33 - pMatrix->_23 * pMatrix->_32 ) * (float)det_1;
        DummyMatrix._21 = - ( pMatrix->_21 * pMatrix->_33 - pMatrix->_23 * pMatrix->_31 ) * (float)det_1;
        DummyMatrix._31 =   ( pMatrix->_21 * pMatrix->_32 - pMatrix->_22 * pMatrix->_31 ) * (float)det_1;
        DummyMatrix._12 = - ( pMatrix->_12 * pMatrix->_33 - pMatrix->_13 * pMatrix->_32 ) * (float)det_1;
        DummyMatrix._22 =   ( pMatrix->_11 * pMatrix->_33 - pMatrix->_13 * pMatrix->_31 ) * (float)det_1;
        DummyMatrix._32 = - ( pMatrix->_11 * pMatrix->_32 - pMatrix->_12 * pMatrix->_31 ) * (float)det_1;
        DummyMatrix._13 =   ( pMatrix->_12 * pMatrix->_23 - pMatrix->_13 * pMatrix->_22 ) * (float)det_1;
        DummyMatrix._23 = - ( pMatrix->_11 * pMatrix->_23 - pMatrix->_13 * pMatrix->_21 ) * (float)det_1;
        DummyMatrix._33 =   ( pMatrix->_11 * pMatrix->_22 - pMatrix->_12 * pMatrix->_21 ) * (float)det_1;

        /* Calculate -C * inverse(A) */
        DummyMatrix._41 = - ( pMatrix->_41 * DummyMatrix._11 + pMatrix->_42 * DummyMatrix._21 + pMatrix->_43 * DummyMatrix._31 );
        DummyMatrix._42 = - ( pMatrix->_41 * DummyMatrix._12 + pMatrix->_42 * DummyMatrix._22 + pMatrix->_43 * DummyMatrix._32 );
        DummyMatrix._43 = - ( pMatrix->_41 * DummyMatrix._13 + pMatrix->_42 * DummyMatrix._23 + pMatrix->_43 * DummyMatrix._33 );

        /* Fill in last column */
        DummyMatrix._14 = DummyMatrix._24 = DummyMatrix._34 = 0.0;
        DummyMatrix._44 = 1.0f;
	}

   	/* Copy contents of dummy matrix in pMatrix */
	D3DTMatrixCopy(pMatrix, &DummyMatrix);
}


/*******************************************************************************
 * Function Name  : D3DTMatrixCopy
 * Input		  : *pSrcMatrix
 * Output		  : *pDstMatrix
 * Globals used	  : None
 * Description    : Copy matrix pSrcMatrix into pDstMatrix
 *
 *******************************************************************************/
void D3DTMatrixCopy(D3DMATRIX *pDstMatrix, const D3DMATRIX *pSrcMatrix)
{
	pDstMatrix->_11=pSrcMatrix->_11;
	pDstMatrix->_12=pSrcMatrix->_12;
	pDstMatrix->_13=pSrcMatrix->_13;
	pDstMatrix->_14=pSrcMatrix->_14;

	pDstMatrix->_21=pSrcMatrix->_21;
	pDstMatrix->_22=pSrcMatrix->_22;
	pDstMatrix->_23=pSrcMatrix->_23;
	pDstMatrix->_24=pSrcMatrix->_24;

	pDstMatrix->_31=pSrcMatrix->_31;
	pDstMatrix->_32=pSrcMatrix->_32;
	pDstMatrix->_33=pSrcMatrix->_33;
	pDstMatrix->_34=pSrcMatrix->_34;

	pDstMatrix->_41=pSrcMatrix->_41;
	pDstMatrix->_42=pSrcMatrix->_42;
	pDstMatrix->_43=pSrcMatrix->_43;
	pDstMatrix->_44=pSrcMatrix->_44;
}


/*******************************************************************************
 * Function Name  : D3DTMatrixDotProduct
 * Inputs		  : *pVectorA, *pVectorB
 * Globals used	  : None
 * Returns		  : float
 * Description    : Returns the dot product between vectors *pVectorA and *pVectorB
 *
 *******************************************************************************/
float D3DTMatrixDotProduct(const D3DVECTOR *pVectorA, const D3DVECTOR *pVectorB)
{
	return (pVectorA->x*pVectorB->x + pVectorA->y*pVectorB->y + pVectorA->z*pVectorB->z);
}


/*******************************************************************************
 * Function Name  : D3DTMatrixCrossProduct
 * Inputs		  : *pVectorA, *pVectorB
 * Output		  : *pResultVector
 * Globals used	  : None
 * Description    : Compute the cross product between pVectorA and pVectorB and
 *					assign the resulting vector in pResultVector.
 *
 *******************************************************************************/
void D3DTMatrixCrossProduct(D3DVECTOR *pResultVector, const D3DVECTOR *pVectorA, const D3DVECTOR *pVectorB)
{
    D3DVECTOR result;

	/* Perform calculation on a dummy VECTOR (result) */
    result.x = pVectorA->y * pVectorB->z - pVectorA->z * pVectorB->y;
    result.y = pVectorA->z * pVectorB->x - pVectorA->x * pVectorB->z;
    result.z = pVectorA->x * pVectorB->y - pVectorA->y * pVectorB->x;
    
	/* Copy result in pResultVector */
	pResultVector->x=result.x;
	pResultVector->y=result.y;
	pResultVector->z=result.z;
}


/*******************************************************************************
 * Function Name  : D3DTMatrixNormalize
 * Input/Output	  : *pVector
 * Globals used	  : None
 * Description    : Normalize vector pVector.
 *
 *******************************************************************************/
void D3DTMatrixNormalize(D3DVECTOR *pVector)
{
    float	fVx, fVy, fVz, fInvMod;

    /* Assign temporary variables */
	fVx=pVector->x;	
    fVy=pVector->y;
    fVz=pVector->z;
 
	/* If vector is not null, then perform normalization */
	if ((fVx==0) && (fVy==0) && (fVz==0))
	{
		/* Null vector, keep it unchanged */
		return;
	}
	
	/* Normalize */
	fInvMod=(float)(1.0f/(float)sqrt(fVx*fVx + fVy*fVy + fVz*fVz));
	pVector->x=fVx*fInvMod;
	pVector->y=fVy*fInvMod;
	pVector->z=fVz*fInvMod;
}

