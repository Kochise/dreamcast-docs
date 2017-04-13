/*
 * STASTRIP.C
 * StatStrip Control
 *
 * Window procedure and other functions that are frequently used in
 * the life of a StatStrip.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "inoledll.h"


/*
 * StatStripWndProc
 *
 * Purpose:
 *  Window procedure for the StatStrip control.
 */

LRESULT APIENTRY StatStripWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PSTATSTRIP      pST;
    int             cyFont;
    HDC             hDC;
    LRESULT         lRet;

    pST=(PSTATSTRIP)GetWindowLong(hWnd, STATWL_STRUCTURE);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pST=(PSTATSTRIP)(void *)LocalAlloc(LPTR, CBSTATSTRIP);

            if (NULL==pST)
                return -1L;

            //Calc size of 0 point font, which we'll use as default.
            hDC=GetDC(NULL);
            cyFont=-MulDiv(10, GetDeviceCaps(hDC, LOGPIXELSY), 72);
            ReleaseDC(NULL, hDC);

            pST->hFont=CreateFont(cyFont, 0, 0, 0, FW_NORMAL, FALSE
                , FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS
                , CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY
                , VARIABLE_PITCH | FF_SWISS, TEXT("MS Sans Serif"));

            /*
             * If we could create the font, remember that we own it.
             * If font creation failed, then we'll just do with the
             * system font.
             */
            pST->fMyFont=(NULL!=pST->hFont);

            SetWindowLong(hWnd, STATWL_STRUCTURE, (LONG)pST);
            return DefWindowProc(hWnd, iMsg, wParam, lParam);


        case WM_DESTROY:
            StatStripClean(pST, TRUE);
            LocalFree((HLOCAL)(UINT)(LONG)pST);
            break;


        case WM_ERASEBKGND:
            /*
             * Eat this message to avoid erasing portions that we are
             * going to repaint in WM_PAINT.  Part of a change-state-
             * and-repaint strategy is to rely on WM_PAINT to do
             * anything visual, which includes erasing invalid
             * portions.  Letting WM_ERASEBKGND erase the background
             * is redundant.
             */
            return TRUE;


        case WM_PAINT:
            StatStripPaint(hWnd, pST);
            break;


        case WM_SETFONT:
            if (!IsWindowEnabled(hWnd))
                break;

            /*
             * wParam has the new font.  Always repaint immediately.
             * First, delete the old font only if we own it.
             */
            if (NULL!=pST->hFont && pST->fMyFont)
                DeleteObject(pST->hFont);

            //Save the new font but mark that we don't own it.
            pST->hFont=(HFONT)wParam;
            pST->fMyFont=FALSE;

            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;


        case WM_GETFONT:
            return (LRESULT)(UINT)pST->hFont;


        case WM_SETTEXT:
            if (!IsWindowEnabled(hWnd))
                break;

            //This saves the text for us, so we only have to repaint.
            lRet=DefWindowProc(hWnd, iMsg, wParam, lParam);

            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;


        case WM_ENABLE:
            //Repaint on enabling or disabling either way.
            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;


        //Control-specific messages
        case STATM_MESSAGEMAP:
            //lParam is an LPSTATMESSAGEMAPINIT
            if (0L!=lParam)
                {
                LPSTATMESSAGEMAPINIT  pMI=(LPSTATMESSAGEMAPINIT)lParam;

                return (LRESULT)StatStripMessageMap(hWnd
                    , pMI->hWndOwner, pMI->hInst, pMI->uIDRMap
                    , pMI->idsMin, pMI->idsMax, pMI->cchMax
                    , pMI->uIDPopupMin, pMI->uIDPopupMax
                    , pMI->uIDStatic, pMI->uIDBlank
                    , pMI->uIDSysMenu);
                }
            break;


        case STATM_MENUSELECT:
            //wParam and lParam from caller's WM_MENUSELECT message
            StatStripMenuSelect(hWnd, wParam, lParam);
            break;


        case STATM_MESSAGEDISPLAY:
            //wParam is ID to display
            StatStripMessageDisplay(hWnd, (USHORT)wParam);
            break;


        default:
            return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

    return 0L;
    }







/*
 * StatStripPaint
 * Internal
 *
 * Purpose:
 *  Provides drawing the StatStrip window with the 3-D effect and the
 *  current message and the current font.
 *
 * Parameters:
 *  hWnd            HWND of the window;
 *  pST             PSTATSTRIP containing control information.
 *
 * Return Value:
 *  None
 */

void StatStripPaint(HWND hWnd, PSTATSTRIP pST)
    {
    int             y;
    HDC             hDC;
    RECT            rc;
    UINT            cch;
    TCHAR           szMsg[512];
    HPEN            hPenFrame, hPenHigh;
    HFONT           hFontT;
    HBRUSH          hBr;
    COLORREF        crHighlight;
    TEXTMETRIC      tm;
    PAINTSTRUCT     ps;

    hDC=BeginPaint(hWnd, &ps);
    GetClientRect(hWnd, &rc);

    //Draw the top line using the frame color
    hPenFrame=CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWFRAME));

    if (NULL!=hPenFrame)
        {
        SelectObject(hDC, hPenFrame);
        MoveToEx(hDC, rc.left, rc.top, NULL);
        LineTo(hDC, rc.right, rc.top);
        }

    //Draw the two highlight lines
    crHighlight=GetSysColor(COLOR_BTNHIGHLIGHT);

    hPenHigh=CreatePen(PS_SOLID, 1, crHighlight);

    if (NULL!=hPenHigh)
        {
        SelectObject(hDC, hPenHigh);
        MoveToEx(hDC, rc.left, rc.bottom, NULL);
        LineTo(hDC, rc.left, rc.top+1);
        LineTo(hDC, rc.right, rc.top+1);
        }


    //Draw the face color avoiding the frame and highlight
    rc.top +=2;
    rc.left+=1;

    hBr=CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
    FillRect(hDC, &rc, hBr);
    DeleteObject(hBr);


    //Now write the text, color sensitive to the enabled state
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, GetSysColor(IsWindowEnabled(hWnd)
        ? COLOR_BTNTEXT : COLOR_BTNSHADOW));

    //Center the font vertically, accounting for borders on the rect.
    hFontT=SelectObject(hDC, pST->hFont);

    GetTextMetrics(hDC, &tm);
    y=rc.top+(((rc.bottom-rc.top)-tm.tmHeight) >> 1);
    y=max(y, rc.top);

    cch=GetWindowText(hWnd, szMsg, sizeof(szMsg));
    TextOut(hDC, 4, y, szMsg, cch);
    SelectObject(hDC, hFontT);

    //Clean up
    EndPaint(hWnd, &ps);

    DeleteObject(hPenHigh);
    DeleteObject(hPenFrame);
    return;
    }







/*
 * StatStripMenuSelect
 * External
 *
 * Purpose:
 *  Displays the appropriate message for whatever is in the
 *  parameters of a WM_MENUSELECT message.  This can only be called
 *  if StatStripMessageMap has already been called and must be used
 *  with the same menu the owner window had at the time of that call.
 *
 *  Since we're unpacking an application's messages for it, the app
 *  and this DLL must match 16-16 and 32-32 bits.
 *
 * Parameters:
 *  hWnd            HWND of the StatStrip
 *  wParam          WPARAM of the WM_MENUSELECT message.
 *  lParam          LPARAM of the WM_MENUSELECT message.
 *
 * Return Value:
 *  None
 */

void WINAPI StatStripMenuSelect(HWND hWnd, WPARAM wParam
    , LPARAM lParam)
    {
    PSTATSTRIP      pST;
    USHORT          uID;

    MENUSELECTPARAMS(wItem, wMenuFlags, hMenu);

    if (!IsWindow(hWnd) || !IsWindowEnabled(hWnd))
        return;

    pST=(PSTATSTRIP)GetWindowLong(hWnd, STATWL_STRUCTURE);

    //Case 1:  Menu was cancelled, display static string
    if (0==wItem && 0xFFFF==wMenuFlags)
        uID=pST->uIDStatic;
    else
        //Case 2:  System menu selected by itself.
        if (MF_POPUP & wMenuFlags && MF_SYSMENU & wMenuFlags)
            uID=pST->uIDSysMenu;
        else
            /*
             * Case 3:  A popup menu was chosen:  Find the ID for
             * hMenu (in wItem)
             */
            if (MF_POPUP & wMenuFlags)
                uID=IDFromHMenu(pST, (HMENU)wItem);
            else
                //Case 4:  A menu item is selected
                if (0!=wItem)
                    uID=(UINT)wItem;
                else
                    //Case 5:  Nothing is selected (like a separator)
                    uID=pST->uIDBlank;


    /*
     * Go display the message.  Since all this function does extra
     * that we may not have to do here is a GetWindowLong, which
     * is quick, so by doing this we keep the code in one place and
     * only have to test this API to test the other.
     */
    StatStripMessageDisplay(hWnd, uID);
    return;
    }






/*
 * StatStripMessageDisplay
 * External
 *
 * Purpose:
 *  Displays the appropriate message for a given ID value.   This can
 *  only be called if StatStripMessageMap has already been called.
 *
 * Parameters:
 *  hWnd            HWND of the StatStrip
 *  uID             USHORT of the message to display.
 *
 * Return Value:
 *  None
 */

void WINAPI StatStripMessageDisplay(HWND hWnd, USHORT uID)
    {
    PSTATSTRIP      pST;
    UINT            idsMsg;

    if (!IsWindow(hWnd) || !IsWindowEnabled(hWnd))
        return;

    pST=(PSTATSTRIP)GetWindowLong(hWnd, STATWL_STRUCTURE);

    //Go look up the string ID to display.
    idsMsg=IStringFromID(pST->pSMM, pST->cMessages, uID);
    SetWindowText(hWnd, pST->ppsz[idsMsg-pST->idsMin]);
    return;
    }






/*
 * IDFromHMenu
 *
 * Purpose:
 *  Given a specific menu handle, searches through pST->pPMM for a
 *  match and returns the ID associated with that menu.
 *
 * Parameters:
 *  pST             PSTATSTRIP of the control
 *  hMenu           HMENU to search for
 *
 * Return Value:
 *  USHORT          ID associated with the menu handle.
 */

USHORT IDFromHMenu(PSTATSTRIP pST, HMENU hMenu)
    {
    USHORT      uID=pST->uIDBlank;      //Default is empty
    UINT        i;

   #ifdef WIN32
    /*
     * Under Win32 the hMenu passed here from the WM_MENUSELECT
     * message will only be the index to the actual menu.  We
     * have to use GetSubMenu from the top-level menu using this
     * index to actually get the menu handle.
     */

    hMenu=GetSubMenu(GetMenu(pST->hWndOwner), (UINT)hMenu);
   #endif

    for (i=0; i < pST->cPopups; i++)
        {
        if (pST->pPMM[i].hMenu==hMenu)
            {
            uID=pST->pPMM[i].uID;
            break;
            }
        }

    return uID;
    }







/*
 * IStringFromID
 *
 * Purpose:
 *  Performs a binary search in a STATMESSAGEMAP array looking for
 *  a specific item ID returning the string ID for that item.
 *
 * Parameters:
 *  pSMM            PSTATMESSAGEMAP to search
 *  cItems          USHORT size of the map in elements
 *  uID             USHORT item ID to locate.
 *
 * Return Value:
 *  UINT            String ID associated with wItem.
 */

UINT IStringFromID(PSTATMESSAGEMAP pSMM, USHORT cItems, USHORT uID)
    {
    UINT        iLow =0;
    UINT        iHigh=cItems-1;
    UINT        iMid;

    while (TRUE)
        {
        iMid=(iLow+iHigh) >> 1;

        if (uID < pSMM[iMid].uID)
            iHigh=iMid-1;
        else
            {
            if (uID > pSMM[iMid].uID)
                iLow=iMid+1;
            else
                break;    //Equality
            }

        if (iHigh < iLow)
            break;
        }

    return pSMM[iMid].idsMsg;
    }




/*
 * StatStripMessageMap
 *
 * Purpose:
 *  Initializes the message mappings in the StatStrip for subsequent
 *  use with StatMessageMenuSelect.  If this function is called more
 *  than once then any previous initialization is cleaned up so
 *  previous message IDs will then be invalid.
 *
 *  The total number of messages is inferred by (idsMax-idsMin+1).
 *  The maximum number of popup menu items we'll hold is inferred by
 *  (uIDPopupMax-uIDPopupMin+1).
 *
 * Parameters:
 *  hWnd            HWND of the StatStrip control.
 *  hWndOwner       HWND of the window owning menus.
 *  hInst           HINSTANCE of the app from which to load resources
 *  uIDRMap         UINT identifying a resource mapping ID values
 *                  to string ID values.
 *  idsMin          UINT specifying the lowest string ID to load.
 *  idsMax          UINT specifying the hightest string ID to load.
 *  cchMax          UINT maximum string length.
 *  uIDPopupMin     USHORT lowest ID to assign to popup menus.
 *  uIDPopupMax     USHORT highest ID to assign to popup menus.
 *  uIDStatic       USHORT ID for the quiescent message.
 *  uIDBlank        USHORT ID for a blank message.
 *  uIDSysMenu      USHORT ID for the system menu.
 *
 * Return Value:
 *  BOOL            TRUE if the function was successful, FALSE
 *                  otherwise.
 */

BOOL WINAPI StatStripMessageMap(HWND hWnd, HWND hWndOwner
    , HINSTANCE hInst , UINT uIDRMap, UINT idsMin, UINT idsMax
    , UINT cchMax, USHORT uIDPopupMin, USHORT uIDPopupMax
    , USHORT uIDStatic, USHORT uIDBlank, USHORT uIDSysMenu)
    {
    PSTATSTRIP      pST;
    HMENU           hMenu;
    HRSRC           hRes;
    UINT            i;
    USHORT          uID;

   #ifdef WIN32
    DWORD           cbRes;
    DWORD           dwPrevProt;
   #endif

    if (!IsWindow(hWnd))
        return FALSE;

    pST=(PSTATSTRIP)GetWindowLong(hWnd, STATWL_STRUCTURE);

    if (NULL==pST)
        return FALSE;

    //Parameter validation
    if (NULL==hInst || idsMax < idsMin || uIDPopupMax < uIDPopupMin)
        return FALSE;

    //Clean ourselves out if we've already initialized.
    if (pST->fMapped)
        StatStripClean(pST, FALSE);

    pST->hWndOwner  =hWndOwner;

    pST->idsMin     =idsMin;
    pST->idsMax     =idsMax;
    pST->cMessages  =(USHORT)(idsMax-idsMin+1);

    pST->uIDPopupMin=uIDPopupMin;
    pST->uIDPopupMax=uIDPopupMax;
    pST->cPopups    =(USHORT)(uIDPopupMax-uIDPopupMin+1);

    pST->uIDStatic  =uIDStatic;
    pST->uIDBlank   =uIDBlank;
    pST->uIDSysMenu =uIDSysMenu;

    //Load the STATMESSAGEMAP array from our resources.
    hRes=FindResource(hInst, MAKEINTRESOURCE(uIDRMap), RT_RCDATA);

    if (NULL==hRes)
        return FALSE;


    pST->hMemSMM=LoadResource(hInst, hRes);

    if (NULL==pST->hMemSMM)
        return FALSE;

    pST->pSMM=(PSTATMESSAGEMAP)LockResource(pST->hMemSMM);

    if (NULL==pST->pSMM)
        {
        StatStripClean(pST, FALSE);
        return FALSE;
        }

   #ifdef WIN32
    /*
     * In Win32 resource pages are read-only when loaded.
     * Change to read-write for the purposes of sorting
     * initially.
     */
    cbRes=SizeofResource(hInst, hRes);
    VirtualProtect(pST->pSMM, cbRes, PAGE_READWRITE, &dwPrevProt);
   #endif

    //Sort these for binary search lookup.
    StatMessageMapSort(pST->pSMM, pST->cMessages);

   #ifdef WIN32
    VirtualProtect(pST->pSMM, cbRes, dwPrevProt, &dwPrevProt);
   #endif

    //Allocate space for string pointers
    pST->ppsz=(LPTSTR *)LocalAlloc(LPTR
        , sizeof(LPTSTR)*pST->cMessages);

    if (NULL==pST->ppsz)
        {
        StatStripClean(pST, FALSE);
        return FALSE;
        }

    //Load the stringtable for messages.
    pST->hMemSzStat=HStringCache(hInst, idsMin, idsMax, cchMax
        , pST->ppsz);

    if (NULL==pST->hMemSzStat)
        {
        StatStripClean(pST, FALSE);
        return FALSE;
        }

    //Allocate an array of POPUPMENUMAP structures
    pST->pPMM=(PPOPUPMENUMAP)(void *)LocalAlloc(LPTR
        , sizeof(POPUPMENUMAP)*pST->cPopups);

    if (NULL==pST->pPMM)
        {
        StatStripClean(pST, FALSE);
        return FALSE;
        }

    //Initialize the array mapping popup menus to specific IDs.
    uID=uIDPopupMin;
    hMenu=GetMenu(hWndOwner);

    for (i=0; i < pST->cPopups; i++)
        {
        pST->pPMM[i].hMenu=GetSubMenu(hMenu, i);
        pST->pPMM[i].uID  =uID++;
        }

    pST->fMapped=TRUE;
    return TRUE;
    }







/*
 * StatStripClean
 *
 * Purpose:
 *  Cleans out any allocations in a STATSTRIP.
 *
 * Parameters:
 *  pST             PSTATSTRIP to clean
 *  fIncludeFont    BOOL indicates if we're to also clean the font.
 *                  This is FALSE from StatMessageMap, TRUE from
 *                  WM_DESTROY.
 *
 * Return Value:
 *  None
 */

void StatStripClean(PSTATSTRIP pST, BOOL fIncludeFont)
    {
    //Free up anything from StatMessageMap
    if (NULL!=pST->pPMM)
        {
        LocalFree((HLOCAL)(UINT)(LONG)pST->pPMM);
        pST->pPMM=NULL;
        }

    if (NULL!=pST->ppsz)
        {
        LocalFree((HLOCAL)(UINT)(LONG)pST->ppsz);
        pST->ppsz=NULL;
        }

    if (NULL!=pST->hMemSzStat)
        {
        HStringCacheFree(pST->hMemSzStat);
        pST->hMemSzStat=NULL;
        }

    if (NULL!=pST->pSMM)
        {
       #ifndef WIN32
        UnlockResource(pST->hMemSMM);
       #endif
        pST->pSMM=NULL;
        }

    if (NULL!=pST->hMemSMM)
        {
        FreeResource(pST->hMemSMM);
        pST->hMemSMM=NULL;
        }

    //Delete the old font only if we own it.
    if (fIncludeFont)
        {
        if (NULL!=pST->hFont && pST->fMyFont)
            {
            DeleteObject(pST->hFont);
            pST->hFont=NULL;
            }
        }

    return;
    }





/*
 * HStringCache
 *
 * Purpose:
 *  Allocates memory and reads a stringtable into that memory.
 *  Pointers to the strings in the memory are then stored at ppsz
 *  which is assumed to be (idsMax-idsMin+1) strings long.
 *
 * Parameters:
 *  hInst           HINSTANCE of the application
 *  idsMin          UINT string index to start loading
 *  idsMax          UINT maximum string index in this table.
 *  cchMax          UINT length of the longest string in TCHARs.
 *  ppsz            LPTSTR * to an array in which to store pointers.
 *
 * Return Value:
 *  HGLOBAL         Handle to the memory.  NULL if memory could
 *                  not be allocated.
 */

HGLOBAL HStringCache(HINSTANCE hInst, UINT idsMin, UINT idsMax
    , UINT cchMax, LPTSTR *ppsz)
    {
    HANDLE      hMem;
    LPTSTR      pch;
    UINT        cchUsed=0;
    UINT        cch;
    UINT        i, cStrings;

    cStrings=idsMax-idsMin+1;
    hMem=GlobalAlloc(GHND, cStrings * cchMax * sizeof(TCHAR));

    if (NULL!=hMem)
        {
        pch=GlobalLock(hMem);

        /*
         * Load the strings into the memory and retain the specific
         * pointer to that string.
         */
        for (i=0; i < cStrings; i++)
            {
            cch=LoadString(hInst, i+idsMin, (LPTSTR)(pch+cchUsed)
                , cchMax-1);
            ppsz[i]=(LPTSTR)(pch+cchUsed);

            /*
             * Add one char to cch to include a NULL.  The memory
             * was ZEROINITed on allocation so by skipping a TCHAR
             * we get the NULL.
             */
            cchUsed+=cch+sizeof(TCHAR);
            }

        /*
         * Memory is locked for the duration of the app.  Don't
         * bother reallocating since we might have to recalc
         * all the pointers to the strings again.
         */
        }

    return hMem;
    }





/*
 * HStringCacheFree
 *
 * Purpose:
 *  Frees up any memory associated with the string cache from
 *  HStringCache.
 *
 * Parameters:
 *  hMem            HGLOBAL to the memory containing the cahce.
 *
 * Return Value:
 *  None
 */

void HStringCacheFree(HGLOBAL hMem)
    {
    if (NULL!=hMem)
        {
        GlobalUnlock(hMem);
        GlobalFree(hMem);
        }
    return;
    }





/*
 * StatMessageMapSort
 *
 * Purpose:
 *  Performs a selection sort on the STATMESSAGEMAP array that we
 *  load from our resource.  Since we expect that the data is
 *  partially sorted (we tend to place things in resources in groups
 *  of seqential values), since the number of messages is usually
 *  < 200, and since we're in startup (which takes a long time
 *  anyway), selection sort is a better choice to implement over
 *  qsort saving much code.
 *
 * Parameters:
 *  pSMM            PSTATMESSAGEMAP to sort
 *  n               USHORT number of elements in the array.
 *
 * Return Value:
 *  None
 */

void StatMessageMapSort(PSTATMESSAGEMAP pSMM, USHORT n)
    {
    USHORT          i, j, k;
    STATMESSAGEMAP  smm;

    for (j=0; j < (UINT)(n-1); j++)
        {
        k=j;
        smm.uID   =pSMM[j].uID;
        smm.idsMsg=pSMM[j].idsMsg;

        for (i=j+1; i < (UINT)n; i++)
            {
            if (pSMM[i].uID < smm.uID)
                {
                smm.uID   =pSMM[i].uID;
                smm.idsMsg=pSMM[i].idsMsg;
                k=i;
                }
            }

        smm.uID       =pSMM[j].uID;
        smm.idsMsg    =pSMM[j].idsMsg;
        pSMM[j].uID   =pSMM[k].uID;
        pSMM[j].idsMsg=pSMM[k].idsMsg;
        pSMM[k].uID   =smm.uID;
        pSMM[k].idsMsg=smm.idsMsg;
        }

    return;
    }
