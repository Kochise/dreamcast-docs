
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

/**************************************************************************\
*  dialogs.c -- module for the two dialogs (LOGFONT & TEXTMETRIC)
*   Includes the window procedure and an initialization routine.
*  the LogFontWndProc is actually used for multiple dialogs.
\**************************************************************************/

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "ttfonts.h"



int initDlg(HWND hwndMain)
{
  /*  load three dialogs and position them. Set the minimize icon for
   *   this CLASS and it affects all dialog windows.
   */

  hwndDlgLF = CreateDialog (hInst, TEXT("logfontDlg"), hwndMain,
                (DLGPROC)LogFontWndProc);
  if (hwndDlgLF == NULL) return FALSE;

  SetWindowPos (hwndDlgLF, NULL,
                CHILDLEFT(1), CHILDTOP,
                0,0, SWP_NOZORDER | SWP_NOSIZE);


  hwndDlgTM = CreateDialog (hInst, TEXT("textmetricDlg"), hwndMain,
                (DLGPROC)LogFontWndProc);
  if (hwndDlgTM == NULL) return FALSE;

  SetWindowPos (hwndDlgTM, NULL,
                CHILDLEFT(0), CHILDTOP,
                0,0, SWP_NOZORDER | SWP_NOSIZE);



  hwndDlgOLTM = CreateDialog (hInst, TEXT("oltextmetricDlg"), hwndMain,
                (DLGPROC)LogFontWndProc);
  if (hwndDlgOLTM == NULL) return FALSE;
  ShowWindow (hwndDlgOLTM, SW_MINIMIZE);




  hwndDlgFD = CreateDialog (hInst, TEXT("getfontdataDlg"), hwndMain,
                (DLGPROC)FontDataWndProc);
  if (hwndDlgFD == NULL) return FALSE;
  ShowWindow (hwndDlgFD, SW_MINIMIZE);
  SetWindowPos (hwndDlgFD, HWND_TOP,
                0, 0,
                0,0, SWP_NOSIZE );



  SetClassLong (hwndDlgLF, GCL_HICON, (LONG)LoadIcon(hInst, TEXT("ttfontsIcon")));


  return TRUE;
}


/* first and last string IDs from string table in RC file */
#define FIRSTSTRING 1
#define LASTSTRING  20



/**************************************************************************\
*
*  function:  FontDataWndProc
*
*  input parameters:  normal window procedure parameters.
*
*  Allow the user to select a table, an offset, and a byte count.
*   on command message, post self a user message (allows the user
*   message to come in from other sources too).  On the user message,
*   just call GetFontData and display the results.
*
*
  // UNICODE NOTICE
  //  Parts of this are held as ANSI because the dwTable
  //  in the fontdata is stored with four 8 bit chars.
  //  And because there is not yet a wide char version of sscanf().
*
*
\**************************************************************************/
LRESULT CALLBACK FontDataWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
#define NCHAR 255
TCHAR buffer[NCHAR];
HDC hdc;
int nBytes, nStrings, i;


  switch (message) {

    /* fill combo box w/ table names, and
     *  entry fields w/ meaningful initial values.
     */
    case WM_INITDIALOG:
      SetDlgItemInt (hwnd, DID_DWOFFSET, 0, TRUE);
      SetDlgItemInt (hwnd, DID_CBDATA, 50, TRUE);
      for (i = FIRSTSTRING; i<= LASTSTRING; i++) {
        LoadString (GetModuleHandle (NULL), i, buffer, NCHAR);
        SendDlgItemMessage (hwnd, DID_DWTABLE, CB_ADDSTRING, 0, (LPARAM)buffer);
      }

    return TRUE;

    /* If the user hits the DOIT button, post message back to the
     *  main window.  It will get an HDC and then post us the proper
     *  user message.
     */
    case WM_COMMAND:
      if (wParam == DID_DOIT)
        PostMessage (hwndMain, WM_COMMAND, TBID_GETFONTDATA, 0);
    break;  /* end WM_COMMAND */



    /**********************************************************************\
    *  WMU_GETFONTDATA
    *
    *  lParam - HDC.
    *
    * User message.  Parse the contents of the entry fields, and make the
    *  GetFontData() call.  Put results in the listbox.
    \**********************************************************************/
    case WMU_GETFONTDATA: {
        DWORD dwTable, dwOffset, cbData;
        LPBYTE   lpDataBuffer;
        DWORD dwNBytes;

        hdc = (HDC) lParam;
        SendDlgItemMessage (hwnd, DID_LISTBOX, LB_RESETCONTENT, 0, 0);


        {
          // UNICODE NOTICE.  GetDlgItemTextA returns ANSI strings.
          //  we are doing manipulation on a byte by byte basis

          CHAR  fourbytes[5];
          CHAR  sbBuffer[NCHAR];

          nBytes = GetDlgItemTextA (hwnd, DID_DWTABLE, fourbytes, 5);
          if (nBytes == 0) {
            dwTable = 0;
          } else {
            dwTable = (DWORD) ((fourbytes[3] << 24)
                            +  (fourbytes[2] << 16)
                            +  (fourbytes[1] <<  8)
                            +  (fourbytes[0]));
          }


          // UNICODE NOTICE.  GetDlgItemTextA returns ANSI strings.
          //  sscanf expects single byte strings.

          GetDlgItemTextA (hwnd, DID_DWOFFSET, sbBuffer, NCHAR);
          sscanf (sbBuffer, "%x", &dwOffset);
          GetDlgItemTextA (hwnd, DID_CBDATA  , sbBuffer, NCHAR);
          sscanf (sbBuffer, "%x", &cbData);
        }


        lpDataBuffer = (LPBYTE) LocalAlloc (LPTR, cbData);
        if (lpDataBuffer == NULL) {
          MessageBox (NULL, szAllocFailed, szMBERROR, MBERRORFLAGS);
          return 0;
        }

        dwNBytes = GetFontData (hdc, dwTable, dwOffset, (LPVOID) lpDataBuffer, cbData);

        if (dwNBytes == -1) {
          MessageBox (NULL, szFontDataErr, szMBERROR, MBERRORFLAGS);
        } else {

          nStrings = dwNBytes / 16;
          for (i = 0; i< nStrings; i++) {
            wsprintf (buffer,
                      TEXT("%02x%02x %02x%02x  %02x%02x %02x%02x  %02x%02x %02x%02x  %02x%02x %02x%02x"),
                      (int)lpDataBuffer[i*16+0],
                      (int)lpDataBuffer[i*16+1],
                      (int)lpDataBuffer[i*16+2],
                      (int)lpDataBuffer[i*16+3],
                      (int)lpDataBuffer[i*16+4],
                      (int)lpDataBuffer[i*16+5],
                      (int)lpDataBuffer[i*16+6],
                      (int)lpDataBuffer[i*16+7],
                      (int)lpDataBuffer[i*16+8],
                      (int)lpDataBuffer[i*16+9],
                      (int)lpDataBuffer[i*16+10],
                      (int)lpDataBuffer[i*16+11],
                      (int)lpDataBuffer[i*16+12],
                      (int)lpDataBuffer[i*16+13],
                      (int)lpDataBuffer[i*16+14],
                      (int)lpDataBuffer[i*16+15]);
            SendDlgItemMessage (hwnd, DID_LISTBOX, LB_ADDSTRING, 0, (LONG) buffer);
          }
        }

        LocalFree ( LocalHandle ((LPVOID)lpDataBuffer));
    } return TRUE;  /* end WMU_GETFONTDATA */

  } /* end switch */
  return 0;
}






/**************************************************************************\
*
*  function:  LogFontWndProc
*
*  input parameters:  normal window procedure parameters.
*  global variables:
*
* This window procedure is used for two completely different dialog boxes.
\**************************************************************************/
LRESULT CALLBACK LogFontWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
static LPLOGFONT    lplf;
static LPTEXTMETRIC lptm;

  switch (message) {


    /**********************************************************************\
    *  WMU_DEMOTOLF
    *
    *  lParam - pointer to LOGFONT structure.
    *
    * User message.  Take the input LOGFONT and fill the edit fields of the
    *  dialog box.
    \**********************************************************************/
    case WMU_DEMOTOLF: {
      lplf = (LPLOGFONT) lParam;

      SetDlgItemInt (hwnd, DIDHEIGHT , lplf->lfHeight,        TRUE);
      SetDlgItemInt (hwnd, DIDWIDTH  , lplf->lfWidth,         TRUE);
      SetDlgItemInt (hwnd, DIDESCAPE , lplf->lfEscapement,    TRUE);
      SetDlgItemInt (hwnd, DIDORIENT , lplf->lfOrientation,   TRUE);
      SetDlgItemInt (hwnd, DIDWEIGHT , lplf->lfWeight,        TRUE);
      SetDlgItemInt (hwnd, DIDITALIC , lplf->lfItalic,        FALSE);
      SetDlgItemInt (hwnd, DIDUNDERL , lplf->lfUnderline,     FALSE);
      SetDlgItemInt (hwnd, DIDSTRIKE , lplf->lfStrikeOut,     FALSE);
      SetDlgItemInt (hwnd, DIDCHARSE , lplf->lfCharSet,       FALSE);
      SetDlgItemInt (hwnd, DIDOUTPRE , lplf->lfOutPrecision,  FALSE);
      SetDlgItemInt (hwnd, DIDCLIPPR , lplf->lfClipPrecision, FALSE);
      SetDlgItemInt (hwnd, DIDQUALIT , lplf->lfQuality,       FALSE);
      SetDlgItemInt (hwnd, DIDPITCHA , lplf->lfPitchAndFamily,FALSE);
      SetDlgItemText (hwnd, DIDFACENA, lplf->lfFaceName);

    } break;


    /**********************************************************************\
    *  WMU_LFTODEMO
    *
    *  lParam - pointer to LOGFONT structure.
    *
    * User message.  Fill the input LOGFONT with the contents of the
    *  edit fields of dialog box.
    \**********************************************************************/
    case WMU_LFTODEMO: {
      BOOL  success;
      lplf = (LPLOGFONT) lParam;


      lplf->lfHeight =        GetDlgItemInt (hwnd, DIDHEIGHT, &success , TRUE);
      lplf->lfWidth  =        GetDlgItemInt (hwnd, DIDWIDTH , &success , TRUE);
      lplf->lfEscapement =    GetDlgItemInt (hwnd, DIDESCAPE, &success , TRUE);
      lplf->lfOrientation =   GetDlgItemInt (hwnd, DIDORIENT, &success , TRUE);
      lplf->lfWeight =        GetDlgItemInt (hwnd, DIDWEIGHT, &success , TRUE);
      lplf->lfItalic =        (BYTE) GetDlgItemInt (hwnd, DIDITALIC, &success , FALSE);
      lplf->lfUnderline =     (BYTE) GetDlgItemInt (hwnd, DIDUNDERL, &success , FALSE);
      lplf->lfStrikeOut =     (BYTE) GetDlgItemInt (hwnd, DIDSTRIKE, &success , FALSE);
      lplf->lfCharSet =       (BYTE) GetDlgItemInt (hwnd, DIDCHARSE, &success , FALSE);
      lplf->lfOutPrecision =  (BYTE) GetDlgItemInt (hwnd, DIDOUTPRE, &success , FALSE);
      lplf->lfClipPrecision = (BYTE) GetDlgItemInt (hwnd, DIDCLIPPR, &success , FALSE);
      lplf->lfQuality =       (BYTE) GetDlgItemInt (hwnd, DIDQUALIT, &success , FALSE);
      lplf->lfPitchAndFamily =(BYTE) GetDlgItemInt (hwnd, DIDPITCHA, &success , FALSE);
      GetDlgItemText (hwnd, DIDFACENA, lplf->lfFaceName, LF_FACESIZE);

    } break;



    /**********************************************************************\
    *  WMU_DEMOTOTM
    *
    *  lParam - pointer to TEXTMETRIC structure.
    *
    * User message.  Take the input LOGFONT and fill the list box with
    *  strings.  Turn off update before hand, then reenable when complete.
    \**********************************************************************/
    case WMU_DEMOTOTM: {
      TCHAR buffer[100];

      lptm = (LPTEXTMETRIC) lParam;

      SendDlgItemMessage (hwnd, DID_LISTBOX, WM_SETREDRAW, FALSE, 0);
      SendDlgItemMessage (hwnd, DID_LISTBOX, LB_RESETCONTENT, 0, 0);

#define LBPUT SendDlgItemMessage (hwnd, DID_LISTBOX, LB_ADDSTRING, 0, (LONG) buffer);

      wsprintf (buffer, TEXT("tmHeight        \t%d")  ,(int) lptm->tmHeight           ); LBPUT
      wsprintf (buffer, TEXT("tmAscent        \t%d")  ,(int) lptm->tmAscent           ); LBPUT
      wsprintf (buffer, TEXT("tmDescent       \t%d")  ,(int) lptm->tmDescent          ); LBPUT
      wsprintf (buffer, TEXT("tmInternalLeading\t%d") ,(int) lptm->tmInternalLeading  ); LBPUT
      wsprintf (buffer, TEXT("tmExternalLeading\t%d") ,(int) lptm->tmExternalLeading  ); LBPUT
      wsprintf (buffer, TEXT("tmAveCharWidth  \t%d")  ,(int) lptm->tmAveCharWidth     ); LBPUT
      wsprintf (buffer, TEXT("tmMaxCharWidth  \t%d")  ,(int) lptm->tmMaxCharWidth     ); LBPUT
      wsprintf (buffer, TEXT("tmWeight        \t%d")  ,(int) lptm->tmWeight           ); LBPUT
      wsprintf (buffer, TEXT("tmOverhang      \t%d")  ,(int) lptm->tmOverhang         ); LBPUT
      wsprintf (buffer, TEXT("tmDigitizedAspectX\t%d"),(int) lptm->tmDigitizedAspectX ); LBPUT
      wsprintf (buffer, TEXT("tmDigitizedAspectY\t%d"),(int) lptm->tmDigitizedAspectY ); LBPUT
      wsprintf (buffer, TEXT("tmItalic        \t%d")  ,(int) lptm->tmItalic           ); LBPUT
      wsprintf (buffer, TEXT("tmUnderlined    \t%d")  ,(int) lptm->tmUnderlined       ); LBPUT
      wsprintf (buffer, TEXT("tmStruckOut     \t%d")  ,(int) lptm->tmStruckOut        ); LBPUT
      wsprintf (buffer, TEXT("tmFirstChar     \t%d")  ,(int) lptm->tmFirstChar        ); LBPUT
      wsprintf (buffer, TEXT("tmLastChar      \t%d")  ,(int) lptm->tmLastChar         ); LBPUT
      wsprintf (buffer, TEXT("tmDefaultChar   \t%d")  ,(int) lptm->tmDefaultChar      ); LBPUT
      wsprintf (buffer, TEXT("tmBreakChar     \t%d")  ,(int) lptm->tmBreakChar        ); LBPUT
      wsprintf (buffer, TEXT("tmPitchAndFamily\t%d")  ,(int) lptm->tmPitchAndFamily   ); LBPUT
      wsprintf (buffer, TEXT("tmCharSet       \t%d")  ,(int) lptm->tmCharSet          ); LBPUT

      SendDlgItemMessage (hwnd, DID_LISTBOX, WM_SETREDRAW, TRUE, 0);
      InvalidateRect (hwnd, NULL, TRUE);
      UpdateWindow (hwnd);

    } break;


    /**********************************************************************\
    *  WMU_DEMOTOOLTM
    *
    *  lParam - HDC.
    *
    * User message.  With the input HDC, allocate space for OUTLINETEXTMETRIC
    *  structure, query it from the HDC, and fill the listbox.  (Allocate the
    *  OUTLINETEXTMETRIC structure dynamically since it is variable size.)
    \**********************************************************************/
    case WMU_DEMOTOOLTM: {
      HDC hdc;
      TCHAR buffer[100];
      UINT cbData;
      LPOUTLINETEXTMETRIC lpoltm;
      LPBYTE lptStr;

      hdc = (HDC) lParam;


      /* figure out how large the structure is, alloc, and re-query
       *  unless cbData ==0, then post no-op string and exit.
       */
      cbData = GetOutlineTextMetrics (hdc, 0, NULL);
      if (cbData == 0) {
        SendDlgItemMessage (hwnd, DID_LISTBOX, LB_RESETCONTENT, 0, 0);
        wsprintf (buffer, TEXT("cbData == 0")); LBPUT
        return 0;
      }
      lpoltm = (LPOUTLINETEXTMETRIC)LocalAlloc (LPTR, cbData);
      GetOutlineTextMetrics (hdc, cbData, lpoltm);


      /* freeze redraw of listbox, and clear contents. */
      SendDlgItemMessage (hwnd, DID_LISTBOX, WM_SETREDRAW, FALSE, 0);
      SendDlgItemMessage (hwnd, DID_LISTBOX, LB_RESETCONTENT, 0, 0);


      wsprintf (buffer, TEXT("otmSize                \t%d"),(int) lpoltm->otmSize               );            LBPUT
      wsprintf (buffer, TEXT("otmTextMetrics { }"));                                                      LBPUT
      wsprintf (buffer, TEXT("otmFiller              \t%d"),(int)(BYTE) lpoltm->otmFiller             );      LBPUT

      wsprintf (buffer, TEXT("otmPanoseNumber           "));                                                  LBPUT
// removed for beta 2.      wsprintf (buffer, TEXT("\t ulCulture        \t%d"),   (int) lpoltm->otmPanoseNumber.ulCulture        ); LBPUT
      wsprintf (buffer, TEXT("\t bFamilyType      \t0x%lx"),(int) lpoltm->otmPanoseNumber.bFamilyType      ); LBPUT
      wsprintf (buffer, TEXT("\t bSerifStyle      \t0x%lx"),(int) lpoltm->otmPanoseNumber.bSerifStyle      ); LBPUT
      wsprintf (buffer, TEXT("\t bWeight          \t0x%lx"),(int) lpoltm->otmPanoseNumber.bWeight          ); LBPUT
      wsprintf (buffer, TEXT("\t bProportion      \t0x%lx"),(int) lpoltm->otmPanoseNumber.bProportion      ); LBPUT
      wsprintf (buffer, TEXT("\t bContrast        \t0x%lx"),(int) lpoltm->otmPanoseNumber.bContrast        ); LBPUT
      wsprintf (buffer, TEXT("\t bStrokeVariation \t0x%lx"),(int) lpoltm->otmPanoseNumber.bStrokeVariation ); LBPUT
      wsprintf (buffer, TEXT("\t bArmStyle        \t0x%lx"),(int) lpoltm->otmPanoseNumber.bArmStyle        ); LBPUT
      wsprintf (buffer, TEXT("\t bLetterform      \t0x%lx"),(int) lpoltm->otmPanoseNumber.bLetterform      ); LBPUT
      wsprintf (buffer, TEXT("\t bMidline         \t0x%lx"),(int) lpoltm->otmPanoseNumber.bMidline         ); LBPUT
      wsprintf (buffer, TEXT("\t bXHeight         \t0x%lx"),(int) lpoltm->otmPanoseNumber.bXHeight         ); LBPUT


      wsprintf (buffer, TEXT("otmfsSelection         \t%d"),(UINT) lpoltm->otmfsSelection        ); LBPUT
      wsprintf (buffer, TEXT("otmfsType              \t%d"),(UINT) lpoltm->otmfsType             ); LBPUT
      wsprintf (buffer, TEXT("otmsCharSlopeRise      \t%d"),(UINT) lpoltm->otmsCharSlopeRise     ); LBPUT
      wsprintf (buffer, TEXT("otmsCharSlopeRun       \t%d"),(UINT) lpoltm->otmsCharSlopeRun      ); LBPUT
      wsprintf (buffer, TEXT("otmItalicAngle         \t%d"),(UINT) lpoltm->otmItalicAngle        ); LBPUT
      wsprintf (buffer, TEXT("otmEMSquare            \t%d"),(UINT) lpoltm->otmEMSquare           ); LBPUT
      wsprintf (buffer, TEXT("otmAscent              \t%d"),(UINT) lpoltm->otmAscent             ); LBPUT
      wsprintf (buffer, TEXT("otmDescent             \t%d"),(int) lpoltm->otmDescent             ); LBPUT
      wsprintf (buffer, TEXT("otmLineGap             \t%d"),(int) lpoltm->otmLineGap             ); LBPUT
      wsprintf (buffer, TEXT("otmsCapEmHeight        \t%d"),(UINT) lpoltm->otmsCapEmHeight        ); LBPUT
      wsprintf (buffer, TEXT("otmsXHeight            \t%d"),(UINT) lpoltm->otmsXHeight            ); LBPUT
      wsprintf (buffer, TEXT("otmrcFontBox           \t (%d, %d, %d, %d)"),
                                                      (int) lpoltm->otmrcFontBox.left,
                                                      (int) lpoltm->otmrcFontBox.top,
                                                      (int) lpoltm->otmrcFontBox.right,
                                                      (int) lpoltm->otmrcFontBox.bottom   ); LBPUT
      wsprintf (buffer, TEXT("otmMacAscent           \t%d"),(int) lpoltm->otmMacAscent          ); LBPUT
      wsprintf (buffer, TEXT("otmMacDescent          \t%d"),(int) lpoltm->otmMacDescent         ); LBPUT
      wsprintf (buffer, TEXT("otmMacLineGap          \t%d"),(UINT) lpoltm->otmMacLineGap         ); LBPUT
      wsprintf (buffer, TEXT("otmusMinimumPPEM       \t%d"),(UINT) lpoltm->otmusMinimumPPEM      ); LBPUT

      wsprintf (buffer, TEXT("otmptSubscriptSize     \t(%d, %d)"),
                                                      (int) lpoltm->otmptSubscriptSize.x,
                                                      (int) lpoltm->otmptSubscriptSize.y    ); LBPUT
      wsprintf (buffer, TEXT("otmptSubscriptOffset   \t(%d, %d)"),
                                                      (int) lpoltm->otmptSubscriptOffset.x,
                                                      (int) lpoltm->otmptSubscriptOffset.y  ); LBPUT
      wsprintf (buffer, TEXT("otmptSuperscriptSize   \t(%d, %d)"),
                                                      (int) lpoltm->otmptSuperscriptSize.x,
                                                      (int) lpoltm->otmptSuperscriptSize.y  ); LBPUT
      wsprintf (buffer, TEXT("otmptSuperscriptOffset \t(%d, %d)"),
                                                      (int) lpoltm->otmptSuperscriptOffset.x,
                                                      (int) lpoltm->otmptSuperscriptOffset.y); LBPUT

      wsprintf (buffer, TEXT("otmsStrikeoutSize      \t%d"),(UINT) lpoltm->otmsStrikeoutSize     ); LBPUT
      wsprintf (buffer, TEXT("otmsStrikeoutPosition  \t%d"),(int) lpoltm->otmsStrikeoutPosition );  LBPUT
      wsprintf (buffer, TEXT("otmsUnderscoreSize     \t%d"),(int) lpoltm->otmsUnderscoreSize    );  LBPUT
      wsprintf (buffer, TEXT("otmsUnderscorePosition \t%d"),(UINT) lpoltm->otmsUnderscorePosition); LBPUT

      /* the last 4 fields are incorrectly typed as PSTR,
       *  they are in fact offsets from the top of the
       *  OUTLINETEXTMETRIC structure, to the location of the string.
       */
      lptStr = (LPBYTE)lpoltm;
      lptStr += (UINT) (PBYTE) lpoltm->otmpFamilyName;
      wsprintf (buffer, TEXT("otmpFamilyName:   %s"),lptStr); LBPUT

      lptStr = (LPBYTE)lpoltm;
      lptStr += (UINT) (PBYTE) lpoltm->otmpFaceName;
      wsprintf (buffer, TEXT("otmpFaceName:   %s"),lptStr);   LBPUT

      lptStr = (LPBYTE)lpoltm;
      lptStr += (UINT) (PBYTE) lpoltm->otmpStyleName;
      wsprintf (buffer, TEXT("otmpStyleName:   %s"),lptStr);  LBPUT

      wsprintf (buffer, TEXT("otmpFullName:"));               LBPUT
      lptStr = (LPBYTE)lpoltm;
      lptStr += (UINT) (PBYTE) lpoltm->otmpFullName;
      wsprintf (buffer, TEXT("  %s"),lptStr);                 LBPUT


      SendDlgItemMessage (hwnd, DID_LISTBOX, WM_SETREDRAW, TRUE, 0);
      InvalidateRect (hwnd, NULL, TRUE);
      UpdateWindow (hwnd);

      /* balance LocalAlloc(), release memory. */
      LocalFree (LocalHandle (lpoltm));

    } break;



    /**********************************************************************\
    *  WM_CHILDACTIVATE
    *
    *  In order for these MDI child windows (dialogs) to be activated
    *   correctly, the dialog procedure here must call the Win32 API
    *   DefMDIChildProc ().
    \**********************************************************************/
    case WM_CHILDACTIVATE:
      DefMDIChildProc(hwnd, message, wParam, lParam);
      return TRUE;
    break;

  } /* end switch */
  return 0;
}
