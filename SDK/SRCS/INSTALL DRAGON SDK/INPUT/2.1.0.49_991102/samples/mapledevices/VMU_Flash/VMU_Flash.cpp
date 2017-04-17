/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    VMU_Flash.cpp

Abstract:

    VMU_Flash Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "VMU_Flash.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CleanUp

Description:

    Cleans up after the application is done.  Frees allocated memory

Arguments:

    None
  
Return Value:

    None

-------------------------------------------------------------------*/
void
CleanUp()
{
    int iPort;

    // Release the device objects that we created
    for (iPort = 0; iPort < g_nPorts; iPort++)
        if (g_rgpcont[iPort])
            delete g_rgpcont[iPort];

    // Release the DI object
    if (g_pdi)
        g_pdi->Release();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    FormatAllFlashDevices

Description:

    Format all of the flash devices that are currently connected

Arguments:

    None
  
Return Value:

    None

-------------------------------------------------------------------*/
void
FormatAllFlashDevices()
{
    int i;
    CFlash *pflash;

    // Examine each of the ports - if there is a controller attached to
    // the port then continue on
    for (i = 0; i < g_nPorts; i++)
    {
        if (g_rgpcont[i] != NULL)
        {
            // There is a controller attached to Port #'i'.  Check to see if
            // it has any Flash devices attached to it.  If so, format them.

            // Flash Device #0
            pflash = g_rgpcont[i]->GetFlash(0);
            if (pflash)
            {
                RetailOutput(TEXT("Formatting device in connection %d on Port #%d...\r\n"), pflash->GetConn(), i);
                pflash->Format();
                RetailOutput(TEXT("Finished Formatting.\r\n"));

				// Flash Device #1
				pflash = g_rgpcont[i]->GetFlash(1);
				if (pflash)
				{
					RetailOutput(TEXT("Formatting device in connection %d on Port #%d...\r\n"), pflash->GetConn(), i);
					pflash->Format();
					RetailOutput(TEXT("Finished Formatting.\r\n"));
				}
				else
					RetailOutput(TEXT("Controller in Port #%d only has one flash device\r\n"), i);
			}
            else
                RetailOutput(TEXT("Controller in Port #%d has no Flash devices\r\n"), i);
        }
        else
            RetailOutput(TEXT("There is no controller in Port #%d\r\n"), i);
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DumpAllFlashDevices

Description:

    Dump the information from all of the flash devices that are currently connected

Arguments:

    None
  
Return Value:

    None

-------------------------------------------------------------------*/
void
DumpAllFlashDevices()
{
    int    i;
    CFlash *pflash;

    // Examine each of the ports - if there is a controller attached to
    // the port then continue on
    for (i = 0; i < g_nPorts; i++)
    {
        if (g_rgpcont[i] != NULL)
        {
            // There is a controller attached to Port #'i'.  Check to
            // see if it has any Flash devices attached to it.  If so,
            // dump their contents

            // Flash Device #0
            pflash = g_rgpcont[i]->GetFlash(0);
            if (pflash)
			{
                pflash->DumpInfo();

				// Flash Device #1
				pflash = g_rgpcont[i]->GetFlash(1);
				if (pflash)
					pflash->DumpInfo();
				else
					RetailOutput(TEXT("Controller in Port #%d only has one Flash device\r\n"), i);
			}
            else
                RetailOutput(TEXT("Controller in Port #%d has no Flash devices\r\n"), i);
        }
        else
            RetailOutput(TEXT("There is no controller in Port #%d\r\n"), i);
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CopyAllFlashDevices

Description:

    For each controller that is connected, if there are two flash devices 
    connected, copy the contents from one to the other.

Arguments:

    None
  
Return Value:

    None

-------------------------------------------------------------------*/
void
CopyAllFlashDevices()
{
    int    i;
    CFlash *pflash1, *pflash2;

    // Examine each of the ports - if there is a controller attached to
    // the port then continue on
    for (i = 0; i < g_nPorts; i++)
    {
        if (g_rgpcont[i] != NULL)
        {
            // There is a controller attached to Port #'i'.  Check to see if
            // it has two Flash devices attached to it.  If so, copy the contents
            // from the one in connection 2 to the one in connection 1
            pflash1 = g_rgpcont[i]->GetFlash(0);
            if (pflash1)
            {
                pflash2 = g_rgpcont[i]->GetFlash(1);
                if (pflash2)
                {
                    RetailOutput(TEXT("Copying contents of device in connection %d to device in connection %d on Port #%d...\r\n"), pflash2->GetConn(), pflash1->GetConn(), i);
                    pflash2->CopyContentsTo(pflash1);
                    RetailOutput(TEXT("File copy process complete.  Unknown number of files copied.\r\n"));
                }
                else
                    RetailOutput(TEXT("Controller in Port #%d must have two Flash devices connected\r\n"), i);
            }
            else
                RetailOutput(TEXT("Controller in Port #%d must have two Flash devices connected\r\n"), i);
        }
        else
            RetailOutput(TEXT("There is no controller in Port #%d\r\n"), i);
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetAlpha

Description:

    Gets the next Alphabetical character or '?' from the passed in
    string.  This function is used in parsing the command line.

Arguments:

    LPTSTR        tszCmdLine    - The command line to parse

    TCHAR         *tch          - Set this to the read-in character

Return Value:

    TCHAR*  - The pointer to the new current location in the command line

-------------------------------------------------------------------*/
TCHAR *GetAlpha(LPTSTR tszCmdLine, TCHAR *tch)
{
    while (*tszCmdLine)
    {
        if ((*tszCmdLine >= 'A' && *tszCmdLine <= 'Z') || (*tszCmdLine >= 'a' && *tszCmdLine <= 'z') || *tszCmdLine == '?')
        {
            *tch = *tszCmdLine;
            tszCmdLine++;
            break;
        }
        tszCmdLine++;
    }

    return tszCmdLine;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ParseCommandLine

Description:

    Parses the specified command line for the desired action.  Default
    action (if none is specified) is Dump Usage

Arguments:

    LPTSTR        tszCmdLine    - The command line to parse

    eCommand      *pecmd        - Desired Action

Return Value:

    None

-------------------------------------------------------------------*/
void
ParseCommandLine(LPTSTR tszCmdLine, eCommand *pecmd)
{
    TCHAR tcAction;

    // Get the desired action.  Skip the initial '-' or '/' and all surrounding whitespace
    tszCmdLine = GetAlpha(tszCmdLine, &tcAction);

    switch (tcAction)
    {
    case 'D':
    case 'd':
        *pecmd = ecmdDumpFlash;
        break;
        
    case 'F':
    case 'f':
        *pecmd = ecmdFormatFlash;
        break;

    case 'C':
    case 'c':
        *pecmd = ecmdCopyFlash;
        break;

    case '?':
    default:
        *pecmd = ecmdDumpUsage;
        break;
    }
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.  It creates an app
    window and then enters a message loop.

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
    eCommand ecmd;

    // Store Instance handle for use later...
    g_hinst = hInstance;

    // Initialize DirectInput.  This will populate the g_rgpcont array,
    // which describes which controllers are in each port.
    if (!InitDirectInput())
        return FALSE;

    // Examine the command line to see what the user wants to do
    ParseCommandLine(lpCmdLine, &ecmd);

    // Take the appropriate action
    switch (ecmd)
    {
    case ecmdDumpUsage:
        // Dump this app's usage information
        RetailOutput(TEXT("\r\nVMU_Flash sample application.\r\n"));
        RetailOutput(TEXT("Usage: VMU_Flash [Action]\r\n\r\n"));
        RetailOutput(TEXT("-?       This output\r\n"));
        RetailOutput(TEXT("-D       Dump Flash Devices.  Dumps contents of all connected\r\n"));
        RetailOutput(TEXT("         flash devices to the debugger\r\n"));
        RetailOutput(TEXT("-F       Format Flash Devices.  Formats all connected flash devices\r\n"));
        RetailOutput(TEXT("-C       Copy Flash devices.  For each controller that is connected,\r\n"));
        RetailOutput(TEXT("         if there are two flash devices connected to it, then copy\r\n"));
        RetailOutput(TEXT("         the contents from the device in connection 2 to the device\r\n"));
        RetailOutput(TEXT("         in connection 1\r\n\r\n"));       
        break;

    case ecmdFormatFlash:
        // Format all of the flash devices that are currently connected
        FormatAllFlashDevices();
        break;

    case ecmdDumpFlash:
        // Dump the information from all of the flash devices that are currently connected
        DumpAllFlashDevices();
        break;

    case ecmdCopyFlash:
        // For each controller that is connected, if there are two flash devices connected,
        // copy the contents from one to the other.
        CopyAllFlashDevices();
        break;
    }

    CleanUp();

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return 0;
}
