/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: hier2.c
 *
 ***************************************************************************/

/*
 * D3D RM Tutorial program frame hierarchy 2
 */

#include "rmdemo.h"

BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
	   LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    D3DRMRENDERQUALITY quality = D3DRMRENDER_FLAT;
    LPDIRECT3DRMLIGHT l1 = NULL;
    LPDIRECT3DRMLIGHT l2 = NULL;
    LPDIRECT3DRMFRAME lights = NULL;
    LPDIRECT3DRMMESHBUILDER torus_builder = NULL;
    LPDIRECT3DRMMESHBUILDER sphere_builder = NULL;
    LPDIRECT3DRMMESHBUILDER cube1_builder = NULL;
    LPDIRECT3DRMMESHBUILDER cube2_builder = NULL;
    LPDIRECT3DRMMESH cube1_mesh = NULL;
    LPDIRECT3DRMMESH cube2_mesh = NULL;
    LPDIRECT3DRMMESH torus_mesh = NULL;
    LPDIRECT3DRMMESH sphere_mesh = NULL;
    LPDIRECT3DRMFRAME torus = NULL;
    LPDIRECT3DRMFRAME sphere = NULL;
    LPDIRECT3DRMFRAME cube1 = NULL;
    LPDIRECT3DRMFRAME cube2 = NULL;
    HRESULT rval;
    view = view;		/* not used */

    /*
     * This Demo shows a more complex hierarchy of frames
     */

    if (FAILED(dev->lpVtbl->SetQuality(dev, quality)))
	goto generic_error;
    if (FAILED(dev->lpVtbl->SetShades(dev, 16)))
	goto generic_error;

    /*
     * initialize the lights in the scene
     */

    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &lights)))
	goto generic_error;
    if (FAILED(lights->lpVtbl->SetPosition(lights, scene, D3DVAL(5), D3DVAL(5),
                                -D3DVAL(5))))
				goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_POINT, D3DVAL(0.9),
                                  D3DVAL(0.8), D3DVAL(0.7), &l1)))
				  goto generic_error;
    if (FAILED(lights->lpVtbl->AddLight(lights, l1)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_AMBIENT, D3DVAL(0.1),
                                  D3DVAL(0.1), D3DVAL(0.1), &l2)))
				  goto generic_error;
    if (FAILED(scene->lpVtbl->AddLight(scene, l2)))
	goto generic_error;
    /*
     * load mesh files
     */
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &torus_builder)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &sphere_builder)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &cube1_builder)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &cube2_builder)))
	goto generic_error;
    rval = torus_builder->lpVtbl->Load(torus_builder, "torus.x", NULL,
    				D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load torus.x.\n");
	goto ret_with_error;
    }
    rval = sphere_builder->lpVtbl->Load(sphere_builder, "sphere4.x", NULL,
    				D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load sphere4.x.\n");
	goto ret_with_error;
    }
    rval = cube1_builder->lpVtbl->Load(cube1_builder, "cube.x", NULL,
    				D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load cube.x.\n");
	goto ret_with_error;
    }
    rval = cube2_builder->lpVtbl->Load(cube2_builder, "cube.x", NULL,
    				D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load cube.x.\n");
	goto ret_with_error;
    }

    if (FAILED(cube1_builder->lpVtbl->Scale(cube1_builder, D3DVAL(0.25), D3DVAL(0.5),
                                 D3DVAL(1.0))))
				 goto generic_error;
    if (FAILED(cube2_builder->lpVtbl->Scale(cube2_builder, D3DVAL(0.5), D3DVAL(1.5),
                                 D3DVAL(1.0))))
				 goto generic_error;

    if (FAILED(cube1_builder->lpVtbl->SetColorRGB(cube1_builder, D3DVAL(0.7), 
                                        D3DVAL(0.0), D3DVAL(0.8))))
					goto generic_error;
    if (FAILED(cube2_builder->lpVtbl->SetColorRGB(cube2_builder, D3DVAL(0.0),
                                        D3DVAL(1.0), D3DVAL(0.5))))
					goto generic_error;
    if (FAILED(torus_builder->lpVtbl->SetColorRGB(torus_builder, D3DVAL(0.2),
                                        D3DVAL(1.0), D3DVAL(0.8))))
					goto generic_error;

    if (FAILED(torus_builder->lpVtbl->CreateMesh(torus_builder, &torus_mesh)))
	goto generic_error;
    if (FAILED(sphere_builder->lpVtbl->CreateMesh(sphere_builder, &sphere_mesh)))
	goto generic_error;
    if (FAILED(cube1_builder->lpVtbl->CreateMesh(cube1_builder, &cube1_mesh)))
	goto generic_error;
    if (FAILED(cube2_builder->lpVtbl->CreateMesh(cube2_builder, &cube2_mesh)))
	goto generic_error;
    RELEASE(torus_builder);
    RELEASE(sphere_builder);
    RELEASE(cube1_builder);
    RELEASE(cube2_builder);

    /*
     * create a torus frame within the scene create torus frame within
     * frame of sphere cube frame within frame of torus
     */

    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &sphere)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, sphere, &torus)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, torus, &cube1)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, torus, &cube2)))
	goto generic_error;

    /*
     * add the loaded mesh into the frame
     */

    if (FAILED(torus->lpVtbl->AddVisual(torus, (LPDIRECT3DRMVISUAL) torus_mesh)))
	goto generic_error;
    if (FAILED(sphere->lpVtbl->AddVisual(sphere, (LPDIRECT3DRMVISUAL) sphere_mesh)))
	goto generic_error;
    if (FAILED(cube1->lpVtbl->AddVisual(cube1, (LPDIRECT3DRMVISUAL) cube1_mesh)))
	goto generic_error;
    if (FAILED(cube2->lpVtbl->AddVisual(cube2, (LPDIRECT3DRMVISUAL) cube2_mesh)))
	goto generic_error;

    /*
     * set up the frames position, orientation and rotations
     */

    if (FAILED(camera->lpVtbl->SetPosition(camera, scene, D3DVAL(0), D3DVAL(0), -D3DVAL(25))))
	goto generic_error;
    if (FAILED(sphere->lpVtbl->SetPosition(sphere, scene, D3DVAL(0), D3DVAL(0), D3DVAL(0))))
	goto generic_error;
    if (FAILED(torus->lpVtbl->SetPosition(torus, sphere, D3DVAL(6), D3DVAL(0), D3DVAL(0))))
	goto generic_error;
    if (FAILED(cube1->lpVtbl->SetPosition(cube1, torus, D3DVAL(0), D3DVAL(4), D3DVAL(0))))
	goto generic_error;
    if (FAILED(cube2->lpVtbl->SetPosition(cube2, torus, D3DVAL(0), -D3DVAL(4), D3DVAL(0))))
	goto generic_error;

    if (FAILED(sphere->lpVtbl->SetRotation(sphere, scene, D3DVAL(0), D3DVAL(0), D3DVAL(1),D3DVAL(0.01))))
	goto generic_error;
    if (FAILED(torus->lpVtbl->SetRotation(torus, sphere, D3DVAL(1), D3DVAL(0), D3DVAL(0), D3DVAL(0.02))))
	goto generic_error;
    if (FAILED(cube1->lpVtbl->SetRotation(cube1, torus, D3DVAL(0.1), D3DVAL(0.2),
                               D3DVAL(0.7), D3DVAL(0.03))))
			       goto generic_error;
    if (FAILED(cube2->lpVtbl->SetRotation(cube2, torus, D3DVAL(0.7), D3DVAL(0.1),
                               D3DVAL(0.2), D3DVAL(0.03))))
			       goto generic_error;

    RELEASE(lights);
    RELEASE(torus_mesh);
    RELEASE(sphere_mesh);
    RELEASE(cube1_mesh);
    RELEASE(cube2_mesh);
    RELEASE(torus);
    RELEASE(sphere);
    RELEASE(cube1);
    RELEASE(cube2);
    RELEASE(l1);
    RELEASE(l2);
    return TRUE;
generic_error:
    Msg("A failure occurred while building the scene.\n");
ret_with_error:
    RELEASE(l1);
    RELEASE(l2);
    RELEASE(lights);
    RELEASE(torus_builder);
    RELEASE(sphere_builder);
    RELEASE(cube1_builder);
    RELEASE(cube2_builder);
    RELEASE(cube1_mesh);
    RELEASE(cube2_mesh);
    RELEASE(torus_mesh);
    RELEASE(sphere_mesh);
    RELEASE(torus);
    RELEASE(sphere);
    RELEASE(cube1);
    RELEASE(cube2);
    return FALSE;
}

void
OverrideDefaults(Defaults* defaults)
{
    defaults->bNoTextures = TRUE;
    defaults->bConstRenderQuality = TRUE;
    lstrcpy(defaults->Name, "Frame Hierarchy II D3D RM Example");
}
