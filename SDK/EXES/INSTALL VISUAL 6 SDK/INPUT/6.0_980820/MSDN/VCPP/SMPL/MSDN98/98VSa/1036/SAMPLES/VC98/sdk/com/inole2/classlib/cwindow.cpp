/*
 * CWINDOW.CPP
 * Sample Code Class Libraries
 *
 * Implementation of a simple CWindow class.
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
 * CWindow::CWindow
 * CWindow::~CWindow
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the task owning us.
 */

CWindow::CWindow(HINSTANCE hInst)
    {
    m_hInst=hInst;
    m_hWnd=NULL;
    return;
    }

CWindow::~CWindow(void)
    {
    if (IsWindow(m_hWnd))
        DestroyWindow(m_hWnd);

    return;
    }






/*
 * CWindow::Window
 *
 * Purpose:
 *  Returns the window handle associated with this object.
 *
 * Return Value:
 *  HWND            Window handle for this object
 */

HWND CWindow::Window(void)
    {
    return m_hWnd;
    }



/*
 * CWindow::Instance
 *
 * Purpose:
 *  Returns the instance handle associated with this object.
 *
 * Return Value:
 *  HINSTANCE       Instance handle of the module stored here.
 */

HINSTANCE CWindow::Instance(void)
    {
    return m_hInst;
    }
