/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENRocket.cpp

Abstract:

    Entity "AI" - rocket.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCEnergy.h"
#include "DCSound.h"
#include "DCParticle.h"

#define ROCKET_LIFETIME 3.0f
#define ROCKET_VELOCITY 750.0f

#define ROCKET_STERN -15.0f
#define ROCKET_NOZZLE_RADIUS 2.0f
#define ROCKET_TRAIL_RATIO 4.0f // Diameter of trail before it starts to fade is 4 times start.

#define EXPLOSION_RADIUS 5.0f
#define EXPLOSION_NUM_PARTICLES 5

class EntityRocket : protected EntityBase
{
protected:
	// Start conditions.
	float TimeSinceStart;
	DCVector StartLoc,Direction,Velocity;

	// For smoke.
	float SmokeTimeSinceStart;
	float TimeLeftOver;
	int LastCount;
	DCVector LastPos;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void ServerTick(float FrameDeltaTime);
	void ClientTick(float FrameDeltaTime);
	BOOL Touch(CollisionInfo *Info);
	void Killed(void);
	float GetDamage();
	void GetVelocity(DCVector *OutVel);
};

// Manufacture function.
EntityBase *ManufactureEntityRocket()
{
	void *Entity=new(EntityRocket);
	
	return (EntityBase *)Entity;
}

void EntityRocket::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Then init the rest.
	TimeSinceStart=0;
	StartLoc=*InLoc;
	Direction=DCVector(0,0,1);
	Direction.RotateX(InRot->X);
	Direction.RotateY(InRot->Y);
	Velocity=Direction*ROCKET_VELOCITY;

	SmokeTimeSinceStart=0;
	TimeLeftOver=FALSE;
	LastPos=DCVector(0,0,0);
	LastCount=0;
}

void EntityRocket::ServerTick(float FrameDeltaTime)
{
	// Expire rocket after a while.
	if (TimeSinceStart>ROCKET_LIFETIME)
		gGame.DestroyEntity(this);
}

void EntityRocket::ClientTick(float FrameDeltaTime)
{
	TimeSinceStart+=FrameDeltaTime;

	// Since travel is linear we can predict path easily.
	DCVector CurrLoc=StartLoc + (Velocity*TimeSinceStart);
	DCVector CurrRot=Rot;
	SetPosition(&CurrLoc,&CurrRot);

	// Do smoke.
	// Figure out position of tail of missile.
	DCVector Pos=Loc+(Direction*ROCKET_STERN);
	
	if (SmokeTimeSinceStart<0.05f)
	{
		SmokeTimeSinceStart+=FrameDeltaTime;
	}
	else
	{
		TimeLeftOver=ParticleSmokeTrail(&LastPos,&Pos,ROCKET_NOZZLE_RADIUS,ROCKET_TRAIL_RATIO,
										TimeLeftOver,FrameDeltaTime,ROCKET_NOZZLE_RADIUS*1.5f/ROCKET_VELOCITY,
										0.5f,0xFFFFFFCF,&LastCount);
	}
	LastPos=Pos;
}

BOOL EntityRocket::Touch(CollisionInfo *Info)
{
	// Killed.
	gGame.NotifyEntityKilled(this);

	// If a rocket touches anything it disappears.
	return TRUE;
}

void EntityRocket::Killed(void)
{
	// Create explosion.
	ParticleExplosion(&Loc, EXPLOSION_RADIUS, EXPLOSION_NUM_PARTICLES,
					  0.5f, 2.0f,
					  1.0f, 0xFFFF7F5F);
}


float EntityRocket::GetDamage()
{
	return ROCKET_DAMAGE;
}

void EntityRocket::GetVelocity(DCVector *OutVel)
{
	*OutVel=Velocity;
}

//****************************************************************
// Version of rocket with sound.
//****************************************************************
class EntityRocketWithSound : protected EntityRocket
{
protected:
	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	BOOL Touch(CollisionInfo *Info);
	void Killed(void);
};

// Manufacture function.
EntityBase *ManufactureEntityRocketWithSound()
{
	void *Entity=new(EntityRocketWithSound);
	
	return (EntityBase *)Entity;
}

void EntityRocketWithSound::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityRocket::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Make launch sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("RocketLaunch")),InLoc);
}

BOOL EntityRocketWithSound::Touch(CollisionInfo *Info)
{
	// If a rocket touches anything it disappears.
	return EntityRocket::Touch(Info);
}

void EntityRocketWithSound::Killed(void)
{
	// Play boom sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("MissileRocketBoom")),&Loc);

	// Create explosion.
	ParticleExplosion(&Loc, EXPLOSION_RADIUS, EXPLOSION_NUM_PARTICLES,
					  0.5f, 2.0f,
					  1.0f, 0xFFFF7F5F);
}

