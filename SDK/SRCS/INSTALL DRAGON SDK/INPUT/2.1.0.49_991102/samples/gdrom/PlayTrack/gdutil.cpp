/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    GDUtil.cpp

Abstract:

    GD-ROM utility functions for the PlayTrack sample

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "PlayTrack.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    PlayTrack

Description:

    Plays the specified track(s) on the specified GDROM device

Arguments:

    HANDLE hGDROM            - The GDROM device from which to play the track(s)

    int    nStartTrackNumber - Starting track to play

    int    nEndTrackNumber   - Final track to play

    int    nRepeats          - Number of times to repeat the track(s)

Return Value:

    None

-------------------------------------------------------------------*/
void
PlayTrack(HANDLE hGDROM, int nStartTrackNumber, int nEndTrackNumber, int nRepeats)
{
    SEGACD_PLAYTRACK PlayTrack;
    DWORD            dwReturned;

    PlayTrack.dwStartTrack = nStartTrackNumber;
    PlayTrack.dwEndTrack   = nEndTrackNumber;
    PlayTrack.dwRepeat     = nRepeats;
    if(!DeviceIoControl(hGDROM, IOCTL_SEGACD_CD_PLAYTRACK, &PlayTrack, sizeof(PlayTrack), NULL, 0, &dwReturned, NULL))
        RetailOutput(TEXT("Error playing track.\r\n"));
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetCDVolume

Description:

    Gets the current volume of the specified GDROM device

Arguments:

    HANDLE hGDROM            - The GDROM device from which to get the volume

    UCHAR  *pucLeftVolume    - Fill this with left volume value

    UCHAR  *pucRightVolume   - Fill this with right volume value

Return Value:

    None

-------------------------------------------------------------------*/
void
GetCDVolume(HANDLE hGDROM, UCHAR* pucLeftVolume, UCHAR* pucRightVolume)
{
    DWORD          dwReturned;
    VOLUME_CONTROL Volume;

    DeviceIoControl(hGDROM, IOCTL_CDROM_GET_VOLUME, NULL, 0, &Volume, sizeof(VOLUME_CONTROL), &dwReturned, NULL);
    
    *pucLeftVolume  = Volume.PortVolume[0];
    *pucRightVolume = Volume.PortVolume[1];
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SetCDVolume

Description:

    Sets the volume of the specified GDROM device

Arguments:

    HANDLE hGDROM            - The GDROM device on which to set the volume.

    UCHAR  ucLeftVolume      - Set left channel volume to this value
    
    UCHAR  ucRightVolume     - Set right channel volume to this value

Return Value:

    None

-------------------------------------------------------------------*/
void
SetCDVolume(HANDLE hGDROM, UCHAR ucLeftVolume, UCHAR ucRightVolume)
{
    DWORD          dwReturned;
    VOLUME_CONTROL Volume;

    Volume.PortVolume[0] = ucLeftVolume;
    Volume.PortVolume[1] = ucRightVolume;

    DeviceIoControl(hGDROM, IOCTL_CDROM_SET_VOLUME, &Volume, sizeof(VOLUME_CONTROL), NULL, 0, &dwReturned, NULL);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    IsCDPlaying

Description:

    Checks if the specified GDROM device is currently playing

Arguments:

    HANDLE hGDROM            - The GDROM device to check

Return Value:

    TRUE if the GDROM is currently playing; false otherwise.

-------------------------------------------------------------------*/
BOOL
IsCDPlaying(HANDLE hGDROM)
{
    SEGACD_STATUS CDStatus;
    DWORD dwReturned;

    // This line is needed if using the emulator, because the emulator does not 
    // update its status register until it gets an actual command
    // Note: it is MUCH MUCH faster if you can avoid using IOCTL_STORAGE_CHECK_VERIFY
    DeviceIoControl(hGDROM, IOCTL_STORAGE_CHECK_VERIFY, NULL, 0, NULL, 0, &dwReturned, NULL);

    DeviceIoControl(hGDROM, IOCTL_SEGACD_GET_STATUS, NULL, 0, &CDStatus, sizeof(SEGACD_STATUS), &dwReturned, NULL);
    return (CDStatus.dwStatus == SEGACD_STAT_PLAY);
}