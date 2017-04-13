
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/******************************************************************************\
*
*  PROGRAM:     GETPDRIV.C
*
*  PURPOSE:     Handles display of information returned by call to
*               GetPrinterDriver. GetPrinterDriver is called for the
*               currently selected printer (in the tool bar comobobox),
*               and the results are formatted and displayed in a dialog
*               box.
*
*  FUNTIONS:    GetPrinterDriverDlgProc - handles messages for dialog
*               DisplayPrinterDriverInfo- retrieves & displays printer
*                                           driver info
*
\******************************************************************************/

#include <windows.h>
#include <winspool.h>
#include <string.h>
#include <stdio.h>
#include <winspool.h>
#include "common.h"
#include "getpdriv.h"


/******************************************************************************\
*
*  FUNCTION:    GetPrinterDriverDlgProc (standard dlg proc INPUTS/RETURNS)
*
*  COMMENTS:    Processes messages for getPrinterDriver dialog box
*
\******************************************************************************/

LRESULT CALLBACK GetPrinterDriverDlgProc (HWND   hwnd,   UINT msg,
                                          WPARAM wParam, LPARAM lParam)
{
  switch (msg)
  {
    case WM_INITDIALOG:
    {
      BOOL bReturn;
      char buf[BUFSIZE];

      //
      // shove all the printer driver info in the list box
      //

      SetCursor (LoadCursor (NULL, IDC_WAIT));
      bReturn = DisplayPrinterDriverInfo (hwnd);
      SetCursor (LoadCursor (NULL, IDC_ARROW));

      if (!bReturn)
      {
        EndDialog (hwnd, TRUE);
      }

      //
      // set window title to reflect current device
      //

      else
      {
        sprintf (buf, "GetPrinterDriver: %s;%s;%s", gszDeviceName, gszPort,
                 gszDriverName);

        SetWindowText (hwnd, (LPCSTR) buf);
      }

      break;
    }

    case WM_COMMAND:

      switch (LOWORD (wParam))
      {
        case DID_OK:

          EndDialog (hwnd, TRUE);
          return 1;
      }
      break;
  }
  return 0;
}



/******************************************************************************\
*
*  FUNCTION:    DisplayPrinterDriverInfo
*
*  INPUTS:      hwnd - handle of GetPrinterDriver dialog box
*
*  RETURNS:     TRUE if successful,
*               FALSE otherwise
*
\******************************************************************************/


BOOL DisplayPrinterDriverInfo (HWND hwnd)
{
  HANDLE        hPrinter;
  DWORD         dwBytesNeeded;
  DRIVER_INFO_1 *pDriverInfo1;
  DRIVER_INFO_2 *pDriverInfo2;
  char          buf[BUFSIZE];
  char          pEnvironment[BUFSIZE] = "";
  BOOL          bReturn = TRUE;

  //
  // open selected printer & alloc buffers & get sundry info, close printer
  //

  OpenPrinter (gszDeviceName, &hPrinter, NULL);

  if (!hPrinter)
  {
    char buf[BUFSIZE];

    sprintf (buf, GetStringRes(IDS_FMT_OPNPRTFAIL), gszDeviceName);
    ErrMsgBox ((LPCSTR) buf, ERR_MOD_NAME);
    bReturn  = FALSE;
    goto display_prt_drv_info_done1;
  }

  GetPrinterDriver (hPrinter, pEnvironment, 1, NULL, 0, &dwBytesNeeded);

  //
  // simple error checking, if these work assume rest will too
  //

  if (!(pDriverInfo1 = (DRIVER_INFO_1 *) LocalAlloc (LPTR, dwBytesNeeded)))
  {
    ErrMsgBox (GetStringRes(IDS_LALLOCFAIL), ERR_MOD_NAME);
    bReturn = FALSE;
    goto display_prt_drv_info_done1;
  }

  if (!GetPrinterDriver (hPrinter, pEnvironment, 1, (LPBYTE) pDriverInfo1,
                         dwBytesNeeded, &dwBytesNeeded))
  {
    ErrMsgBox (GetStringRes(IDS_GETPRTDRVFAIL), ERR_MOD_NAME);
    bReturn = FALSE;
    goto display_prt_drv_info_done2;
  }

  GetPrinterDriver (hPrinter, pEnvironment, 2, NULL, 0, &dwBytesNeeded);
  pDriverInfo2 = (DRIVER_INFO_2 *) LocalAlloc (LPTR, dwBytesNeeded);
  GetPrinterDriver (hPrinter, pEnvironment, 2, (LPBYTE) pDriverInfo2,
                    dwBytesNeeded, &dwBytesNeeded);

  ClosePrinter (hPrinter);

  //
  // shove info in listbox
  //

  sprintf (buf, gaDrvInfo[0]);
  outstr();

  sprintf (buf, gaDrvInfo[1], pDriverInfo1->pName);
  outstr();

  sprintf (buf, gaDrvInfo[2]);
  outstr();

  sprintf (buf, gaDrvInfo[3], pDriverInfo2->cVersion);
  outstr();

  sprintf (buf, gaDrvInfo[4], pDriverInfo2->pName);
  outstr();

  sprintf (buf, gaDrvInfo[5], pDriverInfo2->pEnvironment);
  outstr();

  sprintf (buf, gaDrvInfo[6], pDriverInfo2->pDriverPath);
  outstr();

  sprintf (buf, gaDrvInfo[7], pDriverInfo2->pDataFile);
  outstr();

  sprintf (buf, gaDrvInfo[8], pDriverInfo2->pConfigFile);
  outstr();

  LocalFree (LocalHandle (pDriverInfo2));

display_prt_drv_info_done2:

  LocalFree (LocalHandle (pDriverInfo1));

display_prt_drv_info_done1:

  return bReturn;
}

