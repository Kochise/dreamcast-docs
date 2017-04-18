/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    InitCE.cpp

Abstract:

    Windows CE specific initialization code.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"
#include "DCSound.h"
#include "DCInput.h"
#include "DCTimer.h"
#include "DCNetwork.h"

// Configuration.
static int ResX,ResY;
static BOOL Bits32,Windowed;

// Gets the user configuration. On Dreamcast the configuration is fixed.
BOOL GetUserConfig(void)
{
	ResX=640;
	ResY=480;
	Bits32=FALSE;
	Windowed=FALSE;
	gHighDetail=TRUE;
	gHighTextureDetail=FALSE;
	
	return TRUE;
}

//************************************************************************
// Global functions.
//************************************************************************
// Shutowns down video, audio etc.
void SystemShutdown(void)
{
	// Shutdown network.
	ShutdownNetwork();

	// Shutdown input.
	ShutdownInput(gGraphics.GetAppWindow());

	// Shutdown audio.
	ShutdownSound(gGraphics.GetAppWindow());

	// Shutdown video.
	gGraphics.Shutdown();

	// Shutdown timer.
	ShutdownTimer();

	// Shutdown noise.
	ShutdownNoise();
}

// Gets settings and then initializes video, audio etc.
BOOL SystemInitialize(void)
{
	// Init noise functions.
	if (!InitNoise())
		return FALSE;

	// Initlialize timer functions.
	if (!InitTimer())
	{
		SystemShutdown();
		return FALSE;
	}

	// Get user configuration.
	if (!GetUserConfig())
		return FALSE;
	
	// Initialize video by Initializing graphics class.
	if (!gGraphics.Initialize(NULL,
							  ResX,
							  ResY,
							  (Bits32) ? 32 : 16,
							  Windowed,
							  FALSE))
	{
		// Shutdown anything that got initialized.
		SystemShutdown();
		return FALSE;
	}

	// Initialize audio.
	if (!InitSound(gGraphics.GetAppWindow()))
	{
		SystemShutdown();
		return FALSE;
	}

	// Initialize input.
	if (!InitInput(gGraphics.GetAppWindow()))
	{
		SystemShutdown();
		return FALSE;
	}

	// Initialize network. Hard coded to server, port 1.
	if (!InitNetwork(TRUE,1))
	{
		SystemShutdown();
		return FALSE;
	}

	return TRUE;
}

