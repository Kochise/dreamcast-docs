
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
*  allfont.c -- module to display the result of enumerating all fonts.
*   Includes the window procedure and an initialization routine.
*
*  There are actually two windows serviced by this module.  One for the
*   display fonts, one for the printer fonts.
*
*
*  Data structure:
*   Since we keep a modest amount of data for each possible font, and
*   since the amount of this information is known only at run time,
*   the main data structure used here is all allocated dynamically.
*   parFonts points to an array of ARFONT structures.  These structures
*   store two int's and then three pointers to arrays of LOGFONT,
*   TEXTMETRIC, and int's respectively.
*
*   parFonts--> |--------------------|  |--------------------|
*               |  nFonts (Family0)  |  |  nFonts (Family1)  |
*               |       cySpace      |  |       cySpace      | ...
*               |        hdc         |  |        hdc         |
*               |--------------------|  |--------------------|
*               | lf  |  tm |  Type  |  | lf  |  tm |  Type  |
*               |--------------------|  |--------------------|
*                 |       |       |       |       |       |
*                 |       |       |       |       |       |
*                 V       V       V       V       V       V
*               |----| |------| |----|  |----| |------| |----|
*               |LOG | |TEXT  | |Type|  |LOG | |TEXT  | |Type|
*               |FONT| |METRIC| |    |  |FONT| |METRIC| |    |
*               |0,0 | |0,0   | |0,0 |  |1,0 | |1,0   | |1,0 |
*               |----| |------| |----|  |----| |------| |----|
*               |LOG | |TEXT  | |Type|  |LOG | |TEXT  | |Type|
*               |FONT| |METRIC| |    |  |FONT| |METRIC| |    |
*               |0,1 | |0,1   | |0,1 |  |1,1 | |1,1   | |1,1 |
*               |----| |------| |----|  |----| |------| |----|
*
*                ...    ...      ...     ...    ...      ...
*
*               |----| |------| |----|
*               |LOG | |TEXT  | |Type|
*               |FONT| |METRIC| |    |  |----| |------| |----|
*               |0,  | |0,    | |0,  |  |LOG | |TEXT  | |Type|
*               |nFon| |nFonts| |nFon|  |FONT| |METRIC| |    |
*               |----| |------| |----|  |1,  | |1,    | |1,  |
*                                       |nFon| |nFonts| |nFon|
*                                       |----| |------| |----|
*
*
*   So, to get the FontType of the 4th font within the 2nd family use:
*    parFonts[1].Type[3]
*
*   There is one final ARFONT structure which has no linked lists atttached,
*    but has a blank HDC as padding on the far right of the window.
*
*   The pointer to the array of ARFONT structures is stored in the
*    GWL_PARFONTS extra bytes for each window.  The number of face names
*    for each window is stored in the GWLU_NFACES extra bytes.
*
\**************************************************************************/

#include <windows.h>
#include <string.h>
#include "ttfonts.h"


typedef struct tagArFonts{
  int        nFonts;
  int        cySpace;
  HDC        hdc;
  LOGFONT    *lf;
  TEXTMETRIC *tm;
  int        *Type;
} ARFONTS, *PARFONTS;


#define ALLFONTBORDER  10
#define CXDEF         130
#define BMSIZE         14


#define GWLU_PARFONTS 0
#define GWLU_NFACES   4

/* forward declare function prototypes. */
VOID     DrawBitmapXY (HDC, HBITMAP, int, int);

PARFONTS BuildFontList(HDC, LPINT);
VOID     BuildBitmapStrips (HWND, LPRECT, PARFONTS, int);

int APIENTRY MyEnumFaces(LPLOGFONT, LPTEXTMETRIC, DWORD, LPVOID);
int APIENTRY MyEnumCopy (LPLOGFONT, LPTEXTMETRIC, DWORD, LPVOID);
int APIENTRY MyEnumCount(LPLOGFONT, LPTEXTMETRIC, DWORD, LPINT);



int initAllFont(HWND hwndParent)
{
WNDCLASS  wc;
HDC       hdc;

  wc.style = 0;
  wc.lpfnWndProc = (WNDPROC)AllFontsWndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 8;
  wc.hInstance = hInst;
  wc.hIcon = LoadIcon(hInst, TEXT("ttfontsIcon"));
  wc.hCursor = LoadCursor(NULL, IDC_CROSS);
  wc.hbrBackground = GetStockObject(WHITE_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = TEXT("AllFonts");

  if (!RegisterClass(&wc)) return (FALSE);


  /* create a window to show all of the display fonts, and send it
   *  the proper WMU_CREATE message with an HDC for the display.
   */
  hwndDisplayFonts = CreateMDIWindow(
      TEXT("AllFonts"),
      TEXT("EnumFonts (display)"),
      WS_CHILD | WS_CLIPSIBLINGS | WS_MINIMIZEBOX | WS_MAXIMIZEBOX |
      WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_HSCROLL,
      0,0,
      GetSystemMetrics (SM_CXFULLSCREEN),
      GetSystemMetrics (SM_CYFULLSCREEN) - GetSystemMetrics (SM_CYMENU),
      hwndParent, hInst, 0);

  ShowWindow (hwndDisplayFonts, SW_HIDE);
  hdc = GetDC (hwndDisplayFonts);
  SendMessage (hwndDisplayFonts, WMU_CREATE, (DWORD)hdc, 0);
  ReleaseDC (hwndDisplayFonts, hdc);
  ShowWindow (hwndDisplayFonts, SW_SHOWMINIMIZED);

  if (!hwndDisplayFonts) return (FALSE);


  /* create a window to show all of the printer fonts, and send it
   *  the proper WMU_CREATE message with an HDC for the printer.
   */

  hwndPrinterFonts = CreateMDIWindow(
      TEXT("AllFonts"),
      TEXT("EnumFonts (printer)"),
      WS_CHILD | WS_CLIPSIBLINGS | WS_MINIMIZEBOX | WS_MAXIMIZEBOX |
      WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_HSCROLL,
      0,0,
      GetSystemMetrics (SM_CXFULLSCREEN),
      GetSystemMetrics (SM_CYFULLSCREEN) - GetSystemMetrics (SM_CYMENU),
      hwndParent, hInst, 0);
  if (!hwndPrinterFonts) return (FALSE);

  ShowWindow (hwndPrinterFonts, SW_HIDE);
  hdc = GetPrinterDC ();
  if (hdc == NULL) {
    SetWindowLong (hwndPrinterFonts, GWLU_PARFONTS, (LONG) NULL);
    DestroyWindow (hwndPrinterFonts);
    SendMessage (hwndMain, WM_COMMAND, IDU_NOPRINTER, 0);
  } else {
    SendMessage (hwndPrinterFonts, WMU_CREATE, (DWORD)hdc, 0);
    DeleteDC (hdc);
    ShowWindow (hwndPrinterFonts, SW_SHOWMINIMIZED);
  }

  return TRUE;
}





/**************************************************************************\
*  function:  GetPrinterDC
*
*  input parameters:  none.
*
* Simply return an HDC for the default printer.
*  Note that this HDC should be deleted later (DeleteDC).
*
*
\**************************************************************************/
HDC GetPrinterDC ()
{
  PRINTER_INFO_2  *pi2;
  DWORD  dwNeeded, dwReturned;
  HDC hdc;

  /* Figure out how much memory we need and alloc it. */
  EnumPrinters (PRINTER_ENUM_DEFAULT | PRINTER_ENUM_LOCAL,
                 NULL, 2,
                 NULL, 0,
                 &dwNeeded, &dwReturned);

  /* Watch for case of no default printer... return NULL. */
  if (dwNeeded == 0) return NULL;

  pi2 = LocalAlloc (LPTR, dwNeeded);

  /* Now actually get the information, and create an HDC if successful. */
  if (EnumPrinters (PRINTER_ENUM_DEFAULT | PRINTER_ENUM_LOCAL,
                 NULL, 2,
                 (LPBYTE) pi2, dwNeeded,
                 &dwNeeded, &dwReturned)) {

    hdc = CreateDC (pi2->pDriverName, pi2->pPrinterName, pi2->pPortName, NULL);
  } else {
    MessageBox (NULL, szEnumPrinterR, szMBERROR,MBERRORFLAGS);
    hdc = NULL;
  }

  /* Free memory */
  LocalFree (LocalHandle (pi2));

  return hdc;
}




/**************************************************************************\
*
*  function:  AllFontsWndProc
*
*  input parameters:  normal window procedure parameters.
*
*  global variables:
*   hwndMain - Main window.  place to return focus.
*
* Create array of structures which contain, among other things, bitmap
*  strips containing the face names of fonts.  These strips are later
*  scrolled back and forth as well as selected with the mouse.
*
\**************************************************************************/
LRESULT CALLBACK AllFontsWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
RECT rectClient;
int i,j;
int thumbpos;
int nStrips;
PARFONTS parFonts;
int nFaces;


  /* Get the pointer out of the userdata extra bytes.  */
  parFonts = (PARFONTS) GetWindowLong (hwnd, GWLU_PARFONTS);
  nFaces   =            GetWindowLong (hwnd, GWLU_NFACES);

  if ((parFonts == NULL) && (message != WMU_CREATE))
    return (DefMDIChildProc(hwnd, message, wParam, lParam));

  switch (message) {


    /**********************************************************************\
    *  WMU_CREATE
    *
    * USER create message (sent after the window is created, before it
    *  is shown for the first time).  Use this rather than WM_CREATE because
    *  we want to have control over the message parameters.
    *
    * wParam - HDC which we build the font list for.
    *
    * First build the 2d variable arrays of fonts (c.f. BuildFontList), then
    *  create the bitmap strips (stored in HDCs in ARFONT structures),
    *  Set the parFonts pointer into the extra bytes for use by other messages.
    \**********************************************************************/
    case WMU_CREATE: {
      int rightPos;
      HDC hdc;

      hdc = (HDC) wParam;

      GetClientRect (hwnd, &rectClient);
      InflateRect (&rectClient, 0, -ALLFONTBORDER);

      parFonts = BuildFontList (hdc, &nFaces);

      BuildBitmapStrips (hwnd, &rectClient, parFonts, nFaces);

      SetWindowLong (hwnd, GWLU_PARFONTS, (LONG) parFonts);
      SetWindowLong (hwnd, GWLU_NFACES,   nFaces);

      /* Compute the number of bitmap strips visible in the window.
       * set the scroll bar range,
       * or make it invisible if there are not enough fonts to justify.
       */
      nStrips = (rectClient.right - rectClient.left) /CXDEF + 1;
      if (nFaces > nStrips) {
        rightPos = nFaces - nStrips + 1;
        SetScrollRange (hwnd, SB_HORZ, 0, rightPos, FALSE);
      } else {
        SetScrollRange (hwnd, SB_HORZ, 0, 0, FALSE);
      }

    } break;


    /**********************************************************************\
    *  WM_DESTROY
    *
    * Free up the memory allocated at create time.  Notice that parFonts
    *  is allocated in BuildFontList, as are its subarrays.
    \**********************************************************************/
    case WM_DESTROY:
      for (i= 0; i<nFaces; i++) {
        LocalFree ( LocalHandle ((LPVOID)parFonts[i].lf   ));
        LocalFree ( LocalHandle ((LPVOID)parFonts[i].tm   ));
        LocalFree ( LocalHandle ((LPVOID)parFonts[i].Type ));
        DeleteDC (parFonts[i].hdc);
      }
      /* also get the final, blank one */
      DeleteDC (parFonts[nFaces].hdc);

      LocalFree ( LocalHandle ((LPVOID)parFonts));
    break;


    /**********************************************************************\
    *  WM_HSCROLL
    *
    * Slide the contents of the window back and forth.  Notice that the
    *  scroll bar thumb position is important for painting and hit testing.
    \**********************************************************************/
    case WM_HSCROLL:
      /* compute number of strips for page scrolling. */
      GetClientRect (hwnd, &rectClient);
      nStrips = (rectClient.right - rectClient.left) /CXDEF + 1;

      switch (LOWORD(wParam)){
        int OldPos, NewPos;

        case SB_LINEDOWN:
          OldPos = GetScrollPos (hwnd, SB_HORZ);
          SetScrollPos (hwnd, SB_HORZ, (OldPos+1), TRUE);
          NewPos = GetScrollPos (hwnd, SB_HORZ);
          ScrollWindow (hwnd, (OldPos-NewPos)*CXDEF, 0, NULL, NULL);
        break;

        case SB_PAGEDOWN:
          OldPos = GetScrollPos (hwnd, SB_HORZ);
          SetScrollPos (hwnd, SB_HORZ, (OldPos+(nStrips-1)), TRUE);
          NewPos = GetScrollPos (hwnd, SB_HORZ);
          ScrollWindow (hwnd, (OldPos-NewPos)*CXDEF, 0, NULL, NULL);
        break;

        case SB_LINEUP:
          OldPos = GetScrollPos (hwnd, SB_HORZ);
          SetScrollPos (hwnd, SB_HORZ, (OldPos-1), TRUE);
          NewPos = GetScrollPos (hwnd, SB_HORZ);
          ScrollWindow (hwnd, (OldPos-NewPos)*CXDEF, 0, NULL, NULL);
        break;

        case SB_PAGEUP:
          OldPos = GetScrollPos (hwnd, SB_HORZ);
          SetScrollPos (hwnd, SB_HORZ, (OldPos-(nStrips-1)), TRUE);
          NewPos = GetScrollPos (hwnd, SB_HORZ);
          ScrollWindow (hwnd, (OldPos-NewPos)*CXDEF, 0, NULL, NULL);
        break;

        case SB_THUMBPOSITION:
          OldPos = GetScrollPos (hwnd, SB_HORZ);
          NewPos = HIWORD (wParam);
          SetScrollPos (hwnd, SB_HORZ, NewPos, TRUE);
          ScrollWindow (hwnd, (OldPos-NewPos)*CXDEF, 0, NULL, NULL);
        break;

      }
    break;



    /**********************************************************************\
    *  WM_LBUTTONDOWN
    *
    * Hittest based on the mouse position.  When finished, hide the window.
    \**********************************************************************/
    case WM_LBUTTONDOWN: {
      POINT mousePt;

      mousePt.x = LOWORD(lParam);
      mousePt.y = HIWORD(lParam);

      mousePt.x -= 0;
      mousePt.y -= ALLFONTBORDER;

      i = mousePt.x / CXDEF;
      i += GetScrollPos (hwnd, SB_HORZ);
      if (i < 0) i = 0;
      if (i >= nFaces) i = (nFaces-1);

      j = mousePt.y / parFonts[i].cySpace;
      if (j < 0) j = 0;
      if (j >= parFonts[i].nFonts) j = (parFonts[i].nFonts-1);

      ShowWindow(hwnd, SW_MINIMIZE);
      UpdateWindow(hwndMain);
      flyWinWin(hwndMain,  hwnd, hwndDlgLF, 40);
      SendMessage (hwndDlgLF, WMU_DEMOTOLF, 0,(LONG) &(parFonts[i].lf[j]));

      flyWinWin(hwndMain,  hwnd, hwndDlgTM, 40);
      SendMessage (hwndDlgTM, WMU_DEMOTOTM, 0,(LONG) &(parFonts[i].tm[j]));
      SetFocus (hwndMain);

    }break;


    /**********************************************************************\
    *  WM_RBUTTONDOWN, WM_CHAR
    *
    * Put the window away without changing the LOGFONT or TEXTMETRIC dlgs.
    \**********************************************************************/
    case WM_RBUTTONDOWN:
    case WM_CHAR       :
      ShowWindow(hwnd, SW_MINIMIZE);
      SetFocus (hwndMain);
    break;


    /**********************************************************************\
    *  WM_PAINT
    *
    * Using the HDCs stored in the parFonts array, blt enough strips of
    *  font family names to cover the window.
    \**********************************************************************/
    case WM_PAINT : {
      PAINTSTRUCT ps;
      HDC hdc;
      int iStrip;

      if (parFonts == NULL)  break;

      GetClientRect (hwnd, &rectClient);
      hdc = BeginPaint(hwnd, &ps);

      thumbpos = GetScrollPos (hwnd, SB_HORZ);

      nStrips = (rectClient.right - rectClient.left) /CXDEF + 1;

      for (iStrip= 0; iStrip<nStrips; iStrip++)
          BitBlt (hdc, iStrip*CXDEF,0,
                  CXDEF,
                  (rectClient.bottom - rectClient.top),
                  parFonts[iStrip+thumbpos].hdc, 0,0, SRCCOPY);


      EndPaint (hwnd, &ps);
    } break;


    default: break;
    } /* end switch */

  return (DefMDIChildProc(hwnd, message, wParam, lParam));
}




/**************************************************************************\
*
*  function:  DrawBitmapXY()
*
*  input parameters:  HDC, HBITMAP,
*   X, Y - destination position.  (get width and height from hbitmap)
*
*  Draw the bitmap into the hdc.  Source rectangle computed to include the
*   whole bitmap.
*
*  global variables: none.
*
\**************************************************************************/
VOID DrawBitmapXY (HDC hdc, HBITMAP hbm, int x, int y)
{
    BOOL f;
    HDC hdcBits;
    BITMAP bm;

    hdcBits = CreateCompatibleDC(hdc);
    GetObject (hbm, sizeof(BITMAP), &bm);
    SelectObject(hdcBits,hbm);
    f = BitBlt(hdc,x,y,bm.bmWidth, bm.bmHeight,hdcBits,0,0,SRCCOPY);
    DeleteDC(hdcBits);
}







/**************************************************************************\
*  function:  BuildBitmapStrips
*
*  input parameters:
*   hwnd - window this will all be painted on some day, needed for GetDC
*   lprectClient - Pointer to client window rect, bitmap strips are this high
*   parFonts - array with all the font information.
*   nFaces - number of face names (array size of parFonts).
*
* Once the fonts have all been queried, create bitmaps and HDCs for them, and
*  draw the different fonts into the different bitmap strips.
\**************************************************************************/
VOID BuildBitmapStrips (HWND hwnd, LPRECT lprectClient,
                        PARFONTS parFonts, int nFaces)
{
int     i,j;
HFONT   hNewFont;
HBITMAP hbm;
HBITMAP hbmtt, hbmdevice;
RECT    rectClip, rectStrip;
HDC     hdc;
int     height;
int     rightshift;

  /* load 2 bitmaps used to "tag" true type and printer fonts. */
  hbmtt =     LoadBitmap (hInst, TEXT("bmtt"));
  hbmdevice = LoadBitmap (hInst, TEXT("bmdevice"));

  /* establish bounds of vertical strip that all fonts are drawn into. */
  hdc              = GetDC (hwnd);
  rectStrip.left   = rectStrip.top =0;
  rectStrip.right  = CXDEF;
  rectStrip.bottom = (lprectClient->bottom - lprectClient->top);


  /* step through all of the face names.  For each one, compute the cySpace-
   *  i.e. number of pixels per entry.  also create a memory DC that we can
   *  draw the font into.  This DC provides the STRIP later blt'ed out at
   *  paint time.
   */
  for (i= 0; i<nFaces; i++) {
    parFonts[i].cySpace = rectStrip.bottom / parFonts[i].nFonts;
    parFonts[i].hdc     = CreateCompatibleDC (hdc);

    /* When there is only one font, then make a small bitmap.  If there
     * is more than one, then make a bitmap the whole height of the window.
     */
    height = (parFonts[i].nFonts == 1) ?
      parFonts[i].lf[0].lfHeight + ALLFONTBORDER :
      rectStrip.bottom;
    hbm = CreateCompatibleBitmap (hdc, rectStrip.right,height);

    SelectObject (parFonts[i].hdc, hbm);
    FillRect (parFonts[i].hdc, &rectStrip, GetStockObject(WHITE_BRUSH));
    SelectObject (parFonts[i].hdc, GetStockObject(NULL_BRUSH));

    /* step through each font for the face name.  Establish a bounding
     *  rectangle for the name, write the name and mark with bitmaps if apropos
     */
    for (j = 0; j<parFonts[i].nFonts; j++) {
      rectClip.left   = 0;
      rectClip.right  = rectClip.left + CXDEF - 5;
      rectClip.top    = j*parFonts[i].cySpace+ALLFONTBORDER;
      rectClip.bottom = rectClip.top+ parFonts[i].lf[j].lfHeight;
      rightshift = 0;


      /* for true type fonts, add special bitmap on left, top */
      if (parFonts[i].Type[j] & TRUETYPE_FONTTYPE) {
        DrawBitmapXY (parFonts[i].hdc, hbmtt,rectClip.left,rectClip.top);
        rightshift = BMSIZE;
      }


      /* for printer fonts, add printer bitmap on left, shifted down
       */
      if (parFonts[i].Type[j] & DEVICE_FONTTYPE) {
        DrawBitmapXY (parFonts[i].hdc, hbmdevice,rectClip.left,rectClip.top+ BMSIZE);
        rightshift = BMSIZE;
      }

      /* Create a logical font to draw the face name with */
      hNewFont = CreateFontIndirect (&(parFonts[i].lf[j]));
      SelectObject (parFonts[i].hdc, hNewFont);

      /* iff bitmap drawn, shift text over to the right. */
      rectClip.left+=rightshift;

      /* draw the face name in the rectangle allotted. */
      ExtTextOut (parFonts[i].hdc,
                       rectClip.left, rectClip.top, ETO_CLIPPED,
                       &rectClip,
                       parFonts[i].lf[j].lfFaceName,
                       lstrlen(parFonts[i].lf[j].lfFaceName),
                       NULL );


      SelectObject (parFonts[i].hdc, GetStockObject (SYSTEM_FONT));
      DeleteObject (hNewFont);
    }
  }

  /* make one final strip on the far right side as a white space buffer */
  hbm = CreateCompatibleBitmap (hdc, rectStrip.right, rectStrip.bottom);
  SelectObject (parFonts[nFaces].hdc, hbm);
  FillRect (parFonts[nFaces].hdc, &rectStrip, GetStockObject(WHITE_BRUSH));

  ReleaseDC (hwnd, hdc);
  DeleteObject (hbmtt);
  DeleteObject (hbmdevice);
}





/* In the callback functions from the enumerations, there is a limited
 *  ability to pass in parameters.  For that reason, declare the following
 *  global variables to be used by any of the call back functions.
 */
HDC      hdcGlobal;
PARFONTS parFontsGlobal;
int      iFace,jFont;
int      nFaces;

/* General call structure:
 *
 *  BuildFontList()
 *      EnumFonts
 *          MyEnumCount()
 *      LocalAlloc
 *      EnumFonts
 *          MyEnumFaces()
 *              EnumFonts
 *                  MyEnumCount()
 *              LocalAlloc
 *              LocalAlloc
 *              LocalAlloc
 *              EnumFonts
 *                  MyEnumCopy()
 */



/**************************************************************************\
*  function:  BuildFontList
*
*  input parameters:
*   hdcIn - hdc to query the fonts for.
*   retnFaces - (OUT) pointer to nFaces value
*
* Enumerate all of the fonts for this DC allocating and filling up the
*  parFonts structure as needed.
\**************************************************************************/
PARFONTS BuildFontList(HDC hdcIn, LPINT retnFaces)
{

  nFaces = 0;

  /* hdcGlobal is global variable also used by the callback functions. */
  hdcGlobal = hdcIn;

  /* count the total number of face names. */
  EnumFonts (hdcGlobal, NULL, (FONTENUMPROC)MyEnumCount, (LPARAM)&nFaces);


  /* allocate the pointer to the array of PArFont structures. */
  parFontsGlobal = (PARFONTS)LocalAlloc (LPTR, sizeof(ARFONTS) * (nFaces+1));

  /* step through all fonts again.  For each one fill a LOGFONT and
   * a TEXTMETRIC stucture.
   */
  iFace = 0;
  EnumFonts (hdcGlobal, NULL, (FONTENUMPROC)MyEnumFaces, (LPARAM)NULL);

  *retnFaces = nFaces;
  return parFontsGlobal;
}







/**************************************************************************\
*  function:  MyEnumFaces
*
*  input parameters:  c.f. EnumFonts
*
* Count the number of fonts for this particular face name.  Allocate the
*  LOGFONT and TEXTMETRIC arrays large enough to hold all of them.  Then
*  enumerate the fonts once again to fill in these arrays.
\**************************************************************************/
int APIENTRY MyEnumFaces(
       LPLOGFONT  lpLogFont,
       LPTEXTMETRIC lpTEXTMETRICs,
       DWORD  fFontType,
       LPVOID  lpData)
{
int nFonts;


  UNREFERENCED_PARAMETER (lpTEXTMETRICs);
  UNREFERENCED_PARAMETER (fFontType);
  UNREFERENCED_PARAMETER (lpData);


  nFonts = 0;
  EnumFonts (hdcGlobal, lpLogFont->lfFaceName, (FONTENUMPROC)MyEnumCount, (LPARAM)&nFonts);


  parFontsGlobal[iFace].lf   = (LPLOGFONT)LocalAlloc (LPTR, sizeof(LOGFONT)    * nFonts);
  parFontsGlobal[iFace].tm   = (LPTEXTMETRIC)LocalAlloc (LPTR, sizeof(TEXTMETRIC) * nFonts);
  parFontsGlobal[iFace].Type = (LPINT)LocalAlloc (LPTR, sizeof(int)        * nFonts);

  if ((parFontsGlobal[iFace].lf   == NULL) ||
      (parFontsGlobal[iFace].tm   == NULL) ||
      (parFontsGlobal[iFace].Type == NULL)) {
    MessageBox (hwndMain, szAllocFailed, szMBERROR,MBERRORFLAGS);
    return FALSE;
  }

  parFontsGlobal[iFace].nFonts = nFonts;

  jFont = 0;
  EnumFonts (hdcGlobal, lpLogFont->lfFaceName, (FONTENUMPROC)MyEnumCopy, (LPARAM)NULL);

  iFace++;

  return TRUE;
}



/**************************************************************************\
*  function:  MyEnumCopy
*
*  input parameters:  c.f. EnumFonts
*
* Each time that this function is called, copy the LOGFONT and TEXTMETRIC
*  structures into the proper place in the global arrays.  Incr jFont.
\**************************************************************************/
int APIENTRY MyEnumCopy(
       LPLOGFONT  lpLogFont,
       LPTEXTMETRIC lpTEXTMETRICs,
       DWORD  fFontType,
       LPVOID  lpData)
{
LOGFONT    *lplf;
TEXTMETRIC *lptm;
int        *pType;

  UNREFERENCED_PARAMETER (lpData);

  lplf  = parFontsGlobal[iFace].lf;
  lptm  = parFontsGlobal[iFace].tm;
  pType = parFontsGlobal[iFace].Type;

  lplf[jFont]  = *lpLogFont;
  lptm[jFont]  = *lpTEXTMETRICs;
  pType[jFont] = fFontType;

  jFont++;
  return TRUE;
}



/**************************************************************************\
*  function:  MyEnumCount
*
*  input parameters:  c.f. EnumFonts
*
* Simply increment the variable that lpData points to.
\**************************************************************************/
int APIENTRY MyEnumCount(
       LPLOGFONT  lpLogFont,
       LPTEXTMETRIC lpTEXTMETRICs,
       DWORD  fFontType,
       LPINT  lpData)
{
    UNREFERENCED_PARAMETER (lpLogFont);
    UNREFERENCED_PARAMETER (lpTEXTMETRICs);
    UNREFERENCED_PARAMETER (fFontType);

    (*lpData)++;
    return TRUE;
}
