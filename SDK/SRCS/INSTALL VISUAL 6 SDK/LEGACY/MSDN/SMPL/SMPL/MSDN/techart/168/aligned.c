/*
 *
 *  Window Edit Control Text Test App
 *
 *  Microsoft WinSDK Support
 *
 */
// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.
//

#include <windows.h>
#include "aligned.h"


HANDLE      hgInst;

//These are for one method;
HANDLE      hEditLeft;
HANDLE      hEditCenter;
HANDLE      hEditRight;
HANDLE      hEditLast1;


//These are for another method.
HANDLE      hEdit;
HANDLE      hEditLast2;


/*
 * WinMain
 *
 * Purpose:
 *  Main entry point of application.   Should register the app class
 *  if a previous instance has not done so and do any other one-time
 *  initializations.
 *
 * Parameters:
 *  See Windows SDK Guide to Programming, page 2-3
 *
 * Return Value:
 *  Value to return to Windows--termination code.
 *
 */

int PASCAL WinMain (HANDLE hInstance, HANDLE hPrevInstance,
                    LPSTR lpszCmdLine, int nCmdShow)
    {
    WNDCLASS    wndClass;
    HWND        hWnd;
    MSG         msg;
    short       i;
    HANDLE      hEditMem;
    HANDLE      hMem;


    hgInst=hInstance;

    if (!hPrevInstance)
        {
        wndClass.style          = CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc    = EditAlignWndProc;
        wndClass.cbClsExtra     = 0;
        wndClass.cbWndExtra     = 0;
        wndClass.hInstance      = hInstance;
        wndClass.hIcon          = LoadIcon(hInstance, "EditAlignIcon");
        wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
        wndClass.hbrBackground  = GetStockObject(WHITE_BRUSH);
        wndClass.lpszMenuName   = "EditAlignMenu";
        wndClass.lpszClassName  = "EditAlign";


        if (!RegisterClass(&wndClass))
            return FALSE;
        }



    hWnd=CreateWindow("EditAlign",
                      "Edit Alignment Test",
                      WS_MINIMIZEBOX | WS_OVERLAPPEDWINDOW,
                      35, 35, 400, 150,
                      NULL,
                      NULL,
                      hInstance,
                      NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    hEditLeft=CreateWindowEx(WS_EX_NOPARENTNOTIFY, "edit", "Control #1",
                       WS_BORDER | WS_VISIBLE | WS_CHILD | ES_LEFT | ES_MULTILINE,
                       10, 10, 380, 26, hWnd, 900, hInstance, NULL);

    //Get the edit control handle to it's memory.
    hEditMem=SendMessage(hEditLeft, EM_GETHANDLE, 0, 0L);

    //Remember which one is visible.
    hEditLast1=hEditLeft;

    hEditCenter=CreateWindowEx(WS_EX_NOPARENTNOTIFY, "edit", "",
                       WS_BORDER | WS_CHILD | ES_CENTER | ES_MULTILINE,
                       10, 10, 380, 26, hWnd, 901, hInstance, NULL);

    //Remove the memory that
    hMem=SendMessage(hEditCenter, EM_GETHANDLE, 0, 0L);
    LocalFree(hMem);
    SendMessage(hEditCenter, EM_SETHANDLE, hEditMem, 0L);



    hEditRight=CreateWindowEx(WS_EX_NOPARENTNOTIFY, "edit", "",
                       WS_BORDER | WS_CHILD | ES_RIGHT | ES_MULTILINE,
                       10, 10, 380, 26, hWnd, 902, hInstance, NULL);

    //Get the edit control handle to it's memory.
    hMem=SendMessage(hEditRight, EM_GETHANDLE, 0, 0L);
    LocalFree(hMem);
    SendMessage(hEditRight, EM_SETHANDLE, hEditMem, 0L);


    hEdit=CreateWindowEx(WS_EX_NOPARENTNOTIFY, "edit", "Control #2",
                         WS_VISIBLE | WS_BORDER | WS_CHILD | ES_LEFT | ES_MULTILINE,
                         10, 50, 380, 26, hWnd, 903, hInstance, NULL);
    hEditLast2=hEdit;


    while (GetMessage(&msg, NULL, 0,0 ))
        {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        }


    return msg.wParam;
    }




/*
 * EditAlignWndProc
 *
 * Purpose:
 *  Window class procedure.  Standard callback.
 *
 * Parameters:
 *  The standard.  See Section 2.4 Windows SDK Guide to Programming,
 *  page 2-4.
 *
 * Return Value:
 *  See Parameters, above.
 *
 */


long FAR PASCAL EditAlignWndProc(HWND hWnd, UINT iMessage,
				 WPARAM wParam, LPARAM lParam)
    {
    HANDLE      hEditTmp;
    HANDLE      hMem;
    HANDLE      hMemTmp;
    RECT        rect;
    DWORD       dwStyle;
    POINT       pt;

    switch (iMessage)
        {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_COMMAND:
            switch (wParam)
                {
                //These are combined to save repeated code.
                case IDM_ALIGNMENTLEFT1:
                case IDM_ALIGNMENTCENTER1:
                case IDM_ALIGNMENTRIGHT1:
                    hMem=SendMessage(hEditLast1, EM_GETHANDLE, 0, 0L);
                    ShowWindow(hEditLast1, FALSE);

                    //Get the correct window that is being shown
                    if (wParam==IDM_ALIGNMENTLEFT1)
                        hEditTmp=hEditLeft;
                    else
                        {
                        if (wParam==IDM_ALIGNMENTCENTER1)
                            hEditTmp=hEditCenter;
                        else
                            hEditTmp=hEditRight;
                        }

                    SendMessage(hEditTmp, EM_SETHANDLE, hMem, 0L);
                    ShowWindow(hEditTmp, TRUE);

                    hEditLast1=hEditTmp;
                    break;

                case IDM_ALIGNMENTLEFT2:
                case IDM_ALIGNMENTCENTER2:
                case IDM_ALIGNMENTRIGHT2:
                    GetWindowRect(hEditLast2, &rect);
                    dwStyle=GetWindowLong(hEditLast2, GWL_STYLE);

                    //Remove any alignment style.
                    dwStyle= dwStyle & ~(ES_LEFT | ES_RIGHT | ES_CENTER);

                    //Add the one we want.
                    if (wParam==IDM_ALIGNMENTLEFT2)
                        dwStyle |= ES_LEFT;
                    else
                        {
                        if (wParam==IDM_ALIGNMENTCENTER2)
                            dwStyle |= ES_CENTER;
                        else
                            dwStyle |= ES_RIGHT;
                        }

                    ShowWindow(hEditLast2, FALSE);

                    pt.x=rect.left;
                    pt.y=rect.top;
                    ScreenToClient(hWnd, &pt);

                    GetClientRect(hEditLast2, &rect);

                    hEdit=CreateWindowEx(WS_EX_NOPARENTNOTIFY, "edit", "",
                                         dwStyle,
                                         pt.x, pt.y,
                                         rect.right, rect.bottom,
                                         hWnd, 903, hgInst, NULL);

                    hMem=SendMessage(hEditLast2, EM_GETHANDLE, 0, 0L);
                    hMemTmp=SendMessage(hEdit, EM_GETHANDLE, 0, 0L);

                    SendMessage(hEdit, EM_SETHANDLE, hMem, 0L);
                    SendMessage(hEditLast2, EM_SETHANDLE, hMemTmp, 0L);

                    DestroyWindow(hEditLast2);
                    hEditLast2=hEdit;

                    ShowWindow(hEdit, TRUE);
                    break;


                case IDM_EXIT:
                    PostMessage(hWnd, WM_CLOSE, 0, 0L);
                    break;

                }

        default:
            return (DefWindowProc(hWnd, iMessage, wParam, lParam));
        }

    return 0L;
    }
