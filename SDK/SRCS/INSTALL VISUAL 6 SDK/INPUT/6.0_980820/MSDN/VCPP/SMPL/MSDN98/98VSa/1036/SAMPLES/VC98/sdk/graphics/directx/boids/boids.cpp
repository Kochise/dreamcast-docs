/*
**----------------------------------------------------------------------------
**
**  File:       boids.cpp
**  Purpose:    
**  Notes:
**
**	Copyright (C) 1995 - 1997 Microsoft Corporation. All Rights Reserved.
**----------------------------------------------------------------------------
*/

/*
**----------------------------------------------------------------------------
** Includes
**----------------------------------------------------------------------------
*/

#include <math.h>
#include <time.h>

#include "D3DScene.h"
#include "Debug.h"
#include "D3DWin.h"
#include "d3dutils.h"
#include "d3dtex.h"
#include "boids.h"


/*
**----------------------------------------------------------------------------
** Defines
**----------------------------------------------------------------------------
*/

#define NUM_BOIDS	13

// ground pattern
D3DVECTOR       grid_color(0.0f, 0.3f, 0.5f);
D3DLVERTEX	pattern1[24];
D3DLVERTEX	pattern2[8];
WORD		pat1_indices[25] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 
								13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 0 };
WORD		pat2_indices[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 0 };

#define MESH_SIZE	8
#define SPHERE_VERTICES	(2+MESH_SIZE*MESH_SIZE*2)
#define SPHERE_INDICES	((MESH_SIZE*4 + MESH_SIZE*4*(MESH_SIZE-1))*3)

    
/*
**----------------------------------------------------------------------------
** Local Variables
**----------------------------------------------------------------------------
*/

D3DVERTEX	sphere[SPHERE_VERTICES];
WORD		sphere_indices[SPHERE_INDICES];

Flock		flock;

D3DVERTEX	boid_vertices[16];
WORD		boid_indices[30];

D3DMATRIX	proj, view, world;

Light		*lpLight1,
			*lpLight2;

Material	*lpBackgroundMat,
			*lpGridMat,
			*lpSphereMat,
			*lpBoidMat;

D3DTexture	SphereTex;

/*
**----------------------------------------------------------------------------
** Function definitions
**----------------------------------------------------------------------------
*/

/*
**----------------------------------------------------------------------------
** Name:        DrawBoid
** Purpose:
**----------------------------------------------------------------------------
*/

HRESULT
Drawboid(LPDIRECT3DDEVICE2 lpDev)
{
	HRESULT hResult;

        hResult = lpDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DVT_VERTEX, (LPVOID)boid_vertices, 16, boid_indices, 30, D3DDP_WAIT);

	return hResult;
} // End DrawBoid


/*
**----------------------------------------------------------------------------
** Name:        DrawSphere
** Purpose:
**----------------------------------------------------------------------------
*/

HRESULT
DrawSphere(LPDIRECT3DDEVICE2 lpDev)
{
	HRESULT hResult;

        hResult = lpDev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, D3DVT_VERTEX, (LPVOID)sphere, SPHERE_VERTICES, sphere_indices, SPHERE_INDICES, D3DDP_WAIT);
	if (hResult != D3D_OK)
		return hResult;

	return D3D_OK;
} // End DrawSphere


HRESULT
DrawPattern(LPDIRECT3DDEVICE2 lpDev)
{
	HRESULT hResult;

	for (int dx= -2; dx<3; dx++) {
		for (int dz= -2; dz<3; dz++) {
			D3DVECTOR	offset(dx*80.0f, 0.0f, dz*80.0f);

			world = TranslateMatrix(offset);
			hResult = lpDev->SetTransform(D3DTRANSFORMSTATE_WORLD, &world);
			if (hResult != D3D_OK) {
				REPORTERR(hResult);
				return hResult;
			}
                        hResult = lpDev->DrawIndexedPrimitive(D3DPT_LINESTRIP, D3DVT_LVERTEX, (LPVOID)pattern1, 24, pat1_indices, 25, D3DDP_WAIT);
			if (hResult != D3D_OK) {
				REPORTERR(hResult);
				return hResult;
			}
                        hResult = lpDev->DrawIndexedPrimitive(D3DPT_LINESTRIP, D3DVT_LVERTEX, (LPVOID)pattern2, 8, pat2_indices, 9, D3DDP_WAIT);
			if (hResult != D3D_OK) {
				REPORTERR(hResult);
				return hResult;
			}
		}
	}

	return D3D_OK;
}	// end of DrawPattern()


/*
**----------------------------------------------------------------------------
** D3DScene Methods
**----------------------------------------------------------------------------
*/

/*
**----------------------------------------------------------------------------
** Name:        D3DScene::D3DScene
** Purpose:		Default Constructor
**----------------------------------------------------------------------------
*/

D3DScene::D3DScene(void)
{
	lpd3dWindow = NULL;
} // End D3DScene::D3DScene


  
/*
**----------------------------------------------------------------------------
** Name:        D3DScene::~D3DScene
** Purpose:		Default Destructor
**----------------------------------------------------------------------------
*/

D3DScene::~D3DScene(void)
{
	Fini();
	lpd3dWindow = NULL;
} // End D3DScene::~D3DScene



/*
**----------------------------------------------------------------------------
** Name:        D3DScene::Init
** Purpose:		Do all static intialization here
** Notes:		This means all Scene data that isn't dependent on the
**				D3D interface, viewport, or D3D device in some manner
**----------------------------------------------------------------------------
*/

HRESULT
D3DScene::Init(LPD3DWindow lpd3dWin)
{
	HRESULT hResult;
	int i, j;

	// Check Parameters
	if (! lpd3dWin)	{
		// Need a valid D3D Window object
		hResult = APPERR_INVALIDPARAMS;
		REPORTERR(hResult);
		return hResult;
	}

	// Save assocation with D3D Window
	lpd3dWindow = lpd3dWin;

	// generate the boid data

	// top
	boid_vertices[ 0] = D3DVERTEX(D3DVECTOR(0.0f, 0.0f, 10.0f), Normalize(D3DVECTOR(0.2f, 1.0f, 0.0f)), 0.0f, 0.5f);
	boid_vertices[ 1] = D3DVERTEX(D3DVECTOR(10.0f, 0.0f, -10.0f), Normalize(D3DVECTOR(0.1f, 1.0f, 0.0f)), 0.5f, 1.0f);
	boid_vertices[ 2] = D3DVERTEX(D3DVECTOR(3.0f, 3.0f, -7.0f), Normalize(D3DVECTOR(0.0f, 1.0f, 0.0f)), 0.425f, 0.575f);
	boid_vertices[ 3] = D3DVERTEX(D3DVECTOR(-3.0f, 3.0f, -7.0f), Normalize(D3DVECTOR(-0.1f, 1.0f, 0.0f)), 0.425f, 0.425f);
	boid_vertices[ 4] = D3DVERTEX(D3DVECTOR(-10.0f, 0.0f, -10.0f), Normalize(D3DVECTOR(-0.2f, 1.0f, 0.0f)), 0.5f, 0.0f);

	//bottom
	boid_vertices[ 5] = D3DVERTEX(D3DVECTOR(0.0f, 0.0f, 10.0f), Normalize(D3DVECTOR(0.2f, -1.0f, 0.0f)), 1.0f, 0.5f);
	boid_vertices[ 6] = D3DVERTEX(D3DVECTOR(10.0f, 0.0f, -10.0f), Normalize(D3DVECTOR(0.1f, -1.0f, 0.0f)), 0.5f, 1.0f);
	boid_vertices[ 7] = D3DVERTEX(D3DVECTOR(3.0f, -3.0f, -7.0f), Normalize(D3DVECTOR(0.0f, -1.0f, 0.0f)), 0.575f, 0.575f);
	boid_vertices[ 8] = D3DVERTEX(D3DVECTOR(-3.0f, -3.0f, -7.0f), Normalize(D3DVECTOR(-0.1f, -1.0f, 0.0f)), 0.575f, 0.425f);
	boid_vertices[ 9] = D3DVERTEX(D3DVECTOR(-10.0f, 0.0f, -10.0f), Normalize(D3DVECTOR(-0.2f, -1.0f, 0.0f)), 0.5f, 0.0f);

	// rear
	boid_vertices[10] = D3DVERTEX(D3DVECTOR(10.0f, 0.0f, -10.0f), Normalize(D3DVECTOR(-0.4f, 0.0f, -1.0f)), 0.5f, 1.0f);
	boid_vertices[11] = D3DVERTEX(D3DVECTOR(3.0f, 3.0f, -7.0f), Normalize(D3DVECTOR(-0.2f, 0.0f, -1.0f)), 0.425f, 0.575f);
	boid_vertices[12] = D3DVERTEX(D3DVECTOR(-3.0f, 3.0f, -7.0f), Normalize(D3DVECTOR(0.2f, 0.0f, -1.0f)), 0.425f, 0.425f);
	boid_vertices[13] = D3DVERTEX(D3DVECTOR(-10.0f, 0.0f, -10.0f), Normalize(D3DVECTOR(0.4f, 0.0f, -1.0f)), 0.5f, 0.0f);
	boid_vertices[14] = D3DVERTEX(D3DVECTOR(-3.0f, -3.0f, -7.0f), Normalize(D3DVECTOR(0.2f, 0.0f, -1.0f)), 0.575f, 0.425f);
	boid_vertices[15] = D3DVERTEX(D3DVECTOR(3.0f, -3.0f, -7.0f), Normalize(D3DVECTOR(-0.2f, 0.0f, -1.0f)), 0.575f, 0.575f);

	// top
	boid_indices[ 0] = 0;
	boid_indices[ 1] = 1;
	boid_indices[ 2] = 2;
	boid_indices[ 3] = 0;
	boid_indices[ 4] = 2;
	boid_indices[ 5] = 3;
	boid_indices[ 6] = 0;
	boid_indices[ 7] = 3;
	boid_indices[ 8] = 4;

	// bottom
	boid_indices[ 9] = 5;
	boid_indices[10] = 7;
	boid_indices[11] = 6;
	boid_indices[12] = 5;
	boid_indices[13] = 8;
	boid_indices[14] = 7;
	boid_indices[15] = 5;
	boid_indices[16] = 9;
	boid_indices[17] = 8;

	// rear
	boid_indices[18] = 10;
	boid_indices[19] = 15;
	boid_indices[20] = 11;
	boid_indices[21] = 11;
	boid_indices[22] = 15;
	boid_indices[23] = 12;
	boid_indices[24] = 12;
	boid_indices[25] = 15;
	boid_indices[26] = 14;
	boid_indices[27] = 12;
	boid_indices[28] = 14;
	boid_indices[29] = 13;

	// scale the boid to be unit length
	for (i=0; i<16; i++) {
		boid_vertices[i].x /= 20.0f;
		boid_vertices[i].y /= 20.0f;
		boid_vertices[i].z /= 20.0f;
	}

	// seed the random number generator
	srand(time(NULL));

	// allocate the flock
	if (!(flock.boids = (Boid *)malloc(NUM_BOIDS * sizeof(Boid)))) {
		return FALSE;
	}
	if (!(flock.dist = (float **)malloc(NUM_BOIDS * sizeof(float *)))) {
		return FALSE;
	}

	flock.num_boids = NUM_BOIDS;
	flock.goal = D3DVECTOR(0.0f, 0.0f, 0.0f);

	for (i=0; i<flock.num_boids; i++) {
		flock.boids[i].loc = D3DVECTOR(100.0f*(rnd()-rnd()), 10.0f*rnd(), 100.0f*(rnd()-rnd()));
		flock.boids[i].dir = Normalize(D3DVECTOR(rnd()-rnd(), rnd()-rnd(), rnd()-rnd()));
		flock.boids[i].yaw = flock.boids[i].pitch = flock.boids[i].roll = flock.boids[i].dyaw = 0.0f;
		flock.boids[i].speed = 0.1f;
		flock.boids[i].color = D3DVECTOR(rnd(), rnd(), rnd());
		flock.boids[i].color -= D3DVECTOR(Min(flock.boids[i].color));
		flock.boids[i].color /= Max(flock.boids[i].color);
		if (!(flock.dist[i] = (float *)malloc(NUM_BOIDS * sizeof(float)))) {
			return FALSE;
		}
	}

	flock.num_obs = 4;
	if (!(flock.obs = (Obstacle *)malloc(flock.num_obs * sizeof(Obstacle)))) {
		return FALSE;
	}
    flock.obs[0].loc = D3DVECTOR(100.0f, 10.0f, 0.0f);
    flock.obs[1].loc = D3DVECTOR(-100.0f, 10.0f, 0.0f);
    flock.obs[2].loc = D3DVECTOR(0.0f, 10.0f, 100.0f);
    flock.obs[3].loc = D3DVECTOR(0.0f, 10.0f, -100.0f);
	flock.obs[0].radius = 3.0f;
	flock.obs[1].radius = 3.0f;
	flock.obs[2].radius = 3.0f;
	flock.obs[3].radius = 3.0f;

	D3DCOLOR	diffuse = D3DRGB(grid_color[0], grid_color[1], grid_color[2]),
				specular = D3DRGB(0.0, 0.0, 0.0);

	pattern1[ 0] = D3DLVERTEX(D3DVECTOR(-25.0f, 0.0f, 35.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[ 1] = D3DLVERTEX(D3DVECTOR(-15.0f, 0.0f, 35.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[ 2] = D3DLVERTEX(D3DVECTOR(-5.0f, 0.0f, 25.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[ 3] = D3DLVERTEX(D3DVECTOR(5.0f, 0.0f, 25.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[ 4] = D3DLVERTEX(D3DVECTOR(15.0f, 0.0f, 35.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[ 5] = D3DLVERTEX(D3DVECTOR(25.0f, 0.0f, 35.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[ 6] = D3DLVERTEX(D3DVECTOR(35.0f, 0.0f, 25.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[ 7] = D3DLVERTEX(D3DVECTOR(35.0f, 0.0f, 15.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[ 8] = D3DLVERTEX(D3DVECTOR(25.0f, 0.0f, 5.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[ 9] = D3DLVERTEX(D3DVECTOR(25.0f, 0.0f, -5.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[10] = D3DLVERTEX(D3DVECTOR(35.0f, 0.0f, -15.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[11] = D3DLVERTEX(D3DVECTOR(35.0f, 0.0f, -25.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[12] = D3DLVERTEX(D3DVECTOR(25.0f, 0.0f, -35.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[13] = D3DLVERTEX(D3DVECTOR(15.0f, 0.0f,-35.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[14] = D3DLVERTEX(D3DVECTOR(5.0f, 0.0f, -25.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[15] = D3DLVERTEX(D3DVECTOR(-5.0f, 0.0f, -25.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[16] = D3DLVERTEX(D3DVECTOR(-15.0f, 0.0f,-35.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[17] = D3DLVERTEX(D3DVECTOR(-25.0f, 0.0f,-35.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[18] = D3DLVERTEX(D3DVECTOR(-35.0f, 0.0f, -25.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[19] = D3DLVERTEX(D3DVECTOR(-35.0f, 0.0f, -15.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[20] = D3DLVERTEX(D3DVECTOR(-25.0f, 0.0f, -5.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[21] = D3DLVERTEX(D3DVECTOR(-25.0f, 0.0f, 5.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[22] = D3DLVERTEX(D3DVECTOR(-35.0f, 0.0f, 15.0f), diffuse, specular, 0.0f, 0.0f);
	pattern1[23] = D3DLVERTEX(D3DVECTOR(-35.0f, 0.0f, 25.0f), diffuse, specular, 0.0f, 0.0f);

	pattern2[ 0] = D3DLVERTEX(D3DVECTOR(-5.0f, 0.0f, 15.0f), diffuse, specular, 0.0f, 0.0f);
	pattern2[ 1] = D3DLVERTEX(D3DVECTOR(5.0f, 0.0f, 15.0f), diffuse, specular, 0.0f, 0.0f);
	pattern2[ 2] = D3DLVERTEX(D3DVECTOR(15.0f, 0.0f, 5.0f), diffuse, specular, 0.0f, 0.0f);
	pattern2[ 3] = D3DLVERTEX(D3DVECTOR(15.0f, 0.0f, -5.0f), diffuse, specular, 0.0f, 0.0f);
	pattern2[ 4] = D3DLVERTEX(D3DVECTOR(5.0f, 0.0f, -15.0f), diffuse, specular, 0.0f, 0.0f);
	pattern2[ 5] = D3DLVERTEX(D3DVECTOR(-5.0f, 0.0f, -15.0f), diffuse, specular, 0.0f, 0.0f);
	pattern2[ 6] = D3DLVERTEX(D3DVECTOR(-15.0f, 0.0f, -5.0f), diffuse, specular, 0.0f, 0.0f);
	pattern2[ 7] = D3DLVERTEX(D3DVECTOR(-15.0f, 0.0f, 5.0f), diffuse, specular, 0.0f, 0.0f);

	float   dj = pi/(MESH_SIZE+1.0f);
	float	di = pi/MESH_SIZE;

	// generate the sphere data, note the random texture coords

	// vertices 0 and 1 are the north and south poles
	sphere[0] = D3DVERTEX(D3DVECTOR(0.0f, 1.0f, 0.0f), Normalize(D3DVECTOR(0.0f, 1.0f, 0.0f)), 0.0f, 0.0f);
	sphere[1] = D3DVERTEX(D3DVECTOR(0.0f, -1.0f, 0.0f), Normalize(D3DVECTOR(0.0f, -1.0f, 0.0f)), 1.0f, 1.0f);

	for (j=0; j<MESH_SIZE; j++) {
		for (i=0; i<MESH_SIZE*2; i++) {
			D3DVECTOR	p;
			float		u, v;

			p.y = (float) cos((j+1) * dj);
			p.x = (float) sin(i * di) * (float) sin((j+1) * dj);
			p.z = (float) cos(i * di) * (float) sin((j+1) * dj);
			u = (float)i/MESH_SIZE;
			if (u>1.0f) 
				u -= 1.0f;
			u = 1.0f - u;	// flip so texture is not mirrored
			v = (float)j/MESH_SIZE;
			sphere[2+i+j*MESH_SIZE*2] = D3DVERTEX(p, p, u, v);
		}
	}

	// now generate the traingle indices
	// strip around north pole first
	for (i=0; i<MESH_SIZE*2; i++) {
		sphere_indices[3*i] = 0;
		sphere_indices[3*i+1] = i+2;
		sphere_indices[3*i+2] = i+3;
		if (i==MESH_SIZE*2-1)
			sphere_indices[3*i+2] = 2;
	}

	// now all the middle strips
	int	v;		// vertex offset
	int ind;	// indices offset
	for (j=0; j<MESH_SIZE-1; j++) {
		v = 2+j*MESH_SIZE*2;
		ind = 3*MESH_SIZE*2 + j*6*MESH_SIZE*2;
		for (i=0; i<MESH_SIZE*2; i++) {
			sphere_indices[6*i+ind] = v+i;
			sphere_indices[6*i+2+ind] = v+i+1;
			sphere_indices[6*i+1+ind] = v+i+MESH_SIZE*2;

			sphere_indices[6*i+ind+3] = v+i+MESH_SIZE*2;
			sphere_indices[6*i+2+ind+3] = v+i+1;
			sphere_indices[6*i+1+ind+3] = v+i+MESH_SIZE*2+1;
			if (i==MESH_SIZE*2-1) {
				sphere_indices[6*i+2+ind] = v+i+1-2*MESH_SIZE;
				sphere_indices[6*i+2+ind+3] = v+i+1-2*MESH_SIZE;
				sphere_indices[6*i+1+ind+3] = v+i+MESH_SIZE*2+1-2*MESH_SIZE;
			}
		}
	}

	// finally strip around south pole
	v = SPHERE_VERTICES-MESH_SIZE*2;
	ind = SPHERE_INDICES-3*MESH_SIZE*2;
	for (i=0; i<MESH_SIZE*2; i++) {
		sphere_indices[3*i+ind] = 1;
		sphere_indices[3*i+1+ind] = v+i+1;
		sphere_indices[3*i+2+ind] = v+i;
		if (i==MESH_SIZE*2-1)
			sphere_indices[3*i+1+ind] = v;
	}

	// Success
    return D3D_OK;
} // End D3DScene::Init


  
/*
**-----------------------------------------------------------------------------
**  Name:       D3DScene::Fini
**  Purpose:	Cleanup scene objects
**-----------------------------------------------------------------------------
*/

HRESULT D3DScene::Fini(void)
{
	Detach();
	lpd3dWindow = NULL;

	// Success
	return D3D_OK;
} // End D3DScene::Fini



/*
**----------------------------------------------------------------------------
** Name:        D3DScene::Attach
** Purpose:		Attaching to a new D3DWindow object
** Notes:		Need to create and attach all Scene objects dependent upon
**				the D3D interface, viewport, and D3D device here.  
**				For Example:  Textures, Materials, Lights, etc.
**----------------------------------------------------------------------------
*/

HRESULT D3DScene::Attach(void)
{
	HRESULT hResult;

	// Check Initialization
	if ((! lpd3dWindow) || (! lpd3dWindow->isValid()))	{
		// Error, not properly initialized
		hResult = APPERR_NOTINITIALIZED;
		REPORTERR(hResult);
		return hResult;
	}

	hResult = AttachViewport();
	if (hResult != D3D_OK) {
		return hResult;
	}

	// Success
	return D3D_OK;
} // End D3DScene::Attach

  

/*
**-----------------------------------------------------------------------------
**  Name:       D3DScene::Detach
**  Purpose:	Cleanup all scene objects dependent upon the 
**				D3D Interface, viewport, or D3D device 
**-----------------------------------------------------------------------------
*/

HRESULT D3DScene::Detach(void)
{
	// Cleanup Viewport
	DetachViewport();

	// Success
	return D3D_OK;
} // End D3DScene::Fini




/*
**----------------------------------------------------------------------------
** Name:        D3DScene::Render
** Purpose:
**----------------------------------------------------------------------------
*/

HRESULT D3DScene::Render(void)
{
	LPDIRECT3DDEVICE2	lpDev;
	LPDIRECT3DVIEWPORT2 lpView;
	RECT				rSrc;
	LPD3DRECT			lpExtent = NULL;
	int					i;
	HRESULT				hResult;
	D3DCLIPSTATUS		status;
	D3DRECT				d3dRect;
	D3DVECTOR			offset;
	static D3DVECTOR	from(0.0f, 30.0f, 100.0f);
	static D3DVECTOR	at(0.0f, 0.0f, 50.0f);
	static D3DVECTOR	up(0.0f, 1.0f, 0.0f);
	static float		tic = -200.0f * rnd();

	// Check Initialization
	if ((! lpd3dWindow) || (! lpd3dWindow->isValid ()))	{
		// Error, not properly initialized
		hResult = APPERR_NOTINITIALIZED;
		REPORTERR(hResult);
		return hResult;
	}

	lpDev	= lpd3dWindow->lpd3dDevice;
	lpView  = lpd3dWindow->lpd3dViewport;
	lpd3dWindow->GetSurfaceRect(rSrc);

	// Double Check
#ifdef DEBUG
	if ((! lpDev) || (! lpView))
	{
		// Error, not initialized properly
		hResult = APPERR_NOTINITIALIZED;
		REPORTERR(hResult);
		return hResult;
	}
#endif
	
	
	//
    // Clear both back and z-buffer.
    //
    // NOTE: Its safe to specify the z-buffer clear flag even if we
    // don't have an attached z-buffer. Direct3D will simply discard
    // the flag if no z-buffer is being used.
    //
    // NOTE: For maximum efficiency we only want to clear those
    // regions of the device surface and z-buffer which we actually
    // rendered to in the last frame. This is the purpose of the
    // array of rectangles and count passed to this function. It is
    // possible to query Direct3D for the regions of the device
    // surface that were rendered to by that execute. The application
    // can then accumulate those rectangles and clear only those
    // regions. However this is a very simple sample and so, for
    // simplicity, we will just clear the entire device surface and
    // z-buffer. Probably not something you wan't to do in a real
    // application.
    ///
	d3dRect.lX1 = rSrc.left;
	d3dRect.lX2 = rSrc.right;
	d3dRect.lY1 = rSrc.top;
	d3dRect.lY2 = rSrc.bottom;
	hResult = lpView->Clear(1UL, &d3dRect,
							 D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);
	if (hResult != D3D_OK) {
		REPORTERR(hResult);
		return hResult;
	}	

	
	if (lpExtent) {
		// Calculate exclude region
		status.dwFlags = D3DCLIPSTATUS_EXTENTS2;
		status.dwStatus = 0;
		status.minx = (float)lpExtent->x1;
		status.maxx = (float)lpExtent->x2;
		status.miny = (float)lpExtent->y1;
		status.maxy = (float)lpExtent->y2;
		status.minz = 0.0f;
		status.maxz = 0.0f;

		hResult = lpDev->SetClipStatus(&status);
		if (hResult != D3D_OK) {
			REPORTERR(hResult);
			goto lblCLEANUP;
		}
	}

	// Begin Scene
	// Note:  This is complicated by the need to
	//		  check for lost surfaces and restore
	hResult = lpDev->BeginScene();
	if (hResult != D3D_OK) {
		while (hResult == DDERR_SURFACELOST) {
			// Restore surface
			while (hResult == DDERR_SURFACELOST) {
				hResult = lpd3dWindow->Restore();
			}

			// Try BeginScene again
			hResult = lpDev->BeginScene();
		}

		if (hResult != D3D_OK) {
			REPORTERR(hResult);
			return hResult;
		}
	}

    // Turn off specular highlights
        hResult = lpDev->SetRenderState(D3DRENDERSTATE_SPECULARENABLE, FALSE);
	if (hResult != D3D_OK) {
        REPORTERR(hResult);
		goto lblCLEANUP;
	}

    // Turn on Z-buffering
	hResult = lpDev->SetRenderState(D3DRENDERSTATE_ZENABLE, 1);
	if (hResult != D3D_OK) {
        REPORTERR(hResult);
		goto lblCLEANUP;
	}

	// null out the texture handle
    hResult = lpDev->SetRenderState(D3DRENDERSTATE_TEXTUREHANDLE, 0);
    if (hResult != D3D_OK) {
        REPORTERR(hResult);
		goto lblCLEANUP;
	}

	// turn on dithering
    hResult = lpDev->SetRenderState(D3DRENDERSTATE_DITHERENABLE, TRUE);
    if (hResult != D3D_OK) {
        REPORTERR(hResult);
		goto lblCLEANUP;
	}

	// turn on some ambient light
    hResult = lpDev->SetLightState(D3DLIGHTSTATE_AMBIENT, RGBA_MAKE(10, 10, 10, 10));
    if (hResult != D3D_OK) {
        REPORTERR(hResult);
		goto lblCLEANUP;
	}

	// set the view and projection matrices

	tic += 0.01f;

	view = ViewMatrix(from, at, up);
	proj = ProjectionMatrix(1.0f, 500.0f, pi/4.0f);

	hResult = lpDev->SetTransform(D3DTRANSFORMSTATE_VIEW, &view);
    if (hResult != D3D_OK) {
        REPORTERR(hResult);
		goto lblCLEANUP;
	}

	hResult = lpDev->SetTransform(D3DTRANSFORMSTATE_PROJECTION, &proj);
    if (hResult != D3D_OK) {
        REPORTERR(hResult);
		goto lblCLEANUP;
	}

	// draw ground grid
	lpGridMat->SetAsCurrent(lpDev);
	hResult = DrawPattern(lpDev);
    if (hResult != D3D_OK) {
        REPORTERR(hResult);
		goto lblCLEANUP;
	}


	UpdateFlock(flock);

	at = D3DVECTOR(0.0f);
	// draw the boids
	for (i=0; i<flock.num_boids; i++) {
		D3DVECTOR	step;

		// build the world matrix for the boid
		world = MatrixMult(MatrixMult(RotateYMatrix(flock.boids[i].yaw), RotateXMatrix(flock.boids[i].pitch)), RotateZMatrix(flock.boids[i].roll));

		// first translate into place, then set orientation, then scale (if needed)
		world = TranslateMatrix(flock.boids[i].loc);
		world = MatrixMult(world, MatrixMult(MatrixMult(RotateYMatrix(flock.boids[i].yaw), 
							RotateXMatrix(flock.boids[i].pitch)), RotateZMatrix(flock.boids[i].roll)));

		// apply the world matrix
		hResult = lpDev->SetTransform(D3DTRANSFORMSTATE_WORLD, &world);
		if (hResult != D3D_OK) {
			REPORTERR(hResult);
			goto lblCLEANUP;
		}

		// display the boid
		lpBoidMat->SetDiffuse(flock.boids[i].color);
		lpBoidMat->SetAsCurrent(lpDev);
		hResult = Drawboid(lpDev);
		if (hResult != D3D_OK) {
			REPORTERR(hResult);
			goto lblCLEANUP;
		}

		flock.boids[i].dir[0] = world(2, 0);
		flock.boids[i].dir[1] = world(2, 1);
		flock.boids[i].dir[2] = world(2, 2);

		flock.boids[i].loc += flock.boids[i].dir * flock.boids[i].speed;

		at += flock.boids[i].loc;
	}
	// find the center of the flock and look there for the next frame
	at /= (float)(flock.num_boids);
	from = at + D3DVECTOR(20.0f * (float)sin (tic* 0.223f), 
		                   16.0f + 15.0f * (float)sin (tic * 0.33f), 
						   20.0f * (float)cos (tic * 0.31f));

	flock.goal = D3DVECTOR(105.0f * (float)sin (tic * 0.1f), 
							10.0f, 
							105.0f * (float)cos (tic * 0.1f));



	// Finally, draw obstacles last since they're transparent.
	// Set renderstates to support blending such that the texture
	// color is added over the background color.  Also turn Z-write
	// off so when two spheres line up you can always see them both.
    if (lpDev->SetRenderState(D3DRENDERSTATE_BLENDENABLE, TRUE) != D3D_OK)
        return FALSE;
   	if (lpDev->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_SRCCOLOR) != D3D_OK)
        return FALSE;
    if (lpDev->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ONE) != D3D_OK)
		return FALSE;
    if (lpDev->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, FALSE) != D3D_OK)
		return FALSE;
	// make sure the texture wraps correctly
    if (lpDev->SetRenderState(D3DRENDERSTATE_WRAPU, TRUE) != D3D_OK)
		return FALSE;
	
	lpSphereMat->SetAsCurrent(lpDev);
	for (i=0; i<flock.num_obs; i++) {
		world = MatrixMult(TranslateMatrix(flock.obs[i].loc), MatrixMult(RotateYMatrix(-tic*pi), ScaleMatrix (flock.obs[i].radius)));
		
		hResult = lpDev->SetTransform(D3DTRANSFORMSTATE_WORLD, &world);
		if (hResult != D3D_OK) {
			REPORTERR(hResult);
			return hResult;
		}

		hResult = DrawSphere(lpDev);
		if (hResult != D3D_OK) {
			REPORTERR(hResult);
			goto lblCLEANUP;
		}
	}

	// set renderstates back to default
    if (lpDev->SetRenderState(D3DRENDERSTATE_BLENDENABLE, FALSE) != D3D_OK)
        return FALSE;
    if (lpDev->SetRenderState(D3DRENDERSTATE_SRCBLEND, D3DBLEND_ONE) != D3D_OK)
        return FALSE;
    if (lpDev->SetRenderState(D3DRENDERSTATE_DESTBLEND, D3DBLEND_ZERO) != D3D_OK)
		return FALSE;
    if (lpDev->SetRenderState(D3DRENDERSTATE_ZWRITEENABLE, TRUE) != D3D_OK)
		return FALSE;


lblCLEANUP: 
	// End Scene
	// Note:  This is complicated by the need to restore lost surfaces
    hResult = lpDev->EndScene();
	if (hResult != D3D_OK) {
		while (hResult == DDERR_SURFACELOST) {
			// Restore surface
			while (hResult == DDERR_SURFACELOST) {
				hResult = lpd3dWindow->Restore();
			}

			// Try EndScene again
			hResult = lpDev->EndScene();
		}

		if (hResult != D3D_OK) {
			REPORTERR(hResult);
			return hResult;
		}
	}

	if (lpExtent) {
		hResult = lpDev->GetClipStatus(&status);
		if (hResult != D3D_OK) {
			REPORTERR(hResult);
			return hResult;
		}

		if (status.dwFlags & D3DCLIPSTATUS_EXTENTS2) {
			lpExtent->x1 = (long) floor((double)status.minx);
			lpExtent->x2 = (long) ceil((double)status.maxx);
			lpExtent->y1 = (long) floor((double)status.miny);
			lpExtent->y2 = (long) ceil((double)status.maxy);
		}
	}
		
	return hResult;
} // End D3DScene::Render


  
/*
**----------------------------------------------------------------------------
** Name:        D3DScene::Restore
** Purpose:     Restore any scene specific surfaces that might have been
**				lost on a DDERR_LOSTSURFACE message
**----------------------------------------------------------------------------
*/

HRESULT D3DScene::Restore(void)
{
	// Nothing to do for now

	// Success
	return D3D_OK;
} // End D3DScene::Restore


  
/*
**----------------------------------------------------------------------------
** Name:        D3DScene::AttachViewport
** Purpose:
**----------------------------------------------------------------------------
*/

HRESULT
D3DScene::AttachViewport(void)
{
	LPDIRECT3D2				lpD3D;
	LPDIRECT3DDEVICE2		lpDev;
	LPDIRECT3DVIEWPORT2   	lpView;

	// Check Initialization
	if ((! lpd3dWindow) || (! lpd3dWindow->isValid())) {
		// Error,
		REPORTERR(DDERR_GENERIC);
		return DDERR_GENERIC;
	}

	lpD3D  = lpd3dWindow->lpD3D;
	lpDev  = lpd3dWindow->lpd3dDevice;
	lpView = lpd3dWindow->lpd3dViewport;

	if ((! lpD3D) || (! lpDev) || (! lpView)) {
		REPORTERR(DDERR_GENERIC);
		return DDERR_GENERIC;
	}

	// Create and set up the background material
	lpBackgroundMat = new Material(lpD3D, lpDev);
	lpBackgroundMat->SetDiffuse(D3DVECTOR(0.0f, 0.05f, 0.1f));
	lpBackgroundMat->SetAsBackground(lpView);

	// Create and set up the grid material, since we're using LVertices we want
	// to make sure that ramp mode can actually get the right colors so we set
	// the emissive value to the color we want and choose a small ramp size
	lpGridMat = new Material(lpD3D, lpDev);
	lpGridMat->SetEmissive(grid_color);
	lpGridMat->SetRampSize(2);

	// Create and set up the sphere material
	lpSphereMat = new Material(lpD3D, lpDev);
	lpSphereMat->SetDiffuse(D3DVECTOR(1.0f));

	// Create the sphere texture and attatch it to the material
	SphereTex.Load(lpDev, "DX5_logo");
	lpSphereMat->SetTextureHandle(SphereTex.GetHandle());

	// Create and set up the boid material
	// note that we'll just change the color for each boid we render
	lpBoidMat = new Material(lpD3D, lpDev);
	lpBoidMat->SetDiffuse(D3DVECTOR(1.0f));

	// set up transform matrices
	D3DVECTOR	from(0.0f, 0.0f, -100.0f);
	D3DVECTOR	at(0.0f, 0.0f, 0.0f);
	D3DVECTOR	up(0.0f, 1.0f, 0.0f);

	view = ViewMatrix(from, at, up);
	proj = ProjectionMatrix(1.0f, 400.0f, pi/4.0f);
	world = IdentityMatrix();

	// create 2 lights
	D3DVECTOR	color(1.0f, 1.0f, 1.0f);
	D3DVECTOR	direction(-0.5f, -1.0f, -0.3f);

	lpLight1 = new DirectionalLight(lpD3D, color, Normalize(direction));
	if (lpLight1) {
		lpLight1->AddToViewport(lpView);
	}

	lpLight2 = new DirectionalLight(lpD3D, color/2.0f, -Normalize(direction));
	if (lpLight2) {
		lpLight2->AddToViewport(lpView);
	}

	// Success
    return D3D_OK;
} // End D3DScene::AttachViewport

	

/*
**-----------------------------------------------------------------------------
**  Name:       D3DScene::DetachViewport
**  Purpose:	Cleanup Viewport
**-----------------------------------------------------------------------------
*/

HRESULT D3DScene::DetachViewport(void)
{
	LPDIRECT3DVIEWPORT2 lpViewport = NULL;

	if (lpd3dWindow) {
		lpViewport = lpd3dWindow->GetViewport();
	}

	// Cleanup lights
	if (lpLight1) {
		if (lpViewport) {
			lpLight1->RemoveFromViewport(lpViewport);
		}

	    delete lpLight1;
		lpLight1 = NULL;
	}

	if (lpLight2) {
		if (lpViewport) {
			lpLight2->RemoveFromViewport(lpViewport);
		}

		delete lpLight2;
		lpLight2 = NULL;
	}

	// Cleanup Materials
	delete lpBackgroundMat;
	delete lpGridMat;
	delete lpSphereMat;
	delete lpBoidMat;

	lpBackgroundMat = NULL;
	lpGridMat = NULL;
	lpSphereMat = NULL;
	lpBoidMat = NULL;

	SphereTex.Release();

	// Success
	return D3D_OK;
} // End D3DScene::DetachViewport


  
/*
**----------------------------------------------------------------------------
** End of File
**----------------------------------------------------------------------------
*/

