/********************************************************************
 * toolbar.cpp
 *
 * Description
 *    CToolBar - class thatt handles the display and input of a tool
 *    bar. Commands are sent to an owner window for actual processing.
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "toolbar.h"            // CToolBar

/********************************************************************
 * CToolBar::CToolBar
 *
 * Description
 *    Constructor. Initializes the window, the background bitmap 
 *    surface and the positons of the buttons.
 *
 * Parameters
 *    x		     left position of window
 *    y              top position of window
 *    w              width of window
 *    h              height of window
 *    pszResBackgrnd resource ID of bitmap background
 *    wBitmap        width of buttons pszResButtons bitmap
 *    numBitmap      number of icons in icon strip of pszResButtons
 *    pszResButtons  resource ID of bitmap icon strip of buttons
 *    pButtons       descriptions of buttons to go into tool bar
 * 
 * Returns
 *    N/A
 ********************************************************************/
CToolBar::CToolBar(WORD x, WORD y, WORD w, WORD h, LPCTSTR pszResBackgrnd, 
                   WORD wBitmap, WORD hBitmap, WORD numBitmap, 
                   LPCTSTR pszResButtons, TOOLBAR_BUTTON *pButtons)
         :CWindow(x, y, w, h)
{
    // initialize internal data
    _bCaptured  = FALSE;
    _pWindow    = NULL;

    _nCurCol = 0xffff;
    _nCurRow = 0xffff;

    // load background bitmap surface
    _pDDSBackgrnd = NULL;
    if (pszResBackgrnd)
    {
        _pDDSBackgrnd = CreateBitmapSurface(pszResBackgrnd, w, h,  
                                            FALSE, 0);
    }

    // load buttons bitmap icon strip surface
    _pDDSButtons = NULL;
    if (pszResButtons)
    {
        _pDDSButtons = CreateBitmapSurface(pszResButtons, wBitmap, hBitmap, 
                                           FALSE, 0);
    }

    // calculate size of icons in icon strip
    if (numBitmap)
    {
        _wBitmap = wBitmap / numBitmap;
    }
    else
    {
        _wBitmap = 0;
    }
    _hBitmap  = hBitmap;

    // calculate positions of buttons 
    _pButtons = NULL;
    _nCols    = 0;
    _nRows    = 0;

    if (pButtons)
    {
        WORD nCurCols = 0;
        WORD i = 0;

        while (TRUE)
        {
            // look for row (line) break and end of buttons, counting 
            // rows and columns as we go
            if ((pButtons[i].nID == ID_TB_END) ||
                (pButtons[i].nID == ID_TB_BREAK))
            {
                if (nCurCols > _nCols)
                {
                    _nCols = nCurCols;
                }
                _nRows++;

                if (pButtons[i].nID == ID_TB_END)
                {
                    break;
                }

                nCurCols = 0;
            }
            else
            {
                nCurCols++;
            }

            i++;
        } 

        if (_nCols && _nRows)
        {
            // allocate space for rows and columns
            _pButtons = new TOOLBAR_BUTTON[_nCols * _nRows];
            if (_pButtons)
            {
                // initialize button data
                memset(_pButtons, 0, sizeof(TOOLBAR_BUTTON) * _nCols * _nRows);

                WORD x = 0;
                WORD y = 0;
                i = 0;

                while (TRUE)
                {
                    // look for row (line) break and end of buttons
                    if (pButtons[i].nID == ID_TB_END)
                    {
                        break;
                    }

                    if (pButtons[i].nID == ID_TB_BREAK)
                    {
                        x = 0;
                        y++;
                    }
                    else
                    {
                        // store button data
                        TOOLBAR_BUTTON *pButton = _pButtons + 
                                                  (y * _nCols + x);
                        pButton->nID = pButtons[i].nID;
                        pButton->nBitmapIndex = pButtons[i].nBitmapIndex;
                        x++;
                    }
                    i++;
                }
            }
        }
    }
}

/********************************************************************
 * CToolBar::~CToolBar
 *
 * Description
 *    Destructor. Destroy the bitmap surfaces, the button data, and
 *    release the cursor if the tool bar has it captured.
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CToolBar::~CToolBar(void)
{
    // release cursor capture if needed
    if (_bCaptured)
    {
        ReleaseCursorCapture(this);
        _bCaptured = FALSE;
    }

    // destroy background bitmap surface
    if (_pDDSBackgrnd)
    {
        _pDDSBackgrnd->Release();
        _pDDSBackgrnd = NULL;
    }

    // destroy buttons bitmap surface
    if (_pDDSButtons)
    {
        _pDDSButtons->Release();
        _pDDSButtons = NULL;
    }
}

/********************************************************************
 * CToolBar::SetOwnerWindow
 *
 * Description
 *    Sets the window to receive command notifications. There can be
 *    only one owner at a time.
 *
 * Parameters
 *    pWindow   window to receive notifications
 * 
 * Returns
 *    S_OK      handled
 ********************************************************************/
HRESULT CToolBar::SetOwnerWindow(CWindow *pWindow)
{
    // set new owner
    _pWindow = pWindow;

    return S_OK;
}

/********************************************************************
 * CStatusBar::ChangeButton
 *
 * Description
 *    Changes the specified tool bar button to a new button (command
 *    ID and icon index). Ignored if button is not found.
 *
 * Parameters
 *    nIDCur          existing command ID
 *    nBitmapIndexCur existing icon index
 *    nIDNew          new command ID
 *    nBitmapIndexNew new icon index
 * 
 * Returns
 *    None
 ********************************************************************/
void CToolBar::ChangeButton(WORD nIDCur, WORD nBitmapIndexCur,
                            WORD nIDNew, WORD nBitmapIndexNew)
{
    if (_pButtons)
    {
        // find existing command ID and icon index
        TOOLBAR_BUTTON *pButton = _pButtons;
        while (pButton->nID != ID_TB_END)
        {
            if ((pButton->nID == nIDCur) &&
                (pButton->nBitmapIndex == nBitmapIndexCur))
            {
                // set new command ID and icon index
                pButton->nID          = nIDNew;
                pButton->nBitmapIndex = nBitmapIndexNew;
                return;
            }

            pButton++;
        }
    }
}

/********************************************************************
 * CToolBar::Draw
 *
 * Description
 *    Draws the background bitmap and the tool bar buttons.
 *
 * Parameters
 *    pDDS          destination direct draw surface (screen)
 * 
 * Returns
 *    S_OK          drawn successfully
 *    E_INVALIDARG  NULL pDDS
 ********************************************************************/
HRESULT CToolBar::Draw(LPDIRECTDRAWSURFACE pDDS)
{
    // validate parameters
    if (!pDDS)
    {
        return E_INVALIDARG;
    }

    RECT rc;

    // draw the background
    if (_pDDSBackgrnd)
    {
        rc.left   = 0;
        rc.top    = 0;
        rc.right  = _rc.right - _rc.left;
        rc.bottom = _rc.bottom - _rc.top;
        pDDS->BltFast(_rc.left, _rc.top, _pDDSBackgrnd, &rc, 0); 
    }

    // draw the buttons
    if (_pDDSButtons && _pButtons)
    {
        WORD x;
        WORD y;
        WORD left;
        WORD top;

        // draw row (line) of buttons
        for (y = 0; y < _nRows; y++)
        {
            // draw one button in row
            for (x = 0; x < _nCols; x++)
            {
                TOOLBAR_BUTTON *pButton = _pButtons + (y * _nCols + x);
                if (pButton->nID)
                {
                    // if current button, draw with border
                    if (_bCaptured && (_nCurCol == x) && (_nCurRow == y))
                    {
                        rc.left   = pButton->nBitmapIndex * _wBitmap;
                        rc.right  = rc.left + _wBitmap;
                        rc.top    = 0;
                        rc.bottom = _hBitmap;

                        left = _rc.left + x * _wBitmap + 3;
                        top  = _rc.top  + y * _hBitmap + 3;
                    }
                    // if not current button, draw normal
                    else
                    {
                        rc.left   = pButton->nBitmapIndex * _wBitmap + 2;
                        rc.right  = rc.left + _wBitmap - 4;
                        rc.top    = 2;
                        rc.bottom = _hBitmap - 2;

                        left = _rc.left + x * _wBitmap + 5;
                        top  = _rc.top  + y * _hBitmap + 5;
                    }

                    pDDS->BltFast (left, top, _pDDSButtons, &rc, 0);
                }
            }
        }
    }

    return S_OK;
}

/********************************************************************
 * CToolBar::Joystick
 *
 * Description
 *    Sets cursor to arrow cursor. Handles controller buttons:
 *      A      send command
 *      start  send command
 *      left   select button to left
 *      right  select button to right
 *      up     select button above
 *      down   select button below
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
 *    S_FALSE         not handled because cursor is not over tool bar
 ********************************************************************/
HRESULT CToolBar::Joystick(DWORD dwButtons, DWORD dwButtonsHeld, 
                           WORD x, WORD y)
{
    // check for cursor over tool bar
    if (!((x >= _rc.left) && (x < _rc.right) &&
          (y >= _rc.top)  && (y < _rc.bottom)))
    {
        // no longer over tool bar, release capture
        if (_bCaptured)
        {
            _bCaptured = FALSE;
            ReleaseCursorCapture(this);
            _nCurCol = 0xffff;
            _nCurRow = 0xffff;
        }

        // let another window handle joystick
        return S_FALSE;
    }

    // set to arrow cursor
    SetCursorType(CURSOR_POINTER);

    // capture the cursor
    if (!_bCaptured)
    {
        _bCaptured = TRUE;
        SetCursorCapture(this);
    }

    // determine selected button
    WORD nCurCol = (x - _rc.left - 3) / _wBitmap;
    WORD nCurRow = (y - _rc.top  - 3) / _hBitmap;

    _nCurCol = nCurCol;
    _nCurRow = nCurRow;

    if (!_pButtons)
    {
        return S_OK;
    }

    // on A or Start, send the command to the owning window
    if (dwButtons & (JOYSTICK_A | JOYSTICK_START))
    {
        if (_pWindow)
        {
            _pWindow->Command(_pButtons[_nCurRow * _nCols + _nCurCol].nID);
        }
    }
    // on left, go to the previous button (if one exists), set the 
    // cursor to the newly selected button
    else if (dwButtons & JOYSTICK_LA)
    {
        if (_nCurCol)
        {
            WORD nCurCol = _nCurCol;
            if (nCurCol >= _nCols)
            {
                nCurCol = _nCols;
            }

            nCurCol--;

            while (nCurCol && !_pButtons[_nCurRow * _nCols + nCurCol].nID)
            {
                nCurCol--;
            }

            if (_pButtons[_nCurRow * _nCols + nCurCol].nID && (nCurCol != _nCurCol))
            {
                _nCurCol = nCurCol;
                BlockCursor();
            }
        }
    }

    // on right, go to the next button (if one exists), set the 
    // cursor to the newly selected button
    else if (dwButtons & JOYSTICK_RA)
    {
        if ((_nCurCol < (_nCols - 1)) && _pButtons[_nCurRow * _nCols + (_nCurCol+1)].nID)
        {
            _nCurCol++;
            BlockCursor();
        }
    }

    // on up, go to the previous row (if one exists), set the 
    // cursor to the newly selected button
    if (dwButtons & JOYSTICK_UA)
    {
        if (_nCurRow)
        {
            WORD nCurRow = _nCurRow;
            if (nCurRow >= _nRows)
            {
                nCurRow = _nRows;
            }
        
            nCurRow--;

            while (nCurRow && !_pButtons[nCurRow * _nCols + _nCurCol - _nCols].nID)
            {
                nCurRow--;
            }

            if (_pButtons[nCurRow * _nCols + _nCurCol].nID && 
                (_nCurRow != nCurRow))
            {
                _nCurRow = nCurRow;
                BlockCursor();
            }
        }
    }

    // on down, go to the next row (if one exists), set the 
    // cursor to the newly selected button
    else if (dwButtons & JOYSTICK_DA)
    {
        if ((_nCurRow < (_nRows - 1 )) && _pButtons[(_nCurRow + 1) * _nCols + 
            _nCurCol + _nCols].nID)
        {
            _nCurRow++;
            BlockCursor();
        }
    }

    return S_OK;
}

/********************************************************************
 * CToolBar::BlockCursor
 *
 * Description
 *    Move the cursor to be in the middle of the selected button.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void CToolBar::BlockCursor(void)
{
    // calculate new cursor position
    WORD x = _nCurCol * _wBitmap + (_wBitmap / 2) + (WORD)_rc.left + 3;
    WORD y = _nCurRow * _hBitmap + (_hBitmap / 2) + (WORD)_rc.top  + 3;

    // set it
    SetCursorPosition(x, y);
}
