//*---------------------------------------------------------------------------------
//|  ODBC System Administrator
//|
//|  This code is furnished on an as-is basis as part of the ODBC SDK and is
//|  intended for example purposes only.
//|
//|   Title:   RESULTS.C
//|      This module contains functions which allow you to view results via an
//|      owner-drawn list box.  Having the list box functionality made it easy
//|      to implement Pipes, but has some serious draw-backs as far as record
//|      limits, storage methods, etc...  If you are looking for a great way to
//|      paint data in a grid, check out the C++ or Cursor Demo samples that came
//|      with this SDK.
//*---------------------------------------------------------------------------------
#include <stdio.h>
#include "errcheck.h"
#include "standard.h"
#include "results.h"
#include "math.h"
#include "ini.h"


//------------------------------------------------------------------------
//  Defines
//------------------------------------------------------------------------
VSZFile;


//------------------------------------------------------------------------
//  Globals
//------------------------------------------------------------------------
char szErrMsg[100];
dCSEG(char) szONE[]                       =  "1";
dCSEG(char) szZERO[]                      =  "0";
dCSEG(char) szdate[]                      =  "%02u/%02u/%02u";
dCSEG(char) sztime[]                      =  "%02u:%02u:%02u";
dCSEG(char) sztimestmp[]                  =  "%02u/%02u/%02u %02u:%02u:%02u.%lu";
dCSEG(char) szTypeNotFound[]              =  "Not found";
dCSEG(char) szMaxRowsFetched[]            =  "Maximum rows fetched.  Total rows: %lu";


struct {
   SWORD type;                      // Data type value
   LPSTR sztype;                    // String equivalent
   } SqlTypes[] = {
// type                 sztype
// -------------------  -----------------------------
   SQL_BIGINT,          "SQL_BIGINT=-5",
   SQL_BINARY,          "SQL_BINARY=-2",
   SQL_BIT,             "SQL_BIT=-7",
   SQL_CHAR,            "SQL_CHAR=1",
   SQL_DATE,            "SQL_DATE=9",
   SQL_DECIMAL,         "SQL_DECIMAL=3",
   SQL_DOUBLE,          "SQL_DOUBLE=8",
   SQL_FLOAT,           "SQL_FLOAT=6",
   SQL_INTEGER,         "SQL_INTEGER=4",
   SQL_LONGVARBINARY,   "SQL_LONGVARBINARY=-4",
   SQL_LONGVARCHAR,     "SQL_LONGVARCHAR=-1",
   SQL_NUMERIC,         "SQL_NUMERIC=2",
   SQL_REAL,            "SQL_REAL=7",
   SQL_SMALLINT,        "SQL_SMALLINT=5",
   SQL_TIME,            "SQL_TIME=10",
   SQL_TIMESTAMP,       "SQL_TIMESTAMP=11",
   SQL_TINYINT,         "SQL_TINYINT=-6",
   SQL_VARBINARY,       "SQL_VARBINARY=-3",
   SQL_VARCHAR,         "SQL_VARCHAR=12",
   };


struct {
   SWORD type;                      // Data type value
   LPSTR sztype;                    // String equivalent
   } CTypes[] = {
// type                 sztype
// -------------------  -----------------------------
   SQL_C_BINARY,        "SQL_C_BINARY=-2",
   SQL_C_BIT,           "SQL_C_BIT=-7",
   SQL_C_CHAR,          "SQL_C_CHAR=1",
   SQL_C_DATE,          "SQL_C_DATE=9",
   SQL_C_DOUBLE,        "SQL_C_DOUBLE=8",
   SQL_C_FLOAT,         "SQL_C_FLOAT=7",
   SQL_C_LONG,          "SQL_C_LONG=4",
   SQL_C_SHORT,         "SQL_C_SHORT=5",
   SQL_C_TIME,          "SQL_C_TIME=10",
   SQL_C_TIMESTAMP,     "SQL_C_TIMESTAMP=11",
   SQL_C_TINYINT,       "SQL_C_TINYINT=-6",
   };

typedef struct tagDATATYPE{
   SWORD type;                      // Data type value
   LPSTR sztype;                    // String equivalent
   } DATATYPE;


//------------------------------------------------------------------------
//  Local function prototypes
//------------------------------------------------------------------------
void CheckDisplayMode(LPSTR strin, SDWORD cbin, LPSTR strout);
BOOL INTFUN             DrawRow(DRAWITEMSTRUCT FAR * dw,
                           RESULTSSET FAR * rs, int xLeftCol, int xRightCol, BOOL fSelect);


//*------------------------------------------------------------------------
//| CreateResultsSet:
//|   This is the first function that should be called to create a
//|      results set.  When there is no more use for the results set,
//|      call DeleteResultsSet to delete it.
//|
//|   Parameters:
//|      in    rs                Pointer to a new results set
//|      in    hwndClient        Client window
//|      in    hInst             Instance handle of caller
//|      in    count             How many columns in the results set
//|      in    szTitle           Title for the window
//|
//|   Returns:
//|      TRUE if there were no errors,
//|      FALSE otherwise
//*------------------------------------------------------------------------
BOOL EXTFUN CreateResultsSet(RESULTSSET FAR * rs, HWND hwndClient, HINSTANCE hInst,
            int count, LPSTR szTitle)
{
   if(!rs ||
      count <=0)
      return FALSE;

   memset(rs, 0, sizeof(RESULTSSET));
   rs->cbColumns = count;
   rs->hInst = hInst;
   rs->hwndClient = hwndClient;
   if(*szTitle)
      lstrcpy(rs->szTitle, szTitle);

   rs->md = (METADATA FAR *)GetMemory(sizeof(METADATA) * count);
   if(!rs->md)
      return FALSE;

   return TRUE;
}


//*------------------------------------------------------------------------
//| SetMetaDataColumn:
//|   This function must be called for each column in the results set.  The
//|      information placed for each row can be obtained using ODBC functions
//|      such as SQLDescribeCol and SQLColAttribute.
//|   Parameters:
//|      in    rs                Pointer to a results set
//|      in    iCol              Column number
//|      in    szCol             Pointer to column name
//|      in    szTypeName        Data type name
//|      in    fSqlType          ODBC data type number
//|      in    precision         Precision
//|      in    scale             Scale
//|      in    cbDisplay         Display size
//|      in    fAlign            Alignment
//|   Returns:
//|      Nothing
//*------------------------------------------------------------------------
BOOL EXTFUN SetMetaDataColumn(RESULTSSET FAR * rs, int iCol, LPSTR szCol,
      LPSTR szTypeName, SDWORD fSqlType, UDWORD precision, SWORD scale,
      int cbDisplay, UINT fAlign)
{
   if(!rs ||
      iCol < 0 ||
      !szCol ||
      !*szCol ||
      !szTypeName ||
      !*szTypeName) {
      PostError((LPSTR)szInvalidParms);
      return FALSE;
   }

   rs->md[iCol].szColumnName = (LPSTR)GetMemory(lstrlen(szCol)+1);
   if(!rs->md[iCol].szColumnName)
      return FALSE;
   precision = min(precision, MAXBYTES);
   lstrcpy(rs->md[iCol].szColumnName, szCol);
   lstrcpy(rs->md[iCol].szTypeName, szTypeName);
   rs->md[iCol].fSqlType = fSqlType;
   rs->md[iCol].precision = precision;
   rs->md[iCol].scale = scale;
   rs->md[iCol].cbDisplaySize = cbDisplay;
   rs->md[iCol].fAlign = fAlign;
   rs->md[iCol].cbOffset = (iCol > 0) ? (UINT)(precision + rs->md[iCol-1].cbOffset) : (UINT)(precision);
   ++rs->md[iCol].cbOffset;               // Room for terminators

   return TRUE;
}



//*------------------------------------------------------------------------
//| AllocateRowData:
//|   Call this function for each row in the results set to allocate
//|      memory and insert a row into the results set.
//|   Parameters:
//|      in    rs                Pointer to results set
//|      in    rd                Pointer to a row data structure
//|      in    cColor            Text color
//|      in    cBkg              Background color
//|   Returns:
//|      Pointer to a ROWDATA structure
//*------------------------------------------------------------------------
ROWDATA FAR * AllocateRowData(RESULTSSET FAR * rs, COLORREF cColor, COLORREF cBkg)
{
   ROWDATA FAR *  rd;
   int            dex;

   if(!rs) {
      PostError((LPSTR)szInvalidParms);
      return FALSE;
   }
   rd = (ROWDATA FAR *)GetMemory(sizeof(ROWDATA));
   if(!rd)
      return NULL;
   rd->textColor = cColor;
   rd->bkgrnd = cBkg;
   rd->cd = (COLUMNDATA FAR *)GetMemory((sizeof(COLUMNDATA) * rs->cbColumns));
   if(!rd->cd)
      return NULL;
   rd->data = (LPSTR)GetMemory(rs->md[rs->cbColumns-1].cbOffset + 1);
   if(!rd->data)
      return NULL;
   rd->cd[0].szCols = rd->data;
   for(dex=1;  dex<rs->cbColumns;  dex++)
      rd->cd[dex].szCols = rd->data + rs->md[dex-1].cbOffset;

   return rd;
}



//*------------------------------------------------------------------------
//| SetColumnData:
//|   Call this function for a particular column in a ROWDATA structure.
//|      If memory has been allocated for the column, it will be freed
//|      and reallocated for the new string.
//|   Parameters:
//|      in    icol              Which column?
//|      in    rd                Pointer to a row data structure
//|      in    str               Pointer to the new buffer
//|   Returns:
//|      TRUE if successful
//|      FALSE on error
//*------------------------------------------------------------------------
BOOL EXTFUN SetColumnData(int icol, ROWDATA FAR * rd, LPSTR str)
{
   if(!str ||
      !*str)
      return FALSE;

   lstrcpy(rd->cd[icol].szCols, str);
   return TRUE;
}


//*------------------------------------------------------------------------
//| FreeRowData:
//|   Pass a pointer to the ROWDATA structure to free.  Obviously since
//|      you are asked for a RESULTSSET pointer, you should call this
//|      function before freeing the results set data.
//| Parms:
//|   in       rs                   Pointer to results set
//|   in       rd                   Pointer to row data
//| Returns:
//|   Nothing.
//*------------------------------------------------------------------------
void EXTFUN FreeRowData(RESULTSSET FAR * rs, ROWDATA FAR * rd)
{
   ReleaseMemory(rd->data);
   ReleaseMemory((LPVOID)rd->cd);
   ReleaseMemory((LPVOID)rd);
}



//*------------------------------------------------------------------------
//| FreeResultsSet:
//|   Call this function to free all of the memory for a results set.
//| Parms:
//|   in       rs                   Pointer to results set data to free
//| Returns:
//|   TRUE     If successful
//|   FALSE    if there was an error
//*------------------------------------------------------------------------
void EXTFUN FreeResultsSet(RESULTSSET FAR * rs)
{
   int   dex;

   DeleteObject(rs->hFont);

   for(dex=0;  dex<rs->cbColumns;  dex++)
      ReleaseMemory(rs->md[dex].szColumnName);
   ReleaseMemory(rs->md);
   ReleaseMemory(rs);
   return;
}



//*------------------------------------------------------------------------
//| CreateResultsFont:
//|   This function is called to create a font for the results set.  The
//|   default font is used if the lf parameter is NULL.  Alternatively
//|   the user can pass in a complete LOGFONT structure to use for the
//|   font.
//| Parms:
//|   in       rs                   Pointer to results set to store info
//|   in       hwnd                 Window handle to verify font
//|   in       lf                   LOGFONT structure to use, NULL for dft
//| Returns:
//|   Nothing.
//*------------------------------------------------------------------------
void CreateResultsFont(RESULTSSET FAR * rs, HWND hwnd, LOGFONT FAR * lf)
{
   HDC                     hdc;
   LOGFONT                 logfont;
   HFONT                   hf;
   TEXTMETRIC              tm;
   SIZE                    sz;
   int                     tmp, dex, cbExtra;

   if(!lf) {
      memset(&logfont, 0, sizeof(LOGFONT));
      GetDefaultFont(&logfont);
   }
   else
      memmove(&logfont, lf, sizeof(LOGFONT));

   rs->hFont = CreateFontIndirect(&logfont);
   hdc = GetDC(hwnd);
   hf = SelectObject(hdc, rs->hFont);
   GetTextMetrics(hdc, &tm);
   rs->cx = tm.tmAveCharWidth;

   rs->cy = tm.tmHeight + tm.tmExternalLeading;
   cbExtra = GetSystemMetrics(SM_CYBORDER);
   rs->cTitleHeight = rs->cy + (7 * cbExtra);
   rs->yTitleLoc = (rs->cTitleHeight / 2) + rs->cy;
   for(dex=0, tmp=0;  dex<rs->cbColumns;  dex++) {
      GetTextExtentPoint(hdc, rs->md[dex].szColumnName,
                         lstrlen(rs->md[dex].szColumnName), &sz);
      rs->md[dex].cColWidth = (rs->md[dex].cbDisplaySize * rs->cx) + (7 * cbExtra);
      rs->md[dex].cColWidth = max((UINT)(sz.cx * 1.5),
                                  rs->md[dex].cColWidth);
      rs->md[dex].xCol = tmp;
      tmp += rs->md[dex].cColWidth;
   }
   rs->cRowWidth = tmp;

   SelectObject(hdc,hf);
   ReleaseDC(hwnd, hdc);
}


//*------------------------------------------------------------------------
//| FindRightCol:
//|   This function will take the left column and a results set descriptor
//|      and return the right column index based on what will fit in the
//|      window.
//| Parms:
//|   in       rs                   Pointer to results set to store info
//|   in       xLeftCol             Current left column index
//|   in       cWidth               Available width
//| Returns:
//|   Index to be used for right column
//*------------------------------------------------------------------------
int FindRightCol(RESULTSSET FAR * rs, int xLeftCol, int cWidth)
{
   int xRightCol;
   int cSpace;

   xRightCol = xLeftCol;
   cSpace = cWidth - rs->md[xLeftCol].cColWidth;
   while(cSpace>0 &&
         xRightCol < rs->cbColumns-1) {
      ++xRightCol;
      cSpace -= rs->md[xRightCol].cColWidth;
   }
   return xRightCol;
}


//*------------------------------------------------------------------------
//| DrawRowData:
//|   This function will do the actual drawing on the screen based on the
//|      control structures passed in.
//| Parms:
//|   in       rs                   Pointer to results set to store info
//|   in       dwitem               Draw structure
//|   in       xLeftCol             Current left column index
//|   in       xRightCol            Right column index
//| Returns:
//|   Nothing.
//*------------------------------------------------------------------------
void DrawRowData(RESULTSSET FAR * rs, DRAWITEMSTRUCT FAR * dwitem,
               int xLeftCol, int xRightCol)
{
   switch(dwitem->itemAction) {
     case ODA_DRAWENTIRE:
     case ODA_SELECT:
      DrawRow(dwitem, rs, xLeftCol, xRightCol,
              (dwitem->itemState == ODS_SELECTED));
      return;
   }
}


//*------------------------------------------------------------------------
//| DrawColumnTitles:
//|   This function is called when we need to paint the column titles for a
//|      results set.  We will simply write them out.
//| Parms:
//|   in       hdc                  Handle to our device contex
//|   in       rs                   Our results set to draw
//|   in       crect                Client rectangle to paint in
//|   in       xLeftCol             Left column
//|   in       xRightCol            Right column
//| Returns:
//|   Nothing.
//*------------------------------------------------------------------------
void INTFUN DrawColumnTitles(HDC hdc, RESULTSSET FAR * rs,
            RECT FAR * crect, int xLeftCol, int xRightCol)
{
   int               dex, offset, cright=0;
   RECT              rect;
   HFONT             hf;

   hf = SelectObject(hdc, rs->hFont);
   SetTextColor(hdc, RDATA_BLACK);
   offset = 0 - rs->md[xLeftCol].xCol;
   for (dex=xLeftCol; dex<=xRightCol; dex++)
      cright += rs->md[dex].cColWidth;
   Rectangle(hdc, crect->left, crect->top, min(cright, crect->right), crect->bottom+1);
   SetBkColor(hdc, RDATA_GRAY);

   rect.top = crect->top +1;
   rect.bottom = crect->bottom;
   for(dex=xLeftCol;  dex<=xRightCol;  dex++) {
      rect.left = rs->md[dex].xCol + offset;
      rect.right = rect.left + rs->md[dex].cColWidth;
      MoveTo(hdc, rect.right, rect.top);
      LineTo(hdc, rect.right, rect.bottom);
      ++rect.left;
#ifdef TITLE_DEBUG
      {
         char tmpbuff[50];
         wsprintf(tmpbuff, "Column: %d, left=%d, top=%d, right=%d, bottom=%d",
                  dex,
                  rect.left, rect.top,
                  rect.right, rect.bottom);
         DrawFocusRect(hdc, &rect);
         MessageBox(NULL, (LPSTR)tmpbuff, "Debug", MB_OK);
         DrawFocusRect(hdc, &rect);
      }
#endif
      ExtTextOut(hdc, rs->md[dex].xCol + 3 + offset, rect.top + 4,
                 ETO_CLIPPED | ETO_OPAQUE,
                 &rect,
                 rs->md[dex].szColumnName,
                 lstrlen(rs->md[dex].szColumnName),
                 NULL);
   }
   SelectObject(hdc,hf);               // change font back
}



//*------------------------------------------------------------------------
//| DrawRow:
//|   Call this function for each row which must be painted.
//| Parms:
//|   in       dw                   Draw structure
//|   in       rs                   Our results set to draw
//|   in       xLeftCol             Index to left-most column displayed
//|   in       xRightCol            Index to right-most column displayed
//|   in       fSelect              Is the item supposed to be selected?
//| Returns:
//|   TRUE if successful,
//|   FALSE otherwise
//*------------------------------------------------------------------------
//#define RECT_DEBUG
BOOL INTFUN DrawRow(DRAWITEMSTRUCT FAR * dw,
                     RESULTSSET FAR * rs,
                     int xLeftCol, int xRightCol,
                     BOOL fSelect)
{
   ROWDATA FAR *     rd=(ROWDATA FAR *)dw->itemData;
   int               dex;
   int               offset;
   int               cright=0;
   RECT              rect;
   HFONT             hf;

   //
   // First set the font and text colors according to the user's request, then draw
   //    a line at the bottom of the row for a separator.  Note that the rcItem
   //    rectangle passed to us in the DRAWITEMSTRUCT is for the
   //
   hf = SelectObject(dw->hDC, rs->hFont);
   dw->rcItem.right = min(rs->cRowWidth, dw->rcItem.right);
   for (dex=xLeftCol; dex<=xRightCol; dex++)
      cright += rs->md[dex].cColWidth;
   // Draw top of box
   MoveTo(dw->hDC, dw->rcItem.left, dw->rcItem.top);
   LineTo(dw->hDC, min(cright, dw->rcItem.right), dw->rcItem.top);

   // Draw bottom also, to take care of last line
   MoveTo(dw->hDC, dw->rcItem.left, dw->rcItem.bottom);
   LineTo(dw->hDC, min(cright, dw->rcItem.right), dw->rcItem.bottom);

#ifdef RECT_DEBUG
   {
      char tmpbuff[50];
      wsprintf(tmpbuff, "dw->rcItem, left=%d, top=%d, right=%d, bottom=%d",
               dw->rcItem.left, dw->rcItem.top,
               dw->rcItem.right, dw->rcItem.bottom);
      DrawFocusRect(dw->hDC, &dw->rcItem);
      MessageBox(NULL, (LPSTR)tmpbuff, "Debug", MB_OK);
      DrawFocusRect(dw->hDC, &dw->rcItem);
   }
#endif

   //
   // Now loop through each column in the row and draw it's contents by creating
   //    a logical rectangle for each column, then filling in that rectangle with
   //    the value to be displayed.
   //
   rect.top = dw->rcItem.top+1;
   rect.bottom = dw->rcItem.bottom;
   SetBkMode(dw->hDC, TRANSPARENT);
   if(fSelect) {
      SetBkColor(dw->hDC, GetSysColor(COLOR_HIGHLIGHT));
      SetTextColor(dw->hDC, GetSysColor(COLOR_HIGHLIGHTTEXT));
   }
   else {
      SetBkColor(dw->hDC, rd->bkgrnd);
      SetTextColor(dw->hDC, rd->textColor);
   }
   offset = 0 - rs->md[xLeftCol].xCol;
   for (dex=xLeftCol; dex<=xRightCol; dex++) {
      rect.left = offset + rs->md[dex].xCol;
      rect.right = rect.left + rs->md[dex].cColWidth;
      MoveTo(dw->hDC, rect.right, rect.top);
      LineTo(dw->hDC, rect.right, rect.bottom);

#ifdef RECT_DEBUG
      {
         char tmpbuff[50];
         wsprintf(tmpbuff, "Column: %d, left=%d, top=%d, right=%d, bottom=%d",
                  dex,
                  rect.left, rect.top,
                  rect.right, rect.bottom);
         DrawFocusRect(dw->hDC, &rect);
         MessageBox(NULL, (LPSTR)tmpbuff, "Debug", MB_OK);
         DrawFocusRect(dw->hDC, &rect);
      }
#endif
      SetTextAlign(dw->hDC, rs->md[dex].fAlign);
      if(dex != xLeftCol)
         ++rect.left;
      ExtTextOut(dw->hDC, rs->md[dex].xCol + 3 + offset, rect.top + 4,
                 ETO_CLIPPED | ETO_OPAQUE,
                 &rect,
                 rd->cd[dex].szCols,
                 lstrlen(rd->cd[dex].szCols),
                 NULL);
   }
   SelectObject(dw->hDC,hf);              // change font back

   return TRUE;
}


//*------------------------------------------------------------------------
//| HandleHScroll:
//|   This function adds a new item to our results set.
//| Parms:
//|   in       wParam               Scroll option
//|   in       rs                   Results set pointer
//|   in       hwnd                 Window handle for column title
//|   in       hwndHScroll          Scroll bar window handle
//|   in       xLeftCol             Left column index
//|   in       xRightCol            Right column index
//|   in       hwndList             Listbox window handle
//|   in       cbColumns            Number of columns
//|   in       cbClient             Width of screen available to draw in
//|   in       tRect                Bounding rectangle for client window
//| Returns:
//|   Index to string if successful, LB_ERRSPACE otherwise
//*------------------------------------------------------------------------
void HandleHScroll(WPARAM wParam, RESULTSSET FAR * rs,
         HWND hwnd, HWND hwndHScroll, int FAR * xLeftCol, int FAR * xRightCol,
         HWND hwndList, int cbColumns, int cbClient, RECT FAR * tRect)
{
   int      cHScrollPos;
   int      fhScroll=FALSE;

   cHScrollPos = GetScrollPos(hwndHScroll, SB_CTL);
   switch(wParam) {
     case SB_LINEUP:          // Shift right one column
      if(!*xLeftCol)
         fhScroll = FALSE;
      else {
         --cHScrollPos;
         fhScroll = TRUE;
         --*xLeftCol;
      }
      break;

     case SB_LINEDOWN:           // Shift left one column
      if(*xLeftCol+1 == cbColumns)
         fhScroll = FALSE;             // No change required
      else {
         ++cHScrollPos;
         fhScroll = TRUE;
         ++*xLeftCol;
      }
      break;

     case SB_PAGEUP:          // Shift right one screen
      if(!*xLeftCol)
         fhScroll = FALSE;
      else {
         --cHScrollPos;
         fhScroll = TRUE;
         --*xLeftCol;
      }
      break;

     case SB_PAGEDOWN:           // Shift left one screen
      if(*xLeftCol+1 == cbColumns)
         fhScroll = FALSE;             // No change required
      else {
         if(*xLeftCol < *xRightCol) {
            cHScrollPos += *xRightCol - *xLeftCol;
            *xLeftCol = *xRightCol;
            fhScroll = TRUE;
         }
         else {
            ++cHScrollPos;
            ++*xLeftCol;
            fhScroll = TRUE;
         }
      }
      break;

     case SB_THUMBPOSITION:      // Specific location
      break;
   }

   //
   // If movement is required, we will have adjusted the scroll position
   //    and columns already.  Calculate what columns will fit on our current
   //    display to find the rightmost column.  Next invalidate the areas
   //    requiring painting and set the new scroll position.  This will cause
   //    each row to be redrawn starting with the new rwi->xLeftCol.
   //
   if(fhScroll) {                      // Movement is required
      RECT     rect;
      *xRightCol = FindRightCol(rs, *xLeftCol, cbClient);
      GetClientRect(hwndList, &rect);
      InvalidateRect(hwndList, &rect, TRUE);
      SetScrollPos(hwndHScroll, SB_CTL, cHScrollPos, TRUE);
      InvalidateRect(hwnd, tRect, TRUE);
   }
}


//*------------------------------------------------------------------------
//| HandleVirtualHScroll:
//|   This function should be called in response to the WM_KEYDOWN
//|   message. It will look for a virtual key to see if the user
//|   is trying to do scrolling.  If so, we will force the scroll
//|   to happen.
//| Parms:
//|   in       wParam               Value of wParam for WM_KEYDOWN
//|   in       hwndList             Handle of list box
//|   in       hwndOwner            Owner window of the horizontal scrollbar
//| Returns:
//|   Nothing.
//*------------------------------------------------------------------------
void HandleVirtualHScroll(WPARAM wParam, HWND hwndList, HWND hwndOwner)
{
   switch(wParam) {
     case VK_HOME:
      SendMessage(hwndList, WM_VSCROLL, SB_TOP, 0L);
      return;

     case VK_END:
      SendMessage(hwndList, WM_VSCROLL, SB_BOTTOM, 0L);
      return;

     case VK_PRIOR:
      SendMessage(hwndList, WM_VSCROLL, SB_PAGEUP, 0L);
      return;

     case VK_NEXT:
      SendMessage(hwndList, WM_VSCROLL, SB_PAGEDOWN, 0L);
      return;

     case VK_UP:
      SendMessage(hwndList, WM_VSCROLL, SB_LINEUP, 0L);
      return;

     case VK_DOWN:
      SendMessage(hwndList, WM_VSCROLL, SB_LINEDOWN, 0L);
      return;

     case VK_LEFT:
      SendMessage(hwndOwner, WM_HSCROLL, SB_LINEUP, 0L);
      return;

     case VK_RIGHT:
      SendMessage(hwndOwner, WM_HSCROLL, SB_LINEDOWN, 0L);
      return;
   }
}


//*------------------------------------------------------------------------
//| AddRowData:
//|   This function adds a new item to our results set.
//| Parms:
//|   in       rs                   Pointer to results set
//|   in       rd                   Pointer to row data to add
//| Returns:
//|   Index to string if successful, LB_ERRSPACE otherwise
//*------------------------------------------------------------------------
int AddRowData(RESULTSSET FAR * rs, ROWDATA FAR * rd)
{
   int         rtn;
   DWORD       cbCnt;
   rtn = (int)SendMessage(rs->hwndList, LB_ADDSTRING, 0, (LPARAM)(ROWDATA FAR *)rd);
   if(rtn == LB_ERRSPACE) {
      cbCnt = SendMessage(rs->hwndList, LB_GETCOUNT, 0, 0L);
      wsprintf(szErrMsg, szMaxRowsFetched, cbCnt);
      MessageBox(rs->hwndClient, szErrMsg, szErrTitle, MB_OK);
   }
   return rtn;
}






//*------------------------------------------------------------------------
//| GetNumResultsCols:
//|   Given an hstmt which has an executed statement on it, find the number
//|      of results columns in it.
//| Parms:
//|   in       hstmt                Statement handle with results set
//| Returns:
//|   Number of columns
//*------------------------------------------------------------------------
SWORD GetNumResultsCols(HSTMT hstmt)
{
   SWORD cbCols;
   RETCODE retcode;

   retcode = SQLNumResultCols(hstmt, &cbCols);
   if(RC_NOTSUCCESSFUL(retcode))
      return -1;
   else
      return cbCols;
}



//*------------------------------------------------------------------------
//| GetTypeName:
//|   This function will return the null-terminated character name of
//|   the type passed in.
//| Parms:
//|   in       type                 SQL_TYPE or C_TYPE
//|   in       fType                The fCType or fSqlType
//| Returns:
//|   Nothing.
//*------------------------------------------------------------------------
LPSTR GetTypeName(int type, int fType)
{
   int               dex, stopdex;
   DATATYPE FAR *    dt;

   if(type == SQL_TYPE) {
      stopdex = NumItems(SqlTypes);
      dt = (DATATYPE FAR *)&SqlTypes;
   }
   else {
      stopdex = NumItems(CTypes);
      dt = (DATATYPE FAR *)&CTypes;
   }
   for(dex=0;  dex<stopdex;  dex++)
      if(dt[dex].type == fType)
         return dt[dex].sztype;
   return (LPSTR)szTypeNotFound;
}


//*------------------------------------------------------------------------
//| ConvertSqlTypeToChar:
//|   This function will convert the value passed in to it's character equivalent.
//| Parms:
//|   in       rs                   Pointer to results set
//|   in       col                  Which column is it?
//|   in       inbuff               Input buffer
//|   in       outbuff              Output buffer
//|   in       rtnd                 Returned bytes from SQLGetData
//| Returns:
//|   Nothing.
//*------------------------------------------------------------------------
void ConvertSqlTypeToChar(RESULTSSET FAR * rs, int col, LPSTR inbuff,
         LPSTR outbuff, SDWORD rtnd)
{
   LPSTR                   tmpstr;
   SWORD FAR *             tmpsword;
   SDWORD FAR *            tmpsdword;
   SFLOAT FAR *            tmpsfloat;
   SDOUBLE FAR *           tmpsdouble;
   DATE_STRUCT FAR *       tmpdate;
   TIME_STRUCT FAR *       tmptime;
   TIMESTAMP_STRUCT FAR *  tmptimestmp;

   *outbuff = '\0';
   switch(rs->md[col].fSqlType) {
      //
      // Look for any non-displayable characters and change them to periods
      //
     case SQL_CHAR:
     case SQL_VARCHAR:
     case SQL_LONGVARCHAR:
      CheckDisplayMode((LPSTR)inbuff, rtnd, outbuff);
      tmpstr = outbuff + rtnd;
      *tmpstr = '\0';
      break;

     case SQL_BINARY:
     case SQL_VARBINARY:
     case SQL_LONGVARBINARY:
      lstrcpy(outbuff, "0x");
      BinToChar(outbuff+2, (LPSTR)inbuff, rtnd);
      break;

     case SQL_TINYINT:
     case SQL_SMALLINT:
      tmpsword = (SWORD FAR *)inbuff;
      wsprintf(outbuff, "%d", *tmpsword);
      break;

     case SQL_INTEGER:
     case SQL_BIGINT:
      tmpsdword = (SDWORD FAR *)inbuff;
      wsprintf(outbuff, "%ld", *tmpsdword);
      break;

     case SQL_FLOAT:
     case SQL_DOUBLE:
      tmpsdouble = (SDOUBLE FAR *)inbuff;
      sprintf(outbuff, "%Fg", *tmpsdouble);
      break;

     case SQL_REAL:
      tmpsfloat = (SFLOAT FAR *)inbuff;
      sprintf(outbuff, "%Fg", *tmpsfloat);
      break;

     case SQL_BIT:
      tmpsword = (SWORD FAR *)inbuff;
      lstrcpy(outbuff, (*tmpsword) ? (LPSTR)szONE : (LPSTR)szZERO);
      break;

     case SQL_DECIMAL:
     case SQL_NUMERIC:
      lstrcpy(outbuff, inbuff);
      break;

     case SQL_DATE:
      tmpdate = (DATE_STRUCT FAR *)inbuff;
      wsprintf(outbuff, szdate, tmpdate->month, tmpdate->day, tmpdate->year);
      break;

     case SQL_TIME:
      tmptime= (TIME_STRUCT FAR *)inbuff;
      wsprintf(outbuff, sztime, tmptime->hour, tmptime->minute, tmptime->second);
      break;

     case SQL_TIMESTAMP:
      tmptimestmp = (TIMESTAMP_STRUCT FAR *)inbuff;
      wsprintf(outbuff, sztimestmp, tmptimestmp->year, tmptimestmp->month,
               tmptimestmp->day, tmptimestmp->hour, tmptimestmp->minute,
               tmptimestmp->second, tmptimestmp->fraction);
      break;
   }

   return;
}


//*------------------------------------------------------------------------
//| CheckDisplayMode:
//|   This function looks through a string for the count specified, then
//|      changes any x"00" to a period so it can be displayed.
//| Parms:
//|   strin       - String coming in
//|   cbin        - Byte count of incoming string
//|   strout      - Output string
//*------------------------------------------------------------------------
void CheckDisplayMode(LPSTR strin, SDWORD cbin, LPSTR strout)
{
   SDWORD      dex,max=cbin;
   LPSTR    str=strout;

   if(cbin < 0)
      max = lstrlen(strin);
   memcpy(strout, strin, (size_t)max);
   for(dex=0; dex<cbin; dex++, str++)
      if(!*str)
         *str = '.';
}


//*------------------------------------------------------------------------
//| BinToChar:
//|   Takes a string and converts to its hexidecimal equivalent
//*------------------------------------------------------------------------
void BinToChar(LPSTR outstr, LPSTR instr, SDWORD count)
{
   UCHAR uletter;
   LPSTR istr=instr;
   LPSTR ostr=outstr;

   while(count--) {
      uletter = (*instr & 0xF0) >> 4;              // High nibble
      if(uletter <= 9)
         *ostr++ = uletter + '0';
      else
         *ostr++ = 'A' + (uletter - 10);
      uletter = *instr++ & 0x0F;
      if(uletter <= 9)
         *ostr++ = uletter + '0';
      else
         *ostr++ = 'A' + (uletter - 10);
   }
   *ostr = '\0';
}


