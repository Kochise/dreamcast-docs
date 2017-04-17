/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENSFighterSquad.cpp

Abstract:

    Entity "AI" - small figher (gunship) related entities.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCEnergy.h"
#include "DCWorld.h"
#include "DCCollide.h"
#include "DCSound.h"
#include "DCParticle.h"

#define MAX_TICK_TIME (1.0f/15.0f) // Must tick at least 15 time per second.

#define MAX_CRAFT 4
#define SPEED 450.0f
#define SPACING 250.0f
#define VERTICAL_SPACING 50.0f

#define SPAWN_HEIGHT 300.0f
#define LOW_DESIRED_HEIGHT 350.0f
#define HIGH_DESIRED_HEIGHT 550.0f

#define OFF_AXIS 500.0f
#define ATTACK_RADIUS 1000.0f
#define PEEL_RADIUS 400.0f
#define PEEL_ANGLE DC_TO_RADIANS(45.0f)
#define TURN_AROUND_RADIUS (ATTACK_RADIUS+250.0f)

#define TURN_RADIUS 300.0f
#define TURN_RATE (SPEED/TURN_RADIUS)

#define ROLL_RATE DC_PI*2.0f
#define ROLL_AMOUNT (DC_TO_RADIANS(60.0f)/TURN_RATE)

#define TIME_TO_FULL_TURN 0.25f

#define MAX_ATTACK_ANGLE (DC_TO_RADIANS(45.0f))

#define FIRE_RADIUS 900.0f
#define FIRE_ANGLE_COSINE 0.95f 
#define FIRE_PERIOD 0.45f//0.3f
#define FIRE_ERROR DC_TO_RADIANS(1.0f)

#define GB_Y (-0.722f * 6)
#define GB_Z (8.039f * 6)

#define EXPLOSION_RADIUS 35.0f
#define EXPLOSION_NUM_PARTICLES 25

class EntitySFighterSquad : EntityBase
{
	int CurrentActiveCraft,NumCraft;
	EntityBase *Craft[MAX_CRAFT];

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void Shutdown();
	void ServerTick(float FrameDeltaTime);
};

// Manufacture function.
EntityBase *ManufactureEntitySFighterSquad()
{
	void *Entity=new(EntitySFighterSquad);
	
	return (EntityBase *)Entity;
}

void EntitySFighterSquad::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Then init the rest.
	CurrentActiveCraft=0;
	NumCraft=__min(InUser1,MAX_CRAFT);

	// Spawn the craft.
	float BaseHeight=(InUser2 & 0x04) ? LOW_DESIRED_HEIGHT : HIGH_DESIRED_HEIGHT;
	int Side=InUser2 & 0x08;
	int ClassID=gGame.GetEntityIDFromName(TEXT("EntitySFighter"));
	HANDLE Mesh=GetMeshHandleFromName(TEXT("SFighter"));
	int i;
	for (i=0;i<NumCraft;i++)
	{
		if (gGame.IsClient())
		{
			Craft[i]=NULL;
		}
		else
		{
			// Formation is always a simple 45 degree line.
			DCVector SpawnLoc(Side ? SPACING*i : -SPACING*i,
							  SPAWN_HEIGHT,
							  DCW_SPAWN_RADIUS + SPACING*i);
			SpawnLoc.RotateY(InRot->Y + DC_PI);
			float DesiredHeight=BaseHeight + VERTICAL_SPACING*i;

			Craft[i]=gGame.SpawnEntity(ClassID,COLLISION_BADDIE,Mesh,&SpawnLoc,InRot,0,DC_AS_INT(DesiredHeight));
			if (Craft[i])
				Craft[i]->AddRef(&Craft[i]);
		}
	}
}

void EntitySFighterSquad::Shutdown()
{
	for (int i=0;i<NumCraft;i++)
	{
		if (Craft[i])
			gGame.DestroyEntity(Craft[i]);
	}
	

	EntityBase::Shutdown();
}

void EntitySFighterSquad::ServerTick(float FrameDeltaTime)
{
	// See if all craft have been destroyed yet.
	while (1)
	{
		if (CurrentActiveCraft<NumCraft)
		{
			if (Craft[CurrentActiveCraft]==NULL)
			{
				CurrentActiveCraft++;
				continue;
			}
		}
		break;
	}

	// If all craft destroyed, this entity is done.
	if (CurrentActiveCraft>=NumCraft)
	{
		gGame.DestroyEntity(this);
		return;
	}
}

//*****************************************************************
// Craft entity.
//*****************************************************************
class EntitySFighter : EntityBase
{
	int Type;
	BOOL Side;
	float DesiredHeight;
	int State;
	float Energy;

	DCVector TargetPoint, AimPoint;

	DCVector TargetRot;
	DCVector RotRate;
	DCVector Direction;

	struct
	{
		int ClassID;
		HANDLE Mesh;
		float TimeSinceLast;
	} Bullet;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void Shutdown();
	void ServerTick(float FrameDeltaTime);
	BOOL Touch(CollisionInfo *Info);
	void Killed(void);
	float GetDamage();
	void GetVelocity(DCVector *OutVel);

	void SendBullet(float StartTime);
};

// Manufacture function.
EntityBase *ManufactureEntitySFighter()
{
	void *Entity=new(EntitySFighter);
	
	return (EntityBase *)Entity;
}

void EntitySFighter::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	DesiredHeight=DC_AS_FLOAT(InUser2);
	State=0;
	Energy=SMALL_FIGHTER_ENERGY;

	EntityBase *Player=gGame.GetPlayerEntity();
	DCVector Tmp;
	if (Player)
	{
		Player->GetPosition(&TargetPoint,&Tmp);
		TargetPoint.Y-=GB_Y; // Need to aim a little high/low to account for gun position.
	}
	else
	{
		TargetPoint=DCVector(0,0,0);
	}
	AimPoint=DCVector(0,0,0);
	
	TargetRot=*InRot;	
	RotRate=DCVector(0,0,0);

	Direction=DCVector(0,0,1);
	Direction.RotateX(InRot->X);
	Direction.RotateY(InRot->Y);

	Bullet.ClassID=gGame.GetEntityIDFromName(TEXT("EntityBulletNoGravity"));
	Bullet.Mesh=GetMeshHandleFromName(TEXT("TracerNormal"));
	Bullet.TimeSinceLast=-1;
}

void EntitySFighter::Shutdown()
{
	EntityBase::Shutdown();
}

static inline void GoForTargetHeight(float TargetHeight, float CurrentHeight, float &TargetRot, float &RotRate)
{
	if (CurrentHeight<TargetHeight)
	{
		float Diff=TargetHeight-CurrentHeight;
		if (Diff < TURN_RADIUS)
		{
			TargetRot=Diff * (MAX_ATTACK_ANGLE/TURN_RADIUS);
		}
		else
		{
			TargetRot=MAX_ATTACK_ANGLE;
		}
	}
	else
	{
		float Diff=CurrentHeight-TargetHeight;
		if (Diff < TURN_RADIUS)
		{
			TargetRot=Diff * (-MAX_ATTACK_ANGLE/TURN_RADIUS);
		}
		else
		{
			TargetRot=-MAX_ATTACK_ANGLE;
		}
	}
	RotRate=TURN_RATE;
}

static inline void GoForTargetPoint(float TargetX, float TargetZ, float CurrentX, float CurrentZ,
									float CurrentRot, float &TargetRot, float &RotRate,
									float DeltaTime)
{
	// Get vector towards target.
	float TargetVectorX=TargetX-CurrentX;
	float TargetVectorZ=TargetZ-CurrentZ;

	// Figure out angle from craft to target.
	float H=FastSqrt(TargetVectorX*TargetVectorX + TargetVectorZ*TargetVectorZ);
	float DesiredRot=(float)acos(TargetVectorZ/H);
	if (TargetVectorX > 0)
		DesiredRot*=-1;

	while (CurrentRot - DesiredRot > DC_PI)
		DesiredRot+=DC_PI*2;
	while (DesiredRot - DesiredRot > DC_PI)
		DesiredRot-=DC_PI*2;

	TargetRot=DesiredRot;
	
	float Diff=(float)fabs(TargetRot - CurrentRot);
	while (Diff > DC_PI*2.0f)
		Diff-=DC_PI*2.0f;
	if (Diff < DC_TO_RADIANS(15))
	{
		// Makes rotation out of turn smooth.
		RotRate=Diff * (TURN_RATE/DC_TO_RADIANS(15));
	}
	else
	{
		// Makes rotation into turn smooth.
		RotRate+=DeltaTime * (TURN_RATE/TIME_TO_FULL_TURN);
		if (RotRate > TURN_RATE)
			RotRate=TURN_RATE;
	}
}

static inline void GoForTargetAngle(DCVector &Target, DCVector &Current,
									float CurrentRot, float &TargetRot, float &RotRate,
									float DeltaTime)
{
	// Get vector towards target.
	DCVector TargetVector=Target-Current;

	// Figure out angle from craft to target.
	float Dist=TargetVector.FastLength();
	TargetRot=(float)asin(TargetVector.Y/Dist);

	float Diff=(float)fabs(TargetRot - CurrentRot);
	if (Diff < DC_TO_RADIANS(15))
	{
		// Makes rotation out of turn smooth.
		RotRate=Diff * (TURN_RATE/DC_TO_RADIANS(15));
	}
	else
	{
		RotRate=TURN_RATE;
	}
}

void EntitySFighter::ServerTick(float FrameDeltaTime)
{
	DCVector NewLoc=Loc,NewRot=Rot;

	float TmpFrameDeltaTime;
	for (TmpFrameDeltaTime=FrameDeltaTime;TmpFrameDeltaTime>0;TmpFrameDeltaTime-=MAX_TICK_TIME)
	{
		float DeltaTime=__min(TmpFrameDeltaTime,MAX_TICK_TIME);

		switch (State)
		{
			case 0: // Choose aim point.
				// Was going to have type 2 aim off to the side then turn in
				// but it seems ok with them always going straight for the player.
				AimPoint=DCVector(0,0,0);
				State++;
			case 1: // Heading for aim point.
				if (NewLoc.X*NewLoc.X + NewLoc.Z*NewLoc.Z > 
					ATTACK_RADIUS*ATTACK_RADIUS)
				{
					GoForTargetHeight(DesiredHeight,NewLoc.Y,TargetRot.X,RotRate.X);
					GoForTargetPoint(AimPoint.X,AimPoint.Z,NewLoc.X,NewLoc.Z,
									 NewRot.Y,TargetRot.Y,RotRate.Y,DeltaTime);
					break;
				}
				else
				{
					State++;
				}
			case 2: // Heading for target.
			{
				DCVector Diff=NewLoc-TargetPoint;
				if (Diff.X*Diff.X + Diff.Y*Diff.Y + Diff.Z*Diff.Z > 
					PEEL_RADIUS*PEEL_RADIUS)
				{
					GoForTargetAngle(TargetPoint,NewLoc,NewRot.Y,TargetRot.X,RotRate.X,DeltaTime);
					GoForTargetPoint(TargetPoint.X,TargetPoint.Z,NewLoc.X,NewLoc.Z,
									 NewRot.Y,TargetRot.Y,RotRate.Y,DeltaTime);
					break;
				}
				else
				{
					TargetRot.Y+=(GoodRand() & 0x01) ? PEEL_ANGLE : -PEEL_ANGLE;
					State++;
				}
			}
			case 3: // Peeling away.
			{
				GoForTargetHeight(DesiredHeight,NewLoc.Y,TargetRot.X,RotRate.X);
				// Make roll into turn smooth.
				RotRate.Y+=DeltaTime * (TURN_RATE/TIME_TO_FULL_TURN);
				if (RotRate.Y > TURN_RATE)
					RotRate.Y=TURN_RATE;
				// Make roll out of turn smooth.
				float Diff=(float)fabs(TargetRot.Y - NewRot.Y);
				if (Diff < DC_TO_RADIANS(15))
					RotRate.Y=Diff * (TURN_RATE/DC_TO_RADIANS(15));

				// See if we're ready to turn back for another attack.
				if (NewLoc.X*NewLoc.X + NewLoc.Z*NewLoc.Z >= 
					TURN_AROUND_RADIUS*TURN_AROUND_RADIUS)
					State=0; // Next tick we'll head for a new aim point.
				break;
			}
		}

		// Figure out twist.
		TargetRot.Z=-ROLL_AMOUNT * RotRate.Y;
		if (TargetRot.Y < NewRot.Y)
			TargetRot.Z*=-1;
		RotRate.Z=ROLL_RATE;

		// Do X rotation.
		float NewRotX=NewRot.X;
		if (TargetRot.X!=NewRotX)
		{
			if (NewRotX > TargetRot.X)
			{
				NewRotX-=RotRate.X*DeltaTime;
				if (NewRotX < TargetRot.X)
					NewRotX=TargetRot.X;
			}
			else
			{
				NewRotX+=RotRate.X*DeltaTime;
				if (NewRotX > TargetRot.X)
					NewRotX=TargetRot.X;
			}
		}

		// If necessary, override X rot to make sure we clear the terrain.
		if (NewLoc.Y < GetDangerHeight(NewLoc.X,NewLoc.Z))
		{
			float Angle=GetDangerAngle(NewLoc.X,NewLoc.Z,Direction.X,Direction.Z);
			if (NewRotX < Angle)
			{
				NewRotX=NewRot.X; // Start with original rotation.
				NewRotX+=(SPEED/100.0f)*DeltaTime; // Turn radius is 100.
				if (NewRotX > Angle)
					NewRotX=Angle;
			}
		}
		NewRot.X=NewRotX;

		// Do Y rotation.
		if (TargetRot.Y!=NewRot.Y)
		{
			if (NewRot.Y > TargetRot.Y)
			{
				NewRot.Y-=RotRate.Y*DeltaTime;
				if (NewRot.Y < TargetRot.Y)
					NewRot.Y=TargetRot.Y;
			}
			else
			{
				NewRot.Y+=RotRate.Y*DeltaTime;
				if (NewRot.Y > TargetRot.Y)
					NewRot.Y=TargetRot.Y;
			}
		}

		// Do Z rotation.
		if (TargetRot.Z!=NewRot.Z)
		{
			if (NewRot.Z > TargetRot.Z)
			{
				NewRot.Z-=RotRate.Z*DeltaTime;
				if (NewRot.Z < TargetRot.Z)
					NewRot.Z=TargetRot.Z;
			}
			else
			{
				NewRot.Z+=RotRate.Z*DeltaTime;
				if (NewRot.Z > TargetRot.Z)
					NewRot.Z=TargetRot.Z;
			}
		}
		
		// Move craft forward.
		Direction=DCVector(0,0,1);
		Direction.RotateX(NewRot.X);
		Direction.RotateY(NewRot.Y);
		NewLoc+=(Direction * (SPEED*DeltaTime));
	}

	// Quick sanity check so craft automatically disappear if they go too far off the screen.
	if (NewLoc.X*NewLoc.X + NewLoc.Z*NewLoc.Z > 
		DCW_TERRAIN_OUTER_RADIUS*DCW_TERRAIN_OUTER_RADIUS*1.5f*1.5f)
	{
		gGame.DestroyEntity(this);
		return;
	}

	// Set new position.
	gGame.SetEntityPosition(this,&NewLoc,&NewRot);

	// Handle firing of guns.
	// First see if gun trigger is down or not.
	BOOL TriggerDown=FALSE;
	DCVector Vec=TargetPoint-Loc;
	float Dist=Vec.FastLength();
	if (Dist < FIRE_RADIUS && Dist > PEEL_RADIUS)
	{
		// Close enough so see if on aim.
		Vec*=1.0f/Dist;
		if ((Vec|Direction) > FIRE_ANGLE_COSINE)
			TriggerDown=TRUE;
	}

	// Gun firing code based on turret code.
	if (!gGame.IsTimePaused())
	{
		if (TriggerDown)
		{
			// Fire down.
			if (Bullet.TimeSinceLast==-1)
			{
				// First bullet.
				Bullet.TimeSinceLast=0;
				SendBullet(0);
			}
			else
			{
				// Not first bullet.
				Bullet.TimeSinceLast+=FrameDeltaTime;
				while (Bullet.TimeSinceLast>=FIRE_PERIOD)
				{
					Bullet.TimeSinceLast-=FIRE_PERIOD;
					SendBullet(Bullet.TimeSinceLast);
				}
			}
		}
		else
		{
			// Fire up, reset back to first bullet.
			Bullet.TimeSinceLast=-1;
		}
	}
}

// Spawns a bullet and sends it on its way.
void EntitySFighter::SendBullet(float StartTime)
{
	// Calculate vectors representing view rotated axes.
	DCVector VecX,VecY,VecZ;
	Rot.CalculateViewVectors(&VecX,&VecY,&VecZ);
	// Figure out spawn location.
	DCVector SLoc=Loc + (VecY * GB_Y) + (VecZ * GB_Z);
	// Figure out spawn angle. We add a tiny bit of
	// random deflection to try and add a bit of realism.
	float DefX=(float)GoodRand()*(2.0f/(float)RAND_MAX) - 1.0f;
	float DefY=(float)GoodRand()*(2.0f/(float)RAND_MAX) - 1.0f;
	DCVector SRot=Rot + DCVector(DefX*DefX*DefX*FIRE_ERROR,
								 DefY*DefY*DefY*FIRE_ERROR,
								 0);

	// Spawn the bullet.
	gGame.SpawnEntity(Bullet.ClassID,
					  COLLISION_BADDIE_FIRE,
					  Bullet.Mesh,
					  &SLoc,
					  &SRot,
					  DC_AS_INT(StartTime),
					  0x7FFF7FFF /* No time increasing deflection. */);
}

BOOL EntitySFighter::Touch(CollisionInfo *Info)
{
	if (Info->Terrain) // Suppress terrain collisions.
		return FALSE;

	Energy-=Info->Damage;
	if (Energy<=0)
	{
		// Killed.
		gGame.NotifyEntityKilled(this);

		return TRUE;
	}
	return FALSE;
}

void EntitySFighter::Killed(void)
{
	// Play sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("BaddieBoom")),&Loc);

	// Create explosion.
	ParticleExplosion(&Loc, EXPLOSION_RADIUS, EXPLOSION_NUM_PARTICLES,
					  0.5f, 2.0f,
					  1.0f, 0xFFFF7F5F);
}

float EntitySFighter::GetDamage()
{
	return SMALL_FIGHTER_DAMAGE;
}

void EntitySFighter::GetVelocity(DCVector *OutVel)
{
	*OutVel=Direction*SPEED;
}
