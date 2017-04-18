/*+==========================================================================
  File:      REGISTER.CPP

  Summary:   Implementation file for the REGISTER.EXE code sample
             application.  REGISTER is a simple Win32 application that can
             load a COM component server (either EXE or DLL) and command
             it to register or unregister its components in the system
             Registry.

             For a comprehensive tutorial code tour of REGISTER's contents
             and offerings see the tutorial REGISTER.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the REGISTER source code.

  Classes:   CMainWindow.

  Functions: WinMain.

  Origin:    12-28-96: atrent - Based on SELFREG by Kraig Brockschmidt.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is only intended as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

/*---------------------------------------------------------------------------
  We include WINDOWS.H for all Win32 applications.
  We include OLE2.H because we will be calling the COM/OLE Libraries.
  We include INITGUID.H only once (here) in the entire app because we
    will be using GUIDs and want them as constants in the data segment.
  We include APPUTIL.H because we will be building this application using
    the utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include REGISTER.H because it has resource definitions
    specific to this REGISTER application.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <initguid.h>
#include <apputil.h>
#include "register.h"


/*F+F++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: ErrorBoxID

  Summary:  Utility function to show an error message box dialog.
            Parent window is desktop.

  Args;     HINSTANCE hInst,
              Handle to app instance.
            UINT uStrID
              Resource ID of the error string to display.

  Returns:  int
              TRUE if success; FALSE if not.
              Result of the MessageBox call.
------------------------------------------------------------------------F-F*/
int ErrorBoxID(
      HINSTANCE hInst,
      UINT uStrID)
{
  int iResult = FALSE;
  CHAR szTitle[MAX_STRING];
  CHAR szError[MAX_STRING];

  if (LoadStringA(hInst, IDS_ERROR_TITLE, szTitle, MAX_STRING))
    if (LoadStringA(hInst, uStrID, szError, MAX_STRING))
      iResult = MessageBoxA(
                  NULL,
                  szError,
                  szTitle,
                  MB_OK | MB_ICONEXCLAMATION);

  return (iResult);
}


/*F+F++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Function: SkipAnsiString

  Summary:  Utility function to scan an input ANSI string and either skip
            white characters or skip non-white characters.

  Args;     LPSTR psz,
              Input ANSI string to be scanned.
            BOOL bSkip)
              Input boolean determining whether to skip white space
              or not.  TRUE means skip white space; FALSE means skip
              non-white chars.

  Returns:  LPSTR
              String pointer after the skip.
------------------------------------------------------------------------F-F*/
LPSTR SkipAnsiString(
         LPSTR psz,
         BOOL bSkipWhite)
{
  char ch;
  BOOL bWhite;

  while (ch = *psz)
  {
    bWhite = ('\n'==ch || '\r'==ch || '\t'==ch || ' '==ch);

    if ((bSkipWhite && !bWhite) || (!bSkipWhite && bWhite))
      break;

    psz++;
  }

  return psz;
}


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: WinMain

  Summary:  The Windows main entry point function for this application.
            Initializes the application, the COM Libraries, and starts
            the main application message loop.

  Args:     HINSTANCE hInstance,
              Instance handle; a new one for each invocation of this app.
            HINSTANCE hPrevInstance,
              Instance handle of the previous instance. NULL in Win32.
            LPSTR lpCmdLine,
              Windows passes a pointer to the application's
              invocation command line.
            int nCmdShow)
              Bits telling the show state of the application.

  Returns:  int
              msg.wParam (upon exit of message loop).
              FALSE if this instance couldn't initialize and run.
F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F---F-F*/
extern "C" int PASCAL WinMain(
                        HINSTANCE hInstance,
                        HINSTANCE hPrevInstance,
                        LPSTR pszCmdLine,
                        int nCmdShow)
{
  int   iFail = FALSE;
  BOOL  bEXE = FALSE;
  BOOL  bUnreg = FALSE;
  LPSTR psz;
  char  ch;

  /*--------------------------------------------------------------------
    Walk down the command line looking for /u and /e in any order.
    The first non-whitespace character after whitespace that is not
    a "/" is assumed to be the beginning of the server filename.
    This is all done in ANSI because pszCmdLine is in ANSI.
  --------------------------------------------------------------------*/
  psz = pszCmdLine;

  while (ch = *psz)
  {
    BOOL    bStop = FALSE;

    switch (ch)
    {
      case '\t':
      case '\n':
      case '\r':
      case ' ':
        // Skip any white space.
        psz = SkipAnsiString(psz, TRUE);
        continue;

      case '/':
      case '-':
        // Check what option this is, then skip to next whitespace.
        ch = *(++psz);
        if ('u' == ch)
          bUnreg = TRUE;
        if ('e' == ch)
          bEXE = TRUE;
        psz = SkipAnsiString(psz, FALSE);
        continue;

      default:
        bStop = TRUE;
        break;
    }

    if (bStop)
      break;

    psz++;
  }

  if (0 != ch)
  {
    // If the command line was not null, launch the specified EXE or
    // load the specified DLL and tell either to do their registration
    // or unregistartion.
    if (bEXE)
    {
      UINT uError;
      CHAR szEXE[MAX_PATH];

      wsprintfA(
        szEXE,
        "%s %s",
        psz,
        bUnreg ? "/UNREGSERVER" : "/REGSERVER");

      // We WinExec the .EXE server passing /unregserver or /regserver.
      uError = WinExec(szEXE, SW_HIDE);
      if (uError < 32)
      {
        ErrorBoxID(hInstance, IDS_EXERUN_FAIL);
        iFail = TRUE;
      }
      else
      {
        // Show a timed message box indicating registration success.
        DelayBox(hInstance, MAKEINTRESOURCE(IDD_SUCCESS_MSG), NULL);
      }
    }
    else
    {
      // Because we load the DLL server into our own (ie, REGISTER.EXE)
      // process space, call to initialize the COM Library.  Use the
      // SUCCEEDED macro to detect success.  If fail then exit app
      // with error message.
      if (SUCCEEDED(CoInitialize(NULL)))
      {
        HINSTANCE hMod;

        // Load the Server DLL into our process space.
        hMod = LoadLibraryA(psz);

        if (NULL != hMod)
        {
          HRESULT (STDAPICALLTYPE *pfn)(void);

          if (bUnreg)
          {
            (FARPROC&)pfn = GetProcAddress(hMod, "DllUnregisterServer");

            if (NULL != pfn)
              iFail = FAILED((*pfn)());

            if (iFail)
              ErrorBoxID(hInstance, IDS_DLLUNREG_FAIL);
            else
            {
              // Show a timed message box indicating registration success.
              DelayBox(hInstance, MAKEINTRESOURCE(IDD_SUCCESS_MSG), NULL);
            }
          }
          else
          {
            (FARPROC&)pfn = GetProcAddress(hMod, "DllRegisterServer");

            if (NULL != pfn)
              iFail = FAILED((*pfn)());
            if (iFail)
              ErrorBoxID(hInstance, IDS_DLLREG_FAIL);
            else
            {
              // Show a timed message box indicating registration success.
              DelayBox(hInstance, MAKEINTRESOURCE(IDD_SUCCESS_MSG), NULL);
            }
          }
          CoFreeLibrary(hMod);
        }
        else
          ErrorBoxID(hInstance, IDS_LOADLIB_FAIL);

        // We're exiting this app so shut down the COM Library.
        CoUninitialize();
      }
      else
        ErrorBoxID(hInstance, IDS_COMINITFAILED);
    }
  }

  return iFail;
}
