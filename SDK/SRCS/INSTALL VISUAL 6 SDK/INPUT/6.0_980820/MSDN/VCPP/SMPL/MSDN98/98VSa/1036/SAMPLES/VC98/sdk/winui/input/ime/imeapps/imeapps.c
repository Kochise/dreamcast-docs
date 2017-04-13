/**********************************************************************/
/*                                                                    */
/*      IMEAPPS.C                                                     */
/*                                                                    */
/*      Copyright (c) 1995-1997  Microsoft Corporation                */
/*                                                                    */
/**********************************************************************/

#include "windows.h"
#include "commdlg.h"
#include "commctrl.h"
#include "imm.h"
#include "resource.h"
#include "imeapps.h"


/**********************************************************************/
/*                                                                    */
/*    WinMain(HINSTANCE, HINSTANCE, LPSTR, int)                             */
/*                                                                    */
/**********************************************************************/
int APIENTRY WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow)
HINSTANCE hInstance;
HINSTANCE hPrevInstance;
LPSTR lpCmdLine;
int nCmdShow;
{
    MSG msg;

    if (!hPrevInstance)  
        if (!InitApplication(hInstance))
            return (FALSE);

    if (!InitInstance(hInstance, nCmdShow))
	return (FALSE);

    
    while (GetMessage(&msg, NULL, 0, 0))
    {
	TranslateMessage(&msg);
	DispatchMessage(&msg);
    }
    return (msg.wParam);
}

/**********************************************************************/
/*                                                                    */
/*    InitApplication(HANDLE)                                         */
/*                                                                    */
/**********************************************************************/
BOOL InitApplication(hInstance)
HANDLE hInstance;
{
    WNDCLASS  wc;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = MainWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(hInstance,"MyIcon");
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(LTGRAY_BRUSH); 
    wc.lpszMenuName  = "ImeAppsMenu";
    wc.lpszClassName = "ImeAppsWClass";

    if (! RegisterClass (&wc))
	return FALSE;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = CompStrWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 4;
    wc.hInstance     = hInstance;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(LTGRAY_BRUSH); 
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "CompStrWndClass";

    if (! RegisterClass (&wc))
	return FALSE;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = CandListWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(LTGRAY_BRUSH); 
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "CandListWndClass";

    if (! RegisterClass (&wc))
	return FALSE;

    hFont = GetStockObject(DEFAULT_GUI_FONT);

    return TRUE;
}

/**********************************************************************/
/*                                                                    */
/*    InitInstance(HANDLE, int)                                       */
/*                                                                    */
/**********************************************************************/
BOOL InitInstance(hInstance, nCmdShow)
    HANDLE          hInstance;
    int             nCmdShow;
{
#ifdef USEWAPI
    char szTitle[] =  "ImeApps W API version";
#else
    char szTitle[] =  "ImeApps";
#endif

    hInst = hInstance;


    ptImeUIPos.x = 0;
    ptImeUIPos.y = 0;

    if (!(hWndMain = CreateWindowEx(0L,
	    "ImeAppsWClass", (LPSTR)szTitle,
	    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
	    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
	    NULL, NULL, hInstance, NULL)))
	return FALSE;

    /* display each windows */
    ShowWindow (hWndMain, nCmdShow);
    UpdateWindow (hWndMain);


    return TRUE;

}

/**********************************************************************/
/*                                                                    */
/*    InitIMEUIPosition(HWND)                                         */
/*                                                                    */
/**********************************************************************/
void InitIMEUIPosition(hWnd)
HWND hWnd;
{
    HDC hDC;
    int y;
    SIZE sz;
    HFONT hOldFont;
    HFONT hDefFont;
    int height, defheight;

    hDefFont = GetStockObject(DEFAULT_GUI_FONT);

    hOldFont = NULL;

    y = ORG_Y;

    hDC = GetDC(hWnd);

    if (hFont)
        hOldFont = SelectObject(hDC,hDefFont);


    // Get the height of the default gui font.
    GetTextExtentPoint(hDC,"A",1,&sz);
    defheight = sz.cy + 1;

    // Get the height of the font.
    SelectObject(hDC,hFont);
    GetTextExtentPoint(hDC,"A",1,&sz);
    height = sz.cy + 1;

    SelectObject(hDC,hDefFont);
    y += defheight;

    y += height;

    y += height;

    y += defheight;

    y += height;

    y += height;

    ptImeUIPos.y = y;

    SelectObject(hDC,hOldFont);
    ReleaseDC(hWnd, hDC);

    return;
}

/**********************************************************************/
/*                                                                    */
/*    MainWndProc(HWND, UINT, WPARAM, LPARAM)                         */
/*                                                                    */
/**********************************************************************/
LRESULT CALLBACK MainWndProc(hWnd, message, wParam, lParam)
HWND hWnd;
UINT message;
WPARAM wParam;
LPARAM lParam;
{
    FARPROC lpProc;
    RECT rect;
    HMENU hMenu;
    HIMC hIMC;
    BOOL fOpen;

    switch (message) {
	case WM_CREATE:

            // Create Status Window
            CreateTBar(hWnd);
            CreateStatus(hWnd);

            // Create Child Window
            GetClientRect(hWnd, &rect);
            if (!(hWndCompStr = CreateWindowEx(WS_EX_CLIENTEDGE,
	            "CompStrWndClass", NULL,
	            WS_CHILD | WS_VISIBLE, 
	            // 0, 0, rect.right, rect.bottom - nStatusHeight,
	            0, 0, 0, 0,
	            hWnd, NULL, hInst, NULL)))
	        return FALSE;


            InitIMEUIPosition(hWndCompStr);


            if (!(hWndCandList = CreateWindowEx(WS_EX_CLIENTEDGE,
	            "CandListWndClass", NULL,
	            WS_CHILD | WS_VISIBLE, 
	            0, 0, 0, 0,
	            hWnd, NULL, hInst, NULL)))
	        return FALSE;

            ShowWindow(hWndCompStr, SW_SHOW);
            ShowWindow(hWndCandList, SW_SHOWNA);

            SetStatusItems(hWnd);

            hMenu = GetMenu(hWnd);
            CheckMenuItem(hMenu,IDM_SHOWCAND,
                                (fShowCand ? MF_CHECKED : MF_UNCHECKED));

	    break;

	case WM_COMMAND:
	    switch(LOWORD(wParam))
	    {
		case IDM_ABOUT:
		    lpProc = MakeProcInstance(AboutDlg, hInst);
		    DialogBox(hInst, "ABOUTBOX", hWnd, (DLGPROC)lpProc);
		    FreeProcInstance(lpProc);
		    break;

		case IDM_FONT:
                    {
                    CHOOSEFONT cf;
                    LOGFONT lfT;

                    /* Set all structure fields to zero. */

                    memset(&cf, 0, sizeof(CHOOSEFONT));
                    memcpy(&lfT, &lf, sizeof(LOGFONT));

                    cf.lStructSize = sizeof(CHOOSEFONT);
                    cf.hwndOwner = hWnd;
                    cf.lpLogFont = &lfT;
                    cf.Flags = CF_SCREENFONTS | CF_EFFECTS;
                    cf.nFontType = SCREEN_FONTTYPE;

                    if (ChooseFont(&cf))
                    {
                        if (hFont)
                            DeleteObject(hFont);

                        memcpy(&lf, &lfT, sizeof(LOGFONT));
                        hFont = CreateFontIndirect(&lf);
                        InvalidateRect(hWndCompStr,NULL,TRUE);
                        UpdateWindow(hWndCompStr);
                    }
                    }
                    break;


                case IDM_SHOWCAND:
                    hMenu = GetMenu(hWnd);
                    fShowCand = !fShowCand;
                    CheckMenuItem(hMenu,IDM_SHOWCAND,
                                (fShowCand ? MF_CHECKED : MF_UNCHECKED));
                    MoveCompCandWindow(hWnd);
                    UpdateShowCandButton();
                    break;

                case IDM_OPENSTATUS:
                    hIMC = ImmGetContext(hWndCompStr);
                    fOpen = ImmGetOpenStatus(hIMC);
                    ImmSetOpenStatus(hIMC,!fOpen);
                    UpdateShowOpenStatusButton(!fOpen);
                    ImmReleaseContext(hWndCompStr,hIMC);

                    hMenu = GetMenu(hWnd);
                    CheckMenuItem(hMenu,IDM_OPENSTATUS,
                                (fOpen ? MF_UNCHECKED : MF_CHECKED));
                    break;

                case IDM_NATIVEMODE:
                case IDM_FULLHALF:
                case IDM_ROMAN:
                case IDM_CHARCODE:
                case IDM_HANJA:
                case IDM_SOFTKBD:
                case IDM_EUDC:
                case IDM_SYMBOL:
                    HandleModeCommand(hWnd,wParam,lParam);
                    break;
 
                case IDM_CONVERT:
                case IDM_CANCEL:
                case IDM_REVERT:
                case IDM_COMPLETE:
                case IDM_OPENCAND:
                case IDM_CLOSECAND:
                case IDM_NEXTCAND:
                case IDM_PREVCAND:
                    HandleConvertCommand(hWnd,wParam,lParam);
		    break;

                case IDM_NEXTCLAUSE:
                case IDM_PREVCLAUSE:
                    HandleChangeAttr(hWnd,(LOWORD(wParam) == IDM_NEXTCLAUSE));
		    break;

                default:
		    break;


	    }
	    break;

        case WM_SETFOCUS:
            SetFocus(hWndCompStr);
	    break;

        case WM_NOTIFY:
            SetTooltipText(hWnd, lParam);
            break;

        case WM_SIZE:
            SendMessage(hWndStatus,message,wParam,lParam);
            SendMessage(hWndToolBar,message,wParam,lParam);

            if (wParam != SIZE_MINIMIZED)
                MoveCompCandWindow(hWnd);

	    break;

        case WM_IME_NOTIFY:
            switch (wParam)
            {
                case IMN_OPENSTATUSWINDOW:
                case IMN_CLOSESTATUSWINDOW:
                    break;

                case IMN_SETCONVERSIONMODE:
	            return (DefWindowProc(hWnd, message, wParam, lParam));
            }
	    break;


	case WM_DESTROY:
            if (hFont)
                DeleteObject(hFont);
	    PostQuitMessage(0);
	    break;

	default:
	    return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return 0L;
}
/**********************************************************************/
/*                                                                    */
/*    CompStrWndProc(HWND, UINT, WPARAM, LPARAM)                      */
/*                                                                    */
/**********************************************************************/
LRESULT CALLBACK CompStrWndProc(hWnd, message, wParam, lParam)
HWND hWnd;
UINT message;
WPARAM wParam;
LPARAM lParam;
{
    HIMC hIMC;
    HIMC hOldIMC;

    switch (message) {
	case WM_CREATE:
            hIMC = ImmCreateContext();
            hOldIMC = ImmAssociateContext(hWnd,hIMC);
            SetWindowLong(hWnd, 0, (LONG)hOldIMC);
            fdwProperty = ImmGetProperty(GetKeyboardLayout(0), IGP_PROPERTY);
	    break;

        case WM_CHAR:
            HandleChar(hWnd,wParam,lParam);
	    break;

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
            if (hIMC = ImmGetContext(hWnd))
            {
                HMENU hMenu;

                InitMenuItemIDTable();
                hMenu = CreateImeMenu(hWnd, hIMC, NULL,(message == WM_RBUTTONUP));

                if (hMenu)
                {
                    DWORD dwItemData;
                    DWORD dwPos = (DWORD)GetMessagePos();
                    int nCmd;
                  
                    nCmd = TrackPopupMenuEx(hMenu,
                           TPM_RETURNCMD | TPM_NONOTIFY | 
                           TPM_LEFTBUTTON | TPM_LEFTALIGN | TPM_TOPALIGN, 
                           LOWORD(dwPos), HIWORD(dwPos), 
                           hWnd, NULL);

                    if (nCmd)
                    {
                        nCmd -= IDM_STARTIMEMENU;
                        dwItemData = FindItemData(nCmd);
                        ImmNotifyIME(hIMC, NI_IMEMENUSELECTED, nCmd, dwItemData);
                    }
                }
                EndMenuItemIDTable();

                DestroyMenu(hMenu);
            }
	    break;

        case WM_IME_SETCONTEXT:
            if (fShowCand)
                lParam &= ~ISC_SHOWUICANDIDATEWINDOW;

            if (fdwProperty & IME_PROP_SPECIAL_UI)
            {
            }
            else if (fdwProperty & IME_PROP_AT_CARET)
            {
                lParam &= ~ISC_SHOWUICOMPOSITIONWINDOW;
            }
            else
            {
            }

	    return (DefWindowProc(hWnd, message, wParam, lParam));

        case WM_IME_STARTCOMPOSITION:
            // Normally, we should not call into HandleStartComposition
            // for IME_PROP_SPECIAL_UI and not IME_PROP_AT_CARET IMEs
            // we should pass this message to DefWindowProc directly for
            // this kind of IMEs

            HandleStartComposition(hWnd,wParam,lParam);

            // pass this message to DefWindowProc for IME_PROP_SPECIAL_UI
            // and not IME_PROP_AT_CARET IMEs

            if (fdwProperty & IME_PROP_SPECIAL_UI)
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            else if (fdwProperty & IME_PROP_AT_CARET)
            {
            }
            else
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }

	    break;

        case WM_IME_ENDCOMPOSITION:
            // Normally, we should not call into HandleEndComposition
            // for IME_PROP_SPECIAL_UI and not IME_PROP_AT_CARET IMEs
            // we should pass this message to DefWindowProc directly for
            // this kind of IMEs

            HandleEndComposition(hWnd,wParam,lParam);

            // pass this message to DefWindowProc for IME_PROP_SPECIAL_UI
            // and not IME_PROP_AT_CARET IMEs

            if (fdwProperty & IME_PROP_SPECIAL_UI)
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            else if (fdwProperty & IME_PROP_AT_CARET)
            {
            }
            else
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }

	    break;

        case WM_IME_COMPOSITION:
            // Normally, we should not call into HandleComposition
            // for IME_PROP_SPECIAL_UI and not IME_PROP_AT_CARET IMEs
            // we should pass this message to DefWindowProc directly for
            // this kind of IMEs

            HandleComposition(hWnd,wParam,lParam);

            // pass this message to DefWindowProc for IME_PROP_SPECIAL_UI
            // and not IME_PROP_AT_CARET IMEs

            if (fdwProperty & IME_PROP_SPECIAL_UI)
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            else if (fdwProperty & IME_PROP_AT_CARET)
            {
            }
            else
            {
                return (DefWindowProc(hWnd, message, wParam, lParam));
            }

	    break;

	case WM_PAINT:
            HandlePaint(hWnd,wParam,lParam);
	    break;

        case WM_IME_NOTIFY:
            {
                LRESULT lRet;

                // Normally, we should not call into HandleNotify
                // for IME_PROP_SPECIAL_UI and not IME_PROP_AT_CARET IMEs
                // we should pass this message to DefWindowProc directly for
                // this kind of IMEs

                lRet = HandleNotify(hWnd, message, wParam, lParam);
 
                // pass this message to DefWindowProc for IME_PROP_SPECIAL_UI
                // and not IME_PROP_AT_CARET IMEs

                if (fdwProperty & IME_PROP_SPECIAL_UI)
                {
                    return (DefWindowProc(hWnd, message, wParam, lParam));
                }
                else if (fdwProperty & IME_PROP_AT_CARET)
                {
                }
                else
                {
                    return (DefWindowProc(hWnd, message, wParam, lParam));
                }

                return lRet;
            }

        case WM_DESTROY:
            hOldIMC = (HIMC)GetWindowLong(hWnd, 0);
            hIMC = ImmAssociateContext(hWnd, hOldIMC);
            ImmDestroyContext(hIMC);
	    break;

        case WM_INPUTLANGCHANGE:
            fdwProperty = ImmGetProperty(GetKeyboardLayout(0), IGP_PROPERTY);

            if (hIMC = ImmGetContext(hWnd))
            {
                CANDIDATEFORM cdf;

                if (fdwProperty & IME_PROP_AT_CARET)
                {
                    cdf.dwIndex = 0;
                    cdf.dwStyle = CFS_CANDIDATEPOS;
                    cdf.ptCurrentPos.x = ptImeUIPos.x;
                    cdf.ptCurrentPos.y = ptImeUIPos.y;
                    ImmSetCandidateWindow(hIMC, &cdf);
                }
                else
                {
                    UINT i;

                    // The candidate position should be decided by a near caret
                    // IME. There are 4 candidate form in the input context

                    for (i = 0; i < 4; i++)
                    {
                        if (!ImmGetCandidateWindow(hIMC, i, &cdf))
                        {
                            continue;
                        }

                        if (cdf.dwStyle == CFS_DEFAULT)
                        {
                            continue;
                        }

                        cdf.dwStyle = CFS_DEFAULT;

                        ImmSetCandidateWindow(hIMC, &cdf);
                    }

                }

                ImmReleaseContext(hWnd, hIMC);
            }

	    return (DefWindowProc(hWnd, message, wParam, lParam));

	default:
	    return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return 0L;
}


/**********************************************************************/
/*                                                                    */
/*    CandListWndProc(HWND, UINT, WPARAM, LPARAM)                     */
/*                                                                    */
/**********************************************************************/
LRESULT CALLBACK CandListWndProc(hWnd, message, wParam, lParam)
HWND hWnd;
UINT message;
WPARAM wParam;
LPARAM lParam;
{
    switch (message) {

	case WM_PAINT:
            HandleCandPaint(hWnd,wParam,lParam);
	    break;

        case WM_SETFOCUS:
            SetFocus(hWndCompStr);
	    break;

	default:
	    return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return 0L;
}


/**********************************************************************/
/*                                                                    */
/*    About(HWND, UINT, WPARAM, LPARAM)                               */
/*                                                                    */
/**********************************************************************/
LRESULT CALLBACK AboutDlg(hDlg, message, wParam, lParam)
HWND hDlg;
unsigned message;
WPARAM wParam;
LPARAM lParam;
{
    switch (message) {
	case WM_INITDIALOG:
	    return (TRUE);

	case WM_COMMAND:
	    if (wParam == IDOK
                || wParam == IDCANCEL) {
		EndDialog(hDlg, TRUE);
		return (TRUE);
	    }
	    break;
    }
    return (FALSE);
}




