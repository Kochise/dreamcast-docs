//************************************************************************
//**
//**  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//**  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//**  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
//**  A PARTICULAR PURPOSE.
//**
//**  Copyright (C) 1993 - 1997 Microsoft Corporation. All Rights Reserved.
//**
//**  IDFEDIT.H
//**
//**  DESCRIPTION:
//**
//**
//**  HISTORY:
//**     04/22/93       created.
//**
//************************************************************************

#if !defined IDFEDIT_H
#define IDFEDIT_H

#include <idf.h>
#include "oldidf.h"
#include "res.h"
#include "globals.h"

// main.c
//
int  WINAPI ErrorBox(
   UINT    wStringID,      // stringtable ID
   UINT    wType,          // type of message box (MB_xxx flags)
   ...);

#define EB_FATAL (MB_OK | MB_ICONEXCLAMATION)
#define EB_ERROR (MB_OK | MB_ICONHAND)
#define EB_QUERY (MB_YESNO | MB_ICONQUESTION)
#define EB_INFO  (MB_OK | MB_ICONINFORMATION)
#define EB_YNC   (MB_YESNOCANCEL | MB_ICONQUESTION)

#if !defined SZCODE
  #define SZCODE STATIC CONST TCHAR
#endif

// debug stuff
//
#define SQUAWKNUMZ(num) #num
#define SQUAWKNUM(num) SQUAWKNUMZ(num)
#define SQUAWK __FILE__ "(" SQUAWKNUM(__LINE__) ") : --"
#if defined _DEBUG || defined DEBUG || defined DEBUG_RETAIL
  #define STATICFN
  #define DEBUGLINE __FILE__ "(" SQUAWKNUM(__LINE__) ") "
  #ifdef _X86_
    #define INLINE_BREAK _asm {int 3}
  #else
    #define INLINE_BREAK DebugBreak()
  #endif
  #define assert(exp) {\
      if (!(exp)) {\
          OutputDebugString(DEBUGLINE "assert failed: " #exp "\r\n"); \
	      INLINE_BREAK; \
	      }\
	  }
#else
  #define STATICFN static
  #define assert(a) ((void)0)
  #define INLINE_BREAK
#endif

// idf.c
//
BOOL WINAPI PromptForIDFName (
    HWND    hwnd,
    LPTSTR  lpszPath,
    LPTSTR  lpszTitle,
    BOOL    fSave);

BOOL LoadIDFFromFile (
   LPIDFHEAD pIDF,
   LPTSTR    pszFile);

BOOL SaveIDFToFile (
   LPIDFHEAD pIDF,
   LPTSTR    pszFileIn);

VOID FreeIDFFile (
   LPIDFHEAD pIDF);

LPINSTRUMENT WINAPI NewIDFInstrum (
   LPIDFHEAD  pIDF,
   LPRIFFLIST pList,
   LPSTR      pszInstrument);

VOID DeleteInstrum (
   LPIDFHEAD pIDF);

VOID CopyInstrumToClip (
   LPIDFHEAD pIDF);

VOID PasteInstrum (
   LPIDFHEAD pIDF);

LPRIFF FindListChunk (
   LPRIFFLIST pList,
   DWORD      fccToFind);

void CopyInstrumData (
   LPINSTRUMENT pInstrum, 
   LPRIFFLIST   pList);

LPVOID CopyForEditing (
   LPVOID pData, 
   UINT cbData);

// head.c
//
LONG CALLBACK HeadWndProc (
   HWND   hWnd,
   UINT   wMsgID,
   WPARAM wParam,
   LPARAM lParam);

#define HM_REFRESH_TREE   (WM_USER+1)   
#define Head_RefreshTree(hWnd) SendMessage (hWnd, HM_REFRESH_TREE, 0, 0);


// ======================== Global Variables =======================

// if NO_VARS is defined, dont refer to global variables
// at all.  this is typically used when creating binary
// data using structures defined in this file.
//
#ifndef NO_VARS
//
// if DECLARE_VARS is defined, create global variables
// otherwise just refer to them as externs.  this works
// so long as only one module defines DECLARE_VARS (usually winmain)
//
#ifdef DECLARE_VARS

 #define PUBLIC
 PUBLIC CONST TCHAR cszHdrClass[]  = "IDFHdr";
 PUBLIC CONST TCHAR cszInstrumClass[]  = "IDFInstrum";

#else

 #define PUBLIC extern
 PUBLIC CONST TCHAR cszHdrClass[];
 PUBLIC CONST TCHAR cszInstrumClass[];

#endif

PUBLIC HINSTANCE hInst;       // WinMain, set from hInstance
PUBLIC HWND      hWndMain;    // WinMain, set from CreateWindow
PUBLIC TCHAR     szApp[32];   // WinMain, set from IDS_APPNAME string
PUBLIC DWORD     fdwExStyle;  // WinMain
#ifdef USE_MDI
 PUBLIC HWND      hWndClient;  // handle to MDI Client
#endif

#endif // end of NO_VARS ifdef

#endif // IDFEDIT_H
