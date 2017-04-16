// savewnd.cpp : implementation file
// Default handling for screen-saver window messages

#include "stdafx.h"
#include "resource.h" // for IDC_NULLCURSOR
#include "savewnd.h"

#define THRESHOLD 3

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveWnd

CSaveWnd::CSaveWnd()
{
}

CSaveWnd::~CSaveWnd()
{
}

BEGIN_MESSAGE_MAP(CSaveWnd, CWnd)
	//{{AFX_MSG_MAP(CSaveWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSaveWnd::Create()
{
    // Register a class with no cursor
    const char* pszClassName 
        = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_SAVEBITS|CS_DBLCLKS,
                              ::LoadCursor(AfxGetResourceHandle(),
                                           MAKEINTRESOURCE(IDC_NULLCURSOR)));

    // Create the window
    return CWnd::CreateEx(WS_EX_TOPMOST,
                          pszClassName,
                          "",
                          WS_POPUP | WS_VISIBLE,
                          0, 0,
                          ::GetSystemMetrics(SM_CXSCREEN),
                          ::GetSystemMetrics(SM_CYSCREEN),
                          NULL,
                          NULL);
}

void CSaveWnd::PostNcDestroy() 
{
    // We must delete the window object ourselves since the
    // app framework doesn't do this.
    delete this;
}

LRESULT CSaveWnd::WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    static BOOL     fHere = FALSE;
    static POINT    ptLast;
    POINT           ptCursor, ptCheck;

    switch (nMsg){
    case WM_SYSCOMMAND:
        if ((wParam == SC_SCREENSAVE) || (wParam == SC_CLOSE)) {
            return FALSE;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    case WM_SETCURSOR:
        SetCursor(NULL);
        break;

    case WM_NCACTIVATE:
        if (wParam == FALSE) {
            return FALSE;
        }
        break;

    case WM_ACTIVATE:
    case WM_ACTIVATEAPP:
        if(wParam != FALSE) break;               
        // only fall through if we are losing the focus...

    case WM_MOUSEMOVE:
        if(!fHere) {
            GetCursorPos(&ptLast);
            fHere = TRUE;
        } else {
            GetCursorPos(&ptCheck);
            if(ptCursor.x = ptCheck.x - ptLast.x) {
                if(ptCursor.x < 0) ptCursor.x *= -1;
            }
            if(ptCursor.y = ptCheck.y - ptLast.y) {
                if(ptCursor.y < 0) ptCursor.y *= -1;
            }
            if((ptCursor.x + ptCursor.y) > THRESHOLD) {
                PostMessage(WM_CLOSE, 0, 0l);
            }
        }
        break;

    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
        GetCursorPos(&ptCursor);
        ptCursor.x ++;
        ptCursor.y ++;
        SetCursorPos(ptCursor.x, ptCursor.y);
        GetCursorPos(&ptCheck);
        if(ptCheck.x != ptCursor.x && ptCheck.y != ptCursor.y)
        ptCursor.x -= 2;
        ptCursor.y -= 2;
        SetCursorPos(ptCursor.x,ptCursor.y);

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
        PostMessage(WM_CLOSE, 0, 0l);
        break;
    }
    return CWnd::WindowProc(nMsg, wParam, lParam);
}
