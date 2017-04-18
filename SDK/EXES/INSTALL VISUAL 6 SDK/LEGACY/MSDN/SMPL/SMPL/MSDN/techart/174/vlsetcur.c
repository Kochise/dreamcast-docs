#include "vlistint.h"

LONG vlbSetCurSel( PVLBOX pVLBox, int nOption, LONG lParam)
{
   int i;
   if ( pVLBox->wFlags & USEDATAVALUES ) {
       switch ( nOption) {

          case VLB_FIRST:
              VLBFirstPage(pVLBox);
              SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
              SetSelectedItem(pVLBox);
          break;

          case VLB_PREV:
             if ( (i=vlbFindData(pVLBox, lParam)) == LB_ERR ) {
                if  ( VLBFindPage(pVLBox, (LONG)lParam, TRUE) ) {
                    return VLB_ERR;
                }
                if ( pVLBox->nCountInBox < pVLBox->nLines ) {
                   VLBLastPage(pVLBox);
                }
                else {
                    InvalidateRect(pVLBox->hwndList, NULL, TRUE);
                    UpdateWindow(pVLBox->hwndList);
                }
             }
             i=vlbFindData(pVLBox, lParam);
             if ( i == 0 ) {
                if ( VLBScrollUpLine(pVLBox) )
                    return VLB_ERR;
                else
                    SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
                    SetSelectedItem(pVLBox);
             }
             else {
                SendMessage(pVLBox->hwndList, LB_SETCURSEL, i-1, 0L);
                SetSelectedItem(pVLBox);
             }
          break;

          case VLB_NEXT:
             if ( (i=vlbFindData(pVLBox, lParam)) == LB_ERR ) {
                if  ( VLBFindPage(pVLBox, (LONG)lParam, TRUE) ) {
                    return VLB_ERR;
                }
                UpdateWindow(pVLBox->hwndList);
                i=vlbFindData(pVLBox, lParam);
             }
             if ( i == (pVLBox->nCountInBox-1) ) {
                if ( VLBScrollDownLine(pVLBox) )
                    return VLB_ERR;
                else
                    SendMessage(pVLBox->hwndList, LB_SETCURSEL, pVLBox->nCountInBox-1, 0L);
                    SetSelectedItem(pVLBox);
             }
             else {
                if ( SendMessage(pVLBox->hwndList, LB_SETCURSEL, i+1, 0L) == -1L )
                    return VLB_ERR;
                SetSelectedItem(pVLBox);
             }
          break;

          case VLB_LAST:
              VLBLastPage(pVLBox);
              SendMessage(pVLBox->hwndList, LB_SETCURSEL, pVLBox->nCountInBox-1, 0L);
              SetSelectedItem(pVLBox);
          break;

          case VLB_FINDITEM:
             if ( (i=vlbFindData(pVLBox, lParam)) == LB_ERR ) {
                vlbRedrawOff(pVLBox);
                if  ( VLBFindPage(pVLBox, (LONG)lParam, TRUE) )
                    return VLB_ERR;
                else {
                    if ( pVLBox->nCountInBox < pVLBox->nLines ) {
                       VLBLastPage(pVLBox);
                    }
                    i=vlbFindData(pVLBox, lParam);
                    SendMessage(pVLBox->hwndList, LB_SETCURSEL, i, 0L);
                    pVLBox->lSelItem = (LONG) lParam;
                }
                vlbRedrawOn(pVLBox);
             }
             else {
                SendMessage(pVLBox->hwndList, LB_SETCURSEL, i, 0L);
                SetSelectedItem(pVLBox);
             }
          break;
       }
   }
   else {
       pVLBox->vlbStruct.lIndex = lParam;
       switch ( nOption) {
          case VLB_FIRST:
              VLBFirstPage(pVLBox);
              SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
              SetSelectedItem(pVLBox);
          break;

          case VLB_LAST:
              VLBLastPage(pVLBox);
              SendMessage(pVLBox->hwndList, LB_SETCURSEL, pVLBox->nCountInBox-1, 0L);
              SetSelectedItem(pVLBox);
          break;

          case VLB_PREV:
             if ( pVLBox->vlbStruct.lIndex > pVLBox->lToplIndex &&
                  pVLBox->vlbStruct.lIndex <= (pVLBox->lToplIndex+(LONG)(pVLBox->nCountInBox)-1)) {
                if ( SendMessage(pVLBox->hwndList, LB_SETCURSEL, (int)(pVLBox->vlbStruct.lIndex-pVLBox->lToplIndex)-1, 0L) == -1L)
                    return VLB_ERR;
                else
                    SetSelectedItem(pVLBox);
             }
             else {
                if ( VLBScrollUpLine(pVLBox) )
                    return VLB_ERR;
                else {
                    SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
                    SetSelectedItem(pVLBox);
                }
             }
          break;

          case VLB_NEXT:
             if ( pVLBox->vlbStruct.lIndex >= pVLBox->lToplIndex &&
                  pVLBox->vlbStruct.lIndex < (pVLBox->lToplIndex+(LONG)(pVLBox->nCountInBox)-1)) {
                if ( SendMessage(pVLBox->hwndList, LB_SETCURSEL, (int)(pVLBox->vlbStruct.lIndex-pVLBox->lToplIndex)+1, 0L) == -1L )
                    return VLB_ERR;
                else
                    SetSelectedItem(pVLBox);
             }
             else {
                if ( VLBScrollDownLine(pVLBox) )
                    return VLB_ERR;
                else {
                    SendMessage(pVLBox->hwndList, LB_SETCURSEL, pVLBox->nLines-1, 0L);
                    SetSelectedItem(pVLBox);
                }
             }
          break;

          case VLB_FINDITEM:
             if ( pVLBox->vlbStruct.lIndex >= pVLBox->lToplIndex &&
                  pVLBox->vlbStruct.lIndex <= (pVLBox->lToplIndex+(LONG)(pVLBox->nCountInBox)-1)) {
                SendMessage(pVLBox->hwndList, LB_SETCURSEL, (int)(pVLBox->vlbStruct.lIndex-pVLBox->lToplIndex), lParam);
                SetSelectedItem(pVLBox);
             }
             else {
                if ( VLBFindPage(pVLBox, pVLBox->vlbStruct.lIndex, TRUE) )
                    return VLB_ERR;
                else {
                    SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
                    SetSelectedItem(pVLBox);
                }
             }
          break;
       }
   }
   return (LONG)VLB_OK;
}
