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

APP g_app;

//-----Local Function Prototypes------------------------------------------	  
//
BOOL LOCAL App_Initialize(APP* papp);
int  LOCAL App_Main(APP* papp);
VOID LOCAL App_Terminate(APP* papp, BOOL fEndSession);
BOOL LOCAL App_Idle(APP* papp);
//
//---------------------------------------------------------------------------

// WinMain is not declared as LOCAL or GLOBAL
int PASCAL WinMain(	HINSTANCE hinst, HINSTANCE hinstPrev, 
							LPSTR lpszCmdLine, int cmdShow)
{
    int exitCode;

    // Initialize the APP structure
    //
    g_app.hinst       = hinst;
    g_app.hinstPrev   = hinstPrev;
    g_app.lpszCmdLine = lpszCmdLine;
    g_app.cmdShow     = cmdShow;
    g_app.hwndFrame   = NULL;

    // Initialize, run, and terminate the application
    //
    if (!App_Initialize(&g_app))
		 return 1;

    exitCode = App_Main(&g_app);

    App_Terminate(&g_app, FALSE);

    return exitCode;
}

int LOCAL App_Main(APP* papp)
{
    while (TRUE)
    {
        MSG msg;

        // If a message exists in the queue, translate and dispatch it.
        //
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // If it's time to quit, return exit code
            //
            if (msg.message == WM_QUIT)
                return (int)msg.wParam;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // No messages: do idle processing.
            // If the app is idle, just wait for another message.
            //
            if (App_Idle(papp))
                WaitMessage();
        }
    }
}

BOOL LOCAL App_Initialize(APP* papp)
{
	POINT pos, size ;
	if( papp->hinstPrev == NULL )
	{
    if (!Frame_Initialize(papp))
        return FALSE;

    if (!Client_Initialize(papp))
        return FALSE;
  }

	 // Zusammen specific : Calculate Screen Position of Window
    zu_calcScreenPos(&pos,&size) ;
	 
    papp->hwndFrame = Frame_CreateWindow(
            "Zusammen",
				pos.x, pos.y, size.x,size.y,
            papp->hinst);

    if (papp->hwndFrame == NULL)
		 return FALSE;

    ShowWindow(papp->hwndFrame, papp->cmdShow);
    return TRUE;
}

void LOCAL App_Terminate(APP* papp, BOOL fEndSession)
{
    // Flush any caches and buffers to disk, if necessary.
    //
    // If fEndSession is TRUE, it is not necessary to
    // destroy windows, GDI objects, or free memory.
    //
    if (!fEndSession)
    {
        if (papp->hwndFrame)
        {
            DestroyWindow(papp->hwndFrame);
            papp->hwndFrame = NULL;
        }

        Client_Terminate(papp);

        Frame_Terminate(papp);
    }
}

BOOL LOCAL App_Idle(APP* papp)
{
    // Return TRUE if the app is idle, FALSE if there is more work to do.
    //
    return TRUE;
}
