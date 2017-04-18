/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    RMain.cpp

Abstract:

    Main rendering code. Sets things up and calls all the other
	rendering functions in other files.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCWorld.h"
#include "DCGraphics.h"
#include "DCVis.h"
#include "DCGame.h"
#include "DCRender.h"

// External functions.
BOOL InitText(void);
void ShutdownText(void);
BOOL InitSky(void);
void ShutdownSky(void);
void RenderSky();
BOOL InitTerrain(void);
void ShutdownTerrain(void);
void RenderTerrain();
BOOL InitSun(void);
void ShutdownSun(void);
void RenderSun();
BOOL InitRMesh(void);
void ShutdownRMesh(void);
void RenderOpaqueMeshes(void);
void RenderTranslucentMeshes(void);
void RenderFirstPersonMesh(void);
BOOL InitParticles(void);
void ShutdownParticles(void);
void RenderParticles();
BOOL InitHUD(void);
void ShutdownHUD(void);
void RenderFlash();
void RenderPlayerHUD(void);
void RenderGenericHUD(void);
void RenderHelpOverlay(void);
BOOL InitTracer();
void ShutdownTracer();

void CreateFishEyeView();

// Global rendering structure.
RenderClass gRender;

// Initializes rendering functions.
// Note that model textures will already have been put in
// the texture list when the game class is initialized.
BOOL RenderInit(void)
{
	// Just for debugging.
	gRender.GridTexture=gGraphics.AddTexture(ReadImageFileMipmapped,TEXT("DebugGrid"),TRUE,FALSE);
	
	// Init any stuff which has user render meshes.
	InitTracer();

	// Init text.
	if (!InitText())
		return FALSE;

	// Init sky.
	if (!InitSky())
		return FALSE;

	// Init terrain.
	if (!InitTerrain())
		return FALSE;
	
	// Init sun.
	if (!InitSun())
		return FALSE;

	// Init the mesh rendering.
	if (!InitRMesh())
		return FALSE;

	if (!InitParticles())
		return FALSE;

	// Init HUD.
	if (!InitHUD())
		return FALSE;

	// Now load the textures we have put in the texture list.
	if (!gGraphics.LoadTextures())
		return FALSE;

	return TRUE;
}

void RenderShutdown(void)
{
	// Shutdown all the rendering stuff.
	ShutdownHUD();
	ShutdownParticles();
	ShutdownRMesh();
	ShutdownSun();
	ShutdownTerrain();
	ShutdownSky();
	ShutdownText();

	// User render stuff.
	ShutdownTracer();
}

// Sets state and matrices to "default" for 3D rendering.
static void SetupFor3D()
{
	// Get viewer position.
	DCVector Loc,Rot;
	gGame.GetViewerCoords(&Loc,&Rot);

	// ZFar is maximum possible distance to edge of the world.
	float PlayerRadius=(float)sqrt(Loc.X*Loc.X + Loc.Z*Loc.Z);
	float CombinedRadius=DCW_FAR_VIS_RADIUS+PlayerRadius;
	float ZFar=(float)sqrt(CombinedRadius*CombinedRadius + Loc.Y*Loc.Y);
	
	// ZNear is base ZNear scaled by ratio of ZFar to terrain radius.
	float ZNear=DCW_BASE_ZNEAR*ZFar/DCW_TERRAIN_OUTER_RADIUS;
	
	// Save them.
	gRender.Frame.ZNear=ZNear;
	gRender.Frame.ZFar=ZFar;

	// Set projection matrix to a perspective projection.
	gGraphics.SetPerspectiveProjection(DCW_FOV, ZNear, ZFar);
	// Save it.
	gGraphics.GetProjectionMatrix(&gRender.Frame.ProjectionMatrix);

	// Set the view matrix.
	gGraphics.MatrixIdentity();
	gGraphics.MatrixTranslate(-Loc.X,-Loc.Y,-Loc.Z);
	gGraphics.MatrixRotateY(-Rot.Y);
	gGraphics.MatrixRotateX(-Rot.X);
	gGraphics.SetViewMatrix();
	// Save it.
	gGraphics.MatrixGet(&gRender.Frame.ViewMatrix);

	// Initialize world matrix to identity since the first
	// things we render are already in world coordinates.
	gGraphics.MatrixIdentity();
	gGraphics.SetWorldMatrix();

	// Set "defaults" for certain states.
	gGraphics.EnableTransforms();
	gGraphics.EnableClipping();
	gGraphics.DisableSpecular();

	// Init the visibility testing code.
	float MaxViewAngH,MaxViewAngV;
	gGraphics.GetViewMaxAngles(DCW_FOV,&MaxViewAngH,&MaxViewAngV);
	gVis.InitForFrame(MaxViewAngH,MaxViewAngV,ZNear,ZFar,&Loc,&Rot);

	// Init global per frame stuff.
	gRender.Frame.FrameTime=gGame.GetFrameDeltaTime();
	gRender.Frame.ViewLoc=Loc;
	gRender.Frame.ViewRot=Rot;
	gRender.Frame.IsObserverMode=gGame.IsObserverMode();
	gRender.Frame.IsTimePaused=gGame.IsTimePaused();
	// Init vectors representing view rotated axes.
	Rot.CalculateViewVectors(&gRender.Frame.ViewVecX,&gRender.Frame.ViewVecY,&gRender.Frame.ViewVecZ);
	// Calculate inverse view matrix.
	gGraphics.MatrixIdentity();
	gGraphics.MatrixRotateX(Rot.X);
	gGraphics.MatrixRotateY(Rot.Y);
	gGraphics.MatrixTranslate(Loc.X,Loc.Y,Loc.Z);
	gGraphics.MatrixGet(&gRender.Frame.InvViewMatrix);

	// Init first persion mesh to none.
	gRender.Frame.FirstPerson.Mesh=NULL;
	gRender.Frame.FirstPerson.Loc=gRender.Frame.FirstPerson.Rot=DCVector(0,0,0);

}

// Sets state and matrices to "default" for 2D rendering.
static void SetupFor2D(void)
{
	// Set 2D scale/translate parameters.
	gGraphics.Setup2DScaleTranslate(0,DCW_RESX2D,0,DCW_RESY2D);

	// Don't need transforms.
	gGraphics.DisableTransforms();

	// Most HUD stuff uses this.
	gGraphics.ShadeModeFlat();
	gGraphics.EnableBlend();
	gGraphics.BlendMode(BLEND_SRCALPHA,BLEND_INVSRCALPHA);
	gGraphics.DisableDepthTest();
	gGraphics.DisableDepthWrite();
	gGraphics.CullDisable();
	gGraphics.TexAddressModeClamp();
	gGraphics.TexBlendModulateAlpha();
#ifdef DREAMCAST
	gGraphics.DisableClipping(); // X/Y clipping not necessary on Dreamcast.
#endif
}

// Render each of the components of the scene.
void RenderScene(void)
{
	// Generate the envirionment map texture if necessary 
	// before we render the scene.
	if (gCreateFishEyeView)
	{
		CreateFishEyeView();
		gCreateFishEyeView=FALSE;
	}

	// We don't bother clearing the depth buffer since 
	// rendering sky code will do it...
#ifdef _DEBUG
	// ..except in debug mode where we always clear the depth 
	// and frame buffers up front.
	gGraphics.Clear(NULL,TRUE,0x00BF0000,TRUE,1.0f);
#endif

	// Begin the scene.
	if (!gGraphics.BeginScene())
		return;

	// Set default matrices and state.
	SetupFor3D();
	
	// Render sky.
	RenderSky();

	// Render sun.
	RenderSun();

	// Render terrain.
	RenderTerrain();

	// Render the opaque meshes.
	RenderOpaqueMeshes();

	// Render the translucent meshes.
	RenderTranslucentMeshes();

	// Render particles.
	RenderParticles();

	// Render the first person mesh over the top of everything.
	RenderFirstPersonMesh();

	// Render "2D" stuff.
	// Set default matrices and state.
	SetupFor2D();

	// Render flash if there is one.
	RenderFlash();

	// Render HUD if necessary.
	if (!gRender.Frame.IsObserverMode)
	{
		RenderPlayerHUD();
	}

	// Render rest of HUD which is not specific to the player view.
	RenderGenericHUD();

	// Render "overlay" help info if neccesary.
	if (gGame.IsDisplayHelp())
		RenderHelpOverlay();

	// End the scene.
	if (!gGraphics.EndScene())
		return;

	// Flip.
	gGraphics.Flip();
}

// Sets state and matrices to "default" for 3D rendering.
static void SetupFor3DFishEye(float RotX, float RotY)
{
	// Get viewer position.
	DCVector Loc(0,0,0),Rot;
	EntityBase *Player=gGame.GetPlayerEntity();
	if (Player)
		Player->GetPosition(&Loc,&Rot);
	Rot=DCVector(RotX,RotY,0);
	
	// ZFar is maximum possible distance to edge of the world.
	float PlayerRadius=(float)sqrt(Loc.X*Loc.X + Loc.Z*Loc.Z);
	float CombinedRadius=DCW_TERRAIN_OUTER_RADIUS+PlayerRadius;
	float ZFar=(float)sqrt(CombinedRadius*CombinedRadius + Loc.Y*Loc.Y);
	
	// ZNear is base ZNear scaled by ratio of ZFar to terrain radius.
	float ZNear=DCW_BASE_ZNEAR*ZFar/DCW_TERRAIN_OUTER_RADIUS;
	
	// Save them.
	gRender.Frame.ZNear=ZNear;
	gRender.Frame.ZFar=ZFar;

	// Set projection matrix to a perspective projection.
	gGraphics.SetPerspectiveProjection(DCW_FOV, ZNear, ZFar);
	// Save it.
	gGraphics.GetProjectionMatrix(&gRender.Frame.ProjectionMatrix);

	// Set the view matrix.
	gGraphics.MatrixIdentity();
	gGraphics.MatrixTranslate(-Loc.X,-Loc.Y,-Loc.Z);
	gGraphics.MatrixRotateY(-Rot.Y);
	gGraphics.MatrixRotateX(-Rot.X);
	gGraphics.SetViewMatrix();
	// Save it.
	gGraphics.MatrixGet(&gRender.Frame.ViewMatrix);

	// Initialize world matrix to identity since the first
	// things we render are already in world coordinates.
	gGraphics.MatrixIdentity();
	gGraphics.SetWorldMatrix();

	// Set "defaults" for certain states.
	gGraphics.EnableTransforms();
	gGraphics.EnableClipping();
	gGraphics.DisableSpecular();

	// Init the visibility testing code.
	float MaxViewAngH,MaxViewAngV;
	gGraphics.GetViewMaxAngles(DCW_FOV,&MaxViewAngH,&MaxViewAngV);
	gVis.InitForFrame(MaxViewAngH,MaxViewAngV,ZNear,ZFar,&Loc,&Rot);

	// Init global per frame stuff.
	gRender.Frame.FrameTime=0.0f;
	gRender.Frame.ViewLoc=Loc;
	gRender.Frame.ViewRot=Rot;
	gRender.Frame.IsObserverMode=FALSE;
	gRender.Frame.IsTimePaused=TRUE;
	// Init vectors representing view rotated axes.
	Rot.CalculateViewVectors(&gRender.Frame.ViewVecX,&gRender.Frame.ViewVecY,&gRender.Frame.ViewVecZ);
	// Calculate inverse view matrix.
	gGraphics.MatrixIdentity();
	gGraphics.MatrixRotateX(Rot.X);
	gGraphics.MatrixRotateY(Rot.Y);
	gGraphics.MatrixTranslate(Loc.X,Loc.Y,Loc.Z);
	gGraphics.MatrixGet(&gRender.Frame.InvViewMatrix);
}

// Render environment map scene.
void RenderFishEyeScene(float RotX, float RotY)
{
	gGraphics.Clear(NULL,TRUE,0x00000000,TRUE,1.0f);

	// Begin the scene.
	if (!gGraphics.BeginScene())
		return;

	// Set default matrices and state.
	SetupFor3DFishEye(RotX,RotY);
	
	// Render sky.
	RenderSky();

	// Render sun.
	RenderSun();

	// Render terrain.
	RenderTerrain();

	// Render the opaque meshes.
	RenderOpaqueMeshes();

	// Render the translucent meshes.
	RenderTranslucentMeshes();

	// Render particles.
	RenderParticles();

	// End the scene.
	if (!gGraphics.EndScene())
		return;

	// Flip.
	gGraphics.Flip();
}