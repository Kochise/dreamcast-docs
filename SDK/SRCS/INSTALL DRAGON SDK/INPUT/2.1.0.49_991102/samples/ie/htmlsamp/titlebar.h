#ifndef __TITLEBAR_H            // guard against multiple inclusion
#define __TITLEBAR_H

/********************************************************************
 * titlebar.h
 *
 * Description
 *    CTitleBar
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "status.h"             // base class CStatusBar

/********************************************************************
 * Forward declarations
 ********************************************************************/
class CToolBar;                 // toolbar.h
class CHTMLDoc;                 // htmldoc.h

/********************************************************************
 * class CTitleBar
 *
 * Description
 *    Class for title bar functionality for the HTML control. 
 ********************************************************************/
class CTitleBar : public CStatusBar
{
    public:
        // Constructor/Destructor
        CTitleBar(WORD x, WORD y, WORD w, WORD h, COLORREF clrFore, LPCTSTR pszResBitmap);
        virtual ~CTitleBar(void);

        // Public functions
        HRESULT SetOwnerWindow(CWindow *pWindow);

        // CWindow overrides
        HRESULT Draw(LPDIRECTDRAWSURFACE pDDS);

    private:
        CToolBar * _pToolbar;   // embedded tool bar
};

#endif // __TITLEBAR_H
