#include "vlistint.h"
#include "string.h"
#include "draw3d.h"

#define _LB_MOUSESCROLL         0x0118

#ifdef WIN32
BOOL  fWIN32s;
#endif

BOOL WINAPI RegisterVListBox(HINSTANCE hInstance)
{
static BOOL     bRegistered=FALSE;
WNDCLASS        wndcls;

   if (!bRegistered) {

       wndcls.style         = CS_DBLCLKS| CS_GLOBALCLASS|CS_PARENTDC;
       wndcls.lpfnWndProc   = VListBoxWndProc;
       wndcls.cbClsExtra    = 0;
       wndcls.cbWndExtra    = sizeof(HANDLE);
       wndcls.hInstance     = hInstance;
       wndcls.hIcon         = NULL;
       wndcls.hCursor       = LoadCursor(NULL, IDC_ARROW);
       wndcls.hbrBackground =  (HBRUSH)(COLOR_WINDOW+1);
       wndcls.lpszMenuName  = NULL;
       wndcls.lpszClassName = (LPSTR)VLIST_CLASSNAME;

       bRegistered=RegisterClass(&wndcls);

   }

#ifdef WIN32
   fWIN32s = ((DWORD)GetVersion() & 0x80000000) ? TRUE : FALSE;
#endif

   return bRegistered;
}

LRESULT EXPORT WINAPI VListBoxWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PVLBOX pVLBox;
  LONG lRetVal;

  /* Get the pVLBox for the given window now since we will use it a lot in
   * various handlers. This was stored using SetWindowWord(hwnd,0,pVLBox) when
   * we initially created the Virtual List Box control.
   */
#ifdef WIN32
   pVLBox = (PVLBOX) GetWindowLong(hwnd,0);
   if (message != WM_NCCREATE && (DWORD)pVLBox == (DWORD)-1)
#else
   pVLBox = (PVLBOX) GetWindowWord(hwnd,0);
   if (message != WM_NCCREATE && (WORD)pVLBox == (WORD)-1)
#endif
       // The pVLBox was destroyed and this is a rogue message to be ignored.
       return(0L);

  /* Dispatch the various messages we can receive */
  //
  // check for ListBox message coming from application
  // and forward them onto the listbox itself...
  //
#ifdef WIN32  
  if ( ((fWIN32s == TRUE) && (message >= WM_USER && message < VLB_MSGMIN) ) ||  // WIN32s version 
       ((fWIN32s == FALSE) && (message >= LB_ADDSTRING && message < LB_MSGMAX)) // NT version    
     ) {

     return(SendMessage(pVLBox->hwndList, message, wParam, lParam));
  }
#endif

  switch (message)
  {
    case VLB_INITIALIZE:
      SetScrollRange(pVLBox->hwndList, SB_VERT, 0, 100, TRUE);
      pVLBox->vlbStruct.nCtlID = pVLBox->nId;
      SendMessage(pVLBox->hwndParent, VLB_RANGE, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
      if ( pVLBox->vlbStruct.nStatus == VLB_OK ) {
         pVLBox->lNumLogicalRecs = pVLBox->vlbStruct.lIndex;
      }
      else {
         pVLBox->lNumLogicalRecs = -1L;
         pVLBox->wFlags = pVLBox->wFlags | USEDATAVALUES;
      }

      if ( pVLBox->styleSave & VLBS_USEDATAVALUES )
         pVLBox->wFlags |= USEDATAVALUES;

      if ( pVLBox->lNumLogicalRecs != 0 && pVLBox->nLines != 0)
         VLBFirstPage(pVLBox);

      pVLBox->lSelItem = -1L;

      return VLB_OK;

      break;

    case WM_VSCROLL:
#ifdef WIN32
       switch(LOWORD(wParam)) {
#else
       switch(wParam) {
#endif
          case SB_LINEDOWN:
              VLBScrollDownLine(pVLBox);
              SetSelectedItem(pVLBox);
          break;

          case SB_PAGEDOWN:
              VLBScrollDownPage(pVLBox, 0);
              SetSelectedItem(pVLBox);
          break;

          case SB_LINEUP:
              VLBScrollUpLine(pVLBox);
              SetSelectedItem(pVLBox);
          break;

          case SB_PAGEUP:
              VLBScrollUpPage(pVLBox, 0);
              SetSelectedItem(pVLBox);
          break;

          case SB_TOP:
              VLBFirstPage(pVLBox);
              SetSelectedItem(pVLBox);
          break;

          case SB_BOTTOM:
              VLBLastPage(pVLBox);
              SetSelectedItem(pVLBox);
          break;

          case SB_THUMBPOSITION:
            {
              int nPos;
#ifdef WIN32
              nPos = HIWORD(wParam);
#else
              nPos = LOWORD(lParam);
#endif
              if ( nPos == 0 ) {
                 VLBFirstPage(pVLBox);
                 break;
              }
              else if ( nPos == 100 ) {
                 VLBLastPage(pVLBox);
                 break;
              }

              if ( pVLBox->wFlags & USEDATAVALUES ) {
                    if ( VLBFindPos(pVLBox, nPos) )
                        return VLB_ERR;
                    else
                        SetSelectedItem(pVLBox);
              }
              else {
                 if ( VLBFindPage(pVLBox,
#ifdef WIN32
                 (((LONG)HIWORD(wParam)
#else
                 (((LONG)LOWORD(lParam)
#endif
                   *(pVLBox->lNumLogicalRecs-pVLBox->nLines+1))/100L), TRUE) )
                    return VLB_ERR;
                 else
                    SetSelectedItem(pVLBox);
              }
            }
          break;

       }
       return((LONG)TRUE);
       break;

    case WM_COMMAND:
      /* So that we can handle notification messages from the listbox.
       */
#ifdef WIN32
      if ( HIWORD(wParam) == LBN_SELCHANGE ) {
#else
      if ( HIWORD(lParam) == LBN_SELCHANGE ) {
#endif
         SetSelectedItem(pVLBox);
      }
#ifdef WIN32
      else if (HIWORD(wParam) == LBN_SELCANCEL) {
#else
      else if (HIWORD(lParam) == LBN_SELCANCEL) {
#endif
         pVLBox->lSelItem = -1L;
      }
      if (pVLBox->styleSave & VLBS_NOTIFY ) {
#ifdef WIN32
         return(VLBParentMessageHandler(pVLBox, message, (WPARAM)MAKELONG(pVLBox->nId, HIWORD(wParam)), lParam));

#else
         return(VLBParentMessageHandler(pVLBox, message, (WPARAM)(WORD)pVLBox->nId, lParam));
#endif
      }
      else {
         return TRUE;
      }
      break;

    case WM_CHARTOITEM: {
           long lRet;

           if (pVLBox->styleSave & VLBS_WANTKEYBOARDINPUT ) {
              lRet = VLBParentMessageHandler(pVLBox, WM_CHARTOITEM, wParam, lParam);
           }
           else {
              lRet = -1;
           }

           return lRet;
        }
        break;

    case WM_VKEYTOITEM: {
           long lRet;

           if (pVLBox->styleSave & VLBS_WANTKEYBOARDINPUT ) {
              lRet = VLBParentMessageHandler(pVLBox, WM_VKEYTOITEM, wParam, lParam);
           }
           else {
              lRet = -1;
           }

           if ( lRet == -1 ) {
#ifdef WIN32
       switch(LOWORD(wParam)) {
#else
       switch(wParam) {
#endif
                 case VK_DOWN:
                    vlbLineDn(pVLBox);
                    lRet = -2L;
                 break;

                 case VK_UP:
                    vlbLineUp(pVLBox);
                    lRet = -2L;
                 break;

                 case VK_PRIOR:
                     vlbPGUP(pVLBox);
                    lRet = -2L;
                 break;

                 case VK_NEXT:
                     vlbPGDN(pVLBox);
                    lRet = -2L;
                 break;

                 case VK_HOME:
                     VLBFirstPage(pVLBox);
                     SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
                     SetSelectedItem(pVLBox);
                     lRet = -2L;
                 break;

                 case VK_END:
                  {
                     int nLastLine;

                     if ( (pVLBox->nLines-1) < pVLBox->nCountInBox )
                        nLastLine = pVLBox->nLines-1;
                     else
                        nLastLine = pVLBox->nCountInBox-1;

                     VLBLastPage(pVLBox);
                     SendMessage(pVLBox->hwndList, LB_SETCURSEL, nLastLine, 0L);
                     SetSelectedItem(pVLBox);
                     lRet = -2L;
                  }
                 break;

                 default:
                    return lRet;
              }
              SendMessage(pVLBox->hwndParent, WM_COMMAND,
                          pVLBox->nId, MAKELPARAM(hwnd, LBN_SELCHANGE));
           }
           return lRet;
        }
        break;

    case _LB_MOUSESCROLL:
       {
         //
         // The user is holding the mouse down outside the LB....
         // Scroll the VLB as needed.
         //
         // Dont need to LB_SETCURSEL since the LB is going to do this for us.
         //
         int nSelected;

         nSelected = (int)SendMessage(pVLBox->hwndList, LB_GETCURSEL, 0, 0L);
         if ( nSelected == pVLBox->nLines-1 ) {
            VLBScrollDownLine(pVLBox);
            SetSelectedItem(pVLBox);
         }
         else if ( nSelected == 0 ) {
            VLBScrollUpLine(pVLBox);
            SetSelectedItem(pVLBox);
         }
         //
         // Values doesn't mean much since this messsage is passed back to
         // original LB proc
         //
         return 0L;
      }
      break;

    case WM_CREATE:
      /* wParam - not used
         lParam - Points to the CREATESTRUCT data structure for the window.
       */
      return(VLBCreateHandler(pVLBox, hwnd, (LPCREATESTRUCT)lParam));
      break;

    case WM_ERASEBKGND:
      /* Just return 1L so that the background isn't erased */
      return((LONG)TRUE);
      break;

    case WM_GETFONT:
       return((LONG)(pVLBox->hFont));
       break;

    case WM_GETDLGCODE:
      /* wParam - not used
         lParam - not used */
      return((LONG)(DLGC_WANTCHARS | DLGC_WANTARROWS));
      break;

    case WM_SETFONT:
#ifdef WIN32
      VLBSetFontHandler(pVLBox, (HANDLE)wParam, wParam);
#else
      VLBSetFontHandler(pVLBox, (HANDLE)wParam, LOWORD(lParam));
#endif
      break;

    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_KEYDOWN:
       // Set the focus to the Virtual List Box if we get a mouse click
       // or key press on the parent window.
       SetFocus(pVLBox->hwndList);
       SendMessage(pVLBox->hwndList, message, wParam, lParam);
      break;

    case WM_NCDESTROY:
      /* wParam - used by DefWndProc called within VLBNcDestroyHandler
         lParam - used by DefWndProc called within VLBNcDestroyHandler */
      VLBNcDestroyHandler(hwnd, pVLBox, wParam, lParam);
      break;

    case WM_KILLFOCUS:
          if ( (HWND) wParam != pVLBox->hwndList )
              pVLBox->wFlags  &= ~HASFOCUS;

      break;

    case WM_SETFOCUS:
        {
          int i;

          pVLBox->wFlags  |= HASFOCUS;

          if ( ! (pVLBox->wFlags & PARENTFOCUS) ) {
             if ( (i=vlbInVLB(pVLBox, pVLBox->lSelItem)) >= 0 ) {
                pVLBox->wFlags &= ~PARENTFOCUS;
                SetFocus(pVLBox->hwndList);
             }
             else {
                pVLBox->wFlags |= PARENTFOCUS;
             }
          }
        }
      break;

    case WM_SETREDRAW:
      /* wParam - specifies state of the redraw flag. nonzero = redraw
         lParam - not used */
      if ( wParam) {
         vlbRedrawOn(pVLBox);
      }
      else {
         vlbRedrawOff(pVLBox);
      }
      return TRUE;
      break;

    case WM_ENABLE:
      /* Invalidate the rect to cause it to be drawn in grey for its disabled
       * view or ungreyed for non-disabled view.
       */
      InvalidateRect(pVLBox->hwnd, NULL, FALSE);
      /* Enable/disable the listbox window
       */
      EnableWindow(pVLBox->hwndList, wParam);
      // EnableWindow(pVLBox->hwndScroll, wParam);
      break;

    case WM_SIZE:
      /* wParam - defines the type of resizing fullscreen, sizeiconic,
                  sizenormal etc.
         lParam - new width in LOWORD, new height in HIGHWORD of client area */
      if (!LOWORD(lParam) || !HIWORD(lParam) || !pVLBox->hwndList)
          /* If being sized to a zero width or to a zero height or we aren't
           * fully initialized, just return.
           */
             return(0);
      VLBSizeHandler(pVLBox, 0);
      break;

    case VLB_FINDSTRING:
    case VLB_FINDSTRINGEXACT:
    case VLB_SELECTSTRING:
       {
          VLBSTRUCT FAR *lpvlbInStruct;
          UINT  ReturnMsg;

          switch (message)
          {
            case VLB_FINDSTRING:
                ReturnMsg = VLBR_FINDSTRING;
                break;

            case VLB_FINDSTRINGEXACT:
                ReturnMsg = VLBR_FINDSTRINGEXACT;
                break;

            case VLB_SELECTSTRING:
                ReturnMsg = VLBR_FINDSTRINGEXACT;
                break;
          }

          lpvlbInStruct = (LPVLBSTRUCT)lParam;

          pVLBox->vlbStruct.lIndex        = lpvlbInStruct->lIndex;
          pVLBox->vlbStruct.lData         = lpvlbInStruct->lData;
          pVLBox->vlbStruct.lpFindString  = lpvlbInStruct->lpFindString;
          pVLBox->vlbStruct.lpTextPointer = NULL;

          pVLBox->vlbStruct.nCtlID = pVLBox->nId;
          SendMessage(pVLBox->hwndParent, ReturnMsg, 0,  (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
          if ( pVLBox->vlbStruct.nStatus == VLB_OK ) {
             if ( pVLBox->wFlags & USEDATAVALUES )
                lRetVal = pVLBox->vlbStruct.lData;
             else
                lRetVal = pVLBox->vlbStruct.lIndex;

             if ( message != VLB_SELECTSTRING ) {
                return lRetVal;
             }

             if ( pVLBox->wFlags & USEDATAVALUES ) {
                //
                // Strings or search for data
                //
                int i;
                if ( (i=vlbFindData(pVLBox, pVLBox->vlbStruct.lData)) != LB_ERR ) {
                    SendMessage(pVLBox->hwndList, LB_SETCURSEL, i, 0L);
                    SetSelectedItem(pVLBox);
                    return lRetVal;
                }
                else {
                   if ( VLBFindPage(pVLBox, pVLBox->vlbStruct.lData, TRUE) )
                        return VLB_ERR;

                   SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
                   SetSelectedItem(pVLBox);
                   return lRetVal;
                }
             }
             else {
                //
                // Is this item in the list box now ??
                //
                if ( pVLBox->vlbStruct.lIndex >= pVLBox->lToplIndex &&
                     pVLBox->vlbStruct.lIndex <= (pVLBox->lToplIndex+(LONG)(pVLBox->nCountInBox)-1)) {
                     int nItemNum;

                     nItemNum = (int) (pVLBox->vlbStruct.lIndex-pVLBox->lToplIndex);
                     SendMessage(pVLBox->hwndList, LB_SETCURSEL, nItemNum, 0L);
                     SetSelectedItem(pVLBox);
                     return lRetVal;
                }
                //
                // OK Adjust to show item
                //
                if ( VLBFindPage(pVLBox, pVLBox->vlbStruct.lIndex, TRUE) )
                    return VLB_ERR;

                SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
                SetSelectedItem(pVLBox);
                return lRetVal;
             }
          }
          else
             return VLB_ERR;
       }
      break;

    case VLB_RESETCONTENT:
      SendMessage(pVLBox->hwndParent, VLBN_FREEALL, pVLBox->nId, 0L);
      SendMessage(pVLBox->hwndList, LB_RESETCONTENT, 0, 0L);
      pVLBox->vlbStruct.nCtlID = pVLBox->nId;
      SendMessage(pVLBox->hwndParent, VLB_RANGE, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
      if ( pVLBox->vlbStruct.nStatus == VLB_OK )
         pVLBox->lNumLogicalRecs = pVLBox->vlbStruct.lIndex;
      else {
         pVLBox->lNumLogicalRecs = -1L;
         pVLBox->wFlags |= USEDATAVALUES;
      }

      if ( pVLBox->lNumLogicalRecs != 0 )
         VLBFirstPage(pVLBox);

      pVLBox->lSelItem = -1L;

      return VLB_OK;
      break;

    case VLB_SETCURSEL:
       // wParam Has Set Option:
       //   VLBC_FIRST
       //   VLBC_PREV
       //   VLBC_NEXT
       //   VLBC_LAST
       //   VLBC_FINDITEM
       //
       //  lParam has the item number or item data
       if ( lParam == -1L ) {
              SendMessage(pVLBox->hwndList, LB_SETCURSEL, (WORD)-1, 0L);
              pVLBox->lSelItem = -1L;
              return ( -1L );
       }
       else {
          return ( vlbSetCurSel(pVLBox, wParam, lParam) );
       }
       break;

    case VLB_UPDATEPAGE:
         pVLBox->vlbStruct.nCtlID = pVLBox->nId;
         SendMessage(pVLBox->hwndParent, VLB_RANGE, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
         if ( pVLBox->vlbStruct.nStatus == VLB_OK ) {
            pVLBox->lNumLogicalRecs = pVLBox->vlbStruct.lIndex;
         }
         else {
            pVLBox->lNumLogicalRecs = -1L;
            pVLBox->wFlags |= USEDATAVALUES;
		 }

		 if ( pVLBox->wFlags & USEDATAVALUES ) {
             if ( VLBFindPage(pVLBox, SendMessage(pVLBox->hwndList, LB_GETITEMDATA, 0, 0L), FALSE ) )
                return VLB_ERR;
         }
		 else if ( pVLBox->lNumLogicalRecs == 0L ) {
            SendMessage(pVLBox->hwndParent, VLBN_FREEALL, pVLBox->nId, 0L);
            SendMessage(pVLBox->hwndList, LB_RESETCONTENT, 0, 0L);
            pVLBox->lSelItem = -1L;
         }
         else if ( pVLBox->lNumLogicalRecs <= pVLBox->nLines ) {
            VLBFirstPage(pVLBox);
         }
         else {
             if ( VLBFindPage(pVLBox, pVLBox->lToplIndex, FALSE) )
                return VLB_ERR;
         }
       break;

    case VLB_PAGEUP:
         VLBScrollUpPage(pVLBox, wParam);
         break;

    case VLB_PAGEDOWN:
         VLBScrollDownPage(pVLBox, wParam);
         break;

    case VLB_GETCURSEL:
         return pVLBox->lSelItem;
         break;

    case VLB_GETLINES:
         return (LONG)pVLBox->nLines;
         break;

    case VLB_GETITEMDATA:
        {
          LPVLBSTRUCT lpvlbInStruct;
          int i;
          LPARAM SendlParam;


          lpvlbInStruct = (LPVLBSTRUCT)lParam;

          if (pVLBox->wFlags & USEDATAVALUES) {
             SendlParam = lpvlbInStruct->lData;
          }
          else {
             SendlParam = lpvlbInStruct->lIndex;
          }

          if ( (i=vlbInVLB(pVLBox, SendlParam)) >= 0 ) {
             return(SendMessage(pVLBox->hwndList, LB_GETITEMDATA, i, 0L));
          }
          else {
             pVLBox->vlbStruct.lData = pVLBox->vlbStruct.lIndex = SendlParam;
             pVLBox->vlbStruct.nCtlID = pVLBox->nId;
             SendMessage(pVLBox->hwndParent, VLBR_GETITEMDATA, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
             if ( pVLBox->vlbStruct.nStatus == VLB_OK )
                return pVLBox->vlbStruct.lData;
             else
                return VLB_ERR;
          }
        }
        break;

    case VLB_GETCOUNT:
      return pVLBox->lNumLogicalRecs;

    case VLB_GETTEXT:
        {
          LPVLBSTRUCT lpvlbInStruct;
          int i;
          LPARAM SendlParam;

          lpvlbInStruct = (LPVLBSTRUCT)lParam;

          if (pVLBox->wFlags & USEDATAVALUES) {
             SendlParam = lpvlbInStruct->lData;
          }
          else {
             SendlParam = lpvlbInStruct->lIndex;
          }

          if ( (i=vlbInVLB(pVLBox, SendlParam)) >= 0 ) {
             return(SendMessage(pVLBox->hwndList, LB_GETTEXT, i, (LPARAM)lpvlbInStruct->lpTextPointer));
          }
          else {
             pVLBox->vlbStruct.lData = pVLBox->vlbStruct.lIndex = SendlParam;
             pVLBox->vlbStruct.nCtlID = pVLBox->nId;
             SendMessage(pVLBox->hwndParent, VLBR_GETTEXT, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
             if ( pVLBox->vlbStruct.nStatus == VLB_OK ) {
                _fstrcpy(lpvlbInStruct->lpTextPointer, pVLBox->vlbStruct.lpTextPointer);
                return _fstrlen(pVLBox->vlbStruct.lpTextPointer);
             }
             else
                return VLB_ERR;
          }
        }
        break;

    case VLB_GETTEXTLEN:
        {
          LPVLBSTRUCT lpvlbInStruct;
          int i;
          LPARAM SendlParam;

          lpvlbInStruct = (LPVLBSTRUCT)lParam;

          if (pVLBox->wFlags & USEDATAVALUES) {
             SendlParam = lpvlbInStruct->lData;
          }
          else {
             SendlParam = lpvlbInStruct->lIndex;
          }

          if ( (i=vlbInVLB(pVLBox, SendlParam)) >= 0 ) {
             return(SendMessage(pVLBox->hwndList, LB_GETTEXTLEN, i, 0L));
          }
          else {
             pVLBox->vlbStruct.lData = pVLBox->vlbStruct.lIndex = SendlParam;
             pVLBox->vlbStruct.nCtlID = pVLBox->nId;
             return SendMessage(pVLBox->hwndParent, VLBR_GETTEXTLEN, 0, (LPARAM)(LPVLBSTRUCT)&(pVLBox->vlbStruct));
          }
        }
        break;

    case VLB_SETITEMDATA:
        {
          LPVLBSTRUCT lpvlbInStruct;
          int i;
          LPARAM SendlParam;

          lpvlbInStruct = (LPVLBSTRUCT)lParam;

          if (pVLBox->wFlags & USEDATAVALUES) {
             SendlParam = lpvlbInStruct->lData;
          }
          else {
             SendlParam = lpvlbInStruct->lIndex;
          }

          if ( (i=vlbInVLB(pVLBox, SendlParam)) >= 0 ) {
             return(SendMessage(pVLBox->hwndList, LB_SETITEMDATA, i, (LPARAM)lpvlbInStruct->lIndex));
          }
          else return VLB_ERR;
        }
        break;

    case VLB_SETITEMHEIGHT:
          return SendMessage(pVLBox->hwndList, LB_SETITEMHEIGHT, 0, lParam);
        break;

    case VLB_GETITEMHEIGHT:
          return SendMessage(pVLBox->hwndList, LB_GETITEMHEIGHT, 0, 0L);
        break;

    case VLB_GETITEMRECT:
        {
          LPVLBSTRUCT lpvlbInStruct;
          int i;
          LPARAM SendlParam;

          lpvlbInStruct = (LPVLBSTRUCT)lParam;

          if (pVLBox->wFlags & USEDATAVALUES) {
             SendlParam = lpvlbInStruct->lData;
          }
          else {
             SendlParam = lpvlbInStruct->lIndex;
          }

          if ( (i=vlbInVLB(pVLBox, SendlParam)) >= 0 ) {
             return(SendMessage(pVLBox->hwndList, LB_GETITEMRECT, i, (LPARAM)lpvlbInStruct->lpTextPointer));
          }
          else return VLB_ERR;
        }
        break;

    case VLB_GETHORIZONTALEXTENT:
          return SendMessage(pVLBox->hwndList, LB_GETHORIZONTALEXTENT, 0, 0L);
		break;

	case VLB_SETTABSTOPS:
		  return SendMessage(pVLBox->hwndList, LB_SETTABSTOPS, wParam, lParam);
		break;


    case VLB_SETHORIZONTALEXTENT:
        {
          int nOrigin;
          RECT rc;
          int  nScrollBar;

          SendMessage(pVLBox->hwndList, LB_GETITEMRECT, 0,(LPARAM)(LPRECT)&rc);
          nOrigin = rc.left;
          GetClientRect(pVLBox->hwndList, &rc);
          nScrollBar = max((int)wParam - (rc.right - rc.left),0);
          if (nOrigin || nScrollBar) {
             if ( pVLBox->styleSave & VLBS_DISABLENOSCROLL )
                   EnableScrollBar(pVLBox->hwndList, SB_HORZ, ESB_ENABLE_BOTH);
             else {
             if (!pVLBox->bHScrollBar) {
                   pVLBox->bHScrollBar = TRUE;
                   ShowScrollBar(pVLBox->hwndList, SB_HORZ, TRUE);
                   VLBCountLines(pVLBox);
                }
             }
          }
          else {
             if ( pVLBox->styleSave & VLBS_DISABLENOSCROLL )
                   EnableScrollBar(pVLBox->hwndList, SB_HORZ, ESB_DISABLE_BOTH);
             else {
                if (pVLBox->bHScrollBar) {
                   pVLBox->bHScrollBar = FALSE;
                   ShowScrollBar(pVLBox->hwndList, SB_HORZ, FALSE);
                   VLBCountLines(pVLBox);
                }
             }
          }
          return SendMessage(pVLBox->hwndList, LB_SETHORIZONTALEXTENT, wParam, 0L);
        }
        break;

    case VLB_SETTOPINDEX:
        {
          int i, nScroll;

          if ( (i=vlbInVLB(pVLBox, lParam)) > 0 ) {
             nScroll = (int)(-1*(pVLBox->nLines-i));
             VLBScrollDownPage(pVLBox, nScroll);
          }
          else if ( pVLBox->wFlags & USEDATAVALUES ) {
             if ( VLBFindPage(pVLBox, lParam, TRUE ))
                return VLB_ERR;
          }
          else {
             if ( VLBFindPage(pVLBox, lParam, TRUE) )
                return VLB_ERR;
          }

        }
        break;

    case VLB_GETTOPINDEX:
          if ( pVLBox->wFlags & USEDATAVALUES )
             return SendMessage(pVLBox->hwndList, LB_GETITEMDATA, 0, 0L);
          else
             return pVLBox->lToplIndex;
        break;   
        
    case WM_CTLCOLOR:
         if ( pVLBox->styleSave & VLBS_3DFRAME ) { 
            return (LRESULT) Draw3dCtlColor(CTLCOLOR_LISTBOX, wParam, lParam);
		 }
		 else {
			return(SendMessage(pVLBox->hwndList, message, wParam, lParam));
		 }
        break;
                  
    case WM_PAINT:  
         DefWindowProc(hwnd, message, wParam, lParam);
         if ( pVLBox->styleSave & VLBS_3DFRAME ) {
            RC rc;
            HDC hdc;
            
            GetWindowRect(hwnd, (LPRECT) &rc);
            ScreenToClient( pVLBox->hwndParent, (LPPOINT) &rc);
            ScreenToClient( pVLBox->hwndParent, (LPPOINT) &rc+1);
            hdc = GetDC( pVLBox->hwndParent );  
            
            Draw3dInsetRect(hdc, &rc, DR3ALL);
			hdc = ReleaseDC( pVLBox->hwndParent, hdc);
         }     
         break;              
      
    case WM_MEASUREITEM:
    case WM_DELETEITEM:
    case WM_DRAWITEM:
    case WM_COMPAREITEM:
      return(VLBMessageItemHandler(pVLBox, message, (LPSTR)lParam));
      break;

    case WM_NCCREATE:
      /* wParam - Contains a handle to the window being created
         lParam - Points to the CREATESTRUCT data structure for the window.
       */
      return(VLBNcCreateHandler(hwnd, (LPCREATESTRUCT)lParam));
      break;

    default:
#ifndef WIN32    
      if ( message >= WM_USER )
         return(SendMessage(pVLBox->hwndList, message, wParam, lParam));
      else
#endif      
         return DefWindowProc(hwnd, message, wParam, lParam);
      break;

  } /* switch (message) */

  return((LONG)(LONG)TRUE);
} /* VListBoxWndProc */


LONG VLBMessageItemHandler( PVLBOX pVLBox,  UINT message, LPSTR lpfoo)
/*
 * effects: Handles WM_DRAWITEM,WM_MEASUREITEM,WM_DELETEITEM,WM_COMPAREITEM
 * messages from the listbox.
 */
{
  /*
   * Send the <foo>item message back to the application after changing some
   * parameters to their Virtual List Box specific versions.
   */
  long lRetVal;

  ((LPMEASUREITEMSTRUCT)lpfoo)->CtlType = ODT_LISTBOX;
#ifdef WIN32
  ((LPMEASUREITEMSTRUCT)lpfoo)->CtlID   = (DWORD)pVLBox->nId;
#else
  ((LPMEASUREITEMSTRUCT)lpfoo)->CtlID   = (WORD)pVLBox->nId;
#endif

  if (message == WM_DRAWITEM)
      ((LPDRAWITEMSTRUCT)lpfoo)->hwndItem    = pVLBox->hwnd;
  else if (message == WM_DELETEITEM)
      ((LPDELETEITEMSTRUCT)lpfoo)->hwndItem  = pVLBox->hwnd;
  else if (message == WM_COMPAREITEM)
      ((LPCOMPAREITEMSTRUCT)lpfoo)->hwndItem  = pVLBox->hwnd;

  lRetVal = SendMessage(pVLBox->hwndParent, message,
                    (WPARAM)pVLBox->nId, (LPARAM)lpfoo);

  if (message == WM_MEASUREITEM ) {
     // Size the list box based on height in message
     VLBSizeHandler( pVLBox , ((LPMEASUREITEMSTRUCT)lpfoo)->itemHeight);
  }

  return lRetVal;

}


LONG VLBParentMessageHandler( PVLBOX pVLBox, UINT message, WPARAM wParam, LPARAM lParam)
{
  return SendMessage(pVLBox->hwndParent,
              message,
              wParam,
              MAKELPARAM(pVLBox->hwnd, HIWORD(lParam) ) );

}



int vlbInVLB( PVLBOX pVLBox, LONG lData)
{
   int i;

   if ( pVLBox->wFlags & USEDATAVALUES ) {
      if ( (i=vlbFindData(pVLBox, lData)) != LB_ERR ) {
        return i;
      }
      else {
        return  VLB_ERR;
      }
   }
   else {
      if ( lData >= pVLBox->lToplIndex &&
           lData <= (pVLBox->lToplIndex+(LONG)(pVLBox->nCountInBox)-1)) {
        return (int) (lData - pVLBox->lToplIndex);
      }
      else {
        return  VLB_ERR;
      }
   }
}

int vlbFindData( PVLBOX pVLBox, LONG lData)
{
   int i;

   i = 0;
   while ( i < pVLBox->nCountInBox ) {
      if ( SendMessage(pVLBox->hwndList, LB_GETITEMDATA, i, 0L) == lData )
         return i;
      i++;
   }

   return VLB_ERR;

}

void vlbRedrawOff(PVLBOX pVLBox)
{
     pVLBox->nvlbRedrawState--;
     if ( pVLBox->nvlbRedrawState == 0 ) {
        SendMessage(pVLBox->hwndList, WM_SETREDRAW, 0, 0L);
     }
}

void vlbRedrawOn(PVLBOX pVLBox)
{
     pVLBox->nvlbRedrawState++;
     if ( pVLBox->nvlbRedrawState == 1 ) {
        SendMessage(pVLBox->hwndList, WM_SETREDRAW, 1, 0L);
        InvalidateRect(pVLBox->hwnd, NULL, FALSE);
     }
}


//
// List Box subclass function
//

LRESULT  EXPORT WINAPI LBSubclassProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PVLBOX pVLBox;

    switch (message) {
    case WM_VSCROLL:
        //
        // Handle all the scrolling in the Vlist proc
        //
        return SendMessage(GetParent(hwnd), message, wParam, lParam);

    case _LB_MOUSESCROLL:
        //
        // Check for scroll then pass message on the the LB
        //
        SendMessage(GetParent(hwnd), message, wParam, lParam);
      break;

    default:
        break;
    }

    //
    // call the old window proc
    //
#ifdef WIN32
   pVLBox = (PVLBOX) GetWindowLong(GetParent(hwnd),0);
#else
   pVLBox = (PVLBOX) GetWindowWord(GetParent(hwnd),0);
#endif

    if ( message == WM_SETFOCUS ) {
          pVLBox->wFlags  |= HASFOCUS;
    }

    return CallWindowProc((WNDPROC)(pVLBox->lpfnLBWndProc) , hwnd, message,
                          (WPARAM) wParam, (LPARAM)lParam);

}


BOOL TestSelectedItem(PVLBOX pVLBox, VLBSTRUCT vlbStruct)
{
    if ( pVLBox->wFlags & USEDATAVALUES ) {
       if ( pVLBox->lSelItem == vlbStruct.lData )
         return TRUE;
       else
         return FALSE;
    }
    else {
       if ( pVLBox->lSelItem == vlbStruct.lIndex )
         return TRUE;
       else
         return FALSE;
    }
}

void SetSelectedItem(PVLBOX pVLBox)
{
    int nSelected;

    nSelected = (int)SendMessage(pVLBox->hwndList, LB_GETCURSEL, 0, 0L);

    if ( nSelected == LB_ERR )
       return;

    if ( pVLBox->wFlags & USEDATAVALUES ) {
       pVLBox->lSelItem =
            SendMessage(pVLBox->hwndList, LB_GETITEMDATA, nSelected, 0L);
    }
    else {
       pVLBox->lSelItem = (LONG)nSelected + pVLBox->lToplIndex;
    }
}

void vlbLineDn(PVLBOX pVLBox)
{
    //
    // Do we have a selected item ???
    //
    if ( pVLBox->lSelItem != -1L )
    {
        long lSelected;
        if ( (lSelected = SendMessage(pVLBox->hwndList, LB_GETCURSEL,
             0, 0L)) == -1L ) {
               //
               // Current selction is visible....NOT
               //
               vlbRedrawOff(pVLBox);

               //
               // Put selected item at top of LB
               //
               VLBFindPage(pVLBox, pVLBox->lSelItem, TRUE);

               //
               // Scroll the LB down a line
               //
               VLBScrollDownLine(pVLBox);
               SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
               SetFocus(pVLBox->hwndList);
               SetSelectedItem(pVLBox);

               //
               // Update the Screen
               //
               vlbRedrawOn(pVLBox);
        }
        else {
               //
               // Current selection is visible
               //

               //
               // Where is it ????
               //
               if ( (int)lSelected == (pVLBox->nLines-1) ) {
                  //
                  // At the Bottom... Scroll down 1 page less 1 line
                  //                  Put selection at bottom
                  //
                  VLBScrollDownLine(pVLBox);
                  SendMessage(pVLBox->hwndList, LB_SETCURSEL,
                              pVLBox->nLines-1, 0L);
                  SetFocus(pVLBox->hwndList);
                  SetSelectedItem(pVLBox);
               }
               else {
                   SendMessage(pVLBox->hwndList, LB_SETCURSEL,
                               (int)(lSelected)+1, 0L);
                   SetFocus(pVLBox->hwndList);
                   SetSelectedItem(pVLBox);
               }
        }
    }
}

void vlbLineUp(PVLBOX pVLBox)
{
    //
    // Do we have a selected item ???
    //
    if ( pVLBox->lSelItem != -1L )
    {
        long lSelected;
        if ( (lSelected = SendMessage(pVLBox->hwndList, LB_GETCURSEL,
             0, 0L)) == -1L ) {
               //
               // Current selction is visible....NOT
               //
               vlbRedrawOff(pVLBox);

               //
               // Put selected item at top of LB
               //
               VLBFindPage(pVLBox, pVLBox->lSelItem, TRUE);

               //
               // Scroll the LB down a line
               //
               VLBScrollUpLine(pVLBox);
               SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
               SetFocus(pVLBox->hwndList);
               SetSelectedItem(pVLBox);

               //
               // Update the Screen
               //
               vlbRedrawOn(pVLBox);
        }
        else {
               //
               // Current selection is visible
               //

               //
               // Where is it ????
               //
               if ( (int)lSelected == 0 ) {
                  //
                  // At the Bottom... Scroll up 1 page less 1 line
                  //                  Put selection at bottom
                  //
                  VLBScrollUpLine(pVLBox);
                  SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
                  SetFocus(pVLBox->hwndList);
                  SetSelectedItem(pVLBox);
               }
               else {
                   SendMessage(pVLBox->hwndList, LB_SETCURSEL,
                               (int)(lSelected)-1, 0L);
                   SetFocus(pVLBox->hwndList);
                   SetSelectedItem(pVLBox);
               }
        }
    }
}


void vlbPGDN(PVLBOX pVLBox)
{
    //
    // Do we have a selected item ???
    //
    if ( pVLBox->lSelItem != -1L )
    {
        long lSelected;
        if ( (lSelected = SendMessage(pVLBox->hwndList, LB_GETCURSEL,
             0, 0L)) == -1L ) {
               //
               // Current selction is visible....NOT
               //
               vlbRedrawOff(pVLBox);

               //
               // Put selected item at top of LB
               //
               VLBFindPage(pVLBox, pVLBox->lSelItem, TRUE);

               //
               // Scroll the LB down a page
               //
               VLBScrollDownPage(pVLBox, -1);
               SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
               SetFocus(pVLBox->hwndList);
               SetSelectedItem(pVLBox);

               //
               // Update the Screen
               //
               vlbRedrawOn(pVLBox);
        }
        else {
               //
               // Current selection is visible
               //

               //
               // Where is it ????
               //
               if ( lSelected == 0L ) {
                  //
                  // At the top... put selection at bottom
                  //
                  SendMessage(pVLBox->hwndList, LB_SETCURSEL,
                              pVLBox->nLines-1, 0L);
                  SetFocus(pVLBox->hwndList);
                  SetSelectedItem(pVLBox);
               }
               else if ( (int)lSelected == (pVLBox->nLines-1) ) {
                  //
                  // At the Bottom... Scroll down 1 page less 1 line
                  //                  Put selection at bottom
                  //
                  VLBScrollDownPage(pVLBox, -1);
                  SendMessage(pVLBox->hwndList, LB_SETCURSEL,
                              pVLBox->nLines-1, 0L);
                  SetFocus(pVLBox->hwndList);
                  SetSelectedItem(pVLBox);
               }
               else {
                   //
                   // In the middle ... scroll down 1 page less
                   //                   the number of lines
                   //                   the selection is away
                   //                   from the bottom
                   //
                   //                   Put selection at bottom
                   //
                   int nAdjust;
                   nAdjust = -1 * (pVLBox->nLines-(int)lSelected);
                   VLBScrollDownPage(pVLBox, nAdjust);
                   SendMessage(pVLBox->hwndList, LB_SETCURSEL,
                               pVLBox->nLines-1, 0L);
                   SetFocus(pVLBox->hwndList);
                   SetSelectedItem(pVLBox);
               }
        }
    }
}


void vlbPGUP(PVLBOX pVLBox)
{
    //
    // Do we have a selected item ???
    //
    if ( pVLBox->lSelItem != -1L )
    {
        long lSelected;
        if ( (lSelected = SendMessage(pVLBox->hwndList, LB_GETCURSEL,
             0, 0L)) == -1L ) {
               //
               // Current selction is visible....NOT
               //
               vlbRedrawOff(pVLBox);

               //
               // Put selected item at top of LB
               //
               VLBFindPage(pVLBox, pVLBox->lSelItem, TRUE);

               //
               // Scroll the LB UP a page less 1 line
               //
               VLBScrollUpPage(pVLBox, -1);
               SendMessage(pVLBox->hwndList, LB_SETCURSEL, 0, 0L);
               SetFocus(pVLBox->hwndList);
               SetSelectedItem(pVLBox);

               //
               // Update the Screen
               //
               vlbRedrawOn(pVLBox);
        }
        else {
               //
               // Current selction is visible
               //

               //
               // Where is it ????
               //
               if ( lSelected == (pVLBox->nLines-1) ) {
                  //
                  // At the bottom... put selection at top
                  //
                  SendMessage(pVLBox->hwndList, LB_SETCURSEL,
                              0, 0L);
                  SetFocus(pVLBox->hwndList);
                  SetSelectedItem(pVLBox);
               }
               else if ( (int)lSelected ==  0L) {
                  //
                  // At the TOP ... Scroll up 1 page less 1 line
                  //                  Put selection at top
                  //
                  VLBScrollUpPage(pVLBox, -1);
                  SendMessage(pVLBox->hwndList, LB_SETCURSEL,
                              0, 0L);
                  SetFocus(pVLBox->hwndList);
                  SetSelectedItem(pVLBox);
               }
               else {
                   //
                   // In the middle ... scroll up 1 page less
                   //                   the number of lines
                   //                   the selection is away
                   //                   from the top
                   //
                   //                   Put selection at top
                   //
                   int nAdjust;
                   nAdjust = -1 * ((int)lSelected + 1 );
                   VLBScrollUpPage(pVLBox, nAdjust);
                   SendMessage(pVLBox->hwndList, LB_SETCURSEL,
                               0, 0L);
                   SetFocus(pVLBox->hwndList);
                   SetSelectedItem(pVLBox);
               }
        }
    }
}
