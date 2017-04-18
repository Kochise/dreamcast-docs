/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENSmartBomb.cpp

Abstract:

    Entity "AI" - smart bomb.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCSound.h"

#define FLASH_TIME 2.0f
#define HOLD_TIME 0.0f
#define FLASH_INTENSITY 3.0f

class EntitySmartBomb : EntityBase
{
	float TimeLeft;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void ServerTick(float FrameDeltaTime);
	void ClientTick(float FrameDeltaTime);
};

// Manufacture function.
EntityBase *ManufactureEntitySmartBomb()
{
	void *Entity=new(EntitySmartBomb);
	
	return (EntityBase *)Entity;
}

static void SmartBombCallback(EntityBase *Entity, void *User)
{
	// Sends infinite damage to all baddie entities.	
	gGame.MakeCollision(Entity,(EntityBase *)User);
}

void EntitySmartBomb::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	TimeLeft=FLASH_TIME;
	if (!gGame.IsClient())
	{
		// Destroy all baddies and their fire.
		gGame.GetCollisionEntities(COLLISION_BADDIE,
								   SmartBombCallback,
								   this);
		gGame.GetCollisionEntities(COLLISION_BADDIE_FIRE,
								   SmartBombCallback,
								   this);
	}

	// Play sound.
	gGame.PlaySoundNoAttenuate(GetSoundHandleFromName(TEXT("SmartBomb")));
}

void EntitySmartBomb::ServerTick(float FrameDeltaTime)
{
	if (TimeLeft < 0)
		gGame.DestroyEntity(this);
}

void EntitySmartBomb::ClientTick(float FrameDeltaTime)
{
	if (TimeLeft > 0)
	{
		float I;

		if (TimeLeft >= FLASH_TIME-HOLD_TIME)
			I=FLASH_INTENSITY;
		else
			I=TimeLeft*(FLASH_INTENSITY/(FLASH_TIME-HOLD_TIME));
		if (I > gGame.GetFlashIntensity())
			gGame.SetFlashIntensity(I);
		TimeLeft-=FrameDeltaTime;
	}
}
