/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    WinMain.cpp

Abstract:

    Windows entry point into game.

-------------------------------------------------------------------*/

#include "DC.h"

// External funciton in Main.cpp
int GameMain(void);

// Entry point into game from Windows. 
// Just saves the instance handle and then calls a 
// platform independent main function.
extern "C" int APIENTRY 
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
//int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	// Store hInstance in a global so other routines can access it.
	gHInstance=hInstance;

	int Status=GameMain();

	// Display the error message if there was one.
	int ErrorMessage=GetLastErrorMessage();
	if (ErrorMessage!=NO_ERROR_MESSAGE)
		DisplayErrorMessage(ErrorMessage);

	return Status;
}

