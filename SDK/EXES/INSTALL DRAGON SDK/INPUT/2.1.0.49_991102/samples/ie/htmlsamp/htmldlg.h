#ifndef __HTMLDLG_H             // guard against multiple inclusion
#define __HTMLDLG_H

/********************************************************************
 * htmldlg.h
 *
 * Description
 *    CHTMLDialog
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "window.h"             // base class CWindow
#include <mshtml.h>             // IHTMLDocument2

/********************************************************************
 * class CHTMLDialog
 *
 * Description
 *    Class for HTML dialog input and drawing for the HTML control.
 ********************************************************************/
class CHTMLDialog : public CWindow
{
    public:
        // Constructor/Destructor
        CHTMLDialog(HWND hwnd, IHTMLDocument2 *pHTMLDocument2);
        virtual ~CHTMLDialog(void);

        // Public functions     
        HRESULT GetActiveElement(IHTMLElement **ppElement);
        HRESULT DoInputIME(IHTMLElement *pElement, REFIID iid);
        HWND    GetHWND(void);

        // CWindow overrides
        HRESULT Draw(LPDIRECTDRAWSURFACE pDDS, LPDIRECTDRAWSURFACE pDDSTexture);
        HRESULT Joystick(DWORD dwButtons, DWORD dwButtonsHeld, WORD x, WORD y);

    private:
        // Internal functions
        LRESULT WndProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

        // Internal static functions
        static LRESULT StaticWndProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

    private:
        HWND            _hwnd;                  // window handle of the HTML dialog
        BOOL            _bCaptured;             // flag for having cursor captured
        IHTMLDocument2 *_pHTMLDocument2;        // HTML document of the HTML dialog
        WNDPROC         _pfnOldWndProc;         // original window procedure of the HTML dlg
};


#endif // __HTMLDLG_H
