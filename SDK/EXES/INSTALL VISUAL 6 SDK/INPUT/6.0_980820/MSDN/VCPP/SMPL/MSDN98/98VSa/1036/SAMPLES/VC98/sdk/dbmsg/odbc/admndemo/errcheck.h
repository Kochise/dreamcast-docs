//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|
//|    Title: ERRCHECK.H
//|
//|      This include file contains the definitions for the ERRCHECK.C module.
//|         This module contains common error checking functions.
//|
//*---------------------------------------------------------------------------------
#ifndef errcheck_DEFS
#define errcheck_DEFS

#include <windows.h>
#include <string.h>
#include "standard.h"
#include "sql.h"
#include "sqlext.h"
#include "child.h"



//------------------------------------------------------------------------
//  Defines
//------------------------------------------------------------------------
#define  RTN_MSG_SIZE      SQL_MAX_MESSAGE_LENGTH - 1

#define PostError(str)                                            \
      DoPostError(str, __FILE__, __LINE__)


//------------------------------------------------------------------------
//  Declare global variables
//------------------------------------------------------------------------
extern dCSEG(char) szErrTitle[];
extern dCSEG(char) szError[];
extern dCSEG(char) szOutOfMemory[];
extern dCSEG(char) szInvalidParms[];
extern dCSEG(char) szRegisterClassFailed[];


//------------------------------------------------------------------------
//  Declare function prototypes
//------------------------------------------------------------------------
LPSTR GetSQLState(SWORD handletype, SQLHANDLE handle, SWORD *psMsgNum,
                  LPSTR szState, SDWORD FAR * pfNative, LPSTR szMessage);
void DoPostError(LPSTR szErr, LPSTR szFile, int cbLine);
void PrintErrors(CHILDINFO FAR * ci, SWORD handletype);
void PrintErrorsHwnd(HWND hwnd, SWORD handletype, SQLHANDLE handle);
void DisplayErrors(HWND hwnd, LPSTR title, SWORD handletype, SQLHANDLE handle);


#endif
