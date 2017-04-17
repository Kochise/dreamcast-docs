/********************************************************************
 * titlebar.cpp
 *
 * Description
 *    CTitleBar - class that handles the display and input of the HTML
 *    control title bar. It has an embedded toolbar for bringing up 
 *    the Go To URL HTML dialog.
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "titlebar.h"           // CTitleBar
#include "toolbar.h"            // CToolBar
#include "htmldoc.h"            // CHTMLDoc

/********************************************************************
 * Defines
 ********************************************************************/
#define W_TOOLBAR       27      // width of embedded tool bar
#define W_BUTTONS       24      // width of btns in embedded tool bar
#define H_BUTTONS       25      // height of btns in embedded tool bar
#define H_MARGIN        5       // vertical margin 
#define NUM_BUTTONS     1       // number of btns in embedded tool bar

/********************************************************************
 * CTitleBar::CTitleBar
 *
 * Description
 *    Constructor. Initializes the window and the embedded tool bar.
 *
 * Parameters
 *    x		   left position of window
 *    y            top position of window
 *    w            width of window
 *    h            height of window
 *    pszResBitmap resource ID of background bitmap
 * 
 * Returns
 *    N/A
 ********************************************************************/
CTitleBar::CTitleBar(WORD x, WORD y, WORD w, WORD h, COLORREF clrFore, 
                     LPCTSTR pszResBitmap)
          :CStatusBar(x + W_TOOLBAR, y, w - W_TOOLBAR, h, clrFore, NULL, 
                      H_MARGIN)
{
    // create the bitmap surface instead of letting the base class do 
    // it because the status bar part of the title bar does not span
    // the entire width of the window
    if (pszResBitmap)
    {
        _pDDSBitmap = CreateBitmapSurface(pszResBitmap, w, h, FALSE, 0);
    }

    // initialize embedded tool bar
    TOOLBAR_BUTTON tbButtons[] = 
    {
        { ID_GO,       0 },
        { ID_TB_END,   0 },
    };

    _pToolbar = new CToolBar(x, y, W_TOOLBAR, h, NULL, W_BUTTONS, 
                             H_BUTTONS, NUM_BUTTONS, 
                             MAKEINTRESOURCE(IDB_TITLEBARBTN), 
                             tbButtons);
}

/********************************************************************
 * CTitleBar::~CTitleBar
 *
 * Description
 *    Destructor. Destroy the embedded tool bar.
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CTitleBar::~CTitleBar(void)
{
    // base class will clean up bitmap surface

    // clean up embedded tool bar
    if (_pToolbar)
    {
        _pToolbar->SetOwnerWindow(NULL);
        delete _pToolbar;
        _pToolbar = NULL;
    }
}

/********************************************************************
 * CTitleBar::SetOwnerWindow
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
HRESULT CTitleBar::SetOwnerWindow(CWindow *pWindow)
{
    // set new owner
    if (_pToolbar)
    {
        _pToolbar->SetOwnerWindow(pWindow);
    }

    return S_OK;
}

/********************************************************************
 * CTitleBar::Draw
 *
 * Description
 *    Overrides the CStatusBar implementation to draw the entire
 *    window background instead of just the part under the title text.
 *
 * Parameters
 *    pDDS          destination direct draw surface (screen)
 * 
 * Returns
 *    S_OK          drawn successfully
 *    E_INVALIDARG  NULL pDDS
 ********************************************************************/
HRESULT CTitleBar::Draw(LPDIRECTDRAWSURFACE pDDS)
{
    // validate parameters
    if (!pDDS)
    {
        return E_INVALIDARG;
    }

    // draw background for whole window
    if (_pDDSBitmap)
    {
        RECT rc;
        rc.left   = 0;
        rc.top    = 0;
        rc.right  = _rc.right - _rc.left + W_TOOLBAR;
        rc.bottom = _rc.bottom - _rc.top;
        pDDS->BltFast(_rc.left - W_TOOLBAR, _rc.top, _pDDSBitmap, 
                      &rc, 0); 
    }

    return S_OK;
}

