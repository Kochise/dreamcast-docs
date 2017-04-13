
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/******************************************************************************\
*
*                               GETPDRIV.H
*
\******************************************************************************/
#include "strings.h"


/******************************************************************************\
*                           SYMBOLIC CONSTANTS
\******************************************************************************/

#define ERR_MOD_NAME        IDS_ERR_GETPDRIV



/******************************************************************************\
*                            GLOBAL VARIABLES
\******************************************************************************/

char *gaDrvInfo[] =

    {   "DRIVER_INFO_1",
        "  pName\t\t%s",

        "DRIVER_INFO_2",
        "  cVersion\t%ld",
        "  pName\t\t%s",
        "  pEnvironment\t%s",
        "  pDriverPath\t%s",
        "  pDataFile\t%s",
        "  pConfigFile\t%s" };



/******************************************************************************\
*                          EXTERNAL VARIABLES
\******************************************************************************/

extern HWND ghwndMain;
extern char gszDeviceName [];
extern char gszDriverName [];
extern char gszPort       [];



/******************************************************************************\
*                               MACROS
\******************************************************************************/

#define outstr()  SendDlgItemMessage (hwnd, DID_LISTBOX, LB_INSERTSTRING, \
                                      (UINT)-1, (LONG) buf);



/******************************************************************************\
*                          FUNCTION PROTOTYPES
\******************************************************************************/

BOOL DisplayPrinterDriverInfo (HWND);
