#include "global.h"
#include "mmsystem.h"
#include "stdio.h"

//
// local data
//
int nState=1;	 // States:
#define NOSTATE 	0 // Do nothing
#define PEEKLOOP	1 // Peek Message loop
#define TIMERMSG	2 // TIMER message loop
#define HOG 		3 // Long hog process
#define HOGSLEEP	4 // Long process with sleep
#define HOGPEEK 	5 // Long process with peek message
#define HOGTHREAD	6 // Long process in Thread.

char buf[16];
static long LastTime = 0;
static long LastInterval = 0;
static HANDLE hThread;

//
// local functions
//

static void Create(HWND hWnd, LPCREATESTRUCT lpCI);
static void Size(HWND hWnd, UINT uiX, UINT uiY);
static void Command(HWND hWnd, UINT uParam, LPARAM lParam);
LRESULT HogThread(HWND hWnd);

//
// Entry point
//

int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine,
                   int cmdShow)
{
    MSG msg;
#ifdef SINGLE_INSTANCE
	HWND hWndApp, hWndPopup;
	HANDLE hMutex;
#endif

    hAppInstance = hInstance;
	szAppName = "THREAD";


#ifdef SINGLE_INSTANCE
	hMutex = CreateMutex(NULL, FALSE, "ThreadSampleMutex" );
	if ( WaitForSingleObject(hMutex, 10000) == WAIT_TIMEOUT ) {
		//
		// There is another instance out there, but it is taking to long to
		// locate, just exit
		return FALSE;
	}

	if (hWndApp = FindWindow(szAppName, NULL)) {
	   hWndPopup = GetLastActivePopup(hWndApp);

	   BringWindowToTop(hWndApp);
	   if ( IsIconic(hWndPopup) )
		  ShowWindow(hWndPopup, SW_RESTORE);
	   else
		  SetForegroundWindow(hWndPopup);

	   ReleaseMutex(hMutex);
	   CloseHandle(hMutex);
	   return FALSE;
	}
#endif

	if (!Init(hInstance, cmdShow)) {
#ifdef SINGLE_INSTANCE
	   ReleaseMutex(hMutex);
	   CloseHandle(hMutex);
#endif
	   return 1;
    }

#ifdef SINGLE_INSTANCE
	ReleaseMutex(hMutex);
	CloseHandle(hMutex);
#endif

	LastTime = (long)timeGetTime();

    //
    // Check for messages from Windows and process them.
    // If we have nothing else to do, maybe perform some idle function
    // 

    do {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

            //
            // got a message to process
            //

            if (msg.message == WM_QUIT) break;

            //
            // Do the accelerator thing
            //
            if (!TranslateAccelerator(hwndMain, hAccTable, &msg)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }

        } else {
            //
            // perform some idle routine or just give up so Windows
            // can run till our next message.
			//
			if ( nState == PEEKLOOP )  {
			   long Interval;
			   long NowTime;

			   NowTime = (long) timeGetTime();
			   Interval = NowTime-LastTime;

			   sprintf(buf, "%7ld", Interval);
			   SetWindowText(hwndNoFilter, buf);

			   if ( Interval <= LastInterval ) {
				  Interval = LastInterval;
			   }

			   sprintf(buf, "%7ld", Interval);
			   SetWindowText(hwndFilter, buf);

			   LastTime=NowTime;
			   LastInterval = Interval;
			}
			else {
			   WaitMessage();
			}
        }
    } while (1);

	return (msg.wParam);
}
    
//
// main window message handler
//

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, UINT uParam, LPARAM lParam)
{
	switch(msg) {

    case WM_TIMER:
        //
        // Update the counter and set the new window text
        //
		{
			   long Interval;
			   long NowTime;

			   NowTime = (long) timeGetTime();
			   Interval = NowTime-LastTime;

			   sprintf(buf, "%7ld", Interval);
			   SetWindowText(hwndNoFilter, buf);

			   if ( Interval <= LastInterval ) {
				  Interval = LastInterval;
			   }

			   sprintf(buf, "%7ld", Interval);
			   SetWindowText(hwndFilter, buf);

			   LastTime=NowTime;
			   LastInterval = Interval;
		}
        break;


    case WM_CREATE:
        Create(hWnd, (LPCREATESTRUCT)lParam);
        break;

    case WM_SIZE:
		Size(hWnd, LOWORD(lParam), HIWORD(lParam));
		break;

    case WM_COMMAND:
		Command(hWnd, uParam, lParam);
		break;

	case WM_ACTIVATEAPP:
		if ( nState == HOGTHREAD ) {
			if ( uParam ) {
				SetThreadPriority(hThread, THREAD_PRIORITY_LOWEST );
			}
			else {
				SetThreadPriority(hThread, THREAD_PRIORITY_NORMAL );
			}
		}
		else {
			return DefWindowProc(hWnd, msg, uParam, lParam);
		}
		break;

	case WM_CLOSE:
		if ( nState >= HOG ) {
		   MessageBeep(0);
		   return FALSE;
		}
		else {
		   DestroyWindow(hWnd);
		}
		break;

    case WM_DESTROY:
        Terminate();
        PostQuitMessage(0);
        break;

    default:
		return DefWindowProc(hWnd, msg, uParam, lParam);
        break;
    }
	return 0L;
}

//
// Process WM_CREATE message
//

static void Create(HWND hWnd, LPCREATESTRUCT lpCI)
{
    //
    // Create the two child windows
    //

	hwndFilter = CreateWindow("NoFlickering",
                            "",
                            WS_CHILD | WS_VISIBLE,
                            0, 0,
                            0, 0,
                            hWnd,
                            (HMENU)IDC_NOFLICKER,
                            hAppInstance,
                            (LPSTR)NULL
                            );

	hwndNoFilter = CreateWindow("NoFlickering",
                            "",
                            WS_CHILD | WS_VISIBLE,
                            0, 0,
                            0, 0,
                            hWnd,
                            (HMENU)IDC_NOFLICKER,
                            hAppInstance,
                            (LPSTR)NULL
                            );

}

//
// Process WM_SIZE message
//

static void Size(HWND hWnd, UINT uiX, UINT uiY)
{
    //
    // Create a new big font the right size
    //

    if (hfntBig) {
        DeleteObject(hfntBig);
        hfntBig = NULL;
    }
    hfntBig = CreateFont(
                uiY / 2, 0,
                0, 0,
                700, // weight
                0, 0, 0,
                ANSI_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                PROOF_QUALITY,
                DEFAULT_PITCH | FF_ROMAN,
				"");

	SendMessage(hwndFilter, WM_SETFONT, (UINT)hfntBig, 0);
	SetWindowPos(hwndFilter, NULL, 0, 0, uiX, uiY / 2, SWP_NOACTIVATE);

	SendMessage(hwndNoFilter, WM_SETFONT, (UINT)hfntBig, 0);
	SetWindowPos(hwndNoFilter, NULL, 0, uiY / 2, uiX, uiY / 2, SWP_NOACTIVATE);
}

//
// Process WM_COMMAND messages
//

static void Command(HWND hWnd, UINT uParam, LPARAM lParam)
{
	int i;
	long Interval;
	long NowTime;
	MSG msg;
	int idThread;

	switch ( uParam ) {
    case IDM_EXIT:
        PostMessage(hWnd, WM_CLOSE, 0, 0l);
        break;

	case IDM_RESET:
		   LastInterval = 0;
		   LastTime = (long)timeGetTime()+1000;
		break;

	case IDM_PEEKLOOP:
		if ( nState != PEEKLOOP ) {
		   if ( nState >= HOG ) {
				MessageBeep(0);
				break;
		   }

		   LastTime = (long)timeGetTime();
		   LastInterval = 0;
		   nState = PEEKLOOP;
		   if (uiTimer) {
			  KillTimer(hwndMain, uiTimer);
			  uiTimer = 0;
		   }
		   SetWindowText(hWnd,"Peek Message Loop");
		}
		break;

	case IDM_TIMER:
		   if ( nState >= HOG ) {
				MessageBeep(0);
				break;
		   }

		if ( nState != TIMERMSG ) {
		   LastTime = (long)timeGetTime();
		   LastInterval = 0;
		   nState = TIMERMSG;
		   uiTimer = SetTimer(hwndMain, 1, 1, NULL);
		   SetWindowText(hWnd,"Timer Messages");
		}
		break;

	case IDM_HOG:
			if ( nState >= HOG ) {
				MessageBeep(0);
				break;
			}

			if (uiTimer) {
			  KillTimer(hwndMain, uiTimer);
			  uiTimer = 0;
			}

			nState = HOG;
			LastTime = (long)timeGetTime();
			LastInterval = 0;
			SetWindowText(hWnd,"Hog the System");

			for (i=0; i < 500; i++ ) {
			   sprintf(buf, "%7.0d", i);
			   SetWindowText(hwndFilter, buf);

			   NowTime = (long)timeGetTime();
			   Interval = NowTime-LastTime;
			   sprintf(buf, "%7ld", Interval);
			   SetWindowText(hwndNoFilter, buf);

			   NoFlickUpdate(hwndNoFilter);
			   NoFlickUpdate(hwndFilter);
			}
			SetWindowText(hwndFilter, "Done");
			nState = 0;

			NowTime = (long)timeGetTime();
			Interval = NowTime-LastTime;
			sprintf(buf, "%7ld", Interval);
			SetWindowText(hwndNoFilter, buf);
		break;

	case IDM_HOGSLEEP:
			if ( nState >= HOG ) {
				MessageBeep(0);
				break;
			}

			if (uiTimer) {
			  KillTimer(hwndMain, uiTimer);
			  uiTimer = 0;
			}

			nState = HOGSLEEP;
			LastTime = (long)timeGetTime();
			LastInterval = 0;
			SetWindowText(hWnd,"Hog the System - Sleep");

			for (i=0; i < 500; i++ ) {
			   sprintf(buf, "%7.0d", i);
			   SetWindowText(hwndFilter, buf);

			   NowTime = (long)timeGetTime();
			   Interval = NowTime-LastTime;
			   sprintf(buf, "%7ld", Interval);
			   SetWindowText(hwndNoFilter, buf);

			   NoFlickUpdate(hwndNoFilter);
			   NoFlickUpdate(hwndFilter);
			   Sleep(1);
			}
			SetWindowText(hwndFilter, "Done");
			nState = 0;

			NowTime = (long)timeGetTime();
			Interval = NowTime-LastTime;
			sprintf(buf, "%7ld", Interval);
			SetWindowText(hwndNoFilter, buf);
		break;

	case IDM_HOGPEEK:
			if ( nState >= HOG ) {
				MessageBeep(0);
				break;
			}

			if (uiTimer) {
			  KillTimer(hwndMain, uiTimer);
			  uiTimer = 0;
			}

			nState = HOGPEEK;
			LastTime = (long)timeGetTime();
			LastInterval = 0;
			SetWindowText(hWnd,"Hog the System - PeekMsg");

			for (i=0; i < 500; i++ ) {
			   if ( PeekMessage (&msg, NULL, 0, 0, PM_REMOVE) ) {
					TranslateMessage (&msg);
					DispatchMessage (&msg);
			   }
			   sprintf(buf, "%7.0d", i);
			   SetWindowText(hwndFilter, buf);

			   NowTime = (long)timeGetTime();
			   Interval = NowTime-LastTime;
			   sprintf(buf, "%7ld", Interval);
			   SetWindowText(hwndNoFilter, buf);

			   NoFlickUpdate(hwndNoFilter);
			   NoFlickUpdate(hwndFilter);
			}

			SetWindowText(hwndFilter, "Done");
			nState = 0;

			NowTime = (long)timeGetTime();
			Interval = NowTime-LastTime;
			sprintf(buf, "%7ld", Interval);
			SetWindowText(hwndNoFilter, buf);
		break;


	case IDM_HOGTHREAD:
			if ( nState >= HOG ) {
				MessageBeep(0);
				break;
			}

			if (uiTimer) {
			  KillTimer(hwndMain, uiTimer);
			  uiTimer = 0;
			}

			nState = HOGTHREAD;
			LastTime = (long)timeGetTime();
			LastInterval = 0;
			SetWindowText(hWnd,"Hog the System - Thread");
			hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HogThread, hWnd, 0, &idThread);
		break;

    default:
        break;
    }
}

LRESULT HogThread(HWND hWnd)
{
	int i;
	long Interval;
	long NowTime;

	SetThreadPriority(hThread, THREAD_PRIORITY_LOWEST );
	for (i=0; i < 500; i++ ) {
	   sprintf(buf, "%7.0d", i);
	   SetWindowText(hwndFilter, buf);

	   NowTime = (long)timeGetTime();
	   Interval = NowTime-LastTime;
	   sprintf(buf, "%7ld", Interval);
	   SetWindowText(hwndNoFilter, buf);

		NoFlickUpdate(hwndNoFilter);
		NoFlickUpdate(hwndFilter);
	}
	nState = 0;

	SetWindowText(hwndFilter, "Done");

	NowTime = (long)timeGetTime();
	Interval = NowTime-LastTime;
	sprintf(buf, "%7ld", Interval);
	SetWindowText(hwndNoFilter, buf);

	ExitThread(0);
	return 0;
}
