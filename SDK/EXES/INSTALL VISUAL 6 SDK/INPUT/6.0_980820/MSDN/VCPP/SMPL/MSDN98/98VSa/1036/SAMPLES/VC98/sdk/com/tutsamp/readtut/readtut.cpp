/*+==========================================================================
  File:      READTUT.CPP

  Summary:   Implementation file for the READTUT.EXE code sample
             application. READTUT is a very simple Win32 EXE application
             that uses the ReadTutorial function from the APPUTIL library
             to launch a web browser to view an accompanying HTML tutorial
             file.

             For a comprehensive tutorial code tour of READTUT's contents
             and offerings see the accompanying READTUT.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the READTUT source code.

  Classes:   .

  Functions: WinMain.

  Origin:    12-18-96: atrent - Created for COM Tutorial Samples.

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
  We include APPUTIL.H because we will be building this application using
    the utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include READTUT.H because it has resource definitions specific to
    this tutorial application.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <apputil.h>
#include "readtut.h"


/*F+F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F+++F
  Function: WinMain

  Summary:  The Windows main entry point function for this application.

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
  LPSTR psz;
  char  ch;

  if (SUCCEEDED(CoInitialize(NULL)))
  {
    // Show a message box saying that loading of tutorial is underway.
    DelayBox(hInstance, MAKEINTRESOURCE(IDD_LOADING_MSG), NULL);

    /*--------------------------------------------------------------------
      Walk down the command line looking for an HTML target. The first
      non-whitespace character after whitespace is assumed to be the
      beginning of the HTML target specification. This can be a fully
      qualified internet URL or a path/filename. This is all done in ANSI
      because pszCmdLine is in ANSI. Any command line switches are
      skipped and ignored.
    --------------------------------------------------------------------*/
    psz = pszCmdLine;

    while (ch = *psz)
    {
      BOOL bStop = FALSE;

      switch (ch)
      {
        case '\t':
        case '\n':
        case '\r':
        case ' ':
          // Skip any white space.
          psz = SkipAnsi(psz, TRUE);
          continue;

        case '/':
          // Handle '/' switches here. If '//' then assume it's a URL.
          ch = *(++psz);
          if ('/' == ch)
          {
            --psz;
            bStop = TRUE;
            break;
          }
          else
          {
            // If any '/' switches found skip to next white space.
            psz = SkipAnsi(psz, FALSE);
            continue;
          }

        case '-':
          // If any '-' switches found skip to next white space.
          psz = SkipAnsi(psz, FALSE);
          continue;

        default:
          bStop = TRUE;
          break;
      }

      if (bStop)
        break;

      psz++;
    }

    if (0 == ch)
    {
      /*------------------------------------------------------------------
        If the command line has no HTML target specified then assume a
        file with name <thismodulename>.HTM in the same directory as this
        executing EXE. In this case, the assumed file is READTUT.HTM. Call
        the APPUTIL ReadTutorial utility function to Browse this HTML
        file. If READTUT.EXE is renamed to TUTORIAL.EXE then the assumed
        file to browse is TUTORIAL.HTM.
      ------------------------------------------------------------------*/
      ReadTutorial(hInstance, NULL, NULL);
    }
    else
    {
      // If the command line has an HTML target specified then use it
      // to call the APPUTIL GoWeb utility function to Browse to the
      // specified HTML file on the world wide web.
      GoWeb(hInstance, psz);
    }

    // We're exiting this app so shut down the COM Library.
    CoUninitialize();
  }
  else
  {
    // Show error message box if we can't initialize the COM libraries.
    MessageBox(NULL,
               TEXT(NOCOM_ERROR_STR),
               TEXT(ERROR_TITLE_STR),
               MB_OK | MB_ICONEXCLAMATION);
    iFail = TRUE;
  }

  return iFail;
}
