// SPRITELOW.H: Low-Level Sprite Sutff

#ifndef _H_FILE_SPRITELOW
#define _H_FILE_SPRITELOW

typedef struct tagSPRITELOW
  {
  int                   iCX;
  int                   iCY;
  int                   iX;
  int                   iY;
  LPDIRECTDRAW          lpDirectDraw;
  LPDIRECTDRAWSURFACE   lpSurface;
  LPDIRECTDRAWSURFACE   lpHostSurface;
  }
SPRITELOW, *LPSPRITELOW;

LPSPRITELOW SPRITELOW_CreateSprite( LPDIRECTDRAW        lpDirectDraw,
                                    LPDIRECTDRAWSURFACE lpFrontBuffer,
                                    LPDIRECTDRAWPALETTE *lplpPalette,
                                    int                 xPos, 
                                    int                 yPos, 
                                    LPSTR               szFileName, 
                                    LPDIRECTDRAWSURFACE lpHostSurface,
                                    DWORD               dwColorSpaceLowValue,
                                    DWORD               dwColorSpaceHighValue);
BOOL SPRITELOW_Display ( LPSPRITELOW lpSpriteLow );
BOOL SPRITELOW_DisplayEx ( LPSPRITELOW lpSpriteLow, 
                           int iDestX, 
                           int iDestY,
                           int iSrcX, 
                           int iSrcY, 
                           int iSrcDX, 
                           int iSrcDY);
BOOL SPRITELOW_SetPos ( LPSPRITELOW lpSpriteLow, int x, int y );

#endif
