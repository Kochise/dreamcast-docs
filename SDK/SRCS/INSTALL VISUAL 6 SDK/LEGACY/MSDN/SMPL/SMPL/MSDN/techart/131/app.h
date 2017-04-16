#ifndef _INC_MAIN
#define _INC_MAIN

// Application Functions

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, 
							LPSTR lpszCmdLine, int cmdShow);

//-------------------------------------------------------------------------
// UNPACKED FUNCTIONS BELOW
#pragma pack(4)	// Use default packing

typedef struct tagAPP
{
    MSG         msg;
    HINSTANCE   hinst;
    HINSTANCE   hinstPrev;
    LPSTR       lpszCmdLine;
    int         cmdShow;
    HWND        hwndFrame;
} APP;

#pragma pack()	//Revert to packing specified on command line
//-------------------------------------------------------------------------

// Globals

extern APP g_app;

#endif  // !_INC_MAIN
