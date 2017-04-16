/*    PortTool v2.2     hlsample.c          */

#include "hlsample.h"

// Globals

HWND g_hwndMain;


int PASCAL WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR lpszCmdLine, int cmdShow)
{
    MSG       msg;

    if (!_hPrevInstance)
    {
        WNDCLASS cls;

        cls.hCursor         = LoadCursor(NULL, IDC_ARROW);
        cls.hIcon           = LoadIcon(_hInstance, MAKEINTRESOURCE(IDR_MAINICON));
        cls.lpszMenuName    = MAKEINTRESOURCE(IDR_MAINMENU);
        cls.hInstance       = _hInstance;
        cls.lpszClassName   = "HLSample_MainWnd";
        cls.hbrBackground   = (HBRUSH)(COLOR_WINDOW+1);
        cls.lpfnWndProc     = MainWnd_WndProc;
        cls.style           = CS_DBLCLKS;
        cls.cbWndExtra      = 0;
        cls.cbClsExtra      = 0;

        if (!RegisterClass(&cls))
            return FALSE;
    }

    g_hwndMain = CreateWindowEx(
            0L,
            "HLSample_MainWnd",
            "Hier List box Sample Application",
            WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            NULL,
            NULL,
             _hInstance,
            NULL);

    if (g_hwndMain == NULL)
    return FALSE;

    ShowWindow(g_hwndMain, _cmdShow);

    //
    // If a message exists in the queue, translate and dispatch it.
    //
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyWindow(g_hwndMain);
    g_hwndMain = NULL;

    return TRUE;
}

LRESULT CALLBACK _export MainWnd_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        HANDLE_MSG(hwnd, WM_CLOSE, MainWnd_OnClose);
        HANDLE_MSG(hwnd, WM_COMMAND, MainWnd_OnCommand);
        
        case WM_SYSCOLORCHANGE:
            HLSystemColorChange();
            return TRUE;
        break;
        
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

VOID MainWnd_OnClose(HWND hwnd)
{
    PostQuitMessage(0);
}

VOID MainWnd_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT code)
{
    switch (id)
    {
       case CMD_FILEEXIT:
           PostQuitMessage(0);
       break;

       case CMD_HELPABOUT:
           AboutDlg_Do(hwnd);
       break;

       case CMD_DIALOG:
           HLDialog_Do(hwnd);
       break;
    }
}

// Simple Help About box
//
VOID AboutDlg_Do(HWND hwndOwner)
{
    DLGPROC lpfndp;

    lpfndp = (DLGPROC)MakeProcInstance((FARPROC)AboutDlg_DlgProc, _hInstance);

    if (!lpfndp)
        return;

    DialogBoxParam(_hInstance, MAKEINTRESOURCE(IDR_ABOUTDLG),
            hwndOwner, lpfndp, 0L);


/*    PortTool v2.2     4/1/1993    1:0          */
/*      Found   : FAR          */
/*      Issue   : Win32 is non-segmented, thus FAR == NEAR == nothing!          */

/*    PortTool v2.2     4/1/1993    1:3          */
/*      Found   : FAR          */
/*      Issue   : Win32 is non-segmented, thus FAR == NEAR == nothing!          */
    FreeProcInstance((FARPROC)lpfndp);
}

BOOL CALLBACK _export AboutDlg_DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {

/*    PortTool v2.2     4/1/1993    1:0          */
/*      Found   : WM_COMMAND          */
/*      Issue   : wParam/lParam repacking, refer to tech. ref. for details          */

/*    PortTool v2.2     4/1/1993    1:3          */
/*      Found   : WM_COMMAND          */
/*      Issue   : wParam/lParam repacking, refer to tech. ref. for details          */
    case WM_COMMAND:
        if (wParam == IDOK || wParam == IDCANCEL)
            EndDialog(hwndDlg, TRUE);
        return TRUE;
        break;

    case WM_INITDIALOG:
        return TRUE;
    }
    return FALSE;
}
