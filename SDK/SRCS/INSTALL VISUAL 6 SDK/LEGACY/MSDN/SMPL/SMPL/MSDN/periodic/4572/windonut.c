// WINDONUT.C -- The Core of Donut Ahniliator!

#include "windonut.h"

#define NUMDONUTS    35
#define NUMSHOTS     4   
#define ACCEL_FACTOR 8
#define MAX_X_VEL    700
#define MAX_Y_VEL    700
#define ROTATE_SPEED 2
#define SHOTDURATION 80
#define SHOTSPEED    10
#define FRICTION     1
#define MINSPEED     50


#define SPRITE_SHIP       0
#define SPRITE_BACKGROUND   1
#define SPRITE_SHOTS        2
#define SPRITE_DONUTS       (SPRITE_SHOTS+NUMSHOTS)
#define SPRITE_EXPLOSION    (SPRITE_DONUTS+NUMDONUTS)

enum 
  {
  JOYDIR_LEFT,
  JOYDIR_RIGHT,
  JOYDIR_CENTER
  };


int   iRotateCounter;
BOOL  bFireKeyDown;
int   iDonutRunCountDown;
int   giJoyPos;
BOOL  gbButton1, gbButton2;

int iThrustEffect[32][4] =   // 0 = xVel, 1 = xDir, 2 = yVel, 3 = yDir
  {
   {    0, SPRITE_DIR_STOPPED, 100, SPRITE_DIR_UP },  // 0

   {   12, SPRITE_DIR_RIGHT,    86, SPRITE_DIR_UP },  // 1
   {   24, SPRITE_DIR_RIGHT,    74, SPRITE_DIR_UP },  // 2
   {   36, SPRITE_DIR_RIGHT,    62, SPRITE_DIR_UP },  // 3
   {   50, SPRITE_DIR_RIGHT,    50, SPRITE_DIR_UP },  // 4
   {   62, SPRITE_DIR_RIGHT,    36, SPRITE_DIR_UP },  // 5
   {   74, SPRITE_DIR_RIGHT,    24, SPRITE_DIR_UP },  // 6
   {   86, SPRITE_DIR_RIGHT,    12, SPRITE_DIR_UP },  // 7

   {  100, SPRITE_DIR_RIGHT,     0, SPRITE_DIR_STOPPED },  // 8

   {   86, SPRITE_DIR_RIGHT,    12, SPRITE_DIR_DOWN },  // 9
   {   74, SPRITE_DIR_RIGHT,    24, SPRITE_DIR_DOWN },  // 10
   {   62, SPRITE_DIR_RIGHT,    36, SPRITE_DIR_DOWN },  // 11
   {   50, SPRITE_DIR_RIGHT,    50, SPRITE_DIR_DOWN },  // 12
   {   36, SPRITE_DIR_RIGHT,    62, SPRITE_DIR_DOWN },  // 13
   {   24, SPRITE_DIR_RIGHT,    74, SPRITE_DIR_DOWN },  // 14
   {   12, SPRITE_DIR_RIGHT,    86, SPRITE_DIR_DOWN },  // 15

   {    0, SPRITE_DIR_STOPPED, 100, SPRITE_DIR_DOWN },  // 16

   {   12, SPRITE_DIR_LEFT,    86, SPRITE_DIR_DOWN },  // 17
   {   24, SPRITE_DIR_LEFT,    74, SPRITE_DIR_DOWN },  // 18
   {   36, SPRITE_DIR_LEFT,    62, SPRITE_DIR_DOWN },  // 19
   {   50, SPRITE_DIR_LEFT,    50, SPRITE_DIR_DOWN },  // 20
   {   62, SPRITE_DIR_LEFT,    36, SPRITE_DIR_DOWN },  // 21
   {   74, SPRITE_DIR_LEFT,    24, SPRITE_DIR_DOWN },  // 22
   {   86, SPRITE_DIR_LEFT,    12, SPRITE_DIR_DOWN },  // 23

   {  100, SPRITE_DIR_LEFT,     0, SPRITE_DIR_STOPPED },  // 24

   {   86, SPRITE_DIR_LEFT,    12, SPRITE_DIR_UP },  // 25
   {   74, SPRITE_DIR_LEFT,    24, SPRITE_DIR_UP },  // 26
   {   62, SPRITE_DIR_LEFT,    36, SPRITE_DIR_UP },  // 27
   {   50, SPRITE_DIR_LEFT,    50, SPRITE_DIR_UP },  // 28
   {   36, SPRITE_DIR_LEFT,    62, SPRITE_DIR_UP },  // 29
   {   24, SPRITE_DIR_LEFT,    74, SPRITE_DIR_UP },  // 30
   {   12, SPRITE_DIR_LEFT,    86, SPRITE_DIR_UP }   // 31
 };

void FigureShipPosition    (void);
void FigureBulletPositions (void);
void FigureCollisions      (void);
void ReadJoyStick          (void);

void MakeFlyingDonutSprites             (void);
void MakeDonutBlasterBulletSprites      (void);
void MakeDonutDestroyingSpaceShipSprite (void);
void MakeExplosionSprite                (void);
void MakeBackGroundSprite               (void);

/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/

void FigureShipPosition(void)
{
  int iCurrFrame;
  int iCurXDir, iCurYDir;
  int iCurXVel, iCurYVel;

  if ( 
      (JOYDIR_LEFT == giJoyPos) ||
      (GetAsyncKeyState('1') < 0)  // rotate
     )
    {
    iRotateCounter = (iRotateCounter+1)%ROTATE_SPEED;
    if (!iRotateCounter)
      SPRITEHIGH_PrevFrame ( glpMasterSprite, SPRITE_SHIP);
    }

  if ( 
      (JOYDIR_RIGHT == giJoyPos) ||
      (GetAsyncKeyState('2') < 0)  // rotate
     )
    {
    iRotateCounter = (iRotateCounter+1)%ROTATE_SPEED;
    if (!iRotateCounter)
      SPRITEHIGH_NextFrame ( glpMasterSprite, SPRITE_SHIP);
    }

  iCurrFrame = SPRITEHIGH_GetCurrentFrame ( glpMasterSprite, SPRITE_SHIP);

  if (gbButton2 || GetAsyncKeyState('9') < 0)  // Thrust
    {
    if (glpSoundThrust)
      if (!(glpSoundThrust->bPlaying))
        DIRECTSOUND_Play ( glpDirectSound, glpSoundThrust );

    iCurXDir = SPRITEHIGH_GetCurrentXDirection ( glpMasterSprite, SPRITE_SHIP);
    iCurYDir = SPRITEHIGH_GetCurrentYDirection ( glpMasterSprite, SPRITE_SHIP);
    iCurXVel = SPRITEHIGH_GetCurrentXVelocity  ( glpMasterSprite, SPRITE_SHIP);
    iCurYVel = SPRITEHIGH_GetCurrentYVelocity  ( glpMasterSprite, SPRITE_SHIP);

    // 0 = xVel, 1 = xDir, 2 = yVel, 3 = yDir

    if (iThrustEffect[iCurrFrame][1] == iCurXDir)
      {
      // Add to speed in X direction
      iCurXVel = min(MAX_X_VEL, iCurXVel+ iThrustEffect[iCurrFrame][0]/ACCEL_FACTOR);
      }
    else
      {
      // Slow down or reverse direction
      iCurXVel -= iThrustEffect[iCurrFrame][0]/ACCEL_FACTOR;
      if (iCurXVel < 0)  // Reverse?
        {
        iCurXVel *= -1;
        iCurXDir = iThrustEffect[iCurrFrame][1];
        }
      }

    if (iThrustEffect[iCurrFrame][3] == iCurYDir)
      {
      // Add to speed in Y direction
      iCurYVel = min(MAX_Y_VEL, iCurYVel+ iThrustEffect[iCurrFrame][2]/ACCEL_FACTOR);
      }
    else
      {
      // Slow down or reverse direction
      iCurYVel -= iThrustEffect[iCurrFrame][2]/ACCEL_FACTOR;
      if (iCurYVel < 0)  // Reverse?
        {
        iCurYVel *= -1;
        iCurYDir = iThrustEffect[iCurrFrame][3];
        }
      }

    SPRITEHIGH_SetCurrentXDirection ( glpMasterSprite, SPRITE_SHIP, iCurXDir);
    SPRITEHIGH_SetCurrentYDirection ( glpMasterSprite, SPRITE_SHIP, iCurYDir);
    SPRITEHIGH_SetCurrentXVelocity  ( glpMasterSprite, SPRITE_SHIP, iCurXVel);
    SPRITEHIGH_SetCurrentYVelocity  ( glpMasterSprite, SPRITE_SHIP, iCurYVel);
    }
  else
    {
    if (glpSoundThrust)
      if (glpSoundThrust->bPlaying)
        DIRECTSOUND_Stop ( glpDirectSound, glpSoundThrust );
    }


  // Figure in Friction

  iCurXDir = SPRITEHIGH_GetCurrentXDirection ( glpMasterSprite, SPRITE_SHIP);
  iCurYDir = SPRITEHIGH_GetCurrentYDirection ( glpMasterSprite, SPRITE_SHIP);
  iCurXVel = SPRITEHIGH_GetCurrentXVelocity  ( glpMasterSprite, SPRITE_SHIP);
  iCurYVel = SPRITEHIGH_GetCurrentYVelocity  ( glpMasterSprite, SPRITE_SHIP);
  if (iCurXVel >= MINSPEED) iCurXVel -= FRICTION;
  if (iCurYVel >= MINSPEED) iCurYVel -= FRICTION;
  SPRITEHIGH_SetCurrentXVelocity  ( glpMasterSprite, SPRITE_SHIP, iCurXVel);
  SPRITEHIGH_SetCurrentYVelocity  ( glpMasterSprite, SPRITE_SHIP, iCurYVel);
}

/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/

void FigureBulletPositions(void)
{
  int iCurrFrame;
  int iCurXDir, iCurYDir;
  int iCurXVel, iCurYVel;

  int iShotXDir, iShotYDir;
  int iShotXVel, iShotYVel;

  int iOpenSprite, i;

  iCurrFrame = SPRITEHIGH_GetCurrentFrame ( glpMasterSprite, SPRITE_SHIP);
  iCurXDir = SPRITEHIGH_GetCurrentXDirection ( glpMasterSprite, SPRITE_SHIP);
  iCurYDir = SPRITEHIGH_GetCurrentYDirection ( glpMasterSprite, SPRITE_SHIP);
  iCurXVel = SPRITEHIGH_GetCurrentXVelocity  ( glpMasterSprite, SPRITE_SHIP);
  iCurYVel = SPRITEHIGH_GetCurrentYVelocity  ( glpMasterSprite, SPRITE_SHIP);

  if (gbButton1 || GetAsyncKeyState('0') < 0)  // Fire!
    {
    if (!bFireKeyDown)
      {
      bFireKeyDown = TRUE;

      iOpenSprite = -1;

      for ( i = 0; (i < NUMSHOTS) && ( -1 == iOpenSprite); i++ )
        if (!SPRITEHIGH_GetActiveState ( glpMasterSprite, SPRITE_SHOTS+i ))
          {
          iOpenSprite = i;

          iShotXDir = iThrustEffect[iCurrFrame][1];
          iShotYDir = iThrustEffect[iCurrFrame][3];
          iShotXVel = iThrustEffect[iCurrFrame][0]*SHOTSPEED;
          iShotYVel = iThrustEffect[iCurrFrame][2]*SHOTSPEED;

          if (iCurXVel < 50) iCurXVel = 0;
          if (iCurYVel < 50) iCurYVel = 0;

          // Check for shooting while drifting backwards

          if (iCurXVel && !iCurYVel && ((0 == iCurrFrame)||(16 ==iCurrFrame))) // Drifting straight across
            {
            iShotXVel = iCurXVel;
            iShotXDir = iCurXDir;
            }
          else
            {
            if (iShotXDir != iCurXDir)
              {
              if (iShotXVel < iCurXVel)
                {
                iCurXVel -= iShotXVel;
                iShotXDir = iCurXDir;
                }
              else
                {
                iShotXVel -= iCurXVel;
                }
              }
            else
              {
              iShotXVel += iCurXVel;
              }
            }

          if (!iCurXVel && iCurYVel && ((24 == iCurrFrame)||(8 ==iCurrFrame))) // Drifting straight up/down
            {
            iShotYVel = iCurYVel;
            iShotYDir = iCurYDir;
            }
          else
            {
            if (iShotYDir != iCurYDir)
              {
              if (iShotYVel < iCurYVel)
                {
                iCurYVel -= iShotYVel;
                iShotYDir = iCurYDir;
                }
              else
                {
                iShotYVel -= iCurYVel;
                }
              }
            else
              {
              iShotYVel += iCurYVel;
              }
            }

          SPRITEHIGH_SetPos( glpMasterSprite, 
                             SPRITE_SHOTS + iOpenSprite,
                             SPRITEHIGH_GetXPos(glpMasterSprite, SPRITE_SHIP)+20,
                             SPRITEHIGH_GetYPos(glpMasterSprite, SPRITE_SHIP)+20);
          SPRITEHIGH_SetActiveState ( glpMasterSprite, SPRITE_SHOTS + iOpenSprite, SHOTDURATION );
                                                                             // 0 = xVel, 1 = xDir, 2 = yVel, 3 = yDir

          SPRITEHIGH_SetCurrentXDirection ( glpMasterSprite, SPRITE_SHOTS + iOpenSprite, iShotXDir);
          SPRITEHIGH_SetCurrentYDirection ( glpMasterSprite, SPRITE_SHOTS + iOpenSprite, iShotYDir);
          SPRITEHIGH_SetCurrentXVelocity  ( glpMasterSprite, SPRITE_SHOTS + iOpenSprite, iShotXVel);
          SPRITEHIGH_SetCurrentYVelocity  ( glpMasterSprite, SPRITE_SHOTS + iOpenSprite, iShotYVel);

          if (glpSoundFire)
            DIRECTSOUND_Play ( glpDirectSound, glpSoundFire );
          }
       }
    }
  else
    {
    bFireKeyDown = FALSE;
    }
}

/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/

void FigureCollisions(void)
{
  int i, j, iDonutCount;

  // Collision detection AND checking to see if more donuts are needed

  iDonutCount = 0;

  for ( j = 0; j < NUMDONUTS; j++ )
    if (SPRITEHIGH_GetActiveState ( glpMasterSprite, SPRITE_DONUTS+j ))
      {
      iDonutCount++;
      for ( i = 0; i < NUMSHOTS; i++ )
        if (SPRITEHIGH_GetActiveState ( glpMasterSprite, SPRITE_SHOTS+i ))
           if (SPRITEHIGH_DoTheseCollide(glpMasterSprite, SPRITE_SHOTS+i,
                                         glpMasterSprite, SPRITE_DONUTS+j))
             {
             SPRITEHIGH_SetActiveState ( glpMasterSprite, SPRITE_SHOTS + i, FALSE );
             SPRITEHIGH_SetActiveState ( glpMasterSprite, SPRITE_DONUTS+ j, FALSE );

             SPRITEHIGH_SetCurrentFrame ( glpMasterSprite, SPRITE_EXPLOSION, 0 );
             SPRITEHIGH_SetPos( glpMasterSprite, 
                                SPRITE_EXPLOSION,
                                SPRITEHIGH_GetXPos(glpMasterSprite, SPRITE_DONUTS+ j),
                                SPRITEHIGH_GetYPos(glpMasterSprite, SPRITE_DONUTS+ j));
             SPRITEHIGH_SetActiveState ( glpMasterSprite, SPRITE_EXPLOSION, 11 );

             if (glpSoundExplosion)
               DIRECTSOUND_Play ( glpDirectSound, glpSoundExplosion );
             }
      }

  if (!iDonutCount && !iDonutRunCountDown)  // Time for a donut run!
    {
    iDonutRunCountDown = 120;  // About 2 seconds
    }

  if (iDonutRunCountDown)
    {
    iDonutRunCountDown--;
    if (!iDonutRunCountDown)
      MakeFlyingDonutSprites();
    }
}

/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/

void ReadJoyStick ( void )
{
  JOYINFOEX JoyInfoEx;

  // In case the call to joyGetPosEx fails (for reasons
  // such as the user doesn't have a joystick), set the 
  // defaults to benign values

  giJoyPos  = JOYDIR_CENTER;
  gbButton1 = FALSE;
  gbButton2 = FALSE;

  // Get the joystick's X-axis and buttons
  JoyInfoEx.dwSize = sizeof(JoyInfoEx);
  JoyInfoEx.dwFlags = JOY_RETURNX | JOY_RETURNBUTTONS;
  // We will always use Joystick #1
  if (JOYERR_NOERROR == joyGetPosEx ( JOYSTICKID1, &JoyInfoEx ))
    {
    // Check for the ranges to be at least halfway left
    // or right and convert into our constants
    if (JoyInfoEx.dwXpos < 16384)
      giJoyPos = JOYDIR_LEFT;
    else
      if (JoyInfoEx.dwXpos > 65535-16384)
        giJoyPos = JOYDIR_RIGHT;

    // Read the buttons
    gbButton1 = (BOOL)(JoyInfoEx.dwButtons & JOY_BUTTON1);
    gbButton2 = (BOOL)(JoyInfoEx.dwButtons & JOY_BUTTON2);
    }
}

/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/

void WINDONUT_GameHeartBeat()
{
  if (glpMasterSprite)
    {
    int i;
    int iState;

    // First, you calculate the position/status of all the sprites

    ReadJoyStick ();
    FigureShipPosition();
    FigureBulletPositions();
    FigureCollisions();

    // Second, you animate the sprites (which will also move the sprites
    // according to their direction.

    // Animate your ship
    SPRITEHIGH_Animate (glpMasterSprite, SPRITE_SHIP);

    // Animate the flying donuts
    for ( i = 0; i < NUMDONUTS; i++ )
      SPRITEHIGH_Animate (glpMasterSprite, i+SPRITE_DONUTS);

    // For bullets and Explosions, we use the ActiveState as a lifetime
    // counter: When the counter is zero, the sprite goes away.
    if (iState = SPRITEHIGH_GetActiveState ( glpMasterSprite, SPRITE_EXPLOSION))
      {
      SPRITEHIGH_Animate (glpMasterSprite, SPRITE_EXPLOSION);
      SPRITEHIGH_SetActiveState ( glpMasterSprite, SPRITE_EXPLOSION, iState-1 );
      }

    for ( i = 0; i < NUMSHOTS; i++ )
      if (iState = SPRITEHIGH_GetActiveState ( glpMasterSprite, SPRITE_SHOTS+i))
        {
        SPRITEHIGH_Animate (glpMasterSprite, i+SPRITE_SHOTS);
        SPRITEHIGH_SetActiveState ( glpMasterSprite, SPRITE_SHOTS + i, iState-1 );
        }

    // Third, we draw the playfield to the back buffer.

    // Blank out the background (optional for this game since
    // we fill the entire background with the bitmap, but this
    // is a demo app, right?)
    DIRECTDRAW_FloodFill (glpBackBuffer, 0);

    // Draw the background to fill the screen
    SPRITEHIGH_Display (glpMasterSprite, SPRITE_BACKGROUND);

    // Draw the donuts
    for ( i = 0; i < NUMDONUTS; i++ )
      SPRITEHIGH_Display (glpMasterSprite, i+SPRITE_DONUTS);

    // Draw the bullets
    for ( i = 0; i < NUMSHOTS; i++ )      
      SPRITEHIGH_Display (glpMasterSprite, i+SPRITE_SHOTS);

    // Draw the spaceship
    SPRITEHIGH_Display (glpMasterSprite, SPRITE_SHIP);

    // Draw the explosion (if there is one)
    SPRITEHIGH_Display (glpMasterSprite, SPRITE_EXPLOSION);

    // Fourth and finally, we flip the back buffer to the front buffer
    DIRECTDRAW_FlipBackToFront (glpFrontBuffer);
    }
}

/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/

BOOL WINDONUT_InitGame (void)
{

  if (glpDirectSound = DIRECTSOUND_Enable())
    {
    glpSoundBackground = DIRECTSOUND_LoadWave   ( glpDirectSound, "e:\\windonut2\\background.wav" );
    glpSoundFire       = DIRECTSOUND_LoadWave   ( glpDirectSound, "e:\\windonut2\\fire.wav" );
    glpSoundExplosion  = DIRECTSOUND_LoadWave   ( glpDirectSound, "e:\\windonut2\\explode.wav" );
    glpSoundThrust     = DIRECTSOUND_LoadWave   ( glpDirectSound, "e:\\windonut2\\thrust.wav" );
    glpSoundBackground->bLooped = TRUE;
    glpSoundThrust->bLooped = TRUE;

    DIRECTSOUND_Play ( glpDirectSound, glpSoundBackground );
    }
  else
    {
    return FALSE;
    }

  if (glpDirectDraw =
      DIRECTDRAW_Enable( 640,       // X res
                         480,       // Y res
                         8,         // Color bitdepth
                         0)) // VRAM needed
    {
    LPDIRECTDRAWSURFACE lpSurfaces[2];

    if(DIRECTDRAW_CreateFlippingSurface(glpDirectDraw, 1, lpSurfaces))
      {
      RECT rClip = {0, 0, 640, 480};

      glpFrontBuffer = lpSurfaces[0];
      glpBackBuffer  = lpSurfaces[1];

      glpMasterSprite = SPRITEHIGH_CreateCompositeSprite
                            ( glpDirectDraw,              // Direct Draw Object
                              glpFrontBuffer,             // Owner of the palette
                              &glpPalette,                // The global palette
                              3+NUMDONUTS+NUMSHOTS,       // Explostion Paddle and Background and peices
                              "WINDONUT.BMP",             // Filename of bitmap
                              glpBackBuffer,              // Pointer to back buffer
                              0xff, 0xff);                // Clear color range (index 0)
      if (glpMasterSprite)
        {
        MakeFlyingDonutSprites ();
        MakeDonutDestroyingSpaceShipSprite();
        MakeDonutBlasterBulletSprites();
        MakeExplosionSprite();
        MakeBackGroundSprite();
        return TRUE;
        }
      else
        {
        glpDirectDraw->lpVtbl->Release( glpDirectDraw );
        glpDirectDraw = NULL;
        }
      }
    }

  return FALSE;  // Failed!
}

/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/

void MakeFlyingDonutSprites ( void )
{
  int i; 
  RECT rClip = { 0, 0, 640, 480 };

  for ( i = 0; i < NUMDONUTS; i++ )
    {
    int iRandX, iRandY;
    int iRandXDir, iRandYDir;

    SPRITEHIGH_DefineSprite
      ( glpMasterSprite,     // Composite Sprite
        i+SPRITE_DONUTS,     // Sprite number
        rand()%(640-64),     // Sprite position on playfield
        rand()%(480-64),     // Sprite position on playfield
        0,                   // Position and size of the sprite in
        480,                 // the low-level sprite
        64,                  // Size
        64,                  // Size
        60,                   // Number of frames for sprite (in case it is
                             // animated. Each frame must have the same Y value,
                             // and placed one after another
        10,                  // Number of frames per row
        rand()%60,           // Current frame to display
        1,                   // Animation rate
        SPRITE_DIR_DOWN,     // Direction
        1,                   // Velocity
        TRUE,                // Wrap
        &rClip);             // Unused

    iRandX = (rand()%400);
    iRandY = (rand()%400);

    iRandXDir  = (rand()%2) ? SPRITE_DIR_RIGHT : SPRITE_DIR_LEFT;
    iRandYDir  = (rand()%2) ? SPRITE_DIR_UP    : SPRITE_DIR_DOWN;

    SPRITEHIGH_SetDirection
      (glpMasterSprite,     // Composite Sprite
       i+SPRITE_DONUTS,
       SPRITE_DIR_CUSTOM,
       iRandX, iRandY,
       iRandXDir,
       iRandYDir);

    SPRITEHIGH_SetActiveState ( glpMasterSprite, 
                                i+SPRITE_DONUTS, 
                                TRUE );
    }  // end for
}

/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/

void  MakeDonutBlasterBulletSprites(void)
{
  int i;
  RECT rClip = {0, 0, 640, 480};

  for ( i = 0; i < NUMSHOTS; i++ )
    {
    SPRITEHIGH_DefineSprite
      ( glpMasterSprite,     // Composite Sprite
        i+SPRITE_SHOTS,      // Sprite number
        1000,                // Sprite position on playfield
        1000,                // Sprite position on playfield
        0,                   // Position and size of the sprite in
        944,                 // the low-level sprite
        4,                   // Size
        4,                   // Size
        1,                   // Number of frames for sprite (in case it is
                             // animated. Each frame must have the same Y value,
                             // and placed one after another
        1,                   // Number of frames per row
        0,                   // Current frame to display
        0,                   // Animation rate
        SPRITE_DIR_CUSTOM,   // Direction
        8,                   // Velocity
        TRUE,                // Wrap
        &rClip);             // Unused
    SPRITEHIGH_SetActiveState ( glpMasterSprite, SPRITE_SHOTS + i, FALSE );
    }
}

/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/

void MakeDonutDestroyingSpaceShipSprite(void)
{
  RECT rClip = { 0, 0, 640, 480 };

  SPRITEHIGH_DefineSprite
    (glpMasterSprite,     // Composite Sprite
     SPRITE_SHIP,       // Sprite number
     300,                 // Sprite position on playfield
     220,                 // Sprite position on playfield
     0,                   // Position and size of the sprite in
     864,                 // the low-level sprite
     40,                  // Size
     40,                  // Size
     32,                   // Number of frames for sprite (in case it is
                          // animated. Each frame must have the same Y value,
                          // and placed one after another
     16,                   // Number of frames per row
     0,                   // Current frame to display
     0,                   // Animation rate
     SPRITE_DIR_CUSTOM,   // Direction
     0,                   // Unused
     TRUE,                // Wrap
     &rClip);             // Full screen

  SPRITEHIGH_SetCurrentXDirection ( glpMasterSprite, SPRITE_SHIP, SPRITE_DIR_LEFT);
  SPRITEHIGH_SetCurrentYDirection ( glpMasterSprite, SPRITE_SHIP, SPRITE_DIR_UP);
  SPRITEHIGH_SetCurrentXVelocity  ( glpMasterSprite, SPRITE_SHIP, 0);
  SPRITEHIGH_SetCurrentYVelocity  ( glpMasterSprite, SPRITE_SHIP, 0);
}

/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/

void MakeExplosionSprite(void)
{
  RECT rClip = { 0, 0, 640, 480 };

  SPRITEHIGH_DefineSprite
    (glpMasterSprite,     // Composite Sprite
     SPRITE_EXPLOSION,    // Sprite number
     300,                 // Sprite position on playfield
     220,                 // Sprite position on playfield
     0,                   // Position and size of the sprite in
     948,                 // the low-level sprite
     64,                  // Size
     64,                  // Size
     10,                  // Number of frames for sprite (in case it is
                          // animated. Each frame must have the same Y value,
                          // and placed one after another
     10,                  // Number of frames per row
     0,                   // Current frame to display
     1,                   // Animation rate
     SPRITE_DIR_STOPPED,  // Direction
     0,                   // Unused
     TRUE,                // Wrap
     &rClip);             // Full screen

  SPRITEHIGH_SetActiveState ( glpMasterSprite, SPRITE_EXPLOSION, FALSE );
}

/*********************************************************************
*                                                                    *
*                                                                    *
*                                                                    *
*********************************************************************/

void MakeBackGroundSprite( void )
{
  RECT rClip = { 0, 0, 640, 480 };

  SPRITEHIGH_DefineSprite
    (glpMasterSprite,     // Composite Sprite
     SPRITE_BACKGROUND,   // Sprite number
     0,                   // Sprite position on playfield
     0,                   // Sprite position on playfield
     0,                   // Position and size of the sprite in
     0,                   // the low-level sprite
     640,                 // Sprite size
     480,                 // Sprite size
     1,                   // Number of frames for sprite (in case it is
                          // animated. Each frame must have the same Y value,
                          // and placed one after another
     1,                   // Number of frames per row
     0,                   // Current frame to display
     0,                   // Animation rate
     SPRITE_DIR_STOPPED,  // Direction
     0,                   // Unused
     FALSE,               // Unused
     &rClip);             // Full screen
}

