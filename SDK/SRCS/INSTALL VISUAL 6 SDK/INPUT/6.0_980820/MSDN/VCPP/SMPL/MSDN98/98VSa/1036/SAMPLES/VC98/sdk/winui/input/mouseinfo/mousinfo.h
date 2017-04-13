///////////////////////////////////////////////////////////////////////////
// 
// MODULE:      MOUSINFO.H
//
// DESCRIPTION: Include file for the MousInfo.Exe Tool
//
//
//              Copyright (c) 1995 - 1997, Microsoft Corporation. 
//                       All rights reserved
//
//
///////////////////////////////////////////////////////////////////////////

char szAppName[] = "MousInfo";
char szClassName[] = "MousInfoClass";

// Maximum # of chars in title bar
#define MAX_TITLE_LEN 44           

// Index into Button Message Array
#define NO_MESSAGE  0
#define LBU         1   // Left Button Up 
#define RBU         2   // Right Button Up
#define MBU         3   // Middle Button Up
#define LBD         4   // Left Button Down   
#define RBD         5   // Right Button Down  
#define MBD         6   // Middle Button Down 
#define LB2         7   // Left Button Double Click   
#define MB2         8   // Right Button Double Click  
#define RB2         9   // Middle Button Double Click 
#define MW          10  // Mouse Wheel
#define MH          11  // Mouse Hover
#define ML          12  // Mouse Leave

// Resource defines
#define MOUSINFO_ICON 102

#define IDM_MENU    0x0900

#define IDM_TRACK   0x1000
#define IDM_HOVER   0x1001
#define IDM_LEAVE   0x1002

#define IDM_ABOUT   0x2000



// Function Proto's
int		WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT WINAPI MainWndProc(HWND, UINT, WPARAM, LPARAM);
