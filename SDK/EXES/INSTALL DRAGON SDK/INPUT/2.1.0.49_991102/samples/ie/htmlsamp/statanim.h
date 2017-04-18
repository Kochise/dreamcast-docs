#ifndef __STATANIM_H            // guard against multiple inclusion
#define __STATANIM_H

/********************************************************************
 * statanim.h
 *
 * Description
 *    CStatusAnimated
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "statbmp.h"            // base class CStatusBitmap

/********************************************************************
 * class CStatusAnimated
 *
 * Description
 *    Class for status bar functionality for the HTML control when 
 *    status is indicated by an animated bitmap instead of text. 
 ********************************************************************/
class CStatusAnimated : public CStatusBitmap
{
    public:
        // Constructor/Destructor
        CStatusAnimated(WORD x, WORD y, WORD w, WORD h, LPCTSTR pszResBitmap, WORD wBitmap);
        virtual ~CStatusAnimated(void);

        // Public functions
        HRESULT Animate(BOOL bAnimate);

        // CWindow overrides
        HRESULT Draw(LPDIRECTDRAWSURFACE pDDS);
        HRESULT Joystick(DWORD dwButtons, DWORD dwButtonsHeld, WORD x, WORD y);

    private:
        BOOL  _bAnimate;        // flag for whether window should animate or stay static
        ULONG _ulTickCount;     // time for next frame of animation
};

#endif // __STATANIM_H

