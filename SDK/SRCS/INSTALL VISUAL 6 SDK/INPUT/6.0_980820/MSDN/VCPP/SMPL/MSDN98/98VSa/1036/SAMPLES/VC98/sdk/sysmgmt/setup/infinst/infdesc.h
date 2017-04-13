
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1995-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//Header file for inf specific data

//
// SetupApi helpers for the main exe
// implemented in doinst.c
//
BOOL DoInstallation(HWND, INSTALLINFO*);

//
// These are the custom DirIds for the inf
// Doinst.c maps real install time strings
// to these numbers.
//
// The ids are mapped exactly to the numbers in the inf
// custom ids must be > 65536 (decimal)
// 
// I have chosen 65600 as a starting number at random
//
#define DESTINATION_DIR     65600

//
// optional inf section names, in this sample these
// are not platform speific -- like MS Word templates for examples
//
#define INF_OPTION2         TEXT("Option2Section")
#define INF_OPTION3         TEXT("Option3Section")
#define INF_OPTION4         TEXT("Option4Section")

//
// Main inf section name, in this sample this
// is platform speific -- say the executables for your
// application
//
#ifdef _ALPHA_
#define INF_OPTION1         TEXT("ProductInstall.Alpha")
#else

#ifdef  _MIPS_
#define INF_OPTION1         TEXT("ProductInstall.Mips")
#else

#ifdef  _PPC_
#define INF_OPTION1         TEXT("ProductInstall.PPC")

#else // default to X86
#define INF_OPTION1         TEXT("ProductInstall")
#endif
#endif
#endif


