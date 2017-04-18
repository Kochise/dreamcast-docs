/*==========================================================================
 *
 *  Copyright (C) 1995, 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File: morph.c
 *
 ***************************************************************************/

/*
 * An example of the use of interpolators.
 */

#include "rmdemo.h"

#define NO_NORMAL {D3DVAL(0), D3DVAL(0), D3DVAL(0)}, D3DVAL(0), D3DVAL(0), 0

/* cube corners */
#define CFTL(v)	{{-D3DVAL(v), +D3DVAL(v), -D3DVAL(v)}, NO_NORMAL}
#define CFTR(v)	{{+D3DVAL(v), +D3DVAL(v), -D3DVAL(v)}, NO_NORMAL}
#define CFBR(v)	{{+D3DVAL(v), -D3DVAL(v), -D3DVAL(v)}, NO_NORMAL}
#define CFBL(v)	{{-D3DVAL(v), -D3DVAL(v), -D3DVAL(v)}, NO_NORMAL}
#define CBTL(v)	{{-D3DVAL(v), +D3DVAL(v), +D3DVAL(v)}, NO_NORMAL}
#define CBTR(v)	{{+D3DVAL(v), +D3DVAL(v), +D3DVAL(v)}, NO_NORMAL}
#define CBBR(v)	{{+D3DVAL(v), -D3DVAL(v), +D3DVAL(v)}, NO_NORMAL}
#define CBBL(v)	{{-D3DVAL(v), -D3DVAL(v), +D3DVAL(v)}, NO_NORMAL}

/* face centers */
#define FRT(v)	{{ D3DVAL(0),  D3DVAL(0), -D3DVAL(v)}, NO_NORMAL}
#define BCK(v)	{{ D3DVAL(0),  D3DVAL(0),  D3DVAL(v)}, NO_NORMAL}
#define BTM(v)	{{ D3DVAL(0), -D3DVAL(v),  D3DVAL(0)}, NO_NORMAL}
#define TOP(v)	{{ D3DVAL(0),  D3DVAL(v),  D3DVAL(0)}, NO_NORMAL}
#define LFT(v)	{{-D3DVAL(v),  D3DVAL(0),  D3DVAL(0)}, NO_NORMAL}
#define RGT(v)	{{ D3DVAL(v),  D3DVAL(0),  D3DVAL(0)}, NO_NORMAL}


D3DRMVERTEX verts0[] =
{   CFTL(1), CFTR(1), CFBR(1), CFBL(1),
    CBBR(1), CBTR(1), CBTL(1), CBBL(1),
    CFBR(1), CBBR(1), CBBL(1), CFBL(1),
    CBTL(1), CBTR(1), CFTR(1), CFTL(1),
    CBTL(1), CFTL(1), CFBL(1), CBBL(1),
    CFBR(1), CFTR(1), CBTR(1), CBBR(1),
    FRT(5), BCK(5), BTM(5), TOP(5), LFT(5), RGT(5)
};

D3DRMVERTEX verts1[] =
{   CFTL(2), CFTR(2), CFBR(2), CFBL(2),
    CBBR(2), CBTR(2), CBTL(2), CBBL(2),
    CFBR(2), CBBR(2), CBBL(2), CFBL(2),
    CBTL(2), CBTR(2), CFTR(2), CFTL(2),
    CBTL(2), CFTL(2), CFBL(2), CBBL(2),
    CFBR(2), CFTR(2), CBTR(2), CBBR(2),
    FRT(1), BCK(1), BTM(1), TOP(1), LFT(1), RGT(1)
};

unsigned faces[] =
{    0,  1, 24,  1,  2, 24,  2,  3, 24,  3,  0, 24,
     4,  5, 25,  5,  6, 25,  6,  7, 25,  7,  4, 25,
     8,  9, 26,  9, 10, 26, 10, 11, 26, 11,  8, 26,
    12, 13, 27, 13, 14, 27, 14, 15, 27, 15, 12, 27,
    16, 17, 28, 17, 18, 28, 18, 19, 28, 19, 16, 28,
    20, 21, 29, 21, 22, 29, 22, 23, 29, 23, 20, 29
};

static void CDECL destroyInterp(LPDIRECT3DRMOBJECT obj, void* arg)
{
    LPDIRECT3DRMINTERPOLATOR meshInterp = (LPDIRECT3DRMINTERPOLATOR) arg;

    if (meshInterp) meshInterp->Release();
}

void CDECL 
interpolate(LPDIRECT3DRMFRAME frame, void *arg, D3DVALUE delta)
{
    static D3DVALUE val = D3DVAL(0);
    LPDIRECT3DRMINTERPOLATOR meshInterp = (LPDIRECT3DRMINTERPOLATOR) arg;

    meshInterp->Interpolate(val += delta, NULL, D3DRMINTERPOLATION_CLOSED | D3DRMINTERPOLATION_LINEAR);
}

void generate_normals(D3DRMVERTEX verts[])
{
    unsigned i;
    D3DVECTOR a, b;

    for (i = 0; i < 24; i++)
    {
	D3DRMVectorSubtract(&a, &verts[faces[i * 3 + 1]].position, &verts[i].position);
	D3DRMVectorSubtract(&b, &verts[faces[i * 3 + 2]].position, &verts[i].position);
	D3DRMVectorCrossProduct(&verts[i].normal, &a, &b);
	D3DRMVectorNormalize(&verts[i].normal);
    }
}

#define D3DTRY(x) if (FAILED(x)) goto generic_error

#define CREATE(type, obj) CreateObject(CLSID_C##type, NULL, IID_I##type, (void **) obj)

BOOL
BuildScene(LPDIRECT3DRMDEVICE dev, LPDIRECT3DRMVIEWPORT view,
	   LPDIRECT3DRMFRAME scene, LPDIRECT3DRMFRAME camera)
{
    LPDIRECT3DRMMESH mesh = NULL, meshProxy = NULL;
    LPDIRECT3DRMFRAME frame = NULL, proxyFrame = NULL;
    LPDIRECT3DRMFRAME axis = NULL;
    LPDIRECT3DRMFRAME orbit = NULL;
    LPDIRECT3DRMLIGHT light1 = NULL;
    LPDIRECT3DRMLIGHT light2 = NULL;
    LPDIRECT3DRMINTERPOLATOR meshInterp = NULL;

    dev, view, camera;

    /* generate flat-shading normals for faces */
    generate_normals(verts0);
    generate_normals(verts1);

    D3DTRY(lpD3DRM->CreateObject(CLSID_CDirect3DRMMeshInterpolator, NULL, 
				 IID_IDirect3DRMInterpolator, (void **) &meshInterp));
    D3DTRY(meshInterp->QueryInterface(IID_IDirect3DRMMesh, (void **) &meshProxy));

    D3DTRY(meshInterp->SetIndex(D3DVAL(0)));
    D3DTRY(meshProxy->SetVertices(0, 0, 30, verts1));
    D3DTRY(meshProxy->SetGroupColorRGB(0, D3DVAL(0.5), D3DVAL(0.4), D3DVAL(0.7)));

    D3DTRY(meshInterp->SetIndex(D3DVAL(25)));
    D3DTRY(meshProxy->SetVertices(0, 0, 30, verts0));
    D3DTRY(meshProxy->SetGroupColorRGB(0, D3DVAL(1), D3DVAL(0.0), D3DVAL(0.3)));

    D3DTRY(meshInterp->SetIndex(D3DVAL(40)));
    D3DTRY(meshProxy->SetGroupColorRGB(0, D3DVAL(0.6), D3DVAL(0.6), D3DVAL(0.6)));

    D3DTRY(meshInterp->SetIndex(D3DVAL(75)));
    meshProxy->Release();

    D3DTRY(lpD3DRM->CREATE(Direct3DRMLight, &light1));
    D3DTRY(light1->SetType(D3DRMLIGHT_AMBIENT));
    D3DTRY(light1->SetColorRGB(D3DVAL(0.2), D3DVAL(0.2), D3DVAL(0.2)));

    D3DTRY(lpD3DRM->CREATE(Direct3DRMLight, &light2));
    D3DTRY(light2->SetType(D3DRMLIGHT_DIRECTIONAL));
    D3DTRY(light2->SetColorRGB(D3DVAL(1), D3DVAL(1), D3DVAL(1)));

    D3DTRY(scene->AddLight(light1));
    D3DTRY(scene->SetSceneBackgroundRGB(D3DVAL(0.3), D3DVAL(0.6), D3DVAL(0.3)));

    D3DTRY(lpD3DRM->CREATE(Direct3DRMFrame, &frame));
    D3DTRY(scene->AddChild(frame));
    D3DTRY(frame->SetOrientation(scene, D3DVAL(0.5), -D3DVAL(0.5), D3DVAL(1),
				 D3DVAL(0), D3DVAL(1), D3DVAL(0)));

    D3DTRY(frame->AddLight(light2));
    frame->Release();

    D3DTRY(lpD3DRM->CREATE(Direct3DRMFrame, &frame));
    D3DTRY(scene->AddChild(frame));
    D3DTRY(frame->SetPosition(scene, D3DVAL(0), D3DVAL(0), D3DVAL(15)));
    D3DTRY(frame->SetOrientation(scene, D3DVAL(0), D3DVAL(1.0), D3DVAL(0),
    					D3DVAL(0), D3DVAL(0), D3DVAL(1)));
    D3DTRY(frame->SetRotation(scene, D3DVAL(0), D3DVAL(0.9), D3DVAL(1.0), D3DVAL(0.04)));

    D3DTRY(lpD3DRM->CREATE(Direct3DRMMesh, &mesh));
    D3DTRY(mesh->AddGroup(30, 24, 3, faces, NULL));
    D3DTRY(mesh->SetGroupQuality(0, D3DRMRENDER_FLAT));

    D3DTRY(meshInterp->AttachObject(mesh));
    D3DTRY(frame->AddVisual(mesh));

    D3DTRY(frame->AddMoveCallback(interpolate, meshInterp));
    D3DTRY(frame->AddDestroyCallback(destroyInterp, meshInterp));

    D3DTRY(lpD3DRM->CREATE(Direct3DRMFrame, &axis));
    D3DTRY(frame->AddChild(axis));
    D3DTRY(axis->SetRotation(frame, D3DVAL(0), D3DVAL(1), D3DVAL(0), D3DVAL(0.04)));

    D3DTRY(lpD3DRM->CREATE(Direct3DRMFrame, &orbit));
    D3DTRY(axis->AddChild(orbit));
    D3DTRY(orbit->SetPosition(axis, D3DVAL(2.6), D3DVAL(0), D3DVAL(0)));

    RELEASE(mesh);
    RELEASE(frame);
    RELEASE(axis);
    RELEASE(orbit);
    RELEASE(light1);
    RELEASE(light2);
    /* don't release the wrap */
    return TRUE;
generic_error:
    Msg("A failure occurred while building the scene.\n");
    RELEASE(mesh);
    RELEASE(frame);
    RELEASE(axis);
    RELEASE(orbit);
    RELEASE(light1);
    RELEASE(light2);
    return FALSE;
}

void
OverrideDefaults(Defaults* defaults)
{
    defaults->bConstRenderQuality = TRUE;
    lstrcpy(defaults->Name, "Interpolator Direct3DRM Example");
}
