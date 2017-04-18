/********************************************************************
 * statanim.cpp
 *
 * Description
 *    CStatusAnimated - class that handles the display and input of
 *    an animated status bitmap window (such as the icon that "spins"
 *    while an HTML page is loading).
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "statanim.h"           // CStatusAnimated

/********************************************************************
 * Defines
 ********************************************************************/
#define TIMEOUT_CHANGE_FRAME    100

/********************************************************************
 * CStatusAnimated::CStatusAnimated
 *
 * Description
 *    Constructor. Initializes the status bitmap and the animation
 *    data.
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
CStatusAnimated::CStatusAnimated(WORD x, WORD y, WORD w, WORD h, 
                                 LPCTSTR pszResBitmap, WORD wBitmap)
                :CStatusBitmap(x, y, w, h, pszResBitmap, wBitmap)
{
    // initialize animation data to not animated
    _ulTickCount = 0;
    _bAnimate    = FALSE;
}

/********************************************************************
 * CStatusAnimated::~CStatusAnimated
 *
 * Description
 *    Destructor. 
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CStatusAnimated::~CStatusAnimated(void)
{
    // do nothing
}

/********************************************************************
 * CStatusAnimated::Animate
 *
 * Description
 *    Sets the animation status.
 *
 * Parameters
 *    bAnimate      TRUE to start animating status, FALSE to stop it
 * 
 * Returns
 *    S_OK          animation state changed
 *    S_FALSE       animation state unchanged
 ********************************************************************/
HRESULT CStatusAnimated::Animate(BOOL bAnimate)
{
    // validate parameters
    if (_bAnimate == bAnimate)
    {
        return S_FALSE;
    }

    // set animation status
    _bAnimate = bAnimate;

    // if animating, set the next time out and the next frame to display
    if (_bAnimate && (_nNumBitmaps > 1))
    {
        _nStatus = 1;
        _ulTickCount = GetTickCount() + TIMEOUT_CHANGE_FRAME;
    }
    // if not animating, set the frame to the static frame
    else
    {
        _nStatus = 0;
    }

    return S_OK;
}

/********************************************************************
 * CStatusAnimated::Draw
 *
 * Description
 *    Potentially advances the animation frame, and draws the current 
 *    frame.
 *
 * Parameters
 *    pDDS          destination direct draw surface (screen)
 * 
 * Returns
 *    S_OK          drawn successfully
 *    other         from base class call
 ********************************************************************/
HRESULT CStatusAnimated::Draw(LPDIRECTDRAWSURFACE pDDS)
{
    // if in animation mode, check for frame advancement
    if (_bAnimate)
    {
        ULONG ulTickCount = GetTickCount();
        // time to advance
        if (ulTickCount > _ulTickCount)
        {
            // at end of icon strip, wrap back to first animation 
            // frame
            if (_nStatus == (_nNumBitmaps - 1))
            {
                _nStatus = 1;
            }
            // go to next animation frame
            else
            {
                _nStatus++;
            }

            // set next animation frame change time
            _ulTickCount = ulTickCount + TIMEOUT_CHANGE_FRAME;
        }
    }

    return CStatusBitmap::Draw(pDDS);
}

/********************************************************************
 * CStatusAnimated::Joystick
 *
 * Description
 *    Sets cursor to arrow cursor. In the game version of the sample,
 *    pressing the "A" controller button will unload the HTML control.
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
HRESULT CStatusAnimated::Joystick(DWORD dwButtons, DWORD dwButtonsHeld, 
                                  WORD x, WORD y)
{
#ifdef GAME_SAMPLE
    if (dwButtons & JOYSTICK_A)
    {
        SendMessage(g_hwndGame, WM_TOGGLEHTML, 0, 0);
    }
#endif  // GAME_SAMPLE

    return CStatusBitmap::Joystick(dwButtons, dwButtonsHeld, x, y);
}
