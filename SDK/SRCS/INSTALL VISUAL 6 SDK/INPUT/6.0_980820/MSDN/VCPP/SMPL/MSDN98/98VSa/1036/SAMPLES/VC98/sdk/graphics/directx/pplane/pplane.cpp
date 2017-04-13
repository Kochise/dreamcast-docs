/*
**-----------------------------------------------------------------------------
**  File:       PPlane.cpp
**  Purpose:    Paper plane demo
**  Notes:		Sample demonstrating D3DLVERTEX's, DrawPrimitive, 
**				and SetTransform
**
** Copyright (c) 1995 - 1997 by Microsoft, all rights reserved
**-----------------------------------------------------------------------------
*/

/*
**-----------------------------------------------------------------------------
**	Include files
**-----------------------------------------------------------------------------
*/

#include "Common.h"
#include "Debug.h"
#include "D3DScene.h"
#include <time.h>
#include "d3dutils.h"
#include "pplane.h"



/*
**-----------------------------------------------------------------------------
**	Local variables
**-----------------------------------------------------------------------------
*/

LPDIRECT3DMATERIAL2 g_lpmatBackground, g_lpMat;

extern const float pi;

//#define POINT_LINE_TEST
#define GROUND_GRID
DWORD		g_hBackTex;
DWORD		g_hTex;
DWORD		g_hBackMat;
DWORD		g_hMat;

#define NUM_PLANES		42
Plane	planes[NUM_PLANES];

#define PPLANE_VERTICES	36
#define PPLANE_INDICES	60
D3DVERTEX	pplane[PPLANE_VERTICES];
WORD		pplane_indices[PPLANE_INDICES];

#ifdef GROUND_GRID
	#define NUM_GRID	22
	#define GRID_WIDTH	800.0f
	D3DVERTEX	grid[NUM_GRID*NUM_GRID];
#endif

#ifdef POINT_LINE_TEST
	#define LOTS_OF_POINTS	(222)
	D3DVERTEX	points[LOTS_OF_POINTS];
#endif


D3DMATRIX		g_proj, g_view, g_world;	// Matrices

D3DLIGHT		g_light;		// Structure defining the light
LPDIRECT3DLIGHT	g_lpD3DLight;	// Object pointer for the light


								
/*
**-----------------------------------------------------------------------------
**	Local prototypes
**-----------------------------------------------------------------------------
*/




/*
**-----------------------------------------------------------------------------
**	D3DScene Methods
**-----------------------------------------------------------------------------
*/

/*
**----------------------------------------------------------------------------
** Name:        D3DScene::D3DScene
** Purpose:		Default Constructor
**----------------------------------------------------------------------------
*/

D3DScene::D3DScene (void)
{
	lpd3dWindow = NULL;
} // End D3DScene::D3DScene


  
/*
**----------------------------------------------------------------------------
** Name:        D3DScene::~D3DScene
** Purpose:		Default Destructor
**----------------------------------------------------------------------------
*/

D3DScene::~D3DScene (void)
{
	Fini ();
	lpd3dWindow = NULL;
} // End D3DScene::~D3DScene


							
/*
**-----------------------------------------------------------------------------
**  Name:       DrawPPlane
**  Purpose:	Draws a single Paper plane
**-----------------------------------------------------------------------------
*/

HRESULT
DrawPPlane (LPDIRECT3DDEVICE2 lpDev)
{
	HRESULT hResult;

#ifdef POINT_LINE_TEST
        hResult = lpDev->DrawPrimitive (D3DPT_LINESTRIP, D3DVT_VERTEX, (LPVOID)points, LOTS_OF_POINTS, D3DDP_WAIT);
    if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
	}
#endif

        hResult =lpDev->DrawIndexedPrimitive (D3DPT_TRIANGLELIST, D3DVT_VERTEX, (LPVOID)pplane, PPLANE_VERTICES, pplane_indices, PPLANE_INDICES, D3DDP_WAIT);
    if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
	}

	// Success
	return hResult;
}


/*
**-----------------------------------------------------------------------------
**  Name:       D3DWindow::Init
**  Purpose:	Initialize scene objects
**-----------------------------------------------------------------------------
*/

HRESULT D3DScene::Init (LPD3DWindow lpd3dWin)
{
	HRESULT hResult;

	// Check Parameters
	if (! lpd3dWin)
	{
		REPORTERR (DDERR_INVALIDPARAMS);
		return DDERR_INVALIDPARAMS;
	}

	// Save pointer to D3D Window
	lpd3dWindow = lpd3dWin;


	//
	// generate the paper plane data
	//

	// right wing top
	pplane[ 0] = D3DVERTEX(D3DVECTOR(0.125f, 0.03125f, 3.5f), Normalize(D3DVECTOR(-0.25f, 1.0f, 0.0f)), rnd(), rnd());
	pplane[ 1] = D3DVERTEX(D3DVECTOR(0.75f, 0.1875f, 3.25f), Normalize(D3DVECTOR(-0.25f, 1.0f, 0.0f)), rnd(), rnd());
	pplane[ 2] = D3DVERTEX(D3DVECTOR(2.75f, 0.6875f, -2.0f), Normalize(D3DVECTOR(-0.25f, 1.0f, 0.0f)), rnd(), rnd());
	pplane[ 3] = D3DVERTEX(D3DVECTOR(2.0f, 0.5f, -4.25f), Normalize(D3DVECTOR(-0.25f, 1.0f, 0.0f)), rnd(), rnd());
	pplane[ 4] = D3DVERTEX(D3DVECTOR(0.5f, 0.125f, -3.5f), Normalize(D3DVECTOR(-0.25f, 1.0f, 0.0f)), rnd(), rnd());

	// right wing bottom
	pplane[ 5] = D3DVERTEX(D3DVECTOR(0.125f, 0.03125f, 3.5f), Normalize(D3DVECTOR(0.25f, -1.0f, 0.0f)), rnd(), rnd());
	pplane[ 6] = D3DVERTEX(D3DVECTOR(0.75f, 0.1875f, 3.25f), Normalize(D3DVECTOR(0.25f, -1.0f, 0.0f)), rnd(), rnd());
	pplane[ 7] = D3DVERTEX(D3DVECTOR(2.75f, 0.6875f, -2.0f), Normalize(D3DVECTOR(0.25f, -1.0f, 0.0f)), rnd(), rnd());
	pplane[ 8] = D3DVERTEX(D3DVECTOR(2.0f, 0.5f, -4.25f), Normalize(D3DVECTOR(0.25f, -1.0f, 0.0f)), rnd(), rnd());
	pplane[ 9] = D3DVERTEX(D3DVECTOR(0.5f, 0.125f, -3.5f), Normalize(D3DVECTOR(0.25f, -1.0f, 0.0f)), rnd(), rnd());

	// left wing bottom
	pplane[10] = D3DVERTEX(D3DVECTOR(-0.125f, 0.03125f, 3.5f), Normalize(D3DVECTOR(-0.25f, -1.0f, 0.0f)), rnd(), rnd());
	pplane[11] = D3DVERTEX(D3DVECTOR(-0.75f, 0.1875f, 3.25f), Normalize(D3DVECTOR(-0.25f, -1.0f, 0.0f)), rnd(), rnd());
	pplane[12] = D3DVERTEX(D3DVECTOR(-2.75f, 0.6875f, -2.0f), Normalize(D3DVECTOR(-0.25f, -1.0f, 0.0f)), rnd(), rnd());
	pplane[13] = D3DVERTEX(D3DVECTOR(-2.0f, 0.5f, -4.25f), Normalize(D3DVECTOR(-0.25f, -1.0f, 0.0f)), rnd(), rnd());
	pplane[14] = D3DVERTEX(D3DVECTOR(-0.5f, 0.125f, -3.5f), Normalize(D3DVECTOR(-0.25f, -1.0f, 0.0f)), rnd(), rnd());

	// left wing top
	pplane[15] = D3DVERTEX(D3DVECTOR(-0.125f, 0.03125f, 3.5f), Normalize(D3DVECTOR(0.25f, 1.0f, 0.0f)), rnd(), rnd());
	pplane[16] = D3DVERTEX(D3DVECTOR(-0.75f, 0.1875f, 3.25f), Normalize(D3DVECTOR(0.25f, 1.0f, 0.0f)), rnd(), rnd());
	pplane[17] = D3DVERTEX(D3DVECTOR(-2.75f, 0.6875f, -2.0f), Normalize(D3DVECTOR(0.25f, 1.0f, 0.0f)), rnd(), rnd());
	pplane[18] = D3DVERTEX(D3DVECTOR(-2.0f, 0.5f, -4.25f), Normalize(D3DVECTOR(0.25f, 1.0f, 0.0f)), rnd(), rnd());
	pplane[19] = D3DVERTEX(D3DVECTOR(-0.5f, 0.125f, -3.5f), Normalize(D3DVECTOR(0.25f, 1.0f, 0.0f)), rnd(), rnd());
	
	// right body outside
	pplane[20] = D3DVERTEX(D3DVECTOR(0.125f, 0.03125f, 3.5f), Normalize(D3DVECTOR(1.0f, -0.1f, 0.0f)), rnd(), rnd());
	pplane[21] = D3DVERTEX(D3DVECTOR(0.5f, 0.125f, -3.5f), Normalize(D3DVECTOR(1.0f, -0.1f, 0.0f)), rnd(), rnd());
	pplane[22] = D3DVERTEX(D3DVECTOR(0.0f, -2.25f, -2.75f), Normalize(D3DVECTOR(1.0f, -0.1f, 0.0f)), rnd(), rnd());
	pplane[23] = D3DVERTEX(D3DVECTOR(0.0f, -0.5f, 3.625f), Normalize(D3DVECTOR(1.0f, -0.1f, 0.0f)), rnd(), rnd());

	// right body inside
	pplane[24] = D3DVERTEX(D3DVECTOR(0.125f, 0.03125f, 3.5f), Normalize(D3DVECTOR(-1.0f, 0.1f, 0.0f)), rnd(), rnd());
	pplane[25] = D3DVERTEX(D3DVECTOR(0.5f, 0.125f, -3.5f), Normalize(D3DVECTOR(-1.0f, 0.1f, 0.0f)), rnd(), rnd());
	pplane[26] = D3DVERTEX(D3DVECTOR(0.0f, -2.25f, -2.75f), Normalize(D3DVECTOR(-1.0f, 0.1f, 0.0f)), rnd(), rnd());
	pplane[27] = D3DVERTEX(D3DVECTOR(0.0f, -0.5f, 3.625f), Normalize(D3DVECTOR(-1.0f, 0.1f, 0.0f)), rnd(), rnd());

	// left body outside
	pplane[28] = D3DVERTEX(D3DVECTOR(-0.125f, 0.03125f, 3.5f), Normalize(D3DVECTOR(-1.0f, -0.1f, 0.0f)), rnd(), rnd());
	pplane[29] = D3DVERTEX(D3DVECTOR(-0.5f, 0.125f, -3.5f), Normalize(D3DVECTOR(-1.0f, -0.1f, 0.0f)), rnd(), rnd());
	pplane[30] = D3DVERTEX(D3DVECTOR(0.0f, -2.25f, -2.75f), Normalize(D3DVECTOR(-1.0f, -0.1f, 0.0f)), rnd(), rnd());
	pplane[31] = D3DVERTEX(D3DVECTOR(0.0f, -0.5f, 3.625f), Normalize(D3DVECTOR(-1.0f, -0.1f, 0.0f)), rnd(), rnd());

	// left body inside
	pplane[32] = D3DVERTEX(D3DVECTOR(-0.125f, 0.03125f, 3.5f), Normalize(D3DVECTOR(1.0f, 0.1f, 0.0f)), rnd(), rnd());
	pplane[33] = D3DVERTEX(D3DVECTOR(-0.5f, 0.125f, -3.5f), Normalize(D3DVECTOR(1.0f, 0.1f, 0.0f)), rnd(), rnd());
	pplane[34] = D3DVERTEX(D3DVECTOR(0.0f, -2.25f, -2.75f), Normalize(D3DVECTOR(1.0f, 0.1f, 0.0f)), rnd(), rnd());
	pplane[35] = D3DVERTEX(D3DVECTOR(0.0f, -0.5f, 3.625f), Normalize(D3DVECTOR(1.0f, 0.1f, 0.0f)), rnd(), rnd());

	// right wing top
	pplane_indices[ 0] = 0;
	pplane_indices[ 1] = 1;
	pplane_indices[ 2] = 4;
	pplane_indices[ 3] = 1;
	pplane_indices[ 4] = 2;
	pplane_indices[ 5] = 4;
	pplane_indices[ 6] = 4;
	pplane_indices[ 7] = 2;
	pplane_indices[ 8] = 3;

	// right wing bottom
	pplane_indices[ 9] = 5;
	pplane_indices[10] = 9;
	pplane_indices[11] = 6;
	pplane_indices[12] = 6;
	pplane_indices[13] = 9;
	pplane_indices[14] = 7;
	pplane_indices[15] = 7;
	pplane_indices[16] = 9;
	pplane_indices[17] = 8;

	// left wing top
	pplane_indices[18] = 10;
	pplane_indices[19] = 11;
	pplane_indices[20] = 14;
	pplane_indices[21] = 11;
	pplane_indices[22] = 12;
	pplane_indices[23] = 14;
	pplane_indices[24] = 14;
	pplane_indices[25] = 12;
	pplane_indices[26] = 13;

	// left wing bottom
	pplane_indices[27] = 15;
	pplane_indices[28] = 19;
	pplane_indices[29] = 16;
	pplane_indices[30] = 16;
	pplane_indices[31] = 19;
	pplane_indices[32] = 17;
	pplane_indices[33] = 17;
	pplane_indices[34] = 19;
	pplane_indices[35] = 18;

	// right body outside
	pplane_indices[36] = 20;
	pplane_indices[37] = 23;
	pplane_indices[38] = 21;
	pplane_indices[39] = 21;
	pplane_indices[40] = 23;
	pplane_indices[41] = 22;

	// right body inside
	pplane_indices[42] = 24;
	pplane_indices[43] = 25;
	pplane_indices[44] = 27;
	pplane_indices[45] = 25;
	pplane_indices[46] = 26;
	pplane_indices[47] = 27;

	// left body outside
	pplane_indices[48] = 28;
	pplane_indices[49] = 29;
	pplane_indices[50] = 31;
	pplane_indices[51] = 29;
	pplane_indices[52] = 30;
	pplane_indices[53] = 31;

	// left body inside
	pplane_indices[54] = 32;
	pplane_indices[55] = 35;
	pplane_indices[56] = 33;
	pplane_indices[57] = 33;
	pplane_indices[58] = 35;
	pplane_indices[59] = 34;

	// seed the random number generator
	srand (time (0));

	for (int i=0; i<NUM_PLANES; i++) 
	{
		planes[i].loc = D3DVECTOR(0.0f, 0.0f, 0.0f);
		planes[i].goal = D3DVECTOR(10.0f*(rnd()-rnd()), 10.0f*(rnd()-rnd()), 10.0f*(rnd()-rnd()));
		planes[i].delta = D3DVECTOR(0.0f, 0.0f, 1.0f);
		planes[i].yaw = 0.0f;
		planes[i].pitch = 0.0f;
		planes[i].roll = 0.0f;
		planes[i].dyaw = 0.0f;
	}


#ifdef POINT_LINE_TEST
	for (i=0; i<LOTS_OF_POINTS; i++) 
	{
		float y = cos(pi*(double)i/LOTS_OF_POINTS);
		float x = (float)sin (pi*20.0*(double)i/LOTS_OF_POINTS) * (1.0f-y*y);
		float z = (float)cos (pi*20.0*(double)i/LOTS_OF_POINTS) * (1.0f-y*y);
		D3DVECTOR	p(x, y, z);

		p = Normalize (p);
		points[i] = _D3DVERTEX(10.0*p, p, rnd(), rnd());
	}
#endif

#ifdef GROUND_GRID
	float	size = GRID_WIDTH/(NUM_GRID-1.0f);
	float	offset = GRID_WIDTH/2.0f;
	for (i=0; i<NUM_GRID; i++) 
	{
		for (int j=0; j<NUM_GRID; j++) 
		{
			grid[j+i*NUM_GRID] = D3DVERTEX(D3DVECTOR(i*size-offset, 0.0f, j*size-offset), Normalize(D3DVECTOR(0.0f, 1.0f, 0.0f)), 0.0f, 0.0f);
		}
	}
#endif

	// Initialize Viewport
	hResult = InitViewport ();
	if (FAILED (hResult))
		return hResult;

    return DD_OK;
} // End D3DScene::Init



/*
**-----------------------------------------------------------------------------
**  Name:       D3DScene::Fini
**  Purpose:	Cleanup scene objects
**-----------------------------------------------------------------------------
*/

HRESULT D3DScene::Fini (void)
{
	FiniViewport ();

	// Success
	return DD_OK;
} // End D3DScene::Fini


  
/*
**-----------------------------------------------------------------------------
**  Name:       D3DScene::Render
**  Purpose:	Draws scene
**-----------------------------------------------------------------------------
*/

HRESULT D3DScene::Render (void)
{
	LPDIRECT3DDEVICE2	lpDev;
	LPDIRECT3DVIEWPORT2 lpView; 	
	RECT				rSrc;
	LPD3DRECT			lpExtent = NULL;
    D3DRECT				d3dRect;
	D3DCLIPSTATUS		status;
	HRESULT				hResult;

	// Check Initialization
	if ((! lpd3dWindow) || (! lpd3dWindow->isValid ()))
	{
		// Error,
		REPORTERR (DDERR_GENERIC);
		return DDERR_GENERIC;
	}

	lpDev	= lpd3dWindow->lpd3dDevice;
	lpView  = lpd3dWindow->lpd3dViewport;
	lpd3dWindow->GetSrcRect (rSrc);

    
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
	hResult = lpView->Clear (1UL, &d3dRect,
							 D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER);
	if (FAILED (hResult))
	{
		REPORTERR (hResult);
		return hResult;
	}

	// Calculate exclude region
	if (lpExtent)
	{
		status.dwFlags = D3DCLIPSTATUS_EXTENTS2;
		status.dwStatus = 0;
		status.minx = (float)lpExtent->x1;
		status.maxx = (float)lpExtent->x2;
		status.miny = (float)lpExtent->y1;
		status.maxy = (float)lpExtent->y2;
		status.minz = 0.0f;
		status.maxz = 0.0f;
	}

	hResult = lpDev->BeginScene ();
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
	}

	// Exclude text region
	if (lpExtent)
	{
		hResult = lpDev->SetClipStatus (&status);
		if (FAILED (hResult))
		{
	        REPORTERR (hResult);
			return hResult;
		}
	}

    hResult = lpDev->SetLightState (D3DLIGHTSTATE_MATERIAL, g_hMat);
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
	}

    hResult = lpDev->SetRenderState (D3DRENDERSTATE_ZENABLE, 1);
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
	}

    hResult = lpDev->SetRenderState (D3DRENDERSTATE_TEXTUREHANDLE, 0);
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
	}

	// turn on some ambient light
    hResult = lpDev->SetLightState (D3DLIGHTSTATE_AMBIENT, RGBA_MAKE(60, 60, 60, 60));
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
	}

	// set the projection matrix
	g_proj = ProjectionMatrix (10.0f, 500.0f, pi/2.0f);
	hResult = lpDev->SetTransform (D3DTRANSFORMSTATE_PROJECTION, &g_proj);
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
	}
	
	// play with planes
	static float		tic = 0.0f;
	static float		speed=2.0f;
	static float		angle_tweak = 0.02f;
	static D3DVECTOR	z_ward(0.0f, 0.0f, 1.0f);

	for (int i=0; i<NUM_PLANES; i++) 
	{
		D3DVECTOR	offset;

		// tweek orientation based on last position and goal
		offset = planes[i].goal - planes[i].loc;

		// first, tweak the pitch
		if (offset.y > 1.0) {			// we're too low
			planes[i].pitch += angle_tweak;
			if (planes[i].pitch > 0.8f)
				planes[i].pitch = 0.8f;
		} else if (offset.y < -1.0) {	// we're too high
			planes[i].pitch -= angle_tweak;
			if (planes[i].pitch < -0.8f)
				planes[i].pitch = -0.8f;
		} else {
			// add damping
			planes[i].pitch *= 0.95f;
		}

		// now figure out yaw changes
		offset.y = 0.0f;  planes[i].delta.y = 0.0f;
		planes[i].delta = Normalize (planes[i].delta);
		offset = Normalize (offset);
		float	dot = DotProduct (offset, planes[i].delta);
		offset = CrossProduct (offset, planes[i].delta);
		dot = (1.0f-dot)/2.0f * angle_tweak * 10.0f;
		if (offset.y > 0.01) {
			planes[i].dyaw = (planes[i].dyaw*9.0f + dot) * 0.1f;
		} else if (offset.y < 0.01) {
			planes[i].dyaw = (planes[i].dyaw*9.0f - dot) * 0.1f;
		}
		planes[i].yaw += planes[i].dyaw;
		planes[i].roll = -planes[i].dyaw * 9.0f;

		if (rnd() < 0.03) 
		{
			planes[i].goal = D3DVECTOR(60.0f*(rnd()-rnd()), 60.0f*(rnd()-rnd()), rnd()*300.0f - 100.0f);
		}

		// build the world matrix for the pplane
		g_world = MatrixMult (MatrixMult (RotateYMatrix (planes[i].yaw), RotateXMatrix (planes[i].pitch)), RotateZMatrix (planes[i].roll));
		
		// get delta buy grabbing the z axis out of the transform
		planes[i].delta[0] = g_world(2, 0);
		planes[i].delta[1] = g_world(2, 1);
		planes[i].delta[2] = g_world(2, 2);
		// update position
		planes[i].loc += speed * planes[i].delta;

		// before we draw the first plane use it's position to update the camera
		if (i==0) 
		{
			D3DVECTOR	from, at, local_up;
			D3DVECTOR	up(0.0f, 1.0f, 0.0f);

			local_up[0] = g_world(1, 0);
			local_up[1] = g_world(1, 1);
			local_up[2] = g_world(1, 2);
			from = planes[0].loc - 20.0f * planes[0].delta + 6.0f * local_up;
			at = planes[0].loc + planes[0].delta;

			g_view = ViewMatrix (from, at, up, planes[0].roll);
			hResult = lpDev->SetTransform (D3DTRANSFORMSTATE_VIEW, &g_view);
			if (FAILED (hResult))
			{
				REPORTERR (hResult);
				return hResult;
			}
		}

		// first translate into place, then set orientation, then scale
		g_world = TranslateMatrix (planes[i].loc);
		g_world = MatrixMult (g_world, MatrixMult (MatrixMult (RotateYMatrix (planes[i].yaw), RotateXMatrix (planes[i].pitch)), RotateZMatrix (planes[i].roll)));
		//g_world = MatrixMult (g_world, Scale(5.0f));
		
		// apply the world matrix
		hResult = lpDev->SetTransform (D3DTRANSFORMSTATE_WORLD, &g_world);
		if (FAILED (hResult))
		{
		    REPORTERR (hResult);
			return hResult;
		}

		// display the pplane
		DrawPPlane (lpDev);
	}	// end of loop for each pplane

#ifdef GROUND_GRID
	g_world = TranslateMatrix (0.0f, -60.0f, 0.0f);
	hResult = lpDev->SetTransform (D3DTRANSFORMSTATE_WORLD, &g_world);
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
	}

        hResult = lpDev->DrawPrimitive (D3DPT_LINELIST, D3DVT_VERTEX, (LPVOID)grid, NUM_GRID*NUM_GRID, D3DDP_WAIT);
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
	}

	g_world = MatrixMult (g_world, RotateYMatrix (pi/2.0f));
	hResult = lpDev->SetTransform (D3DTRANSFORMSTATE_WORLD, &g_world);
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
	}

        hResult = lpDev->DrawPrimitive (D3DPT_LINELIST, D3DVT_VERTEX, (LPVOID)grid, NUM_GRID*NUM_GRID, D3DDP_WAIT);
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
	}
#endif

	tic += 0.01f;

	if (lpExtent)
	{
		hResult = lpDev->GetClipStatus (&status);
		if (FAILED (hResult))
		{
			REPORTERR (hResult);
			return hResult;
		}
	}

    hResult = lpDev->EndScene ();
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
	}

	if (lpExtent)
	{
		// return clip status in extent struct
		if (status.dwFlags & D3DCLIPSTATUS_EXTENTS2)
		{
			lpExtent->x1 = (long)floor ((double)status.minx);
			lpExtent->x2 = (long)ceil ((double)status.maxx);
			lpExtent->y1 = (long)floor ((double)status.miny);
			lpExtent->y2 = (long)ceil ((double)status.maxy);
		}
	}

	// Success
    return DD_OK;
} // End D3DScene::Render


  
/*
**----------------------------------------------------------------------------
** Name:        D3DScene::Restore
** Purpose:     Restore any scene specific surfaces that might have been
**				lost on a DDERR_LOSTSURFACE message
**----------------------------------------------------------------------------
*/

HRESULT D3DScene::Restore (void)
{
	// Nothing to do for now

	// Success
	return DD_OK;
} // End D3DScene::Restore



/*
**-----------------------------------------------------------------------------
**  Name:       D3DScene::InitViewport
**  Purpose:	Initialize Viewport
**-----------------------------------------------------------------------------
*/

HRESULT D3DScene::InitViewport (void)
{
	LPDIRECT3D2			lpD3D;
	LPDIRECT3DDEVICE2   lpDev;
	LPDIRECT3DVIEWPORT2 lpViewport;
	HRESULT				hResult;
    D3DMATERIAL			matBackground, mat;
    D3DMATERIALHANDLE	hBackMat, hMat;

	// Check Initialization
	if ((! lpd3dWindow) || (! lpd3dWindow->isValid ()))
	{
		// Error,
		REPORTERR (DDERR_GENERIC);
		return DDERR_GENERIC;
	}

	lpD3D  = lpd3dWindow->lpD3D;
	lpDev  = lpd3dWindow->lpd3dDevice;
	lpViewport = lpd3dWindow->lpd3dViewport;

	if ((! lpD3D) || (! lpDev) || (! lpViewport))
	{
		REPORTERR (DDERR_GENERIC);
		return DDERR_GENERIC;
	}
   
	// Create and set up the background material
    hResult = lpD3D->CreateMaterial (&g_lpmatBackground, NULL);
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
    }

    memset (&matBackground, 0, sizeof(D3DMATERIAL));
    matBackground.dwSize = sizeof(D3DMATERIAL);
    matBackground.diffuse.r = (D3DVALUE)0.2;
    matBackground.diffuse.g = (D3DVALUE)0.6;
    matBackground.diffuse.b = (D3DVALUE)1.0;
    matBackground.ambient.r = (D3DVALUE)1.0;
    matBackground.ambient.g = (D3DVALUE)1.0;
    matBackground.ambient.b = (D3DVALUE)1.0;
//    matBackground.hTexture = hBackTex;
	matBackground.dwRampSize = 1;
    
	hResult = g_lpmatBackground->SetMaterial (&matBackground);
	if (FAILED (hResult))
	{
		REPORTERR (hResult);
		return hResult;
	}
    
	hResult = g_lpmatBackground->GetHandle (lpDev, &hBackMat);
	if (FAILED (hResult))
	{
		REPORTERR (hResult);
		return hResult;
	}

    hResult = lpViewport->SetBackground (hBackMat);
	if (FAILED (hResult))
	{
		REPORTERR (hResult);
		return hResult;
	}

	g_hBackMat = hBackMat;

	// create and set up the plane material
    hResult = lpD3D->CreateMaterial (&g_lpMat, NULL);
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
    }

    memset(&mat, 0, sizeof(D3DMATERIAL));
    mat.dwSize = sizeof(D3DMATERIAL);
    mat.diffuse.r = (D3DVALUE)1.0;
    mat.diffuse.g = (D3DVALUE)1.0;
    mat.diffuse.b = (D3DVALUE)1.0;
    mat.ambient.r = (D3DVALUE)1.0;
    mat.ambient.g = (D3DVALUE)1.0;
    mat.ambient.b = (D3DVALUE)1.0;
#define SPECULAR
#ifdef SPECULAR
    mat.specular.r = (D3DVALUE)1.0;
    mat.specular.g = (D3DVALUE)1.0;
    mat.specular.b = (D3DVALUE)1.0;
    mat.power = (float)40.0;
#else
    mat.specular.r = (D3DVALUE)0.0;
    mat.specular.g = (D3DVALUE)0.0;
    mat.specular.b = (D3DVALUE)0.0;
    mat.power = (float)0.0;
#endif    
//    mat.hTexture = hTexure;
    mat.dwRampSize = 16;
    g_lpMat->SetMaterial (&mat);
    g_lpMat->GetHandle (lpDev, &hMat);
	g_hMat= (DWORD) hMat;
//	g_hTex= hTexure;

	//g_view = ViewMatrix(100.0f);
	g_proj = ProjectionMatrix (1.0f, 1000.0f, 90.0f);
	g_world = IdentityMatrix ();

	// set up the light
    memset (&g_light, 0, sizeof(D3DLIGHT));
    g_light.dwSize = sizeof(D3DLIGHT);
    g_light.dltType = D3DLIGHT_POINT;
	// position light behind viewer
    g_light.dvPosition.x = 0.0f;
    g_light.dvPosition.y = 1000.0f;
    g_light.dvPosition.z = -100.0f;
    g_light.dcvColor.r = D3DVAL(1.0);
    g_light.dcvColor.g = D3DVAL(1.0);
    g_light.dcvColor.b = D3DVAL(1.0);
    g_light.dvAttenuation0 = (float)1.0;
    g_light.dvAttenuation1 = (float)0.0;
    g_light.dvAttenuation2 = (float)0.0;

    hResult = lpD3D->CreateLight (&g_lpD3DLight, NULL);
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
    }

    hResult = g_lpD3DLight->SetLight (&g_light);
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
    }

    hResult = lpViewport->AddLight (g_lpD3DLight);
	if (FAILED (hResult))
	{
        REPORTERR (hResult);
		return hResult;
    }

	// Success
    return DD_OK;
} // End D3DScene::InitViewport



/*
**-----------------------------------------------------------------------------
**  Name:       D3DScene::FiniViewport
**  Purpose:	Cleanup Viewport
**-----------------------------------------------------------------------------
*/

HRESULT D3DScene::FiniViewport (void)
{
	HRESULT hResult;
	LPDIRECT3DVIEWPORT2 lpViewport;

	// Check Initialization
	if (! lpd3dWindow)
	{
		// Error,
		REPORTERR (DDERR_GENERIC);
		return DDERR_GENERIC;
	}

	lpViewport = lpd3dWindow->GetViewport ();

	// Cleanup light
	if (g_lpD3DLight)
	{
		// Remove from current view
	    if (lpViewport) 
		{
			hResult = lpViewport->DeleteLight (g_lpD3DLight);
			if (FAILED (hResult))
			{
				REPORTERR (hResult);
			}

		}

		// Release light
		hResult = g_lpD3DLight->Release ();
		if (FAILED (hResult))
		{
			REPORTERR (hResult);
		}

		g_lpD3DLight = NULL;
	}

	// Cleanup Material
    if (g_lpMat)
	{
		hResult = g_lpMat->Release ();
		if (FAILED (hResult))
		{
			REPORTERR (hResult);
		}

		g_lpMat = NULL;
		g_hMat = NULL;
	}

	// Cleanup Background
	if (g_lpmatBackground)
	{
		hResult = g_lpmatBackground->Release ();
		if (FAILED (hResult))
		{
			REPORTERR (hResult);
		}

		g_lpmatBackground = NULL;
		g_hBackMat = NULL;
	}

	// Success
	return DD_OK;
} // End D3DScene::FiniViewport


  
/*
**-----------------------------------------------------------------------------
**	End of File
**-----------------------------------------------------------------------------
*/


