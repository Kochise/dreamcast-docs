/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: shadow.c
 *
 ***************************************************************************/

#include "rmdemo.h"

BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
	   LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    D3DRMRENDERQUALITY quality = D3DRMRENDER_FLAT;
    LPDIRECT3DRMFRAME lights = NULL;
    LPDIRECT3DRMMESHBUILDER teapot_builder = NULL;
    LPDIRECT3DRMMESH teapot_mesh = NULL;
    LPDIRECT3DRMVISUAL teapot_shadow = NULL;
    LPDIRECT3DRMFRAME teapot = NULL;
    LPDIRECT3DRMLIGHT shadow_light = NULL;
    LPDIRECT3DRMLIGHT l2 = NULL;
    HRESULT rval;

    view = view;		/* not used */

    if (FAILED(dev->lpVtbl->SetQuality(dev, quality)))
	goto generic_error;
    if (FAILED(scene->lpVtbl->SetSceneBackgroundRGB(scene, D3DVAL(1), D3DVAL(1),
                                         D3DVAL(1))))
					 goto generic_error;

    /*
     * initialize the lights in the scene
     */
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &lights)))
	goto generic_error;
    if (FAILED(lights->lpVtbl->SetPosition(lights, scene, D3DVAL(2), D3DVAL(5),
                                -D3DVAL(10))))
				goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_POINT, D3DVAL(0.9),
                                  D3DVAL(0.8), D3DVAL(0.7), &shadow_light)))
				  goto generic_error;
    if (FAILED(lights->lpVtbl->AddLight(lights, shadow_light)))
	goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_AMBIENT, D3DVAL(0.1),
                                  D3DVAL(0.1), D3DVAL(0.1), &l2)))
				  goto generic_error;
    if (FAILED(scene->lpVtbl->AddLight(scene, l2)))
	goto generic_error;

    /*
     * load mesh file
     */
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &teapot_builder)))
	goto generic_error;
    rval = teapot_builder->lpVtbl->Load(teapot_builder, "teapot.x", NULL,
    				D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load teapot.x.\n");
	goto ret_with_error;
    }
    if (FAILED(teapot_builder->lpVtbl->CreateMesh(teapot_builder, &teapot_mesh)))
	goto generic_error;
    RELEASE(teapot_builder);

    /*
     * create a teapot frame within the scene
     */
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &teapot)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateShadow(lpD3DRM, (LPDIRECT3DRMVISUAL) teapot_mesh,
                                shadow_light, D3DVAL(0), D3DVAL(-3), D3DVAL(0), D3DVAL(0), D3DVAL(1),
                                D3DVAL(0), &teapot_shadow)))
				goto generic_error;

    /*
     * add the loaded mesh into the frame
     */
    if (FAILED(teapot->lpVtbl->AddVisual(teapot, (LPDIRECT3DRMVISUAL) teapot_mesh)))
	goto generic_error;
    if (FAILED(teapot->lpVtbl->AddVisual(teapot, teapot_shadow)))
	goto generic_error;

    /*
     * set up the frames position, orientation and rotation
     */

    if (FAILED(camera->lpVtbl->SetPosition(camera, scene, D3DVAL(0), D3DVAL(0), -D3DVAL(10))))
	goto generic_error;
    if (FAILED(camera->lpVtbl->SetOrientation(camera, scene, D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0),
                                   D3DVAL(1), D3DVAL(0))))
				   goto generic_error;
    if (FAILED(teapot->lpVtbl->SetRotation(teapot, scene, D3DVAL(0), D3DVAL(1), D3DVAL(1),
                                D3DVAL(0.02))))
				goto generic_error;

    RELEASE(lights);
    RELEASE(teapot_mesh);
    RELEASE(teapot_shadow);
    RELEASE(teapot);
    RELEASE(shadow_light);
    RELEASE(l2);
    return TRUE;
generic_error:
    Msg("A failure occurred while building the scene.\n");
ret_with_error:
    RELEASE(lights);
    RELEASE(teapot_builder);
    RELEASE(teapot_mesh);
    RELEASE(teapot_shadow);
    RELEASE(teapot);
    RELEASE(shadow_light);
    RELEASE(l2);
    return FALSE;
}

void
OverrideDefaults(Defaults* defaults)
{
    defaults->bNoTextures = TRUE;
    defaults->bConstRenderQuality = TRUE;
    lstrcpy(defaults->Name, "Shadow Direct3DRM Example");
}
