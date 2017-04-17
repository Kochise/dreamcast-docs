/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GATick.cpp

Abstract:

    Game management - entity ticking and related (collision) code.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCCollide.h"
#include "DCEnergy.h"
#include "DCNetwork.h"

static inline BOOL HandleCollision(EntityBase *Entity, CollisionInfo *Info)
{
	if (Entity->Touch(Info))
	{
		gGame.DestroyEntity(Entity);
		return TRUE;
	}
	return FALSE;
}

static inline void FillCollisionInfo(CollisionInfo &Info, EntityBase *Entity, DCVector &Loc, DCVector &Rot)
{
	Info.ClassID=Entity->ClassID;
	Info.CollisionType=Entity->CollisionType;
	Info.Mesh=Entity->GetMesh(FALSE);
	Info.Loc=&Loc;
	Info.Rot=&Rot;
	Info.Damage=Entity->GetDamage();
	Info.Terrain=FALSE;
}

BOOL GameClass::MakeCollision(EntityBase *Dst, EntityBase *Src)
{
	CollisionInfo Info;
	DCVector Loc,Rot;

	Src->GetPosition(&Loc,&Rot);
	FillCollisionInfo(Info,Src,Loc,Rot);
	return HandleCollision(Dst,&Info);
}

static CollisionInfo TerrainCollisionInfo={0,COLLISION_NONE,NULL,NULL,NULL,INFINITE_DAMAGE,TRUE};

static void HandlePointCollisions(EntityBase **PointList, EntityBase **HullList, float FrameDeltaTime)
{
	EntityBase *PointEntity,*NextPointEntity;
	EntityBase *HullEntity,*NextHullEntity;
	CollisionInfo PointInfo, HullInfo;
	
	float HalfTime=FrameDeltaTime*0.5f;

	for (PointEntity=*PointList;PointEntity;PointEntity=NextPointEntity)
	{
		// Get next point entity while we still can.
		NextPointEntity=PointEntity->NextCollision;

		// Get point entity location and mesh.
		DCVector PointLoc,PointRot;
		PointEntity->GetPosition(&PointLoc,&PointRot);
		// Get amount of movement.
		DCVector Movement;
		PointEntity->GetVelocity(&Movement);
		Movement*=HalfTime;

		// See if it collides with any of the hull entities.
		for (HullEntity=*HullList;HullEntity;HullEntity=NextHullEntity)
		{
			// Get next hull entity while we still can.
			NextHullEntity=HullEntity->NextCollision;

			// Get hull entity location and mesh.
			HANDLE HullMesh=HullEntity->GetMesh(FALSE);
			DCVector HullLoc,HullRot;
			HullEntity->GetPosition(&HullLoc,&HullRot);

			// See if they collide.
			if (IsMovingPointInMeshHull(&PointLoc,&Movement,HullMesh,&HullLoc,&HullRot))
			{
				// They do collide, so get stuff we need before they are possibly destroyed.
				FillCollisionInfo(PointInfo,PointEntity,PointLoc,PointRot);
				FillCollisionInfo(HullInfo,HullEntity,HullLoc,HullRot);
				// Handle collision for hull entity.
				HandleCollision(HullEntity,&PointInfo);
				// Handle collision for point entity.
				if (HandleCollision(PointEntity,&HullInfo))
					goto Destroyed;
			}
		}

		// See if point entity collides with terrain.
		if (GetTerrainHeight(PointLoc.X,PointLoc.Z)>=PointLoc.Y)
		{
			HandleCollision(PointEntity,&TerrainCollisionInfo);
		}
Destroyed:; // Sorry, I had to.
	}
}

static void HandleHullCollisions(EntityBase **List1, EntityBase **List2)
{


}

static void HandleTerrainCollisions(EntityBase **List)
{
	EntityBase *Entity,*NextEntity;

	// Walk list
	for (Entity=*List;Entity;Entity=NextEntity)
	{
		// Get next hull entity while we still can.
		NextEntity=Entity->NextCollision;

		// Get hull entity location and mesh.
		HANDLE Mesh=Entity->GetMesh(FALSE);
		DCVector Loc,Rot;
		Entity->GetPosition(&Loc,&Rot);

		// See if they collide.
		DCVector LowPoint=GetMeshBoundingLowPoint(Mesh,&Loc,&Rot);
		if (GetTerrainHeight(LowPoint.X,LowPoint.Z)>=LowPoint.Y)
		{
			HandleCollision(Entity,&TerrainCollisionInfo);
		}
	}
}

void GameClass::TickFrame(void)
{
	// Calculate new frame time.
	LastFrameAbsTime=ThisFrameAbsTime;
	ThisFrameAbsTime=TimerGetGameTime();
	FrameDeltaTime=TimerGetTimeDelta(LastFrameAbsTime,ThisFrameAbsTime);
	
	// Calculaye new app frame time.
	LastFrameAppAbsTime=ThisFrameAppAbsTime;
	ThisFrameAppAbsTime=TimerGetAppTime();
	AppFrameDeltaTime=TimerGetTimeDelta(LastFrameAppAbsTime,ThisFrameAppAbsTime);

	// Send delta time to client (only useful for recording demos).
	if (ClientCount && IsRecordingDemo())
	{
		// Limit frame rate to 30fps so demo file doesn't take up too much memory and so
		// timedemo will play back at a consistent rate.
		while (AppFrameDeltaTime < 1.0f/30.0f)
		{
			ThisFrameAppAbsTime=TimerGetAppTime();
			AppFrameDeltaTime=TimerGetTimeDelta(LastFrameAppAbsTime,ThisFrameAppAbsTime);
		}
		SendStartFrame(FrameDeltaTime);
	}

	// Tick demo playback if a demo is playing.
	if (IsDemoPlayback())
		TickDemoPlayback(FrameDeltaTime);
	
	// Tick the network receieve. This will update the entities. We must always 
	// tick even if there is no client so we catch connect messages from a new client.
	TickNetworkReceive(GameNetworkCallback);

	// Update player view.
	TickPlayerView();

	EntityBase *Entity,*Next;
	// Walk the entity list and server tick all the entities provided
	// we're not a client.
	if (!IsClient())
	{
		for (Entity=EntityGlobalList;Entity;Entity=Next)
		{
			// Get next now in case entity is destroyed.
			Next=Entity->NextGlobal;
			Entity->ServerTick(FrameDeltaTime);
		}
	}
	// Walk the entity list and client tick all the entities.
	for (Entity=EntityGlobalList;Entity;Entity=Next)
	{
		// Get next now in case entity is destroyed.
		Next=Entity->NextGlobal;
		Entity->ClientTick(FrameDeltaTime);
	}

	// Now do collision tests.
	if (!State.TimeIsPaused && !IsClient())
	{
		// Handle various types of collisions possible. We separate these
		// out to help performance.
		HandlePointCollisions(&EntityGoodieFireList,&EntityBaddieList,FrameDeltaTime);
		HandlePointCollisions(&EntityBaddieFireList,&EntityGoodieList,FrameDeltaTime);
//		HandleHullCollisions(&EntityGoodieList,&EntityBaddieList);
//		HandleTerrainCollisions(&EntityBaddieList);
	}

	// All done so do network send.
	SendNetBuffer();
	TickNetworkSend();
}