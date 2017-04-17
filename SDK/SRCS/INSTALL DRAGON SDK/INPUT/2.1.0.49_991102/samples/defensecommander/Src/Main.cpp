/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    Main.cpp

Abstract:

    Main function for game which calls all other functions. Called
	from file which is entry point into game (e.g. WinMain.cpp).

-------------------------------------------------------------------*/

#define DEFINE_GLOBALS // Define globals in this file.
#include "DC.h"

// External functions.

//InitPC/DR.cpp
BOOL SystemInitialize(void);
void SystemShutdown(void);

//GAMain.cpp
BOOL GameInit(void);
void GameShutdown(void);
void GameTickFrame(void);

//Input.cpp
void ProcessInput(void);

//Intro.cpp
void DisplayIntroScreen(void);

//RMain.cpp
BOOL RenderInit(void);
void RenderShutdown(void);
void RenderScene(void);

// Mesh.cpp
BOOL MeshInit(void);
void MeshShutdown(void);

// Sound.cpp
BOOL LoadSounds();
void UnloadSounds();
void TickSound(void);

// Entry point into game.
int GameMain(void)
{	
	// Initialize video, sound etc.
	if (SystemInitialize())
	{
		// Display intro/credits screen.
		DisplayIntroScreen();

		// Get start time so we can make sure splash
		// doesn't go by too fast.
		TIMEVALUE StartTime=TimerGetSysTime();
	
		// Load sounds.
		if (LoadSounds())
		{
			// Load and initialize meshes.
			if (MeshInit())
			{
				// Initialize rendering functions.
				if (RenderInit())
				{
					// Just wait a while if necessary
					// so splash doesn't go by too fast.
					TimerWaitCoarse(StartTime,10.0f);

					// Initialize game functions.
					if (GameInit())
					{
						// Main game loop.
						for (;;)
						{
							// Process input. 
							// This function won't return while the app is paused.
							ProcessInput();

							// Break if exiting.
							if (gAppExit)
								break;

							// Process AI.
							GameTickFrame();

							// Render the scene.
							RenderScene();

							// Tick the sound.
							TickSound();
						}
						// Shutdown game functions.
						GameShutdown();
					}
					// Shutdown rendering functions.
					RenderShutdown();
				}
				// Shutdown/release meshes.
				MeshShutdown();
			}
			// Unload sounds.
			UnloadSounds();
		}
		// Shutdown video, sound etc.
		SystemShutdown();
	}
	return 0;
}
