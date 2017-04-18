/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GAState.cpp

Abstract:

    Game management - game state.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"

// Toggles whether game time is paused or not.
void GameClass::SetPauseTime(GameToggleControl Control)
{
	switch (Control)
	{
		case OFF:	
			if (!State.TimeIsPaused)
			{
				State.TimeIsPaused=TRUE;
				TimerPauseGameTime();
			}
			break;
		case ON:
			if (State.TimeIsPaused)
			{
				State.TimeIsPaused=FALSE;
				TimerUnpauseGameTime();
			}
			break;
		case TOGGLE:
			if (State.TimeIsPaused)
			{
				State.TimeIsPaused=FALSE;
				TimerUnpauseGameTime();
			}
			else
			{
				State.TimeIsPaused=TRUE;
				TimerPauseGameTime();
			}
			break;
	}
	if (ClientCount)
		SendSimpleMessage(State.TimeIsPaused ? GNM_PAUSE_TIME : GNM_UNPAUSE_TIME);
}

// Toggles whether in god mode or not.
void GameClass::SetGodMode(GameToggleControl Control)
{
	State.GodMode=GetNewToggleState(State.GodMode,Control);
}

// Toggles whether the help screen is to be displayed or not.
void GameClass::SetDisplayHelp(GameToggleControl Control)
{
	State.DisplayHelp=GetNewToggleState(State.DisplayHelp,Control);
}

// Causes the game to start if there isn't a game running.
void GameClass::StartGame(void)
{
	// Make sure there isn't already something other than 
	// a demo running.
	if (State.GameRunning==GAME || State.GameRunning==NETWORK_CLIENT)
		return;
		
	if (State.GameRunning!=NONE)
	{
		// Kill existing game.
		DestroyGame();
	}

	// Start new game.
	CreateGame(GAME);
}	

// End whatever kind of game is running
// and then start the demo running.
void GameClass::EndGame(void)
{
	if (State.GameRunning!=NONE)
	{
		// Kill existing game.
		DestroyGame();
	}
	// Start a demo running.
	CreateGame(DEMO);
}

// Starts a demo timing sequence.
void GameClass::StartTimeDemo()
{
	if (State.GameRunning==NETWORK_CLIENT)
		return;

	EndGame();
	Demo.TimeDemo=TRUE;
}

// Handles a start pressed situation.
void GameClass::StartPressed()
{
	if (State.GameRunning==NETWORK_CLIENT)
		return;

	if (State.GameRunning==DEMO)
	{
		if (Demo.TimeDemo)
		{
			if (Demo.Fps)
				EndGame();
		}
		else
		{
			StartGame();
		}
	}
}

// Handles an end pressed situation.
void GameClass::EndPressed()
{
	if (State.GameRunning==NETWORK_CLIENT)
	{
		gAppExit=TRUE;
		return;
	}

	if ((State.GameRunning==DEMO && Demo.TimeDemo) || State.GameRunning==GAME)
		EndGame();
	else
		gAppExit=TRUE;
}
