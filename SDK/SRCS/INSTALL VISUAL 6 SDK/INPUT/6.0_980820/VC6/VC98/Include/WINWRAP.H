// --winwrap.h------------------------------------------------------------------
//
// Header file for Windows NT service (Windows application) shell for EDK
// applications.
// 
// Copyright (C) Microsoft Corp., 1986-1996.  All Rights Reserved.
// -----------------------------------------------------------------------------

#ifndef _WINWRAP_H
#define _WINWRAP_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define MAX_SERVICE_NAME_LENGTH 256

//$--EDK_Service_Control_T---------------------------------------------------
//  Service control instructions returned by HrServiceWaitForControl().
// --------------------------------------------------------------------------
typedef enum _EDKServiceControl_T
{
    EDK_SC_NONE = 0,    // no change
    EDK_SC_PAUSE,       // pause the service
    EDK_SC_CONTINUE,    // continue the service
    EDK_SC_STOP,        // stop the service
    EDK_SC_LAST         // all values are less than this
} EDK_SERVICE_CONTROL_T;

//$--FIsService-----------------------------------------------------------------
//  Returns TRUE if the application is running as an NT service.
// -----------------------------------------------------------------------------
BOOL FIsService(                        // RETURNS: TRUE if service
    IN VOID);                           // no arguments

//$--GetServiceStopEvent-------------------------------------------------------
//  Returns the handle for the service stop event.
// -----------------------------------------------------------------------------
HANDLE GetServiceStopEvent(            // RETURNS: handle to stop event
    VOID);                              // no arguments

//$--GetServiceInstance--------------------------------------------------------
//  Returns the handle for the service instance.
// -----------------------------------------------------------------------------
HANDLE GetServiceInstance(             // RETURNS: handle to service instance
    VOID);                              // no arguments

//$--HServiceCreateThread-----------------------------------------------------------
//  Create a wrapped thread.
// -----------------------------------------------------------------------------
HANDLE HServiceCreateThread(                            // RETURNS: handle
    IN  LPLONG lplStartThreads,                     // number of running threads
    IN  LPLONG lplStopThreads,                      // number of stopped threads
    IN  LPSECURITY_ATTRIBUTES lpThreadAttributes,   // thread attributes
    IN  DWORD dwStackSize,                          // stack size
    IN  LPTHREAD_START_ROUTINE lpStartAddress,      // start address
    IN  LPVOID lpParameter,                         // parameter
    IN  DWORD dwCreationFlags,                      // creation flags
    OUT LPDWORD lpThreadId);                        // thread ID

//$--SetServiceExitCode---------------------------------------------------------
//  This function is called by the application to set the service exit code.
//
//  dwWin32ExitCode
//
//      - specifies a Win32 error code that the service uses to
//        report an error that occurs when it is starting or
//        stopping. To return an error code specific to the service,
//        the service must set this value to
//        ERROR_SERVICE_SPECIFIC_ERROR to indicate that the
//        dwServiceSpecificExitCode member contains the error code.
//        The service should set this value to NO_ERROR when it is
//        running and on normal termination. 
//
//  dwServiceSpecificExitCode
//
//      - specifies a service specific error code that the
//        service returns when an error occurs while the service is
//        starting or stopping. This value is ignored unless the
//        dwWin32ExitCode member is set to ERROR_SERVICE_SPECIFIC_ERROR. 
//      
// -----------------------------------------------------------------------------
VOID SetServiceExitCode(
    IN DWORD dwWin32ExitCode,           // Win32 exit code
    IN DWORD dwServiceSpecificExitCode);// service specific exit code

//$--HrServiceConfirmStop----------------------------------------------------
//  This function is called by the application to indicate that it has stopped.
// -----------------------------------------------------------------------------
HRESULT HrServiceConfirmStop(        // RETURNS: return code
    VOID);                              // no arguments

//$--HrServiceGetName--------------------------------------------------------
//  The HrServiceGetName function can be used by any thread to get the
//  service name after the service has been started. lpszName must point to a
//  block of memory at least MAX_SERVICE_NAME_LENGTH+1 bytes in length.
// -----------------------------------------------------------------------------
HRESULT HrServiceGetName(            // RETURNS: return code
    OUT LPSTR lpszName);                // pointer to service name buffer

//$--HrServiceGetArgv--------------------------------------------------------
//  The HrServiceGetArgv function can be used by any thread to get the
//  service argv[] after the service has been started.
// -----------------------------------------------------------------------------
HRESULT HrServiceGetArgv(            // RETURNS: return code
    OUT DWORD  *lpdwArgc,               // pointer to argc address variable
    OUT LPSTR **lppszArgv);             // pointer to argv[] address variable

//$--FServiceReportStatus-------------------------------------------------------
//  This function is called by the private _ServiceMain() and
//  ServCtrlHandler() functions to update the service's status
//  to the service control manager.
// -----------------------------------------------------------------------------
BOOL FServiceReportStatus(              // RETURNS: TRUE if successful
    IN DWORD dwCurrentState,            // current state of service
    IN DWORD dwWin32ExitCode,           // service Win32 exit code
    IN DWORD dwServiceSpecificExitCode, // service specific exit code
    IN DWORD dwCheckPoint,              // check point number
    IN DWORD dwWaitHint);               // time to wait

//$--ServiceStop-------------------------------------------------------------
//  This function can be used by any thread to stop the service.
// -----------------------------------------------------------------------------
VOID ServiceStop(                    // RETURNS: nothing
    VOID);                              // no argument


//$--HrServiceWaitForControl----------------------------------------------------
//  The HrServiceWaitForControl function can be used by any thread to get or
//  wait for service control after the service has been started.
// -----------------------------------------------------------------------------
HRESULT HrServiceWaitForControl(        // RETURNS: return code
    IN DWORD dwTimeout,                 // time-out interval in milliseconds
    OUT EDK_SERVICE_CONTROL_T *pedksc); // pointer to service name buffer

//$--HrServiceWaitForContinue---------------------------------------------------
//  The HrServiceWaitForContinue function can be used by any thread to get or
//  wait for service control after the service has been started.
// -----------------------------------------------------------------------------
HRESULT HrServiceWaitForContinue(       // RETURNS: return code
    IN DWORD dwTimeout,                 // time-out interval in milliseconds
    OUT EDK_SERVICE_CONTROL_T *pedksc); // pointer to service name buffer

//$--HrServiceWaitForStop-------------------------------------------------------
//  The HrServiceWaitForStop function can be used by any thread to get or
//  wait for service control after the service has been started.
// -----------------------------------------------------------------------------
HRESULT HrServiceWaitForStop(           // RETURNS: return code
    IN DWORD dwTimeout,                 // time-out interval in milliseconds
    OUT EDK_SERVICE_CONTROL_T *pedksc); // pointer to service name buffer

//$--HrServiceProcessControl---------------------------------------------------
//  Check for service control
// -----------------------------------------------------------------------------
HRESULT HrServiceProcessControl(       // RETURNS: return code
    VOID);                              // no arguments

//
//  The following service functions and extern variables are defined by the
//  application writer.
//

//$--HrServiceStartup---------------------------------------------------------
//  This function is called at startup to initialize the NT service.
//------------------------------------------------------------------------------
HRESULT HrServiceStartup(             // RETURNS: return code
    IN HINSTANCE hInstance,             // handle of current instance
    IN HINSTANCE hPrevInstance,         // handle of previous instance
    IN HWND hwndMainWindow,             // handle to main window
    IN LPSTR pszCmdLine);               // pointer to command line

//$--ServiceMain--------------------------------------------------------------
//  This function is given its own thread to execute.
//------------------------------------------------------------------------------
void ServiceMain(                     // RETURNS: nothing
    IN HANDLE hShutdownEvent);          // Handle to Shutdown event object

//$--HrServiceShutdown--------------------------------------------------------
//  This function is called when the user wants to shutdown.
//------------------------------------------------------------------------------
HRESULT HrServiceShutdown(            // RETURNS: return value for WinMain
    VOID);                              // No arguments

//------------------------------------------------------------------------------

extern CHAR szAppName[];               // WNDCLASS class name
extern CHAR szWindowTitle[];           // Application window title

//------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
