//************************************************************************
//**
//**  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//**  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//**  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
//**  A PARTICULAR PURPOSE.
//**
//**  Copyright (C) 1993 - 1997 Microsoft Corporation. All Rights Reserved.
//**
//**  tridee.c
//**
//**  DESCRIPTION:
//**    routines to draw 3d borders
//**
//************************************************************************

#include <windows.h>
#include <windowsx.h>

#include "res.h"
#include "tridee.h"

// declare variables global to this module
//
static COLORREF crFace;
static COLORREF crHilite;
static COLORREF crShadow;

static HBRUSH hBrFace = NULL;
static HBRUSH hBrShadow = NULL;
static HBRUSH hBrHilite = NULL;
static BOOL   bIs3D = FALSE;
static int    cUsers = 0;

/*+ TrideeCreate
 *
 * Register a new client for the Tridee stuff.
 *
 * on the first client we create the brushes that we will need.
 * on others we just release the useage count.
 *
 * this routine is intended to be called in the WM_CREATE case of the
 * client.
 *
 *-=================================================================*/

HBRUSH FAR PASCAL TrideeCreate(HWND hWnd)
{
   hWnd;

   if(!cUsers++)
   {
      // create the button face brush, if we fail this,
      // set the use count back to 0 and return failure to
      // the caller.
      //
      crFace = GetSysColor(COLOR_BTNFACE);
      crShadow = GetSysColor(COLOR_BTNSHADOW);
      crHilite = GetSysColor(COLOR_BTNHIGHLIGHT);

      hBrFace = CreateSolidBrush(crFace);
      if(!hBrFace)
      {
         cUsers = 0;
         return NULL;
      }

      // if the button face color is white, assume we are
      // on a EGA or Mono system, and dont even try to create
      // hilite and shadow brushes.
      bIs3D = (crFace != RGB(255,255,255));
      if (!bIs3D)
         hBrShadow = hBrHilite = NULL;
      else
      {
         // create brushes for the hilite and shadow
         //
         hBrShadow = CreateSolidBrush(crShadow);
         hBrHilite = CreateSolidBrush(crHilite);
      }
   }

   return hBrFace;
}

/*+ TrideeDestroy
 *
 * DeRegister a client for the tridee stuff.
 *
 * when the count of clients gets to 0, we destroy the brushes.
 *
 * this routine is intended to be used in the WM_DESTROY case of
 * the client.
 *
 *-=================================================================*/

BOOL FAR PASCAL TrideeDestroy(HWND hWnd)
{
   hWnd;

   if(!--cUsers)
   {
      // free the GDI objects
      if(hBrFace)
         DeleteObject(hBrFace), hBrFace = NULL;
      if(hBrHilite)
         DeleteObject(hBrHilite), hBrHilite = NULL;
      if(hBrShadow)
         DeleteObject(hBrShadow), hBrShadow = NULL;
   }
   return TRUE;
}

/*+ TrideeWellShadow
 *
 * draw a well border just inside the supplied rectangle.
 * (a well has a hilite on lower and right edges and shadow
 * on upper and left)
 *
 * this routine does not fill the recangle, it merely paints
 * the 'frame'
 *
 *-=================================================================*/

VOID FAR PASCAL TrideeWellShadow(HDC hDC, LPRECT lprc)
{
   // draw the left and upper shadow
   //
   SelectObject(hDC, hBrShadow);
   PatBlt(hDC, lprc->left, lprc->top, 2, 
                     lprc->bottom - lprc->top -2, PATCOPY);
   PatBlt(hDC, lprc->left, lprc->top, 
                     lprc->right - lprc->left, 2, PATCOPY);

   // now draw the bottom and right hilite
   //
   SelectObject(hDC, hBrHilite);
   PatBlt(hDC, lprc->right-1, lprc->top+1,
                1, lprc->bottom - lprc->top -2, PATCOPY);
   PatBlt(hDC, lprc->left+1, lprc->bottom-1,
                lprc->right -lprc->left-1, 1, PATCOPY);

}
