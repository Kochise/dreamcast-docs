/********************************************************************
 * status.cpp
 *
 * Description
 *    CStatusBar - class that handles the display and input of a text
 *    status bar (such as the status bar for the HTML control and the
 *    status bars for the Battleship game window).
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "status.h"             // CStatusBar

/********************************************************************
 * Defines
 ********************************************************************/
#define X_SBMARGIN    4         // text margin
#define W_SBBORDER    2         // border width

/********************************************************************
 * CStatusBar::CStatusBar
 *
 * Description
 *    Constructor. Initializes the window, the background bitmap 
 *    surface and the font.
 *
 * Parameters
 *    x		   left position of window
 *    y            top position of window
 *    w            width of window
 *    h            height of window
 *    pszResBitmap resource ID of bitmap background
 *    nMarin       vertical margin
 * 
 * Returns
 *    N/A
 ********************************************************************/
CStatusBar::CStatusBar(WORD x, WORD y, WORD w, WORD h, COLORREF clrFore, 
                       LPCTSTR pszResBitmap, WORD nMargin)
           :CWindow(x, y, w, h)
{
    // initialize internal data
    _clrFore = clrFore;
    _pszText = NULL;
    _nMargin = nMargin;

    // load background bitmap
    _pDDSBitmap = NULL;
    if (pszResBitmap)
    {
        _pDDSBitmap = CreateBitmapSurface(pszResBitmap, w, h, FALSE, 0);
    }

    // create font for status text
    LOGFONT lf;
    memset(&lf, 0, sizeof(lf));
    lf.lfHeight         = (_rc.bottom - _rc.top) - ((2 * _nMargin) + 
                          W_SBBORDER + W_SBBORDER);
    lf.lfWeight         = FW_NORMAL;
    lf.lfCharSet        = DEFAULT_CHARSET;
    lf.lfOutPrecision   = OUT_DEFAULT_PRECIS;
    lf.lfClipPrecision  = CLIP_DEFAULT_PRECIS;
    lf.lfQuality        = DEFAULT_QUALITY;
    lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    _tcscpy(lf.lfFaceName, FONT_NAME);

    _hFont = CreateFontIndirect(&lf);
}

/********************************************************************
 * CStatusBar::~CStatusBar
 *
 * Description
 *    Destructor. Destroy the bitmap surface, the font, and the 
 *    last status text.
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CStatusBar::~CStatusBar(void)
{
    // destroy text
    if (_pszText)
    {
        delete [] _pszText;
        _pszText = NULL;
    }

    // destroy background bitmap surface
    if (_pDDSBitmap)
    {
        _pDDSBitmap->Release();
        _pDDSBitmap = NULL;
    }

    // destroy font
    if (_hFont)
    {
        DeleteObject(_hFont);
        _hFont = NULL;
    }
}

/********************************************************************
 * CStatusBar::SetText
 *
 * Description
 *    Sets the current status text with given string.
 *
 * Parameters
 *    pszText   new status text
 * 
 * Returns
 *    S_OK      handled
 ********************************************************************/
HRESULT CStatusBar::SetText(LPCTSTR pszText)
{
    // destroy previous text
    if (_pszText)
    {
        delete [] _pszText;
    }

    // allocate and copy new text
    if (pszText)
    {
        _pszText = new TCHAR[_tcslen(pszText) + 1];
        if (_pszText)
        {
            _tcscpy(_pszText, pszText);
        }
    }
    else
    {
        _pszText = NULL;
    }

    return S_OK;
}

/********************************************************************
 * CStatusBar::SetText
 *
 * Description
 *    Sets the current status text by loading requested string 
 *    resource; does nothing if string not found in resources.
 *
 * Parameters
 *    hInst     hInstance of resource
 *    uiRes     resource ID of string
 * 
 * Returns
 *    S_OK      handled
 ********************************************************************/
HRESULT CStatusBar::SetText(HINSTANCE hInst, UINT uiRes)
{
    TCHAR szBuf[MAX_PATH];

    // load string and set text
    if (LoadString(hInst, uiRes, szBuf, sizeof(szBuf) / sizeof(szBuf[0])))
    {
        return SetText(szBuf);
    }
}

/********************************************************************
 * CStatusBar::Draw
 *
 * Description
 *    Draws the background bitmap.
 *
 * Parameters
 *    pDDS          destination direct draw surface (screen)
 * 
 * Returns
 *    S_OK          drawn successfully
 *    E_INVALIDARG  NULL pDDS
 ********************************************************************/
HRESULT CStatusBar::Draw(LPDIRECTDRAWSURFACE pDDS)
{
    // validate parameters
    if (!pDDS)
    {
        return E_INVALIDARG;
    }

    // draw background bitmap
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
 * CStatusBar::Draw
 *
 * Description
 *    Draw the status text (other verion of Draw has already been
 *    called to draw the background).
 *
 * Parameters
 *    hdc           destination device context
 * 
 * Returns
 *    S_OK          drawn successfully
 *    E_INVALIDARG  NULL hdc
 ********************************************************************/
HRESULT CStatusBar::Draw(HDC hdc)
{
    // validate parameters
    if (!hdc)
    {
        return E_INVALIDARG;
    }

    // draw text if not blank
    if (_pszText && *_pszText)
    {
        // set text color, background mode, and font
        COLORREF clrForeOld = SetTextColor(hdc, RGB(0xFF,0xFF,0xFF));
        int      nModeOld   = SetBkMode(hdc, TRANSPARENT);
        HFONT    fontOld    = (HFONT)SelectObject(hdc, _hFont);

        // calculate drawing rectangle
        RECT r = _rc;
        r.left   += (X_SBMARGIN + W_SBBORDER);
        r.right  -= (X_SBMARGIN + W_SBBORDER);
        r.top    += (_nMargin + W_SBBORDER);
        r.bottom -= (_nMargin + W_SBBORDER);

        // move the rectangle up, and draw the shadow text
        OffsetRect(&r, 0, -1);
        ExtTextOut(hdc, r.left, r.top, ETO_CLIPPED, &r, _pszText, 
                   _tcslen(_pszText), NULL);

        // move the rectangle down, and draw over the shadow text
        SetTextColor(hdc, _clrFore);
        OffsetRect(&r, 1, 1);
        ExtTextOut(hdc, r.left, r.top, ETO_CLIPPED, &r, _pszText, 
                   _tcslen(_pszText), NULL);

        // restore text color, background mode, and font
        SelectObject(hdc, fontOld);
        SetBkMode(hdc, nModeOld);
        SetTextColor(hdc, clrForeOld);
    }

    return S_OK;
}

/********************************************************************
 * CStatusBar::Joystick
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
HRESULT CStatusBar::Joystick(DWORD dwButtons, DWORD dwButtonsHeld, 
                             WORD x, WORD y)
{
    // set cursor to arrow
    SetCursorType(CURSOR_POINTER);

    return S_OK;
}
