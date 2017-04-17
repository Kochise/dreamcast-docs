/*****************************************************************************
  Name : D3DTTrans.c
  Date : July 1998
  Platform : ANSI compatible
 
  $Revision: 1.8 $

  * Description : 
  This file is part of the TOOLS library (D3DTools.lib) used
  with the SDK demos for PowerVR series 2.

  Set of functions used for 3D transformations and projections.

  Note: HS4 built-in APIs have been added to some functions.
  

  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#include <math.h>
#include <d3d.h>
#include <shintr.h> /* For SH4 built-in APIs */
#include "D3DTMatrix.h"
#include "D3DTTrans.h"

 
/*************************************
** Prototypes of internal functions **
*************************************/
static void	CreateViewMatrix(D3DMATRIX *pViewMatrix, const D3DVECTOR *pFrom, const D3DVECTOR *pAt, const float fRoll);



/*******************************************************************************
 * Function Name  : D3DTTransComputeBoundingBox
 * Inputs		  : nNumberOfVertices, *pVertex
 * Output		  : *pBoundingBox
 * Globals used	  : None
 * Description    : Calculate the eight vertices that surround an object.
 *					This "bounding box" is used later to determine whether
 *					the object is visible or not.
 *					This function should only be called once to determine the
 *					object's bounding box.
 *
 *******************************************************************************/
void D3DTTransComputeBoundingBox(const int nNumberOfVertices, const float *pVertex, D3DTBOUNDINGBOX *pBoundingBox)
{
	int		i;
	float	MinX, MaxX, MinY, MaxY, MinZ, MaxZ;

	/* Inialise values to first vertex */
	MinX=pVertex[0];	MaxX=pVertex[0];
	MinY=pVertex[1];	MaxY=pVertex[1];
	MinZ=pVertex[2];	MaxZ=pVertex[2];

	/* Loop through all vertices to find extremas */
	for (i=1; i<nNumberOfVertices; i++)
	{
		/* Minimum and Maximum X */
		if (pVertex[3*i]<MinX) MinX=pVertex[3*i];
		if (pVertex[3*i]>MaxX) MaxX=pVertex[3*i];

		/* Minimum and Maximum Y */
		if (pVertex[3*i+1]<MinY) MinY=pVertex[3*i+1];
		if (pVertex[3*i+1]>MaxY) MaxY=pVertex[3*i+1];

		/* Minimum and Maximum Z */
		if (pVertex[3*i+2]<MinZ) MinZ=pVertex[3*i+2];
		if (pVertex[3*i+2]>MaxZ) MaxZ=pVertex[3*i+2];
	}

	/* Assign the resulting extremas to the bounding box structure */
	/* Point 0 */
	pBoundingBox->Point[0].x=MinX;
	pBoundingBox->Point[0].y=MinY;
	pBoundingBox->Point[0].z=MinZ;

	/* Point 1 */
	pBoundingBox->Point[1].x=MinX;
	pBoundingBox->Point[1].y=MinY;
	pBoundingBox->Point[1].z=MaxZ;

	/* Point 2 */
	pBoundingBox->Point[2].x=MinX;
	pBoundingBox->Point[2].y=MaxY;
	pBoundingBox->Point[2].z=MinZ;

	/* Point 3 */
	pBoundingBox->Point[3].x=MinX;
	pBoundingBox->Point[3].y=MaxY;
	pBoundingBox->Point[3].z=MaxZ;

	/* Point 4 */
	pBoundingBox->Point[4].x=MaxX;
	pBoundingBox->Point[4].y=MinY;
	pBoundingBox->Point[4].z=MinZ;

	/* Point 5 */
	pBoundingBox->Point[5].x=MaxX;
	pBoundingBox->Point[5].y=MinY;
	pBoundingBox->Point[5].z=MaxZ;

	/* Point 6 */
	pBoundingBox->Point[6].x=MaxX;
	pBoundingBox->Point[6].y=MaxY;
	pBoundingBox->Point[6].z=MinZ;

	/* Point 7 */
	pBoundingBox->Point[7].x=MaxX;
	pBoundingBox->Point[7].y=MaxY;
	pBoundingBox->Point[7].z=MaxZ;
}


/*******************************************************************************
 * Function Name  : D3DTTransTransformBoundingBox
 * Inputs		  : *pWorldMatrix, *pBoundingBox
 * Output		  : *pTBoundingBox
 * Globals used	  : None
 * Description    : Transform bounding box from Local space to World space.
 *					This function should only be used to perform collision
 *					detection in World space. To determine if an object needs 
 *					clipping using the bounding box, use IsBoundingBoxVisible(...)
 *
 *******************************************************************************/
void D3DTTransTransformBoundingBox(const D3DMATRIX *pWorldMatrix, const D3DTBOUNDINGBOX *pBoundingBox, 
								   D3DTBOUNDINGBOX *pTBoundingBox)
{
	int			i;
				
	/* Transform the 8 vertices defining the bounding box */
	for (i=0; i<8; i++)
	{
		pTBoundingBox->Point[i].x  =	pBoundingBox->Point[i].x*pWorldMatrix->_11 +
										pBoundingBox->Point[i].y*pWorldMatrix->_21 +
										pBoundingBox->Point[i].z*pWorldMatrix->_31 +
										pWorldMatrix->_41;
		pTBoundingBox->Point[i].y  =	pBoundingBox->Point[i].x*pWorldMatrix->_12 +
										pBoundingBox->Point[i].y*pWorldMatrix->_22 +
										pBoundingBox->Point[i].z*pWorldMatrix->_32 +
										pWorldMatrix->_42;
		pTBoundingBox->Point[i].z  =	pBoundingBox->Point[i].x*pWorldMatrix->_13 +
										pBoundingBox->Point[i].y*pWorldMatrix->_23 +
										pBoundingBox->Point[i].z*pWorldMatrix->_33 +
										pWorldMatrix->_43;
	}
}


/*******************************************************************************
 * Function Name  : D3DTTransIsBoundingBoxVisible
 * Inputs		  : *pWorldMatrix, *pBoundingBox, nViewportWidth, nViewportHeight,
 *					*pCamFrom, *pCamTo, fRoll,
 *					D, F, fViewAngleHoriz, fViewAngleVert
 * Output		  : *pNeedsZClipping
 * Globals used	  : None
 * Returns		  : TRUE if the object is visible, FALSE if not.
 * Description    : Determine if a bounding box is "visible" or not along the
 *					Z axis.
 *					If the function returns TRUE, the object is visible and should
 *					be displayed (check bNeedsZClipping to know if Z Clipping needs
 *					to be done).
 *					If the function returns FALSE, the object is not visible and thus
 *					does not require to be displayed.
 *					bNeedsZClipping indicates whether the object needs Z Clipping
 *					(i.e. the object is partially visible).
 *					- pWorldMatrix is the World matrix used to transform the
 *					  object.
 *					- *pBoundingBox is a pointer to the bounding box structure.
 *					- nViewportWidth and nViewportHeight are the width and height
 *					  of the rendering surface.
 *					- *pCamFrom is the camera position in World space.
 *					- *pCamTo is the World space vertex the camera is looking at.
 *					- fRoll is the camera roll value (usually 0).
 *					- D and F are the front and back clipping plane in World Space.
 *					- fViewAngleHoriz is the horizontal field of view (in radians).
 *					- fViewAngleVert is the vertical field of view (in radians).
 *					  If fViewAngleVert is 0, then the vertical field of view will
 *					  automatically be computed by the function (assuming a
 *					  SQUARE aspect ratio for the scene).
 *
 *******************************************************************************/
BOOL D3DTTransIsBoundingBoxVisible(const D3DMATRIX *pWorldMatrix, const D3DTBOUNDINGBOX *pBoundingBox, 
								   const int nViewportWidth, const int nViewportHeight,
								   const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
								   const float D, const float F, 
								   const float fViewAngleHoriz, const float fViewAngleVert,
								   BOOL *pNeedsZClipping)
{
	D3DMATRIX	TransformationMatrix, ProjectionMatrix, ViewMatrix;
	D3DVECTOR	TBoundingBox[8];
	float		fOneOverhH, fOneOverhV;
	int			i, nNumberOfVisiblePoints=0;
	
	/* Create View matrix */
	CreateViewMatrix(&ViewMatrix, pCamFrom, pCamTo, fRoll);

	/* Transformation matrix is the result of the concatenation between World and View matrices */
	D3DTMatrixMultiply(&TransformationMatrix, pWorldMatrix, &ViewMatrix);
	
	/* Compute 1 over h */
	fOneOverhH=1.0f / (D * (float)tan(fViewAngleHoriz / 2.0f));
	if (fViewAngleVert==0.0f)
	{
		fOneOverhV=1.0f / (D * (float)tan(((float)nViewportHeight/nViewportWidth) * fViewAngleHoriz / 2.0f));
	}
	else
	{
		fOneOverhV=1.0f / (D * (float)tan(fViewAngleVert / 2.0f));
	}

	/* Compute projection matrix */
	memset(&ProjectionMatrix, 0, sizeof(D3DMATRIX));
	ProjectionMatrix._11=fOneOverhH;
	ProjectionMatrix._22=fOneOverhV;
	ProjectionMatrix._33=F / (D * (F - D));
	ProjectionMatrix._34=1.0f / D;
	ProjectionMatrix._43=-F / (F - D);

	/* Transformation matrix is the result of the concatenation between World matrix 
	   (including View matrix now) and Projection matrix */
	D3DTMatrixMultiply(&TransformationMatrix, &TransformationMatrix, &ProjectionMatrix);

	/* Transform the eight bounding box vertices (z is actually W) */
	for (i=0; i<8; i++)
	{
		TBoundingBox[i].x =	pBoundingBox->Point[i].x*TransformationMatrix._11 +
							pBoundingBox->Point[i].y*TransformationMatrix._21 +
							pBoundingBox->Point[i].z*TransformationMatrix._31 +
							TransformationMatrix._41;
		TBoundingBox[i].y =	pBoundingBox->Point[i].x*TransformationMatrix._12 +
							pBoundingBox->Point[i].y*TransformationMatrix._22 +
							pBoundingBox->Point[i].z*TransformationMatrix._32 +
							TransformationMatrix._42;
		TBoundingBox[i].z =	pBoundingBox->Point[i].x*TransformationMatrix._14 +
							pBoundingBox->Point[i].y*TransformationMatrix._24 +
							pBoundingBox->Point[i].z*TransformationMatrix._34 +
							TransformationMatrix._44;
	}

	/* Default value */
	*pNeedsZClipping=FALSE;

	/* First test if object is visible on the X axis */
	/* X axis : test if -W<X */
	for (nNumberOfVisiblePoints=0, i=0; i<8; i++)
	{
		if (-TBoundingBox[i].z<TBoundingBox[i].x) 
		{
			nNumberOfVisiblePoints++;
			break;
		}
	}
	/* If no visible points, then return FALSE */
	if (!nNumberOfVisiblePoints) return FALSE;
	
	/* X axis : test if X<W */
	for (nNumberOfVisiblePoints=0, i=0; i<8; i++)
	{
		if (TBoundingBox[i].x<TBoundingBox[i].z) 
		{
			nNumberOfVisiblePoints++;
			break;
		}
	}
	/* If no visible points, then return FALSE */
	if (!nNumberOfVisiblePoints) return FALSE;
	

	/* Then test if object is visible on the Y axis */
	/* Y axis : test if -W<Y */
	for (nNumberOfVisiblePoints=0, i=0; i<8; i++)
	{
		if (-TBoundingBox[i].z<TBoundingBox[i].y) 
		{
			nNumberOfVisiblePoints++;
			break;
		}
	}
	/* If the number of visible points is 0, the object is not visible
	   and thus does not require to be displayed */
	if (!nNumberOfVisiblePoints) return FALSE;

	/* Y axis : test if Y<W */
	for (nNumberOfVisiblePoints=0, i=0; i<8; i++)
	{
		if (TBoundingBox[i].y<TBoundingBox[i].z) 
		{
			nNumberOfVisiblePoints++;
			break;
		}
	}
	/* If the number of visible points is 0, the object is not visible
	   and thus does not require to be displayed */
	if (!nNumberOfVisiblePoints) return FALSE;
	

	/* Test depth visibility of object (W<1.0f means non-visible) */
	for (nNumberOfVisiblePoints=0, i=0; i<8; i++)
	{
		if (TBoundingBox[i].z>1.0f) nNumberOfVisiblePoints++;
	}

	/* If the number of visible points is 0, the object is not visible
	   and thus does not require to be displayed */
	if (!nNumberOfVisiblePoints) return FALSE;
	
	/* If all bounding box vertices are visible, it means that the object does
	   not need to be clipped (entirely visible) */
	if (nNumberOfVisiblePoints==8) return TRUE;
	
	/* At this point, the object is partially visible, thus requires Z clipping */
	*pNeedsZClipping=TRUE;
	return TRUE;
}



/*******************************************************************************
 * Function Name  : D3DTTransTransform
 * Inputs		  : *pWorldMatrix, nNumberOfVertices, *pVertex, 
 * Output		  : *pTransformedVertex
 * Globals used	  : None
 * Description    : Transform all vertices in pVertex and store them in 
 *					pTransformedVertex. The resulting vertices are in World Space.
 *					This function should only be called if transformed vertices
 *					are required in your application.
 *					- pWorldMatrix is the World matrix used to transform the
 *					  object.
 *					- nNumberOfVertices is the number of vertices of the object.
 *					- pVertex is the pointer to untransformed object vertices.
 *					- pTransformedVertex is the pointer that will receive transformed vertices.
 *
 *******************************************************************************/
void D3DTTransTransform(const D3DMATRIX *pWorldMatrix, 
					    const int nNumberOfVertices, const float *pVertex, float *pTransformedVertex)
{
	D3DVECTOR	*pSrcVectorPointer;
	D3DVECTOR	*pDestVectorPointer;
	int			i;
				
	/* Getting Source vector pointer */
	pSrcVectorPointer=(D3DVECTOR *)&pVertex[0];

	/* Getting Destination vector pointer */
	pDestVectorPointer=(D3DVECTOR *)&pTransformedVertex[0];

	/* Transform all vertices with TransformationMatrix */
	for (i=0; i<nNumberOfVertices; i++)
	{
		pDestVectorPointer[i].x =	pSrcVectorPointer[i].x*pWorldMatrix->_11 +
									pSrcVectorPointer[i].y*pWorldMatrix->_21 +
									pSrcVectorPointer[i].z*pWorldMatrix->_31 +
									pWorldMatrix->_41;
		pDestVectorPointer[i].y =	pSrcVectorPointer[i].x*pWorldMatrix->_12 +
									pSrcVectorPointer[i].y*pWorldMatrix->_22 +
									pSrcVectorPointer[i].z*pWorldMatrix->_32 +
									pWorldMatrix->_42;
		pDestVectorPointer[i].z =	pSrcVectorPointer[i].x*pWorldMatrix->_13 +
									pSrcVectorPointer[i].y*pWorldMatrix->_23 +
									pSrcVectorPointer[i].z*pWorldMatrix->_33 +
									pWorldMatrix->_43;
	}
}


/*******************************************************************************
 * Function Name  : D3DTTransTransformProject
 * Inputs		  : *pWorldMatrix, nNumberOfVertices, *pVertex, 
 *					*pCamFrom, *pCamTo, fRoll,
 *					D, F, fViewAngleHoriz, fViewAngleVert
 * Output		  : *pTLVertex
 * Globals used	  : None
 * Description    : Transform and project all vertices in pVertex and store them 
 *					in pTLVertex. This function gives homogeneous clipping
 *					coordinates (-1, +1).
 *					Use this function to perform clipping on your data.
 *					IMPORTANT : sz will NOT be computed by this function, as 
 *					all clipping information can be contained in rhw (w).
 *					- pWorldMatrix is the World matrix used to transform the
 *					  object.
 *					- nNumberOfVertices is the number of vertices of the object.
 *					- pVertex is the pointer to untransformed object vertices.
 *					- pTLVertex is the pointer that will receive transformed vertices.
 *					- nViewportWidth and nViewportHeight are the width and height
 *					  of the rendering surface.
 *					- *pCamFrom is the camera position in World space.
 *					- *pCamTo is the World space vertex the camera is looking at.
 *					- fRoll is the camera roll value (usually 0).
 *					- D and F are the front and back clipping plane in World Space.
 *					- fViewAngleHoriz is the horizontal field of view (in radians).
 *					- fViewAngleVert is the vertical field of view (in radians).
 *					  If fViewAngleVert is 0, then the vertical field of view will
 *					  automatically be computed by the function (assuming a
 *					  SQUARE aspect ratio for the scene).
 *
 *******************************************************************************/
void D3DTTransTransformProject(const D3DMATRIX *pWorldMatrix, 
							   const int nNumberOfVertices, const float *pVertex, D3DTLVERTEX *pTLVertex,
							   const int nViewportWidth, const int nViewportHeight,
							   const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
							   const float D, const float F, 
							   const float fViewAngleHoriz, const float fViewAngleVert)
{
	float		SH4Matrix1[4], SH4Matrix2[4], SH4Matrix3[4], SH4Vector[4];
	D3DMATRIX	TransformationMatrix;
	D3DMATRIX	ViewMatrix;
	D3DMATRIX	ProjectionMatrix;
	float		fOneOverhH, fOneOverhV;
	int			i;
					
	/* Create View matrix */
	CreateViewMatrix(&ViewMatrix, pCamFrom, pCamTo, fRoll);
	
	/* Transformation matrix is the result of the concatenation between World and View matrices */
	D3DTMatrixMultiply(&TransformationMatrix, pWorldMatrix, &ViewMatrix);
	
	/* Compute 1 over h */
	fOneOverhH=1.0f / (D * (float)tan(fViewAngleHoriz / 2.0f));
	if (fViewAngleVert==0.0f)
	{
		fOneOverhV=1.0f / (D * (float)tan(((float)nViewportHeight/nViewportWidth) * fViewAngleHoriz / 2.0f));
	}
	else
	{
		fOneOverhV=1.0f / (D * (float)tan(fViewAngleVert / 2.0f));
	}

	/* Compute projection matrix */
	memset(&ProjectionMatrix, 0, sizeof(D3DMATRIX));
	ProjectionMatrix._11=fOneOverhH;
	ProjectionMatrix._22=fOneOverhV;
	ProjectionMatrix._33=F / (D * (F - D));
	ProjectionMatrix._34=1.0f / D;
	ProjectionMatrix._43=-F / (F - D);

	/* Transformation matrix is the result of the concatenation between World matrix 
	   (including View matrix now) and Projection matrix */
	D3DTMatrixMultiply(&TransformationMatrix, &TransformationMatrix, &ProjectionMatrix);

	/* HS4 Vectors for dot product */
	SH4Matrix1[0] = TransformationMatrix._11; SH4Matrix1[1] = TransformationMatrix._21;
	SH4Matrix1[2] = TransformationMatrix._31; SH4Matrix1[3] = TransformationMatrix._41;

	SH4Matrix2[0] = TransformationMatrix._12; SH4Matrix2[1] = TransformationMatrix._22;
	SH4Matrix2[2] = TransformationMatrix._32; SH4Matrix2[3] = TransformationMatrix._42;

	SH4Matrix3[0] = TransformationMatrix._14; SH4Matrix3[1] = TransformationMatrix._24;
	SH4Matrix3[2] = TransformationMatrix._34; SH4Matrix3[3] = TransformationMatrix._44;

	SH4Vector[3] = 1.0f;

	/* Transform all vertices with TransformationMatrix */
	for (i=0; i<nNumberOfVertices; i++)
	{
		SH4Vector[0] =  *pVertex++;
		SH4Vector[1] =  *pVertex++;
		SH4Vector[2] =  *pVertex++;
		
		pTLVertex[i].sx =	_Dot4dV(SH4Vector, SH4Matrix1);
		pTLVertex[i].sy =	_Dot4dV(SH4Vector, SH4Matrix2);
		pTLVertex[i].rhw =	_Dot4dV(SH4Vector, SH4Matrix3);		/* rhw=w for now */
	}

	/* At this point, all vertices are projected and homogeneous (clipping coordinates) */
}


/*******************************************************************************
 * Function Name  : D3DTTransPerspective
 * Inputs		  : nNumberOfVertices, 
 *					nViewportWidth, nViewportHeight,
 *					D, F
 * Input/Output	  : *pTLVertex
 * Globals used	  : None
 * Description    : Perform perspective division and get screen coordinates from
 *					vertices in *pTLVertex. 
 *					This function should be called after transformation, projection
 *					and (if required) clipping of your model data.
 *					- nNumberOfVertices is the number of vertices of the object.
 *					- pTLVertex is the pointer to vertices that will become
 *					  screen coordinates.
 *					- nViewportWidth and nViewportHeight are the width and height
 *					  of the rendering surface.
 *					- D and F are the front and back clipping plane in World Space.
 *
 *******************************************************************************/
void D3DTTransPerspective(const int nNumberOfVertices, D3DTLVERTEX *pTLVertex,
						  const int nViewportWidth, const int nViewportHeight,
						  const float D, const float F)
{
	float		fRHW, fApprox;
	int			i, nHalfWidth, nNegHalfHeight;

	/* Compute fApprox (could be made equal to 1 when F >> D) */
	fApprox=F / (F - D);
	
	/* Compute half viewport dimensions */
	nHalfWidth		= nViewportWidth / 2;
	nNegHalfHeight	= -(nViewportHeight / 2);
	
	/* Optimised calculation */
	for (i=0; i<nNumberOfVertices; i++)
	{
		/* Compute rhw = 1/w */
		fRHW=1.0f / pTLVertex[i].rhw;

		/* Set TLVertex values */
		pTLVertex[i].rhw= fRHW;
		pTLVertex[i].sx	=	 nHalfWidth  * fRHW * pTLVertex[i].sx + nHalfWidth;
		pTLVertex[i].sy	= nNegHalfHeight * fRHW * pTLVertex[i].sy - nNegHalfHeight;
		pTLVertex[i].sz	= fApprox * (1.0f - fRHW);
	}
}


/*******************************************************************************
 * Function Name  : D3DTTransTransformProjectPerspective
 * Inputs		  : *pWorldMatrix, nNumberOfVertices, *pVertex, 
 *					nViewportWidth, nViewportHeight,
 *					*pCamFrom, *pCamTo, fRoll,
 *					D, F, fViewAngleHoriz, fViewAngleVert
 * Output		  : *pTLVertex
 * Globals used	  : None
 * Description    : Transform and project all vertices in pVertex and store them 
 *					in pTLVertex. This function directly gives screen coordinates
 *					ready to be used by D3D. Should be used when no clipping is
 *					required.
 *					- pWorldMatrix is the World matrix used to transform the
 *					  object.
 *					- nNumberOfVertices is the number of vertices of the object.
 *					- pVertex is the pointer to untransformed object vertices.
 *					- pTLVertex is the pointer that will receive transformed vertices.
 *					- nViewportWidth and nViewportHeight are the width and height
 *					  of the rendering surface.
 *					- *pCamFrom is the camera position in World space.
 *					- *pCamTo is the World space vertex the camera is looking at.
 *					- fRoll is the camera roll value (usually 0).
 *					- D and F are the front and back clipping plane in World Space.
 *					- fViewAngleHoriz is the horizontal field of view (in radians).
 *					- fViewAngleVert is the vertical field of view (in radians).
 *					  If fViewAngleVert is 0, then the vertical field of view will
 *					  automatically be computed by the function (assuming a
 *					  SQUARE aspect ratio for the scene).
 *
 *******************************************************************************/
void D3DTTransTransformProjectPerspective(const D3DMATRIX *pWorldMatrix, 
										  const int nNumberOfVertices, const float *pVertex, D3DTLVERTEX *pTLVertex,
										  const int nViewportWidth, const int nViewportHeight,
										  const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
										  const float D, const float F, 
										  const float fViewAngleHoriz, const float fViewAngleVert)
{
	D3DMATRIX	TransformationMatrix, ViewMatrix, ProjectionMatrix;
	D3DVECTOR	*pVectorPointer, WorldUp={ 0.0f, 1.0f, 0.0f };
	int			i, nHalfWidth, nNegHalfHeight;
	float		fOneOverhH, fOneOverhV, fRHW, fApprox;
	float		SH4Matrix1[4], SH4Matrix2[4], SH4Matrix3[4], SH4Vector[4];
				
	/* Create View matrix */
	CreateViewMatrix(&ViewMatrix, pCamFrom, pCamTo, fRoll);
	
	/* Transformation matrix is the result of the concatenation between World and View matrices */
	D3DTMatrixMultiply(&TransformationMatrix, pWorldMatrix, &ViewMatrix);
	
	/* Compute 1 over h */
	fOneOverhH=1.0f / (D * (float)tan(fViewAngleHoriz / 2.0f));
	if (fViewAngleVert==0.0f)
	{
		fOneOverhV=1.0f / (D * (float)tan(((float)nViewportHeight/nViewportWidth) * fViewAngleHoriz / 2.0f));
	}
	else
	{
		fOneOverhV=1.0f / (D * (float)tan(fViewAngleVert / 2.0f));
	}

	/* Compute fApprox (could be made equal to 1 when F >> D) */
	fApprox=F / (F - D);

	/* Compute projection matrix */
	memset(&ProjectionMatrix, 0, sizeof(D3DMATRIX));
	ProjectionMatrix._11=fOneOverhH;
	ProjectionMatrix._22=fOneOverhV;
	ProjectionMatrix._33=F / ( D * (F - D) );
	ProjectionMatrix._34=1.0f / D;
	ProjectionMatrix._43=-F / (F - D);

	/* Transformation matrix is the result of the concatenation between World matrix 
	   (including View matrix now) and Projection matrix */
	D3DTMatrixMultiply(&TransformationMatrix, &TransformationMatrix, &ProjectionMatrix);

	/* Compute half viewport dimensions */
	nHalfWidth		= nViewportWidth / 2;
	nNegHalfHeight	= -(nViewportHeight / 2);
	
	/* Getting vector pointer */
	pVectorPointer=(D3DVECTOR *)&pVertex[0];

	/* HS4 Vectors for dot product */
	SH4Matrix1[0] = TransformationMatrix._11; SH4Matrix1[1] = TransformationMatrix._21;
	SH4Matrix1[2] = TransformationMatrix._31; SH4Matrix1[3] = TransformationMatrix._41;

	SH4Matrix2[0] = TransformationMatrix._12; SH4Matrix2[1] = TransformationMatrix._22;
	SH4Matrix2[2] = TransformationMatrix._32; SH4Matrix2[3] = TransformationMatrix._42;

	SH4Matrix3[0] = TransformationMatrix._14; SH4Matrix3[1] = TransformationMatrix._24;
	SH4Matrix3[2] = TransformationMatrix._34; SH4Matrix3[3] = TransformationMatrix._44;

	SH4Vector[3] = 1.0f;

	/* Transform all vertices with TransformationMatrix */
	for (i=0; i<nNumberOfVertices; i++)
	{
		SH4Vector[0] =  *pVertex++;
		SH4Vector[1] =  *pVertex++;
		SH4Vector[2] =  *pVertex++;
		
		pTLVertex[i].sx =	_Dot4dV(SH4Vector, SH4Matrix1);
		pTLVertex[i].sy =	_Dot4dV(SH4Vector, SH4Matrix2);
		pTLVertex[i].rhw =	_Dot4dV(SH4Vector, SH4Matrix3);		/* rhw=w for now */

		/* At this point, all vertices are projected and homogeneous (clipping coordinates) */
	
		/* Compute rhw = 1/w */
		fRHW=1.0f / pTLVertex[i].rhw;

		/* Set TLVertex values */
		pTLVertex[i].rhw= fRHW;
		pTLVertex[i].sx	=	 nHalfWidth  * fRHW * pTLVertex[i].sx + nHalfWidth;
		pTLVertex[i].sy	= nNegHalfHeight * fRHW * pTLVertex[i].sy - nNegHalfHeight;
		pTLVertex[i].sz	= fApprox * (1.0f - fRHW);
	}
}


/*******************************************************************************
 * Function Name  : D3DTTransTransformProjectZSlamPerspective
 * Inputs		  : *pWorldMatrix, nNumberOfVertices, *pVertex, 
 *					nViewportWidth, nViewportHeight,
 *					*pCamFrom, *pCamTo, fRoll,
 *					D, F, fViewAngleHoriz, fViewAngleVert
 * Output		  : *pTLVertex
 * Globals used	  : None
 * Description    : Transform and project all vertices in pVertex and store them 
 *					in pTLVertex. This function directly gives screen coordinates
 *					ready to be used by D3D. Any W values below 1 will be clamped
 *					to 1.
 *					- pWorldMatrix is the World matrix used to transform the
 *					  object.
 *					- nNumberOfVertices is the number of vertices of the object.
 *					- pVertex is the pointer to untransformed object vertices.
 *					- pTLVertex is the pointer that will receive transformed vertices.
 *					- nViewportWidth and nViewportHeight are the width and height
 *					  of the rendering surface.
 *					- *pCamFrom is the camera position in World space.
 *					- *pCamTo is the World space vertex the camera is looking at.
 *					- fRoll is the camera roll value (usually 0).
 *					- D and F are the front and back clipping plane in World Space.
 *					- fViewAngleHoriz is the horizontal field of view (in radians).
 *					- fViewAngleVert is the vertical field of view (in radians).
 *					  If fViewAngleVert is 0, then the vertical field of view will
 *					  automatically be computed by the function (assuming a
 *					  SQUARE aspect ratio for the scene).
 *
 *******************************************************************************/
void D3DTTransTransformProjectZSlamPerspective(const D3DMATRIX *pWorldMatrix, 
											   const int nNumberOfVertices, const float *pVertex, D3DTLVERTEX *pTLVertex,
											   const int nViewportWidth, const int nViewportHeight,
											   const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
											   const float D, const float F, 
											   const float fViewAngleHoriz, const float fViewAngleVert)
{
	D3DMATRIX	TransformationMatrix, ViewMatrix, ProjectionMatrix;
	D3DVECTOR	WorldUp={ 0.0f, 1.0f, 0.0f };
	int			i, nHalfWidth, nNegHalfHeight;
	float		fOneOverhH, fOneOverhV, fRHW, fApprox;
	float		SH4Matrix1[4], SH4Matrix2[4], SH4Matrix3[4], SH4Vector[4];
	float		fX, fY, fZ;
			
	/* Create View matrix */
	CreateViewMatrix(&ViewMatrix, pCamFrom, pCamTo, fRoll);
	
	/* Transformation matrix is the result of the concatenation between World and View matrices */
	D3DTMatrixMultiply(&TransformationMatrix, pWorldMatrix, &ViewMatrix);
	
	/* Compute 1 over h */
	fOneOverhH=1.0f / (D * (float)tan(fViewAngleHoriz / 2.0f));
	if (fViewAngleVert==0.0f)
	{
		fOneOverhV=1.0f / (D * (float)tan(((float)nViewportHeight/nViewportWidth) * fViewAngleHoriz / 2.0f));
	}
	else
	{
		fOneOverhV=1.0f / (D * (float)tan(fViewAngleVert / 2.0f));
	}

	/* Compute fApprox (could be made equal to 1 when F >> D) */
	fApprox= F / (F - D);

	/* Compute projection matrix */
	memset(&ProjectionMatrix, 0, sizeof(D3DMATRIX));
	ProjectionMatrix._11=fOneOverhH;
	ProjectionMatrix._22=fOneOverhV;
	ProjectionMatrix._33=F / (D * (F - D));
	ProjectionMatrix._34=1.0f / D;
	ProjectionMatrix._43=-F / (F - D);

	/* Transformation matrix is the result of the concatenation between World matrix 
	   (including View matrix now) and Projection matrix */
	D3DTMatrixMultiply(&TransformationMatrix, &TransformationMatrix, &ProjectionMatrix);

	/* Compute half viewport dimensions */
	nHalfWidth		= nViewportWidth / 2;
	nNegHalfHeight	= -(nViewportHeight / 2);
	
	/* HS4 Vectors for dot product */
	SH4Matrix1[0] = TransformationMatrix._11; SH4Matrix1[1] = TransformationMatrix._21;
	SH4Matrix1[2] = TransformationMatrix._31; SH4Matrix1[3] = TransformationMatrix._41;

	SH4Matrix2[0] = TransformationMatrix._12; SH4Matrix2[1] = TransformationMatrix._22;
	SH4Matrix2[2] = TransformationMatrix._32; SH4Matrix2[3] = TransformationMatrix._42;

	SH4Matrix3[0] = TransformationMatrix._14; SH4Matrix3[1] = TransformationMatrix._24;
	SH4Matrix3[2] = TransformationMatrix._34; SH4Matrix3[3] = TransformationMatrix._44;

	SH4Vector[3] = 1.0f;

	/* Transform all vertices with TransformationMatrix */
	for (i=0; i<nNumberOfVertices; i++)
	{
		SH4Vector[0] =  *pVertex++;
		SH4Vector[1] =  *pVertex++;
		SH4Vector[2] =  *pVertex++;
		SH4Vector[3] =  1.0f;
		
		fX = _Dot4dV(SH4Vector, SH4Matrix1);
		fY = _Dot4dV(SH4Vector, SH4Matrix2);
		fZ = _Dot4dV(SH4Vector, SH4Matrix3);		/* rhw=w for now */

			/* Z Slamming (rhw is actually still w at this point) */
		if (fZ<1.0f)
		{
			fZ=1.0f;
		}

		/* Compute rhw = 1/w */
		fRHW=1.0f / fZ;

		/* Set TLVertex values */
		pTLVertex[i].rhw= fRHW;
		pTLVertex[i].sx	= nHalfWidth  * fRHW * fX + nHalfWidth;
		pTLVertex[i].sy	= nNegHalfHeight * fRHW * fY - nNegHalfHeight;
		pTLVertex[i].sz	= fApprox * (1.0f - fRHW);
	}
}


/*******************************************************************************
 * Function Name  : D3DTTransZClipProjectedVertices
 * Inputs		  : nNumberOfVertices, *pTLVertex, 
 *					nNumberOfTriangles, 
 * Input/Output	  : *pTriangleList
 * Output		  : *pNumberOfVisibleTriangles
 * Globals used	  : None
 * Description    : This function culls non-visible triangle and clamp out-of-bounds
 *					w values to the minimum value (1.0f)
 *					The rhw values are actually w at this stage (before perspective
 *					division)
 *
 *******************************************************************************/
void D3DTTransZClipProjectedVertices(const int nNumberOfVertices, D3DTLVERTEX *pTLVertex,
									 const int nNumberOfTriangles, WORD *pTriangleList, 
									 int *pNumberOfVisibleTriangles)
{
	WORD	P1, P2, P3;
	int		nNumberOfVisibleTriangles;
	int		i=0;

	/* Get total number of triangles */
	nNumberOfVisibleTriangles=nNumberOfTriangles;
	
	/* Loop through all triangles and check if they are visible */
	while (i<nNumberOfVisibleTriangles)
	{
		/* Get 3 vertex numbers of current triangle */
		P1=pTriangleList[3*i];
		P2=pTriangleList[3*i+1];
		P3=pTriangleList[3*i+2];

		/* Test if the 3 vertices defining the triangle are not visible (below 1) */
		if ( (pTLVertex[P1].rhw<=1.0f) &&
			 (pTLVertex[P2].rhw<=1.0f) &&
			 (pTLVertex[P3].rhw<=1.0f) )
		{
			/* Triangle is not visible, decrease number of visible triangles */
			nNumberOfVisibleTriangles--;
				
			/* Swap triangles in triangle list */
			pTriangleList[3*i]=  pTriangleList[3*nNumberOfVisibleTriangles];
			pTriangleList[3*i+1]=pTriangleList[3*nNumberOfVisibleTriangles+1];
			pTriangleList[3*i+2]=pTriangleList[3*nNumberOfVisibleTriangles+2];
			pTriangleList[3*nNumberOfVisibleTriangles]=  P1;
			pTriangleList[3*nNumberOfVisibleTriangles+1]=P2;
			pTriangleList[3*nNumberOfVisibleTriangles+2]=P3;
		}
		else
		{
			/* Triangle is visible, increment i */
			i++;
		}
	}

	/* Give final number of visible triangles */
	*pNumberOfVisibleTriangles=nNumberOfVisibleTriangles;

	/* W values below 1.0f are set to 1.0f */
	for (i=0; i<nNumberOfVertices; i++)
	{
		if (pTLVertex[i].rhw<=1.0f)
		{
			pTLVertex[i].rhw=1.0f;
		}
	}
}


/****************************************************************************
 * Function Name  : D3DTTransUVEnvMap
 * Inputs		  : pWorldMatrix, nNumberOfVertices, pNormals,
 *					pCamFrom, pCamTo, fRoll
 * Output		  : *pTLVertex
 * Globals used	  : None
 * Description    : Sets the 'tu and 'tv' values in the D3DTLVERTEX's for
 *					environment (aka chrome) wrapping.
 ***************************************************************************/
void D3DTTransUVEnvMap(const D3DMATRIX *pWorldMatrix,
					   const int nNumberOfVertices, const float *pNormals, D3DTLVERTEX *pTLVertex,
					   const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll)
{
	D3DMATRIX	mView, mTrans;
	float		fTmp;
	int			nVert;

	/* Create View matrix */
	CreateViewMatrix(&mView, pCamFrom, pCamTo, fRoll);

	/* Transformation matrix is the result of the concatenation between World and View matrices */
	D3DTMatrixMultiply(&mTrans, pWorldMatrix, &mView);

	/* Transform all vertices with TransformationMatrix */
	nVert = nNumberOfVertices;
	while(nVert--) 
	{
		/* Calculate X */
		fTmp =	pNormals[3 * nVert + 0] * mTrans._11 +
				pNormals[3 * nVert + 1] * mTrans._21 +
				pNormals[3 * nVert + 2] * mTrans._31 +
				mTrans._41;

		/* Set texture coordinate U */
		pTLVertex[nVert].tu = fTmp / 2 + 0.5f;


		/* Calculate Y */
		fTmp =	pNormals[3 * nVert + 0] * mTrans._12 +
				pNormals[3 * nVert + 1] * mTrans._22 +
				pNormals[3 * nVert + 2] * mTrans._32 +
				mTrans._42;

		/* Set texture coordinate V */
		pTLVertex[nVert].tv = fTmp / 2 + 0.5f;
	}
}
/*******************************************************************************
 * Function Name  : 
 * Inputs		  : 
 * Output		  : 
 * Globals used	  : 
 * Description    : 
 *******************************************************************************/
void D3DTTransCalculateVPMatrix(D3DMATRIX *pViewMatrix, D3DMATRIX *pProjMatrix,
											   const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
											   const float D, const float F, 
											   const float fViewAngleHoriz, const float fViewAngleVert)
{
D3DVECTOR	WorldUp={ 0.0f, 1.0f, 0.0f };
float		fOneOverhH, fOneOverhV, fApprox;
				
	/* Create View matrix */
	CreateViewMatrix(pViewMatrix, pCamFrom, pCamTo, fRoll);

	/* Compute 1 over h */
	fOneOverhH=1.0f / (D * (float)tan(fViewAngleHoriz / 2.0f));
	if (fViewAngleVert==0.0f)
	{
		fOneOverhV=1.0f / (D * (float)tan(fViewAngleHoriz / 2.0f));
	}
	else
	{
		fOneOverhV=1.0f / (D * (float)tan(fViewAngleVert / 2.0f));
	}

	/* Compute fApprox (could be made equal to 1 when F >> D) */
	fApprox= F / (F - D);

	/* Compute projection matrix */
	memset(pProjMatrix, 0, sizeof(D3DMATRIX));
	pProjMatrix->_11	=	fOneOverhH;
	pProjMatrix->_22	=	fOneOverhV;
	pProjMatrix->_33	=	F / (D * (F - D));
	pProjMatrix->_34	=	1.0f / D;
	pProjMatrix->_43	=	-F / (F - D);

}
/******************************************************
****************** INTERNAL FUNCTIONS *****************
******************************************************/


/*******************************************************************************
 * Function Name  : CreateViewMatrix
 * Inputs		  : *pFrom, *pAt, fRoll
 * Output		  : *pViewMatrix
 * Globals used	  : None
 * Description    : Create a view matrix.
 *					- *pFrom is the camera position.
 *					- *pAt is the position the camera is pointing to.
 *					- fRoll is the roll value (if required)
 *
 *******************************************************************************/
void CreateViewMatrix(D3DMATRIX *pViewMatrix, const D3DVECTOR *pFrom, const D3DVECTOR *pAt, const float fRoll)
{
    D3DMATRIX	DummyMatrix;
    D3DVECTOR	Up, Right, ViewDir;
	D3DVECTOR	WorldUp={0.0f, 1.0f, 0.0f};
    
    /* Reset matrix */
	D3DTMatrixReset(pViewMatrix);

	/* Compute view vector */
	ViewDir.x=pAt->x-pFrom->x;
	ViewDir.y=pAt->y-pFrom->y;
	ViewDir.z=pAt->z-pFrom->z;
	
	/* Normalise view vector */
	D3DTMatrixNormalize(&ViewDir);

	/* Compute cross products */
	D3DTMatrixCrossProduct(&Right, &WorldUp, &ViewDir);
	
	/* If ViewDir is colinear to WorldUp (i.e. ViewDir.x=ViewDir.z=0.0f) arrange Right */
	if (Right.x==0.0f && Right.y==0.0f && Right.z==0.0f)
	{
		Right.z=1.0f;
	}
    D3DTMatrixCrossProduct(&Up, &ViewDir, &Right);
    
    /* Normalise resulting vectors */
	D3DTMatrixNormalize(&Right);
    D3DTMatrixNormalize(&Up);
    
    /* Fill View matrix */
	pViewMatrix->_11 = Right.x;
    pViewMatrix->_21 = Right.y;
    pViewMatrix->_31 = Right.z;
    pViewMatrix->_12 = Up.x;
    pViewMatrix->_22 = Up.y;
    pViewMatrix->_32 = Up.z;
    pViewMatrix->_13 = ViewDir.x;
    pViewMatrix->_23 = ViewDir.y;
    pViewMatrix->_33 = ViewDir.z;
	pViewMatrix->_41 = -D3DTMatrixDotProduct(&Right, pFrom);
    pViewMatrix->_42 = -D3DTMatrixDotProduct(&Up, pFrom);
    pViewMatrix->_43 = -D3DTMatrixDotProduct(&ViewDir, pFrom);
    
    /* Add roll to the View matrix if requested */
	if (fRoll!=0.0f) 
	{
        D3DTMatrixReset(&DummyMatrix);
		D3DTMatrixRotate(&DummyMatrix, 0.0f, 0.0f, -fRoll);
		D3DTMatrixMultiply(pViewMatrix, pViewMatrix, &DummyMatrix);
    }
}