/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: tex4.c
 *
 ***************************************************************************/

/*
 * A texture mapping example using a spherical mapping relative to the
 * camera. The texture is also used as a background for the scene.
 */

#include "rmdemo.h"

void CDECL 
applyWrap(LPDIRECT3DRMFRAME frame, void* arg, D3DVALUE delta)
{
    LPDIRECT3DRMWRAP wrap = (LPDIRECT3DRMWRAP) arg;
    LPDIRECT3DRMVISUALARRAY visuals;
    LPDIRECT3DRMVISUAL v;
    int count, i;
    LPDIRECT3DRMMESH mesh;

    frame->lpVtbl->GetVisuals(frame, &visuals);
    count = visuals->lpVtbl->GetSize(visuals);

    for (i = 0; i < count; i++) {
	visuals->lpVtbl->GetElement(visuals, i, &v);

	if (SUCCEEDED(v->lpVtbl->QueryInterface(v, &IID_IDirect3DRMMesh, &mesh))) {
	    wrap->lpVtbl->ApplyRelative(wrap, frame, (LPDIRECT3DRMOBJECT)mesh);
	    mesh->lpVtbl->Release(mesh);
	}
	v->lpVtbl->Release(v);
    }

    visuals->lpVtbl->Release(visuals);
}

void CDECL 
cleanupWrap(LPDIRECT3DRMOBJECT obj, void *arg)
{
    LPDIRECT3DRMWRAP wrap = (LPDIRECT3DRMWRAP) arg;
    obj;

    wrap->lpVtbl->Release(wrap);
}

BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
	   LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    LPDIRECT3DRMMESH mesh = NULL;
    LPDIRECT3DRMFRAME frame = NULL;
    LPDIRECT3DRMFRAME axis = NULL;
    LPDIRECT3DRMFRAME child = NULL;
    LPDIRECT3DRMTEXTURE tex = NULL;
    LPDIRECT3DRMWRAP wrap = NULL;
    LPDIRECT3DRMLIGHT light1 = NULL;
    LPDIRECT3DRMLIGHT light2 = NULL;
    LPDIRECT3DRMMESHBUILDER builder = NULL;
    HRESULT rval;
    dev;
    view;
    camera;


    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_AMBIENT, D3DVAL(0.2),
                                  D3DVAL(0.2), D3DVAL(0.2), &light1)))
				  goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_DIRECTIONAL, D3DVAL(1),
                                  D3DVAL(1), D3DVAL(1), &light2)))
				  goto generic_error;
    if (FAILED(scene->lpVtbl->AddLight(scene, light1)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &frame)))
	goto generic_error;
    if (FAILED(frame->lpVtbl->SetOrientation(frame, scene, -D3DVAL(1), -D3DVAL(1),
                                  D3DVAL(1), D3DVAL(0), D3DVAL(1), D3DVAL(0))))
				  goto generic_error;
    if (FAILED(frame->lpVtbl->AddLight(frame, light2)))
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
    rval = builder->lpVtbl->Load(builder, "sphere3.x", NULL, D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load sphere3.x.\n");
	goto ret_with_error;
    }
    if (FAILED(builder->lpVtbl->Scale(builder, D3DVAL(0.2), D3DVAL(0.2), D3DVAL(0.2))))
	goto generic_error;
    if (FAILED(builder->lpVtbl->CreateMesh(builder, &mesh)))
	goto generic_error;
    RELEASE(builder);
    if (FAILED(frame->lpVtbl->AddVisual(frame, (LPDIRECT3DRMVISUAL) mesh)))
	goto generic_error;
    RELEASE(mesh);

    if (FAILED(lpD3DRM->lpVtbl->CreateWrap(lpD3DRM, D3DRMWRAP_SPHERE, camera,
			      D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0),
			      D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
			      D3DVAL(0.0), D3DVAL(0.0), -D3DVAL(1.0),
			      D3DVAL(0.0), D3DVAL(0.0),
			      D3DVAL(5.0), D3DVAL(5.0),
			      &wrap)))
			      goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, frame, &axis)))
	goto generic_error;
    if (FAILED(axis->lpVtbl->SetRotation(axis, frame, D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(0.04))))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, axis, &child)))
	goto generic_error;
    if (FAILED(child->lpVtbl->SetPosition(child, axis, D3DVAL(3), D3DVAL(0), D3DVAL(0))))
	goto generic_error;
    if (FAILED(child->lpVtbl->SetRotation(child, axis, D3DVAL(1), D3DVAL(1), D3DVAL(0),
                               D3DVAL(0.04))))
			       goto generic_error;

    rval = lpD3DRM->lpVtbl->LoadTexture(lpD3DRM, "lake.ppm", &tex);
    if (rval != D3DRM_OK) {
	Msg("Failed to load lake.ppm.\n");
	goto ret_with_error;
    }
    if (FAILED(tex->lpVtbl->SetColors(tex, 32)))
	goto generic_error;
    if (FAILED(tex->lpVtbl->SetDecalScale(tex, TRUE)))
	goto generic_error;
    if (FAILED(tex->lpVtbl->SetDecalOrigin(tex, 128, 128)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &builder)))
	goto generic_error;
    rval = builder->lpVtbl->Load(builder, "tpot2.x", NULL, D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load tpot2.x.\n");
	goto ret_with_error;
    }

    if (FAILED(builder->lpVtbl->Scale(builder, D3DVAL(2), D3DVAL(2), D3DVAL(2))))
	goto generic_error;
    if (FAILED(builder->lpVtbl->SetTexture(builder, tex)))
	goto generic_error;
    if (FAILED(builder->lpVtbl->SetQuality(builder, D3DRMRENDER_GOURAUD)))
	goto generic_error;
    if (FAILED(builder->lpVtbl->CreateMesh(builder, &mesh)))
	goto generic_error;
    RELEASE(builder);

    if (FAILED(child->lpVtbl->AddVisual(child, (LPDIRECT3DRMVISUAL) mesh)))
	goto generic_error;
    if (FAILED(child->lpVtbl->AddMoveCallback(child, applyWrap, (void *) wrap)))
	goto generic_error;
    if (FAILED(child->lpVtbl->AddDestroyCallback(child, cleanupWrap, wrap)))
	goto generic_error;
    if (FAILED(scene->lpVtbl->SetSceneBackgroundImage(scene, tex)))
	goto generic_error;

    RELEASE(mesh);
    RELEASE(frame);
    RELEASE(axis);
    RELEASE(child);
    RELEASE(tex);
    RELEASE(light1);
    RELEASE(light2);

    /* don't release the wrap */
    return TRUE;
generic_error:
    Msg("A failure occurred while building the scene.\n");
ret_with_error:
    RELEASE(mesh);
    RELEASE(frame);
    RELEASE(axis);
    RELEASE(child);
    RELEASE(tex);
    RELEASE(wrap);
    RELEASE(light1);
    RELEASE(light2);
    RELEASE(builder);
    return FALSE;
}

void
OverrideDefaults(Defaults* defaults)
{
    defaults->bConstRenderQuality = TRUE;
    lstrcpy(defaults->Name, "Texture Mapping IV Direct3DRM Example");
}
