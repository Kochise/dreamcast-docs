/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    Reboot.cpp

Abstract:

    Reboot Sample Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include <windows.h>
#include <platutil.h>

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++

int g_nZero = 0;     // We use this to cause divide by zero error at runtime

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CauseException

Description:

    This function generates a divide by zero exception

Arguments:

    None

Return Value:

    Garbage

-------------------------------------------------------------------*/
int CauseException()
{
    OutputDebugString(TEXT("\r\nAbout to cause an exception for demonstration purposes...\r\n"));
    return 10 / g_nZero;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.

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
    // Entire program is executed in try/except block
    __try
    {
        // Message Handling loop and all other code should happen in this
        // __try {} block.  That way, if anything bad happens, the __except {}
        // block below will catch it.

        // Fake an exception to demonstrate how this works.
        CauseException();
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        // Execution gets here if an unhandled exception has occurred
        OutputDebugString(TEXT("Unhandled exception caught in WinMain -- rebooting\r\n"));

        // For lack of anything better to do, reset the Dreamcast rather than
        // letting it hang.
        ResetToFirmware();
    }
    
    OutputDebugString(TEXT("\r\nApp exited...\r\n"));

    return 0;
}
