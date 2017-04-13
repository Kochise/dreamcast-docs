/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: quat.c
 *
 ***************************************************************************/

/*
 * demonstration of representation of orientation using quaternions
 */

#include "rmdemo.h"

#define PI2 6.28318
#define XPOS 2.0
#define INTERPOLATE_STEP 0.05

static D3DRMQUATERNION q;

static int view_width, view_height;

void ReadMouse(int* buttons, int* x, int* y);

void CDECL
UserControl(LPDIRECT3DRMFRAME frame, void* arg, D3DVALUE delta)
{
    int mx, my, mb;
    LPDIRECT3DRMFRAME scene;
    D3DVALUE angle;
    D3DVECTOR vx = {D3DVAL(1), D3DVAL(0), D3DVAL(0)},
     vy = {D3DVAL(0), D3DVAL(1), D3DVAL(0)};
    D3DRMQUATERNION qx, qy;
    D3DRMMATRIX4D mat;

    arg = arg;

    ReadMouse(&mb, &mx, &my);
    angle = D3DMultiply((-D3DVAL(0.5) + D3DDivide(D3DVAL(my),
                       D3DVAL(view_height))), D3DVAL(PI2));
    D3DRMQuaternionFromRotation(&qx, &vx, angle);
    angle = D3DMultiply((-D3DVAL(0.5) + D3DDivide(D3DVAL(mx),
                       D3DVAL(view_width))), D3DVAL(PI2));
    D3DRMQuaternionFromRotation(&qy, &vy, angle);
    D3DRMQuaternionMultiply(&q, &qx, &qy);
    D3DRMMatrixFromQuaternion(mat, &q);
    frame->lpVtbl->AddTransform(frame, D3DRMCOMBINE_REPLACE, mat);
    frame->lpVtbl->GetScene(frame, &scene);
    frame->lpVtbl->SetPosition(frame, scene, D3DVAL(-XPOS), D3DVAL(0),
                               D3DVAL(0));

    RELEASE(scene);
}

void CDECL
Follow(LPDIRECT3DRMFRAME frame, void* arg, D3DVALUE delta)
{
    LPDIRECT3DRMFRAME scene;
    int mx, my, mb;
    static D3DRMQUATERNION qstart = {D3DVAL(1), {D3DVAL(0), D3DVAL(0),D3DVAL(0)}},
                                 qend;
    static D3DVALUE alpha = D3DVAL(0);

    arg = arg;

    ReadMouse(&mb, &mx, &my);
    if (mb && alpha == D3DVAL(0)) {
	qend = q;
	alpha = D3DVAL(INTERPOLATE_STEP);
    }
    if (alpha > D3DVAL(0)) {
	D3DRMQUATERNION interp;
	D3DRMMATRIX4D mat;

	D3DRMQuaternionSlerp(&interp, &qstart, &qend, alpha);
	D3DRMMatrixFromQuaternion(mat, &interp);

	if (alpha >= D3DVAL(1)) {
	    D3DRMMatrixFromQuaternion(mat, &qend);
	    alpha = D3DVAL(0);
	    qstart = qend;
	} else
	    alpha += D3DVAL(INTERPOLATE_STEP);

	frame->lpVtbl->AddTransform(frame, D3DRMCOMBINE_REPLACE, mat);
	frame->lpVtbl->GetScene(frame, &scene);
	frame->lpVtbl->SetPosition(frame, scene, D3DVAL(XPOS), D3DVAL(0), D3DVAL(0));
	RELEASE(scene);
    }
}

BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
	   LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    D3DRMRENDERQUALITY quality = D3DRMRENDER_FLAT;
    LPDIRECT3DRMFRAME lights = NULL;
    LPDIRECT3DRMFRAME user = NULL;
    LPDIRECT3DRMFRAME follower = NULL;
    LPDIRECT3DRMMESHBUILDER builder = NULL;
    LPDIRECT3DRMMESH mesh = NULL;
    LPDIRECT3DRMLIGHT l1 = NULL;
    LPDIRECT3DRMLIGHT l2 = NULL;
    HRESULT rval;

    if (FAILED(dev->lpVtbl->SetQuality(dev, quality)))
	goto generic_error;

    view_width = view->lpVtbl->GetWidth(view);
    view_height = view->lpVtbl->GetHeight(view);

    /*
     * initialize the lights in the scene
     */
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &lights)))
	goto generic_error;
    if (FAILED(lights->lpVtbl->SetOrientation(lights, scene,
	   D3DVAL(-1), D3DVAL(-1), D3DVAL(0), D3DVAL(0), D3DVAL(1), D3DVAL(0))))
	   goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_DIRECTIONAL, D3DVAL(0.8),
                                  D3DVAL(0.6), D3DVAL(0.7), &l1)))
				  goto generic_error;
    if (FAILED(lights->lpVtbl->AddLight(lights, l1)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_AMBIENT, D3DVAL(0.1),
                                  D3DVAL(0.1), D3DVAL(0.1), &l2)))
				  goto generic_error;
    if (FAILED(scene->lpVtbl->AddLight(scene, l2)))
	goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &builder)))
	goto generic_error;
    rval = builder->lpVtbl->Load(builder, "dropship.x", NULL,
    				D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load dropship.x.\n%s", D3DRMErrorToString(rval));
	goto ret_with_error;
    }
    if (FAILED(builder->lpVtbl->Scale(builder, D3DVAL(0.1),
                                     D3DVAL(0.08), D3DVAL(0.1))))
				     goto generic_error;
    if (FAILED(builder->lpVtbl->CreateMesh(builder, &mesh)))
	goto generic_error;
    RELEASE(builder);

    if (FAILED(camera->lpVtbl->SetPosition(camera, scene, D3DVAL(0), D3DVAL(0), 
                                D3DVAL(-12))))
				goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &user)))
	goto generic_error;
    if (FAILED(user->lpVtbl->AddVisual(user, (LPDIRECT3DRMVISUAL) mesh)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &follower)))
	goto generic_error;
    if (FAILED(follower->lpVtbl->AddVisual(follower, (LPDIRECT3DRMVISUAL) mesh)))
	goto generic_error;

    if (FAILED(follower->lpVtbl->SetPosition(follower, scene, D3DVAL(XPOS), D3DVAL(0),
                                  D3DVAL(0))))
				  goto generic_error;

    if (FAILED(user->lpVtbl->AddMoveCallback(user, UserControl, NULL)))
	goto generic_error;
    if (FAILED(follower->lpVtbl->AddMoveCallback(follower, Follow, NULL)))
	goto generic_error;

    RELEASE(lights);
    RELEASE(user);
    RELEASE(follower);
    RELEASE(mesh);
    RELEASE(l1);
    RELEASE(l2);
    return TRUE;
generic_error:
    Msg("A failure occurred while building the scene.\n");
ret_with_error:
    RELEASE(lights);
    RELEASE(user);
    RELEASE(follower);
    RELEASE(builder);
    RELEASE(mesh);
    RELEASE(l1);
    RELEASE(l2);
    return FALSE;
}

void
OverrideDefaults(Defaults* defaults)
{
    defaults->bNoTextures = TRUE;
    defaults->bConstRenderQuality = TRUE;
    lstrcpy(defaults->Name, "Quaternion Direct3DRM Example");
}
