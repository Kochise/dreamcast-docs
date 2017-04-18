
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
*  display.c -- module for the window with the test font.
*   Includes the window procedure and an initialization routine.
*
* store the handle to the test font in the extra bytes of this window.
*
*
* HORZ_SCROLL used to step through UC ranges when in "all glyphs" mode.
* VERT_SCROLL:
*   scroll bar range is the total number of lines needed for all glyphs
*    minus the number which may be shown in the window.
*   scroll bar position is then the first line which is to be drawn.
*
*
*
\**************************************************************************/

#include <windows.h>
#include <string.h>
#include "ttfonts.h"

/* defines for the gridding pattern in background of window */
#define GRIDCOLOR  PALETTEINDEX (3)
#define TICKSPACE  10


/* global variables store the start and end codepoints for UC ranges. */
USHORT *endCount= NULL;
USHORT *startCount= NULL;

int CountUCSegments (HDC);
/* error return value from CountUCSegments */
#define SEGMENTERROR -1

HWND   hwndFaceBanner;
TCHAR szHello[] = TEXT("Hello");

VOID BlamGlyphs (HDC, PTEXTMETRIC, USHORT, USHORT, PRECT, BOOL);



int initDisplay(HWND hwndParent)
{
WNDCLASS  wc;

  wc.style = CS_VREDRAW | CS_HREDRAW;
  wc.lpfnWndProc = (WNDPROC)DisplayWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInst;
  wc.hIcon = LoadIcon(hInst, TEXT("ttfontsIcon"));
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = TEXT("display");

  if (!RegisterClass(&wc)) return (FALSE);

  hwndDisplay = CreateMDIWindow(
      TEXT("display"),
      TEXT("Display"),
      WS_CHILD | WS_CLIPSIBLINGS | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE |
                 WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_VSCROLL | WS_HSCROLL,
      CHILDLEFT(2),
      CHILDTOP,
      GetSystemMetrics (SM_CXFULLSCREEN)/3 - 10,
      GetSystemMetrics (SM_CYFULLSCREEN)/3,
      hwndParent, hInst, 0);

  /* create child window to display face name */
  hwndFaceBanner = CreateWindow(
        TEXT("STATIC"), TEXT(""),
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        -1,0,
        GetSystemMetrics (SM_CXFULLSCREEN),
        GetSystemMetrics (SM_CYMENU),
        hwndDisplay, NULL, hInst, NULL);

  if (!hwndDisplay) return (FALSE);


  return TRUE;
}




/**************************************************************************\
*
*  function:  DisplayWndProc()
*
*  input parameters:  normal window procedure parameters.
*
*  global variables:
*   gDisplaymode - menu state
\**************************************************************************/
LRESULT CALLBACK DisplayWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
static HANDLE hPenGrid;
static LPLOGFONT     lplf;
static LPTEXTMETRIC  lptm;
static HFONT  hfont;
static HDC    hdcStatic;  /* Sent to other window procedures. */

static HDC hdc;
static RECT rect;
static int min, max;
static TEXTMETRIC tm;
static int iSeg;
static TCHAR buffer[100];

static int nCharPerLine, nTotalGlyphs, lineHeight;
static int nLinesTotal, nLinesWindow, nLinesDifference;
static int scrollRangeHigh, topLineShowing;
int i;


  switch (message) {






    /**********************************************************************\
    *  WMU_DEMOTOLF
    *
    *  lParam - pointer to LOGFONT structure.
    *
    * User message.  Fill up the display LOGFONT from the HFONT
    *  in the extra bytes.
    \**********************************************************************/
    case WMU_DEMOTOLF: {
      lplf = (LPLOGFONT) lParam;

      hfont = (HFONT) GetWindowLong (hwnd, GWL_USERDATA);
      GetObject (hfont, sizeof(LOGFONT), lplf);
    } return 0;




    /**********************************************************************\
    *  WMU_DEMOTOTM
    *
    *  lParam - pointer to TEXTMETRIC structure.
    *
    * User message.  Fill up the TEXTMETRIC from the HFONT
    *  in the extra bytes.
    \**********************************************************************/
    case WMU_DEMOTOTM: {
      lptm = (LPTEXTMETRIC) lParam;

      hfont = (HFONT) GetWindowLong (hwnd, GWL_USERDATA);

      hdc = GetDC (hwnd);
      SelectObject (hdc,hfont);
      GetTextMetrics (hdc, lptm);
      ReleaseDC (hwnd, hdc);
    } return 0;


    /**********************************************************************\
    *  WMU_DEMOGETDC
    *
    * User message.  Return an HDC.
    \**********************************************************************/
    case WMU_DEMOGETDC: {
      hfont = (HFONT) GetWindowLong (hwnd, GWL_USERDATA);

      hdcStatic = GetDC (hwnd);
      SelectObject (hdcStatic,hfont);
      return (LRESULT)hdcStatic;
    } break;


    /**********************************************************************\
    *  WMU_DEMORELEASEDC
    *
    *  lParam - the same HDC returned by WMU_DEMOGETDC
    *
    * User message.  Release the HDC.
    \**********************************************************************/
    case WMU_DEMORELEASEDC: {
      hdcStatic = (HDC) lParam;
      ReleaseDC (hwnd, hdcStatic);
    } return 0;




    /**********************************************************************\
    *  WMU_HFONTTODEMO
    *
    *  lParam - hFont
    *
    * User message.  Use the input HFONT to set a new
    *  font for this window.  Store the new font in the HFONT extra bytes.
    \**********************************************************************/
    case WMU_HFONTTODEMO: {
      /* Get and delete the last font placed in this window. */
      hfont = (HFONT) GetWindowLong (hwnd, GWL_USERDATA);
      DeleteObject (hfont);

      hfont = (HFONT) lParam;
      SetWindowLong (hwnd, GWL_USERDATA, (LONG) hfont);

      /* make sure that scroll metrics are ok */
      switch (gDisplaymode) {
        case IDM_MODEHELLO:   SendMessage (hwnd, WMU_NEWMODEHELLO, 0,0);
          break;
        case IDM_MODETMRANGE: SendMessage (hwnd, WMU_NEWMODETMRANGE, 0,0);
          break;
        case IDM_MODEALL:
          if (!SendMessage (hwndDisplay, WMU_NEWMODEALL, 0,0)) {
            MessageBox (NULL, szResetDisplay, szMBERROR, MBERRORFLAGS);
            SendMessage (hwndMain, WM_COMMAND, IDM_MODEHELLO, 0);
            return 0;
          }
          break;
      } /* end switch */

      InvalidateRect (hwnd, NULL, TRUE);
    } return 0;




    /**********************************************************************\
    *  WMU_NEWFONT
    *
    *  lParam - pointer to LOGFONT structure.
    *
    * User message.  Use the input LOGFONT structure to create a new
    *  font for this window.  Send a WMU_HFONTTODEMO message to set the
    *  font into the extra bytes for the window.
    \**********************************************************************/
    case WMU_NEWFONT: {
      lplf = (LPLOGFONT) lParam;

      /* Create a new logical font and set it into the windows extra bytes. */
      hfont = CreateFontIndirect (lplf);

      SendMessage (hwnd, WMU_HFONTTODEMO, 0, (LPARAM) hfont);
    } return 0;






    /**********************************************************************\
    *  WM_CREATE
    *
    * Create pens for drawing with later.
    \**********************************************************************/
    case WM_CREATE:
      hPenGrid   = CreatePen (PS_SOLID, 1, GRIDCOLOR);
      SetWindowLong (hwnd, GWL_USERDATA, (LONG) GetStockObject (SYSTEM_FONT));
    break;


    /**********************************************************************\
    *  WM_DESTROY
    *
    * Complement of the WM_CREATE message.  Delete the pens that were
    *  created, free startCount, endCount arrays.
    *
    \**********************************************************************/
    case WM_DESTROY:
      DeleteObject (hPenGrid);
      if (startCount != NULL) LocalFree (LocalHandle (startCount));
      if (endCount != NULL) LocalFree (LocalHandle (endCount));
    break;




    /**********************************************************************\
    *  WM_ERASEBKGND
    *
    * Offset the origin conditional on gDisplaymode.  Grid the window.
    \**********************************************************************/
    case WM_ERASEBKGND: {
      HDC hdc;
      RECT rect;
      int i;

      hdc = (HDC)wParam;

      GetClientRect (hwnd, &rect);
      FillRect (hdc, &rect, GetStockObject (LTGRAY_BRUSH));

      if (gDisplaymode == IDM_MODEHELLO) {
        SetViewportOrgEx (hdc, rect.right /2, rect.bottom/2, NULL);
        OffsetRect (&rect, -rect.right/2, -rect.bottom/2);

        SelectObject(hdc, hPenGrid);
        /* Draw vertical lines.  */
        for (i = 0; i<= rect.right; i+=TICKSPACE){
          MoveToEx (hdc, i, rect.top, NULL);
          LineTo (hdc, i, rect.bottom);
          MoveToEx (hdc, -i, rect.top, NULL);
          LineTo (hdc, -i, rect.bottom);
        }
        MoveToEx (hdc, 1, rect.top, NULL);
        LineTo (hdc, 1, rect.bottom);

        /* Draw horizontal lines.  */
        for (i = 0; i<= rect.bottom; i+=TICKSPACE){
          MoveToEx (hdc, rect.left,i, NULL);
          LineTo (hdc, rect.right,i);
          MoveToEx (hdc, rect.left,-i, NULL);
          LineTo (hdc, rect.right,-i);
        }
        MoveToEx (hdc, rect.left, 1, NULL);
        LineTo (hdc, rect.right,1);

      }


    } return TRUE;




    /**********************************************************************\
    *  WM_VSCROLL
    *
    * Slide the contents of the window up and down.  Notice that the
    *  scroll bar thumb position is important for painting.
    \**********************************************************************/
    case WM_VSCROLL:

      switch (LOWORD(wParam)){
        int OldPos, NewPos;

        case SB_PAGEDOWN:
        case SB_LINEDOWN:
          OldPos = GetScrollPos (hwnd, SB_VERT);
          SetScrollPos (hwnd, SB_VERT, (OldPos+1), TRUE);
          NewPos = GetScrollPos (hwnd, SB_VERT);
          ScrollWindow (hwnd, 0,(OldPos-NewPos)*lineHeight, NULL, NULL);
        break;

        case SB_PAGEUP:
        case SB_LINEUP:
          OldPos = GetScrollPos (hwnd, SB_VERT);
          SetScrollPos (hwnd, SB_VERT, (OldPos-1), TRUE);
          NewPos = GetScrollPos (hwnd, SB_VERT);
          ScrollWindow (hwnd, 0,(OldPos-NewPos)*lineHeight, NULL, NULL);
        break;

        case SB_THUMBPOSITION:
          OldPos = GetScrollPos (hwnd, SB_VERT);
          NewPos = HIWORD (wParam);
          SetScrollPos (hwnd, SB_VERT, NewPos, TRUE);
          ScrollWindow (hwnd, 0, (OldPos-NewPos)*lineHeight, NULL, NULL);
        break;

      }
    break;




    /**********************************************************************\
    *  WM_HSCROLL
    *
    * The horz scroll should only be present when in MODEALL.
    * Step through the allglyphs ranges.
    * In every case, inform the window the range has changed,
    *  and invalidate it to force a repaint.
    \**********************************************************************/
    case WM_HSCROLL:

      switch (LOWORD(wParam)){
        int OldPos, NewPos;

        case SB_PAGEDOWN:
        case SB_LINEDOWN:
          OldPos = GetScrollPos (hwnd, SB_HORZ);
          SetScrollPos (hwnd, SB_HORZ, (OldPos+1), TRUE);
          SendMessage (hwnd,WMU_NEWMODE_NEWSEG, 0,0);
          InvalidateRect (hwnd, NULL, TRUE);
        break;

        case SB_PAGEUP:
        case SB_LINEUP:
          OldPos = GetScrollPos (hwnd, SB_HORZ);
          SetScrollPos (hwnd, SB_HORZ, (OldPos-1), TRUE);
          SendMessage (hwnd,WMU_NEWMODE_NEWSEG, 0,0);
          InvalidateRect (hwnd, NULL, TRUE);
        break;

        case SB_THUMBPOSITION:
          OldPos = GetScrollPos (hwnd, SB_HORZ);
          NewPos = HIWORD (wParam);
          SetScrollPos (hwnd, SB_HORZ, NewPos, TRUE);
          SendMessage (hwnd,WMU_NEWMODE_NEWSEG, 0,0);
          InvalidateRect (hwnd, NULL, TRUE);
        break;

      }

    break;



    /**********************************************************************\
    * WMU_NEWMODEALL
    *
    *   returns - TRUE if a scalable font file.
    *             FALSE if GetFontData fails.
    *
    * This message is sent one time when the user checks "Show all glyphs."
    *  Here we set up the horizontal scroll bar, and the start/endCount arrays.
    \**********************************************************************/
    case WMU_NEWMODEALL: {
      HDC hdc;
      int nSegments;

      SetCursor (LoadCursor (NULL, IDC_WAIT));
      hdc = GetDC(hwnd);
      hfont = (HFONT) GetWindowLong (hwnd, GWL_USERDATA);
      SelectObject (hdc,hfont);
      nSegments = CountUCSegments (hdc); /* slow computation */
      ReleaseDC (hwnd, hdc);
      SetCursor (LoadCursor (NULL, IDC_ARROW));

      if (nSegments == SEGMENTERROR) return FALSE;

      gDisplaymode =IDM_MODEALL;
      ShowWindow (hwndFaceBanner, SW_HIDE);

      SetScrollRange (hwnd, SB_HORZ, 0, (nSegments-1), TRUE);
      SetScrollPos (hwnd, SB_HORZ, 0, TRUE);

      SendMessage (hwndDisplay, WMU_NEWMODE_NEWSEG, 0,0);
      return TRUE;

    } break;



    /**********************************************************************\
    *  WMU_NEWMODEHELLO
    *  WMU_NEWMODETMRANGE
    *  WMU_NEWMODE_NEWSEG
    *
    *
    * Sent every time an event occurs which will change the layout of
    *  the display glyphs.  I.e.
    *       window resized.
    *       display mode switch
    *       allglyph display mode, next range
    *
    * Be careful because the SetScrollRange() may cause a new WM_SIZE
    *  which in turn will cause this message to be resent.
    *
    \**********************************************************************/
    case WMU_NEWMODEHELLO:
      /* Set the window title text. */
      SetWindowText (hwnd, TEXT("Display"));

      gDisplaymode =IDM_MODEHELLO;
      ShowWindow (hwndFaceBanner, SW_SHOW);

      SetScrollRange (hwnd, SB_HORZ, 0, 0, TRUE);
      SetScrollRange (hwnd, SB_VERT, 0, 0, TRUE);
    break;


    case WMU_NEWMODETMRANGE: {
      /* Set the window title text. */
      SetWindowText (hwnd, TEXT("Display [tmFirstChar, tmLastChar]"));

      gDisplaymode =IDM_MODETMRANGE;
      ShowWindow (hwndFaceBanner, SW_HIDE);

      SetScrollRange (hwnd, SB_HORZ, 0, 0, TRUE);

      hdc = GetDC(hwnd);
      GetClientRect (hwnd, &rect);

      /* subtract off the scroll width if it is NOT there.
       *  (if it is, it will be automatically excluded by GetClientRect)
       *  if it is not there, it may be added, and we want space for it.
       */
      GetScrollRange (hwnd, SB_VERT, &min, &max);
      if (min == max) rect.right -= GetSystemMetrics (SM_CXVSCROLL);

      /* select the font into the window to get text metrics for. */
      hfont = (HFONT) GetWindowLong (hwnd, GWL_USERDATA);
      SelectObject (hdc,hfont);
      GetTextMetrics (hdc, &tm);

      nCharPerLine = rect.right / tm.tmAveCharWidth;
      nTotalGlyphs = tm.tmLastChar-tm.tmFirstChar;
      lineHeight = tm.tmHeight + tm.tmExternalLeading;
      nLinesTotal = nTotalGlyphs / nCharPerLine;
      nLinesWindow = rect.bottom / lineHeight;
      nLinesDifference = nLinesTotal - nLinesWindow;
      scrollRangeHigh = nLinesTotal - nLinesWindow;

      /* reset the scroll bar range.  If there is no need for one,
       *  then set the position to 0, and the range to 0,0 and it
       *  will not be visisble.
       */
      if (nLinesDifference >0) {
        SetScrollRange (hwnd, SB_VERT, 0, (nLinesDifference +1), TRUE);
      } else {
        SetScrollPos (hwnd, SB_VERT, 0, TRUE);
        SetScrollRange (hwnd, SB_VERT, 0, 0, TRUE);
      }

      ReleaseDC (hwnd, hdc);
    } return FALSE;



    case WMU_NEWMODE_NEWSEG: {
      gDisplaymode =IDM_MODEALL;
      SetScrollPos (hwnd, SB_VERT, 0, TRUE);

      hdc = GetDC(hwnd);
      GetClientRect (hwnd, &rect);

      /* subtract off the scroll width if it is NOT there.
       *  (if it is, it will be automatically excluded by GetClientRect)
       *  if it is not there, it may be added, and we want space for it.
       */
      GetScrollRange (hwnd, SB_VERT, &min, &max);
      if (min == max) rect.right -= GetSystemMetrics (SM_CXVSCROLL);


      /* select the font into the window to get text metrics for. */
      hfont = (HFONT) GetWindowLong (hwnd, GWL_USERDATA);
      SelectObject (hdc,hfont);
      GetTextMetrics (hdc, &tm);


      iSeg = GetScrollPos (hwnd, SB_HORZ);

      /* Set the window title text to show display range. */
      wsprintf (buffer, TEXT("Display [%04x, %04x]"),
                                  (int)startCount[iSeg],
                                  (int)endCount[iSeg]);
      SetWindowText (hwnd, buffer);




      nTotalGlyphs = endCount[iSeg] - startCount[iSeg];

      nCharPerLine = rect.right / tm.tmAveCharWidth;
      nLinesTotal = nTotalGlyphs / nCharPerLine;

      lineHeight = tm.tmHeight + tm.tmExternalLeading;
      nLinesWindow = rect.bottom / lineHeight;
      nLinesDifference = nLinesTotal - nLinesWindow;
      scrollRangeHigh = nLinesTotal - nLinesWindow;

      /* reset the scroll bar range.  If there is no need for one,
       *  then set the position to 0, and the range to 0,0 and it
       *  will not be visisble.
       */
      if (nLinesDifference >0) {
        SetScrollRange (hwnd, SB_VERT, 0, (nLinesDifference +1), FALSE);
      } else {
        SetScrollPos (hwnd, SB_VERT, 0, TRUE);
        SetScrollRange (hwnd, SB_VERT, 0, 0, TRUE);
      }

      ReleaseDC (hwnd, hdc);
    } return FALSE;




    /**********************************************************************\
    *  WM_SIZE
    *
    \**********************************************************************/
    case WM_SIZE:
      /* make sure that scroll metrics are ok */
      switch (gDisplaymode) {
        case IDM_MODEHELLO:   SendMessage (hwnd, WMU_NEWMODEHELLO, 0,0);
          break;
        case IDM_MODETMRANGE: SendMessage (hwnd, WMU_NEWMODETMRANGE, 0,0);
          break;
        case IDM_MODEALL:     SendMessage (hwnd, WMU_NEWMODE_NEWSEG, 0,0);
          break;
      } /* end switch */

    break;  /* fall through to MDIChildProc */


    /**********************************************************************\
    *  WM_PAINT
    *
    * Offset the origin conditional on gDisplaymode.  Write the "Hello"
    *  string, or step though all of the glyphs (from TEXTMETRIC.tmFirstChar
    *  to TEXTMETRIC.tmLastChar), or paint all of the glyphs in the UC segment.
    \**********************************************************************/
    case WM_PAINT: {
      HDC hdc;
      PAINTSTRUCT ps;
      RECT rect;

      hdc = BeginPaint(hwnd, &ps);


      GetClientRect (hwnd, &rect);
      hfont = (HFONT) GetWindowLong (hwnd, GWL_USERDATA);
      SelectObject (hdc,hfont);
      SetBkMode (hdc, TRANSPARENT);
      SetTextAlign (hdc, TA_LEFT | TA_TOP | TA_UPDATECP);
      GetTextMetrics (hdc, &tm);
      MoveToEx (hdc, 0,0, NULL);


      switch (gDisplaymode) {
        case IDM_MODEHELLO: {
          TCHAR szFace[LF_FACESIZE+2];
          TCHAR szBuffer[LF_FACESIZE+100];
          SIZE  ExtentSize;

          SetViewportOrgEx (hdc, rect.right /2, rect.bottom/2, NULL);
          TextOut (hdc, 0, 0, szHello, lstrlen (szHello));
          GetTextFace (hdc, LF_FACESIZE+2, szFace);
          GetTextExtentPoint (hdc, szHello, lstrlen (szHello), &ExtentSize);
          wsprintf (szBuffer,
                    TEXT("GetTextFace: \"%s\",  GetTextExtentPoint: (%d, %d)"),
                    szFace, ExtentSize.cx, ExtentSize.cy);

          SetWindowText (hwndFaceBanner, szBuffer);
        } break;

        case IDM_MODETMRANGE: {
          USHORT start, end;

          topLineShowing= GetScrollPos (hwnd, SB_VERT);
          start = tm.tmFirstChar;
          start += (topLineShowing * nCharPerLine);
          end = tm.tmLastChar;
          BlamGlyphs (hdc, &tm, start, end, &rect, FALSE);

        } break;

        case IDM_MODEALL: {
          USHORT start, end;

          iSeg= GetScrollPos (hwnd, SB_HORZ);
          topLineShowing = GetScrollPos (hwnd, SB_VERT);
          start = startCount[iSeg];
          start += (topLineShowing * nCharPerLine);
          end = endCount[iSeg];

          BlamGlyphs (hdc, &tm, start, end, &rect, FALSE);
        } break;

      } /* end switch */




      EndPaint (hwnd, &ps);

    } return FALSE; /* end WM_PAINT */



    /**********************************************************************\
    *  WMU_PRINT
    *
    * user message.  Get an HDC for the printer, send it formatted
    *  output based on the mode of the display window.
    \**********************************************************************/
    case WMU_PRINT: {
      HDC hdc;
      RECT rect;
      POINT point;
      int nchar;
      int ScrollMin, ScrollMax;
      UINT cbData;
      DOCINFO di;
      di.cbSize      = sizeof(DOCINFO);
      di.lpszDocName = TEXT("ttfonts");
      di.lpszOutput  = NULL;


      SetCursor (LoadCursor (NULL, IDC_WAIT));

      hdc = GetPrinterDC();
      if (hdc == NULL) return 0;
      StartDoc  (hdc, &di);
      StartPage (hdc);


      hfont = (HFONT) GetWindowLong (hwnd, GWL_USERDATA);
      SelectObject (hdc,hfont);
      rect.top = rect.left = 0;
      rect.right = GetDeviceCaps (hdc, HORZRES);
      rect.bottom = GetDeviceCaps (hdc, VERTRES);
      SetBkMode (hdc, TRANSPARENT);
      SetTextAlign (hdc, TA_LEFT | TA_TOP | TA_UPDATECP);
      GetTextMetrics (hdc, &tm);

      /* write a little banner at the top */
      MoveToEx (hdc, 0,0, NULL);
      TextOut (hdc, 0,0,TEXT ("ttfonts -- "), 11);

      cbData = GetOutlineTextMetrics (hdc, 0, NULL);
      if (cbData == 0) {
        TextOut (hdc, 0,0, szFontDataErr,
                lstrlen(szFontDataErr));
      } else {
        LPOUTLINETEXTMETRIC lpoltm;
        LPBYTE lptStr;

        lpoltm = (LPOUTLINETEXTMETRIC)LocalAlloc (LPTR, cbData);
        GetOutlineTextMetrics (hdc, cbData, lpoltm);

        lptStr = (LPBYTE)lpoltm;
        lptStr += (UINT) (PBYTE) lpoltm->otmpFamilyName;
        TextOut (hdc, 0,0, (LPCTSTR) lptStr, lstrlen((LPCTSTR)lptStr));
        LocalFree (LocalHandle (lpoltm));
      }

      /* Draw a thick line, and leave the cursor in the right place. */
      GetCurrentPositionEx (hdc, &point);  /* fill point */
      point.x = rect.right;
      point.y += tm.tmHeight;
      for (i = 0; i<5; i++) {
        MoveToEx (hdc, point.x, point.y, NULL);
        LineTo (hdc, 0, point.y);
        point.y++;
      }


      switch (gDisplaymode) {
        case IDM_MODEHELLO:
          SetViewportOrgEx (hdc, rect.right /2, rect.bottom/2, NULL);
          TextOut (hdc, 0, 0, szHello, lstrlen (szHello));
        break;


        case IDM_MODETMRANGE:
          BlamGlyphs (hdc, &tm, tm.tmFirstChar, tm.tmLastChar, &rect, TRUE);
        break;

        case IDM_MODEALL:
          /* the horz scroll bar has the number of segments stored as
           *  the scroll bar range, query and use it.
           */
          GetScrollRange (hwnd, SB_HORZ, &ScrollMin, &ScrollMax);

          for (i = 0; i<= ScrollMax; i++) {
            MoveToEx (hdc,rect.right, point.y, NULL);
            LineTo (hdc, rect.left, point.y);

            SelectObject (hdc,GetStockObject (DEVICE_DEFAULT_FONT));
            nchar = wsprintf (buffer, TEXT("[%04x, %04x]"), (int)startCount[i],
                                                      (int)endCount[i]);
            TextOut (hdc, 0,0,buffer, nchar);
            SelectObject (hdc,hfont);


            BlamGlyphs (hdc, &tm, startCount[i], endCount[i], &rect, TRUE);

            GetCurrentPositionEx (hdc, &point);
            point.x = 0;
            point.y += (tm.tmHeight + tm.tmExternalLeading);
            MoveToEx (hdc, point.x, point.y, NULL);
            if ((point.y+tm.tmHeight+tm.tmExternalLeading) > rect.bottom) {
              point.x = point.y = 0;
              EndPage   (hdc);
              StartPage (hdc);
              MoveToEx (hdc, point.x, point.y, NULL);
            }
          }
        break;  /* end IDM_MODEALL */
      } /* end switch */

      EndPage   (hdc);
      EndDoc    (hdc);

      DeleteDC (hdc);
      SetCursor (LoadCursor (NULL, IDC_ARROW));

    } return TRUE;

  } /* end switch */

  return (DefMDIChildProc(hwnd, message, wParam, lParam));
}




/**************************************************************************\
*
*  function:  BlamGlyphs
*
*  input parameters:
*   hdc with font selected into it.
*   pointer to a text metric structure.
*   start and end of code point range to print
*   pointer to rectangle which serves as bounds.
*
*  Starting at the current point, write one glyph after the other, starting
*   with the "Start" parameter, and ending with the "End" parameter.  If
*   the next character will overrun on the right, start again on a new line.
*  Special case Start = 0xfff which happens because the start/endCount
*   arrays always end with this value.
*
*
  // UNICODE NOTICE
  //  This function is held as unicode because it needs to display
  //  wide characters (i.e. need TextOutW).
*
*
\**************************************************************************/
VOID BlamGlyphs (HDC hdc, PTEXTMETRIC ptm, USHORT Start, USHORT End, PRECT prect, BOOL printing)
{
USHORT i;
POINT point;
WCHAR outChar;

  if (Start == 0xffff) return;

  for (i = Start; i<=End; i++) {

    /* special case the non-spacing diacritic marks. U+0300 -> U+036F
     *  Write a space first, for them to 'modify.'
     */
    if ( (0x0300 <= i) && (i <= 0x036F) ) {
      outChar = (WCHAR) 0x0020;
      TextOutW (hdc, 0,0, &outChar, 1);
    }


    outChar = (WCHAR) i;
    TextOutW (hdc, 0,0, &outChar, 1);

    /* Watch for overflow in x */
    GetCurrentPositionEx (hdc, &point);
    if (point.x > (prect->right - ptm->tmAveCharWidth)) {
      point.x = 0;
      point.y += (ptm->tmHeight + ptm->tmExternalLeading);
      MoveToEx (hdc, point.x, point.y, NULL);
    }

    /* Watch for overflow in y */
    if (printing) {
      if (point.y > (prect->bottom-(ptm->tmHeight+ptm->tmExternalLeading))) {
        EndPage   (hdc);
        StartPage (hdc);
        point.x = point.y = 0;
        MoveToEx (hdc, point.x, point.y, NULL);
      }
    } else {
      if (point.y > prect->bottom) {
        return;
      }
    }
  } /* end for (i= Start; i<=End ... */
}




/**************************************************************************\
*
* All of the code below is used for parsing "font data."  It will only
*  make sense if you have a copy of the True Type font spec.  In short,
*  we grab the 'cmap' table, look through it for a subtable, and then
*  get two parallel arrays from the subtable.  Complications arise because
*  the true type data is "BIG ENDIAN" and NT is being run "little endian."
*  For this reason, once we locate the short or long, we call Swap* to
*  change the byte ordering.
*
\**************************************************************************/


VOID SwapShort (PUSHORT);
VOID SwapULong  (PULONG);



typedef struct tagTABLE{
    USHORT platformID;
    USHORT encodingID;
    ULONG  offset;
} TABLE, *PTABLE;

typedef struct tagSUBTABLE{
    USHORT format;
    USHORT length;
    USHORT version;
    USHORT segCountX2;
    USHORT searchRange;
    USHORT entrySelector;
    USHORT rangeShift;
} SUBTABLE, *PSUBTABLE;


/* 'cmap' is passed in by value in a DWORD */
#define CMAPHEX  0x70616d63
#define NBYTES   256
#define OFFSETERROR  0



/**************************************************************************\
*
*  function:  CountUCSegments()
*
*  input parameters:
*   hdc - with the logical font set into it.
*   prect - pointer to client rectangle.
*
*  Global variables:
*   startCount
*   endCount
*
*  returns:
*   number of UC segments or
*   SEGMENTERROR if there is some kind of error.
*
*  essential side effect:
*   Fills in global startCount, endCount arrays.
\**************************************************************************/
int CountUCSegments (HDC hdc)
{
DWORD       cbData;
USHORT      aShort[2];
DWORD       nBytes;
USHORT      i, nTables;
PTABLE      pTable;
PSUBTABLE   pSubTable;
ULONG       offset,offsetFormat4;
USHORT      segCount;
BYTE        buffer[NBYTES];




    /* find number of "subtables", second long in cmap */
    nBytes=GetFontData (hdc, CMAPHEX, 0, aShort, 4);
    if (nBytes == GDI_ERROR) {
      MessageBox (NULL, szFontDataErr, szMBERROR , MBERRORFLAGS);
      return SEGMENTERROR;
    }
    if (nBytes == 0) {
      MessageBox (NULL, szNoCMAPTable, szMBERROR , MBERRORFLAGS);
      return SEGMENTERROR;
    }
    nTables = aShort[1];
    SwapShort (&nTables);


    cbData = nTables * sizeof(TABLE);
    if (cbData >NBYTES) {
      MessageBox (NULL, szCBDataTooBig, szMBERROR , MBERRORFLAGS);
      return SEGMENTERROR;
    }

    /* get array of subtables information.  Check each one for 3,1*/
    nBytes=GetFontData (hdc, CMAPHEX, 4, buffer, cbData);
    pTable = (PTABLE)buffer;
    offsetFormat4 = OFFSETERROR;
    for (i = 0; i< nTables; i++) {

        SwapShort (&(pTable->encodingID));
        SwapShort (&(pTable->platformID));

        if ((pTable->platformID == 3)&&(pTable->encodingID == 1)) {
          offsetFormat4 = pTable->offset;
          SwapULong (&offsetFormat4);
          break;
        }
        pTable++;
    }

    /* verify that we got the correct offset to the FORMAT 4 subtable */
    if (offsetFormat4 == OFFSETERROR){
      MessageBox (NULL, szNoTable, szMBERROR , MBERRORFLAGS);
      return SEGMENTERROR;
    }

    /* Get the beginning of the subtable, especially the segment count */
    nBytes=GetFontData (hdc, CMAPHEX, offsetFormat4, buffer, sizeof(SUBTABLE));
    pSubTable = (PSUBTABLE) buffer;
    SwapShort (&(pSubTable->format));
    SwapShort (&(pSubTable->segCountX2));

    if (pSubTable->format != 4){
      MessageBox (NULL, szFormatNot4, szMBERROR, MBERRORFLAGS);
      return SEGMENTERROR;
    }

    segCount = pSubTable->segCountX2 / 2;

    /* Now that we know how many segments that the font contains,
     *  free up the old memory, and realloc. the two global arrays.
     */
    if (startCount != NULL) LocalFree (LocalHandle (startCount));
    if (endCount != NULL) LocalFree (LocalHandle (endCount));
    startCount = LocalAlloc (LPTR, segCount * sizeof(USHORT));
    endCount = LocalAlloc (LPTR, segCount * sizeof(USHORT));

    if ((startCount == NULL) || (endCount == NULL)) {
      MessageBox (NULL, szAllocFailed, szMBERROR, MBERRORFLAGS);
      return SEGMENTERROR;
    }

    /* read in the array of endCount values */
    offset = offsetFormat4
           + (7 * sizeof (USHORT));  /* skip constant # bytes in subtable */
    cbData = segCount * sizeof (USHORT);
    nBytes=GetFontData (hdc, CMAPHEX, offset, endCount, cbData );
    for (i = 0; i<segCount; i++)
        SwapShort (& (endCount[i]));

    /* read in the array of startCount values */
    offset = offsetFormat4
           + (7 * sizeof (USHORT))   /* skip constant # bytes in subtable */
           + (segCount * sizeof (USHORT)) /* skip endCount array */
           + sizeof (USHORT);             /* skip reservedPad */
    cbData = segCount * sizeof (USHORT);
    nBytes=GetFontData (hdc, CMAPHEX, offset, startCount, cbData );
    for (i = 0; i<segCount; i++)
        SwapShort (& (startCount[i]));


    return segCount;
}










VOID SwapShort (PUSHORT p)
{
SHORT temp;

    temp =(SHORT)( HIBYTE (*p) + (LOBYTE(*p) << 8));
    *p = temp;
}



VOID SwapULong (PULONG p)
{
ULONG temp;

    temp = (LONG) ((BYTE) *p);
    temp <<= 8;
    *p >>=8;

    temp += (LONG) ((BYTE) *p);
    temp <<= 8;
    *p >>=8;

    temp += (LONG) ((BYTE) *p);
    temp <<= 8;
    *p >>=8;

    temp += (LONG) ((BYTE) *p);
    *p = temp;
}
