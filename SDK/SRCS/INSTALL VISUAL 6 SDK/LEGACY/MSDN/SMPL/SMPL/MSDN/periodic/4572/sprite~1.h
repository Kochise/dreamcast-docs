// SPRITEHIGH.H: Boring memory manager stuff

#ifndef _H_FILE_SPRITEHIGH
#define _H_FILE_SPRITEHIGH

typedef enum
  {
  SPRITE_DIR_STOPPED,
  SPRITE_DIR_UP,
  SPRITE_DIR_DOWN,
  SPRITE_DIR_LEFT,
  SPRITE_DIR_RIGHT,
  SPRITE_DIR_UPLEFT,
  SPRITE_DIR_UPRIGHT,
  SPRITE_DIR_DOWNLEFT,
  SPRITE_DIR_DOWNRIGHT,
  SPRITE_DIR_CUSTOM
  };

typedef struct tagSPRITEHIGH
  {
  BOOL  bActive;          // Is this sprite active or unused?

  int   xPos;             // Sprite position on playfield
  int   yPos;             // Sprite position on playfield

  int   xPosInSpriteLow;  // Position and size of the sprite in
  int   yPosInSpriteLow;  // the low-level sprite
  int   xFrameSize;       // There can be multiple frames
  int   yFrameSize;       // for animated sprites

  int   iNumberOfFrames;  // Number of frames for sprite (in case it is
                          // animated. Each frame must have the same Y value,
                          // and placed one after another
  int   iFramesPerRow;    // Number of frames per row
  int   iCurrentFrame;    // Current frame to display
  int   iAnimateFrameRate; // Frequency of frame updates
  int   iAnimateFrameRateCount; // Counter for managing above

  int   iDirection;       // See enum above
  int   iVelocity;        // Number of pixels to move sprite

                          // Custom Direction Movement. Negative moves object up,left
                          // positive moves right, down
  int   iXVelocity;       // Horizontal velocity, in hundreds, i.e. 3.14 = 314
  int   iYVelocity;       // Vertical Velocity, in hundreds
  int   iXVelocityCount;  // Horizontal velocity count
  int   iYVelocityCount;  // Vertical Velocity
  int   iXDir;            // Horizontal direction (SPRITE_DIR_LEFT or SPRITE_DIR_RIGHT)
  int   iYDir;            // Horizontal direction (SPRITE_DIR_UP or SPRITE_DIR_DOWN)

  BOOL  bWrap;            // Wrap around when edge of screen hit?

  RECT  rClipRect;        // Where on the screen this sprite can live

  LPSPRITELOW   lpSpriteLow;    // The low-level sprite this is based on
  }
SPRITEHIGH, *LPSPRITEHIGH;

typedef struct tagSPRITEHIGHCOMP
  {
  LPSPRITELOW   lpSpriteLow;    // The low-level sprite
  int           iNumSprites;    // Number of sprites living in this sprite
  LPSPRITEHIGH  lpSpriteArray;  // Array of those sprites
  }
SPRITEHIGHCOMP, *LPSPRITEHIGHCOMP;

LPSPRITEHIGHCOMP SPRITEHIGH_CreateCompositeSprite( LPDIRECTDRAW        lpDirectDraw,
                                               LPDIRECTDRAWSURFACE lpFrontBuffer,
                                               LPDIRECTDRAWPALETTE *lplpPalette,
                                               int                 iNumSprites,
                                               LPSTR               szFileName, 
                                               LPDIRECTDRAWSURFACE lpHostSurface,
                                               DWORD               dwColorSpaceLowValue,
                                               DWORD               dwColorSpaceHighValue);

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
                              int           iFramesPerRow,    // Number of frames per row
                              int           iCurrentFrame,    // Current frame to display
                              int           iAnimateFrameRate,  // Animation rate

                              int           iDirection,       // See enum above
                              int           iVelocity,        // Number of pixels to move sprite
                              BOOL          bWrap,            // Wrap around when edge of screen hit?
                              LPRECT        lprClipRect);     // Clipping rect

void SPRITEHIGH_Display( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                         int           iSpriteNum );       // Sprite number

void SPRITEHIGH_SetPos( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                        int           iSpriteNum,       // Sprite number
                        int           x,
                        int           y );

void SPRITEHIGH_Animate( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                         int           iSpriteNum);       // Sprite number

int SPRITEHIGH_GetWidth( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                          int           iSpriteNum );       // Sprite number

int SPRITEHIGH_GetHeight( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                          int           iSpriteNum );       // Sprite number

void SPRITEHIGH_SetDirection( LPSPRITEHIGHCOMP  lpSpriteHighComp, // Composite Sprite
                              int           iSpriteNum,   // Sprite number
                              int           iDirection,   // Direction from ENUM above
                              int           iXVelocity,   // Speed in hundreds (3.14 = 314)
                              int           iYVelocity,   // Speed in hundreds
                              int           iXDir,        // Horizontal direction (SPRITE_DIR_LEFT or SPRITE_DIR_RIGHT) 
                              int           iYDir);       // Horizontal direction (SPRITE_DIR_UP or SPRITE_DIR_DOWN)    

void SPRITEHIGH_SetVelocity ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                              int           iSpriteNum,       // Sprite number
                              int           iVelocity);        // Velocity

void SPRITEHIGH_SetCurrentFrame ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                  int           iSpriteNum,       // Sprite number
                                  int           iCurrentFrame);   // Frame

void SPRITEHIGH_NextFrame ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                            int           iSpriteNum);       // Sprite number

void SPRITEHIGH_PrevFrame ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                            int           iSpriteNum);       // Sprite number

int SPRITEHIGH_GetCurrentFrame  ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                  int           iSpriteNum);       // Sprite number


int SPRITEHIGH_GetCurrentXDirection ( LPSPRITEHIGHCOMP  lpSpriteHighComp,      // Composite Sprite
                                      int           iSpriteNum);       // Sprite number
int SPRITEHIGH_GetCurrentYDirection ( LPSPRITEHIGHCOMP  lpSpriteHighComp,      // Composite Sprite
                                      int           iSpriteNum);       // Sprite number
int SPRITEHIGH_GetCurrentXVelocity  ( LPSPRITEHIGHCOMP  lpSpriteHighComp,      // Composite Sprite
                                      int           iSpriteNum);       // Sprite number
int SPRITEHIGH_GetCurrentYVelocity  ( LPSPRITEHIGHCOMP  lpSpriteHighComp,      // Composite Sprite
                                      int           iSpriteNum);       // Sprite number

void SPRITEHIGH_SetCurrentXDirection ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                       int           iSpriteNum,       // Sprite number
                                       int           iXDir);
void SPRITEHIGH_SetCurrentYDirection ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                       int           iSpriteNum,       // Sprite number
                                       int           iYDir);
void SPRITEHIGH_SetCurrentXVelocity  ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                       int           iSpriteNum,       // Sprite number
                                       int           iXVelocity);
void SPRITEHIGH_SetCurrentYVelocity  ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                       int           iSpriteNum,       // Sprite number
                                       int           iYVelocity);

int SPRITEHIGH_GetActiveState  ( LPSPRITEHIGHCOMP  lpSpriteHighComp,      // Composite Sprite
                                 int           iSpriteNum);        // Sprite number

void SPRITEHIGH_SetActiveState ( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                                 int           iSpriteNum,       // Sprite number
                                 BOOL          bActive); 

int  SPRITEHIGH_GetXPos( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                         int           iSpriteNum);       // Sprite number

int  SPRITEHIGH_GetYPos( LPSPRITEHIGHCOMP  lpSpriteHighComp,     // Composite Sprite
                         int           iSpriteNum);       // Sprite number

BOOL SPRITEHIGH_DoTheseCollide( LPSPRITEHIGHCOMP  lpSpriteHighComp1,     // Composite Sprite
                                int           iSpriteNum1,       // Sprite number
                                LPSPRITEHIGHCOMP  lpSpriteHighComp2,     // Composite Sprite
                                int           iSpriteNum2);      // Sprite number


#endif
