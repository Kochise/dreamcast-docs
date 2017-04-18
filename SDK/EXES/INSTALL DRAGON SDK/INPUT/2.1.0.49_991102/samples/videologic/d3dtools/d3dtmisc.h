/*****************************************************************************
  Name : D3DTMisc.h
  Date : July 1998
  Platform : ANSI compatible
 
  Description : Header file of D3DTMisc.c
				Contains structure definitions and prototypes 
				of all functions in D3DTMisc.c

  
  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#ifndef _D3DTMISC_H_
#define _D3DTMISC_H_

#ifdef __cplusplus
extern "C" {
#endif

/************
** Defines **
************/
#ifndef RELEASE
#define RELEASE(x)	if (x) { (x)->lpVtbl->Release(x); (x)=NULL; }
#endif

/* PowerVR2-specific hardware information (used with the PowerVR2 Detection) */
#ifndef NEC_VENDOR_ID
#define NEC_VENDOR_ID	0x1033
#define PMX1_DEVICE_ID	0x0067
#define PMX1C_REVISION	0x01
#define PMX1LC_REVISION	0x02
#endif

/***************
** Prototypes **
***************/


/* Debug functions */
void	D3DTMiscDisplayMatrixInDebug(const D3DMATRIX *pMatrix);
void	D3DTMiscDisplayVectorInDebug(const D3DVECTOR *pVector);

/* Background function */
void D3DTMiscSetBackgroundColor(LPDIRECT3D3 lpD3D3, LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3, D3DCOLOR dwColor);


#ifdef __cplusplus
}
#endif
	

#endif

