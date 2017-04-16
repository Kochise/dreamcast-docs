//---------------------------------------------------------------------------
//  vbDLL Sample Application
//
//  This sample application demonstrates how to create DLL for Native VB Functions
//
//  Author: Ken Lassesen
//              Developers NetWork
//              Microsoft Corp.
//
//---------------------------------------------------------------------------


#include <windows.h>
#include <vbapi.h>
#include "nativevb.h"
#include <toolhelp.h>	//For StopWatch
//---------------------------------------------------------------------------
// Function declarations
//---------------------------------------------------------------------------

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpstrCmdLine, int cmdShow);

//---------------------------------------------------------------------------
// Global Variables...
//---------------------------------------------------------------------------
HINSTANCE hInstance;		  // Global instance handle for application      

//---------------------------------------------------------------------------
// WinMain
//---------------------------------------------------------------------------

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpstrCmdLine, int cmdShow)
{
    //
    // Set the global instance variable
    //
    hInstance = hInst;
	return(1);
}                                      

#include "toolhelp.h"	//For StopWatch
TIMERINFO tiThisTime;
DWORD dwStopWatchStarted=0;
//---------------------------------------------------------------------------
//  .StopWatch_Reset()
//---------------------------------------------------------------------------
// We set the StopWatchStarted to the current ticks
void  _pascal __export StopWatch_Reset()
{    
if (tiThisTime.dwSize==0)
   tiThisTime.dwSize=sizeof(TIMERINFO);
if (0==TimerCount(&tiThisTime))
	MessageBox(NULL,"Unable to obtain current time for stopWatch.","Unexpected Error",MB_ICONSTOP);
	dwStopWatchStarted=tiThisTime.dwmsThisVM; //Records starting Milliseconds
}          

//---------------------------------------------------------------------------
//  .StopWatch_Time()
//---------------------------------------------------------------------------
// We return the ticks since the StopWatchStarted was reset above.
long _pascal __export StopWatch_Time()
{
if (dwStopWatchStarted==0)  //if user forgot to set it then we reset it for them.
		StopWatch_Reset();
if (0==TimerCount(&tiThisTime)) //Get time
	MessageBox(NULL,"Unable to obtain current time for StopWatch.","Unexpected Error",MB_ICONSTOP);
return  (long) (tiThisTime.dwmsThisVM-dwStopWatchStarted); //Returns Milliseconds since start
}
