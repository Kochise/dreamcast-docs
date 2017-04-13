
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
*  PROGRAM:     GETCAPS.C
*
*  PURPOSE:     Handles display of information returned by call to
*               GetDeviceCaps. GetDeviceCaps is called for the
*               currently selected deivce (in the tool bar comobobox),
*               and the results are formatted and displayed in a dialog
*               box.
*
*  FUNTIONS:    GetDeviceCapsDlgProc - handles messages for dialog
*               DisplayDeviceCapsInfo- retrieves device caps info
*               TranslateDeviceCaps  - displays a capability in listbox
*               ComplexDeviceCapsLine- formats a bitfield capability
*
\******************************************************************************/

#include <windows.h>
#include <winspool.h>
#include <string.h>
#include <stdio.h>
#include <winspool.h>
#include "common.h"
#include "getcaps.h"



/******************************************************************************\
*
*  FUNCTION:    GetDeviceCapsDlgProc (standard dialog procedure INPUTS/RETURNS)
*
*  COMMENTS:    Processes messages for GetDeviceCaps dialog box
*
\******************************************************************************/

LRESULT CALLBACK   GetDeviceCapsDlgProc (HWND   hwnd, UINT msg, WPARAM wParam,
                                         LPARAM lParam)
{
  switch (msg)
  {
    case WM_INITDIALOG:
    {
      BOOL bReturn;
      char buf[BUFSIZE];

      ghwndDevCaps = hwnd;

      //
      // shove all the caps info in the list box
      //

      SetCursor (LoadCursor (NULL, IDC_WAIT));
      bReturn = DisplayDeviceCapsInfo ();
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
        sprintf (buf, "GetDeviceCaps: %s;%s;%s", gszDeviceName, gszPort,
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
*  FUNCTION:    DisplayDeviceCapsInfo
*
*  RETURNS:     TRUE if successful,
*               FALSE otherwise
*
*  COMMENTS:    Retrieves all device caps for current deivce & calls
*                 TranslateCaps to insert them in the dialog's listbox.
*
\******************************************************************************/

BOOL DisplayDeviceCapsInfo ()
{
  HDC hdc;
  int i, iValue;

  if (!strcmp (gszDeviceName, "Display"))
  {
    if (!(hdc = GetDC (ghwndDevCaps)))
    {
      ErrMsgBox (GetStringRes(IDS_GETDCFAIL), ERR_MOD_NAME);
      return FALSE;
    }
  }

  else
  {
    if (!(hdc = CreateDC (gszDriverName, gszDeviceName, gszPort, NULL)))
    {
      char buf[BUFSIZE];

      sprintf (buf, GetStringRes(IDS_FMT_CREDCFAIL),
               gszDriverName, gszDeviceName, gszPort);
      ErrMsgBox (buf, ERR_MOD_NAME);
      return FALSE;
    }
  }

  for (i = 0; i < MAX_DEVICE_CAPS; i++)
  {
    iValue = GetDeviceCaps (hdc, gaCaps[i].iValue);
    TranslateDeviceCaps (i, gaCaps[i].iValue, iValue);
  }
  DeleteDC (hdc);

  return TRUE;
}



/******************************************************************************\
*
*  FUNCTION:    TranslateDeviceCaps
*
*  INPUTS:      arrayIndex - index into gaCaps[]
*               capIndex   - devcap index (eg. TECHNOLOGY, CURVECAPS)
*               iValue     - value returned by GetDeviceCaps
*
*  COMMENTS:    For simple devcaps (eg. tjose with single numeric return
*               value), appends caps value to string and inserts into
*               listbox. For "complex" caps (those returning multiple
*               bit-values) calls ComplexCapsLine which handles text
*               formattting & insertion.
*
\******************************************************************************/

void TranslateDeviceCaps (int arrayIndex, int capIndex, int iValue)
{
  char buf[BUFSIZE];

  strcpy (buf, gaCaps[arrayIndex].szValue);

  switch (capIndex)
  {
    case TECHNOLOGY:
    {
      int     i;
      
      for (i = 0; i < MAX_TECHNOLOGY_CAPS; i++)
        if (iValue == (gaTechnologyCaps + i)->iValue)
        {
          strcat(buf, (gaTechnologyCaps + i)->szValue);
          SendDlgItemMessage (ghwndDevCaps, DID_LISTBOX, LB_INSERTSTRING,
                              (UINT)-1, (LONG) buf);
          break;
        }
            
      break;
    }

    case CURVECAPS:

      ComplexDeviceCapsLine (buf, gaCurveCaps, MAX_CURVE_CAPS, iValue);
      break;

    case LINECAPS:

      ComplexDeviceCapsLine (buf, gaLineCaps, MAX_LINE_CAPS, iValue);
      break;

    case POLYGONALCAPS:

      ComplexDeviceCapsLine (buf, gaPolygonCaps, MAX_POLYGON_CAPS, iValue);
      break;

    case TEXTCAPS:

      ComplexDeviceCapsLine (buf, gaTextCaps, MAX_TEXT_CAPS, iValue);
      break;

    case CLIPCAPS:

      ComplexDeviceCapsLine (buf, gaClipCaps, MAX_CLIP_CAPS, iValue);
      break;

    case RASTERCAPS:

      ComplexDeviceCapsLine (buf, gaRasterCaps, MAX_RASTER_CAPS, iValue);
      break;

    default:

      wsprintf(buf, gaCaps[arrayIndex].szValue, iValue);

      SendDlgItemMessage (ghwndDevCaps, DID_LISTBOX, LB_INSERTSTRING,
                          (UINT)-1, (LONG) buf);
      break;
  }
}



/******************************************************************************\
*
*  FUNCTION:     ComplexDeviceCapsLine
*
*  INPUTS:       pbuf        - pointer to buffer containing a cap-type
*                              string
*                pLkUp       - pointer to a CAPSLOOKUP table
*                iMaxEntries - # of enries in table pointed at by pLkUp
*                iValue      - an integer containing 1+ bit-value flags.
*
*  COMMENTS:     This function is used to expand an int containing
*                multiple bit-values into a set of strings which are
*                inserted into the DevCapsDlg listbox. The iValue
*                parameter is checked against each iIndex entry in the
*                CAPSLOOKUP table pointed at by pLkUp, and when matches
*                are found the corresponding (lpszValue) string is
*                inserted.
*
*                The buffer pointed to by pbuf will be destroyed.
*
\******************************************************************************/

void ComplexDeviceCapsLine (char *pbuf, CAPSLOOKUP *pLkUp, int iMaxEntries,
                     int iValue)
{
  int  i;
  BOOL bNewLine = FALSE;

  for (i = 0; i < iMaxEntries; i++)

    if (iValue & (pLkUp + i)->iValue)
    {
      if (bNewLine)
      {
        //
        // Keep the first symbolic constant on the same line as the
        //   cap type, eg:  "TECHNOLOGY:     DT_RASDISPLAY".
        //

        strcpy (pbuf, BLANKS);
        strcat (pbuf, (pLkUp + i)->szValue);
      }
      else
      {
        //
        // Put symbolic constant on new line, eg:
        //                  "                DT_RASPRINTER".
        //

        strcat (pbuf, (pLkUp + i)->szValue);
        bNewLine = TRUE;
      }
      SendDlgItemMessage (ghwndDevCaps, DID_LISTBOX, LB_INSERTSTRING,
                          (UINT)-1, (LONG) pbuf);
   }
}

