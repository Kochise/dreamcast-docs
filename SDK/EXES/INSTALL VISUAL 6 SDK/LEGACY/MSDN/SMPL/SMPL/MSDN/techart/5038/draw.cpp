/*==========================================================================
 *
 *  Copyright (C) 1996 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       draw.cpp
 *  Content:    DirectDraw support for Moby Dick
 *
 ***************************************************************************/
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include "draw.h"
#include "ttfont.h"
#include "resource.h"

LPDIRECTDRAW            lpDD;           
LPDIRECTDRAWSURFACE     lpDDSPrimary;  
LPDIRECTDRAWSURFACE     lpDDSBack;   
LPDIRECTDRAWSURFACE     lpDDS_Map;
// sprites
LPDIRECTDRAWSURFACE     lpDDS_Sprites[NUMSPRITES];    
LPDIRECTDRAWCLIPPER     lpClipper;

LPDIRECTDRAWPALETTE     lpDDPal;     
RECT                    MapRect;
HFONT                   hFont;

/* ******************************************************
   DDLoadBitmap
   create a DirectDrawSurface from a bitmap resource.
  *******************************************************  */

IDirectDrawSurface* DDLoadBitmap(IDirectDraw *pdd, LPCSTR szBitmap, 
                                 int dx, int dy)
  {
  HBITMAP             hbm;
  BITMAP              bm;
  DDSURFACEDESC       ddsd;
  IDirectDrawSurface *pdds;
  HRESULT             ddresult;

  hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, dx, dy, LR_CREATEDIBSECTION);
  if (hbm == NULL)
    return NULL;

  // get size of the bitmap
  GetObject(hbm, sizeof(bm), &bm);   

  // create a DirectDrawSurface for this bitmap
  ZeroMemory(&ddsd, sizeof(ddsd));
  ddsd.dwSize = sizeof(ddsd);
  ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
  ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
  ddsd.dwWidth = bm.bmWidth;
  ddsd.dwHeight = bm.bmHeight;

  ddresult = pdd->CreateSurface(&ddsd, &pdds, NULL);
  if (ddresult != DD_OK) return NULL;

  DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);

  DeleteObject(hbm);
  return pdds;
  }

/* ********************************************************
   DDReLoadBitmap
   Reload a bitmap from resource into a directdraw surface.
  ********************************************************* */

HRESULT DDReLoadBitmap(IDirectDrawSurface *pdds, LPCSTR szBitmap)
{
  HBITMAP             hbm;
  HRESULT             hr;

  //  load the bitmap as a resource
  hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), szBitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

  if (hbm == NULL)
  {
    OutputDebugString("handle is null\n");
    return E_FAIL;
  }
  hr = DDCopyBitmap(pdds, hbm, 0, 0, 0, 0);
  if (hr != DD_OK)
  {
    OutputDebugString("DDCopyBitmap failed\n");
  }
  DeleteObject(hbm);
  return hr;
}

/* ********************************************************
    DDCopyBitmap
    Draw a bitmap into a DirectDrawSurface
  *********************************************************  */

HRESULT DDCopyBitmap(IDirectDrawSurface *pdds, HBITMAP hbm, 
                     int x, int y, int dx, int dy)
  {
  HDC                 hdcImage;
  HDC                 hdc;
  BITMAP              bm;
  DDSURFACEDESC       ddsd;
  HRESULT             hr;

  if (hbm == NULL || pdds == NULL)
      return E_FAIL;

  // make sure this surface is restored.
  pdds->Restore();

  //  select bitmap into a memoryDC so we can use it.
  hdcImage = CreateCompatibleDC(NULL);
  if (!hdcImage)
      OutputDebugString("createcompatible dc failed\n");
  SelectObject(hdcImage, hbm);

  // get size of the bitmap
  GetObject(hbm, sizeof(bm), &bm);    // get size of bitmap
  dx = dx == 0 ? bm.bmWidth  : dx;    // use the passed size, unless zero
  dy = dy == 0 ? bm.bmHeight : dy;

  // get size of surface.
  ddsd.dwSize = sizeof(ddsd);
  ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
  pdds->GetSurfaceDesc(&ddsd);

  if ((hr = pdds->GetDC(&hdc)) == DD_OK)
  {
      StretchBlt(hdc, 0, 0, ddsd.dwWidth, ddsd.dwHeight, hdcImage, x, y, dx, dy, SRCCOPY);
      pdds->ReleaseDC(hdc);
  }
  DeleteDC(hdcImage);
  return hr;
  }

/* ************************************************************
    DDLoadPalette
    Create a DirectDraw palette object from a bitmap resoure
    if the resource does not exist or NULL is passed create a
    default 332 palette.
  ************************************************************* */
IDirectDrawPalette * DDLoadPalette(IDirectDraw *pdd, LPCSTR szBitmap)
  {
  IDirectDrawPalette* ddpal;
  int                 i;
  int                 n;
  int                 fh;
  HRSRC               h;
  LPBITMAPINFOHEADER  lpbi;
  PALETTEENTRY        ape[256];
  RGBQUAD *           prgb;

  //
  // build a 332 palette as the default.
  //
  for (i=0; i<256; i++)
  {
      ape[i].peRed   = (BYTE)(((i >> 5) & 0x07) * 255 / 7);
      ape[i].peGreen = (BYTE)(((i >> 2) & 0x07) * 255 / 7);
      ape[i].peBlue  = (BYTE)(((i >> 0) & 0x03) * 255 / 3);
      ape[i].peFlags = (BYTE)0;
  }

  // get a pointer to the bitmap resource.
  if (szBitmap && (h = FindResource(NULL, szBitmap, RT_BITMAP)))
  {
      lpbi = (LPBITMAPINFOHEADER)LockResource(LoadResource(NULL, h));
      if (!lpbi)
          OutputDebugString("Lock resource failed\n");
      prgb = (RGBQUAD*)((BYTE*)lpbi + lpbi->biSize);

      if (lpbi == NULL || lpbi->biSize < sizeof(BITMAPINFOHEADER))
          n = 0;
      else if (lpbi->biBitCount > 8)
          n = 0;
      else if (lpbi->biClrUsed == 0)
          n = 1 << lpbi->biBitCount;
      else
          n = lpbi->biClrUsed;

      //  a DIB color table has its colors stored BGR not RGB
      //  so flip them around.
      for(i=0; i<n; i++ )
      {
          ape[i].peRed   = prgb[i].rgbRed;
          ape[i].peGreen = prgb[i].rgbGreen;
          ape[i].peBlue  = prgb[i].rgbBlue;
          ape[i].peFlags = 0;
      }
    }
  else if (szBitmap && (fh = _lopen(szBitmap, OF_READ)) != -1)
    {
    BITMAPFILEHEADER bf;
    BITMAPINFOHEADER bi;

    _lread(fh, &bf, sizeof(bf));
    _lread(fh, &bi, sizeof(bi));
    _lread(fh, ape, sizeof(ape));
    _lclose(fh);

    if (bi.biSize != sizeof(BITMAPINFOHEADER))
        n = 0;
    else if (bi.biBitCount > 8)
        n = 0;
    else if (bi.biClrUsed == 0)
        n = 1 << bi.biBitCount;
    else
        n = bi.biClrUsed;

    // A DIB color table has its colors stored BGR not RGB
    // so flip them around.
    for (i=0; i<n; i++ )
      {
      BYTE r = ape[i].peRed;
      ape[i].peRed  = ape[i].peBlue;
      ape[i].peBlue = r;
      }
    }
  pdd->CreatePalette(DDPCAPS_8BIT, ape, &ddpal, NULL);
  return ddpal;
  }

/* ***********************************************************
    DDColorMatch
    Convert an RGB color to a physical color.
    We do this by letting GDI SetPixel() do the color matching
    then we lock the memory and see what it got mapped to.
  ************************************************************ */

DWORD DDColorMatch(IDirectDrawSurface *pdds, COLORREF rgb)
  {
  COLORREF rgbT;
  HDC hdc;
  DWORD dw = CLR_INVALID;
  DDSURFACEDESC ddsd;
  HRESULT hres;

  //  use GDI SetPixel to color match for us
  if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
    rgbT = GetPixel(hdc, 0, 0);             // save current pixel value
    SetPixel(hdc, 0, 0, rgb);               // set our value
    pdds->ReleaseDC(hdc);
    }

  // now lock the surface so we can read back the converted color
  ddsd.dwSize = sizeof(ddsd);
  while ((hres = pdds->Lock(NULL, &ddsd, 0, NULL)) == DDERR_WASSTILLDRAWING)
      ;

  if (hres == DD_OK)
    {
    dw  = *(DWORD *)ddsd.lpSurface;                     // get DWORD
    dw &= (1 << ddsd.ddpfPixelFormat.dwRGBBitCount)-1;  // mask it to bpp
    pdds->Unlock(NULL);
    }

  //  now put the color that was there back.
  if (rgb != CLR_INVALID && pdds->GetDC(&hdc) == DD_OK)
    {
    SetPixel(hdc, 0, 0, rgbT);
    pdds->ReleaseDC(hdc);
    }
  return dw;
  }

/* ****************************************************
    DDSetColorKey
    Set a color key for a surface, given a RGB.
    If you pass CLR_INVALID as the color key, the pixel
    in the upper-left corner will be used.
  ***************************************************** */

HRESULT DDSetColorKey(IDirectDrawSurface *pdds, COLORREF rgb)
{
  DDCOLORKEY          ddck;

  ddck.dwColorSpaceLowValue  = DDColorMatch(pdds, rgb);
  ddck.dwColorSpaceHighValue = ddck.dwColorSpaceLowValue;
  return pdds->SetColorKey(DDCKEY_SRCBLT, &ddck);
}

/* ***************************************
    InitGraphics
    Set up DDraw and the surfaces
  **************************************** */

BOOL InitGraphics(HWND hwnd)
  {
  DDSURFACEDESC ddsd;
  HRESULT       ddrval;
  HDC           hdc;

  // create the main DirectDraw object
  if (DirectDrawCreate( NULL, &lpDD, NULL ) != DD_OK )
    {
    OutputDebugString("Failed to create DirectDraw object");
    return FALSE;
    }

  // set DDraw cooperative level
  if (lpDD->SetCooperativeLevel( hwnd, DDSCL_NORMAL ) != DD_OK )
     return FALSE;

  // Create the primary surface
  ddsd.dwSize = sizeof(ddsd);
  ddsd.dwFlags = DDSD_CAPS ;
  ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
  if (ddrval = lpDD->CreateSurface(&ddsd, &lpDDSPrimary, NULL) != DD_OK)
    {
    OutputDebugString("Failed to create primary surface\n");   
    return FALSE;
    }

  // Create a DirectDraw Palette and associate it with the front buffer
  lpDDPal = DDLoadPalette(lpDD, MAKEINTRESOURCE(IDB_MAP));
  if (lpDDPal)
    {
      ddrval = lpDDSPrimary->SetPalette(lpDDPal);
      if (ddrval != DD_OK)
      {
        OutputDebugString("Failed to set palette\n");
      // if surface is not 8-bit color, an error is returned but 
      //   we carry on without the palette
      }
    }
    else
    {
      OutputDebugString("Failed to load palette\n");
      return FALSE;
    }

  // Create background surface
  lpDDSBack = DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_MAP), 0, 0);
  if (lpDDSBack == NULL) 
    {
    OutputDebugString("Failed to create background surface\n");   
    return FALSE;
    }
  lpDDSBack->GetSurfaceDesc(&ddsd);

  // save dimensions of background image
  SetRect(&MapRect, 0, 0, ddsd.dwWidth, ddsd.dwHeight);

  // create the ocean chart
  lpDDS_Map =
      DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_MAP), 0, 0);    
    // get a display font
  lpDDS_Map->GetDC(&hdc);
  hFont = EzCreateFont(hdc, "Times New Roman", 150, 0, EZ_ATTR_ITALIC, 0);
  SelectObject(hdc, hFont);
  SetBkMode(hdc, TRANSPARENT);

  // put a legend on the background map
  TextOut(hdc, 50, 50, "Here be Whales", 14);

  // delete the font object. SelectObject() returns the handle
  // of the object being replaced; we delete our font object by 
  // selecting the default font
  DeleteObject(SelectObject(hdc, GetStockObject(SYSTEM_FONT))); 
  lpDDS_Map->ReleaseDC(hdc);

  // create sprites
  lpDDS_Sprites[BM_MOBY] = 
    DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_MOBY), 0, 0);    
  lpDDS_Sprites[BM_WAKE] = 
    DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_WAKE), 0, 0);    
  lpDDS_Sprites[BM_SPOUT] = 
    DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_SPOUT), 0, 0);    
  lpDDS_Sprites[BM_AHAB] = 
    DDLoadBitmap(lpDD, MAKEINTRESOURCE(IDB_AHAB), 0, 0);;    
  for (int k = 0; k < NUMSPRITES; k++)
    {
    if (lpDDS_Sprites[k] == NULL) 
      {
      OutputDebugString("Failed to load sprites\n");    
      return FALSE;
      }
    ddrval = DDSetColorKey(lpDDS_Sprites[k], CLR_INVALID);
    }

    // Create a DirectDrawClipper object. The object enables clipping to the 
    //   window boundaries in the IDirectDrawSurface::Blt function for the 
    //   primary surface. This isn't actually necessary in Moby Dick, since 
    //   we never attempt to write beyond the window boundaries.
	ddrval = lpDD->CreateClipper(0, &lpClipper, NULL);
  if( ddrval != DD_OK )
    {
      OutputDebugString("Can't create clipper\n");
      return FALSE;
    }

	ddrval = lpClipper->SetHWnd(0, hwnd);
  if( ddrval != DD_OK )
    {
      OutputDebugString("Can't set clipper window handle\n");
      return FALSE;
    }

  ddrval = lpDDSPrimary->SetClipper(lpClipper);
  if( ddrval != DD_OK )
    {
    OutputDebugString("Can't attach clipper to primary surface\n");
    return FALSE;
    }
    
  return TRUE;
  } // InitGraphics


/* ***************************************
    CleanupGraphics
    Release all DDraw objects
  **************************************** */

void CleanupGraphics(void)
  {
  if (lpDDSPrimary != NULL) lpDDSPrimary->Release();
  if (lpDDSBack != NULL) lpDDSBack->Release();
  if (lpDDS_Map != NULL) lpDDS_Map->Release();
  
  for (int k = 0; k < NUMSPRITES; k++)
    if (lpDDS_Sprites[k] != NULL)
      lpDDS_Sprites[k]->Release();

  if (lpClipper != NULL)
    lpClipper->Release();
  if (lpDDPal != NULL)
    lpDDPal->Release();
  // finally, the DD object itself
  if (lpDD != NULL) lpDD->Release();

} // CleanupGraphics

/* ****************************************************************** 
   UpdateScreen()
   Copies the background buffer to the screen window. This has the
   same effect as the IDirectDrawSurface2::Flip() method but is for 
   windowed rather than full-screen applications.
  ******************************************************************* */

BOOL UpdateScreen(HWND hwnd)
  {
  HRESULT  ddrval;
  RECT	   DestRect;
  DDBLTFX  DDbltfx;

	// Get screen coordinates of client window for blit
 GetClientRect(hwnd, &DestRect);
 ClientToScreen(hwnd, (LPPOINT)&DestRect);
 ClientToScreen(hwnd, (LPPOINT)&DestRect+1);

  // initialize special effects structure
  ZeroMemory(&DDbltfx, sizeof(DDbltfx));
  DDbltfx.dwSize = sizeof(DDbltfx);   

  // do the blit from back surface
  ddrval = lpDDSPrimary->Blt(
				&DestRect,       // destination rect
				lpDDSBack,
				&MapRect,     
				DDBLT_WAIT,
				&DDbltfx);

   return (ddrval == DD_OK);
  } // UpdateScreen

/* ****************************************************************** 
   PutSprite()
   Paints a sprite to the background buffer
  ******************************************************************* */

HRESULT PutSprite(int X, int Y, int sprite)
  {
  RECT		            SrcRect;
  LPDIRECTDRAWSURFACE lpDDS;
  DDSURFACEDESC       ddsd;

  EraseSprite(X, Y);
  lpDDS = lpDDS_Sprites[sprite];
  ddsd.dwSize = sizeof(ddsd);
  ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
  lpDDS->GetSurfaceDesc(&ddsd);

  SrcRect.top = 0;
  SrcRect.left = 0;
  SrcRect.right = ddsd.dwWidth;
  SrcRect.bottom = ddsd.dwHeight;
  return lpDDSBack->BltFast(X, Y, lpDDS, &SrcRect, 
                            DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
  } // PutSprite()


/* ******************************************************************
   EraseSprite()
   Erases a sprite from the background buffer by copying the 
   appropriate part of the map over it
  ******************************************************************* */

void EraseSprite(int X, int Y)
  {
  RECT		 DestRect, SrcRect;
	DDBLTFX  DDbltfx;

  SrcRect.top = Y;
  SrcRect.left = X;
  SrcRect.right = X + SPRITE_WD; // KLUDGE -- get dimensions from surface desc
  SrcRect.bottom = Y + SPRITE_HT;
  DestRect.top = Y;
  DestRect.left = X;
  DestRect.right = X + SPRITE_WD;
  DestRect.bottom = Y + SPRITE_HT;
  // initialize special effects structure
  ZeroMemory(&DDbltfx, sizeof(DDbltfx));
	DDbltfx.dwSize = sizeof(DDbltfx);   

  lpDDSBack->Blt(
				&DestRect,       
				lpDDS_Map,
				&SrcRect,     
				DDBLT_WAIT,
				&DDbltfx);
  } // EraseSprite()


/* ******************************************************************
   EraseAllSprites()
   Clears the back buffer by filling it with the ocean map 
  ******************************************************************* */

void EraseAllSprites(void)
  {
  RECT		      DestRect, SrcRect;
	DDBLTFX       DDbltfx;
  DDSURFACEDESC ddsd;

  ddsd.dwSize = sizeof(ddsd);
  ddsd.dwFlags = DDSD_HEIGHT | DDSD_WIDTH;
  lpDDS_Map->GetSurfaceDesc(&ddsd);
  SrcRect.top = 0;
  SrcRect.left = 0;
  SrcRect.right = ddsd.dwWidth;
  SrcRect.bottom = ddsd.dwHeight;
  // make source and destination rects the same
  memcpy(&DestRect, &SrcRect, sizeof(SrcRect));

  // initialize special effects structure
  ZeroMemory(&DDbltfx, sizeof(DDbltfx));
	DDbltfx.dwSize = sizeof(DDbltfx);   

  lpDDSBack->Blt(
				&DestRect,       
				lpDDS_Map,
				&SrcRect,     
				DDBLT_WAIT,
				&DDbltfx);

  } // EraseAllSprites()