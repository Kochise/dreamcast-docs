/*****************************************************************************
  Name : KMTransform.c
  Date : August 1998
  Platform : ANSI compatible
 
  * Description : 
  This file is part of the KAMUI TOOLS library (KMTools.lib) used
  with the SDK demos for PowerVR series 2.

  Set of functions used for 3D transformations and projections.
  

  Copyright : 1998 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#include <Machine.h>
#include <math.h>

#include "KMTools.h"

/*************************************/
/*  ALIGNED GLOBALS FOR SH4 ROUTINES */
/*************************************/

unsigned long	Buffer0[70];
#define	pSH4Matrix		((MATRIX *)(((unsigned long)Buffer0+7)&0xFFFFFFF8))

unsigned long	Buffer1[10];
#define	pSH4Vector		((float *)(((unsigned long)Buffer1+7)&0xFFFFFFF8))


/*************************************
** Prototypes of internal functions **
*************************************/
static void	CreateViewMatrix(MATRIX *pViewMatrix, const km_vector From, const km_vector At, const float fRoll);


void ZeroMemory(void *pBuffer, unsigned size)
{
unsigned char *pPointer;

    pPointer = (unsigned char *)pBuffer;

	while(size--)
	{
		*pPointer++ = 0;
	}
}
/*******************************************************************************
 * Function Name  : KMTransComputeBoundingBox
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
void KMTransComputeBoundingBox(const int nNumberOfVertices, const float *pVertex, BOUNDINGBOX *pBoundingBox)
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
	pBoundingBox->Point[0][0]=MinX;
	pBoundingBox->Point[0][1]=MinY;
	pBoundingBox->Point[0][2]=MinZ;

	/* Point 1 */
	pBoundingBox->Point[1][0]=MinX;
	pBoundingBox->Point[1][1]=MinY;
	pBoundingBox->Point[1][2]=MaxZ;

	/* Point 2 */
	pBoundingBox->Point[2][0]=MinX;
	pBoundingBox->Point[2][1]=MaxY;
	pBoundingBox->Point[2][2]=MinZ;

	/* Point 3 */
	pBoundingBox->Point[3][0]=MinX;
	pBoundingBox->Point[3][1]=MaxY;
	pBoundingBox->Point[3][2]=MaxZ;

	/* Point 4 */
	pBoundingBox->Point[4][0]=MaxX;
	pBoundingBox->Point[4][1]=MinY;
	pBoundingBox->Point[4][2]=MinZ;

	/* Point 5 */
	pBoundingBox->Point[5][0]=MaxX;
	pBoundingBox->Point[5][1]=MinY;
	pBoundingBox->Point[5][2]=MaxZ;

	/* Point 6 */
	pBoundingBox->Point[6][0]=MaxX;
	pBoundingBox->Point[6][1]=MaxY;
	pBoundingBox->Point[6][2]=MinZ;

	/* Point 7 */
	pBoundingBox->Point[7][0]=MaxX;
	pBoundingBox->Point[7][1]=MaxY;
	pBoundingBox->Point[7][2]=MaxZ;
}


/*******************************************************************************
 * Function Name  : KMTransTransformBoundingBox
 * Inputs		  : *pWorldMatrix, *pBoundingBox
 * Output		  : *pTBoundingBox
 * Globals used	  : None
 * Description    : Transform bounding box from Local space to World space.
 *					This function should only be used to perform collision
 *					detection in World space. To determine if an object needs 
 *					clipping using the bounding box, use IsBoundingBoxVisible(...)
 *
 *******************************************************************************/
void KMTransTransformBoundingBox(const MATRIX *pWorldMatrix, const BOUNDINGBOX *pBoundingBox, 
						  BOUNDINGBOX *pTBoundingBox)
{
	int			i;
				
	/* Getting ready our matrix for Hitachi builtin rutines */
	/* Realise I just change the order to get the matrix in */
	/* usable fashion for vector operations.                */
	pSH4Matrix->_11 = pWorldMatrix->_11;
	pSH4Matrix->_12 = pWorldMatrix->_21;
	pSH4Matrix->_13 = pWorldMatrix->_31;
	pSH4Matrix->_14 = pWorldMatrix->_41;

	pSH4Matrix->_21 = pWorldMatrix->_12;
	pSH4Matrix->_22 = pWorldMatrix->_22;
	pSH4Matrix->_23 = pWorldMatrix->_32;
	pSH4Matrix->_24 = pWorldMatrix->_42;

	pSH4Matrix->_31 = pWorldMatrix->_14;
	pSH4Matrix->_32 = pWorldMatrix->_24;
	pSH4Matrix->_33 = pWorldMatrix->_34;
	pSH4Matrix->_34 = pWorldMatrix->_44;

	/* Transform all vertices with TransformationMatrix */
	for (i=0; i<8; i++)
	{
		pSH4Vector[0] = pBoundingBox->Point[i][0];
		pSH4Vector[1] = pBoundingBox->Point[i][1];
		pSH4Vector[2] = pBoundingBox->Point[i][2];
		pSH4Vector[3] = 1.0f;

		/* fipr calculates the dot product      */ 
		/* (Use 32bits aligned variables ONLY)  */
		pTBoundingBox->Point[i][0] =  fipr (pSH4Vector, &pSH4Matrix->_11);
		pTBoundingBox->Point[i][1] =  fipr (pSH4Vector, &pSH4Matrix->_21);
		pTBoundingBox->Point[i][2] =  fipr (pSH4Vector, &pSH4Matrix->_31);
	}
}


/*******************************************************************************
 * Function Name  : KMTransIsBoundingBoxVisible
 * Inputs		  : *pWorldMatrix, *pBoundingBox
 * Output		  : *pTBoundingBox
 * Globals used	  : None
 * Returns		  : TRUE if the object is visible, FALSE if not.
 * Description    : Determine if a bounding box is "visible" or not.
 *					If the function returns TRUE, the object is visible and should
 *					be displayed (check bNeedsZClipping to know if Z Clipping needs
 *					to be done). (XY clipping needn't to be done as TA does it
 *					for you)
 *					If the function returns FALSE, the object is not visible and thus
 *					does not require to be displayed.
 *					bNeedsZClipping indicates whether the object needs Z Clipping
 *					(i.e. the object is partially visible).
 *
 *******************************************************************************/
BOOL KMTransIsBoundingBoxVisible(const MATRIX *pWorldMatrix, const BOUNDINGBOX *pBoundingBox, 
						  const km_vector CamFrom, const km_vector CamTo, const float fRoll,
						  const float D, const float F, const float fViewAngle,
						  BOOL *pNeedsZClipping)
{
	MATRIX		TransformationMatrix, ProjectionMatrix, ViewMatrix;
	km_vector	TBoundingBox[8];
	float		h, X, Y, W;
	int			i, nNumberOfVisiblePoints=0;

	/* Create View matrix */
	CreateViewMatrix(&ViewMatrix, CamFrom, CamTo, fRoll);

	/* Transformation matrix is the result of the concatenation between World and View matrices */
	KMMatrixMultiply(&TransformationMatrix, pWorldMatrix, &ViewMatrix);
	
	/* Compute h corresponding to Field Of View and Front Clipping plane */
	h=D*(float)tan(fViewAngle/2.0f);

	/* Compute projection matrix */
	ZeroMemory(&ProjectionMatrix, sizeof(MATRIX));
	ProjectionMatrix._11=1.0f;
	ProjectionMatrix._22=1.0f;
	ProjectionMatrix._33=h*F/(D*(F-D));
	ProjectionMatrix._34=h/D;
	ProjectionMatrix._43=-h*F/(F-D);

	/* Transformation matrix is the result of the concatenation between World matrix 
	   (including View matrix now) and Projection matrix */
	KMMatrixMultiply(&TransformationMatrix, &TransformationMatrix, &ProjectionMatrix);

	/* Getting ready our matrix for Hitachi builtin rutines */
	/* Realise I just change the order to get the matrix in */
	/* usable fashion for vector operations.                */
	pSH4Matrix->_11 = TransformationMatrix._11;
	pSH4Matrix->_12 = TransformationMatrix._21;
	pSH4Matrix->_13 = TransformationMatrix._31;
	pSH4Matrix->_14 = TransformationMatrix._41;

	pSH4Matrix->_21 = TransformationMatrix._12;
	pSH4Matrix->_22 = TransformationMatrix._22;
	pSH4Matrix->_23 = TransformationMatrix._32;
	pSH4Matrix->_24 = TransformationMatrix._42;

	pSH4Matrix->_31 = TransformationMatrix._14;
	pSH4Matrix->_32 = TransformationMatrix._24;
	pSH4Matrix->_33 = TransformationMatrix._34;
	pSH4Matrix->_34 = TransformationMatrix._44;

	/* Transform all vertices with TransformationMatrix */
	for (i=0; i<8; i++)
	{
		pSH4Vector[0] = pBoundingBox->Point[i][0];
		pSH4Vector[1] = pBoundingBox->Point[i][1];
		pSH4Vector[2] = pBoundingBox->Point[i][2];
		pSH4Vector[3] = 1.0f;

		/* fipr calculates the dot product      */ 
		/* (Use 32bits aligned variables ONLY)  */
		TBoundingBox[i][0] =  fipr (pSH4Vector, &pSH4Matrix->_11);
		TBoundingBox[i][1] =  fipr (pSH4Vector, &pSH4Matrix->_21);
		TBoundingBox[i][2] =  fipr (pSH4Vector, &pSH4Matrix->_31);
	}

	/* At this point, we got the transformed 8 vertices (clipping coordinates) */

	/* First test if object is visible on the X axis */
	nNumberOfVisiblePoints=8;
	for (i=0; i<8; i++)
	{
		X=TBoundingBox[i][0];
		W=TBoundingBox[i][2];
		/* X axis : test if -W<X<W */
		if (-W<X && X<W)
		{
			/* At least one point is visible, so object is visible on the X axis */
			break;
		}
		else nNumberOfVisiblePoints--;
	}
	if (nNumberOfVisiblePoints==0)
	{
		/* All points are invisible on the X axis */
		*pNeedsZClipping=FALSE;
		return FALSE;
	}

	/* Then test if object is visible on the Y axis */
	nNumberOfVisiblePoints=8;
	for (i=0; i<8; i++)
	{
		Y=TBoundingBox[i][1];
		W=TBoundingBox[i][2];
		/* Y axis : test if -W<Y<W */
		if (-W<Y && Y<W)
		{
			/* At least one point is visible, so object is visible on the Y axis */
			break;
		}
		else nNumberOfVisiblePoints--;
	}
	if (nNumberOfVisiblePoints==0)
	{
		/* All points are invisible on the Y axis */
		*pNeedsZClipping=FALSE;
		return FALSE;
	}
	
	/* At last, test visibility of object on Z axis */
	nNumberOfVisiblePoints=0;
	for (i=0; i<8; i++)
	{
		/* Test W (h<W means visible on the Z axis) */
		if (TBoundingBox[i][2]>h) nNumberOfVisiblePoints++;
	}

	/* If the number of visible points is 0, the object is not visible
	   and thus does not require to be displayed */
	if (nNumberOfVisiblePoints==0)
	{
		*pNeedsZClipping=FALSE;
		return FALSE;
	}

	/* If all bounding box vertices are visible, it means that the object does
	   not need to be clipped (entirely visible) */
	if (nNumberOfVisiblePoints==8)
	{
		*pNeedsZClipping=FALSE;
		return TRUE;
	}

	/* At this point, the object is partially visible, thus requires Z clipping */
	*pNeedsZClipping=TRUE;
	return TRUE;
}


/*******************************************************************************
 * Function Name  : KMTransTransformVertices
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
void KMTransTransformVertices(const MATRIX *pWorldMatrix, 
					   const int nNumberOfVertices, const float *pVertex, float *pTransformedVertex)
{

	km_vector	*pDestVectorPointer;
	int			i;

	/* Getting Destination vector pointer */
	pDestVectorPointer=(km_vector *)&pTransformedVertex[0];

	/* Getting ready our matrix for Hitachi builtin rutines */
	/* Realise I just change the order to get the matrix in */
	/* usable fashion for vector operations.                */
	pSH4Matrix->_11 = pWorldMatrix->_11;
	pSH4Matrix->_12 = pWorldMatrix->_21;
	pSH4Matrix->_13 = pWorldMatrix->_31;
	pSH4Matrix->_14 = pWorldMatrix->_41;

	pSH4Matrix->_21 = pWorldMatrix->_12;
	pSH4Matrix->_22 = pWorldMatrix->_22;
	pSH4Matrix->_23 = pWorldMatrix->_32;
	pSH4Matrix->_24 = pWorldMatrix->_42;

	pSH4Matrix->_31 = pWorldMatrix->_14;
	pSH4Matrix->_32 = pWorldMatrix->_24;
	pSH4Matrix->_33 = pWorldMatrix->_34;
	pSH4Matrix->_34 = pWorldMatrix->_44;

	/* Transform all vertices with WorldMatrix */
	for (i=0; i<nNumberOfVertices; i++)
	{
		pSH4Vector[0] = *(pVertex++);
		pSH4Vector[1] = *(pVertex++);
		pSH4Vector[2] = *(pVertex++);
		pSH4Vector[3] = 1.0f;

		/* fipr calculates the dot product      */ 
		/* (Use 32bits aligned variables ONLY)  */
		pDestVectorPointer[i][0] =	fipr (pSH4Vector, &pSH4Matrix->_11);
		pDestVectorPointer[i][1] =	fipr (pSH4Vector, &pSH4Matrix->_21);
		pDestVectorPointer[i][2] =  fipr (pSH4Vector, &pSH4Matrix->_31);
	}

}

/*******************************************************************************
 * Function Name  : KMTransTransformProjectVertices
 * Inputs		  : *pWorldMatrix, nNumberOfVertices, *pVertex, 
 *					CamFrom, CamTo, fRoll,
 *					D, F, fViewAngle
 * Output		  : *pTLVertex
 * Globals used	  : None
 * Description    : Transform and project all vertices in pVertex and store them 
 *					in pTLVertex. This function gives homogeneous clipping
 *					coordinates (-1, +1).
 *					Use this function to perform clipping on your data.
 *					IMPORTANT : sz will NOT be computed by this function, as 
 *					all clipping information can be contained in rhw. (And
 *					anyway Kamui doesn't need Z information, only rhw)
 *					fInvW is in fact W after projection (useful for clipping).
 *					- pWorldMatrix is the World matrix used to transform the
 *					  object.
 *					- nNumberOfVertices is the number of vertices of the object.
 *					- pVertex is the pointer to untransformed object vertices.
 *					- pTLVertex is the pointer that will receive transformed vertices.
 *					- CamFrom is the camera position in World space.
 *					- CamTo is the World space vertex the camera is looking at.
 *					- fRoll is the camera roll value (usually 0).
 *					- D and F are the front and back clipping plane in World Space.
 *					- fViewAngle is the field of view (in radians).
 *
 *******************************************************************************/
void KMTransTransformProjectVertices(MATRIX *pWorldMatrix, 
							  int nNumberOfVertices, float *pVertex, KMVERTEX_03 *pTLVertex,
							  const km_vector CamFrom, const km_vector CamTo, const float fRoll,
							  const float D, const float F, const float fViewAngle)

{
	MATRIX		TransformationMatrix, ProjectionMatrix, ViewMatrix;
	float		h;
	int			i;

	/* Create View matrix */
	CreateViewMatrix(&ViewMatrix, CamFrom, CamTo, fRoll);

	/* Transformation matrix is the result of the concatenation between World and View matrices */
	KMMatrixMultiply(&TransformationMatrix, pWorldMatrix, &ViewMatrix);
	
	/* Compute h corresponding to Field Of View and Front Clipping plane */
	h=D*(float)tan(fViewAngle/2.0f);

	/* Compute projection matrix */
	ZeroMemory(&ProjectionMatrix, sizeof(MATRIX));
	ProjectionMatrix._11=1.0f;
	ProjectionMatrix._22=1.0f;
	ProjectionMatrix._33=h*F/(D*(F-D));
	ProjectionMatrix._34=h/D;
	ProjectionMatrix._43=-h*F/(F-D);

	/* Transformation matrix is the result of the concatenation between World matrix 
	   (including View matrix now) and Projection matrix */
	KMMatrixMultiply(&TransformationMatrix, &TransformationMatrix, &ProjectionMatrix);


	/* Getting ready our matrix for Hitachi builtin rutines */
	/* Realise I just change the order to get the matrix in */
	/* usable fashion for vector operations.                */
	pSH4Matrix->_11 = TransformationMatrix._11;
	pSH4Matrix->_12 = TransformationMatrix._21;
	pSH4Matrix->_13 = TransformationMatrix._31;
	pSH4Matrix->_14 = TransformationMatrix._41;

	pSH4Matrix->_21 = TransformationMatrix._12;
	pSH4Matrix->_22 = TransformationMatrix._22;
	pSH4Matrix->_23 = TransformationMatrix._32;
	pSH4Matrix->_24 = TransformationMatrix._42;

	pSH4Matrix->_31 = TransformationMatrix._14;
	pSH4Matrix->_32 = TransformationMatrix._24;
	pSH4Matrix->_33 = TransformationMatrix._34;
	pSH4Matrix->_34 = TransformationMatrix._44;

	/* Transform all vertices with TransformationMatrix */
	for (i=0; i<nNumberOfVertices; i++)
	{
		pSH4Vector[0] = *(pVertex++);
		pSH4Vector[1] = *(pVertex++);
		pSH4Vector[2] = *(pVertex++);
		pSH4Vector[3] = 1.0f;

		/* fipr calculates the dot product      */ 
		/* (Use 32bits aligned variables ONLY)  */
		pTLVertex[i].fX =	fipr (pSH4Vector, &pSH4Matrix->_11);
		pTLVertex[i].fY =	fipr (pSH4Vector, &pSH4Matrix->_21);
		pTLVertex[i].u.fZ=  fipr (pSH4Vector, &pSH4Matrix->_31);

	}

	/* At this point, all vertices are projected and homogeneous (clipping coordinates) */
}


/*******************************************************************************
 * Function Name  : KMTransPerspectiveVertices
 * Inputs		  : nNumberOfVertices, 
 *					nViewportWidth, nViewportHeight,
 *					D, F, fViewAngle
 * Input/Output	  : *pTLVertex
 * Globals used	  : None
 * Description    : Perform perspective division and get screen coordinates from
 *					vertices in *pTLVertex. 
 *					This function should be called after transformation, projection
 *					and (if required) clipping of your model data.
 *					- nNumberOfVertices is the number of vertices of the object.
 *					- pTLVertex is the pointer to vertices that will become
 *					screen coordinates.
 *					- nViewportWidth and nViewportHeight are the width and height
 *					  of the rendering surface (used to keep square ratio).
 *					- D and F are the front and back clipping plane in World Space.
 *					- fViewAngle is the field of view (in radians).
 *
 *******************************************************************************/
void KMTransPerspectiveVertices(const int nNumberOfVertices, KMVERTEX_03 *pTLVertex,
						 const int nViewportWidth, const int nViewportHeight,
						 const float D, const float F, const float fViewAngle)
{
	DWORD		dwHalfWidth, dwHalfHeight;
	float		h, fRHW, fSpeedUp;
	int			i;

	/* Compute h corresponding to Field Of View and Front Clipping plane */
	h=D*(float)tan(fViewAngle/2.0f);

	/* Getting middle coordinate of viewport */
	dwHalfWidth=nViewportWidth>>1;
	dwHalfHeight=nViewportHeight>>1;
	
	/* Calculating screen coordinates in one go (Optimised calculation) */
	for (i=0; i<nNumberOfVertices; i++)
	{
		fRHW=1.0f/pTLVertex[i].u.fZ;	
		fSpeedUp=dwHalfWidth*fRHW;

		pTLVertex[i].u.fZ=fRHW;
		pTLVertex[i].fX= fSpeedUp * pTLVertex[i].fX + dwHalfWidth;
		pTLVertex[i].fY=-fSpeedUp * pTLVertex[i].fY + dwHalfHeight;
	}
}


/*******************************************************************************
 * Function Name  : KMTransTransformProjectPerspective
 * Inputs		  : *pWorldMatrix, nNumberOfVertices, *pVertex, 
 *					nViewportWidth, nViewportHeight,
 *					CamFrom, CamTo, fRoll,
 *					D, F, fViewAngle
 * Output		  : *pTLVertex
 * Globals used	  : None
 * Description    : Transform and project all vertices in pVertex and store them 
 *					in pTLVertex. This function directly gives screen coordinates
 *					ready to be used by Kamui. Should be used when no clipping is
 *					required.
 *					- pWorldMatrix is the World matrix used to transform the
 *					  object.
 *					- nNumberOfVertices is the number of vertices of the object.
 *					- pVertex is the pointer to untransformed object vertices.
 *					- pTLVertex is the pointer that will receive transformed vertices.
 *					- nViewportWidth and nViewportHeight are the width and height
 *					  of the rendering surface (used to keep square ratio).
 *					- CamFrom is the camera position in World space.
 *					- CamTo is the World space vertex the camera is looking at.
 *					- fRoll is the camera roll value (usually 0).
 *					- D and F are the front and back clipping plane in World Space.
 *					- fViewAngle is the field of view (in radians).
 *
 *******************************************************************************/
int KMTransTransformProjectPerspective(MATRIX *pWorldMatrix, 
										 int nNumberOfVertices, float *pVertex, KMVERTEX_03 *pTLVertex,
										 int nViewportWidth, int nViewportHeight,
										 const km_vector CamFrom, const km_vector CamTo, const float fRoll,
										 const float D, const float F, const float fViewAngle)
{
	MATRIX		TransformationMatrix, ProjectionMatrix, ViewMatrix;
	DWORD		dwHalfWidth, dwHalfHeight;
	float		h, fRHW, fSpeedUp;
	int			i, ret = 1;
	
	/* Create View matrix */
	CreateViewMatrix(&ViewMatrix, CamFrom, CamTo, fRoll);

	/* Transformation matrix is the result of the concatenation between World and View matrices */
	KMMatrixMultiply(&TransformationMatrix, pWorldMatrix, &ViewMatrix);
	
	/* Compute h corresponding to Field Of View and Front Clipping plane */
	h=D*(float)tan(fViewAngle/2.0f);

	/* Compute projection matrix */
	ZeroMemory(&ProjectionMatrix, sizeof(MATRIX));
	ProjectionMatrix._11=1.0f;
	ProjectionMatrix._22=1.0f;
	ProjectionMatrix._33=h*F/(D*(F-D));
	ProjectionMatrix._34=h/D;
	ProjectionMatrix._43=-h*F/(F-D);

	/* Transformation matrix is the result of the concatenation between World matrix 
	   (including View matrix now) and Projection matrix */
	KMMatrixMultiply(&TransformationMatrix, &TransformationMatrix, &ProjectionMatrix);

	/* Getting ready our matrix for Hitachi builtin rutines */
	/* Realise I just change the order to get the matrix in */
	/* usable fashion for vector operations.                */
	pSH4Matrix->_11 = TransformationMatrix._11;
	pSH4Matrix->_12 = TransformationMatrix._21;
	pSH4Matrix->_13 = TransformationMatrix._31;
	pSH4Matrix->_14 = TransformationMatrix._41;

	pSH4Matrix->_21 = TransformationMatrix._12;
	pSH4Matrix->_22 = TransformationMatrix._22;
	pSH4Matrix->_23 = TransformationMatrix._32;
	pSH4Matrix->_24 = TransformationMatrix._42;

	pSH4Matrix->_31 = TransformationMatrix._14;
	pSH4Matrix->_32 = TransformationMatrix._24;
	pSH4Matrix->_33 = TransformationMatrix._34;
	pSH4Matrix->_34 = TransformationMatrix._44;

       /* Getting middle coordinate of viewport */
	dwHalfWidth=nViewportWidth>>1;
	dwHalfHeight=nViewportHeight>>1;	 

	/* Transform all vertices with TransformationMatrix */
	for (i=0; i<nNumberOfVertices; i++)
	{
		pSH4Vector[0] = *(pVertex++);
		pSH4Vector[1] = *(pVertex++);
		pSH4Vector[2] = *(pVertex++);
		pSH4Vector[3] = 1.0f;

		/* fipr calculates the dot product      */ 
		/* (Use 32bits aligned variables ONLY)  */
		pTLVertex[i].fX =	fipr (pSH4Vector, &pSH4Matrix->_11);
		pTLVertex[i].fY =	fipr (pSH4Vector, &pSH4Matrix->_21);
		pTLVertex[i].u.fZ=  fipr (pSH4Vector, &pSH4Matrix->_31);

		/*  Well, this is the Z slamming.                                              */
		/*  PVR doesn't need X and Y clipping so this cheap method usually works fine  */
                /*  unless you need a real Z clipping (I.e. floor,walls, etc.)                 */

		// if (pTLVertex[i].u.fZ<1.0f)
		// {
		// 	pTLVertex[i].u.fZ=1.0f;
		// 	ret = 0;
		//}
		
	        fRHW=1.0f/pTLVertex[i].u.fZ;		
		fSpeedUp=dwHalfWidth*fRHW;

		pTLVertex[i].u.fZ=fRHW;
		pTLVertex[i].fX= fSpeedUp * pTLVertex[i].fX + dwHalfWidth;
		pTLVertex[i].fY=-fSpeedUp * pTLVertex[i].fY + dwHalfHeight;
	
	}

	/* At this point, all vertices are projected and homogeneous (clipping coordinates) */

	/* Calculating screen coordinates in one go */
	for (i=0; i<nNumberOfVertices; i++)
	{
	}

	return ret;
}
/*******************************************************************************
 * Function Name  : KMTransZClipProjectedVertices
 * Inputs		  : nNumberOfVertices, *pTLVertex, 
 *					nNumberOfTriangles, 
 *					D, F, fViewAngle
 * Input/Output	  : *pTriangleList
 * Output		  : *pNumberOfVisibleTriangles
 * Globals used	  : None
 * Description    : Crap Z clipping method since it clamps out-of-bounds W values
 *					to the minimal value (given by h).
 *
 *******************************************************************************/
void KMTransZClipProjectedVertices(int nNumberOfVertices, KMVERTEX_03 *pTLVertex,
							int nNumberOfTriangles, int *pTriangleList, int *pNumberOfVisibleTriangles,
							const float D, const float F, const float fViewAngle)
{
	DWORD	P1, P2, P3;
	float	h;
	int		nNumberOfVisibleTriangles;
	int		i=0;

	/* Compute h */
	h=D*(float)tan((60.0f*3.14159f/180.0f)/2.0f);
		
	/* Get total number of triangles */
	nNumberOfVisibleTriangles=nNumberOfTriangles;
	
	/* Loop through all triangles and check if they are visible */
	while (i<nNumberOfVisibleTriangles)
	{
		/* Get 3 vertex numbers of current triangle */
		P1=pTriangleList[3*i];
		P2=pTriangleList[3*i+1];
		P3=pTriangleList[3*i+2];

		/* Test if the 3 vertices defining the triangle are not visible (below h) */
		if ( (pTLVertex[P1].u.fZ<=h) &&
			 (pTLVertex[P2].u.fZ<=h) &&
			 (pTLVertex[P3].u.fZ<=h) )
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

	/* W values below h are set to h */
	for (i=0; i<nNumberOfVertices; i++)
	{
		if (pTLVertex[i].u.fZ<=h)
		{
			pTLVertex[i].u.fZ=h;
		}
	}
}

/*******************************************************************************
 * Function Name  : KMTransEnvironmentMap
 * Inputs		  : 
 *					D, F, fViewAngle
 * Output		  : *pTLVertex
 * Globals used	  : None
 * Description    : 
 *******************************************************************************/
int KMTransEnvironmentMap(MATRIX *pWorldMatrix, 
										 int nNumberOfVertices, float *pNormals, KMVERTEX_03 *pTLVertex,
										 const km_vector CamFrom, const km_vector CamTo, const float fRoll,
										 const float D, const float F, const float fViewAngle)
{
	MATRIX		TransformationMatrix, ProjectionMatrix, ViewMatrix;
	DWORD		dwHalfWidth, dwHalfHeight;
	float		h, fRHW, fSpeedUp;
	int			i, ret = 1;


	/* Create View matrix */
	CreateViewMatrix(&ViewMatrix, CamFrom, CamTo, fRoll);

	/* Transformation matrix is the result of the concatenation between World and View matrices */
	KMMatrixMultiply(&TransformationMatrix, pWorldMatrix, &ViewMatrix);
	
	/* Compute h corresponding to Field Of View and Front Clipping plane */
	h=D*(float)tan(fViewAngle/2.0f);

	/* Compute projection matrix */
	ZeroMemory(&ProjectionMatrix, sizeof(MATRIX));
	ProjectionMatrix._11=1.0f;
	ProjectionMatrix._22=1.0f;
	ProjectionMatrix._33=h*F/(D*(F-D));
	ProjectionMatrix._34=h/D;
	ProjectionMatrix._43=-h*F/(F-D);

	/* Transformation matrix is the result of the concatenation between World matrix 
	   (including View matrix now) and Projection matrix */
	KMMatrixMultiply(&TransformationMatrix, &TransformationMatrix, &ProjectionMatrix);

	/* Getting ready our matrix for Hitachi builtin rutines */
	/* Realise I just change the order to get the matrix in */
	/* usable fashion for vector operations.                */
	pSH4Matrix->_11 = TransformationMatrix._11;
	pSH4Matrix->_12 = TransformationMatrix._21;
	pSH4Matrix->_13 = TransformationMatrix._31;
	pSH4Matrix->_14 = TransformationMatrix._41;

	pSH4Matrix->_21 = TransformationMatrix._12;
	pSH4Matrix->_22 = TransformationMatrix._22;
	pSH4Matrix->_23 = TransformationMatrix._32;
	pSH4Matrix->_24 = TransformationMatrix._42;

	pSH4Matrix->_31 = TransformationMatrix._14;
	pSH4Matrix->_32 = TransformationMatrix._24;
	pSH4Matrix->_33 = TransformationMatrix._34;
	pSH4Matrix->_34 = TransformationMatrix._44;

	/* Transform all vertices with TransformationMatrix */
	for (i=0; i<nNumberOfVertices; i++)
	{
		pSH4Vector[0] = *(pNormals++);
		pSH4Vector[1] = *(pNormals++);
		pSH4Vector[2] = *(pNormals++);
		pSH4Vector[3] = 1.0f;

		/* fipr calculates the dot product      */ 
		/* (Use 32bits aligned variables ONLY)  */
		pTLVertex[i].fU =	0.5f + 0.5f * fipr (pSH4Vector, &pSH4Matrix->_11);
		pTLVertex[i].fV =	0.5f + 0.5f * fipr (pSH4Vector, &pSH4Matrix->_21);
	
	}


	return TRUE;
}

/******************************************************
****************** INTERNAL FUNCTIONS *****************
******************************************************/


/*******************************************************************************
 * Function Name  : CreateViewMatrix
 * Inputs		  : From, At, fRoll
 * Output		  : *pViewMatrix
 * Globals used	  : None
 * Description    : Create a view matrix to be used in projection functions.
 *					- From is the camera position.
 *					- At is the position the camera is pointing to.
 *					- fRoll is the roll value (if required)
 *
 *******************************************************************************/
void CreateViewMatrix(MATRIX *pViewMatrix, const km_vector From, const km_vector At, const float fRoll)
{
    MATRIX		DummyMatrix;
    km_vector	Up, Right, ViewDir;
	km_vector	WorldUp={0.0f, 1.0f, 0.0f};
    
    /* Reset matrix to identity */
	KMMatrixReset(pViewMatrix);

	/* Compute view vector */
	ViewDir[0]=At[0]-From[0];
	ViewDir[1]=At[1]-From[1];
	ViewDir[2]=At[2]-From[2];
	
	/* Normalise view vector */
	KMMatrixNormalize(ViewDir);
	
    /* Compute cross products */
	KMMatrixCrossProduct(Right, WorldUp, ViewDir);
    KMMatrixCrossProduct(Up, ViewDir, Right);
    
    /* Normalise resulting vectors */
	KMMatrixNormalize(Right);
    KMMatrixNormalize(Up);
    
    /* Fill View matrix */
	pViewMatrix->_11 = Right[0];
    pViewMatrix->_21 = Right[1];
    pViewMatrix->_31 = Right[2];
    pViewMatrix->_12 = Up[0];
    pViewMatrix->_22 = Up[1];
    pViewMatrix->_32 = Up[2];
    pViewMatrix->_13 = ViewDir[0];
    pViewMatrix->_23 = ViewDir[1];
    pViewMatrix->_33 = ViewDir[2];
	pViewMatrix->_41 = -KMMatrixDotProduct(Right, From);
    pViewMatrix->_42 = -KMMatrixDotProduct(Up, From);
    pViewMatrix->_43 = -KMMatrixDotProduct(ViewDir, From);
    
    /* Add roll to the View matrix if requested */
	if (fRoll!=0.0f) 
	{
        KMMatrixReset(&DummyMatrix);
		KMMatrixRotate(&DummyMatrix, 0.0f, 0.0f, -fRoll);
		KMMatrixMultiply(pViewMatrix, pViewMatrix, &DummyMatrix);
    }
}



