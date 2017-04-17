/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENPowerUpDroneSquad.cpp

Abstract:

    Entity "AI" - power up drone related.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCWorld.h"
#include "DCEnergy.h"
#include "DCCollide.h"
#include "DCSound.h"
#include "DCParticle.h"

// 5 different types of formations, one for each powerup.
// 0 - Loop-the-looper.
// 1 - Upside downer.
// 2 - Go arounder.
// 3 - Side changer.
// 4 - Splitter.

#define MAX_TICK_TIME (1.0f/15.0f) // Must tick at least 15 time per second.

#define MAX_CRAFT 6
#define SPEED 500.0f
#define SPACING 80.0f
#define OFF_AXIS_LARGE 700.0f
#define OFF_AXIS_SMALL 500.0f
#define SHARP_TURN_RADIUS 300.0f
#define BLUNT_TURN_RADIUS OFF_AXIS_SMALL
#define SHARP_TURN_RATE (SPEED/SHARP_TURN_RADIUS)
#define BLUNT_TURN_RATE (SPEED/BLUNT_TURN_RADIUS)
#define DESIRED_HEIGHT 300.0f

#define ROLL_RATE DC_PI*2.0f
#define ROLL_AMOUNT (DC_TO_RADIANS(60.0f)/SHARP_TURN_RATE)

#define MAX_ATTACK_ANGLE (DC_TO_RADIANS(45.0f))

#define LOOPER_LOOP_DISTANCE 700.0f
#define UPSIDE_DOWNER_LOOP_DISTANCE 100.0f
#define SPLITTER_SPLIT_DISTANCE 500.0f
#define SIDE_CHANGER_CHANGE_DISTANCE 700.0f

#define EXPLOSION_RADIUS 30.0f
#define EXPLOSION_NUM_PARTICLES 25

class EntityPowerUpDroneSquad : EntityBase
{
	float Age;
	int Type,CurrentActiveCraft,NumCraft;
	EntityBase *Craft[MAX_CRAFT];
	DCVector LastLoc;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void Shutdown();
	void ServerTick(float FrameDeltaTime);
};

// Manufacture function.
EntityBase *ManufactureEntityPowerUpDroneSquad()
{
	void *Entity=new(EntityPowerUpDroneSquad);
	
	return (EntityBase *)Entity;
}

void EntityPowerUpDroneSquad::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Then init the rest.
	Age=0;
	Type=InUser2 % 5;
	CurrentActiveCraft=0;
	NumCraft=__min(InUser1,MAX_CRAFT);

	// Spawn craft, location depending on type.
	DCVector Locs[MAX_CRAFT];
	DCVector Rots[MAX_CRAFT];
	int Sides[MAX_CRAFT];
	int i;
	switch (Type)
	{
		case 0:
			for (i=0;i<NumCraft;i++)
			{
				DCVector Tmp;
				Tmp.X=(float)(NumCraft-1)*0.5f*SPACING*1.5f - i*SPACING*1.5f;
				Tmp.Y=DESIRED_HEIGHT;
				Tmp.Z=DCW_SPAWN_RADIUS + i*SPACING*1.5f;
				Tmp.RotateY(InRot->Y+DC_PI);
				Locs[i]=Tmp;
				Rots[i]=*InRot;
				Sides[i]=0;
			}
			break;
		case 1:
			for (i=0;i<NumCraft;i++)
			{
				DCVector Tmp;
				Tmp.X=OFF_AXIS_SMALL + (float)i * SPACING;
				Tmp.Y=DESIRED_HEIGHT;
				Tmp.Z=(i & 0x01) ? -DCW_SPAWN_RADIUS : DCW_SPAWN_RADIUS;
				Tmp.RotateY(InRot->Y+DC_PI);
				Locs[i]=Tmp;
				Rots[i]=*InRot;
				if (i & 0x01)
					Rots[i].Y+=DC_PI;
				Sides[i]=0;
			}
			break;
		case 2:
			for (i=0;i<NumCraft;i++)
			{
				DCVector Tmp;
				Tmp.X=(i & 0x01) ? -BLUNT_TURN_RADIUS : BLUNT_TURN_RADIUS;
				Tmp.Y=DESIRED_HEIGHT;
				Tmp.Z=DCW_SPAWN_RADIUS + (i/2)*SPACING*3;
				Tmp.RotateY(InRot->Y+DC_PI);
				Locs[i]=Tmp;
				Rots[i]=*InRot;
				Sides[i]=i;
			}
			break;
		case 3:
			for (i=0;i<NumCraft;i++)
			{
				DCVector Tmp;
				Tmp.X=(i & 0x01) ? -OFF_AXIS_LARGE : OFF_AXIS_LARGE;
				Tmp.Y=DESIRED_HEIGHT;
				Tmp.Z=DCW_SPAWN_RADIUS + i*SPACING;
				Tmp.RotateY(InRot->Y+DC_PI);
				Locs[i]=Tmp;
				Rots[i]=*InRot;
				Sides[i]=(i & 0x01);
			}
			break;
		case 4:
			for (i=0;i<NumCraft;i++)
			{
				DCVector Tmp;
				Tmp.X=(float)((NumCraft+1)/2)*SPACING - (i+0.5f)*SPACING;
				Tmp.Y=DESIRED_HEIGHT;
				Tmp.Z=DCW_SPAWN_RADIUS;
				if (i < (NumCraft+1)/2)
				{
					Tmp.Z+=i*SPACING;
					Sides[i]=0;
				}
				else
				{
					Tmp.Z+=(((NumCraft+1)/2)*2 -1-i)*SPACING;
					Sides[i]=1;
				}
				Tmp.RotateY(InRot->Y+DC_PI);
				Locs[i]=Tmp;
				Rots[i]=*InRot;
			}
			break;
	}

	// Spawn craft.
	int ClassID=gGame.GetEntityIDFromName(TEXT("EntityPowerUpDrone"));
	HANDLE Mesh=GetMeshHandleFromName(TEXT("PowerUpDrone"));
	for (i=0;i<NumCraft;i++)
	{
		if (gGame.IsClient())
		{
			Craft[i]=NULL;
		}
		else
		{
			Craft[i]=gGame.SpawnEntity(ClassID,COLLISION_BADDIE,Mesh,&Locs[i],&Rots[i],Type,Sides[i]);
			if (Craft[i])
				Craft[i]->AddRef(&Craft[i]);
		}
	}

	// Keep track of one of the craft since this is where 
	// we will spawn the powerup.
	LastLoc=Locs[0];
}

void EntityPowerUpDroneSquad::Shutdown()
{
	for (int i=0;i<NumCraft;i++)
	{
		if (Craft[i])
			gGame.DestroyEntity(Craft[i]);
	}
	
	EntityBase::Shutdown();
}

void EntityPowerUpDroneSquad::ServerTick(float FrameDeltaTime)
{
	// Increment age.
	Age+=FrameDeltaTime;

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

	// If all craft destroyed, spawn powerup.
	if (CurrentActiveCraft>=NumCraft)
	{
		// Make sure all destroyed.
		for (int i=0;i<NumCraft;i++)
			if (Craft[i])
				break;
		if (i==NumCraft)
		{
			gGame.SpawnEntity(gGame.GetEntityIDFromName(TEXT("EntityPowerUp")),
							  COLLISION_NONE,
							  NULL,
							  &LastLoc,&DCVector(0,0,0),
							  Type,
							  0);
		}
		gGame.DestroyEntity(this);
		return;
	}
	else
	{
		// Get position of one of the craft so we know where to spawn the powerup.
		DCVector Dummy;
		Craft[CurrentActiveCraft]->GetPosition(&LastLoc,&Dummy);

		// If been a while and craft outside, we're done with this craft.
		if (Age > (DCW_SPAWN_RADIUS/SPEED) && 
			LastLoc.X*LastLoc.X + LastLoc.Z*LastLoc.Z >
			DCW_SPAWN_RADIUS*DCW_SPAWN_RADIUS)
		{
			CurrentActiveCraft++;
		}
	}
}

//*****************************************************************
// Craft entity.
//*****************************************************************
class EntityPowerUpDrone : EntityBase
{
	int Type;
	int Side;
	int State;
	float Age;
	float Energy;

	DCVector TargetRot;
	DCVector RotRate;

	DCPlane Plane;

	DCVector Direction;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void Shutdown();
	void ServerTick(float FrameDeltaTime);
	BOOL Touch(CollisionInfo *Info);
	void Killed(void);
	float GetDamage();
	void GetVelocity(DCVector *OutVel);
};

// Manufacture function.
EntityBase *ManufactureEntityPowerUpDrone()
{
	void *Entity=new(EntityPowerUpDrone);
	
	return (EntityBase *)Entity;
}

void EntityPowerUpDrone::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	Type=InUser1 % 5;
	Side=InUser2;
	State=0;
	Age=0;
	Energy=POWER_UP_DRONE_ENERGY;
	TargetRot=*InRot;	
	RotRate=DCVector(0,0,0);

	// Set plane dependent on type.
	DCVector Vec(0,0,1);
	Vec.RotateY(InRot->Y+DC_PI);
	Plane.X=Vec.X;
	Plane.Y=Vec.Y;
	Plane.Z=Vec.Z;
	if (Type==0)
		Plane.W=-LOOPER_LOOP_DISTANCE;
	else if (Type==1)
		Plane.W=UPSIDE_DOWNER_LOOP_DISTANCE;
	else if (Type==3)
	{
		float R=FastSqrt(InLoc->X*InLoc->X + InLoc->Z*InLoc->Z);
		Plane.W=-(SIDE_CHANGER_CHANGE_DISTANCE + R - DCW_SPAWN_RADIUS);
	}
	else if (Type==4)
	{
		float R=FastSqrt(InLoc->X*InLoc->X + InLoc->Z*InLoc->Z);
		Plane.W=-(SPLITTER_SPLIT_DISTANCE + R - DCW_SPAWN_RADIUS);
	}
	else
		Plane.W=0;

	Direction=DCVector(0,0,1);
	Direction.RotateX(InRot->X);
	Direction.RotateY(InRot->Y);
}

void EntityPowerUpDrone::Shutdown()
{
	EntityBase::Shutdown();
}

static inline void GoForTargetHeight(float TargetHeight, float CurrentHeight, float &TargetRot, float &RotRate)
{
	if (CurrentHeight<TargetHeight)
	{
		float Diff=TargetHeight-CurrentHeight;
		if (Diff < SHARP_TURN_RADIUS)
		{
			TargetRot=Diff * (MAX_ATTACK_ANGLE/SHARP_TURN_RADIUS);
		}
		else
		{
			TargetRot=MAX_ATTACK_ANGLE;
		}
	}
	else
	{
		float Diff=CurrentHeight-TargetHeight;
		if (Diff < SHARP_TURN_RADIUS)
		{
			TargetRot=Diff * (-MAX_ATTACK_ANGLE/SHARP_TURN_RADIUS);
		}
		else
		{
			TargetRot=-MAX_ATTACK_ANGLE;
		}
	}
	RotRate=SHARP_TURN_RATE;
}

void EntityPowerUpDrone::ServerTick(float FrameDeltaTime)
{
	DCVector NewLoc=Loc,NewRot=Rot;

	for (;FrameDeltaTime>0;FrameDeltaTime-=MAX_TICK_TIME)
	{
		float DeltaTime=__min(FrameDeltaTime,MAX_TICK_TIME);

		switch (Type)
		{
			case 0:
				switch (State)
				{
					case 0: // Going to target.
						if ((Plane|NewLoc) > 0)
						{
							GoForTargetHeight(DESIRED_HEIGHT,NewLoc.Y,TargetRot.X,RotRate.X);
							break;
						}
						else
						{
							TargetRot.X=DC_PI;
							RotRate.X=BLUNT_TURN_RATE;
							State++;
						}
					case 1: // Looping up.
						if (NewRot.X<DC_PI)
						{
							break;
						}
						else
						{
							TargetRot.X=DC_PI*2;
							RotRate.X=SHARP_TURN_RATE;
							State++;
						}
					case 2: // Looping down.
						if (NewRot.X<DC_PI*2)
						{
							break;
						}
						else
						{
							TargetRot.X=NewRot.X=0;
							State++;
						}
					case 3: // Heading for mountains.
						if (NewLoc.X*NewLoc.X + NewLoc.Z*NewLoc.Z <= 
							DCW_TERRAIN_HIGH_INNER_RADIUS*DCW_TERRAIN_HIGH_INNER_RADIUS)
						{
							break;
						}
						else
						{
							NewRot.Z+=DC_PI*2.0f; // For effect, causes a quick spin to happen.
							State++;
						}
					case 4: // Leaving.
						GoForTargetHeight(0,NewLoc.Y,TargetRot.X,RotRate.X);
						break;
				}
				break;
			case 1:
				switch (State)
				{
					case 0: // Going to target.
						if ((Plane|NewLoc) > 0)
						{
							GoForTargetHeight(DESIRED_HEIGHT,NewLoc.Y,TargetRot.X,RotRate.X);
							break;
						}
						else
						{
							TargetRot.X=DC_PI;
							RotRate.X=SHARP_TURN_RATE;
							State++;
						}
					case 1: // Looping up.
						if (NewRot.X<DC_PI)
						{
							break;
						}
						else
						{
							NewRot.X=0;
							NewRot.Y-=DC_PI;
							TargetRot.X=NewRot.X;
							TargetRot.Y=NewRot.Y;
							NewRot.Z=DC_PI;
							State++;
						}
					case 2:
						if (NewRot.Z!=0)
						{
							break;
						}
						else
						{
							State++;
						}
					case 3: // Heading for mountains.
						if (NewLoc.X*NewLoc.X + NewLoc.Z*NewLoc.Z <= 
							DCW_TERRAIN_HIGH_INNER_RADIUS*DCW_TERRAIN_HIGH_INNER_RADIUS)
						{
							break;
						}
						else
						{
							State++;
						}
					case 4: // Leaving.
						GoForTargetHeight(0,NewLoc.Y,TargetRot.X,RotRate.X);
						break;
				}
				break;
			case 2:
				switch (State)
				{
					case 0: // Crossing mountains.
						if (NewLoc.X*NewLoc.X + NewLoc.Z*NewLoc.Z > 
							DCW_TERRAIN_HIGH_INNER_RADIUS*DCW_TERRAIN_HIGH_INNER_RADIUS)
						{
							TargetRot.X=0;
							RotRate.X=SHARP_TURN_RATE;
							break;
						}
						else
						{
							NewRot.Z+=DC_PI*2.0f; // For effect, causes a quick spin to happen.
							State++;
						}
					case 1: // Going to target.
						if ((Plane|NewLoc) > 0)
						{
							GoForTargetHeight(DCW_DANGER_LOW_HEIGHT+Side*SPACING,
											  Loc.Y,TargetRot.X,RotRate.X);
							break;
						}
						else
						{
							TargetRot.Y=NewRot.Y + ((Side & 0x01) ? DC_PI : -DC_PI);
							RotRate.Y=BLUNT_TURN_RATE;
							TargetRot.X=0;
							State++;
						}
					case 2: // Looping sideways.
						if (NewRot.Y!=TargetRot.Y)
						{
							break;
						}
						else
						{
							RotRate.Y=0;
							State++;
						}
					case 3: // Heading for mountains.
						if (NewLoc.X*NewLoc.X + NewLoc.Z*NewLoc.Z <= 
							DCW_TERRAIN_HIGH_INNER_RADIUS*DCW_TERRAIN_HIGH_INNER_RADIUS)
						{
							break;
						}
						else
						{
							State++;
						}
					case 4: // Leaving.
						GoForTargetHeight(0,NewLoc.Y,TargetRot.X,RotRate.X);
						break;
				}
				break;
			case 3:
				switch (State)
				{
					case 0: // Going to target.
						if ((Plane|NewLoc) > 0)
						{
							GoForTargetHeight(DESIRED_HEIGHT,NewLoc.Y,TargetRot.X,RotRate.X);
							break;
						}
						else
						{
							TargetRot.Y=NewRot.Y + (Side ? DC_PI*0.5f : -DC_PI*0.5f);
							RotRate.Y=SHARP_TURN_RATE;
							TargetRot.X=0;
							State++;
						}
					case 1: // Looping sideways.
						if (NewRot.Y!=TargetRot.Y)
						{
							break;
						}
						else
						{
							RotRate.Y=0;
							Age=0;
							State++;
						}
					case 2: // Crossing.
						if (Age < (OFF_AXIS_LARGE*2-SHARP_TURN_RADIUS*2)/SPEED)
						{
							Age+=DeltaTime;
							break;
						}
						else
						{
							TargetRot.Y=NewRot.Y + (Side ? -DC_PI*0.5f : DC_PI*0.5f);
							RotRate.Y=SHARP_TURN_RATE;
							State++;
						}
					case 3: // Looping sideways.
						if (NewRot.Y!=TargetRot.Y)
						{
							break;
						}
						else
						{
							RotRate.Y=0;
							State++;
						}
					case 4: // Heading for mountains.
						if (NewLoc.X*NewLoc.X + NewLoc.Z*NewLoc.Z <= 
							DCW_TERRAIN_HIGH_INNER_RADIUS*DCW_TERRAIN_HIGH_INNER_RADIUS)
						{
							break;
						}
						else
						{
							State++;
						}
					case 5: // Leaving.
						GoForTargetHeight(0,NewLoc.Y,TargetRot.X,RotRate.X);
						break;
				}
				break;
			case 4:
				switch (State)
				{
					case 0: // Going to target.
						if ((Plane|NewLoc) > 0)
						{
							GoForTargetHeight(DESIRED_HEIGHT,NewLoc.Y,TargetRot.X,RotRate.X);
							break;
						}
						else
						{
							TargetRot.Y=NewRot.Y + (Side ? -DC_PI*0.5f : DC_PI*0.5f);
							RotRate.Y=SHARP_TURN_RATE;
							TargetRot.X=0;
							State++;
						}
					case 1: // Looping sideways.
						if (NewRot.Y!=TargetRot.Y)
						{
							break;
						}
						else
						{
							RotRate.Y=0;
							State++;
						}
					case 2: // Heading for mountains.
						if (NewLoc.X*NewLoc.X + NewLoc.Z*NewLoc.Z <= 
							DCW_TERRAIN_HIGH_INNER_RADIUS*DCW_TERRAIN_HIGH_INNER_RADIUS)
						{
							break;
						}
						else
						{
							NewRot.Z+=DC_PI*2.0f; // For effect, causes a quick spin to happen.
							State++;
						}
					case 3: // Leaving.
						GoForTargetHeight(0,NewLoc.Y,TargetRot.X,RotRate.X);
						break;
				}
				break;
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
}

BOOL EntityPowerUpDrone::Touch(CollisionInfo *Info)
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

void EntityPowerUpDrone::Killed(void)
{
	// Play sound.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("BaddieBoom")),&Loc);

	// Create explosion.
	ParticleExplosion(&Loc, EXPLOSION_RADIUS, EXPLOSION_NUM_PARTICLES,
					  0.5f, 2.0f,
					  1.0f, 0xFFFF7F5F);
}

float EntityPowerUpDrone::GetDamage()
{
	return POWER_UP_DRONE_DAMAGE;
}

void EntityPowerUpDrone::GetVelocity(DCVector *OutVel)
{
	*OutVel=Direction*SPEED;
}
