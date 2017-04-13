/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: globe.c
 *
 ***************************************************************************/

#include "rmdemo.h"

D3DRMRENDERQUALITY quality = D3DRMRENDER_GOURAUD;

LPDIRECT3DRMANIMATION anim;
int motion_points = 17;

D3DVECTOR motion[17] =
{{-D3DVAL(14), D3DVAL(4), D3DVAL(45)},
{D3DVAL(9), -D3DVAL(3), D3DVAL(36)},
{D3DVAL(5), D3DVAL(0), D3DVAL(5)},
{-D3DVAL(5), D3DVAL(8), D3DVAL(25)},
{D3DVAL(0), D3DVAL(3), D3DVAL(20)},
{-D3DVAL(3), -D3DVAL(4), D3DVAL(10)},
{D3DVAL(8), D3DVAL(10), D3DVAL(15)},
{D3DVAL(16), D3DVAL(0), D3DVAL(30)},
{D3DVAL(10), -D3DVAL(4), D3DVAL(42)},
{-D3DVAL(15), D3DVAL(0), D3DVAL(37)},
{-D3DVAL(5), -D3DVAL(7), D3DVAL(15)},
{D3DVAL(5), D3DVAL(5), D3DVAL(20)},
{D3DVAL(5), D3DVAL(10), D3DVAL(30)},
{D3DVAL(13), D3DVAL(8), D3DVAL(50)},
{D3DVAL(0), D3DVAL(8), D3DVAL(25)},
{D3DVAL(0), D3DVAL(0), D3DVAL(20)},
{-D3DVAL(14), D3DVAL(4), D3DVAL(45)}
};

static void CDECL cleanupPath(LPDIRECT3DRMOBJECT obj, void* arg)
{
    anim->lpVtbl->Release(anim);
}

static void CDECL moveCamera(LPDIRECT3DRMFRAME frame, void *arg, D3DVALUE delta)
{
    static D3DVALUE t = D3DVAL(0.0);
    LPDIRECT3DRMFRAME world_frame = (LPDIRECT3DRMFRAME) arg;
    LPDIRECT3DRMFRAME scene;

    frame->lpVtbl->GetScene(frame, &scene);

    t += D3DVAL(0.08);
    anim->lpVtbl->SetFrame(anim, frame);
    anim->lpVtbl->SetTime(anim, t);

    frame->lpVtbl->LookAt(frame, world_frame, scene, D3DRMCONSTRAIN_Z);

    scene->lpVtbl->Release(scene);
}

/*
 * world_scene
 */
BOOL
run_world_scene(LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    LPDIRECT3DRMFRAME light1 = NULL;
    LPDIRECT3DRMFRAME world_frame = NULL;
    LPDIRECT3DRMLIGHT l1 = NULL;
    LPDIRECT3DRMLIGHT l2 = NULL;
    LPDIRECT3DRMTEXTURE tex = NULL;
    LPDIRECT3DRMWRAP wrap = NULL;
    LPDIRECT3DRMMESHBUILDER sphere3_builder = NULL;
    LPDIRECT3DRMMATERIAL mat = NULL;
    HRESULT rval;
    D3DRMBOX box;
    D3DVALUE miny, maxy, height;

    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &light1)))
	goto generic_error;
    if (FAILED(light1->lpVtbl->SetPosition(light1, scene, D3DVAL(2), D3DVAL(0.0), D3DVAL(22))))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_DIRECTIONAL, D3DVAL(0.9),
                                  D3DVAL(0.9), D3DVAL(0.9), &l1)))
				  goto generic_error;
    if (FAILED(light1->lpVtbl->AddLight(light1, l1)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_AMBIENT, D3DVAL(0.1),
                                  D3DVAL(0.1), D3DVAL(0.1), &l2)))
				  goto generic_error;
    if (FAILED(scene->lpVtbl->AddLight(scene, l2)))
	goto generic_error;
    if (FAILED(camera->lpVtbl->SetPosition(camera, scene, D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0))))
	goto generic_error;
    if (FAILED(camera->lpVtbl->SetOrientation(camera, scene, D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1), D3DVAL(0.0),
						D3DVAL(1), D3DVAL(0.0))))
						goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &world_frame)))
	goto generic_error;
    if (FAILED(world_frame->lpVtbl->SetPosition(world_frame, scene, D3DVAL(0.0), D3DVAL(0.0), D3DVAL(30))))
	goto generic_error;
    if (FAILED(world_frame->lpVtbl->SetOrientation(world_frame, scene, D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1),
                                        D3DVAL(0.0), D3DVAL(1), D3DVAL(0.0))))
					goto generic_error;
    if (FAILED(world_frame->lpVtbl->SetRotation(world_frame, scene, D3DVAL(0.03), 
                                     D3DVAL(0.1), D3DVAL(0.0), D3DVAL(0.1))))
				     goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &sphere3_builder)))
	goto generic_error;
    rval = sphere3_builder->lpVtbl->Load(sphere3_builder, "sphere3.x",
    					NULL, D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
	Msg("Failed to load sphere3.x.\n%s", D3DRMErrorToString(rval));
	goto ret_with_error;
    }
    if (FAILED(lpD3DRM->lpVtbl->CreateMaterial(lpD3DRM, D3DVAL(20.0), &mat)))
	goto generic_error;
    if (FAILED(sphere3_builder->lpVtbl->SetMaterial(sphere3_builder, mat)))
	goto generic_error;
    mat->lpVtbl->Release(mat); mat = NULL;
    if (FAILED(sphere3_builder->lpVtbl->Scale(sphere3_builder,
    				   D3DVAL(2), D3DVAL(2), D3DVAL(2))))
				   goto generic_error;

    if (FAILED(sphere3_builder->lpVtbl->SetColorRGB(sphere3_builder, D3DVAL(1), D3DVAL(1), D3DVAL(1))))
	goto generic_error;
    if (FAILED(sphere3_builder->lpVtbl->GetBox(sphere3_builder, &box)))
	goto generic_error;
    maxy = box.max.y;
    miny = box.min.y;
    height = maxy - miny;

    if (FAILED(lpD3DRM->lpVtbl->CreateWrap
	(lpD3DRM, D3DRMWRAP_CYLINDER, NULL,
	 D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0),
	 D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
	 D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0),
	 D3DVAL(0.0), D3DDivide(miny, height),
	 D3DVAL(1.0), D3DDivide(-D3DVAL(1.0), height),
	 &wrap
	)))
	goto generic_error;
    if (FAILED(wrap->lpVtbl->Apply(wrap, (LPDIRECT3DRMOBJECT) sphere3_builder)))
	goto generic_error;

    rval = lpD3DRM->lpVtbl->LoadTexture(lpD3DRM, "tex1.ppm", &tex);
    if (rval != D3DRM_OK) {
	Msg("Failed to load tex1.ppm\n%s", D3DRMErrorToString(rval));
	goto ret_with_error;
    }
    if (FAILED(tex->lpVtbl->SetShades(tex, 32)))
	goto generic_error;
    if (FAILED(sphere3_builder->lpVtbl->SetTexture(sphere3_builder, tex)))
	goto generic_error;

    if (FAILED(world_frame->lpVtbl->AddVisual(world_frame, (LPDIRECT3DRMVISUAL) sphere3_builder)))
	goto generic_error;

    if (FAILED(camera->lpVtbl->AddMoveCallback(camera, moveCamera, 
				    (void *) world_frame)))
				    goto generic_error;
    if (FAILED(camera->lpVtbl->AddDestroyCallback(camera, cleanupPath, NULL)))
	goto generic_error;

    RELEASE(light1);
    RELEASE(world_frame);
    RELEASE(sphere3_builder);
    RELEASE(l1);
    RELEASE(l2);
    RELEASE(tex);
    RELEASE(wrap);
    return TRUE;
generic_error:
    Msg("An error occurred while building the scene.\n");
ret_with_error:
    RELEASE(light1);
    RELEASE(world_frame);
    RELEASE(l1);
    RELEASE(l2);
    RELEASE(tex);
    RELEASE(wrap);
    RELEASE(sphere3_builder);
    RELEASE(mat);
    return FALSE;
}

BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
	   LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    int i;

    view = view;		/* not used */

    /*
     * This example flys a camera around a globe. The path taken is
     * defined by a spline curve.
     */


    if (FAILED(dev->lpVtbl->SetQuality(dev, quality)))
	goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateAnimation(lpD3DRM, &anim)))
	goto generic_error;
    if (FAILED(anim->lpVtbl->SetOptions(anim, D3DRMANIMATION_CLOSED | D3DRMANIMATION_LINEARPOSITION | D3DRMANIMATION_POSITION)))
	goto generic_error;
    for (i = 0; i < motion_points; i++) {
        if (FAILED(anim->lpVtbl->AddPositionKey(anim, D3DVAL(i), motion[i].x, motion[i].y,
	                         motion[i].z/2)))
				 goto generic_error;
    }
    if (!run_world_scene(scene, camera))
	goto ret_with_error;
    return TRUE;
generic_error:
    Msg("A failure occurred while building the scene.\n");
ret_with_error:
    return FALSE;
}

void
OverrideDefaults(Defaults* defaults)
{
    lstrcpy(defaults->Name, "Globe Direct3DRM Example");
}
