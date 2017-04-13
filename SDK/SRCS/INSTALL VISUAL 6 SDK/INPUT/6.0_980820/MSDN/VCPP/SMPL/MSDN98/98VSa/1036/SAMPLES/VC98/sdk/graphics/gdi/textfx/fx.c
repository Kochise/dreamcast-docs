/*****************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\*****************************************************************************/
/*****************************************************************************
 *																			 *
 *	FX.C     										                         *
 *																			 *
 *	PURPOSE:  Routines for rendering text with stange effects                *
 *																			 *
 *																			 *
 *	FillOut	           - Converts an array of line segments into an array of *
 *                       all the points in the segments					     *
 *																			 *
 *	RenderPathPoints   - Renders the outline of points returned from GetPath * 
 *																			 *
 *	RenderAndFillPath  - Renders the points returned from GetPath as a       *
 *                       filled polygon										 *
 *																			 *
 *	TextEffect         - Draws a string of text between two guide lines      *
 *																			 *
 *****************************************************************************/
 
#include <windows.h>
#include "fx.h"

// This structure is used by FillOut for passing data into LineDDA
typedef struct tagSEG {
  DWORD dwPos;
  LPPOINT lpPoints; 
} PTS;

/**********************************************************************
 *                                                                    *
 * AddSegment - used with LineDDA to add points from a line segment   *
 *    to an array containing all the points on a set of line segments *
 *                                                                    *
 *********************************************************************/
VOID CALLBACK AddSegment(int x, int y, PTS *pts)
{
   pts->lpPoints[pts->dwPos].x = x;
   pts->lpPoints[pts->dwPos].y = y;
   pts->dwPos++;
} 

/**********************************************************************
 *                                                                    *
 * CountPoints - used with LineDDA to determine the number of points  *
 *    needed to store all the points on a set of line segments        *
 *                                                                    *
 *********************************************************************/
VOID CALLBACK CountPoints(int x, int y, LPDWORD lpdwNumPts)
{
   (*lpdwNumPts)++;

   UNREFERENCED_PARAMETER(x);
   UNREFERENCED_PARAMETER(y);
} 


/**********************************************************************
 *                                                                    *
 * FUNCTION:  FillOut(LPPOINT, LPDWORD)                               *
 *																	  *
 * PURPOSE:   Converts an array of line segments into an array of all *
 *            of the points comprising the line segments.             *
 *                                                                    *
 *********************************************************************/
BOOL FillOut(LPPOINT *lpPoints, LPDWORD lpdwNumPts)
{
   DWORD i;
   LPPOINT lpPts = *lpPoints;
   PTS pts;
   DWORD dwNumPts = 0;

   // Make sure we have at least two points
   if (*lpdwNumPts < 2) {
     MessageBox(NULL, "You need at least two points for a guide line.", "Not enough points!", MB_ICONSTOP);
     *lpdwNumPts = 0;
     return FALSE;
   }

   // Find out how namy points are on the segments
   for (i=0; i<*lpdwNumPts - 1; i++) 
     LineDDA(lpPts[i].x, lpPts[i].y, lpPts[i+1].x, lpPts[i+1].y, (LINEDDAPROC)CountPoints, (LPARAM)&dwNumPts);
   
   // If there are too many points, print an anoying message so the user doesnt do it again
   if (dwNumPts > MAXFILLPOINTS) {
     MessageBox(NULL, "Make your guide lines a bit shorter please!", "Too many points!", MB_ICONSTOP);
     *lpdwNumPts = 0;
     return FALSE;  // Bail
   }
   
   // Allocate memory for the the points and initialize our "last point" index
   pts.lpPoints = (LPPOINT)GlobalAlloc(GPTR, dwNumPts * sizeof(POINT));
   pts.dwPos = 0;
                                                                    
   // Convert the segments to points
   for (i=0; i<*lpdwNumPts - 1; i++) 
     LineDDA(lpPts[i].x, lpPts[i].y, lpPts[i+1].x, lpPts[i+1].y, (LINEDDAPROC)AddSegment, (LPARAM)&pts);
   
   // Get rid of the original array of segments...
   GlobalFree(lpPts);
 
   // ... and replace it with the new points
   *lpPoints = pts.lpPoints;
   *lpdwNumPts = pts.dwPos;
   
   // Check to see if anything hit the fan
   if (!pts.dwPos)
     return FALSE;

   return TRUE;  
}

/**********************************************************************
 *                                                                    *
 * FUNCTION:  PolyDraw95(HDC, LPPOINT, LPBYTE, int)                   *
 *																	  *
 * PURPOSE:   Draws the points returned from a call to GetPath()      *
 *            to an HDC                                               *
 *                                                                    *
 * NOTES:     This function is similar to the Windows NT function     *
 *            PolyDraw which draws a set of line segments and Bézier  *
 *            curves.  Since PolyDraw is not supported on Windows 95  *
 *            this PolyDraw95 is used instead.                        *  
 *                                                                    *
 *********************************************************************/
BOOL PolyDraw95(HDC  hdc,              // handle of a device context 
                CONST LPPOINT lppt,	   // address of array of points 
                CONST LPBYTE lpbTypes, // address of line and curve identifiers  
                int  cCount) 	       // count of points 
{
  int i;
  
  for (i=0; i<cCount; i++) 
    switch (lpbTypes[i]) {
      case PT_MOVETO : 
         MoveToEx(hdc, lppt[i].x, lppt[i].y, NULL); 
         break;
      
      case PT_LINETO | PT_CLOSEFIGURE:
      case PT_LINETO : 
         LineTo(hdc, lppt[i].x, lppt[i].y); 
         break;
      
      case PT_BEZIERTO | PT_CLOSEFIGURE:
      case PT_BEZIERTO :
	     PolyBezierTo(hdc, &lppt[i], 3);
		 i+=2;
         break;
   }

   return TRUE;
}  


/**********************************************************************
 *                                                                    *
 * FUNCTION:  RenderPathPoints(HDC, LPPOINT, LPBYTE, int, BOOL)	      *
 *																	  *
 * PURPOSE:   Renders the points returned from a call to GetPath()    *
 *            by converting them back into a path and calling either  *
 *            FillPath or StrokePath to display them.                 *
 *                                                                    *
 * NOTE:      The R2_MERGEPENNOT is used here so that things like the *
 *            inside of and "a" or an "o" get painted correctly when  *
 *            using FillPath.                                         *
 *                                                                    *
 *********************************************************************/
BOOL RenderPathPoints(HDC hDC, LPPOINT lpPoints, LPBYTE lpTypes, int iNumPts, BOOL bOutline)
{
  BeginPath(hDC); // Draw into a path so that we can use FillPath()

  PolyDraw95(hDC, lpPoints, lpTypes, iNumPts);

  CloseFigure(hDC);
  EndPath(hDC);   

  // Draw the path
  if (bOutline)  
    StrokePath(hDC); // As an outline
  else 
      {              // As solid figures
        int iROP2 = SetROP2(hDC, R2_MERGEPENNOT);
        HPEN hPen = SelectObject(hDC, GetStockObject(NULL_PEN)); // Just say "no" to outlines
        HBRUSH hBrush = SelectObject(hDC, GetStockObject(BLACK_BRUSH)); // Paint It Black

        FillPath(hDC);  

        // Restore the DC to its previous state
        SetROP2(hDC, iROP2);        
        SelectObject(hDC, hPen);
        SelectObject(hDC, hBrush);
      } 
  
  return TRUE;
}


/**********************************************************************
 *                                                                    *
 * FUNCTION:  GetRealTextExtent(LPPOINT, int, LPSIZE)                 *
 *																	  *
 * PURPOSE:   Makes sure that the extents in a SIZE are large enough  *
 *            to bound the points in an array.                        *
 *                                                                    *
 * NOTES:     Why not just use GetTextExtentPoint32?  Well, the text  *
 *            extents returned by GetTextExtentPoint32 dont include   *
 *            the overhang of an italics character into the next      *
 *            cell.  This function expands the extents to include     *
 *            the greatest x, and y extents of the string data.       *
 *                                                                    *
 *********************************************************************/
void GetRealTextExtent(LPPOINT lpPoints, int iNumPts, LPSIZE size)
{
  int i;

  for (i=0; i<iNumPts; i++) {
    if (lpPoints[i].x > size->cx) size->cx = lpPoints[i].x;
    if (lpPoints[i].y > size->cy) size->cy = lpPoints[i].y;
  }
}

/**********************************************************************
 *                                                                    *
 * FUNCTION:  TextEffect(HDC, LPPOINT, LPPOINT, DWORD, DWORD,         *
 *                            LPSTR, BOOL)  						  *
 *																	  *
 * PURPOSE:   Draws a string of text in the currently selected font   *
 *            using two arrays of points as guide lines for orienting *
 *            the text.  The text can be displayed either as outlines *
 *            or as filled characters.                                *
 *                                                                    *
 *********************************************************************/
BOOL TextEffect(HDC hDC,            // DC to display into
                LPPOINT lpTop,  	// Top guide line
                LPPOINT lpBot, 		// Bottom guide line
                DWORD dwTopPts, 	// Number of points in top guide
                DWORD dwBotPts, 	// Number of points in bottom guide
                LPSTR szText, 		// Text string to apply effects to
                BOOL bOutlineOnly)  // Print as outline or as solid text
{
   LPPOINT lpPoints;		  // Path data points
   LPBYTE lpTypes;			  // Path data types
   int i, iNumPts;
   SIZE size;				  // Text size info
   float fXScale, fYScale;	  // Scaling values
   int iTopInd, iBotInd;	  // Guide array indices

   // Set to transparent so we dont get an outline around the text string
   SetBkMode(hDC, TRANSPARENT);
      
   // Output the text into a path
   BeginPath(hDC);
   TextOut(hDC, 0, 0, szText, strlen(szText));
   EndPath(hDC);    
      
   // How many points are in the path
   iNumPts = GetPath(hDC, NULL, NULL, 0);
   if (iNumPts == -1) return FALSE;

   // Allocate room for the points
   lpPoints = (LPPOINT)GlobalAlloc(GPTR, sizeof(POINT) * iNumPts);
   if (!lpPoints) return FALSE;

   // Allocate room for the point types
   lpTypes = GlobalAlloc(GPTR, iNumPts);
   if (!lpTypes) {
     GlobalFree(lpPoints);
  	 return FALSE;
   }
   
   // Get the points and types from the current path
   iNumPts = GetPath(hDC, lpPoints, lpTypes, iNumPts);

   // Even more error checking
   if (iNumPts == -1) {
     GlobalFree(lpTypes);
     GlobalFree(lpPoints);
	 return FALSE;
   }
   
   //Get extents of the text string for scaling purposes  
   GetTextExtentPoint32(hDC, szText, strlen(szText), &size);

   // OK, but lets make sure our extents are big enough (handle italics fonts)
   GetRealTextExtent(lpPoints, iNumPts, &size);
   
   // Relocate the points in the path based on the guide lines
   for (i=0; i < iNumPts; i++) {
   	 // How far along is this point on the x-axis
     fXScale = (float)lpPoints[i].x / (float)size.cx;

     // What point on the top guide does this coorespond to
     iTopInd = (int)(fXScale * (dwTopPts-1));
	 // What point on the bottom guide does this coorespond to
     iBotInd = (int)(fXScale * (dwBotPts-1));

     // How far along is this point on the y-axis
     fYScale = (float)lpPoints[i].y / (float)size.cy;

     // Scale the points to their new locations
     lpPoints[i].x = (int)((lpBot[iBotInd].x * fYScale) + (lpTop[iTopInd].x * (1.0f-fYScale)));
     lpPoints[i].y = (int)((lpBot[iBotInd].y * fYScale) + (lpTop[iTopInd].y * (1.0f-fYScale)));
   }

   // Draw the new path 
   RenderPathPoints(hDC, lpPoints, lpTypes, iNumPts, bOutlineOnly);
   
   GlobalFree(lpPoints);
   GlobalFree(lpTypes);

   return TRUE;
}
