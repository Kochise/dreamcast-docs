/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GADemoPlayback.cpp

Abstract:

   Game management - Demo playback functions. 

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"

#define DEMO_FILE_NAME TEXT("DC.DEM")

void GameClass::InitDemoPlayback()
{
	Demo.Data=(BYTE *)ReadFileIntoMemory(ROOT_DIRECTORY,DEMO_FILE_NAME,(DWORD *)&Demo.DataSize);
}

void GameClass::ShutdownDemoPlayback()
{
	if (Demo.Data)
		DCFree(Demo.Data);
	Demo.DataSize=0;
}
	
void GameClass::StartDemoPlayback()
{
	Demo.CurrentPosition=0;
	Demo.CurrentTime=0;
	
	Demo.TimeDemo=FALSE;
	Demo.StartTime=Demo.EndTime=TimerGetGameTime();
	Demo.Frames=0;
	Demo.Fps=0;
}

// This is necessary to deal with data alignment issues on Dreamcast.
static float GetFloat(void *Buffer)
{
	union
	{
		BYTE b[4];
		float f;
	} U;
	
	U.b[0]=((BYTE *)Buffer)[0];
	U.b[1]=((BYTE *)Buffer)[1];
	U.b[2]=((BYTE *)Buffer)[2];
	U.b[3]=((BYTE *)Buffer)[3];
	
	return U.f;
}

void GameClass::TickDemoPlayback(float DeltaTime)
{
	if (!Demo.Data)
		return;

	Demo.Frames++;

	if (Demo.TimeDemo)
	{
		// Play 2 frames each demo each frame. This gives a nice fast playback.
		int LoopCount=2;
		float DeltaTime=0;

		while (Demo.CurrentPosition<Demo.DataSize)
		{
			BYTE BlockSize=Demo.Data[Demo.CurrentPosition++];
			BYTE MessageID=Demo.Data[Demo.CurrentPosition];
			if (MessageID==GNM_START_FRAME)
			{
				DeltaTime+=GetFloat(Demo.Data+Demo.CurrentPosition+1);
				
				Demo.CurrentPosition+=BlockSize;
				LoopCount--;
				if (!LoopCount)
				{
					// We must update this so client side predicted stuff runs at right rate.
					FrameDeltaTime=DeltaTime;
					return;
				}
			}
			else
			{
				GameNetworkCallback(Demo.Data+Demo.CurrentPosition,BlockSize);
				Demo.CurrentPosition+=BlockSize;
			}
		}

		// If we're here, playback is finished so calculate FPS.
		if (!Demo.Fps)
		{
			Demo.EndTime=TimerGetGameTime();
			Demo.Fps=(float)Demo.Frames/TimerGetTimeDelta(Demo.StartTime,Demo.EndTime);
		}
	}
	else
	{
		Demo.CurrentTime-=DeltaTime;
		
		while (Demo.CurrentPosition<Demo.DataSize && Demo.CurrentTime<=0)
		{
			BYTE BlockSize=Demo.Data[Demo.CurrentPosition++];
			BYTE MessageID=Demo.Data[Demo.CurrentPosition];
			if (MessageID==GNM_START_FRAME)
			{
				Demo.CurrentTime+=GetFloat(Demo.Data+Demo.CurrentPosition+1);

				Demo.CurrentPosition+=BlockSize;
			}
			else
			{
				GameNetworkCallback(Demo.Data+Demo.CurrentPosition,BlockSize);
				Demo.CurrentPosition+=BlockSize;
			}
		}
		// End current game. This will cause a new demo sequence to start,
		if (Demo.CurrentPosition>=Demo.DataSize)
			EndGame();
	}
}
