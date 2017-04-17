/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GAEntity.cpp

Abstract:

    Game management - entity management.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"

#define MANUFACTURE_FUNCTION(FUNCTION) EntityBase *(FUNCTION)();

struct EntityData
{
	TCHAR *Name;
	MANUFACTURE_FUNCTION(*Manufacture);
};

// Have to have this for all entity factory functions.
extern MANUFACTURE_FUNCTION(ManufactureEntityBase);

extern MANUFACTURE_FUNCTION(ManufactureEntityBulletNoGravity);
extern MANUFACTURE_FUNCTION(ManufactureEntityRocket);
extern MANUFACTURE_FUNCTION(ManufactureEntityRocketWithSound);
extern MANUFACTURE_FUNCTION(ManufactureEntityBomb);
extern MANUFACTURE_FUNCTION(ManufactureEntityPowerUp);
extern MANUFACTURE_FUNCTION(ManufactureEntityPowerUpFlare);
extern MANUFACTURE_FUNCTION(ManufactureEntityPowerUpSpinner);
extern MANUFACTURE_FUNCTION(ManufactureEntityPowerUpDrone);
extern MANUFACTURE_FUNCTION(ManufactureEntitySFighter);
extern MANUFACTURE_FUNCTION(ManufactureEntityMFighter);
extern MANUFACTURE_FUNCTION(ManufactureEntityBomber);

extern MANUFACTURE_FUNCTION(ManufactureEntityBulletNormal);
extern MANUFACTURE_FUNCTION(ManufactureEntityBulletSeeker);
extern MANUFACTURE_FUNCTION(ManufactureEntityBulletExplosiveTip);
extern MANUFACTURE_FUNCTION(ManufactureEntityMissile);
extern MANUFACTURE_FUNCTION(ManufactureEntitySmartBomb);
extern MANUFACTURE_FUNCTION(ManufactureEntityTurret);
extern MANUFACTURE_FUNCTION(ManufactureEntityTurretSwivel);
extern MANUFACTURE_FUNCTION(ManufactureEntityBuilding);
extern MANUFACTURE_FUNCTION(ManufactureEntityBuildingIndestructable);
extern MANUFACTURE_FUNCTION(ManufactureEntityLord);
extern MANUFACTURE_FUNCTION(ManufactureEntityPowerUpDroneSquad);
extern MANUFACTURE_FUNCTION(ManufactureEntitySFighterSquad);
extern MANUFACTURE_FUNCTION(ManufactureEntityMFighterSquad);
extern MANUFACTURE_FUNCTION(ManufactureEntityBomberSquad);

// List of all types of entities. 
// Should be no more than 256 since BYTE is sent across network.
EntityData EntityList[]=
{
	{TEXT("EntityBase"),ManufactureEntityBase},

	{TEXT("EntityBulletNoGravity"),ManufactureEntityBulletNoGravity},
	{TEXT("EntityRocket"),ManufactureEntityRocket},
	{TEXT("EntityRocketWithSound"),ManufactureEntityRocketWithSound},
	{TEXT("EntityBomb"),ManufactureEntityBomb},
	{TEXT("EntityPowerUp"),ManufactureEntityPowerUp},
	{TEXT("EntityPowerUpFlare"),ManufactureEntityPowerUpFlare},
	{TEXT("EntityPowerUpSpinner"),ManufactureEntityPowerUpSpinner},
	{TEXT("EntityPowerUpDrone"),ManufactureEntityPowerUpDrone},
	{TEXT("EntitySFighter"),ManufactureEntitySFighter},
	{TEXT("EntityMFighter"),ManufactureEntityMFighter},
	{TEXT("EntityBomber"),ManufactureEntityBomber},

	// Stuff which isn't spawned in performance critical code at end.
	{TEXT("EntityBulletNormal"),ManufactureEntityBulletNormal},
	{TEXT("EntityBulletSeeker"),ManufactureEntityBulletSeeker},
	{TEXT("EntityBulletExplosiveTip"),ManufactureEntityBulletExplosiveTip},
	{TEXT("EntityMissile"),ManufactureEntityMissile},
	{TEXT("EntitySmartBomb"),ManufactureEntitySmartBomb},

	{TEXT("EntityTurret"),ManufactureEntityTurret},
	{TEXT("EntityTurretSwivel"),ManufactureEntityTurretSwivel},
	{TEXT("EntityBuilding"),ManufactureEntityBuilding},
	{TEXT("EntityBuildingIndestructable"),ManufactureEntityBuildingIndestructable},
	{TEXT("EntityLord"),ManufactureEntityLord},
	{TEXT("EntityPowerUpDroneSquad"),ManufactureEntityPowerUpDroneSquad},
	{TEXT("EntitySFighterSquad"),ManufactureEntitySFighterSquad},
	{TEXT("EntityMFighterSquad"),ManufactureEntityMFighterSquad},
	{TEXT("EntityBomberSquad"),ManufactureEntityBomberSquad},

	{NULL,NULL}
};

// Entity  functions.
int GameClass::GetEntityIDFromName(TCHAR *Name)
{
	for (int i=0;EntityList[i].Name!=NULL;i++)
		if (lstrcmp(EntityList[i].Name,Name)==0)
			return i;
	// Return 0 so at least we always get some kind of entity.
	return 0;
}

// Spawn functions.
EntityBase *GameClass::SpawnEntity(int ClassID, EntityCollisionType CollisionType, HANDLE Mesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2, int NetworkID)
{
	if (NetworkID==-1)
		NetworkID=GetNetworkID();
	
	// Send the spawn across the network.
	if (ClientCount)
		SendEntitySpawn(NetworkID,ClassID,CollisionType,GetMeshID(Mesh),InLoc,InRot,InUser1,InUser2);
	
	// Manufacture the class.
	EntityBase *Entity=(*(EntityList[ClassID].Manufacture))();
	DC_ASSERT(Entity);

	// Set ID's.
	Entity->ClassID=ClassID;

	// Set network ID.
	Entity->NetworkID=NetworkID;

	// Add the entity to the global entity list.
	ADD_TO_LINKED_LIST(EntityGlobalList,Entity,PreviousGlobal,NextGlobal);

	// Add the entity to the appropriate collision list.
	switch (CollisionType)
	{
		case COLLISION_BADDIE:
			ADD_TO_LINKED_LIST(EntityBaddieList,Entity,PreviousCollision,NextCollision);
			break;
		case COLLISION_GOODIE:
			ADD_TO_LINKED_LIST(EntityGoodieList,Entity,PreviousCollision,NextCollision);
			break;
		case COLLISION_BADDIE_FIRE:
			ADD_TO_LINKED_LIST(EntityBaddieFireList,Entity,PreviousCollision,NextCollision);
			break;
		case COLLISION_GOODIE_FIRE:
			ADD_TO_LINKED_LIST(EntityGoodieFireList,Entity,PreviousCollision,NextCollision);
			break;
	}

	// Store entity type.
	Entity->CollisionType=CollisionType;

	// Init the class.
	Entity->Init(Mesh,InLoc,InRot,InUser1,InUser2);

	return Entity;
}

// Destroy functions.
void GameClass::DestroyEntity(EntityBase *Entity)
{
	// Shutdown the entity.
	Entity->Shutdown();

	// Unhook from linked lists.
	REMOVE_FROM_LINKED_LIST(EntityGlobalList,Entity,PreviousGlobal,NextGlobal);
	switch (Entity->CollisionType)
	{
		case COLLISION_BADDIE:
			REMOVE_FROM_LINKED_LIST(EntityBaddieList,Entity,PreviousCollision,NextCollision);
			break;
		case COLLISION_GOODIE:
			REMOVE_FROM_LINKED_LIST(EntityGoodieList,Entity,PreviousCollision,NextCollision);
			break;
		case COLLISION_BADDIE_FIRE:
			REMOVE_FROM_LINKED_LIST(EntityBaddieFireList,Entity,PreviousCollision,NextCollision);
			break;
		case COLLISION_GOODIE_FIRE:
			REMOVE_FROM_LINKED_LIST(EntityGoodieFireList,Entity,PreviousCollision,NextCollision);
			break;
	}

	// Send destroy across network.
	if (ClientCount)
		SendEntityDestroy(Entity->NetworkID);

	// Free the memory for the entity.
	delete Entity;
}

// Sets the entity position.
void GameClass::SetEntityPosition(EntityBase *Entity, DCVector *InLoc, DCVector *InRot)
{
	// Send position across the network.
	if (ClientCount)
		SendEntityPosition(Entity->NetworkID,InLoc,InRot);

	// Set the position.
	Entity->SetPosition(InLoc,InRot);
}

void GameClass::NotifyEntityKilled(EntityBase *Entity)
{
	// Send across the network.
	if (ClientCount)
		SendEntityKilled(Entity->NetworkID);
	
	// Notify entity.
	Entity->Killed();
}


// Walks the entity list, returning all entities with a mesh to the callback.
void GameClass::GetAllEntityMeshes(void (*Callback)(HANDLE Mesh, DCVector *Loc, DCVector *Rot, void *User),
								   void *User, BOOL ForRender)
{
	HANDLE Mesh;
	DCVector Loc,Rot;

	for (EntityBase *Entity=EntityGlobalList;Entity;Entity=Entity->NextGlobal)
	{
		Mesh=Entity->GetMesh(ForRender);
		if (Mesh)
		{
			Entity->GetPosition(&Loc,&Rot);	
			Callback(Mesh,&Loc,&Rot,User);
		}
	}
}

// Walks the appropriate collision list, returning all entities with a mesh to the callback.
void GameClass::GetCollisionEntityMeshes(EntityCollisionType CollisionType,
										 void (*Callback)(HANDLE Mesh, DCVector *Loc, DCVector *Rot, void *User),
										 void *User, BOOL ForRender)
{
	// Get list.
	EntityBase *List;
	switch (CollisionType)
	{
		case COLLISION_BADDIE:
			List=EntityBaddieList;
			break;
		case COLLISION_GOODIE:
			List=EntityGoodieList;
			break;
		case COLLISION_BADDIE_FIRE:
			List=EntityBaddieFireList;
			break;
		case COLLISION_GOODIE_FIRE:
			List=EntityGoodieFireList;
			break;
		default:
			return;		
	}

	// Walk list and callback.
	HANDLE Mesh;
	DCVector Loc,Rot;

	for (EntityBase *Entity=List;Entity;Entity=Entity->NextCollision)
	{
		Mesh=Entity->GetMesh(ForRender);
		if (Mesh)
		{
			Entity->GetPosition(&Loc,&Rot);	
			Callback(Mesh,&Loc,&Rot,User);
		}
	}
}

// Walks the entity list, returning all entities with a mesh to the callback.
void GameClass::GetAllEntities(void (*Callback)(EntityBase *Entity, void *User),void *User)
{
	for (EntityBase *Entity=EntityGlobalList,*Next;Entity;Entity=Next)
	{
		Next=Entity->NextGlobal;
		Callback(Entity,User);
	}
}

// Walks the appropriate collision list, returning all entities with a mesh to the callback.
void GameClass::GetCollisionEntities    (EntityCollisionType CollisionType,
										 void (*Callback)(EntityBase *Entity, void *User),
										 void *User)
{
	// Get list.
	EntityBase *List;
	switch (CollisionType)
	{
		case COLLISION_BADDIE:
			List=EntityBaddieList;
			break;
		case COLLISION_GOODIE:
			List=EntityGoodieList;
			break;
		case COLLISION_BADDIE_FIRE:
			List=EntityBaddieFireList;
			break;
		case COLLISION_GOODIE_FIRE:
			List=EntityGoodieFireList;
			break;
		default:
			return;		
	}

	// Walk list and callback.
	for (EntityBase *Entity=List,*Next;Entity;Entity=Next)
	{
		Next=Entity->NextCollision;
		Callback(Entity,User);
	}
}

void *GameClass::SendEntityMessage(EntityBase *Entity, void *Message)
{
	if (Entity)
		return Entity->Message(Message);
	else
		return NULL;
}
