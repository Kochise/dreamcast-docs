
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

// include windows.h before including this header file into your source

// define some string length constants
#define    MAXTOKENLEN		  100
#define    MAXHELPLEN		  100
#define    MAXISSUELEN		  1024
#define    MAXSUGGESTLEN	  1024

// define option flags
#define    PT_IGNORETOKEN	  0x00010000	// informs port.dll to ignore this token
#define    PT_DEFAULT		  0x00000000	// checks for everything
#define    PT_NOAPIS		  0x00000002	// do not check for APIs
#define    PT_NOMESSAGES	  0x00000004	// do not check for messages
#define    PT_NOTYPES		  0x00000008	// do not check for types
#define    PT_NOSTRUCTURES	  0x00000010	// do not check for structures
#define    PT_NOMACROS		  0x00000020	// do not check for macros
#define    PT_NOCONSTANTS	  0x00000040	// do not check for constants
#define    PT_NOCUSTOM		  0x00000080	// do not check for custom tokens
#define    PT_IGNORECASE	  0x00000100	// disable case sensitivity
						//   (not helpful for APIs and MSGs)


// result structure returns results of line checked
typedef struct tagResult
    {
    char    *lpszToken;
    char    *lpszHelpStr;
    char    *lpszIssue;
    char    *lpszSuggest;
    int     nPosToken;
    }RESULT, * LPRESULT;


// function checks a string for a matching token
BOOL WINAPI CheckString (char *lpszSrc, DWORD fSearch, LPRESULT lpResult);
//    lpszSrc  - source string to search
//    fSearch  - search flags define how to check string
//    lpResult - structure of data passed to/from DLL
//
// When calling this function you must pass a valid LPRESULT structure having
//   allocated memory for each of the string pointer fields in the structure.
//   It is recommended that you allocate enough memory to fulfill the max length
//   for each field as defined by the constants above.	Also, you must indicate the
//   actual length of each string allocated in the first WORD of each string.  The
//   CheckString function will copy at most length-1 characters and zero terminate
//   the string for you.
//
// New for version 2.2.  The option to ignore a specific issue for the duration of
//   the DLL is loaded is now provided.  This is done by calling the CheckString
//   function with the PT_IGNORETOKEN bit set in the search flags.  In this case,
//   the CheckString function toggles the ignore state on a token matching the string
//   lpszSrc passed to the function.  The lpResult parameter is ignored in this case.
//   Successive calls with the PT_IGNORETOKEN bit can be used to toggle the state of
//   any token to IGNORED or not IGNORED.
//  NOTE: The PT_IGNORETOKEN flag cannot be reset by the DLL since the search flags
//   parameter is passed by value.  The application that calls CheckString must reset
//   the flag when the function returns.
//
