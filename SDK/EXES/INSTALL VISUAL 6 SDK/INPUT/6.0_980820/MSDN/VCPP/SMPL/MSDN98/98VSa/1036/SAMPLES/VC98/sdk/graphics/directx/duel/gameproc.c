/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       gameproc.c
 *  Content:    Game processing code
 *
 *
 ***************************************************************************/
#include "gameproc.h"
#include "util.h"
#include "gfx.h"
#include "comm.h"
#include "input.h"
#include "lobby.h"
#include "wizard.h"
#include "dsound.h"
#include "sfx.h"
#include "stdio.h"

/*
 * Externals
 */
extern DWORD					gdwKeys;
extern LPDIRECTDRAWSURFACE		glpShip0;
extern LPDIRECTDRAWSURFACE		glpShip1;
extern LPDIRECTDRAWSURFACE		glpShip2;
extern LPDIRECTDRAWSURFACE		glpShip3;
extern BOOL						gbShowFrameCount;
extern LPDIRECTDRAWSURFACE		glpNum;
extern BOOL						gbIsHost;
extern BOOL						gbIsActive;
extern LPDPSESSIONDESC2			glpdpSD;
extern HWND						ghWndMain;
extern HINSTANCE				ghinst;
extern BOOL                     gbReliable;

/*
 * Globals
 */
FRAG							gFrags[64];					// ship framents
BLOCKS							gBlocks;					// field layout
LPVOID				            glpvReceiveBuffer = NULL;	// buffer to store received messages
DWORD           				gdwReceiveBufferSize = 0;	// size of buffer
DPID							gOurID;						// our player id
BOOL							gbHaveHostInit;				// do we need to do host initializaton
int								gnProgramState;				// current state of the game
DWORD							gdwFrameCount;				// used for fps calc
DWORD							gdwFramesLast;				// ..
DWORD							gdwFrameTime;				// ..
BOOL                            gbUpdate;                   // TRUE if player data needs to be updated
BOOL                            gbNoField;                  // display blocks ?
BOOL                            gbSessionLost;              // did we get disconnected ?
HOSTMSG                         gHostMsg;                   // message buffer
BLOCKHITMSG                     gBlockHitMsg;               // ..
SHIPHITMSG                      gShipHitMsg;                // ..
ADDBLOCKMSG                     gAddBlockMsg;               // ..
CONTROLMSG                      gControlMsg;                // .. 
SYNCMSG                         gSyncMsg;                   // ..
TCHAR                           gDebugBuff[MAX_ERRORMSG];   // buffer for debug output

/*
 * Statics
 */

static double      gDirx[40] =							
{
    0.000000,
    0.156434,
    0.309017,
    0.453991,
    0.587785,
    0.707107,
    0.809017,
    0.891007,
    0.951057,
    0.987688,
    1.000000,
    0.987688,
    0.951057,
    0.891007,
    0.809017,
    0.707107,
    0.587785,
    0.453990,
    0.309017,
    0.156434,
    0.000000,
    -0.156435,
    -0.309017,
    -0.453991,
    -0.587785,
    -0.707107,
    -0.809017,
    -0.891007,
    -0.951057,
    -0.987688,
    -1.000000,
    -0.987688,
    -0.951056,
    -0.891006,
    -0.809017,
    -0.707107,
    -0.587785,
    -0.453990,
    -0.309017,
    -0.156434
};

static double      gDiry[40] =
{
    -1.000000,
    -0.987688,
    -0.951057,
    -0.891007,
    -0.809017,
    -0.707107,
    -0.587785,
    -0.453990,
    -0.309017,
    -0.156434,
    0.000000,
    0.156434,
    0.309017,
    0.453991,
    0.587785,
    0.707107,
    0.809017,
    0.891007,
    0.951057,
    0.987688,
    1.000000,
    0.987688,
    0.951057,
    0.891006,
    0.809017,
    0.707107,
    0.587785,
    0.453990,
    0.309017,
    0.156434,
    0.000000,
    -0.156435,
    -0.309017,
    -0.453991,
    -0.587785,
    -0.707107,
    -0.809017,
    -0.891007,
    -0.951057,
    -0.987688
};

/*
 * InitMessageBuffers
 *
 * Sets up buffes used for sending different types of messages
 */
void InitMessageBuffers(void)
{
    gHostMsg.byType        = MSG_HOST;
    gBlockHitMsg.byType    = MSG_BLOCKHIT;
    gShipHitMsg.byType     = MSG_SHIPHIT;    
    gAddBlockMsg.byType    = MSG_ADDBLOCK;
    gControlMsg.byType     = MSG_CONTROL; 
    gSyncMsg.byType        = MSG_SYNC;
}

/*
 * LaunchGame
 *
 * Sets up the game layout and launches
 */
void LaunchGame(void)
{
	HRESULT hr;

	// initialize global message buffers
    InitMessageBuffers();

	// update window title
	UpdateTitle();

	// get current session description (glpdpSD is initialized in here)
    hr = DPlayGetSessionDesc();
    if (FAILED(hr) || (!glpdpSD))
	{
        ShowError(IDS_DPLAY_ERROR_GSD);
        goto ABORT;
	}

	// initialize random number seed
	srand((int)GetTickCount());

	// clear front buffer before changing palette
	EraseScreen();
	FlipScreen();

        // Begin collecting input
        ReacquireInputDevices();

    // initialize us
  	hr = InitOurShip();
    if (FAILED(hr))
    {
        goto ABORT;
    }

    // get the field layout
	if( gbIsHost )
	{
        // initialize field (done only by host)
        if (!gbNoField)
            InitField();

        // we have host initialization
		gbHaveHostInit = TRUE;

        // start updating screen
        gbIsActive = TRUE;
	}
	else
	{
        // get it from host, if we are joining
		gbHaveHostInit = FALSE;
	}

    // success
    return;

ABORT:
    // something went wrong, terminate game
    ExitGame();
}

/*
 * ExitGame
 *
 * Game termination code
 */
void ExitGame(void)
{
    // shut down app
	PostMessage( ghWndMain, WM_CLOSE, 0, 0 );
}

/*
 * InitOurShip
 *
 * Initializes our ship's initial attributes
 */
HRESULT InitOurShip(void)
{
    int i;
    SHIP ship;
    HRESULT hr;

	// wipe out everything
	ZeroMemory(&ship, sizeof(ship));

	// initialize sound buffers, tell function that it's OUR ship
    // so that it can use the global sound buffers instead of duplicating
    // from them and wasting resources.
	InitPlayerLocalSoundData(&ship, TRUE);

	// calculate ship type based on the number of players in the game
    // we cycle through four ships (Y,R,G,B) for now.

	ship.byType = (BYTE) ((glpdpSD->dwCurrentPlayers-1) % NUM_SHIP_TYPES);
    ship.dPosX  = randInt(0,MAX_SHIP_X);
    ship.dPosY  = randInt(0,MAX_SHIP_Y);
    ship.cFrame = randInt(0, MAX_SHIP_FRAME);
	ship.bEnable = TRUE;

    // set our local data
	hr = DPlaySetPlayerData(gOurID, &ship, sizeof(ship), DPSET_LOCAL);
    if (FAILED(hr))
    {
        ShowError(IDS_DPLAY_ERROR_SPLD);
        goto FAIL;
    }

    // no ship fragments
    for(i=0; i<64; i++)
        gFrags[i].valid = FALSE;

    // success
    return DP_OK;

FAIL:
    // failed
    return hr;
}

/*
 *FUNCTION:   InitPlayerLocalSoundData
 *
 *
 *NOTES:      Takes a ship and initializes ONLY its soundbuffers and sound flags.
 *            It leaves everything else alone.  Good for when going to
 *            full-screen mode, when we need to get rid of the sound buffers
 *            for a bit, but don't want to change the data.
 */
void InitPlayerLocalSoundData(LPSHIP lpShip, BOOL bOurShip)
{
int i;
    if (gbSoundInitialized)
    {
        for (i=0; i<MAX_SOUNDS; i++)
        {
            if (FALSE == WaveGetBuffers(gSoundEffect[i],&lpShip->lpDirectSoundBuffer[i], &lpShip->lpDirectSound3DBuffer[i], bOurShip))
            {//if it didn't work, get rid of all the other sound buffers
             //the current ones have already been set NULL by the failed function.
                ShowError(IDS_DSOUND_DUPBUF);
                for (--i; i>=0; i--)
                {
                    // if it's our ship then we don't want to release the regular
                    // (non-3D) buffer because it's just a copy of a pointer to
                    // the corresponding GLOBAL sound buffer.
                    IDirectSoundBuffer_Release(lpShip->lpDirectSound3DBuffer[i]);
                    if (!bOurShip)
                    {
                        IDirectSoundBuffer_Release(lpShip->lpDirectSoundBuffer  [i]);
                    }
                    lpShip->lpDirectSoundBuffer  [i] = NULL;
                    lpShip->lpDirectSound3DBuffer[i] = NULL;
                }
                return;
            }
        }

        lpShip->bFiring        = FALSE;
        lpShip->bBounced       = FALSE;
        lpShip->bDeath         = FALSE;
        lpShip->bBlockHit      = FALSE;
        lpShip->bEngineRunning = FALSE;
        lpShip->bMoving        = FALSE;
    }
    else
    {
    //if sound initialization has already failed in InitSfx(), then we want the ships'
    //sound buffers to be NULL so that we don't try to release them later.
        for (i=0; i<MAX_SOUNDS; i++)
        {
            lpShip->lpDirectSoundBuffer  [i] = NULL;
            lpShip->lpDirectSound3DBuffer[i] = NULL;
        }
    }
};

/*
 *FUNCTION:   SetPlayerLocalSoundDataCB (CALLBACK)
 *
 *PURPOSE:    Initializes and registers a player's local SOUND data ONLY.
 */
BOOL WINAPI SetPlayerLocalSoundDataCB(DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName, 
				   	                  DWORD dwFlags, LPVOID lpContext)
{
	SHIP ship;
    DWORD dwSize = sizeof(ship);
    HRESULT hr;
    BOOL bOurShip;

    DPlayGetPlayerData(dpId, &ship, &dwSize, DPGET_LOCAL); 

	// no player data yet
	if (0 == dwSize)
		return TRUE;

    //we need to know if it's our ship because we use the global sound buffers
    //while all the other ships have to DUPLICATE their sound buffers from
    //those global buffers.   
    bOurShip = (dpId == gOurID);
    InitPlayerLocalSoundData(&ship, bOurShip);

	hr = DPlaySetPlayerData(dpId, &ship, dwSize, DPSET_LOCAL);
    return (DP_OK == hr);
};

/*
 *FUNCTION:   InitLocalSoundData
 *
 *PURPOSE:    Initializes and registers all players' sound data ONLY
 */
HRESULT InitLocalSoundData(void)
{
    HRESULT hr;
	hr = DPlayEnumPlayers(&(glpdpSD->guidInstance), SetPlayerLocalSoundDataCB, NULL, 0);
    return hr;
}

/*
 *FUNCTION:   ReleaseLocalSoundData
 *
 *NOTES:      Releases a single ship's local sound buffers.
 */
void ReleasePlayerLocalSoundData(LPSHIP lpShip)
{
int i;

    if (gbSoundInitialized)
    {
        for (i=0; i<MAX_SOUNDS; i++)
        {
            if (lpShip->lpDirectSoundBuffer[i] != NULL)
            {
                IDirectSoundBuffer_Stop     (lpShip->lpDirectSoundBuffer[i]);
                //only release if it's not just a pointer copy from the global.
                if (lpShip->lpDirectSoundBuffer[i] != gSoundEffect[i]->lpDirectSoundBuffer)
                {
                    //This ship's buffer is not identical to its global, we can release it.
                    IDirectSoundBuffer_Release  (lpShip->lpDirectSoundBuffer[i]);
                }
                lpShip->lpDirectSoundBuffer[i] = NULL;
            }

            if (lpShip->lpDirectSound3DBuffer[i] != NULL)
            {
                IDirectSound3DBuffer_Release(lpShip->lpDirectSound3DBuffer[i]);	
                lpShip->lpDirectSound3DBuffer[i] = NULL;
            }
        }
    }
};

/*
 *FUNCTION:   ReleasePlayerLocalData  (CALLBACK)
 *
 *PURPOSE:    Retrieves and releases a player's local data from dplay.
 */
BOOL WINAPI ReleasePlayerLocalDataCB(DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName,
					                 DWORD dwFlags, LPVOID lpContext)
{
	SHIP ship;
    DWORD dwSize = sizeof(SHIP);    
    HRESULT hr;
	
    hr = DPlayGetPlayerData(dpId, &ship, &dwSize, DPGET_LOCAL);
    if (FAILED(hr))
    {
        wsprintf(gDebugBuff, TEXT("Get Player local data failed for id %d\n"), dpId);
        DEBUG_OUT(gDebugBuff);
        goto FAIL;
    }

	// no player data yet
	if (0 == dwSize)
		return TRUE;

    ReleasePlayerLocalSoundData(&ship);

    hr = DPlaySetPlayerData(dpId, &ship,  dwSize, DPSET_LOCAL);
    if (FAILED(hr))
    {
        wsprintf(gDebugBuff, TEXT("Set Player local data failed for id %d\n"), dpId);
        DEBUG_OUT(gDebugBuff);
        goto FAIL;
    }

    // success
	return TRUE;
FAIL:
    // we failed
    return FALSE;
}

/*
 *FUNCTION:   ReleaseLocalData
 *
 *PURPOSE:    Releases local data of ALL players.
 */
void ReleaseLocalData(void)
{
     HRESULT hr;

     if (gnProgramState == PS_ACTIVE)
     {
         hr = DPlayEnumPlayers(&(glpdpSD->guidInstance), ReleasePlayerLocalDataCB, NULL, 0);
         if (FAILED(hr))
         {
             ShowError(IDS_DPLAY_ERROR_EP);
         }
     }
};

/*
 * ProcessUserInput
 *
 * Processes any input from the user and updates our ship state
 */
void ProcessUserInput(LPSHIP lpShip)
{
    static dwOldKeys = 0;

    gbUpdate = FALSE;

    // DSOUND: check if the engine was turned off
    if (!(gdwKeys    & (KEY_DOWN | KEY_UP)) && 
		(dwOldKeys & (KEY_DOWN | KEY_UP)))
    {
        gdwKeys |= KEY_ENGINEOFF;

        gControlMsg.byState = (BYTE) gdwKeys;
        // let everyone know that we just turned our engine off
        SendGameMessage((LPGENERICMSG) &gControlMsg, DPID_ALLPLAYERS);
    }

    // update our ship state
    UpdateState(lpShip, gdwKeys);

    // remember current keys for next frame
    dwOldKeys = gdwKeys;
}

/*
 * UpdateState
 *
 * Updates the current state of our ship, given user input
 */
void UpdateState(LPSHIP lpShip, DWORD dwControls)
{
    lpShip->dwKeys = dwControls;

    if( dwControls & KEY_LEFT )
    {
        gbUpdate = TRUE;
        lpShip->cFrame -= 1;
		if( lpShip->cFrame < 0 )
			lpShip->cFrame += MAX_SHIP_FRAME;
    }
    if( dwControls & KEY_RIGHT )
    {
        gbUpdate = TRUE;
        lpShip->cFrame += 1;
		if( lpShip->cFrame >= MAX_SHIP_FRAME )
			lpShip->cFrame -= MAX_SHIP_FRAME;
    }
    if( dwControls & KEY_UP )
    {
        gbUpdate = TRUE;
        lpShip->dVelX += gDirx[lpShip->cFrame] * 10.0 / 1000.0;
        lpShip->dVelY += gDiry[lpShip->cFrame] * 10.0 / 1000.0;
    }
    if( dwControls & KEY_DOWN )
    {
        gbUpdate = TRUE;
        lpShip->dVelX -= gDirx[lpShip->cFrame] * 10.0 / 1000.0;
        lpShip->dVelY -= gDiry[lpShip->cFrame] * 10.0 / 1000.0;
    }
    if( dwControls & KEY_STOP )
    {
        gbUpdate = TRUE;
        lpShip->dVelX = 0.0;
        lpShip->dVelY = 0.0;
    }
    if( !lpShip->bBulletEnable && lpShip->bEnable )
    {
		if( dwControls & KEY_FIRE )
		{
            gbUpdate = TRUE;
			// launch a new bullet
			lpShip->dBulletPosX = (WORD) (gDirx[lpShip->cFrame]*6.0 + 16.0 + lpShip->dPosX);
			lpShip->dBulletPosY = (WORD) (gDiry[lpShip->cFrame]*6.0 + 16.0 + lpShip->dPosY);
			lpShip->dBulletVelX = gDirx[lpShip->cFrame]*500.0/1000.0;
			lpShip->dBulletVelY = gDiry[lpShip->cFrame]*500.0/1000.0;
			lpShip->bBulletEnable = TRUE;
			lpShip->dwBulletFrame = 0;
		}
    }
}

/*
 * SendSync
 *
 * Sends a sync message with the rendevous position. We are using a synchronization technique in
 * which every player informs everyone else where the player is going to be at the end of the 
 * next sync interval. Based on this rendezvous position, everyone tries to move their corresponding
 * ghosts to the rendezvous position by the end of the interval.
 */
void SendSync(LPSHIP lpShip)
{
	gSyncMsg.byShipType = lpShip->byType;
    gSyncMsg.cFrame = lpShip->cFrame;
    gSyncMsg.dPosX  = lpShip->dPosX + lpShip->dVelX*1000;
    gSyncMsg.dPosY  = lpShip->dPosY + lpShip->dVelY*1000;

    SendGameMessage((LPGENERICMSG) &gSyncMsg, DPID_ALLPLAYERS);
}

/*
 * UpdateDisplayStatus
 *
 * Updates the disable timeout. Enables the ship if disable timeout has elapsed.
 */
void UpdateDisplayStatus(LPSHIP lpShip)
{
    DWORD dwTickDiff;
    DWORD dwTickCount;

    // current time
    dwTickCount = timeGetTime();

    // time elapsed since last update
    dwTickDiff =  dwTickCount - lpShip->dwLastTick;

    // timestamp
    lpShip->dwLastTick = dwTickCount;

    // update time-out
    lpShip->iCountDown -= dwTickDiff;

    // time-out ?
	if( lpShip->iCountDown < 0 )
	{
        // get new position and enable our lpShip
	    lpShip->dPosX = randInt(0,MAX_SHIP_X);
	    lpShip->dPosY = randInt(0,MAX_SHIP_Y);
	    lpShip->cFrame = randInt(0, MAX_SHIP_FRAME);
		lpShip->bEnable = TRUE;
	}
}

/*
 * UpdatePosition
 *
 * Updates our ship's position
 */
void UpdatePosition(DPID dpId, LPSHIP lpShip )
{
    int     x,y;
    BYTE    oldxCell, oldyCell, newxCell, newyCell, mask, col, row;
    double  thisTick, totalTick, xtick, ytick;
    DWORD   dwTickCount;
    DWORD   dwTickDiff;

    if( !lpShip->bEnable )
        return;

    // how long has it been since we last updated
    dwTickCount = timeGetTime();
    dwTickDiff = dwTickCount - lpShip->dwLastTick;

    // current timestamp
    lpShip->dwLastTick = dwTickCount;

	oldxCell = (int)(lpShip->dPosX+16.0) >> 4;
	oldyCell = (int)(lpShip->dPosY+16.0) >> 4;

    // compute new position
    lpShip->dPosX += lpShip->dVelX * dwTickDiff;
    lpShip->dPosY += lpShip->dVelY * dwTickDiff;

	newxCell = (int)(lpShip->dPosX+16.0) >> 4;
	newyCell = (int)(lpShip->dPosY+16.0) >> 4;
	if(oldxCell != newxCell)
	{
        // we allow ghosts to pass through the blocks
		if( (dpId == gOurID) && IsHit( newxCell, newyCell ) )
		{
			if( lpShip->dVelX > 0.0 )
				lpShip->dPosX = (oldxCell << 4) + 15 - 16;
			else
				lpShip->dPosX = (oldxCell << 4) - 16;
			lpShip->dVelX = -lpShip->dVelX*0.9;
			newxCell = oldxCell;
            lpShip->bBounced = TRUE;
		}
	}
	if(oldyCell != newyCell)
	{
        // we allow ghosts to pass through the blocks
		if( (dpId == gOurID) && IsHit( newxCell, newyCell ) )
		{
			if( lpShip->dVelY > 0.0 )
				lpShip->dPosY = (oldyCell << 4) + 15 - 16;
			else
				lpShip->dPosY = (oldyCell << 4) - 16;

            lpShip->dVelY = -lpShip->dVelY*0.9;
            lpShip->bBounced = TRUE;
	    }
	}

    if( lpShip->dPosX > MAX_SHIP_X )
    {
        lpShip->dPosX = MAX_SHIP_X;
        lpShip->dVelX = -lpShip->dVelX*0.9;
        lpShip->bBounced = TRUE;
    }
    else if ( lpShip->dPosX < 0 )
    {
        lpShip->dPosX =0;
        lpShip->dVelX = -lpShip->dVelX*0.9;
        lpShip->bBounced = TRUE;
    }
    if( lpShip->dPosY > MAX_SHIP_Y )
    {
        lpShip->dPosY = MAX_SHIP_Y;
        lpShip->dVelY = -lpShip->dVelY*0.9;
        lpShip->bBounced = TRUE;
    }
    else if ( lpShip->dPosY < 0 )
    {
        lpShip->dPosY =0;
        lpShip->dVelY = -lpShip->dVelY*0.9;
        lpShip->bBounced = TRUE;
    }    

    if ((dpId == gOurID) && lpShip->bBounced)
    {
        SendSync(lpShip);
    }

    if( !lpShip->bBulletEnable )
        return;

    // update the active bullet
    lpShip->dwBulletFrame += dwTickDiff;
    if( lpShip->dwBulletFrame >= MAX_BULLET_FRAME )
    {
        lpShip->bFiring = FALSE;
        lpShip->bBulletEnable = FALSE;
		return;
    }


    if( lpShip->dBulletVelX != 0.0 )
		xtick = 8.0/lpShip->dBulletVelX;
    else
        xtick = 999999.0;

    if( lpShip->dBulletVelY != 0.0 )
		ytick = 8.0/lpShip->dBulletVelY;
    else
        ytick = 999999.0;

    if( xtick < 0.0 )
        xtick = -xtick;
    if( ytick < 0.0 )
        ytick = -ytick;

    if( xtick < ytick )
        thisTick = xtick;
    else
        thisTick = ytick;
	
    if( thisTick > dwTickDiff )
        thisTick = dwTickDiff;
	        
    for( totalTick = 0.0; totalTick < dwTickDiff; )
    {
        totalTick += thisTick;

        lpShip->dBulletPosX += lpShip->dBulletVelX * thisTick;
        lpShip->dBulletPosY += lpShip->dBulletVelY * thisTick;

        if( lpShip->dBulletPosX > MAX_BULLET_X )
        {
            lpShip->dBulletPosX = MAX_BULLET_X;
            lpShip->dBulletVelX = -lpShip->dBulletVelX*0.9;
        }
        else if ( lpShip->dBulletPosX < 0 )
        {
            lpShip->dBulletPosX =0;
            lpShip->dBulletVelX = -lpShip->dBulletVelX*0.9;
        }
        if( lpShip->dBulletPosY > MAX_BULLET_Y )
        {
            lpShip->dBulletPosY = MAX_BULLET_Y;
            lpShip->dBulletVelY = -lpShip->dBulletVelY*0.9;
        }
        else if ( lpShip->dBulletPosY < 0 )
        {
            lpShip->dBulletPosY =0;
            lpShip->dBulletVelY = -lpShip->dBulletVelY*0.9;
        }
    
        // check to see if it hit anything
        x = (int)(lpShip->dBulletPosX + 0.5) + 1;
        y = (int)(lpShip->dBulletPosY + 0.5) + 1;
	
        row = y >> 4;
        col = x >> 4;
        mask = 1 << (col & 0x7);
        col = col >> 3;
        if( gBlocks.bits[row][col] & mask )
        {
			// dwScored a block hit
            gBlockHitMsg.byRow = row;
            gBlockHitMsg.byCol = col;
            gBlockHitMsg.byMask = mask;
			SendGameMessage((LPGENERICMSG) &gBlockHitMsg, DPID_ALLPLAYERS);

			gBlocks.bits[row][col] &= ~mask;
			lpShip->dwScore += 10;
			lpShip->bBulletEnable = FALSE;
            lpShip->bBlockHit = TRUE;
            lpShip->bFiring   = FALSE;
        }
    }
}


/*
 * IsHit
 *
 * Tells if there is a block at (x,y) location
 */
BOOL IsHit( int x, int y )
{
    int col, mask;
    
    // outside screen boundaries?
    if( (x < 0) || (y < 0) || (x >= 40) || (y >= 30) )
        return TRUE;
	
    // look at the block bits
    mask = 1 << (x & 0x7);
    col = x >> 3;
    if( gBlocks.bits[y][col] & mask )
        return TRUE;
    else
        return FALSE;
}

/*
 * InitField
 *
 * Initializes block positions on the field
 */
void InitField(void)
{
    int i, x, y;
    
    // clear all gBlocks
    for(x=0; x<5; x++)
        for(y=0; y<30; y++)
		    gBlocks.bits[y][x] = 0;

    // set random gBlocks
    for(i=0; i<400; i++)
    {
        x = randInt(0, 40);
		y = randInt(0, 30);
		if( !setBlock(x, y) ) i--;
    }
}

/*
 * AddBlock
 *
 * Adds a block to the field
 */
void AddBlock(void)
{
	int x,y;

    // maybe add a block?
	if(gbIsHost && gbIsActive && ( randInt( 0, 100 ) > 98 ))
	{
		x = randInt( 0, 40);
		y = randInt( 0, 30);
		if( setBlock( x, y) )
		{
            gAddBlockMsg.byX    = (BYTE) x;
            gAddBlockMsg.byY    = (BYTE) y;
			SendGameMessage((LPGENERICMSG) &gAddBlockMsg, DPID_ALLPLAYERS);
		}
	}
}

/*
 * setBlock
 *
 * Turns on a block
 */
BOOL setBlock( int x, int y )
{
    BYTE  mask, col;

    mask = 1 << (x & 0x7);
    col = x >> 3;
    
    // is Block already set?
    if( gBlocks.bits[y][col] & mask )
        return FALSE;
	
    // set the block and return success
    gBlocks.bits[y][col] |= mask;
    return TRUE;
}

/*
 * AddFrag
 *
 * Turns on a fragment
 */
void AddFrag(LPSHIP lpShip, int offX, int offY)
{
    int i;
    for(i=0; i<64; i++) // find available fragment
    {
        if( !gFrags[i].valid )
	    break;
    }
    if( i == 64 )
        return;
	
    
    gFrags[i].dPosX = offX + lpShip->dPosX;
    gFrags[i].dPosY = offY + lpShip->dPosY;
    switch( lpShip->byType )
    {
    case 0: gFrags[i].surf = glpShip0;    break;
    case 1: gFrags[i].surf = glpShip1;    break;
    case 2: gFrags[i].surf = glpShip2;    break;
    case 3: gFrags[i].surf = glpShip3;    break;
	default: DEBUG_OUT(TEXT("Unknown ship type\n")); return;
    }
    gFrags[i].src.top = 32 * ( (int)lpShip->cFrame / 10 ) + offX;
    gFrags[i].src.left = 32 * ( (int)lpShip->cFrame % 10 ) + offY;
    gFrags[i].src.right = gFrags[i].src.left + 8;
    gFrags[i].src.bottom = gFrags[i].src.top + 8;
    gFrags[i].dVelX = ((double)offX - 12.0)/24.0;
    gFrags[i].dVelY = ((double)offY - 12.0)/24.0;
    gFrags[i].valid = TRUE;
}

/*
 * UpdateFragment
 *
 * Updates the position of a fragment
 */
void UpdateFragment(int i)
{
    DWORD   dwTickCount;
    static DWORD   dwTickDiff;
    static DWORD dwLastTick;

    if( i == 0)
    {
        dwTickCount = timeGetTime();
        dwTickDiff = dwTickCount - dwLastTick;
        dwLastTick = dwTickCount;
    }
    
    if( !gFrags[i].valid )
        return;
	
    gFrags[i].dPosX += (int) (gFrags[i].dVelX * dwTickDiff);
    gFrags[i].dPosY += (int) (gFrags[i].dVelY * dwTickDiff);
    if( (gFrags[i].dPosX < 0.0) || (gFrags[i].dPosX >= 632.0) ||
        (gFrags[i].dPosY < 0.0) || (gFrags[i].dPosY >= 472.0) )
    {
        gFrags[i].valid = FALSE;
    }
}

/*
 * DestroyShip
 *
 * Renders a bunch of fragments to show that the ship is destroyed
 */
void DestroyShip( LPSHIP lpShip )
{
	// Set flag for explosion sound
	lpShip->bDeath  = TRUE;

    // add ship fragments
    AddFrag(lpShip, 0, 0);
    AddFrag(lpShip, 8, 0);
    AddFrag(lpShip, 16, 0);
    AddFrag(lpShip, 24, 0);
    AddFrag(lpShip, 0, 8);
    AddFrag(lpShip, 8, 8);
    AddFrag(lpShip, 16, 8);
    AddFrag(lpShip, 24, 8);
    AddFrag(lpShip, 0, 16);
    AddFrag(lpShip, 8, 16);
    AddFrag(lpShip, 16, 16);
    AddFrag(lpShip, 24, 16);
    AddFrag(lpShip, 0, 24);
    AddFrag(lpShip, 8, 24);
    AddFrag(lpShip, 16, 24);
    AddFrag(lpShip, 24, 24);

    // Play explosion sound
    ProcessSoundFlags(lpShip);
}

/*
 * UpdateFrame
 *
 * Refreshes the screen
 */
BOOL UpdateFrame( void )
{
    int i;
    DWORD dwTickCount;
    SHIP  ship;
    DWORD dwSize;
    HRESULT hr;
    static dwSyncLastTick = 0;
    static dwUpdateLastTick = 0;
    
    switch( gnProgramState )
    {
    case PS_ACTIVE:
        // DINPUT: use DirectInput to read game-play keys
	    DI_ReadKeys();

        // get our local data
        dwSize = sizeof(ship);
        hr = DPlayGetPlayerData(gOurID, &ship, &dwSize, DPGET_LOCAL);
        if (FAILED(hr))
        {
            wsprintf(gDebugBuff, TEXT("Get Player local data failed for id %d\n"), gOurID);
            DEBUG_OUT(gDebugBuff);
            goto FAIL;
        }

        if (!ship.bEnable)
        {
            // update disable timeout and display status
            UpdateDisplayStatus(&ship);
        }
        else
        {
            // process any change in game controls 
            ProcessUserInput(&ship);

            dwTickCount = timeGetTime();

            // synchronize if it's time
            if (gbIsActive && ((dwTickCount - dwSyncLastTick) > SYNC_INTERVAL))
            {
                SendSync(&ship);
                dwSyncLastTick = dwTickCount;
            }

            // if our player changed any keys, let everyone know
            if (gbUpdate)
            {
                // control the number of packets we send
                if ((dwTickCount - dwUpdateLastTick) > UPDATE_INTERVAL)
                {
        		    // let others know
                    gControlMsg.byState = (BYTE) gdwKeys;
                    SendGameMessage((LPGENERICMSG) &gControlMsg, DPID_ALLPLAYERS);
                    dwUpdateLastTick = dwTickCount;
                }
            }
        }

	    // save ship data as RenderPlayerCB reads stored data
	    hr = DPlaySetPlayerData(gOurID, &ship, sizeof(ship), DPSET_LOCAL);
        if (FAILED(hr))
        {
            ShowError(IDS_DPLAY_ERROR_SPLD);
            goto FAIL;
        }   

		// update fragments
		for(i=0; i<64; i++)
			UpdateFragment(i);

    	// add a block
        if (!gbNoField)
    	    AddBlock();

        // render everything		
        if (!DrawScreen())
        {
            goto FAIL;
        }
        break;

    case PS_REST:
		if( gbHaveHostInit )
		{
			SetGamePalette();
			gnProgramState = PS_ACTIVE;
		}
		break;
    }

    // success
    return TRUE;

FAIL:
    // failed
    return FALSE;
}

/*
 *FUNCTION:   ProcessSoundFlags
 *
 *PARAMETERS:
 *    lpShip: Points to a ship structure (originally retrieved from
 *            GetPlayerData) in RenderPlayer.
 *
 *NOTES:      All y-coordinates must be made negative, because the
 *            3D Sound API's use an opposite coordinate system than
 *            the screen.
 */
void ProcessSoundFlags(LPSHIP lpShip)
{
    int i;
    BOOL bStart[MAX_SOUNDS]; //flags, used so we can 
    BOOL bStop [MAX_SOUNDS];

    if (!gbSoundInitialized)
	{
		// clear bounce flag so we don't send a message every time through the loop
        lpShip->bBounced = FALSE;
        return;
	}

    //if one is NULL, so are the other ones and we aren't initialized yet.
    for (i=0; i<MAX_SOUNDS; i++)
    {
        if (lpShip->lpDirectSoundBuffer[i]==NULL)
            return;
    }

    //set all our temporary flags to FALSE.
    for (i=0; i<MAX_SOUNDS; i++)
    {
        bStart[i] = FALSE;
        bStop[i]  = FALSE;
    }

    if (lpShip->dwKeys & KEY_ENGINEOFF)
        {
        bStop[SENGINE] = TRUE;
        lpShip->bEngineRunning = FALSE;
        }

    if (lpShip->dwKeys & (KEY_UP | KEY_DOWN))
        {
        if (!lpShip->bEngineRunning) //turn on engine
            {
            bStart[SENGINE] = TRUE;
            if (!lpShip->bMoving)   //"fire-up-engine" sound
                {
                bStart[SSTART] = TRUE;
                IDirectSound3DBuffer_SetPosition(lpShip->lpDirectSound3DBuffer[SSTART],
                                                  P2M(lpShip->dPosX - 320),
                                                 -P2M(lpShip->dPosY - 240),
                                                 D3DVAL(0),
                                                 DS3D_DEFERRED);
                bStart[SSTART] = TRUE;
                lpShip->bMoving = TRUE;
                }
            lpShip->bEngineRunning = TRUE;
            }
        }

    if (lpShip->bMoving)
        {
        IDirectSound3DBuffer_SetPosition(lpShip->lpDirectSound3DBuffer[SENGINE],
                                         P2M(lpShip->dPosX - 320),
                                        -P2M(lpShip->dPosY - 240),
                                        D3DVAL(0),
                                        DS3D_DEFERRED);
        IDirectSound3DBuffer_SetVelocity(lpShip->lpDirectSound3DBuffer[SENGINE],
                                         D3DVAL(lpShip->dVelX * 10), //exagerater vel
                                         -D3DVAL(lpShip->dVelY * 10),
                                         D3DVAL(0),
                                         DS3D_DEFERRED);
        }

    if (lpShip->dwKeys & KEY_STOP)
        {
        if (lpShip->bMoving)
            {
            IDirectSound3DBuffer_SetPosition(lpShip->lpDirectSound3DBuffer[SSTOP],
                                              P2M(lpShip->dPosX - 320),
                                             -P2M(lpShip->dPosY - 240),
                                             D3DVAL(0),
                                             DS3D_DEFERRED);
            bStart[SSTOP]   = TRUE;
            bStop[SENGINE]  = TRUE;
            lpShip->bEngineRunning  = FALSE;
            lpShip->bMoving         = FALSE;
            }
        }

    if (lpShip->dwKeys & KEY_FIRE)
        {
        if (!lpShip->bFiring)
            {
            IDirectSound3DBuffer_SetPosition(lpShip->lpDirectSound3DBuffer[BFIRE],
                                              P2M(lpShip->dPosX - 320),
                                             -P2M(lpShip->dPosY - 240),
                                             D3DVAL(0),
                                             DS3D_DEFERRED);
            bStart[BFIRE]   = TRUE;
            lpShip->bFiring = TRUE;
            }
        }

    if (lpShip->bBlockHit)
        {
        IDirectSound3DBuffer_SetPosition(lpShip->lpDirectSound3DBuffer[LBOOM],

                                          P2M(lpShip->dBulletPosX - 320),
                                         -P2M(lpShip->dBulletPosY - 240),
                                         D3DVAL(0),
                                         DS3D_DEFERRED);

        bStart[LBOOM] = TRUE;
        lpShip->bBlockHit = FALSE;
        }

    if (lpShip->bBounced)
        {
        IDirectSound3DBuffer_SetPosition(lpShip->lpDirectSound3DBuffer[SBOUNCE],
                                         P2M(lpShip->dPosX - 320),
                                         -P2M(lpShip->dPosY - 240),
                                         D3DVAL(0),
                                         DS3D_DEFERRED);

        bStart[SBOUNCE] = TRUE;
        lpShip->bBounced = FALSE;
        }


    if (lpShip->bDeath)
        {
        bStop [BFIRE]   = TRUE;
        bStop [SBOUNCE] = TRUE;
        bStop [SSTOP]   = TRUE;
        bStop [SSTART]  = TRUE;
        bStop [SENGINE] = TRUE;
        bStart[SBOOM]   = TRUE; 
        lpShip->bDeath  = FALSE;  //turn off sound flag.
        }

    //stop, update, and start sounds.
    for (i=0; i<MAX_SOUNDS; i++)
        {
        if (bStop[i])
            {
            IDirectSoundBuffer_Stop(lpShip->lpDirectSoundBuffer[i]);
            bStart[i] = FALSE;
            }
        }
    IDirectSound3DListener_CommitDeferredSettings(glpDirectSound3DListener);

    for (i=0; i<MAX_SOUNDS; i++)
        {
        if (bStart[i])
            {
             IDirectSoundBuffer_SetCurrentPosition(lpShip->lpDirectSoundBuffer[i], 0);

             if (DSERR_BUFFERLOST==IDirectSoundBuffer_Play(lpShip->lpDirectSoundBuffer[i],
                                                           0,
                                                           0,
                                                           (i==SENGINE) ? DSBPLAY_LOOPING : 0))
                {
                WaveReload(gSoundEffect[i]);
                }
            }
        }
    lpShip->dwKeys = 0;
};




/*
 * RenderPlayerCB
 *
 * Renders a ship in its current state. Also checks if we hit the ship and informs
 * the ship that it has been destroyed.
  */

BOOL WINAPI RenderPlayerCB(DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName, 
	DWORD dwFlags, LPVOID lpContext)
{
    SHIP ship, ourShip;
    DWORD dwSize = sizeof(ship);
    BOOL bHit = FALSE;
    HRESULT hr;
    DWORD dwTickCount;
    
    // get ship data
    hr = DPlayGetPlayerData(dpId, &ship, &dwSize, DPGET_LOCAL);

    if (FAILED(hr))
    {
        wsprintf(gDebugBuff, TEXT("Get Player local data failed for id %d\n"), dpId);
        DEBUG_OUT(gDebugBuff);
        goto FAIL;
    }

	// no player data yet
	if (0 == dwSize)
		return TRUE; 

    // ignore current ship ?
    if (ship.bIgnore)
    {
	    // if this ship was being ignored, update ignore time-out
	    // A time-out is used here to ensure that this ship doesn't get ignored
	    // forever on our screen in case the destroy message was dropped.
        dwTickCount = timeGetTime();
	    ship.iCountDown -= dwTickCount - ship.dwLastTick;
        ship.dwLastTick = dwTickCount;
	    if( ship.iCountDown < 0 ) 
		{
            ship.bIgnore = FALSE;
		}

        // save ship data
	    hr = DPlaySetPlayerData(dpId, &ship, sizeof(ship), DPSET_LOCAL);
        if (FAILED(hr))
        {
			wsprintf(gDebugBuff, TEXT("Set Player local data failed for id %d\n"), dpId);
			DEBUG_OUT(gDebugBuff);
            goto FAIL;
        }
        // we are ignoring this ship, so just bail
        return TRUE;
    }

    // bail, if ship is disabled
    if (!ship.bEnable) return TRUE;

	// update ship's position
	UpdatePosition(dpId, &ship);

    // get our player data to compare with others
    dwSize = sizeof(ship);
    hr = DPlayGetPlayerData(gOurID, &ourShip, &dwSize, DPGET_LOCAL);
    if (FAILED(hr))
    {
        wsprintf(gDebugBuff, TEXT("Get Player local data failed for id %d\n"), dpId);
        DEBUG_OUT(gDebugBuff);
        goto FAIL;
    }

	// check if our bullet hit the current ship
	if((dpId != gOurID) && ourShip.bBulletEnable && ship.bEnable)
	{
		if( (ourShip.dBulletPosX > ship.dPosX) &&
			(ourShip.dBulletPosX < (ship.dPosX + 32.0) ) &&
			(ourShip.dBulletPosY > ship.dPosY) &&
			(ourShip.dBulletPosY < (ship.dPosY + 32.0) ) )
		{
			// hasta-la-vista baby
			DestroyShip(&ship);
            // we nailed it
            bHit = TRUE;
            // turn off ship locally
            ship.bEnable = FALSE;
			// temporarily ignore ship until we get a response
			ship.bIgnore = TRUE;
			// set its ignore time-out
			ship.iCountDown = HIDE_TIMEOUT;
            // time-stamp
            ship.dwLastTick = timeGetTime();
			// turn our bullet off
			ship.bBulletEnable = FALSE;
			// update our score
            ourShip.dwScore += 1000;
        	// save our score
	        hr = DPlaySetPlayerData(gOurID, &ourShip, sizeof(ourShip), DPSET_LOCAL);
            if (FAILED(hr))
            {
                ShowError(IDS_DPLAY_ERROR_SPLD);
                goto FAIL;
            }
		}
	}

	// render the ship
	if (ship.bBulletEnable) DrawBullet(&ship);
	if (ship.bEnable)       DrawShip(&ship);

    ProcessSoundFlags(&ship);

	// save ship data
	hr = DPlaySetPlayerData(dpId, &ship, sizeof(ship), DPSET_LOCAL);
    if (FAILED(hr))
    {
		wsprintf(gDebugBuff, TEXT("Set Player local data failed for id %d\n"), dpId);
		DEBUG_OUT(gDebugBuff);
        goto FAIL;
    }

	// inform the player
    if (bHit)
    {
        gShipHitMsg.Id = dpId;
        SendGameMessage((LPGENERICMSG) &gShipHitMsg, dpId);
    }

    // success
    return TRUE;

FAIL:
    // failed
    return FALSE;
}

/*
 * DrawScreen
 * 
 * Renders the current frame
 */
BOOL DrawScreen( void )
{
    BYTE    mask, col;
    int     x, y;
    HRESULT hr;

	// clear screen
    EraseScreen();
    
	// render players
    hr = DPlayEnumPlayers(NULL, RenderPlayerCB, NULL, 0);
    if (FAILED(hr))
    {
        ShowError(IDS_DPLAY_ERROR_EP);
        goto FAIL;
    }

	// render field
    for( y=0; y<30; y++)
    {
        for( x=0; x<40; x++)
		{
			mask = 1 << (x & 0x7);
			col = x >> 3;
			if( gBlocks.bits[y][col] & mask )
				DrawBlock( x, y );
		}
    }
    
	// render score
    if (!DrawScore())
    {
        goto FAIL;
    }

	// render fragments
    DrawFragments();    

	// render frame rate
    if( gbShowFrameCount )
        DisplayFrameRate();

	// show
    FlipScreen();

    // success
    return TRUE;

FAIL:
    return FALSE;
}

/*
 * DisplayFrameRate
 * 
 * Renders current frame rate
 */
void DisplayFrameRate( void )
{
    DWORD			time2;
    char			buff[256];
	static DWORD	dwFrames;
	
    gdwFrameCount++;
    time2 = timeGetTime() - gdwFrameTime;
    if( time2 > 1000 )
    {
        dwFrames = (gdwFrameCount*1000)/time2;
        gdwFrameTime = timeGetTime();
        gdwFrameCount = 0;
    }
    if( dwFrames == 0 )
    {
        return;
    }

    if (dwFrames != gdwFramesLast)
    {
        gdwFramesLast = dwFrames;
    }

    if( dwFrames > 99 )
    {
	dwFrames = 99;
    }
    buff[0] = (char)((dwFrames / 10) + '0');
    buff[1] = (char)((dwFrames % 10) + '0');
    buff[2] = '\0';
    bltScore(buff, 295, 10);
}

/*
 * DrawScore
 *
 * Renders our current score
 */
BOOL DrawScore( void )
{
    SHIP        ship;
    DWORD       dwSize;
    char        dwScorebuf[11];
    int         rem;
    HRESULT     hr;

    dwSize = sizeof(ship);
    hr = DPlayGetPlayerData(gOurID, &ship, &dwSize, DPGET_LOCAL);
    if (FAILED(hr))
    {
        wsprintf(gDebugBuff, TEXT("Get Player local data failed for id %d\n"), gOurID);
        DEBUG_OUT(gDebugBuff);
        goto FAIL;
    }

    // blt everything in reverse order if we are doing destination transparency
    // calculate dwScore string
    dwScorebuf[0] = (BYTE)ship.dwScore/100000 + '0';
    rem = ship.dwScore % 100000;
    dwScorebuf[1] = rem/10000 + '0';
    rem = ship.dwScore % 10000;
    dwScorebuf[2] = rem/1000 + '0';
    rem = ship.dwScore % 1000;
    dwScorebuf[3] = rem/100 + '0';
    rem = ship.dwScore % 100;
    dwScorebuf[4] = rem/10 + '0';
    rem = ship.dwScore % 10;
    dwScorebuf[5] = rem + '0';
    dwScorebuf[6] = '\0';

    bltScore(dwScorebuf, 8, 8);

	// save ship data
	hr = DPlaySetPlayerData(gOurID, &ship, sizeof(ship), DPSET_LOCAL);
    if (FAILED(hr))
    {
        ShowError(IDS_DPLAY_ERROR_SPLD);
        goto FAIL;
    }

    return TRUE;

FAIL:
    // failed
    return FALSE;
}

/*
 * DrawBlock
 *
 * Renders a block
 */
void DrawBlock( int x, int y )
{
    RECT    src;
    
    src.top = 0;
    src.left = 224;
    src.right = src.left + 16;
    src.bottom = src.top + 16;
    bltObject( x << 4, y << 4, glpNum, &src, DDBLTFAST_SRCCOLORKEY );
}

/*
 * DrawShip
 *
 * Renders a ship
 */
void DrawShip( LPSHIP lpShip )
{
    RECT    src;
    LPDIRECTDRAWSURFACE surf;

    src.top = 32 * (lpShip->cFrame / 10 );
    src.left = 32 * (lpShip->cFrame % 10 );
    src.right = src.left + 32;
    src.bottom = src.top + 32;
    switch( lpShip->byType )
    {
    case 0: surf = glpShip0; break;
    case 1: surf = glpShip1; break;
    case 2: surf = glpShip2; break;
    case 3: surf = glpShip3; break;
    default: DEBUG_OUT(TEXT("Ship type not specified\n")); return;
    }
    bltObject((int)lpShip->dPosX, (int)lpShip->dPosY, surf, &src, DDBLTFAST_SRCCOLORKEY );
}

/*
 * DrawBullet
 *
 * Renders a bullet 
 */
void DrawBullet( LPSHIP lpShip )
{
    RECT    src;
    
    src.top = BULLET_Y;
    src.left = BULLET_X + (lpShip->byType)*4;
    src.right = src.left + 3;
    src.bottom = src.top + 3;
    bltObject((int)lpShip->dBulletPosX, (int)lpShip->dBulletPosY, glpNum, &src, DDBLTFAST_SRCCOLORKEY );
}

/*
 * DrawFragments
 *
 * Renders the fragments
 */

void DrawFragments( void )
{
    int     i;
    
    for(i=0; i<64; i++)
    {
		if( gFrags[i].valid )
		{
			bltObject((int)gFrags[i].dPosX, (int)gFrags[i].dPosY, gFrags[i].surf,
				&(gFrags[i].src), DDBLTFAST_SRCCOLORKEY );
		}
    }
}

/*
 * ReceiveGameMessages
 *
 * Checks if there are any messages for us and receives them
 */
HRESULT ReceiveMessages( void )
{
	DPID				idFrom, idTo;
	LPVOID				lpvMsgBuffer;
	DWORD				dwMsgBufferSize;
	HRESULT				hr;

	// read all messages in queue
	dwMsgBufferSize = gdwReceiveBufferSize;
	lpvMsgBuffer = glpvReceiveBuffer;
	
	while (TRUE)
	{
		// see what's out there
		idFrom = 0;
		idTo = 0;

		hr = DPlayReceive(&idFrom, &idTo, DPRECEIVE_ALL, lpvMsgBuffer, &dwMsgBufferSize);
		if (hr == DPERR_BUFFERTOOSMALL)
		{
			if (lpvMsgBuffer == NULL)
			{
				lpvMsgBuffer = GlobalAllocPtr(GHND, dwMsgBufferSize);
				if (lpvMsgBuffer == NULL)
					return (DPERR_NOMEMORY);
				glpvReceiveBuffer = lpvMsgBuffer;
				gdwReceiveBufferSize = dwMsgBufferSize;
			}
			else if (dwMsgBufferSize > gdwReceiveBufferSize)
			{
				lpvMsgBuffer = GlobalReAllocPtr(lpvMsgBuffer, dwMsgBufferSize, 0);
				if (lpvMsgBuffer == NULL)
					return (DPERR_NOMEMORY);
				glpvReceiveBuffer = lpvMsgBuffer;
				gdwReceiveBufferSize = dwMsgBufferSize;
			}
		}
		else if ((hr == DP_OK) && 
                 ((dwMsgBufferSize >= sizeof(GENERICMSG)) || 
                  (dwMsgBufferSize >= sizeof(DPMSG_GENERIC))))
		{
			if (idFrom == DPID_SYSMSG)
            {
				DoSystemMessage((LPDPMSG_GENERIC) lpvMsgBuffer, dwMsgBufferSize, idFrom, idTo);
            }
			else
            {
				DoApplicationMessage((LPGENERICMSG) lpvMsgBuffer, dwMsgBufferSize, idFrom, idTo);
            }
		}
		else
			break;
	};

    return hr;
}

/*
 * DoSystemMessage
 *
 * Evaluates system messages and performs appropriate actions
 */
void DoSystemMessage( LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize, DPID idFrom, DPID idTo )
{
    switch( lpMsg->dwType)
    {
    case DPSYS_CREATEPLAYERORGROUP:
        {
        	LPDPMSG_CREATEPLAYERORGROUP lpAddMsg = (LPDPMSG_CREATEPLAYERORGROUP) lpMsg;

            if( gbIsHost)
		    {
                gHostMsg.Blocks = gBlocks;
			    SendGameMessage((LPGENERICMSG) &gHostMsg, lpAddMsg->dpId);
		    }
        }
		break;

    case DPSYS_DESTROYPLAYERORGROUP:
        {
            LPSHIP lpShip;
        	LPDPMSG_DESTROYPLAYERORGROUP lpDestroyMsg = (LPDPMSG_DESTROYPLAYERORGROUP) lpMsg;

            if ((sizeof(SHIP) != lpDestroyMsg->dwLocalDataSize) || 
                (NULL == lpDestroyMsg->lpLocalData))
                break;

            lpShip = lpDestroyMsg->lpLocalData;
            ReleasePlayerLocalSoundData(lpShip);
        }
		break;

	case DPSYS_HOST:
        {	    	
            gbIsHost = TRUE;            
			UpdateTitle();
        }

		break;

    case DPSYS_SESSIONLOST:
        // inform user that session was lost
        ShowError(IDS_DPLAY_ERROR_SL);
        gbSessionLost = TRUE;
        break;
    }
}

/*
 * DoApplicationMessage
 *
 * Evaluates an application message and performs appropriate actions
 */
void DoApplicationMessage( LPGENERICMSG lpMsg, DWORD dwMsgSize, DPID idFrom, DPID idTo )
{        
    HRESULT hr;

    switch( lpMsg->byType )
    {
    case MSG_HOST:
		{
			LPHOSTMSG       lpHost;

			if( !gbIsHost )
			{
				lpHost = (LPHOSTMSG) lpMsg;
                // receive the field layout
				gBlocks = lpHost->Blocks;

                // have host initializtion at this point
				gbHaveHostInit = TRUE;
                
                // start updating screen
                gbIsActive = TRUE;
			}
		}
		break;

    case MSG_BLOCKHIT:
		{
			LPBLOCKHITMSG   lpBlockHit;

			lpBlockHit = (LPBLOCKHITMSG) lpMsg;
			gBlocks.bits[lpBlockHit->byRow][lpBlockHit->byCol] &= ~lpBlockHit->byMask;
		}
		break;

    case MSG_ADDBLOCK:
		{
			LPADDBLOCKMSG   lpAddBlock;

			lpAddBlock = (LPADDBLOCKMSG) lpMsg;
			setBlock( lpAddBlock->byX, lpAddBlock->byY);
		}
		break;

    case MSG_SHIPHIT:
        {
		    LPSHIPHITMSG    lpShipHit = (LPSHIPHITMSG) lpMsg;
            SHIP ship;
            DWORD dwSize;

            dwSize = sizeof(SHIP);
			 // get player local data
			hr = DPlayGetPlayerData(lpShipHit->Id, &ship, &dwSize, DPGET_LOCAL);
            if (FAILED(hr))
                return;

			// no player data yet
			if (0 == dwSize)
				return;

			if (!ship.bIgnore) 
            {
				// explode the ship on our screen
				DestroyShip(&ship);

    			// turn it off
				ship.bEnable = FALSE;
				ship.bBulletEnable = FALSE;

				// if it is us
				if (lpShipHit->Id == gOurID)
				{
                    // set our hide time-out
    				ship.iCountDown = HIDE_TIMEOUT;
                    ship.dwLastTick = timeGetTime();
                    // let the world know that we are dead
                    gShipHitMsg.Id = gOurID;
					SendGameMessage((LPGENERICMSG) &gShipHitMsg, DPID_ALLPLAYERS);					
				}
			}
            // update player local data
  			DPlaySetPlayerData(lpShipHit->Id, &ship, sizeof(ship), DPSET_LOCAL);
        }
		break;

    case MSG_CONTROL:
        {
            LPCONTROLMSG lpControlMsg;
            SHIP ship;
            DWORD dwSize;

            lpControlMsg = (LPCONTROLMSG) lpMsg;
            dwSize = sizeof(SHIP);
			// get player local data
			hr = DPlayGetPlayerData(idFrom, &ship, &dwSize, DPGET_LOCAL);
            if (FAILED(hr))
                return;

			// no player data yet
			if (0 == dwSize)
				return;

            // update its State
            UpdateState(&ship, (DWORD)lpControlMsg->byState);

            // save it back
   			DPlaySetPlayerData(idFrom, &ship, dwSize, DPSET_LOCAL);
        }
        break;

    case MSG_SYNC:
        {
            LPSYNCMSG lpSyncMsg;
            SHIP ship;
            DWORD dwSize;

            lpSyncMsg = (LPSYNCMSG) lpMsg;
            dwSize = sizeof(SHIP);
			// get player local data
			hr = DPlayGetPlayerData(idFrom, &ship, &dwSize, DPGET_LOCAL);
            if (FAILED(hr))
                return;

			// we are seeing this player for the first time
			// so do the initialization
			if (0 == dwSize)
			{
				ZeroMemory(&ship, sizeof(ship));

				// initialize sound buffers (this should never be us)                     
                if(gOurID == idFrom) 
                {
                    MessageBox (NULL, "gOurID == idFrom", "Ack!!!", MB_ICONEXCLAMATION | MB_OK | MB_TASKMODAL);
                    _asm int 3
                }
				InitPlayerLocalSoundData(&ship, FALSE);

				ship.byType = lpSyncMsg->byShipType;
                ship.dPosX = lpSyncMsg->dPosX;
                ship.dPosY = lpSyncMsg->dPosY;
                ship.cFrame = lpSyncMsg->cFrame;
                ship.dwLastTick = timeGetTime();
                ship.bEnable = TRUE;
			}
			
			if (ship.bEnable)
            {
                // head towards rendezvous location (accelerate/decelerate as necessary)
                ship.dVelX = (lpSyncMsg->dPosX - ship.dPosX)/1000;
                ship.dVelY = (lpSyncMsg->dPosY - ship.dPosY)/1000;
                ship.cFrame = lpSyncMsg->cFrame;
            }
            else if (!ship.bIgnore)
            // Ship is alive, but we just don't know it.
			// So, display it at the rendezvous location.
            {
                ship.dPosX = lpSyncMsg->dPosX;
                ship.dPosY = lpSyncMsg->dPosY;
                ship.cFrame = lpSyncMsg->cFrame;
                ship.dwLastTick = timeGetTime();
                ship.bEnable = TRUE;
            }

            // save it back
   			DPlaySetPlayerData(idFrom, &ship, sizeof(ship), DPSET_LOCAL);
        }
        break;

    default:
		{
            wsprintf(gDebugBuff, TEXT("Unknown message type %d\n"), lpMsg->byType);
			DEBUG_OUT( gDebugBuff );
		}
		break;
    }
}

/*
 * SendGameMessage
 *
 * Sends a message to specified player(s)
 */
void SendGameMessage( LPGENERICMSG lpMsg, DPID idTo )
{
    int             nBytes;
	DWORD			dwFlags = 0;

    if (gbSessionLost)
    {
        // no sends when we are not in the session
        return;
    }

    switch( lpMsg->byType )
    {
    case MSG_HOST:
        nBytes = sizeof( HOSTMSG );
		dwFlags = DPSEND_GUARANTEED;
		break;

    case MSG_BLOCKHIT:
		nBytes = sizeof( BLOCKHITMSG );
		break;

    case MSG_SHIPHIT:
		nBytes = sizeof( SHIPHITMSG );
		break;

    case MSG_ADDBLOCK:
		nBytes = sizeof( ADDBLOCKMSG );
		break;

    case MSG_CONTROL:
		nBytes = sizeof( CONTROLMSG );
        break;

    case MSG_SYNC:
		nBytes = sizeof( SYNCMSG );
        break;

    default:
        return;
	}

    if (gbReliable)
    {
    	dwFlags = DPSEND_GUARANTEED;
    }

	// Send the message to the relevant player(s)
	DPlaySend(gOurID, idTo, dwFlags, (LPVOID)lpMsg, nBytes);	
}

/*
 * CleanupComm
 *
 * Cleans up communication stuff
 */
void CleanupComm(void)
{
	HRESULT hr;

	//free up all the local sound buffers
    ReleaseLocalData();

    // free the receive buffer
    if (glpvReceiveBuffer)
	{
    	GlobalFreePtr(glpvReceiveBuffer);
		glpvReceiveBuffer = NULL;
	}

    // delete our player
    if( gOurID ) 
    {
        hr = DPlayDestroyPlayer(gOurID);
        if (FAILED(hr))
        {
            ShowError(IDS_DPLAY_ERROR_DP);
        }
		gOurID = 0;
    }

	// cleanup directplay objects
	hr = DPlayClose();
	hr = DPlayRelease();
}
