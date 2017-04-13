/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: faces.c
 *
 ***************************************************************************/

/*
 * Example program to demonstrate MeshAddFaces
 */

#include "rmdemo.h"

D3DVECTOR cube_vertices[] = {-D3DVAL(0.5), -D3DVAL(0.5), -D3DVAL(0.5),
    -D3DVAL(0.5), -D3DVAL(0.5), D3DVAL(0.5),
    -D3DVAL(0.5), D3DVAL(0.5), -D3DVAL(0.5),
    -D3DVAL(0.5), D3DVAL(0.5), D3DVAL(0.5),
    D3DVAL(0.5), -D3DVAL(0.5), -D3DVAL(0.5),
    D3DVAL(0.5), -D3DVAL(0.5), D3DVAL(0.5),
    D3DVAL(0.5), D3DVAL(0.5), -D3DVAL(0.5),
    D3DVAL(0.5), D3DVAL(0.5), D3DVAL(0.5)
};

/*
 * face_data is a vertex count followed by the vertex reference in the
 * vertices list. If normal_count > 0, then pairs of vectors are
 * referenced: first the vertex and secondly the normal reference. the
 * list is terminated by a 0 (vertex count to a face)
 */


BOOL
build_face1(LPDIRECT3DRMMESHBUILDER msh)
{
    /*
     * add a single face to a mesh.
     */

    /*
     * Single face with all normals pointing in the same direction.
     */

    int vertex_count = 4;
    D3DVECTOR vertices[4] = {D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0),
	D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0),
	D3DVAL(1.0), D3DVAL(0.0), D3DVAL(1.0),
	D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0)
    };
    int normal_count = 4;
    D3DVECTOR normals[4] = {D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
	D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
	D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
	D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
    };
    int face_data[] = {4, 0, 0, 1, 1, 2, 2, 3, 3, 0};

    if (FAILED(msh->lpVtbl->AddFaces(msh, vertex_count, vertices, normal_count, 
                          normals, face_data, NULL)))
			  return FALSE;
    return TRUE;
}

BOOL
build_face2(LPDIRECT3DRMMESHBUILDER msh)
{
    /*
     * Single face with normals pointing in different directions to
     * approximate a curved surface.
     */
    int vertex_count = 4;
    D3DVECTOR vertices[4] = {D3DVAL(0.0), D3DVAL(0.0), D3DVAL(0.0),
	D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0),
	D3DVAL(1.0), D3DVAL(0.0), D3DVAL(1.0),
	D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0)
    };
    int normal_count = 4;
    D3DVECTOR normals[4] = {
	D3DVAL(0.5), D3DVAL(0.7), D3DVAL(0.5),
	D3DVAL(0.5), D3DVAL(0.7), -D3DVAL(0.5),
	-D3DVAL(0.5), D3DVAL(0.7), -D3DVAL(0.5),
	-D3DVAL(0.5), D3DVAL(0.7), D3DVAL(0.5)
    };
    int face_data[] = {4, 0, 0, 1, 1, 2, 2, 3, 3, 0};

    if (FAILED(msh->lpVtbl->AddFaces(msh, vertex_count, vertices, normal_count, 
                          normals, face_data, NULL)))
			  return FALSE;
    return TRUE;
}

BOOL
build_cube1(LPDIRECT3DRMMESHBUILDER msh)
{
    /*
     * cube 1 has planar faces, one normal is shared by all vertices of a
     * face
     */
    int face1_data[] = {
	4, 1, 0, 5, 1, 7, 2, 3, 3,
	4, 2, 4, 3, 5, 7, 6, 6, 7,
	4, 5, 8, 4, 9, 6, 10, 7, 11,
	4, 0, 12, 2, 13, 6, 14, 4, 15,
	4, 0, 16, 4, 17, 5, 18, 1, 19,
	4, 0, 20, 1, 21, 3, 22, 2, 23,
    0};

    D3DVECTOR cube1_normals[] = {
	D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0),
	D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0),
	D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0),
	D3DVAL(0.0), D3DVAL(0.0), D3DVAL(1.0),
	D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
	D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
	D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
	D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0),
	D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0),
	D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0),
	D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0),
	D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0),
	D3DVAL(0.0), D3DVAL(0.0), -D3DVAL(1.0),
	D3DVAL(0.0), D3DVAL(0.0), -D3DVAL(1.0),
	D3DVAL(0.0), D3DVAL(0.0), -D3DVAL(1.0),
	D3DVAL(0.0), D3DVAL(0.0), -D3DVAL(1.0),
	D3DVAL(0.0), -D3DVAL(1.0), D3DVAL(0.0),
	D3DVAL(0.0), -D3DVAL(1.0), D3DVAL(0.0),
	D3DVAL(0.0), -D3DVAL(1.0), D3DVAL(0.0),
	D3DVAL(0.0), -D3DVAL(1.0), D3DVAL(0.0),
	-D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0)
	- D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0)
	- D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0)
	- D3DVAL(1.0), D3DVAL(0.0), D3DVAL(0.0)
    };

    if (FAILED(msh->lpVtbl->AddFaces(msh, 8, cube_vertices, 6 * 4, cube1_normals,
			  face1_data, NULL)))
			  return FALSE;
    return TRUE;
}

BOOL
build_cube2(LPDIRECT3DRMMESHBUILDER msh)
{
    /*
     * cube 2 has rounded faces, the normals radiate out at each vertex,
     * one normal to each vertex
     */

    int face2_data[] = {
	4, 1, 1, 5, 5, 7, 7, 3, 3,
	4, 2, 2, 3, 3, 7, 7, 6, 6,
	4, 5, 5, 4, 4, 6, 6, 7, 7,
	4, 0, 0, 2, 2, 6, 6, 4, 4,
	4, 0, 0, 4, 4, 5, 5, 1, 1,
	4, 0, 0, 1, 1, 3, 3, 2, 2,
    0};

    D3DVECTOR cube2_normals[] = {
	-D3DVAL(1.0), -D3DVAL(1.0), -D3DVAL(1.0),
	-D3DVAL(1.0), -D3DVAL(1.0), D3DVAL(1.0),
	-D3DVAL(1.0), D3DVAL(1.0), -D3DVAL(1.0),
	-D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0),
	D3DVAL(1.0), -D3DVAL(1.0), -D3DVAL(1.0),
	D3DVAL(1.0), -D3DVAL(1.0), D3DVAL(1.0),
	D3DVAL(1.0), D3DVAL(1.0), -D3DVAL(1.0),
	D3DVAL(1.0), D3DVAL(1.0), D3DVAL(1.0)
    };
    if (FAILED(msh->lpVtbl->AddFaces(msh, 8, cube_vertices, 8, cube2_normals,
			  face2_data, NULL)))
			  return FALSE;
    return TRUE;
}

BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
	   LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    D3DRMRENDERQUALITY quality = D3DRMRENDER_GOURAUD;
    LPDIRECT3DRMMESHBUILDER light_builder, face1_builder, face2_builder;
    LPDIRECT3DRMMESHBUILDER cube1_builder, cube2_builder;
    LPDIRECT3DRMMESH light_mesh, face1_mesh, face2_mesh, cube1_mesh, cube2_mesh;
    LPDIRECT3DRMFRAME frame1, frame2, face_frame1, face_frame2, light_frame;
    LPDIRECT3DRMFRAME lights;
    LPDIRECT3DRMLIGHT light1, light2;
    HRESULT rval;

    view = view;		/* not used */
    light_builder = NULL; face1_builder = NULL; face2_builder = NULL;
    cube1_builder = NULL; cube2_builder = NULL;
    light_mesh = NULL; face1_mesh = NULL; face2_mesh = NULL;
    cube1_mesh = NULL; cube2_mesh = NULL;
    frame1 = NULL; frame2 = NULL; face_frame1 = NULL; face_frame2 = NULL;
    light_frame = NULL; lights = NULL; light1 = NULL; light2 = NULL;

    /*
     * This Demo shows the construction of planar faces\n"); with vertex
     * normals for realistic modelling of\n"); flat and curved surfaces by
     * polygonal approximation.\n");
     */

    if (FAILED(dev->lpVtbl->SetQuality(dev, quality)))
	goto generic_error;
	
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &face_frame1)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &face_frame2)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &frame1)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &frame2)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, scene, &light_frame)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateFrame(lpD3DRM, light_frame, &lights)))
	goto generic_error;

    if (FAILED(lights->lpVtbl->SetPosition(lights, light_frame, D3DVAL(0.0), D3DVAL(0.0), D3DVAL(2.2))))
	goto generic_error;
    if (FAILED(light_frame->lpVtbl->SetPosition(light_frame, scene, D3DVAL(0.0), D3DVAL(0.4), D3DVAL(0.0))))
	goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_POINT, D3DVAL(0.9),
                                  D3DVAL(0.8), D3DVAL(0.7), &light1)))
				  goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateLightRGB(lpD3DRM, D3DRMLIGHT_AMBIENT, D3DVAL(0.02),
                                  D3DVAL(0.01), D3DVAL(0.01), &light2)))
				  goto generic_error;
    if (FAILED(lights->lpVtbl->AddLight(lights, light1)))
	goto generic_error;
    if (FAILED(scene->lpVtbl->AddLight(scene, light2)))
	goto generic_error;
    RELEASE(light1);
    RELEASE(light2);

    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &face1_builder)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &face2_builder)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &cube1_builder)))
	goto generic_error;
    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &cube2_builder)))
	goto generic_error;

    if (!build_face1(face1_builder))
	goto generic_error;
    if (!build_face2(face2_builder))
	goto generic_error;
    if (!build_cube1(cube1_builder))
	goto generic_error;
    if (!build_cube2(cube2_builder))
	goto generic_error;

    if (FAILED(face1_builder->lpVtbl->CreateMesh(face1_builder, &face1_mesh)))
	goto generic_error;
    if (FAILED(face2_builder->lpVtbl->CreateMesh(face2_builder, &face2_mesh)))
	goto generic_error;
    if (FAILED(cube1_builder->lpVtbl->CreateMesh(cube1_builder, &cube1_mesh)))
	goto generic_error;
    if (FAILED(cube2_builder->lpVtbl->CreateMesh(cube2_builder, &cube2_mesh)))
	goto generic_error;

    RELEASE(face1_builder);
    RELEASE(face2_builder);
    RELEASE(cube1_builder);
    RELEASE(cube2_builder);

    if (FAILED(face_frame1->lpVtbl->AddVisual(face_frame1, (LPDIRECT3DRMVISUAL) face1_mesh)))
	goto generic_error;
    if (FAILED(face_frame2->lpVtbl->AddVisual(face_frame2, (LPDIRECT3DRMVISUAL) face2_mesh)))
	goto generic_error;
    if (FAILED(frame1->lpVtbl->AddVisual(frame1, (LPDIRECT3DRMVISUAL) cube1_mesh)))
	goto generic_error;
    if (FAILED(frame2->lpVtbl->AddVisual(frame2, (LPDIRECT3DRMVISUAL) cube2_mesh)))
	goto generic_error;

    if (FAILED(lpD3DRM->lpVtbl->CreateMeshBuilder(lpD3DRM, &light_builder)))
	goto generic_error;
    rval = light_builder->lpVtbl->Load(light_builder, "sphere0.x", NULL,
    				D3DRMLOAD_FROMFILE, NULL, NULL);
    if (rval != D3DRM_OK) {
        Msg("Failed to load sphere0.x\n");
	goto ret_with_error;
    }
    if (FAILED(light_builder->lpVtbl->SetColorRGB(light_builder, D3DVAL(1), D3DVAL(1),
                                        D3DVAL(1))))
					goto generic_error;
    if (FAILED(light_builder->lpVtbl->Scale(light_builder, D3DVAL(0.1), D3DVAL(0.1), 
                                 D3DVAL(0.1))))
				 goto generic_error;
    if (FAILED(light_builder->lpVtbl->SetQuality(light_builder, D3DRMRENDER_UNLITFLAT)))
	goto generic_error;
    if (FAILED(light_builder->lpVtbl->CreateMesh(light_builder, &light_mesh)))
	goto generic_error;
    RELEASE(light_builder);

    if (FAILED(lights->lpVtbl->AddVisual(lights, (LPDIRECT3DRMVISUAL) light_mesh)))
	goto generic_error;

    if (FAILED(camera->lpVtbl->SetPosition(camera, scene, D3DVAL(0.0), D3DVAL(2), -D3DVAL(5))))
	goto generic_error;
    if (FAILED(face_frame1->lpVtbl->SetPosition(face_frame1, scene, -D3DVAL(0.5), 
                                     D3DVAL(0.5), D3DVAL(2))))
				     goto generic_error;
    if (FAILED(face_frame2->lpVtbl->SetPosition(face_frame2, scene, -D3DVAL(0.5), 
                                     -D3DVAL(1.5), D3DVAL(2))))
				     goto generic_error;
    if (FAILED(frame1->lpVtbl->SetPosition(frame1, scene, -D3DVAL(2.0), D3DVAL(0.0), D3DVAL(2))))
	goto generic_error;
    if (FAILED(frame2->lpVtbl->SetPosition(frame2, scene, D3DVAL(1.5), D3DVAL(0.0), D3DVAL(2))))
	goto generic_error;

    if (FAILED(face_frame1->lpVtbl->SetOrientation(face_frame1, scene, D3DVAL(0.0), D3DVAL(1), D3DVAL(0.0),
                                        D3DVAL(0.0), D3DVAL(0.0), -D3DVAL(1))))
					goto generic_error;
    if (FAILED(face_frame2->lpVtbl->SetOrientation(face_frame2, scene, D3DVAL(0.0), D3DVAL(1), D3DVAL(0.0),
                                        D3DVAL(0.0), D3DVAL(0.0), -D3DVAL(1))))
					goto generic_error;
    if (FAILED(camera->lpVtbl->SetOrientation(camera, scene, D3DVAL(0.0), -D3DVAL(0.2), D3DVAL(1),
                                   D3DVAL(0.0), D3DVAL(1), D3DVAL(0.0))))
				   goto generic_error;
    if (FAILED(frame1->lpVtbl->SetRotation(frame1, scene, D3DVAL(1), D3DVAL(0.0), D3DVAL(1),
                                -D3DVAL(0.005))))
				goto generic_error;
    if (FAILED(frame2->lpVtbl->SetRotation(frame2, scene, D3DVAL(0.0), D3DVAL(1), D3DVAL(1),
                                -D3DVAL(0.005))))
				goto generic_error;
    if (FAILED(light_frame->lpVtbl->SetRotation(light_frame, scene, D3DVAL(0.0), D3DVAL(1), D3DVAL(0.0),
                                     -D3DVAL(0.02))))
				     goto generic_error;

    RELEASE(light_mesh);
    RELEASE(face1_mesh);
    RELEASE(face2_mesh);
    RELEASE(cube1_mesh);
    RELEASE(cube2_mesh);

    RELEASE(frame1);
    RELEASE(frame2);
    RELEASE(face_frame1);
    RELEASE(face_frame2);
    RELEASE(light_frame);
    RELEASE(lights);
    return TRUE;
generic_error:
    Msg("An error has occurred while building the scene.\n");
ret_with_error:
    RELEASE(light_builder);
    RELEASE(face1_builder);
    RELEASE(face2_builder);
    RELEASE(cube1_builder);
    RELEASE(cube2_builder);
    RELEASE(light_mesh);
    RELEASE(face1_mesh);
    RELEASE(face2_mesh);
    RELEASE(cube1_mesh);
    RELEASE(cube2_mesh);
    RELEASE(frame1);
    RELEASE(frame2);
    RELEASE(face_frame1);
    RELEASE(face_frame2);
    RELEASE(light_frame);
    RELEASE(lights);
    RELEASE(light1);
    RELEASE(light2);
    return FALSE;
}

void
OverrideDefaults(Defaults *defaults)
{
    defaults->bNoTextures = TRUE;
    defaults->bConstRenderQuality = TRUE;
    lstrcpy(defaults->Name, "Faces Direct3DRM Example");
}
