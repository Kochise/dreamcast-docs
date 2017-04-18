#ifndef TKIME_H
#define TKIME_H

class CTkIme
{
    private:
        BOOL fInit;
    public:
        CTkIme( HINSTANCE            hInst,
                LPDIRECTDRAW        lpDD,
                LPDIRECTDRAWSURFACE lpDDSPrimary,
                LPDIRECTDRAWSURFACE lpDDSBack     );
        ~CTkIme( void );
        HRESULT GetImeInput( LPTSTR               lpBuffer,
                             LPDIRECTINPUTDEVICE2 pdidevice2JoystickCaller,
                             BYTE                *prgvButtonsCaller         );
};

#endif
