/*
 * CTOOLBAR.CPP
 * Sample Code Class Libraries
 *
 * Implementation of the CToolBar class
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
 * CToolBar::CToolBar
 * CToolBar::~CToolBar
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the module we're loaded in.
 */

CToolBar::CToolBar(HINSTANCE hInst)
    : CWindow(hInst)
    {
    return;
    }


CToolBar::~CToolBar(void)
    {
    return;
    }





/*
 * CToolBar::Init
 *
 * Purpose:
 *  Initializes a toolbar object by creating the control that it
 *  owns.
 *
 * Parameters:
 *  hWndParent      HWND of the parent window.  The toolbar is
 *                  created up from the bottom of this window,
 *                  spanning the entire width of the window.
 *  uID             UINT id of the control.
 *  cy              UINT height to create the control
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CToolBar::Init(HWND hWndParent, UINT uID, UINT cy)
    {
    RECT            rc;

    /*
     * Note that the class is already registered since we live in a
     * DLL and that DLL will be loaded if anyone is using this class
     * library.
     */

    GetClientRect(hWndParent, &rc);
    m_cyBar=cy;

    m_hWnd=CreateWindow(CLASS_GIZMOBAR, TEXT("Wooley")
        , WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, rc.left, rc.top
        , rc.right-rc.left, m_cyBar, hWndParent, (HMENU)uID, m_hInst
        , 0L);

    return (NULL!=m_hWnd);
    }







/*
 * CToolBar::OnSize
 *
 * Purpose:
 *  Handles parent resizing.  The owner of this window is responsible
 *  to call this function when it wants the toolbar to resize.  The
 *  toolbar will automatically occupy a strip of the appropriate
 *  height along the top of the window.
 *
 * Parameters:
 *  hWndParent      HWND of the parent window to which we're resizing
 *
 * Return Value:
 *  None
 */

void CToolBar::OnSize(HWND hWndParent)
    {
    RECT        rc;

    GetClientRect(hWndParent, &rc);

    SetWindowPos(m_hWnd, NULL, rc.left, rc.top, rc.right-rc.left
        , m_cyBar, SWP_NOZORDER);

    return;
    }






/*
 * CToolBar::FontSet
 *
 * Purpose:
 *  Changes the font in the StatStrip.
 *
 * Parameters:
 *  hFont           HFONT of the font to use in the control.
 *  fRedraw         BOOL indicating if the control is to repaint
 *
 * Return Value:
 *  None
 */

void CToolBar::FontSet(HFONT hFont, BOOL fRedraw)
    {
    SendMessage((UINT)m_hWnd, WM_SETFONT, (WPARAM)hFont, fRedraw);
    return;
    }





/*
 * CToolBar::FontGet
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

HFONT CToolBar::FontGet(void)
    {
    return (HFONT)(UINT)SendMessage((UINT)m_hWnd, WM_GETFONT, 0, 0L);
    }






/*
 * CToolBar::Enable
 *
 * Purpose:
 *  Enables or disables the StatStrip window, graying the text if
 *  the control is disabled.
 *
 * Parameters:
 *  fEnable         BOOL specifying to enable (TRUE) or disable
 *
 * Return Value:
 *  None
 */

void CToolBar::Enable(BOOL fEnable)
    {
    EnableWindow(m_hWnd, fEnable);
    return;
    }






/*
 * CToolBar::HwndAssociateSet
 *
 * Purpose:
 *  Changes the associate window of a toolbar.
 *
 * Parameters:
 *  hWndNew         HWND of new associate.
 *
 * Return Value:
 *  HWND            Handle of previous associate.
 */

HWND CToolBar::HwndAssociateSet(HWND hWndNew)
    {
    return GBHwndAssociateSet(m_hWnd, hWndNew);
    }





/*
 * CToolBar::HwndAssociateGet
 *
 * Purpose:
 *  Retrieves the associate window of a toolbar
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HWND            Handle of current associate.
 */

HWND CToolBar::HwndAssociateGet(void)
    {
    return GBHwndAssociateGet(m_hWnd);
    }







/*
 * CToolBar::Add
 *
 * Purpose:
 *  Creates a new tool on the toolbar.  Subsequent operations
 *  should be done using the identifier, uID, for this tool.
 *
 * Parameters:
 *  iType           UINT type of the tool to create.
 *  iTool           UINT position (zero-based) for the tool.
 *  uID             UINT identifier for WM_COMMAND from this tool.
 *  dx, dy          UINT dimensions of the tool.
 *  pszText         LPTSTR initial text for edit, list, combo, text
 *  hBitmap         HBITMAP for tools of the button types (COMMAND
 *                  or ATTRIBUTE) specifies a source bitmap from
 *                  which the button image is taken.
 *  iImage          UINT index into hBitmap for the button image
 *  uState          UINT initial state of the tool.
 *
 * Return Value:
 *  BOOL            TRUE if creation succeeded, FALSE otherwise.
 */

BOOL CToolBar::Add(UINT iType, UINT iTool, UINT uID, UINT dx
    , UINT dy, LPTSTR pszText, HBITMAP hBmp, UINT iImage, UINT uState)
    {
    return GBGizmoAdd(m_hWnd, iType, iTool, uID, dx, dy
        , pszText, hBmp, iImage, uState);
    }







/*
 * CToolBar::Remove
 *
 * Purpose:
 *  Removes an existing tool from the toolbar.
 *
 * Parameters:
 *  uID             UINT identifier for this tool.
 *
 * Return Value:
 *  BOOL            TRUE if deletion succeeded, FALSE otherwise.
 */

BOOL CToolBar::Remove(UINT uID)
    {
    return GBGizmoRemove(m_hWnd, uID);
    }






/*
 * CToolBar::SendMessage
 *
 * Purpose:
 *  Implements the equivalent of SendMessage to a tool in the
 *  toolbar.  Separators, command buttons, and attribute buttons
 *  do not accept messages.
 *
 * Parameters:
 *  uID             UINT identifier of the tool to affect.
 *  iMsg            UINT message to send.
 *  wParam          WPARAM of the message.
 *  lParam          LPARAM of the message.
 *
 * Return Value:
 *  LONG            Return value from the message.  0L if the
 *                  tool does not accept messages.
 */

LONG CToolBar::SendMessage(UINT uID, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
    return GBGizmoSendMessage(m_hWnd, uID, iMsg, wParam, lParam);
    }







/*
 * CToolBar::Show
 *
 * Purpose:
 *  Shows or hides a control, adjusting the positions of all others
 *  to make room for or reuse the space for this control.
 *
 * Parameters:
 *  uID             UINT identifier of the tool to affect.
 *  fShow           BOOL TRUE to show the tool, FALSE to hide it.
 *
 * Return Value:
 *  BOOL            TRUE if the function was successful, FALSE
 *                  otherwise.
 */

BOOL CToolBar::Show(UINT uID, BOOL fShow)
    {
    return GBGizmoShow(m_hWnd, uID, fShow);
    }






/*
 * CToolBar::Enable
 *
 * Purpose:
 *  Enables or disables a control on the toolbar.
 *
 * Parameters:
 *  uID             UINT identifier of the tool to affect.
 *  fEnable         BOOL TRUE to enable the tool, FALSE otherwise.
 *
 * Return Value:
 *  BOOL            TRUE if the tool was previously disabled, FALSE
 *                  otherwise.
 */

BOOL CToolBar::Enable(UINT uID, BOOL fEnable)
    {
    return GBGizmoEnable(m_hWnd, uID, fEnable);
    }





/*
 * CToolBar::Check
 *
 * Purpose:
 *  Checks or unchecks an attribute button in the toolbar.  If the
 *  tool is part of a group of mutually exclusive attributes, then
 *  other tools are unchecked when this one is checked.  If this is
 *  the only one checked in these circumstances, this function is
 *  a NOP.
 *
 * Parameters:
 *  uID             UINT identifier of the tool to affect.
 *  fCheck          BOOL TRUE to check this tool, FALSE to uncheck.
 *
 * Return Value:
 *  BOOL            TRUE if the change took place.  FALSE otherwise.
 */

BOOL CToolBar::Check(UINT uID, BOOL fCheck)
    {
    return GBGizmoCheck(m_hWnd, uID, fCheck);
    }





/*
 * CToolBar::FocusSet
 *
 * Purpose:
 *  Sets the focus to a partuclar tool in the toolbar if that tool
 *  can accept the focus.  Separators, attribute buttons, text,
 *  and command buttons cannot have the focus.
 *
 * Parameters:
 *  uID             UINT identifier of the tool to affect.
 *
 * Return Value:
 *  BOOL            TRUE if the focus was set.  FALSE otherwise,
 *                  such as when uID identifies a control that
 *                  cannot have focus.
 *
 */

UINT CToolBar::FocusSet(UINT uID)
    {
    return GBGizmoFocusSet(m_hWnd, uID);
    }








/*
 * CToolBar::Exist
 *
 * Purpose:
 *  Determines if a tool of a given identifier exists.
 *
 * Parameters:
 *  uID             UINT identifier to verify.
 *
 * Return Value:
 *  BOOL            TRUE if the tool exists, FALSE otherwise.
 */

BOOL CToolBar::Exist(UINT uID)
    {
    return GBGizmoExist(m_hWnd, uID);
    }





/*
 * CToolBar::TypeGet
 *
 * Purpose:
 *  Returns the type of the tool specified by the given identifer.
 *
 * Parameters:
 *  uID             UINT identifier to find.
 *
 * Return Value:
 *  int             A GIZMOTYPE_* value if the function is
 *                  successful, otherwise -1.
 */

int CToolBar::TypeGet(UINT uID)
    {
    return GBGizmoTypeGet(m_hWnd, uID);
    }








/*
 * CToolBar::DataSet
 * CToolBar::DataGet
 *
 * Purpose:
 *  Sets or retrieves an extra DWORD value associated with the given
 *  tool.  Applications can store any information here they please.
 *
 * Parameters:
 *  uID             UINT identifier of the tool.
 *  dwData          (Set only) DWORD data to store with the tool.
 *
 * Return Value:
 *  DWORD           Set:  Previous value
 *                  Get:  Current value
 */

DWORD CToolBar::DataSet(UINT uID, DWORD dwData)
    {
    return GBGizmoDataSet(m_hWnd, uID, dwData);
    }


DWORD CToolBar::DataGet(UINT uID)
    {
    return GBGizmoDataGet(m_hWnd, uID);
    }





/*
 * CToolBar::NotifySet
 * CToolBar::NotifyGet
 *
 * Purpose:
 *  Sets or retrieves the notify status of a tool.  If notify is
 *  FALSE, the no WM_COMMAND messages are sent from the toolbar
 *  to the parent window when this tool is used.
 *
 * Parameters:
 *  uID             UINT identifier of the tool.
 *  fNotify         (Set only) BOOL new notify status to set.
 *
 * Return Value:
 *  BOOL            Set:  Previous value of the notify flag.
 *                  Get:  Current value of the notify flag.
 */

BOOL CToolBar::NotifySet(UINT uID, BOOL fNotify)
    {
    return GBGizmoNotifySet(m_hWnd, uID, fNotify);
    }


BOOL CToolBar::NotifyGet(UINT uID)
    {
    return GBGizmoNotifyGet(m_hWnd, uID);
    }







/*
 * CToolBar::TextSet
 * CToolBar::TextGet
 *
 * Purpose:
 *  Retrieves or sets text in a toolbar control.  Separators,
 *  command buttons, and attribute buttons are not affected by
 *  this call.
 *
 * Parameters:
 *  uID             UINT identifying the tool.
 *  psz             LPTSTR pointing to a buffer to receive the text.
 *  cch             (Get only) UINT maximum number of chars to copy
 *                  to psz.
 *
 * Return Value:
 *  int             Number of characters copied to psz.
 */

void CToolBar::TextSet(UINT uID, LPTSTR psz)
    {
    GBGizmoTextSet(m_hWnd, uID, psz);
    return;
    }


int CToolBar::TextGet(UINT uID, LPTSTR psz, UINT cch)
    {
    return GBGizmoTextGet(m_hWnd, uID, psz, cch);
    }







/*
 * CToolBar::IntSet
 * CToolBar::IntGet
 *
 * Purpose:
 *  Retrieves or sets an integer in a toolbar control.  Separators,
 *  command buttons, and attribute buttons are not affected by this
 *  call.
 *
 * Parameters:
 *  uID             UINT identifying the tool.
 *
 *  Get Parameters:
 *  pfTrans         BOOL * in which the success of the function is
 *                  returned.
 *  fSigned         BOOL TRUE to indicate if the value is signed.
 *
 *  Set Parameters:
 *  u               UINT value to set in the tool.
 *  fSigned         BOOL TRUE to indicate if the value is signed.
 *
 * Return Value:
 *  UINT            Integer translation of the tool's text.
 */

void CToolBar::IntSet(UINT uID, int i, BOOL fSigned)
    {
    GBGizmoIntSet(m_hWnd, uID, i, fSigned);
    return;
    }


UINT CToolBar::IntGet(UINT uID, BOOL *pfTrans, BOOL fSigned)
    {
    return GBGizmoIntGet(m_hWnd, uID, pfTrans, fSigned);
    }
