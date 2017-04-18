/*==========================================================================
 *
 *  Copyright (C) 1995, 1996, 1997 Microsoft Corporation.
 *  All Rights Reserved.
 *
 *  File:    tex1.c
 *  Purpose: Functions particular to the texture-wrapping sample
 *
 ***************************************************************************/

#include <windows.h>
#include "rmdemo.h"
#include <d3drmwin.h>
#include <d3drm.h>
#include "rmtex.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

float wOx,wOy,wOz;
float wZx,wZy,wZz;
float wYx,wYy,wYz;
float tOx,tOy;
float tSx,tSy;

int		floatToInt(float f );
float	intToFloat(int i );
char*	floatToText(float f);
float	textToFloat(char* t);
char*	intToText(int i);
int		textToInt(char* t);

int floatToInt(float f)
{
   return (int)f;
}
float intToFloat(int i )
{
   return (float)i;
}
static char szBuf[128];
char* floatToText(float f)
{
   sprintf(szBuf,"%f",f);
   return szBuf;
}
float textToFloat(char* t)
{
  float f;
  f = (float)atof(t);
  return f;
}
char* intToText(int i)
{
   sprintf(szBuf,"%i",i);
   return szBuf;
}
int  textToInt(char* t)
{
  int i;
  i = atoi(t);
  return i;
}

LPDIRECT3DRMFRAME fObj = NULL;
BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
           LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    LPDIRECT3DRMMESHBUILDER builder = NULL;
    LPDIRECT3DRMFRAME frame = NULL;
    LPDIRECT3DRMTEXTURE tex = NULL;
    LPDIRECT3DRMMATERIAL mat = NULL;
    LPDIRECT3DRMWRAP wrap = NULL;
    LPDIRECT3DRMLIGHT l1 = NULL;
    LPDIRECT3DRMLIGHT l2 = NULL;
    HRESULT rval;

    dev;
    view;
    camera;

    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_AMBIENT, D3DVAL(0.2),
                                  D3DVAL(0.2), D3DVAL(0.2), &l1)))
                                  goto generic_error;
    if (FAILED(scene->lpVtbl->AddLight(scene, l1)))
        goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &frame)))
        goto generic_error;
    if (FAILED(frame->lpVtbl->SetOrientation(frame, scene, -D3DVAL(1), -D3DVAL(1),
                                  D3DVAL(1), D3DVAL(0), D3DVAL(1), D3DVAL(0))))
                                  goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_DIRECTIONAL, D3DVAL(1),
                                  D3DVAL(1), D3DVAL(1), &l2)))
                                  goto generic_error;
    if (FAILED(frame->lpVtbl->AddLight(frame, l2)))
        goto generic_error;
    RELEASE(frame);

    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &frame)))
        goto generic_error;
    if (FAILED(frame->lpVtbl->SetPosition(frame, scene, D3DVAL(0), D3DVAL(0), D3DVAL(15))))
        goto generic_error;
    if (FAILED(frame->lpVtbl->SetRotation(frame, scene, D3DVAL(1.1), D3DVAL(0.3), 
                               D3DVAL(0.0), D3DVAL(0.04))))
                               goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &builder)))
        goto generic_error;
    rval = builder->lpVtbl->Load(builder, "sphere4.x", NULL,
                        D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load sphere4.x.\n%s", D3DRMErrorToString(rval));
        goto ret_with_error;
    }

    rval = lpD3DRM->lpVtbl->LoadTexture(lpD3DRM, "check.ppm", &tex);
    if (rval != D3DRM_OK) {
        Msg("Failed to load check.ppm.\n%s", D3DRMErrorToString(rval));
        goto ret_with_error;
    }
    texImage = tex->lpVtbl->GetImage(tex);
    if (FAILED(lpD3DRM->lpVtbl->CreateMaterial(lpD3DRM, D3DVAL(10.0), &mat)))
        goto generic_error;

    if (FAILED(builder->lpVtbl->SetTexture(builder, tex)))
        goto generic_error;
    if (FAILED(builder->lpVtbl->SetMaterial(builder, mat)))
        goto generic_error;
    if (FAILED(builder->lpVtbl->SetColorRGB(builder, D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0))))
        goto generic_error;

    if (FAILED(builder->lpVtbl->CreateMesh(builder, &mesh)))
        goto generic_error;
    RELEASE(builder);

    setBoxDims(&box);

    wOx =  D3DVAL(0.0);
    wOy =  D3DVAL(0.0);
    wOy =  D3DVAL(0.0);
    wZx =  D3DVAL(1.0);
    wZy =  D3DVAL(0.0);
    wZy =  D3DVAL(0.0);
    wYx =  D3DVAL(0.0);
    wYy =  D3DVAL(1.0);
    wYx =  D3DVAL(0.0);
    tOx =  D3DVAL(0.0);
    tOy =  D3DVAL(0.0);
    //setup for cylindrical
    tSx =  D3DVAL(1.0);
    tSy =  D3DVAL(1.0/texImage->height);
    if (FAILED(lpD3DRM->lpVtbl->CreateWrap(lpD3DRM, D3DRMWRAP_CYLINDER, NULL, 
                              wOx,wOy,wOz,
                              wZx,wZy,wZz,
                              wYx,wYy,wYz,
                              tOx,tOy,
                              tSx,tSy,
                              &wrap)))
                              goto generic_error;

    if (FAILED(wrap->lpVtbl->Apply(wrap, (LPDIRECT3DRMOBJECT)mesh)))
        goto generic_error;
    if (FAILED(frame->lpVtbl->AddVisual(frame, (LPDIRECT3DRMVISUAL) mesh)))
        goto generic_error;

    fObj = frame;
    fObj->lpVtbl->AddRef(fObj);

    RELEASE(frame);
    RELEASE(wrap);
    RELEASE(tex);
    RELEASE(mat);
    RELEASE(l1);
    RELEASE(l2);
    return TRUE;
generic_error:
    Msg("A failure occured while building the scene.\n");
ret_with_error:
    RELEASE(mesh);
    RELEASE(builder);
    RELEASE(frame);
    RELEASE(tex);
    RELEASE(mat);
    RELEASE(wrap);
    RELEASE(l1);
    RELEASE(l2);
    return FALSE;
}

void
OverrideDefaults(Defaults* defaults)
{
    defaults->bConstRenderQuality = TRUE;
    lstrcpy(defaults->Name, "Texture Mapping Direct3DRM Example");
}
void setBoxDims(LPD3DRMBOX box)
{
   if (FAILED(mesh->lpVtbl->GetBox(mesh,box)))
      return;
   maxx = box->max.x;
   minx = box->min.x;
   width = (float)fabs((double)maxx - (double)minx);
   maxy = box->max.y;
   miny = box->min.y;
   height = (float)fabs((double)maxy - (double)miny);
   maxz = box->max.z;
   minz = box->min.z;
   depth =  (float)fabs((double)maxz - (double)minz);
}
