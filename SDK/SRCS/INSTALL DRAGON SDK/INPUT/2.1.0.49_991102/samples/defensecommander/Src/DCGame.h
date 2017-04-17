/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    DCGame.h

Abstract:

	Main game management and related classes.

-------------------------------------------------------------------*/


enum GameNetworkMessage
{
	GNM_MULTIMESSAGE=0,
	GNM_CLIENT_CONNECT,
	GNM_CLIENT_DISCONNECT,
	GNM_MESH_NAME,
	GNM_SOUND_NAME,
	GNM_DESTROY_ALL,

	GNM_START_FRAME,
	
	GNM_PAUSE_TIME,
	GNM_UNPAUSE_TIME,
	
	GNM_ENTITY_SPAWN,
	GNM_ENTITY_DESTROY,
	GNM_ENTITY_POSITION,
	GNM_ENTITY_KILLED,

	GNM_PLAY_SOUND,
	GNM_PLAY_SOUND_NO_ATTENUATE
};

enum GameInputControl
{
	INPUT_STARTBUTTON=0,
	INPUT_STARTGAME,
	INPUT_ENDGAME,

	INPUT_FIRE1,
	INPUT_FIRE2,
	INPUT_FIRE3,
	
	INPUT_HELP,
	INPUT_PAUSETIME,
	INPUT_OBSERVERTOGGLE,
	INPUT_GODMODETOGGLE,

	INPUT_FORWARD,
	INPUT_BACKWARD,
	INPUT_LEFTSTRAFE,
	INPUT_RIGHTSTRAFE,

	INPUT_MOUSEX,
	INPUT_MOUSEY,
	INPUT_JOYX,
	INPUT_JOYY,

	INPUT_START_DEMO_RECORD,
	INPUT_END_DEMO_RECORD,

	INPUT_TIMEDEMO
};

enum GameTypeRunning
{
	NONE=0,
	GAME,
	DEMO,
	NETWORK_CLIENT
};

enum GameToggleControl
{
	OFF=0,
	ON=1,
	TOGGLE=2
};

// Should be in the range 0-255 since only byte is sent across network.
enum EntityCollisionType
{
	COLLISION_NONE=0,
	COLLISION_BADDIE,
	COLLISION_GOODIE,
	COLLISION_BADDIE_FIRE,
	COLLISION_GOODIE_FIRE
};

class EntityBase;

class ReferenceClass
{
public:	
	EntityBase **Ref;
	ReferenceClass *Next;
};

// Holds info about the entity the entity is colliding with.
struct CollisionInfo
{
	int ClassID;
	EntityCollisionType CollisionType;
	HANDLE Mesh;
	DCVector *Loc,*Rot;
	float Damage;
	BOOL Terrain;
};

// Entities also have a per-instance portion.
class EntityBase
{
public:
	// Stuff for entity maganement.
	int ClassID;  // ID of entity class.
	int NetworkID; // Used when networking to match up entities on each side.
	// We keep linked list pointers in here. Its a bit ugly but means we
	// don't have to allocate any extra memory.
	EntityBase *PreviousGlobal;
	EntityBase *NextGlobal;
	EntityBase *PreviousCollision;
	EntityBase *NextCollision;
	EntityCollisionType CollisionType;

	// Mesh for the entity (can be null).
	HANDLE	Mesh;
	
	// Location/rotation.
	DCVector Loc, Rot;

	// Keep User1 and User2 so its possible to transmit it to the client.
	int User1, User2;

	// List of references, normally NULL.
	ReferenceClass *RefList;

	virtual void Init(HANDLE InMesh, DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	virtual void Shutdown();
	virtual void AddRef(EntityBase **Ref);
	virtual void RemoveRef(EntityBase **Ref);

	virtual void SetPosition(DCVector *InLoc,DCVector *InRot);
	virtual void GetPosition(DCVector *OutLoc,DCVector *OutRot);
	virtual void GetVelocity(DCVector *OutVel);
	virtual HANDLE GetMesh(BOOL ForRender);
	virtual void ServerTick(float FrameDeltaTime);
	virtual void ClientTick(float FrameDeltaTime);
	virtual BOOL Touch(CollisionInfo *Info);
	virtual void Killed(void); // Entity should make death explosion on this call.
	virtual float GetDamage();
	virtual void *Message(void *Message);
};

class GameClass
{
	BOOL Initialized;
	
	// For dealing with the different states the game can be in.
	struct StateStruct
	{
		GameTypeRunning GameRunning;
		BOOL TimeIsPaused;
		BOOL GodMode;
		BOOL DisplayHelp;
	} State;
	void StartPressed(void);
	void EndPressed(void);
	void StartGame(void);
	void EndGame(void);
	void StartTimeDemo();
	void SetPauseTime(GameToggleControl Control);
	void SetGodMode(GameToggleControl Control);
	void SetDisplayHelp(GameToggleControl Control);

	// For creating/destroying a new game.
	void CreateGame(GameTypeRunning GameType);
	void DestroyGame();

	// Entity lists.
	EntityBase *EntityGlobalList;
	// For collision.
	EntityBase *EntityBaddieList;
	EntityBase *EntityGoodieList;
	EntityBase *EntityBaddieFireList;
	EntityBase *EntityGoodieFireList;

	// Need to access these entities for a number of things.
	EntityBase *PlayerEntity;
	EntityBase *LordEntity;

	// For dealing with the player's view.
	struct ViewStruct
	{
		BOOL		Observer;
		DCVector	Loc,Rot;
	}View;
	void SetObserverMode(GameToggleControl Control);
	void TickPlayerView(void);

	// Data for dealing with controls.
	struct ControlsStruct
	{
		int MouseMoveX;
		int MouseMoveY;
		int JoyX;
		int JoyY;
		BOOL Fire1Down;
		BOOL Fire2Down;
		BOOL Fire3Down;
		BOOL StrafeLeftDown;
		BOOL StrafeRightDown;
		BOOL ForwardDown;
		BOOL BackwardDown;
	}Controls;

	// Time.
	TIMEVALUE ThisFrameAbsTime,LastFrameAbsTime;
	float FrameDeltaTime;
	TIMEVALUE ThisFrameAppAbsTime,LastFrameAppAbsTime;
	float AppFrameDeltaTime;

	// Utility functions.
	BOOL GetNewToggleState(BOOL CurrentState, GameToggleControl Control);

	// Networking.
	int ClientCount;
	int LastNetworkID;
	int GetNetworkID();
	EntityBase *GetEntityFromNetworkID(int NetworkID);
	void SendGameState();
	void SendSimpleMessage(GameNetworkMessage Message);
	void SendEntitySpawn(int NetworkID, int ClassID, EntityCollisionType CollisionType, int MeshID, 
						 DCVector *InLoc, DCVector *InRot, int InUser1, int InUser2);
	void SendEntityDestroy(int NetworkID);
	void SendEntityPosition(int NetworkID, DCVector *InLoc, DCVector *InRot);
	void SendEntityKilled(int NetworkID);
	void SendPlaySound(int NetworkID, DCVector *InLoc, float Volume);
	void SendPlaySoundNoAttenuate(int NetworkID, float Volume);
	void SendStartFrame(float DeltaTime);

#define NET_BUFFER_SIZE 512
	BYTE NetBuffer[NET_BUFFER_SIZE];
	int NetBufferIndex;
	void BufferMessage(void *Buffer,int Size);
	void SendNetBuffer();
		
	friend void GameNetworkCallback(void *Buffer, int Size);
	friend void MeshCallback(TCHAR *Name, HANDLE Mesh);
	friend void SoundCallback(TCHAR *Name, int SoundID);

	// Passing data back and forward.
	float FlashIntensity;

	// Demo playback.
	struct 
	{
		BYTE *Data;
		int DataSize;
		int CurrentPosition;
		float CurrentTime;
		
		BOOL TimeDemo;
		TIMEVALUE StartTime, EndTime;
		int Frames;
		float Fps;
	} Demo;
	void InitDemoPlayback();
	void ShutdownDemoPlayback();
	void StartDemoPlayback();
	void TickDemoPlayback(float DeltaTime);

public:
	// Constructor function.
	GameClass(void) { Initialized=FALSE; }

	// Initialization/shutdown.
	BOOL Initialize(void);
	void Shutdown(void);

	// Frame tick.
	void TickFrame(void);

	// Input.
	void InputEvent(GameInputControl Control, int Event);

	// View.
	void SetViewerCoords(DCVector *Loc, DCVector *Rot);
	void ForceObserverMode();

	// Passing data.
	void SetFlashIntensity(float Intensity) { FlashIntensity=Intensity; }
	float GetFlashIntensity() { return FlashIntensity; }

	// Querying.
	BOOL IsObserverMode(void) { return View.Observer; }
	BOOL IsDisplayHelp(void) { return State.DisplayHelp; }
	BOOL IsTimePaused() { return State.TimeIsPaused; }
	BOOL IsGodMode() { return State.GodMode; }
	BOOL IsClient() { return (State.GameRunning==DEMO || State.GameRunning==NETWORK_CLIENT); }
	BOOL IsDemoPlayback() { return (State.GameRunning==DEMO); }
	BOOL IsTimeDemo() { return (State.GameRunning==DEMO && Demo.TimeDemo); }
	float GetTimeDemoFps() { return (IsTimeDemo() ? Demo.Fps : 0); }
	float GetFrameDeltaTime(void) { return FrameDeltaTime; }
	TIMEVALUE GetThisFrameAbsTime(void) { return ThisFrameAbsTime; }
	float GetAppFrameDeltaTime(void) { return AppFrameDeltaTime; }
	TIMEVALUE GetThisFrameAppAbsTime(void) { return ThisFrameAppAbsTime; }
	void GetViewerCoords(DCVector *Loc, DCVector *Rot);
	BOOL GetFire1Status() { return Controls.Fire1Down; }
	BOOL GetFire2Status() { return Controls.Fire2Down; };
	BOOL GetFire3Status() { return Controls.Fire3Down; };

	// Entity related. Some of these funcitons will transmit network data.
	int  GetEntityIDFromName(TCHAR *Name);
	EntityBase *SpawnEntity(int ClassID, EntityCollisionType CollisionType,
							HANDLE Mesh, DCVector *InLoc, DCVector *InRot, 
							int InUser1, int InUser2,
							int NetworkID=-1);
	void SetEntityPosition(EntityBase *Entity, DCVector *InLoc,DCVector *InRot);
	void NotifyEntityKilled(EntityBase *Entity);
	void DestroyEntity(EntityBase *Entity);
	void *SendEntityMessage(EntityBase *Entity, void *Message);
	void GetAllEntityMeshes(void (*Callback)(HANDLE Mesh, DCVector *Loc, DCVector *Rot, void *User),
							void*User, BOOL ForRender);
	void GetCollisionEntityMeshes(EntityCollisionType Type,
								  void (*Callback)(HANDLE Mesh, DCVector *Loc, DCVector *Rot, void *User),
								  void *User, BOOL ForRender);
	void GetAllEntities    (void (*Callback)(EntityBase *Entity, void *User), void*User);
	void GetCollisionEntities    (EntityCollisionType Type,
								  void (*Callback)(EntityBase *Entity, void *User),
								  void *User);
	BOOL MakeCollision(EntityBase *Dst, EntityBase *Src);
	EntityBase *GetPlayerEntity() { return PlayerEntity; }
	void SetPlayerEntity(EntityBase *Entity) { PlayerEntity=Entity;	PlayerEntity->AddRef(&PlayerEntity); }
	EntityBase *GetLordEntity() { return LordEntity; }
	void SetLordEntity(EntityBase *Entity) { LordEntity=Entity; LordEntity->AddRef(&LordEntity); }

	// Sound related.
	void PlaySound(HANDLE Sound, DCVector *Loc, BOOL SendToClients=FALSE, float Volume=1.0f);
	void PlaySoundNoAttenuate(HANDLE Sound, BOOL SendToClients=FALSE, float Volume=1.0f);

	// Demo recording.
	HANDLE DemoFile;
	void StartDemoRecord();
	void EndDemoRecord();
	void RecordMessage(void *Data, int Size);
	BOOL IsRecordingDemo() { return DemoFile!=NULL; }
};

extern GameClass gGame;
