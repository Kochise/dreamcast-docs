#ifndef __TOOLBAR_H             // guard against multiple inclusion
#define __TOOLBAR_H

/********************************************************************
 * toolbar.h
 *
 * Description
 *    TOOLBAR_BUTTON
 *    CToolBar
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "window.h"             // base class CWindow

/********************************************************************
 * struct TOOLBAR_BUTTON
 *
 * Description
 *    Structure defining the command ID and index into the bitmap
 *    "icon strip" for one tool bar button.
 ********************************************************************/
struct TOOLBAR_BUTTON
{
    WORD nID;                   // command ID for tool bar button
    WORD nBitmapIndex;          // index into bitmap icon strip for btn
};

/********************************************************************
 * class CToolBar
 *
 * Description
 *    Class for tool bar functionality for the HTML control.
 ********************************************************************/
class CToolBar : public CWindow
{
    public:
        // Constructor/Destructor
        CToolBar(WORD x, WORD y, WORD w, WORD h, LPCTSTR pszResBackgrnd, 
                 WORD wBitmap, WORD hBitmap, WORD nBitmap, LPCTSTR pszResButtons, 
                 TOOLBAR_BUTTON *pButtons);
        virtual ~CToolBar(void);

        // Public functions
        HRESULT SetOwnerWindow(CWindow *pWindow);
        void    ChangeButton(WORD nIDCur, WORD nBitmapIndexCur,
                             WORD nIDNew, WORD nBitmapIndexNew);

        // CWindow overrides
        HRESULT Draw(LPDIRECTDRAWSURFACE pDDS);
        HRESULT Joystick(DWORD dwButtons, DWORD dwButtonsHeld, WORD x, WORD y);

    private:
        // Internal functions
        void    BlockCursor(void);

    private:
        BOOL                _bCaptured;         // flag for having cursor captured
        WORD                _nRows;             // number of rows of buttons
        WORD                _nCols;             // number of columns of buttons
        WORD                _nCurRow;           // row index of selected button
        WORD                _nCurCol;           // column index of selected button
        WORD                _wBitmap;           // width of one icon in bitmap icon strip
        WORD                _hBitmap;           // height of one icon in bitmap icon strip
        TOOLBAR_BUTTON *    _pButtons;          // button descriptions
        CWindow *           _pWindow;           // window to which to send command messages
        LPDIRECTDRAWSURFACE _pDDSBackgrnd;      // bitmap surface of background of tool bar
        LPDIRECTDRAWSURFACE _pDDSButtons;       // bitmap surface of icon strip
};

/********************************************************************
 * Includes
 ********************************************************************/
#define ID_TB_END       0x0000  // flag for last button in TOOLBAR_BUTTON array
#define ID_TB_BREAK     0xffff  // flag for row (line) break in TOOLBAR_BUTTON array

#endif // __TOOLBAR_H
