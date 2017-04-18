/*****************************************************************************
  Name : KMMatrix.c
  Date : August 1998
  Platform : ANSI compatible
 
  * Description : 
  This file is part of the KAMUI TOOLS library (KMTools.lib) used
  with the SDK demos for PowerVR series 2.

  Set of mathematical functions involving matrices and vectors.
  
  The general matrix format used in these functions is the same
  as the D3D format (D3DMATRIX). The matrix format is of the form:

				  (	11 12 13 14 )
				  (	21 22 23 24 )
			  M = (	31 32 33 34 )
				  (	41 42 43 44 )

  
  Copyright : 1998 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#include <Machine.h>
#include <math.h>

#include "KMTools.h"

/*************************************/
/*  ALIGNED GLOBALS FOR SH4 ROUTINES */
/*************************************/

unsigned long	Buffer2[70];
#define	pSH4Matrix1		((MATRIX *)(((unsigned long)Buffer2+7)&0xFFFFFFF8))

unsigned long	Buffer3[70];
#define	pSH4Matrix2		((MATRIX *)(((unsigned long)Buffer3+7)&0xFFFFFFF8))

unsigned long	Buffer4[10];
#define	pSH4Vector1		((float *)(((unsigned long)Buffer4+7)&0xFFFFFFF8))

unsigned long	Buffer5[10];
#define	pSH4Vector2		((float *)(((unsigned long)Buffer5+7)&0xFFFFFFF8))


/*******************************************************************************
 * Function Name  : KMMatrixReset
 * Inputs		  : *pMatrix
 * Globals used   : None
 * Description    : Reset matrix to identity matrix.
 *
 *******************************************************************************/
void KMMatrixReset(MATRIX *pMatrix)
{
	pMatrix->_11=1.0f;		pMatrix->_12=0.0f;		pMatrix->_13=0.0f;		pMatrix->_14=0.0f;	
	pMatrix->_21=0.0f;		pMatrix->_22=1.0f;		pMatrix->_23=0.0f;		pMatrix->_24=0.0f;	
	pMatrix->_31=0.0f;		pMatrix->_32=0.0f;		pMatrix->_33=1.0f;		pMatrix->_34=0.0f;	
	pMatrix->_41=0.0f;		pMatrix->_42=0.0f;		pMatrix->_43=0.0f;		pMatrix->_44=1.0f;	
}


/*******************************************************************************
 * Function Name  : KMMatrixMultiply
 * Inputs		  : *pMatrixA, *pMatrixB
 * Output		  : *pResultMatrix
 * Globals used   : None
 * Description    : Multiply pMatrixA by pMatrixB and assign the result
 *					in pResultMatrix (pResultMatrix = pMatrixA * pMatrixB)
 *
 *******************************************************************************/
void KMMatrixMultiply(MATRIX *pResultMatrix, const MATRIX *pMatrixA, const MATRIX *pMatrixB)  
{
    MATRIX ret;
	
	/* Matrix A */
	pSH4Matrix1->_11 = pMatrixA->_11;
	pSH4Matrix1->_12 = pMatrixA->_12;
	pSH4Matrix1->_13 = pMatrixA->_13;
	pSH4Matrix1->_14 = pMatrixA->_14;

	pSH4Matrix1->_21 = pMatrixA->_21;
	pSH4Matrix1->_22 = pMatrixA->_22;
	pSH4Matrix1->_23 = pMatrixA->_23;
	pSH4Matrix1->_24 = pMatrixA->_24;

	pSH4Matrix1->_31 = pMatrixA->_31;
	pSH4Matrix1->_32 = pMatrixA->_32;
	pSH4Matrix1->_33 = pMatrixA->_33;
	pSH4Matrix1->_34 = pMatrixA->_34;

	pSH4Matrix1->_41 = pMatrixA->_41;
	pSH4Matrix1->_42 = pMatrixA->_42;
	pSH4Matrix1->_43 = pMatrixA->_43;
	pSH4Matrix1->_44 = pMatrixA->_44;

	/* Matrix B */
	pSH4Matrix2->_11 = pMatrixB->_11;
	pSH4Matrix2->_12 = pMatrixB->_21;
	pSH4Matrix2->_13 = pMatrixB->_31;
	pSH4Matrix2->_14 = pMatrixB->_41;

	pSH4Matrix2->_21 = pMatrixB->_12;
	pSH4Matrix2->_22 = pMatrixB->_22;
	pSH4Matrix2->_23 = pMatrixB->_32;
	pSH4Matrix2->_24 = pMatrixB->_42;

	pSH4Matrix2->_31 = pMatrixB->_13;
	pSH4Matrix2->_32 = pMatrixB->_23;
	pSH4Matrix2->_33 = pMatrixB->_33;
	pSH4Matrix2->_34 = pMatrixB->_43;

	pSH4Matrix2->_41 = pMatrixB->_14;
	pSH4Matrix2->_42 = pMatrixB->_24;
	pSH4Matrix2->_43 = pMatrixB->_34;
	pSH4Matrix2->_44 = pMatrixB->_44;

    /*
	I'm using dot product instead the proper SH4 Matrix Multiplication
				mtrx4mul (pSH4Matrix1, pSH4Matrix2); 
	*/

	/* Matrix Result */
	pResultMatrix->_11 = fipr (&pSH4Matrix1->_11, &pSH4Matrix2->_11);
	pResultMatrix->_12 = fipr (&pSH4Matrix1->_11, &pSH4Matrix2->_21);
	pResultMatrix->_13 = fipr (&pSH4Matrix1->_11, &pSH4Matrix2->_31);
	pResultMatrix->_14 = fipr (&pSH4Matrix1->_11, &pSH4Matrix2->_41);

	pResultMatrix->_21 = fipr (&pSH4Matrix1->_21, &pSH4Matrix2->_11);
	pResultMatrix->_22 = fipr (&pSH4Matrix1->_21, &pSH4Matrix2->_21);
	pResultMatrix->_23 = fipr (&pSH4Matrix1->_21, &pSH4Matrix2->_31);
	pResultMatrix->_24 = fipr (&pSH4Matrix1->_21, &pSH4Matrix2->_41);

	pResultMatrix->_31 = fipr (&pSH4Matrix1->_31, &pSH4Matrix2->_11);
	pResultMatrix->_32 = fipr (&pSH4Matrix1->_31, &pSH4Matrix2->_21);
	pResultMatrix->_33 = fipr (&pSH4Matrix1->_31, &pSH4Matrix2->_31);
	pResultMatrix->_34 = fipr (&pSH4Matrix1->_31, &pSH4Matrix2->_41);

	pResultMatrix->_41 = fipr (&pSH4Matrix1->_41, &pSH4Matrix2->_11);
	pResultMatrix->_42 = fipr (&pSH4Matrix1->_41, &pSH4Matrix2->_21);
	pResultMatrix->_43 = fipr (&pSH4Matrix1->_41, &pSH4Matrix2->_31);
	pResultMatrix->_44 = fipr (&pSH4Matrix1->_41, &pSH4Matrix2->_41);

}   


/*******************************************************************************
 * Function Name  : KMMatrixTranslate
 * Input/Output	  : *pMatrix
 * Inputs		  : fX, fY, fZ
 * Globals used   : None
 * Description    : Translate matrix pMatrix by fX, fY and fZ.
 *
 *******************************************************************************/
void KMMatrixTranslate(MATRIX *pMatrix, const float fX, const float fY, const float fZ)
{
	pMatrix->_41+=fX;
	pMatrix->_42+=fY;
	pMatrix->_43+=fZ;				
}   


/*******************************************************************************
 * Function Name  : KMMatrixScale
 * Input/Output	  : *pMatrix
 * Input		  : fFactor
 * Globals used   : None
 * Description    : Scale matrix pMatrix by the homogeneous factor fFactor.
 *
 *******************************************************************************/
void KMMatrixScale(MATRIX *pMatrix, const float fFactor)
{
	pMatrix->_11*=fFactor;	pMatrix->_12*=fFactor;	pMatrix->_13*=fFactor;	pMatrix->_14*=fFactor;	
	pMatrix->_21*=fFactor;	pMatrix->_22*=fFactor;	pMatrix->_23*=fFactor;	pMatrix->_24*=fFactor;
	pMatrix->_31*=fFactor;	pMatrix->_32*=fFactor;	pMatrix->_33*=fFactor;	pMatrix->_34*=fFactor;
	pMatrix->_41*=fFactor;	pMatrix->_42*=fFactor;	pMatrix->_43*=fFactor;	pMatrix->_44*=fFactor;
}


/*******************************************************************************
 * Function Name  : KMMatrixRotate
 * Input/Output	  : *pMatrix
 * Input		  : fXAngle, fYAngle, fZAngle
 * Globals used   : None
 * Description    : Apply rotations to matrix pMatrix
 *
 *******************************************************************************/
void KMMatrixRotate(MATRIX *pMatrix, const float fXAngle, const float fYAngle, const float fZAngle)
{
	MATRIX rot;
	float  cosine, sine;

	/* X Rotation */

    /* Precompute cos and sin */
	cosine=(float)cos(fXAngle);
    sine=(float)sin(fXAngle);
    
	/* Create the trigonometric matrix corresponding to X Rotation */
	rot._11=1.0f;			rot._12=0.0f;		rot._13=0.0f;			rot._14=0.0f;	
	rot._21=0.0f;			rot._22=cosine;		rot._23=sine;			rot._24=0.0f;	
	rot._31=0.0f;			rot._32=-sine;		rot._33=cosine;			rot._34=0.0f;	
	rot._41=0.0f;			rot._42=0.0f;		rot._43=0.0f;			rot._44=1.0f;	

	/* Multiply the given matrix with this trigonometric matrix */
	KMMatrixMultiply(pMatrix, pMatrix, &rot);

	/* Y Rotation */

	/* Precompute cos and sin */
	cosine=(float)cos(fYAngle);
    sine=(float)sin(fYAngle);
    
	/* Create the trigonometric matrix corresponding to Y Rotation */
	rot._11=cosine;			rot._12=0.0f;		rot._13=-sine;			rot._14=0.0f;	
	rot._21=0.0f;			rot._22=1.0f;		rot._23=0.0f;			rot._24=0.0f;	
	rot._31=sine;			rot._32=0.0f;		rot._33=cosine;			rot._34=0.0f;	
	rot._41=0.0f;			rot._42=0.0f;		rot._43=0.0f;			rot._44=1.0f;	

	/* Multiply the given matrix with this trigonometric matrix */
	KMMatrixMultiply(pMatrix, pMatrix, &rot);

	/* Z Rotation */
	
	/* Precompute cos and sin */
	cosine=(float)cos(fZAngle);
    sine=(float)sin(fZAngle);
    
	/* Create the trigonometric matrix corresponding to Z Rotation */
	rot._11=cosine;			rot._12=sine;		rot._13=0.0f;			rot._14=0.0f;	
	rot._21=-sine;			rot._22=cosine;		rot._23=0.0f;			rot._24=0.0f;	
	rot._31=0.0f;			rot._32=0.0f;		rot._33=1.0f;			rot._34=0.0f;	
	rot._41=0.0f;			rot._42=0.0f;		rot._43=0.0f;			rot._44=1.0f;	

	/* Multiply the given matrix with this trigonometric matrix */
	KMMatrixMultiply(pMatrix, pMatrix, &rot);
}


/*******************************************************************************
 * Function Name  : KMMatrixInverse
 * Input/Output	  : *pMatrix
 * Globals used   : None
 * Description    : Compute the inverse matrix of pMatrix.
 *					The matrix must be of the form :  
 * 					A 0
 *					C 1 
 *					Where A is a 3x3 matrix and C is a 1x3 matrix.
 *
 *******************************************************************************/
void KMMatrixInverse(MATRIX *pMatrix)
{
	MATRIX		DummyMatrix;
	double		det_1;
	double		pos, neg, temp;

    /* Calculate the determinant of submatrix A and determine if the
     * the matrix is singular as limited by the double precision
     * floating-point data representation. */
    pos = neg = 0.0;
    temp =  pMatrix->_11 * pMatrix->_22 * pMatrix->_33;
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp =  pMatrix->_12 * pMatrix->_23 * pMatrix->_31;
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp =  pMatrix->_13 * pMatrix->_21 * pMatrix->_32;
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -pMatrix->_13 * pMatrix->_22 * pMatrix->_31;
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -pMatrix->_12 * pMatrix->_21 * pMatrix->_33;
    if (temp >= 0.0) pos += temp; else neg += temp;
    temp = -pMatrix->_11 * pMatrix->_23 * pMatrix->_32;
    if (temp >= 0.0) pos += temp; else neg += temp;
    det_1 = pos + neg;

    /* Is the submatrix A singular? */
    if ((det_1 == 0.0) || (fabs(det_1 / (pos - neg)) < 1.0e-15)) 
	{
        /* Matrix M has no inverse : singular matrix */
        return;
    }
    else 
	{
        /* Calculate inverse(A) = adj(A) / det(A) */
        det_1 = 1.0 / det_1;
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
        DummyMatrix._14 = DummyMatrix._24 = DummyMatrix._34 = 0.0f;
        DummyMatrix._44 = 1.0f;
	}

   	/* Copy contents of dummy matrix in pMatrix */
	KMMatrixCopy(pMatrix, &DummyMatrix);
}


/*******************************************************************************
 * Function Name  : KMMatrixCopy
 * Input		  : *pSrcMatrix
 * Output		  : *pDstMatrix
 * Globals used   : None
 * Description    : Copy matrix pSrcMatrix into pDstMatrix
 *
 *******************************************************************************/
void KMMatrixCopy(MATRIX *pDstMatrix, const MATRIX *pSrcMatrix)
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
 * Function Name  : KMMatrixDotProduct
 * Inputs		  : VectorA, VectorB
 * Globals used   : None
 * Returns		  : float
 * Description    : Returns the dot product between vector pVectorA and pVectorB
 *
 *******************************************************************************/
float KMMatrixDotProduct(const km_vector VectorA, const km_vector VectorB)
{
	pSH4Vector1[0] = VectorA[0];
	pSH4Vector1[1] = VectorA[1];
	pSH4Vector1[2] = VectorA[2];
	pSH4Vector1[3] = 0.0f;

	pSH4Vector2[0] = VectorB[0];
	pSH4Vector2[1] = VectorB[1];
	pSH4Vector2[2] = VectorB[2];
	pSH4Vector2[3] = 0.0f;

	return (fipr(pSH4Vector1,pSH4Vector2));
}


/*******************************************************************************
 * Function Name  : KMMatrixCrossProduct
 * Inputs		  : *pVectorA, *pVectorB
 * Output		  : *pResultVector
 * Globals used   : None
 * Description    : Compute the cross product between pVectorA and pVectorB and
 *					assign the resulting vector in pResultVector.
 *
 *******************************************************************************/
void KMMatrixCrossProduct(km_vector ResultVector, const km_vector VectorA, const km_vector VectorB)
{
    km_vector result;

	/* Perform calculation on a dummy VECTOR (result) in case of ResultVector also used as Vector A or B */
    result[0] = VectorA[1] * VectorB[2] - VectorA[2] * VectorB[1];
    result[1] = VectorA[2] * VectorB[0] - VectorA[0] * VectorB[2];
    result[2] = VectorA[0] * VectorB[1] - VectorA[1] * VectorB[0];
    
	/* Copy result in pResultVector */
	ResultVector[0]=result[0];
	ResultVector[1]=result[1];
	ResultVector[2]=result[2];
}


/*******************************************************************************
 * Function Name  : KMMatrixNormalize
 * Input/Output	  : Vector
 * Globals used   : None
 * Description    : Normalize vector Vector.
 *
 *******************************************************************************/
void KMMatrixNormalize(km_vector Vector)
{
    float	fVx, fVy, fVz, fInvMod;

    /* Assign temporary variables */
	fVx=Vector[0];	
    fVy=Vector[1];
    fVz=Vector[2];
 
	/* If vector is not null, then perform normalization */
	if ((fVx==0) && (fVy==0) && (fVz==0))
	{
		/* Null vector, keep it unchanged */
		return;
	}
	
	/* Normalize */
	fInvMod=(float)(1.0f/sqrt(fVx*fVx + fVy*fVy + fVz*fVz));
	Vector[0]=fVx*fInvMod;
	Vector[1]=fVy*fInvMod;
	Vector[2]=fVz*fInvMod;
}