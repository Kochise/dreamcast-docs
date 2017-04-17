/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENTurret.cpp

Abstract:

    Entity "AI" - turret (player).

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCEnergy.h"
#include "DCRHUD.h"
#include "DCWorld.h"
#include "DCSound.h"
#include "DCParticle.h"\

#define BULLET_NORMAL_FIRE_PERIOD 0.15f
#define BULLET_RAPID_FIRE_PERIOD (BULLET_NORMAL_FIRE_PERIOD*0.5f)
#define BULLET_SEEKER_FIRE_PERIOOD (0.135f);

#define MISSILE_TARGET_MAX_COSINE 0.8910f // 27 Degrees.
#define MISSILE_TARGET_LOCK_TIME  1.5f

#define GB_X 9.0f
#define GB_Y -8.0f //-8.7f
#define GB_Z 40.0f // 34.8f

#define MB_X 26.6f
#define MB_Y 0.6f
#define MB_Z 35.0f

#define EXPLOSION_RADIUS 100.0f
#define EXPLOSION_NUM_PARTICLES 25

class EntityTurret : EntityBase
{
	// Levels.
	float Energy;
	// Power up counts.
	int RapidFire;
	int Seeker;
	int ExplosiveTip;
	// Class ID of enemy bullets.
	int BaddieBulletID;
	HANDLE TurretHitSound;

	HANDLE InsideMesh;

	// Gun variables.
	struct
	{
		int NormalClassID;
		int SeekerClassID;
		int ExplosiveTipClassID;
		HANDLE Mesh;

		int CurrentClassID;
		int *CurrentCount;
		
		float TimeSinceLast;
		float FirePeriod;
		int	CurrentGun;
	} Bullet;

	// Missile variables.
	struct _MissileStruct
	{
		int ClassID;
		HANDLE Mesh;

		float TimeTargeted;
		EntityBase *CurrentTarget;
		DCVector CurrentTargetLoc;
		EntityBase *CurrentMissile;
		int CurrentLauncher;
		BOOL LastFire2Status;

		// Used so we can't shoot powerups with missiles.
		int PowerUpClassID;

		// Temp variables used by baddie enumerator.
		float BestCosine;
		DCVector TurretDirection;
	} Missile;

	// Smart bomb variables.
	struct SmartBombStruct
	{
		int Count;
		BOOL LastFire3Status;
		int ClassID;
		EntityBase *CurrentBomb;
	} SmartBomb;

	// Base entity functions.
	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void Shutdown();
	void ServerTick(float FrameDeltaTime);
	void ClientTick(float FrameDeltaTime);
	void SetPosition(DCVector *InLoc,DCVector *InRot);
	HANDLE GetMesh(BOOL ForRender);
	BOOL Touch(CollisionInfo *Info);
	void Killed(void);
	void *Message(void *Message);

	// Other functions.
	void HandleBulletChange();
	void SendBullet(float StartTime);

	friend void FindTargetCallback(EntityBase *Entity, void *User);
};

// Manufacture function.
EntityBase *ManufactureEntityTurret()
{
	void *Entity=new(EntityTurret);
	
	return (EntityBase *)Entity;
}

void EntityTurret::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Init the rest.
	Energy=TURRET_ENERGY;
	RapidFire=Seeker=ExplosiveTip=0;
	InsideMesh=GetMeshHandleFromName(TEXT("TurretInside"));
	
	BaddieBulletID=gGame.GetEntityIDFromName(TEXT("EntityBulletNoGravity"));
	TurretHitSound=GetSoundHandleFromName(TEXT("TurretHit"));

	// Gun.
	Bullet.NormalClassID=gGame.GetEntityIDFromName(TEXT("EntityBulletNormal"));
	Bullet.SeekerClassID=gGame.GetEntityIDFromName(TEXT("EntityBulletSeeker"));
	Bullet.ExplosiveTipClassID=gGame.GetEntityIDFromName(TEXT("EntityBulletExplosiveTip"));
	Bullet.Mesh=GetMeshHandleFromName(TEXT("TracerNormal"));
	Bullet.CurrentClassID=Bullet.NormalClassID;
	Bullet.CurrentCount=NULL;
	Bullet.TimeSinceLast=-1;
	Bullet.FirePeriod=BULLET_NORMAL_FIRE_PERIOD;
	Bullet.CurrentGun=0;

	Missile.ClassID=gGame.GetEntityIDFromName(TEXT("EntityMissile"));
	Missile.Mesh=GetMeshHandleFromName(TEXT("Missile"));
	Missile.TimeTargeted=0;
	Missile.CurrentTarget=Missile.CurrentMissile=NULL;
	Missile.CurrentLauncher=0;
	Missile.LastFire2Status=gGame.GetFire2Status();
	Missile.PowerUpClassID=gGame.GetEntityIDFromName(TEXT("EntityPowerUpSpinner"));

	SmartBomb.Count=3;
	SmartBomb.LastFire3Status=gGame.GetFire3Status();
	SmartBomb.ClassID=gGame.GetEntityIDFromName(TEXT("EntitySmartBomb"));
	SmartBomb.CurrentBomb=NULL;

	// Spawn attached entities.
	if (!gGame.IsClient())
	{
		// We need to put this in here so it never gets executed directly on a client.
		// Spawn the temple.
		EntityBase *Temple=gGame.SpawnEntity(gGame.GetEntityIDFromName(TEXT("EntityBuildingIndestructable")),
											 COLLISION_NONE,
											 GetMeshHandleFromName(TEXT("Temple")),
											 &Loc,&DCVector(0,0,0),
											 0,0);
		// Get the top of the temple.
		DCVector TempleLoc,TempleRot;
		Temple->GetPosition(&TempleLoc,&TempleRot);
		DCVector TempleTop=GetMeshBoundingHighPoint(Temple->GetMesh(FALSE),&TempleLoc,&TempleRot);

		// Get the bottom of the turret.
		DCVector TurretBottom=GetMeshBoundingLowPoint(GetMeshHandleFromName(TEXT("TurretBase")),&Loc,&DCVector(0,0,0));

		// Move turret to be on top of temple.
		gGame.SetEntityPosition(this,&DCVector(Loc.X,Loc.Y-TurretBottom.Y+TempleTop.Y,Loc.Z),&Rot);
		
		// Spawn other parts of the turret.
		gGame.SpawnEntity(gGame.GetEntityIDFromName(TEXT("EntityBase")),
						  COLLISION_NONE,
						  GetMeshHandleFromName(TEXT("TurretBase")),
						  &Loc,&DCVector(0,0,0),
						  0,0);
		gGame.SpawnEntity(gGame.GetEntityIDFromName(TEXT("EntityTurretSwivel")),
						  COLLISION_NONE,
						  GetMeshHandleFromName(TEXT("TurretSwivel")),
						  &Loc,&DCVector(0,Rot.Y,0),
						  0,0);
	}

	// Set player entity. Must do it here do deal with case when we're a client.
	gGame.SetPlayerEntity(this);
}

void EntityTurret::Shutdown()
{
	// Can't be in player view any more.
	gGame.ForceObserverMode();

	// Remove references if we have any.
	if (Missile.CurrentTarget)
		Missile.CurrentTarget->RemoveRef(&Missile.CurrentTarget);
	if (Missile.CurrentMissile)
		Missile.CurrentMissile->RemoveRef(&Missile.CurrentMissile);
	if (SmartBomb.CurrentBomb)
		SmartBomb.CurrentBomb->RemoveRef(&SmartBomb.CurrentBomb);

	EntityBase::Shutdown();
}

// Handles the change is the type of bullet currently being fired. 
// This happens when we get a new powerup or one runs out.
void EntityTurret::HandleBulletChange()
{
	if (Seeker)
	{
		Bullet.CurrentClassID=Bullet.SeekerClassID;
		Bullet.CurrentCount=&Seeker;
		Bullet.FirePeriod=BULLET_SEEKER_FIRE_PERIOOD;
	}
	else if (ExplosiveTip)
	{
		Bullet.CurrentClassID=Bullet.ExplosiveTipClassID;
		Bullet.CurrentCount=&ExplosiveTip;
		Bullet.FirePeriod=BULLET_NORMAL_FIRE_PERIOD;
	}
	else if (RapidFire)
	{
		Bullet.CurrentClassID=Bullet.NormalClassID;
		Bullet.CurrentCount=&RapidFire;
		Bullet.FirePeriod=BULLET_RAPID_FIRE_PERIOD;
	}
	else
	{
		Bullet.CurrentClassID=Bullet.NormalClassID;
		Bullet.CurrentCount=NULL;
		Bullet.FirePeriod=BULLET_NORMAL_FIRE_PERIOD;
	}
}

// Spawns a bullet and sends it on its way.
void EntityTurret::SendBullet(float StartTime)
{
	// Calculate vectors representing view rotated axes.
	DCVector VecX,VecY,VecZ;
	Rot.CalculateViewVectors(&VecX,&VecY,&VecZ);
	// Figure out spawn location.
	DCVector SLoc=Loc + 
				  (VecX * (Bullet.CurrentGun ? GB_X : -GB_X)) +
				  (VecY * GB_Y) +
				  (VecZ * GB_Z);
	// Figure out deflection values.
	int Def=(FastRand()&0xFFFF) | (FastRand()<<16);

	// Spawn the bullet.
	gGame.SpawnEntity(Bullet.CurrentClassID,
					  COLLISION_GOODIE_FIRE,
					  Bullet.Mesh,
					  &SLoc,
					  &Rot,
					  DC_AS_INT(StartTime),
					  Def);
	
	// Swap to other gun.
	Bullet.CurrentGun^=0x01;

	// Decrease powerup.
	if (Bullet.CurrentCount)
	{
		if (--(*Bullet.CurrentCount)<=0)
			HandleBulletChange();
	}
}

static void FindTargetCallback(EntityBase *Entity, void *User)
{
#define THIS_ENTITY ((EntityTurret *)User)
	// Make sure not powerup.
	if (Entity->ClassID==THIS_ENTITY->Missile.PowerUpClassID)
		return;

	// Get potential target position.
	DCVector Loc, Rot;
	Entity->GetPosition(&Loc,&Rot);
	// Calculate normal from center to potential target.
	DCVector N=Loc - THIS_ENTITY->Loc;
	N.FastNormalize();
	// Calculate dot product (cosine of angle between objects).
	float Cosine=N | THIS_ENTITY->Missile.TurretDirection;
	// Use this one if best so far.
	if (Cosine > THIS_ENTITY->Missile.BestCosine &&
		(Loc.X*Loc.X + Loc.Z*Loc.Z) < DCW_DANGER_HIGH_OUTER_RADIUS*DCW_DANGER_HIGH_OUTER_RADIUS)
	{
		THIS_ENTITY->Missile.BestCosine=Cosine;
		THIS_ENTITY->Missile.CurrentTarget=Entity;
		THIS_ENTITY->Missile.CurrentTargetLoc=Loc;
	}
#undef THIS_ENTITY
}

void EntityTurret::ServerTick(float FrameDeltaTime)
{
	// If not in observer mode get position from viewer direction.
	if (!gGame.IsObserverMode())
	{
		DCVector ViewLoc,ViewRot;
		gGame.GetViewerCoords(&ViewLoc,&ViewRot);
		gGame.SetEntityPosition(this,&Loc,&ViewRot);
	}

	// Handle weapon fire so long as time isn't paused.
	if (!gGame.IsTimePaused())
	{
		// Handle guns.
		if (gGame.GetFire1Status() && !gGame.IsObserverMode())
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
				while (Bullet.TimeSinceLast>=Bullet.FirePeriod)
				{
					Bullet.TimeSinceLast-=Bullet.FirePeriod;
					SendBullet(Bullet.TimeSinceLast);
				}
			}
		}
		else
		{
			// Fire up, reset back to first bullet.
			Bullet.TimeSinceLast=-1;
		}

		// Handle missiles.
		BOOL Fire2Status=gGame.GetFire2Status();
		if (Missile.CurrentMissile)
		{
			// Already have a missile launched so just update location of target
			// for HUD's benefit.
			if (Missile.CurrentTarget)
			{
				DCVector TRot;
				Missile.CurrentTarget->GetPosition(&Missile.CurrentTargetLoc,&TRot);

				// If Target gone too far, loose it.
				
				if (Missile.CurrentTargetLoc.X*Missile.CurrentTargetLoc.X +
					Missile.CurrentTargetLoc.Z*Missile.CurrentTargetLoc.Z >
					DCW_DANGER_HIGH_OUTER_RADIUS*DCW_DANGER_HIGH_OUTER_RADIUS)
				{
					Missile.CurrentTarget->RemoveRef(&Missile.CurrentTarget);
					Missile.CurrentTarget=NULL;
				}
			}
			if (!Missile.CurrentTarget)
			{
				// No target so release lock.
				Missile.TimeTargeted=0;
				Missile.CurrentMissile->RemoveRef(&Missile.CurrentMissile);
				Missile.CurrentMissile=NULL;
			}
		}
		else
		{
			// Get view direction of turret.
			Missile.TurretDirection=DCVector(0,0,1);
			Missile.TurretDirection.RotateX(Rot.X);
			Missile.TurretDirection.RotateY(Rot.Y);

			// If we have a target, see if it is still valid.
			if (Missile.CurrentTarget)
			{
				DCVector TLoc,TRot;
				Missile.CurrentTarget->GetPosition(&TLoc,&TRot);
				DCVector TVec=TLoc-Loc;
				TVec.FastNormalize();
				if ((Missile.TurretDirection|TVec) < MISSILE_TARGET_MAX_COSINE ||
					(TLoc.X*TLoc.X + TLoc.Z*TLoc.Z) > DCW_DANGER_HIGH_OUTER_RADIUS*DCW_DANGER_HIGH_OUTER_RADIUS)
				{
					// Angle or distance too great so loose lock.
					Missile.CurrentTarget->RemoveRef(&Missile.CurrentTarget);
					Missile.CurrentTarget=NULL;
					Missile.TimeTargeted=0;
				}
				else
				{
					Missile.TimeTargeted+=FrameDeltaTime;
					Missile.CurrentTargetLoc=TLoc;
				}
			}

			// If we don't have a target, look for one.
			if (!Missile.CurrentTarget)
			{
				Missile.BestCosine=MISSILE_TARGET_MAX_COSINE;
				gGame.GetCollisionEntities(COLLISION_BADDIE,FindTargetCallback,this);

				// If we found a target, add a reference to it.
				if (Missile.CurrentTarget)
					Missile.CurrentTarget->AddRef(&Missile.CurrentTarget);

				// Always set time targeted back to 0.
				Missile.TimeTargeted=0;
			}

			// Launch missile if locked and fire button pressed.
			if (Fire2Status && Fire2Status!=Missile.LastFire2Status && 
				!gGame.IsObserverMode() && 
				Missile.TimeTargeted >= MISSILE_TARGET_LOCK_TIME)
			{
				// Calculate vectors representing view rotated axes.
				DCVector VecX,VecY,VecZ;
				Rot.CalculateViewVectors(&VecX,&VecY,&VecZ);
				// Figure out spawn location.
				DCVector SLoc=Loc + 
							  (VecX * (Missile.CurrentLauncher ? MB_X : -MB_X)) +
							  (VecY * MB_Y) +
							  (VecZ * MB_Z);

				// Spawn the Missile.
				Missile.CurrentMissile=
					gGame.SpawnEntity(Missile.ClassID,
									  COLLISION_GOODIE_FIRE,
									  Missile.Mesh,
									  &SLoc,
									  &Rot,
									  DC_AS_INT(Missile.CurrentTarget),
									  0);
				// If spawn successful, add reference.
				if (Missile.CurrentMissile)
					Missile.CurrentMissile->AddRef(&Missile.CurrentMissile);
	
				// Swap to other gun.
				Missile.CurrentLauncher^=0x01;
			}
		}
		Missile.LastFire2Status=Fire2Status;

		// Handle smart bomb.
		BOOL Fire3Status=gGame.GetFire3Status();
		if (Fire3Status && !SmartBomb.LastFire3Status &&
			SmartBomb.Count && !SmartBomb.CurrentBomb &&
			!gGame.IsObserverMode())
		{
			// Spawn a smart bomb.
			SmartBomb.CurrentBomb=
				gGame.SpawnEntity(SmartBomb.ClassID,
								  COLLISION_NONE,
								  NULL,
								  &Loc,
								  &Rot,
								  0,
								  0);
			// If spawn successful, add reference.
			if (SmartBomb.CurrentBomb)
				SmartBomb.CurrentBomb->AddRef(&SmartBomb.CurrentBomb);
			
			// Decrement smart bomb count.
			SmartBomb.Count--;
		}
		SmartBomb.LastFire3Status=Fire3Status;
	}
}

void EntityTurret::ClientTick(float FrameDeltaTime)
{
	// If not in observer mode set viewer to match turret.
	if (!gGame.IsObserverMode())
	{
		gGame.SetViewerCoords(&Loc,&Rot);
	}
}

void EntityTurret::SetPosition(DCVector *InLoc,DCVector *InRot)
{
	// Keep RotX between -pi and pi.
	if (InRot->X > DC_PI)
	{
		float RotX=InRot->X - (float)((int)(InRot->X/(DC_PI*2)))*DC_PI*2;
		if (RotX > DC_PI)
			RotX-=DC_PI*2;
		EntityBase::SetPosition(InLoc,&DCVector(RotX,InRot->Y,InRot->Z));
	}
	else
	{
		EntityBase::SetPosition(InLoc,InRot);
	}
}

HANDLE EntityTurret::GetMesh(BOOL ForRender)
{
	// Don't return mesh unless we are in observer mode.
	return (gGame.IsObserverMode() || !ForRender) ? Mesh : InsideMesh;
}

BOOL EntityTurret::Touch(CollisionInfo *Info)
{
	if (!gGame.IsGodMode())
	{
		if (Info->ClassID==BaddieBulletID)
		{
			gGame.PlaySound(TurretHitSound,&Loc,TRUE,QUARTER_VOLUME);
		}
		
		Energy-=Info->Damage;
		if (Energy<0)
		{
			// Killed.
			gGame.NotifyEntityKilled(this);

			return TRUE;
		}
	}
	return FALSE;
}

void EntityTurret::Killed(void)
{
	// Play lots of boom sounds.
	gGame.PlaySound(GetSoundHandleFromName(TEXT("RocketBoom")),&Loc);
	gGame.PlaySound(GetSoundHandleFromName(TEXT("MissileBoom")),&Loc);
	gGame.PlaySound(GetSoundHandleFromName(TEXT("BombBoom")),&Loc);
	gGame.PlaySound(GetSoundHandleFromName(TEXT("ExplosiveTipBoom")),&Loc);
	gGame.PlaySound(GetSoundHandleFromName(TEXT("BaddieBoom")),&Loc);

	// Create explosions. Second one is smaller and fades slower to give a lasting effect.
	ParticleExplosion(&(Loc+DCVector(0,EXPLOSION_RADIUS*0.5f,0)), EXPLOSION_RADIUS, EXPLOSION_NUM_PARTICLES,
					  0.5f, 2.0f,
					  1.0f, 0xFFFF7F5F);
	ParticleExplosion(&(Loc+DCVector(0,EXPLOSION_RADIUS*0.5f,0)), EXPLOSION_RADIUS*0.5f, EXPLOSION_NUM_PARTICLES/2,
					  0.25f, 1.0f,
					  1.0f, 0xFFFF7F5F);
}

void *EntityTurret::Message(void *Message)
{
	switch (((DWORD *)Message)[0])
	{
		case 1:
			// PowerUp. Types are:
			// 0 - Rapid fire.
			// 1 - Explosive tip.
			// 2 - Seeker.
			// 3 - Damage Repair.
			// 4 - Smart bomb.
			switch (((DWORD *)Message)[1])
			{
				case 0:
					RapidFire+=((DWORD *)Message)[2];
					HandleBulletChange();
					break;
				case 1:
					ExplosiveTip+=((DWORD *)Message)[2];
					HandleBulletChange();
					break;
				case 2:
					Seeker+=((DWORD *)Message)[2];
					HandleBulletChange();
					break;
				case 3:
					Energy+=TURRET_ENERGY*0.5f;
					if (Energy>TURRET_ENERGY)
						Energy=TURRET_ENERGY;
					break;
				case 4:
					SmartBomb.Count+=((DWORD *)Message)[2];
					break;

			}
			break;
		case 2:
		{
			// Request for HUD info.
			HUDInfo *Info=((HUDInfo **)Message)[1];

			if (Seeker)
			{
				Info->CurrentFire=1;
				Info->FireCount=Seeker;
			}
			else if (ExplosiveTip)
			{
				Info->CurrentFire=2;
				Info->FireCount=ExplosiveTip;
			}
			else if (RapidFire)
			{
				Info->CurrentFire=3;
				Info->FireCount=RapidFire;
			}
			else
			{
				Info->CurrentFire=0;
			}
			Info->SmartBombCount=SmartBomb.Count;
			Info->Energy=Energy*(1.0f/(float)TURRET_ENERGY);
			if (Missile.TimeTargeted)
			{
				if (Missile.TimeTargeted >= MISSILE_TARGET_LOCK_TIME)
					Info->MissileTargetStatus=2;
				else
					Info->MissileTargetStatus=1;
				Info->MissileTarget=Missile.CurrentTargetLoc;
			}
			else
			{
				Info->MissileTargetStatus=0;
			}
			return (void *)1;
		}
	}
	return NULL;
}
