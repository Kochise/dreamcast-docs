/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GAMain.cpp

Abstract:

    Game management - main functions.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCNetwork.h"

// Define globals here.
GameClass gGame;

// Functions to interface to the game class.
BOOL GameInit(void)
{
	return gGame.Initialize();
}

void GameShutdown(void)
{
	gGame.Shutdown();
}

void GameTickFrame(void)
{
	gGame.TickFrame();
}

// Initializes the game class.
BOOL GameClass::Initialize(void)
{
	// Initialize everything to 0.
	DCZeroMemory(this,sizeof(GameClass));

	// Init time.
	ThisFrameAbsTime=TimerGetGameTime();
	ThisFrameAppAbsTime=TimerGetAppTime();

	// Initialize view. 
	SetObserverMode(OFF);

	Initialized=TRUE;

	NetBuffer[0]=GNM_MULTIMESSAGE;
	NetBufferIndex=1;

	// Init demo playback.
	InitDemoPlayback();

	// Start a demo game running.
	CreateGame(IsNetworkClient() ? NETWORK_CLIENT : DEMO);

	return TRUE;
}

// Shuts down the game class.
void GameClass::Shutdown(void)
{
	// Kill of any game that is running.
	DestroyGame();
	
	// Shutdown demo playback.
	ShutdownDemoPlayback();

	Initialized=FALSE;
}

// Handles an input event.
void GameClass::InputEvent(GameInputControl Control, int Event)
{
	switch (Control)
	{
		case INPUT_STARTBUTTON:
			if (Event)
			{
				if (IsDemoPlayback())
					StartPressed();
				else if (!IsClient())
					EndPressed();
				break;
			}
		case INPUT_STARTGAME:
			if (Event)
				StartPressed();
			break;
		case INPUT_ENDGAME:
			if (Event)
				EndPressed();
			break;
		case INPUT_FIRE1:
			if (IsDemoPlayback())
			{
				if (Event)
					StartPressed();
			}
			else if (!GetPlayerEntity())
			{
				if (Event)
					EndPressed();
			}
			else
				Controls.Fire1Down=(Event) ? TRUE : FALSE;
			break;
		case INPUT_FIRE2:
			if (IsDemoPlayback())
			{
				if (Event)
					StartPressed();
			}
			else if (!GetPlayerEntity())
			{
				if (Event)
					EndPressed();
			}
			else
				Controls.Fire2Down=(Event) ? TRUE : FALSE;
			break;
		case INPUT_FIRE3:
			if (IsDemoPlayback())
			{
				if (Event)
					StartPressed();
			}
			else if (!GetPlayerEntity())
			{
				if (Event)
					EndPressed();
			}
			else
				Controls.Fire3Down=(Event) ? TRUE : FALSE;
			break;
		case INPUT_FORWARD:
			Controls.ForwardDown=(Event) ? TRUE : FALSE;
			break;
		case INPUT_BACKWARD:
			Controls.BackwardDown=(Event) ? TRUE : FALSE;
			break;
		case INPUT_LEFTSTRAFE:
			Controls.StrafeLeftDown=(Event) ? TRUE : FALSE;
			break;
		case INPUT_RIGHTSTRAFE:
			Controls.StrafeRightDown=(Event) ? TRUE : FALSE;
			break;
		case INPUT_HELP:
			if (Event)
				SetDisplayHelp(TOGGLE);
			break;
		case INPUT_PAUSETIME:
			if (Event && !IsClient())
				SetPauseTime(TOGGLE);
			break;
		case INPUT_OBSERVERTOGGLE:
			if (Event && GetPlayerEntity() && !IsTimeDemo()) // Can't toggle observer mode if you're dead.
				SetObserverMode(TOGGLE);
			break;
		case INPUT_GODMODETOGGLE:
			if (Event && !IsClient())
				SetGodMode(TOGGLE);
			break;
		case INPUT_MOUSEX:
			Controls.MouseMoveX+=Event;
			break;
		case INPUT_MOUSEY:
			Controls.MouseMoveY+=Event;
			break;
		case INPUT_JOYX:
			Controls.JoyX=Event;
			break;
		case INPUT_JOYY:
			Controls.JoyY=Event;
			break;
		case INPUT_START_DEMO_RECORD:
			StartDemoRecord();
			break;
		case INPUT_END_DEMO_RECORD:
			EndDemoRecord();
			break;
		case INPUT_TIMEDEMO:
			if (!IsTimeDemo())
				StartTimeDemo();
			break;
	}
}

// Returns the new state of a toggle based on the current state
// and the control mode.
BOOL GameClass::GetNewToggleState(BOOL CurrentState, GameToggleControl Control)
{
	if (Control==OFF)
		return FALSE;
	else if (Control==ON)
		return TRUE;
	else // Control==TOGGLE
		if (CurrentState)
			return FALSE;
		else
			return TRUE;
}
