#ifndef __GAMEFLD_H             // guard against multiple inclusion
#define __GAMEFLD_H

/********************************************************************
 * gamefld.h
 *
 * Description
 *    CGameField
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "window.h"             // base class CWindow

/********************************************************************
 * Forward declarations
 ********************************************************************/
class CStatusBar;               // status.h

/********************************************************************
 * Defines - game field size
 ********************************************************************/
#define C_GAMEFLD       15
#define R_GAMEFLD       16

/********************************************************************
 * class CTitleBar
 *
 * Description
 *    Class for Battleship game field functionality. 
 ********************************************************************/
class CGameField : public CWindow
{
    public:
        // Constructor/Destructor
        CGameField(WORD x, WORD y, WORD w, WORD h, CStatusBar *pStatus, 
                   CStatusBar *pShotStatus);
        virtual ~CGameField(void);

        // CWindow overrides
        HRESULT Draw(LPDIRECTDRAWSURFACE pDDS);
        HRESULT Joystick(DWORD dwButtons, DWORD dwButtonsHeld, WORD x, WORD y);

    private:
        // Internal functsions
        void    BlockCursor(void);
        void    HideShip(WORD wShip, WORD nSize);
        void    HideShips(void);
        void    ShowShips(void);
        void    Fire(void);
        void    UpdateShotStatus(void);

    private:
        WORD                _xCurrent;                          // x position of selected square
        WORD                _yCurrent;                          // y position of selected square
        WORD                _nShots;                            // number of shots remaining
        WORD                _nMisses;                           // number of misses
        WORD                _nHits;                             // number of hits
        WORD                _nShipsAlive;                       // number of ships left 
        BOOL                _bCaptured;                         // flag for having cursor captured
        WORD                _Field[C_GAMEFLD][R_GAMEFLD];       // status of blocks in grid
        TCHAR               _szShots[MAX_PATH];                 // status text for shots remaining, etc.
        TCHAR               _szMiss[MAX_PATH];                  // status text for missed shot
        TCHAR               _szHit[MAX_PATH];                   // status text for hit shot
        TCHAR               _aszSunk[4][MAX_PATH];              // status text for sunk ships
        CStatusBar *        _pGameStatus;                       // status bar for hit/miss/sunk text
        CStatusBar *        _pShotStatus;                       // status bar for shots remaining text
        LPDIRECTDRAWSURFACE _pDDSBoard;                         // bitmap surface for background of grid
        LPDIRECTDRAWSURFACE _pDDSBitmap;                        // bitmap surface for icon strip 
};

#endif // __GAMEFLD_H

