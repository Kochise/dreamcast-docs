/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: tex5.c
 *
 ***************************************************************************/

/*
 * A texture mapping example showing the use of chrome mapping and decals.
 */

#include "rmdemo.h"

void CDECL 
applyWrap(LPDIRECT3DRMFRAME frame, void* arg, D3DVALUE delta)
{
    LPDIRECT3DRMWRAP wrap = (LPDIRECT3DRMWRAP) arg;
    LPDIRECT3DRMVISUALARRAY visuals;
    LPDIRECT3DRMVISUAL v;
    int count, i;

    frame->lpVtbl->GetVisuals(frame, &visuals);
    if (visuals) {
	count = visuals->lpVtbl->GetSize(visuals);

	for (i = 0; i < count; i++) {
	    visuals->lpVtbl->GetElement(visuals, i, &v);
	    wrap->lpVtbl->ApplyRelative(wrap, frame, (LPDIRECT3DRMOBJECT) v);
	    v->lpVtbl->Release(v);
	}

	visuals->lpVtbl->Release(visuals);
    }
}

void CDECL 
toggleDecalScale(LPDIRECT3DRMFRAME frame, void* arg, D3DVALUE delta)
{
    LPDIRECT3DRMTEXTURE decal = (LPDIRECT3DRMTEXTURE) arg;
    static int i = 0;

    i++;
    if (i == 20) {
	int scale;

	i = 0;

	scale = decal->lpVtbl->GetDecalScale(decal);
	decal->lpVtbl->SetDecalScale(decal, !scale);
    }
}

void CDECL 
cleanupWrap(LPDIRECT3DRMOBJECT obj, void* arg)
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
    LPDIRECT3DRMFRAME orbit = NULL;
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
    if (FAILED(frame->lpVtbl->SetOrientation(frame, scene, D3DVAL(0), D3DVAL(1.0), D3DVAL(0),
    					D3DVAL(0), D3DVAL(0), D3DVAL(1))))
					goto generic_error;
    if (FAILED(frame->lpVtbl->SetRotation(frame, scene, D3DVAL(0), D3DVAL(0.9), D3DVAL(1.0),
                               D3DVAL(0.04))))
			       goto generic_error;

    rval = lpD3DRM->lpVtbl->LoadTexture(lpD3DRM, "lake.ppm", &tex);
    if (rval != D3DRM_OK) {
	Msg("Failed to load lake.ppm.\n");
	goto ret_with_error;
    }
    if (FAILED(tex->lpVtbl->SetColors(tex, 256)))
	goto generic_error;
    if (FAILED(tex->lpVtbl->SetShades(tex, 1)))
	goto generic_error;
    if (FAILED(tex->lpVtbl->SetDecalScale(tex, TRUE)))
	goto generic_error;
    if (FAILED(tex->lpVtbl->SetDecalOrigin(tex, 128, 128)))
	goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &builder)))
	goto generic_error;
    rval = builder->lpVtbl->Load(builder, "torus.x", NULL,
    			D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load torus.x.\n");
	goto ret_with_error;
    }
    if (FAILED(builder->lpVtbl->SetTexture(builder, tex)))
	goto generic_error;
    if (FAILED(builder->lpVtbl->SetQuality(builder, D3DRMRENDER_GOURAUD)))
	goto generic_error;
    if (FAILED(builder->lpVtbl->CreateMesh(builder, &mesh)))
	goto generic_error;
    RELEASE(builder);
    
    
    if (FAILED(mesh->lpVtbl->SetGroupColorRGB(mesh, 0, D3DVAL(0.7), D3DVAL(0.3), D3DVAL(0.3))))
	goto generic_error;
    if (FAILED(mesh->lpVtbl->SetGroupColorRGB(mesh, 1, D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0))))
	goto generic_error;

    if (FAILED(frame->lpVtbl->AddVisual(frame, (LPDIRECT3DRMVISUAL) mesh)))
	goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateWrap
	(lpD3DRM, D3DRMWRAP_CHROME, camera,
	 D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0),
	 D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
	 D3DVAL(0.0), D3DVAL(0.0), -D3DVAL(1.0),
	 D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0),
	 -D3DVAL(1.0), &wrap)))
	 goto generic_error;

    if (FAILED(frame->lpVtbl->AddMoveCallback(frame, applyWrap, (void *) wrap)))
	goto generic_error;
    if (FAILED(frame->lpVtbl->AddDestroyCallback(frame, cleanupWrap, wrap)))
	goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, frame, &axis)))
	goto generic_error;
    if (FAILED(axis->lpVtbl->SetRotation(axis, frame, D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(0.04))))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, axis, &orbit)))
	goto generic_error;
    if (FAILED(orbit->lpVtbl->SetPosition(orbit, axis, D3DVAL(2.6), D3DVAL(0), D3DVAL(0))))
	goto generic_error;
    if (FAILED(orbit->lpVtbl->AddVisual(orbit, (LPDIRECT3DRMVISUAL) tex)))
	goto generic_error;
    //orbit->lpVtbl->AddMoveCallback(orbit, toggleDecalScale, (void*) tex);
    if (FAILED(scene->lpVtbl->SetSceneBackgroundImage(scene, tex)))
	goto generic_error;

    RELEASE(mesh);
    RELEASE(frame);
    RELEASE(axis);
    RELEASE(orbit);
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
    RELEASE(orbit);
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
    lstrcpy(defaults->Name, "Texture Mapping V Direct3DRM Example");
}
