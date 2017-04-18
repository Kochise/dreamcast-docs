/****************************************************************************
  Name : D3DTLight.c
  Date : October 1998
  Platform : ANSI compatible
 
  $Revision: 1.6 $

  * Description : 
  This file is part of the TOOLS library (D3DTools.lib) used
  with the SDK demos for PowerVR series 2.

  Set of functions used to perform 3D lighting.


  Copyright : 1998 by Imagination Technologies Limited. All rights reserved.
****************************************************************************/
#include <math.h>
#include <d3d.h>
#include "D3DTMatrix.h"
#include "D3DTLight.h"


/* Use D3DTLightSmoothShade() normally, D3DTLightSpecular() if you want
** specular highlights. The latter takes longer to complete. */


/****************************************************************************
 * Function Name  : D3DTLightSmoothShade
 * Inputs		  : *pWorldMatrix, nNumberOfVertices, *pNormals, 
 *					*pLightVector, dwLightColor
 * Output		  : *pTLVertex
 * Globals used	  : None
 * Description    : Smooth shade vertices.
 *					The WORLD matrix is passed as a parameter (pWorldMatrix) and the
 *					inverse matrix is computed in the function to perform the
 *					shading.
 *					The resulting colour is asserted in the
 *					pTLVertex array.
 *					Of course normal vectors must be normalised.
 *					You can set the Alpha value of the vertices by passing
 *					dwLightColor with an ALPHA component.
 *					Vertex fog (alpha channel in the specular component) is unchanged.
 ****************************************************************************/
void D3DTLightSmoothShade(const D3DMATRIX *pWorldMatrix,
						  const int nNumberOfVertices, const float *pNormals, D3DTLVERTEX *pTLVertex,
						  const D3DVECTOR *pLightVector, const D3DCOLOR dwLightColor)
{
	D3DMATRIX	mInverse;
	D3DVECTOR	TLightVector;
	D3DVECTOR	*pNormalVectorPointer;
	D3DTLVERTEX	*pTLVertexPointer;
	DWORD		Red, Green, Blue, Alpha;
	DWORD		dwTmp;
	float		fCosine;
	int			nLoop;

	/* Copy world matrix and compute inverse matrix */
	D3DTMatrixCopy(&mInverse, pWorldMatrix);
	D3DTMatrixInverse(&mInverse);

	/* Transform the [inverted] light vector with inverse world matrix.
	   Note : Don't include Inverse._4X because LightVector = TO - FROM. 
	   FROM is always (0, 0, 0), so transformed FROM would be equal to
	   (Inverse._41, Inverse._42, Inverse._43). Thus by doing TO - FROM, Inverse._4X
	   would be subtracted with themselves, hence yielding zero */
	/* negatives effectively invert the light vector */
	TLightVector.x = -(pLightVector->x * mInverse._11 +
					   pLightVector->y * mInverse._21 +
					   pLightVector->z * mInverse._31);

	TLightVector.y = -(pLightVector->x * mInverse._12 +
					   pLightVector->y * mInverse._22 +
					   pLightVector->z * mInverse._32);

	TLightVector.z = -(pLightVector->x * mInverse._13 +
					   pLightVector->y * mInverse._23 +
					   pLightVector->z * mInverse._33);

	/* Normalize light vector in case it is not */
	D3DTMatrixNormalize(&TLightVector);

	/* Get Red, Green and Blue components of light, as well as Alpha */
	Red = RGB_GETRED(dwLightColor);
	Green =	RGB_GETGREEN(dwLightColor);
	Blue = RGB_GETBLUE(dwLightColor);
	Alpha =	RGBA_GETALPHA(dwLightColor);

	/* Get pointers */
	pNormalVectorPointer = (D3DVECTOR *)pNormals;
	pTLVertexPointer = pTLVertex;

	/* If the light is white we can avoid 3 multiplications per vertex */
	if(Red==Green && Green==Blue)
	{
		/* WHITE LIGHT */

		/* Compute dot product for each vertex */
		for(nLoop = 0; nLoop < nNumberOfVertices; nLoop++)
		{
			/* fCosine = cosinus angle between light vector and normal vector */
			fCosine = D3DTMatrixDotProduct(pNormalVectorPointer++, &TLightVector);

			/* If cosine is negative, then make it 0 */
			if (fCosine<0) fCosine=0;

			/* Compute white light color value */
			dwTmp = (DWORD)(fCosine*Red);

			/* Diffuse colour */
			pTLVertexPointer->color=RGBA_MAKE(dwTmp, dwTmp, dwTmp, Alpha);

			/* Increase vertex count */
			pTLVertexPointer++;
		}
	}
	else
	{
		/* COLORED LIGHT */

		/* Compute dot product for each vertex */
		for(nLoop = 0; nLoop < nNumberOfVertices; nLoop++)
		{
			/* fCosine = cosinus angle between light vector and normal vector */
			fCosine = D3DTMatrixDotProduct(pNormalVectorPointer++, &TLightVector);

			/* If cosine is negative, then make it 0 */
			if(fCosine > 0)
			{
				/* Diffuse colour; Compute Red, Green and Blue colour values */
				pTLVertexPointer->color = RGBA_MAKE(
					(DWORD)(fCosine * Red),
					(DWORD)(fCosine * Green),
					(DWORD)(fCosine * Blue),
					Alpha);
			}
			else
			{
				/* normal points away from light, no colour at all */
				pTLVertexPointer->color = RGBA_MAKE(0, 0, 0, Alpha);
			}

			/* Increase vertex count */
			pTLVertexPointer++;
		}
	}
}


/****************************************************************************
 * Function Name  : D3DTLightSpecular
 * Inputs		  : *pWorldMatrix, nNumberOfVertices, *pNormals, *pVertex,
 *					*pLightVector, *pCameraVector, cDiffuse, cSpecular,
 *					fSpecularPower
 * Output		  : *pTLVertex
 * Globals used	  : None
 * Description	  *	Smooth shade vertices with specular highlights.
 *				  *	The WORLD matrix is passed as a parameter (pWorldMatrix) and the
 *					inverse matrix is computed in the function to perform the
 *					shading, colour cDiffuse.
 *				  *	The camera World position (pCamWorldPos, camera 'from'
 *					vector) is used for specular highlight intensity (colour
 *					cSpecular). The alternative would be to use the inverse
 *					view matrix to back transform [0, 0, 0] to world
 *					co-ordinates and use that as the camera position, but the
 *					transformation functions build the view matrix internally.
 *				  *	The resulting colours are asserted in the pTLVertex array.
 *				  *	Of course normal vectors must be normalised.
 *				  *	You can set the Alpha value of the vertices by passing
 *					cDiffuse with an ALPHA component.
 *				  *	Vertex fog (alpha channel in the pTLVertex specular
 *					component) is unchanged.
 ****************************************************************************/
void D3DTLightSpecular(const D3DMATRIX *pWorldMatrix,
					   const int nNumberOfVertices, const float *pNormals,
					   const float *pVertex, D3DTLVERTEX *pTLVertex,
					   const D3DVECTOR *pLightVector, const D3DVECTOR *pCamWorldPos,
					   const D3DCOLOR cDiffuse, const D3DCOLOR cSpecular,
					   const float fSpecularPower)
{
	D3DVECTOR	*pvNormals = (D3DVECTOR *)pNormals;
	D3DVECTOR	*pvVertex = (D3DVECTOR *)pVertex;
	D3DVECTOR	vTLight, vTView, vHalfway;
	int			nLoop;
	float		fCosine;
	D3DMATRIX	mInverse;
	DWORD		dwDiffuseR, dwDiffuseG, dwDiffuseB, dwDiffuseA;	/* Diffuse colour components */
	DWORD		dwSpecularR, dwSpecularG, dwSpecularB;			/* Specular colour components */

	/* extract colour components */
	dwDiffuseR = RGB_GETRED(cDiffuse);
	dwDiffuseG = RGB_GETGREEN(cDiffuse);
	dwDiffuseB = RGB_GETBLUE(cDiffuse);
	dwDiffuseA = cDiffuse & 0xFF000000;		/* notice this is not shifted into LSByte! */

	dwSpecularR = RGB_GETRED(cSpecular);
	dwSpecularG = RGB_GETGREEN(cSpecular);
	dwSpecularB = RGB_GETBLUE(cSpecular);

	/* Copy world matrix and compute inverse matrix */
	D3DTMatrixCopy(&mInverse, pWorldMatrix);
	D3DTMatrixInverse(&mInverse);

	/* Transform the [inverted] light vector with inverse world matrix.
	   Note : Don't include Inverse._4X because LightVector = TO - FROM. 
	   FROM is always (0, 0, 0), so transformed FROM would be equal to
	   (Inverse._41, Inverse._42, Inverse._43). Thus by doing TO - FROM, Inverse._4X
	   would be subtracted with themselves, hence yielding zero */
	/* negatives effectively invert the light vector */
	vTLight.x = -(pLightVector->x * mInverse._11 +
				  pLightVector->y * mInverse._21 +
				  pLightVector->z * mInverse._31);

	vTLight.y = -(pLightVector->x * mInverse._12 + 
				  pLightVector->y * mInverse._22 +
				  pLightVector->z * mInverse._32);

	vTLight.z = -(pLightVector->x * mInverse._13 + 
				  pLightVector->y * mInverse._23 +
				  pLightVector->z * mInverse._33);

	/* Normalize light vector in case it is not */
	D3DTMatrixNormalize(&vTLight);


	/* back transform camera; world space to model space */
	vTView.x = pCamWorldPos->x * mInverse._11 +
			   pCamWorldPos->y * mInverse._21 +
			   pCamWorldPos->z * mInverse._31;

	vTView.y = pCamWorldPos->x * mInverse._12 + 
			   pCamWorldPos->y * mInverse._22 +
			   pCamWorldPos->z * mInverse._32;

	vTView.z = pCamWorldPos->x * mInverse._13 + 
			   pCamWorldPos->y * mInverse._23 +
			   pCamWorldPos->z * mInverse._33;


	/* for a white-light speedup, this while() would have to be repeated
	** four times, once for each combination of specular & diffuse
	** white/coloured light */
	nLoop = nNumberOfVertices;
	while(nLoop--)
	{
		/* Diffuse colour */
		/* fCosine = cosinus angle between light vector and normal vector */
		fCosine = D3DTMatrixDotProduct(pvNormals, &vTLight);

		/* If cosine is negative, then make it 0 */
		if(fCosine > 0)
		{
			/* Compute Red, Green and Blue colour values; pass through alpha */
			pTLVertex->color = dwDiffuseA | RGB_MAKE(
				(DWORD)(dwDiffuseR * fCosine),
				(DWORD)(dwDiffuseG * fCosine),
				(DWORD)(dwDiffuseB * fCosine));
		}
		else
		{
			/* normal points away from light, no colour at all */
			pTLVertex->color = dwDiffuseA;
		}


		/* Specular colour
		** Method:
		**   New View vector for each vertex. 'halfway' vector between Light
		**   vector & View vector [addition & normalization]. Dot product of
		**   this and vertex normal, to power of fSpecularPower, gives
		**   specular colour factor */

		/* Vector: cam-vertex [View vector for vertex] */
		vHalfway.x = vTView.x - pvVertex->x;
		vHalfway.y = vTView.y - pvVertex->y;
		vHalfway.z = vTView.z - pvVertex++->z;

		/* Normalize view vector */
		D3DTMatrixNormalize(&vHalfway);

		/* & this makes halfway vector */
		vHalfway.x += vTLight.x;
		vHalfway.y += vTLight.y;
		vHalfway.z += vTLight.z;

		/* Normalize halfway vector */
		D3DTMatrixNormalize(&vHalfway);

		/* fCosine = cosinus angle between halfway-vector and normal-vector */
		fCosine = D3DTMatrixDotProduct(pvNormals++, &vHalfway);

		/* If cosine is negative, then make it 0 */
		if(fCosine > 0)
		{
			fCosine = (float)pow(fCosine, fSpecularPower);

			/* Compute Red, Green and Blue colour values; Save vertex fog */
			pTLVertex->specular = (pTLVertex->specular & 0xFF000000) | RGB_MAKE(
				(DWORD)(dwSpecularR * fCosine),
				(DWORD)(dwSpecularG * fCosine),
				(DWORD)(dwSpecularB * fCosine)
			);
		}
		else
		{
			/* no specular; save vertex fog value */
			pTLVertex->specular &= 0xFF000000;
		}

		/* Increase vertex count */
		pTLVertex++;
	}
}
