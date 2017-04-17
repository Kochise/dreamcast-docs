#ifndef __STATBMP_H             // guard against multiple inclusion
#define __STATBMP_H

/********************************************************************
 * statbmp.h
 *
 * Description
 *    CStatusBitmap
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "window.h"             // base class CWindow

/********************************************************************
 * class CStatusBitmap
 *
 * Description
 *    Class for status bar functionality for the HTML control when 
 *    status is indicated by a bitmap instead of text. 
 ********************************************************************/
class CStatusBitmap : public CWindow
{
    public:
        // Constructor/Destructor
        CStatusBitmap(WORD x, WORD y, WORD w, WORD h, LPCTSTR pszResBitmap, WORD wBitmap);
        virtual ~CStatusBitmap(void);

        // Public functions
        HRESULT SetBitmap(WORD nStatus);

        // CWindow overrides
        HRESULT Draw(LPDIRECTDRAWSURFACE pDDS);
        HRESULT Joystick(DWORD dwButtons, DWORD dwButtonsHeld, WORD x, WORD y);

    private:
        LPDIRECTDRAWSURFACE _pDDSBitmap;        // bitmap surface of bitmap icon strip

    protected:
        WORD                _nStatus;           // current status (index into icon strip)
        WORD                _nNumBitmaps;       // total number of icons in icon strip
};

#endif // __STATBMP_H

