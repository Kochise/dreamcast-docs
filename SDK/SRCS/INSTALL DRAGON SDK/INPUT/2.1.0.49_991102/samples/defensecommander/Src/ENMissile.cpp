/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENMissile.cpp

Abstract:

    Entity "AI" - missile.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCEnergy.h"
#include "DCWorld.h"
#include "DCSound.h"
#include "DCParticle.h"

#define MISSILE_LIFETIME 15.0f
#define MISSILE_VELOCITY 1000.0f // 750.0f
#define MISSILE_TURN_RATE (DC_PI*0.5f)
#define MISSILE_MAX_TICK_TIME 0.0333f // Doesn't work well if tick rate too slow.

#define MISSILE_STERN -23.0f
#define MISSILE_NOZZLE_RADIUS 2.0f
#define MISSILE_TRAIL_RATIO 8.0f // Diameter of trail before it starts to fade is 8 times start.
#define MISSILE_SMOKE_WAIT 0.07f

#define EXPLOSION_RADIUS 15.0f
#define EXPLOSION_NUM_PARTICLES 10

//****************************************************************
// Base bullet class.
//****************************************************************
class EntityMissile : protected EntityBase
{
protected:
	// Start conditions.
	float TimeSinceStart;
	DCVector Direction;
	EntityBase *Target;

	// For smoke.
	float SmokeTimeSinceStart;
	float TimeLeftOver;
	int LastCount;
	DCVector LastPos;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void Shutdown();
	void ServerTick(float FrameDeltaTime);
	void ClientTick(float FrameDeltaTime);
	BOOL Touch(CollisionInfo *Info);
	void Killed(void);
	float GetDamage();
	void GetVelocity(DCVector *OutVel);
};

// Manufacture function.
EntityBase *ManufactureEntityMissile()
{
	void *Entity=new(EntityMissile);
	
	return (EntityBase *)Entity;
}

void EntityMissile::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Then init the rest.
	TimeSinceStart=0;
	Direction=DCVector(0,0,1);
	Direction.RotateX(Rot.X);
	Direction.RotateY(Rot.Y);
	if (InUser1 && !gGame.IsClient())
	{
		Target=(EntityBase *)InUser1;
		Target->AddRef(&Target);
	}
	else
	{
		Target=NULL;
	}

	SmokeTimeSinceStart=0;
	TimeLeftOver=FALSE;
	LastPos=DCVector(0,0,0);
	LastCount=0;

	// Make launch sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("MissileLaunch")),InLoc);
}

void EntityMissile::Shutdown()
{
	// Remove reference to BestTarget if we have one.
	if (Target)
		Target->RemoveRef(&Target);

	EntityBase::Shutdown();
}

void EntityMissile::ServerTick(float FrameDeltaTime)
{
	// Expire bullet after a while.
	TimeSinceStart+=FrameDeltaTime;
	if (TimeSinceStart>MISSILE_LIFETIME)
	{
		gGame.DestroyEntity(this);
		return;
	}

	// If we have a target, seek towards it.
	if (Target)
	{
		// Get target location.
		DCVector TargetLoc, TargetRot;
		Target->GetPosition(&TargetLoc,&TargetRot);

		// Temp copy of position.
		DCVector NewRot=Rot;
		DCVector NewLoc=Loc;
		// Seeker doesn't work well if tick rate is less than 30 fps.
		for (;FrameDeltaTime>0;FrameDeltaTime-=MISSILE_MAX_TICK_TIME)
		{
			float DeltaTime=__min(FrameDeltaTime,MISSILE_MAX_TICK_TIME);

			// Get vector towards target.
			DCVector TargetVector=TargetLoc - NewLoc;

			// Adjust bullet rotation towards target.
			float MaxRot=MISSILE_TURN_RATE*DeltaTime;
			// Horizontal.
			float H=FastSqrt(TargetVector.X*TargetVector.X + TargetVector.Z*TargetVector.Z);
			float DesiredRotY=(float)acos(TargetVector.Z/H);
			if (TargetVector.X > 0)
				DesiredRotY*=-1;
			DesiredRotY-=NewRot.Y;
			while (DesiredRotY>DC_PI)
				DesiredRotY-=DC_PI*2;
			while (DesiredRotY<-DC_PI)
				DesiredRotY+=DC_PI*2;
			if ((float)fabs(DesiredRotY)>MaxRot)
			{
				if (DesiredRotY>0)
					NewRot.Y+=MaxRot;
				else
					NewRot.Y-=MaxRot;
			}
			else
			{
				NewRot.Y+=DesiredRotY;
			}
			// Vertical.
			float Hyp=TargetVector.FastLength();
			float DesiredRotX=(float)acos(H/Hyp);
			if (TargetVector.Y < 0)
				DesiredRotX*=-1;
			DesiredRotX-=NewRot.X;
			while (DesiredRotX>DC_PI)
				DesiredRotX-=DC_PI*2;
			while (DesiredRotX<-DC_PI)
				DesiredRotX+=DC_PI*2;
			if ((float)fabs(DesiredRotX)>MaxRot)
			{
				if (DesiredRotX>0)
					NewRot.X+=MaxRot;
				else
					NewRot.X-=MaxRot;
			}
			else
			{
				NewRot.X+=DesiredRotX;
			}
			// Calculate movement based on new rotation.
			Direction=DCVector(0,0,1);
			Direction.RotateX(NewRot.X);
			Direction.RotateY(NewRot.Y);
			NewLoc+=(Direction*(MISSILE_VELOCITY*DeltaTime));
		}

		// Set new postion.
		gGame.SetEntityPosition(this,&NewLoc,&NewRot);
	}
	else
	{
		// If not seeking and gone outside world, die.
		if (Loc.X*Loc.X + Loc.Y*Loc.Y + Loc.Z*Loc.Z > DCW_TERRAIN_OUTER_RADIUS*DCW_TERRAIN_OUTER_RADIUS)
		{
			gGame.DestroyEntity(this);
		}
		else
		{
			// No seeking towards anything so just move, don't rotate.
			// We can just use old direction since without a target, it won't have changed.
			DCVector NewLoc=Loc+(Direction*(MISSILE_VELOCITY*FrameDeltaTime));
			gGame.SetEntityPosition(this,&NewLoc,&Rot);
		}
	}
}

void EntityMissile::ClientTick(float FrameDeltaTime)
{
	// Need to figure out direction on client.
	if (gGame.IsClient())
	{
		Direction=DCVector(0,0,1);
		Direction.RotateX(Rot.X);
		Direction.RotateY(Rot.Y);
	}
	
	// Figure out position of tail of missile.
	DCVector Pos=Loc+(Direction*MISSILE_STERN);
	
	if (SmokeTimeSinceStart<MISSILE_SMOKE_WAIT)
	{
		SmokeTimeSinceStart+=FrameDeltaTime;
		TimeLeftOver=SmokeTimeSinceStart-MISSILE_SMOKE_WAIT;
	}
	else
	{
		TimeLeftOver=ParticleSmokeTrail(&LastPos,&Pos,MISSILE_NOZZLE_RADIUS,MISSILE_TRAIL_RATIO,
										TimeLeftOver,FrameDeltaTime,MISSILE_NOZZLE_RADIUS/MISSILE_VELOCITY,
										1.0f,0xFFFFFFFF,&LastCount);
	}

	LastPos=Pos;
}

BOOL EntityMissile::Touch(CollisionInfo *Info)
{
	// Killed.
	gGame.NotifyEntityKilled(this);

	// If a missile touches anything it disappears.
	return TRUE;
}

void EntityMissile::Killed(void)
{
	// Play boom sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("MissileRocketBoom")),&Loc);

	// Create explosion.
	ParticleExplosion(&Loc, EXPLOSION_RADIUS, EXPLOSION_NUM_PARTICLES,
					  0.5f, 2.0f,
					  1.0f, 0xFFFF7F5F);
}

float EntityMissile::GetDamage()
{
	return MISSILE_DAMAGE;
}

void EntityMissile::GetVelocity(DCVector *OutVel)
{
	*OutVel=Direction*MISSILE_VELOCITY;
}
