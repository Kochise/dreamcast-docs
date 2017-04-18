#include <windows.h>
#include <commdlg.h>
#include <colordlg.h>
#include <stdlib.h>
#include <math.h>
#include <mmsystem.h>
#include "resource.h"
#include "w32pen.h"


/***********************************************************************

  FUNCTION   : GetPen

  PARAMETERS : PPENDRECORD pPenRecord

  PURPOSE    : create a pen based on the user defined parameters as
               specified in pPenRecord

  CALLS      : ExtCreatePen

  MESSAGES   : none

  RETURNS    : HPEN - handle of created pen

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr
  				10/26/93 - modified - a-jasons

************************************************************************/

HPEN GetPen(PPENRECORD pPenRecord)
{
  	HPEN hPen;

  	hPen =  ExtCreatePen(pPenRecord->dwPenType | pPenRecord->dwPenStyle
                      | pPenRecord->dwJoinStyle | pPenRecord->dwEndCapStyle, 
                      pPenRecord->dwWidth, &pPenRecord->lb, (DWORD) NULL, 
                      (LPDWORD) NULL);
  	return (hPen);
}


/***********************************************************************

  FUNCTION   : DrawRndLine

  PARAMETERS : HDC hdc
               PPENRECORD pPenRecord

  PURPOSE    : draw a polyline within a clipping region using randomly
               generated polylines

  CALLS      : PolyLine
               MoveToEx
			   LineTo
               SelectClipRgn
               CreateRectRgnIndirect
			   SetGraphicsMode
			   SetWorldTransform
			   SaveDC
			   RestoreDC

  MESSAGES   : none

  RETURNS    : void

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr
  				10/26/93 - modified - a-jasons

************************************************************************/

void DrawRndLine(HDC hdc, PPENRECORD pPenRecord)
{
	HPEN hpenOld, hPen;
	HRGN hrgn;
	RECT rcTemp;
	int   nSavedDC;

	//
	//remove old clip rgn
	//
	SelectClipRgn(hdc, NULL);
	//
	//establish new clip rgn
	//
	memcpy(&rcTemp, &grWorkRect, sizeof(RECT));
	InflateRect(&rcTemp, -4, -4);
	rcTemp.right --;
	rcTemp.bottom--;

	hrgn = CreateRectRgnIndirect(&rcTemp);
	if (hrgn)
	  SelectClipRgn(hdc, hrgn);

	if ((hPen = GetPen(pPenRecord)))
	{
      hpenOld = SelectObject(hdc,hPen);

	  if ((nSavedDC = SaveDC(hdc)))
	  {
	    SetGraphicsMode(hdc, GM_ADVANCED);

	    if (SetWorldTransform(hdc, &pPenRecord->xf))
          Polyline(hdc, (LPPOINT)pPenRecord->PtsToDraw, NUMPOINTS);

	    SetGraphicsMode(hdc, GM_COMPATIBLE);

		RestoreDC(hdc, nSavedDC);
	  }

      DeleteObject(SelectObject(hdc, hpenOld));
	}
}


/***********************************************************************

  FUNCTION   : DrawJoinCap

  PARAMETERS : HDC hdc
               PPENRECORD pPenRecord

  PURPOSE    : draw the join and endcap styles for the current pen node.

  CALLS      : PolyLine
               MoveToEx
			   LineTo
               SelectClipRgn
               CreateRectRgnIndirect
			   SetGraphicsMode
			   SetWorldTransform
			   SaveDC
			   RestoreDC

  MESSAGES   : none

  RETURNS    : void

  COMMENTS   : This function is simply copied from the original code in
  				DrawRndLine() and is only slightly modified.  Its removal
  				from DrawRndLine() is intended to facilitate the
  				implementation of a performance test procedure.

  HISTORY    : 10/26/93 - created - a-jasons

************************************************************************/

void DrawJoinCap(HDC hdc, PPENRECORD pPenRecord)
{
	HPEN hpenOld;
	HRGN hrgn;
	POINT pt[3];
	RECT rcTemp;

	//
	// draw the endcap and join if this is a display dc versus a 
	// metaDC
	//
    if (GetObjectType(hdc) == OBJ_DC)
    {	
	  	//
	  	//remove old clip rgn
	  	//
	  	SelectClipRgn(hdc, NULL);
	  	
	  	//
	  	//establish new clip rgn
	  	//    
	  	
	  	memcpy(&rcTemp, &grJoinCapRect, sizeof(RECT));
	  	InflateRect(&rcTemp, -4, -4);
	  	rcTemp.right --;
	  	rcTemp.bottom--;

	  	hrgn = CreateRectRgnIndirect(&rcTemp);
	  	if (hrgn)
	    	SelectClipRgn(hdc, hrgn);

	  	//
	  	// Hopefully the Join/Endcap region hasn't been drawn in
	  	// since the last DrawWorkSpace() call
	  	//

	  	if (pPenRecord->dwPenType & PS_GEOMETRIC)
			//
			// Pen is geometric, so draw the joins, et al
      		hpenOld = SelectObject(hdc,
                           ExtCreatePen(PS_GEOMETRIC | PS_SOLID
                           | pPenRecord->dwJoinStyle | pPenRecord->dwEndCapStyle, 
                           (grJoinCapRect.right - grJoinCapRect.left) / 2,
                           &pPenRecord->lb, (DWORD) NULL,
                           (LPDWORD) NULL));
	  	else
	  		hpenOld = SelectObject(hdc,
                           ExtCreatePen(PS_GEOMETRIC | PS_SOLID
                           | PS_JOIN_MITER | PS_ENDCAP_SQUARE, 
                           (grJoinCapRect.right - grJoinCapRect.left) / 4,
                           &pPenRecord->lb, (DWORD) NULL,
                           (LPDWORD) NULL));

	  	//
	  	//draw a wide line showing the endcap
	  	//
      	MoveToEx(hdc, grJoinCapRect.left + (grJoinCapRect.right - 
      				grJoinCapRect.left) / 2, grJoinCapRect.bottom / 2, NULL);

	  	LineTo(hdc, grJoinCapRect.left + (grJoinCapRect.right - 
	  				grJoinCapRect.left) / 2, grJoinCapRect.top);

	  	//
	  	//draw a line with a right angle to show the join
	  	//
      	pt[0].x = grJoinCapRect.left;
	  	pt[0].y = grJoinCapRect.bottom - ((grJoinCapRect.bottom - 
	  										grJoinCapRect.top) / 4);
	  	pt[1].x = grJoinCapRect.left + (grJoinCapRect.right - 
	  										grJoinCapRect.left) / 2;
	  	pt[1].y = pt[0].y;
	  	pt[2].x = pt[1].x;
	  	pt[2].y = grJoinCapRect.bottom;

      	Polyline(hdc, (LPPOINT)&pt, 3);

      	DeleteObject(SelectObject(hdc, hpenOld));
    }
}

/***********************************************************************

  FUNCTION   : ClearWorkAreas

  PARAMETERS : HWND hWnd
               LPRECT lprcWork - working area in middle of client area
			   LPRECT lprcJoinCap - small rect on left used for end cap
			                        and join

  PURPOSE    : invalidate the working areas of the app 

  CALLS      : InvalidateRect
               UpdateWindow

  MESSAGES   : none

  RETURNS    : void

  COMMENTS   :

  HISTORY    : 9/20/93 - created - denniscr

************************************************************************/

BOOL ClearWorkAreas(HWND hWnd, LPRECT lprcWork, LPRECT lprcJoinCap)
{
  if (lprcWork)
    InvalidateRect(hWnd, lprcWork, TRUE);
  if (lprcJoinCap)
    InvalidateRect(hWnd, lprcJoinCap, TRUE);
  return (UpdateWindow(hWnd));
}



 
