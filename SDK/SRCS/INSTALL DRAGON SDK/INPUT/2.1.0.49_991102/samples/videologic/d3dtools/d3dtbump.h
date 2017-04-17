/*****************************************************************************
  Name : D3DTBump.h
  Date : May 1999
  Platform : ANSI compatible
 
  Description : Header file for D3DTBump.c.
		
  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#ifndef _D3DTBUMP_H_
#define _D3DTBUMP_H_

#ifdef __cplusplus
extern "C" {
#endif


/***********************************/
/*  BUMPMAP DEFINES                */
/***********************************/
/* These are creation methods for the bumpmap local coordinate system used by 
 * KMBumpCalculateLocalCoords() 
 *
 * The first one (BUMP_COORDS_UPRIGHT) only works fine when the texture has been aplied uniformly
 * and looking upwards. It has been added here just because is a easy and common way of calculating
 * the local coordinate system for bump-mapping. We don't recomend using it.
 * 
 * The second one (BUMP_COORDS_ANYDIRECTION) works always for any model. 
 *
 * The last one (BUMP_COORDS_ANYDIRECTION_AVERAGE) is the same but average results to 'smooth' critical vertices.
 * It is very slow, and is not really needed in most cases.
 */
#define BUMP_COORDS_UPRIGHT 0
#define BUMP_COORDS_ANYDIRECTION 1
#define BUMP_COORDS_ANYDIRECTION_AVERAGE 2

/* These are different methods to calculate bumpmap angles (specular color) on the fly. 
 * They are used by KMBumpShade().
 *
 * Blend modes:
 * BUMP_METHOD_STANDARD
 * BUMP: Opaque -> Blend mode: DECAL_ALPHA 
 * BASE: Light-map -> Blend mode: MODULATE_ALPHA, Blend Operation: DESTCOLOR/ZERO
 *
 * BUMP_METHOD_TRANSLUCENT
 * BUMP: Translucent -> Blend mode: MODULATE_ALPHA, Blend Operation: SRCALPHA/INVSRCALPHA 
 * BASE: Opaque -> Blend mode: MODULATE_ALPHA
 *
 * BUMP_METHOD_HIGHLIGHT
 * BUMP: Opaque -> Blend mode: DECAL_ALPHA	
 * BASE: Additive -> Blend mode: MODULATE_ALPHA, Blend Operation: ONE/ONE */ 

#define BUMP_METHOD_STANDARD    0
#define BUMP_METHOD_TRANSLUCENT 1
#define BUMP_METHOD_HIGHLIGHT   2


/***************/
/*  PROTOTYPES */
/***************/
/*
 *  Calculates Bump-map angles and smooth shading 
 *  Notes:
 *  Set the parameter *pTLVertexObject to NULL if you only want to calculate Bumpmap.
 *  This method uses the local coordinate systems calculated by 
 *  KMBumpCalculateLocalCoords().
 *	Call this funtion every frame to get a correct phong bumpmapping.
 */
void D3DTBumpShade(D3DMATRIX *pMatrix, 
				 unsigned nNumberOfVertices, float *pBumpCoords, float *pNormals,
				 D3DLVERTEX *pTLVertexBump, D3DLVERTEX *pTLVertexObject,
				 D3DVECTOR LightVector, int nMethod);

/*
 *  Calculates Bump-map angles only (tricky way).
 *  Notes:
 *  This method is fast and cheap, but the look is not very correct.
 *  This method is not supported by Naomi2.
 *  It doesn't need local co-ordinate systems, but only works with 
 *  upright textures.
 *	If the light is very close to X=0 Y=0 the bumpmap jumps very quickly.
 */
void D3DTCheapBumpShade(D3DMATRIX *pMatrix,  unsigned nNumberOfVertices, D3DTLVERTEX *pTLVertexBump, D3DVECTOR LightVector, int nMethod);


/*
 *  Calculates the local coordinate systems for KMBumpShade() and for Naomi2 hardware.
 *	Note: This function has to be called once at the begining of the application.
 *  The array pBumpCoords has to be allocated by the user. Its size is:
 *   NumberOfVertices * 6 * sizeof(float)
 */
void D3DTBumpCalculateLocalCoords (float *pBumpCoords, int CreationMode,
								 unsigned nNumberOfVertices, float *ptVertex,float *ptNormals, float *ptUV, 
							     unsigned nNumFaces, unsigned short *ptFaces);



#ifdef __cplusplus
}
#endif


#endif

