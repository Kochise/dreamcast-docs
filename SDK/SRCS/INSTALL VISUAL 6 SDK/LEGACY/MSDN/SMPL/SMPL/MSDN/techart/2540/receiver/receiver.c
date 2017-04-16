
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

#include <windows.h>
#include "receiver.h"

  char szBuf[20]="0";



/*typedef struct ChainedStruct
{ struct ChainedStruct *next;
  PSTR lpString;
} CHAINEDSTRUCT;

CHAINEDSTRUCT *csRoot,*csCurrent;
*/
HWND hWndReceiver;

int CALLBACK LibMain(HINSTANCE hInst, WORD wDataSeg, WORD wCBHeap, LPSTR lpCmd)
{
/*csRoot = (CHAINEDSTRUCT *)0;
csCurrent = (CHAINEDSTRUCT *)0; 
*/
return(1);
}

void FAR PASCAL Register(HWND hWnd)
{ hWndReceiver = hWnd;
}

void FAR PASCAL ReceiveDisplayString(LPSTR lpStr)
{
//  wsprintf(szBuf,"%d",hWndReceiver,
  SendMessage(hWndReceiver, WM_USER+MESSAGEOFFSET,0,(LPARAM)lpStr);
//  MessageBeep(-1);
//  MessageBox(GetFocus(),szBuf,"RDS",NULL);
}


