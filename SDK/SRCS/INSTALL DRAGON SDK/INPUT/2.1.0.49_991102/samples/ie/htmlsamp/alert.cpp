/********************************************************************
 * alert.cpp
 *
 * Description
 *    CAlertWindow - class that handles the display and input of 
 *    game alert "windows" (such as the wait/finished alerts for
 *    VMU selection and the win/lose alerts of Battleship game).
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "alert.h"              // CAlertWindow
#include "status.h"             // CStatusBar

/********************************************************************
 * CAlertWindow::CAlertWindow
 *
 * Description
 *    Constructor. Initializes the window and the bitmap to display.
 *
 * Parameters
 *    x		   left position of window
 *    y            top position of window
 *    w            width of window
 *    h            height of window
 *    pszResBitmap resource ID of bitmap to display in alert
 *    bAllowExit   flag for whether or not user can close the alert
 *    uiResStatus  resource ID of string to display in status bar
 *                 when alert is dismissed
 *    pStatus      status bar in which to display uiResStatus string
 * 
 * Returns
 *    N/A
 ********************************************************************/
CAlertWindow::CAlertWindow(WORD x, WORD y, WORD w, WORD h, 
                           LPCTSTR pszResBitmap, BOOL bAllowExit, 
                           WORD uiResStatus, CStatusBar *pStatus)
              :CWindow(x, y, w, h)
{
    // set internal data
    _pStatus = pStatus;
    _bAllowExit = bAllowExit;

    // load bitmap to display in alert
    _pDDSBitmap = NULL;
    if (pszResBitmap)
    {
        _pDDSBitmap = CreateBitmapSurface(MAKEINTRESOURCE(pszResBitmap), 
                                          w, h,  FALSE, 0);
    }

    // load string to display in status bar
    LoadString(g_hInstance, uiResStatus, _szStatus, 
               sizeof(_szStatus) / sizeof(_szStatus[0]));

    // force cursor to be inside the window
    POINT ptCursor = QueryCursorPosition();
    if ((ptCursor.x < _rc.left) || (ptCursor.y < _rc.top) || 
        (ptCursor.x >= _rc.right) || (ptCursor.y >= _rc.bottom))
    {
        SetCursorPosition(x + (w / 2), y + (h / 2));
    }

    // capture the cursor
    EnableModal(this);
}

/********************************************************************
 * CAlertWindow::~CAlertWindow
 *
 * Description
 *    Destructor. Destroy the bitmap surface.
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CAlertWindow::~CAlertWindow(void)
{
    // destroy the bitmap
    if (_pDDSBitmap)
    {
        _pDDSBitmap->Release();
        _pDDSBitmap = NULL;
    }
}

/********************************************************************
 * CAlertWindow::Draw
 *
 * Description
 *    Draws the bitmap for the alert window.
 *
 * Parameters
 *    pDDS          destination direct draw surface (screen)
 * 
 * Returns
 *    S_OK          drawn successfully
 *    E_INVALIDARG  NULL pDDS
 ********************************************************************/
HRESULT CAlertWindow::Draw(LPDIRECTDRAWSURFACE pDDS)
{
    // validate parameters
    if (!pDDS)
    {
        return E_INVALIDARG;
    }

    // draw the bitmap
    if (_pDDSBitmap )
    {
        RECT rc;
        rc.left   = 0;
        rc.top    = 0;
        rc.right  = _rc.right - _rc.left;
        rc.bottom = _rc.bottom - _rc.top;
        pDDS->BltFast(_rc.left, _rc.top, _pDDSBitmap, &rc, 0); 
    }

    return S_OK;
}

/********************************************************************
 * CAlertWindow::Joystick
 *
 * Description
 *    Sets cursor to arrow cursor, constrains the cursor to within 
 *    the alert window, and dismisses the alert on controller button
 *    "A" if allowed.
 *
 * Parameters
 *    dwButtons       flags describing which buttons were pressed
 *    dwButtondsHelp  flags desribing which buttons are still down 
 *                    from last time
 *    x               x coorinate of current cursor position
 *    y               x coorinate of current cursor position
 * 
 * Returns
 *    S_OK            handled
 ********************************************************************/
HRESULT CAlertWindow::Joystick(DWORD dwButtons, DWORD dwButtonsHeld, 
                               WORD x, WORD y)
{
    // set cursor to arrow
    SetCursorType(CURSOR_POINTER);

    // keep cursor in window
    if (x < (_rc.left + 2))
    {
        x = _rc.left + 2;
    }  
    else if (x > (_rc.right - 2))
    {
        x = _rc.right - 2;
    }

    if (y < (_rc.top + 2))
    {
        y = _rc.top + 2;
    }
    else if (y > (_rc.bottom - 2))
    {
        y = _rc.bottom - 2;
    }

    SetCursorPosition(x, y);

    // check for user exiting alert
    if (_bAllowExit && (dwButtons & JOYSTICK_A))
    {
        // hide the window
        DisableModal(this);
        Hide();

        // set the status text on exit
        if (_pStatus)
        {
            _pStatus->SetText(_szStatus);
        }

        // destroy the alert window
        delete this;
    }

    return S_OK;
}

