/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENBuilding.cpp

Abstract:

    Entity "AI" - building.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCCollide.h"
#include "DCEnergy.h"
#include "DCParticle.h"

class EntityBuilding : public EntityBase
{
	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void Shutdown();
	BOOL Touch(CollisionInfo *Info);
	void Killed(void);
};

// Manufacture function.
EntityBase *ManufactureEntityBuilding()
{
	void *Entity=new(EntityBuilding);
	
	return (EntityBase *)Entity;
}

void EntityBuilding::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Adjust height so building sits properly on terrain.
	float Height=GetTerrainHeight(Loc.X,Loc.Z);
	gGame.SetEntityPosition(this,&DCVector(Loc.X,Height,Loc.Z),&Rot);
}

void EntityBuilding::Shutdown()
{
	// Tell lord we've been destroyed.
	EntityBase *Lord=gGame.GetLordEntity();
	if (Lord)
		Lord->Message((void *)1);

	EntityBase::Shutdown();
}

BOOL EntityBuilding::Touch(CollisionInfo *Info)
{
	// Weapons must destroy buildings in a single
	// hit. Buildings to not accumulate damage. This 
	// prevents the building suddenly exploding after
	// numerous hits with a pea shooter.
	if (Info->Damage >= BUILDING_ENERGY)
	{
		// Killed.
		gGame.NotifyEntityKilled(this);

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void EntityBuilding::Killed(void)
{
	// Create explosion.
	HANDLE Mesh=GetMesh(TRUE);
	if (Mesh)
	{
		float Radius=GetMeshBoundingRadius(Mesh,FALSE)*0.5f;

		ParticleExplosion(&(Loc+DCVector(0,Radius,0)), Radius, 15,
						  0.5f, 2.0f,
						  1.0f, 0xFFFF7F5F);
	}
}


// Special building which can't be destroyed and won't get targeted by bombers.
class EntityBuildingIndestructable : EntityBuilding
{
	BOOL Touch(CollisionInfo *Info);
	void Shutdown();
};

// Manufacture function.
EntityBase *ManufactureEntityBuildingIndestructable()
{
	void *Entity=new(EntityBuildingIndestructable);
	
	return (EntityBase *)Entity;
}

BOOL EntityBuildingIndestructable::Touch(CollisionInfo *Info)
{
	return FALSE;
}

void EntityBuildingIndestructable::Shutdown()
{
	// Regular shutdown, don't tell the lord anything.
	EntityBase::Shutdown();
}