/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: egg.c
 *
 ***************************************************************************/

#include "rmdemo.h"

BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
	   LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    LPDIRECT3DRMFRAME lights = NULL;
    LPDIRECT3DRMMESHBUILDER egg_builder = NULL;
    LPDIRECT3DRMFRAME egg = NULL;
    LPDIRECT3DRMLIGHT light1 = NULL;
    LPDIRECT3DRMLIGHT light2 = NULL;
    HRESULT rval;

    view = view;		/* not used */

    /*
     * initialize the lights in the scene
     */
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &lights)))
	goto generic_error;
    if (FAILED(lights->lpVtbl->SetPosition(lights, scene, D3DVAL(5), D3DVAL(5),
                                -D3DVAL(1))))
				goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_DIRECTIONAL, D3DVAL(0.9),
                                  D3DVAL(0.8), D3DVAL(0.7), &light1)))
				  goto generic_error;
    if (FAILED(lights->lpVtbl->AddLight(lights, light1)))
	    goto generic_error;
    if (FAILED(lights->lpVtbl->SetRotation(lights, scene, D3DVAL(0), D3DVAL(1), D3DVAL(1),
                                D3DVAL(-0.02))))
				goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_AMBIENT, D3DVAL(0.1),
                                  D3DVAL(0.1), D3DVAL(0.1), &light2)))
				  goto generic_error;
    if (FAILED(scene->lpVtbl->AddLight(scene, light2)))
	goto generic_error;

    /*
     * load mesh file
     */
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &egg_builder)))
	goto generic_error;
    rval = egg_builder->lpVtbl->Load(egg_builder, "egg.x", NULL,
    				D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load egg.x\n%s", D3DRMErrorToString(rval));
	goto ret_with_error;
    }

    /*
     * create an egg frame within the scene
     */
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &egg)))
	goto generic_error;

    /*
     * add the loaded mesh into the frame
     */
    if (FAILED(egg->lpVtbl->AddVisual(egg, (LPDIRECT3DRMVISUAL)egg_builder)))
	goto generic_error;

    /*
     * set up the frames position, orientation and rotation
     */
    if (FAILED(camera->lpVtbl->SetPosition(camera, scene, D3DVAL(0), D3DVAL(0), -D3DVAL(10))))
	goto generic_error;
    if (FAILED(camera->lpVtbl->SetOrientation(camera, scene, D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0),
                                   D3DVAL(1), D3DVAL(0))))
				   goto generic_error;
    if (FAILED(egg->lpVtbl->SetRotation(egg, scene, D3DVAL(0), D3DVAL(1), D3DVAL(1),
                             D3DVAL(0.02))))
			     goto generic_error;

    RELEASE(egg);
    RELEASE(lights);
    RELEASE(egg_builder);
    RELEASE(light1);
    RELEASE(light2);
    return TRUE;

generic_error:
    Msg("A failure occured while building the scene.\n");
ret_with_error:
    RELEASE(egg);
    RELEASE(lights);
    RELEASE(egg_builder);
    RELEASE(light1);
    RELEASE(light2);
    return FALSE;
}

void
OverrideDefaults(Defaults *defaults)
{
    defaults->bNoTextures = TRUE;
    lstrcpy(defaults->Name, "Egg Direct3DRM Example");
}
