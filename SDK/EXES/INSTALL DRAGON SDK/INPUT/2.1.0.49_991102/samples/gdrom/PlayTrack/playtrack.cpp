/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    PlayTrack.cpp

Abstract:

    PlayTrack Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "PlayTrack.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    PrintUsage

Description:

    Outputs the usage of this program to the standard output stream

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void PrintUsage()
{
    RetailOutput(TEXT("Usage:\r\n"));
    RetailOutput(TEXT("    s playtrack [options] <starting track number> [<ending track number> [<repeats>]]\r\n\r\n"));

    RetailOutput(TEXT("    Options:\r\n\r\n"));

    RetailOutput(TEXT("        -s <left vol> <right vol>   - Set volume to specified values\r\n"));
    RetailOutput(TEXT("        -g                          - Display current GD-DA volume\r\n"));
    RetailOutput(TEXT("        -w                          - Wait until playback is finished before exiting\r\n"));
    RetailOutput(TEXT("        -?                          - Print this message\r\n\r\n"));
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.  Play the specified
    tracks on the GDROM device.

Arguments:

    hInstance           - HInstance of the process

    hPrev               - HInstance of another process running the program

    LPTSTR lpCmdLine    - Pointer to command line string

    nCmdShow            - Whether the app should be shown (ignored)

Return Value:

    We normally return the wParam value from the WM_QUIT message.  If
    there's a failure upon initialization, we just return 0.

-------------------------------------------------------------------*/
extern "C" int APIENTRY 
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine, int nCmdShow)
{
    HANDLE hGDROM;
    UCHAR  ucLeftVolume;
    UCHAR  ucRightVolume;
    BOOL   fWaitFlag    = FALSE;
    BOOL   fIgnoreError = FALSE;
    TCHAR* pFlag;
    int    nRepeat      = 0;
    int    nStart       = 0;
    int    nEnd;
    
    // Create a handle to the GDROM drive.
    hGDROM = CreateFile(TEXT("\\Device\\CDROM0"), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL );
    if (hGDROM == INVALID_HANDLE_VALUE)
    {
        RetailOutput(TEXT("Error opening CD-rom\r\n"));
        return -1;
    }

    pFlag = _tcstok(pCmdLine, TEXT(" "));
    if(pFlag == NULL)
    {
        PrintUsage();
        return 0;
    }

    while(pFlag != NULL)
    {
        if(*pFlag == TEXT('-'))
        {
            ++pFlag;
            switch(*pFlag)
            {
            case TEXT('?'):
                PrintUsage();
                return 0;

            case TEXT('w'):
            case TEXT('W'):
                fWaitFlag = TRUE;
                break;

            case TEXT('g'):
            case TEXT('G'):
                GetCDVolume(hGDROM, &ucLeftVolume, &ucRightVolume);
                RetailOutput(TEXT("Current GD-DA Volume: Left[%d] Right[%d]\r\n"), ucLeftVolume, ucRightVolume);
                fIgnoreError = TRUE;
                break;

            case TEXT('s'):
            case TEXT('S'):
                pFlag = _tcstok(NULL, TEXT(" "));
                if(pFlag == NULL)
                    goto error;
                ucLeftVolume = (UCHAR)_ttoi(pFlag);
                pFlag = _tcstok(NULL, TEXT(" "));
                if(pFlag == NULL)
                    goto error;
                ucRightVolume = (UCHAR)_ttoi(pFlag);
                SetCDVolume(hGDROM, ucLeftVolume, ucRightVolume);
                fIgnoreError = TRUE;
                break;
            }
        }
        else
        {
            // Note that there is no checking done to see if the track specified is a valid
            // track number or if it is a GD-DA or a data track.  This can be done by reading
            // the TOC information using IOCTL_CDROM_READ_TOC.
            nStart = nEnd = _ttoi(pFlag);

            // See if an end track was specified
            pFlag  = _tcstok(NULL, TEXT(" "));
            if(pFlag != NULL)
            {
                nEnd = _ttoi(pFlag);

                // Check if a repeat count was specified
                pFlag = _tcstok(NULL, TEXT(" "));
                if(pFlag != NULL)
                {
                    nRepeat = _ttoi(pFlag);
                }
            }
        }
        pFlag = _tcstok(NULL, TEXT(" "));
    }
    if(nStart < 1)
    {
        if(fIgnoreError)
        {
            CloseHandle(hGDROM);
            return 0;
        }
error:
        RetailOutput(TEXT("Error - not enough or invalid parameters.\r\n\r\n"));
        PrintUsage();
        CloseHandle(hGDROM);
        return 0;
    }

    PlayTrack(hGDROM, nStart, nEnd, nRepeat);

    if(fWaitFlag)
    {
        // wait until track is done playing
        while(IsCDPlaying(hGDROM))
        {
            Sleep(100);
        }
        RetailOutput(TEXT("GD-DA Playback complete\r\n"));
    }

    CloseHandle(hGDROM);
 
    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return 0;
}