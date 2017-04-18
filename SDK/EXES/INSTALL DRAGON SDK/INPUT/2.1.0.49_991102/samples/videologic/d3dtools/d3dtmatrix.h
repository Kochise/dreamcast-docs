/*****************************************************************************
  Name : D3DTMatrix.h
  Date : July 1998
  Platform : ANSI compatible
 
  Description : Header file of D3DTMatrix.c
				Contains structure definitions and prototypes 
				of all functions in D3DTMatrix.c

  
  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#ifndef _D3DTMATRIX_H_
#define _D3DTMATRIX_H_

#ifdef __cplusplus
extern "C" {
#endif


/***************
** Prototypes **
***************/
/* Matrix functions */
void	D3DTMatrixReset(D3DMATRIX *pMatrix);
void	D3DTMatrixMultiply(D3DMATRIX *pResultMatrix, const D3DMATRIX *pMatrixA, const D3DMATRIX *pMatrixB);
void	D3DTMatrixTranslate(D3DMATRIX *pMatrix, const float fX, const float fY, const float fZ);
void	D3DTMatrixScale(D3DMATRIX *pMatrix, const float fFactor);
void	D3DTMatrixRotate(D3DMATRIX *pMatrix, const float fXAngle, const float fYAngle, const float fZAngle);
void	D3DTMatrixInverse(D3DMATRIX *pMatrix);
void	D3DTMatrixCopy(D3DMATRIX *pDstMatrix, const D3DMATRIX *pSrcMatrix);

/* Vector functions */
float	D3DTMatrixDotProduct(const D3DVECTOR *pVectorA, const D3DVECTOR *pVectorB);
void	D3DTMatrixCrossProduct(D3DVECTOR *pResultVector, const D3DVECTOR *pVectorA, const D3DVECTOR *pVectorB);
void	D3DTMatrixNormalize(D3DVECTOR *pVector);


#ifdef __cplusplus
}
#endif
	

#endif

