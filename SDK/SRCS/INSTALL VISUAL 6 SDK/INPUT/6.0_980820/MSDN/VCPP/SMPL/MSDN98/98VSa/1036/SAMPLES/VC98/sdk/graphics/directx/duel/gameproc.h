/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:		gameproc.h
 *  Content:	game processing info. include file
 *
 *
 ***************************************************************************/
#define IDIRECTPLAY2_OR_GREATER
#include <ddraw.h>
#include <dplay.h>
#include <dsound.h>
#include "sfx.h"
#include "duel.h"

// align on single byte boundaries
// this is a stop-gap measure until the structures can be re-arranged.
#pragma pack(1)

#define     MAX_SHIP_X     (MAX_SCREEN_X - 32)
#define     MAX_SHIP_Y     (MAX_SCREEN_Y - 32)
#define     MAX_SHIP_FRAME 40
#define     MAX_BULLET_X    (MAX_SCREEN_X - 3)
#define     MAX_BULLET_Y    (MAX_SCREEN_Y - 3)
#define     MAX_BULLET_FRAME 400

#define		NUM_SHIP_TYPES 4

#define		DEF_SHOW_DELAY     (2000)
#define		MAX_BUFFER_SIZE	   256

#define     UPDATE_INTERVAL     40      // interval between position updates in milliseconds (25 FPS)
#define     SYNC_INTERVAL       1000    // synchronize once every second
#define     HIDE_TIMEOUT        5000    // time for which a ship is disabled after a hit

/*
 * keyboard commands
 */

#define KEY_STOP        0x00000001l
#define KEY_DOWN        0x00000002l
#define KEY_LEFT        0x00000004l
#define KEY_RIGHT       0x00000008l
#define KEY_UP          0x00000010l
#define KEY_FIRE        0x00000020l
#define KEY_ENGINEOFF   0x00000040l

/*
 * Offsets for the bullet bitmap
 */

#define     BULLET_X    304
#define     BULLET_Y    0

typedef struct _frag
{
    double		dPosX;
    double		dPosY;
    LPDIRECTDRAWSURFACE surf;
    RECT        src;
    double      dVelX;
    double      dVelY;
    BOOL        valid;
} FRAG, *LPFRAG;

/*
 * structures
 */

typedef struct _SHIP
{
    double				dPosX, dPosY;				// ship x and y position
    double				dBulletPosX, dBulletPosY;	// bullet x and y position
    DWORD				dwBulletFrame;				// bullet frame
    char 				cFrame;						// current ship frame
	BYTE				byType;						// ship type 
    BOOL                bEnable;					// is this ship active?
    BOOL                bBulletEnable;				// Is there an active bullet?

    double				dVelX, dVelY;				// ship x and y velocity (pixels/millisecond)
    double				dBulletVelX, dBulletVelY;	// bullet x and y velocity (pixels/millisecond)
    DWORD				dwScore;					// current score
    DWORD               dwLastTick;					// most recent time stamp
    BOOL                bIgnore;	                // flag used to synchronize ship explosions
	int					iCountDown;                 // enable time-out            
    DWORD               dwFrameCount;               // number of frames since beginning of time
    /* DSOUND members */
    LPDIRECTSOUNDBUFFER   lpDirectSoundBuffer  [MAX_SOUNDS]; // SoundBuffer interface
    LPDIRECTSOUND3DBUFFER lpDirectSound3DBuffer[MAX_SOUNDS]; // 3D interface (to same buffer)  
    DWORD                 dwKeys;                            // the keyboard state
    BOOL                  bEngineRunning;                    // These BOOLs keep track of the ship's
    BOOL                  bMoving;                           //   last condition so we can play sounds
    BOOL                  bBounced;                          //   when they change
    BOOL                  bBlockHit;
    BOOL                  bDeath;
    BOOL                  bFiring;
    /* DSOUND members */

} SHIP, *LPSHIP;

typedef struct _BLOCKS
{
    BYTE        bits[30][5];
} BLOCKS, *LPBLOCKS;

//----------------------------------------------------------
// communication packet structures
//----------------------------------------------------------
#define MSG_HOST        0x11    // message containing field layout, sent by host
#define MSG_BLOCKHIT    0x22    // block hit message
#define MSG_SHIPHIT     0x33    // ship hit message
#define MSG_ADDBLOCK	0x44    // add block message
#define MSG_CONTROL     0x55    // game keys message
#define MSG_SYNC        0x66    // synchronization message containing the rendezvous location

typedef struct _GENERICMSG
{
    BYTE        byType;
} GENERICMSG, *LPGENERICMSG;

typedef struct _HOSTMSG
{
    BYTE        byType;
    BLOCKS      Blocks;
} HOSTMSG, *LPHOSTMSG;

typedef struct _BLOCKHITMSG
{
    BYTE        byType;
    BYTE        byRow;
    BYTE        byCol;
    BYTE        byMask;
} BLOCKHITMSG, *LPBLOCKHITMSG;

typedef struct _SHIPHITMSG
{
    BYTE        byType;
    DPID        Id;
} SHIPHITMSG, *LPSHIPHITMSG;

typedef struct _ADDBLOCKMSG
{
    BYTE        byType;
    BYTE        byX;
    BYTE        byY;
} ADDBLOCKMSG, *LPADDBLOCKMSG;

typedef struct _CONTROLMSG
{
    BYTE        byType;
    BYTE        byState;
} CONTROLMSG, *LPCONTROLMSG;

typedef struct _SYNCMSG
{
    BYTE        byType;
    BYTE        byShipType;     // this is needed only when sends are unreliable
    char        cFrame;
    double      dPosX;
    double      dPosY;
} SYNCMSG, *LPSYNCMSG;

/*
 * Prototypes
 */
void	LaunchGame(void);
void	ExitGame(void);
HRESULT InitOurShip(void);

HRESULT InitLocalSoundData(void);
void InitPlayerLocalSoundData(LPSHIP lpShip, BOOL bOurShip);
BOOL WINAPI SetPlayerLocalSoundDataCB(DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName, 
				   	                  DWORD dwFlags, LPVOID lpContext);

void ReleaseLocalData(void);
void ReleasePlayerLocalSoundData(LPSHIP lpShip);
BOOL WINAPI ReleasePlayerLocalDataCB(DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName,
					                 DWORD dwFlags, LPVOID lpContext);

void    UpdateState(LPSHIP lpShip, DWORD dwControls);
void    SendSync(LPSHIP lpShip);
void    UpdateDisplayStatus(LPSHIP lpShip);
void    UpdatePosition( DPID dpId, LPSHIP ship );
BOOL    IsHit( int x, int y );
void    InitField(void);
BOOL    setBlock( int x, int y );
void    AddFrag(LPSHIP lpShip, int offX, int offY);
void    UpdateFragment(int i);
void    DestroyShip( LPSHIP lpShip);
void	DestroyGame( void );
BOOL	UpdateFrame( void );

void    ProcessSoundFlags(LPSHIP lpShip);
BOOL WINAPI RenderPlayerCB(DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName, 
	                     DWORD dwFlags, LPVOID lpContext);
BOOL	DrawScreen( void );
BOOL    DrawScore( void );
void    DrawShip( LPSHIP lpShip );
void    DrawBlock( int x, int y );
void    DrawBullet( LPSHIP lpShip );
void    DrawFragments( void );
void    DisplayFrameRate( void );

void	GetConnection(void);
HRESULT ReceiveMessages( void );
void	DoSystemMessage( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID idFrom, DPID idTo );
void    DoApplicationMessage( LPGENERICMSG lpMsg, DWORD dwMsgSize, DPID idFrom, DPID idTo );
void    SendGameMessage( LPGENERICMSG lpMsg, DPID idTo );
void	CleanupComm(void);


// restore default alignment
#pragma pack()
