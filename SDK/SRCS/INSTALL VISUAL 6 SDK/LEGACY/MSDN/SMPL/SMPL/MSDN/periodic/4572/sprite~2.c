// SPRITELOW.C:  Low level sprite suff- Communicating with DirectDraw

#include "windonut.h"

/***********************************************************************

***********************************************************************/

LPSPRITELOW SPRITELOW_CreateSprite( LPDIRECTDRAW        lpDirectDraw,
                                    LPDIRECTDRAWSURFACE lpFrontBuffer,
                                    LPDIRECTDRAWPALETTE *lplpPalette,
                                    int                 xPos, 
                                    int                 yPos, 
                                    LPSTR               szFileName, 
                                    LPDIRECTDRAWSURFACE lpHostSurface,
                                    DWORD               dwColorSpaceLowValue,
                                    DWORD               dwColorSpaceHighValue)
{
  int               iCX, iCY;
  LPDIRECTDRAWSURFACE lpSurface;

  // Allocate the memory for this sprite
  LPSPRITELOW lpSpriteLow = MEMORY_New (sizeof(SPRITELOW));

  // Create the surface by passing NULL as the lpSurface
  lpSurface = DIRECTDRAW_CreateSurfaceFromBitmap
                ( lpDirectDraw, 
                  lpFrontBuffer,  // Owner of the palette
                  lplpPalette,    // the palette
                  szFileName, 
                  &iCX, 
                  &iCY, 
                  NULL,
                  dwColorSpaceLowValue,
                  dwColorSpaceHighValue  );

  if (lpSurface) 
    {
    // Fill in the sprite structure

    lpSpriteLow->iCX          = iCX;
    lpSpriteLow->iCY          = iCY;
    lpSpriteLow->iX           = xPos;
    lpSpriteLow->iY           = yPos;
    lpSpriteLow->lpDirectDraw  = lpDirectDraw;
    lpSpriteLow->lpSurface     = lpSurface;
    lpSpriteLow->lpHostSurface = lpHostSurface;

    return lpSpriteLow;
    }
  else
    {
    MEMORY_Delete(lpSpriteLow);
    return NULL;
    }
}

/***********************************************************************

***********************************************************************/

BOOL SPRITELOW_Display ( LPSPRITELOW lpSpriteLow )
{
  RECT    rect;
  HRESULT ddrval;
  int     iTries;

  rect.left  = 0;
  rect.top   = 0;
  rect.right = lpSpriteLow->iCX;
  rect.bottom= lpSpriteLow->iCY;

  iTries = 0;

  while (iTries < 50)
    {
    ddrval = lpSpriteLow->lpHostSurface->lpVtbl->BltFast( lpSpriteLow->lpHostSurface,
                                                          lpSpriteLow->iX,
                                                          lpSpriteLow->iY,
                                                          lpSpriteLow->lpSurface,
                                                          &rect, 
                                                          TRUE );
    if ( DD_OK == ddrval ) break;
    iTries++;
    }

  if (50 == iTries) MessageBeep(0);
  return TRUE;
}

/***********************************************************************

***********************************************************************/

BOOL SPRITELOW_DisplayEx ( LPSPRITELOW lpSpriteLow, 
                           int iDestX, 
                           int iDestY,
                           int iSrcX, 
                           int iSrcY, 
                           int iSrcDX, 
                           int iSrcDY)
{
  RECT    rect;
  HRESULT ddrval;
  int     iTries;

  if ((iDestX + iSrcDX) > 640) iSrcDX = 640-iDestX;
  if ((iDestY + iSrcDY) > 480) iSrcDY = 480-iDestY;

  if (iDestY < 0)
    {
    iSrcY  -= iDestY;
    iSrcDY += iDestY;
    iDestY = 0;
    }


  if (iDestX < 0)
    {
    iSrcX  -= iDestX;
    iSrcDX += iDestX;
    iDestX = 0;
    }

  rect.left  = iSrcX;
  rect.top   = iSrcY+1;
  rect.right = rect.left + iSrcDX;
  rect.bottom= rect.top + iSrcDY;

  if ((rect.top == rect.bottom) || (rect.left == rect.right)) return TRUE;
  iTries = 0;

  while (iTries < 50)
    {
    ddrval = lpSpriteLow->lpHostSurface->lpVtbl->BltFast( lpSpriteLow->lpHostSurface,
                                                          iDestX,
                                                          iDestY,
                                                          lpSpriteLow->lpSurface,
                                                          &rect, 
                                                          TRUE );
    if ( DD_OK == ddrval ) break;
    iTries++;
    }

  if (50 == iTries) 
    {

    }
  return TRUE;
}

/***********************************************************************

***********************************************************************/

BOOL SPRITELOW_SetPos ( LPSPRITELOW lpSpriteLow, int x, int y )
{
  lpSpriteLow->iX = x;
  lpSpriteLow->iY = y;
  return TRUE;
}
