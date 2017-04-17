/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GADemoRecord.cpp

Abstract:

    Game management - Demo recording functions.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"

#define RECORD_DEMO_FILE_NAME TEXT("NEW.DEM")

void GameClass::StartDemoRecord()
{
	if (!DemoFile && !ClientCount && !IsClient())
	{
		DemoFile=OpenFileForWrite(RECORD_DEMO_FILE_NAME,NULL);
		if (DemoFile)
		{
			ClientCount++;

			// Get game to call back with data.
			SendGameState();
		}
	}
}

void GameClass::EndDemoRecord()
{
	if (DemoFile)
	{
		CloseOpenFile(DemoFile);
		DemoFile=NULL;
		if (ClientCount)
			ClientCount--;
	}
}

void GameClass::RecordMessage(void *Data, int Size)
{
	if (DemoFile)
	{
		BYTE Message=((BYTE *)Data)[0];

		// Destroy all means game over.
		if (Message==GNM_DESTROY_ALL)
		{
			EndDemoRecord();
			return;
		}

		// Filter out crud we don't need.
		if (Message!=GNM_CLIENT_CONNECT &&
			Message!=GNM_CLIENT_DISCONNECT)
		{
			// Write packet size.
			WriteToFile(DemoFile,&Size,1);
			// Write packet.
			WriteToFile(DemoFile,Data,Size);
		}
	}
}

