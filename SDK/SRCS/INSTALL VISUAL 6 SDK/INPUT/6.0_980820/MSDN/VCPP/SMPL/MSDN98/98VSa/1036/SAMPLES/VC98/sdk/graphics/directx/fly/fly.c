/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: fly.c
 *
 ***************************************************************************/

/*
 * landscape fly by
 */

#include <math.h>
#include <stdlib.h>
#include "rmdemo.h"

typedef struct PATHINFO {
    D3DVALUE t;
    LPDIRECT3DRMFRAME chase;
    LPDIRECT3DRMFRAME plane_frame;
    LPDIRECT3DRMANIMATION flight_path;
} pathInfo;

#define NUM_SMOKE 7
int smoke_num = 0;
int done_all = 0;

LPDIRECT3DRMFRAME smoke[NUM_SMOKE];

static void CDECL cleanupObjects(LPDIRECT3DRMOBJECT obj, void* arg)
{
    pathInfo *info = (pathInfo*) arg;
    int i;

    for (i = 0; i < NUM_SMOKE; i++)
	smoke[i]->lpVtbl->Release(smoke[i]);
    info->chase->lpVtbl->Release(info->chase);
    info->plane_frame->lpVtbl->Release(info->plane_frame);
    info->flight_path->lpVtbl->Release(info->flight_path);
}

static void CDECL moveCamera(LPDIRECT3DRMFRAME camera, void *arg, D3DVALUE delta)
{
    D3DVECTOR dir, up;
    D3DVECTOR dirCam, upCam;
    struct PATHINFO *info;
    LPDIRECT3DRMFRAME scene;
    D3DVALUE a_bit;

    info = (struct PATHINFO *) arg;
    camera->lpVtbl->GetScene(camera, &scene);
    info->t += D3DVAL(0.04);
    info->flight_path->lpVtbl->SetFrame(info->flight_path, camera);
    info->flight_path->lpVtbl->SetTime(info->flight_path, info->t);

    info->flight_path->lpVtbl->SetFrame(info->flight_path, info->plane_frame);
    info->flight_path->lpVtbl->SetTime(info->flight_path, info->t + D3DVAL(0.5));

    info->flight_path->lpVtbl->SetFrame(info->flight_path, info->chase);
    info->flight_path->lpVtbl->SetTime(info->flight_path, info->t + D3DVAL(1.0));

    camera->lpVtbl->LookAt(camera, info->plane_frame, scene, D3DRMCONSTRAIN_Z);
    info->plane_frame->lpVtbl->LookAt(info->plane_frame, info->chase,scene,
                                      D3DRMCONSTRAIN_Y);
    camera->lpVtbl->GetOrientation(camera, scene, &dirCam, &upCam);
    info->plane_frame->lpVtbl->GetOrientation(info->plane_frame, scene,
                                              &dir, &up);
    up.x = dir.x - dirCam.x;
    up.y = dir.y - dirCam.y + D3DVAL(1.0);
    up.z = dir.z - dirCam.z;
                
    info->plane_frame->lpVtbl->SetOrientation(info->plane_frame, scene,
					      dir.x, dir.y, dir.z,
					      up.x, up.y, up.z);

    if (done_all < NUM_SMOKE) {
	scene->lpVtbl->AddVisual(scene, (LPDIRECT3DRMVISUAL) smoke[smoke_num]);
	done_all++;
    } else {
	if (smoke_num == NUM_SMOKE) {
	    smoke_num = 0;
	}
    }
    a_bit = D3DDivide(D3DDivide(D3DVAL(smoke_num), D3DVAL(NUM_SMOKE)),
                     D3DVAL(10.0));
    info->flight_path->lpVtbl->SetFrame(info->flight_path, smoke[smoke_num]);
    info->flight_path->lpVtbl->SetTime(info->flight_path, 
                                       info->t + D3DVAL(0.4) - a_bit);
    smoke[smoke_num]->lpVtbl->SetOrientation(smoke[smoke_num], scene,
					     dir.x, dir.y, dir.z,
					     up.x, up.y, up.z);
    smoke_num++;
    scene->lpVtbl->Release(scene);
}

BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
	   LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    LPDIRECT3DRMFRAME lights = NULL;
    D3DRMBOX box;
    LPDIRECT3DRMMESHBUILDER plane_builder = NULL;
    LPDIRECT3DRMMESHBUILDER mesh_builder = NULL;
    LPDIRECT3DRMMESHBUILDER smoke_builder = NULL;
    LPDIRECT3DRMMESH plane = NULL;
    LPDIRECT3DRMMESH mesh = NULL;
    LPDIRECT3DRMMESH smokemesh = NULL;
    LPDIRECT3DRMLIGHT ambient = NULL;
    LPDIRECT3DRMLIGHT parallel = NULL;
    D3DCOLOR smokec;
    LPDIRECT3DRMFRAME frame = NULL;
    LPDIRECT3DRMFRAME sl = NULL;
    LPDIRECT3DRMFRAME sr = NULL;
    HRESULT rval;
    int i;
    int numPts = 11;
    D3DVECTOR path[] = {
	-D3DVAL(8.0), D3DVAL(3.0), -D3DVAL(12.0),
	-D3DVAL(4.0), D3DVAL(2.0), -D3DVAL(8.0),
	-D3DVAL(2.0), D3DVAL(0.0), -D3DVAL(4.0),
	D3DVAL(9.0), -D3DVAL(1.0), D3DVAL(7.0),
	D3DVAL(4.0), D3DVAL(6.0), D3DVAL(10.0),
	-D3DVAL(4.0), D3DVAL(5.0), D3DVAL(9.0),
	D3DVAL(5.5), D3DVAL(3.5), -D3DVAL(6.5),
	D3DVAL(2.0), D3DVAL(5.0), -D3DVAL(10.0),
	D3DVAL(0.0), D3DVAL(4.0), -D3DVAL(15.0),
	-D3DVAL(5.0), D3DVAL(4.0), -D3DVAL(15.0),
	-D3DVAL(8.0), D3DVAL(3.0), -D3DVAL(12.0)
    };
    D3DVALUE path_t[] = {
        D3DVAL(0), D3DVAL(1), D3DVAL(2), D3DVAL(3), D3DVAL(4), D3DVAL(5), D3DVAL(6), D3DVAL(7), D3DVAL(8), D3DVAL(9), D3DVAL(10)
    };
    static pathInfo info;

    if (FAILED(view->lpVtbl->SetField(view, D3DVAL(0.8))))
	goto generic_error;
    if (FAILED(dev->lpVtbl->SetQuality(dev, D3DRMRENDER_GOURAUD)))
	goto generic_error;
#ifdef FOG
    if (FAILED(dev->lpVtbl->SetDither(dev, TRUE)))
	goto generic_error;
    if (FAILED(scene->lpVtbl->SetFogEnable(scene, TRUE)))
	goto generic_error;
    if (FAILED(scene->lpVtbl->SetFogParams(scene, 1, 30, 1)))
	goto generic_error;
#endif

    /*
     * This Demo flies a plane through a small landscape, followed by a
     * camera. The paths are spline curves.
     */

    /*
     * Initialise smoke trail
     */
    smokec = D3DRMCreateColorRGBA(D3DVAL(0.6), D3DVAL(0.6), D3DVAL(0.6),
				D3DVAL(0.5));
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &smoke_builder)))
	goto generic_error;
    rval = smoke_builder->lpVtbl->Load(smoke_builder, "sphere0.x", NULL,
    				D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load sphere0.x.\n%s", D3DRMErrorToString(rval));
	goto ret_with_error;
    }
    if (FAILED(smoke_builder->lpVtbl->Scale(smoke_builder, D3DVAL(0.015), D3DVAL(0.015),
                                 D3DVAL(0.015))))
				 goto generic_error;

    if (FAILED(smoke_builder->lpVtbl->CreateMesh(smoke_builder, &smokemesh)))
	goto generic_error;
    for (i = 0; i < NUM_SMOKE; i++) {
	if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &smoke[i])))
	    goto generic_error;
	if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, smoke[i], &sl)))
	    goto generic_error;
	if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, smoke[i], &sr)))
	    goto generic_error;

	if (FAILED(sl->lpVtbl->AddVisual(sl, (LPDIRECT3DRMVISUAL) smokemesh)))
	    goto generic_error;
	if (FAILED(sr->lpVtbl->AddVisual(sr, (LPDIRECT3DRMVISUAL) smokemesh)))
	    goto generic_error;
	if (FAILED(sr->lpVtbl->SetPosition(sr, smoke[i], D3DVAL(-0.1), D3DVAL(0.0),
	                                   D3DVAL(0.0))))
					   goto generic_error;
	if (FAILED(smoke[i]->lpVtbl->SetMaterialMode(smoke[i], D3DRMMATERIAL_FROMFRAME)))
	    goto generic_error;
	if (FAILED(smoke[i]->lpVtbl->SetColor(smoke[i], smokec)))
	    goto generic_error;
	if (FAILED(sl->lpVtbl->SetMaterialMode(sl, D3DRMMATERIAL_FROMPARENT)))
	    goto generic_error;
	if (FAILED(sr->lpVtbl->SetMaterialMode(sr, D3DRMMATERIAL_FROMPARENT)))
	    goto generic_error;
	RELEASE(sl);
	RELEASE(sr);
    }
    /*
     * initialize the lights in the scene
     */
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &lights)))
	goto generic_error;
    if (FAILED(lights->lpVtbl->SetPosition(lights, scene, D3DVAL(5.0), D3DVAL(5.0),
					    -D3DVAL(5.0))))
	goto generic_error;
                                
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_PARALLELPOINT, D3DVAL(0.8),
						D3DVAL(0.6), D3DVAL(0.7), &parallel)))
						goto generic_error;
                                  
    if (FAILED(lights->lpVtbl->AddLight(lights, parallel)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_AMBIENT, D3DVAL(0.1),
                                  D3DVAL(0.1), D3DVAL(0.1), &ambient)))
				  goto generic_error;
    if (FAILED(scene->lpVtbl->AddLight(scene, ambient)))
	goto generic_error;

    /*
     * load mesh file
     */

    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &frame)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &mesh_builder)))
	goto generic_error;
    if (FAILED(mesh_builder->lpVtbl->Load(mesh_builder, "land4.x", NULL,
    					D3DRMLOAD_FROMFILE, NULL, NULL)))
	goto generic_error;
    if (FAILED(mesh_builder->lpVtbl->Scale(mesh_builder, D3DVAL(10.0), D3DVAL(8.0),
                                D3DVAL(10.0))))
				goto generic_error;
    if (FAILED(mesh_builder->lpVtbl->GetBox(mesh_builder, &box)))
	goto generic_error;

    /*
     * Color the landscape's faces.
     */
    if (mesh_builder) {
	LPDIRECT3DRMFACEARRAY faces;
	LPDIRECT3DRMFACE this_face;
	int face_count, vertex_count;
	int j;
	D3DVALUE range, height;
	D3DVECTOR *coords;

	if (FAILED(mesh_builder->lpVtbl->GetFaces(mesh_builder, &faces)))
	    goto generic_error;
	face_count = faces->lpVtbl->GetSize(faces);
	    
	range = box.max.y - box.min.y;

	/*
	 * color the faces according to the height
	 */
	for (i = 0; i < face_count; i++) {
	    faces->lpVtbl->GetElement(faces, i, &this_face);
	    vertex_count = this_face->lpVtbl->GetVertexCount(this_face);
	    coords = (LPD3DVECTOR) malloc(vertex_count * sizeof(D3DVECTOR));
	    this_face->lpVtbl->GetVertices(this_face, &vertex_count,
	                                   coords, NULL);
	    if (vertex_count) {
		/*
		 * find maximum height of the face
		 */
		height = coords[0].y;
		for (j = 1; j < vertex_count; j++) {
		    if (coords[j].y > height)
			height = coords[j].y;
		}
		height = D3DDivide((height - box.min.y), range);

		if (height < D3DVAL(0.03))	/* water */
		    this_face->lpVtbl->SetColorRGB(this_face,
				     D3DVAL(0.2), D3DVAL(0.2), D3DVAL(0.5));
		else if (height < D3DVAL(0.3))	/* greenery */
		    this_face->lpVtbl->SetColorRGB(this_face,
				     D3DVAL(0.1), D3DVAL(0.8), D3DVAL(0.1));
		else if (height < D3DVAL(0.5))	/* rocks */
		    this_face->lpVtbl->SetColorRGB(this_face, D3DVAL(0.6),
		                                    D3DVAL(0.3),D3DVAL(0.3));
		else if (height < D3DVAL(0.7))	/* dirty snow */
		    this_face->lpVtbl->SetColorRGB(this_face, D3DVAL(0.8),
		                                    D3DVAL(0.65),
		                                    D3DVAL(0.65));
		else		/* snow */
		    this_face->lpVtbl->SetColorRGB(this_face, D3DVAL(1.0),
		                                    D3DVAL(1.0),D3DVAL(1.0));
	    }
	    free(coords);
	    RELEASE(this_face);
	}
	RELEASE(faces);
    }
    if (FAILED(mesh_builder->lpVtbl->CreateMesh(mesh_builder, &mesh)))
	goto generic_error;
    if (FAILED(frame->lpVtbl->AddVisual(frame, (LPDIRECT3DRMVISUAL) mesh)))
	goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &plane_builder)))
	goto generic_error;
    rval = plane_builder->lpVtbl->Load(plane_builder, "dropship.x", NULL,
    				D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load dropship.x.\n%s", D3DRMErrorToString(rval));
	goto ret_with_error;
    }
    if (FAILED(plane_builder->lpVtbl->Scale(plane_builder, D3DVAL(0.015),
                                 D3DVAL(0.008), D3DVAL(0.015))))
				 goto generic_error;
    if (FAILED(plane_builder->lpVtbl->CreateMesh(plane_builder, &plane)))
	goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateAnimation(lpD3DRM, &info.flight_path)))
	goto generic_error;
    info.flight_path->lpVtbl->SetOptions(info.flight_path, D3DRMANIMATION_CLOSED
    					 | D3DRMANIMATION_SPLINEPOSITION
					 | D3DRMANIMATION_POSITION);
    for (i = 0; i < numPts; i++)
	info.flight_path->lpVtbl->AddPositionKey(info.flight_path, path_t[i], 
                                                 path[i].x,
	                                         path[i].y, path[i].z);

    info.t = D3DVAL(0.0);
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &info.chase)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &info.plane_frame)))
	goto generic_error;
    if (FAILED(info.plane_frame->lpVtbl->AddVisual(info.plane_frame,
                                        (LPDIRECT3DRMVISUAL) plane)))
					goto generic_error;

    if (FAILED(camera->lpVtbl->AddMoveCallback(camera, moveCamera, (void *) &info)))
	goto generic_error;
    if (FAILED(camera->lpVtbl->AddDestroyCallback(camera, cleanupObjects, &info)))
	goto generic_error;

    RELEASE(lights);
    RELEASE(plane_builder);
    RELEASE(mesh_builder);
    RELEASE(smoke_builder);
    RELEASE(plane);
    RELEASE(mesh);
    RELEASE(smokemesh);
    RELEASE(ambient);
    RELEASE(parallel);
    RELEASE(frame);
    return TRUE;

generic_error:
    Msg("A failure has occurred while building the scene.\n");
ret_with_error:
    RELEASE(lights);
    RELEASE(plane_builder);
    RELEASE(mesh_builder);
    RELEASE(smoke_builder);
    RELEASE(plane);
    RELEASE(mesh);
    RELEASE(smokemesh);
    RELEASE(ambient);
    RELEASE(parallel);
    RELEASE(frame);
    RELEASE(sl);
    RELEASE(sr);
    return FALSE;
}

void
OverrideDefaults(Defaults* defaults)
{
    defaults->bNoTextures = TRUE;
    defaults->bConstRenderQuality = TRUE;
    lstrcpy(defaults->Name, "Fly Direct3DRM Example");
}
