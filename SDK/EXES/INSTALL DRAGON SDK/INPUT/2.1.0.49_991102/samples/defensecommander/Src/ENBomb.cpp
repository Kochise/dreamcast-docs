/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENBomb.cpp

Abstract:

    Entity "AI" - bomb.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCEnergy.h"
#include "DCSound.h"
#include "DCParticle.h"

#define MAX_TICK_TIME (1.0f/15.0f) // Doesn't work well if tick rate too slow.

#define TERMINAL_VELOCITY 1500.0f
#define GRAVITY_ACCELERATION 250.0f
#define HORZ_START_SPEED 400.0f
#define ROT_SCALE_VALUE 100.0f
#define ROT_RETARD_DIST 25.0f

#define SPLASH_DAMAGE_RADIUS 100.0f

#define EXPLOSION_RADIUS 150.0f
#define EXPLOSION_NUM_PARTICLES 15

class EntityBomb : EntityBase
{
	float StartY;
	float DownSpeed;
	DCVector Velocity;
	
	BOOL Triggered;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void ServerTick(float FrameDeltaTime);
	BOOL Touch(CollisionInfo *Info);
	void Killed(void);
	float GetDamage();
	void GetVelocity(DCVector *OutVel);
};

// Manufacture function.
EntityBase *ManufactureEntityBomb()
{
	void *Entity=new(EntityBomb);
	
	return (EntityBase *)Entity;
}

void EntityBomb::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Then init the rest.
	DownSpeed=-GRAVITY_ACCELERATION*0.5f; // Jump start by 0.1 second so bomb clears bomber quickly.
	StartY=InLoc->Y - ROT_RETARD_DIST;
	Velocity=DCVector(0,0,0);
	
	Triggered=FALSE;
}

struct SplashInfo
{
	EntityBase *BombEntity;
	DCVector BombLoc;
};

static void SplashCallback(EntityBase *Entity, void *User)
{
	SplashInfo *Info=(SplashInfo *)User;

	DCVector TLoc,TRot;
	Entity->GetPosition(&TLoc,&TRot);

	// If within splash radius, do collision.
	HANDLE Mesh=Entity->GetMesh(FALSE);
	float R=GetMeshBoundingRadius(Mesh,FALSE)*0.5f + SPLASH_DAMAGE_RADIUS;
	float DiffX=TLoc.X - Info->BombLoc.X;
	float DiffZ=TLoc.Z - Info->BombLoc.Z;
	if (DiffX*DiffX + DiffZ*DiffZ < R*R)
	{
		gGame.MakeCollision(Entity,Info->BombEntity);
	}
}

void EntityBomb::ServerTick(float FrameDeltaTime)
{
	if (Triggered)
	{
		SplashInfo Info;
		Info.BombEntity=this;
		Info.BombLoc=Loc;
		gGame.GetCollisionEntities(COLLISION_GOODIE,SplashCallback,&Info);

		// Killed.
		gGame.NotifyEntityKilled(this);

		// Bomb is done.
		gGame.DestroyEntity(this);
		return;
	}
	else
	{
		// Tick position. We could actually client side predict this
		// if a better integrator was used.
		DCVector NewLoc=Loc,NewRot=Rot;

		for (;FrameDeltaTime>0;FrameDeltaTime-=MAX_TICK_TIME)
		{
			float DeltaTime=__min(FrameDeltaTime,MAX_TICK_TIME);

			// Rotate bomb towards ground based on distance fallen.
			if (NewLoc.Y <= StartY)
			{
				NewRot.X=(float)atan(ROT_SCALE_VALUE/(StartY-NewLoc.Y));
			}
			else
			{
				NewRot.X=DC_PI*0.5f;
			}
			// Accelerate downwards.
			float A=-GRAVITY_ACCELERATION + 
					DownSpeed*DownSpeed*(GRAVITY_ACCELERATION/(TERMINAL_VELOCITY*TERMINAL_VELOCITY));

			if (A < 0)
			{
				DownSpeed+=A*DeltaTime;
				if (DownSpeed < -TERMINAL_VELOCITY)
					DownSpeed=-TERMINAL_VELOCITY;
			}

			// Update velocity.
			DCVector Tmp(0,-HORZ_START_SPEED,0);
			Tmp.RotateX(NewRot.X);
			Tmp.RotateY(NewRot.Y);
			Velocity=DCVector(Tmp.X,DownSpeed,Tmp.Z);

			// Move location.
			NewLoc+=Velocity*DeltaTime;
		}

		// Set new position.
		gGame.SetEntityPosition(this,&NewLoc,&NewRot);
	}
}

BOOL EntityBomb::Touch(CollisionInfo *Info)
{
	// Bombs are always destroyed on contact but we'll wait
	// and do splash damage in the next server tick.
	Triggered=TRUE;
	return FALSE;
}

void EntityBomb::Killed(void)
{
	// Play boom sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("BombBoom")),&Loc);

	// Create explosion.
	ParticleExplosion(&(Loc+DCVector(0,EXPLOSION_RADIUS*0.5f,0)), EXPLOSION_RADIUS, EXPLOSION_NUM_PARTICLES,
					  0.5f, 2.0f,
					  1.0f, 0xFFFF7F5F);
}

float EntityBomb::GetDamage()
{
	return (gGame.IsGodMode()) ? 0.0f : BOMB_DAMAGE;
}

void EntityBomb::GetVelocity(DCVector *OutVel)
{
	*OutVel=Velocity;
}