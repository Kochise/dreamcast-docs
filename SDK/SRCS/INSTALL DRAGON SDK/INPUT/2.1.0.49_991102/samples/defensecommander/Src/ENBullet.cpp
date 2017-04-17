/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENBullet.cpp

Abstract:

    Entity "AI" - various types of bullets.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCEnergy.h"
#include "DCSound.h"
#include "DCParticle.h"

#define BULLET_LIFETIME 2.0f // 3.0f
#define BULLET_VELOCITY 1875.0f //1250.0f
#define BULLET_GRAVITY  -40.0f
#define BULLET_DEFLECTION 7.5f
#define SEEKER_TARGET_COSINE_LIMIT 0.9914f // 7.5 degrees.
#define SEEKER_TURN_RATE (DC_PI*4)
#define SEEKER_MAX_TICK_TIME 0.0333f // Seeker doesn't work well if tick rate is less than 30 fps.
#define SEEKER_MAX_ROT (DC_PI*0.5f) // Don't bother seeking if angle too great.

#define EXPLOSION_RADIUS 5.0f
#define EXPLOSION_NUM_PARTICLES 5

//****************************************************************
// Base bullet class.
//****************************************************************
class EntityBulletBase : protected EntityBase
{
protected:
	// Start conditions.
	BOOL FirstTick;
	float TimeSinceStart;
	DCVector StartLoc;
	DCVector StartVec;
	DCVector StartRot;
	float DefX,DefY;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void ServerTick(float FrameDeltaTime);
	void ClientTick(float FrameDeltaTime);
	BOOL Touch(CollisionInfo *Info);
	float GetDamage();
	void GetVelocity(DCVector *OutVel);
	HANDLE GetMesh(BOOL ForRender);
};

void EntityBulletBase::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Then init the rest.
	TimeSinceStart=DC_AS_FLOAT(InUser1);
	StartLoc=*InLoc;
	StartRot=*InRot;
	DCVector Dummy1,Dummy2;
	InRot->CalculateViewVectors(&Dummy1,&Dummy2,&StartVec);
	StartVec*=BULLET_VELOCITY;

	DefX=(float)(InUser2 & 0xFFFF)*(2.0f/65565.0f)-1.0f;
	DefX=DefX*BULLET_DEFLECTION;
	DefY=(float)(InUser2 >> 16)*(2.0f/65565.0f)-1.0f;
	DefY=DefY*BULLET_DEFLECTION + BULLET_GRAVITY*0.5f;

	// Do client tick to update position based on time since the bullet was spawned.
	FirstTick=TRUE;
	ClientTick(0);
	FirstTick=TRUE;
}

void EntityBulletBase::ServerTick(float FrameDeltaTime)
{
	// Expire bullet after a while.
	if (TimeSinceStart>BULLET_LIFETIME)
		gGame.DestroyEntity(this);
}

void EntityBulletBase::ClientTick(float FrameDeltaTime)
{
	if (FirstTick)
		FirstTick=FALSE;
	else
		TimeSinceStart+=FrameDeltaTime;

	// Set new location based on time since the bullet was spawned and initial
	// location and direction. This is done client side so we don't eat too much network traffic.
	// Bullet is affected by gravity, so will follow a parabolic path.
	float t2=TimeSinceStart*TimeSinceStart;
	DCVector CurrLoc=DCVector(StartLoc.X + StartVec.X*TimeSinceStart + DefX*t2,
							  StartLoc.Y + StartVec.Y*TimeSinceStart + DefY*t2,
							  StartLoc.Z + StartVec.Z*TimeSinceStart + DefX*t2);
	// This uses an approximation that tan(Angle)=Angle. For angle large, becomes
	// very inaccurate and bullet will turn too much. We only bother adjusting
	// the vertical rotation since the horizonal deflection is just a hacked mix of
	// X and Z components.
	DCVector CurrRot=DCVector(StartRot.X + (TimeSinceStart*DefY*2.0f/BULLET_VELOCITY),
							  StartRot.Y,
							  StartRot.Z);
	SetPosition(&CurrLoc,&CurrRot);
}

BOOL EntityBulletBase::Touch(CollisionInfo *Info)
{
	// If a bullet touches anything it disappears.
	return TRUE;
}

float EntityBulletBase::GetDamage()
{
	return BULLET_DAMAGE;
}

void EntityBulletBase::GetVelocity(DCVector *OutVel)
{
	*OutVel=DCVector(StartVec.X,
					 StartVec.Y+TimeSinceStart*DefY*2.0f/BULLET_VELOCITY,
					 StartVec.Z);
}

HANDLE EntityBulletBase::GetMesh(BOOL ForRender)
{
	return (ForRender) ? Mesh : NULL;
}


//****************************************************************
// Normal bullet class. Identical to base bullet class except plays sound.
//****************************************************************
class EntityBulletNormal : protected EntityBulletBase
{
	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
};

// Manufacture function.
EntityBase *ManufactureEntityBulletNormal()
{
	void *Entity=new(EntityBulletNormal);
	
	return (EntityBase *)Entity;
}

void EntityBulletNormal::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBulletBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Play sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("BulletNormal")),InLoc,FALSE,THREE_QUARTER_VOLUME);
}

//****************************************************************
// Seeker bullet class.
//****************************************************************
class EntityBulletSeeker : protected EntityBulletBase
{
	DCVector Direction;
	float BestCosine;
	EntityBase *BestTarget;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void Shutdown();
	void ServerTick(float FrameDeltaTime);
	void ClientTick(float FrameDeltaTime);
	void GetVelocity(DCVector *OutVel);

	friend void FindTargetCallback(EntityBase *Entity, void *User);
};

// Manufacture function.
EntityBase *ManufactureEntityBulletSeeker()
{
	void *Entity=new(EntityBulletSeeker);
	
	return (EntityBase *)Entity;
}

static void FindTargetCallback(EntityBase *Entity, void *User)
{
#define THIS_ENTITY ((EntityBulletSeeker *)User)
	// Get potential target position.
	DCVector Loc, Rot;
	Entity->GetPosition(&Loc,&Rot);
	// Calculate normal from center to potential target.
	DCVector N=Loc - THIS_ENTITY->Loc;
	N.FastNormalize();
	// Calculate dot product (cosine of angle between objects).
	float Cosine=N | THIS_ENTITY->Direction;
	// Use this one if best so far.
	if (Cosine > THIS_ENTITY->BestCosine)
	{
		THIS_ENTITY->BestCosine=Cosine;
		THIS_ENTITY->BestTarget=Entity;
	}
#undef THIS_ENTITY
}

void EntityBulletSeeker::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBulletBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Find a target.
	BestCosine=SEEKER_TARGET_COSINE_LIMIT;
	BestTarget=NULL;
	Direction=DCVector(0,0,1);
	Direction.RotateX(Rot.X);
	Direction.RotateY(Rot.Y);
	gGame.GetCollisionEntities(COLLISION_BADDIE,FindTargetCallback,this);

	// If we got a target, add a reference to it.
	if (BestTarget)
		BestTarget->AddRef(&BestTarget);

	// Play sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("BulletNormal")),InLoc,FALSE,THREE_QUARTER_VOLUME);
}

void EntityBulletSeeker::Shutdown()
{
	// Remove reference to BestTarget if we have one.
	if (BestTarget)
		BestTarget->RemoveRef(&BestTarget);

	EntityBulletBase::Shutdown();
}

void EntityBulletSeeker::ServerTick(float FrameDeltaTime)
{
	// Expire bullet after a while.
	TimeSinceStart+=FrameDeltaTime;
	if (TimeSinceStart>BULLET_LIFETIME)
	{
		gGame.DestroyEntity(this);
		return;
	}

	// If we have a target, seek towards it.
	if (BestTarget)
	{
		// Get target location.
		DCVector TargetLoc, TargetRot;
		BestTarget->GetPosition(&TargetLoc,&TargetRot);
		// Temp copy of position.
		DCVector NewRot=Rot;
		DCVector NewLoc=Loc;
		// Seeker doesn't work well if tick rate is less than 30 fps.
		for (;FrameDeltaTime>0;FrameDeltaTime-=SEEKER_MAX_TICK_TIME)
		{
			float DeltaTime=__min(FrameDeltaTime,SEEKER_MAX_TICK_TIME);

			// Get vector towards target.
			DCVector TargetVector=TargetLoc - NewLoc;

			// Adjust bullet rotation towards target.
			float MaxRot=SEEKER_TURN_RATE*DeltaTime;
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
			float AbsRotY=(float)fabs(DesiredRotY);
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
			float AbsRotX=(float)fabs(DesiredRotX);
			if (AbsRotY <= SEEKER_MAX_ROT && AbsRotX <= SEEKER_MAX_ROT)
			{
				// Horizontal.
				if (AbsRotY>MaxRot)
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
				if (AbsRotX>MaxRot)
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
			}
			// Calculate movement based on new rotation.
			Direction=DCVector(0,0,1);
			Direction.RotateX(NewRot.X);
			Direction.RotateY(NewRot.Y);
			NewLoc+=(Direction*(BULLET_VELOCITY*DeltaTime));
		}

		// Set new postion.
		gGame.SetEntityPosition(this,&NewLoc,&NewRot);
	}
	else
	{
		// No seeking towards anything so just move, don't rotate.
		// We can just use old direction since without a target, it won't have changed.
		DCVector NewLoc=Loc+(Direction*(BULLET_VELOCITY*FrameDeltaTime));
		gGame.SetEntityPosition(this,&NewLoc,&Rot);
	}
}

// Seeker is not client side predicted.
void EntityBulletSeeker::ClientTick(float FrameDeltaTime)
{
}

void EntityBulletSeeker::GetVelocity(DCVector *OutVel)
{
	*OutVel=Direction*BULLET_VELOCITY;
}

//****************************************************************
// Explosive tip bullet class.
//****************************************************************
class EntityBulletExplosiveTip : EntityBulletBase
{
	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	BOOL Touch(CollisionInfo *Info);
	void Killed(void);
	float GetDamage();
};

// Manufacture function.
EntityBase *ManufactureEntityBulletExplosiveTip()
{
	void *Entity=new(EntityBulletExplosiveTip);
	
	return (EntityBase *)Entity;
}

void EntityBulletExplosiveTip::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBulletBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Play sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("BulletNormal")),InLoc,FALSE,FULL_VOLUME);
}

BOOL EntityBulletExplosiveTip::Touch(CollisionInfo *Info)
{
	// Killed.
	gGame.NotifyEntityKilled(this);

	// If a bullet touches anything it disappears.
	return TRUE;
}

void EntityBulletExplosiveTip::Killed(void)
{
	// Play sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("ExplosiveTipBoom")),&Loc,FALSE,HALF_VOLUME);

	// Create explosion.
	ParticleExplosion(&Loc, EXPLOSION_RADIUS, EXPLOSION_NUM_PARTICLES,
					  0.5f, 2.0f,
					  1.0f, 0xFFFF7F5F);
	// Create another explosion above it since the other one often ends up below ground.
	ParticleExplosion(&(Loc+DCVector(0,10.0f,0)), EXPLOSION_RADIUS, EXPLOSION_NUM_PARTICLES,
					  0.5f, 2.0f,
					  1.0f, 0xFFFF7F5F);
}

float EntityBulletExplosiveTip::GetDamage()
{
	return EXPLOSIVE_BULLET_DAMAGE;
}

//****************************************************************
// No gravity bullet class.
//****************************************************************
class EntityBulletNoGravity : EntityBulletBase
{
	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void ClientTick(float FrameDeltaTime);
	float GetDamage();
};

// Manufacture function.
EntityBase *ManufactureEntityBulletNoGravity()
{
	void *Entity=new(EntityBulletNoGravity);
	
	return (EntityBase *)Entity;
}

void EntityBulletNoGravity::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBulletBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Play sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("BulletBaddie")),InLoc);
}

void EntityBulletNoGravity::ClientTick(float FrameDeltaTime)
{
	TimeSinceStart+=FrameDeltaTime;

	// Since travel is linear we can predict path easily.
	DCVector CurrLoc=DCVector(StartLoc.X + StartVec.X*TimeSinceStart,
							  StartLoc.Y + StartVec.Y*TimeSinceStart,
							  StartLoc.Z + StartVec.Z*TimeSinceStart);
	DCVector CurrRot=Rot;
	SetPosition(&CurrLoc,&CurrRot);
}

float EntityBulletNoGravity::GetDamage()
{
	return BADDIE_BULLET_DAMAGE;
}

