/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENPowerUp.cpp

Abstract:

    Entity "AI" - power ups.

-------------------------------------------------------------------*/

// Several types of powerups:
// 0 - Rapid fire.
// 1 - Explosive tip.
// 2 - Seeker.
// 3 - Damage Repair.
// 4 - Smart bomb.

#include "DC.h"
#include "DCGame.h"
#include "DCSound.h"

static int PowerUpCounts[]={200, 50, 100, 1, 1};

class EntityPowerUp : EntityBase
{
	float Age;
	int State;
	int SpinnerClassID;
	HANDLE SpinnerMesh;
	EntityBase *Spinner;
	BOOL HaveSpinner;
	int FlareClassID;
	HANDLE FlareMesh;
	EntityBase *Flare1, *Flare2, *Flare3, *Flare4;
	int Type;
	int BulletClassID, MissileClassID;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void Shutdown();
	void ServerTick(float FrameDeltaTime);

	void HandleFlareSpawn(EntityBase **Entity, int Type);
	void HandleSpinnerSpawn(EntityBase **Entity);
	void HandleDestroy(EntityBase **Entity);
};

// Manufacture function.
EntityBase *ManufactureEntityPowerUp()
{
	void *Entity=new(EntityPowerUp);
	
	return (EntityBase *)Entity;
}

void EntityPowerUp::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Set other variables.
	Age=0;
	State=0;
	Type=__min(4,__max(0,InUser1));

	SpinnerClassID=gGame.GetEntityIDFromName(TEXT("EntityPowerUpSpinner"));
	TCHAR *Name;
	switch (Type)
	{
		case 0:
			Name=TEXT("RapidFire");
			break;
		case 1:
			Name=TEXT("ExplosiveTip");
			break;
		case 2:
			Name=TEXT("Seeker");
			break;
		case 3:
			Name=TEXT("DamageRepair");
			break;
		case 4:
			Name=TEXT("SmartBomb");
			break;
	}
	SpinnerMesh=GetMeshHandleFromName(Name);
	Spinner=NULL;
	HaveSpinner=FALSE;
	
	FlareClassID=gGame.GetEntityIDFromName(TEXT("EntityPowerUpFlare"));
	FlareMesh=GetMeshHandleFromName(TEXT("PowerUpFlare"));
	Flare1=Flare2=Flare3=Flare4=NULL;
}

void EntityPowerUp::Shutdown()
{
	if (Flare1)
		gGame.DestroyEntity(Flare1);
	if (Flare2)
		gGame.DestroyEntity(Flare2);
	if (Flare3)
		gGame.DestroyEntity(Flare3);
	if (Flare4)
		gGame.DestroyEntity(Flare4);
	if (Spinner)
		gGame.DestroyEntity(Spinner);

	EntityBase::Shutdown();
}

#define SPAWN_INTERVAL 0.25f
#define POWERUP_LIFETIME 10.0f
#define DESTROY_INTERVAL 1.0f

void EntityPowerUp::HandleFlareSpawn(EntityBase **Entity, int Type)
{
	*Entity=gGame.SpawnEntity(FlareClassID,COLLISION_NONE,FlareMesh,&Loc,&Rot,Type,0);
	if (*Entity)
		(*Entity)->AddRef(Entity);
	State++;
}

void EntityPowerUp::HandleSpinnerSpawn(EntityBase **Entity)
{
	*Entity=gGame.SpawnEntity(SpinnerClassID,COLLISION_BADDIE,SpinnerMesh,&Loc,&Rot,Type,0);
	if (*Entity)
	{
		(*Entity)->AddRef(Entity);
		HaveSpinner=TRUE;
	}
	State++;
}

void EntityPowerUp::HandleDestroy(EntityBase **Entity)
{
	if (*Entity)
		gGame.DestroyEntity(*Entity);
	State++;
}

void EntityPowerUp::ServerTick(float FrameDeltaTime)
{
	// See if spinner has been destroyed.
	if (HaveSpinner && !Spinner)
	{
		gGame.DestroyEntity(this);
		return;
	}

	Age+=FrameDeltaTime;

	switch (State)
	{
		case 0:
			// Need to spawn first flare.
			if (Age > SPAWN_INTERVAL*0)
				HandleFlareSpawn(&Flare1,0);
			else
				break;
		case 1:
			// Need to spawn second flare.
			if (Age > SPAWN_INTERVAL*1)
				HandleFlareSpawn(&Flare2,1);
			else
				break;
		case 2:
			// Need to spawn third flare.
			if (Age > SPAWN_INTERVAL*2)
				HandleFlareSpawn(&Flare3,2);
			else
				break;
		case 3:
			// Need to spawn fourth flare.
			if (Age > SPAWN_INTERVAL*3)
				HandleFlareSpawn(&Flare4,3);
			else
				break;
		case 4:
			if (Age > SPAWN_INTERVAL*4)
				HandleSpinnerSpawn(&Spinner);
			else
				break;
		case 5:
			// Waiting to destroy first flare.
			if (Age > POWERUP_LIFETIME-DESTROY_INTERVAL*3)
				HandleDestroy(&Flare4);
			else
				break;
		case 6:
			// Waiting to destroy second flare.
			if (Age > POWERUP_LIFETIME-DESTROY_INTERVAL*2)
				HandleDestroy(&Flare3);
			else
				break;
		case 7:
			// Waiting to destroy third flare.
			if (Age > POWERUP_LIFETIME-DESTROY_INTERVAL*1)
				HandleDestroy(&Flare2);
			else
				break;
		case 8:
			// Waiting to destroy fourth flare.
			if (Age > POWERUP_LIFETIME-DESTROY_INTERVAL*0)
				HandleDestroy(&Flare1);
			else
				break;
		case 9:
			// Waiting to destroy power up.
			if (Age > POWERUP_LIFETIME)
			{
				gGame.DestroyEntity(this);
				return;
			}
	}
}

//*****************************************
// PowerUp spinner entity.
//*****************************************
class EntityPowerUpSpinner : EntityBase
{
	int Type;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void ClientTick(float FrameDeltaTime);
	BOOL Touch(CollisionInfo *Info);
};

// Manufacture function.
EntityBase *ManufactureEntityPowerUpSpinner()
{
	void *Entity=new(EntityPowerUpSpinner);
	
	return (EntityBase *)Entity;
}

void EntityPowerUpSpinner::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	Type=__min(4,__max(0,InUser1));

	// Play sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("PowerUpSpawn")),&Loc);
}

void EntityPowerUpSpinner::ClientTick(float FrameDeltaTime)
{
	SetPosition(&Loc,&DCVector(Rot.X,Rot.Y-DC_PI*FrameDeltaTime,Rot.Z));
}

BOOL EntityPowerUpSpinner::Touch(CollisionInfo *Info)
{
	if (Info->CollisionType==COLLISION_GOODIE_FIRE)
	{
		// Send a message to the turret to give it this powerup.
		DWORD Message[3];

		Message[0]=1;		// Turret message meaning "PowerUp".
		Message[1]=Type;	// Powerup type.
		Message[2]=PowerUpCounts[Type];

		gGame.SendEntityMessage(gGame.GetPlayerEntity(),Message);

		// Play sound.
		gGame.PlaySoundNoAttenuate(GetSoundHandleFromName(TEXT("PowerUpGet")),TRUE);
	}

	// Anything touching a powerup destroys it.
	return TRUE;
}

//*****************************************
// PowerUp flare entity.
//*****************************************
class EntityPowerUpFlare : EntityBase
{
	float ScaleXRot,ScaleYRot;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void ClientTick(float FrameDeltaTime);
};

// Manufacture function.
EntityBase *ManufactureEntityPowerUpFlare()
{
	void *Entity=new(EntityPowerUpFlare);
	
	return (EntityBase *)Entity;
}

#define ROT_RATE 0.5f

void EntityPowerUpFlare::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Save type based info.
	switch(InUser1)
	{
		default:
		case 0:
			ScaleXRot=ScaleYRot=ROT_RATE;
			break;
		case 1:
			ScaleXRot=ROT_RATE;
			ScaleYRot=ROT_RATE*2;
			break;
		case 2:
			ScaleXRot=ROT_RATE*2;
			ScaleYRot=ROT_RATE;
			break;
		case 3:
			ScaleXRot=ScaleYRot=ROT_RATE*2;
			break;
	}
}

void EntityPowerUpFlare::ClientTick(float FrameDeltaTime)
{
	SetPosition(&Loc,&DCVector(Rot.X+DC_PI*FrameDeltaTime*ScaleXRot,
							   Rot.Y+DC_PI*FrameDeltaTime*ScaleYRot,
							   Rot.Z));
}
