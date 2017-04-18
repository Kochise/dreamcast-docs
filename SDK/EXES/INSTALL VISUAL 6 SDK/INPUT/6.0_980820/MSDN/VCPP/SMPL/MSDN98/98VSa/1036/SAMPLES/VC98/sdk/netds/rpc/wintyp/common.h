/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                  Copyright Microsoft Corp. 1992-1996                 */
/*                      Remote Machine pipe sample                      */
/*                                                                      */
/* FILE     :   common.h                                                */
/*                                                                      */
/* PURPOSE  :   Definitions used in the program                         */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifndef __COMMON_WINTYP_SAMPLE__    // If this file already included - 
#define __COMMON_WINTYP_SAMPLE__    // don't include it again

#include <stdio.h>
#include <stdlib.h>

#include <tchar.h>                  // Included to support UNICODE/ANSI

// Common type definition and defines used in the program
#define FINDEDGE    1       // Action to take - Find edges in image
#define FLIPIMAGE   2       // Action to take - Flip the imagedata

#define PROTOCOL_SEQUENCE   TEXT("ncacn_np")
#define END_POINT           TEXT("\\pipe\\wintyp_sample")
	
// Return values from the program to the OS
#define EXECUTION_FAILED    -1
#define EXECUTION_OK        0

// Exception handler macro
#define DO_EXCEPTION        1       // Execute the exception block

/* Macro for printing out error message and exit the program if an      */
/* error occured                                                        */
#define EXIT_IF_FAIL(x, string){	\
    ((x) != RPC_S_OK)?_tprintf(TEXT("%s returned with error: %d\n"), \
    TEXT(string), (x)),exit(x):0;} 

// Macro for printing messages to the screen
#define PRINT(X, Y) MessageBox(g_hWnd, (X), (Y), MB_OK )

#endif	// __COMMON_WINTYP_SAMPLE__