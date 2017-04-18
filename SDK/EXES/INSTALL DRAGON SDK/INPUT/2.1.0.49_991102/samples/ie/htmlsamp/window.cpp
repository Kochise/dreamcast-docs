/********************************************************************
 * window.cpp
 *
 * Description
 *    CWindow - base class for all "windows" in the system. See
 *    draw.cpp and all classes derived from CWindow.
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "window.h"             // CWindow

/********************************************************************
 * CWindow::CWindow
 *
 * Description
 *    Constructor. Initializes the window position, visibility, and
 *    screen and adds it to the "window manager."
 *
 * Parameters
 *    x		left position of window
 *    y         top position of window
 *    w         width of window
 *    h         height of window
 *    bVisible  visibility of window
 *    nScreen   screen on which to display window
 * 
 * Returns
 *    N/A
 ********************************************************************/
CWindow::CWindow(WORD x, WORD y, WORD w, WORD h, BOOL bVisible, 
                 WORD nScreen)
{
    // set initial position
    _rc.left   = x;
    _rc.right  = x + w;
    _rc.top    = y;
    _rc.bottom = y + h;

    // set visibility and screen    
    _bVisible  = bVisible;
    _nScreen   = nScreen;

    // add to window manager
    AddWindow(this, nScreen);
}

/********************************************************************
 * CWindow::~CWindow
 *
 * Description
 *    Destructor. Removes the window from the "window manager."
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CWindow::~CWindow(void)
{
    // remove from window manager
    RemoveWindow(this, _nScreen);
}

/********************************************************************
 * CWindow::Hide
 *
 * Description
 *    Sets the visibility of the window to hidden.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void CWindow::Hide(void)
{
    // set visibility
    _bVisible = FALSE;
}

/********************************************************************
 * CWindow::Show
 *
 * Description
 *    Sets the visibility of the window to not hidden.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void CWindow::Show(void)
{
    // set visibility
    _bVisible = TRUE;
}

/********************************************************************
 * CWindow::MoveRelative
 *
 * Description
 *    Moves the window on the screen by the given relative amount.
 *
 * Parameters
 *    xDelta    amount to move the window horizontally
 *    yDelta    amount to move the window vertically
 * 
 * Returns
 *    None
 ********************************************************************/
void CWindow::MoveRelative(short xDelta, short yDelta)
{
    // move window
    _rc.left   += xDelta;
    _rc.right  += xDelta;
    _rc.top    += yDelta;
    _rc.bottom += yDelta;
}

/********************************************************************
 * CWindow::IsVisible
 *
 * Description
 *    Returns whether window is visible.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    TRUE      if window is visible
 *    FALSE     if window is hidden
 ********************************************************************/
BOOL CWindow::IsVisible(void)
{
    // return visiblity
    return _bVisible;
}

/********************************************************************
 * CWindow::PointInWindow
 *
 * Description
 *    Returns whether given point is within the window boundaries.
 *
 * Parameters
 *    In
 *    x         x cooridinate of point to check
 *    y         y cooridinate of point to check
 * 
 * Returns
 *    TRUE      if point is in window
 *    FALSE     if point is outside window
 ********************************************************************/
BOOL CWindow::PointInWindow(WORD x, WORD y)
{
    // return point in rectangle
    return (x >= _rc.left) && (x < _rc.right ) && 
           (y >= _rc.top ) && (y < _rc.bottom);
}

/********************************************************************
 * CWindow::GetRect
 *
 * Description
 *    Returns bounding rectangle of window
 *
 * Parameters
 *    prc       pointer to where to store bounding rectangle
 * 
 * Returns
 *    None
 ********************************************************************/
void CWindow::GetRect(RECT *prc)
{
    // validate parameter
    if (prc)
    {
        // set bounding rectangle
        *prc = _rc;
    }
}

/********************************************************************
 * CWindow::Draw
 *
 * Description
 *    Base Draw function does nothing. Must be overridden to actually
 *    draw. This version of the Draw function is for blting GDI data
 *    to the DDraw surface.
 *
 * Parameters
 *    pDDS        destination direct draw surface (screen)
 *    pDDSTexture GDI surface (GDI frame buffer)
 * 
 * Returns
 *    S_OK        handled by default
 ********************************************************************/
HRESULT CWindow::Draw(LPDIRECTDRAWSURFACE pDDS, 
                      LPDIRECTDRAWSURFACE pDDSTexture)
{
    // do nothing
    return S_OK;
}

/********************************************************************
 * CWindow::Draw
 *
 * Description
 *    Base Draw function does nothing. Must be overriddent to actually
 *    draw. This version of the Draw function is for standard DDraw
 *    work.
 *
 * Parameters
 *    pDDS        destination direct draw surface (screen)
 * 
 * Returns
 *    S_OK        handled by default
 ********************************************************************/
HRESULT CWindow::Draw(LPDIRECTDRAWSURFACE pDDS)
{
    // do nothing
    return S_OK;
}

/********************************************************************
 * CWindow::Draw
 *
 * Description
 *    Base Draw function does nothing. Must be overridden to actually
 *    draw. This version of the Draw function is for doing work that
 *    requires a device context (text drawing).
 *
 * Parameters
 *    hdc         destination device context
 * 
 * Returns
 *    S_OK        handled by default
 ********************************************************************/
HRESULT CWindow::Draw(HDC hdc)
{
    // do nothing
    return S_OK;
}

/********************************************************************
 * CWindow::Joystick
 *
 * Description
 *    Base Joystick function does nothing. Must be overridden to 
 *    actually respond to controller. Return S_OK if handled or
 *    S_FALSE if not handled (to give other windows a chance).
 *
 * Parameters
 *    dwButtons       flags describing which buttons were pressed
 *    dwButtondsHelp  flags desribing which buttons are still down 
 *                    from last time
 *    x               x coorinate of current cursor position
 *    y               x coorinate of current cursor position
 * 
 * Returns
 *    S_FALSE         not handled by default
 ********************************************************************/
HRESULT CWindow::Joystick(DWORD dwButtons, DWORD dwButtonsHeld, 
                          WORD x, WORD y)
{
    // do nothing
    return S_FALSE;
}

/********************************************************************
 * CWindow::Command
 *
 * Description
 *    Base Command function does nothing. Must be overriddent to 
 *    actually respond to command. Window must be registered to 
 *    tool bar before this will be called.
 *
 * Parameters
 *    nID         ID of command to process
 * 
 * Returns
 *    S_FALSE     not handled by default
 ********************************************************************/
HRESULT CWindow::Command(WORD nID)
{
    // do nothing
    return S_FALSE;
}

