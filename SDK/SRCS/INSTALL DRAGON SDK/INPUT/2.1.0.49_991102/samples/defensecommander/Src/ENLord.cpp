/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    ENLord.cpp

Abstract:

    Entity "AI" - "Lord". Takes care of spawning baddies.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCWorld.h"

#define STAGE_MESSAGE_TIME 2.0f
#define STAGE_WAIT_TIME 1.0f

#define BADDIE_CAP 15

// Parameters for stages is hard coded here.
struct CraftStruct
{
	int GroupSize;
	int NumGroups;
};

struct StageStruct
{
	float SpawnDelta; // 0 means no more stages defined.
	CraftStruct PowerUpDrone;
	CraftStruct SFighter;
	CraftStruct MFighter;
	CraftStruct Bomber;
};

StageStruct Stages[]=
{
//	 Delta PowerUpDrone SFighter	MFighter	Bomber.
	{7.0f,	{5,2},		{3,3},		{2,3},		{1,1}	},
	{6.5f,	{5,2},		{3,3},		{2,3},		{2,1}	},
	{6.0f,	{6,2},		{3,4},		{3,3},		{2,2}	},
	{5.9f,	{6,2},		{4,4},		{3,4},		{3,2}	},
	{5.8f,	{6,3},		{4,5},		{3,4},		{3,2}	}
};

#define MAX_STAGES (sizeof(Stages)/sizeof(StageStruct))
#define MIN_SPAWN_DELTA 1.0f

struct EntityInfoStruct
{
	int ClassID;
	int GroupSize;
	DCVector Loc,Rot;
	float SpawnTime;
	int RandValue;

	EntityBase *Entity;
};

class EntityLord : EntityBase
{
	int State; // 0 = Starting stage, 1 = In stage, 2= Ending stage.
	float CurrentTime; // Reset to zero each time we enter a new state.

	int CurrentStage;
	int LastStageSeed;

	// Entity class IDs.
	int PowerUpDroneID;
	int SFighterID;
	int MFighterID;
	int BomberID;

	// Stage information.
	struct
	{
		int CurrentActiveEntity;
		int CurrentEntityToSpawn;
		int NumEntities;
		// List of currently spawned entities or entities we need to spawn.
		EntityInfoStruct *EntityInfo;
	} Stage;

	int LastPowerUp,SecondLastPowerUp;
	int LastBomber;

	int CurrentBuildingCount,TotalBuildingCount;
	BOOL NeedRecount;

	void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void Shutdown();
	void ServerTick(float FrameDeltaTime);
	void *Message(void *Message);

	void CreateStage(int Stage);
	void DestroyStage();
};

// Manufacture function.
EntityBase *ManufactureEntityLord()
{
	void *Entity=new(EntityLord);
	
	return (EntityBase *)Entity;
}

static int BuildingClassID;
static void CountCallback(EntityBase *Entity, void *User)
{
	if (Entity->ClassID==BuildingClassID)
	{
		int *Count=(int *)User;
		(*Count)++;
	}
}

void EntityLord::Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	// Call base init function first.
	EntityBase::Init(InMesh,InLoc,InRot,InUser1,InUser2);

	// Then init the rest.
	State=0;
	CurrentTime=0;
	CurrentStage=0;
	LastStageSeed=1;

	PowerUpDroneID=gGame.GetEntityIDFromName(TEXT("EntityPowerUpDroneSquad"));
	SFighterID=gGame.GetEntityIDFromName(TEXT("EntitySFighterSquad"));
	MFighterID=gGame.GetEntityIDFromName(TEXT("EntityMFighterSquad"));
	BomberID=gGame.GetEntityIDFromName(TEXT("EntityBomberSquad"));

	DCZeroMemory(&Stage,sizeof(Stage));

	// Make these seeker and explosive tip so the start order for
	// power ups is rapid, explosive tip, seeker.
	LastPowerUp=2;
	SecondLastPowerUp=1;

	LastBomber=1;

	// Count buildings.
	BuildingClassID=gGame.GetEntityIDFromName(TEXT("EntityBuilding"));
	TotalBuildingCount=0;
	gGame.GetCollisionEntities(COLLISION_GOODIE,CountCallback,&TotalBuildingCount);
	CurrentBuildingCount=TotalBuildingCount;
	NeedRecount=FALSE;

	// Set lord entity. Must do it here do deal with case when we're a client.
	gGame.SetLordEntity(this);
}

void EntityLord::Shutdown()
{
	DestroyStage();

	EntityBase::Shutdown();
}

void EntityLord::CreateStage(int StageNum)
{
	int Add=0;
	float SpawnDelta;

	// If we go past the end of the pre-defines stages, automatically increase
	// difficulty level somehow.
	if (StageNum >= MAX_STAGES)
	{
		Add=StageNum-MAX_STAGES+1;
		StageNum=MAX_STAGES-1;
	}

	// Figure out spawn delta.
	SpawnDelta=Stages[StageNum].SpawnDelta;
	int i;
	for (i=0;i<Add && SpawnDelta > MIN_SPAWN_DELTA; i++)
		SpawnDelta*=0.95f;
	if (SpawnDelta < MIN_SPAWN_DELTA)
		SpawnDelta=MIN_SPAWN_DELTA;

	// Figure out number of entities for this stage.
	int NumPowerUpDrone=Stages[StageNum].PowerUpDrone.NumGroups+Add/4;
	int NumSFighter=Stages[StageNum].SFighter.NumGroups+Add;
	int NumMFighter=Stages[StageNum].MFighter.NumGroups+Add;
	int NumBomber=Stages[StageNum].Bomber.NumGroups+Add/2;
	int NumEntities=NumPowerUpDrone+NumSFighter+NumMFighter+NumBomber;
	
	// Init stage structure.
	Stage.CurrentActiveEntity=0;
	Stage.CurrentEntityToSpawn=0;
	Stage.NumEntities=NumEntities;
	// Allocate space for entity structures.
	int Size=NumEntities*sizeof(EntityInfoStruct);
	Stage.EntityInfo=(EntityInfoStruct *)DCMalloc(Size);
	DC_ASSERT(Stage.EntityInfo);
	DCZeroMemory(Stage.EntityInfo,Size);

	// Insert each of the types of entities into the list, mostly randomly.
	SeedGoodRand(LastStageSeed);

	// Bombers - distributed evenly through stage.
	for (i=0;i<NumBomber;i++)
	{
		int Index=NumEntities-1-i*NumEntities/NumBomber;
		Index=__min(NumEntities-1,__max(0,Index));

		EntityInfoStruct *Info=Stage.EntityInfo+Index;
		Info->ClassID=BomberID;
		Info->GroupSize=Stages[StageNum].Bomber.GroupSize;
	}

	// Power ups - also distributed evenly through stage.
	for (i=0;i<NumPowerUpDrone;i++)
	{
		int Index=i*NumEntities/NumPowerUpDrone;
		Index=__min(NumEntities-1,__max(0,Index));

		// Walk forward until we find an unused entity.
		for (;Stage.EntityInfo[Index].ClassID!=0 && Index<NumEntities-1;Index++);
		// Walk backward until we find an unused entity.
		for (;Stage.EntityInfo[Index].ClassID!=0 && Index>0;Index--);

		EntityInfoStruct *Info=Stage.EntityInfo+Index;
		Info->ClassID=PowerUpDroneID;
		Info->GroupSize=Stages[StageNum].PowerUpDrone.GroupSize;
	}

	// Small fighters, randomly distributed.
	for (i=0;i<NumSFighter;i++)
	{
		int Index;

		// Look for an unused position by trying random positions.
		for (int j=0;j<100;j++) // Don't keep trying random positions forever.
		{
			Index=GoodRand() % NumEntities;
			if (Stage.EntityInfo[Index].ClassID==0)
				break;
		}

		// Walk forward until we find an unused entity.
		for (;Stage.EntityInfo[Index].ClassID!=0 && Index<NumEntities-1;Index++);
		// Walk backward until we find an unused entity.
		for (;Stage.EntityInfo[Index].ClassID!=0 && Index>0;Index--);

		EntityInfoStruct *Info=Stage.EntityInfo+Index;
		Info->ClassID=SFighterID;
		Info->GroupSize=Stages[StageNum].SFighter.GroupSize;
	}

	// Medium fighters, all unused positions 
	// (effectively random since random small fighter placement leaves random
	//  unused spots for medium fighters).
	for (i=0;i<NumEntities;i++)
	{
		EntityInfoStruct *Info=Stage.EntityInfo + i;
		if (Info->ClassID==0)
		{
			Info->ClassID=MFighterID;
			Info->GroupSize=Stages[StageNum].MFighter.GroupSize;
		}
	}

	// Finish filling in the entity structures.
	float CurrentSpawnTime=0;
	for (i=0;i<NumEntities;i++)
	{
		EntityInfoStruct *Info=Stage.EntityInfo+i;

		// Figure out a direction for the entity to come from.
		// Make sure direction isn't too near the last two entity spawns.
		float Angle;
		for (int j=0;j<100;j++) // Don't keep looking forever though.
		{
			Angle=((float)GoodRand()) * (DC_PI*2.0f/(float)GOOD_RAND_MAX);
			if (i>0)
			{
				float Delta=(float)fabs(Angle-Info[-1].Rot.Y);
				if (Delta>DC_PI)
					Delta=DC_PI*2 - Delta;
				if (Delta < DC_PI*0.25f)
					continue;
			}
			if (i>1)
			{
				float Delta=(float)fabs(Angle-Info[-2].Rot.Y);
				if (Delta>DC_PI)
					Delta=DC_PI*2 - Delta;
				if (Delta < DC_PI*0.125f)
					continue;
			}
			break;
		}
		// Set location and rotation.
		DCVector Tmp(0,0,DCW_SPAWN_RADIUS);
		Tmp.RotateY(Angle+DC_PI);
		Info->Loc=Tmp;
		Info->Rot=DCVector(0,Angle,0);

		// Set spawn time.
		if (Info->ClassID==BomberID)
		{
			// Bombers always spawn together with something else 
			// (the entity previous in the list).
			Info->SpawnTime=CurrentSpawnTime-SpawnDelta;
		}
		else
		{
			Info->SpawnTime=CurrentSpawnTime;
			CurrentSpawnTime+=SpawnDelta;//*0.1;
		}

		// Limit types of power ups depending on stage.
		// No smart bombs or health powerups in first two stages
		// since player isn't likely to need them.
		// Also, make sure powerup isnt the same as one of the last
		// two.
		if (Info->ClassID==PowerUpDroneID)
		{
			for (int j=0;j<100;j++)	// Don't hunt forever.
			{
				Info->RandValue=GoodRand();
				if (StageNum < 2)
					Info->RandValue%=3;
				else
					Info->RandValue%=5;
				if (Info->RandValue!=LastPowerUp && 
					Info->RandValue!=SecondLastPowerUp)
					break;
			}
			SecondLastPowerUp=LastPowerUp;
			LastPowerUp=Info->RandValue;
		}
		else if (Info->ClassID==BomberID)
		{
			for (int j=0;j<100;j++)	// Don't hunt forever.
			{
				Info->RandValue=GoodRand();
				if (StageNum < 2)
				{
					Info->RandValue%=2;
				}
				else
				{
					// High ones are hard to hit so make them less likely.
					Info->RandValue%=6;
					if (Info->RandValue==3 || Info->RandValue==4)
						Info->RandValue=0;
					else if (Info->RandValue==5)
						Info->RandValue=1;
				}
				if (Info->RandValue!=LastBomber)
					break;
			}
			LastBomber=Info->RandValue;
		}
		else
		{
			// Set rand value.
			Info->RandValue=GoodRand();
		}
	}

	// Save off a new seed for the next stage.
	LastStageSeed=GoodRand();
}

void EntityLord::DestroyStage()
{
	if (Stage.EntityInfo)
	{
		for (int i=0;i<Stage.NumEntities;i++)
		{
			if (Stage.EntityInfo[i].Entity)
			{
				Stage.EntityInfo[i].Entity->RemoveRef(&Stage.EntityInfo[i].Entity);
				Stage.EntityInfo[i].Entity=NULL;
			}
		}
		DCFree(Stage.EntityInfo);
		DCZeroMemory(&Stage,sizeof(Stage));
	}
}

void BaddieCountCallback(EntityBase *Entity, void *User)
{
	int *Count=(int *)User;
	(*Count)++;
}

void EntityLord::ServerTick(float FrameDeltaTime)
{
	CurrentTime+=FrameDeltaTime;
	
	// State 0 - Spawn stage.
	if (State==0)
	{
		// Immediately create the stage and move on.
		State=1;
		CurrentTime=0;

		CreateStage(CurrentStage);
	}
	
	// State 1 - Stage is running.
	if (State==1)
	{
		// Spawn any things that need spawning.
		while (1)
		{
			if (Stage.CurrentEntityToSpawn < Stage.NumEntities)
			{
				if (Stage.EntityInfo[Stage.CurrentEntityToSpawn].SpawnTime <= CurrentTime)
				{
					// Do a quick check to make sure there arent too many entities.
					// This will stop network traffic and rendering performance
					// from getting too insane.
					int Count=0;
					gGame.GetCollisionEntities(COLLISION_BADDIE, BaddieCountCallback, &Count);
					if (Count > BADDIE_CAP)
						break;
					
					// Spawn this entity.
					EntityInfoStruct *Info=Stage.EntityInfo + Stage.CurrentEntityToSpawn;

					Info->Entity=gGame.SpawnEntity(
						Info->ClassID,COLLISION_NONE,NULL,
						&Info->Loc,&Info->Rot,
						Info->GroupSize,Info->RandValue);
					if (Info->Entity)
						Info->Entity->AddRef(&Info->Entity);
			
					// Move on to next entity.
					Stage.CurrentEntityToSpawn++;
					continue;
				}
			}
			break;
		}

		// Move marker which keeps track of first active entity forward if necessary.
		while (Stage.CurrentActiveEntity < Stage.CurrentEntityToSpawn &&
			   Stage.EntityInfo[Stage.CurrentActiveEntity].Entity==NULL)
			Stage.CurrentActiveEntity++;
		
		if (Stage.CurrentActiveEntity>=Stage.NumEntities)
		{
			// No more entities active, stage over, move to next state.
			DestroyStage();
			
			State=2;
			CurrentTime=0;
			CurrentStage++;
		}
	}

	// State 2 - Waiting before going to next stage.
	if (State==2)
	{
		if (CurrentTime>STAGE_WAIT_TIME)
		{
			State=0;
			CurrentTime=0;
		}
	}

	// Count buildings if necessary.
	if (NeedRecount)
	{
		CurrentBuildingCount=0;
		gGame.GetCollisionEntities(COLLISION_GOODIE,CountCallback,&CurrentBuildingCount);
		NeedRecount=FALSE;
	}
}

void *EntityLord::Message(void *Message)
{
	if ((int)Message==0 && State==1 && CurrentTime<STAGE_MESSAGE_TIME)
		return (void *)(CurrentStage+1);
	if ((int)Message==1)
	{
		// Building is telling us it is destroyed.
		CurrentBuildingCount--;
		NeedRecount=TRUE; // Do a recount in case things get out of sync.
		return NULL;
	}
	if ((int)Message==2)
	{
		// Return amount of buildings left.
		union
		{
			float F;
			void *V;
		}Ret;
		Ret.F=(TotalBuildingCount) ? (float)CurrentBuildingCount/(float)TotalBuildingCount : 0;
		Ret.F=__min(1.0f,__max(0.0f,Ret.F));
		return Ret.V;
	}

	return NULL;	
}
