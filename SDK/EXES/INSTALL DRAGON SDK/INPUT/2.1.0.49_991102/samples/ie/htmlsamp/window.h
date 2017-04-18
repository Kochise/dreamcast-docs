#ifndef __WINDOW_H              // guard against multiple inclusion
#define __WINDOW_H

/********************************************************************
 * window.h
 *
 * Description
 *    CWindow
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include <ddraw.h>              // DDraw data types and prototypes

/********************************************************************
 * class CWindow
 *
 * Description
 *    Base class for all "windows" in the game. A "window" is not 
 *    necessarily an HWND but is just any rectangle on the screen that 
 *    is drawn as a unit and has its own actions when the "cursor" is 
 *    over it.
 ********************************************************************/
class CWindow
{
    public:
        // Constructor/Destructor
        CWindow(WORD x, WORD y, WORD w, WORD h, BOOL bVisible = TRUE, WORD nScreen = 0);
        virtual ~CWindow(void);

        // Public functions
        void    Hide(void);
        void    Show(void);
        void    MoveRelative(short xDelta, short yDelta);
        BOOL    IsVisible(void);
        BOOL    PointInWindow(WORD x, WORD y);
        void    GetRect(RECT *prc);

        // Virtual functions
        virtual HRESULT Draw(LPDIRECTDRAWSURFACE pDDS, LPDIRECTDRAWSURFACE pDDSTexture);
        virtual HRESULT Draw(LPDIRECTDRAWSURFACE pDDS);
        virtual HRESULT Draw(HDC hdc);
        virtual HRESULT Joystick(DWORD dwButtons, DWORD dwButtonsHeld, WORD x, WORD y);
        virtual HRESULT Command(WORD nID);

    protected:
        RECT    _rc;            // rectangle of window on screen

    private:
        BOOL    _bVisible;      // visibility status of window
        WORD    _nScreen;       // screen number of window
};

#endif // __WINDOW_H

