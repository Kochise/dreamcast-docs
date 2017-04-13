/*
 *  S M H T B . C
 *
 *  Sample mail handling hook configuration toolbar
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#include "_pch.h"
#include <richedit.h>

#ifndef WIN16
#include <commctrl.h>
#endif

/*  Maximum number of font digits */

#define cchSizeMax  16

/*  Enumeration of button bitmaps if toolbar bitmap */

enum {
    itbBold,
    itbItalic,
    itbUnderline,
    itbColor,
    ctbMax
};

/*  Gap sizes for format bar */

#define cxDownButton    16
#define cxName          (125 + cxDownButton)
#define cxSize          (40 + cxDownButton)
#define cxPlaceHolder   (cxName + 8 + cxSize + 8)
#define cxIndent        (1440 / 4)

/*  Button descriptions for format bar */

static const TBBUTTON rgtbbChar[] =
{
    { cxPlaceHolder, 0L, TBSTATE_ENABLED, TBSTYLE_SEP, {0}, 0L, -1},
    { itbColor, ID_Color, TBSTATE_ENABLED, TBSTYLE_BUTTON, {0}, 0L, -1 },
    { itbBold, ID_Bold, TBSTATE_ENABLED, TBSTYLE_CHECK, {0}, 0L, -1},
    { itbItalic, ID_Italic, TBSTATE_ENABLED, TBSTYLE_CHECK, {0}, 0L, -1},
    { itbUnderline, ID_Underline, TBSTATE_ENABLED, TBSTYLE_CHECK, {0}, 0L, -1},
};
#define ctbbChar   (sizeof(rgtbbChar) / sizeof(TBBUTTON))

/*  Color descriptions for dropdown color list */

DWORD rgrgb[] = {
    RGB(  0,   0,   0), /* Auto         */
    RGB(  0,   0,   0), /* Black        */
    RGB(128,   0,   0), /* Dark red     */
    RGB(  0, 128,   0), /* Dark green   */
    RGB(128, 128,   0), /* Dark yellow  */
    RGB(  0,   0, 128), /* Dark blue    */
    RGB(128,   0, 128), /* Dark purple  */
    RGB(  0, 128, 128), /* Dark aqua    */
    RGB(128, 128, 128), /* Dark grey    */
    RGB(192, 192, 192), /* Light grey   */
    RGB(255,   0,   0), /* Light red    */
    RGB(  0, 255,   0), /* Light green  */
    RGB(255, 255,   0), /* Light yellow */
    RGB(  0,   0, 255), /* Light blue   */
    RGB(255,   0, 255), /* Light purple */
    RGB(  0, 255, 255), /* Light aqua   */
    RGB(255, 255, 255), /* White        */
};
#define crgb    (sizeof(rgrgb) / sizeof(rgrgb[0]))
const LPTSTR rgszColor[] = {
    "Auto", "Black", "Maroon",
    "Green", "Olive", "Navy",
    "Purple", "Teal", "Gray",
    "Silver", "Red", "Lime",
    "Yellow", "Blue", "Fuchia",
    "Aqua", "White"
};

/*  Font and paragraph effects */
    
static const DWORD rgdwEffect[] = { CFE_BOLD, CFE_ITALIC, CFE_UNDERLINE };
static const WORD rgwAlign[] = { PFA_LEFT, PFA_CENTER, PFA_RIGHT };
static const UINT rglFontSize[] =
{
     8,  9, 10, 11,
    12, 14, 16, 18,
    20, 22, 24, 26,
    28, 36, 48, 72
};
#define FontSize(_y)    MulDiv((int)(_y), 72, 1440)

/*  Toolbar and combobox class names */

static const TCHAR rgchTBClass[] = "SMHToolbar";
static const TCHAR rgchComboBox[] = "ComboBox";

#ifdef  WIN16
#define GWL_USERDATA 0
#endif


/*
 *  Font, font size, and color dropdown and listing functions -----------------
 *
 *  These functions are used to fill in and display the character formats
 *  for the format bar.  The font listbox gets filled once and only once
 *  on format bar creation.  The font size listbox will get filled up each
 *  and everytime the font list gets dropped down.  The font color menu
 *  will get filled once at startup.
 */

INT CALLBACK EXPORT
EnumFontNames (LPVOID lpvLogFont,
    NEWTEXTMETRIC FAR * lpntm,
    INT nFontType,
    LPARAM lParam)
{
    UINT i;
    DWORD dw = 0;
    LOGFONT FAR * lplf = FWin4Shell()
                            ? &((ENUMLOGFONTEX FAR *)lpvLogFont)->elfLogFont
                            : (LOGFONT FAR *)lpvLogFont;

    /*  Add the face name into the listbox */

    DebugTrace ("SMH: adding font: %s%s\n", lplf->lfFaceName,
        (lpntm->tmPitchAndFamily & TMPF_TRUETYPE)
            ? " (TrueType)"
            : "");

    i = ComboBox_AddString ((HWND)lParam, lplf->lfFaceName);
    if ((i != CB_ERR) || (i != CB_ERRSPACE))
    {
        Assert (!(lplf->lfCharSet & 0xFFFFFF00));
        Assert (!(lplf->lfPitchAndFamily & 0xFFFFFF00));
        Assert (!(nFontType & 0xFFFF0000));
        dw = lplf->lfCharSet & 0xFF;
        dw <<= 8;
        dw |= lplf->lfPitchAndFamily & 0xFF;
        dw <<= 16;
        dw |= nFontType & 0xFFFF;
        ComboBox_SetItemData ((HWND)lParam, i, dw);
    }
    return TRUE;
}

void
FillFontNames (HWND hwnd)
{
    HDC hdc;

    /*  Empty the contents of the listbox and enumerate the fonts */
    
    ComboBox_ResetContent (hwnd);
    if (hdc = GetDC(NULL))
    {
        EnumFontFamilies (hdc,
            (LPTSTR)NULL,
            (FONTENUMPROC)EnumFontNames,
            (LPARAM)(LPVOID)hwnd);
        ReleaseDC (NULL, hdc);
    }
}

INT CALLBACK EXPORT
EnumFontSizes (LPVOID lpvLogFont,
    NEWTEXTMETRIC FAR * lpntm,
    INT nFontType,
    LPARAM lParam)
{
    TCHAR rgch[cchSizeMax];
    UINT i;

    if (lpntm->tmPitchAndFamily & TMPF_TRUETYPE)
    {
        /*  If the font is TrueType, then just fillin random sizes */
        
        for (i = 0; i < (sizeof(rglFontSize) / sizeof(UINT)); i++)
        {
            wsprintf (rgch, "%d", rglFontSize[i]);
            DebugTrace ("SMH: adding font size: %s\n", rgch);
            ComboBox_AddString (((LPFORMATBAR)lParam)->hwndSize, rgch);
        }
        return FALSE;
    }
    else
    {
        /*  Calculate the size of the current instance */

        wsprintf (rgch, "%d", MulDiv ((INT)lpntm->tmHeight - lpntm->tmInternalLeading, 72,
            GetDeviceCaps (((LPFORMATBAR)lParam)->hdc, LOGPIXELSY)));
        if (ComboBox_FindStringExact (((LPFORMATBAR)lParam)->hwndSize, -1, rgch) == CB_ERR)
        {
            DebugTrace ("SMH: font height: %d\n", lpntm->tmHeight - lpntm->tmInternalLeading);
            DebugTrace ("SMH: adding font size: %s\n", rgch);
            ComboBox_AddString (((LPFORMATBAR)lParam)->hwndSize, rgch);
            ((LPFORMATBAR)lParam)->cSize++;
        }
        return TRUE;
    }
}

void
FillSizes (LPFORMATBAR lpfb)
{
    TCHAR rgch[30];

    /*  Empty the contents of the listbox and enumerate the fonts */
    
    ComboBox_ResetContent (lpfb->hwndSize);
    ComboBox_GetText (lpfb->hwndFont, rgch, sizeof(rgch) - 1);

    if (lpfb->hdc = GetDC (lpfb->hwndSize))
    {
        lpfb->cSize = 0;
        EnumFontFamilies (lpfb->hdc, rgch, (FONTENUMPROC)EnumFontSizes, (LPARAM)lpfb);
        ReleaseDC (lpfb->hwndSize, lpfb->hdc);
    }
}

void CALLBACK
ColorMenu_MeasureItem (HWND hwnd, MEASUREITEMSTRUCT FAR * lpmis)
{
    LPFORMATBAR lpfb = (LPFORMATBAR)GetWindowLong (hwnd, GWL_USERDATA);
    HFONT hfnt;
    TEXTMETRIC tm;

    hfnt = SelectObject (lpfb->hdc, lpfb->hfnt);
    GetTextMetrics (lpfb->hdc, &tm);
    SelectObject (lpfb->hdc, hfnt);
    lpmis->itemHeight = tm.tmHeight;
    lpmis->itemWidth = 14 * tm.tmAveCharWidth;
    return;
}

void CALLBACK EXPORT
ColorMenu_DrawItem (HWND hwnd, DRAWITEMSTRUCT FAR * lpdis)
{
    LPFORMATBAR lpfb = (LPFORMATBAR)(GetWindowLong (hwnd, GWL_USERDATA));
    HBRUSH hbr;
    WORD dx;
    WORD dy;
    RECT rc;
    DWORD rgbBack;
    DWORD rgbText;

    if (lpdis->itemState & ODS_SELECTED)
    {
        rgbBack = SetBkColor (lpdis->hDC, GetSysColor (COLOR_HIGHLIGHT));
        rgbText = SetTextColor (lpdis->hDC, GetSysColor (COLOR_HIGHLIGHTTEXT));
    }
    else
    {
        rgbBack = SetBkColor (lpdis->hDC, GetSysColor(COLOR_WINDOW));
        rgbText = SetTextColor (lpdis->hDC, GetSysColor(COLOR_WINDOWTEXT));
    }

    ExtTextOut (lpdis->hDC,
            lpdis->rcItem.left,
            lpdis->rcItem.top,
            ETO_OPAQUE,
            &lpdis->rcItem,
            NULL, 0, NULL);

    dx = GetSystemMetrics(SM_CXBORDER);
    dy = GetSystemMetrics(SM_CYBORDER);
    rc.top = lpdis->rcItem.top + dy;
    rc.bottom = lpdis->rcItem.bottom - dy;
    rc.left = lpdis->rcItem.left + dx;
    rc.right = rc.left + 2 * (rc.bottom - rc.top);

    if (hbr = CreateSolidBrush (lpdis->itemData))
    {
        hbr = SelectObject (lpdis->hDC, hbr);
        Rectangle (lpdis->hDC, rc.left, rc.top, rc.right, rc.bottom);
        DeleteObject (SelectObject (lpdis->hDC, hbr));
    }

    DebugTrace ("SMH: color menu: painting item: %s\n",
        (LPCSTR)rgszColor[lpdis->itemID - ID_Color - 1]);
    SelectObject (lpdis->hDC, lpfb->hfnt);
    TextOut (lpdis->hDC,
        2 * dx + rc.right,
        lpdis->rcItem.top,
        rgszColor[lpdis->itemID - ID_Color - 1],
        lstrlen ((LPCSTR)rgszColor[lpdis->itemID - ID_Color - 1]));

    SetTextColor (lpdis->hDC, rgbText);
    SetBkColor (lpdis->hDC, rgbBack);
    return;
}

void
FillColors (LPFORMATBAR lpfb)
{
    UINT irgb;

    /*  Setup the auto color */

    rgrgb[0] = GetSysColor (COLOR_WINDOWTEXT);

    for (irgb = 0; irgb < crgb; irgb++)
    {
        DebugTrace ("SMH: color menu: adding item: %s (0x%08lX)\n",
            (LPCSTR)rgszColor[irgb], rgrgb[irgb]);
        AppendMenu (lpfb->hmnuColor,
            MF_ENABLED | MF_OWNERDRAW,
            ID_Color + irgb + 1,
            (LPCSTR)rgrgb[irgb]);
    }
}

/*
 *  FormatBar window proc -----------------------------------------------------
 *
 *  The formatbar window proc intercepts several window messages and
 *  processes them as needed.  The primary messages we operate on are the
 *  messages that will cause items to be redrawn or shown.
 *
 *  Additionally, WM_DESTROY is processed as for cleanup of all the
 *  formatbar components
 */

LRESULT CALLBACK EXPORT
FormatBarWndProc (HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    LPFORMATBAR lpfb = (LPFORMATBAR)GetWindowLong (hwnd, GWL_USERDATA);

    switch (msg)
    {
      case WM_COMMAND:
        
        if ((GET_WM_COMMAND_CMD (wParam, lParam) == CBN_DROPDOWN) &&
            (GET_WM_COMMAND_ID (wParam, lParam) == ID_FontSize))
            FillSizes (lpfb);
        SendMessage (GetParent(hwnd), WM_COMMAND, wParam, lParam);
        return TRUE;

      case WM_SHOWWINDOW:
        
        SendMessage (lpfb->hwndTb, msg, wParam, lParam);
        break;

      case WM_DRAWITEM:
        
        ColorMenu_DrawItem (hwnd, (DRAWITEMSTRUCT FAR *)lParam);
        return TRUE;

      case WM_MEASUREITEM:
        
        ColorMenu_MeasureItem (hwnd, (MEASUREITEMSTRUCT FAR *)lParam);
        return TRUE;

      case WM_DESTROY:
        
        DebugTrace ("SMH: destroying format bar\n");
        DestroyWindow (lpfb->hwndTb);
        DestroyWindow (lpfb->hwndFont);
        DestroyWindow (lpfb->hwndSize);
        DeleteObject (lpfb->hbrBtnFace);
        DestroyMenu (lpfb->hmnuColor);
        UlRelease (lpfb->lpreoc);
        (*lpfb->lpscd->lpfnFree) (lpfb);
        break;
    }
    return DefWindowProc (hwnd, msg, wParam, lParam);
}

/*
 *  Toolbar subclass proc -----------------------------------------------------
 *
 *  The subclassing of the toolbar is done so that the listboxes added to
 *  the toolbar will be drawn with the correct control color.
 */

LRESULT CALLBACK EXPORT
ToolbarSubclassProc (HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
    LPFORMATBAR lpfb = (LPFORMATBAR)GetWindowLong (GetParent (hwnd), GWL_USERDATA);

    switch (msg)
    {
#ifdef _WIN32
      case WM_CTLCOLORLISTBOX:
#else
      case WM_CTLCOLOR:
  
        switch (HIWORD (lParam))
        {
          case CTLCOLOR_LISTBOX:
#endif
            if (!lpfb->hbrBtnFace)
            {
                lpfb->hbrBtnFace = CreateSolidBrush (FWin4Shell()
                                                        ? GetSysColor (COLOR_WINDOW)
                                                        : GetSysColor (COLOR_BTNFACE));
            }
            return (LRESULT)(LPVOID)lpfb->hbrBtnFace;
#ifdef _WIN32
            break;
#else
            break;
        }
        break;
#endif
    }

    return CallWindowProc (lpfb->lpfnToolbar, hwnd, msg, wParam, lParam);
}

STDMETHODIMP_(SCODE)
ScCreateToolbar (LPSCD lpscd,
    HWND hwnd,
    UINT idPeg,
    BOOL fPropsheet,
    LPFORMATBAR FAR * lppfb)
{
    SCODE sc;
    RECT rc;
    RECT rcId;
    RECT rcTb;
    RECT rcCli;
    UINT x;
    UINT y;
    WNDCLASS wc = {0};
    LPFORMATBAR lpfb = NULL;

    sc = (*lpscd->lpfnAlloc) (sizeof(FORMATBAR), &lpfb);
    if (!FAILED (sc))
    {
        memset (lpfb, 0, sizeof(FORMATBAR));
        lpfb->hwndEdit = GetDlgItem (hwnd, idPeg);

        lpfb->cf.cbSize = sizeof(CHARFORMAT);
        SendMessage (lpfb->hwndEdit, EM_GETCHARFORMAT, TRUE, (LPARAM)(LPVOID)&lpfb->cf);
        lpfb->pf.cbSize = sizeof(PARAFORMAT);
        SendMessage (lpfb->hwndEdit, EM_GETPARAFORMAT, 0, (LPARAM)(LPVOID)&lpfb->pf);
        SendMessage (lpfb->hwndEdit, EM_SETEVENTMASK, 0, ENM_SELCHANGE | ENM_CHANGE);

        lpfb->cf.dwMask = CFM_FACE | CFM_SIZE | CFE_BOLD | CFE_ITALIC | CFE_UNDERLINE | CFM_COLOR;
        lpfb->cf.dwEffects = CFE_AUTOCOLOR;
        lstrcpy (lpfb->cf.szFaceName, "Arial");
        lpfb->cf.yHeight = 200;
        SendMessage (lpfb->hwndEdit, EM_SETCHARFORMAT, 0, (LPARAM)(LPVOID)&lpfb->cf);

        if (!GetClassInfo (lpscd->hinst, rgchTBClass, &wc))
        {
            wc.style = CS_HREDRAW | CS_VREDRAW;
            wc.lpfnWndProc = FormatBarWndProc;
            wc.cbWndExtra = sizeof(LPVOID);
            wc.hInstance = lpscd->hinst;
            wc.hCursor = LoadCursor (NULL, IDC_ARROW);
            wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wc.lpszClassName = (LPCTSTR)rgchTBClass;
            SideAssert (RegisterClass (&wc));
        }
        Assert (IsWindow (hwnd));
        GetWindowRect (lpfb->hwndEdit, &rcId);
        if (lpfb->hwndFrame = CreateWindow ((LPCTSTR)rgchTBClass,
                                        "SMH",
                                        WS_CHILD,
                                        0, 0, rcId.right, 30,
                                        hwnd,
                                        (HMENU)ID_Frame,
                                        lpscd->hinst,
                                        NULL))
        {

            CTL3D_SubclassCtl (lpCtl3D, lpfb->hwndFrame);

            lpfb->hmnuColor = CreatePopupMenu();
            FillColors (lpfb);

            if (lpfb->hwndTb = CreateToolbarEx (lpfb->hwndFrame,
                                        CCS_TOP | WS_CHILD,
                                        0,
                                        ctbMax,
                                        lpscd->hinst,
                                        ID_Toolbar,
                                        rgtbbChar,
                                        ctbbChar,
                                        16, 16, 16, 16,
                                        sizeof(TBBUTTON)))
            {
                lpfb->lpscd = lpscd;
                SetWindowLong (lpfb->hwndFrame, GWL_USERDATA, (ULONG)lpfb);

                /*  Move the window to where it belongs */

                GetWindowRect (hwnd, &rc);
                GetClientRect (lpfb->hwndTb, &rcTb);

                x = rcId.left - rc.left;
                y = rcId.top - rc.top - rcTb.bottom - 2;

                /*  Adjust y by any title bars and framing */

                if (!fPropsheet)
                {
                    GetClientRect (hwnd, &rcCli);
                    y -= rc.bottom - rc.top - rcCli.bottom;
                    x -= (rc.right - rc.left - rcCli.right) / 2;
                    y += (rc.right - rc.left - rcCli.right) / 2;
                }

                MoveWindow (lpfb->hwndFrame, x, y, rcId.right - rcId.left, rcTb.bottom, FALSE);

                lpfb->hfnt = (HFONT) SendMessage (lpfb->hwndTb, WM_GETFONT, 0, 0);

                lpfb->lpfnToolbar = (WNDPROC)SetWindowLong (lpfb->hwndTb,
                                        GWL_WNDPROC,
                                        (LONG)ToolbarSubclassProc);

                lpfb->hwndFont = CreateWindow ((LPCTSTR)rgchComboBox,
                                        NULL,
                                        WS_CHILD | WS_VSCROLL | CBS_DROPDOWN | CBS_SORT | WS_VISIBLE,
                                        0, 3, cxName, rcTb.bottom * 5,
                                        lpfb->hwndTb,
                                        (HMENU) ID_Font,
                                        lpscd->hinst,
                                        NULL);

                CTL3D_SubclassCtl (lpCtl3D, lpfb->hwndFont);

                SetWindowFont (lpfb->hwndFont, lpfb->hfnt, TRUE);
                ComboBox_SetExtendedUI (lpfb->hwndFont, TRUE);
                FillFontNames (lpfb->hwndFont);

                lpfb->hwndSize = CreateWindow ((LPCTSTR)rgchComboBox,
                                        NULL,
                                        WS_CHILD | WS_VSCROLL | CBS_DROPDOWN | WS_VISIBLE,
                                        cxName + 8, 3, cxSize, rcTb.bottom * 5,
                                        lpfb->hwndTb,
                                        (HMENU) ID_FontSize,
                                        lpscd->hinst,
                                        NULL);

                CTL3D_SubclassCtl (lpCtl3D, lpfb->hwndSize);

                SetWindowFont (lpfb->hwndSize, lpfb->hfnt, TRUE);
                ComboBox_SetExtendedUI (lpfb->hwndSize, TRUE);
                ComboBox_LimitText (lpfb->hwndSize, cchSizeMax);
                FillSizes (lpfb);

                UpdateFormatBar (lpfb->hwndFrame);
                ShowWindow (lpfb->hwndFrame, SW_SHOW);
                ShowWindow (lpfb->hwndTb, SW_SHOW);
            }
        }
    }
    *lppfb = lpfb;
    DebugTraceSc (ScCreateToolbar(), (lpfb->hwndFrame ? S_OK : MAPI_E_CALL_FAILED));
    return (lpfb->hwndFrame ? S_OK : MAPI_E_CALL_FAILED);
}

STDMETHODIMP_(BOOL)
FDoRTFCommand (HWND hwnd, UINT id, UINT code)
{
    LPFORMATBAR lpfb = (LPFORMATBAR)(GetWindowLong (hwnd, GWL_USERDATA));
    DWORD dw;
    RECT rc;
    UINT iSel;

    switch (id)
    {
      case ID_Font:

        if (code == CBN_SELENDOK)
        {
            FillSizes (lpfb);
            iSel = ComboBox_GetCurSel (lpfb->hwndFont);
            lpfb->cf.dwMask = CFM_FACE | CFM_CHARSET;
            ComboBox_GetLBText (lpfb->hwndFont, iSel, lpfb->cf.szFaceName);
            dw = ComboBox_GetItemData (lpfb->hwndFont, iSel);
            lpfb->cf.bPitchAndFamily = (BYTE)(dw >>= 16) & 0xFF;
            lpfb->cf.bCharSet = (BYTE)(dw >>= 8) & 0xFF;
            SendMessage (lpfb->hwndEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)(LPVOID)&lpfb->cf);
            UpdateFormatBar (lpfb->hwndFrame);
            SetFocus (lpfb->hwndEdit);
        }
        break;

      case ID_FontSize:

        if (code == CBN_SELENDOK)
        {
            UINT i;
            TCHAR rgch[cchSizeMax];

            rgch[0] = 0;
            lpfb->cf.dwMask = CFM_SIZE;
            ComboBox_GetLBText (lpfb->hwndSize,
                        ComboBox_GetCurSel (lpfb->hwndSize),
                        rgch);
            for (lpfb->cf.yHeight = 0, i = 0; rgch[i]; i++)
                lpfb->cf.yHeight = (lpfb->cf.yHeight * 10) + (rgch[i] - '0');
            lpfb->cf.yHeight *= 20;
            SendMessage (lpfb->hwndEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)(LPVOID)&lpfb->cf);
            UpdateFormatBar (lpfb->hwndFrame);
            SetFocus (lpfb->hwndEdit);
        }
        break;
        break;

      case ID_Color:

        if (lpfb->hdc = GetDC (lpfb->hwndTb))
        {
            SendMessage (lpfb->hwndTb, TB_GETITEMRECT, 1, (LPARAM) &rc);
            MapWindowPoints (lpfb->hwndTb, NULL, (LPPOINT)&rc, 2);
            TrackPopupMenu (lpfb->hmnuColor, TPM_LEFTALIGN | TPM_LEFTBUTTON,
                    rc.left, rc.bottom + 2, 0, hwnd, NULL);
            ReleaseDC (lpfb->hwndTb, lpfb->hdc);
        }
        break;

      case ID_ColorAuto:
      case ID_ColorBlack:
      case ID_ColorMaroon:
      case ID_ColorGreen:
      case ID_ColorOlive:
      case ID_ColorBlue:
      case ID_ColorPurple:
      case ID_ColorTeal:
      case ID_ColorGray:
      case ID_ColorSilver:
      case ID_ColorRed:
      case ID_ColorLime:
      case ID_ColorYellow:
      case ID_ColorNavy:
      case ID_ColorFuchia:
      case ID_ColorAqua:
      case ID_ColorWhite:

        lpfb->cf.dwMask = CFM_COLOR;
        lpfb->cf.dwEffects &= ~CFE_AUTOCOLOR;
        lpfb->cf.dwEffects |= (id == ID_ColorAuto) ? CFE_AUTOCOLOR : 0;
        lpfb->cf.crTextColor = (COLORREF)rgrgb[id - ID_Color - 1];
        SendMessage (lpfb->hwndEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)(LPVOID)&lpfb->cf);
        break;

      case ID_Bold:
      case ID_Italic:
      case ID_Underline:

        DebugTrace ("dwMask before: 0x%08lX\n", lpfb->cf.dwMask);
        DebugTrace ("dwEffects before: 0x%08lX\n", lpfb->cf.dwEffects);
        lpfb->cf.dwMask = rgdwEffect[id - ID_Bold];
        lpfb->cf.dwEffects ^= rgdwEffect[id - ID_Bold];
        DebugTrace ("dwMask after: 0x%08lX\n", lpfb->cf.dwMask);
        DebugTrace ("dwEffects after: 0x%08lX\n", lpfb->cf.dwEffects);
        SendMessage (lpfb->hwndEdit, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)(LPVOID)&lpfb->cf);
        break;

      case ID_Indent:
      case ID_Collapse:

        lpfb->pf.dwMask = PFM_STARTINDENT;
        lpfb->pf.dxStartIndent += ((id == ID_Indent) ? cxIndent : -cxIndent);
        SendMessage (lpfb->hwndEdit, EM_SETPARAFORMAT, 0, (LPARAM)(LPVOID)&lpfb->pf);
        break;

      case ID_Left:
      case ID_Center:
      case ID_Right:

        lpfb->pf.dwMask = PFM_ALIGNMENT;
        lpfb->pf.wAlignment = rgwAlign[id - ID_Left];
        SendMessage (lpfb->hwndEdit, EM_SETPARAFORMAT, 0, (LPARAM)(LPVOID)&lpfb->pf);
        break;

      case ID_Bullet:

        lpfb->pf.dwMask = PFM_NUMBERING | PFM_OFFSET;
        if (lpfb->pf.wNumbering != PFN_BULLET)
        {
            lpfb->pf.wNumbering = PFN_BULLET;
            lpfb->pf.dxOffset = cxIndent;
        }
        else
        {
            lpfb->pf.wNumbering = 0;
            lpfb->pf.dxOffset = 0;
        }
        SendMessage (lpfb->hwndEdit, EM_SETPARAFORMAT, 0, (LPARAM)(LPVOID)&lpfb->pf);
        break;

      default:

        return FALSE;
    }
    return TRUE;
}

void
UpdateFormatBar (HWND hwnd)
{
    LPFORMATBAR lpfb = (LPFORMATBAR)(GetWindowLong (hwnd, GWL_USERDATA));
    TCHAR rgch[cchSizeMax];
    UINT i;

    SendMessage (lpfb->hwndEdit, EM_GETCHARFORMAT, TRUE, (LPARAM)(LPVOID)&lpfb->cf);
    DebugTrace ("SMH: updating formatbar: format: %s%s%s\n",
        (lpfb->cf.dwEffects & rgdwEffect[0]) ? "BOLD, " : "",
        (lpfb->cf.dwEffects & rgdwEffect[1]) ? "ITALIC, " : "",
        (lpfb->cf.dwEffects & rgdwEffect[2]) ? "UNDERLINED" : "");
    DebugTrace ("SMH: updating formatbar: current font: %s\n", lpfb->cf.szFaceName);
    DebugTrace ("SMH: updating formatbar: current font height: %d\n", lpfb->cf.yHeight);
    DebugTrace ("SMH: updating formatbar: current font size: %d\n", FontSize (lpfb->cf.yHeight));
    DebugTrace ("SMH: updating formatbar: color: 0x%2X (r), 0x%2X (g), 0x%2x (b)\n",
        GetRValue (lpfb->cf.crTextColor),
        GetGValue (lpfb->cf.crTextColor),
        GetBValue (lpfb->cf.crTextColor));
        
    for (i = ID_Bold; i <= ID_Underline; i++)
        SendMessage (lpfb->hwndTb, TB_CHECKBUTTON, i,
            MAKELONG (lpfb->cf.dwEffects & rgdwEffect[i - ID_Bold], 0));

    i = ComboBox_FindString (lpfb->hwndFont, -1, lpfb->cf.szFaceName);
    if (i != (UINT)ComboBox_GetCurSel (lpfb->hwndFont))
    {
        ComboBox_SetCurSel (lpfb->hwndFont, i);
        ComboBox_SetText (lpfb->hwndFont, lpfb->cf.szFaceName);
    }

    wsprintf (rgch, "%d", FontSize (lpfb->cf.yHeight));
    i = (UINT)ComboBox_FindStringExact (lpfb->hwndSize, -1, rgch);
    if ((i != CB_ERR) || (i != (UINT)ComboBox_GetCurSel (lpfb->hwndSize)))
        ComboBox_SetCurSel (lpfb->hwndSize, i);
    ComboBox_SetText (lpfb->hwndSize, rgch);
    return;
}
