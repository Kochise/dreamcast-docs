/*++

Copyright (c) 1995  Microsoft Corporation

Module:

    ppcload.h

Purpose:

    This include file is the public header file for the PocketPC Load program (PPCLOAD.DLL)

--*/

#ifndef PPCLOAD_INCLUDED
#define PPCLOAD_INCLUDED

//
// Simplified set of error codes returned by the PocketPC Load program
//

typedef DWORD LOADERROR;

#define LOAD_SUCCESS            0
#define LOAD_OUTOFSTORAGE       1   // out of memory on the Pegasus
#define LOAD_CANCELLEDBYUSER    2   // loading cancelled by the user
#define LOAD_INVALID_PARAMETER  3   // invalid parameter in the command line parameters
#define LOAD_FAILED             4   // generic load failure
#define LOAD_FAILEDCANTCLEANUP  5   // load failure, and cannot clean-up what was done to the Pegasus
#define LOAD_DISCONNECTED       6   // disconnection in communications
#define LOAD_CANT_CREATE_DIR    7   // cannot create the destination directory
#define LOAD_REG_ERROR          8   // cannot create the registry entry
#define LOAD_ERROR              9   // not used
#define LOAD_ALREADY_LOADING   10   // already loading - cannot continue until first Load() is done


/////////////////////////////////////////////////////////
//
// Load_PegCpuType:
//      Retrieves the shortened name of the Pegasus CPU type
//
// Arguments:
//      lpszCpu     - string to store the CPU type, allocated/deallocated by caller
//
// Return Values:
//      TRUE        - CPU type successfully retrieved
//      FALSE       - an error occurred during the retrieval, or an unknown CPU type was found
//
// Notes:
//      - For this function to return a CPU type, Pegasus Manager must have previously
//        connected to the Pegasus at least once
//      - Currently returns the following strings in "lpszCpu"
//              SH3
//              MIPS
//
BOOL WINAPI
Load_PegCpuType (
    OUT LPSTR   lpszCpu
);

/////////////////////////////////////////////////////////
//
// Load_Init:
//      Starts the RPC services
//
// Arguments:
//      None
//
// Return Values:
//      LOAD_SUCCESS    - successfully started the RPC services
//      LOAD_FAILURE    - otherwise
//
// Notes:
//      - This function must be called before "Load()"
//      - The function "Load_Exit()" must be called at a later time, to stop the RPC services
//
LOADERROR WINAPI
Load_Init ();

/////////////////////////////////////////////////////////
//
// Load_AlreadyInstalled:
//      Determines if the application has already been installed on the Pegasus
//
// Arguments:
//      lpszAppName     - the name of your application
//
// Return Values:
//      FALSE           - not currently installed
//      TRUE            - currently installed, or an error occurred
//
// Notes:
//      - This function requires "Load_Init()" to have been previously called
//      - If an error occurred during this function, it returns TRUE, so that the caller
//        can prevent accidental overwriting
//
BOOL WINAPI
Load_AlreadyInstalled (
    IN LPSTR    lpszAppName
);

/////////////////////////////////////////////////////////
//
// Load_PegFreeSpace:
//      Returns the memory remaining on the Pegasus in bytes
//
// Arguments:
//      None
//
// Return Values:
//      - the amount of memory remaining on the Pegasus in bytes
//
// Notes:
//      - This function requires "Load_Init()" to have been previously called
//
DWORD WINAPI
Load_PegFreeSpace ();

/////////////////////////////////////////////////////////
//
// Load:
//      The main entry point to download an application from the desktop to the Pegasus
//
// Arguments:
//      hwndParent      - parent window handler, used for displaying the progress bar
//      lpszCmdLine     - command line parameters to be parsed:
//                             <cpu_type> <app_name> <install_directory> <total_bytes_to_copy>
//                             <user_name> <user_company> <load_file1> <load_file2> ...
//
// Return Values:
//      - a LOADERROR error code
//
// Notes:
//      - This function requires "Load_Init()" to have been previously called
//
LOADERROR WINAPI
Load (
    IN HWND     hwndParent,
    IN LPSTR    lpszCmdLine
);

/////////////////////////////////////////////////////////
//
// Load_RegisterFileInfo:
//      This function registers the file information with the
//      Pegasus Manager so that Pegasus Manager can display
//      the right file type and icon. 
//
// Arguments:
//      szFileName  - Application name with ext but without the path.
//      szIconFile  - File/Module name containing the icon, with the path.
//      szFileType  - File Type. Currently not being used 
//      iIcon       - Indes to the icon.
//
// Return Values:
//      - a LOADERROR error code
//
// Notes:
//      If the app does not not register file info with Pegasus 
//      Manager it will get the default icon.
//
LOADERROR WINAPI 
Load_RegisterFileInfo (
    IN LPCSTR  szFileName,
    IN LPCSTR  szIconFile,
    IN LPCSTR  szFileType,
    IN int     iIcon
);

/////////////////////////////////////////////////////////
//
// Load_Exit:
//      Stops the RPC services
//
// Arguments:
//      None
//
// Return Values:
//      None
//
// Notes:
//      - This function requires "Load_Init()" to have been previously called
//
void WINAPI
Load_Exit ();

#endif  // PPCLOAD_INCLUDED
