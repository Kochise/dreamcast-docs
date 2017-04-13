/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: hier1.c
 *
 ***************************************************************************/

/*
 * RL Tutorial program 2 frame hierarchy
 */

#include "rmdemo.h"

BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
	   LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    D3DRMRENDERQUALITY quality = D3DRMRENDER_FLAT;
    LPDIRECT3DRMFRAME lights = NULL;
    LPDIRECT3DRMFRAME axis = NULL;
    LPDIRECT3DRMMESH torus_mesh = NULL;
    LPDIRECT3DRMMESH sphere_mesh = NULL;
    LPDIRECT3DRMFRAME torus = NULL;
    LPDIRECT3DRMFRAME sphere = NULL;
    LPDIRECT3DRMLIGHT lp = NULL;
    LPDIRECT3DRMLIGHT la = NULL;
    LPDIRECT3DRMMESHBUILDER builder = NULL;
    HRESULT rval;

    view = view;		/* not used */

    /*
     * This Demo shows a simple hierarchy of frames
     */

    if (FAILED(dev->lpVtbl->SetQuality(dev, quality)))
	goto generic_error;

    /*
     * initialize the lights in the scene
     */
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &lights)))
	goto generic_error;
    if (FAILED(lights->lpVtbl->SetPosition(lights, scene, D3DVAL(5), D3DVAL(5), 
                                -D3DVAL(9))))
				goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_POINT, D3DVAL(0.9), 
                                  D3DVAL(0.8), D3DVAL(0.7), &lp)))
				  goto generic_error;
    if (FAILED(lights->lpVtbl->AddLight(lights, lp)))
	goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_AMBIENT, D3DVAL(0.1), 
                                  D3DVAL(0.1), D3DVAL(0.1), &la)))
				  goto generic_error;
    if (FAILED(scene->lpVtbl->AddLight(scene, la)))
	goto generic_error;


    /*
     * load mesh files
     */
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &builder)))
	goto generic_error;
    rval = builder->lpVtbl->Load(builder, "torus.x", NULL,
    			D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load torus.x\n%s", D3DRMErrorToString(rval));
	goto ret_with_error;
    }
    if (FAILED(builder->lpVtbl->CreateMesh(builder, &torus_mesh)))
	goto generic_error;
    RELEASE(builder);

    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &builder)))
	goto generic_error;
    rval = builder->lpVtbl->Load(builder, "sphere2.x", NULL,
    				D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load sphere2.x\n%s", D3DRMErrorToString(rval));
	goto ret_with_error;
    }
    if (FAILED(builder->lpVtbl->CreateMesh(builder, &sphere_mesh)))
	goto generic_error;
    RELEASE(builder);

    if (FAILED(torus_mesh->lpVtbl->SetGroupColorRGB(torus_mesh, -1, D3DVAL(0.0), 
                                            D3DVAL(0.0), D3DVAL(1.0))))
					    goto generic_error;

    /*
     * create a torus frame within the scene create axis frame within
     * frame of sphere create torus frame within frame of axis
     */
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &sphere)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, sphere, &axis)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, axis, &torus)))
	goto generic_error;

    {
	/*
	 * load a texture and wrap it onto the sphere
	 */
	LPDIRECT3DRMTEXTURE tex;
	LPDIRECT3DRMWRAP wrap;
	D3DVALUE height;

	D3DRMBOX box;
	D3DVALUE miny, maxy;
	if (FAILED(sphere_mesh->lpVtbl->GetBox(sphere_mesh, &box)))
	    goto generic_error;
	maxy = box.max.y;
	miny = box.min.y;
	height = maxy - miny;

	if (FAILED(lpD3DRM->lpVtbl->CreateWrap(lpD3DRM, D3DRMWRAP_CYLINDER, NULL, D3DVAL(0.0),
	                          D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0),
	                          D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
	                          D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0),
	                          D3DDivide(maxy, height), D3DVAL(1.0),
	                          D3DDivide(D3DVAL(1), height), &wrap)))
				  goto generic_error;
	if (FAILED(wrap->lpVtbl->Apply(wrap, (LPDIRECT3DRMOBJECT)sphere_mesh)))
	    goto generic_error;
	RELEASE(wrap);

	rval = lpD3DRM->lpVtbl->LoadTexture(lpD3DRM, "tex2.ppm", &tex);
	if (rval != D3DRM_OK) {
            Msg("Failed to load tex2.ppm\n%s", D3DRMErrorToString(rval));
	    goto ret_with_error;
	}
	if (FAILED(tex->lpVtbl->SetColors(tex, 16)))
	    goto generic_error;
	if (FAILED(tex->lpVtbl->SetShades(tex, 8)))
	    goto generic_error;
	if (FAILED(sphere_mesh->lpVtbl->SetGroupTexture(sphere_mesh, -1, tex)))
	    goto generic_error;
	RELEASE(tex);
    }
    /*
     * add the loaded mesh into the frame
     */
    if (FAILED(torus->lpVtbl->AddVisual(torus, (LPDIRECT3DRMVISUAL) torus_mesh)))
	goto generic_error;
    if (FAILED(sphere->lpVtbl->AddVisual(sphere, (LPDIRECT3DRMVISUAL) sphere_mesh)))
	goto generic_error;

    /*
     * set up the frames position, orientation and rotation
     */
    if (FAILED(camera->lpVtbl->SetPosition(camera, scene, D3DVAL(0), D3DVAL(0), -D3DVAL(10))))
	goto generic_error;
    if (FAILED(sphere->lpVtbl->SetPosition(sphere, scene, D3DVAL(0), D3DVAL(0), D3DVAL(0))))
	goto generic_error;
    if (FAILED(axis->lpVtbl->SetPosition(axis, sphere, D3DVAL(2), D3DVAL(0), D3DVAL(0))))
	goto generic_error;
    if (FAILED(torus->lpVtbl->SetPosition(torus, axis, D3DVAL(1.0), D3DVAL(0), D3DVAL(0))))
	goto generic_error;

    if (FAILED(sphere->lpVtbl->SetRotation(sphere, scene, D3DVAL(0), D3DVAL(1.0), D3DVAL(0.5),D3DVAL(0.05))))
	goto generic_error;
    if (FAILED(axis->lpVtbl->SetRotation(axis, sphere, D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(0.01))))
	goto generic_error;
    if (FAILED(torus->lpVtbl->SetRotation(torus, axis, D3DVAL(0), D3DVAL(0), D3DVAL(1), -D3DVAL(0.05))))
	goto generic_error;

    RELEASE(lights);
    RELEASE(axis);
    RELEASE(torus_mesh);
    RELEASE(sphere_mesh);
    RELEASE(torus);
    RELEASE(sphere);
    RELEASE(lp);
    RELEASE(la);
    return TRUE;
generic_error:
    Msg("A failure occurred while building the scene.\n");
ret_with_error:
    RELEASE(lights);
    RELEASE(axis);
    RELEASE(torus_mesh);
    RELEASE(sphere_mesh);
    RELEASE(torus);
    RELEASE(sphere);
    RELEASE(lp);
    RELEASE(la);
    RELEASE(builder);
    return FALSE;
}

void
OverrideDefaults(Defaults* defaults)
{
    defaults->bConstRenderQuality = TRUE;
    lstrcpy(defaults->Name, "Frame Hierarchy D3D RM Example");
}
