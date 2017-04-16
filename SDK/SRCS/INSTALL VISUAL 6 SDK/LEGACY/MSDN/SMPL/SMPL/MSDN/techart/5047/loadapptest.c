/*****************************************************************************
 *
 *  LoadAppTest.c
 *  Main module to demonstrate use of dmdfm.c
 *
 *  Copyright (c) 1996 Microsoft Corporation.  All Rights Reserved.
 *
 *****************************************************************************/



#define NAME "LoadApp Test"
#define TITLE NAME

#include <windows.h>
#include "dmdfm.h"

LRESULT CALLBACK WindowProc( HWND hWnd, UINT message, 
                            WPARAM wParam, LPARAM lParam )
{

    HRESULT hr;
    static HINSTANCE hInstance;

    switch( message )
    {
    case WM_CREATE:
      hInstance = ((LPCREATESTRUCT) lParam)->hInstance;
      return 0;

    case WM_KEYDOWN:
        switch( wParam )
        {
        case VK_ESCAPE:
            PostMessage(hWnd, WM_CLOSE, 0, 0);
            break;

        case VK_F2:
            hr = DetachFromMedium(hInstance, DMDFM_ALWAYS | DMDFM_ALLPAGES);
            if (SUCCEEDED(hr))
              MessageBox(hWnd, "File successfully detached.", "Info", MB_OK);
            else
              MessageBox(hWnd, "Failed to detach file.", "Info", MB_OK);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);

} /* WindowProc */

/*
 * WinMain - initialization, message loop
 */
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine, int nCmdShow)
{
    MSG         msg;
    HWND        hwnd;
    WNDCLASS    wc;

    lpCmdLine = lpCmdLine;          // to avoid compiler warnings
    hPrevInstance = hPrevInstance;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( hInstance, IDI_APPLICATION );
    wc.hCursor = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NAME;
    wc.lpszClassName = NAME;
    RegisterClass( &wc );
    
    /*
     * create a window
     */
    hwnd = CreateWindow(
        NAME,
        TITLE,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        HWND_DESKTOP,
        NULL,
        hInstance,
        NULL );

    ShowWindow( hwnd, nCmdShow );
    UpdateWindow( hwnd );

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;

} /* WinMain */
