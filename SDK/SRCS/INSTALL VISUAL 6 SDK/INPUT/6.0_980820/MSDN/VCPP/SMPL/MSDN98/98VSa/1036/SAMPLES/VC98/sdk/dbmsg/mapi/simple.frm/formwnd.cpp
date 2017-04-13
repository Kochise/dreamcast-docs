/***********************************************************************
 *
 *  FORMWND.CPP
 *
 *
 *  Copyright 1986-1996 Microsoft Corporation.  All Rights Reserved.
 *
 ***********************************************************************/

#include        "precomp.h"

BOOL CALLBACK
AboutDlgProc (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

//WM_SIZE handler
void ON_Size(HWND hwnd, UINT state, int x, int y)
{
    CBaseForm * pform = (CBaseForm *) GetWindowLong(hwnd, 0);

    SetWindowPos(pform->m_hwndDialog, NULL, 0, 0, x, y,
              SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
} 


////  A specialized version of the window proc which plays how messages
//      are going to be handled.
//   


////

BOOL CALLBACK FormDlgProcSend(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    CBaseForm *         pfrm;
    RECT                rect;
    int                 wmId;
    int                 wmEvent;
    
    
    pfrm = (CBaseForm *) GetWindowLong(GetParent(hdlg), 0);
    
    switch ( msg ) {
    case WM_INITDIALOG:
        GetWindowRect(hdlg, &rect);
        pfrm->SetMinSize(rect.right - rect.left,
                         rect.bottom - rect.top +
                         GetSystemMetrics(SM_CYCAPTION) +
                         GetSystemMetrics(SM_CYMENU));
        break;

    case WM_SIZE:
        {
            HWND        hwnd;
            RECT        rect;
            int         cx;
            int         cy;
            
            //resize edit to match the dialog
            GetWindowRect(hdlg, &rect);
            cx = rect.right;
            cy = rect.bottom;

            HDWP hdwp = BeginDeferWindowPos(4);
            if(NULL == hdwp)
                break;
            
            hwnd = GetDlgItem(hdlg, ID_TO);
            GetWindowRect(hwnd, &rect);
            if(NULL == DeferWindowPos(hdwp, hwnd, NULL, 0, 0, cx - rect.left - 2,
                         rect.bottom - rect.top, SWP_NOACTIVATE | SWP_NOMOVE |
                         SWP_NOZORDER))
            {
                break;
            }

            hwnd = GetDlgItem(hdlg, ID_CC);
            GetWindowRect(hwnd, &rect);
            if(NULL == DeferWindowPos(hdwp, hwnd, NULL, 0, 0, cx - rect.left - 2,
                         rect.bottom - rect.top, SWP_NOACTIVATE | SWP_NOMOVE |
                         SWP_NOZORDER))
            {
                break;
            }

            hwnd = GetDlgItem(hdlg, ID_SUBJECT);
            GetWindowRect(hwnd, &rect);
            if(NULL == DeferWindowPos(hdwp, hwnd, NULL, 0, 0, cx - rect.left - 2,
                         rect.bottom - rect.top, SWP_NOACTIVATE | SWP_NOMOVE |
                         SWP_NOZORDER))
            {
                break;
            }

            hwnd = GetDlgItem(hdlg, ID_BODY);
            GetWindowRect(hwnd, &rect);
            if(NULL == DeferWindowPos(hdwp, hwnd, NULL, 0, 0, cx - rect.left, cy - rect.top,
                         SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER))
            {
                break;
            }

            EndDeferWindowPos(hdwp);
        }
        break;

    case WM_COMMAND:
        wmId = GET_WM_COMMAND_ID(wParam, lParam);  
        wmEvent = GET_WM_COMMAND_CMD(wParam, lParam);

        switch(wmId) {
        case ID_TO_BUTTON:
        case ID_CC_BUTTON:
            switch (wmEvent) {
            case BN_CLICKED:
                pfrm->Address(wmId);
                break;

            default:
                return FALSE;
            }
            break;
        case ID_BODY:
        {
            HMENU hMenu = GetMenu(GetParent(hdlg));
            if(wmEvent == EN_KILLFOCUS)
            {
                EnableMenuItem(hMenu, IDC_EDIT_CUT, MF_BYCOMMAND|MF_GRAYED);
                EnableMenuItem(hMenu, IDC_EDIT_COPY, MF_BYCOMMAND|MF_GRAYED);
                EnableMenuItem(hMenu, IDC_EDIT_PASTE, MF_BYCOMMAND|MF_GRAYED);
                EnableMenuItem(hMenu, IDC_EDIT_UNDO, MF_BYCOMMAND|MF_GRAYED);
            }
            else if(wmEvent == EN_SETFOCUS)
            {
                EnableMenuItem(hMenu, IDC_EDIT_CUT, MF_BYCOMMAND);
                EnableMenuItem(hMenu, IDC_EDIT_COPY, MF_BYCOMMAND);
                EnableMenuItem(hMenu, IDC_EDIT_PASTE, MF_BYCOMMAND);
                EnableMenuItem(hMenu, IDC_EDIT_UNDO, MF_BYCOMMAND);
            }
        }
        break;
        case ID_SUBJECT:
            if (wmEvent == EN_KILLFOCUS) {
                char    sz[250];

                if (Edit_GetText(GET_WM_COMMAND_HWND(wParam, lParam), sz, 200)) {
                    lstrcat(sz, " - ");
                    lstrcat(sz, g_szWindowCaption);
                    SetWindowText(GetParent(hdlg), sz);
                }
                else
                    SetWindowText(GetParent(hdlg), g_szWindowCaption);

                break;
            }
            return FALSE;

        default:
            return FALSE;
        }
        
    default:
        return FALSE;
    }

    return TRUE;
}

//// Window proc for frame window of both the read and send form.
//   
//  Send frame window does not receive IDC_VIEW_ITEMABOVE, IDC_VIEW_ITEMBELOW
// commands.
// Read frame window does not receive IDC_MESSAGE_SUBMIT command.
LRESULT CALLBACK WndProcForm(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HMENU               hMenu;
    CBaseForm *         pform;
    int                 wmId;
    int                 wmEvent;

    pform = (CBaseForm *) GetWindowLong(hwnd, 0);
    
    switch( msg ) {
    case WM_COMMAND:
        wmId = GET_WM_COMMAND_ID(wParam, lParam);  
        wmEvent = GET_WM_COMMAND_CMD(wParam, lParam);

        switch( wmId ) {
        case IDC_MESSAGE_CLOSE:
            pform->ShutdownForm(SAVEOPTS_PROMPTSAVE);
            break;

        case IDC_MESSAGE_SAVE:
            pform->DoSave();
            break;
        
        case IDC_VIEW_ITEMABOVE:
        case IDC_VIEW_ITEMBELOW:
            {
                ULONG ulDir = IDC_VIEW_ITEMABOVE == wmId ? VCDIR_PREV:VCDIR_NEXT;
                pform->DoNext(ulDir);
                
                break;
            }
        case IDC_MESSAGE_DELETE:
            pform->DoDelete();
            break;
        
        case IDC_MESSAGE_REPLY:
            pform->DoReply(eREPLY);
            break;

        case IDC_MESSAGE_FORWARD:
            pform->DoReply(eFORWARD);
            break;

        case IDC_MESSAGE_SUBMIT:
            pform->DoSubmit();
            break;
            
        case IDC_MESSAGE_COPY:
            pform->DoCopy();
            break;

        case IDC_MESSAGE_MOVE:
            pform->DoMove();
            break;
            
        //the edit menu commands are enabled only if the ID_BODY text
        //box has the focus
        case IDC_EDIT_COPY:
            SendMessage(GetDlgItem(pform->m_hwndDialog, ID_BODY), WM_COPY, 0,0);
            break;
        case IDC_EDIT_CUT:
            SendMessage(GetDlgItem(pform->m_hwndDialog, ID_BODY), WM_CUT, 0,0);
            break;
        case IDC_EDIT_PASTE:
            SendMessage(GetDlgItem(pform->m_hwndDialog, ID_BODY), WM_PASTE, 0,0);
            break;
        case IDC_EDIT_UNDO:
            SendMessage(GetDlgItem(pform->m_hwndDialog, ID_BODY), WM_UNDO, 0,0);
            break;

        case IDC_HELP_ABOUT:
            DialogBox (g_hinst, "AboutBox", hwnd, AboutDlgProc);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        break;

        //
        //  Do all of the correct menu graying
        //
    case WM_INITMENU:
        hMenu = (HMENU) wParam;
        pform->ConfigMenu(hMenu);
   break;
        
        //
        //  Deal with the System Close message
        //
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_CLOSE)
        {
            pform->ShutdownForm(SAVEOPTS_PROMPTSAVE);
        }
        else
        {
            goto DoDefault;
        }
        break;

    case WM_SETFOCUS:
        SetFocus(pform->m_hwndDialog);
        break;

        //
        //  Let the object know that the window has been destroyed so 
        //      that it will not talk to it any more
        //
    case WM_DESTROY:
        pform->ClearWindow();
        goto DoDefault;

    case WM_SIZE:
        HANDLE_WM_SIZE(hwnd, wParam, lParam, ON_Size); 
        goto DoDefault;
        
        
    default:
DoDefault:
        return DefWindowProc (hwnd, msg, wParam, lParam);
    }

    return 0;
}


////

BOOL CALLBACK FormDlgProcRead(HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    CBaseForm *         pfrm;
    RECT                rect;
    int                 wmId;
    int                 wmEvent;
    
    pfrm = (CBaseForm *) GetWindowLong(GetParent(hdlg), 0);
    
    switch ( msg ) {
    case WM_INITDIALOG:
        {
            Assert(pfrm);

            GetWindowRect(hdlg, &rect);
            pfrm->SetMinSize(rect.right - rect.left,
                            rect.bottom - rect.top +
                            GetSystemMetrics(SM_CYCAPTION) +
                            GetSystemMetrics(SM_CYMENU));
            break;
        }                                                   
    
    case WM_SIZE:
        {
            HWND        hwnd;
            RECT        rect;
            int         cx;
            int         cy;

            GetWindowRect(hdlg, &rect);
            cx = rect.right;
            cy = rect.bottom;

            HDWP hdwp = BeginDeferWindowPos(5);
            if(NULL == hdwp)
                break;

            hwnd = GetDlgItem(hdlg, ID_FROM);
            GetWindowRect(hwnd, &rect);
            if(NULL == DeferWindowPos(hdwp, hwnd, NULL, 0, 0, cx - rect.left - 2,
                         rect.bottom - rect.top, SWP_NOACTIVATE | SWP_NOMOVE |
                         SWP_NOZORDER))
            {
                break;
            }

            hwnd = GetDlgItem(hdlg, ID_SENT);
            GetWindowRect(hwnd, &rect);
            if(NULL == DeferWindowPos(hdwp, hwnd, NULL, 0, 0, cx - rect.left - 2,
                         rect.bottom - rect.top, SWP_NOACTIVATE | SWP_NOMOVE |
                         SWP_NOZORDER))
            {
                break;
            }

            hwnd = GetDlgItem(hdlg, ID_TO);
            GetWindowRect(hwnd, &rect);
            if(NULL == DeferWindowPos(hdwp, hwnd, NULL, 0, 0, cx - rect.left - 2,
                         rect.bottom - rect.top, SWP_NOACTIVATE | SWP_NOMOVE |
                         SWP_NOZORDER))
            {
                break;
            }

            hwnd = GetDlgItem(hdlg, ID_SUBJECT);
            GetWindowRect(hwnd, &rect);
            if(NULL == DeferWindowPos(hdwp, hwnd, NULL, 0, 0, cx - rect.left - 2,
                         rect.bottom - rect.top, SWP_NOACTIVATE | SWP_NOMOVE |
                         SWP_NOZORDER))
            {
                break;
            }

            hwnd = GetDlgItem(hdlg, ID_BODY);
            GetWindowRect(hwnd, &rect);
            if(NULL == DeferWindowPos(hdwp, hwnd, NULL, 0, 0, cx - rect.left, cy - rect.top,
                         SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER))
            {
                break;
            }

            EndDeferWindowPos(hdwp);
        }
        break;

    case WM_COMMAND:
        wmId = GET_WM_COMMAND_ID(wParam, lParam);  
        wmEvent = GET_WM_COMMAND_CMD(wParam, lParam);

        switch(wmId) {
        case ID_BODY:
        {
            HMENU hMenu = GetMenu(GetParent(hdlg));
            if(wmEvent == EN_KILLFOCUS)
            {
                EnableMenuItem(hMenu, IDC_EDIT_CUT, MF_BYCOMMAND|MF_GRAYED);
                EnableMenuItem(hMenu, IDC_EDIT_COPY, MF_BYCOMMAND|MF_GRAYED);
                EnableMenuItem(hMenu, IDC_EDIT_PASTE, MF_BYCOMMAND|MF_GRAYED);
                EnableMenuItem(hMenu, IDC_EDIT_UNDO, MF_BYCOMMAND|MF_GRAYED);
            }
            else if(wmEvent == EN_SETFOCUS)
            {
                EnableMenuItem(hMenu, IDC_EDIT_CUT, MF_BYCOMMAND);
                EnableMenuItem(hMenu, IDC_EDIT_COPY, MF_BYCOMMAND);
                EnableMenuItem(hMenu, IDC_EDIT_PASTE, MF_BYCOMMAND);
                EnableMenuItem(hMenu, IDC_EDIT_UNDO, MF_BYCOMMAND);
            }
        }
        break;
        default:
            return FALSE;
        }
        
    default:
        return FALSE;
    }

    return TRUE;
}

BOOL CALLBACK
AboutDlgProc (HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    char    rgchVersion[80];

    switch (msg)
    {
    case WM_INITDIALOG:
        wsprintf(rgchVersion, "Version %d.%d.%d (%s)", rmj, rmm, rup,
            szVerName && *szVerName ? szVerName : "BUDDY");
        SetDlgItemText(hDlg, IDC_VERSION, rgchVersion);
        return TRUE;

    case WM_COMMAND:
        if (wParam == IDOK || wParam == IDCANCEL)
        {
            EndDialog (hDlg, TRUE);
            return TRUE;
        }
        break;
    }
    return FALSE;
}
