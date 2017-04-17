#ifndef __DIALER_H              // guard against multiple inclusion
#define __DIALER_H

/********************************************************************
 * dialer.h
 *
 * Description
 *    CDialer
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include <ras.h>                // RAS data types and prototypes

/********************************************************************
 * class CDialer
 *
 * Description
 *    Wrapper class for RAS connection functionality.
 ********************************************************************/
class CDialer
{
    public:
        // Constructor/Destructor
        CDialer();
        virtual ~CDialer(void);

        // Public functions
        HRESULT Dial(void);
        void    HangUp(void);
        HRESULT IsInit();
        HRESULT IsConnect();

    private:
        // Internal functions
        static  LRESULT CALLBACK WndProc(HWND hwnd, UINT wm, WPARAM wParam, LPARAM lParam);
        HRESULT InitDialParams(RASDIALPARAMS &RasDialParams);
        HRESULT InitRasEntry(void);

    private:
        BOOL        _fInit;                             // flag for object having been initlized
        BOOL        _fConnect;                          // flag for RAS connection established
        HRASCONN    _hRasConn;                          // handle to RAS connection
        TCHAR       _achEntryName[RAS_MaxEntryName+1];  // RAS entry name
};

#endif // __DIALER_H
