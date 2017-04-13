/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*                  Copyright Microsoft Corp. 1992-1996                 */
/*                      Remote Machine pipe sample                      */
/*                                                                      */
/*  FILE    :   common.h                                                */
/*                                                                      */
/*  PURPOSE :   Definitions used in the program                         */
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#ifndef __COMMON_PIPE_SAMPLE__      // If this file has be included before  
#define __COMMON_PIPE_SAMPLE__      // Don't include it again

#include <shellapi.h>               // CommandLineToArgvw is defined here
#include <tchar.h>                  // Included to support UNICODE/ANSI
#include <stdio.h>
#include <stdlib.h>

// Common type definition and defines used in the program
// Return values from the program to the OS
#define EXECUTION_FAILED    -1
#define EXECUTION_OK        0

// Exception handler macro
#define DO_EXCEPTION        1       // Execute the exception block

#define SCRAMBLE    1               // Action to take - Encode the file
#define UNSCRAMBLE  2               // Action to take - Decode the file

#define PROTOCOL_SEQUENCE   TEXT("ncacn_np")
#define END_POINT           TEXT("\\pipe\\pipe_sample")
	
// This struct is used by the client to keep track of the state	
typedef struct	{
    FILE        *hOld;          // Handle to the old file
    FILE        *hNew;          // Handle to the new file
    _TUCHAR     *pszOldName;       // Name of the old file
    _TUCHAR     *pszNewName;       // Name of the new file
} pipe_state;

// Macro for printing out error message and exit the program if an 
// error occured
#define EXIT_IF_FAIL(x, string){   \
    ((x) != RPC_S_OK)?_tprintf(TEXT("%s returned with error: %d\n"), \
    TEXT(string), (x)),exit(x):0;} 

#endif  //  __COMMON_PIPE_SAMPLE__