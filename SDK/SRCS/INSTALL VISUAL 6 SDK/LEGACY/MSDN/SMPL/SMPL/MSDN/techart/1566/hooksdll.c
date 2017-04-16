//---------------------------------------------------------------------------
//  Windows hooks Sample Application - The DLL
//
//  This sample application demonstrates how to use Windows hooks.
//
//  This File contains the source code for the hooksdll
//
//  Author:	Kyle Marsh
//              Windows Developer Technology Group
//              Microsoft Corp.
//
//---------------------------------------------------------------------------


#include "windows.h"
#include "malloc.h"
#include "string.h"
#include "hooks32.h"

//---------------------------------------------------------------------------
// Function declarations
//---------------------------------------------------------------------------

BOOL	CALLBACK LibMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved);
int 	CALLBACK WEP (int bSystemExit);
int 	CALLBACK InitHooksDll(HWND hwndMainWindow, int nWinLineHeight);
int 	CALLBACK PaintHooksDll(HDC hDC );
int 	CALLBACK InstallFilter (int nHookIndex, int nCode );
char	*szMessageString(int ID);

LRESULT	CALLBACK CallWndProcFunc (int nCode, WPARAM wParam, LPARAM lParam );
LRESULT	CALLBACK CbtFunc (int nCode, WPARAM wParam, LPARAM lParam );
LRESULT	CALLBACK GetMessageFunc (int nCode, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK JournalPlaybackFunc (int nCode, WPARAM wParam, LPARAM lParam );
LRESULT	CALLBACK JournalRecordFunc (int nCode, WPARAM wParam, LPARAM lParam );
LRESULT CALLBACK KeyboardFunc (int nCode, WPARAM wParam, LPARAM lParam );
LRESULT	CALLBACK MouseFunc (int nCode, WPARAM wParam, LPARAM lParam );
LRESULT	CALLBACK SysMsgFilterFunc (int nCode, WPARAM wParam, LPARAM lParam );
LRESULT	CALLBACK DebugFilterFunc (int nCode, WPARAM wParam, LPARAM lParam );

//---------------------------------------------------------------------------
// Global Variables...
//---------------------------------------------------------------------------

HANDLE	hInstance;				// Global instance handle for	DLL
int		InitCalled = 0;			// Has the Init function been called ?
char	szType[64];				// A Place to write temporary strings
DWORD	dwStartRecordTime;		// Time JournalRecord Started

typedef struct TAGEventNode {
	EVENTMSG		 Event;
	struct TAGEventNode *lpNextEvent;
} EventNode;

EventNode *lpEventChain	= NULL;  // Head of recorded Event List
EventNode *lpLastEvent	= NULL;  // Tail of recorded Event List
EventNode *lpPlayEvent	= NULL;  // Current Event being played

//
//  My Hook States
//
int HookStates[NUMOFHOOKS] = { 0,0,0,0,0,0,0,0,0,0 } ; // State Table of my hooks

//
//  Hook Codes
//
int HookCodes[NUMOFHOOKS] = {
			       WH_CALLWNDPROC,
			       WH_CBT,
			       WH_GETMESSAGE,
			       WH_JOURNALPLAYBACK,
			       WH_JOURNALRECORD,
			       WH_KEYBOARD,
			       WH_MOUSE,
			       WH_MSGFILTER,
				   WH_SYSMSGFILTER,
				   WH_DEBUG
			    };

//
// Filter Function Addresses
//
FARPROC lpfnHookProcs[NUMOFHOOKS] = {
				      (FARPROC) CallWndProcFunc,
				      (FARPROC) CbtFunc,
				      (FARPROC) GetMessageFunc,
				      (FARPROC) JournalPlaybackFunc,
				      (FARPROC) JournalRecordFunc,
				      (FARPROC) KeyboardFunc,
				      (FARPROC) MouseFunc,
				      NULL,
				      (FARPROC) SysMsgFilterFunc,
					  (FARPROC) DebugFilterFunc,
				    };

//
// Hook Handles
//
HHOOK hhookHooks[NUMOFHOOKS];

//
// Output Lines
//
char szFilterLine[NUMOFHOOKS][128];

// Shared DATA
#pragma data_seg("SHARDATA")
static HWND	hwndMain = NULL;		// Main hwnd. We will get this from the App
static int	nLineHeight = 0;		// Heigth of lines in window
#pragma data_seg()

//---------------------------------------------------------------------------
// LibMain
//---------------------------------------------------------------------------
BOOL CALLBACK LibMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
    hInstance = hModule;
    return 1;
}

//---------------------------------------------------------------------------
// WEP
//---------------------------------------------------------------------------
int CALLBACK WEP (int bSystemExit)
{
    return(1);
}



//---------------------------------------------------------------------------
// InitHooksDll
//---------------------------------------------------------------------------
int CALLBACK InitHooksDll(HWND hwndMainWindow, int nWinLineHeight)
{
    hwndMain = hwndMainWindow;
    nLineHeight = nWinLineHeight;


    InitCalled = 1;
    return (0);
}


//---------------------------------------------------------------------------
// PaintHooksDll
//---------------------------------------------------------------------------
int CALLBACK PaintHooksDll(HDC hDC )
{
   int i;

   for (i = 0; i < NUMOFHOOKS; i++ ) {
       if ( HookCodes[i] != WH_MSGFILTER && HookStates[i] )
	   TabbedTextOut(hDC, 1, nLineHeight * i,
		(LPSTR)szFilterLine[i], strlen(szFilterLine[i]), 0, NULL, 1);
   }

   return (0);
}

//---------------------------------------------------------------------------
// InstallSysMsgFilter
//
// Install / Remove Filter function for the WH_SYSMSGFILTER
//
//---------------------------------------------------------------------------
int CALLBACK InstallFilter (int nHookIndex, int nCode )
{

     if ( ! InitCalled ) {
		return (-1);
     }
     if ( nCode ) {
		hhookHooks[nHookIndex] =
		SetWindowsHookEx(HookCodes[nHookIndex], (HOOKPROC) lpfnHookProcs[nHookIndex], hInstance, 0);
		HookStates[nHookIndex] = TRUE;
     }
     else {
		UnhookWindowsHookEx(hhookHooks[nHookIndex]);
		HookStates[nHookIndex] = FALSE;
		InvalidateRect(hwndMain, NULL, TRUE);
		UpdateWindow(hwndMain);
     }
}

//---------------------------------------------------------------------------
// CallWndProcFunc
//
// Filter function for the WH_CALLWNDPROC
//
//---------------------------------------------------------------------------
LRESULT CALLBACK CallWndProcFunc (int nCode, WPARAM wParam, LPARAM lParam )
{
   HDC		   hDC;
   PCWPSTRUCT  pParamStruct;


   if ( nCode >= 0 ) {

	  pParamStruct = (PCWPSTRUCT) lParam;

      if ( wParam )
		 strcpy(szType,"From Current Task");
      else
		 strcpy(szType," ");

      wsprintf((LPSTR)szFilterLine[CALLWNDPROCINDEX],
	       "CALLWNDPROC\tWnd:%d\t%s %s                    ",
		   pParamStruct->hwnd,
		   szMessageString(pParamStruct->message), (LPSTR)szType);

      hDC = GetDC(hwndMain);
      TabbedTextOut(hDC, 1, nLineHeight * CALLWNDPROCINDEX,
	    (LPSTR)szFilterLine[CALLWNDPROCINDEX],
	    strlen(szFilterLine[CALLWNDPROCINDEX]), 0, NULL, 1);
      ReleaseDC(hwndMain, hDC);

   }

   //
   // We looked at the message ... sort of processed it but since we are
   // looking we will pass all messages on to CallNextHookEx.
   //
   return CallNextHookEx(hhookHooks[CALLWNDPROCINDEX], nCode, wParam, lParam);
}

//---------------------------------------------------------------------------
// CbtFunc
//
// Filter function for the WH_CBT
//
//---------------------------------------------------------------------------
LRESULT CALLBACK CbtFunc (int nCode, WPARAM wParam, LPARAM lParam )
{
   HDC	       hDC;
   CBTACTIVATESTRUCT *Active;
   LPMOUSEHOOKSTRUCT MouseHookParam;
   LPCBT_CREATEWND   CreateWndParam;
   LPRECT	     Rect;

   if ( nCode >= 0 ) {
      switch ( nCode ) {
	  case HCBT_ACTIVATE:
		 Active = (CBTACTIVATESTRUCT *) lParam;
	     wsprintf((LPSTR)szFilterLine[CBTINDEX],
		  "CBT\t\tGoing to Activate Wnd:%d Wnd:%d is active. Mouse Flag:%d                      ",
		  wParam,Active->hWndActive,Active->fMouse);
	     break;

	  case HCBT_CLICKSKIPPED:
	     MouseHookParam = (LPMOUSEHOOKSTRUCT) lParam;
	     wsprintf((LPSTR)szFilterLine[CBTINDEX],
		  "CBT\t\tMouse Message Removed from Queue. Point:%d %d %s                              ",
		  MouseHookParam->pt.x,MouseHookParam->pt.y,
		  szMessageString(wParam));

	     break;

	  case HCBT_CREATEWND:
		 CreateWndParam = (LPCBT_CREATEWND) lParam;
{long proc;
		 proc = GetWindowLong((HWND)wParam, GWL_WNDPROC);
		 wsprintf((LPSTR)szFilterLine[CBTINDEX],
		   "CBT\t\t\t\t\t\t\t\t\tGoing to Create Wnd:%d  Proc:%ld                                                     ",
		   wParam, proc);
}
	     break;

	  case HCBT_DESTROYWND:
	     wsprintf((LPSTR)szFilterLine[CBTINDEX],
		  "CBT\t\tGoing to Destroy Wnd:%d                                                       ",
		  wParam);

	     break;

	  case HCBT_KEYSKIPPED:
	     wsprintf((LPSTR)szFilterLine[CBTINDEX],
		  "CBT\t\tKeyboard Message Removed from Queue. Key:%d                                   ",
		  wParam);

	     break;

	  case HCBT_MINMAX:
	     switch ( LOWORD(lParam) ) {
		 case SW_HIDE:
			strcpy(szType, "SW_HIDE");
		    break;

		 case SW_NORMAL:
			strcpy(szType, "SW_NORMAL");
		    break;

		 case SW_SHOWMINIMIZED:
			strcpy(szType, "SW_SHOWMINIMIZED");
		    break;

		 case SW_MAXIMIZE:
			strcpy(szType, "SW_MAXIMIZE");
		    break;

		 case SW_SHOWNOACTIVATE:
			strcpy(szType, "SW_SHOWNOACTIVATE");
		    break;

		 case SW_SHOW:
			strcpy(szType, "SW_SHOW");
		    break;

		 case SW_MINIMIZE:
			strcpy(szType, "SW_MINIMIZE");
		    break;

		 case SW_SHOWMINNOACTIVE:
			strcpy(szType, "SW_SHOWMINNOACTIVE");
		    break;

		 case SW_SHOWNA:
			strcpy(szType, "SW_SHOWNA");
		    break;

		 case SW_RESTORE:
			strcpy(szType, "SW_RESTORE");
		    break;

		 default:
			strcpy(szType,"Unknown Message");

	     }
	     wsprintf((LPSTR)szFilterLine[CBTINDEX],
		  "CBT\t\tGoing to MIN/MAX Wnd:%d %s                                                    ",
		  wParam,(LPSTR)szType);

	     break;

	  case HCBT_MOVESIZE:
	     Rect = (LPRECT) lParam;
	     wsprintf((LPSTR)szFilterLine[CBTINDEX],
		  "CBT\t\tDone MOVE/SIZE Wnd:%d to %d %d %d %d                                          ",
		  wParam,Rect->left,Rect->top,Rect->right,Rect->bottom);

	     break;

	  case HCBT_QS:
	     wsprintf((LPSTR)szFilterLine[CBTINDEX],
		  "CBT\t\tWM_QUEUESYNC Message                                                          ");

	     break;

	  case HCBT_SETFOCUS:
	     wsprintf((LPSTR)szFilterLine[CBTINDEX],
		  "CBT\t\tGiving Focus to Wnd:%d Taking Focus From Wnd:%d                               ",
		  wParam,LOWORD(lParam));

	     break;

	  case HCBT_SYSCOMMAND:
	     switch ( wParam ) {
		  case SC_SIZE:
			 strcpy(szType,"SC_SIZE");
		     break;

		  case SC_MOVE:
			 strcpy(szType,"SC_MOVE");
		     break;

		  case SC_MINIMIZE:
			 strcpy(szType,"SC_MINIMIZE");
		     break;

		  case SC_MAXIMIZE:
			 strcpy(szType,"SC_MAXIMIZE");
		     break;

		  case SC_NEXTWINDOW:
			 strcpy(szType,"SC_NEXTWINDOW");
		     break;

		  case SC_PREVWINDOW:
			 strcpy(szType,"SC_PREVWINDOW");
		     break;

		  case SC_CLOSE:
			 strcpy(szType,"SC_CLOSE");
		     break;

		  case SC_VSCROLL:
			 strcpy(szType,"SC_VSCROLL");
		     break;

		  case SC_HSCROLL:
			 strcpy(szType,"SC_HSCROLL");
		     break;

		  case SC_MOUSEMENU:
			 strcpy(szType,"SC_MOUSEMENU");
		     break;

		  case SC_KEYMENU:
			 strcpy(szType,"SC_KEYMENU");
		     break;

		  case SC_ARRANGE:
			 strcpy(szType,"SC_ARRANGE");
		     break;

		  case SC_RESTORE:
			 strcpy(szType,"SC_RESTORE");
		     break;

		  case SC_TASKLIST:
			 strcpy(szType,"SC_TASKLIST");
		     break;

		  case SC_SCREENSAVE:
			 strcpy(szType,"SC_SCREENSAVE");
		     break;

		  case SC_HOTKEY:
			 strcpy(szType,"SC_HOTKEY");
		     break;

		 default:
			strcpy(szType,"Unknown Message");

	     }
	     wsprintf((LPSTR)szFilterLine[CBTINDEX],
		  "CBT\t\tAbout to Perform System Command: %s                                           ",
		  (LPSTR)szType);

	     break;

      }

      hDC = GetDC(hwndMain);
      TabbedTextOut(hDC, 1, nLineHeight * CBTINDEX,
	    (LPSTR)szFilterLine[CBTINDEX],
	    strlen(szFilterLine[CBTINDEX]), 0, NULL, 1);
      ReleaseDC(hwndMain, hDC);
   }

   //
   // We looked at the message ... sort of processed it but since we are
   // looking we will pass all messages on to CallNextHookEx.
   //

   return( CallNextHookEx(hhookHooks[CBTINDEX], nCode,wParam, lParam));
}

//---------------------------------------------------------------------------
// GetMessageFunc
//
// Filter function for the WH_GETMESSAGE
//
//---------------------------------------------------------------------------
LRESULT CALLBACK GetMessageFunc (int nCode, WPARAM wParam, LPARAM lParam )
{
   MSG *lpMsg;
   HDC hDC;

   if ( nCode >= 0 ) {
	  lpMsg = (MSG *) lParam;
      wsprintf((LPSTR)szFilterLine[GETMESSAGEINDEX],
		   "GETMESSAGE\tWnd:%d Time:%d  Point:%d %d %s                                  ",
	       lpMsg->hwnd, lpMsg->time,
	       lpMsg->pt.x, lpMsg->pt.y, szMessageString(lpMsg->message));


      hDC = GetDC(hwndMain);
      TabbedTextOut(hDC, 1, nLineHeight * GETMESSAGEINDEX,
	    (LPSTR)szFilterLine[GETMESSAGEINDEX],
	    strlen(szFilterLine[GETMESSAGEINDEX]), 0, NULL, 1);
      ReleaseDC(hwndMain, hDC);
   }

   //
   // We looked at the message ... sort of processed it but since we are
   // looking we will pass all messages on to CallNextHookEx.
   //
   return CallNextHookEx(hhookHooks[GETMESSAGEINDEX], nCode, wParam, lParam);
}

//---------------------------------------------------------------------------
// JournalPlaybackFunc
//
// Filter function for the WH_JOURNALPLAYBACK
//
//---------------------------------------------------------------------------
LRESULT CALLBACK JournalPlaybackFunc (int nCode, WPARAM wParam, LPARAM lParam )
{
   static	  int		 nRepeatRequests;
   static	  DWORD		 dwTimeAdjust;
   static	  DWORD		 dwLastEventTime;
			  HDC		 hDC;
			  LPEVENTMSG lpEvent;
			  long		 lReturnValue;
			  HMENU 	 hMenu;

   if ( nCode >= 0 ) {
      // No Playback if we haven't recorded an Event
      //
      // No Playback While recording.
      // This is not a limitation of the hooks.
      // This is only because of the simple event storage used in this example
      //
      // We should never get here since the enable / disable menu stuff should
      // make getting here impossible
      //
      if ( lpEventChain == NULL || HookStates[JOURNALRECORDINDEX]) {
		  InstallFilter(JOURNALPLAYBACKINDEX, FALSE);
		  hMenu = GetMenu(hwndMain);
		  CheckMenuItem(hMenu, IDM_JOURNALPLAYBACK, MF_UNCHECKED | MF_BYCOMMAND);
		  EnableMenuItem(hMenu, IDM_JOURNALPLAYBACK, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
		  wsprintf((LPSTR)szFilterLine[JOURNALPLAYBACKINDEX],
			  "WH_JOURNALPLAYBACK -- No recorded Events to Playback  or JournalRecord in Progress                  ");
		  hDC = GetDC(hwndMain);
		  TabbedTextOut(hDC, 1, nLineHeight * JOURNALPLAYBACKINDEX,
				   (LPSTR)szFilterLine[JOURNALPLAYBACKINDEX],
				   strlen(szFilterLine[JOURNALPLAYBACKINDEX]), 0, NULL, 1);
		  ReleaseDC(hwndMain, hDC);
		  return( (int)CallNextHookEx(hhookHooks[JOURNALPLAYBACKINDEX], nCode, wParam, lParam ));
      }

      if ( lpPlayEvent == NULL ) {
		 lpPlayEvent = lpEventChain;
		 lpLastEvent = NULL;	   // For the next time we start the recorder
		 dwTimeAdjust = GetTickCount() - dwStartRecordTime;
		 dwLastEventTime = (DWORD) GetTickCount();
		 nRepeatRequests = 1;
      }

      if (nCode == HC_SKIP ) {
	  nRepeatRequests = 1;

	  if ( lpPlayEvent->lpNextEvent == NULL ) {
	      wsprintf((LPSTR)szFilterLine[JOURNALPLAYBACKINDEX],
		      "WH_JOURNALPLAYBACK -- Done Recorded Events");
	      hDC = GetDC(hwndMain);
	      TabbedTextOut(hDC, 1, nLineHeight * JOURNALPLAYBACKINDEX,
				 (LPSTR)szFilterLine[JOURNALPLAYBACKINDEX],
		  strlen(szFilterLine[JOURNALPLAYBACKINDEX]), 0, NULL, 1);
	      ReleaseDC(hwndMain, hDC);

		  free(lpEventChain);
	      lpEventChain = lpPlayEvent = NULL ;

	      InstallFilter(JOURNALPLAYBACKINDEX, FALSE);
	      hMenu = GetMenu(hwndMain);
	      CheckMenuItem(hMenu, IDM_JOURNALPLAYBACK, MF_UNCHECKED | MF_BYCOMMAND);
	      EnableMenuItem(hMenu, IDM_JOURNALPLAYBACK, MF_DISABLED | MF_GRAYED | MF_BYCOMMAND);
	  }
	  else {
	      dwLastEventTime = lpPlayEvent->Event.time;
	      lpPlayEvent = lpPlayEvent->lpNextEvent;
		  free(lpEventChain);
	      lpEventChain = lpPlayEvent;
	  }
      }
      else if ( nCode == HC_GETNEXT) {
	  lpEvent = (LPEVENTMSG) lParam;
	  lpEvent->message = lpPlayEvent->Event.message;
	  lpEvent->paramL  = lpPlayEvent->Event.paramL;
	  lpEvent->paramH  = lpPlayEvent->Event.paramH;
	  lpEvent->time    = lpPlayEvent->Event.time + dwTimeAdjust;

	  wsprintf((LPSTR)szFilterLine[JOURNALPLAYBACKINDEX],
		   "WH_JOURNALPLAYBACK -- Playing Event %d times                    ",
		   nRepeatRequests++);
	  hDC = GetDC(hwndMain);
	  TabbedTextOut(hDC, 1, nLineHeight * JOURNALPLAYBACKINDEX,
		(LPSTR)szFilterLine[JOURNALPLAYBACKINDEX],
		strlen(szFilterLine[JOURNALPLAYBACKINDEX]), 0, NULL, 1);
	  ReleaseDC(hwndMain, hDC);

	  lReturnValue = lpEvent->time - GetTickCount();
	  //
	  // No Long ( negative ) waits
	  //
	  if ( lReturnValue < 0L ) {
	     lReturnValue  = 0L;
	     lpEvent->time = GetTickCount();
	  }
	  return ( (DWORD) lReturnValue );
      }

      hDC = GetDC(hwndMain);
      TabbedTextOut(hDC, 1, nLineHeight * JOURNALPLAYBACKINDEX,
	    (LPSTR)szFilterLine[JOURNALPLAYBACKINDEX],
	    strlen(szFilterLine[JOURNALPLAYBACKINDEX]), 0, NULL, 1);
      ReleaseDC(hwndMain, hDC);
   }

   return( CallNextHookEx(hhookHooks[JOURNALPLAYBACKINDEX], nCode, wParam, lParam));
}

//---------------------------------------------------------------------------
// JournalRecordFunc
//
// Filter function for the WH_JOURNALRECORD
//
//---------------------------------------------------------------------------
LRESULT CALLBACK JournalRecordFunc (int nCode, WPARAM wParam, LPARAM lParam )
{
   HDC		   hDC;
   EventNode  *lpEventNode;
   LPEVENTMSG  lpEvent;
   HMENU	   hMenu;

   if ( nCode >= 0 ) {

      lpEvent = (LPEVENTMSG) lParam;
      //
      // Skip recording while playing back
      // This is not a limitation of the hooks.
      // This is only because of the simple event storage used in this example
      //
      if ( HookStates[JOURNALPLAYBACKINDEX] ) {
		 wsprintf((LPSTR)szFilterLine[JOURNALRECORDINDEX],
				"WH_JOURNALRECORD\tSkipping Recording during Playback                        ");
		 hDC = GetDC(hwndMain);
		 TabbedTextOut(hDC, 1, nLineHeight * JOURNALRECORDINDEX,
				(LPSTR)szFilterLine[JOURNALRECORDINDEX],
			   strlen(szFilterLine[JOURNALRECORDINDEX]), 0, NULL, 1);
		 ReleaseDC(hwndMain, hDC);
		 return 0;
      }

      //
      // Stop recording ?
      //
	  if ( lpEvent->message == WM_KEYDOWN && LOBYTE(lpEvent->paramL)  == VK_F2 ) {
		 wsprintf((LPSTR)szFilterLine[JOURNALRECORDINDEX],
				"WH_JOURNALRECORD\tRecording Stopped with F2                                                                 ");
		 InstallFilter(JOURNALRECORDINDEX, FALSE);
		 hMenu = GetMenu(hwndMain);
		 CheckMenuItem(hMenu, IDM_JOURNALRECORD, MF_UNCHECKED | MF_BYCOMMAND);
		 EnableMenuItem(hMenu, IDM_JOURNALPLAYBACK, MF_ENABLED | MF_BYCOMMAND);
		 return 0;
      }

	  if ( (lpEventNode = (EventNode *)malloc(sizeof(EventNode))) == NULL ) {
		 wsprintf((LPSTR)szFilterLine[JOURNALRECORDINDEX],
				"WH_JOURNALRECORD\tNo Memory Available");
		 InstallFilter(JOURNALRECORDINDEX, FALSE);
		 hMenu = GetMenu(hwndMain);
		 CheckMenuItem(hMenu, IDM_JOURNALRECORD, MF_UNCHECKED | MF_BYCOMMAND);
		 EnableMenuItem(hMenu, IDM_JOURNALPLAYBACK, MF_ENABLED | MF_BYCOMMAND);
      }


      if ( lpLastEvent == NULL ) {
		 dwStartRecordTime = (DWORD) GetTickCount();
		 lpEventChain = lpEventNode;
      }
      else {
		 lpLastEvent->lpNextEvent = lpEventNode;
      }

      lpLastEvent = lpEventNode;
      lpLastEvent->lpNextEvent = NULL;

      lpLastEvent->Event.message = lpEvent->message;
      lpLastEvent->Event.paramL  = lpEvent->paramL;
      lpLastEvent->Event.paramH  = lpEvent->paramH;
      lpLastEvent->Event.time	 = lpEvent->time;


      wsprintf((LPSTR)szFilterLine[JOURNALRECORDINDEX],
		"WH_JOURNALRECORD\tRecording\tTime:%d\tPRESS F2 To Stop Recording\t%s                        ",
	    lpEvent->time,szMessageString(lpEvent->message));
      hDC = GetDC(hwndMain);
      TabbedTextOut(hDC, 1, nLineHeight * JOURNALRECORDINDEX,
	    (LPSTR)szFilterLine[JOURNALRECORDINDEX],
	    strlen(szFilterLine[JOURNALRECORDINDEX]), 0, NULL, 1);
      ReleaseDC(hwndMain, hDC);
	  return 0;
   }

   return (CallNextHookEx(hhookHooks[JOURNALRECORDINDEX], nCode, wParam, lParam));
}

//---------------------------------------------------------------------------
// KeyboardFunc
//
// Filter function for the WH_KEYBOARD
//
//---------------------------------------------------------------------------
LRESULT CALLBACK KeyboardFunc (int nCode, WPARAM wParam, LPARAM lParam )
{
   HDC	       hDC;

   if ( nCode >= 0 ) {

      if ( nCode == HC_NOREMOVE )
		  strcpy(szType, "NOT Removed from Queue");
      else
		 strcpy(szType, "REMOVED from Queue                                             ");

      wsprintf((LPSTR)szFilterLine[KEYBOARDINDEX],
	       "KEYBOARD\tKey:%d\t%s",wParam,(LPSTR)szType);

      hDC = GetDC(hwndMain);
      TabbedTextOut(hDC, 1, nLineHeight * KEYBOARDINDEX,
	    (LPSTR)szFilterLine[KEYBOARDINDEX],
	    strlen(szFilterLine[KEYBOARDINDEX]), 0, NULL, 1);
      ReleaseDC(hwndMain, hDC);
   }

   //
   // We looked at the message ... sort of processed it but since we are
   // looking we will pass all messages on to CallNextHookEx.
   //
   return( CallNextHookEx(hhookHooks[KEYBOARDINDEX], nCode, wParam, lParam));
}

//---------------------------------------------------------------------------
// MouseFunc
//
// Filter function for the WH_MOUSE
//
//---------------------------------------------------------------------------
LRESULT CALLBACK MouseFunc (int nCode, WPARAM wParam, LPARAM lParam )
{
   HDC	       hDC;
   LPMOUSEHOOKSTRUCT MouseHookParam;

   if ( nCode >= 0 ) {
      if ( nCode == HC_NOREMOVE )
		 strcpy(szType, "NOT Removed from Queue");
      else
		 strcpy(szType, "REMOVED from Queue                                             ");

	  MouseHookParam = (MOUSEHOOKSTRUCT *) lParam;

      wsprintf((LPSTR)szFilterLine[MOUSEINDEX],
	      "MOUSE\t\tWnd:%d Point:%d %d\t%s %s",MouseHookParam->hwnd,
	      MouseHookParam->pt.x,MouseHookParam->pt.y,
		  szMessageString(wParam),(LPSTR)szType);

      hDC = GetDC(hwndMain);
      TabbedTextOut(hDC, 1, nLineHeight * MOUSEINDEX,
	    (LPSTR)szFilterLine[MOUSEINDEX], strlen(szFilterLine[MOUSEINDEX]),
	    0, NULL, 1 );
      ReleaseDC(hwndMain, hDC);

   }

   //
   // We looked at the message ... sort of processed it but since we are
   // looking we will pass all messages on to CallNextHookEx.
   //
   return( CallNextHookEx(hhookHooks[MOUSEINDEX], nCode, wParam, lParam));
}

//---------------------------------------------------------------------------
// SysMsgFilterFunc
//
// Filter function for the WH_SYSMSGFILTER
//
//---------------------------------------------------------------------------
LRESULT CALLBACK SysMsgFilterFunc (int nCode, WPARAM wParam, LPARAM lParam )
{
   MSG *lpMsg;
   HDC hDC;

   if ( nCode >= 0 ) {
      if ( nCode == MSGF_DIALOGBOX )
		 strcpy(szType,"Dialog");
      else
		 strcpy(szType,"Menu");

	  lpMsg = (MSG *) lParam;
      wsprintf((LPSTR)szFilterLine[SYSMSGFILTERINDEX],
		   "SYSMSGFILTER\t%s\tWnd:%d Time:%d  Point:%d %d %s                                ",
	       (LPSTR)szType, lpMsg->hwnd, lpMsg->time,
	       lpMsg->pt.x, lpMsg->pt.y, szMessageString(lpMsg->message));

      hDC = GetDC(hwndMain);
      TabbedTextOut(hDC, 1, nLineHeight * SYSMSGFILTERINDEX,
	    (LPSTR)szFilterLine[SYSMSGFILTERINDEX],
	    strlen(szFilterLine[SYSMSGFILTERINDEX]), 0, NULL, 1 );
      ReleaseDC(hwndMain, hDC);
   }

   //
   // We looked at the message ... sort of processed it but since we are
   // looking we will pass all messages on to CallNextHookEx.
   //
   return( CallNextHookEx(hhookHooks[SYSMSGFILTERINDEX], nCode, wParam, lParam));
}

//---------------------------------------------------------------------------
// SysMsgFilterFunc
//
// Filter function for the WH_SYSMSGFILTER
//
//---------------------------------------------------------------------------
LRESULT CALLBACK DebugFilterFunc (int nCode, WPARAM wParam, LPARAM lParam )
{
   PDEBUGHOOKINFO pDebugHook;
   HDC hDC;
   static int Called=0;

   if ( nCode >= 0 ) {
	  pDebugHook = (PDEBUGHOOKINFO) lParam;
	  wsprintf((LPSTR)szFilterLine[DEBUGFILTERINDEX],
		   "DEBUGFILTER\tCalled %d Times                                                       ",
		   ++Called);

      hDC = GetDC(hwndMain);
	  TabbedTextOut(hDC, 1, nLineHeight * DEBUGFILTERINDEX,
		(LPSTR)szFilterLine[DEBUGFILTERINDEX],
		strlen(szFilterLine[DEBUGFILTERINDEX]), 0, NULL, 1 );
      ReleaseDC(hwndMain, hDC);
   }

   //
   // We looked at the message ... sort of processed it but since we are
   // looking we will pass all messages on to CallNextHookEx.
   //
   return( CallNextHookEx(hhookHooks[SYSMSGFILTERINDEX], nCode, wParam, lParam));
}


//---------------------------------------------------------------------------
// MessageString
//
// Function to load string from the STRINGTABLE
//
//---------------------------------------------------------------------------
char *szMessageString(int ID)
{
   static char szBuffer[256];

   if ( LoadString(hInstance, ID, szBuffer, 255) == 0)
		 strcpy(szBuffer,"Unknown Message");

   return (szBuffer);

}
