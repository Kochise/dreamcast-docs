/*
 * CSTATLIN.C
 * Sample Code Class Libraries
 *
 * C++ wrapper class for a status line control
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include <windows.h>
#include "classlib.h"


/*
 * CStatusLine::CStatusLine
 * CStatusLine::~CStatusLine
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the module we're loaded in.
 */

CStatusLine::CStatusLine(HINSTANCE hInst)
    : CWindow(hInst)
    {
    return;
    }


CStatusLine::~CStatusLine(void)
    {
    return;
    }






/*
 * CStatusLine::Init
 *
 * Purpose:
 *  Initializes a status line object by creating the control that it
 *  owns.
 *
 * Parameters:
 *  hWndParent      HWND of the parent window.  The status line is
 *                  created up from the bottom of this window,
 *                  spanning the entire width of the window.
 *  uID             UINT id of the control.
 *  cy              UINT height to create the control
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CStatusLine::Init(HWND hWndParent, UINT uID, UINT cy)
    {
    RECT        rc;

    GetClientRect(hWndParent, &rc);

    m_cy=cy;
    m_hWnd=CreateWindow(CLASS_STATSTRIP, TEXT("Ready")
        , WS_CHILD | WS_VISIBLE, rc.left, rc.top, rc.right-rc.left
        , cy , hWndParent, (HMENU)uID, m_hInst, 0L);

    return (NULL!=m_hWnd);
    }






/*
 * CStatusLine::OnSize
 *
 * Purpose:
 *  Handles parent resizing.  The owner of this window is responsible
 *  to call this function when it wants the status line to resize.  The
 *  status line will automatically occupy a lower strip of CYSTATSTRIP
 *  high on the bottom of the window.
 *
 * Parameters:
 *  hWndParent      HWND of the parent window to which we're resizing
 *
 * Return Value:
 *  None
 */

void CStatusLine::OnSize(HWND hWndParent)
    {
    RECT        rc;

    GetClientRect(hWndParent, &rc);

    SetWindowPos(m_hWnd, NULL, rc.left, rc.bottom-rc.top-CYSTATSTRIP
        , rc.right-rc.left, m_cy, SWP_NOZORDER);

    return;
    }







/*
 * CStatusLine::MessageSet
 *
 * Purpose:
 *  Sets a message in the status line explicitly with a string.
 *
 * Parameters:
 *  pszMsg          LPTSTR to the string to display.
 *
 * Return Value:
 *  None
 */

void CStatusLine::MessageSet(LPTSTR psz)
    {
    SetWindowText(m_hWnd, psz);
    return;
    }





/*
 * CStatusLine::MessageGet
 *
 * Purpose:
 *  Retrieves the current message from the status line
 *
 * Parameters:
 *  psz             LPTSTR in which to return the message.
 *  cchMax          UINT maximum number of characters to copy.
 *
 * Return Value:
 *  UINT            Number of characters copied.
 */

UINT CStatusLine::MessageGet(LPTSTR psz, UINT cchMax)
    {
    return GetWindowText(m_hWnd, psz, cchMax);
    }






/*
 * CStatusLine::MessageGetLength
 *
 * Purpose:
 *  Returns the length of the current message in the status line.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Number of characters in the current message
 */

UINT CStatusLine::MessageGetLength(void)
    {
    return GetWindowTextLength(m_hWnd);
    }






/*
 * CStatusLine::FontSet
 *
 * Purpose:
 *  Changes the font in the status line.
 *
 * Parameters:
 *  hFont           HFONT of the font to use in the control.
 *  fRedraw         BOOL indicating if the control is to repaint or
 *                  not.
 *
 * Return Value:
 *  None
 */

void CStatusLine::FontSet(HFONT hFont, BOOL fRedraw)
    {
    SendMessage(m_hWnd, WM_SETFONT, (WPARAM)hFont, fRedraw);
    return;
    }





/*
 * CStatusLine::FontGet
 *
 * Purpose:
 *  Retrieves the handle of the current font used in the control.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HFONT           Handle to the current font.
 */

HFONT CStatusLine::FontGet(void)
    {
    return (HFONT)(UINT)SendMessage(m_hWnd, WM_GETFONT, 0, 0L);
    }





/*
 * CStatusLine::Enable
 *
 * Purpose:
 *  Enables or disables the status line window, graying the text if
 *  the control is disabled.
 *
 * Parameters:
 *  fEnable         BOOL specifying to enable (TRUE) or disable
 *
 * Return Value:
 *  None
 */

void CStatusLine::Enable(BOOL fEnable)
    {
    EnableWindow(m_hWnd, fEnable);
    return;
    }





/*
 * CStatusLine::MessageMap
 *
 * Purpose:
 *  Initializes a CStatusLine for automated processing of
 *  WM_MENUSELECT messages as well as setting up a list of messages
 *  that we can display using identifiers instead of string
 *  pointers.  See MenuSelect and MessageDisplay members.
 *
 * Parameters:
 *  hWnd            HWND of the window owning menus.
 *  hInst           HINSTANCE of the app from which to load resources
 *  uIDRMap         UINT identifying a resource mapping ID values to
 *                  string ID values.
 *  idsMin          UINT specifying the lowest string ID to load.
 *  idsMax          UINT specifying the hightest string ID to load.
 *  cchMax          UINT maximum string length.
 *  uIDPopupMin     UINT lowest ID to assign to popup menus.
 *  uIDPopupMax     UINT highest ID to assign to popup menus.
 *  uIDStatic       UINT ID for the quiescent message.
 *  uIDBlank        UINT ID for a blank message.
 *  uIDSysMenu      UINT ID for the system menu.
 *
 * Return Value:
 *  BOOL            TRUE if the function was successful, FALSE
 *                  otherwise.
 */

BOOL CStatusLine::MessageMap(HWND hWnd, HINSTANCE hInst, UINT uIDRMap
    , UINT idsMin, UINT idsMax, UINT cchMax, UINT uIDPopupMin
    , UINT uIDPopupMax, UINT uIDStatic, UINT uIDBlank
    , UINT uIDSysMenu)
    {
    //Initialize all the messages in the status line
    return StatStripMessageMap(m_hWnd, hWnd, hInst, uIDRMap, idsMin
        , idsMax, cchMax, uIDPopupMin, uIDPopupMax, uIDStatic
        , uIDBlank, uIDSysMenu);
    }






/*
 * CStatusLine::MenuSelect
 *
 * Purpose:
 *  Displays the appropriate message for whatever is in the
 *  parameters of a WM_MENUSELECT message.  This can only be called
 *  if StatStripMessageMap has already been called and must be used
 *  with the same menu the owner window had at the time of that call.
 *
 * Parameters:
 *  wParam          WPARAM of the WM_MENUSELECT message.
 *  lParam          LPARAM of the WM_MENUSELECT message.
 *
 * Return Value:
 *  None
 */

void CStatusLine::MenuSelect(WPARAM wParam, LPARAM lParam)
    {
    StatStripMenuSelect(m_hWnd, wParam, lParam);
    return;
    }





/*
 * CStatusLine::MessageDisplay
 *
 * Purpose:
 *  Displays the appropriate message for a given ID value.   This can
 *  only be called if StatStripMessageMap has already been called.
 *
 * Parameters:
 *  uID             UINT of the message to display.
 *
 * Return Value:
 *  None
 */

void CStatusLine::MessageDisplay(UINT uID)
    {
    StatStripMessageDisplay(m_hWnd, uID);
    return;
    }
