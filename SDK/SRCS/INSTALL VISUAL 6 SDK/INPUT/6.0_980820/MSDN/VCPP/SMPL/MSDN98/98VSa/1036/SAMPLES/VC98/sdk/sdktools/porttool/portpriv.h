
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

#include <windows.h>

// define ini file section names
#define    IDS_PORTAPIS 	  200
#define    IDS_PORTMESSAGES	  201
#define    IDS_PORTSTRUCTURES	  202
#define    IDS_PORTTYPES	  203
#define    IDS_PORTCONSTANTS	  204
#define    IDS_PORTCUSTOM	  205
#define    IDS_PORTMACROS	  206
#define    IDS_WINDOWSAPPNAME	  207
#define    IDS_INIFILE		  209
#define    IDS_MAPFILENAME	  210


// local constant defintions
#define    FIFTY_K_LINE		  51200
#define    TEN_K_LINE		  10240
#define    TWO_K_LINE		  2056
#define    PT_APIS		  0x00000002
#define    PT_MESSAGES		  0x00000004
#define    PT_TYPES		  0x00000008
#define    PT_STRUCTURES	  0x00000010
#define    PT_MACROS		  0x00000020
#define    PT_CONSTANTS 	  0x00000040
#define    PT_CUSTOM		  0x00000080
#define    PT_IGNORED		  0x00010000


// private port structure
typedef struct tagPort
    {
    int    nSize;
    int    nPosToken;
    int    nPosHelpStr;
    int    nPosIssue;
    int    nPosSuggest;
    DWORD  dwType;
    }PORT, * LPPORT;
