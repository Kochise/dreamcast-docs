//**  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//**  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//**  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
//**  A PARTICULAR PURPOSE.
//**
//**  Copyright (C) 1993 - 1997 Microsoft Corporation. All Rights Reserved.
//**
//**  head.c
//**
//**  DESCRIPTION:
//**     Window proc for IDF head pane
//**
//************************************************************************

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <commctrl.h>

#include "idfedit.h"
#include "tridee.h"

/*+
 *
 *-=================================================================*/

STATICFN void LoadTree (
   HWND      hWndT,
   struct _instrum_info * piSelect,
   LPIDFHEAD pih)
{
   HTREEITEM htiSelect = NULL;
   HTREEITEM htiParent = TVI_ROOT;
   struct _instrum_info * pi;
   UINT  ii;

   TreeView_DeleteAllItems(hWndT);

   for (pi = &pih->ai[ii = 0]; ii < pih->nInstrum; ++ii, ++pi)
      {
      TV_INSERTSTRUCT ti;
      HTREEITEM       hti;

      ZeroMemory (&ti, sizeof(ti));

      ti.hParent        = TVI_ROOT;
      ti.hInsertAfter   = TVI_SORT;
      ti.item.mask      = TVIF_TEXT | TVIF_STATE | TVIF_PARAM;
      ti.item.state     = TVIS_EXPANDED;
      ti.item.stateMask = 0xFF;
      ti.item.lParam    = (LPARAM)pi;

      if (pi->pInstrum)
         ti.item.pszText = pi->pInstrum->szInstID;
      else if (pi->pList)
         {
         LPRIFF pRiff = FindListChunk(pi->pList, FCC_hdr);
         if (pRiff && pRiff->cb >= sizeof(IDFHEADER))
            ti.item.pszText = ((LPIDFHEADER)(pRiff+1))->abInstID;
         }                                                             
         

      assert (ti.item.pszText);
      if ( ! ti.item.pszText)
         continue;

      hti = TreeView_InsertItem (hWndT, &ti);

      if (piSelect && (piSelect == pi))
         htiSelect = hti;
      }

   if (htiSelect)
      {
      assert (piSelect);
      TreeView_SelectItem (hWndT, htiSelect);
      }
}

/*+
 *  HeadPrivate
 *
 *-=================================================================*/

static LONG WINAPI HeadPrivate (
   HWND   hWnd,
   UINT   wMsgID,
   WPARAM wParam,
   LPARAM lParam)
   {
   LONG       lRet = 0l;               // return value from this routine
   LPIDFHEAD  pih;

   pih = (LPVOID) GetWindowLong (hWnd, GWL_USERDATA);

   switch (wMsgID)
      {
      case HM_REFRESH_TREE:
         LoadTree(pih->hWndTree, pih->piSelect, pih);
         InvalidateRect (hWnd, NULL, FALSE);
         break;
      }

   return lRet;
   }

/*+
 *  HeadCommands
 *
 *-=================================================================*/

LONG WINAPI HeadCommands (
   HWND   hWnd,
   WPARAM wParam,
   LPARAM lParam)
   {
   LONG       lRet = 0l;               // return value from this routine
   LPIDFHEAD  pih;

   pih = (LPVOID) GetWindowLong (hWnd, GWL_USERDATA);

   switch (GET_WM_COMMAND_ID(wParam,lParam))
      {
      }

   return lRet;
   }

/*+
 *  
 *
 *-=================================================================*/

STATICFN BOOL WINAPI HandleInstrumentsSelChange (
    HWND      hWnd,
    LPNMHDR   lpnm,
    LPIDFHEAD pih)
{
   LPNM_TREEVIEW pntv = (LPVOID)lpnm;
   LPTV_ITEM     pti  = &pntv->itemNew;
   //TV_ITEM       ti;
   struct _instrum_info * pi;
   //char          szSingle[MAX_ALIAS];
   //BOOL          bChange = FALSE;

   if (!pih)
      return FALSE;

   // if there was a valid previous selection.
   // make sure that there a now changes to be
   // saved off before we allow selection to proceed.
   //
   pi = (LPVOID)pntv->itemNew.lParam;
   if (pi && !pi->pInstrum &&
       (pih->piSelect == pi) && 
       (pih->pInstrumSelect == &pih->instrum) &&
       (pih->instrum.bChanged))
      {
      assert (0);
      // need to save changes made to the instrument data
      //
      pi->pInstrum = CopyForEditing (&pih->instrum, sizeof(pih->instrum));
      pih->bChanged = TRUE;
      }

   // setup ti to get text & # of children
   // from the IDF filename entry.
   //
   //ti.mask       = TVIF_PARAM;
   //ti.mask       = TVIF_TEXT | TVIF_PARAM;
   //ti.pszText    = szSingle;
   //ti.cchTextMax = NUMELMS(szSingle);
   //ti.hItem      = pti->hItem;
   //TreeView_GetItem (lpnm->hwndFrom, &ti);
   //pi = (LPVOID)ti.lParam;
   pi = (LPVOID)pti->lParam;
   if (!pi)
      return FALSE;

   // if the selected instrument has no editable data set, 
   // copy the raw RIFF data into the temp edit set
   // and display instrument settings from there.
   //
   pih->piSelect = NULL;
   pih->pInstrumSelect = NULL;
   if (pih->nInstrum)
      {
      pih->piSelect = pi;
      pih->pInstrumSelect = pi->pInstrum;
      if (!pi->pInstrum)
         {
         CopyInstrumData (&pih->instrum, pi->pList);
         pih->pInstrumSelect = &pih->instrum;
         }
      }

   View_SetData (pih->hWndInstrument, pih->pInstrumSelect);
   View_InvalidateLines (pih->hWndInstrument, 0, 0);
   return TRUE;
}

/*+
 *  HeadNotifications
 *
 *-=================================================================*/

LONG WINAPI HeadNotifications (
   HWND     hWnd,
   LPNMHDR  lpnm)
   {
   LONG       lRet = 0l;               // return value from this routine
   LPIDFHEAD  pih;

   pih = (LPVOID) GetWindowLong (hWnd, GWL_USERDATA);

   switch (lpnm->idFrom)
      {
      case IDL_INSTRUMENTS:
         switch (lpnm->code)
            {
            case TVN_SELCHANGED:
                HandleInstrumentsSelChange (hWnd, lpnm, pih);
                break;

            //case NM_DBLCLK:
            //    break;

            case TVN_ENDLABELEDIT:
                {
                TV_DISPINFO * ptv = (LPVOID)lpnm;
                struct _instrum_info * pi = (LPVOID)ptv->item.lParam;

                if (!pi)
                   break;

                if (!pi->pInstrum)
                   {
                   if (pih->piSelect == pi && pih->pInstrumSelect == &pih->instrum)
                      pi->pInstrum = CopyForEditing (&pih->instrum, sizeof(pih->instrum));
                   else
                      {
                      assert (0); // shoundn't be able to label edit without first selecting
                      pi->pInstrum = HeapAlloc (gs.idf.hEditHeap, 0, sizeof(INSTRUMENT));
                      CopyInstrumData (pi->pInstrum, pi->pList);
                      }
                   }
                  
                lstrcpyn (pi->pInstrum->szInstID, ptv->item.pszText, NUMELMS(pi->pInstrum->szInstID));
                pi->pInstrum->bChanged = TRUE;
                pih->bChanged = TRUE;
                View_InvalidateLines (pih->hWndInstrument, 0, 0);
                lRet = 1;
                }
                break;
            }
         break;

      case IDC_CURRENT_INSTRUM:
         switch (lpnm->code)
            {
            case VN_CHANGE:
               if (pih->pInstrumSelect)
                  {
                  if (pih->pInstrumSelect == &pih->instrum)
                     {
                     assert (!pih->piSelect->pInstrum);
                     if ( ! pih->piSelect->pInstrum)
                        {
                        pih->pInstrumSelect =
                        pih->piSelect->pInstrum = CopyForEditing (&pih->instrum, sizeof(pih->instrum));
                        View_SetData (pih->hWndInstrument, pih->pInstrumSelect);
                        View_InvalidateLines (pih->hWndInstrument, 0, 0);
                        }
                     }
                  pih->pInstrumSelect->bChanged = TRUE;
                  pih->bChanged = TRUE;
                  }
               else
                  {
                  assert (0);
                  }
               break;
            }
         break;
      }

   return lRet;
   }

/*+
 *  HeadWndProc
 *
 *-=================================================================*/

LONG CALLBACK HeadWndProc (
   HWND   hWnd,
   UINT   wMsgID,
   WPARAM wParam,
   LPARAM lParam)
   {
   LONG       lRet = 0l;               // return value from this routine
   if (wMsgID >= WM_USER && wMsgID < 0x8000)
      lRet = HeadPrivate (hWnd, wMsgID, wParam, lParam);
   else
   switch (wMsgID)
      {
      case WM_COMMAND:
         lRet = HeadCommands (hWnd, wParam, lParam);
         break;

      case WM_NOTIFY:
         lRet = HeadNotifications (hWnd, (LPNMHDR)lParam);
         break;

      case WM_SIZE:
         {
         LPIDFHEAD pih = (LPVOID) GetWindowLong (hWnd, GWL_USERDATA);
         HDC hDC;
         TEXTMETRIC tm;
         #define BORDER 0

         hDC = GetDC (hWnd);
         //if (pih->hFont)
         //   SelectObject (hDC, pih->hFont);
         GetTextMetrics (hDC, &tm);
         pih->ptClient.y = tm.tmHeight + tm.tmExternalLeading + 6;
         pih->ptClient.x = 0;
         ReleaseDC (hWnd, hDC);

         pih->sClient.cx = LOWORD(lParam) - pih->ptClient.x;
         pih->sClient.cy = HIWORD(lParam) - pih->ptClient.y;

         SetWindowPos (pih->hWndTree, NULL,
                       pih->ptClient.x, pih->ptClient.y,
                       pih->cxTree, pih->sClient.cy,
                       SWP_NOZORDER);

         SetWindowPos (pih->hWndInstrument, NULL,
                       pih->ptClient.x + pih->cxTree + BORDER, pih->ptClient.y,
                       pih->sClient.cx - pih->cxTree - BORDER, pih->sClient.cy,
                       SWP_NOZORDER);
         }
         break;

      case WM_CREATE:
         {
         LPCREATESTRUCT    lpCreate = (LPCREATESTRUCT)lParam;
         LPIDFHEAD         pih;

         SetWindowLong (hWnd, GWL_USERDATA, 0);

         pih = (LPVOID)lpCreate->lpCreateParams;
         if (!pih)
             return -1;
         SetWindowLong (hWnd, GWL_USERDATA, (LONG)pih);

         pih->cxTree = LOWORD(GetDialogBaseUnits()) * 20;

         pih->hWndTree = 
             CreateWindowEx (fdwExStyle | WS_EX_NOPARENTNOTIFY,
                             WC_TREEVIEW,
                             "",
                             TVS_DISABLEDRAGDROP |
                             TVS_SHOWSELALWAYS |
                             TVS_EDITLABELS |
                             WS_CHILD | WS_VISIBLE | WS_BORDER,
                             0, 0, pih->cxTree, 0,
                             hWnd,
                             (HMENU)IDL_INSTRUMENTS,
                             hInst,
                             NULL);
         if ( ! pih->hWndTree)
            lRet = -1;

         pih->hWndInstrument = 
             CreateWindowEx (fdwExStyle | WS_EX_NOPARENTNOTIFY,
                             cszInstrumClass,
                             "",
                             WS_CHILD | WS_VISIBLE | WS_BORDER,
                             pih->cxTree + 6, 0, 200, 0,
                             hWnd,
                             (HMENU)IDC_CURRENT_INSTRUM,
                             hInst,
                             &pih->vi);
         if ( ! pih->hWndInstrument)
            lRet = -1;

         LoadTree (pih->hWndTree, &pih->ai[0], pih);
         LoadString (hInst, IDS_TREE_LABEL, pih->szTreeLabel, NUMELMS(pih->szTreeLabel));
         LoadString (hInst, IDS_VIEW_LABEL, pih->szViewLabel, NUMELMS(pih->szViewLabel));

         TrideeCreate(hWnd);
         }
         break;

      case WM_DESTROY:
         {
         LPIDFHEAD pih = (LPVOID) GetWindowLong (hWnd, GWL_USERDATA);
         if (pih && pih != &gs.idf)
            HeapFree (GetProcessHeap(), 0, pih);
         SetWindowLong (hWnd, GWL_USERDATA, 0);
         TrideeDestroy(hWnd);
         }
         break;

      case WM_ERASEBKGND:
         {
         RECT rc;
         LPIDFHEAD pih = (LPVOID) GetWindowLong (hWnd, GWL_USERDATA);
         HDC  hDC = (HDC)wParam;
         int  cx = 2;
         int  cy = 4;

         lRet = DefWindowProc (hWnd, wMsgID, wParam, lParam);

         GetClientRect (hWnd, &rc);

         SetTextColor (hDC, GetSysColor (COLOR_BTNTEXT));
         SetBkColor (hDC, GetSysColor (COLOR_BTNFACE));

         SetTextAlign (hDC, TA_TOP | TA_LEFT);
         ExtTextOut (hDC, cx, cy, ETO_CLIPPED, &rc, 
                     pih->szTreeLabel, lstrlen(pih->szTreeLabel), NULL);

         cx = pih->ptClient.x + pih->cxTree + BORDER +2;
         ExtTextOut (hDC, cx, cy, ETO_CLIPPED, &rc, 
                     pih->szViewLabel, lstrlen(pih->szViewLabel), NULL);

         rc.bottom = rc.top + 2;
         TrideeWellShadow(hDC, &rc);
         }
         break;

      case WM_PAINT:
         {
         PAINTSTRUCT ps;           // structure for BeginPaint
         HDC         hDC;          // DC to draw info into

         LPIDFHEAD pih = (LPVOID) GetWindowLong (hWnd, GWL_USERDATA);

         // and draw the info into our client area
         //
         hDC = BeginPaint (hWnd, &ps);
         EndPaint (hWnd, &ps);
         }
         break;

      default:
         lRet = DefWindowProc (hWnd, wMsgID, wParam, lParam);
      }

   return lRet;
   }
