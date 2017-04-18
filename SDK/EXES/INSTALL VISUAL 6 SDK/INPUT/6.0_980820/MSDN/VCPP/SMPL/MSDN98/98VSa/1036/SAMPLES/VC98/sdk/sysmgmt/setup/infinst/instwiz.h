
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1995-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//////////////////////////////
// resource definitions

#include "resource.h"

//
// constants
//
#define NUM_PAGES    6
#define MAX_BUF    	5000
#define MAX_LINE    512

//
// Pages for INSTALL
//
BOOL APIENTRY Welcome(HWND, UINT, UINT, LONG);
BOOL APIENTRY License(HWND, UINT, UINT, LONG);
BOOL APIENTRY YourInfo(HWND, UINT, UINT, LONG);
BOOL APIENTRY Install_Type(HWND, UINT, UINT, LONG);
BOOL APIENTRY Install_Destination(HWND, UINT, UINT, LONG);
BOOL APIENTRY Specify_Location(HWND, UINT, UINT, LONG);
BOOL APIENTRY Custom_Options(HWND, UINT, UINT, LONG);
BOOL APIENTRY Install(HWND, UINT, UINT, LONG);

//
//functions
//
int CreateWizard(HWND, HINSTANCE);
void FillInPropertyPage( PROPSHEETPAGE* , int, LPSTR, DLGPROC);

