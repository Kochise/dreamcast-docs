/********************************************************************
 * statbmp.cpp
 *
 * Description
 *    CStatusBitmap - class that handles the display and input of a
 *    status bitmap window (such as the icon that indicates secure 
 *    HTML page).
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "statbmp.h"            // CStatusBitmap

/********************************************************************
 * CStatusBitmap::CStatusBitmap
 *
 * Description
 *    Constructor. Initializes the window and the bitmap "icon strip"
 *    surface.
 *
 * Parameters
 *    x		   left position of window
 *    y            top position of window
 *    w            width of window
 *    h            height of window
 *    pszResBitmap resource ID of bitmap icon strip
 *    wBitmap      width of bitmap icon strip (whole bitmap)
 * 
 * Returns
 *    N/A
 ********************************************************************/
CStatusBitmap::CStatusBitmap(WORD x, WORD y, WORD w, WORD h, 
                             LPCTSTR pszResBitmap, WORD wBitmap)
              :CWindow(x, y, w, h)
{
    // initialize to 0 status
    _nStatus = 0;

    // determine number of icons in strip
    if (w)
    {
        _nNumBitmaps = wBitmap / w;
    }
    else
    {
        _nNumBitmaps = 0;
    }

    // load bitmap icon strip surface
    _pDDSBitmap = NULL;
    if (pszResBitmap)
    {
        _pDDSBitmap = CreateBitmapSurface(pszResBitmap, wBitmap, h,  
                                          FALSE, 0);
    }
}

/********************************************************************
 * CStatusBitmap::~CStatusBitmap
 *
 * Description
 *    Destructor. Destroy the bitmap "icon strip" surface.
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CStatusBitmap::~CStatusBitmap(void)
{
    // if bitmap surface was created, destroy it
    if (_pDDSBitmap)
    {
        _pDDSBitmap->Release();
        _pDDSBitmap = NULL;
    }
}

/********************************************************************
 * CStatusBitmap::SetBitmap
 *
 * Description
 *    Sets the current status.
 *
 * Parameters
 *    nStatus       status ID and index of icon in the bitmap icon
 *    strip.
 * 
 * Returns
 *    S_OK          status set successfully
 *    E_INVALIDARG  bogus status ID passed in
 ********************************************************************/
HRESULT CStatusBitmap::SetBitmap(WORD nStatus)
{
    // validate parameter 
    if (nStatus >= _nNumBitmaps)
    {
        return E_INVALIDARG;
    }

    // set status
    _nStatus = nStatus;

    return S_OK;
}

/********************************************************************
 * CStatusBitmap::Draw
 *
 * Description
 *    Draws the current status icon in the bitmap icon strip.
 *
 * Parameters
 *    pDDS          destination direct draw surface (screen)
 * 
 * Returns
 *    S_OK          drawn successfully
 *    E_INVALIDARG  NULL pDDS
 ********************************************************************/
HRESULT CStatusBitmap::Draw(LPDIRECTDRAWSURFACE pDDS)
{
    // validate parameters
    if (!pDDS)
    {
        return E_INVALIDARG;
    }

    // draw icon for current status in window's rectangle
    if (_pDDSBitmap)
    {
        RECT rc;
        rc.top    = 0;
        rc.bottom = _rc.bottom - _rc.top;
        rc.left   = _nStatus * (_rc.right - _rc.left);
        rc.right  = rc.left + (_rc.right - _rc.left);
        pDDS->BltFast(_rc.left, _rc.top, _pDDSBitmap, &rc, 0);
    }

    return S_OK;
}

/********************************************************************
 * CStatusBitmap::Joystick
 *
 * Description
 *    Sets cursor to arrow cursor. Ignores all button presses.
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
HRESULT CStatusBitmap::Joystick(DWORD dwButtons, DWORD dwButtonsHeld, 
                                WORD x, WORD y)
{
    // set cursor to arrow
    SetCursorType(CURSOR_POINTER);

    return S_OK;
}
