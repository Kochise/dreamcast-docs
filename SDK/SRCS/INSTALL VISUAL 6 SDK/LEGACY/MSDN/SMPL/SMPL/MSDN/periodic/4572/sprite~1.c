// SPRITEHIGH.C:  High level sprite suff- moving the sprite automatically, etc

#include "windonut.h"


LPSPRITEHIGHCOMP SPRITEHIGH_CreateCompositeSprite( LPDIRECTDRAW        lpDirectDraw,
                                               LPDIRECTDRAWSURFACE lpFrontBuffer,
                                               LPDIRECTDRAWPALETTE *lplpPalette,
                                               int                 iNumSprites,
                                               LPSTR               szFileName, 
                                               LPDIRECTDRAWSURFACE lpHostSurface,
                                               DWORD               dwColorSpaceLowValue,
                                               DWORD               dwColorSpaceHighValue)
{
  LPSPRITEHIGHCOMP  lpSpriteHighComp;
  int           i;

  // Alloc mem for the SPRITEHIGHCOMP struct

  lpSpriteHighComp = MEMORY_New (sizeof(SPRITEHIGHCOMP));
  if (!lpSpriteHighComp) return NULL;

  // Alloc mem for each individual sprite

  lpSpriteHighComp->iNumSprites = iNumSprites;
  lpSpriteHighComp->lpSpriteArray = MEMORY_New (sizeof(SPRITEHIGH)*iNumSprites);
  if (!lpSpriteHighComp)
    {
    MEMORY_Delete(lpSpriteHighComp);
    return NULL;
    }

  // Go get the low-level sprite

  lpSpriteHighComp->lpSpriteLow = 
    SPRITELOW_CreateSprite( lpDirectDraw,   // Pointer to DirectDraw sprite
                            lpFrontBuffer,  // Owner of the palette
                            lplpPalette,
                            0, 0,           // Position of low-level sprite (unused)
                            szFileName,     // Composite bitmap with images
                            lpHostSurface,  // Host surface
                            dwColorSpaceLowValue,  // Clear color range start
                            dwColorSpaceHighValue);// Clear color range end

  if (!lpSpriteHighComp->lpSpriteLow)
    {
    MEMORY_Delete(lpSpriteHighComp->lpSpriteArray);
    MEMORY_Delete(lpSpriteHighComp);
    return NULL;
    }

  // Initialize the array of sprites to be empty

  for ( i = 0; i < iNumSprites; i++)
    {
    lpSpriteHighComp->lpSpriteArray[i].lpSpriteLow     = lpSpriteHighComp->lpSpriteLow;
    lpSpriteHighComp->lpSpriteArray[i].bActive         = FALSE;
    lpSpriteHighComp->lpSpriteArray[i].iNumberOfFrames = 1;
    lpSpriteHighComp->lpSpriteArray[i].iFramesPerRow   = 1;
    lpSpriteHighComp->lpSpriteArray[i].iCurrentFrame   = 0;
    lpSpriteHighComp->lpSpriteArray[i].iDirection      = SPRITE_DIR_STOPPED;
    lpSpriteHighComp->lpSpriteArray[i].iVelocity       = 1; 
    lpSpriteHighComp->lpSpriteArray[i].bWrap           = TRUE;
    lpSpriteHighComp->lpSpriteArray[i].iAnimateFrameRate = 1;
    lpSpriteHighComp->lpSpriteArray[i].iAnimateFrameRateCount = 0;
    }

  return lpSpriteHighComp;
}


void SPRITEHIGH_DefineSprite( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite

                              int           iSpriteNum,       // Sprite number

                              int           xPos,             // Sprite position on playfield
                              int           yPos,             // Sprite position on playfield

                              int           xPosInSpriteLow,  // Position and size of the sprite in
                              int           yPosInSpriteLow,  // the low-level sprite
                              int           xFrameSize,       // There can be multiple frames
                              int           yFrameSize,       // for animated sprites

                              int           iNumberOfFrames,  // Number of frames for sprite (in case it is
                                                              // animated. Each frame must have the same Y value,
                                                              // and placed one after another
                              int           iFramesPerRow,    // Number of frames in each row
                              int           iCurrentFrame,    // Current frame to display
                              int           iAnimateFrameRate,  // Animation rate

                              int           iDirection,       // See enum above
                              int           iVelocity,        // Number of pixels to move sprite
                              BOOL          bWrap,            // Wrap around when edge of screen hit?
                              LPRECT        lprClipRect)      // Clipping rect

{
  if (iSpriteNum < lpSpriteHighComp->iNumSprites)
    {
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].xPos             = xPos            ;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].yPos             = yPos            ;
                                                                              
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].xPosInSpriteLow  = xPosInSpriteLow ;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].yPosInSpriteLow  = yPosInSpriteLow ;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].xFrameSize       = xFrameSize      ;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].yFrameSize       = yFrameSize      ;
                                                                              
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iNumberOfFrames  = iNumberOfFrames ;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iFramesPerRow    = iFramesPerRow   ;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iCurrentFrame    = iCurrentFrame   ;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iAnimateFrameRate= iAnimateFrameRate;
                                                                              
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iDirection       = iDirection      ;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity        = iVelocity       ;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].bWrap            = bWrap           ;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].rClipRect        = *lprClipRect    ;

    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXVelocity       = 0;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYVelocity       = 0;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXVelocityCount  = 0;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYVelocityCount  = 0;

    lpSpriteHighComp->lpSpriteArray[iSpriteNum].bActive          = TRUE;
    }
}

void SPRITEHIGH_Display( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                         int           iSpriteNum )       // Sprite number
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    if (lpSpriteHighComp->lpSpriteArray[iSpriteNum].bActive)
      SPRITELOW_DisplayEx ( lpSpriteHighComp->lpSpriteLow, 
                            lpSpriteHighComp->lpSpriteArray[iSpriteNum].xPos,
                            lpSpriteHighComp->lpSpriteArray[iSpriteNum].yPos,
                            lpSpriteHighComp->lpSpriteArray[iSpriteNum].xPosInSpriteLow+
                              (lpSpriteHighComp->lpSpriteArray[iSpriteNum].iCurrentFrame%
                              lpSpriteHighComp->lpSpriteArray[iSpriteNum].iFramesPerRow)*
                              lpSpriteHighComp->lpSpriteArray[iSpriteNum].xFrameSize,
                            lpSpriteHighComp->lpSpriteArray[iSpriteNum].yPosInSpriteLow+
                              (lpSpriteHighComp->lpSpriteArray[iSpriteNum].iCurrentFrame/
                              lpSpriteHighComp->lpSpriteArray[iSpriteNum].iFramesPerRow)*
                              lpSpriteHighComp->lpSpriteArray[iSpriteNum].yFrameSize,
                            lpSpriteHighComp->lpSpriteArray[iSpriteNum].xFrameSize,
                            lpSpriteHighComp->lpSpriteArray[iSpriteNum].yFrameSize);

}

int SPRITEHIGH_GetXPos( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                         int           iSpriteNum)       // Sprite number
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    return lpSpriteHighComp->lpSpriteArray[iSpriteNum].xPos;
}

int SPRITEHIGH_GetYPos( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                         int           iSpriteNum)       // Sprite number
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    return lpSpriteHighComp->lpSpriteArray[iSpriteNum].yPos;
}

void SPRITEHIGH_SetPos( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                        int           iSpriteNum,       // Sprite number
                        int           x,
                        int           y )
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    {
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].xPos = x;
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].yPos = y;
    }
}

int SPRITEHIGH_GetWidth( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                          int           iSpriteNum )       // Sprite number
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    return lpSpriteHighComp->lpSpriteArray[iSpriteNum].xFrameSize;
  else
    return -1;
}

int SPRITEHIGH_GetHeight( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                          int           iSpriteNum )       // Sprite number
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    return lpSpriteHighComp->lpSpriteArray[iSpriteNum].yFrameSize;
  else
    return -1;
}

#define MOVEUP   bCanMove &=                                        \
MoveUp( &x, &y, dx, dy,                                             \
        lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity,          \
        &(lpSpriteHighComp->lpSpriteArray[iSpriteNum].rClipRect),       \
        bWrap )

#define MOVEDOWN bCanMove &=                                          \
MoveDown( &x, &y, dx, dy,                                             \
          lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity,          \
        &(lpSpriteHighComp->lpSpriteArray[iSpriteNum].rClipRect),         \
        bWrap )

#define MOVELEFT bCanMove &=                                          \
MoveLeft( &x, &y, dx, dy,                                             \
          lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity,          \
        &(lpSpriteHighComp->lpSpriteArray[iSpriteNum].rClipRect),         \
        bWrap )

#define MOVERIGHT bCanMove &=                                          \
MoveRight( &x, &y, dx, dy,                                             \
          lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity,           \
        &(lpSpriteHighComp->lpSpriteArray[iSpriteNum].rClipRect),          \
        bWrap )

BOOL MoveUp( LPINT px, LPINT py, 
             int dx, int dy, 
             int iVelocity, 
             LPRECT prClip, 
             BOOL bWrap )
{
  if ((*py + dy - iVelocity) < prClip->top)
    if (!bWrap)
      return FALSE;
    else
      *py = prClip->bottom + dy;

  *py -= iVelocity;

  return TRUE;
}

BOOL MoveDown( LPINT px, LPINT py, 
               int dx, int dy, 
               int iVelocity, 
               LPRECT prClip, 
               BOOL bWrap )
{
  if ((*py + iVelocity) > prClip->bottom)
    {
    if (!bWrap)
      return FALSE;
    else
      *py = prClip->top - dy;
    }
  else
    {
    *py += iVelocity;
    }

  return TRUE;
}

BOOL MoveLeft( LPINT px, LPINT py, 
               int dx, int dy, 
               int iVelocity, 
               LPRECT prClip, 
               BOOL bWrap )
{
  if ((*px + dx - iVelocity) < prClip->left)
    if (!bWrap)
      return FALSE;
    else
      *px = prClip->right + dx;

  *px -= iVelocity;

  return TRUE;
}

BOOL MoveRight( LPINT px, LPINT py, 
                int dx, int dy, 
                int iVelocity, 
                LPRECT prClip, 
                BOOL bWrap )
{
  if ((*px + iVelocity) > prClip->right)
    if (!bWrap)
      return FALSE;
    else
      *px -= (prClip->right - prClip->left + dx);

  *px += iVelocity;

  return TRUE;
}

#define INT_ABS(a) (max(a,-a))

void SPRITEHIGH_Animate( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                         int           iSpriteNum)       // Sprite number
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    {
    int   x, y, dx, dy; // Sprite's object values
    int   iOldVelocity;
    BOOL  bCanMove;
    BOOL  bWrap = lpSpriteHighComp->lpSpriteArray[iSpriteNum].bWrap;

    if (lpSpriteHighComp->lpSpriteArray[iSpriteNum].bActive)
      {
      // First, pick the frame to use for animation

      if (lpSpriteHighComp->lpSpriteArray[iSpriteNum].iAnimateFrameRate)
        {
        (lpSpriteHighComp->lpSpriteArray[iSpriteNum].iAnimateFrameRateCount)++;
        if (lpSpriteHighComp->lpSpriteArray[iSpriteNum].iAnimateFrameRateCount >
            lpSpriteHighComp->lpSpriteArray[iSpriteNum].iAnimateFrameRate) 
          {
          lpSpriteHighComp->lpSpriteArray[iSpriteNum].iAnimateFrameRateCount = 0;
          SPRITEHIGH_NextFrame ( lpSpriteHighComp, iSpriteNum);
          }
        }

      // Second, move the sprite in it's bounding rect

      x = lpSpriteHighComp->lpSpriteArray[iSpriteNum].xPos;
      y = lpSpriteHighComp->lpSpriteArray[iSpriteNum].yPos;
      dx= lpSpriteHighComp->lpSpriteArray[iSpriteNum].xFrameSize;
      dy= lpSpriteHighComp->lpSpriteArray[iSpriteNum].yFrameSize;

      bCanMove = TRUE;

      switch (lpSpriteHighComp->lpSpriteArray[iSpriteNum].iDirection)
        {
        case SPRITE_DIR_UP       : MOVEUP;             break;
        case SPRITE_DIR_DOWN     : MOVEDOWN;           break;
        case SPRITE_DIR_LEFT     : MOVELEFT;           break;
        case SPRITE_DIR_RIGHT    : MOVERIGHT;          break;
        case SPRITE_DIR_UPLEFT   : MOVELEFT; MOVEUP;   break;
        case SPRITE_DIR_UPRIGHT  : MOVERIGHT;MOVEUP;   break;
        case SPRITE_DIR_DOWNLEFT : MOVELEFT; MOVEDOWN; break;
        case SPRITE_DIR_DOWNRIGHT: MOVERIGHT;MOVEDOWN; break;
        case SPRITE_DIR_CUSTOM   :

          iOldVelocity = lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity;

          // Calculate the "real velocities"

          lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXVelocityCount +=
            lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXVelocity;
          lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYVelocityCount +=
            lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYVelocity;

          // First, move the sprite in the x direction

          lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity = 
            lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXVelocityCount/100;

          if (lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity)
            {
            lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXVelocityCount -=
              100 * lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity;

            if (SPRITE_DIR_LEFT == lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXDir)
              MOVELEFT;
            else
              MOVERIGHT;
            }

          lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity = 
            lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYVelocityCount/100;

          if (lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity)
            {
            lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYVelocityCount -=
              100 * lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity;

            if (SPRITE_DIR_DOWN == lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYDir)
              MOVEDOWN;
            else
              MOVEUP;
            }

          lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity = iOldVelocity;

          break;
          
        }  // end switch

      lpSpriteHighComp->lpSpriteArray[iSpriteNum].xPos = x;
      lpSpriteHighComp->lpSpriteArray[iSpriteNum].yPos = y;

      lpSpriteHighComp->lpSpriteArray[iSpriteNum].bActive = bCanMove;
      } // end if bActive
    }  // end if iNumSprites
}

void SPRITEHIGH_SetDirection( LPSPRITEHIGHCOMP  lpSpriteHighComp, // Composite Sprite
                              int           iSpriteNum,   // Sprite number
                              int           iDirection,   // Direction from ENUM above
                              int           iXVelocity,   // Speed in hundreds (3.14 = 314)
                              int           iYVelocity,   // Speed in hundreds
                              int           iXDir,        // Horizontal direction (SPRITE_DIR_LEFT or SPRITE_DIR_RIGHT) 
                              int           iYDir)        // Horizontal direction (SPRITE_DIR_UP or SPRITE_DIR_DOWN)    
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    {
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iDirection = iDirection;
    if (SPRITE_DIR_CUSTOM == iDirection)
      {
      lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXVelocity = iXVelocity;
      lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYVelocity = iYVelocity;
      lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXVelocityCount = 0;
      lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYVelocityCount = 0;
      lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXDir = iXDir;
      lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYDir = iYDir;
      }
    }
}

void SPRITEHIGH_SetVelocity ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                              int           iSpriteNum,       // Sprite number
                              int           iVelocity)        // Velocity
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iVelocity = iVelocity;
}


void SPRITEHIGH_SetCurrentFrame ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                  int           iSpriteNum,       // Sprite number
                                  int           iCurrentFrame)    // Frame
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iCurrentFrame = iCurrentFrame;
}                                  

int SPRITEHIGH_GetCurrentFrame  ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                  int           iSpriteNum)       // Sprite number

{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    return lpSpriteHighComp->lpSpriteArray[iSpriteNum].iCurrentFrame;
}                                  


void SPRITEHIGH_NextFrame ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                            int           iSpriteNum)       // Sprite number

{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iCurrentFrame = 
      (lpSpriteHighComp->lpSpriteArray[iSpriteNum].iCurrentFrame+1)%
        lpSpriteHighComp->lpSpriteArray[iSpriteNum].iNumberOfFrames;
}                                  

void SPRITEHIGH_PrevFrame ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                            int           iSpriteNum)       // Sprite number

{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iCurrentFrame = 
      (lpSpriteHighComp->lpSpriteArray[iSpriteNum].iCurrentFrame+
       lpSpriteHighComp->lpSpriteArray[iSpriteNum].iNumberOfFrames-1)%
        lpSpriteHighComp->lpSpriteArray[iSpriteNum].iNumberOfFrames;
}                                  

int SPRITEHIGH_GetCurrentXDirection ( LPSPRITEHIGHCOMP  lpSpriteHighComp,      // Composite Sprite
                                      int           iSpriteNum)        // Sprite number
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    return lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXDir;
  else
    return 0;
}

int SPRITEHIGH_GetCurrentYDirection ( LPSPRITEHIGHCOMP  lpSpriteHighComp,      // Composite Sprite
                                      int           iSpriteNum)        // Sprite number
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    return lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYDir;
  else
    return 0;
}

int SPRITEHIGH_GetCurrentXVelocity  ( LPSPRITEHIGHCOMP  lpSpriteHighComp,      // Composite Sprite
                                      int           iSpriteNum)        // Sprite number
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    return lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXVelocity;
  else
    return 0;
}

int SPRITEHIGH_GetCurrentYVelocity  ( LPSPRITEHIGHCOMP  lpSpriteHighComp,      // Composite Sprite
                                      int           iSpriteNum)        // Sprite number
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    return lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYVelocity;
  else
    return 0;
}

void SPRITEHIGH_SetCurrentXDirection ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                       int           iSpriteNum,       // Sprite number
                                       int           iXDir) 
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXDir = iXDir;
}

void SPRITEHIGH_SetCurrentYDirection ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                       int           iSpriteNum,       // Sprite number
                                       int           iYDir) 
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYDir = iYDir;
}

void SPRITEHIGH_SetCurrentXVelocity  ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                       int           iSpriteNum,       // Sprite number
                                       int           iXVelocity) 
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iXVelocity = iXVelocity;
}

void SPRITEHIGH_SetCurrentYVelocity  ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                       int           iSpriteNum,       // Sprite number
                                       int           iYVelocity) 
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].iYVelocity = iYVelocity;
}


int SPRITEHIGH_GetActiveState  ( LPSPRITEHIGHCOMP  lpSpriteHighComp,      // Composite Sprite
                                 int           iSpriteNum)        // Sprite number
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    return lpSpriteHighComp->lpSpriteArray[iSpriteNum].bActive;
  else
    return 0;
}

void SPRITEHIGH_SetActiveState ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                 int           iSpriteNum,       // Sprite number
                                 BOOL          bActive) 
{
  if (iSpriteNum < (lpSpriteHighComp->iNumSprites))
    lpSpriteHighComp->lpSpriteArray[iSpriteNum].bActive = bActive;
}

BOOL SPRITEHIGH_DoTheseCollide( LPSPRITEHIGHCOMP  lpSpriteHighComp1,     // Composite Sprite
                                int           iSpriteNum1,       // Sprite number
                                LPSPRITEHIGHCOMP  lpSpriteHighComp2,     // Composite Sprite
                                int           iSpriteNum2)       // Sprite number
{
  // No bounds checking here for increased speed

  RECT r1 = {lpSpriteHighComp1->lpSpriteArray[iSpriteNum1].xPos,

             lpSpriteHighComp1->lpSpriteArray[iSpriteNum1].yPos,

             lpSpriteHighComp1->lpSpriteArray[iSpriteNum1].xPos+
             lpSpriteHighComp1->lpSpriteArray[iSpriteNum1].xFrameSize,

             lpSpriteHighComp1->lpSpriteArray[iSpriteNum1].yPos+
             lpSpriteHighComp1->lpSpriteArray[iSpriteNum1].yFrameSize};

  RECT r2 = {lpSpriteHighComp1->lpSpriteArray[iSpriteNum2].xPos,

             lpSpriteHighComp1->lpSpriteArray[iSpriteNum2].yPos,

             lpSpriteHighComp1->lpSpriteArray[iSpriteNum2].xPos+
             lpSpriteHighComp1->lpSpriteArray[iSpriteNum2].xFrameSize,

             lpSpriteHighComp1->lpSpriteArray[iSpriteNum2].yPos+
             lpSpriteHighComp1->lpSpriteArray[iSpriteNum2].yFrameSize};

  RECT r;

  return IntersectRect ( &r, &r1, &r2 ); 
}
