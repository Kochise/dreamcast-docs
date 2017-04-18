/**********************************************************************/
/*                                                                    */
/*      MULTIUI.C                                                     */
/*                                                                    */
/*      Copyright (c) 1995-1996  Microsoft Corporation                     */
/*                                                                    */
/**********************************************************************/

#include "windows.h"
#include "imm.h"
#include "resource.h"
#include "multiui.h"


/**********************************************************************/
/*                                                                    */
/*    WinMain(HANDLE, HANDLE, LPSTR, int)                             */
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

    wc.style         = (UINT)NULL;
    wc.lpfnWndProc   = MainWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(hInstance,"MyIcon");
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH); 
    wc.lpszMenuName  = "MultiUiMenu";
    wc.lpszClassName = "MultiUiWClass";

    if (! RegisterClass (&wc))
	return FALSE;


    wc.style         = CS_DBLCLKS;
    wc.lpfnWndProc   = NoUINoIMCWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = WNDEXTRA_NOUINOIMC;
    wc.hInstance     = hInstance;
    wc.hIcon         = 0;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH); 
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "NoUINoIMCWClass";

    if (! RegisterClass (&wc))
	return FALSE;

    wc.style         = CS_DBLCLKS;
    wc.lpfnWndProc   = NoUIOwnIMCWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = WNDEXTRA_NOUIOWNIMC;
    wc.hInstance     = hInstance;
    wc.hIcon         = 0;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH); 
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "NoUIOwnIMCWClass";

    if (! RegisterClass (&wc))
	return FALSE;

    wc.style         = CS_DBLCLKS;
    wc.lpfnWndProc   = OwnUIOwnIMCWndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = WNDEXTRA_OWNUIOWNIMC;
    wc.hInstance     = hInstance;
    wc.hIcon         = 0;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetStockObject(WHITE_BRUSH); 
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "OwnUIOwnIMCWClass";

    if (! RegisterClass (&wc))
	return FALSE;

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
    RECT rc;
    int iDesc = 0;
    HDC hIC;
    TEXTMETRIC tm;
    HFONT hFont = GetDefaultGUIFont();

    char szTitle[20] =  "MultiUi TestTool";

    hInst = hInstance;

    if (!(hWndMain = CreateWindow(
	    "MultiUiWClass", (LPSTR)szTitle,
	    WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
	    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
	    NULL, NULL, hInstance, NULL)))
	return FALSE;


    GetClientRect(hWndMain,&rc);

    rc.right  /= 2;
    rc.bottom /= 3;

    hIC = CreateIC("DISPLAY", NULL, NULL, NULL);

    SelectObject(hIC, hFont);

    GetTextMetrics(hIC,&tm);

    if (rc.bottom >= tm.tmHeight)
        iDesc = tm.tmHeight + tm.tmExternalLeading;

    DeleteDC(hIC);

    if (!(hWndDef1 = CreateWindowEx(WS_EX_CLIENTEDGE, "NoUINoIMCWClass", "",
            WS_CHILD|WS_VISIBLE,
	    rc.left, rc.top + iDesc, rc.right, rc.bottom - iDesc,
	    hWndMain, NULL, hInstance, NULL)))
	return FALSE;

    if (!(hWndDef2 = CreateWindowEx(WS_EX_CLIENTEDGE, "NoUINoIMCWClass", "",
            WS_CHILD|WS_VISIBLE,
	    rc.right, rc.top + iDesc, rc.right, rc.bottom - iDesc,
	    hWndMain, NULL, hInstance, NULL)))
	return FALSE;

    if (!(hWndIMC1 = CreateWindowEx(WS_EX_CLIENTEDGE, "NoUIOwnIMCWClass", "",
            WS_CHILD|WS_VISIBLE,
	    rc.left, rc.bottom + iDesc, rc.right, rc.bottom - iDesc,
	    hWndMain, NULL, hInstance, NULL)))
	return FALSE;

    if (!(hWndIMC2 = CreateWindowEx(WS_EX_CLIENTEDGE, "NoUIOwnIMCWClass", "",
            WS_CHILD|WS_VISIBLE,
	    rc.right, rc.bottom + iDesc, rc.right, rc.bottom - iDesc,
	    hWndMain, NULL, hInstance, NULL)))
	return FALSE;

    if (!(hWndIMCUI1 = CreateWindowEx(WS_EX_CLIENTEDGE, "OwnUIOwnIMCWClass", "",
            WS_CHILD|WS_VISIBLE,
	    rc.left, rc.bottom * 2 + iDesc, rc.right, rc.bottom - iDesc,
	    hWndMain, NULL, hInstance, NULL)))
	return FALSE;

    if (!(hWndIMCUI2 = CreateWindowEx(WS_EX_CLIENTEDGE, "OwnUIOwnIMCWClass", "",
            WS_CHILD|WS_VISIBLE,
	    rc.right, rc.bottom * 2 + iDesc, rc.right, rc.bottom - iDesc,
	    hWndMain, NULL, hInstance, NULL)))
	return FALSE;


    /* display each windows */
    ShowWindow (hWndMain, nCmdShow);
    UpdateWindow (hWndMain);

    return TRUE;

}

/**********************************************************************/
/*                                                                    */
/*    MainWndProc(HWND, UINT, WPARAM, LPARAM)                         */
/*                                                                    */
/**********************************************************************/
long FAR PASCAL MainWndProc(hWnd, message, wParam, lParam)
HWND hWnd;
UINT message;
WPARAM wParam;
LPARAM lParam;
{
    PAINTSTRUCT ps;
    HDC  hDC;
    FARPROC lpProc;
    RECT rc;
    int iDesc = 0;
    HDC hIC;
    TEXTMETRIC tm;
    HFONT hFont;
    HFONT hOldFont;
    HIMC hIMC;
    HWND hIMEWnd;
    char szDesc[128];

    switch (message) {
	case WM_CREATE:
	    break;

	case WM_SIZE:
            switch (wParam)
            {
                case SIZENORMAL:
                case SIZEFULLSCREEN:
                    GetClientRect(hWndMain,&rc);
                    rc.right  /= 2;
                    rc.bottom /= 3;

                    hFont = GetDefaultGUIFont();
                    hIC = CreateIC("DISPLAY", NULL, NULL, NULL);

                    SelectObject(hIC, hFont);

                    GetTextMetrics(hIC,&tm);

                    iDesc = 0;
                    if (rc.bottom >= tm.tmHeight)
                        iDesc = tm.tmHeight + tm.tmExternalLeading;

                    DeleteDC(hIC);

                    MoveWindow(hWndDef1,
                               rc.left,rc.top + iDesc,
                               rc.right,rc.bottom - iDesc,TRUE);
                    MoveWindow(hWndDef2,
                               rc.right,rc.top + iDesc,
                               rc.right,rc.bottom - iDesc,TRUE);
                    MoveWindow(hWndIMC1,
                               rc.left,rc.bottom + iDesc,
                               rc.right,rc.bottom - iDesc,TRUE);
                    MoveWindow(hWndIMC2,
                               rc.right,rc.bottom + iDesc,
                               rc.right,rc.bottom - iDesc,TRUE);
                    MoveWindow(hWndIMCUI1,
                               rc.left,rc.bottom * 2 + iDesc,
                               rc.right,rc.bottom - iDesc,TRUE);
                    MoveWindow(hWndIMCUI2,
                               rc.right,rc.bottom * 2 + iDesc,
                               rc.right,rc.bottom - iDesc,TRUE);

                    InvalidateRect(hWnd,NULL,TRUE);
                    break;

                case SIZEICONIC:
	            return (DefWindowProc(hWnd, message, wParam, lParam));
                    break;
           
            }
	    break;

	case WM_PAINT:
	    hDC = BeginPaint (hWnd, &ps);
            hFont = GetDefaultGUIFont();
            hOldFont = SelectObject(hDC, hFont);

            GetClientRect(hWndMain,&rc);
            rc.right  /= 2;
            rc.bottom /= 3;

            wsprintf(szDesc,"%08lX Default IMC and Default IME window"
                     ,(DWORD)hWndDef1);
            TextOut(hDC, rc.left,rc.top,szDesc,lstrlen(szDesc));

            wsprintf(szDesc,"%08lX Default IMC and Default IME window"
                     ,(DWORD)hWndDef2);
            TextOut(hDC, rc.right,rc.top,szDesc,lstrlen(szDesc));

            hIMC = (HIMC)GetWindowLong(hWndIMC1,MYGWL_IMC);
            wsprintf(szDesc,"%08lX IMC[%08lX] and Default IME window"
                     ,(DWORD)hWndIMC1, (DWORD)hIMC);
            TextOut(hDC, rc.left,rc.bottom,szDesc,lstrlen(szDesc));

            hIMC = (HIMC)GetWindowLong(hWndIMC2,MYGWL_IMC);
            wsprintf(szDesc,"%08lX IMC[%08lX] and Default IME window"
                     ,(DWORD)hWndIMC2, (DWORD)hIMC);
            TextOut(hDC, rc.right,rc.bottom,szDesc,lstrlen(szDesc));

            hIMC = (HIMC)GetWindowLong(hWndIMCUI1,MYGWL_IMC);
            hIMEWnd = (HWND)GetWindowLong(hWndIMCUI1,MYGWL_IMEWND);
            wsprintf(szDesc,"%08lX IMC[%08lX] and IME window[%08lX]"
                     ,(DWORD)hWndIMCUI1, (DWORD)hIMC ,(DWORD)hIMEWnd);
            TextOut(hDC, rc.left,rc.bottom * 2,szDesc,lstrlen(szDesc));

            hIMC = (HIMC)GetWindowLong(hWndIMCUI2,MYGWL_IMC);
            hIMEWnd = (HWND)GetWindowLong(hWndIMCUI2,MYGWL_IMEWND);
            wsprintf(szDesc,"%08lX IMC[%08lX] and IME window[%08lX]"
                     ,(DWORD)hWndIMCUI2, (DWORD)hIMC ,(DWORD)hIMEWnd);
            TextOut(hDC, rc.right,rc.bottom * 2,szDesc,lstrlen(szDesc));

            SelectObject(hDC, hOldFont);
	    EndPaint (hWnd, &ps);
	    break;

	case WM_COMMAND:
	    switch(WMCOMMANDWPARAM(wParam))
	    {
		case IDM_ABOUT:
		    lpProc = MakeProcInstance(AboutDlg, hInst);
		    DialogBox(hInst, "ABOUTBOX", hWnd, (DLGPROC)lpProc);
		    FreeProcInstance(lpProc);
		    break;

	    }
	    break;

	case WM_DESTROY:
	    PostQuitMessage(0);
	    break;

	default:
	    return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return 0L;
}

