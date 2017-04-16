// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.

#include "zusammen.h"
#include "string.h"
/*
Module Struture:
		app.c		-	WinMain and Message Loops
			frame.c	-	Setups Frame Window
				wframe.c - Handle Frame Window Messages
					client.c	-	Maintains and controls client Window
						wclient.c - Handle Client Window Messages
							zusammen.c - All code specific to Zusammen

*/
//------Defines
//
#define ZU_TITLE		0
#define ZU_WINDOW1	1
#define ZU_WINDOW2	2

//------Variables
//
PICKER_STRUCT aPicker[3] ;  

//-----Local Function Prototypes------------------------------------------	  
//
void LOCAL printLine(HWND hwnd, HDC hdc, RECT rc, int iLine) ;
void LOCAL clearPick(HWND hwnd, int iwhich);

//---------------------------------------------------------------------------
//
void GLOBAL zu_calcScreenPos(LPPOINT lpPos, LPPOINT lpSize )
{
	 int xscreen = GetSystemMetrics(SM_CXSCREEN);
	 int yscreen = GetSystemMetrics(SM_CYSCREEN);
	 int xicon = GetSystemMetrics(SM_CXICON);
	 int yicon = GetSystemMetrics(SM_CYICON);
	 
	 lpSize->x = xicon * 9 ;
	 lpSize->y = yicon * 5 ;
	 lpPos->x = xscreen - lpSize->x ;
	 lpPos->y = yscreen - lpSize->y ;
}

BOOL GLOBAL zu_OnCreate (HWND hwnd, CREATESTRUCT FAR* lpCreateStruct)
{
	 
	 LoadString(g_app.hinst,IDS_FILENAME,aPicker[ZU_TITLE].szFilename,FILENAMESIZE) ;	 
	 LoadString(g_app.hinst,IDS_CLASSNAME,aPicker[ZU_TITLE].szClassname,CLASSNAMESIZE);
	 LoadString(g_app.hinst,IDS_CAPTION,aPicker[ZU_TITLE].szCaption,CAPTIONSIZE);
	 LoadString(g_app.hinst,IDS_EMPTY,aPicker[ZU_WINDOW1].szFilename,FILENAMESIZE);
	 LoadString(g_app.hinst,IDS_EMPTY,aPicker[ZU_WINDOW2].szFilename,FILENAMESIZE);
	 
	 SetScrollRange(hwnd ,SB_VERT,1,100,FALSE);
	 SetScrollPos(hwnd,SB_VERT,50,TRUE);
	 SetScrollRange(hwnd ,SB_HORZ,1,100,FALSE);
	 SetScrollPos(hwnd,SB_HORZ,50,TRUE);
	 
    return TRUE;
}

void GLOBAL zu_OnCommand (HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	 int iwhich = id - CMD_PICKWINDOW1 + 1;
    switch (id)
    {
		 case CMD_PICKWINDOW1:
		 case CMD_PICKWINDOW2:
				Picker_Do( hwnd , &aPicker[iwhich] );

				InvalidateRect(hwnd,NULL,TRUE);
				UpdateWindow(hwnd);
        break;
    default:
        break;
    }
}
// Handle the scroll bar stuff
void GLOBAL zu_OnVScroll (HWND hwnd, HWND hwndCtl, UINT code, int pos)
{
	switch(code)
	{
		case SB_BOTTOM:
		case SB_TOP:
		case SB_PAGEUP:
		case SB_PAGEDOWN:
		case SB_ENDSCROLL:
		case SB_LINEDOWN:
		case SB_LINEUP:
			if (IsWindow(aPicker[ZU_WINDOW1].hwnd))
			{
				FORWARD_WM_VSCROLL(aPicker[ZU_WINDOW1].hwnd,NULL,code,0,SendMessage);
				InvalidateRect(aPicker[ZU_WINDOW1].hwnd,NULL,FALSE);
				UpdateWindow(aPicker[ZU_WINDOW1].hwnd);
			}
			else
			{
				clearPick(hwnd,ZU_WINDOW1);
			}
						
			if (IsWindow(aPicker[ZU_WINDOW2].hwnd))
			{
				FORWARD_WM_VSCROLL(aPicker[ZU_WINDOW2].hwnd,NULL,code,0,SendMessage);				
				InvalidateRect(aPicker[ZU_WINDOW2].hwnd,NULL,FALSE);
				UpdateWindow(aPicker[ZU_WINDOW2].hwnd);
			}			
			else
			{
				clearPick(hwnd,ZU_WINDOW2);
			}

			break ;
		default:
			break;
		
	}
	
}


void GLOBAL zu_OnHScroll (HWND hwnd, HWND hwndCtl, UINT code, int pos)
{
	switch(code)
	{
		case SB_BOTTOM:
		case SB_TOP:
		case SB_PAGEUP:
		case SB_PAGEDOWN:
		case SB_ENDSCROLL:
		case SB_LINEDOWN:
		case SB_LINEUP:
			if (IsWindow(aPicker[ZU_WINDOW1].hwnd))
			{
				FORWARD_WM_HSCROLL(aPicker[ZU_WINDOW1].hwnd,NULL,code,0,SendMessage);
				InvalidateRect(aPicker[ZU_WINDOW1].hwnd,NULL,FALSE);
				UpdateWindow(aPicker[ZU_WINDOW1].hwnd);
			}
			else
			{
				clearPick(hwnd,ZU_WINDOW1);
			}
			
			if (IsWindow(aPicker[ZU_WINDOW2].hwnd))
			{
				FORWARD_WM_HSCROLL(aPicker[ZU_WINDOW2].hwnd,NULL,code,0,SendMessage);				
				InvalidateRect(aPicker[ZU_WINDOW2].hwnd,NULL,FALSE);
				UpdateWindow(aPicker[ZU_WINDOW2].hwnd);				
			}			
			else 
			{
				clearPick(hwnd,ZU_WINDOW2);
			}
			break ;
		default:
			break;
	}
}

void GLOBAL zu_OnPaint (HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rc;

    hdc = BeginPaint(hwnd, &ps);

    GetClientRect(hwnd, &rc);
    FillRect(hdc, &rc, GetStockBrush(WHITE_BRUSH));

	 printLine(hwnd,hdc,rc,ZU_TITLE);
	 printLine(hwnd,hdc,rc,ZU_WINDOW1);
	 printLine(hwnd,hdc,rc,ZU_WINDOW2);
	 
    EndPaint(hwnd, &ps);
}

//-----------------Local Functions--------------------------------
//
//
// An example of the use of the intrinsic pragma for optimizing select
// sections of code.
// Here we inline the C runtime function strlen
//

#pragma intrinsic(strlen)

void LOCAL printLine (HWND hwnd, HDC hdc, RECT rc, int iLine)
{
	
    if ( aPicker[iLine].szFilename[0] != '\0' )
    {
        int cch ;
        int x;
        static int y;
		  unsigned int cy ;
	     char szBuffer[256];

		  wsprintf(szBuffer,"%8s ( %16s )  %s",(LPSTR)aPicker[iLine].szFilename,
					  (LPSTR)aPicker[iLine].szClassname,
					  (LPSTR)aPicker[iLine].szCaption);

		  cch = strlen(szBuffer);
		  cy = HIWORD(GetTextExtent(hdc,szBuffer,cch));

		  if (iLine == 0)
		  {
          y = rc.top + cy/2 ;
		  }
		  
		  x = rc.left  ;

        SetTextColor(hdc, RGB(0,0,0));
		  TextOut(hdc, x, y, szBuffer,cch);

		  y += (cy*3/2) ;
    }
}

#pragma function(strlen)

// clearPick
//
void LOCAL clearPick (HWND hwnd, int iwhich )
{
	if(aPicker[iwhich].hwnd)
	{
		aPicker[iwhich].hwnd = NULL ;
		LoadString(g_app.hinst,IDS_EMPTY,aPicker[iwhich].szFilename,FILENAMESIZE);
		aPicker[iwhich].szCaption[0] = '\0' ;
		aPicker[iwhich].szClassname[0] = '\0' ;
		InvalidateRect(hwnd,NULL,TRUE);
		UpdateWindow(hwnd);
	}

}
