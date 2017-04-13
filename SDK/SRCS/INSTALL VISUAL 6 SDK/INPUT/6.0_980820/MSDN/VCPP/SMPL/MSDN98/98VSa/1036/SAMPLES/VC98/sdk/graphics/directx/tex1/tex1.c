/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: tex1.c
 *
 ***************************************************************************/

/*
 * A texture mapping example using a cylindrical mapping.
 */

#include "rmdemo.h"

BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
	   LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    LPDIRECT3DRMMESH mesh = NULL;
    LPDIRECT3DRMMESHBUILDER builder = NULL;
    LPDIRECT3DRMFRAME frame = NULL;
    LPDIRECT3DRMTEXTURE tex = NULL;
    LPDIRECT3DRMMATERIAL mat = NULL;
    LPDIRECT3DRMWRAP wrap = NULL;
    LPDIRECT3DRMLIGHT l1 = NULL;
    LPDIRECT3DRMLIGHT l2 = NULL;
    D3DRMBOX box;
    D3DVALUE miny, maxy;
    D3DVALUE height;
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

    rval = lpD3DRM->lpVtbl->LoadTexture(lpD3DRM, "tex7.ppm", &tex);
    if (rval != D3DRM_OK) {
        Msg("Failed to load tex7.ppm.\n%s", D3DRMErrorToString(rval));
	goto ret_with_error;
    }
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

    if (FAILED(mesh->lpVtbl->GetBox(mesh, &box)))
	goto generic_error;
    maxy = box.max.y;
    miny = box.min.y;
    height = maxy - miny;

    if (FAILED(lpD3DRM->lpVtbl->CreateWrap(lpD3DRM, D3DRMWRAP_CYLINDER, NULL, D3DVAL(0.0),
                              D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0),
                              D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0),
                              D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
                              D3DDivide(miny, height), D3DVAL(1.0),
                              D3DDivide(-D3DVAL(1.0), height), &wrap)))
			      goto generic_error;

    if (FAILED(wrap->lpVtbl->Apply(wrap, (LPDIRECT3DRMOBJECT)mesh)))
	goto generic_error;
    if (FAILED(frame->lpVtbl->AddVisual(frame, (LPDIRECT3DRMVISUAL) mesh)))
	goto generic_error;

    RELEASE(frame);
    RELEASE(wrap);
    RELEASE(mesh);
    RELEASE(tex);
    RELEASE(mat);
    RELEASE(l1);
    RELEASE(l2);
    return TRUE;
generic_error:
    Msg("A failure occurred while building the scene.\n");
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
