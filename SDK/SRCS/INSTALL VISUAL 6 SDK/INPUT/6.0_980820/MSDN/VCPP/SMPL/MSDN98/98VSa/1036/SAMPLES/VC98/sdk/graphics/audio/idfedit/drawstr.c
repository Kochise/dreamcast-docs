
/*****************************************************************************
*
*  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
*  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
*  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
*  A PARTICULAR PURPOSE.
*
*  Copyright (C) 1993 - 1997 Microsoft Corporation. All Rights Reserved.
*
*****************************************************************************/

/*+ DrawStr.c
 *
 *-=================================================================*/

#include <windows.h>
#include <windowsx.h>

#include <string.h>
#include <memory.h>
#include <stdlib.h>

#include "drawstr.h"
#include "tridee.h"
#include "res.h"
#include "idfedit.h"

CONST LOGFONT lfMain = {
    12,                        //int   lfHeight;
    0,                         //int   lfWidth;
    0,                         //int   lfEscapement;
    0,                         //int   lfOrientation;
    FW_DONTCARE,               //int   lfWeight;
    0,                         //BYTE  lfItalic;
    0,                         //BYTE  lfUnderline;
    0,                         //BYTE  lfStrikeOut;
    ANSI_CHARSET,              //BYTE  lfCharSet;
    OUT_DEFAULT_PRECIS,        //BYTE  lfOutPrecision;
    CLIP_DEFAULT_PRECIS,       //BYTE  lfClipPrecision;
    DEFAULT_QUALITY,           //BYTE  lfQuality;
    DEFAULT_PITCH | FF_SWISS,  //BYTE  lfPitchAndFamily;
    "MS Sans Serif",           //BYTE  lfFaceName[LF_FACESIZE];
    };

DSPREF dspref = {0};
BOOL   bInEditingMode;

#ifdef USE_MDI
 #define DefProc DefMDIChildProc
#else
 #define DefProc DefWindowProc
#endif

/*+  AccessFilter
 *
 *   exception filter for access violations
 *
 *   this function is a filter for an except block. It must
 *   return one of the following DWORD values:
 *      EXCEPTION_EXECUTE_HANDLER
 *      EXCEPTION_CONTINUE_SEARCH
 *      EXCEPTION_CONTINUE_EXECUTION
 *
 *-=================================================================*/

DWORD AccessFilter (
   DWORD dwExceptCode)
{
   if (dwExceptCode == EXCEPTION_ACCESS_VIOLATION)
      return EXCEPTION_EXECUTE_HANDLER;
   return EXCEPTION_CONTINUE_SEARCH;
}

/*+ DrawDsLabels
 *
 *-=================================================================*/

VOID WINAPI DrawDsLabels (
   HDC          hDC,
   PDSFIELDTBL  pTable,
   PDSLINEINFO  pLineInfo,
   LPRECT       lpRect,
   POINT        ptOffset)
   {
   WORD        wOldAlign;  // temp, prev state of alignment
   UINT        ii;         // general index variable
   int         cx;         // current x position to draw at
   int         cy;         // current y position to draw at
   int         cyText;
   PDSFIELD    pField;
   struct _dsline * pLine;
   char        sz[100];

   // do some simple error checking, if not a valid DC
   // dont go any further.
   //
   if (!hDC)
      return;

   // get the text metrics and initialize the max width variable
   //
   cyText = pLineInfo->cyLine;

   // setup the current x & y locations for writing text
   //
   cx = lpRect->left - ptOffset.x;
   cy = lpRect->top - ptOffset.y;

   // draw each of the labels making a vertical
   // column starting 'cx,cy'.  But be sure not to
   // draw outside of the rectangle 'lpRect'
   //
   wOldAlign = SetTextAlign (hDC, TA_TOP | TA_LEFT);

   // clear the background
   //
   ExtTextOut (hDC, cx, cy, ETO_CLIPPED | ETO_OPAQUE, lpRect, "", 0, NULL);

   // draw the labels
   //
   for (pLine = &pLineInfo->aLine[ii = 0];
        ii < pLineInfo->nCurLine;
        ++ii, ++pLine, cy += cyText)
      {
      if (cy < lpRect->top - cyText)
         continue;

      if (cy > lpRect->bottom)
         break;

      pField = pTable[pLine->uStruct].pFields;
      pField += pLine->uField;

      wsprintf (sz, pField->psz, pLine->uMember);

      if (sz[0] == ' ')
         {
         SetTextAlign (hDC, TA_TOP | TA_RIGHT);
         cx = lpRect->right - 2;
         }
      else
         {
         SetTextAlign (hDC, TA_TOP | TA_LEFT);
         cx = lpRect->left - ptOffset.x + (pLine->uDepth-1) * 16;
         }

      // draw the label pointed to by pFields[ii].psz
      // then increment cy by the height of a label
      //
      ExtTextOut (hDC,
                  cx,
                  cy,
                  ETO_CLIPPED,
                  lpRect,
                  sz,
                  lstrlen(sz),
                  NULL);
      }

   // restore text alignment and return
   //
   SetTextAlign (hDC, wOldAlign);

   return;
   }

/*+ GetFieldText
 *
 *-=================================================================*/

VOID WINAPI GetFieldText (
   PDSFIELD  pField,
   LPVOID    lpData,
   UINT      uMember,
   LPSTR     pszIn,
   UINT      cchIn,
   PDSBUFF   pds)
   {
   UINT    cb;
   LPBYTE  lp;

   pds->ptr = pszIn;
   pds->cch = cchIn;
   if (pds->cch > 10) // allow a bit of slop
      pds->cch -= 10;
   pds->ptr[0] = 0;

   __try
      {
      if (pField->fmt & AS_REF)
         {
         lp = *(LPBYTE *)lpData;
         lp += (uMember * pField->siz);

         if (dspref.bShowAddresses)
            {
            wsprintf (pds->ptr, "@%08x: ", lpData);
            cb = lstrlen(pds->ptr);
            pds->ptr += cb;
            pds->cch -= cb;
            }
         }
      else
         {
         lp = (LPBYTE)lpData + (uMember * pField->siz);

         if (dspref.bShowAddresses)
            {
            wsprintf (pds->ptr, "@%08x: ", lp);
            cb = lstrlen(pds->ptr);
            pds->ptr += cb;
            pds->cch -= cb;
            }
         }


      if (lp == NULL)
         lstrcpy (pds->ptr, "<null>");
      else
      switch (pField->fmt & 0xFF)
         {
         case AS_NONE:
            //wsprintf (pds->ptr, "%08X = ", lp);
            break;

         case AS_SZ:
            strncpy (pds->ptr, (LPTSTR)lp, pds->cch);
            break;

         case AS_MODE:
            {
            UINT (*pfnMode)(LPSTR, UINT, DWORD) = (LPVOID)pField->aux;

            if (pField->siz == sizeof(DWORD))
                pfnMode (pds->ptr, pds->cch, *(DWORD *)lp);
            else
                pfnMode (pds->ptr, pds->cch, (DWORD)lp);
            }
            break;

         case AS_XMODE:
            {
            UINT (*pfnMode)(LPSTR, UINT, UINT, UINT, UINT) = (LPVOID)pField->aux;

            if (pField->siz == sizeof(DWORD))
                pfnMode (pds->ptr, pds->cch, *(UINT *)lp, pField->array, WM_GETTEXT);
            else
                pfnMode (pds->ptr, pds->cch, (UINT)lp, pField->array, WM_GETTEXT);
            }
            break;

         case AS_ERROR:
            {
            UINT cb;
            DWORD dwError = *(LPDWORD)lp;

            pds->ptr[0] = 0;
            if (dwError)
                FormatMessage (FORMAT_MESSAGE_IGNORE_INSERTS
                               | FORMAT_MESSAGE_FROM_SYSTEM,
                               0,
                               dwError,
                               0,
                               pds->ptr,
                               pds->cch,
                               NULL);

            // get rid of terminating CR/LF if it exists
            //
            cb = lstrlen(pds->ptr);
            if (cb > 2)
               pds->ptr[cb-2] = 0;
            }
            break;

         case AS_ACH:
            {
            UINT jj;
            for (jj = 0; jj < pds->cch-1 && jj < pField->siz; ++jj)
                pds->ptr[jj] = lp[jj] > 31 ? lp[jj] : '.';
            pds->ptr[jj] = 0;
            }
            break;

         case AS_DUMP:
            {
            UINT   jj;
            UINT   cb;

            for (jj = 0; jj < pField->siz; jj += sizeof(WORD))
               {
               cb = wsprintf (pds->ptr, "%04X ", *(WORD *)(lp+jj));
               if (cb >= pds->cch)
                  {
                  pds->ptr[pds->cch-1] = 0;
                  break;
                  }

               pds->cch -= cb;
               pds->ptr += cb;
               }

            for (jj = 0; jj < pds->cch-1 && jj < pField->siz; ++jj)
                pds->ptr[jj] = lp[jj] > 31 ? lp[jj] : '.';
            pds->ptr[jj] = 0;
            }
            break;

         case AS_HEX:
            {
            UINT   jj;
            UINT   cb;

            if (pField->siz == sizeof(DWORD))
                pds->ptr += wsprintf (pds->ptr, "%08X", *(DWORD *)lp);
            else
            for (jj = 0; jj < pField->siz; jj += sizeof(WORD))
               {
               cb = wsprintf (pds->ptr, "%04X ", *(WORD *)(lp+jj));
               if (cb >= pds->cch)
                  {
                  pds->ptr[pds->cch-1] = 0;
                  break;
                  }

               pds->cch -= cb;
               pds->ptr += cb;
               }
            *pds->ptr = 0;
            }
            break;

         case AS_INT:
         case AS_UINT:
            if (sizeof(WORD) == pField->siz)
               wsprintf (pds->ptr, "%d", *(WORD *)lp);
            else if (sizeof(DWORD) == pField->siz)
               wsprintf (pds->ptr, "%d", *(DWORD *)lp);
            else
               {
               int  jj;
               UINT cb;

               for (jj = pField->siz-2; jj >= 0; jj -= sizeof(WORD))
                  {
                  cb = wsprintf (pds->ptr, "%d ", *(WORD *)(lp+jj));
                  if (cb >= pds->cch)
                     {
                     pds->ptr[pds->cch-1] = 0;
                     break;
                     }
                  pds->ptr += cb;
                  pds->ptr -= cb;
                  }
               *pds->ptr = 0;
               }
            break;

         case AS_HANDLE:
            wsprintf (pds->ptr, "%08X", *(UINT *)lp);
            break;

         case AS_BITFIELD:
            lstrcpy (pds->ptr, ((*(UINT *)lp & (1 << pField->aux)) ? "TRUE" : "FALSE"));
            break;

         case AS_RECT:
            wsprintf (pds->ptr, "%d,%d,%d,%d", *(LPRECT)lp);
            break;

         case AS_POINT:
         case AS_SIZE:
            wsprintf (pds->ptr, "%d,%d", *(LPPOINT)lp);
            break;

         case AS_POINTS:
            wsprintf (pds->ptr, "%d,%d", ((SHORT *)lp)[0], ((SHORT *)lp)[1]);
            break;

         case AS_FLOAT:
            lstrcpy (pds->ptr, "<float not supported>");
            break;

         case AS_BYTES:
            {
            UINT   jj;
            LPTSTR psz = pds->ptr;

            for (jj = 0; jj < pField->siz; ++jj)
               {
               wsprintf (psz, "%3d ", *(BYTE *)((LPSTR)lp+jj));
               psz += lstrlen(psz);
               *psz = 0;
               if (psz > (pds->ptr + pds->cch - 10))
                  {
                  *psz++ = '.';
                  *psz++ = '.';
                  *psz++ = '.';
                  *psz++ = 0;
                  break;
                  } 
               }
            }
            break;
         }
      }
   __except (AccessFilter(GetExceptionCode()))
      {
      lstrcpy (pds->ptr, "<no access>");
      }

   return;
   }

/*+ SetFieldText
 *
 *
 *-=================================================================*/

BOOL SetFieldText (
   struct _dsline * pLine,
   PDSFIELD         pField,
   PDSBUFF          pds)
{
   LPBYTE lpv;

   lpv = pLine->lpv;
   if (pField->fmt & AS_REF)
     lpv = *(LPBYTE *)lpv;
   lpv += (pLine->uMember * pField->siz);

   if (!pds->cch)
      return FALSE;
   pds->ptr[pds->cch-1] = 0;

   switch (pField->fmt & 0xFF)
      {
      case AS_SZ:
         strncpy (lpv, pds->ptr, min(pField->siz, pds->cch));
         break;

      case AS_BITFIELD:
         {
         LPTSTR psz = pds->ptr;

         while (*psz == '\t' && *psz == ' ')
            ++psz;

         if ((*psz & ~0x20) == 'T' || (*psz & ~0x20) == 'Y' || *psz == '1')
            *(LPDWORD)lpv |= (1 << pField->aux);
         else if ((*psz & ~0x20) == 'F' || (*psz & ~0x20) == 'N' || *psz == '0')
            *(LPDWORD)lpv &= ~(1 << pField->aux);
         }
         break;

      case AS_XMODE:
         {
         UINT (*pfnMode)(LPSTR, UINT, UINT, UINT, UINT) = (LPVOID)pField->aux;

         if (pField->siz == sizeof(DWORD))
             pfnMode (pds->ptr, pds->cch, *(UINT *)lpv, pField->array, WM_SETTEXT);
         else
             pfnMode (pds->ptr, pds->cch, (UINT)lpv, pField->array, WM_SETTEXT);
         }
         break;

      case AS_UINT:
         {
         LPSTR pszStop = pds->ptr;
         DWORD dw = (DWORD)strtoul (pds->ptr, &pszStop, 10);
         if (pszStop != pds->ptr)
            {
            if (pField->siz == sizeof(DWORD))
               *(LPDWORD)lpv = dw;
            else if (pField->siz == sizeof(WORD))
               *(LPWORD)lpv = LOWORD(dw);
            }
         }
         break;

      case AS_INT:
         {
         LPSTR pszStop = pds->ptr;
         LONG  ii = strtol (pds->ptr, &pszStop, 10);
         if (pszStop != pds->ptr)
            {
            if (pField->siz == sizeof(LONG))
               *(LPLONG)lpv = ii;
            else if (pField->siz == sizeof(short))
               *(short int *)lpv = (short int)ii;
            }
         }
         break;

      case AS_BYTES:
         {
         UINT   jj;
         LPTSTR psz;

         psz = pds->ptr;
         for (jj = 0; jj < pField->siz; ++jj)
            {
            ULONG uu;
            LPTSTR pszStop;
            while (*psz == '\t' || *psz == ' ')
               ++psz;

            pszStop = psz;
            uu = strtoul (psz, &pszStop, 10);
            if (pszStop == psz)
               break;

            lpv[jj] = (BYTE)uu;

            psz = pszStop;
            }
         }
         break;

      case AS_HEX:
         {
         DWORD  dw = 0;
         LPTSTR psz;

         psz = pds->ptr;
         while (*psz == '\t' || *psz == ' ')
             ++psz;

         if (psz[0] == '0' && (psz[1] == 'X' || psz[1] == 'x'))
             psz += 2;

         while (*psz)
            {
            if (*psz >= '0' && *psz <= '9')
               dw = (dw << 4) + *psz - '0';
            else if ((*psz >= 'A' && *psz <= 'F') ||
                     (*psz >= 'a' && *psz <= 'f'))
               dw = (dw << 4) + (*psz & ~0x20) - 'A' + 10;
            else
               break;
            ++psz;
            }

         if (dw != 0 || (psz > pds->ptr && psz[-1] == '0'))
            {
            if (pField->siz == sizeof(DWORD))
               *(LPDWORD)lpv = dw;
            else if (pField->siz == sizeof(WORD))
               *(LPWORD)lpv = LOWORD(dw);
            }
         }
         break;
      }

   return TRUE;
}

/*+ DrawDsData
 *
 *-=================================================================*/

VOID WINAPI DrawDsData (
   HDC          hDC,
   PDSFIELDTBL  pTable,
   PDSLINEINFO  pLineInfo, //
   LPRECT       lpRect,     // rectangle to clip drawing to
   POINT        ptOffset)   // scrolling offset for upper left corner
   {
   WORD        wOldAlign;  // temp, prev state of alignment
   UINT        ii;         // general index variable
   int         cx;         // current x position to draw at
   int         cy;         // current y position to draw at
   int         cyText;
   PDSFIELD    pField;
   struct _dsline * pLine;

   // do some simple error checking, if not a valid DC
   // dont go any further.
   //
   if (!hDC)
      return;

   // get the text metrics and initialize the max width variable
   //
   cyText = pLineInfo->cyLine;

   // setup the current x & y locations for writing text
   //
   cx = lpRect->left - ptOffset.x;
   cy = lpRect->top - ptOffset.y;

   // draw each of the labels making a vertical
   // column starting 'cx,cy'.  But be sure not to
   // draw outside of the rectangle 'lpRect'
   //
   wOldAlign = SetTextAlign (hDC, TA_TOP | TA_LEFT);

   // clear the background
   //
   ExtTextOut (hDC, cx, cy, ETO_CLIPPED | ETO_OPAQUE, lpRect, "", 0, NULL);

   // draw the data
   //
   for (pLine = &pLineInfo->aLine[ii = 0];
        ii < pLineInfo->nCurLine;
        ++ii, ++pLine, cy += cyText)
      {
      char   sz[1024]; // buffer for formatting text info
      LPBYTE lpv;
      DSBUFF ds;
      UINT   cb;

      if (cy < lpRect->top - cyText)
         continue;
      if (cy > lpRect->bottom)
         break;

      pField = pTable[pLine->uStruct].pFields;
      pField += pLine->uField;
      lpv = pLine->lpv;

      sz[0] = 0;
      GetFieldText (pField, lpv, pLine->uMember, sz, NUMELMS(sz), &ds);
      if (cb = lstrlen (sz))
         ExtTextOut (hDC,
                     cx, cy,
                     ETO_CLIPPED, lpRect, sz, cb, NULL);
      }

   // restore text alignment and return
   //
   SetTextAlign (hDC, wOldAlign);

   return;
   }

/*+ GetDsLabelWidth
 *
 *-=================================================================*/

int WINAPI GetDsLabelWidth (
   HDC          hDC,
   PDSFIELDTBL  pTable,
   PDSLINEINFO  pLineInfo)
   {
   int  cxWidth = 0;
   UINT ii;
   struct _dsline * pLine = pLineInfo->aLine;

   for (pLine = &pLineInfo->aLine[ii = 0];
        ii < pLineInfo->nCurLine;
        ++ii, ++pLine)
      {
      PDSFIELD pFields = pTable[pLine->uStruct].pFields;
      SIZE     size = {0,0};

      GetTextExtentPoint (hDC,
                          pFields[pLine->uField].psz,
                          lstrlen (pFields[pLine->uField].psz),
                          &size);

      size.cx += (pLine->uDepth * 16) - 16;

      if (cxWidth < size.cx)
         cxWidth = size.cx;
      }

   return cxWidth;
   }

/*+ AllocDsLineInfo
 *
 *-=================================================================*/

PDSLINEINFO WINAPI AllocDsLineInfo (
   UINT nMax)
   {
   PDSLINEINFO pLineInfo;

   pLineInfo = GlobalAllocPtr (GHND, sizeof(DSLINEINFO)
                               + sizeof(struct _dsline) * nMax);
   pLineInfo->nMaxLine = nMax;
   pLineInfo->nMaxDepth = 10;
   pLineInfo->nCurLine = 0;
   pLineInfo->nCurDepth = 0;
   return pLineInfo;
   }

/*+ BuildDsLineInfo
 *
 *-=================================================================*/

VOID WINAPI BuildDsLineInfo (
   PDSFIELDTBL  pTable,
   UINT         uStruct,    //
   LPVOID       lpData,     // pointer to structure to show
   WORD         nMember,
   WORD         nLastMember,
   PDSLINEINFO  pLineInfo)
   {
   UINT      uField;
   PDSFIELD  pField;
   UINT      cbStruct;

   if (!pTable)
     return;
   pField = pTable[uStruct].pFields;
   cbStruct = pTable[uStruct].cbSize;


   if (pLineInfo->nCurDepth >= pLineInfo->nMaxDepth)
      return;

   ++pLineInfo->nCurDepth;

   do
   {
      // now build the lines
      //
      for (uField = 0; pField->psz != NULL; ++pField, ++uField)
         {
         UINT   ix;

         if (pLineInfo->nCurLine >= pLineInfo->nMaxLine)
            break;

         ix = 0;
         do {
            struct _dsline * pLine;
            LPBYTE lpv;

            if (pLineInfo->nCurLine >= pLineInfo->nMaxLine)
               break;

            pLine = &pLineInfo->aLine[pLineInfo->nCurLine];
            ++pLineInfo->nCurLine;

            pLine->uStruct = uStruct;
            pLine->uField = uField;
            pLine->uDepth = pLineInfo->nCurDepth;
            pLine->uMember = ix;
            pLine->lpv = (LPVOID)-2;

            __try
               {
               lpv = (LPBYTE)lpData + (cbStruct * nMember) + pField->off;

               pLine->lpv = lpv;

               if (HIWORD(lpv)) // simple validity check...
                  {
                  lpv += (ix * pField->siz);
                  if ((pField->fmt & 0x1FF) == AS_STRUCT)
                      BuildDsLineInfo (pTable, pField->aux, lpv,
                                       (WORD)ix, (WORD)ix, pLineInfo);
                  }
               }
            __except (AccessFilter(GetExceptionCode()))
               {
               }
            } while (++ix < pField->array);
         }

   } while (++nMember <= nLastMember);

   --pLineInfo->nCurDepth;
   return;
   }

/*+ GetViewExtent
 *
 *-=================================================================*/

int WINAPI GetViewExtent (
   HDC         hDC,
   PVIEWINIT   pvim,
   PDSLINEINFO pLineInfo,
   LPSIZE      lpItemSize,
   LPSIZE      lpTotalSize)
   {
   TEXTMETRIC tm;

   pLineInfo->nCurLine = 0;
   pLineInfo->nCurDepth = 0;

   BuildDsLineInfo (pvim->pTable,
                    pvim->uStruct,
                    pvim->lpData,
                    0, 0,
                    pLineInfo);

   GetTextMetrics (hDC, &tm);
   pLineInfo->cyLine = tm.tmHeight + tm.tmExternalLeading;

   lpItemSize->cx = GetDsLabelWidth (hDC, pvim->pTable, pLineInfo);
   lpItemSize->cy = pLineInfo->cyLine;

   lpTotalSize->cx = lpItemSize->cx * 2;
   lpTotalSize->cy = pLineInfo->cyLine * pLineInfo->nCurLine;

   return pLineInfo->nCurLine;
   }

/*+
 *  ViewWndProc
 *
 *-=================================================================*/

// misc manifest constants
//
#define HTLABEL 1
#define HTEDGE  2
#define HTDATA  3

typedef struct _viewstate {
   UINT        wLabelWidth;
   SIZE        sTotal;
   SIZE        sLabel;
   SIZE        sScroll;
   POINT       ptVisible;
   //HBRUSH      hBrFace;
   HFONT       hFontLabel;
   HFONT       hFontData;
   HMENU       hMenu;
   WORD        wHit;
   UINT        nHitLine;
   HCURSOR     hCurEdge;
   POINT       ptEdgeBegin;
   int         cxEdgeSlop;
   POINT       ptLastEdge;
   int         nWindowCnt;
   PDSLINEINFO pLineInfo;
   int         cyLine;
   int         cyWnd;
   VIEWINIT    vi;
   } VIEWSTATE, *PVIEWSTATE;


/*+
 *
 *
 *-=================================================================*/

VOID WINAPI UpdateScrollRanges (
   PVIEWSTATE pv,
   HWND       hWnd)
   {
   RECT rc;

   pv->sTotal.cy = pv->cyLine * pv->pLineInfo->nCurLine;

   GetClientRect (hWnd, &rc);
   pv->cyWnd = (rc.bottom - rc.top);
   pv->cyWnd -= (pv->cyWnd % pv->cyLine);
   pv->sScroll.cy = max (pv->sTotal.cy - pv->cyWnd, 0);
   pv->ptVisible.y = min (pv->sScroll.cy, pv->ptVisible.y);

   SetScrollRange (hWnd, SB_VERT, 0, pv->sScroll.cy, FALSE);
   SetScrollPos (hWnd, SB_VERT, pv->ptVisible.y, TRUE);
   }

/*+
 *  ViewPrivate
 *
 *-=================================================================*/

UINT WINAPI EditInPlace (
   HWND       hWnd,
   PVIEWSTATE pv,
   UINT       nLine);

LONG WINAPI ViewPrivate (
   HWND   hWnd,
   UINT   wMsgID,
   WPARAM wParam,
   LPARAM lParam)
   {
   LONG       lRet = 0l;               // return value from this routine
   PVIEWSTATE pv;

   pv = (LPVOID) GetWindowLong (hWnd, GWL_USERDATA);
   if (!pv)
      return 0;

   switch (wMsgID)
      {
      case VM_GETDATA:
         lRet = (LRESULT)pv->vi.lpData;
         break;

      case VM_SETDATA:
         lRet = (LRESULT)pv->vi.lpData;
         pv->vi.lpData = (LPVOID)lParam;
         if (lRet != (LRESULT)pv->vi.lpData)
            {
            RECT rc;

            pv->pLineInfo->nCurLine = 0;
            pv->pLineInfo->nCurDepth = 0;

            BuildDsLineInfo (pv->vi.pTable,
                             pv->vi.uStruct,
                             pv->vi.lpData,
                             0, 0,
                             pv->pLineInfo);

            GetClientRect (hWnd, &rc);
            rc.left = pv->wLabelWidth + 5;
            InvalidateRect (hWnd, &rc, FALSE);
            }
         break;

      case VM_INVALIDATE:
         {
         RECT  rc;
         int   yLine;

         if (!wParam && !lParam)
            InvalidateRect (hWnd, NULL, FALSE);

         GetClientRect (hWnd, &rc);
         yLine = ((int)lParam * pv->cyLine) - pv->ptVisible.y;
         if (yLine >= rc.top && yLine <= rc.bottom)
            {
            rc.left += pv->wLabelWidth + 5;
            rc.top += yLine;
            rc.bottom = rc.top + (pv->cyLine * max(1, wParam));
            InvalidateRect (hWnd, &rc, FALSE);
            }
         }
         break;

      case VM_SETSEL:
         {
         UINT nLine = (UINT)lParam;
         BOOL bPrev = (BOOL)wParam;

         while (nLine < pv->pLineInfo->nCurLine)
            {
            struct _dsline * pLine = &pv->pLineInfo->aLine[nLine];
            PDSFIELD pField = pv->vi.pTable[pLine->uStruct].pFields + pLine->uField;
            if (pField->fmt & IS_EDIT)
               {
               RECT rc;
               int  yLine;

               GetClientRect (hWnd, &rc);
               yLine = (int)(nLine * pv->cyLine) - pv->ptVisible.y;
               if (yLine >= rc.top && (yLine + pv->cyLine) <= rc.bottom)
                  pv->nHitLine = nLine, lRet = 1;
               break;
               }
            if (bPrev && nLine == 0)
                break;
            nLine = bPrev ? nLine-1 : nLine+1;
            }

         }
         break;

      case VM_EDITNEXT:
         {
         UINT nLine = pv->nHitLine;
         BOOL bPrev = (BOOL)wParam;

         if (bPrev && nLine == 0)
            break;
         nLine = bPrev ? nLine-1 : nLine+1;

         if (ViewPrivate (hWnd, VM_SETSEL, bPrev, nLine))
            {
            EditInPlace (hWnd, pv, pv->nHitLine);
            }
         }
      }

   return lRet;
   }

/*+
 *  
 *
 *-=================================================================*/

LRESULT Notify (
   HWND hWnd,
   UINT code)
{
   NMHDR nm;

   nm.hwndFrom = hWnd;
   nm.idFrom = GetDlgCtrlID(hWnd);
   nm.code = code;
   return SendMessage (GetParent(hWnd), WM_NOTIFY, nm.idFrom, (LPARAM)(LPVOID)&nm);
}

/*+
 *  EditInPlace
 *
 *-=================================================================*/

UINT WINAPI EditInPlace (
   HWND       hWnd,
   PVIEWSTATE pv,
   UINT       nLine)
   {
   PDSFIELDTBL  pTable = pv->vi.pTable;
   PDSLINEINFO  pLineInfo = pv->pLineInfo;
   struct _dsline * pLine;
   PDSFIELD         pField;
   TCHAR        sz[1000];
   HWND         hWndEdit;
   RECT         rc;
   MSG          msg;
   UINT         uId;
   DSBUFF       ds;

   if (nLine >= pLineInfo->nCurLine)
      return 0;

   pLine = &pLineInfo->aLine[nLine];
   pField = pTable[pLine->uStruct].pFields + pLine->uField;

   GetFieldText (pField, pLine->lpv, pLine->uMember, sz, NUMELMS(sz), &ds);

   GetClientRect (hWnd, &rc);
   rc.left += pv->wLabelWidth + 5;
   rc.top = (nLine * pv->cyLine) - pv->ptVisible.y -2;
   rc.bottom = rc.top + pv->cyLine + 4;

   hWndEdit = CreateWindowEx (fdwExStyle | WS_EX_NOPARENTNOTIFY,
                              "Edit",
                              sz,
                              ES_AUTOHSCROLL |
                              ES_LEFT |
                              WS_CHILD | WS_BORDER,
                              rc.left, rc.top,
                              rc.right - rc.left, rc.bottom - rc.top,
                              hWnd,
                              (HMENU)IDE_VALUE,
                              GetWindowInstance(hWnd),
                              NULL);
   if ( ! hWndEdit)
      return 0;

   SendMessage (hWndEdit, WM_SETFONT, (WPARAM)pv->hFontData, 0);
   Edit_SetSel (hWndEdit, 0, NUMELMS(sz)+2);
   ShowWindow (hWndEdit, SW_SHOWNORMAL);
   SetFocus (hWndEdit);

   uId = IDOK;
   bInEditingMode = TRUE;
   do {
      if (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
         {
         if (msg.hwnd != hWndEdit &&
             (msg.message == WM_LBUTTONDOWN ||
              msg.message == WM_RBUTTONDOWN))
            break;

         if (msg.message == WM_QUIT)
            break;

         if (msg.message == WM_SYSKEYDOWN)
            break;

         GetMessage (&msg, NULL, 0, 0);
         if ((msg.hwnd == hWndEdit) && (msg.message == WM_KEYDOWN))
            {
            if (LOWORD(msg.wParam) == VK_RETURN)
               break;
            else if (LOWORD(msg.wParam) == VK_TAB)
               {
               PostMessage (hWnd, VM_EDITNEXT, (WPARAM)GetKeyState(VK_SHIFT), 0);
               break;
               }
            else if (LOWORD(msg.wParam) == VK_ESCAPE)
               {
               uId = IDCANCEL;
               break;
               }
            }

         TranslateMessage (&msg);
         DispatchMessage (&msg);
         }
      else
         {
         //SendMessage (hWnd, WM_ENTERIDLE, 0, 0);
         WaitMessage();
         }

      } while (bInEditingMode && GetFocus() == hWndEdit);

   bInEditingMode = FALSE;
   if (uId == IDOK)
   {
       GetWindowText (hWndEdit, sz, NUMELMS(sz));
       ds.ptr = sz;
       ds.cch = lstrlen(ds.ptr)+1;
       SetFieldText (pLine, pField, &ds);
       ViewPrivate (hWnd, VM_INVALIDATE, 0, nLine);
       Notify (hWnd, VN_CHANGE);
   }
   DestroyWindow (hWndEdit);

   return uId;
}

/*+
 *  CopyLineToClip
 *
 *-=================================================================*/

LONG WINAPI CopyLineToClip (
   HWND       hWnd,
   PVIEWSTATE pv,
   UINT       nLine)
{
   PDSFIELDTBL  pTable = pv->vi.pTable;
   PDSLINEINFO  pLineInfo = pv->pLineInfo;
   HGLOBAL      hMem;
   struct _dsline * pLine;
   PDSFIELD         pField;
   UINT         cfType;

   pLine = &pLineInfo->aLine[nLine];
   pField = pTable[pLine->uStruct].pFields + pLine->uField;

   switch (pField->fmt & 0xFF)
      {
      case AS_BYTES:
      case AS_DUMP:
         {
         LPRIFF pRiff;
         LPBYTE lpv;

         lpv = pLine->lpv;
         if (pField->fmt & AS_REF)
            lpv = *(LPBYTE *)lpv;
         lpv += (pLine->uMember * pField->siz);

         cfType = CF_RIFF;
         hMem = GlobalAlloc (GHND, pField->siz + sizeof(RIFF));
         if (!(pRiff = GlobalLock (hMem)))
            return 0;

         pRiff->fcc = MAKEFOURCC('B','y','t','e');
         pRiff->cb = pField->siz;
         CopyMemory (pRiff+1, lpv, pField->siz);
         GlobalUnlock (hMem);
         }
         break;

      case AS_XMODE:
         {
         UINT (*pfnMode)(LPSTR, UINT, UINT, UINT, UINT) = (LPVOID)pField->aux;
         LPBYTE lpv;

         lpv = pLine->lpv;
         if (pField->fmt & AS_REF)
            lpv = *(LPBYTE *)lpv;
         lpv += (pLine->uMember * pField->siz);

         if (pField->siz == sizeof(DWORD))
             {
             if (pfnMode (NULL, (UINT)hWnd, *(UINT *)lpv, pField->array, WM_COPY))
                return 0;
             }
         else
             {
             if (pfnMode (NULL, (UINT)hWnd, (UINT)lpv, pField->array, WM_COPY))
                return 0;
             }
         }
         // fall through
      default:
         {
         DSBUFF ds;
         LPSTR  psz;
         UINT   cch = 128 * 5 + 10;
         cfType = CF_TEXT;

         hMem = GlobalAlloc (GHND, cch);
         if (!(psz = GlobalLock (hMem)))
            return 0;

         // get data for the current line into the global
         // object.
         //
         GetFieldText (pField, pLine->lpv, pLine->uMember, psz, cch, &ds);

         // truncate the global object to fit the size of the data
         //
         GlobalUnlock (hMem);
         GlobalReAlloc (hMem, lstrlen(psz) + 2, 0);
         }
         break;
      }

   if (OpenClipboard (hWnd))
       {
       EmptyClipboard ();
       SetClipboardData (cfType, hMem);
       CloseClipboard ();
       }
   else
       GlobalFree (hMem);

   return 0;
}

/*+
 *  PasteLineFromClip
 *
 *-=================================================================*/

LONG WINAPI PasteLineFromClip (
   HWND       hWnd,
   PVIEWSTATE pv,
   UINT       nLine)
{
   HGLOBAL hMem;
   PDSFIELDTBL  pTable = pv->vi.pTable;
   PDSLINEINFO  pLineInfo = pv->pLineInfo;
   struct _dsline * pLine = &pLineInfo->aLine[nLine];
   PDSFIELD     pField = pTable[pLine->uStruct].pFields + pLine->uField;
   LONG lRet = 0;

   switch (pField->fmt & 0xFF)
      {
      case AS_BYTES:
      case AS_DUMP:
          if (OpenClipboard (hWnd))
             {
             if (hMem = GetClipboardData (CF_RIFF))
               {
               LPRIFF pRiff;
               LPBYTE lpv;

               lpv = pLine->lpv;
               if (pField->fmt & AS_REF)
                  lpv = *(LPBYTE *)lpv;
               lpv += (pLine->uMember * pField->siz);

               if (pRiff = GlobalLock (hMem))
                  {
                  if (pRiff->fcc == MAKEFOURCC('B','y','t','e') &&
                      pRiff->cb == pField->siz)
                     {
                     CopyMemory (lpv, pRiff+1, pField->siz);
                     lRet = 2;
                     }
                  GlobalUnlock (hMem);
                  }
               } 
            CloseClipboard ();
            }
         break;

      case AS_XMODE:
         {
         UINT (*pfnMode)(LPSTR, UINT, UINT, UINT, UINT) = (LPVOID)pField->aux;
         LPBYTE lpv;

         lpv = pLine->lpv;
         if (pField->fmt & AS_REF)
            lpv = *(LPBYTE *)lpv;
         lpv += (pLine->uMember * pField->siz);

         if (pField->siz == sizeof(DWORD))
             lRet = pfnMode (NULL, (UINT)hWnd, *(UINT *)lpv, pField->array, WM_PASTE);
         else
             lRet = pfnMode (NULL, (UINT)hWnd, (UINT)lpv, pField->array, WM_PASTE);

         // fall through if pfnMode handled the paste operation
         //
         if (lRet != 0)
            break;
         }
         // fall through
      default:
         if (OpenClipboard (hWnd))
            {
            if (hMem = GetClipboardData (CF_TEXT))
               {
               DSBUFF ds;
               ds.ptr = GlobalLock (hMem);
               if (ds.ptr)
                  {
                  ds.cch = lstrlen(ds.ptr)+1;
                  SetFieldText (pLine, pField, &ds);
                  lRet = 2;
                  }
               }
            CloseClipboard ();
            }
         break;
      }

   if (lRet > 0)
   {
      ViewPrivate (hWnd, VM_INVALIDATE, 0, nLine);
      Notify (hWnd, VN_CHANGE);
   }

   return lRet;
}

/*+
 *  ViewCommands
 *
 *-=================================================================*/

LONG WINAPI ViewCommands (
   HWND   hWnd,
   WPARAM wParam,
   LPARAM lParam)
   {
   LONG       lRet = 0l;               // return value from this routine
   PVIEWSTATE pv;

   pv = (LPVOID) GetWindowLong (hWnd, GWL_USERDATA);
   if (!pv)
      return 0;

   switch (GET_WM_COMMAND_ID(wParam,lParam))
      {
      case IDM_OBJEDIT:
          EditInPlace   (hWnd, pv, pv->nHitLine);
          //EditLineValue (hWnd, pv, pv->nHitLine);
          break;

      case IDM_EDITCOPY:
          CopyLineToClip (hWnd, pv, pv->nHitLine);
          break;

      case IDM_EDITPASTE:
          PasteLineFromClip (hWnd, pv, pv->nHitLine);
          break;
      }

   return lRet;
   }

/*+
 *  ViewWndProc
 *
 *-=================================================================*/

LONG CALLBACK ViewWndProc (
   HWND   hWnd,
   UINT   wMsgID,
   WPARAM wParam,
   LPARAM lParam)
   {
   LONG       lRet = 0l;               // return value from this routine
   PVIEWSTATE pv;

   pv = (LPVOID) GetWindowLong (hWnd, GWL_USERDATA);

   if (wMsgID >= WM_USER && wMsgID < 0x8000)
      lRet = ViewPrivate (hWnd, wMsgID, wParam, lParam);
   else
   switch (wMsgID)
      {
      case WM_NCHITTEST:
         lRet = DefProc (hWnd, wMsgID, wParam, lParam);
         if (lRet == HTCLIENT)
            {
            POINT pt = {MAKEPOINTS(lParam).x, MAKEPOINTS(lParam).y};

            ScreenToClient (hWnd, &pt);

            pv->wHit = HTEDGE;
            if (pt.x <= (int)pv->wLabelWidth -4)
               pv->wHit = HTLABEL;
            else if (pt.x >= (int)pv->wLabelWidth +4)
               pv->wHit = HTDATA;
            }
         break;

     #if 0
      case WM_SETCURSOR:
         if (LOWORD (lParam) == HTCLIENT &&
             pv->wHit == HTEDGE &&
             pv->hCurEdge != NULL)
            SetCursor (pv->hCurEdge);
         else
            lRet = DefProc (hWnd, wMsgID, wParam, lParam);
         break;
     #endif

      case WM_LBUTTONDBLCLK:
         {
         POINT pt = {MAKEPOINTS(lParam).x, MAKEPOINTS(lParam).y};
         PDSFIELDTBL  pTable = pv->vi.pTable;
         PDSLINEINFO  pLineInfo = pv->pLineInfo;
         UINT         nLine = (pt.y + pv->ptVisible.y) / pv->cyLine;

         lRet = DefProc (hWnd, wMsgID, wParam, lParam);

         if (nLine < pLineInfo->nCurLine)
             {
             struct _dsline * pLine = &pLineInfo->aLine[nLine];
             PDSFIELD pField = pTable[pLine->uStruct].pFields + pLine->uField;

             if ((pField->fmt & IS_EDIT) && pv->hMenu)
                {
                pv->nHitLine = nLine;
                SetCapture (hWnd);
                }
            }
         break;
         }

      case WM_LBUTTONUP:
         {
         if (GetCapture() == hWnd)
            {
            POINT pt = {MAKEPOINTS(lParam).x, MAKEPOINTS(lParam).y};
            PDSFIELDTBL  pTable = pv->vi.pTable;
            PDSLINEINFO  pLineInfo = pv->pLineInfo;
            UINT         nLine = (pt.y + pv->ptVisible.y) / pv->cyLine;

            ReleaseCapture ();

            if (nLine == pv->nHitLine)
               PostMessage (hWnd, WM_COMMAND, IDM_OBJEDIT, 0);
            }
         lRet = DefProc (hWnd, wMsgID, wParam, lParam);
         break;
         }

      case WM_LBUTTONDOWN:
      case WM_RBUTTONDOWN:
         SetFocus (hWnd);
         lRet = DefProc (hWnd, wMsgID, wParam, lParam);
         break;

      case WM_RBUTTONUP:
         {
         POINT pt = {MAKEPOINTS(lParam).x, MAKEPOINTS(lParam).y};
         PDSFIELDTBL  pTable = pv->vi.pTable;
         PDSLINEINFO  pLineInfo = pv->pLineInfo;
         UINT         nLine = (pt.y + pv->ptVisible.y) / pv->cyLine;


         lRet = DefProc (hWnd, wMsgID, wParam, lParam);

         if (nLine < pLineInfo->nCurLine)
             {
             struct _dsline * pLine = &pLineInfo->aLine[nLine];
             PDSFIELD pField = pTable[pLine->uStruct].pFields + pLine->uField;

             //if (pv->wHit == HTLABEL)
             //   {
             //   }

             if ((pField->fmt & IS_EDIT) && pv->hMenu)
                {
                pv->nHitLine = nLine;
                ClientToScreen (hWnd, &pt);
                TrackPopupMenu (pv->hMenu,
                               #if (WINVER >= 0x400)
                                TPM_TOPALIGN |
                               #endif
                                TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                                pt.x, pt.y,
                                0,
                                hWnd,
                                NULL);
                }
            }
         break;

         }

      case WM_COMMAND:
         lRet = ViewCommands (hWnd, wParam, lParam);
         break;

      case WM_SIZE:
         lRet = DefProc (hWnd, wMsgID, wParam, lParam);
         UpdateScrollRanges (pv, hWnd);
         break;

      case WM_KEYDOWN:
         {
         int  nNewPos = -1;

         switch (LOWORD(wParam))
            {
            case VK_UP:
               nNewPos = pv->ptVisible.y - pv->cyLine;
               break;

            case VK_DOWN:
               nNewPos = pv->ptVisible.y + pv->cyLine;
               break;

            case VK_PRIOR:
               nNewPos = pv->ptVisible.y - (pv->cyWnd - pv->cyLine);
               break;

            case VK_NEXT:
               nNewPos = pv->ptVisible.y + (pv->cyWnd - pv->cyLine);
               break;
            }

         if (nNewPos != -1)
            {
            nNewPos = min (nNewPos, pv->sScroll.cy);
            nNewPos = max (nNewPos, 0);
            ScrollWindow (hWnd, 0, pv->ptVisible.y - nNewPos, NULL, NULL);
            pv->ptVisible.y = nNewPos;
            SetScrollPos (hWnd, SB_VERT, pv->ptVisible.y, TRUE);
            }
         break;
         }

     case WM_VSCROLL:
         {
         int  nPos;
         int  nNewPos = -1;
         WORD wScrollCode;

         wScrollCode = LOWORD (wParam);
         nPos        = (int)HIWORD (wParam);
      
         switch (wScrollCode)
            {
            case SB_LINEUP:
               nNewPos = pv->ptVisible.y - pv->cyLine;
               break;

            case SB_LINEDOWN:
               nNewPos = pv->ptVisible.y + pv->cyLine;
               break;

            case SB_PAGEUP:
               nNewPos = pv->ptVisible.y - (pv->cyWnd - pv->cyLine);
               break;

            case SB_PAGEDOWN:
               nNewPos = pv->ptVisible.y + (pv->cyWnd - pv->cyLine);
               break;

            case SB_THUMBPOSITION:
               nNewPos = nPos - (nPos % pv->cyLine);
               break;
            }


         if (nNewPos != -1)
            {
            nNewPos = min (nNewPos, pv->sScroll.cy);
            nNewPos = max (nNewPos, 0);
            ScrollWindow (hWnd, 0, pv->ptVisible.y - nNewPos, NULL, NULL);
            pv->ptVisible.y = nNewPos;
            SetScrollPos (hWnd, SB_VERT, pv->ptVisible.y, TRUE);
            }
         break;
         }

      case WM_ERASEBKGND:
         {
         RECT rc;
         lRet = DefWindowProc (hWnd, wMsgID, wParam, lParam);

         GetClientRect (hWnd, &rc);
         //rc.left = pv->wLabelWidth + 3;
         //TrideeWellShadow ( (HDC)wParam, &rc);

         SetTextColor ( (HDC)wParam, RGB (0,0,128));
         //SetBkColor ( (HDC)wParam, GetSysColor (COLOR_BTNFACE));

         //rc.left = 0;
         rc.right = pv->wLabelWidth;
         //TrideeWellShadow ( (HDC)wParam, &rc);
         if (pv->hFontLabel)
            SelectObject ((HDC)wParam, pv->hFontLabel);

         DrawDsLabels ((HDC)wParam,
                       pv->vi.pTable,
                       pv->pLineInfo,
                       &rc,
                       pv->ptVisible);
         break;
         }

      case WM_PAINT:
         {
         PAINTSTRUCT ps;           // structure for BeginPaint
         HDC         hDC;          // DC to draw info into
         RECT        rcClip;       // clip rect for drawing

         // and draw the info into our client area
         //
         hDC = BeginPaint (hWnd, &ps);
         GetClientRect (hWnd, &rcClip);
         rcClip.left += pv->wLabelWidth + 5;

         if (pv->hFontData)
            SelectObject (hDC, pv->hFontData);
         SetTextColor (hDC, GetSysColor (COLOR_WINDOWTEXT));
         SetBkColor (hDC, GetSysColor (COLOR_WINDOW));

         DrawDsData (hDC,
                     pv->vi.pTable,
                     pv->pLineInfo,
                     &rcClip,
                     pv->ptVisible);

         EndPaint (hWnd, &ps);
         break;
         }

      case WM_CREATE:
         {
         HDC               hDC;
         char              sz[120];
         LPCREATESTRUCT    lpCreate = (LPCREATESTRUCT)lParam;
         POINT             pt = {0,0};

         pv = LocalAlloc (LPTR, sizeof(VIEWSTATE));
         if (!pv)
            return -1;
         SetWindowLong (hWnd, GWL_USERDATA, (LONG)pv);

         // init local state information
         //
         pv->pLineInfo = AllocDsLineInfo (1000);
         //pv->hBrFace = TrideeCreate (hWnd);
          //CreateFontIndirect (&lfMain);
         pv->hFontLabel = GetStockObject (DEFAULT_GUI_FONT);
         pv->hFontData  = GetStockObject (ANSI_FIXED_FONT);

         pv->hMenu = CreatePopupMenu ();
         //AppendMenuItem (pv->hMenu, &mii);
         AppendMenu (pv->hMenu, MF_STRING, IDM_OBJEDIT, "&Edit...");
         AppendMenu (pv->hMenu, MF_STRING, IDM_EDITCOPY, "&Copy");
         AppendMenu (pv->hMenu, MF_STRING, IDM_EDITPASTE, "&Paste");

         // get init stuff from last parameter (if possible)
         //
        #ifdef USE_MDI
         {
         LPMDICREATESTRUCT lpMcs;
         lpMcs = (LPMDICREATESTRUCT) (lpCreate->lpCreateParams);
         lpMcs->x = lpMcs->y = CW_USEDEFAULT;
         lpMcs->cx = lpMcs->cy = CW_USEDEFAULT;
         if (lpMcs->lParam)
            pv->vi = *(PVIEWINIT)lpMcs->lParam;
         }
        #else
         if (lpCreate->lpCreateParams)
            pv->vi = *(PVIEWINIT)(lpCreate->lpCreateParams);
        #endif

         hDC = GetDC (hWnd);
         if (pv->hFontLabel)
            SelectObject (hDC, pv->hFontLabel);

         GetViewExtent (hDC,
                        &pv->vi,
                        pv->pLineInfo,
                        &pv->sLabel,
                        &pv->sTotal);

         pv->cyLine = pv->pLineInfo->cyLine;
         pv->wLabelWidth = pv->sLabel.cx + 16;
         ReleaseDC (hWnd, hDC);

         pv->hCurEdge = LoadCursor (lpCreate->hInstance,
                                    MAKEINTRESOURCE (IDC_EDGE));

         wsprintf (sz, "%s:%08lxx",
                   pv->vi.pTable[pv->vi.uStruct].pszName,
                   pv->vi.lpData);

         SetWindowText (hWnd, sz);
         
         break;
         }

      case WM_DESTROY:
         {
         //TrideeDestroy (hWnd);

         // delete font if not using stock object
         //DeleteObject (pv->hFontLabel);

         break;            // return FALSE;
         }

      default:
         lRet = DefProc (hWnd, wMsgID, wParam, lParam);
      }

   return lRet;
   }


/*+ DrawDragEdge
 *
 *
 *-=================================================================*/

VOID WINAPI DrawDragEdge (HWND hWnd, LPPOINT lppt, LPPOINT lpptLastEdge)
   {
   HDC  hDC;
   RECT rc;

   hDC = GetDC (hWnd);

   GetClientRect (hWnd, &rc);

   if (lpptLastEdge)
      PatBlt (hDC, lpptLastEdge->x, rc.top, 3, rc.bottom - rc.top, PATINVERT);

   if (lppt)
      {
      PatBlt (hDC, lppt->x, rc.top, 3, rc.bottom - rc.top, PATINVERT);
      if (lpptLastEdge)
         *lpptLastEdge = *lppt;
      }

   ReleaseDC (hWnd, hDC);
   }
