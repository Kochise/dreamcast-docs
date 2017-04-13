// ===========================================================================
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright 1997 Microsoft Corporation.  All Rights Reserved.
// ===========================================================================
//
//+--------------------------------------------------------------------------
//
// File:        sa.cpp
//
// Contents:    All code needed to build the simple job submission tool
//
// Purpose:     Demonstration of calls to methods of the following new
//              interfaces:
//                  1. ITaskScheduler
//                  2. ITask
//                  3. ITaskTrigger
//                  4. IEnumWorkItems
//
// Comments:    This application is similar in functionality to
//              the "AT" command provided with Windows NT.  However,
//              the AT command functions through the NetSchedule APIs,
//              as opposed to the COM interfaces demonstrated here.
//
//              The Task Scheduler replaces ATSVC.EXE and implements
//              those APIs as a restricted subset of the new ones
//              demonstrated here.
//
//              On Win9x systems, the Task Scheduler replaces
//              the System Agent, providing more flexible and reliable
//              scheduling options than previously available.
//              However, although the SAGE jobs are converted
//              to Task Scheduler work items, the actual
//              SAGE API has been abandoned and is not implemented.
//
//              The Task Scheduler APIs provide a greater degree of
//              freedom and robustness than those APIs.  This code
//              demonstrates a stripped version of AT rewritten to
//              use the new APIs.
//
// Additional:  The Task Scheduler service must be running.  It is easily
//              started by the command "net start schedule" if it is not
//              running.  It is also trivial to start it through
//              the service control manager APIs. Doing it in the code
//              directly makes a good enhancement to the program below.
// 
//              Since there is not a service controller on Win9x, 
//              the user may start the service by executing the
//              binary directly from the command line (mstask.exe).
//              Win9x users will see a system tray icon if the service 
//              is running.
//
//              The service may also be started from the folder UI available
//              directly by opening "My Computer" and then opening the 
//              "Scheduled Tasks" folder.  The start command appears on the
//              "Advanced" menu.
//
//              Sample code to start and stop the service, on both 
//              Windows NT and Win9x based systems appears in the
//              documentation.
//
//              If the Task Scheduler service is not running, most 
//              of this program will fail to execute.  If there are 
//              tasks waiting to execute after login, the service 
//              will have been started by default.
//             
//---------------------------------------------------------------------------

#include <wchar.h>
#include <windows.h>
#include <mbctype.h>
#include <initguid.h>
#include <mstask.h>
#include <msterr.h>

//+--------------------------------------------------------------------------
// Global variables
//---------------------------------------------------------------------------

ITaskScheduler *g_pITaskScheduler = NULL;

//+--------------------------------------------------------------------------
// Function Prototypes
//---------------------------------------------------------------------------

HRESULT Init(void);
void Cleanup(void);
void DisplayHelp(LPWSTR);
HRESULT EnumerateJobs(void);
HRESULT DeleteJob(LPWSTR);
HRESULT AddJob(LPWSTR, LPSYSTEMTIME, LPWSTR, LPWSTR, LPWSTR);
HRESULT ConvertToSystemTime(LPWSTR, LPSYSTEMTIME);


//+--------------------------------------------------------------------------
//
// Function:        main
//
// Synopsis:        Entry point for code.  Parses command line,
//                  and calls appropriate subfunction as a result.
//
//  Arguments:      See DisplayHelp().  Uses argv, argc to get 
//                  command line args.
//
//  Returns:        S_OK for success or the failure code for failure.
//
//---------------------------------------------------------------------------

LONG _CRTAPI1 main (int argc, char **argv)
{
    HRESULT hr = S_OK;
    UINT uCodePage;
    char *lpcszDeleteFlag = "/DELETE";
    WCHAR lpwszJobName[255], lpwszTime[32];
    WCHAR lpwszUserName[64], lpwszPassword[64], lpwszCommand[255];
    WCHAR lpwszProgName[255];
    SYSTEMTIME tTime;

    // For protection

    g_pITaskScheduler = NULL;

    // String conversion initialization

    uCodePage = _getmbcp();
   
    MultiByteToWideChar(uCodePage, 0, argv[0],
                        -1, lpwszProgName,
                        255);

    // Check number of command line arguments.
    //      1 argument      =   enumerate work items 
    //      2 args          =   display help (don't init OLE)
    //      3 args          =   delete work item 
    //      4, 5 or 6 args  =   add a work item 
    //      all others      =   error, display help

    if ((argc == 2) || (argc > 6))
    {
        DisplayHelp(lpwszProgName);
        return hr;
    }

    // Attempt to initialize OLE and fill in the global g_pITaskScheduler

    hr = Init();
    if (FAILED(hr))
    {
        wprintf(L"Error: OLE initialization and instantiation failed\n");
        return hr;
    }
    
    switch(argc)
    {
        case 1:
            // User would like to enumerate work items 

            hr = EnumerateJobs();
            break;

        case 3:
            if (! lstrcmpiA(argv[2], lpcszDeleteFlag))
            {
                // User would like to delete work item in argv[1]

                MultiByteToWideChar(uCodePage, 0, argv[1], 
                                    -1, lpwszJobName,
                                    255);

                hr = DeleteJob(lpwszJobName);
            }
            else
            {
                // User has made an error in command line args                
                
                wprintf(L"Error: Must be %s taskname.job /DELETE\n", lpwszProgName);
                wprintf(L"\n %s /?  for more help.\n", lpwszProgName);
                
                Cleanup();
                return E_FAIL;
            }
            break;

        case 4:
        case 5:
        case 6:
            // User would like to add a work item.  The following
            // argument cases apply:
            //      4 - User has specified work item name, but not given 
            //          username or password.  Will prompt later.
            //      5 - User has specified work item name and username,
            //          but no password.  Will prompt later.            
            //      6 - User has specified all information.
            
                uCodePage = _getmbcp();
    
                MultiByteToWideChar(uCodePage, 0, argv[1], 
                                    -1, lpwszJobName,
                                    255);
                MultiByteToWideChar(uCodePage, 0, argv[2],
                                    -1, lpwszTime,
                                    32);

            hr = ConvertToSystemTime(lpwszTime, &tTime);
            if (FAILED(hr))
            {
                wprintf(L"Error: Conversion of command line time to system time failed.\n");
                Cleanup();
                return hr;
            }
            
            *lpwszUserName = L'\0';
            *lpwszPassword = L'\0';

            MultiByteToWideChar(uCodePage, 0, argv[3],
                                -1, lpwszCommand,
                                255);

            if (argc > 4)
            {

                MultiByteToWideChar(uCodePage, 0, argv[4],
                                    -1, lpwszUserName,
                                    64);
            }
            if (argc == 6)
            {

                MultiByteToWideChar(uCodePage, 0, argv[5],
                                    -1, lpwszPassword,
                                    64);
            }
            
            hr = AddJob(lpwszJobName, &tTime, lpwszCommand, lpwszUserName, lpwszPassword);
            
            break;

        default:
            hr = E_FAIL;
            DisplayHelp(lpwszProgName);
    }
    
    Cleanup();
    return hr;
}


//+--------------------------------------------------------------------------
//
// Function:        Init()
//
// Synopsis:        Called to initialize and instantiate a task 
//                  scheduler object.
//
// Arguments:       none (void)
//
// Returns:         HRESULT indicating success or failure.  S_OK on success.
//
// Side effect:     Sets global pointer g_pITaskScheduler, for use in other
//                  functions.  
//
//---------------------------------------------------------------------------

HRESULT Init()
{
    HRESULT hr = S_OK;

    // Bring in the library

    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        return hr;
    }

    // Create the pointer to Task Scheduler object
    // CLSID from the header file mstask.h

    hr = CoCreateInstance(
        CLSID_CTaskScheduler,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_ITaskScheduler,
        (void **) &g_pITaskScheduler);

    // Should we fail, unload the library

    if (FAILED(hr))
    {
        CoUninitialize();
    }

    return hr;
}


//+--------------------------------------------------------------------------
//
// Function:    Cleanup()
//
// Synopsis:    Called to clean up OLE, memory, etc. before termination
//
// Arguments:   none (void)
//
// Returns:     nothing (void)
//
// Side effect: Cancels the global pointer g_pITaskScheduler.
//
//---------------------------------------------------------------------------

void Cleanup()
{
    if (g_pITaskScheduler)
    {
        g_pITaskScheduler->Release();
        g_pITaskScheduler = NULL;
    }
   
    // Unload the library, now that our pointer is freed.

    CoUninitialize();
    return;
}


//+--------------------------------------------------------------------------
//
// Function:    DisplayHelp() 
//
// Synopsis:    Prints out help and usage information
//
// Arguments:   lpwszProgName - a pointer to a WSTR containing argv[0]
//
// Returns:     nothing (void)
//
//---------------------------------------------------------------------------

void DisplayHelp(LPWSTR lpwszProgName)
{
    wprintf(L"%s -- a small program to replicate some\n", lpwszProgName); 
    wprintf(L"\tfunctionality of the AT command, using the\n");
    wprintf(L"\tnew Task Scheduler interfaces.\n\n");

    wprintf(L"Usage:\n");
    wprintf(L"\t%s /?\n\t\t\t\t\t\t- Display this help\n",lpwszProgName);
    wprintf(L"\t%s\n\t\t\t\t\t\t- Show all work items\n",lpwszProgName);
    wprintf(L"\t%s TaskName.job /DELETE \n\t\t\t\t\t\t- delete work item\n",lpwszProgName);
    wprintf(L"\t%s TaskName.job Time Command [UserName [Password]]\n\t\t\t\t\t\t- submit a new work item\n\n",lpwszProgName);

    wprintf(L"TaskName.job is the name of the work item object on disk.\n");
    wprintf(L"The work item will appear in the Scheduled Tasks folder as TaskName\n");
    wprintf(L"but must be given the extension \".job\" for the service \n");
    wprintf(L"to recognize and run it.\n\n");

    wprintf(L"Task Time is in 24 hour format (such as 15:30) and is the\n");
    wprintf(L"next instance of this time within 24 hours.\n\n");
    
    wprintf(L"The Command should contain the name of the executable to run.\n");
    wprintf(L"Note that the pathname may NOT contain spaces.  If the\n");
    wprintf(L"program requires command line parameters, enclose the entire\n");
    wprintf(L"command string in quotation marks.\n\n");

    wprintf(L"Username and password are required to run the specified work item under Windows NT.\n");
    wprintf(L"Under Windows NT, if not specified, you will be prompted.\n");
    wprintf(L"Under Windows 95, both fields are ignored.  If not specified\n");
    wprintf(L"on the command line, you will not be prompted.\n\n");
    
    return;
}
 

//+--------------------------------------------------------------------------
//
// Function:    EnumerateJobs()
//
// Synopsis:    Goes through all scheduled work items on a system and 
//              lists them, along with a short trigger string.
//
// Arguments:   none (void).  Requires g_pITaskScheduler.
//
// Returns:     HRESULT indicating success (S_OK) or other.
//
//---------------------------------------------------------------------------

HRESULT EnumerateJobs()
{
    HRESULT hr = S_OK, hrLoop = S_OK;
    IEnumWorkItems *pIEnumWorkItems;
    IUnknown *pIU;
    ITask *pITask;
    ULONG ulTasksToGet = 1, ulActualTasksRetrieved = 0;
    LPWSTR *rgpwszNames, pwszTrigger;
    WORD wTrigCount = 0;
    WORD wTemp;

    
    //
    // Get an enumeration pointer, using ITaskScheduler::Enum
    //

    hr = g_pITaskScheduler->Enum(&pIEnumWorkItems);
    if (FAILED(hr))
    {
        wprintf(L"Failed to get enumerator\n");
        return hr;
    }

    do
    {
        // Get a single work item, using IEnumWorkItems::Next

        hrLoop = pIEnumWorkItems->Next(ulTasksToGet, &rgpwszNames,
                                       &ulActualTasksRetrieved);
        if (hrLoop == S_FALSE)
        {
            // There are no more waiting tasks to look at
            break;
        }

        // Attach to the work item, using ITaskScheduler::Activate

        hr = g_pITaskScheduler->Activate(rgpwszNames[0], IID_ITask, &pIU);
        if (FAILED(hr))
        {
            wprintf(L"Error: Activate Failed\n",hr);
            break;
        }

        // QI pIU for pITask
   
        hr = pIU->QueryInterface(IID_ITask, (void **) &pITask);
        pIU->Release();
        pIU = NULL;
        if (FAILED(hr))
        {
            wprintf(L"Error: QI for ITask failed in Activate.\n");
            break;
        }

        // Display task name

        wprintf(L"Task: %s\n",rgpwszNames[0]); 

        // Use ITask::GetTriggerCount to get count of triggers

        hr = pITask->GetTriggerCount(&wTrigCount);
        if (FAILED(hr))
        {
            wprintf(L"Error: Failed to count triggers\n");
            pITask->Release();
            break;
        }
        
        for (wTemp = 0; wTemp < wTrigCount; wTemp++)
        {
            // Dump Triggers using ITask::GetTriggerString

            hr = pITask->GetTriggerString(wTemp, &pwszTrigger);
            if (FAILED(hr))
            {
                wprintf(L"Error: Failed to get trigger string\n");
                pITask->Release();
                break;
            }

            wprintf(L"\tTrigger: %s\n",pwszTrigger);

            // Clean up the memory we were allocated for trig string

            CoTaskMemFree(pwszTrigger);
        }

        // Clean up each element in the array of job names, then
        // clean up the final array.

        CoTaskMemFree(rgpwszNames[0]);
        CoTaskMemFree(rgpwszNames);
        
        // Free the ITask pointer
    
        pITask->Release();

    } while(1);

    // Release the enumeration pointer
    
    pITask = NULL;

    pIEnumWorkItems->Release();
    pIEnumWorkItems = NULL;

    return hr; 
}    
    

//+--------------------------------------------------------------------------
//
// Function:        DeleteJob()
//
// Synopsis:        Deletes a work item from the Scheduled Tasks folder.
//
// Arguments:       lpwszJobName - the name of the work item to delete
//
// Returns:         HRESULT indicating success (S_OK) or failure.
//
//---------------------------------------------------------------------------

HRESULT DeleteJob(LPWSTR lpwszJobName)
{
    HRESULT hr = S_OK;

    hr = g_pITaskScheduler->Delete(lpwszJobName);

    return hr;
}


//+--------------------------------------------------------------------------
//
// Function:        AddJob()
//
// Synopsis:        Adds a new work item to the Scheduled Tasks folder.
//
// Arguments:       lpwszJobName - name of the task file
//                  lptTime      - pointer to SYSTEMTIME struct containing
//                                      the time the job should run.
//                  lpwszCommand - name of application (command) to run.
//                  lpwszUserName- user name to run job under
//                  lpwszPassword- password for that user
//
// Returns:         HRESULT indicating success (S_OK) or failure.
//
// Notes:           The password or BOTH the username and password
//                  may be passed in as '\0' strings, in which case
//                  this function will prompt on stdout for password
//                  and username
//
//---------------------------------------------------------------------------

HRESULT AddJob(LPWSTR lpwszJobName, LPSYSTEMTIME lptTime,
                LPWSTR lpwszCommand, LPWSTR lpwszUserName,
                LPWSTR lpwszPassword)
{
    HRESULT hr = S_OK;
    IUnknown *pIU;
    IPersistFile *pIPF;
    ITask *pITask;
    ITaskTrigger *pITaskTrig;
    DWORD dwTaskFlags, dwTrigFlags;
    WORD wTrigNumber;
    TASK_TRIGGER TaskTrig;
    WCHAR lpwszAppName[255];
    int i;
    
    // Add the task.  Most likely failure is that work item already exists.
    // Uses ITaskScheduler::NewWorkItem

    hr = g_pITaskScheduler->NewWorkItem(lpwszJobName, 
                                        CLSID_CTask, 
                                        IID_ITask, 
                                        &pIU);
    if (FAILED(hr))
    {
        wprintf(L"Error:  Create New Task failure\n");
        return hr;
    }

    // We now have an IUnknown pointer.  This is queried for an ITask
    // pointer on the work item we just added.
    
    hr = pIU->QueryInterface(IID_ITask, (void **) &pITask);
    if (FAILED(hr))
    {
        wprintf(L"Error: IUnknown failed to yield ITask\n");
        pIU->Release();
        return hr;
    }
    
    // Cleanup pIUnknown, as we are done with it.
    
    pIU->Release();
    pIU = NULL;

    //
    // We need to see if we support security, and we
    // do this by calling ITask::SetAccountInformation
    // and checking if the failure code is SCHED_E_NO_SECURITY_SERVICES
    //

    hr = pITask->SetAccountInformation(lpwszUserName, lpwszPassword);
    if (hr != SCHED_E_NO_SECURITY_SERVICES)
    {
    
        // Check to see if username is null

        if (*lpwszPassword == L'\0')
        {
            // If password was null, chance username is, too.

            if (*lpwszUserName == L'\0')
            {
                wprintf(L"Enter username to run job %s as: ",lpwszJobName);
                wscanf(L"%s",lpwszUserName);
                wprintf(L"\n");
            }
    
            wprintf(L"Enter password to user %s: ",lpwszUserName);
            wscanf(L"%s",lpwszPassword);
            wprintf(L"\n");
        }
    }

    // Set the account information using ITask::SetAccountInformation
    // This fails for Win9x, but we ignore the failure.

    hr = pITask->SetAccountInformation(lpwszUserName, lpwszPassword);
    if ((FAILED(hr)) && (hr != SCHED_E_NO_SECURITY_SERVICES))
    {
        wprintf(L"Error: Failed to set credentials on task object %x\n",hr);
        pITask->Release();
        return hr;
    }

    // Extract parameters from the application name
    // Note that there might not be any parameters at all.
    // We butcher a path like C:\Program Files\foo.exe, because
    // we break on space, but this is ok, because user could say
    // C:\progra~1\foo.exe instead.

    i = 0;
    while ((*lpwszCommand != L' ') && (*lpwszCommand != '\0'))
    {
        lpwszAppName[i] = *lpwszCommand;
        i++;
        lpwszCommand++;
    }
    lpwszAppName[i] = L'\0';
    if (*lpwszCommand == L' ')
    {
        lpwszCommand++;
    }
    
    // Set command name with ITask::SetApplicationName

    hr = pITask->SetApplicationName(lpwszAppName);
    if (FAILED(hr))
    {
        wprintf(L"Error: Failed to set command name (with parms)\n"); 
        pITask->Release();
        return hr;
    }


    // Set task parameters with ITask::SetParameters

    hr = pITask->SetParameters(lpwszCommand);
    if (FAILED(hr))
    {
        wprintf(L"Error: Failed to set parameters\n");
        pITask->Release();
        return hr;
    }
        
    // Set the comment, so we know how this job go there
    // Uses ITask::SetComment

    hr = pITask->SetComment(L"This scheduled task created by command line SDK sample tool");
    if (FAILED(hr))
    {
        wprintf(L"Error: Task comment could not be set\n");
        pITask->Release();
        return hr;
    }

    // Set the flags on the task object
    // Use ITask::SetFlags

    dwTaskFlags = TASK_FLAG_DELETE_WHEN_DONE;
    hr = pITask->SetFlags(dwTaskFlags);
    if (FAILED(hr))
    {
        wprintf(L"Error: Could not set task flags\n");
        pITask->Release();
        return hr;
    }

    // Now, create a trigger to run the task at our specified time.
    // Uses ITask::CreateTrigger()

    hr = pITask->CreateTrigger(&wTrigNumber, &pITaskTrig);
    if (FAILED(hr))
    {
        wprintf(L"Error: Could not create a new trigger\n");
        pITask->Release();
        return hr;
    }

    // Now, fill in the trigger as necessary.

    dwTrigFlags = 0;

    TaskTrig.cbTriggerSize = sizeof(TASK_TRIGGER);
    TaskTrig.Reserved1 = 0;
    TaskTrig.wBeginYear = lptTime->wYear;
    TaskTrig.wBeginMonth = lptTime->wMonth;
    TaskTrig.wBeginDay = lptTime->wDay;
    TaskTrig.wEndYear = 0;
    TaskTrig.wEndMonth = 0;
    TaskTrig.wEndDay = 0;
    TaskTrig.wStartHour = lptTime->wHour;
    TaskTrig.wStartMinute = lptTime->wMinute;
    TaskTrig.MinutesDuration = 0;
    TaskTrig.MinutesInterval = 0;
    TaskTrig.rgFlags = dwTrigFlags;
    TaskTrig.TriggerType = TASK_TIME_TRIGGER_ONCE;
    TaskTrig.wRandomMinutesInterval = 0;
    TaskTrig.Reserved2 = 0;

    // Add this trigger to the task using ITaskTrigger::SetTrigger

    hr = pITaskTrig->SetTrigger(&TaskTrig);
    if (FAILED(hr))
    {
        wprintf(L"Error: Failed to set trigger to desired values\n");
        pITaskTrig->Release();
        pITask->Release();
        return hr;
    }

    // Make the changes permanent
    // Requires using IPersistFile::Save()

    hr = pITask->QueryInterface(IID_IPersistFile, (void **) &pIPF); 
    if (FAILED(hr))
    {
        wprintf(L"Error: Could not get IPersistFile on task\n");
        pITaskTrig->Release();
        pITask->Release();
        return hr;
    }

    hr = pIPF->Save(NULL, FALSE);
    if (FAILED(hr))
    {
        wprintf(L"Error: Could not save object\n");
        pITaskTrig->Release();
        pITask->Release();
        pIPF->Release();
        return hr;
    }

    // We no longer need ITask
    
    pITask->Release();
    pITask = NULL;

    // Done with ITaskTrigger pointer
    
    pITaskTrig->Release();
    pITaskTrig = NULL;

    // Done with IPersistFile
    
    pIPF->Release();
    pIPF = NULL;

    return hr;
} 


//+--------------------------------------------------------------------------
//
// Function:        ConvertToSystemTime()
//
// Synopsis:        Given a text string from the command line of the form
//                  XX:YY where XX = 0 - 23, and YY = 0 - 59,
//                  obtain the next instance in 24 hours of said time
//                  and return this time in a SYSTEMTIME structure
//                  so that it can be used to set triggers
//
// Arguments:       lpwszTime    -   The text string of time
//                  lptTime     -   The SYSTEMTIME pointer
//
// Returns:         HRESULT of success (S_OK) or failure
//
//---------------------------------------------------------------------------

HRESULT ConvertToSystemTime(LPWSTR lpwszTime, LPSYSTEMTIME lptTime)
{
    WORD wMin = 0, wHr = 0, wMaxFeb = 28;
    WCHAR szTemp[3], *szEnd1, *szEnd2;
    SYSTEMTIME tNow;
    int i, j;

    // Extract minutes and hour from string

    if ((wcslen(lpwszTime) > 5) || (wcslen(lpwszTime) < 4))
    {
        wprintf(L"Error: Invalid time string given\n");
        return E_FAIL;
    }

    // Hours first.
    
    i = 0;
    while (*lpwszTime != ':')
    {
        szTemp[i] = *lpwszTime;
        i++;
        if (i > 2)
        {
            // User gave a bad time string
            wprintf(L"Error: Bad hours in time string\n");
            return E_FAIL;
        }
        lpwszTime++;
    }
    szTemp[i] = L'\0';
    lpwszTime++;
 
    // Convert to value

    wHr = (WORD) wcstoul(szTemp, &szEnd1, 10);
    
    // Now do minutes
 
    i = wcslen(lpwszTime);
    j = 0;
    while (i)
    {
        szTemp[j] = *lpwszTime;
        j++;
        i--;
        lpwszTime++;
    }
    szTemp[j] = L'\0';

    wMin = (WORD) wcstoul(szTemp, &szEnd2, 10);

    // Now figure out if we are running today or tomorrow
    
    GetLocalTime(&tNow);
    if ((wHr < tNow.wHour) || 
       ((wHr == tNow.wHour) && (wMin < tNow.wMinute)))
    {
        // Job is tomorrow - we must figure out what tomorrow is
        
        switch(tNow.wMonth)
        {
            case 4:
            case 6:
            case 9:
            case 11:
                // Thirty day months
                
                if ((tNow.wDay + 1) > 30)
                {
                    tNow.wDay = 1;
                    tNow.wMonth++;
                }
                else
                {
                    tNow.wDay++;
                }
                break;

            case 2:
                // February
                // Leap Year?
                
                if ((tNow.wYear % 4) == 0) 
                {
                    wMaxFeb = 29;
                }
                if (((tNow.wYear % 100) == 0) &&
                    ((tNow.wYear % 400) != 0))
                {
                    wMaxFeb = 28;
                }

                if ((tNow.wDay + 1) > wMaxFeb)
                {
                    tNow.wDay = 1;
                    tNow.wMonth++;
                }
                else
                {
                    tNow.wDay++;
                }
                break;

            default:
                // 31 day months.  Handle Dec. later
                
                if ((tNow.wDay + 1) > 31)
                {
                    tNow.wDay = 1;
                    tNow.wMonth++;
                }
                else
                {
                    tNow.wDay++;
                }
                
                if (tNow.wMonth > 12)
                {
                    tNow.wMonth = 1;
                    tNow.wYear++;
                }
        }
    }

    if ((wMin < 0) || (wMin > 59))
    {
        wprintf(L"Error: Invalid minutes (need 0 - 59)\n");
        return E_FAIL;
    }
    else
    {
        tNow.wMinute = wMin;
    }
    if ((wHr < 0) || (wHr > 23))
    {
        wprintf(L"Error: Invalid hours (need 0 - 23)\n");
        return E_FAIL;
    }
    else
    {
        tNow.wHour = wHr;
    }

    lptTime->wHour = tNow.wHour;
    lptTime->wMinute = tNow.wMinute;
    lptTime->wYear = tNow.wYear;
    lptTime->wMonth = tNow.wMonth;
    lptTime->wDay = tNow.wDay;
    lptTime->wDayOfWeek = 0;
    lptTime->wSecond = 0;
    lptTime->wMilliseconds = 0;
    return S_OK;
} 
