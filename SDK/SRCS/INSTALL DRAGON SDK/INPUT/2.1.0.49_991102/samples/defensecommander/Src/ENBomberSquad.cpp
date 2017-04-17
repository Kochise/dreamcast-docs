/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENBomberSquad.cpp

Abstract:

    Entity "AI" - bomber related entities.

-------------------------------------------------------------------*/

// Bomber squad works by having the squad entity move around towards a target, and then
// sets the craft positions directly. The craft entities are dumb.

#include "DC.h"
#include "DCGame.h"
#include "DCWorld.h"
#include "DCEnergy.h"
#include "DCCollide.h"
#include "DCSound.h"
#include "DCParticle.h"

// 3 different types:
// 0 - low height
// 1 - medium height
// 2 - very high height

#define MAX_TICK_TIME (1.0f/10.0f) // Must tick at least 15 time per second.

#define MAX_CRAFT 3
#define SPEED 400.0f
#define SPACING 250.0f

#define START_HEIGHT 400.0f

#define VERT_TURN_RADIUS 500.0f
#define HORZ_TURN_RADIUS 1250.0f
#define VERT_TURN_RATE (SPEED/VERT_TURN_RADIUS)
#define HORZ_TURN_RATE (SPEED/HORZ_TURN_RADIUS)

#define MAX_UP_ATTACK_ANGLE (DC_TO_RADIANS(30.0f))
#define MAX_DOWN_ATTACK_ANGLE (DC_TO_RADIANS(45.0f))

#define ROLL_RATE (DC_PI*0.125f)
#define ROLL_AMOUNT (DC_TO_RADIANS(60.0f)/(5.0f/3.0f))

//#define STRAFE_RADIUS ((DCW_TERRAIN_LOW_OUTER_RADIUS+DCW_TERRAIN_HIGH_INNER_RADIUS)*0.5f)
#define STRAFE_RADIUS (DCW_TERRAIN_LOW_OUTER_RADIUS+750.0f)

#define EXPLOSION_RADIUS 80.0f
#define EXPLOSION_NUM_PARTICLES 25

static int BuildingClassID=0;

class EntityBomberSquad : EntityBase
{
	int Type,CurrentActiveCraft,NumCraft;
	EntityBase *Craft[MAX_CRAFT];
	float PosX[MAX_CRAFT];
	float PosZ[MAX_CRAFT];

	int State;
	float TargetHeight;
	float DangerTargetHeight;
	DCVector TargetBuildingLoc;

	DCVector TargetRot;
	DCVector RotRate;

	DCVector Direction;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void Shutdown();
	void ServerTick(float FrameDeltaTime);
};

// Manufacture function.
EntityBase *ManufactureEntityBomberSquad()
{
	void *Entity=new(EntityBomberSquad);
	
	return (EntityBase *)Entity;
}

void GetSquadPosition(int Number, float &X, float &Z)
{
	int RowSize,Row;

	Number+=1;

	for (Row=0,RowSize=1;;)
	{
		if (Number<=RowSize)
		{
			X=((RowSize-1)*0.5f - (Number-1)) * SPACING;
			Z=Row*SPACING;
			return;
		}
		Number-=RowSize;
		Row++;
		RowSize++;
	}
}

void EntityBomberSquad::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Then init the rest.
	// Then init the rest.
	Type=InUser2 % 3;
	CurrentActiveCraft=0;
	NumCraft=__min(InUser1,MAX_CRAFT);

	// Spawn the craft.
	int ClassID=gGame.GetEntityIDFromName(TEXT("EntityBomber"));
	HANDLE Mesh=GetMeshHandleFromName(TEXT("Bomber"));

	Craft[0]=NULL;
	for (int i=0;i<NumCraft;i++)
	{
		if (gGame.IsClient())
		{
			Craft[i]=NULL;
		}
		else
		{
			float X,Z;
			GetSquadPosition(i,X,Z);

			DCVector Tmp;
			Tmp.X=X;
			Tmp.Y=START_HEIGHT;
			Tmp.Z=DCW_SPAWN_RADIUS+Z;
			Tmp.RotateY(InRot->Y+DC_PI);

			Craft[i]=gGame.SpawnEntity(ClassID,COLLISION_BADDIE,Mesh,&Tmp,InRot,0,0);
			if (Craft[i])
				Craft[i]->AddRef(&Craft[i]);
			PosX[i]=X;
			PosZ[i]=Z;
		}
	}

	State=0;
	switch (Type)
	{
		case 2:
			TargetHeight=DCW_DANGER_HIGH_HEIGHT*1.5f;
			break;
		case 1:
			TargetHeight=DCW_DANGER_HIGH_HEIGHT*1.0f;
			break;
		default:
			TargetHeight=DCW_DANGER_HIGH_HEIGHT*0.5f;
	}
	DangerTargetHeight=__max(TargetHeight,DCW_DANGER_HIGH_HEIGHT);
	TargetBuildingLoc=DCVector(0,0,0);
	
	Rot=TargetRot=*InRot;
	Rot.X=TargetRot.X=DC_PI*0.5f; // Craft starts pointing directly upwards,
								  // hopefully helping it avoid the tops of the mountains.
	RotRate=DCVector(0,0,0);

	Direction=DCVector(0,0,1);
	Direction.RotateX(InRot->X);
	Direction.RotateY(InRot->Y);

	if (BuildingClassID==0)
		BuildingClassID=gGame.GetEntityIDFromName(TEXT("EntityBuilding"));
}

void EntityBomberSquad::Shutdown()
{
	for (int i=0;i<NumCraft;i++)
	{
		if (Craft[i])
			gGame.DestroyEntity(Craft[i]);
	}

	EntityBase::Shutdown();
}

static inline void GoForTargetHeight(float TargetHeight, float CurrentHeight, float &TargetRot, float &RotRate)
{
	if (CurrentHeight<TargetHeight)
	{
		float Diff=TargetHeight-CurrentHeight;
		if (Diff < VERT_TURN_RADIUS)
		{
			TargetRot=Diff * (MAX_UP_ATTACK_ANGLE/VERT_TURN_RADIUS);
		}
		else
		{
			TargetRot=MAX_UP_ATTACK_ANGLE;
		}
	}
	else
	{
		float Diff=CurrentHeight-TargetHeight;
		if (Diff < VERT_TURN_RADIUS)
		{
			TargetRot=Diff * (-MAX_DOWN_ATTACK_ANGLE/VERT_TURN_RADIUS);
		}
		else
		{
			TargetRot=-MAX_DOWN_ATTACK_ANGLE;
		}
	}
	RotRate=VERT_TURN_RATE;
}

static void CountCallback(EntityBase *Entity, void *User)
{
	if (Entity->ClassID==BuildingClassID)
	{
		int *Count=(int *)User;
		(*Count)++;
	}
}

struct CallbackStruct
{
	int CurrentCount;
	int DesiredCount;
	DCVector Loc;
};

static void TargetCallback(EntityBase *Entity, void *User)
{
	if (Entity->ClassID==BuildingClassID)
	{
		CallbackStruct *C=(CallbackStruct *)User;
	
		if (C->CurrentCount==C->DesiredCount)
		{
			DCVector Tmp;
			Entity->GetPosition(&(C->Loc),&Tmp);
		}
		C->CurrentCount++;
	}
}

void EntityBomberSquad::ServerTick(float FrameDeltaTime)
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

	// If all craft destroyed we are done.
	if (CurrentActiveCraft>=NumCraft)
	{
		gGame.DestroyEntity(this);
		return;
	}

	// Tick position of squad.
	DCVector NewLoc=Loc,NewRot=Rot;

	for (;FrameDeltaTime>0;FrameDeltaTime-=MAX_TICK_TIME)
	{
		float DeltaTime=__min(FrameDeltaTime,MAX_TICK_TIME);

		switch (State)
		{
			case 0: // Climbing up to top of mountains.
				if (NewLoc.X*NewLoc.X + NewLoc.Z*NewLoc.Z >
					DCW_TERRAIN_HIGH_OUTER_RADIUS*DCW_TERRAIN_HIGH_OUTER_RADIUS)
				{
					GoForTargetHeight(DangerTargetHeight,NewLoc.Y,TargetRot.X,RotRate.X);
					break;
				}
				else
				{
					State++;
				}
			case 1: // Acquiring target.
			{
				// Count buildings.
				int Count=0;
				gGame.GetCollisionEntities(COLLISION_GOODIE,CountCallback,&Count);
				if (Count)
				{
					CallbackStruct C;
					C.CurrentCount=0;
					C.DesiredCount=GoodRand() % Count;
					C.Loc=DCVector(0,0,0);
					gGame.GetCollisionEntities(COLLISION_GOODIE,TargetCallback,&C);

					TargetBuildingLoc=C.Loc;
				}
				else
				{
					TargetBuildingLoc=DCVector(0,0,0);
				}
				State++;
			}
			case 2: // Turning towards target.
				if (NewLoc.X*NewLoc.X + NewLoc.Z*NewLoc.Z >=
					STRAFE_RADIUS*STRAFE_RADIUS)
				{
					GoForTargetHeight(TargetHeight,NewLoc.Y,TargetRot.X,RotRate.X);

					// Get vector towards target.
					DCVector TargetVector=TargetBuildingLoc - NewLoc;

					// Figure out angle from craft to target.
					float H=FastSqrt(TargetVector.X*TargetVector.X + TargetVector.Z*TargetVector.Z);
					float DesiredRotY=(float)acos(TargetVector.Z/H);
					if (TargetVector.X > 0)
						DesiredRotY*=-1;

					while (NewRot.Y - DesiredRotY > DC_PI)
						DesiredRotY+=DC_PI*2;
					while (DesiredRotY - NewRot.Y > DC_PI)
						DesiredRotY-=DC_PI*2;

					TargetRot.Y=DesiredRotY;
					
					float Diff=(float)fabs(TargetRot.Y - NewRot.Y);
					while (Diff > DC_PI*2.0f)
						Diff-=DC_PI*2.0f;
					if (Diff < DC_TO_RADIANS(10))
						RotRate.Y=Diff * (HORZ_TURN_RATE/DC_TO_RADIANS(10));
					else
						RotRate.Y=HORZ_TURN_RATE;

					break;
				}
				else
				{
					RotRate.Y=0;
					State++;
				}
			case 3: // Strafing run.
				if (NewLoc.X*NewLoc.X + NewLoc.Z*NewLoc.Z <
					STRAFE_RADIUS*STRAFE_RADIUS)
				{
					GoForTargetHeight(TargetHeight,NewLoc.Y,TargetRot.X,RotRate.X);

					// Get vector towards target.
					DCVector TargetVector=TargetBuildingLoc - NewLoc;

					// Figure out angle from craft to target.
					float H=FastSqrt(TargetVector.X*TargetVector.X + TargetVector.Z*TargetVector.Z);
					float DesiredRotY=(float)acos(TargetVector.Z/H);
					if (TargetVector.X > 0)
						DesiredRotY*=-1;

					while (NewRot.Y - DesiredRotY > DC_PI)
						DesiredRotY+=DC_PI*2;
					while (DesiredRotY - NewRot.Y > DC_PI)
						DesiredRotY-=DC_PI*2;

					float Diff=(float)fabs(DesiredRotY - NewRot.Y);
					while (Diff > DC_PI*2.0f)
						Diff-=DC_PI*2.0f;
					if (Diff < DC_PI*0.5f)
					{
						TargetRot.Y=DesiredRotY;
						if (Diff < DC_TO_RADIANS(10))
							RotRate.Y=Diff * (HORZ_TURN_RATE/DC_TO_RADIANS(10));
						else
							RotRate.Y=HORZ_TURN_RATE;
					}
					else
					{
						RotRate.Y=0;
					}
					break;
				}
				else
				{
					State=1;
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
				NewRotX+=(SPEED/300.0f)*DeltaTime; // Turn radius is 300.
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
	Loc=NewLoc;Rot=NewRot;

	// Set position of craft.
	DCVector XVec(0,0,1),ZVec(0,0,1);
	XVec.RotateY(Rot.Y+DC_PI*0.5f);
	ZVec.RotateY(Rot.Y+DC_PI);

	for (int i=CurrentActiveCraft;i<NumCraft;i++)
	{
		if (Craft[i])
			gGame.SetEntityPosition(Craft[i],&(Loc + (XVec*PosX[i]) + (ZVec*PosZ[i])), &Rot);
	}
}

//*****************************************************************
// Craft entity.
//*****************************************************************
#define BOMB_SPAWN_X (1.87f*6)
#define BOMB_SPAWN_Y (-1.124f*6)
#define BOMB_TIME_INTERVAL 10.0f
#define BOMB_INITIAL_TIME_INTERVAL 12.0f
#define BOMB_DROP_RANGE 200.0f
#define BOMB_TARGET_INTERVAL 1.0f
#define BOMB_TARGET_LEAD SPEED*0.75f // Bomb travels forward about 1 seconds worth.

class EntityBomber : EntityBase
{
	float Energy;
	float TimeSinceLastBomb;

	BOOL HaveBombInfo;
	int BombClassID;
	HANDLE BombMesh;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void Shutdown();
	void ServerTick(float FrameDeltaTime);
	BOOL Touch(CollisionInfo *Info);
	void Killed(void);
	float GetDamage();
	void GetVelocity(DCVector *OutVel);
};

// Manufacture function.
EntityBase *ManufactureEntityBomber()
{
	void *Entity=new(EntityBomber);
	
	return (EntityBase *)Entity;
}

void EntityBomber::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	Energy=BOMBER_ENERGY;
	TimeSinceLastBomb=BOMB_TIME_INTERVAL-BOMB_INITIAL_TIME_INTERVAL; // Don't let bomber drop bombs straight away.

	HaveBombInfo=FALSE;
	BombClassID=0;
	BombMesh=NULL;
}

void EntityBomber::Shutdown()
{
	EntityBase::Shutdown();
}

struct TargetInfo
{
	BOOL HaveTargets;
	float BestDistSq;
	DCVector Center;
};

static void BombTargetCallback(EntityBase *Entity, void *User)
{
	if (Entity->ClassID==BuildingClassID)
	{
		TargetInfo *Info=(TargetInfo *)User;
		
		// Set this so we know there are targets.
		Info->HaveTargets=TRUE;

		// Get position of potential target.
		DCVector TLoc,TRot;
		Entity->GetPosition(&TLoc,&TRot);

		// See if distance from line too far.
		float DiffX=Info->Center.X-TLoc.X;
		float DiffZ=Info->Center.Z-TLoc.Z;
		float DistSq=DiffX*DiffX + DiffZ*DiffZ;
		if (DistSq < Info->BestDistSq)
		{
			Info->BestDistSq=DistSq;
		}
	}
}

void EntityBomber::ServerTick(float FrameDeltaTime)
{
	if (TimeSinceLastBomb >= BOMB_TIME_INTERVAL)
	{
		// Don't bother looking for a bombing target if outside the strafe radius.
		if (Loc.X*Loc.X + Loc.Z*Loc.Z < STRAFE_RADIUS*STRAFE_RADIUS)
		{
			// See if a building is in bombing range.
			// This is a bit CPU and cache intensive but other
			// techniques that were tried didn't work too well.
			float MaxDistSq=BOMB_DROP_RANGE+SPEED*FrameDeltaTime;
			MaxDistSq*=MaxDistSq;
			struct TargetInfo Info;
			Info.HaveTargets=FALSE;
			Info.BestDistSq=MaxDistSq;
			Info.Center=DCVector(0,0,BOMB_TARGET_LEAD);
			Info.Center.RotateY(Rot.Y);
			Info.Center+=Loc;
			gGame.GetCollisionEntities(COLLISION_GOODIE,BombTargetCallback,&Info);

			// When there are no targets, center (turret) is the target.
			if (!Info.HaveTargets)
			{
				float DistSq=Info.Center.X*Info.Center.X + Info.Center.Z*Info.Center.Z;
				if (DistSq < Info.BestDistSq)
					Info.BestDistSq=DistSq;
			}

			if (Info.BestDistSq<MaxDistSq)
			{
				// Spawn a bomb.
				if (!HaveBombInfo)
				{
					BombClassID=gGame.GetEntityIDFromName(TEXT("EntityBomb"));
					BombMesh=GetMeshHandleFromName(TEXT("Bomb"));
					HaveBombInfo=TRUE;
				}
				DCVector VecX,VecY,VecZ;
				Rot.CalculateViewVectors(&VecX,&VecY,&VecZ);
				gGame.SpawnEntity(BombClassID,COLLISION_BADDIE_FIRE,BombMesh,
								  &(Loc + (VecX*BOMB_SPAWN_X) + (VecY*BOMB_SPAWN_X)),
								  &DCVector(DC_PI*0.5f,Rot.Y,0),0,0);
				TimeSinceLastBomb=0;
			}
		}
	}
	else
	{
		TimeSinceLastBomb+=FrameDeltaTime;
	}
}

BOOL EntityBomber::Touch(CollisionInfo *Info)
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

void EntityBomber::Killed(void)
{
	// Play sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("BaddieBoom")),&Loc);

	// Create explosion.
	ParticleExplosion(&Loc, EXPLOSION_RADIUS, EXPLOSION_NUM_PARTICLES,
					  0.5f, 2.0f,
					  1.0f, 0xFFFF7F5F);
}

float EntityBomber::GetDamage()
{
	return BOMBER_DAMAGE;
}

void EntityBomber::GetVelocity(DCVector *OutVel)
{
	DCVector Vel(0,0,SPEED);
	Vel.RotateX(Rot.X);
	Vel.RotateY(Rot.Y);

	*OutVel=Vel;
}
