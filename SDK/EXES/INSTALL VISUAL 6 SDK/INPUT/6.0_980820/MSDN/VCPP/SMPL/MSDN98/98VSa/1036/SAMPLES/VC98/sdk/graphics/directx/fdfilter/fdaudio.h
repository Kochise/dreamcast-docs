#ifndef __AUDIO_H__
#define __AUDIO_H__


BOOL InitSoundDevices( BOOL );
BOOL ReOpenSoundDevices( BOOL );
BOOL FormatCodeToText( DWORD, LPSTR, int );
BOOL FormatCodeToWFX( DWORD, PWAVEFORMATEX );
void DisableFormatCode( PFORMATDATA, DWORD );
BOOL WriteSilenceToOutput( DWORD, DWORD );

void ClearDSDeviceList( PDSDEVICEDESC * );
void FillDeviceCombo( HWND, PDSDEVICEDESC );

void ScanAvailableDSFormats( void );
void ScanAvailableDSCFormats( void );
void CloseDSDevice( void );
void CloseDSCDevice(BOOL fBufferOnly);

BOOL InitBuffers( void );
BOOL DestroyBuffers( void );
BOOL StartBuffers( void );
BOOL StopBuffers( void );

DWORD WINAPI ThreadProcessInput( LPVOID );

#endif


