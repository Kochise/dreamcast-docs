/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    RHUD.cpp

Abstract:

    Head up display and other "2D" rendering.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCWorld.h"
#include "DCGraphics.h"
#include "DCRText.h"
#include "DCGame.h"
#include "DCRHUD.h"
#include "DCRender.h"
#include "DCNetwork.h"

#define RADAR_X	40
#define RADAR_Y	(DCW_RESY2D-85)
#define RADAR_R 35
#define RADAR_INNER_R 30
#define RADAR_RANGE (DCW_TERRAIN_HIGH_INNER_RADIUS)

// Overlay.
static DCVertex OverlayVerts[4];

// Help string.
static TCHAR *HelpTitle,*HelpString;
static float HelpTitleWidth,HelpLines,HelpWidth;

// Other strings.
static TCHAR *FPSString;
static TCHAR *TimePausedString;
static float TimePausedStringLength;
static TCHAR *GodModeString;
static float GodModeStringLength;
static TCHAR *GameOverString, *StageString, *ReachedStageString;
static TCHAR *DemoRecordingString;
static TCHAR *DefenseMarkString;
static TCHAR *FireToBeginString, *FireToContinueString;
static TCHAR *DevelopedByString;

static HANDLE GunSightTexture, MissileLockTexture;
static HANDLE RadarBaseTexture, RadarFlareTexture;
static HANDLE IconTurretTexture, IconSmartBombTexture, 
			  IconRapidFireTexture, IconExplosiveTipTexture,
			  IconSeekerTexture, IconBuildingTexture;
static HANDLE TSLogoTexture;

static int PowerUpDroneID=0, SFighterID, MFighterID, BomberID, PowerUpID, BuildingID;

// Initialize the Head up Display
BOOL InitHUD(void)
{
	// Initialize overlay vertices.
	OverlayVerts[0].Z=OverlayVerts[1].Z=OverlayVerts[2].Z=OverlayVerts[3].Z=0;
	OverlayVerts[0].InvW=OverlayVerts[1].InvW=OverlayVerts[2].InvW=OverlayVerts[3].InvW=1;
	OverlayVerts[0].Color=OverlayVerts[1].Color=OverlayVerts[2].Color=OverlayVerts[3].Color=0xAF000000;
	OverlayVerts[0].X=0;
	OverlayVerts[0].Y=0;
	OverlayVerts[1].X=(float)gGraphics.GetFrameBufferResX();
	OverlayVerts[1].Y=0;
	OverlayVerts[2].X=0;
	OverlayVerts[2].Y=(float)gGraphics.GetFrameBufferResY();
	OverlayVerts[3].X=(float)gGraphics.GetFrameBufferResX();
	OverlayVerts[3].Y=(float)gGraphics.GetFrameBufferResY();

	// Load and initialize help string.
	HelpTitle=LoadTextString(IDS_HELP_TITLE);
	HelpTitleWidth=(float)GetMaxLineLength(HelpTitle);
	HelpString=LoadTextString(IDS_HELP);
	HelpLines=(float)GetNumLines(HelpString);
	HelpWidth=(float)GetMaxLineLength(HelpString);

	// Load other strings.
	FPSString=LoadTextString(IDS_FPS);
	TimePausedString=LoadTextString(IDS_TIME_PAUSED);
	TimePausedStringLength=(float)GetMaxLineLength(TimePausedString);
	GodModeString=LoadTextString(IDS_GOD_MODE);
	GodModeStringLength=(float)GetMaxLineLength(GodModeString);
	GameOverString=LoadTextString(IDS_GAME_OVER);
	StageString=LoadTextString(IDS_STAGE);
	ReachedStageString=LoadTextString(IDS_REACHED_STAGE);
	DemoRecordingString=LoadTextString(IDS_RECORDING_DEMO);
	DefenseMarkString=LoadTextString(IDS_DEFENSEMARK);
	FireToBeginString=LoadTextString(IDS_FIRE_TO_BEGIN);
	FireToContinueString=LoadTextString(IDS_FIRE_TO_CONTINUE);
	DevelopedByString=LoadTextString(IDS_DEVELOPED_BY);

	// Load HUD textures.
	GunSightTexture=
		gGraphics.AddTexture(ReadImageFileIntensityToAlphaNotMipmapped,TEXT("GunSight"),TRUE,FALSE);
	MissileLockTexture=
		gGraphics.AddTexture(ReadImageFileIntensityToAlphaNotMipmapped,TEXT("MissileLock"),TRUE,FALSE);
	RadarBaseTexture=
		gGraphics.AddTexture(ReadImageFileIntensityToAlphaNotMipmapped,TEXT("RadarBase"),TRUE,FALSE);
	RadarFlareTexture=
		gGraphics.AddTexture(ReadImageFileIntensityToAlphaNotMipmapped,TEXT("RadarFlare"),TRUE,FALSE);

	IconTurretTexture=
		gGraphics.AddTexture(ReadImageFileIntensityToAlphaNotMipmapped,TEXT("IconTurret"),TRUE,FALSE);
	IconSmartBombTexture=
		gGraphics.AddTexture(ReadImageFileIntensityToAlphaNotMipmapped,TEXT("IconSmartBomb"),TRUE,FALSE);
	IconRapidFireTexture=
		gGraphics.AddTexture(ReadImageFileIntensityToAlphaNotMipmapped,TEXT("IconRapidFire"),TRUE,FALSE);
	IconExplosiveTipTexture=
		gGraphics.AddTexture(ReadImageFileIntensityToAlphaNotMipmapped,TEXT("IconExplosiveTip"),TRUE,FALSE);
	IconSeekerTexture=
		gGraphics.AddTexture(ReadImageFileIntensityToAlphaNotMipmapped,TEXT("IconSeeker"),TRUE,FALSE);
	IconBuildingTexture=
		gGraphics.AddTexture(ReadImageFileIntensityToAlphaNotMipmapped,TEXT("IconBuilding"),TRUE,FALSE);

	TSLogoTexture=
		gGraphics.AddTexture(ReadImageFilePlusAlphaNotMipmapped,TEXT("TSLogo"),TRUE,FALSE);

	return TRUE;
}

// Shutdown the Head up Display.
void ShutdownHUD(void)
{
	// Free text strings.
#define SAFE_FREE(a) { if (a) { DCFree(a); a=NULL; } }
	SAFE_FREE(HelpTitle);
	SAFE_FREE(HelpString);
	SAFE_FREE(FPSString);
	SAFE_FREE(TimePausedString);
	SAFE_FREE(GodModeString);
	SAFE_FREE(GameOverString);
	SAFE_FREE(StageString);
	SAFE_FREE(ReachedStageString);
	SAFE_FREE(DemoRecordingString);
	SAFE_FREE(DefenseMarkString);
	SAFE_FREE(FireToBeginString);
	SAFE_FREE(FireToContinueString);
#undef SAFE_FREE
}

// Figures out where a 3D point maps onto the screen.
static BOOL GetPointScreenMapping(float &X, float &Y, DCVector &Loc)
{
	// Get into view coords.
#define M gRender.Frame.ViewMatrix
	DCVector View=DCVector(M.m11*Loc.X + M.m21*Loc.Y + M.m31*Loc.Z + M.m41,
						   M.m12*Loc.X + M.m22*Loc.Y + M.m32*Loc.Z + M.m42,
						   M.m13*Loc.X + M.m23*Loc.Y + M.m33*Loc.Z + M.m43);
#undef M
	if (View.Z < gRender.Frame.ZNear) // Make sure in front of clipping plane.
		return FALSE;
	// Get into clip coords. W held in Z member.
#define M gRender.Frame.ProjectionMatrix
	DCVector Clip=DCVector(M.m11*View.X + M.m21*View.Y + M.m31*View.Z + M.m41,
						   M.m12*View.X + M.m22*View.Y + M.m32*View.Z + M.m42,
						   M.m14*View.X + M.m24*View.Y + M.m34*View.Z + M.m44);
#undef M
	// Do perspective division and convert to screen coordinates.
	float Recip=0.5f/Clip.Z;
	X=(Clip.X*Recip + 0.5f)*DCW_RESX2D;
	Y=(Clip.Y*-Recip + 0.5f)*DCW_RESY2D;

	return TRUE;
}


// Renders a 2D icon.
static void RenderIcon(float X1, float Y1, float X2, float Y2, HANDLE Texture, DWORD Color)
{
	DCVertex V[4];

	X1=X1*gGraphics.ScaleX2D + gGraphics.TransX2D;
	Y1=Y1*gGraphics.ScaleY2D + gGraphics.TransY2D;
	X2=X2*gGraphics.ScaleX2D + gGraphics.TransX2D;
	Y2=Y2*gGraphics.ScaleY2D + gGraphics.TransY2D;

	V[0].X=X1; V[0].Y=Y1; V[0].Z=0; V[0].InvW=1; V[0].Color=Color; V[0].U=0, V[0].V=1;
	V[1].X=X2; V[1].Y=Y1; V[1].Z=0; V[1].InvW=1; V[1].Color=Color; V[1].U=1, V[1].V=1;
	V[2].X=X1; V[2].Y=Y2; V[2].Z=0; V[2].InvW=1; V[2].Color=Color; V[2].U=0, V[2].V=0;
	V[3].X=X2; V[3].Y=Y2; V[3].Z=0; V[3].InvW=1; V[3].Color=Color; V[3].U=1, V[3].V=0;

	gGraphics.SetTexture(Texture);
	gGraphics.Strip(V,4);
}

// Renders a 2D icon with the specified UV coordinates.
static void RenderIconUV(float X1, float Y1, float X2, float Y2, 
						 float U1, float V1, float U2, float V2, 
						 HANDLE Texture, DWORD Color)
{
	DCVertex V[4];

	X1=X1*gGraphics.ScaleX2D + gGraphics.TransX2D;
	Y1=Y1*gGraphics.ScaleY2D + gGraphics.TransY2D;
	X2=X2*gGraphics.ScaleX2D + gGraphics.TransX2D;
	Y2=Y2*gGraphics.ScaleY2D + gGraphics.TransY2D;

	V[0].X=X1; V[0].Y=Y1; V[0].Z=0; V[0].InvW=1; V[0].Color=Color; V[0].U=U1, V[0].V=V1;
	V[1].X=X2; V[1].Y=Y1; V[1].Z=0; V[1].InvW=1; V[1].Color=Color; V[1].U=U2, V[1].V=V1;
	V[2].X=X1; V[2].Y=Y2; V[2].Z=0; V[2].InvW=1; V[2].Color=Color; V[2].U=U1, V[2].V=V2;
	V[3].X=X2; V[3].Y=Y2; V[3].Z=0; V[3].InvW=1; V[3].Color=Color; V[3].U=U2, V[3].V=V2;

	gGraphics.SetTexture(Texture);
	gGraphics.Strip(V,4);
}

// Renders a 2D icon. Won't be scaled in on a TV.
static void RenderIconNoShrink(float X1, float Y1, float X2, float Y2, HANDLE Texture, DWORD Color)
{
	DCVertex V[4];

	X1=X1*gGraphics.ScaleX2DNoShrink + gGraphics.TransX2DNoShrink;
	Y1=Y1*gGraphics.ScaleY2DNoShrink + gGraphics.TransY2DNoShrink;
	X2=X2*gGraphics.ScaleX2DNoShrink + gGraphics.TransX2DNoShrink;
	Y2=Y2*gGraphics.ScaleY2DNoShrink + gGraphics.TransY2DNoShrink;

	V[0].X=X1; V[0].Y=Y1; V[0].Z=0; V[0].InvW=1; V[0].Color=Color; V[0].U=0, V[0].V=1;
	V[1].X=X2; V[1].Y=Y1; V[1].Z=0; V[1].InvW=1; V[1].Color=Color; V[1].U=1, V[1].V=1;
	V[2].X=X1; V[2].Y=Y2; V[2].Z=0; V[2].InvW=1; V[2].Color=Color; V[2].U=0, V[2].V=0;
	V[3].X=X2; V[3].Y=Y2; V[3].Z=0; V[3].InvW=1; V[3].Color=Color; V[3].U=1, V[3].V=0;

	gGraphics.SetTexture(Texture);
	gGraphics.Strip(V,4);
}

// Renders a 2D icon with the specified UV coordinates. Won't be scaled in on a TV.
static void RenderIconUVNoShrink(float X1, float Y1, float X2, float Y2, 
						 float U1, float V1, float U2, float V2, 
						 HANDLE Texture, DWORD Color)
{
	DCVertex V[4];

	X1=X1*gGraphics.ScaleX2DNoShrink + gGraphics.TransX2DNoShrink;
	Y1=Y1*gGraphics.ScaleY2DNoShrink + gGraphics.TransY2DNoShrink;
	X2=X2*gGraphics.ScaleX2DNoShrink + gGraphics.TransX2DNoShrink;
	Y2=Y2*gGraphics.ScaleY2DNoShrink + gGraphics.TransY2DNoShrink;

	V[0].X=X1; V[0].Y=Y1; V[0].Z=0; V[0].InvW=1; V[0].Color=Color; V[0].U=U1, V[0].V=V1;
	V[1].X=X2; V[1].Y=Y1; V[1].Z=0; V[1].InvW=1; V[1].Color=Color; V[1].U=U2, V[1].V=V1;
	V[2].X=X1; V[2].Y=Y2; V[2].Z=0; V[2].InvW=1; V[2].Color=Color; V[2].U=U1, V[2].V=V2;
	V[3].X=X2; V[3].Y=Y2; V[3].Z=0; V[3].InvW=1; V[3].Color=Color; V[3].U=U2, V[3].V=V2;

	gGraphics.SetTexture(Texture);
	gGraphics.Strip(V,4);
}

struct RadarCallbackStruct
{
	DCVertex V[4];
	float SinA,CosA;
};

static void RadarCallback(EntityBase *Entity, void *User)
{
	RadarCallbackStruct *RadarData=(RadarCallbackStruct *)User;

	DCVector Loc,Rot;
	Entity->GetPosition(&Loc,&Rot);

	float WorldR=FastSqrt(Loc.X*Loc.X + Loc.Z*Loc.Z);
	if (WorldR > RADAR_RANGE)
		return;

	float X=(Loc.X*RadarData->CosA - Loc.Z*RadarData->SinA)*(RADAR_INNER_R/RADAR_RANGE)+RADAR_X;
	float Z=(Loc.X*RadarData->SinA + Loc.Z*RadarData->CosA)*(-RADAR_INNER_R/RADAR_RANGE)+RADAR_Y;
	float R;
	if (Entity->ClassID==PowerUpID)
		R=1.0f;
	else if (Entity->ClassID==PowerUpDroneID)
		R=1.6f;
	else if (Entity->ClassID==SFighterID)
		R=2.0f;
	else if (Entity->ClassID==MFighterID)
		R=2.0f;
	else if (Entity->ClassID==BomberID)
		R=2.5f;
	else
		R=1.5f;

	float X1=(X-R)*gGraphics.ScaleX2D + gGraphics.TransX2D;
	float Y1=(Z-R)*gGraphics.ScaleY2D + gGraphics.TransY2D;
	float X2=(X+R)*gGraphics.ScaleX2D + gGraphics.TransX2D;
	float Y2=(Z+R)*gGraphics.ScaleY2D + gGraphics.TransY2D;

	DCVertex *V=RadarData->V;
	V[0].X=X1; V[0].Y=Y1;
	V[1].X=X2; V[1].Y=Y1;
	V[2].X=X1; V[2].Y=Y2;
	V[3].X=X2; V[3].Y=Y2;

	gGraphics.Strip(V,4);
}

// Render HUD items for player view.
void RenderPlayerHUD(void)
{
	// Get HUD info from player.
	BOOL HaveHUDInfo=FALSE;
	HUDInfo Info;
	EntityBase *Player=gGame.GetPlayerEntity();
	if (Player)
	{
		DWORD Message[2];
		Message[0]=2;
		Message[1]=(DWORD)&Info;
		if (Player->Message(Message))
			HaveHUDInfo=TRUE;
	}
	
	float Size=20;
	DWORD BaseAlpha=0xAF000000;
	DWORD ShadedAlpha=(BaseAlpha>>2) & 0xFF000000;
	DWORD BaseColor=0x004FFF4F;

	if (HaveHUDInfo && !gGame.IsClient())
	{
		// Missile lock.
		if (Info.MissileTargetStatus)
		{
			float X,Y;
			if (GetPointScreenMapping(X,Y,Info.MissileTarget))
			{
				if (Info.MissileTargetStatus==1)
					RenderIconUVNoShrink(X-5,Y-5,X+5,Y+5,0.25f,0.25f,0.75f,0.75f,MissileLockTexture,0xFFFF3F3F);
				else
					RenderIconNoShrink(X-10,Y-10,X+10,Y+10,MissileLockTexture,0xFFFF3F3F);
			}
		}
		// Bomb icons.
		for (int i=0;i<Info.SmartBombCount && i<10;i++)
			RenderIcon(Size*(i*0.5f+0.25f),DCW_RESY2D-Size*1.5f,
					   Size*(i*0.5f+0.75f),DCW_RESY2D-Size*0.5f,
					   IconSmartBombTexture,BaseColor | BaseAlpha);
		// Turret icon.
		DWORD EnergyColor;
		float TurretVPos=0.0f;
		if (Info.Energy<0.2f)
			EnergyColor=0x00FF0000;
		else
			EnergyColor=BaseColor;
		RenderIcon(DCW_RESX2D-Size*1.75f,DCW_RESY2D-Size*(TurretVPos+1.5f),
				   DCW_RESX2D-Size*0.75f,DCW_RESY2D-Size*(TurretVPos+0.5f),
				   IconTurretTexture,EnergyColor | BaseAlpha);

		// Power up.
		if (Info.CurrentFire)
		{
			float VPos=1.0f;
			// Icon.
			HANDLE Texture;
			if (Info.CurrentFire==1)
				Texture=IconSeekerTexture;
			else if (Info.CurrentFire==2)
				Texture=IconExplosiveTipTexture;
			else 
				Texture=IconRapidFireTexture;

			RenderIcon(DCW_RESX2D-Size*1.75f,DCW_RESY2D-Size*(VPos + 1.375f),
					   DCW_RESX2D-Size*0.25f,DCW_RESY2D-Size*(VPos + 0.625f),
					   Texture,BaseColor | BaseAlpha);

			// Amount.
			float Amount=(Info.FireCount>400 ? 400 : Info.FireCount) / 200.0f;
			RenderIcon(DCW_RESX2D-Size*(2.0f+2.0f*Amount),DCW_RESY2D-Size*(VPos + 1.20f),
					   DCW_RESX2D-Size*2.0f,DCW_RESY2D-Size*(VPos + 0.80f),
					   NULL,BaseColor | BaseAlpha);
		}

		// Turret energy.
		RenderIcon(DCW_RESX2D-Size*4.0f,DCW_RESY2D-Size*(TurretVPos+1.20f),
				   DCW_RESX2D-Size*(2.0f+2.0f*Info.Energy),DCW_RESY2D-Size*(TurretVPos+0.80f),
				   NULL,EnergyColor | ShadedAlpha);
		RenderIcon(DCW_RESX2D-Size*(2.0f+2.0f*Info.Energy),DCW_RESY2D-Size*(TurretVPos+1.20f),
				   DCW_RESX2D-Size*2.0f,DCW_RESY2D-Size*(TurretVPos+0.80f),
				   NULL,EnergyColor | BaseAlpha);
	}

	// Building energy.
	EntityBase *Lord=gGame.GetLordEntity();
	if (Lord && !gGame.IsClient())
	{
		union
		{
			float F;
			void *V;
		} Energy;
		Energy.V=Lord->Message((void *)2); // "Get city energy" message.

		// Building icon.
		DWORD EnergyColor;
		if (Energy.F<0.2f)
			EnergyColor=0x00FF0000;
		else
			EnergyColor=BaseColor;
		float VPos=0.0f;
		float HShift=-Size*3.5f;
		RenderIcon(HShift + DCW_RESX2D-Size*1.75f,DCW_RESY2D-Size*(VPos+1.5f),
				   HShift + DCW_RESX2D-Size*0.75f,DCW_RESY2D-Size*(VPos+0.5f),
				   IconBuildingTexture,EnergyColor | BaseAlpha);

		// Buildings energy.
		RenderIcon(HShift + DCW_RESX2D-Size*4.0f,DCW_RESY2D-Size*(VPos+1.20f),
				   HShift + DCW_RESX2D-Size*(2.0f+2.0f*Energy.F),DCW_RESY2D-Size*(VPos+0.80f),
				   NULL,EnergyColor | ShadedAlpha);
		RenderIcon(HShift + DCW_RESX2D-Size*(2.0f+2.0f*Energy.F),DCW_RESY2D-Size*(VPos+1.20f),
				   HShift + DCW_RESX2D-Size*2.0f,DCW_RESY2D-Size*(VPos+0.80f),
				   NULL,EnergyColor | BaseAlpha);
	}

	// Radar.
	if (PowerUpDroneID==0)
	{
		PowerUpDroneID=gGame.GetEntityIDFromName(TEXT("EntityPowerUpDrone"));
		SFighterID=gGame.GetEntityIDFromName(TEXT("EntitySFighter"));
		MFighterID=gGame.GetEntityIDFromName(TEXT("EntityMFighter"));
		BomberID=gGame.GetEntityIDFromName(TEXT("EntityBomber"));
		PowerUpID=gGame.GetEntityIDFromName(TEXT("EntityPowerUpSpinner"));
		BuildingID=gGame.GetEntityIDFromName(TEXT("EntityBuilding"));
	}

	RenderIcon(RADAR_X-RADAR_R, RADAR_Y-RADAR_R,
			   RADAR_X+RADAR_R, RADAR_Y+RADAR_R,
			   RadarBaseTexture, ShadedAlpha | BaseColor);

	RenderIconUV(RADAR_X-3.5,RADAR_Y-3.5,RADAR_X+3.5,RADAR_Y+3.5,
				 0.25f,0.25f,0.75f,0.75f,MissileLockTexture, BaseAlpha | BaseColor);

	RadarCallbackStruct RadarData;
	DCVertex *V=RadarData.V;
	DWORD Color=Color=BaseAlpha | BaseColor;
	V[0].Z=0; V[0].InvW=1; V[0].Color=Color; V[0].U=0, V[0].V=1;
	V[1].Z=0; V[1].InvW=1; V[1].Color=Color; V[1].U=1, V[1].V=1;
	V[2].Z=0; V[2].InvW=1; V[2].Color=Color; V[2].U=0, V[2].V=0;
	V[3].Z=0; V[3].InvW=1; V[3].Color=Color; V[3].U=1, V[3].V=0;
	RadarData.SinA=(float)sin(-gRender.Frame.ViewRot.Y);
	RadarData.CosA=(float)cos(-gRender.Frame.ViewRot.Y);
	gGraphics.SetTexture(RadarFlareTexture);
	gGame.GetCollisionEntities(COLLISION_BADDIE,RadarCallback,&RadarData);

	// Gun sight.
	float SightSize=9;
	RenderIconNoShrink(DCW_RESX2D*0.5f - SightSize, DCW_RESY2D*0.5f+2 - SightSize,
			   DCW_RESX2D*0.5f + SightSize, DCW_RESY2D*0.5f+2 + SightSize,
			   GunSightTexture,0xFFFFFFFF);
}

// Render HUD items for all views.
void RenderGenericHUD(void)
{	
	// Render any generic HUD text.
	TCHAR Buffer[0x100];
	RenderTextBegin();

	// Render stage/game over message.
	static int LastStage=1;
	// We check to see if the lord entity exists. If it doesn't exist, the game isn't over,
	// the entities just haven't been loaded yet.
	if (!gGame.IsClient())
	{
		if (!gGame.GetPlayerEntity() && gGame.GetLordEntity() && !gGame.IsDemoPlayback())
		{
			RenderText(GameOverString,
					   DCW_RESX2D*0.5f - FONT_SIZE_LARGE*lstrlen(GameOverString)*0.5f,
					   DCW_RESY2D*0.5f - FONT_SIZE_LARGE*2,
					   FONT_SIZE_LARGE);

			wsprintf(Buffer,ReachedStageString,LastStage);
			RenderText(Buffer,
					   DCW_RESX2D*0.5f - FONT_SIZE_MEDIUM*lstrlen(Buffer)*0.5f,
					   DCW_RESY2D*0.5f - FONT_SIZE_LARGE*0.5f,
					   FONT_SIZE_MEDIUM);
		}
		else
		{
			EntityBase *Lord=gGame.GetLordEntity();
			if (Lord)
			{
				int Stage=(int)Lord->Message(0);
				if (Stage)
				{
					LastStage=Stage;
					wsprintf(Buffer,StageString,Stage);
					RenderText(Buffer,
							   DCW_RESX2D*0.5f - FONT_SIZE_LARGE*lstrlen(Buffer)*0.5f,
							   DCW_RESY2D*0.5f - FONT_SIZE_LARGE*2,
							   FONT_SIZE_LARGE);
				}
			}
		}
	}

	// Display FPS if enabled.
	if (gDisplayStats)
	{
		wsprintf(Buffer,FPSString,(int)(1.0f/gGame.GetAppFrameDeltaTime()));
		RenderText(Buffer,DCW_RESX2D-FONT_SIZE_SMALL*8.5f,FONT_SIZE_SMALL*0.5f,FONT_SIZE_SMALL);
		
		// Print net stats if any.
		int Rec,Send,Packets,Data;
		GetNetStats(&Rec,&Send,&Packets,&Data);
		if (Rec || Send)
		{
			wsprintf(Buffer,TEXT("%i %i"),Rec,Send);
			RenderText(Buffer,DCW_RESX2D-FONT_SIZE_SMALL*7.5f,FONT_SIZE_SMALL*4.5f,FONT_SIZE_SMALL);
			int Bps=(int)((float)Send/gGame.GetAppFrameDeltaTime());
			wsprintf(Buffer,TEXT("(%5i)"),Bps);
			RenderText(Buffer,DCW_RESX2D-FONT_SIZE_SMALL*7.0f,FONT_SIZE_SMALL*5.5f,FONT_SIZE_SMALL,
					   (Bps > 115200/9) ? 0xFFFF0000 : 0xFFFFFFFF);
		}
		if (Packets || Data)
		{
			wsprintf(Buffer,TEXT("%i %i"),Packets,Data);
			RenderText(Buffer,DCW_RESX2D-FONT_SIZE_SMALL*(__max(lstrlen(Buffer),7)+0.5f),
					   FONT_SIZE_SMALL*6.5f,FONT_SIZE_SMALL);
		}
	}
	if (gGame.IsTimePaused())
	{
		RenderText(TimePausedString,
				   DCW_RESX2D-FONT_SIZE_TINY*(TimePausedStringLength+0.5f),
				   FONT_SIZE_SMALL*1.5f,
				   FONT_SIZE_TINY);
	}
	if (gGame.IsGodMode())
	{
		RenderText(GodModeString,
				   DCW_RESX2D-FONT_SIZE_TINY*(GodModeStringLength+0.5f),
				   FONT_SIZE_SMALL*1.5f+FONT_SIZE_TINY,
				   FONT_SIZE_TINY);
	}
	if (gGame.IsRecordingDemo())
	{
		RenderText(DemoRecordingString,
				   DCW_RESX2D-FONT_SIZE_TINY*(GetMaxLineLength(DemoRecordingString)+0.5f),
				   FONT_SIZE_SMALL*1.5f+FONT_SIZE_TINY*2,
				   FONT_SIZE_TINY);
	}
	if (gGame.GetTimeDemoFps())
	{
		RenderTextEnd();

		// Render translucent black overlay.
		gGraphics.SetTexture(NULL);
		OverlayVerts[0].Color=OverlayVerts[1].Color=OverlayVerts[2].Color=OverlayVerts[3].Color=0xAF000000;
		gGraphics.Strip(OverlayVerts,4);

		RenderTextBegin();
		// Render fps.
		wsprintf(Buffer,DefenseMarkString,(int)(gGame.GetTimeDemoFps()),(int)(gGame.GetTimeDemoFps()*10)%10);
		RenderText(Buffer,
				   DCW_RESX2D*0.5f - FONT_SIZE_MEDIUMLARGE*lstrlen(Buffer)*0.5f,
				   DCW_RESY2D*0.5f - FONT_SIZE_MEDIUMLARGE*2,
				   FONT_SIZE_MEDIUMLARGE);

		RenderText(FireToContinueString,
				   DCW_RESX2D*0.5f - FONT_SIZE_MEDIUM*lstrlen(FireToContinueString)*0.5f,
				   DCW_RESY2D*0.5f - FONT_SIZE_MEDIUMLARGE*0.5f,
				   FONT_SIZE_MEDIUM);
	}
	if (gGame.IsDemoPlayback() && !gGame.IsTimeDemo())
	{
		RenderText(FireToBeginString,
				   DCW_RESX2D*0.5f - FONT_SIZE_MEDIUM*lstrlen(FireToBeginString)*0.5f,
				   DCW_RESY2D*0.5f + FONT_SIZE_MEDIUM*1.75f,
				   FONT_SIZE_MEDIUM);
	}
	
	if (gGame.IsClient() && !gGame.IsTimeDemo())
	{
#define DB_FONT_SIZE 4
		RenderText(DevelopedByString,
				   DCW_RESX2D*0.5f - DB_FONT_SIZE*lstrlen(DevelopedByString)*0.5f,
				   DB_FONT_SIZE*0.25f,
				   DB_FONT_SIZE);
	}

	RenderTextEnd();

	if (gGame.IsClient() && !gGame.IsTimeDemo())
	{
#define LOGO_WIDTH 180.0f
		RenderIconUV(DCW_RESX2D*0.5f - LOGO_WIDTH*0.5f, DB_FONT_SIZE*1.5f,
				   DCW_RESX2D*0.5f + LOGO_WIDTH*0.5f, DB_FONT_SIZE*1.5f + LOGO_WIDTH*89.0f/512.0f,
				   0.0f, 1.0f, 1.0f, 1.0f-89.0f/128.0f,
				   TSLogoTexture,0xFFFFFFFF);
#undef LOGO_WIDTH
#undef DB_FONT_SIZE
	}
}

// Render help overlay.
void RenderHelpOverlay(void)
{
	// Render translucent black overlay.
	gGraphics.SetTexture(NULL);
	OverlayVerts[0].Color=OverlayVerts[1].Color=OverlayVerts[2].Color=OverlayVerts[3].Color=0xAF000000;
	gGraphics.Strip(OverlayVerts,4);

	// Render help text.
	RenderTextBegin();
	RenderText(HelpTitle,(DCW_RESX2D-HelpTitleWidth*FONT_SIZE_MEDIUM)*0.5f,
			   (DCW_RESY2D-HelpLines*FONT_SIZE_MEDIUM)*0.5f,FONT_SIZE_MEDIUM);
	RenderText(HelpString,(DCW_RESX2D-HelpWidth*FONT_SIZE_MEDIUM)*0.5f,
			   (DCW_RESY2D-HelpLines*FONT_SIZE_MEDIUM)*0.5f,FONT_SIZE_MEDIUM);
	RenderTextEnd();
}

// Renders the screen flash if there is one.
void RenderFlash()
{
	float FlashIntensity=gGame.GetFlashIntensity();
	if (FlashIntensity)
	{
		gGraphics.BlendMode(BLEND_OTHERCOLOR,BLEND_OTHERCOLOR);
		gGraphics.SetTexture(NULL);

		// Calculate total intensity.
		FlashIntensity+=1.0f;
		if (FlashIntensity>4.0f)
			FlashIntensity=4.0f;
		
		// Render passes necessary to get flash intensity greater than 2.
		while (FlashIntensity > 2.0f)
		{
			OverlayVerts[0].Color=OverlayVerts[1].Color=OverlayVerts[2].Color=OverlayVerts[3].Color=0xFFFFFFFF;
			gGraphics.Strip(OverlayVerts,4);
			FlashIntensity*=0.5f;
		}

		// Calculate color necessary to get intensity we want.
		DWORD I=(DWORD)(FlashIntensity*128.0f);
		I=__max(0,__min(255,I));
		DWORD Color=0xFF000000 | (I << 16) | (I << 8) | I;

		OverlayVerts[0].Color=OverlayVerts[1].Color=OverlayVerts[2].Color=OverlayVerts[3].Color=Color;
		gGraphics.Strip(OverlayVerts,4);
		
		gGraphics.BlendMode(BLEND_SRCALPHA,BLEND_INVSRCALPHA);

		// Set the flash intensity to zero just to make sure flash doesn't last forever.
		gGame.SetFlashIntensity(0.0f);
	}
}
