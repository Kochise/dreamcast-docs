/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: trans.c
 *
 ***************************************************************************/

#include "rmdemo.h"

unsigned char check[] = {
    1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2,
    1, 1, 1, 1, 2, 2, 2, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2,
    1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2,
    1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2,
    1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2,
    1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1,
    2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 3, 3, 2, 1, 0, 0, 1,
    2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1,
    2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1,
    2, 3, 3, 2, 1, 0, 0, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1,
    2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2,
    1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2,
    1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2,
    1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2,
    1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 1, 1, 1, 2, 2, 2, 2,
    1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2,
    2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1,
    2, 2, 2, 2, 1, 1, 1, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1,
    2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1,
    2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1,
    2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1,
    2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2,
    1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 0, 0, 1, 2, 3, 3, 2,
    1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2,
    1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2,
    1, 0, 0, 1, 2, 3, 3, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2,
    1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1,
    2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1,
    2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1,
    2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1,
    2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 2, 2, 2, 1, 1, 1, 1,
    2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1,
    1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2,
    1, 1, 1, 1, 2, 2, 2, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2,
    1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2,
    1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2,
    1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2,
    1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1,
    2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 3, 3, 2, 1, 0, 0, 1,
    2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1,
    2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1, 2, 3, 3, 2, 1, 0, 0, 1,
    2, 3, 3, 2, 1, 0, 0, 1, 2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1,
    2, 2, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1,
};

D3DRMPALETTEENTRY checkPal[] = {
    {0, 0, 0, D3DRMPALETTE_READONLY},
    {127, 255, 127, D3DRMPALETTE_READONLY},
    {0, 0, 255, D3DRMPALETTE_READONLY},
    {255, 255, 127, D3DRMPALETTE_READONLY},
    {255, 255, 255, D3DRMPALETTE_READONLY},
};

D3DRMIMAGE checkImage = {
    32, 32,
    1, 1,
    8, FALSE,
    32,
    check, NULL,
    0xff, 0xff, 0xff, 0xff,
    5, checkPal,
};

static void CDECL mutateTexture(LPDIRECT3DRMFRAME frame, void* arg, D3DVALUE delta)
{
    LPDIRECT3DRMTEXTURE tex = (LPDIRECT3DRMTEXTURE) arg;
    static int col = -1;
    static int delay = 10;
    static int count = 0;
    int i;

    if (--delay)
	return;
    delay = 10;

    if (col >= 0)
	for (i = 0; i < sizeof(check); i++)
	    if (check[i] == 4)
		check[i] = col;

    count++;
    col = count & 3;

    for (i = 0; i < sizeof(check); i++)
	if (check[i] == col)
	    check[i] = 4;

    tex->lpVtbl->Changed(tex, TRUE, FALSE);
}

BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
	   LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    LPDIRECT3DRMFRAME box1 = NULL;
    LPDIRECT3DRMFRAME box2 = NULL;
    LPDIRECT3DRMFRAME sphere = NULL;
    LPDIRECT3DRMFRAME decal = NULL;
    LPDIRECT3DRMFRAME light = NULL;
    LPDIRECT3DRMMESH obj = NULL;
    LPDIRECT3DRMLIGHT dlight = NULL;
    LPDIRECT3DRMLIGHT alight = NULL;
    LPDIRECT3DRMTEXTURE tex = NULL;
    LPDIRECT3DRMMESHBUILDER builder = NULL;
    LPDIRECT3DRMWRAP wrap = NULL;
    LPDIRECT3DRMTEXTURE sphereTex = NULL;
    LPDIRECT3DRMTEXTURE decalTex = NULL;
    LPDIRECT3DRMMATERIAL mat = NULL;
    D3DRMBOX box;
    D3DVALUE miny, maxy;
    D3DVALUE height;
    HRESULT rval;

    view = view;
    dev = dev;
    camera = camera;		/* unused */

    if (FAILED(scene->lpVtbl->SetSceneBackground(scene, D3DRGB(D3DVAL(0.2), D3DVAL(0.2),
                                      D3DVAL(0.2)))))
				      goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &light)))
	goto generic_error;
    if (FAILED(light->lpVtbl->SetPosition(light, scene, D3DVAL(2.0), D3DVAL(3.0),
                               D3DVAL(8.0))))
			       goto generic_error;
    if (FAILED(light->lpVtbl->SetOrientation(light, scene, D3DVAL(-1.0), D3DVAL(-1.0),
                                  D3DVAL(1.0), D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0))))
				  goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_DIRECTIONAL, D3DVAL(1),
                                  D3DVAL(1), D3DVAL(1), &dlight)))
				  goto generic_error;
    if (FAILED(light->lpVtbl->AddLight(light, dlight)))
	goto generic_error;
    RELEASE(dlight);
    RELEASE(light);

    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_AMBIENT, D3DVAL(0.1),
                                  D3DVAL(0.1), D3DVAL(0.1), &alight)))
				  goto generic_error;
    if (FAILED(scene->lpVtbl->AddLight(scene, alight)))
	goto generic_error;
    RELEASE(alight);

    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &box1)))
	goto generic_error;
    if (FAILED(box1->lpVtbl->SetRotation(box1, scene, D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
			      D3DVAL(-0.02))))
			      goto generic_error;
    if (FAILED(box1->lpVtbl->SetPosition(box1, scene, D3DVAL(2.0), D3DVAL(0.0), D3DVAL(7.0))))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &builder)))
	goto generic_error;
    rval = builder->lpVtbl->Load(builder, "ncube.x", NULL,
    			D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load ncube.x.\n");
	goto ret_with_error;
    }
    if (FAILED(builder->lpVtbl->SetPerspective(builder, TRUE)))
	goto generic_error;
    if (FAILED(builder->lpVtbl->CreateMesh(builder, &obj)))
	goto generic_error;
    RELEASE(builder);
    if (FAILED(lpD3DRM->lpVtbl->CreateTexture(lpD3DRM, &checkImage, &tex)))
	goto generic_error;
    if (FAILED(obj->lpVtbl->SetGroupTexture(obj, D3DRMGROUP_ALLGROUPS, tex)))
	goto generic_error;
    if (FAILED(obj->lpVtbl->SetGroupMapping(obj, D3DRMGROUP_ALLGROUPS, D3DRMMAP_PERSPCORRECT)))
	goto generic_error;
    if (FAILED(box1->lpVtbl->AddVisual(box1, (LPDIRECT3DRMVISUAL) obj)))
	goto generic_error;
    if (FAILED(box1->lpVtbl->AddMoveCallback(box1, mutateTexture, tex)))
	goto generic_error;
    RELEASE(obj);
    RELEASE(tex);

    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &box2)))
	goto generic_error;
    if (FAILED(box2->lpVtbl->SetRotation(box2, scene, D3DVAL(0.1), D3DVAL(1.0), D3DVAL(0.0),
                              D3DVAL(0.1))))
			      goto generic_error;
    if (FAILED(box2->lpVtbl->SetPosition(box2, box1, D3DVAL(-4.0), D3DVAL(0.0), D3DVAL(0.0))))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &builder)))
	goto generic_error;
    rval = builder->lpVtbl->Load(builder, "ncube.x", NULL,
    			D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load ncube.x.\n");
	goto ret_with_error;
    }
    //builder->lpVtbl->Scale(builder, D3DVAL(2.0), D3DVAL(2.0), D3DVAL(2.0));
    if (FAILED(builder->lpVtbl->SetPerspective(builder, TRUE)))
	goto generic_error;
    if (FAILED(builder->lpVtbl->CreateMesh(builder, &obj)))
	goto generic_error;
    RELEASE(builder);
    rval = lpD3DRM->lpVtbl->LoadTexture(lpD3DRM, "checker.ppm", &tex);
    if (rval != D3DRM_OK) {
	Msg("Failed to load checker.ppm.\n");
	goto ret_with_error;
    }
    if (FAILED(tex->lpVtbl->SetDecalTransparency(tex, TRUE)))
	goto generic_error;

    if (FAILED(obj->lpVtbl->SetGroupTexture(obj, D3DRMGROUP_ALLGROUPS, tex)))
	goto generic_error;
    if (FAILED(obj->lpVtbl->SetGroupMapping(obj, D3DRMGROUP_ALLGROUPS, D3DRMMAP_PERSPCORRECT)))
	goto generic_error;
    if (FAILED(box2->lpVtbl->AddVisual(box2, (LPDIRECT3DRMVISUAL) obj)))
	goto generic_error;
    RELEASE(obj);
    RELEASE(tex);
    RELEASE(box2);

    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &builder)))
	goto generic_error;
    rval = builder->lpVtbl->Load(builder, "sphere3.x", NULL,
    			D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load sphere3.x.\n");
	goto ret_with_error;
    }
    if (FAILED(builder->lpVtbl->CreateMesh(builder, &obj)))
	goto generic_error;
    RELEASE(builder);
    if (FAILED(obj->lpVtbl->GetBox(obj, &box)))
	goto generic_error;
    maxy = box.max.y;
    miny = box.min.y;
    height = maxy - miny;

    if (FAILED(lpD3DRM->lpVtbl->CreateWrap(lpD3DRM, D3DRMWRAP_CYLINDER, NULL,
			      D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0),
			      D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
			      D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0),
			      D3DVAL(0.0), D3DDivide(miny, height),
		              D3DVAL(1.0), D3DDivide(D3DVAL(-1.0),height),
		              &wrap)))
			      goto generic_error;
    if (FAILED(wrap->lpVtbl->Apply(wrap, (LPDIRECT3DRMOBJECT) obj)))
	goto generic_error;
    RELEASE(wrap);

    rval = lpD3DRM->lpVtbl->LoadTexture(lpD3DRM, "tex3.ppm", &sphereTex);
    if (rval != D3DRM_OK) {
	Msg("Failed to load tex3.ppm.\n");
	goto ret_with_error;
    }
    if (FAILED(sphereTex->lpVtbl->SetColors(sphereTex, 16)))
	goto generic_error;
    if (FAILED(obj->lpVtbl->SetGroupTexture(obj, D3DRMGROUP_ALLGROUPS, sphereTex)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateMaterial(lpD3DRM, D3DVAL(16.0), &mat)))
	goto generic_error;
    if (FAILED(obj->lpVtbl->SetGroupMaterial(obj, D3DRMGROUP_ALLGROUPS, mat)))
	goto generic_error;
    RELEASE(sphereTex);
    RELEASE(mat);

    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &sphere)))
	goto generic_error;
    if (FAILED(sphere->lpVtbl->AddVisual(sphere, (LPDIRECT3DRMVISUAL) obj)))
	goto generic_error;
    RELEASE(obj);
    if (FAILED(sphere->lpVtbl->SetPosition(sphere, scene, D3DVAL(0.0), D3DVAL(0.0), D3DVAL(8.0))))
	goto generic_error;
    if (FAILED(sphere->lpVtbl->SetRotation(sphere, scene, D3DVAL(-0.1), D3DVAL(1.0),
	                        D3DVAL(0.0), D3DVAL(0.02))))
				goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, sphere, &decal)))
	goto generic_error;

    rval = lpD3DRM->lpVtbl->LoadTexture(lpD3DRM, "checker.ppm", &decalTex);
    if (rval != D3DRM_OK) {
	Msg("Failed to load checker.ppm.\n");
	goto ret_with_error;
    }
    if (FAILED(decalTex->lpVtbl->SetDecalScale(decalTex, TRUE)))
	goto generic_error;
    if (FAILED(decalTex->lpVtbl->SetDecalSize(decalTex, D3DVAL(2.0), D3DVAL(2.0))))
	goto generic_error;
    if (FAILED(decalTex->lpVtbl->SetDecalOrigin(decalTex, 4, 4)))
	goto generic_error;
    if (FAILED(decalTex->lpVtbl->SetDecalTransparency(decalTex, TRUE)))
	goto generic_error;
    if (FAILED(decal->lpVtbl->SetPosition(decal, sphere, D3DVAL(0.0), D3DVAL(0.0), D3DVAL(2.0))))
	goto generic_error;
    if (FAILED(decal->lpVtbl->AddVisual(decal, (LPDIRECT3DRMVISUAL) decalTex)))
	goto generic_error;
    RELEASE(decalTex);

    RELEASE(box1);
    RELEASE(decal);
    RELEASE(sphere);
    return TRUE;
generic_error:
    Msg("A failure occurred while building the scene.\n");
ret_with_error:
    RELEASE(box1);
    RELEASE(box2);
    RELEASE(sphere);
    RELEASE(decal);
    RELEASE(light);
    RELEASE(obj);
    RELEASE(dlight);
    RELEASE(alight);
    RELEASE(tex);
    RELEASE(builder);
    RELEASE(wrap);
    RELEASE(sphereTex);
    RELEASE(decalTex);
    RELEASE(mat);
    return FALSE;
}

void
OverrideDefaults(Defaults* defaults)
{
    defaults->bConstRenderQuality = TRUE;
    lstrcpy(defaults->Name, "Transparency Direct3DRM Example");
}
