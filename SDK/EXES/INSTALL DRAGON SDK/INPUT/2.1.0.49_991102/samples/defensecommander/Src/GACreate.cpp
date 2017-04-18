/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    Game management - .cpp

Abstract:

    Game management - creation/destruction of games.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCParticle.h"
#include "DCMesh.h"
#include "DCNetwork.h"

struct
{
	TCHAR *Name;
	float X,Z;
	float Rot;
} Buildings[]=
{
	// Obelisk's around main temple.
	{TEXT("Obelisk01")			,61		,0		,0},
	{TEXT("Obelisk01")			,-61	,0		,0},

	// Small temple and surrounds.
	{TEXT("SmallTemple")		,0		,-120	,180},
	{TEXT("Building03")			,0-40	,-120+40,45+180},
	{TEXT("Building03")			,0+40	,-120+40,-45+180},
	{TEXT("Building03")			,0-40	,-120-40,135+180},
	{TEXT("Building03")			,0+40	,-120-40,-135+180},

	// Right cluster.
	{TEXT("Building07")			, 142	,35		,180},
	{TEXT("Building07")			, 142	,-35	,0},
	{TEXT("Building06")			, 118	,15		,0},
	{TEXT("Building06")			, 118	,-15	,0},
	{TEXT("Building06")			, 166	,15		,180},
	{TEXT("Building06")			, 166	,-15	,180},
	
	// Left cluster.
	{TEXT("Building07")			,-142	,35		,180},
	{TEXT("Building07")			,-142	,-35	,0},
	{TEXT("Building06")			,-118	,15		,180},
	{TEXT("Building06")			,-118	,-15	,180},
	{TEXT("Building06")			,-166	,15		,0},
	{TEXT("Building06")			,-166	,-15	,0},

	// Bottom right cluster.
	{TEXT("Building04")			,111.5f	,-100.4f,48.00f},
//	{TEXT("Building05")			,182.9f	,- 81.0f,66.12f},
	{TEXT("Building05")			,167.8f	,-108.8f,57.06f},
	{TEXT("Building05")			,148.6f	,-133.8f,48.00f},
	{TEXT("Building05")			,125.7f	,-155.6f,38.94f},
//	{TEXT("Building05")			, 99.6f	,-173.4f,29.88f},

	// Bottom left cluster.
	{TEXT("Building08")			,-111.5f,-100.4f,-48.00f},
//	{TEXT("Building05")			,-182.9f,- 81.0f,-66.12f},
	{TEXT("Building05")			,-167.8f,-108.8f,-57.06f},
	{TEXT("Building05")			,-148.6f,-133.8f,-48.00f},
	{TEXT("Building05")			,-125.7f,-155.6f,-38.94f},
//	{TEXT("Building05")			, -99.6f,-173.4f,-29.88f},

	// Straddling water.
	{TEXT("Building01")			,111.5f	,100.4f,180-48.00f},
	{TEXT("Building02")			,-111.5f,100.4f,-180+48.00f},

	{NULL						,0		,	0	,0}
};



// Creates a new game and starts it running.
void GameClass::CreateGame(GameTypeRunning GameType)
{
	if (GameType==GAME)
	{
		// Spawn building entities.
		for (int i=0;Buildings[i].Name!=NULL;i++)
		{
			gGame.SpawnEntity(GetEntityIDFromName(TEXT("EntityBuilding")),
							  COLLISION_GOODIE,
							  GetMeshHandleFromName(Buildings[i].Name),
							  &DCVector(Buildings[i].X*MESH_SCALE,0,Buildings[i].Z*MESH_SCALE),
							  &DCVector(0,DC_TO_RADIANS(Buildings[i].Rot),0),
							  0,0);
		}
	
		// Spawn turret. Turret will in turn spawn attached entities on next
		// server tick.
		gGame.SpawnEntity(GetEntityIDFromName(TEXT("EntityTurret")),
						  COLLISION_GOODIE,
						  GetMeshHandleFromName(TEXT("Turret")),
						  &DCVector(0,0,0),&DCVector(0,0,0),
						  0,0);

		// Spawn lord entity which controls spawning of baddies and other
		// running operations required by the game.
		gGame.SpawnEntity(GetEntityIDFromName(TEXT("EntityLord")),
						  COLLISION_NONE,
						  NULL,
						  &DCVector(0,0,0),&DCVector(0,0,0),
						  0,0);

		SetObserverMode(OFF);

		// Set new viewer direction.
		DCVector Loc,Rot;
		GetViewerCoords(&Loc,&Rot);
		SetViewerCoords(&Loc,&DCVector(0,0,0));
	}
	else if (GameType==NETWORK_CLIENT)
	{
		// Set to observer mode so we can see something.
		ForceObserverMode();

		// Make sure we're not in GOD mode. Doesn't make any difference to game but
		// don't want "God Mode" displayed on the screen.
		SetGodMode(OFF);

		// Request game state from server.
		SendSimpleMessage(GNM_CLIENT_CONNECT);
	}
	else if (GameType==DEMO)
	{
		// Set view.
		if (Demo.Data)
			SetObserverMode(OFF);
		else
			ForceObserverMode(); // For case when there is no demo file.


		// Make sure we're not in GOD mode. Doesn't make any difference to game but
		// don't want "God Mode" displayed on the screen.
		SetGodMode(OFF);

		// Start demo playback.
		StartDemoPlayback();
	}
	
	State.GameRunning=GameType;
}


void GameClass::DestroyGame()
{
	// Destroy all the entities.
	for (EntityBase *Entity=EntityGlobalList,*Next;Entity;Entity=Next)
	{
		// Get next entity before this one is lost.
		Next=Entity->NextGlobal;
		// Destroy the entity.
		DestroyEntity(Entity);
	}

	// If connectect to a server, break the connection.
	if (State.GameRunning==NETWORK_CLIENT)
	{
		SendSimpleMessage(GNM_CLIENT_DISCONNECT);
		SendNetBuffer();
	}
	// If we have a client, send a destroy all just in case a destroy got lost in the ether.
	else if (ClientCount)
	{
		SendSimpleMessage(GNM_DESTROY_ALL);
		SendNetBuffer();
	}

	// Kill off all particles, scorch marks and playing sounds.
	KillAllParticles();

	State.GameRunning=NONE;
}
