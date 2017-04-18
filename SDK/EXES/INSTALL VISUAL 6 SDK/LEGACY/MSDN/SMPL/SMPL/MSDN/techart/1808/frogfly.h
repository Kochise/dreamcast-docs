
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1993 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/

/***************************************************************************/
/*                 SYMBOLIC CONSTANTS                                      */
/***************************************************************************/

#define FROG_TYPE 0
#define FLY_TYPE 1

#define STATUS_ALIVE 0
#define STATUS_DEAD 1

/* these constants determine in what range the objects will change their directions
   when bouncing on a wall. When the moving routine detects collision with a
   wall, it will reverse the direction and add a random value between 1 and these
   respective values to it. Without these constants, the objects would only
   move on predefined tracks. */

#define XVARIATION 90
#define YVARIATION 90

/* this determines how close the frog must be to a fly to reach and eat it. */
#define CLOSENESS 8

/* this constant determines by how much the frog's calory count is bumped when
   it eats a fly. */

#define FLY_NUTRITION_VALUE 503

/* determines how much calories a fly gains when eating. */

#define KETCHUP_NUTRITION_VALUE 750

/* defines how many calories a fly must have accumulated to multiply */

#define FLY_MULTIPLY_CALORIES 7500

/* determines how many calories an object loses per move */

#define MOVE_DEDUCTION 5

/* the calory count that a frog starts out with */

#define INITIAL_FROG_CALORIES 10000

/* the calory count a fly starts out with */

#define INITIAL_FLY_CALORIES 5000

/* the pixel color that a fly must find on its target field in order to eat.
   A left button mouse click from the user will set a pixel of that color
   on the screen.
   Note that this value must be a "true" color because GetPixel() will
   always return a pure color which does not match against a compound
   color value. GetNearestColor() could be used to eliminate the problem.*/

#define KETCHUP_COLOR RGB(255,0,0)

/* the number of pixels that the frog's direction changes when the user
   controls it with the keyboard */

#define FROGMOVEMENT 15

#define MAX_OBJECTS 200

#define DELAY 50


#define IDM_STARTSIM             100
#define IDM_STOPSIM 		 101
#define IDM_ADDFLY		 102

#define WM_OBJECT_DIED WM_USER+0xc001


BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
