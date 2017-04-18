/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File: rm.cpp
 *
 ***************************************************************************/

// Includes....
#include "rm.h"
#include "directx.h"
#include "mmsystem.h"
#include "stdio.h"
#include "control.h"

// Globals....
LPDIRECT3DRMFRAME		g_lpScene = NULL;	// Scene frame
LPDIRECT3DRMFRAME		g_lpCamera = NULL;	// Camera frame
LPDIRECT3DRMFRAME		g_lpArena = NULL;	// Arena frame
LPDIRECT3DRMFRAME		g_lpBackground = NULL;	// Background frame

LPDIRECT3DRMFRAME		g_lpPlayers = NULL;	// Encapsulating frame
LPDIRECT3DRMFRAME		g_lpPlayer1 = NULL;	// Human player
LPDIRECT3DRMFRAME		g_lpPlayer1HeadFrame = NULL;// Human player head frame
LPDIRECT3DRMANIMATIONSET	g_lpPlayer1AnimSet = NULL;// Human player animation set
LPDIRECT3DRMFRAME		g_lpPlayer2 = NULL;	// Computer player
LPDIRECT3DRMFRAME		g_lpPlayer2HeadFrame = NULL;// Computer player head frame
LPDIRECT3DRMANIMATIONSET	g_lpPlayer2AnimSet = NULL;// Computer player animation set

LPDIRECT3DRMFRAME		g_lpTmp = NULL;		// Temporary frame

LPDIRECT3DRMLIGHT		g_lpDir;		// Global light frame

LPDIRECT3DRMMESHBUILDER		g_lpRedDebris = NULL;	// Red debris model
LPDIRECT3DRMMESHBUILDER		g_lpBlueDebris = NULL;	// Blue debris model
Debris				g_debris[NUM_DEBRIS];	// Debris

LPDIRECT3DRMANIMATION		g_lpAnim = NULL;	// Intro anim

// Timing stuff
D3DVALUE			g_timingDelta = D3DVAL(0.0f);

// Frame rate stuff
DWORD				g_dwLastTime = 0;
DWORD				g_dwCurTime = 0;
DWORD				g_dwFpsTime = 0;
DWORD				g_dwDeltaTime = 0;
DWORD				g_dwFramesRendered = 0;
DWORD				g_dwFps = 0;

// Externals....
extern BOOL			g_bShowStats;		// Defined in WINMAIN.CPP
extern BOOL			g_bHardware3D;		// Defined in DIRECTX.CPP
extern LPDIRECT3DRM		g_lpD3DRM;		// Defined in DIRECTX.CPP
extern LPDIRECT3DRMVIEWPORT	g_lpD3DRMViewport;	// Defined in DIRECTX.CPP
extern LPDIRECT3DRMDEVICE	g_lpD3DRMDevice;	// Defined in DIRECTX.CPP
extern LPDIRECTDRAWSURFACE	g_lpPrimary;		// Defined in DIRECTX.CPP
extern LPDIRECTDRAWSURFACE	g_lpBackBuffer;		// Defined in DIRECTX.CPP
extern LPDIRECTDRAWSURFACE	g_lpZBuffer;		// Defined in DIRECTX.CPP
extern DWORD			g_vidModeX;		// Defined in DIRECTX.CPP
extern DWORD			g_vidModeY;		// Defined in DIRECTX.CPP
extern DWORD			g_vidModeBIT;		// Defined in DIRECTX.CPP
extern DWORD			g_dwFontHeight;		// Defined in DIRECTX.CPP
extern DWORD			g_dwAveCharWidth;	// Defined in DIRECTX.CPP

extern DWORD			g_player1health;	// Defined in CONTROL.CPP
extern DWORD			g_player2health;	// Defined in CONTROL.CPP

extern DWORD			g_lbar1;		// Defined in DIRECTX.CPP
extern DWORD			g_wbar1;		// Defined in DIRECTX.CPP
extern DWORD			g_lbar2;		// Defined in DIRECTX.CPP
extern DWORD			g_wbar2;		// Defined in DIRECTX.CPP
extern DWORD			g_hbar1;		// Defined in DIRECTX.CPP
extern DWORD			g_hbar2;		// Defined in DIRECTX.CPP

extern AnimArgs			g_player1AnimArgs;
extern AnimArgs			g_player2AnimArgs;

//----------------------------------------------------------------------
// 
// Function	: InitScene
//
// Purpose	: Initialises Direct3D RM objects and loads scene for demo
//
//----------------------------------------------------------------------

BOOL InitScene()
{
    LPDIRECT3DRMLIGHT		pAmb;
    LPDIRECT3DRMFRAME		pLight;
    LPDIRECT3DRMMESHBUILDER pMeshBuilder;

    // Create the scene (parent) frame
    TRY_D3DRM(g_lpD3DRM->CreateFrame(NULL, &g_lpScene))

    // Create the camera (child of g_lpScene)
    TRY_D3DRM(g_lpD3DRM->CreateFrame(g_lpScene, &g_lpCamera))

    // Create the arena frame
    TRY_D3DRM(g_lpD3DRM->CreateFrame(g_lpScene, &g_lpArena))

    // Create the frame that encapsulates both players
    TRY_D3DRM(g_lpD3DRM->CreateFrame(g_lpScene, &g_lpPlayers))
    
    // Create player frames
    TRY_D3DRM(g_lpD3DRM->CreateFrame(g_lpPlayers, &g_lpPlayer1))

    TRY_D3DRM(g_lpD3DRM->CreateFrame(g_lpPlayers, &g_lpPlayer2))
    
    // Create temporary frame
    TRY_D3DRM(g_lpD3DRM->CreateFrame(g_lpScene, &g_lpTmp))
    
    // Create lights and position in world
    TRY_D3DRM(g_lpD3DRM->CreateLightRGB(D3DRMLIGHT_AMBIENT, D3DVAL(0.2), D3DVAL(0.2), D3DVAL(0.2), &pAmb))
    
    TRY_D3DRM(g_lpD3DRM->CreateLightRGB(D3DRMLIGHT_DIRECTIONAL, D3DVAL(0.7), D3DVAL(0.7), D3DVAL(0.7), &g_lpDir))

    // Create ambient light frame
    TRY_D3DRM(g_lpD3DRM->CreateFrame(g_lpScene, &pLight))
    
    // Add the light to the frame
    TRY_D3DRM(pLight->AddLight(pAmb))
    
    // Release the light frame
    pLight->Release();	

    // Create directional light frame
    TRY_D3DRM(g_lpD3DRM->CreateFrame(g_lpScene, &pLight))
    
    // Set position and orientation of directional light
    pLight->SetPosition(g_lpScene, D3DVAL(1000), D3DVAL(1000), D3DVAL(1000));
    pLight->SetOrientation(g_lpScene, D3DVAL(-1.0), D3DVAL(-1.0), D3DVAL(1.0), D3DVAL(0.0), D3DVAL(1.0), D3DVAL(0.0));
    
    // Add the light to the frame
    TRY_D3DRM(pLight->AddLight(g_lpDir))
    
    // Enable lights only for any object that is a child of g_lpPlayers
    TRY_D3DRM(g_lpDir->SetEnableFrame(g_lpPlayers))

    // Release the light frame
    pLight->Release();

    // Create mesh builder for arena
    TRY_D3DRM(g_lpD3DRM->CreateMeshBuilder(&pMeshBuilder))
    
    // Load the arena
    TRY_D3DRM(pMeshBuilder->Load("ARENA.X", NULL, D3DRMLOAD_FROMFILE, LoadTextures, NULL))
    
    // Make sure we use perspective correct!
    pMeshBuilder->SetPerspective(TRUE);
    
    // Add the mesh to the scene
    TRY_D3DRM(g_lpArena->AddVisual(pMeshBuilder))
    
    g_lpArena->SetZbufferMode(D3DRMZBUFFER_DISABLE);

    // Release the mesh builder
    pMeshBuilder->Release();

    // Load player 1's model	
    TRY_D3DRM(g_lpD3DRM->CreateAnimationSet(&g_lpPlayer1AnimSet))

    // Load the model and animation
    TRY_D3DRM(g_lpPlayer1AnimSet->Load("SKMECH.X", NULL, D3DRMLOAD_FROMFILE, LoadTextures, NULL, g_lpPlayer1))

    // Add animation callback for player 1
    g_player1AnimArgs.lpAnimSet = g_lpPlayer1AnimSet;
    g_player1AnimArgs.time		= D3DVAL(0);
    TRY_D3DRM(g_lpPlayer1->AddMoveCallback(Player1AnimationCallback, NULL))

    // Setup the initial position of player 1
    g_lpPlayer1->SetPosition(g_lpScene, D3DVAL(0), D3DVAL(0), D3DVAL(-200));

    // Load player 2's model
    TRY_D3DRM(g_lpD3DRM->CreateAnimationSet(&g_lpPlayer2AnimSet))

    // Load the model and animation
    TRY_D3DRM(g_lpPlayer2AnimSet->Load("DEMECH.X", NULL, D3DRMLOAD_FROMFILE, LoadTextures, NULL, g_lpPlayer2))
    
    // Add animation callback for player 2
    g_player2AnimArgs.lpAnimSet = g_lpPlayer2AnimSet;
    g_player2AnimArgs.time		= D3DVAL(0);
    TRY_D3DRM(g_lpPlayer2->AddMoveCallback(Player2AnimationCallback, NULL))	

    for (int i = 0; i < NUM_DEBRIS; i ++)
    {
	TRY_D3DRM(g_lpD3DRM->CreateFrame(g_lpPlayers, &g_debris[i].m_pFrame))
	
	g_debris[i].m_bInUse = FALSE;
    }

    // Load the red debris
    TRY_D3DRM(g_lpD3DRM->CreateMeshBuilder(&g_lpRedDebris))

    TRY_D3DRM(g_lpRedDebris->Load("debris_r.x", NULL, D3DRMLOAD_FROMFILE, NULL, NULL))
    
    // Load the blue debris
    TRY_D3DRM(g_lpD3DRM->CreateMeshBuilder(&g_lpBlueDebris))

    TRY_D3DRM(g_lpBlueDebris->Load("debris_b.x", NULL, D3DRMLOAD_FROMFILE, NULL, NULL))

    // Setup the initial position of player 2
    g_lpPlayer2->SetPosition(g_lpScene, D3DVAL(0), D3DVAL(0), D3DVAL(200));

    // Create the intro path
    TRY_D3DRM(g_lpD3DRM->CreateAnimation(&g_lpAnim))

    // Setup the animation options
    g_lpAnim->SetOptions(D3DRMANIMATION_OPEN | 
			 D3DRMANIMATION_LINEARPOSITION | 
			 D3DRMANIMATION_POSITION);
    
    // Add the starting position (as a keyframe)
    g_lpAnim->AddPositionKey(D3DVAL(0), D3DVAL(200), D3DVAL(2000), D3DVAL(0));
    
    // Add the ending position (as a keyframe)
    g_lpAnim->AddPositionKey(D3DVAL(1), D3DVAL(700), D3DVAL(100), D3DVAL(0));
    
    // Make the camera follow this animation
    g_lpAnim->SetFrame(g_lpCamera);	

    // Retrieve player 1 and player 2's head frames	
    LPDIRECT3DRMOBJECT tmp;
	    
    TRY_D3DRM(g_lpD3DRM->GetNamedObject("x3ds_Head", &tmp))
    g_lpPlayer1HeadFrame = (LPDIRECT3DRMFRAME)tmp;

    TRY_D3DRM(g_lpD3DRM->GetNamedObject("x3ds_xHead", &tmp))
    g_lpPlayer2HeadFrame = (LPDIRECT3DRMFRAME)tmp;

    // Yahoo!
    return TRUE;
}

//----------------------------------------------------------------------
// 
// Function	: TermScene
//
// Purpose	: Destroys scene
//
//----------------------------------------------------------------------

void TermScene()
{	
    // Destroy the scene frame
    if (g_lpScene)
    {
	g_lpScene->Release();
	g_lpScene = NULL;
    }

    // Destroy the animation sets
    if (g_lpPlayer1AnimSet)
    {
	g_lpPlayer1AnimSet->Release();
	g_lpPlayer1AnimSet = NULL;
    }

    if (g_lpPlayer2AnimSet)
    {
	g_lpPlayer2AnimSet->Release();
	g_lpPlayer2AnimSet = NULL;
    }
}

//----------------------------------------------------------------------
// 
// Function	: RenderScene
//
// Purpose	: Renders scene
//
//----------------------------------------------------------------------

BOOL RenderScene()
{
    static BOOL b = FALSE;

    // Verify both surfaces
    if (!g_lpPrimary) return FALSE;

    if (!g_lpZBuffer) return FALSE;

    // Perform some timing stuff	
    g_dwCurTime	  = timeGetTime();
    g_dwDeltaTime = g_dwCurTime - g_dwLastTime;
    g_dwLastTime  = g_dwCurTime;
    g_dwFpsTime  += g_dwDeltaTime;

    // Move the scene
    g_lpScene->Move(D3DVAL(g_dwDeltaTime));

    if (b) {
	b = FALSE;
	TRY_D3DRM(g_lpD3DRMViewport->ForceUpdate(0, 0, g_vidModeX, g_vidModeY))
    }

    // Restore the primary surface if it has been lost
    if (g_lpPrimary->IsLost())
    {
	    HRESULT rval = g_lpPrimary->Restore();
	    if (rval != DD_OK) return TRUE;
	    TRY_D3DRM(g_lpD3DRMViewport->ForceUpdate(0, 0, g_vidModeX, g_vidModeY))
	    b = TRUE;
    }
    
    // Restore the ZBuffer if it has been lost
    if (g_lpZBuffer->IsLost())
    {
	    HRESULT rval = g_lpZBuffer->Restore();
	    if (rval != DD_OK) return TRUE;
	    TRY_D3DRM(g_lpD3DRMViewport->ForceUpdate(0, 0, g_vidModeX, g_vidModeY))
    }

    // Clear the viewport ready for rendering
    TRY_D3DRM(g_lpD3DRMViewport->Clear())
    
    // Render the scene
    TRY_D3DRM(g_lpD3DRMViewport->Render(g_lpScene))

    g_dwFramesRendered ++;

    // Show stats if necessary
    if (g_bShowStats)
    {
	// String to hold stats
	char sStats[256];		

	// If 2 seconds have elapsed, calculate the frame rate
	if (g_dwFpsTime > 2000)
	{
	    g_dwFps		= g_dwFramesRendered / 2;
	    g_dwFramesRendered	= 0;
	    g_dwFpsTime		= 0;
	}

	// Copy info into stat string
	sprintf(sStats, "SX:%d, SY:%d, SBD:%d FPS:%d, %s", g_vidModeX, g_vidModeY, g_vidModeBIT, g_dwFps, g_bHardware3D ? "(H)" : "(S)");

	// Get a DC to the backbuffer (very useful!)
	HDC hDC;
	g_lpBackBuffer->GetDC(&hDC);
	if (!hDC) return FALSE;

	// Use TextOut to draw the text onto the surface
	DWORD dwStringPixelWidth = strlen(sStats) * g_dwAveCharWidth;

        SetBkMode( hDC, TRANSPARENT );
        SetTextColor( hDC, RGB(255,255,255) );
	TextOut(hDC, (g_vidModeX >> 1) - (dwStringPixelWidth >> 1), g_vidModeY - g_dwFontHeight, sStats, strlen(sStats));

	// Must release DC before calling Flip()
	g_lpBackBuffer->ReleaseDC(hDC);
    }

    // Draw the power bars
    DDBLTFX ddBltFx;
    memset(&ddBltFx, 0, sizeof(DDBLTFX));
    ddBltFx.dwSize = sizeof(DDBLTFX);

    RECT rcBar1 = { g_lbar1, g_hbar1, g_lbar1 + g_wbar1, g_hbar1 + g_hbar2 };
    RECT rcBar2 = { g_lbar2, g_hbar1, g_lbar2 + g_wbar2, g_hbar1 + g_hbar2 };

    switch (g_vidModeBIT)
    {
	case 8  : ddBltFx.dwFillColor = 253; break;
	case 16 : ddBltFx.dwFillColor = 1 << 4; break;
	case 24 : ddBltFx.dwFillColor = 1 << 7; break;
    }
    if (g_player1health > 0) {
	TRY_DD(g_lpBackBuffer->Blt(&rcBar1, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddBltFx))
	TRY_D3DRM(g_lpD3DRMViewport->ForceUpdate(rcBar1.left, rcBar1.top, rcBar1.right, rcBar1.bottom))
    }

    switch (g_vidModeBIT)
    {
	case 8  : ddBltFx.dwFillColor = 254; break;
	case 16 : ddBltFx.dwFillColor = 1 << 5 << 5 << 4; break;
	case 24 : ddBltFx.dwFillColor = 1 << 8 << 8 << 7; break;
    }	
    if (g_player2health > 0) {
	TRY_DD(g_lpBackBuffer->Blt(&rcBar2, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddBltFx))
	TRY_D3DRM(g_lpD3DRMViewport->ForceUpdate(rcBar2.left, rcBar2.top, rcBar2.right, rcBar2.bottom))
    }

    // And update the device
    TRY_D3DRM(g_lpD3DRMDevice->Update())

    // Finally, flip the back buffer onto the primary surface, displaying
    // the last rendered frame
    TRY_DD(g_lpPrimary->Flip(NULL, DDFLIP_WAIT))

    // Yahoo!
    return TRUE;
}

//------------------------------------------------------------------
// 
// Function	: LoadTextures
//
// Purpose	: Loads an individual texture
//
// NOTE		: Textures must have a size divisible by 2 (e.g. 128x64, 256x256)
//
//------------------------------------------------------------------

HRESULT LoadTextures(char *sName, void *pArg, LPDIRECT3DRMTEXTURE *hTexture)
{    
    char *sTmpName = sName;
	    
    // Find the extension
    while(sTmpName[0] != '.') sTmpName ++;

    // Add .ppm to the picture file used by 3D Studio (.TGA, .GIF, .CEL etc)
    strcpy(sTmpName, ".ppm");
    
    // Load the texture
    if (FAILED(g_lpD3DRM->LoadTexture(sName, hTexture))) return -1;

    if (!strcmp(sName, "gdk_fill.ppm"))
    {
	(*hTexture)->SetShades(1);
    }

    return 0;
}

