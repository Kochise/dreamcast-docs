#ifndef __STATUS_H              // guard against multiple inclusion
#define __STATUS_H

/********************************************************************
 * Includes
 ********************************************************************/
#include "window.h"             // base class CWindow

/********************************************************************
 * class CToolBar
 *
 * Description
 *    Class for status bar functionality for the game and the HTML
 *    control. 
 ********************************************************************/
class CStatusBar : public CWindow
{
    public:
        // Constructor/Destructor
        CStatusBar(WORD x, WORD y, WORD w, WORD h, COLORREF clrFore, LPCTSTR pszResBitmap, WORD nMargin = 0);
        virtual ~CStatusBar(void);

        // Public functions
        HRESULT SetText(LPCTSTR pszText);
        HRESULT SetText(HINSTANCE hInst, UINT uiRes);

        // CWindow overrides
        HRESULT Draw(LPDIRECTDRAWSURFACE pDDS);
        HRESULT Draw(HDC hdc);
        HRESULT Joystick(DWORD dwButtons, DWORD dwButtonsHeld, WORD x, WORD y);

    protected:
        COLORREF            _clrFore;           // text color
        LPTSTR              _pszText;           // current text to display
        HFONT               _hFont;             // font to display text
        LPDIRECTDRAWSURFACE _pDDSBitmap;        // bitmap surface of background
        WORD                _nMargin;           // left margin of text
};

#endif // __STATUS_H

