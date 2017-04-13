/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: triangle.c
 *
 ***************************************************************************/

#include <math.h>
#include <d3d.h>
#include "d3ddemo.h"

LPDIRECT3DMATERIAL2 lpBmat, lpMat1;
#define NUM_SQUARESTRIP 50
#define NUM_VERTICES (4 + (NUM_SQUARESTRIP + 1) * 2)
#define NUM_TRIANGLES 1
#define NUM_TSTRIPIDX ((NUM_SQUARESTRIP + 1) * 2 )
#define NUM_TFANIDX (NUM_TSTRIPIDX + 1)
#define NUM_INDICES (NUM_TSTRIPIDX + NUM_TFANIDX)
D3DTLVERTEX src_v[NUM_VERTICES];
WORD src_t[NUM_INDICES];
DWORD hTex;
DWORD hMat;

void CreateGridStrip(int x)
{
}

void
OverrideDefaults(Defaults* defaults)
{
    lstrcpy(defaults->Name, "Triangle D3D Example");
    defaults->rs.bPerspCorrect = FALSE;
    defaults->bResizingDisabled = FALSE;
}

BOOL
RenderScene(LPDIRECT3DDEVICE2 lpDev, LPDIRECT3DVIEWPORT2 lpView,
            LPD3DRECT lpExtent)
{
	LPD3DTLVERTEX tstrip_v = src_v+3;
        D3DCLIPSTATUS status={D3DCLIPSTATUS_EXTENTS2, 0, 2048.0f, 0.0f, 2048.0f, 0.0f, 0.0f, 0.0f};

    if (lpDev->lpVtbl->BeginScene(lpDev) != D3D_OK)
        return FALSE;
    if (lpDev->lpVtbl->SetLightState(lpDev, D3DLIGHTSTATE_MATERIAL, hMat) != D3D_OK)
        return FALSE; 
    if (lpDev->lpVtbl->SetRenderState(lpDev, D3DRENDERSTATE_TEXTUREHANDLE, hTex) != D3D_OK)
        return FALSE; 
    if (lpDev->lpVtbl->SetClipStatus(lpDev, &status) != D3D_OK)
        return FALSE; 
/*	if (lpDev->lpVtbl->DrawIndexedPrimitive(lpDev, D3DPT_TRIANGLELIST, 
					   D3DVT_TLVERTEX, (LPVOID)src_v, 3, (LPWORD)src_t, 
                                           NUM_TRIANGLES*3, D3DDP_WAIT) != D3D_OK)
		return FALSE;
	if (lpDev->lpVtbl->DrawIndexedPrimitive(lpDev, D3DPT_TRIANGLESTRIP, 
					   D3DVT_TLVERTEX, (LPVOID)tstrip_v, NUM_TSTRIPIDX, (LPWORD)src_t, 
                                           NUM_TSTRIPIDX, D3DDP_WAIT) != D3D_OK)
		return FALSE;
	if (lpDev->lpVtbl->DrawIndexedPrimitive(lpDev, D3DPT_TRIANGLEFAN, 
					   D3DVT_TLVERTEX, (LPVOID)tstrip_v, NUM_TSTRIPIDX + 1, (LPWORD)src_t + NUM_TSTRIPIDX, 
                                           NUM_TFANIDX, D3DDP_WAIT) != D3D_OK)
		return FALSE;*/
	if (lpDev->lpVtbl->DrawPrimitive(lpDev, D3DPT_TRIANGLEFAN, 
                                           D3DVT_TLVERTEX, (LPVOID)tstrip_v, NUM_TSTRIPIDX, D3DDP_WAIT) != D3D_OK)
		return FALSE;
/*	if (lpDev->lpVtbl->DrawPrimitive(lpDev, D3DPT_TRIANGLESTRIP, 
                                           D3DVT_TLVERTEX, (LPVOID)tstrip_v, NUM_TSTRIPIDX, D3DDP_WAIT) != D3D_OK)
		return FALSE;
	if (lpDev->lpVtbl->DrawPrimitive(lpDev, D3DPT_TRIANGLELIST, 
                                           D3DVT_TLVERTEX, (LPVOID)src_v, 3, D3DDP_WAIT) != D3D_OK)
		return FALSE;*/
    if (lpDev->lpVtbl->GetClipStatus(lpDev, &status) != D3D_OK)
        return FALSE; 
    if (lpDev->lpVtbl->EndScene(lpDev) != D3D_OK)
        return FALSE;
	lpExtent->x1 = (LONG)floor((double)status.minx);
	lpExtent->x2 = (LONG)ceil((double)status.maxx);
	lpExtent->y1 = (LONG)floor((double)status.miny);
	lpExtent->y2 = (LONG)ceil((double)status.maxy);
    return TRUE;
}

void
ReleaseScene(void)
{
    return;
}

void
ReleaseView(LPDIRECT3DVIEWPORT2 lpView)
{
    lpView;
    RELEASE(lpMat1);
    RELEASE(lpBmat);
}

BOOL
InitScene(void)
{
	int i;
	LPD3DTLVERTEX tstrip_v = src_v+3;

    /*
     * Setup vertices for single triangle
     */
    memset(&src_v[0], 0, sizeof(D3DVERTEX) * NUM_VERTICES);
    src_v[0].sx = D3DVAL(10.0);
    src_v[0].sy = D3DVAL(10.0);
    src_v[0].sz = D3DVAL(0.1);
    src_v[0].rhw = D3DVAL(1.0);
    src_v[0].color = RGBA_MAKE(255, 0, 255, 255);
    src_v[0].specular = RGB_MAKE(0, 0, 255);
    src_v[0].tu = D3DVAL(0.0);
    src_v[0].tv = D3DVAL(0.0);
    src_v[1].sx = D3DVAL(300.0);
    src_v[1].sy = D3DVAL(50.0);
    src_v[1].sz = D3DVAL(0.9);
    src_v[1].rhw = D3DVAL(2.0);
    src_v[1].color = RGBA_MAKE(255, 255, 255, 255);
    src_v[1].specular = RGB_MAKE(0, 0, 0);
    src_v[1].tu = D3DVAL(1.0);
    src_v[1].tv = D3DVAL(1.0);
    src_v[2].sx = D3DVAL(150.0);
    src_v[2].sy = D3DVAL(180.0);
    src_v[2].sz = D3DVAL(0.6);
    src_v[2].rhw = D3DVAL(1.0);
    src_v[2].color = RGBA_MAKE(255, 255, 0, 255);
    src_v[2].specular = RGB_MAKE(0, 0, 0);
    src_v[2].tu = D3DVAL(0.0);
    src_v[2].tv = D3DVAL(1.0);

    /*
     * Setup vertices for triangle strip
     */
	for (i=0; i<=NUM_SQUARESTRIP; ++i)
	{
		tstrip_v[i*2].sx = i*300.0f/NUM_SQUARESTRIP;
		tstrip_v[i*2].sy = 200.0f;
		tstrip_v[i*2].sz = .5f;
		tstrip_v[i*2].rhw = 1.0f;
		tstrip_v[i*2].color = RGBA_MAKE(255, 255, 255, 255);
		tstrip_v[i*2].specular = RGB_MAKE(0, 0, 0);
		tstrip_v[i*2].tu = (float)i/NUM_SQUARESTRIP;
		tstrip_v[i*2].tv = 0.0f;
		tstrip_v[i*2+1].sx = i*300.0f/NUM_SQUARESTRIP;
		tstrip_v[i*2+1].sy = 0.0f;
		tstrip_v[i*2+1].sz = .5f;
		tstrip_v[i*2+1].rhw = 1.0f;
		tstrip_v[i*2+1].color = RGBA_MAKE(255, 255, 255, 255);
		tstrip_v[i*2+1].specular = RGB_MAKE(0, 0, 0);
		tstrip_v[i*2+1].tu = (float)i/NUM_SQUARESTRIP;
		tstrip_v[i*2+1].tv = 1.0f;
	}
	/* Set up base vertex for trifan */
	tstrip_v[i*2].sx = 0.0f;
	tstrip_v[i*2].sy = 100.0f;
	tstrip_v[i*2].sz = .5f;
	tstrip_v[i*2].rhw = 1.0f;
	tstrip_v[i*2].color = RGBA_MAKE(255, 255, 255, 255);
	tstrip_v[i*2].specular = RGB_MAKE(0, 0, 0);
	tstrip_v[i*2].tu = 0.0f;
	tstrip_v[i*2].tv = 0.5f;

	/*
	 * Set Up Triangle strip indices & base Tri Fan index
	 */
	for (i=0; i<=NUM_TSTRIPIDX; ++i)
		src_t[i]=i;
	/*
	 * Set Up Triangle fan indices
	 */
	for (i=0; i<=NUM_SQUARESTRIP; ++i)
	{
		src_t[NUM_TSTRIPIDX+1+i]=i*2+1;
		src_t[NUM_INDICES-1-i]=i*2;
	}
    return TRUE;
}

BOOL
InitView(LPDIRECTDRAW lpDD, LPDIRECT3D2 lpD3D, LPDIRECT3DDEVICE2 lpDev,
	   LPDIRECT3DVIEWPORT2 lpView, int NumTextures,
	   LPD3DTEXTUREHANDLE TextureHandle)
{
    D3DMATERIAL bmat, mat;
    D3DMATERIALHANDLE hBmat, hMat1;

    if (lpD3D->lpVtbl->CreateMaterial(lpD3D, &lpBmat, NULL) != D3D_OK) {
	return FALSE;
    }
    memset(&bmat, 0, sizeof(D3DMATERIAL));
    bmat.dwSize = sizeof(D3DMATERIAL);
    bmat.diffuse.r = (D3DVALUE)1.0;
    bmat.diffuse.g = (D3DVALUE)1.0;
    bmat.diffuse.b = (D3DVALUE)1.0;
    bmat.ambient.r = (D3DVALUE)1.0;
    bmat.ambient.g = (D3DVALUE)1.0;
    bmat.ambient.b = (D3DVALUE)1.0;
    bmat.hTexture = TextureHandle[0];
    bmat.dwRampSize = 1;
    lpBmat->lpVtbl->SetMaterial(lpBmat, &bmat);
    lpBmat->lpVtbl->GetHandle(lpBmat, lpDev, &hBmat);
    lpView->lpVtbl->SetBackground(lpView, hBmat);

    if (lpD3D->lpVtbl->CreateMaterial(lpD3D, &lpMat1, NULL) != D3D_OK) {
	return FALSE;
    }
    memset(&mat, 0, sizeof(D3DMATERIAL));
    mat.dwSize = sizeof(D3DMATERIAL);
    mat.diffuse.r = (D3DVALUE)1.0;
    mat.diffuse.g = (D3DVALUE)1.0;
    mat.diffuse.b = (D3DVALUE)1.0;
    mat.ambient.r = (D3DVALUE)1.0;
    mat.ambient.g = (D3DVALUE)1.0;
    mat.ambient.b = (D3DVALUE)1.0;
#define SPECULAR
#ifdef SPECULAR
    mat.specular.r = (D3DVALUE)1.0;
    mat.specular.g = (D3DVALUE)1.0;
    mat.specular.b = (D3DVALUE)1.0;
    mat.power = (float)40.0;
#else
    mat.specular.r = (D3DVALUE)0.0;
    mat.specular.g = (D3DVALUE)0.0;
    mat.specular.b = (D3DVALUE)0.0;
    mat.power = (float)0.0;
#endif    
    mat.hTexture = TextureHandle[1];
    mat.dwRampSize = 16;
    lpMat1->lpVtbl->SetMaterial(lpMat1, &mat);
    lpMat1->lpVtbl->GetHandle(lpMat1, lpDev, &hMat1);
	hMat= (DWORD) hMat1;
	hTex=TextureHandle[1];
    return TRUE;
}

