/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    VMU_Timer.cpp

Abstract:

    VMU_Timer Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "VMU_Timer.hpp"

// ++++ Enumerated Types ++++++++++++++++++++++++++++++++++++++++++++

// User Commands
typedef enum eCommand {ecmdDumpUsageInfo, ecmdReadTimer, ecmdSetTimer, ecmdSoundAlarm};

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// numeric->String date conversion array
TCHAR *g_rgtszDayOfWeek[7] = {TEXT("Sunday"), TEXT("Monday"), TEXT("Tuesday"),
                              TEXT("Wednesday"), TEXT("Thursday"), TEXT("Friday"), TEXT("Saturday")};

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

    OutputCurTime

Description:

    Outputs the current time of the specified timer device to the 
    debugger.

Arguments:

    CTimer  *ptimer     - The timer whose time should be output
  
Return Value:

    None

-------------------------------------------------------------------*/
void
OutputCurTime(CTimer *ptimer)
{
    TMR_CURR_TIME tmrcurrtime;

    memset(&tmrcurrtime, 0, sizeof(tmrcurrtime));

    ptimer->ReadTime(&tmrcurrtime);

    RetailOutput(TEXT("   Current Timer time: Year = %04d, Month = %02d, Day = %02d, %02d:%02d:%02d, Day of Week = %s\r\n"),
                 tmrcurrtime.tmrCurrYear, 
                 tmrcurrtime.tmrCurrMonth,
                 tmrcurrtime.tmrCurrDay,
                 tmrcurrtime.tmrCurrHour,
                 tmrcurrtime.tmrCurrMinute,
                 tmrcurrtime.tmrCurrSecond,
                 g_rgtszDayOfWeek[tmrcurrtime.tmrCurrDayOfWeek]);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetAlpha

Description:

    Gets the next Alphabetical character or '?' from the passed in
    string.  This function is used in parsing the command line.

Arguments:

    LPTSTR        lpCmdLine     - The command line to parse

    TCHAR         *tch          - Set this to the read-in character

Return Value:

    TCHAR*  - The pointer to the new current location in the command line

-------------------------------------------------------------------*/
TCHAR *GetAlpha(LPTSTR lpCmdLine, TCHAR *tch)
{
    while (*lpCmdLine)
    {
        if ((*lpCmdLine >= 'A' && *lpCmdLine <= 'Z') || (*lpCmdLine >= 'a' && *lpCmdLine <= 'z') || *lpCmdLine == '?')
        {
            *tch = *lpCmdLine;
            lpCmdLine++;
            break;
        }
        lpCmdLine++;
    }

    return lpCmdLine;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetNumber

Description:

    Gets the next numerical value from the passed-in string.  This 
    function is used in parsing the command line.

Arguments:

    LPTSTR        lpCmdLine     - The command line to parse

    USHORT         *pi          - Set this to the read-in number

Return Value:

    TCHAR*  - The pointer to the new current location in the command line

-------------------------------------------------------------------*/
TCHAR *GetNumber(LPTSTR lpCmdLine, USHORT *pi)
{
    BOOL fStart = FALSE;
    USHORT n = 0;

    while (*lpCmdLine)
    {
        if ((*lpCmdLine >= '0' && *lpCmdLine <= '9'))
        {
            n = n * 10 + (*lpCmdLine - '0');
            fStart = TRUE;
        }
        else if (fStart)
        {
            lpCmdLine++;
            break;
        }

        lpCmdLine++;
    }

    *pi = n;

    return lpCmdLine;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ParseCommandLine

Description:

    Parses the specified command line for the desired action.  Default
    action (if none is specified) is Read timer on Port 1

Arguments:

    LPTSTR        lpCmdLine     - The command line to parse

    int           *piPort       - Port of the device to use

    eCommand      *pecmd        - Desired Action

    TMR_CURR_TIME *ptmrcurrtime - if 'SetTime' is specified, then this is the 
                                  time to which the timer is set.
  
Return Value:

    None

-------------------------------------------------------------------*/
void
ParseCommandLine(LPTSTR lpCmdLine, int *piPort, eCommand *pecmd, TMR_CURR_TIME *ptmrcurrtimeSet, int *pnAlarm, int *pnFreq, int *pnVol)
{
    TCHAR tcAction;

    // Specify the default action if none is specified
    *pecmd  = ecmdReadTimer;
    *piPort = 0;
    *pnAlarm = 0;
    *pnFreq = 0;
    *pnVol = 0;

    // Get the desired action.  Skip the initial '-' or '/' and all surrounding whitespace
    lpCmdLine = GetAlpha(lpCmdLine, &tcAction);

    // Find the desired action
    switch (tcAction) {
    case '?':
        // Dump Usage info
        *pecmd = ecmdDumpUsageInfo;
        return;
        break;

    case 'R':
    case 'r':
        // Read Timer
        *pecmd = ecmdReadTimer;

        // Get the desired port number
        lpCmdLine = GetNumber(lpCmdLine, (USHORT*)piPort);
        break;

    case 'S':
    case 's':
        // Set Timer
        *pecmd = ecmdSetTimer;

        // Get the desired port number
        lpCmdLine = GetNumber(lpCmdLine, (USHORT*)piPort);
        
        // Get the time to set the timer to
        lpCmdLine = GetNumber(lpCmdLine, &ptmrcurrtimeSet->tmrCurrYear);
        lpCmdLine = GetNumber(lpCmdLine, &ptmrcurrtimeSet->tmrCurrMonth);
        lpCmdLine = GetNumber(lpCmdLine, &ptmrcurrtimeSet->tmrCurrDay);
        lpCmdLine = GetNumber(lpCmdLine, &ptmrcurrtimeSet->tmrCurrHour);
        lpCmdLine = GetNumber(lpCmdLine, &ptmrcurrtimeSet->tmrCurrMinute);
        lpCmdLine = GetNumber(lpCmdLine, &ptmrcurrtimeSet->tmrCurrSecond);
        ptmrcurrtimeSet->tmrCurrDayOfWeek = 0;
        break;

    case 'A':
    case 'a':
        // Do Alarm
        *pecmd = ecmdSoundAlarm;

        // Get the desired port number
        lpCmdLine = GetNumber(lpCmdLine, (USHORT*)piPort);

        // Get the alarm number, freq, and vol
        lpCmdLine = GetNumber(lpCmdLine, (USHORT*)pnAlarm);

        //
        lpCmdLine = GetNumber(lpCmdLine, (USHORT*)pnFreq);
        lpCmdLine = GetNumber(lpCmdLine, (USHORT*)pnVol);
        break;

    default:
        // Invalid input.
        RetailOutput(TEXT("\r\nInvalid Action specified.\r\n"));
        *pecmd = ecmdDumpUsageInfo;
        return;
    }

    if (*piPort < 0 || *piPort > 3)
    {
        RetailOutput(TEXT("\r\nInvalid Port # specified\r\n"));
        *pecmd = ecmdDumpUsageInfo;
        return;
    }

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.  It parses the command
    line and performs the requested action.

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
    TMR_CURR_TIME tmrcurrtimeSet; // Structure to store desired time if 'SetTime' specified
    eCommand      ecmd;           // The command that the user wants performed
    int           iPort;          // The port of the timer on which the user wants to perform the action
    CTimer        *ptimer;        // The timer device on which the user wants to perform the action
    int           nAlarm;         // The alarm number to test (1 or 2)
    int           nAlarmFreq;     // The alarm frequency
    int           nAlarmVol;      // The alarm volume

    // Store Instance handle for use later...
    g_hinst = hInstance;

    // Check the command line parameters to see what the user wants to do
    ParseCommandLine(lpCmdLine, &iPort, &ecmd, &tmrcurrtimeSet, &nAlarm, &nAlarmFreq, &nAlarmVol);

    // If the user asked for usage info, then output it and quit
    if (ecmd == ecmdDumpUsageInfo)
    {
        RetailOutput(TEXT("\r\nVMU_Timer sample application.\r\n"));
        RetailOutput(TEXT("Usage: VMU_Timer [Action] [Parms]\r\n\r\n"));
        RetailOutput(TEXT("-?       This output\r\n"));
        RetailOutput(TEXT("-R       Read Timer.  [port number]\r\n"));
        RetailOutput(TEXT("-S       Set Timer.  [port yyyy mm dd hh mm ss].  For example\r\n"));
        RetailOutput(TEXT("             \"VMU_TIMER -S 0 1998 12 25 13 25 33\"\r\n"));
	RetailOutput(TEXT("             sets the timer on port 0 to 1:25:33pm, 25 Dec 98\r\n"));
        RetailOutput(TEXT("-A       Set the Alarm to the desired volume frequency and then\r\n"));
        RetailOutput(TEXT("         play the sound for 2 seconds\r\n"));
        RetailOutput(TEXT("         [port alarm# Frequency Volume].  For example\r\n"));
        RetailOutput(TEXT("             \"VMU_TIMER -A 0 1 255 255\" Plays the lowest frequency sound\r\n"));
        RetailOutput(TEXT("             at the highest volume from alarm #1 on the timer on port 0\r\n"));
        return 0;
    }

    // Initialize DirectInput.  This automatically enumerates all controllers and devices
    if (!InitDirectInput())
        return 1;

    // Check if the desired port has a controller attached to it
    if (g_rgpcont[iPort] == NULL)
    {
        RetailOutput(TEXT("There is no controller on port #%d!\r\n"), iPort);
        return 1;
    }

    // Check if the controller on the desired port has a timer device attached to it
    ptimer = g_rgpcont[iPort]->GetTimer();
    if (ptimer == NULL)
    {
        RetailOutput(TEXT("There is no timer in the controller on port #%d!\r\n"), iPort);
        return 1;
    }

    // Perform the desired action
    switch(ecmd) {
    case ecmdReadTimer:
        RetailOutput(TEXT("Read Timer (port #%d):\r\n"), iPort);

        // Read and output the current time of the specified timer device
        OutputCurTime(ptimer);
        break;

    case ecmdSetTimer:
        RetailOutput(TEXT("Set Timer (port #%d):\r\n"), iPort);

        // Set the current time
        ptimer->SetTime(&tmrcurrtimeSet);
        RetailOutput(TEXT("Timer Set."));

        // Now that the time is set, read and output it to verify that it was set correctly
        OutputCurTime(ptimer);
        break;

    case ecmdSoundAlarm:
        RetailOutput(TEXT("Alarm (port #%d):\r\n"), iPort);
        
        // Check if the desired alarm is supported on the specified device
        if (!ptimer->HasAlarm(nAlarm))
            RetailOutput(TEXT("Invalid Alarm # specified\r\n"));
        else
        {
            // Play the alarm sound for 2 seconds.
            RetailOutput(TEXT("Playing alarm...\r\n"));
            ptimer->SoundAlarm(nAlarm, nAlarmFreq, nAlarmVol);
            Sleep(2000);
            ptimer->StopAlarm();
            RetailOutput(TEXT("Done playing alarm.\r\n"));
        }
        break;

    default:
        DebugOutput(TEXT("invalid command specified\r\n"));
        return 1;
    }

    // Now that we're done, clean up after ourselves
    CleanUp();
    RetailOutput(TEXT("App Done.\r\n"));

    return 0;
}
