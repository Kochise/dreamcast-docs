#include "vlistint.h"
#include "draw3d.h"

LONG VLBNcCreateHandler( HWND hwnd, LPCREATESTRUCT lpcreateStruct)
{
  PVLBOX pVLBox;

  //
  // Allocate storage for the vlbox structure
  //
  pVLBox = (PVLBOX) LocalAlloc(LPTR, sizeof(VLBOX));

  if (!pVLBox)
      // Error, no memory
      return((long)NULL);

#ifdef WIN32
  SetWindowLong(hwnd, 0, (WPARAM)pVLBox);
#else
  SetWindowWord(hwnd, 0, (WPARAM)pVLBox);
#endif

  pVLBox->styleSave = lpcreateStruct->style;

  //
  // Make sure that there are no scroll bar styles
  //
  SetWindowLong(hwnd, GWL_STYLE,
                (LPARAM)(DWORD)( pVLBox->styleSave &
                ~WS_VSCROLL & ~WS_HSCROLL));


  Draw3dRegister();
  
  return((LONG)hwnd);

}


LONG VLBCreateHandler( PVLBOX pVLBox, HWND hwnd, LPCREATESTRUCT lpcreateStruct)
{
  LONG           windowStyle = pVLBox->styleSave;
  RECT           rc;
  TEXTMETRIC     TextMetric;
  HDC            hdc;

  //
  // Initialize Variables
  //
  pVLBox->hwnd            = hwnd;
  pVLBox->hwndParent      = lpcreateStruct->hwndParent;
  pVLBox->nId             = (int) lpcreateStruct->hMenu;
  pVLBox->hInstance       = lpcreateStruct->hInstance;
  pVLBox->nvlbRedrawState = 1;
  pVLBox->lNumLogicalRecs = -2L;
  pVLBox->lSelItem        = -1L;
  pVLBox->wFlags          = 0;
  pVLBox->hwndList        = NULL;

  //
  // Check for USEDATAVALUES
  //
  if ( windowStyle & VLBS_USEDATAVALUES )
      pVLBox->wFlags  |= USEDATAVALUES;
  else
      pVLBox->wFlags &= ~USEDATAVALUES;

  //
  // Dertermine if this VLB is storing string
  //
  pVLBox->wFlags |= HASSTRINGS;
  if ((windowStyle & VLBS_OWNERDRAWFIXED )
     && (!(windowStyle & VLBS_HASSTRINGS)))
     pVLBox->wFlags &= ~HASSTRINGS;

  //
  // Get the font height and Number of lines
  //
  hdc = GetDC(hwnd);
  GetTextMetrics(hdc, &TextMetric);
  ReleaseDC(hwnd,hdc);
  pVLBox->nchHeight = TextMetric.tmHeight;
  GetClientRect(hwnd,&rc);
  pVLBox->nLines = ((rc.bottom - rc.top) / pVLBox->nchHeight);

  //
  // Remove borders and scroll bars, add keyboard input
  //
  windowStyle = windowStyle & ~WS_BORDER & ~WS_THICKFRAME;
  windowStyle = windowStyle & ~WS_VSCROLL & ~WS_HSCROLL;

  //
  // Remove regular list box we don't support
  //
  windowStyle = windowStyle & ~LBS_SORT;
  windowStyle = windowStyle & ~LBS_MULTIPLESEL;
  windowStyle = windowStyle & ~LBS_OWNERDRAWVARIABLE;
  windowStyle = windowStyle & ~LBS_MULTICOLUMN;
  windowStyle = windowStyle & ~VLBS_USEDATAVALUES;

  //
  // Add List box styles we have to have
  //
  windowStyle = windowStyle | LBS_WANTKEYBOARDINPUT;
  windowStyle = windowStyle | LBS_NOINTEGRALHEIGHT;
  windowStyle = windowStyle | LBS_NOTIFY;

  //
  // create the list box window
  //
  pVLBox->hwndList =
    CreateWindowEx((DWORD)0L,
                 (LPSTR)"LISTBOX",(LPSTR)NULL,
                 windowStyle | WS_CHILD,
                 0,
                 0,
                 rc.right,
                 rc.bottom,
                 pVLBox->hwnd,
                 (HMENU)VLBLBOXID,
                 pVLBox->hInstance,
                 NULL);

  if (!pVLBox->hwndList)
      return((LONG)-1L);

  if ( pVLBox->styleSave & VLBS_DISABLENOSCROLL ) {
     ShowScrollBar(pVLBox->hwndList, SB_VERT, TRUE);
     EnableScrollBar(pVLBox->hwndList, SB_VERT, ESB_DISABLE_BOTH);
     if ( pVLBox->styleSave & WS_HSCROLL) {
        pVLBox->bHScrollBar = TRUE;
        ShowScrollBar(pVLBox->hwndList, SB_HORZ, TRUE);
        EnableScrollBar(pVLBox->hwndList, SB_HORZ, ESB_DISABLE_BOTH);
        VLBCountLines(pVLBox);
     }
  }
  else {
     pVLBox->bHScrollBar = FALSE;
  }

  //
  // Subclass the list box
  //
  pVLBox->lpfnLBWndProc = (WNDPROC)SetWindowLong(pVLBox->hwndList, GWL_WNDPROC,
                                        (LONG)(WNDPROC)LBSubclassProc);

  return((LONG)hwnd);
}

void VLBNcDestroyHandler(HWND hwnd,  PVLBOX pVLBox, WPARAM wParam, LPARAM lParam)
{

  if (pVLBox)
      LocalFree((HANDLE)pVLBox);
      
  Draw3dUnregister();
    
  //
  // In case rogue messages float through after we have freed the pVLBox, set
  // the handle in the window structure to FFFF and test for this value at the
  // top of the WndProc
  //
#ifdef WIN32
  SetWindowLong(hwnd, 0, (WPARAM)-1);
#else
  SetWindowWord(hwnd, 0, (WPARAM)-1);
#endif

  DefWindowProc(hwnd, WM_NCDESTROY, wParam, lParam);
}


void VLBSetFontHandler( PVLBOX pVLBox, HANDLE hFont, BOOL fRedraw)
{
  pVLBox->hFont = hFont;

#ifdef WIN32
  SendMessage(pVLBox->hwndList, WM_SETFONT, (WPARAM)hFont, (LPARAM)MAKELPARAM(FALSE,0));
#else
  SendMessage(pVLBox->hwndList, WM_SETFONT, (WPARAM)hFont, (LPARAM)FALSE);
#endif

  VLBSizeHandler(pVLBox, 0);

  if (fRedraw)
    {
      InvalidateRect(pVLBox->hwnd, NULL, TRUE);
    }
}


void VLBSizeHandler( PVLBOX pVLBox, int nItemHeight)
//
// Recalculates the sizes of the internal control in response to a
// resizing of the Virtual List Box window.
//
{
  HDC             hdc;
  TEXTMETRIC      TextMetric;
  RECT            rcWindow;
  RECT            rcClient;
  HANDLE          hOldFont;

  //
  // Set the line height
  //
  if ( nItemHeight ) {
    pVLBox->nchHeight = nItemHeight;
  }
  else if ( (pVLBox->styleSave & VLBS_OWNERDRAWFIXED) ) {
    pVLBox->nchHeight = (int) SendMessage(pVLBox->hwndList, LB_GETITEMHEIGHT, 0,0L);
  }
  else {
    hdc = GetDC(pVLBox->hwndList);
    if (pVLBox->hFont)
       hOldFont = SelectObject(hdc, pVLBox->hFont);
    GetTextMetrics(hdc, &TextMetric);
    pVLBox->nchHeight = TextMetric.tmHeight;
    if (pVLBox->hFont)
       SelectObject(hdc, hOldFont);
    ReleaseDC(pVLBox->hwndList,hdc);
  }

  //
  // Get the main windows client area
  //
  GetClientRect(pVLBox->hwnd,&rcClient);

  //
  // If there is a Window and
  // If the list box is integral height ...
  //
  if ( pVLBox->hwnd && !(pVLBox->styleSave & VLBS_NOINTEGRALHEIGHT) ) {
      //
      // Does it need adjusting ??????
      //
      if (rcClient.bottom % pVLBox->nchHeight) {
          //
          // Adjust
          //
             GetWindowRect(pVLBox->hwnd,&rcWindow);
             SetWindowPos(pVLBox->hwnd, NULL, 0, 0,
                 rcWindow.right - rcWindow.left,
                 ((rcClient.bottom / pVLBox->nchHeight) * pVLBox->nchHeight)
                     + ((rcWindow.bottom-rcWindow.top) - (rcClient.bottom)),
                 SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
      }
  }

  //
  // Now adjust the child list box to fill the new main window's
  // client area.
  //
  if ( pVLBox->hwndList ) {
      //
      // Get the main windows client area
      //
      GetClientRect(pVLBox->hwnd,&rcClient);
      SetWindowPos(pVLBox->hwndList, NULL, 0, 0,
         rcClient.right+(GetSystemMetrics(SM_CXBORDER)*2),
         rcClient.bottom+(GetSystemMetrics(SM_CXBORDER)*2),
         SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
  }

  VLBCountLines( pVLBox);
}



void VLBCountLines( PVLBOX pVLBox)
{
  RECT   rcClient;
  LONG   lFreeItem;

  //
  // calculate the number of lines
  //
  GetClientRect(pVLBox->hwndList,&rcClient);
  pVLBox->nLines = rcClient.bottom / pVLBox->nchHeight;

  //
  // If there is stuff already int the list box
  // update the display ( more items or fewer items now )
  //
  if ( pVLBox->lNumLogicalRecs != -2L ) {
      int nItemsinLB;

      nItemsinLB = SendMessage(pVLBox->hwndList, LB_GETCOUNT, 0, 0L);
      if ( nItemsinLB > pVLBox->nLines ) {
         // Free the items you can see.
         vlbRedrawOff(pVLBox);
         while ( nItemsinLB > pVLBox->nLines ) {
             nItemsinLB--;
             if ( pVLBox->wFlags & USEDATAVALUES ) {
                 lFreeItem = SendMessage(pVLBox->hwndList, LB_GETITEMDATA, nItemsinLB, 0L);
             }
             else {
                 lFreeItem = pVLBox->lToplIndex+nItemsinLB;
             }
             SendMessage(pVLBox->hwndParent, VLBN_FREEITEM, pVLBox->nId, lFreeItem);
             SendMessage(pVLBox->hwndList, LB_DELETESTRING, nItemsinLB, 0L);
         }
         UpdateVLBWindow(pVLBox, NULL);
         vlbRedrawOn(pVLBox);
      }
      else if ( nItemsinLB < pVLBox->nLines) {
         // Add items to fill box.
         //
         // Special case. LB can hold all the items. Jump to top.
         if ( pVLBox->lNumLogicalRecs <= pVLBox->nLines ) {
            VLBFirstPage(pVLBox);
         }
         else if ( pVLBox->wFlags & USEDATAVALUES ) {
             VLBFindPage(pVLBox, SendMessage(pVLBox->hwndList, LB_GETITEMDATA, 0, 0L), FALSE );
         }
         else {
             VLBFindPage(pVLBox, pVLBox->lToplIndex, FALSE);
         }
     }
  }
}
