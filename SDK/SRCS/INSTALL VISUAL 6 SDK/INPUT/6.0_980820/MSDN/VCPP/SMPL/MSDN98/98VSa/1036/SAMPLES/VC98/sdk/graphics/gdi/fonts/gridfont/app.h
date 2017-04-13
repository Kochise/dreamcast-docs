
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/


#ifndef TEXT
// this is non-Unicode Win16 build
#define CHAR   char
#define UCHAR  unsigned char
#define TCHAR  CHAR
#define LPTSTR LPSTR
#define TEXT(x) x
#define COORD   int

#else
#define COORD   LONG
#define HINSTANCE HMODULE
#endif

// Menu item IDs
#define IDM_PRINT       1
#define IDM_EXIT        2
#define IDM_NEXTPAGE    3
#define IDM_PREVPAGE    4
#define IDM_NEXTSECTION 5
#define IDM_PREVSECTION 6
#define IDM_ZOOMIN      7
#define IDM_ZOOMOUT     8
#define IDM_FONT        9
#define IDM_DECIMAL     10
#define IDM_HELP        11
#define IDM_ABOUT       12
#define IDM_ALLPAGES    13

#define IDM_FIRSTPAGE   200  // pseudo menu items
#define IDM_LASTPAGE    201

// String Table IDs
#define IDS_CLASSNAME    1024
#define IDS_MSGCAPTION   1025
#define IDS_UCFONT       1026
#define IDS_ANSIFONT     1027
#define IDS_LABELFONT    1028
#define IDS_HEADERFONT   1029
#define IDS_PRINTERR     1030
#define IDS_NOTIMPLEM    1031

// Manifest Constants
#define DONE TRUE
#define INCH1     1440
#define INCH2      720  // half
#define INCH4      360  // quarter
#define INCH8      180  // eigth
#define INCH10     144  // tenth

// Paper Size: Redefine for non-US
#define PAGEWIDTH  (8*INCH1+INCH2)
#define PAGEHEIGHT (11*INCH1)

#include "resource.h"
