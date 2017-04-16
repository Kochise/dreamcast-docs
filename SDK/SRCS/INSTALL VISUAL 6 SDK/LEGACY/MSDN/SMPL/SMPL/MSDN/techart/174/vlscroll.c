#include "vlistint.h"

#include <string.h>

static void SetFocustoLB(PVLBOX pVLBox);
static void SetFocustoVLB(PVLBOX pVLBox);

int VLBScrollDownLine( PVLBOX pVLBox)
{
    RECT   UpdRect;
    int    nSelected;
    LONG   lFreeItem;

    if ( pVLBox->wFlags & USEDATAVALUES ) {
        pVLBox->vlbStruct.lIndex = -1L;
        lFreeItem = SendMessage(pVLBox->hwndList, LB_GETITEMDATA, 0, 0L);
    }
    else {
        pVLBox->vlbStruct.lIndex = pVLBox->lToplIndex + pVLBox->nLines - 1L;
        lFreeItem = pVLBox->lToplIndex;
    }

    pVLBox->vlbStruct.lpTextPointer = NULL;
    pVLBox->vlbStruct.lData = SendMessage(pVLBox->hwndList, LB_GETITEMDATA, pVLBox->nCountInBox-1, 0L);
    pVLBox->vlbStruct.nCtlID = pVLBox->nId;
    SendMessage(pVLBox->hwndParent, VLB_NEXT, 0, (LPARAM)((LPVLBSTRUCT)&(pVLBox->vlbStruct)));
    if ( pVLBox->vlbStruct.nStatus == VLB_OK ) {
       nSelected = (int)SendMessage(pVLBox->hwndList, LB_GETCURSEL, 0, 0L);
       if ( nSelected == 0 ) {
           SendMessage(pVLBox->hwndList, LB_SETCURSEL, (WPARAM)-1, (LPARAM)0L);
           SetFocustoVLB(pVLBox);
       }

       //
       // Remove the top String
       //
       SendMessage(pVLBox->hwndList, LB_DELETESTRING, 0, 0L);
       SendMessage(pVLBox->hwndParent, VLBN_FREEITEM, pVLBox->nId, lFreeItem);

       //
       // Add the new line
       //
       if ( pVLBox->wFlags & HASSTRINGS) {
           SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lpTextPointer);
           SendMessage(pVLBox->hwndList, LB_SETITEMDATA, pVLBox->nCountInBox-1, pVLBox->vlbStruct.lData);
       }
       else
           SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lData);



       pVLBox->lToplIndex++;
       UpdateVLBWindow(pVLBox, &UpdRect);

       //
       // Tell Windows not to paint the whole LB
       //
       ValidateRect(pVLBox->hwndList, NULL);

       //
       // Scroll the window up
       //
       ScrollWindow(pVLBox->hwndList, 0, (-1)*pVLBox->nchHeight, NULL, NULL);

       //
       // Now tell windows the bottom line needs fixing
       //
       SendMessage(pVLBox->hwndList, LB_GETITEMRECT,
                   pVLBox->nLines-1, (LPARAM) (LPRECT) &UpdRect);

       InvalidateRect(pVLBox->hwndList, &UpdRect, TRUE);

       UpdateWindow(pVLBox->hwndList);

       if ( TestSelectedItem(pVLBox, pVLBox->vlbStruct) ) {
          SendMessage(pVLBox->hwndList, LB_SETCURSEL, pVLBox->nLines-1, 0L);
          SetFocustoLB(pVLBox);
       }
       else if ( nSelected != LB_ERR ) {
          if ( nSelected != 0 ) {
              // Need to move the selection Up 1
              SendMessage(pVLBox->hwndList, LB_SETCURSEL, nSelected-1, 0L);
          }
       }


       return VLB_OK;
    }
    return VLB_ERR;
}

int VLBScrollUpLine( PVLBOX pVLBox)
{
    RECT   UpdRect;
    RECT   ListRect;
    RECT   FAR *lpRect;
    int    nSelected;
    LONG   lFreeItem;

    if ( pVLBox->wFlags & USEDATAVALUES ) {
        pVLBox->vlbStruct.lIndex = -1L;
        lFreeItem = SendMessage(pVLBox->hwndList, LB_GETITEMDATA, pVLBox->nCountInBox-1, 0L);
    }
    else {
        pVLBox->vlbStruct.lIndex = pVLBox->lToplIndex;
        lFreeItem = pVLBox->lToplIndex + pVLBox->nLines - 1L;
    }

    pVLBox->vlbStruct.lpTextPointer = NULL;
    pVLBox->vlbStruct.lData = SendMessage(pVLBox->hwndList, LB_GETITEMDATA, 0, 0L);
    pVLBox->vlbStruct.nCtlID = pVLBox->nId;
    SendMessage(pVLBox->hwndParent, VLB_PREV, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
    if ( pVLBox->vlbStruct.nStatus  == VLB_OK ) {
       nSelected = (int)SendMessage(pVLBox->hwndList, LB_GETCURSEL, 0, 0L);
       if ( nSelected == pVLBox->nLines-1 ) {
          SendMessage(pVLBox->hwndList, LB_SETCURSEL, (WPARAM)-1, (LPARAM)0L);
          SetFocustoVLB(pVLBox);
       }

       //
       // Remove the bottom String
       //
       SendMessage(pVLBox->hwndList, LB_DELETESTRING, pVLBox->nLines-1, 0L);
       SendMessage(pVLBox->hwndParent, VLBN_FREEITEM, pVLBox->nId, lFreeItem);

       //
       // Add the new line
       //
       if ( pVLBox->wFlags & HASSTRINGS) {
           SendMessage(pVLBox->hwndList, LB_INSERTSTRING, 0, (LPARAM) pVLBox->vlbStruct.lpTextPointer);
           SendMessage(pVLBox->hwndList, LB_SETITEMDATA, 0, pVLBox->vlbStruct.lData);
       }
       else
           SendMessage(pVLBox->hwndList, LB_INSERTSTRING, 0, (LPARAM) pVLBox->vlbStruct.lData);

       pVLBox->lToplIndex--;
       UpdateVLBWindow(pVLBox, &UpdRect);

       //
       // Tell Windows not to paint the whole LB
       //
       ValidateRect(pVLBox->hwndList, NULL);

       //
       // Check for partial line at bottom...
       // if so clear it
       //
       SendMessage(pVLBox->hwndList, LB_GETITEMRECT,
                   pVLBox->nLines-1, (LPARAM)(LPRECT)&UpdRect);

       GetClientRect(pVLBox->hwndList, &ListRect);
       if ( pVLBox->bHScrollBar || (UpdRect.bottom != ListRect.bottom) ) {
           ListRect.bottom = UpdRect.top ;
           lpRect = &ListRect;
       }
       else {
           lpRect = NULL;
       }

       //
       // Scroll the window down
       //
       ScrollWindow(pVLBox->hwndList, 0, pVLBox->nchHeight, lpRect, NULL);

       //
       // Now tell windows the top line needs fixing
       //
       SendMessage(pVLBox->hwndList, LB_GETITEMRECT,
                   0, (LPARAM)(LPRECT)&UpdRect);
       InvalidateRect(pVLBox->hwndList, &UpdRect, TRUE);
       UpdateWindow(pVLBox->hwndList);

       if ( TestSelectedItem(pVLBox, pVLBox->vlbStruct) ) {
          SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
          SetFocustoLB(pVLBox);
       }
       else if ( nSelected != LB_ERR ) {
          if ( nSelected !=  pVLBox->nLines-1) {
              // Need to move the selection Up 1
              SendMessage(pVLBox->hwndList, LB_SETCURSEL, nSelected+1, 0L);
          }
       }


       return VLB_OK;
    }
    return VLB_ERR;
}


int VLBScrollDownPage( PVLBOX pVLBox, int nAdjustment)
{
    int  nCount;
    int  nSelected;
    LONG lFreeItem;

    nSelected = (int)SendMessage(pVLBox->hwndList, LB_GETCURSEL, 0, 0L);
    if ( nSelected == LB_ERR )
        nSelected = -10000;

    SendMessage(pVLBox->hwndList, LB_SETCURSEL, (WPARAM)-1, (LPARAM)0L);
	SetFocustoVLB(pVLBox);

    for ( nCount = 0; nCount < pVLBox->nLines+nAdjustment; nCount++) {
        if ( pVLBox->wFlags & USEDATAVALUES )
            pVLBox->vlbStruct.lIndex = -1L;
        else
            pVLBox->vlbStruct.lIndex = pVLBox->lToplIndex + pVLBox->nLines - 1L;

        pVLBox->vlbStruct.lpTextPointer = NULL;
        pVLBox->vlbStruct.lData = SendMessage(pVLBox->hwndList, LB_GETITEMDATA, pVLBox->nCountInBox-1, 0L);
        pVLBox->vlbStruct.nCtlID = pVLBox->nId;
        SendMessage(pVLBox->hwndParent, VLB_NEXT, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
        if (  pVLBox->vlbStruct.nStatus == VLB_OK ) {

           if ( nCount == 0 )
              vlbRedrawOff(pVLBox);

           if ( pVLBox->wFlags & USEDATAVALUES ) {
               lFreeItem = SendMessage(pVLBox->hwndList, LB_GETITEMDATA, 0, 0L);
           }
           else {
               lFreeItem = pVLBox->lToplIndex;
           }
           SendMessage(pVLBox->hwndList, LB_DELETESTRING, 0, 0L);
           SendMessage(pVLBox->hwndParent, VLBN_FREEITEM, pVLBox->nId, lFreeItem);

           if ( pVLBox->wFlags & HASSTRINGS) {
               SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lpTextPointer);
               SendMessage(pVLBox->hwndList, LB_SETITEMDATA, pVLBox->nCountInBox-1, pVLBox->vlbStruct.lData);
           }
           else
               SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lData);

           if ( TestSelectedItem(pVLBox, pVLBox->vlbStruct) ) {
              nSelected = pVLBox->nLines-1;
           }
           else {
              nSelected--;
           }

           pVLBox->lToplIndex++;

        }
        else {
            if ( nCount == 0 )
            break;
        }
    }

    if ( nSelected >= 0 ) {
       SendMessage(pVLBox->hwndList, LB_SETCURSEL, nSelected, 0L);
       SetFocustoLB(pVLBox);
    }
    else {
       SetFocustoVLB(pVLBox);
       SendMessage(pVLBox->hwndList, LB_SETCURSEL, (WPARAM)-1, (LPARAM)0L);
    }

	if ( nCount == 0 )
		return VLB_ERR;

    UpdateVLBWindow(pVLBox, NULL);
    vlbRedrawOn(pVLBox);
    return VLB_OK;

}


int VLBScrollUpPage( PVLBOX pVLBox, int nAdjustment)
{
    int  nCount;
    int  nSelected;
    LONG lFreeItem;

    nSelected = (int)SendMessage(pVLBox->hwndList, LB_GETCURSEL, 0, 0L);
    if ( nSelected == LB_ERR )
        nSelected = -10000;

    SetFocustoVLB(pVLBox);
    SendMessage(pVLBox->hwndList, LB_SETCURSEL, (WPARAM)-1, (LPARAM)0L);

    for ( nCount = 0; nCount < pVLBox->nLines+nAdjustment; nCount++) {
        if ( pVLBox->wFlags & USEDATAVALUES ) {
            pVLBox->vlbStruct.lIndex = -1L;
        }
        else {
            pVLBox->vlbStruct.lIndex = pVLBox->lToplIndex;
        }

        pVLBox->vlbStruct.lpTextPointer = NULL;
        pVLBox->vlbStruct.lData = SendMessage(pVLBox->hwndList, LB_GETITEMDATA, 0, 0L);
        pVLBox->vlbStruct.nCtlID = pVLBox->nId;
        SendMessage(pVLBox->hwndParent, VLB_PREV, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
        if ( pVLBox->vlbStruct.nStatus  == VLB_OK ) {
           if ( nCount == 0 )
              vlbRedrawOff(pVLBox);

           if ( pVLBox->wFlags & HASSTRINGS) {
               SendMessage(pVLBox->hwndList, LB_INSERTSTRING, 0, (LPARAM) pVLBox->vlbStruct.lpTextPointer);
               SendMessage(pVLBox->hwndList, LB_SETITEMDATA, 0, pVLBox->vlbStruct.lData);
           }
           else
               SendMessage(pVLBox->hwndList, LB_INSERTSTRING, 0, (LPARAM) pVLBox->vlbStruct.lData);

           if ( TestSelectedItem(pVLBox, pVLBox->vlbStruct) ) {
              nSelected = 0;
           }
           else {
              nSelected++;
           }

           if ( pVLBox->wFlags & USEDATAVALUES ) {
               lFreeItem = SendMessage(pVLBox->hwndList, LB_GETITEMDATA, pVLBox->nLines, 0L);
           }
           else {
               lFreeItem = pVLBox->lToplIndex + pVLBox->nLines - 1L;
           }
           SendMessage(pVLBox->hwndList, LB_DELETESTRING, pVLBox->nLines, 0L);
           SendMessage(pVLBox->hwndParent, VLBN_FREEITEM, pVLBox->nId, lFreeItem);

           pVLBox->lToplIndex--;
        }
        else  {
            if ( nCount == 0 )
           break;
        }
    }

    if ( nSelected >= 0 && nSelected <= pVLBox->nLines ) {
       SendMessage(pVLBox->hwndList, LB_SETCURSEL, nSelected, 0L);
       SetFocustoLB(pVLBox);
    }
    else {
       SetFocustoVLB(pVLBox);
       SendMessage(pVLBox->hwndList, LB_SETCURSEL, (WPARAM)-1, (LPARAM)0L);
    }

	if ( nCount == 0 )
		return VLB_ERR;

	UpdateVLBWindow(pVLBox, NULL);
    vlbRedrawOn(pVLBox);
    return VLB_OK;
}


void UpdateVLBWindow( PVLBOX pVLBox, LPRECT lpRect)
{
    int   nPos;

    if ( pVLBox->lNumLogicalRecs == -1L )
       SetScrollPos(pVLBox->hwndList, SB_VERT, 50, TRUE);
    else {
       if ( pVLBox->lNumLogicalRecs <= pVLBox->nLines ) {
          if ( pVLBox->styleSave & VLBS_DISABLENOSCROLL )
             EnableScrollBar(pVLBox->hwndList, SB_VERT, ESB_DISABLE_BOTH);
          else
             ShowScrollBar(pVLBox->hwndList, SB_VERT, FALSE);
       }
       else {
           if ( pVLBox->styleSave & VLBS_DISABLENOSCROLL )
              EnableScrollBar(pVLBox->hwndList, SB_VERT, ESB_ENABLE_BOTH);
           else
              ShowScrollBar(pVLBox->hwndList, SB_VERT, TRUE);
           if ( pVLBox->lToplIndex >= (pVLBox->lNumLogicalRecs-pVLBox->nLines) ) {
               nPos = 100;
           }
           else if (pVLBox->lToplIndex == 0L) {
               nPos = 0;
           }
           else {
               nPos = (int) ((pVLBox->lToplIndex*100L) / (pVLBox->lNumLogicalRecs-pVLBox->nLines+1));
           }
           SetScrollPos(pVLBox->hwndList, SB_VERT, nPos, TRUE);
       }

    }

}



int VLBFindPos( PVLBOX pVLBox, int nPos)
{
    pVLBox->vlbStruct.lpTextPointer = NULL;
    pVLBox->vlbStruct.lIndex = (LONG) nPos;
    pVLBox->vlbStruct.lData = (LONG) nPos;
    pVLBox->vlbStruct.nCtlID = pVLBox->nId;
    SendMessage(pVLBox->hwndParent, VLB_FINDPOS, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
    if ( pVLBox->vlbStruct.nStatus  == VLB_OK ) {
       SetFocustoVLB(pVLBox);
       vlbRedrawOff(pVLBox);
       SendMessage(pVLBox->hwndParent, VLBN_FREEALL, pVLBox->nId, 0L);
       SendMessage(pVLBox->hwndList, LB_RESETCONTENT, 0, 0L);

       if ( pVLBox->wFlags & HASSTRINGS) {
           SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lpTextPointer);
           SendMessage(pVLBox->hwndList, LB_SETITEMDATA, 0, pVLBox->vlbStruct.lData);
       }
       else
           SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lData);

       if ( TestSelectedItem(pVLBox, pVLBox->vlbStruct) ) {
          SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
          SetFocustoLB(pVLBox);
       }

       if ( pVLBox->lNumLogicalRecs == -1L )
          pVLBox->lToplIndex = pVLBox->vlbStruct.lData;
       else if ( pVLBox->wFlags & USEDATAVALUES )
          pVLBox->lToplIndex = (LONG)nPos* (pVLBox->lNumLogicalRecs-pVLBox->nLines+1)/100L;
       else
          pVLBox->lToplIndex = pVLBox->vlbStruct.lIndex;

       pVLBox->vlbStruct.lIndex = 0L;
       pVLBox->nCountInBox = 1;
       while ( pVLBox->nCountInBox < pVLBox->nLines ) {
          pVLBox->vlbStruct.nCtlID = pVLBox->nId;
          SendMessage(pVLBox->hwndParent, VLB_NEXT, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
          if ( pVLBox->vlbStruct.nStatus  == VLB_OK ) {
             if ( pVLBox->wFlags & HASSTRINGS) {
                 SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lpTextPointer);
                 SendMessage(pVLBox->hwndList, LB_SETITEMDATA, pVLBox->nCountInBox, pVLBox->vlbStruct.lData);
             }
             else
                 SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lData);

             if ( TestSelectedItem(pVLBox, pVLBox->vlbStruct) ) {
                SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
                SetFocustoLB(pVLBox);
             }

             pVLBox->nCountInBox++;
          }
          else
            break;
       }
       UpdateVLBWindow(pVLBox, NULL);
       vlbRedrawOn(pVLBox);
       return VLB_OK;
    }
    else
        return VLB_ERR;
}


int VLBFindPage( PVLBOX pVLBox, LONG lFindRecNum, BOOL bUpdateTop)
{
    int nSelected;

    nSelected = -1000;
    pVLBox->vlbStruct.lpTextPointer = NULL;
    pVLBox->vlbStruct.lData = pVLBox->vlbStruct.lIndex = lFindRecNum;
    pVLBox->vlbStruct.nCtlID = pVLBox->nId;
    SendMessage(pVLBox->hwndParent, VLB_FINDITEM, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
    if ( pVLBox->vlbStruct.nStatus  == VLB_OK ) {
       SetFocustoVLB(pVLBox);
       vlbRedrawOff(pVLBox);

       SendMessage(pVLBox->hwndParent, VLBN_FREEALL, pVLBox->nId, 0L);
       SendMessage(pVLBox->hwndList, LB_RESETCONTENT, 0, 0L);

       if ( pVLBox->wFlags & HASSTRINGS) {
           SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lpTextPointer);
           SendMessage(pVLBox->hwndList, LB_SETITEMDATA, 0, pVLBox->vlbStruct.lData);
       }
       else
           SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lData);

       if ( TestSelectedItem(pVLBox, pVLBox->vlbStruct) ) {
          nSelected = 0;
       }

       if ( bUpdateTop ) {
           if ( pVLBox->lNumLogicalRecs == -1L )
              pVLBox->lToplIndex = pVLBox->vlbStruct.lData;
           else if ( pVLBox->wFlags & USEDATAVALUES )
              pVLBox->lToplIndex = pVLBox->lNumLogicalRecs/2L;
           else
              pVLBox->lToplIndex = pVLBox->vlbStruct.lIndex;
       }

       pVLBox->vlbStruct.lIndex = lFindRecNum;
       pVLBox->nCountInBox = 1;
       while ( pVLBox->nCountInBox < pVLBox->nLines ) {
          pVLBox->vlbStruct.nCtlID = pVLBox->nId;
          SendMessage(pVLBox->hwndParent, VLB_NEXT, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
          if ( pVLBox->vlbStruct.nStatus  == VLB_OK ) {
             if ( pVLBox->wFlags & HASSTRINGS) {
                 SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lpTextPointer);
                 SendMessage(pVLBox->hwndList, LB_SETITEMDATA, pVLBox->nCountInBox, pVLBox->vlbStruct.lData);
             }
             else
                 SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lData);

             if ( TestSelectedItem(pVLBox, pVLBox->vlbStruct) ) {
                 nSelected = pVLBox->nCountInBox;
             }

             pVLBox->nCountInBox++;
          }
          else
            break;
       }

       if ( pVLBox->nCountInBox < pVLBox->nLines ) {
          if ( pVLBox->wFlags & USEDATAVALUES )
              pVLBox->vlbStruct.lIndex = -1L;
          else
              pVLBox->vlbStruct.lIndex = pVLBox->lToplIndex;
          pVLBox->vlbStruct.lpTextPointer = NULL;
          pVLBox->vlbStruct.lData = SendMessage(pVLBox->hwndList, LB_GETITEMDATA, 0, 0L);
          while ( pVLBox->nCountInBox < pVLBox->nLines ) {
             pVLBox->vlbStruct.nCtlID = pVLBox->nId;
             SendMessage(pVLBox->hwndParent, VLB_PREV, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
             if ( pVLBox->vlbStruct.nStatus  == VLB_OK ) {
                if ( pVLBox->wFlags & HASSTRINGS) {
                    SendMessage(pVLBox->hwndList, LB_INSERTSTRING, 0, (LPARAM) pVLBox->vlbStruct.lpTextPointer);
                    SendMessage(pVLBox->hwndList, LB_SETITEMDATA, 0, pVLBox->vlbStruct.lData);
                }
                else
                    SendMessage(pVLBox->hwndList, LB_INSERTSTRING, 0, (LPARAM) pVLBox->vlbStruct.lData);

                if ( TestSelectedItem(pVLBox, pVLBox->vlbStruct) ) {
                    nSelected = 0;
                }
                else {
                    nSelected++;
                }

                pVLBox->nCountInBox++;
                if ( pVLBox->lNumLogicalRecs != -1L )
                   pVLBox->lToplIndex--;
             }
             else
                break;
          }
       }

       if ( nSelected >= 0 ) {
          SendMessage(pVLBox->hwndList, LB_SETCURSEL, nSelected, 0L);
          SetFocustoLB(pVLBox);
       }

       UpdateVLBWindow(pVLBox, NULL);
       vlbRedrawOn(pVLBox);
       return VLB_OK;
    }
    else
        return VLB_ERR;
}


void VLBFirstPage( PVLBOX pVLBox)
{
    pVLBox->vlbStruct.lpTextPointer = NULL;
    pVLBox->vlbStruct.lData = pVLBox->vlbStruct.lIndex = 0L;
    pVLBox->vlbStruct.nCtlID = pVLBox->nId;
    SendMessage(pVLBox->hwndParent, VLB_FIRST, 0, (LPARAM)((LPVLBSTRUCT)&(pVLBox->vlbStruct)));
    if ( pVLBox->vlbStruct.nStatus  == VLB_OK ) {
       SetFocustoVLB(pVLBox);
       vlbRedrawOff(pVLBox);
       SendMessage(pVLBox->hwndParent, VLBN_FREEALL, pVLBox->nId, 0L);
       SendMessage(pVLBox->hwndList, LB_RESETCONTENT, 0, 0L);

       if ( pVLBox->wFlags & HASSTRINGS) {
           SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0,  (LPARAM) pVLBox->vlbStruct.lpTextPointer);
           SendMessage(pVLBox->hwndList, LB_SETITEMDATA, 0, pVLBox->vlbStruct.lData);
       }
       else
           SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0,  (LPARAM) pVLBox->vlbStruct.lData);

       if ( TestSelectedItem(pVLBox, pVLBox->vlbStruct) ) {
           SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
           SetFocustoLB(pVLBox);
       }

       if ( pVLBox->lNumLogicalRecs == -1L )
          pVLBox->lToplIndex = pVLBox->vlbStruct.lData;
       else if ( pVLBox->wFlags & USEDATAVALUES )
          pVLBox->lToplIndex = 0L;
       else
          pVLBox->lToplIndex = pVLBox->vlbStruct.lIndex;

       pVLBox->vlbStruct.lIndex = 0L;
       pVLBox->nCountInBox = 1;
       while ( pVLBox->nCountInBox < pVLBox->nLines ) {
          pVLBox->vlbStruct.nCtlID = pVLBox->nId;
          SendMessage(pVLBox->hwndParent, VLB_NEXT, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
          if ( pVLBox->vlbStruct.nStatus  == VLB_OK ) {
            if ( pVLBox->wFlags & HASSTRINGS) {
                SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lpTextPointer);
                SendMessage(pVLBox->hwndList, LB_SETITEMDATA, pVLBox->nCountInBox, pVLBox->vlbStruct.lData);
            }
            else
                SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lData);

            if ( TestSelectedItem(pVLBox, pVLBox->vlbStruct) ) {
               SendMessage(pVLBox->hwndList, LB_SETCURSEL, pVLBox->nCountInBox, 0L);
               SetFocustoLB(pVLBox);
            }

            pVLBox->vlbStruct.lIndex = (LONG) pVLBox->nCountInBox;
            pVLBox->nCountInBox++;
          }
          else
            break;
       }
    }
    UpdateVLBWindow(pVLBox, NULL);
    vlbRedrawOn(pVLBox);
}

void VLBLastPage(PVLBOX pVLBox)
{
    pVLBox->vlbStruct.lpTextPointer = NULL;
    pVLBox->vlbStruct.lData = pVLBox->vlbStruct.lIndex = 0L;
    pVLBox->vlbStruct.nCtlID = pVLBox->nId;
    SendMessage(pVLBox->hwndParent, VLB_LAST, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
    if ( pVLBox->vlbStruct.nStatus  == VLB_OK ) {
       SetFocustoVLB(pVLBox);
       vlbRedrawOff(pVLBox);
       SendMessage(pVLBox->hwndParent, VLBN_FREEALL, pVLBox->nId, 0L);
       SendMessage(pVLBox->hwndList, LB_RESETCONTENT, 0, 0L);

       if ( pVLBox->wFlags & HASSTRINGS) {
           SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lpTextPointer);
           SendMessage(pVLBox->hwndList, LB_SETITEMDATA, 0, pVLBox->vlbStruct.lData);
       }
       else
           SendMessage(pVLBox->hwndList, LB_ADDSTRING, 0, (LPARAM) pVLBox->vlbStruct.lData);

       if ( TestSelectedItem(pVLBox, pVLBox->vlbStruct) ) {
          SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
          SetFocustoLB(pVLBox);
       }

       if ( pVLBox->lNumLogicalRecs == -1L )
          pVLBox->lToplIndex = pVLBox->vlbStruct.lData;
       else if ( pVLBox->wFlags & USEDATAVALUES )
          pVLBox->lToplIndex = pVLBox->lNumLogicalRecs;
       else
          pVLBox->lToplIndex = pVLBox->vlbStruct.lIndex;

       pVLBox->nCountInBox = 1;
       while ( pVLBox->nCountInBox < pVLBox->nLines ) {
          pVLBox->vlbStruct.nCtlID = pVLBox->nId;
          SendMessage(pVLBox->hwndParent, VLB_PREV, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
          if ( pVLBox->vlbStruct.nStatus  == VLB_OK ) {
             if ( pVLBox->wFlags & HASSTRINGS) {
                 SendMessage(pVLBox->hwndList, LB_INSERTSTRING, 0, (LPARAM) pVLBox->vlbStruct.lpTextPointer);
                 SendMessage(pVLBox->hwndList, LB_SETITEMDATA, 0, pVLBox->vlbStruct.lData);
             }
             else
                 SendMessage(pVLBox->hwndList, LB_INSERTSTRING, 0, (LPARAM) pVLBox->vlbStruct.lData);

             if ( TestSelectedItem(pVLBox, pVLBox->vlbStruct) ) {
                 SendMessage(pVLBox->hwndList, LB_SETCURSEL, pVLBox->nCountInBox, 0L);
                 SetFocustoLB(pVLBox);
             }

             pVLBox->nCountInBox++;
             if ( pVLBox->lNumLogicalRecs != -1L )
                pVLBox->lToplIndex--;
          }
          else
             break;
       }

       UpdateVLBWindow(pVLBox, NULL);
       vlbRedrawOn(pVLBox);
    }
}


static void SetFocustoLB(PVLBOX pVLBox)
{
   pVLBox->wFlags &= ~PARENTFOCUS;
   if ( pVLBox->wFlags & HASFOCUS ) {
      SetFocus(pVLBox->hwndList);
   }
}


static void SetFocustoVLB(PVLBOX pVLBox)
{
   pVLBox->wFlags |= PARENTFOCUS;
   if ( pVLBox->wFlags & HASFOCUS ) {
      SetFocus(pVLBox->hwnd);
   }
}
