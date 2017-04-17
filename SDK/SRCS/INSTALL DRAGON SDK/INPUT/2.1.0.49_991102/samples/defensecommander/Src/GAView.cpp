/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GAView.cpp

Abstract:

    Game management - view control.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCCollide.h"

#define VIEW_VMIN DC_TO_RADIANS(-25)
#define VIEW_VMAX DC_TO_RADIANS(75)
#define VIEW_VMIN_OBS DC_TO_RADIANS(-90)
#define VIEW_VMAX_OBS DC_TO_RADIANS(90)

#define VIEW_MOVE 1000

// Enables or disables the observer mode.
void GameClass::SetObserverMode(GameToggleControl Control)
{
	// UpdatePlayerView will handle all the work later on,
	// we just need to toggle the boolean.
	View.Observer=GetNewToggleState(View.Observer,Control);
}

// Updates the view direction based on the mouse and joystick movement.
static inline  void UpdateDirection(DCVector &Rot,
									int &MouseMoveX, int &MouseMoveY,
									int &JoyX, int &JoyY,
									float VMin, float VMax,
									float FrameTime)
{
	// Handle mouse movement.
	Rot.Y-=(float)MouseMoveX * DC_TO_RADIANS(0.001f);
	Rot.X-=(float)MouseMoveY * DC_TO_RADIANS(0.001f);
	MouseMoveX=0;
	MouseMoveY=0;

	// Handle joystick position.
	Rot.Y-=(float)JoyX*FrameTime * DC_TO_RADIANS(0.001f);
	Rot.X+=(float)JoyY*FrameTime * DC_TO_RADIANS(0.001f);

	// Clamp movement.
	while (Rot.Y < 0)
		Rot.Y+=DC_PI*2;
	while (Rot.Y >= DC_PI*2)
		Rot.Y-=DC_PI*2;
	if (Rot.X < VMin)
		Rot.X=VMin;
	if (Rot.X > VMax)
		Rot.X=VMax;

	// Z rotation always zero.
	Rot.Z=0;
}

// Updates the view position based on button input.
static inline void UpdatePosition(DCVector &Loc,
								  DCVector &Rot,
								  BOOL StrafeLeft, BOOL StrafeRight,
								  BOOL Forward, BOOL Backward,
								  float FrameTime)
{
	if (Forward || Backward)
	{
		// Create vector from view angles.
		DCVector V1(0,0,1);
		V1.RotateX(Rot.X);
		V1.RotateY(Rot.Y);
		if (Forward)
			Loc+=V1 * ((float)VIEW_MOVE*FrameTime);
		if (Backward)
			Loc-=V1 * ((float)VIEW_MOVE*FrameTime);
	}
	
	if (StrafeLeft || StrafeRight)
	{
		// Create another vector just from horizonal angles.
		DCVector V2(0,0,1);
		V2.RotateY(Rot.Y+(DC_PI*0.5f));
		if (StrafeLeft)
			Loc+=V2 * ((float)VIEW_MOVE*FrameTime);
		if (StrafeRight)
			Loc-=V2 * ((float)VIEW_MOVE*FrameTime);
	}
}

// Update player view.
void GameClass::TickPlayerView(void)
{
	if (View.Observer)
	{
		// Save this in case collision runs into trouble.
		DCVector OrgLoc=View.Loc;

		// In observer mode. We can change position as well as direction.
		UpdateDirection(View.Rot,
						Controls.MouseMoveX,Controls.MouseMoveY,
						Controls.JoyX,Controls.JoyY,
						VIEW_VMIN_OBS,VIEW_VMAX_OBS,
						GetAppFrameDeltaTime());
		UpdatePosition(View.Loc,
					   View.Rot,
					   Controls.StrafeLeftDown,Controls.StrafeRightDown,
					   Controls.ForwardDown,Controls.BackwardDown,
					   GetAppFrameDeltaTime());

		// Handle collision.
		HandleObserverCollision(&View.Loc,&OrgLoc);
	}
	else
	{
		// We can change direction only.
		UpdateDirection(View.Rot,
						Controls.MouseMoveX,Controls.MouseMoveY,
						Controls.JoyX,Controls.JoyY,
						VIEW_VMIN,VIEW_VMAX,
						GetAppFrameDeltaTime());
	}
}

// Returns the current player view coordinates.
void GameClass::GetViewerCoords(DCVector *Loc, DCVector *Rot)
{
	*Loc=View.Loc;
	*Rot=View.Rot;
}

// Overrides the current player view coordinates.
void GameClass::SetViewerCoords(DCVector *Loc, DCVector *Rot)
{
	View.Loc=*Loc;
	View.Rot=*Rot;
}

// Forces the game into observer mode with a good viewing position.
void GameClass::ForceObserverMode()
{
	SetObserverMode(ON);
//	SetViewerCoords(&DCVector(142*6*1.7f,250,35*6*1.7f),&DCVector(0,DC_TO_RADIANS(104),0));
	SetViewerCoords(&DCVector(-724,470,1746),&DCVector(DC_TO_RADIANS(5),DC_TO_RADIANS(201),0));
}
