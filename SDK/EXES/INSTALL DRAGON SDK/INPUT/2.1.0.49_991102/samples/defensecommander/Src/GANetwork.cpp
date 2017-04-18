/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    GANetwork.cpp

Abstract:

    Game management - intermediate network handling.
	Calls Network.cpp

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGame.h"
#include "DCNetwork.h"
#include "DCSound.h"

#define SEND_NETWORK_MESSAGE(a,b) \
{ \
	if (gGame.DemoFile) \
		gGame.RecordMessage(a,b); \
	else \
		/*SendNetworkPacket(a,b);*/ \
		gGame.BufferMessage(a,b); \
}

struct SpawnStruct
{
	BYTE MessageID;
	BYTE EntityID[3];
	BYTE ClassID;
	BYTE CollisionType;
	BYTE MeshID;
	BYTE dwPos[3][4];
	BYTE iUser1[4],iUser2[4];
};

struct DestroyStruct
{
	BYTE MessageID;
	BYTE EntityID[3];
};

struct PositionStruct
{
	BYTE MessageID;
	BYTE EntityID[3];
	BYTE dwPos[3][4];
};

struct KilledStruct
{
	BYTE MessageID;
	BYTE EntityID[3];
};

struct NameStruct
{
	BYTE MessageID;
	BYTE ObjectID;
	BYTE wObjectName[2];
};

struct SoundStruct
{
	BYTE MessageID;
	BYTE SoundID;
	BYTE wLoc[3][2];
	BYTE Volume;
};

struct SoundNoAttenuateStruct
{
	BYTE MessageID;
	BYTE SoundID;
	BYTE Volume;
};

struct StartFrameStruct
{
	BYTE MessageID;
	BYTE fDeltaTime[4];
};

// Larger data types must be individually packed, unpacked into byte arrays
// so packing is as tight as possible and also to remove any potential problems
// with alignment.

static inline int MakeNetworkID(BYTE *Src) // Network IDs are 24 bit.
{
	union
	{
		BYTE b[4];
		int i;
	} Tmp;

	Tmp.b[0]=Src[0];
	Tmp.b[1]=Src[1];
	Tmp.b[2]=Src[2];
	Tmp.b[3]=0;

	return Tmp.i;
}

#ifdef DREAMCAST // Dreamcast can't handle unaligned data.

static inline WORD MakeWord(BYTE *Src)
{
	union
	{
		BYTE b[2];
		WORD w;
	} Tmp;

	Tmp.b[0]=Src[0];
	Tmp.b[1]=Src[1];

	return Tmp.w;
}

static inline DWORD MakeDword(BYTE *Src)
{
	union
	{
		BYTE b[4];
		DWORD dw;
	} Tmp;

	Tmp.b[0]=Src[0];
	Tmp.b[1]=Src[1];
	Tmp.b[2]=Src[2];
	Tmp.b[3]=Src[3];

	return Tmp.dw;
}

static inline int MakeInt(BYTE *Src)
{
	union
	{
		BYTE b[4];
		int i;
	} Tmp;

	Tmp.b[0]=Src[0];
	Tmp.b[1]=Src[1];
	Tmp.b[2]=Src[2];
	Tmp.b[3]=Src[3];

	return Tmp.i;
}

static inline float MakeFloat(BYTE *Src)
{
	union
	{
		BYTE b[4];
		float f;
	} Tmp;

	Tmp.b[0]=Src[0];
	Tmp.b[1]=Src[1];
	Tmp.b[2]=Src[2];
	Tmp.b[3]=Src[3];

	return Tmp.f;
}

static inline void PackWord(BYTE *Dst, WORD Src)
{
	union
	{
		BYTE b[2];
		WORD w;
	} Tmp;

	Tmp.w=Src;
	
	Dst[0]=Tmp.b[0];
	Dst[1]=Tmp.b[1];
}

static inline void PackDword(BYTE *Dst, DWORD Src)
{
	union
	{
		BYTE b[4];
		DWORD dw;
	} Tmp;

	Tmp.dw=Src;
	
	Dst[0]=Tmp.b[0];
	Dst[1]=Tmp.b[1];
	Dst[2]=Tmp.b[2];
	Dst[3]=Tmp.b[3];
}

static inline void PackInt(BYTE *Dst, int Src)
{
	union
	{
		BYTE b[4];
		int i;
	} Tmp;

	Tmp.i=Src;
	
	Dst[0]=Tmp.b[0];
	Dst[1]=Tmp.b[1];
	Dst[2]=Tmp.b[2];
	Dst[3]=Tmp.b[3];
}

static inline void PackFloat(BYTE *Dst, float Src)
{
	union
	{
		BYTE b[4];
		float f;
	} Tmp;

	Tmp.f=Src;
	
	Dst[0]=Tmp.b[0];
	Dst[1]=Tmp.b[1];
	Dst[2]=Tmp.b[2];
	Dst[3]=Tmp.b[3];
}

#else // Intel can handle unaligned data.

static inline WORD MakeWord(BYTE *Src)
{
	return *((WORD *)Src);
}

static inline DWORD MakeDword(BYTE *Src)
{
	return *((DWORD *)Src);
}

static inline int MakeInt(BYTE *Src)
{
	return *((int *)Src);
}

static inline float MakeFloat(BYTE *Src)
{
	return *((float *)Src);
}

static inline void PackWord(BYTE *Dst, WORD Src)
{
	*((WORD *)Dst)=Src;
}

static inline void PackDword(BYTE *Dst, DWORD Src)
{
	*((DWORD *)Dst)=Src;
}

static inline void PackInt(BYTE *Dst, int Src)
{
	*((int *)Dst)=Src;
}

static inline void PackFloat(BYTE *Dst, float Src)
{
	*((float *)Dst)=Src;
}

#endif

static inline DWORD PackPos(float Loc, float Rot)
{
	DWORD Ret=(int)(Rot*1024.0f/(DC_PI*2.0f));
	if (Ret < 0)
		Ret+=0x80000000;
	Ret&=0x00000FFF;
	Ret|=0xFFFFF000 & DC_AS_DWORD(Loc);
	return Ret;
}

static inline void UnpackPos(float &Loc, float &Rot, DWORD Packed)
{
	DWORD Tmp=Packed&0xFFFFF000;	
	Loc=DC_AS_FLOAT(Tmp);
	Rot=(float)(Packed & 0x0FFF) * (DC_PI*2.0f)/1024.0f;
}

static inline WORD PackLoc(float Loc)
{
	union
	{
		WORD W[2];
		float f;
	} U;

	U.f=Loc;
	return U.W[1];
}

static inline void UnpackLoc(float &Loc, WORD Packed)
{
	union
	{
		WORD W[2];
		float f;
	} U;

	U.W[0]=0;
	U.W[1]=Packed;
	Loc=U.f;
}


// Callback from network receive code.
void GameNetworkCallback(void *Buffer, int Size)
{
	switch (((BYTE *)Buffer)[0])
	{
		case GNM_CLIENT_CONNECT:
			// Client has attached so send it the game state.
			gGame.ClientCount++;
			gGame.SendGameState();
			break;
		case GNM_CLIENT_DISCONNECT:
			// Client has disconnected so decrement client count;
			gGame.ClientCount--;
			if (gGame.ClientCount<0)
				gGame.ClientCount=0;
			break;
		case GNM_MESH_NAME:
		case GNM_SOUND_NAME:
		{
			// Sending mesh name and matching mesh ID so client and server can
			// syncronize.
			NameStruct *S=(NameStruct *)Buffer;
			int Len=1+(Size-sizeof(NameStruct))/sizeof(WORD);
			TCHAR *Name=(TCHAR *)DCMalloc((Len+1)*sizeof(TCHAR));
			if (Name)
			{
				for (int i=0;i<=Len;i++)
					Name[i]=(TCHAR)MakeWord(S->wObjectName + i*2);
				Name[Len]=0;

				if (S->MessageID==GNM_MESH_NAME)
					SetMeshID(GetMeshHandleFromName(Name),S->ObjectID);
				else
					SetSoundID(GetSoundHandleFromName(Name),S->ObjectID);
				
				DCFree(Name);
			}
			break;
		}
		case GNM_DESTROY_ALL:
		{
			// Make sure client gets updated.
			if (gGame.ClientCount)
				gGame.SendSimpleMessage(GNM_DESTROY_ALL);

			// Destroy all the entities.
			for (EntityBase *Entity=gGame.EntityGlobalList,*Next;Entity;Entity=Next)
			{
				// Get next entity before this one is lost.
				Next=Entity->NextGlobal;
				// Destroy the entity.
				gGame.DestroyEntity(Entity);
			}
			break;
		}
		case GNM_PAUSE_TIME:
			gGame.SetPauseTime(OFF);
			break;
		case GNM_UNPAUSE_TIME:
			gGame.SetPauseTime(ON);
			break;
		case GNM_ENTITY_SPAWN:
		{
			SpawnStruct *S=(SpawnStruct *)Buffer;
			int NetworkID=MakeNetworkID(S->EntityID);
			DCVector Loc,Rot;
			UnpackPos(Loc.X, Rot.X, MakeDword(&S->dwPos[0][0]));
			UnpackPos(Loc.Y, Rot.Y, MakeDword(&S->dwPos[1][0]));
			UnpackPos(Loc.Z, Rot.Z, MakeDword(&S->dwPos[2][0]));

			gGame.SpawnEntity((int)S->ClassID,(EntityCollisionType)S->CollisionType,
							  GetMeshHandleFromID((int)S->MeshID),
							  &Loc,&Rot,
							  MakeInt(S->iUser1),MakeInt(S->iUser2),
							  NetworkID);
			break;
		}
		case GNM_ENTITY_DESTROY:
		{
			DestroyStruct *S=(DestroyStruct *)Buffer;
			int NetworkID=MakeNetworkID(S->EntityID);
			EntityBase *Entity=gGame.GetEntityFromNetworkID(NetworkID);
			if (Entity)
				gGame.DestroyEntity(Entity);
			break;
		}
		case GNM_ENTITY_POSITION:
		{
			PositionStruct *S=(PositionStruct *)Buffer;
			int NetworkID=MakeNetworkID(S->EntityID);
			DCVector Loc,Rot;
			UnpackPos(Loc.X, Rot.X, MakeDword(&S->dwPos[0][0]));
			UnpackPos(Loc.Y, Rot.Y, MakeDword(&S->dwPos[1][0]));
			UnpackPos(Loc.Z, Rot.Z, MakeDword(&S->dwPos[2][0]));
			EntityBase *Entity=gGame.GetEntityFromNetworkID(NetworkID);
			if (Entity)
				gGame.SetEntityPosition(Entity,&Loc,&Rot);
			break;
		}
		case GNM_ENTITY_KILLED:
		{
			PositionStruct *S=(PositionStruct *)Buffer;
			int NetworkID=MakeNetworkID(S->EntityID);
			EntityBase *Entity=gGame.GetEntityFromNetworkID(NetworkID);
			if (Entity)
				gGame.NotifyEntityKilled(Entity);
			break;
		}
		case GNM_PLAY_SOUND:
		{
			SoundStruct *S=(SoundStruct *)Buffer;

			DCVector Loc;
			UnpackLoc(Loc.X,MakeWord(&S->wLoc[0][0]));
			UnpackLoc(Loc.Y,MakeWord(&S->wLoc[1][0]));
			UnpackLoc(Loc.Z,MakeWord(&S->wLoc[2][0]));
			float Volume=(float)S->Volume * (1.0f/255.0f);
			gGame.PlaySound(GetSoundHandleFromID(S->SoundID),&Loc,TRUE,Volume);
			break;
		}
		case GNM_PLAY_SOUND_NO_ATTENUATE:
		{
			SoundNoAttenuateStruct *S=(SoundNoAttenuateStruct *)Buffer;

			float Volume=(float)S->Volume * (1.0f/255.0f);
			gGame.PlaySoundNoAttenuate(GetSoundHandleFromID(S->SoundID),TRUE,Volume);
			break;
		}
		case GNM_MULTIMESSAGE:
		{	
			// Multimessage is multiple messages in a single packet for
			// better efficiency.
			for (int Index=1;Index<Size;Index+=((BYTE *)Buffer)[Index]+1)
			{
				GameNetworkCallback(((BYTE *)Buffer) + Index+1, ((BYTE *)Buffer)[Index]);
			}
			break;
		}
		default:
			break;
	}
}

// Returns a network ID for an entity. Note that the value is only 24 bit
// and hence could wrap and cause problems.
int GameClass::GetNetworkID()
{
	if (State.GameRunning==NETWORK_CLIENT)
		return 0;

	LastNetworkID=(LastNetworkID + 1) & 0x00FFFFFF;
	return LastNetworkID;
}

static void MeshCallback(TCHAR *Name, HANDLE Mesh)
{
	int Len=lstrlen(Name);
	int Size=sizeof(NameStruct)+(Len-1)*sizeof(WORD);
	NameStruct *S;

	S=(NameStruct *)DCMalloc(Size);
	if (!S)
		return;
	
	S->MessageID=GNM_MESH_NAME;
	S->ObjectID=GetMeshID(Mesh);

	for (int i=0;i<Len;i++)
		PackWord(S->wObjectName + i*2,Name[i]);

	SEND_NETWORK_MESSAGE(S,Size);

	DCFree(S);
}
	
static void SoundCallback(TCHAR *Name, int SoundID)
{
	int Len=lstrlen(Name);
	int Size=sizeof(NameStruct)+(Len-1)*sizeof(WORD);
	NameStruct *S;

	S=(NameStruct *)DCMalloc(Size);
	if (!S)
		return;
	
	S->MessageID=GNM_SOUND_NAME;
	S->ObjectID=SoundID;

	for (int i=0;i<Len;i++)
		PackWord(S->wObjectName + i*2,Name[i]);

	SEND_NETWORK_MESSAGE(S,Size);

	DCFree(S);
}
	
// Sends the current game state to the client.
void GameClass::SendGameState()
{
	// Send mesh name to ID mappings.
	GetAllMeshes(MeshCallback);

	// Send sound name to ID mappings.
	GetAllSoundIDs(SoundCallback);

	// Send current entity list.
	for (EntityBase *Entity=EntityGlobalList;Entity;Entity=Entity->NextGlobal)
	{
		SendEntitySpawn(Entity->NetworkID, Entity->ClassID, 
						Entity->CollisionType, GetMeshID(Entity->Mesh),
						&Entity->Loc, &Entity->Rot,
						Entity->User1, Entity->User2);
	}

	// Send current pause state.
	SendSimpleMessage(State.TimeIsPaused ? GNM_PAUSE_TIME : GNM_UNPAUSE_TIME);
}

// Sends a single byte message.
void GameClass::SendSimpleMessage(GameNetworkMessage Message)
{
	SEND_NETWORK_MESSAGE(&Message,1);
}

// Sends a spawn message.
void GameClass::SendEntitySpawn(int NetworkID, int ClassID, EntityCollisionType CollisionType, int MeshID, 
								DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2)
{
	SpawnStruct S;

	S.MessageID=GNM_ENTITY_SPAWN;
	S.EntityID[0]=((BYTE *)&NetworkID)[0];
	S.EntityID[1]=((BYTE *)&NetworkID)[1];
	S.EntityID[2]=((BYTE *)&NetworkID)[2];

	S.ClassID=(BYTE)ClassID;
	S.CollisionType=(BYTE)CollisionType;
	S.MeshID=(BYTE)MeshID;
	
	PackDword(&S.dwPos[0][0],PackPos(InLoc->X,InRot->X));
	PackDword(&S.dwPos[1][0],PackPos(InLoc->Y,InRot->Y));
	PackDword(&S.dwPos[2][0],PackPos(InLoc->Z,InRot->Z));

	PackInt(S.iUser1,InUser1);
	PackInt(S.iUser2,InUser2);

	SEND_NETWORK_MESSAGE(&S,sizeof(S));
}
	
void GameClass::SendEntityDestroy(int NetworkID)
{
	DestroyStruct S;

	S.MessageID=GNM_ENTITY_DESTROY;
	S.EntityID[0]=((BYTE *)&NetworkID)[0];
	S.EntityID[1]=((BYTE *)&NetworkID)[1];
	S.EntityID[2]=((BYTE *)&NetworkID)[2];

	SEND_NETWORK_MESSAGE(&S,sizeof(S));
}

void GameClass::SendEntityPosition(int NetworkID, DCVector *InLoc, DCVector *InRot)
{
	PositionStruct S;

	S.MessageID=GNM_ENTITY_POSITION;
	S.EntityID[0]=((BYTE *)&NetworkID)[0];
	S.EntityID[1]=((BYTE *)&NetworkID)[1];
	S.EntityID[2]=((BYTE *)&NetworkID)[2];

	PackDword(&S.dwPos[0][0],PackPos(InLoc->X,InRot->X));
	PackDword(&S.dwPos[1][0],PackPos(InLoc->Y,InRot->Y));
	PackDword(&S.dwPos[2][0],PackPos(InLoc->Z,InRot->Z));

	SEND_NETWORK_MESSAGE(&S,sizeof(S));
}

void GameClass::SendEntityKilled(int NetworkID)
{
	KilledStruct S;

	S.MessageID=GNM_ENTITY_KILLED;
	S.EntityID[0]=((BYTE *)&NetworkID)[0];
	S.EntityID[1]=((BYTE *)&NetworkID)[1];
	S.EntityID[2]=((BYTE *)&NetworkID)[2];

	SEND_NETWORK_MESSAGE(&S,sizeof(S));
}

void GameClass::SendPlaySound(int NetworkID, DCVector *InLoc, float Volume)
{
	SoundStruct S;

	S.MessageID=GNM_PLAY_SOUND;
	S.SoundID=(BYTE)NetworkID;
	PackWord(&S.wLoc[0][0],PackLoc(InLoc->X));
	PackWord(&S.wLoc[1][0],PackLoc(InLoc->Y));
	PackWord(&S.wLoc[2][0],PackLoc(InLoc->Z));
	S.Volume=__max(0,__min(255,(int)(Volume*255.0f)));
	
	SEND_NETWORK_MESSAGE(&S,sizeof(S));
}

void GameClass::SendPlaySoundNoAttenuate(int NetworkID, float Volume)
{
	SoundNoAttenuateStruct S;

	S.MessageID=GNM_PLAY_SOUND_NO_ATTENUATE;
	S.SoundID=(BYTE)NetworkID;
	S.Volume=__max(0,__min(255,(int)(Volume*255.0f)));
	
	SEND_NETWORK_MESSAGE(&S,sizeof(S));
}

void GameClass::SendStartFrame(float DeltaTime)
{
	StartFrameStruct S;

	S.MessageID=GNM_START_FRAME;
	PackFloat(S.fDeltaTime,DeltaTime);

	SEND_NETWORK_MESSAGE(&S,sizeof(S));
}

EntityBase *GameClass::GetEntityFromNetworkID(int NetworkID)
{
	for (EntityBase *Entity=EntityGlobalList;Entity;Entity=Entity->NextGlobal)
		if (Entity->NetworkID==NetworkID)
			return Entity;
	return NULL;
}

// Buffers network messages so as to reduce per-message overhead.
void GameClass::BufferMessage(void *Buffer, int Size)
{
	// Make sure shorter than 256 (we only use a byte to store the length).
	if (Size >= 256)
	{
		SendNetBuffer();
		SendNetworkPacket(Buffer,Size);
		return;
	}
	
	// Make sure we have valid net buffer.
	if (NetBufferIndex+Size+1 > NET_BUFFER_SIZE)
	{
		SendNetBuffer();
		
		if (NetBufferIndex+Size+1 > NET_BUFFER_SIZE)
		{
			// If message is still too big, don't buffer it.
			SendNetworkPacket(Buffer,Size);
			return;
		}
	}

	// Set message length.
	NetBuffer[NetBufferIndex++]=Size;

	// Copy message.
	DCCopyMemory(NetBuffer+NetBufferIndex,Buffer,Size);
	NetBufferIndex+=Size;
}

// Sends network buffer if there is anything in it.
void GameClass::SendNetBuffer()
{
	if (NetBufferIndex>1)
	{
		SendNetworkPacket(NetBuffer,NetBufferIndex);
	}
	NetBufferIndex=1;
}

