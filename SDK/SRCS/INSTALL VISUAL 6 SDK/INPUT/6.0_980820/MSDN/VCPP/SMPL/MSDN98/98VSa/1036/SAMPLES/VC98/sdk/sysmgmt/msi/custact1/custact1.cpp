#pragma message("Simple Custom Action DLL.  Copyright (c) 1997 Microsoft Corp.")
#if 0  // makefile definitions, build with "nmake -f CustAct1.cpp"
DESCRIPTION = Custom Action Test DLL
MODULENAME = CustAct1
FILEVERSION = 0.20
ENTRY = Action1
!include <MsiTool.Mak>
!if 0  #nmake skips the rest of this file
#endif // end of makefile definitions

// test of external database access
#define WINDOWS_LEAN_AND_MEAN  // faster compile
#include <windows.h>  // included for both CPP and RC passes
#ifndef RC_INVOKED    // start of CPP source code
#include <stdio.h>    // printf/wprintf
#include <tchar.h>    // define UNICODE=1 on nmake command line to build UNICODE
#include "MsiQuery.h" // must be in this directory or on INCLUDE path

UINT __stdcall Action1(MSIHANDLE hInstall)
{
	TCHAR szValue[200];
	DWORD cchValue = sizeof(szValue)/sizeof(TCHAR);
	if (MsiGetProperty(hInstall, "TESTACTION", szValue, &cchValue)
		== ERROR_SUCCESS)
		::MessageBox(0, szValue, TEXT("Greetings from Action1"), MB_OK);
	return ERROR_SUCCESS;
}

#else // RC_INVOKED, end of CPP source code, start of resource definitions
// resource definition go here
#endif // RC_INVOKED
#if 0  // required at end of source file, to hide makefile terminator
!endif // makefile terminator
#endif
