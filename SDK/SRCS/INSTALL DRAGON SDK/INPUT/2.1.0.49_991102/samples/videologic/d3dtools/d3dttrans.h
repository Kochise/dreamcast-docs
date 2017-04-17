/*****************************************************************************
  Name : D3DTTrans.h
  Date : July 1998
  Platform : ANSI compatible
 
  $Revision: 1.8 $

  Description : Header file of D3DTTrans.c
				Contains structure definitions and prototypes 
				of all functions in D3DTTrans.c

  
  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#ifndef _D3DTTRANS_H_
#define _D3DTTRANS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*************
** Typedefs **
*************/
typedef struct D3DTBOUNDINGBOXTAG
{
	D3DVECTOR	Point[8];
} D3DTBOUNDINGBOX, *LPD3DTBOUNDINGBOX;


/***************
** Prototypes **
***************/
void D3DTTransComputeBoundingBox(const int nNumberOfVertices, const float *pVertex, D3DTBOUNDINGBOX *pBoundingBox);
void D3DTTransTransformBoundingBox(const D3DMATRIX *pWorldMatrix, const D3DTBOUNDINGBOX *pBoundingBox, 
								   D3DTBOUNDINGBOX *pTBoundingBox);
BOOL D3DTTransIsBoundingBoxVisible(const D3DMATRIX *pWorldMatrix, const D3DTBOUNDINGBOX *pBoundingBox, 
								   const int nViewportWidth, const int nViewportHeight,
								   const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
								   const float D, const float F, 
								   const float fViewAngleHoriz, const float fViewAngleVert,
								   BOOL *pNeedsZClipping);
void D3DTTransTransform(const D3DMATRIX *pWorldMatrix, 
						const int nNumberOfVertices, const float *pVertex, float *pTransformedVertex);
void D3DTTransTransformProject(const D3DMATRIX *pWorldMatrix, 
							   const int nNumberOfVertices, const float *pVertex, D3DTLVERTEX *pTLVertex,
							   const int nViewportWidth, const int nViewportHeight,
							   const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
							   const float D, const float F, 
							   const float fViewAngleHoriz, const float fViewAngleVert);
void D3DTTransPerspective(const int nNumberOfVertices, D3DTLVERTEX *pTLVertex,
						  const int nViewportWidth, const int nViewportHeight,
						  const float D, const float F);
void D3DTTransTransformProjectPerspective(const D3DMATRIX *pWorldMatrix, 
										  const int nNumberOfVertices, const float *pVertex, D3DTLVERTEX *pTLVertex,
										  const int nViewportWidth, const int nViewportHeight,
										  const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
										  const float D, const float F, 
										  const float fViewAngleHoriz, const float fViewAngleVert);
void D3DTTransTransformProjectZSlamPerspective(const D3DMATRIX *pWorldMatrix, 
											   const int nNumberOfVertices, const float *pVertex, D3DTLVERTEX *pTLVertex,
											   const int nViewportWidth, const int nViewportHeight,
											   const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
											   const float D, const float F, 
											   const float fViewAngleHoriz, const float fViewAngleVert);
void D3DTTransZClipProjected(const int nNumberOfVertices, D3DTLVERTEX *pTLVertex,
							 const int nNumberOfTriangles, WORD *pTriangleList, int *pNumberOfVisibleTriangles);
void D3DTTransUVEnvMap(const D3DMATRIX *pWorldMatrix,
					   const int nNumberOfVertices, const float *pNormals, D3DTLVERTEX *pTLVertex,
					   const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll);

void D3DTTransCalculateVPMatrix(D3DMATRIX *pViewMatrix,D3DMATRIX *pProjMatrix,
											   const D3DVECTOR *pCamFrom, const D3DVECTOR *pCamTo, const float fRoll,
											   const float D, const float F, 
											   const float fViewAngleHoriz, const float fViewAngleVert);

#ifdef __cplusplus
}
#endif
	

#endif

