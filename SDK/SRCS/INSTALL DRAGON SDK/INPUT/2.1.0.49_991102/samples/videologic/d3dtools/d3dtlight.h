/*****************************************************************************
  Name : D3DTLight.h
  Date : July 1998
  Platform : ANSI compatible
 
  $Revision: 1.6 $

  Description : Header file of D3DTLight.c
				Contains structure definitions and prototypes 
				of all functions in D3DTLight.c

  
  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#ifndef _D3DTLIGHT_H_
#define _D3DTLIGHT_H_

#ifdef __cplusplus
extern "C" {
#endif


/***************
** Prototypes **
***************/
void D3DTLightSmoothShade(const D3DMATRIX *pWorldMatrix, 
						  const int nNumberOfVertices, const float *pNormals, D3DTLVERTEX *pTLVertex, 
						  const D3DVECTOR *pLightVector, const D3DCOLOR dwLightColor);

void D3DTLightSpecular(const D3DMATRIX *pWorldMatrix,
					   const int nNumberOfVertices, const float *pNormals, const float *pVertex, D3DTLVERTEX *pTLVertex,
					   const D3DVECTOR *pLightVector, const D3DVECTOR *pCamWorldPos,
					   const D3DCOLOR cDiffuse, const D3DCOLOR cSpecular,
					   const float fSpecularPower);

#ifdef __cplusplus
}
#endif
	

#endif

