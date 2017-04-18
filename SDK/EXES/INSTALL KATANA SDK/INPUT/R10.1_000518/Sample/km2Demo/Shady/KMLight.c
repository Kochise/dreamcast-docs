/*****************************************************************************
  Name : KMLight.c
  Date : August 1998
  Platform : ANSI compatible
 
  * Description : 
  This file is part of the KAMUI TOOLS library (KMTools.lib) used
  with the SDK demos for PowerVR series 2.

  Set of functions used to perform 3D lighting.


  Copyright : 1998 by VideoLogic Limited. All rights reserved.
******************************************************************************/
#include <Machine.h>

#include "KMTools.h"

/*************************************/
/*  ALIGNED GLOBALS FOR SH4 ROUTINES */
/*************************************/

unsigned long	Buffer6[10];
#define	pNormalVector		((float *)(((unsigned long)Buffer6+7)&0xFFFFFFF8))

unsigned long	Buffer7[10];
#define	pLightDirection		((float *)(((unsigned long)Buffer7+7)&0xFFFFFFF8))

unsigned long	Buffer8[10];
#define	pLightDirection1		((float *)(((unsigned long)Buffer8+7)&0xFFFFFFF8))



/*******************************************************************************
 * Function Name  : KMLightSmoothShade
 * Inputs		  : *pMatrix, nNumberOfVertices, *pNormals, 
 *					LightVector, dwLightColour
 * Output		  : *pTLVertex
 * Globals used   : None
 * Description    : Smooth shade vertices.
 *					The WORLD matrix is passed as a parameter (pMatrix) and the
 *					inverse matrix is computed in the function to perform the
 *					shading.
 *					The resulting colour and specular are set in the
 *					pTLVertex array.
 *					Of course normal vectors must be normalised.
 *					You can set the Alpha value of the vertices by passing
 *					dwLightColour with an ALPHA component.
 *					Vertex fog is set to 0.
 *					To compute specular color set the bUseSpecular flag to TRUE.
 *					The Vfog parameter in the specular color is not changed here.
 *					
 *******************************************************************************/
void KMLightSmoothShade(MATRIX *pMatrix, 
				 int nNumberOfVertices, float *pNormals, KMVERTEX_03 *pTLVertex, 
				 km_vector LightVector, DWORD dwLightColour, int bUseSpecular)
{

	MATRIX		Inverse;
	float		TLightVector[3];
	float		LVector[3];
	km_vector	*pNormalPointer;
	KMVERTEX_03	*pTLVertexPointer;
	BYTE		Red, Green, Blue, Alpha;
	BYTE		r, g, b, w;
	float		fCosine;
	int			i;
	int         bIsWhiteLight;
	KMDWORD     nFog;

	/* Copy world matrix and compute inverse matrix */
	KMMatrixCopy(&Inverse, pMatrix);
	KMMatrixInverse(&Inverse);

	/* Invert light vector */
	LVector[0]=-LightVector[0];
	LVector[1]=-LightVector[1];
	LVector[2]=-LightVector[2];
	
	/* Normalize light vector in case it is not */
	KMMatrixNormalize(LVector);

	/* Transform the light vector with inverse world matrix.
	   Note : Don't include Inverse._4X because LightVector = TO - FROM. 
	   FROM is always (0, 0, 0), so transformed FROM would be equal to
	   (Inverse._41, Inverse._42, Inverse._43). Thus by doing TO - FROM, Inverse._4X
	   would be subtracted with themselves, hence yielding zero */
	TLightVector[0]=LVector[0]*Inverse._11 + 
					LVector[1]*Inverse._21 +
					LVector[2]*Inverse._31;

	TLightVector[1]=LVector[0]*Inverse._12 + 
					LVector[1]*Inverse._22 +
					LVector[2]*Inverse._32;

	TLightVector[2]=LVector[0]*Inverse._13 + 
					LVector[1]*Inverse._23 +
					LVector[2]*Inverse._33;
	

	/* Get Red, Green and Blue components of light */
	Red=	GET_RED(dwLightColour);
	Green=	GET_GREEN(dwLightColour);
	Blue=	GET_BLUE(dwLightColour);
	Alpha=	GET_ALPHA(dwLightColour);

	/* If the light is white we can avoid */
	/* 3 multiplications per vertex       */
	if (Red == Green && Green == Blue)
	{
		bIsWhiteLight = TRUE;
		pLightDirection[0] = TLightVector[0] * (float)Red;
		pLightDirection[1] = TLightVector[1] * (float)Red;
		pLightDirection[2] = TLightVector[2] * (float)Red;
		pLightDirection[3] = 0.0f;
	}
	else
	{
		bIsWhiteLight = FALSE;
		pLightDirection[0] = TLightVector[0];
		pLightDirection[1] = TLightVector[1];
		pLightDirection[2] = TLightVector[2];
		pLightDirection[3] = 0.0f;
	}

	/* Get pointers */
	pNormalPointer=(km_vector *)&pNormals[0];
	pTLVertexPointer=&pTLVertex[0];
	
	/* Compute dot product for each vertex */
	for (i=0; i<nNumberOfVertices; i++)
	{
		pNormalVector[0] = *pNormals++;
		pNormalVector[1] = *pNormals++;
		pNormalVector[2] = *pNormals++;
		pNormalVector[3] = 0.0f;

		fCosine= fipr(pNormalVector, pLightDirection);
				
		/* If colour is negative, then make it 0 */
		if (fCosine<0) fCosine=0;

		if (!bIsWhiteLight) /* Coulored light */
		{
			/* Compute Red, Green and Blue colour values */
			r=(BYTE)(fCosine*Red);
			g=(BYTE)(fCosine*Green);
			b=(BYTE)(fCosine*Blue);

			/* Diffuse colour */
			pTLVertex->uBaseRGB.dwPacked = MAKE_RGBA(r, g, b, Alpha);

			/* Compute highlight : set highlight to 0 for any intensity value below 240 */
			/* We keep the original vertex fog value                                    */
			if (bUseSpecular)
			{
			nFog = pTLVertex->uOffsetRGB.dwPacked & 0xFF000000;
			 pTLVertex->uOffsetRGB.dwPacked = nFog | MAKE_RGB( (r>240) ? (r-240)<<4 : 0, (g>240) ? (g-240)<<4 : 0, (b>240) ? (b-240)<<4 : 0);
			}
		}

  		else /* White light */
		{
			w = (BYTE) (fCosine);
			/* Diffuse colour */
			pTLVertex->uBaseRGB.dwPacked = MAKE_RGBA(w, w, w, Alpha);

			/* Compute highlight : set highlight to 0 for any intensity value below 240 */
			/* We keep the original vertex fog value                                    */
			if (bUseSpecular)
			{
			nFog = pTLVertex->uOffsetRGB.dwPacked & 0xFF000000;
			pTLVertex->uOffsetRGB.dwPacked = nFog | MAKE_RGB( (w>240) ? (w-240)<<4 : 0, (w>240) ? (w-240)<<4 : 0, (w>240) ? (w-240)<<4 : 0);
		
			}
		}

		/* Increase vertex count */
		pTLVertex++;
	}

}