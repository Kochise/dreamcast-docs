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
 *  GetGuideLine       - Retrieves a guide line from the user.  A guide line *
 *						 is just an array of line segments.   				 *
 *																			 *
 *  ShowGuide		   - Displays a guide line into a DC                     *
 *																			 *
 *****************************************************************************/

#include <windows.h>
#include "guide.h"

/**********************************************************************
 *                                                                    *
 * FUNCTION:  GetGuideLine(HWND, LPPOINT, LPDWORD)                    *
 *																	  *
 * PURPOSE:   Gets a guide line that is entered by the user.  This is *
 *            initiated on a WM_LBUTTONDOWN.                          *
 *                                                                    *
 *********************************************************************/
BOOL GetGuideLine(HWND hWnd, LPPOINT *lpPoint, LPDWORD lpdwNumPts)
{
    MSG msg;
    HDC hDC = GetDC(hWnd);
    BOOL bFirstTime = TRUE;
    DWORD dwPos = 0;
    RECT rect;

    SetCapture(hWnd);
    GetClientRect(hWnd, &rect);
    
    // Allocate enough room for a reasonable line
    *lpPoint = (LPPOINT)GlobalAlloc(GPTR, MAXGUIDESEGMENTS * sizeof(POINT));

    /* Eat mouse messages until a WM_LBUTTONUP is encountered. Meanwhile
     * continue to draw a line that follows the mouse
     */
    for (;;){
        WaitMessage();
        if (PeekMessage(&msg,NULL,WM_MOUSEFIRST,WM_MOUSELAST,PM_REMOVE)) {
                        
            // Make sure we are still tracking in our client area
            if ((LOWORD(msg.lParam) < rect.right) && (HIWORD(msg.lParam) < rect.bottom)) {
            
                // Set the CP to our starting position if we are starting
                if (bFirstTime) {
                  bFirstTime = FALSE;
    			  MoveToEx(hDC, LOWORD(msg.lParam), HIWORD(msg.lParam), NULL);
    			}				
                          
                // If we dont have more points than we want...
                if (dwPos < MAXGUIDESEGMENTS) {
    		    
    		        // Store the point in our array
    		        (*lpPoint)[dwPos].x = LOWORD(msg.lParam);
    		        (*lpPoint)[dwPos].y = HIWORD(msg.lParam);
                
    		        // Draw from the last point to this one
    		        LineTo(hDC, (*lpPoint)[dwPos].x, (*lpPoint)[dwPos].y);
		
    		        // Increment our "number of points" counter
    		        dwPos++;
    			}
            }

            // Bail when the user lets the left button up
            if (msg.message == WM_LBUTTONUP)
               break;                       
        }
        else
            continue;
    }

    *lpdwNumPts = dwPos;

    ReleaseDC(hWnd, hDC);
   
    ReleaseCapture();

    return TRUE;
}

/**********************************************************************
 *                                                                    *
 * FUNCTION:  ShowGuide(HDC, LPPOINT, DWORD)                          *
 *																	  *
 * PURPOSE:   Draws a guide line into a DC							  *
 *                                                                    *
 *********************************************************************/
BOOL ShowGuide(HDC hDC, LPPOINT lpPoints, DWORD dwNumPts)
{
  HPEN hOldBrush;
   
  // Draw the line
  Polyline(hDC, lpPoints, dwNumPts);

  // Draw green circle to indicate line starting point
  hOldBrush = SelectObject(hDC, CreateSolidBrush(RGB(0,255,0))); 
  Ellipse(hDC, lpPoints[0].x-5, lpPoints[0].y-5, 
               lpPoints[0].x+5, lpPoints[0].y+5);
  
  // Draw red circle to indicate line ending point
  DeleteObject(SelectObject(hDC, CreateSolidBrush(RGB(255,0,0)))); 
  Ellipse(hDC, lpPoints[dwNumPts-1].x-5, lpPoints[dwNumPts-1].y-5, 
               lpPoints[dwNumPts-1].x+5, lpPoints[dwNumPts-1].y+5);
  DeleteObject(SelectObject(hDC, hOldBrush)); 
  
  return TRUE;
}

