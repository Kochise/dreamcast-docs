/********************************************************************
 * gamefld.cpp
 *
 * Description
 *    CGameField - class that handles the display and input of the
 *    Battleshiop game window.
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers

#ifdef GAME_SAMPLE              

/********************************************************************
 * Includes
 ********************************************************************/
#include "gamefld.h"            // CGameField
#include "status.h"             // CStatusBar
#include "alert.h"              // CAlertWindow

/********************************************************************
 * Defines - flags contents of game field blocks
 ********************************************************************/
#define BLOCK_SHIPMASK      0x0007      // mask for ship type
#define BLOCK_NOSHIP        0x0000      // no ship in block
#define BLOCK_BATTLESHIP    0x0001      // battleship piece in block
#define BLOCK_CRUISER       0x0002      // cruiser piece in block
#define BLOCK_DESTROYER     0x0003      // destroyer piece in block
#define BLOCK_SUBMARINE     0x0004      // submarine piece in block

#define BLOCK_FRONT         0x0010      // front of ship in block
#define BLOCK_MIDDLE1       0x0020      // middle of ship in block
#define BLOCK_MIDDLE2       0x0040      // middle of ship in block
#define BLOCK_MIDDLE3       0x0080      // middle of ship in block
#define BLOCK_END           0x0100      // back of ship in block

#define BLOCK_HORZ          0x0000      // ship in block is horizontal
#define BLOCK_VERT          0x1000      // ship in block is vertical

#define BLOCK_SUNK          0x8000      // ship in block has been sunk
#define BLOCK_HIT           0x4000      // block has been hit

/********************************************************************
 * Defines - numbers of types of ships
 ********************************************************************/
#define NUM_BATTLESHIP      1           
#define NUM_CRUISER         2
#define NUM_DESTROYER       3
#define NUM_SUBMARINE       4
#define NUM_TYPESHIPS       4

/********************************************************************
 * Defines - sizes of types of ships
 ********************************************************************/
#define SIZE_BATTLESHIP     5
#define SIZE_CRUISER        4
#define SIZE_DESTROYER      3
#define SIZE_SUBMARINE      2

/********************************************************************
 * Defines - block sizes and icons in block sizes
 ********************************************************************/
#define BITMAP_HEIGHT       20
#define BITMAP_WIDTH        BITMAP_HEIGHT

#define BLOCK_WIDTH         (BITMAP_WIDTH + 2)
#define BLOCK_HEIGHT        (BITMAP_HEIGHT + 2)

/********************************************************************
 * Defines - offsets into bitmap icon strip
 ********************************************************************/
#define OFFSET_HIT          0
#define OFFSET_MISS         20
#define OFFSET_SELECTION    40
#define OFFSET_HSUBFRONT    60
#define OFFSET_HDESTFRONT   100
#define OFFSET_HCRUISFRONT  160
#define OFFSET_HBSHIPFRONT  240
#define OFFSET_VERTICAL     280
#define OFFSET_END          620

/********************************************************************
 * Defines - shots
 ********************************************************************/
#define NUM_SHOTS           25
#define NUM_SHOTS_HIT       2
#define NUM_SHOTS_SINK      3

/********************************************************************
 * CGameField::CGameField
 *
 * Description
 *    Constructor. Initializes the window and the bitmaps to display.
 *    Also loads status strings and sets up the game.
 *
 * Parameters
 *    x		   left position of window
 *    y            top position of window
 *    w            width of window
 *    h            height of window
 *    pGameStatus  status bar for hit/miss messages
 *    pShotStatus  status bar for num shots/kills messags
 * 
 * Returns
 *    N/A
 ********************************************************************/
CGameField::CGameField(WORD x, WORD y, WORD w, WORD h, CStatusBar *pGameStatus, CStatusBar *pShotStatus)
	   :CWindow(x, y, w, h)
{
    // set internal data
    _pGameStatus = pGameStatus;
    _pShotStatus = pShotStatus;

    _bCaptured = FALSE;

    // load background and blocks icon strip bitmap surfaces
    _pDDSBoard  = CreateBitmapSurface(MAKEINTRESOURCE(IDB_BOARD), w, h, FALSE, 0);
    _pDDSBitmap = CreateBitmapSurface(MAKEINTRESOURCE(IDB_BLOCKS), OFFSET_END, BITMAP_HEIGHT,  FALSE, 0);

    // load status messages
    LoadString(g_hInstance, IDS_SHOTS, _szShots, sizeof(_szShots) / sizeof(_szShots[0]));
    LoadString(g_hInstance, IDS_MISS,  _szMiss,  sizeof(_szMiss)  / sizeof(_szMiss[0]));
    LoadString(g_hInstance, IDS_HIT,   _szHit,   sizeof(_szHit)   / sizeof(_szHit[0]));

    WORD i;
    for (i = 0; i < 4; i++)
    {
	LoadString(g_hInstance, IDS_SUNK_FIRST + i, _aszSunk[i], sizeof(_aszSunk[i])  / sizeof(_aszSunk[i][0]));
    }

    // hide the ships in the grid
    HideShips();
}

/********************************************************************
 * CGameField::~CGameField
 *
 * Description
 *    Destructor. Destroy the bitmap surfaces and release capture.
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CGameField::~CGameField(void)
{
    // release cursor capture
    if (_bCaptured)
    {
	ReleaseCursorCapture(this);
	_bCaptured = FALSE;
    }

    // destroy bitmap surfaces
    if (!_pDDSBoard)
    {
	_pDDSBoard->Release();   
	_pDDSBoard = NULL;
    }

    if (!_pDDSBitmap)
    {
	_pDDSBitmap->Release();   
	_pDDSBitmap = NULL;
    }

}

/********************************************************************
 * CGameField::Draw
 *
 * Description
 *    Draws the game field background and the status (ships, hits, 
 *    misses) of each of the blocks in the field.
 *
 * Parameters
 *    pDDS          destination direct draw surface (screen)
 * 
 * Returns
 *    S_OK          drawn successfully
 *    E_INVALIDARG  NULL pDDS
********************************************************************/
HRESULT CGameField::Draw(LPDIRECTDRAWSURFACE pDDS)
{
    // validate parameters
    if (!pDDS)
    {
	return E_INVALIDARG;
    }

    // make sure we have something to draw
    if (!_pDDSBoard)
    {
	return S_OK;
    }

    WORD x;
    WORD y;

    DDBLTFX ddbltfx;
    ddbltfx.dwSize = sizeof(ddbltfx);

    // draw background bitmap
    RECT rc;
    rc.left   = 0;
    rc.top    = 0;
    rc.right  = _rc.right - _rc.left;
    rc.bottom = _rc.bottom - _rc.top;
    pDDS->BltFast (_rc.left, _rc.top, _pDDSBoard, &rc, 0);

    if (!_pDDSBitmap)
    {
	return S_OK;
    }

    // show current selection frame
    WORD left;
    WORD top;
    RECT rcSrc;

    if (_nShots && _nShipsAlive && (_xCurrent != 0xffff) && (_yCurrent != 0xffff))
    {
	left = _xCurrent * BLOCK_WIDTH  + 2 + (WORD)_rc.left;
	top  = _yCurrent * BLOCK_HEIGHT + 2 + (WORD)_rc.top;

	rcSrc.left   = OFFSET_SELECTION;
	rcSrc.right  = rcSrc.left + BITMAP_WIDTH;
	rcSrc.top    = 0;
	rcSrc.bottom = BITMAP_HEIGHT;
	pDDS->BltFast(left, top, _pDDSBitmap, &rcSrc, 0); // DDBLTFAST_SRCCOLORKEY);
    }

    WORD wBlock;
    WORD wShip;

    // show status of all blocks
    for (y = 0; y < R_GAMEFLD; y++)
    {
	for (x = 0; x < C_GAMEFLD; x++)
	{
            // calculate current block rectangle
	    left = x * BLOCK_WIDTH + 2 + (WORD)_rc.left;
	    top  = y * BLOCK_WIDTH + 2 + (WORD)_rc.top;
	    rcSrc.left = 0;
	    rcSrc.right = BITMAP_WIDTH;
	    rcSrc.top    = 0;
	    rcSrc.bottom = BITMAP_HEIGHT;

            // only draw interior for current selection
	    if ((x == _xCurrent) && (y == _yCurrent))
	    {
		rcSrc.left ++;
		rcSrc.right --;
		rcSrc.top ++;
		rcSrc.bottom --;
		left ++;
		top  ++;
	    }

            // get status flags for block
	    wBlock = _Field[x][y];

            // if no hits, there is nothing to draw
	    if (!(wBlock & BLOCK_HIT))
	    {
		continue;
	    }

            // find icon in strip to draw for block
	    wShip = wBlock & BLOCK_SHIPMASK;
	    if (wShip)
	    {
		WORD n = 0;
                // if ship has been sunk, show actual ship picture
		if (wBlock & BLOCK_SUNK)
		{
		    if (wShip == BLOCK_SUBMARINE)
		    {
			rcSrc.left  += OFFSET_HSUBFRONT;
			rcSrc.right += OFFSET_HSUBFRONT;
			n = 1;
		    }
		    else if (wShip == BLOCK_DESTROYER)
		    {
			rcSrc.left  += OFFSET_HDESTFRONT;
			rcSrc.right += OFFSET_HDESTFRONT;
			n = 2;
		    }
		    else if (wShip == BLOCK_CRUISER)
		    {
			rcSrc.left  += OFFSET_HCRUISFRONT;
			rcSrc.right += OFFSET_HCRUISFRONT;
			n = 3;
		    }
                    else if (wShip == BLOCK_BATTLESHIP)
                    {
                        rcSrc.left  += OFFSET_HBSHIPFRONT;
                        rcSrc.right += OFFSET_HBSHIPFRONT;
                        n = 4;
                    }

		    if (wBlock & BLOCK_VERT)
		    {
			rcSrc.left  += OFFSET_VERTICAL;
			rcSrc.right += OFFSET_VERTICAL;
		    }

		    if (wBlock & BLOCK_MIDDLE1)
		    {
			rcSrc.left  += BITMAP_WIDTH;
			rcSrc.right += BITMAP_WIDTH;
		    }
		    else if (wBlock & BLOCK_MIDDLE2)
		    {
			rcSrc.left  += BITMAP_WIDTH * 2;
			rcSrc.right += BITMAP_WIDTH * 2;
		    }
		    else if (wBlock & BLOCK_MIDDLE3)
		    {
			rcSrc.left  += BITMAP_WIDTH * 3;
			rcSrc.right += BITMAP_WIDTH * 3;
		    }
		    else if (wBlock & BLOCK_END)
		    {
			rcSrc.left  += BITMAP_WIDTH * n;
			rcSrc.right += BITMAP_WIDTH * n;
		    }

                    // draw ship piece block
		    pDDS->BltFast(left, top, _pDDSBitmap, &rcSrc, 0); 
		}
		else
		{
                    // block has been hit but ship not sunk, draw hit
		    rcSrc.left  += OFFSET_HIT;
		    rcSrc.right += OFFSET_HIT;
		    pDDS->BltFast(left, top, _pDDSBitmap, &rcSrc, 0); 
		}
	    }
	    else
	    {
                // block has been hit, but no ship at block, draw miss
		rcSrc.left  += OFFSET_MISS;
		rcSrc.right += OFFSET_MISS;
		pDDS->BltFast(left, top, _pDDSBitmap, &rcSrc, 0); 
	    }
	}
    }

    return S_OK;
}

/********************************************************************
 * CGameField::Joystick
 *
 * Description
 *    Sets cursor to gun sight cursor, captures or releases the cursor
 *    as needed. Also checks for shots and movement.
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
 *    S_FALSE         not in window
 ********************************************************************/
HRESULT CGameField::Joystick(DWORD dwButtons, DWORD dwButtonsHeld, WORD x, WORD y)
{
    // check if cursor is no longer in window
    if (!((x >= _rc.left) && (x < _rc.right) &&
	  (y >= _rc.top)  && (y < _rc.bottom)))
    {
	if (_bCaptured)
	{
            // left the window, so release capture
	    _bCaptured = FALSE;
	    ReleaseCursorCapture(this);
	    _xCurrent = 0xffff;
	    _yCurrent = 0xffff;
	}

	return S_FALSE;
    }

    // set to gun sight cursor
    SetCursorType(CURSOR_GAME);

    // capture cursor
    if (!_bCaptured)
    {
	_bCaptured = TRUE;
	SetCursorCapture(this);
    }

    // find selected block
    _xCurrent = (x - _rc.left - 2) / BLOCK_WIDTH;
    _yCurrent = (y - _rc.top  - 2) / BLOCK_HEIGHT;

    // check for shot (A button or trigger button)
    if (dwButtons & (JOYSTICK_A | JOYSTICK_RTRIG | JOYSTICK_LTRIG))
    {
        // make sure we have something still to do
	if (_nShots && _nShipsAlive)
	{
            // fire at current block and update status
	    Fire();
	    UpdateShotStatus();

            // if all shiops have been sunk or out of shots, display
            // message to user
	    if (!_nShipsAlive)
	    {
		new CAlertWindow(160, 140, 300, 200, MAKEINTRESOURCE(IDB_WINNER), TRUE, 
				 IDS_WINNER, _pGameStatus);
	    }
	    else if (!_nShots)
	    {
		new CAlertWindow(210, 140, 200, 200, MAKEINTRESOURCE(IDB_LOSER), TRUE, 
				 IDS_LOSER, _pGameStatus);
                // show all the ships so the user can see where the ships were hiding
		ShowShips();
	    }
	}
    }
    else 
    {
        // handle moving through the directional button
	if (dwButtons & JOYSTICK_LA)
	{
	    if (_xCurrent)
	    {
		_xCurrent--;
		BlockCursor();
	    }
	}
	else if (dwButtons & JOYSTICK_RA)
	{
	    if (_xCurrent < (C_GAMEFLD - 1))
	    {
		_xCurrent++;
		BlockCursor();
	    }
	}

	if (dwButtons & JOYSTICK_UA)
	{
	    if (_yCurrent)
	    {
		_yCurrent--;
		BlockCursor();
	    }
	}
	else if (dwButtons & JOYSTICK_DA)
	{
	    if (_yCurrent < (R_GAMEFLD - 1 ))
	    {
		_yCurrent++;
		BlockCursor();
	    }
	}
    }

    return S_OK;
}

/********************************************************************
 * CGameField::BlockCursor
 *
 * Description
 *    When selected block is changed due to directional button instead
 *    of joystick, move the cursor to the middle of the newly selected
 *    block.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void CGameField::BlockCursor(void)
{
    // move cursor to middle of selected block
    WORD x = _xCurrent * BLOCK_WIDTH  + 1 + BLOCK_WIDTH  / 2 + (WORD)_rc.left;
    WORD y = _yCurrent * BLOCK_HEIGHT + 1 + BLOCK_HEIGHT / 2 + (WORD)_rc.top;
    SetCursorPosition(x, y);
}

/********************************************************************
 * CGameField::HideShip
 *
 * Description
 *    Hides given ship in the game field so that it's not touching
 *    (catty-corner is okay) any other ships.
 *
 * Parameters
 *    wShip    type of ship to hide
 *    nSize    number of blocks the ship occupies
 * 
 * Returns
 *    None
 ********************************************************************/
void CGameField::HideShip(WORD wShip, WORD nSize)
{
    BOOL  bOkay;
    BOOL  bVertical;
    WORD  xStart;
    WORD  yStart;
    WORD  x;
    WORD  y;
    WORD  nCount;
    short xDelta;
    short yDelta;

    // keep trying new location until a valid location is found
    do
    {
        // assume this position will work
	bOkay = TRUE;

        // randomly make the ship vertical or horizontal
	bVertical = Random() & 0x01;

        // randomly pick a start position
	xStart = (WORD) (Random() % (bVertical ? C_GAMEFLD : (C_GAMEFLD - nSize)));
	yStart = (WORD) ((Random() % (bVertical ? (R_GAMEFLD - nSize) : R_GAMEFLD)) + nSize - 1);

	xDelta = bVertical ?  0 : 1;
	yDelta = bVertical ? -1 : 0;
	nCount = nSize;

        // location is not valid if block immediately before or after ship
        // is occupied
	if (bVertical)
	{
	    if (yStart && _Field[xStart][yStart-1])
	    {
		bOkay = FALSE;
		continue;    
	    }
 
	    if (((yStart + nSize) < R_GAMEFLD) && _Field[xStart][yStart+nSize])
	    {
		bOkay = FALSE;
		continue;    
	    }
	}
	else
	{
	    if (xStart && _Field[xStart-1][yStart])
	    {
		bOkay = FALSE;
		continue;    
	    }
 
	    if (((xStart + nSize) < C_GAMEFLD) && _Field[xStart+nSize][yStart])
	    {
		bOkay = FALSE;
		continue;    
	    }
	}

        // location is invalid if any block next to any ship's block is 
        // occupied
	for (x = xStart, y = yStart; nCount; x += xDelta, y += yDelta, nCount--)
	{
	    if (_Field[x][y])
	    {
		bOkay = FALSE;
		break;
	    }

	    if (x && _Field[x-1][y])
	    {
		bOkay = FALSE;
		break;
	    }

	    if ((x < (C_GAMEFLD - 1)) && _Field[x+1][y])
	    {
		bOkay = FALSE;
		break;
	    }

	    if (y && _Field[x][y-1])
	    {
		bOkay = FALSE;
		break;
	    }

	    if ((y < (R_GAMEFLD - 1 )) && _Field[x][y+1])
	    {
		bOkay = FALSE;
		break;
	    }
	}
    } while (!bOkay);

    // got a valid location for ship; mark the blocks' status
    nCount = nSize;
    for (x = xStart, y = yStart; nCount; x += xDelta, y += yDelta, nCount--)
    {
	_Field[x][y] |= wShip;

	if (nCount == nSize)
	{
	    _Field[x][y] |= BLOCK_FRONT;
	}
	else if (nCount == 1)
	{
	    _Field[x][y] |= BLOCK_END;
	}
	else if (nCount < nSize)
	{
	    _Field[x][y] |= (BLOCK_MIDDLE1 << (nSize - nCount - 1));
	}

	if (bVertical)
	{
	    _Field[x][y] |= BLOCK_VERT;
	}
    }
}

/********************************************************************
 * CGameField::HideShips
 *
 * Description
 *    Hides all the ships in the game field so that no two are 
 *    touching.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void CGameField::HideShips(void)
{
    // initialize game data and position
    _xCurrent = 0;
    _yCurrent = 0;

    _nShots  = NUM_SHOTS;
    _nHits   = 0;
    _nMisses = 0;
    _nShipsAlive = NUM_BATTLESHIP + NUM_CRUISER + NUM_DESTROYER + NUM_SUBMARINE;

    UpdateShotStatus();
    BlockCursor();

    // clear game field
    memset(&_Field, 0, sizeof(_Field));

    WORD i;
    WORD j;
    WORD nShips = NUM_BATTLESHIP;
    WORD nSize  = SIZE_BATTLESHIP;

    // hide 1 battleship, 2 cruisers, 3 destroyers, and 4 submarines
    for (i = 0; i < NUM_TYPESHIPS; i++)
    {
	for (j = 0; j < nShips; j++)
	{
	    HideShip(i + 1, nSize);
	}

	nShips++;
	nSize--;
    }
}

/********************************************************************
 * CGameField::ShowShips
 *
 * Description
 *    Mark all blocks with ship pieces as sunk so next draw will show
 *    all ships.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void CGameField::ShowShips(void)
{
    WORD x;
    WORD y;

    // for each block, if it contains a ship piece, mark it hit
    // and sunk
    for (y = 0; y < R_GAMEFLD; y++)
    {
	for (x = 0; x < C_GAMEFLD; x++)
	{
	    if (_Field[x][y] & BLOCK_SHIPMASK)
	    {
		_Field[x][y] |= (BLOCK_HIT | BLOCK_SUNK);
	    }
	}
    }
}

/********************************************************************
 * CGameField::Fire
 *
 * Description
 *    Marks the current block as hit (if not already hit), and checks
 *    for ship or water hit. Also checks for ship sinking if a ship
 *    piece was hit.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void CGameField::Fire(void)
{
    // clear previous status text
    if (_pGameStatus)
    {
	_pGameStatus->SetText(NULL);
    }

    WORD x = _xCurrent;
    WORD y = _yCurrent;

    // if block has already been hit, ignore the fire
    if (_Field[x][y] & BLOCK_HIT)
    {
	return;
    }

    // mark the block as hit
    _Field[x][y] |= BLOCK_HIT;

    WORD wShip  = (_Field[x][y] & BLOCK_SHIPMASK);

    // see if the block contains a ship piece
    if (!wShip)    
    {
        // no ship, decrement shots remaining, display Miss message

	_nShots --;

	if (_pGameStatus)
	{
	    _pGameStatus->SetText(_szMiss);
	}

	_nMisses++;

	return;
    }

    // ship hit, give more shots
    _nShots += NUM_SHOTS_HIT;

    // check for sinking
    _nHits++;

    short xDelta = 0;
    short yDelta = 0;

    if (_Field[x][y] & BLOCK_VERT)
    {
	yDelta = -1;
    }
    else
    {
	xDelta = 1;
    }

    while (!(_Field[x][y] & BLOCK_FRONT))
    {
	x -= xDelta;
	y -= yDelta;
    }

    // should be at start of ship now
    while (TRUE)
    {
	if (!(_Field[x][y] & BLOCK_HIT))
	{
            // ship not sunk, display hit message
	    if (_pGameStatus)
	    {
		_pGameStatus->SetText(_szHit);
	    }

	    return;
	}

	if (_Field[x][y] & BLOCK_END)
	{
	    break;
	}

	x += xDelta;
	y += yDelta;
    }

    // ship is sunk
    _nShots += NUM_SHOTS_SINK;
    _nShipsAlive--;

    // mark whole ship sunk
    while (TRUE)
    {
	_Field[x][y] |= BLOCK_SUNK;

	if (_Field[x][y] & BLOCK_FRONT)
	{
	    break;
	}

	x -= xDelta;
	y -= yDelta;
    }

    // display sunk message
    if (_pGameStatus)
    {
	_pGameStatus->SetText(_aszSunk[wShip-1]);
    }

    return;
}

/********************************************************************
 * CGameField::UpdateShotStatus
 *
 * Description
 *    Displays number of shots remaining, number of shots that hit
 *    ship pieces, number of shots that hit water, and the number of
 *    ships sunk in the status bar.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void CGameField::UpdateShotStatus(void)
{
    // display shots remaining, shots hit, shots missed, and ships
    // killed
    if (_pShotStatus)
    {
	TCHAR szBuffer[MAX_PATH];
	_stprintf(szBuffer, _szShots, _nShots, _nHits, _nMisses, 
		  (NUM_BATTLESHIP + NUM_CRUISER + NUM_DESTROYER + NUM_SUBMARINE) - _nShipsAlive);
	_pShotStatus->SetText(szBuffer);
    }

}

#endif // GAME_SAMPLE
