#ifndef SFX_HEADER
#define SFX_HEADER
/*==========================================================================
 *
 *  Copyright (C) 1995 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       sfx.h
 *  Content:    Routines
 *
 *
 ***************************************************************************/

#include <dsound.h>
#include "ds3dutil.h"
/******************* DEFINITIONS ***************************
These will be used to index the array of CSound3D objects.
*********************************************************/
#define BFIRE       0 //Bullet Firing
#define SBOOM       1 //Ship Exploding
#define SENGINE     2 //Ship Engine
#define SSTART      3 //Starting Engine
#define SSTOP       4 //Stopping Engine (key 5)
#define SBOUNCE     5 //Bouncing off a block or window edge
#define LBOOM       6 //Block destruction

#define MAX_SOUNDS  7 

/******************* DEFINITIONS FOR SHARED INFO ************/
#define ENGINE_STATE 0x00000001l      // Set if Engine is running


/**************** CONVERSION MACROS **************************
These would be faster if hard-coded, but are left like this
for readability.
**************************************************************/
#define SCREEN_METERS D3DVAL(6)         //(How many meters wide is the screen?)
#define PPM    D3DVAL(640/SCREEN_METERS)  //How many pixels per meter?
#define MPP    D3DVAL(SCREEN_METERS/640.f)  //How many meters per pixel?
#define P2M(x) D3DVAL(D3DVAL(x) * MPP)   //converts pixels to meters
#define M2P(x) D3DVAL(D3DVAL(x) * PPM)   //converts meters to pixels

/****************** FUNCTION PROTOTYPES *********************/
BOOL InitSfx(void);
void CleanupSfx(void);
/************************ VARIABLES *************************/
extern LPWAVEDATA           gSoundEffect[MAX_SOUNDS];
extern BOOL                 gbSoundInitialized;
extern CHAR *               gszResourceName[MAX_SOUNDS];
extern LPDIRECTSOUND        glpDirectSound;
extern LPDIRECTSOUND3DLISTENER   glpDirectSound3DListener;
extern LPDIRECTSOUNDBUFFER  glpPrimaryBuffer;

#endif
