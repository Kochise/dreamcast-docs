/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    PlayVideo.cpp

Abstract:

    PlayVideo Sample Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "PlayVideo.hpp"

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    PlayMovie

Description:

    Load and play the media specified in the 'tszMediaName' parameter.

Arguments:

    TCHAR *tszMediaName     - Name of the file to load and play.

Return Value:

    TRUE on success, FALSE on failure

-------------------------------------------------------------------*/
BOOL
PlayMovie(TCHAR *tszMediaName)
{
    IMediaControl *pmediacontrol = NULL;
    IGraphBuilder *pgraphbuilder = NULL;
    IMediaEventEx *pmediaevent   = NULL;
    BOOL          fRet           = TRUE;
    long          lEventCode;

    g_errLast = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IMediaControl, (void **)&pmediacontrol);
    if (CheckError(TEXT("CoCreateInstance for CLSID_FilterGraph")))
    {
        fRet = FALSE;
        goto doneplaymovie;
    }

    g_errLast = pmediacontrol->QueryInterface(IID_IGraphBuilder, (void **)&pgraphbuilder);
    if (CheckError(TEXT("QueryInterface for IGraphBuilder")))
    {
        fRet = FALSE;
        goto doneplaymovie;
    }

    g_errLast = pmediacontrol->QueryInterface(IID_IMediaEventEx, (void **)&pmediaevent);
    if (CheckError(TEXT("QueryInterface for IMediaEventEx")))
    {
        fRet = FALSE;
        goto doneplaymovie;
    }

    RetailOutput(TEXT("RenderFile...\r\n"));
    g_errLast = pgraphbuilder->RenderFile(tszMediaName, NULL);
    if (CheckError(TEXT("RenderFile")))
    {
        fRet = FALSE;
        goto doneplaymovie;
    }

    RetailOutput(TEXT("Pause playback...\r\n"));
    pmediacontrol->Pause();

    RetailOutput(TEXT("Run MediaControl...\r\n"));
    g_errLast = pmediacontrol->Run();
    if (g_errLast != S_OK && g_errLast != S_FALSE)
    {
        RetailOutput(TEXT("Run Movie failed (Error # = 0x%08x)\r\n"), g_errLast);
        fRet = FALSE;
        goto doneplaymovie;
    }

    // Now sit back and wait for the movie to complete playing.  If your app allows the user to 
    // skip movies, then you would not block infinitely on this event - instead, alternate checking
    // if user input has occurred with checking if the movie is done.
    RetailOutput(TEXT("Wait for completion...\r\n"));
    g_errLast = pmediaevent->WaitForCompletion(INFINITE, &lEventCode);
    if (CheckError(TEXT("WaitForCompletion")))
    {
        fRet = FALSE;
        goto doneplaymovie;
    }

    RetailOutput(TEXT("Done playing movie...\r\n"));

    // Once done, release all of the interfaces we created for this function
doneplaymovie:
    if (pmediacontrol)
        pmediacontrol->Release();

    if (pgraphbuilder)
        pgraphbuilder->Release();

    if (pmediaevent)
        pmediaevent->Release();

    return fRet;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.  It loads a video stream
    and plays it back

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
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    TCHAR szFile[MAX_PATH];
    DWORD dwAttributes;

    if (*lpCmdLine == NULL)
    {
        // The user must specify a filename
        RetailOutput(TEXT("Error: filename not specified.  File must either be specified with full path\r\n"));
        RetailOutput(TEXT("name, or must reside in your Release\\<retail/debug>\\Samples directory\r\n"));
        RetailOutput(TEXT("Usage: PlayVideo [filename]\r\n"));
        return 1;
    }

    // Get the desired filename from the command line
    lstrcpy(szFile, lpCmdLine);

    // Check to see if the file is specified using the full path (ie "\windows\test.mpg")
    dwAttributes = GetFileAttributes(szFile);
    if (dwAttributes == 0xFFFFFFFF || dwAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        // The file was not specifies using the full path; check to see if the filename
        // specified exists in the Flat Release directory
        lstrcpy(szFile, TEXT("\\PC\\Samples\\"));
        lstrcat(szFile, lpCmdLine);
        dwAttributes = GetFileAttributes(szFile);
        if (dwAttributes == 0xFFFFFFFF || dwAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            // The file wasn't there either - this sample doesn't support loading from other
            // default directories, so report usage and exit
            RetailOutput(TEXT("specified media file (%s) not found\r\n"), lpCmdLine);
            RetailOutput(TEXT("File must either be specified with full path name, or must reside in\r\n"));
            RetailOutput(TEXT("your Release\\<retail/debug>\\Samples directory\r\n"));
            RetailOutput(TEXT("Usage: PlayVideo [filename]\r\n"));
            return 1;
        }
    }

    // If here, then the media file was found. 

    CoInitializeEx(NULL, COINIT_MULTITHREADED);

    // Now, actually play the movie itself.  This will take care of loading it and rendering it to the screen.
    PlayMovie(szFile);

    CoUninitialize();

    RetailOutput(TEXT("\r\nApp exited...\r\n"));
    return 0;
}
