/******************************Module*Header*******************************\
* Module Name: bndscan.h
*
* Contains the #defines used for finding boundary points
*
* Created: 19-Mar-1992 16:10:14
* Author: Petrus Wong
*
* Copyright (C) 1993-1997 Microsoft Corporation
*
* The eight neighbors of any boundary point are represented by thier
* relative direction.  For example, north, south, east and west.
* The directions are #defined clockwise.  And these defined values will
* be used with shifting operations.
*
* Dependencies:
*
*   none
*
\**************************************************************************/
#define EAST        0x0001
#define SOUTHEAST   0x0002
#define SOUTH       0x0004
#define SOUTHWEST   0x0008
#define WEST        0x0010
#define NORTHWEST   0x0020
#define NORTH       0x0040
#define NORTHEAST   0x0080

//
// Turning left and right are also defined.
//
#define LEFT	    1
#define RIGHT	    2

//
// This is maximum number of boundary points we are going to handle.
// Works pretty well in most cases.  This limit exists for catching
// the unprobable situation of infinite loop.
//
#define MAXPOINT    50000

#define MM_SELCLIPRGN           7050

//
// Internal data structure used for boundary point finding only.
//
typedef struct _node {
    DWORD   dwDirection;
    BOOL    bEscape;
}NODE;

//
// externs
//
extern HPEN hpnGreen;
extern HPEN hpnBlack;
extern HWND ghwndMain;
extern char gtext[256];
extern HBITMAP SaveBitmap   (HWND, HPALETTE);
extern LONG lMul(LONG, LONG);
extern LONG lDiv(LONG, LONG);
