/*****************************************************************************
  Name : D3DTBump.c
  Date : May 1999
  Platform : ANSI compatible
  Author: Carlos Sarria
 
  * Description : 
  This file is part of the DRAGON TOOLS library (D3DTTools.lib) used
  with the Videologic demos for PowerVR series 2 (Dreamcast).

  Set of functions used to perform BumpMap.
  ENHANCED VERSION.

  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#include <windows.h>
#include <d3d.h>
#include <math.h>
#include <shintr.h> /* sh4 built-in functions */

#include "D3DTools.h"

#define WCE_DEBUG(x) OutputDebugString((unsigned short *)x);

/*************************************/
/*  GLOBALS FOR SH4 ROUTINES		 */
/*************************************/
float pNormalVector[4];
float pLightDirection[4];
float pVector[4];

/*************************************/
/*  LOCAL PROTOTYPES                 */
/*************************************/
/*  Different methods to create buimpmap local co-ordinate systems (Tangent Spaces) */
void CalculateTangentSpaceMethodUpRight (D3DVECTOR *vBinormal, D3DVECTOR *vNormal, D3DVECTOR *vTangent, 
							int CurrentVertex, int nNumFaces, unsigned short *ptFaces, 
						   float *ptVertex, float *ptUV);

void CalculateTangentSpaceMethodAnyUV (D3DVECTOR *vBinormal, D3DVECTOR *vNormal, D3DVECTOR *vTangent, 
						   int CurrentVertex, int nNumFaces, unsigned short *ptFaces, 
						   float *ptVertex, float *ptUV);

void CalculateTangentSpaceMethodAnyUVAverage (D3DVECTOR *vBinormal, D3DVECTOR *vNormal, D3DVECTOR *vTangent, 
						   int CurrentVertex, int nNumFaces, unsigned short *ptFaces, 
						   float *ptVertex, float *ptUV);

/*
// Routine to convert XYZ light direction vector to the 'polar'
// coordinate system of the first set of PVR2 chips
*/
void FXYZLightDirToSKK(const float xyz[3], UINT8  skk[3]);


/*******************************************************************************
 * Function Name  : D3DTBumpShade
 * Inputs		  : *pMatrix, nNumberOfVertices, *pNormals, 
 *					LightVector, dwLightColour
 * Output		  : *pTLVertex
 * Globals used   : None
 * Description    : Calculates Bump-map angles and smooth shading.
 * Notes          : Set the parameter *pTLVertexObject to NULL if you only want to calculate Bumpmap.
 *                  This method uses the local coordinate systems calculated by D3DTBumpCalculateLocalCoords().
 *	                Call this funtion every frame to get a correct phong bumpmapping.
 *******************************************************************************/
void D3DTBumpShade(D3DMATRIX *pMatrix, 
				 unsigned nNumberOfVertices, float *pBumpCoords, float *pNormals,
				 D3DTLVERTEX *pTLVertexBump, D3DTLVERTEX *pTLVertexObject,
				 D3DVECTOR LightVector, int nMethod)
{
D3DMATRIX		Inverse;
float			TLightVector[3];
D3DVECTOR		LVector;
BYTE			w = 0xFF, f;
float			fCosine;
int				i;
float			LBump[3];
unsigned char   AngBump[3];


	/* Copy world matrix and compute inverse matrix */
	D3DTMatrixCopy(&Inverse, pMatrix);
	D3DTMatrixInverse(&Inverse);

	/* Invert light vector */
	LVector.x=-LightVector.x;
	LVector.y=-LightVector.y;
	LVector.z=-LightVector.z;
	
	/* Normalize light vector in case it is not */
	D3DTMatrixNormalize(&LVector);

	/* Transform the light vector with inverse world matrix.
	   Note : Don't include Inverse._4X because LightVector = TO - FROM. 
	   FROM is always (0, 0, 0), so transformed FROM would be equal to
	   (Inverse._41, Inverse._42, Inverse._43). Thus by doing TO - FROM, Inverse._4X
	   would be subtracted with themselves, hence yielding zero */
	TLightVector[0]=LVector.x*Inverse._11 + 
					LVector.y*Inverse._21 +
					LVector.z*Inverse._31;

	TLightVector[1]=LVector.x*Inverse._12 + 
					LVector.y*Inverse._22 +
					LVector.z*Inverse._32;

	TLightVector[2]=LVector.x*Inverse._13 + 
					LVector.y*Inverse._23 +
					LVector.z*Inverse._33;
	

	/* The light is always white, so we can avoid */
	/* 3 multiplications per vertex.					*/

	pLightDirection[0] = TLightVector[0] * 127.0f;
	pLightDirection[1] = TLightVector[1] * 127.0f;
	pLightDirection[2] = TLightVector[2] * 127.0f;
	pLightDirection[3] = 0.0f;


	/* Compute dot product for each vertex */
	for (i=0; i<(int)nNumberOfVertices; i++)
	{
		/* First Axis (Binormal) */
		pNormalVector[0] = *pBumpCoords++;
		pNormalVector[1] = *pBumpCoords++;
		pNormalVector[2] = *pBumpCoords++;
		pNormalVector[3] = 0.0f;

		fCosine= _Dot4dV(pNormalVector, pLightDirection);
		LBump[0] =  fCosine;
	
		/* Second Axis(this is the Normal so we use this value for smooth shading as well)*/
		pNormalVector[0] = *pNormals++;
		pNormalVector[1] = *pNormals++;
		pNormalVector[2] = *pNormals++;
		pNormalVector[3] = 0.0f;

		fCosine= _Dot4dV(pNormalVector, pLightDirection);
		LBump[1] =  fCosine;

		if (fCosine<0.0f) w = 0;
		else w = (BYTE)fCosine << 1;

		/* Third Axis (Tangent)*/
		pNormalVector[0] = *pBumpCoords++;
		pNormalVector[1] = *pBumpCoords++;
		pNormalVector[2] = *pBumpCoords++;
		pNormalVector[3] = 0.0f;

		fCosine= _Dot4dV(pNormalVector, pLightDirection);
		LBump[2] = fCosine;
		
		/* Now we have a local light position so we translate it to KKKQ */
		/* K1 = 255 - 255 * Intensity  */
		/* K2 = AngBump[1] * Intensity = 255 * cos(Elevation) * Intensity  */
		/* K3 = AngBump[2] * Intensity = 255 * sin (Elevation) * Intensity  */
		/* Q  = AngBump[0] = Azimuth */
		FXYZLightDirToSKK (LBump, AngBump);
		
		
		switch (nMethod)
		{
			default:
			case BUMP_METHOD_STANDARD:
				/* BUMP: Opaque -> Blend mode: DECAL_ALPHA */
				/* BASE: Light-map blending -> Blend mode: MODULATE_ALPHA, Blend Operation: DESTCOLOR/ZERO */ 
				/* The intensity is set to the maximun value = 1.0 */
				/* Important: To avoid flat shading set AngBump[1] to 255     */

				pTLVertexBump->color = RGBA_MAKE(0x00, 0x00,0x00,0xFF);
				
				//pTLVertexBump->specular = RGBA_MAKE(AngBump[1], AngBump[2], AngBump[0], 0);
				pTLVertexBump->specular = RGBA_MAKE(0xFF, AngBump[2], AngBump[0], 0);

				break;
				
				
			case BUMP_METHOD_TRANSLUCENT:
				/* BUMP: Translucent -> Blend mode: MODULATE_ALPHA, Blend Operation: SRCALPHA/INVSRCALPHA */
				/* BASE: Opaque -> Blend mode: MODULATE_ALPHA*/
				pTLVertexBump->color = RGBA_MAKE(0x00, 0x00,0x00,0xA0);

				pTLVertexBump->specular = RGBA_MAKE(0, AngBump[2], 128+AngBump[0], 128);
			
				break;
				
				
			case BUMP_METHOD_HIGHLIGHT:
				/* BUMP: Opaque -> Blend mode: DECAL_ALPHA	*/
				/* BASE: Additive blending -> Blend mode: MODULATE_ALPHA, Blend Operation: ONE/ONE */ 
				if (w<230) f = 0;
				else f = (BYTE)(((float)w - 230.0f) * 6.0f);
				pTLVertexBump->color = RGBA_MAKE(f, f, f, 0xFF);

				pTLVertexBump->specular = RGBA_MAKE(0, 255 - AngBump[2], AngBump[0], 0);
			}

		/* Smooth shading */
		if (pTLVertexObject)
		{
			pTLVertexObject->color			=	RGBA_MAKE(w,w,w,0xFF);
			pTLVertexObject->specular		=	RGBA_MAKE(0,0,0,0);

			/* Increase vertex count */
			pTLVertexObject++;
		}

		/* Increase vertex count */
		pTLVertexBump++;
	}

}
/*******************************************************************************
 * Function Name  : D3DTCheapBumpShade
 * Inputs		  : 
 * Output		  : 
 * Globals used   : 
 * Description    : Calculates Bump-map angles only (tricky way).
 * Notes          : This method is fast and cheap, but the look is not very correct.
 *                  It doesn't need local co-ordinate systems, but only works with 
 *                   upright textures.
 *	                If the light is very close to X=0 Y=0 the bumpmap jumps very quickly.
 *******************************************************************************/
void D3DTCheapBumpShade(D3DMATRIX *pMatrix,  unsigned nNumberOfVertices, D3DTLVERTEX *pTLVertexBump, D3DVECTOR LightVector, int nMethod)
{
D3DVECTOR vY_Axis, vLight; 
register i;
float fQAngle, fLightAngle, fYAngle;
BYTE  Q, K1,K2,K3;
 
	
	/* X and Y lights co-ordinates */
	vLight.x = -LightVector.x;
	vLight.y = -LightVector.y;
	vLight.z = 0.0f; 

	D3DTMatrixNormalize (&vLight);

	/* Aplying the transformation matrix to the vector looking upwards (0,1,0) (Rotations only)
	 * X and Y co-ords only.
	 */
	vY_Axis.x = pMatrix->_21;
	vY_Axis.y = pMatrix->_22;
	vY_Axis.z = 0.0f;

	D3DTMatrixNormalize (&vY_Axis);

	/* Angle between the light and (0,1,0) (Range: 0-255)*/
	fLightAngle = (vLight.y + 1.0f) * 64.0f;
	if (vLight.x<0.0f) fLightAngle = 256.0f - fLightAngle;

	/* Angle between the rotated vector and (0,1,0) (Range: 0-255)*/
	fYAngle = (vY_Axis.y + 1.0f) * 64.0f;
	if (vY_Axis.x<0.0f) fYAngle = 256.0f - fYAngle;

	/* Get the angle between these two vectors */
	switch (nMethod)
	{				 
		case BUMP_METHOD_STANDARD :
			K1 = 0;
			K2 = 255;
			K3 = 255;
			fQAngle =  64.0f + (fLightAngle - fYAngle);
			break;
			
		case BUMP_METHOD_TRANSLUCENT :
			 K1 = 128;
			 K2 = 0; 
			 K3 = 255;
			 fQAngle =  192.0f + (fLightAngle - fYAngle); 
			 break;

		case BUMP_METHOD_HIGHLIGHT:
			K1 = 0;
			K2 = 0;
			K3 = 0;
			fQAngle =  64.0f + (fLightAngle - fYAngle);
			break;
	}
		
	if (fQAngle<0.0f) fQAngle = 255.0f + fQAngle;
	
	Q = (BYTE) (fQAngle + 0.5f);

	/* Set the same value for every vertex */
	for (i=0; i<(int)nNumberOfVertices; i++)
	{
		pTLVertexBump->color	= RGBA_MAKE(0x00,0x00,0x00,0xA0);
		pTLVertexBump->specular = RGBA_MAKE(K2, K3, Q, K1);

		pTLVertexBump++;
	}
}

/*******************************************************************************
 * Function Name  : D3DTBumpCalculateLocalCoords
 * Inputs		  : 
 * Output		  : *pBumpCoords
 * Globals used   : 
 * Description    : Calculates the local coordinate systems for D3DTBumpShade() and for Naomi2 hardware.
 *					Note: This function has to be called once at the begining of the application.
 *					The array pBumpCoords has to be allocated by the user. Its size is:
 *					  NumberOfVertices * 6 * sizeof(float)
  *******************************************************************************/
void D3DTBumpCalculateLocalCoords (float *pBumpCoords, int CreationMode,
								 unsigned nNumberOfVertices, float *ptVertex,float *ptNormals, float *ptUV,
							     unsigned nNumFaces, unsigned short *ptFaces)
{
register i;
D3DVECTOR  NormalBumpX, NormalBumpY, NormalBumpZ;

	for (i=0; i<(int)nNumberOfVertices; i++)
	{
		NormalBumpY.x = *ptNormals++;
		NormalBumpY.y = *ptNormals++;
		NormalBumpY.z = *ptNormals++;

		switch (CreationMode)
		{
			case BUMP_COORDS_UPRIGHT:
					CalculateTangentSpaceMethodUpRight(&NormalBumpX, &NormalBumpY, &NormalBumpZ, 
											i, nNumFaces, ptFaces, ptVertex, ptUV); 
					break;

			case BUMP_COORDS_ANYDIRECTION:
					CalculateTangentSpaceMethodAnyUV(&NormalBumpX, &NormalBumpY, &NormalBumpZ, 
								i, nNumFaces, ptFaces, ptVertex, ptUV);
					break;

			case BUMP_COORDS_ANYDIRECTION_AVERAGE:
				CalculateTangentSpaceMethodAnyUVAverage(&NormalBumpX, &NormalBumpY, &NormalBumpZ, 
								i, nNumFaces, ptFaces, ptVertex, ptUV);
					break;
		}

		*pBumpCoords++ = NormalBumpX.x;
		*pBumpCoords++ = NormalBumpX.y;
		*pBumpCoords++ = NormalBumpX.z;

		*pBumpCoords++ = NormalBumpZ.x;
		*pBumpCoords++ = NormalBumpZ.y;
		*pBumpCoords++ = NormalBumpZ.z;
	}
}
/*******************************************************************************
 * Function Name  : CalculateTangentSpaceMethodUpRight
 * Inputs		  :
 * Output		  : 
 * Globals used   : 
 * Description    : This method is very straight forward and very simple, but only works
 *					with meshes that have been mapped 'upright'.
 *					Planar, spherical and cylindrical mapping works fine.
 *******************************************************************************/
void CalculateTangentSpaceMethodUpRight (D3DVECTOR *vBinormal, D3DVECTOR *vNormal, D3DVECTOR *vTangent, 
							int CurrentVertex, int nNumFaces, unsigned short *ptFaces, 
						   float *ptVertex, float *ptUV)
{
D3DVECTOR   BaseVector;
register	i;
float		fUA, fUB, fUC;
float		fVA, fVB, fVC;
int			IndexA, IndexB,  IndexC;

	/* Z axe */
	BaseVector.x =  0.0f;
	BaseVector.y =	1.0f;
	BaseVector.z =  0.0f;

	/* Binormal (perpendicular to Z and the Normal */
	D3DTMatrixCrossProduct(vBinormal, vNormal, &BaseVector);

	/* The Tangent vector is horizontal (perpendicular to the Binormal and the Normal)*/
	D3DTMatrixCrossProduct(vTangent, vBinormal , vNormal);


	/* Checking if the UVs have been flipped (This extra work is only for 'planar' mapping) */ 

	/* Looking for a face that contains this vertex */
	for (i=0; i<nNumFaces; i++)
	{
		IndexA = *(ptFaces+i*3+0);
		IndexB = *(ptFaces+i*3+1);
		IndexC = *(ptFaces+i*3+2);

		if (CurrentVertex == IndexA || CurrentVertex == IndexB || CurrentVertex == IndexC)
		{
			break;
		}
	}

	fUA = *(ptUV+IndexA*2+0);
	fUB = *(ptUV+IndexB*2+0);
	fUC = *(ptUV+IndexC*2+0);

	fVA = *(ptUV+IndexA*2+1);
	fVB = *(ptUV+IndexB*2+1);
	fVC = *(ptUV+IndexC*2+1);

	/* If this poly is flipped, mirror the Binormal */
	if ((fUA-fUC)*(fVB-fVC) > (fUB-fUC)*(fVA-fVC))
	{
		vBinormal->x = -vBinormal->x; 
		vBinormal->y = -vBinormal->y; 
		vBinormal->z = -vBinormal->z; 
	}

}
/*******************************************************************************
 * Function Name  : CalculateTangentSpaceMethodAnyUV
 * Inputs		  : 
 * Output		  : 
 * Globals used   : 
 * Description    : This method works with any mesh and with any type of mapping.
 *					It checks what is the correct UVs direction for each vertex.
 *******************************************************************************/
void CalculateTangentSpaceMethodAnyUV (D3DVECTOR *vBinormal, D3DVECTOR *vNormal, D3DVECTOR *vTangent, 
						   int CurrentVertex, int nNumFaces, unsigned short *ptFaces, 
						   float *ptVertex, float *ptUV)
{
int			i;
int			IndexA, IndexB,  IndexC;
D3DVECTOR   VertexA, VertexB, VertexC;
D3DVECTOR   BaseVector1, BaseVector2, vAlignedVector;
D3DVECTOR   fModUV;
float		fUA, fUB, fUC;
float		fVA, fVB, fVC;

	/*
	 * First we look for a polygon where CurrentVertex is contained.
	 */
	for (i=0; i<nNumFaces; i++)
	{
		IndexA = *(ptFaces+i*3+0);
		IndexB = *(ptFaces+i*3+1);
		IndexC = *(ptFaces+i*3+2);

		if (CurrentVertex == IndexA || CurrentVertex == IndexB || CurrentVertex == IndexC)
		{
			break;
		}
	}
		
		
	VertexA.x = *(ptVertex+IndexA*3+0);
	VertexA.y = *(ptVertex+IndexA*3+1);
	VertexA.z = *(ptVertex+IndexA*3+2);

	VertexB.x = *(ptVertex+IndexB*3+0);
	VertexB.y = *(ptVertex+IndexB*3+1);
	VertexB.z = *(ptVertex+IndexB*3+2);

	VertexC.x = *(ptVertex+IndexC*3+0);
	VertexC.y = *(ptVertex+IndexC*3+1);
	VertexC.z = *(ptVertex+IndexC*3+2);

	/*
	 * BaseVectors are A-B and A-C.
     */
	BaseVector1.x = VertexB.x - VertexA.x;
	BaseVector1.y = VertexB.y - VertexA.y;
	BaseVector1.z = VertexB.z - VertexA.z;

	BaseVector2.x = VertexC.x - VertexA.x;
	BaseVector2.y = VertexC.y - VertexA.y;
	BaseVector2.z = VertexC.z - VertexA.z;

	fUA = *(ptUV+IndexA*2+0) + 10.0f;
	fUB = *(ptUV+IndexB*2+0) + 10.0f;
	fUC = *(ptUV+IndexC*2+0) + 10.0f;

	fVA = *(ptUV+IndexA*2+1) + 10.0f;
	fVB = *(ptUV+IndexB*2+1) + 10.0f;
	fVC = *(ptUV+IndexC*2+1) + 10.0f;
   
	/* 
	 * Check if any of the vector is already aligned 
	 * If it is, use that vector as the tangent direction.
	 */
	if (fUB==fUA || fUC==fUA) 
	{
		if(fUB==fUA)
		{
			fModUV.x = (fVA<fVB) ? -1.0f: 1.0f;
			fModUV.y = 0.0f;
		}
		else if(fUC==fUA)
		{
			fModUV.x = 0.0f;
			fModUV.y = (fVA<fVC) ? 1.0f: -1.0f;
		}
	}
	else
	{
		/*
		 * fModUV.x and fModUV.x are the values that multiplied by (B-A) and (C-A)
		 * gives to you two points that are in the line where U=0.
		 */
		fModUV.x = -fUA / (fUB - fUA);
		fModUV.y = -fUA / (fUC - fUA);
		
		/* Check for vectors that look in the other way around */
		if ((fModUV.x*fModUV.y)<0.0f) 
		{ 
			fModUV.x = -fModUV.x; 
			fModUV.y = -fModUV.y; 
		}
	
	}

	/* This is the vector that follows the tangent direction (it is not the tangent vector)*/
	vAlignedVector.x = BaseVector2.x * fModUV.y - BaseVector1.x * fModUV.x;
	vAlignedVector.y = BaseVector2.y * fModUV.y - BaseVector1.y * fModUV.x;
	vAlignedVector.z = BaseVector2.z * fModUV.y - BaseVector1.z * fModUV.x;

	D3DTMatrixNormalize (&vAlignedVector);

	/* The Binormal vector is perpendicular to the plane defined by vAlignedVector and 
	 * the Normal.
	 */
	D3DTMatrixCrossProduct(vBinormal,  vNormal, &vAlignedVector);
	
	/* The Tangent vector is the vector perpendicular to the Normal and Binormal (and
	 * that follows the vAlignedVector direction)
	 */
	D3DTMatrixCrossProduct(vTangent, vBinormal, vNormal);

	/* If the UVs have been flipped, mirror the Tangent vector */
	if ((fUA-fUC)*(fVB-fVC) > (fUB-fUC)*(fVA-fVC))
	{
		vTangent->x = -vTangent->x; 
		vTangent->y = -vTangent->y; 
		vTangent->z = -vTangent->z; 
	}
}
/*******************************************************************************
 * Function Name  : CalculateTangentSpaceMethodAnyUVAverage
 * Inputs		  : 
 * Output		  : 
 * Globals used   : 
 * Description    : This method works with any mesh and with any type of mapping.
 *					It checks what is the correct UVs direction for each vertex.
 *					The values are averaged to 'smooth' critical vertices.
 *******************************************************************************/
void CalculateTangentSpaceMethodAnyUVAverage (D3DVECTOR *vBinormal, D3DVECTOR *vNormal, D3DVECTOR *vTangent, 
						   int CurrentVertex, int nNumFaces, unsigned short *ptFaces, 
						   float *ptVertex, float *ptUV)
{
int			i;
int			IndexA, IndexB,  IndexC;
D3DVECTOR   VertexA, VertexB, VertexC;
D3DVECTOR   BaseVector1, BaseVector2, vAlignedVector;
D3DVECTOR   fModUV;
float		fUA, fUB, fUC;
float		fVA, fVB, fVC;
D3DVECTOR   vTempBinormal;
float		nNumBinormals = 0.0f;

	vTempBinormal.x = 0.0f;
	vTempBinormal.y = 0.0f;
	vTempBinormal.z = 0.0f;

	/*
	 * First we look for all the polygons where CurrentVertex is contained.
	 */
	for (i=0; i<nNumFaces; i++)
	{
		IndexA = *(ptFaces+i*3+0);
		IndexB = *(ptFaces+i*3+1);
		IndexC = *(ptFaces+i*3+2);

		if (CurrentVertex == IndexA || CurrentVertex == IndexB || CurrentVertex == IndexC)
		{
		
		
			VertexA.x = *(ptVertex+IndexA*3+0);
			VertexA.y = *(ptVertex+IndexA*3+1);
			VertexA.z = *(ptVertex+IndexA*3+2);

			VertexB.x = *(ptVertex+IndexB*3+0);
			VertexB.y = *(ptVertex+IndexB*3+1);
			VertexB.z = *(ptVertex+IndexB*3+2);

			VertexC.x = *(ptVertex+IndexC*3+0);
			VertexC.y = *(ptVertex+IndexC*3+1);
			VertexC.z = *(ptVertex+IndexC*3+2);

			/*
			 * BaseVectors are A-B and A-C.
			 */
			BaseVector1.x = VertexB.x - VertexA.x;
			BaseVector1.y = VertexB.y - VertexA.y;
			BaseVector1.z = VertexB.z - VertexA.z;

			BaseVector2.x = VertexC.x - VertexA.x;
			BaseVector2.y = VertexC.y - VertexA.y;
			BaseVector2.z = VertexC.z - VertexA.z;

			fUA = *(ptUV+IndexA*2+0) + 10.0f;
			fUB = *(ptUV+IndexB*2+0) + 10.0f;
			fUC = *(ptUV+IndexC*2+0) + 10.0f;

			fVA = *(ptUV+IndexA*2+1) + 10.0f;
			fVB = *(ptUV+IndexB*2+1) + 10.0f;
			fVC = *(ptUV+IndexC*2+1) + 10.0f;
   
	
			/* 
			 * Check if any of the vector is already aligned 
			 * If it is, use that vector as the tangent direction.
			 */
			if (fUB==fUA || fUC==fUA) 
			{
				if(fUB==fUA)
				{
					fModUV.x = (fVA<fVB) ? -1.0f: 1.0f;
					fModUV.y = 0.0f;
				}
				else if(fUC==fUA)
				{
					fModUV.x = 0.0f;
					fModUV.y = (fVA<fVC) ? 1.0f: -1.0f;
				}
			}
			else
			{
				/*
				 * fModUV.x and fModUV.x are the values that multiplied by (B-A) and (C-A)
				 * gives to you two points that are in the line where U=0.
				 */
				fModUV.x = -fUA / (fUB - fUA);
				fModUV.y = -fUA / (fUC - fUA);
		
				/* Check for vectors that look in the other way around */
				if ((fModUV.x*fModUV.y)<0.0f) 
				{ 
					fModUV.x = -fModUV.x; fModUV.y = -fModUV.y; 
				}
			}

			/* This is the vector that follows the tangent direction (it is not the tangent vector)*/
			vAlignedVector.x = BaseVector2.x * fModUV.y - BaseVector1.x * fModUV.x;
			vAlignedVector.y = BaseVector2.y * fModUV.y - BaseVector1.y * fModUV.x;
			vAlignedVector.z = BaseVector2.z * fModUV.y - BaseVector1.z * fModUV.x;

			D3DTMatrixNormalize (&vAlignedVector);

			/* The Binormal vector is perpendicular to the plane defined by vAlignedVector and 
			 * the Normal.
			 */
			D3DTMatrixCrossProduct(vBinormal, vNormal, &vAlignedVector);

			vTempBinormal.x += vBinormal->x;
			vTempBinormal.y += vBinormal->y;
			vTempBinormal.z += vBinormal->z;

			nNumBinormals++;
		}
	}

	if (nNumBinormals==0) return;

	/* Averaging the result */
	vBinormal->x = (float) (vTempBinormal.x/nNumBinormals);
	vBinormal->y = (float) (vTempBinormal.y/nNumBinormals);
	vBinormal->z = (float) (vTempBinormal.z/nNumBinormals);

	D3DTMatrixNormalize (vBinormal);

	/* 
	 * We have already the Normal vector and the Binormal direction (UV direction).
	 * Just a cross product are needed to calculate the third axe (Tangent vector).
	 */
	D3DTMatrixCrossProduct(vTangent, vBinormal, vNormal);

	/* If the UVs have been flipped, mirror the Tangent vector */
	if ((fUA-fUC)*(fVB-fVC) > (fUB-fUC)*(fVA-fVC))
	{
		vTangent->x = -vTangent->x; 
		vTangent->y = -vTangent->y; 
		vTangent->z = -vTangent->z; 
	}
}

/*************************************************************************
* Name : bldconv.c
* Title :  Bump Map Light Direction Conversion
* Author : Simon Fenney
* Created : 17/06/1998
*
* Copyright : 1998 by Imagination Technologies Limited. All rights reserved.
* : No part of this software, either material or conceptual 
* : may be copied or distributed, transmitted, transcribed,
* : stored in a retrieval system or translated into any 
* : human or computer language in any form by any means,
* : electronic, mechanical, manual or other-wise, or 
* : disclosed to third parties without the express written
* : permission of Imagination Technologies Limited, Unit 8, HomePark
* : Industrial Estate, King's Langley, Hertfordshire,
* : WD4 8LZ, U.K.
*
* Description :	 Routines to convert from a cartesian XYZ light
*				direction format, to the OLD S, K2, K3 angular format.
*				
*				One routine assumes the XYZ is specied as 3 signed bytes,
*				while the other assumes 3 floats.
*
* Platform : ANSI/IEEE compatible
*
* $Log$
*
*************************************************************************/

#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/*
// Magic numbers for converting Floats to "Ints" via FP addition
*/
#define F_TO_I_CONVERT (1.5f * 8388608.0f)
#define F_TO_I_CONVERT_256 (1.5f * 8388608.0f / 256.0f)

/*
// Code to set up the Inverse Square root look up table.
// (Some of this is adapted from Graphics Gems V p16)
//
//
// Parameters...
*/

#define LOOKUP_BITS	(5)		/*Number of manitssa bits for lookup*/
#define EXP_POS		(23)	/*pos of exponent*/
#define EXP_BIAS	(127)	/*bias of exponent*/

/*
// Derived parameters
*/
#define LOOKUP_POS	(EXP_POS-LOOKUP_BITS) 	/*pos of mantissa lookup*/
#define SEED_POS	(EXP_POS - 8)			/*pos of mantissa seed*/
#define TABLE_SIZE	(2 << LOOKUP_BITS)		/*size of table IN BYTES*/
#define LOOKUP_MASK	(TABLE_SIZE - 1)
#define GET_EXP(a)	(((a) >> EXP_POS)& 0xFF)/*extract Exponent*/
#define SET_EXP(a)	((a) << EXP_POS)		/*set exponent*/

#define GET_EMANT(a)	(((a) >> LOOKUP_POS) & LOOKUP_MASK) /*Mantissa MSBs*/
#define SET_MANTSEED(a)	(((UINT32) (a)) << SEED_POS)	/*set mantissa 8 MSBs*/

typedef union
{
	UINT32 i;
	float f;
}flong;

/*
// Define the lookup table for the Inverse Square root
// seeds - Again based on Graphics Gems V. p 16
*/
const static UINT8 iSqrt[TABLE_SIZE] =
{0x6A, 0x64, 0x5F, 0x5A, 0x55, 0x50, 0x4C, 0x48, 
 0x44, 0x40, 0x3C, 0x38, 0x34, 0x31, 0x2E, 0x2A, 
 0x27, 0x24, 0x21, 0x1F, 0x1C, 0x19, 0x16, 0x14, 
 0x11, 0x0F, 0x0D, 0x0A, 0x08, 0x06, 0x04, 0x02, 
 0xFF, 0xF8, 0xF0, 0xE9, 0xE2, 0xDC, 0xD6, 0xD0, 
 0xCA, 0xC4, 0xBF, 0xB9, 0xB4, 0xB0, 0xAB, 0xA6, 
 0xA2, 0x9E, 0x99, 0x95, 0x91, 0x8E, 0x8A, 0x86, 
 0x83, 0x7F, 0x7C, 0x79, 0x76, 0x73, 0x70, 0x6D
};

/*
// Define table for arctan computation. This
// is quite small so should be resident
// in the cache assuming that we do a batch
// of light direction conversions.
//
// Note this is indexed by the concatenation
// of the following 3 bits...
// (Sign Bit of Z, Sign Bit of X, "|Z|>|X|")
//
// This gives the following numbering scheme...
//		\	|	/
//		 \3	|1 /
//		  \	| /
//		2  \|/	0
//    -------------
//		6  /|\
//		  /	| \	 4
//		 /	|  \
//		/	|	\
//	   /  7 |  5 \
//
*/
const static float Octants[8] = 
{    0.0f,  64.0f,  128.0f, -64.0f,
   256.0f,-192.0f, -128.0f, 192.0f};

/*
// Macro to access a float as an integer
*/
#define FTOI(X) (* (int*) (&X))

/*
// Macro to mask off the sign bit
*/
#define FP_SIGN_MASK (0x7FFFFFFF)

/*
// A small "floating point" number - approx
// 2^(-100) 
*/
#define EPSILON (0x20 << (30 - 7)) 


/**************************************************************************
 * Function Name  : FXYZLightDirToSKK
 * Inputs         : fxyz:   Light direction vector in floats.
 * Outputs        : skk:   Light direction as angle S and Sin(T), Cos(T)
 * Input/Output	  : NONE
 * Returns        : NONE
 * Global Used    : NONE
 *
 * Description    : As for IXYZLightDirToSKK except that it takes float as
 *					input. (This version is intended to support D3D)
 **************************************************************************/
void FXYZLightDirToSKK(const float fxyz[3],
					UINT8  skk[3])
{

	/*
	// Values for computing arctan - needed to get angle "s"
	*/
	float fxzMax, fxzMin; 	/*the max and min of x and z (via magnitudes)*/
	float y;				/*FP equivalents of y*/

	int   octant;			/*which octant the XZ lies in*/
		
	flong flong0, flong1, flong2;/*used to compute inverse sqrts and float-ints*/
	UINT32 a0, a1;


	float xzSQ, xyzSQ;	/*x^2+z^2 and x^2+y^2+z^2*/
	float Rxz,  Rxyz;	/* inverse sqrts of the above*/

	float sinT, cosT;

	float s;			/*value used to compute s etc via arctan*/



	/*
	// calc x^2+z^2
	*/
	xzSQ  = fxyz[0] * fxyz[0] + fxyz[2] * fxyz[2];

	/*
	// Work out least sig bit of the octant XZ is in.
	//
	// First check for a bad case - the case where we don't care
	// which angle S is at all. This is when both x and z are tiny.
	*/
	if(((FTOI(fxyz[0]) | FTOI(fxyz[2])) & FP_SIGN_MASK) < EPSILON)
	{
		octant = 0;
		fxzMax = 1.0f;
		fxzMin = 0.0f;
	}
	/*
	// else if X larger	- do comparison in integer because
	// FP compare on intel is shite.
	*/
	else if((FTOI(fxyz[0])& FP_SIGN_MASK)  >= (FTOI(fxyz[2]) & FP_SIGN_MASK))
	{
		octant = 0;
		fxzMax = fxyz[0];
		fxzMin = fxyz[2];	
	}
	else
	{
		octant = 1;
		fxzMax = fxyz[2];
		fxzMin = fxyz[0];	
	}

	/*
	// check for  negative y values.  The angle version can't
	// cope with them.
	*/
	if( FTOI(fxyz[1]) & ~FP_SIGN_MASK)
	{
		y = 0.00001f;
	}
	else
	{
		y = fxyz[1]; 
	}

	/*
	// 	 and x^2+y^2+z^2  (ie square of length of vector)
	*/
	xyzSQ = xzSQ + y * y;

  	/*
	// Get the seeds for the inverse square root approximations.
	*/
	flong0.f = xzSQ;
	flong1.f = xyzSQ;

	/*
	// "Kick off" xzMin/xzMax.  We don't actually need the result
	// of this for a while, so we should be able to do some integer
	// computation in the mean time.
	*/
	s = fxzMin / fxzMax;


	/*
	// "convert" each float to 'integer'
	*/
	a0 = flong0.i;
	a1 = flong1.i;

	/*
	// generate the 'seed's in integer form
	*/
	flong0.i = SET_EXP(((3*EXP_BIAS - 1) - GET_EXP(a0)) >> 1)
		| SET_MANTSEED(iSqrt[GET_EMANT(a0)]);

	flong1.i = SET_EXP(((3*EXP_BIAS - 1) - GET_EXP(a1)) >> 1)
		| SET_MANTSEED(iSqrt[GET_EMANT(a1)]);

	/*
	// and "convert" them back to float
	*/
	Rxz  = flong0.f;
	Rxyz = flong1.f;

	/*
	// Hopefully by now the division will be about done.
	*/
	/*
	// Compute the 'octant' bit of the arctan using quadratic
	// approximation. Note that we want 0-360 degrees represented
	// by 0 to 256, so one octant goes from 0-32.
	*/
	s = (float) fabs(s);
	s = (-11.562812f * s + 43.562812f) * s;

	/*
	// Do one iteration to double the number of accuracy bits for the
	// the inverse square roots
	*/
	Rxz  = (3.0f - Rxz  * Rxz  * xzSQ)  * Rxz  * 0.5f; 
	Rxyz = (3.0f - Rxyz * Rxyz * xyzSQ) * Rxyz * 0.5f;
	

	/*
	// We now need to look up which octant we belong to. This is
	// done using sign bits and the table. By using the table
	// and fabs, we don't have to use branches.
	//
	// The Z>X is the least sig bit, the sign of X the next most sig,
	// and sign of Z the most sig. 
	*/
	octant |= ((FTOI(fxyz[0]) >> 30) & 0x2) | ((FTOI(fxyz[2]) >> 29) & 0x4);

	s = (float) fabs(s - Octants[octant]);
 
 	/*
	// Finally, compute sine and cosine
	*/
	sinT = y * Rxyz;
	cosT = (Rxz * xzSQ) *  Rxyz;

	/*
	// Convert them all to "integer" using the magic number conversion
	// method
	*/
	flong0.f = s    + F_TO_I_CONVERT;
	flong1.f = sinT + F_TO_I_CONVERT_256;
	flong2.f = cosT + F_TO_I_CONVERT_256;

	/*
	// because the rounding mode is probably not truncate, check for possible
	// overflow (ie > 0xFF). The chances of this is small, so first test for ANY
	// overflow and then if it occurs, do the more individual tests...
	*/
	if((flong0.i | flong1.i | flong2.i) & 0x100)
	{
		/*
		// Check for individual overflow
		*/
		if(flong0.i & 0x100)
		{
			skk[0] = (UINT8) 255;
		}
		else
		{
			skk[0] = (UINT8) flong0.i;
		}

		if(flong1.i & 0x100)
		{
			skk[1] = (UINT8) 255;
		}
		else
		{
			skk[1] = (UINT8) flong1.i;
		}
	
		if(flong2.i & 0x100)
		{
			skk[2] = (UINT8) 255;
		}
		else
		{
			skk[2] = (UINT8) flong2.i;
		}
	}
	/*
	// Else overflow free
	*/
	else
	{
		skk[0] = (UINT8) flong0.i;
		skk[1] = (UINT8) flong1.i;
		skk[2] = (UINT8) flong2.i;
	}
}
/*
// End of file
*/
