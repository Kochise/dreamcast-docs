#ifndef __ALERT_H               // guard against multiple inclusion
#define __ALERT_H

/********************************************************************
 * alert.h
 *
 * Description
 *    CAlertWindow
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
 * class CAlertWindow
 *
 * Description
 *    Class for pop up alert window functionality for the game and the
 *    HTML control. The alert can be set to not allow the user to
 *    dismiss it (dismissal through code only).
 ********************************************************************/
class CAlertWindow : public CWindow
{
    public:
        // Constructor/Destructor
        CAlertWindow(WORD x, WORD y, WORD w, WORD h, LPCTSTR pszResBitmap, 
                     BOOL bAllowExit = TRUE, WORD uiResStatus = 0, CStatusBar *pStatus = NULL);
        virtual ~CAlertWindow(void);

        // CWindow overrides
        HRESULT Draw(LPDIRECTDRAWSURFACE pDDS);
        HRESULT Joystick(DWORD dwButtons, DWORD dwButtonsHeld, WORD x, WORD y);

    private:
        BOOL                _bAllowExit;                // flag for whether user can escape out of alert 
        CStatusBar *        _pStatus;                   // status bar in which to display text after alert dismissal
        TCHAR               _szStatus[MAX_PATH];        // status text to display after alert dismissal
        LPDIRECTDRAWSURFACE _pDDSBitmap;                // bitmap to display for alert
};

#endif // __ALERT_H
