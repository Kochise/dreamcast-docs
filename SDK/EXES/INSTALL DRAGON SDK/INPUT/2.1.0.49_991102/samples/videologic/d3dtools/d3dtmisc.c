/*****************************************************************************
  Name : D3DTMisc.c
  Date : July 1998
  Platform : ANSI compatible
 
  * Description : 
  This file is part of the TOOLS library (D3DTools.lib) used
  with the SDK demos for PowerVR series 2.

  Miscallenous functions used in 3D rendering.


  Copyright : 1999 by Imagination Technologies Limited. All rights reserved.
******************************************************************************/
#include <stdio.h>
#include <d3d.h>
#include "D3DTMisc.h"



/*******************************************************************************
 * Function Name  :	D3DTMiscDisplayMatrixInDebug
 * Input		  : *pMatrix
 * Globals used	  : None
 * Description    : Display matrix in debug output.
 *
 *******************************************************************************/
void D3DTMiscDisplayMatrixInDebug(const D3DMATRIX *pMatrix)
{
	TCHAR	pszString[300];
	
	/* Format string */
	wsprintf(pszString, TEXT("%f	%f	%f	%f\n%f	%f	%f	%f\n%f	%f	%f	%f\n%f	%f	%f	%f\n"),
	pMatrix->_11, pMatrix->_12, pMatrix->_13, pMatrix->_14, 
	pMatrix->_21, pMatrix->_22, pMatrix->_23, pMatrix->_24, 
	pMatrix->_31, pMatrix->_32, pMatrix->_33, pMatrix->_34,
	pMatrix->_41, pMatrix->_42, pMatrix->_43, pMatrix->_44);

	/* Display string */
	OutputDebugString(pszString);
}


/*******************************************************************************
 * Function Name  : D3DTMiscDisplayVectorInDebug
 * Input		  : *pVector
 * Globals used	  : None
 * Description    : Display vector in debug output.
 *
 *******************************************************************************/
void D3DTMiscDisplayVectorInDebug(const D3DVECTOR *pVector)
{
	TCHAR	pszString[200];

	/* Format string */
	wsprintf(pszString, TEXT("(%f, %f, %f)\n"), pVector->x, pVector->y, pVector->z);

	/* Display string */
	OutputDebugString(pszString);
}


/*******************************************************************************
 * Function Name  : D3DTMiscSetBackgroundColor
 * Inputs		  : lpD3D3, lpDev3, lpView3, dwColor
 * Globals used	  : None
 * Description    : Define a material color to background.
 *
 *******************************************************************************/
void D3DTMiscSetBackgroundColor(LPDIRECT3D3 lpD3D3, LPDIRECT3DDEVICE3 lpDev3, LPDIRECT3DVIEWPORT3 lpView3, D3DCOLOR dwColor)
{
	D3DMATERIALHANDLE	hMat=0;					
	LPDIRECT3DMATERIAL3 lpMat=NULL;
	D3DMATERIAL			mat;
	HRESULT				hres;

	/* Create material */
	if (lpD3D3->lpVtbl->CreateMaterial(lpD3D3, &lpMat, NULL)!=D3D_OK) 
	{
		OutputDebugString(TEXT("Failed in CreateMaterial\n"));
    }
	memset(&mat, 0, sizeof(D3DMATERIAL));
    mat.dwSize = sizeof(D3DMATERIAL);
    mat.diffuse.r = (D3DVALUE)(RGB_GETRED(dwColor)/255.0f);
    mat.diffuse.g = (D3DVALUE)(RGB_GETGREEN(dwColor)/255.0f);
    mat.diffuse.b = (D3DVALUE)(RGB_GETBLUE(dwColor)/255.0f);
    mat.ambient.r = (D3DVALUE)1.0;
    mat.ambient.g = (D3DVALUE)1.0;
    mat.ambient.b = (D3DVALUE)1.0;
    mat.specular.r = (D3DVALUE)1.0;
    mat.specular.g = (D3DVALUE)1.0;
    mat.specular.b = (D3DVALUE)1.0;
    mat.power = (float)40.0;
    mat.hTexture = 0;
    mat.dwRampSize = 1;
    lpMat->lpVtbl->SetMaterial(lpMat, &mat);
    lpMat->lpVtbl->GetHandle(lpMat, lpDev3, &hMat);

	/* Set background */
	hres=lpView3->lpVtbl->SetBackground(lpView3, hMat);
	if (hres!=DD_OK)
	{
		OutputDebugString(TEXT("SetBackground failed\n"));
	}
}


