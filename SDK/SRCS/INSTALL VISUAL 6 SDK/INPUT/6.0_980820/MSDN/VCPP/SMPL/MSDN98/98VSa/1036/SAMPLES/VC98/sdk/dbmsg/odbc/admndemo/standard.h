//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   STANDARD.H
//|      This module contains standard includes which are required by many modules.
//|         This include file is not specific for any tool.
//|   Notes:
//|      1) If using this file for a DLL, #define STANDARD_DLL, otherwise it is
//|            assumed that it is being used for a Windows application.
//*---------------------------------------------------------------------------------
#ifndef STANDARD_DEFS
#define STANDARD_DEFS

#include <windows.h>
#include "sql.h"
#include "sqlext.h"


//----------------------------------------------------------------------------------
//    Defines and macros
//----------------------------------------------------------------------------------
#define TEMP_SIZE    50
#define MAX_BUFF     1000
#define  MAXBUFF           256
#define  MAXFILEBUFF       32000
#define  DFTBUFFSIZE       30
#define  LARGEBUFF         65535

//
// When calling ODBC functions, you should allow for the case where
// SQL_SUCCESS_WITH_INFO was returned.  Unless you want to see the informational
// SQL state, you should treat these as the same.  The following macros are
// handy to do just that.
//
#define RC_SUCCESSFUL(rc)  (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO)
#define RC_NOTSUCCESSFUL(rc) (!(RC_SUCCESSFUL(rc)))

//
// Win 3.x specific items
//
#ifndef WIN32

#define INTFUN FAR PASCAL
#define EXTFUN FAR PASCAL __export
#define dCSEG(type) const type _based(_segname("_CODE"))

//
// 32-bit stuff
//
#else
#define MoveTo(hdc, x, y)        MoveToEx(hdc, x, y, NULL)
#define dCSEG(type) const type
#define INTFUN WINAPI
#define EXTFUN WINAPI

#define WRITE     OF_WRITE
#define READ      OF_READ
#endif



#ifdef WIN32
#else
#endif
#define VSZFile static char vszFile[]=__FILE__;

#ifdef _DEBUG
#define DEBUGMSG(msg) OutputDebugString((LPSTR)msg)
#else
#define DEBUGMSG(msg)
#endif


#ifdef _DEBUG
void FAR * DebugGetMemory(DWORD size, LPSTR szFile, int cbLine);
void DebugReleaseMemory(LPVOID ptr, LPSTR szFile, int cbLine);
void WinAssertReal(int exp, LPSTR msg, LPSTR file, int line);

#define WinAssert(exp, msg)                                             \
         WinAssertReal(exp, msg, vszFile, __LINE__);
#define GetMemory(size) DebugGetMemory(size, vszFile, __LINE__)
#define ReleaseMemory(size) DebugReleaseMemory(size, vszFile, __LINE__)
#define DEBUGADDR(title, hwnd, ptr)                                                                      \
   {                                                                                                     \
   static char szTmp[100];                                                                               \
   wsprintf(szTmp, "%s, hwnd: %04X, ptr: %04X:%04X", (LPSTR)title, hwnd, HIWORD(ptr), LOWORD(ptr));      \
   DEBUGMSG(szTmp);                                                                                      \
   }
#else
#define  WinAssert(exp, msg)
#define GetMemory(size) DoGetMemory(size)
#define ReleaseMemory(size) DoReleaseMemory(size)
#define DEBUGADDR(p1,p2,p3)
#endif

#define NumItems(s) (sizeof (s) / sizeof(s[0]))

#define ABS(val) ((val < 0) ? (val * -1) : (val))

//*---------------------------------------------------------------------------------
//|   Global variables
//*---------------------------------------------------------------------------------
dCSEG(char) szui[];
dCSEG(char) szEmpty[];

//*---------------------------------------------------------------------------------
//|   Function prototypes
//*---------------------------------------------------------------------------------
void FAR * DoGetMemory(DWORD size);
void DoReleaseMemory(LPVOID ptr);
void RemoveCrLf(LPSTR instr);
void GetNewDirectory(LPSTR outstr, LPSTR instr);
BOOL ValidName(LPSTR instr);
int lpatoi(LPSTR instr);

LPSTR EXTFUN GetidsString(UINT ids, LPSTR szOut, UINT cbSize);
VOID FAR CDECL szWrite(HWND hwnd, LPSTR szFmt, ...);
int FAR CDECL szMessageBox(HWND hwnd, UINT style, LPSTR szTitle, LPSTR szFmt, ...);


#endif
